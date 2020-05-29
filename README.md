Similar to [dwm-flexipatch](https://github.com/bakkeby/dwm-flexipatch) this dmenu 4.9 (750b30, 2019-03-03) project has a different take on patching. It uses preprocessor directives to decide whether or not to include a patch during build time. Essentially this means that this build, for better or worse, contains both the patched _and_ the original code. The aim being that you can select which patches to include and the build will contain that code and nothing more.

For example to include the `alpha` patch then you would only need to flip this setting from 0 to 1 in [patches.h](https://github.com/bakkeby/dmenu-flexipatch/blob/master/patches.def.h):
```c
#define ALPHA_PATCH 1
```

Once you have found out what works for you and what doesn't then you should be in a better position to choose patches should you want to start patching from scratch.

Alternatively if you have found the patches you want, but don't want the rest of the flexipatch entanglement on your plate then you may want to have a look at [flexipatch-finalizer](https://github.com/bakkeby/flexipatch-finalizer); a custom pre-processor tool that removes all the unused flexipatch code leaving you with a build that contains the patches you selected.

Refer to [https://tools.suckless.org/dmenu/](https://tools.suckless.org/dmenu/) for details on dmenu, how to install it and how it works.

---

### Changelog:

2020-05-29 - Added the alpha patch (derived from Baitinq's [build](https://github.com/Baitinq/dmenu))

2020-04-05 - Added fuzzyhighlight patch

2020-02-09 - Added revised border patch (adding command line parameter for setting border width)

2019-12-29 - Added xresources patch

2019-10-16 - Introduced [flexipatch-finalizer](https://github.com/bakkeby/flexipatch-finalizer)

2019-09-18 - Added border, center, fuzzymatch, incremental, initialtext, instant, line-height, mouse-support, navhistory, non-blocking-stdin, password, pipeout, printinputtext, rejectnomatch, scroll, vertfull, wmtype and xyw patches

### Patches included:

   - [alpha](https://github.com/bakkeby/patches/blob/master/dmenu/dmenu-alpha-4.9_20190303_190303.diff)
      - adds transparency for the dmenu window

   - [border](http://tools.suckless.org/dmenu/patches/border/)
      - adds a border around the dmenu window

   - [center](https://tools.suckless.org/dmenu/patches/center/)
      - this patch centers dmenu in the middle of the screen

   - [fuzzyhighlight](https://tools.suckless.org/dmenu/patches/fuzzyhighlight/)
      - intended to be combined with the fuzzymatch patch, this makes it so that fuzzy matches are highlighted

   - [fuzzymatch](https://tools.suckless.org/dmenu/patches/fuzzymatch/)
      - adds support for fuzzy-matching to dmenu, allowing users to type non-consecutive portions of the string to be matched

   - [incremental](https://tools.suckless.org/dmenu/patches/incremental/)
      - this patch causes dmenu to print out the current text each time a key is pressed

   - [initialtext](https://tools.suckless.org/dmenu/patches/initialtext/)
      - adds an option to provide preselected text

   - [instant](https://tools.suckless.org/dmenu/patches/instant/)
      - adds a flag that will cause dmenu to select an item immediately if there is only one matching option left

   - [line-height](http://tools.suckless.org/dmenu/patches/line-height/)
      - adds a '-h' option which sets the minimum height of a dmenu line
      - this helps integrate dmenu with other UI elements that require a particular vertical size

   - [mouse-support](https://tools.suckless.org/dmenu/patches/mouse-support/)
      - adds basic mouse support for dmenu

   - [navhistory](https://tools.suckless.org/dmenu/patches/navhistory/)
      - provides dmenu the ability for history navigation similar to that of bash

   - [non-blocking-stdin](https://tools.suckless.org/dmenu/patches/non_blocking_stdin/)
      - this is a patch to have dmenu read stdin in a non blocking way, making it wait for input both from stdin and from X
      - this means that you can continue feeding dmenu while you type
      - the patch is meant to be used along with the incremental patch in order to use stdout to feed stdin

   - [password](https://tools.suckless.org/dmenu/patches/password/)
      - with this patch dmenu will not directly display the keyboard input, but instead replace it with dots
      - all data from stdin will be ignored

   - [pipeout](https://tools.suckless.org/dmenu/patches/pipeout/)
      - this patch allows the selected text to be piped back out with dmenu
      - this can be useful if you want to display the output of a command on the screen

   - [prefix-completion](https://tools.suckless.org/dmenu/patches/prefix-completion/)
      - changes the behaviour of matched items and the Tab key to allow tab completion

   - [printinputtext](https://tools.suckless.org/dmenu/patches/printinputtext/)
      - this patch adds a flag (-t) which makes Return key ignore selection and print the input text to stdout
      - the flag basically swaps the functions of Return and Shift+Return hotkeys

   - [rejectnomatch](https://tools.suckless.org/dmenu/patches/reject-no-match/)
      - adds a new flag to dmenu with which text input will be rejected if it would result in no matching item

   - [scroll](https://tools.suckless.org/dmenu/patches/scroll/)
      - this patch adds support for text scrolling
      - it doesn't append '...' for long input anymore as it can handle long text

   - [vertfull](https://tools.suckless.org/dmenu/patches/vertfull/)
      - prevents dmenu from indenting items at the same level as the prompt length

   - [wmtype](https://github.com/Baitinq/dmenu/blob/master/patches/dmenu-wm_type.diff)
      - adds extended window manager hints such as \_NET_WM_WINDOW_TYPE and \_NET_WM_WINDOW_TYPE_DOCK

   - [xresources](https://tools.suckless.org/dmenu/patches/xresources/)
      - allows dmenu to read font and colors from Xresources
      - note that with this patch the Xresources settings takes precedence over command line arguments

   - [xyw](https://tools.suckless.org/dmenu/patches/xyw/)
      - adds options for specifying dmenu window position and width
