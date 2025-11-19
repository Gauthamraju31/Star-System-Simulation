/**
 * @file x11.c
 * @brief X11 window management and event handling implementation
 * 
 * This file implements the X11-based graphical interface for the solar
 * system simulation, including window creation, event handling, and
 * rendering functions.
 */

#include "x11.h"

/** @brief External reference to the global running flag */
extern bool running;

/**
 * @brief Initialize X11 display and create the application window
 * 
 * Opens a connection to the X display, creates a simple window with
 * specified dimensions, sets up event handling, and prepares the
 * graphics context for drawing.
 * 
 * @param x11 Pointer to X11Disp structure to initialize
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 * @return true if initialization succeeded, false on error
 */
bool init_x(X11Disp *x11, unsigned int width, unsigned int height) {
    if (!x11) return false;

    x11->width = width;
    x11->height = height;

    x11->display = XOpenDisplay(NULL);
    if (!x11->display) {
        fprintf(stderr, "Error: Cannot open X display.\n");
        return false;
    }

    x11->screen = DefaultScreen(x11->display);
    unsigned long black = BlackPixel(x11->display, x11->screen);
    unsigned long white = WhitePixel(x11->display, x11->screen);

    x11->window = XCreateSimpleWindow(
        x11->display,
        DefaultRootWindow(x11->display),
        0, 0,
        width, height,
        5,
        white,
        black
    );

    XSetStandardProperties(
        x11->display, x11->window,
        "Star System", "Star!",
        None, NULL, 0, NULL
    );

    XSelectInput(
        x11->display, x11->window,
        ExposureMask | ButtonPressMask | KeyPressMask
    );

    x11->gc = XCreateGC(x11->display, x11->window, 0, 0);
    XSetBackground(x11->display, x11->gc, white);
    XSetForeground(x11->display, x11->gc, black);

    XClearWindow(x11->display, x11->window);
    XMapRaised(x11->display, x11->window);

    return true;
}

/**
 * @brief Process pending X11 events
 * 
 * Handles all pending events in the X11 event queue. Currently supports:
 * - KeyPress events: 'q' key quits the application
 * - ClientMessage events: Window close button
 * 
 * @param display X11 display connection
 * @param window Window handle for which to process events
 */
void handle_x11_events(Display *display, Window window) {
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);

            if (key == XK_q) {
                running = false;
                return;
            }
        }

        if (event.type == ClientMessage) {
            running = false;
            return;
        }
    }
}

/**
 * @brief Clean up and close the X11 display
 * 
 * Frees the graphics context, destroys the window, and closes the
 * display connection. Safe to call multiple times or with partially
 * initialized structures.
 * 
 * @param x11 Pointer to X11Disp structure to clean up
 */
void close_x(X11Disp *x11) {
    if (!x11 || !x11->display) return;

    XFreeGC(x11->display, x11->gc);
    XDestroyWindow(x11->display, x11->window);
    XCloseDisplay(x11->display);

    x11->display = NULL;
}

/**
 * @brief Clear the window in preparation for redrawing
 * 
 * Clears the entire window to the background color, preparing
 * it for the next frame of rendering.
 * 
 * @param x11 Pointer to X11Disp structure
 */
void redraw_x(X11Disp *x11) {
    if (!x11 || !x11->display) return;
    XClearWindow(x11->display, x11->window);
}
