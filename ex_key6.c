#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>

int main() {
    Display *dpy = XOpenDisplay(NULL);
    XkbStateRec state;
    XkbGetState(dpy, XkbUseCoreKbd, &state);

    int group = state.group;
    int new_group = (group + 1) % 2;

    XkbLockGroup(dpy, XkbUseCoreKbd, new_group);
    printf ("Current, New: %d, %d\n", group, new_group);

    XCloseDisplay(dpy);
    return 0;
}
