# dmenu version
VERSION = 5.4

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
# OpenBSD (uncomment)
#FREETYPEINC = $(X11INC)/freetype2
#MANPREFIX = ${PREFIX}/man

# Uncomment on RHEL for strcasecmp
#EXTRAFLAGS=-D_GNU_SOURCE

# Uncomment for the alpha patch / ALPHA_PATCH
#XRENDER = -lXrender

# Uncomment for the bidi patch / BIDI_PATCH
#BIDILIBS = `pkg-config --libs fribidi`
#BIDIINC = `pkg-config --cflags fribidi`

# Uncomment for the pango patch / PANGO_PATCH
#PANGOINC = `pkg-config --cflags xft pango pangoxft`
#PANGOLIB = `pkg-config --libs xft pango pangoxft`

# includes and libs
INCS = -I$(X11INC) -I$(FREETYPEINC) $(PANGOINC) $(BIDIINC)
LIBS = -L$(X11LIB) -lX11 $(XINERAMALIBS) $(FREETYPELIBS) -lm $(XRENDER) $(PANGOLIB) $(BIDILIBS)

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" $(XINERAMAFLAGS) $(EXTRAFLAGS)
CFLAGS   = -std=c99 -pedantic -Wall -Os $(INCS) $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# compiler and linker
CC = cc
