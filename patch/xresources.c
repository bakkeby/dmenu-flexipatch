#include <X11/Xresource.h>

void
readxresources(void)
{
	XrmInitialize();

	char* xrm;
	if ((xrm = XResourceManagerString(drw->dpy))) {
		char *type;
		XrmDatabase xdb = XrmGetStringDatabase(xrm);
		XrmValue xval;

		if (XrmGetResource(xdb, "dmenu.font", "*", &type, &xval))
			#if PANGO_PATCH
			strcpy(font, xval.addr);
			#else
			fonts[0] = strdup(xval.addr);
			#endif // PANGO_PATCH
		#if !PANGO_PATCH
		else
			fonts[0] = strdup(fonts[0]);
		#endif // PANGO_PATCH
		if (XrmGetResource(xdb, "dmenu.background", "*", &type, &xval))
			colors[SchemeNorm][ColBg] = strdup(xval.addr);
		else
			colors[SchemeNorm][ColBg] = strdup(colors[SchemeNorm][ColBg]);
		if (XrmGetResource(xdb, "dmenu.foreground", "*", &type, &xval))
			colors[SchemeNorm][ColFg] = strdup(xval.addr);
		else
			colors[SchemeNorm][ColFg] = strdup(colors[SchemeNorm][ColFg]);
		if (XrmGetResource(xdb, "dmenu.selbackground", "*", &type, &xval))
			colors[SchemeSel][ColBg] = strdup(xval.addr);
		else
			colors[SchemeSel][ColBg] = strdup(colors[SchemeSel][ColBg]);
		if (XrmGetResource(xdb, "dmenu.selforeground", "*", &type, &xval))
			colors[SchemeSel][ColFg] = strdup(xval.addr);
		else
			colors[SchemeSel][ColFg] = strdup(colors[SchemeSel][ColFg]);
		if (XrmGetResource(xdb, "dmenu.outbackground", "*", &type, &xval))
			colors[SchemeOut][ColBg] = strdup(xval.addr);
		else
			colors[SchemeOut][ColBg] = strdup(colors[SchemeOut][ColBg]);
		if (XrmGetResource(xdb, "dmenu.outforeground", "*", &type, &xval))
			colors[SchemeOut][ColFg] = strdup(xval.addr);
		else
			colors[SchemeOut][ColFg] = strdup(colors[SchemeOut][ColFg]);
		#if MORECOLOR_PATCH
		if (XrmGetResource(xdb, "dmenu.midbackground", "*", &type, &xval))
			colors[SchemeMid][ColBg] = strdup(xval.addr);
		else
			colors[SchemeMid][ColBg] = strdup(colors[SchemeMid][ColBg]);
		if (XrmGetResource(xdb, "dmenu.midforeground", "*", &type, &xval))
			colors[SchemeMid][ColFg] = strdup(xval.addr);
		else
			colors[SchemeMid][ColFg] = strdup(colors[SchemeMid][ColFg]);
		#endif // MORECOLOR_PATCH
		#if HIGHLIGHT_PATCH || FUZZYHIGHLIGHT_PATCH
		if (XrmGetResource(xdb, "dmenu.selhlbackground", "*", &type, &xval))
			colors[SchemeSelHighlight][ColBg] = strdup(xval.addr);
		else
			colors[SchemeSelHighlight][ColBg] = strdup(colors[SchemeSelHighlight][ColBg]);
		if (XrmGetResource(xdb, "dmenu.selhlforeground", "*", &type, &xval))
			colors[SchemeSelHighlight][ColFg] = strdup(xval.addr);
		else
			colors[SchemeSelHighlight][ColFg] = strdup(colors[SchemeSelHighlight][ColFg]);
		if (XrmGetResource(xdb, "dmenu.hlbackground", "*", &type, &xval))
			colors[SchemeNormHighlight][ColBg] = strdup(xval.addr);
		else
			colors[SchemeNormHighlight][ColBg] = strdup(colors[SchemeNormHighlight][ColBg]);
		if (XrmGetResource(xdb, "dmenu.hlforeground", "*", &type, &xval))
			colors[SchemeNormHighlight][ColFg] = strdup(xval.addr);
		else
			colors[SchemeNormHighlight][ColFg] = strdup(colors[SchemeNormHighlight][ColFg]);
		#endif // HIGHLIGHT_PATCH | FUZZYHIGHLIGHT_PATCH
		#if HIGHPRIORITY_PATCH
		if (XrmGetResource(xdb, "dmenu.hpbackground", "*", &type, &xval))
			colors[SchemeHp][ColBg] = strdup(xval.addr);
		else
			colors[SchemeHp][ColBg] = strdup(colors[SchemeHp][ColBg]);
		if (XrmGetResource(xdb, "dmenu.hpforeground", "*", &type, &xval))
			colors[SchemeHp][ColFg] = strdup(xval.addr);
		else
			colors[SchemeHp][ColFg] = strdup(colors[SchemeHp][ColFg]);
		#endif // HIGHPRIORITY_PATCH
		#if EMOJI_HIGHLIGHT_PATCH
		if (XrmGetResource(xdb, "dmenu.hoverbackground", "*", &type, &xval))
			colors[SchemeHover][ColBg] = strdup(xval.addr);
		else
			colors[SchemeHover][ColBg] = strdup(colors[SchemeHover][ColBg]);
		if (XrmGetResource(xdb, "dmenu.hoverforeground", "*", &type, &xval))
			colors[SchemeHover][ColFg] = strdup(xval.addr);
		else
			colors[SchemeHover][ColFg] = strdup(colors[SchemeHover][ColFg]);
		if (XrmGetResource(xdb, "dmenu.greenbackground", "*", &type, &xval))
			colors[SchemeGreen][ColBg] = strdup(xval.addr);
		else
			colors[SchemeGreen][ColBg] = strdup(colors[SchemeGreen][ColBg]);
		if (XrmGetResource(xdb, "dmenu.greenforeground", "*", &type, &xval))
			colors[SchemeGreen][ColFg] = strdup(xval.addr);
		else
			colors[SchemeGreen][ColFg] = strdup(colors[SchemeGreen][ColFg]);
		if (XrmGetResource(xdb, "dmenu.yellowbackground", "*", &type, &xval))
			colors[SchemeYellow][ColBg] = strdup(xval.addr);
		else
			colors[SchemeYellow][ColBg] = strdup(colors[SchemeYellow][ColBg]);
		if (XrmGetResource(xdb, "dmenu.yellowforeground", "*", &type, &xval))
			colors[SchemeYellow][ColFg] = strdup(xval.addr);
		else
			colors[SchemeYellow][ColFg] = strdup(colors[SchemeYellow][ColFg]);
		if (XrmGetResource(xdb, "dmenu.bluebackground", "*", &type, &xval))
			colors[SchemeBlue][ColBg] = strdup(xval.addr);
		else
			colors[SchemeBlue][ColBg] = strdup(colors[SchemeBlue][ColBg]);
		if (XrmGetResource(xdb, "dmenu.blueforeground", "*", &type, &xval))
			colors[SchemeBlue][ColFg] = strdup(xval.addr);
		else
			colors[SchemeBlue][ColFg] = strdup(colors[SchemeBlue][ColFg]);
		if (XrmGetResource(xdb, "dmenu.purplebackground", "*", &type, &xval))
			colors[SchemePurple][ColBg] = strdup(xval.addr);
		else
			colors[SchemePurple][ColBg] = strdup(colors[SchemePurple][ColBg]);
		if (XrmGetResource(xdb, "dmenu.purpleforeground", "*", &type, &xval))
			colors[SchemePurple][ColFg] = strdup(xval.addr);
		else
			colors[SchemePurple][ColFg] = strdup(colors[SchemePurple][ColFg]);
		if (XrmGetResource(xdb, "dmenu.redbackground", "*", &type, &xval))
			colors[SchemeRed][ColBg] = strdup(xval.addr);
		else
			colors[SchemeRed][ColBg] = strdup(colors[SchemeRed][ColBg]);
		if (XrmGetResource(xdb, "dmenu.redforeground", "*", &type, &xval))
			colors[SchemeRed][ColFg] = strdup(xval.addr);
		else
			colors[SchemeRed][ColFg] = strdup(colors[SchemeRed][ColFg]);
		#endif // EMOJI_HIGHLIGHT_PATCH
		XrmDestroyDatabase(xdb);
	}
}