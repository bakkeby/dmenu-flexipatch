static unsigned int using_vi_mode = 0;

void
vi_keypress(KeySym ksym, const XKeyEvent *ev)
{
	static const size_t quit_len = LENGTH(quit_keys);
	if (ev->state & ControlMask) {
		switch(ksym) {
		/* movement */
		case XK_d: /* fallthrough */
			if (next) {
				sel = curr = next;
				calcoffsets();
				goto draw;
			} else
				ksym = XK_G;
			break;
		case XK_u:
			if (prev) {
				sel = curr = prev;
				calcoffsets();
				goto draw;
			} else
				ksym = XK_g;
			break;
		case XK_p: /* fallthrough */
		case XK_P: break;
		case XK_c:
			cleanup();
			exit(1);
		case XK_Return: /* fallthrough */
		case XK_KP_Enter: break;
		default: return;
		}
	}

	switch(ksym) {
	/* movement */
	case XK_0:
		cursor = 0;
		break;
	case XK_dollar:
		if (text[cursor + 1] != '\0') {
			cursor = strlen(text) - 1;
			break;
		}
		break;
	case XK_b:
		movewordedge(-1);
		break;
	case XK_e:
		cursor = nextrune(+1);
		movewordedge(+1);
		if (text[cursor] == '\0')
			--cursor;
		else
			cursor = nextrune(-1);
		break;
	case XK_g:
		if (sel == matches) {
			break;
		}
		sel = curr = matches;
		calcoffsets();
		break;
	case XK_G:
		if (next) {
			/* jump to end of list and position items in reverse */
			curr = matchend;
			calcoffsets();
			curr = prev;
			calcoffsets();
			while (next && (curr = curr->right))
				calcoffsets();
		}
		sel = matchend;
		break;
	case XK_h:
		if (cursor)
			cursor = nextrune(-1);
		break;
	case XK_j:
		if (sel && sel->right && (sel = sel->right) == next) {
			curr = next;
			calcoffsets();
		}
		break;
	case XK_k:
		if (sel && sel->left && (sel = sel->left)->right == curr) {
			curr = prev;
			calcoffsets();
		}
		break;
	case XK_l:
		if (text[cursor] != '\0' && text[cursor + 1] != '\0')
			cursor = nextrune(+1);
		else if (text[cursor] == '\0' && cursor)
			--cursor;
		break;
	case XK_w:
		movewordedge(+1);
		if (text[cursor] != '\0' && text[cursor + 1] != '\0')
			cursor = nextrune(+1);
		else if (cursor)
			--cursor;
		break;
	/* insertion */
	case XK_a:
		cursor = nextrune(+1);
		/* fallthrough */
	case XK_i:
		using_vi_mode = 0;
		break;
	case XK_A:
		if (text[cursor] != '\0')
			cursor = strlen(text);
		using_vi_mode = 0;
		break;
	case XK_I:
		cursor = using_vi_mode = 0;
		break;
	case XK_p:
		if (text[cursor] != '\0')
			cursor = nextrune(+1);
		XConvertSelection(dpy, (ev->state & ControlMask) ? clip : XA_PRIMARY,
							utf8, utf8, win, CurrentTime);
		return;
	case XK_P:
		XConvertSelection(dpy, (ev->state & ControlMask) ? clip : XA_PRIMARY,
							utf8, utf8, win, CurrentTime);
		return;
	/* deletion */
	case XK_D:
		text[cursor] = '\0';
		if (cursor)
			cursor = nextrune(-1);
		match();
		break;
	case XK_x:
		cursor = nextrune(+1);
		insert(NULL, nextrune(-1) - cursor);
		if (text[cursor] == '\0' && text[0] != '\0')
			--cursor;
		match();
		break;
	/* misc. */
	case XK_Return:
	case XK_KP_Enter:
		puts((sel && !(ev->state & ShiftMask)) ? sel->text : text);
		if (!(ev->state & ControlMask)) {
			cleanup();
			exit(0);
		}
		if (sel)
			sel->out = 1;
		break;
	case XK_Tab:
		if (!sel)
			return;
		strncpy(text, sel->text, sizeof text - 1);
		text[sizeof text - 1] = '\0';
		cursor = strlen(text) - 1;
		match();
		break;
	default:
		for (size_t i = 0; i < quit_len; ++i)
			if (quit_keys[i].ksym == ksym &&
				(quit_keys[i].state & ev->state) == quit_keys[i].state) {
				cleanup();
				exit(1);
			}
	}

draw:
	drawmenu();
}
