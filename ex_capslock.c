#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>

int main(void)
{
    Display *display;
    XkbStateRec state;

    display = XOpenDisplay(NULL);
    if (!display)
    {
        fprintf(stderr, "Failed to open display\n");
        return 1;
    }


    //int opcode, error, major, minor;
    //Bool xkb_present = XkbQueryExtension(display, &opcode, &error, &major, &minor);
    int opcode, event_base, error_base, major, minor;
    Bool xkb_present = XkbQueryExtension(display, &opcode, &event_base, &error_base, &major, &minor);


    if (xkb_present) {
        printf("XKB extension is available.\n");
        printf("opcode: %d\n", opcode);
        printf("major: %d\n", major);
        printf("minor: %d\n", minor);
    } else {
        printf("XKB extension is not available.\n");
    }


    // XKB extension is available
    printf("XKB extension is available.\n");

    XkbGetState(display, XkbUseCoreKbd, &state);

    //if (state.loccked_mods & XkbModifierLockMask)
    /*
     * $2 = {group = 0 '\000', locked_group = 0 '\000', base_group = 0, 
     * latched_group = 0, mods = 2 '\002', base_mods = 0 '\000', 
     * latched_mods = 0 '\000', locked_mods = 2 '\002', compat_state = 2 '\002', 
     * grab_mods = 0 '\000', compat_grab_mods = 0 '\000', lookup_mods = 0 '\000', 
     * compat_lookup_mods = 0 '\000', ptr_buttons = 0}
     * 
     * locked_mods = 2 -> Caps lock is on, 0 -> Caps lock is off.
    */
    
    if (state.locked_mods & (1L<<1))
    {
        printf("Caps lock is on\n");
    }
    else
    {
        printf("Caps lock is off\n");
    }

    XCloseDisplay(display);
    return 0;
}
