static int composing;
static char preview[512] = "";

static size_t nextrunetext(const char *text, size_t position, int inc);
static size_t runebytes(const char *text, size_t n);
static size_t runechars(const char *text, size_t n);
static void preeditcaret(XIC xic, XPointer clientdata, XPointer calldata);
static int preeditstart(XIC xic, XPointer clientdata, XPointer calldata);
static void preeditdone(XIC xic, XPointer clientdata, XPointer calldata);
static void preeditdraw(XIC xic, XPointer clientdata, XPointer calldata);
static void init_input_method(XIM xim);
