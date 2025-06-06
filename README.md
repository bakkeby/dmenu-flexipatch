Similar to [dwm-flexipatch](https://github.com/bakkeby/dwm-flexipatch) this dmenu 5.3 (b1e217b,
2025-03-17) project has a different take on patching. It uses preprocessor directives to decide
whether or not to include a patch during build time. Essentially this means that this build, for
better or worse, contains both the patched _and_ the original code. The aim being that you can
select which patches to include and the build will contain that code and nothing more.

For example to include the `alpha` patch then you would only need to flip this setting from 0
to 1 in [patches.h](https://github.com/bakkeby/dmenu-flexipatch/blob/master/patches.def.h):
```c
#define ALPHA_PATCH 1
```

Once you have found out what works for you and what doesn't then you should be in a better position
to choose patches should you want to start patching from scratch.

Alternatively if you have found the patches you want, but don't want the rest of the flexipatch
entanglement on your plate then you may want to have a look at
[flexipatch-finalizer](https://github.com/bakkeby/flexipatch-finalizer); a custom pre-processor
tool that removes all the unused flexipatch code leaving you with a build that contains the patches
you selected.

Refer to [https://tools.suckless.org/dmenu/](https://tools.suckless.org/dmenu/) for details on
dmenu, how to install it and how it works.

Browsing patches? There is a [map of patches](https://coggle.it/diagram/YjT2DD6jBM9dayf3) diagram which tries to organise patches into categories.

---

### Changelog:

2025-05-28 - Added the colored caret and vi mode patches

2024-07-17 - Added the input method patch

2024-07-16 - Added the mouse motion support patch

2023-06-15 - Added the caret width patch

2022-09-05 - Removed the json patch due to maintenance and compatibility reasons, added the
             separator patch

2022-09-04 - Added the fzfexpect patch

2022-06-21 - Adding barpadding patch and relative input width patch

2022-03-02 - Bump to 5.1

2021-05-23 - Adding support for `ctrl+v` to paste and adding emoji-highlight patch

2021-05-17 - Added the restrict return, no sort, gridnav and plain-prompt (listfullwidth) patches

2021-05-15 - Added the tsv and printindex patches

2020-08-08 - Added the json, symbols, managed, morecolor, multi-selection and preselect patches

2020-08-05 - Added the grid, highlight, highpriority, dynamic options and numbers patches

2020-06-13 - Added the pango patch

2020-06-10 - Added the case-insensitive patch

2020-05-29 - Added the alpha patch (derived from Baitinq's [build](https://github.com/Baitinq/dmenu))
             and the color emoji patch

2020-04-05 - Added fuzzyhighlight patch

2020-02-09 - Added revised border patch (adding command line parameter for setting border width)

2019-12-29 - Added xresources patch

2019-10-16 - Introduced [flexipatch-finalizer](https://github.com/bakkeby/flexipatch-finalizer)

2019-09-18 - Added border, center, fuzzymatch, incremental, initialtext, instant, line-height,
             mouse-support, navhistory, non-blocking-stdin, password, pipeout, printinputtext,
             rejectnomatch, scroll, vertfull, wmtype and xyw patches

### Patches included:

   - [alpha](https://github.com/bakkeby/patches/blob/master/dmenu/dmenu-alpha-5.0_20210725_523aa08.diff)
      - adds transparency for the dmenu window

   - [barpadding](https://github.com/bakkeby/patches/wiki/barpadding)
      - adds padding for dmenu in similar fashion to the [barpadding](https://dwm.suckless.org/patches/barpadding/)
        patch for dwm

   - [border](http://tools.suckless.org/dmenu/patches/border/)
      - adds a border around the dmenu window

   - [caret-width](https://github.com/DarkSamus669/dmenu-patches/blob/main/dmenu-caretwidth-5.2.diff)
      - makes the caret width configurable and overridable via a command line option

   - [case-insensitive](http://tools.suckless.org/dmenu/patches/case-insensitive/)
      - makes dmenu case-insensitive by default, replacing the case-insensitive `-i` option with a
        case sensitive `-s` option

   - [center](https://tools.suckless.org/dmenu/patches/center/)
      - this patch centers dmenu in the middle of the screen

   - color_emoji
      - enables color emoji in dmenu by removing a workaround for a BadLength error in the Xft
        library when color glyphs are used
      - enabling this will crash dmenu on encountering such glyphs unless you also have an updated
        Xft library that can handle them

   - [colored caret](https://tools.suckless.org/dmenu/patches/colored-caret/)
      - adds the `SchemeCaret` colour scheme allowing customised styling of the caret

   - [dynamic_options](https://tools.suckless.org/dmenu/patches/dynamicoptions/)
      - adds a flag (`-dy`) which makes dmenu run the command given to it whenever input is changed
        with the current input as the last argument and update the option list according to the
        output of that command

   - [emoji-highlight](https://tools.suckless.org/dmenu/patches/emoji-highlight/)
      - this patch will allow for emojis on the left side with a colored background when selected

   - [fuzzyhighlight](https://tools.suckless.org/dmenu/patches/fuzzyhighlight/)
      - intended to be combined with the fuzzymatch patch, this makes it so that fuzzy matches are
        highlighted

   - [fuzzymatch](https://tools.suckless.org/dmenu/patches/fuzzymatch/)
      - adds support for fuzzy-matching to dmenu, allowing users to type non-consecutive portions
        of the string to be matched

   - [fzfexpect](https://github.com/DAFF0D11/dafmenu/blob/master/patches/dmenu-fzfexpect-5.1.diff)
      - adds fzf expect functionality in dmenu

   - [grid](https://tools.suckless.org/dmenu/patches/grid/)
      - allows dmenu's entries to be rendered in a grid by adding a new `-g` flag to specify the
        number of grid columns
      - the `-g` and `-l` options can be used together to create a G columns * L lines grid

   - [gridnav](https://tools.suckless.org/dmenu/patches/gridnav/)
      - adds the ability to move left and right through a grid (when using the grid patch)

   - [highlight](https://tools.suckless.org/dmenu/patches/highlight/)
      - this patch highlights the individual characters of matched text for each dmenu list entry

   - [highpriority](https://tools.suckless.org/dmenu/patches/highpriority/)
      - this patch will automatically sort the search result so that high priority items are shown
        first

   - [incremental](https://tools.suckless.org/dmenu/patches/incremental/)
      - this patch causes dmenu to print out the current text each time a key is pressed

   - [initialtext](https://tools.suckless.org/dmenu/patches/initialtext/)
      - adds an option to provide preselected text

   - input-method
      - adds support for input methods (fctix, ibus, etc.)

   - [instant](https://tools.suckless.org/dmenu/patches/instant/)
      - adds a flag that will cause dmenu to select an item immediately if there is only one
        matching option left

   - [~json~](https://tools.suckless.org/dmenu/patches/json/)
      - ~adds basic support for json files~

   - [line-height](http://tools.suckless.org/dmenu/patches/line-height/)
      - adds a `-h` option which sets the minimum height of a dmenu line
      - this helps integrate dmenu with other UI elements that require a particular vertical size

   - [managed](https://tools.suckless.org/dmenu/patches/managed/)
      - adds a `-wm` flag which sets override_redirect to false; thus letting your window manager
        manage the dmenu window
      - this may be helpful in contexts where you don't want to exclusively bind dmenu or want to
        treat dmenu more as a "window" rather than as an overlay

   - [morecolor](https://tools.suckless.org/dmenu/patches/morecolor/)
      - adds an additional color scheme for highlighting entries adjacent to the current selection

   - [mouse-support](https://tools.suckless.org/dmenu/patches/mouse-support/)
      - adds basic mouse support for dmenu

   - [multi-selection](https://tools.suckless.org/dmenu/patches/multi-selection/)
      - without this patch when you press `Ctrl+Enter` dmenu just outputs current item and it is
        not possible to undo that
      - with this patch dmenu will output all selected items only on exit
      - it is also possible to deselect any selected item

   - [navhistory](https://tools.suckless.org/dmenu/patches/navhistory/)
      - provides dmenu the ability for history navigation similar to that of bash

   - [no-sort](https://tools.suckless.org/dmenu/patches/no-sort/)
      - adds the `-S` option to disable sorting menu items after matching
      - useful, for example, when menu items are sorted by their frequency of use (using an
        external cache) and the most frequently selected items should always appear first regardless
        of how they were exact, prefix, or substring matches

   - [non-blocking-stdin](https://tools.suckless.org/dmenu/patches/non_blocking_stdin/)
      - this is a patch to have dmenu read stdin in a non blocking way, making it wait for input
        both from stdin and from X
      - this means that you can continue feeding dmenu while you type
      - the patch is meant to be used along with the incremental patch in order to use stdout to
        feed stdin

   - [numbers](https://tools.suckless.org/dmenu/patches/numbers/)
      - adds text which displays the number of matched and total items in the top right corner of
        dmenu

   - [pango](https://github.com/StillANixRookie/dmenu-pango/)
      - adds simple markup for dmenu using pango markup

   - [password](https://tools.suckless.org/dmenu/patches/password/)
      - with this patch dmenu will not directly display the keyboard input, but instead replace it
        with dots
      - all data from stdin will be ignored

   - [pipeout](https://tools.suckless.org/dmenu/patches/pipeout/)
      - this patch allows the selected text to be piped back out with dmenu
      - this can be useful if you want to display the output of a command on the screen

   - [plain-prompt](https://tools.suckless.org/dmenu/patches/listfullwidth/)
      - simple change that avoids colors for the prompt by making it use the same style as the
        rest of the input field

   - [prefix-completion](https://tools.suckless.org/dmenu/patches/prefix-completion/)
      - changes the behaviour of matched items and the Tab key to allow tab completion

   - [preselect](https://tools.suckless.org/dmenu/patches/preselect/)
      - adds an option `-ps` to preselect an item by providing the index that should be pre-selected

   - [printindex](https://tools.suckless.org/dmenu/patches/printindex/)
      - allows dmenu to print out the 0-based index of matched text instead of the matched text
        itself
      - this can be useful in cases where you would like to select entries from one array of text
        but index into another, or when you are selecting from an ordered list of non-unique items

   - [printinputtext](https://tools.suckless.org/dmenu/patches/printinputtext/)
      - this patch adds a flag `-t` which makes Return key ignore selection and print the input
        text to stdout
      - the flag basically swaps the functions of Return and Shift+Return hotkeys

   - [rejectnomatch](https://tools.suckless.org/dmenu/patches/reject-no-match/)
      - adds a new flag to dmenu with which text input will be rejected if it would result in no
        matching item

   - relative_input_width
      - prior to commit [e1e1de7](https://git.suckless.org/dmenu/commit/e1e1de7b3b8399cba90ddca9613f837b2dbef7b9.html)
        the input width was calculated based on the input options
      - this feature was removed in favour of hardcoding the input width to always take up 1/3rd of
        the available space
      - this patch adds that feature back in with some bespoke performance optimisations at the cost
        of accuracy and correctness

   - [restrict-return](https://tools.suckless.org/dmenu/patches/restrict-return/)
      - adds a `-1` option which disables Shift-Return and Ctrl-Return
      - this guarantees that dmenu will only output one item, and that item was read from stdin

   - [scroll](https://tools.suckless.org/dmenu/patches/scroll/)
      - this patch adds support for text scrolling
      - it doesn't append `...` for long input anymore as it can handle long text

   - [separator](https://tools.suckless.org/dmenu/patches/separator/)
      - adds `-d` and `-D` flags which separates the input into two halves; one half to be
        displayed in dmenu and the other to be printed to stdout

   - [symbols](https://tools.suckless.org/dmenu/patches/symbols/)
      - allows the symbols, which are printed in dmenu to indicate that either the input is too
        long or there are too many options to be shown in dmenu in one line, to be defined

   - [tsv](https://tools.suckless.org/dmenu/patches/tsv/)
      - makes dmenu split input lines at first tab character and only display first part, but it
        will perform matching on and output full lines as usual
      - can be useful if you want to separate data and representation

   - [vertfull](https://tools.suckless.org/dmenu/patches/vertfull/)
      - prevents dmenu from indenting items at the same level as the prompt length

   - [vi mode](https://tools.suckless.org/dmenu/patches/vi-mode/)
      - adds basic vi mode capabilities to dmenu

   - [wmtype](https://github.com/Baitinq/dmenu/blob/master/patches/dmenu-wm_type.diff)
      - adds extended window manager hints such as \_NET_WM_WINDOW_TYPE and \_NET_WM_WINDOW_TYPE_DOCK

   - [xresources](https://tools.suckless.org/dmenu/patches/xresources/)
      - allows dmenu to read font and colors from Xresources
      - note that with this patch the Xresources settings takes precedence over command line arguments

   - [xyw](https://tools.suckless.org/dmenu/patches/xyw/)
      - adds options for specifying dmenu window position and width
