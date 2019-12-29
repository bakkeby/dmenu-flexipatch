#include <X11/Xresource.h>

void
read_Xresources(void)
{
	XrmInitialize();

	char* xrm = XResourceManagerString(drw->dpy);
	if (xrm) {
		char *type;
		XrmDatabase xdb = XrmGetStringDatabase(xrm);
		XrmValue xval;

		if (XrmGetResource(xdb, "dmenu.font", "*", &type, &xval) == True) /* font or font set */
			fonts[0] = strdup(xval.addr);
		if (XrmGetResource(xdb, "dmenu.background", "*", &type, &xval) == True)  /* normal background color */
			colors[SchemeSel][ColBg] = strdup(xval.addr);
		if (XrmGetResource(xdb, "dmenu.foreground", "*", &type, &xval) == True)  /* normal foreground color */
			colors[SchemeNorm][ColFg] = strdup(xval.addr);
		if (XrmGetResource(xdb, "dmenu.selbackground", "*", &type, &xval) == True)  /* selected background color */
			colors[SchemeSel][ColBg] = strdup(xval.addr);
		if (XrmGetResource(xdb, "dmenu.selforeground", "*", &type, &xval) == True)  /* selected foreground color */
			colors[SchemeSel][ColFg] = strdup(xval.addr);

		XrmDestroyDatabase(xdb);
	}
}