#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    //int opcode, error, major, minor;
    //Bool xkb_present = XkbQueryExtension(display, &opcode, &error, &major, &minor);
    int opcode, event_base, error_base, major, minor;
    Bool xkb_present = XkbQueryExtension(display, &opcode, &event_base, &error_base, &major, &minor);

    if (xkb_present) {
        XkbStateRec state;
        XkbGetState(display, XkbUseCoreKbd, &state);

        // Check if the caps lock is on
        if (state.locked_mods & LockMask) {
            // Turn off the caps lock
            XkbLockModifiers(display, XkbUseCoreKbd, LockMask, 0);
        } else {
            // Turn on the caps lock
            XkbLockModifiers(display, XkbUseCoreKbd, LockMask, LockMask);
        }
    } else {
        printf("XKB extension is not available.\n");
    }

    XCloseDisplay(display);
    return 0;
}
