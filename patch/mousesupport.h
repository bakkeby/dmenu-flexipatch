static void buttonpress(XEvent *e);
static void clickitem(struct item *item, XButtonEvent *ev);
#if MOTION_SUPPORT_PATCH
static void motionevent(XButtonEvent *ev);
#endif // MOTION_SUPPORT_PATCH
