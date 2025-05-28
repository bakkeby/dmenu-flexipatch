typedef struct {
	KeySym ksym;
	unsigned int state;
} Key;

static void vi_keypress(KeySym ksym, const XKeyEvent *ev);
