#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    Display *dpy;
    int group;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return -1;
    }

    XkbStateRec state;
    XkbGetState(dpy, XkbUseCoreKbd, &state);
    group = state.group;

    if (group == 0) {
        XkbLockGroup(dpy, XkbUseCoreKbd, 1);
        printf ("Code: 1\n");
    } else {
        XkbLockGroup(dpy, XkbUseCoreKbd, 0);
        printf ("Code: 0\n");
    }

    XCloseDisplay(dpy);
    return 0;
}
