static size_t nextrunetext(const char *text, size_t position, int inc)
{
	ssize_t n;

	/* return location of next utf8 rune in the given direction (+1 or -1) */
	for (n = position + inc; n + inc >= 0 && (text[n] & 0xc0) == 0x80; n += inc)
		;
	return n;
}

/* return bytes from beginning of text to nth utf8 rune to the right */
static size_t runebytes(const char *text, size_t n)
{
	size_t ret;

	ret = 0;
	while (n-- > 0)
		ret += nextrunetext(text + ret, 0, 1);
	return ret;
}

/* return number of characters from beginning of text to nth byte to the right
 */
static size_t runechars(const char *text, size_t n)
{
	size_t ret, i;

	ret = i = 0;
	while (i < n) {
		i += nextrunetext(text + i, 0, 1);
		ret++;
	}
	return ret;
}

/* move caret on pre-edit text */
static void preeditcaret(XIC xic, XPointer clientdata, XPointer calldata)
{
	XIMPreeditCaretCallbackStruct *pcaret;

	(void)xic;
	pcaret = (XIMPreeditCaretCallbackStruct *)calldata;
	if (!pcaret)
		return;
	switch (pcaret->direction) {
	case XIMForwardChar:
		cursor = nextrune(+1);
		break;
	case XIMBackwardChar:
		cursor = nextrune(-1);
		break;
	case XIMForwardWord:
		movewordedge(+1);
		break;
	case XIMBackwardWord:
		movewordedge(-1);
		break;
	case XIMLineStart:
		cursor = 0;
		break;
	case XIMLineEnd:
		if (preview[cursor] != '\0')
			cursor = strlen(preview);
		break;
	case XIMAbsolutePosition:
		cursor = runebytes(text, pcaret->position);
		break;
	case XIMDontChange:
		/* do nothing */
		break;
	case XIMCaretUp:
	case XIMCaretDown:
	case XIMNextLine:
	case XIMPreviousLine:
		/* not implemented */
		break;
	}
	pcaret->position = runechars(preview, cursor);
}

/* start input method pre-editing */
static int preeditstart(XIC xic, XPointer clientdata, XPointer calldata)
{
	(void)xic;
	(void)calldata;
	(void)clientdata;
	composing = 1;
	printf("PREEDIT\n");
	return BUFSIZ;
}

/* end input method pre-editing */
static void preeditdone(XIC xic, XPointer clientdata, XPointer calldata)
{
	(void)xic;
	(void)clientdata;
	(void)calldata;
	printf("DONE\n");

	composing = 0;
}

/* draw input method pre-edit text */
static void preeditdraw(XIC xic, XPointer clientdata, XPointer calldata)
{
	XIMPreeditDrawCallbackStruct *pdraw;
	size_t beg, dellen, inslen, endlen;

	printf("DRAW\n");

	(void)xic;
	pdraw = (XIMPreeditDrawCallbackStruct *)calldata;
	if (!pdraw)
		return;

	/* we do not support wide characters */
	if (pdraw->text && pdraw->text->encoding_is_wchar == True) {
		fputs("warning: wchar is not supportecd; use utf8", stderr);
		return;
	}

	beg = runebytes(text, pdraw->chg_first);
	dellen = runebytes(preview + beg, pdraw->chg_length);
	inslen = pdraw->text ? runebytes(pdraw->text->string.multi_byte, pdraw->text->length) : 0;
	endlen = 0;
	if (beg + dellen < strlen(preview))
		endlen = strlen(preview + beg + dellen);

	/* we cannot change text past the end of our pre-edit string */

	if (beg + dellen >= BUFSIZ || beg + inslen >= BUFSIZ)
		return;

	/* get space for text to be copied, and copy it */
	memmove(preview + beg + inslen, preview + beg + dellen, endlen + 1);
	if (pdraw->text && pdraw->text->length)
		memcpy(preview + beg, pdraw->text->string.multi_byte, inslen);
	(preview + beg + inslen + endlen)[0] = '\0';

	/* get caret position */
	cursor = runebytes(text, pdraw->caret);
}

static void init_input_method(XIM xim)
{
	XVaNestedList preedit = NULL;
	XICCallback start, done, draw, caret;
	XIMStyle preeditstyle;
	XIMStyle statusstyle;
	XIMStyles *imstyles;
	int i;

	/* get styles supported by input method */
	if (XGetIMValues(xim, XNQueryInputStyle, &imstyles, NULL) != NULL)
		fputs("XGetIMValues: could not obtain input method values", stderr);

	/* check whether input method support on-the-spot pre-editing */
	preeditstyle = XIMPreeditNothing;
	statusstyle = XIMStatusNothing;
	for (i = 0; i < imstyles->count_styles; i++) {
		if (imstyles->supported_styles[i] & XIMPreeditCallbacks) {
			preeditstyle = XIMPreeditCallbacks;
			break;
		}
	}

	/* create callbacks for the input context */
	start.client_data = NULL;
	done.client_data = NULL;
	draw.client_data = (XPointer)text;
	caret.client_data = (XPointer)text;
	start.callback = (XICProc)preeditstart;
	done.callback = (XICProc)preeditdone;
	draw.callback = (XICProc)preeditdraw;
	caret.callback = (XICProc)preeditcaret;

	/* create list of values for input context */
	preedit = XVaCreateNestedList(0, XNPreeditStartCallback, &start, XNPreeditDoneCallback,
				      &done, XNPreeditDrawCallback, &draw, XNPreeditCaretCallback,
				      &caret, NULL);
	if (preedit == NULL)
		fputs("XVaCreateNestedList: could not create nested list", stderr);

	xic = XCreateIC(xim, XNInputStyle, preeditstyle | statusstyle, XNPreeditAttributes, preedit,
			XNClientWindow, win, XNFocusWindow, win, NULL);
	XFree(preedit);

	long eventmask;
	/* get events the input method is interested in */
	if (XGetICValues(xic, XNFilterEvents, &eventmask, NULL))
		fputs("XGetICValues: could not obtain input context values", stderr);

	XSelectInput(dpy, win,
		     ExposureMask | KeyPressMask | VisibilityChangeMask | ButtonPressMask |
			     PointerMotionMask | eventmask);
}
