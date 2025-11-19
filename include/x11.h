/**
 * @file x11.h
 * @brief X11 windowing and graphics interface
 * 
 * This header provides the interface for creating and managing the X11 window
 * used for rendering the solar system simulation.
 */

#ifndef _X11_H_
#define _X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// --- X11 Display Context ---

/**
 * @brief X11 display context structure
 * 
 * Encapsulates all the X11-specific state needed for rendering,
 * including the display connection, window, and graphics context.
 */
typedef struct {
    Display *display;      /**< X11 display connection */
    int screen;            /**< Screen number */
    Window window;         /**< Window handle */
    GC gc;                 /**< Graphics context for drawing */
    unsigned int width;    /**< Window width in pixels */
    unsigned int height;   /**< Window height in pixels */
} X11Disp;

// --- Function Declarations ---

/**
 * @brief Initialize the X11 display and create a window
 * 
 * Opens a connection to the X server, creates a window with the specified
 * dimensions, and sets up the graphics context for drawing.
 * 
 * @param x11 Pointer to X11Disp structure to initialize
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @return bool true on success, false on failure
 */
bool init_x(X11Disp *x11, unsigned int width, unsigned int height);

/**
 * @brief Process X11 events from the event queue
 * 
 * Handles keyboard input and window events. Currently supports:
 * - 'q' key to quit the application
 * - Window close events
 * 
 * @param display X11 display connection
 * @param window Window handle
 */
void handle_x11_events(Display *display, Window window);

/**
 * @brief Close the X11 display and release resources
 * 
 * Frees the graphics context, destroys the window, and closes the
 * display connection. Safe to call with NULL or partially initialized structures.
 * 
 * @param x11 Pointer to X11Disp structure to clean up
 */
void close_x(X11Disp *x11);

/**
 * @brief Clear the window for redrawing
 * 
 * Clears the entire window to prepare for the next frame of rendering.
 * 
 * @param x11 Pointer to X11Disp structure
 */
void redraw_x(X11Disp *x11);

#endif