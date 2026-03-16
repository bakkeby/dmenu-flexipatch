# dmenu - dynamic menu
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dmenu.c stest.c util.c
OBJ = $(SRC:.c=.o)

desktoponly = false

all: dmenu stest

.c.o:
	$(CC) -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

patches.h:
	cp patches.def.h $@

$(OBJ): arg.h config.h config.mk drw.h patches.h

dmenu: dmenu.o drw.o util.o
	$(CC) -o $@ dmenu.o drw.o util.o $(LDFLAGS)

stest: stest.o
	$(CC) -o $@ stest.o $(LDFLAGS)

clean:
	rm -f dmenu stest $(OBJ) dmenu-$(VERSION).tar.gz

dist: clean
	mkdir -p dmenu-$(VERSION)
ifeq ($(desktoponly), true)
	cp LICENSE Makefile README arg.h config.def.h config.mk dmenu.1\
		drw.h util.h dmenu_path dmenu_path_desktop dmenu_run dmenu_run_desktop stest.1 $(SRC)\
		dmenu-$(VERSION)
else
	cp LICENSE Makefile README arg.h config.def.h config.mk dmenu.1\
		drw.h util.h dmenu_path dmenu_run stest.1 $(SRC)\
		dmenu-$(VERSION)
endif
	tar -cf dmenu-$(VERSION).tar dmenu-$(VERSION)
	gzip dmenu-$(VERSION).tar
	rm -rf dmenu-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
ifeq ($(desktoponly), true)
	cp -f dmenu dmenu_path dmenu_path_desktop dmenu_run dmenu_run_desktop stest $(DESTDIR)$(PREFIX)/bin
else
	cp -f dmenu dmenu_path dmenu_run stest $(DESTDIR)$(PREFIX)/bin
endif
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu_path
ifeq ($(desktoponly), true)
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu_path_desktop
endif
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu_run
ifeq ($(desktoponly), true)
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dmenu_run_desktop
endif
	chmod 755 $(DESTDIR)$(PREFIX)/bin/stest
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < dmenu.1 > $(DESTDIR)$(MANPREFIX)/man1/dmenu.1
	sed "s/VERSION/$(VERSION)/g" < stest.1 > $(DESTDIR)$(MANPREFIX)/man1/stest.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/dmenu.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/stest.1

uninstall:
ifeq ($(desktoponly), true)
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu\
		$(DESTDIR)$(PREFIX)/bin/dmenu_path\
		$(DESTDIR)$(PREFIX)/bin/dmenu_path_desktop\
		$(DESTDIR)$(PREFIX)/bin/dmenu_run\
		$(DESTDIR)$(PREFIX)/bin/dmenu_run_desktop\
		$(DESTDIR)$(PREFIX)/bin/stest\
		$(DESTDIR)$(MANPREFIX)/man1/dmenu.1\
		$(DESTDIR)$(MANPREFIX)/man1/stest.1
else
	rm -f $(DESTDIR)$(PREFIX)/bin/dmenu\
		$(DESTDIR)$(PREFIX)/bin/dmenu_path\
		$(DESTDIR)$(PREFIX)/bin/dmenu_run\
		$(DESTDIR)$(PREFIX)/bin/stest\
		$(DESTDIR)$(MANPREFIX)/man1/dmenu.1\
		$(DESTDIR)$(MANPREFIX)/man1/stest.1
endif

.PHONY: all clean dist install uninstall
