/**
 * @file main.c
 * @brief Main entry point for the solar system simulation
 * 
 * This file contains the main simulation loop and core functions for:
 * - Converting colors to hexadecimal format for X11
 * - Drawing celestial bodies on the display
 * - Computing gravitational forces between all bodies
 * - Managing the simulation lifecycle
 * 
 * The simulation uses Newtonian physics to model gravitational interactions
 * between celestial bodies in a 2D projection of 3D space.
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // for usleep
#include <time.h>

#include "vector.h"
#include "physics.h"
#include "x11.h"
#include "log.h"
#include "config.h"

/**
 * @brief Convert RGB color components to hexadecimal format
 * 
 * Combines separate red, green, and blue components into a single
 * unsigned long value suitable for X11 color functions.
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @return unsigned long Packed hexadecimal color value
 */
unsigned long convert2Hex(unsigned int r, unsigned int g, unsigned int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

/**
 * @brief Draw a celestial body on the X11 display
 * 
 * Renders a sphere as a filled circle on the display. The position is
 * transformed from simulation space to screen space with appropriate
 * scaling and centering.
 * 
 * @param body Pointer to the sphere to draw
 * @param solar_display Pointer to the X11 display context
 */
void draw_body(Sphere *body, X11Disp *solar_display)
{
    int body_offset_x = (int)(body->position.x * solar_display->width) / 3 + solar_display->width / 2;
    int body_offset_y = (int)(body->position.y * solar_display->height) / 3 + solar_display->height / 2;
    int body_offset_r = (int)(body->radius * solar_display->height / 3);


    unsigned long body_color = convert2Hex(body->color.r, body->color.g, body->color.b);

    XSetForeground(solar_display->display, solar_display->gc, body_color);

    XFillArc(solar_display->display, solar_display->window, solar_display->gc,
             body_offset_x - body_offset_r, body_offset_y - body_offset_r,
             body_offset_r * 2, body_offset_r * 2, 0, 360 * 64);
}

/** @brief Global flag to control the main simulation loop */
bool running = true;

/** @brief Array of pointers to all celestial bodies in the simulation */
Sphere *planets[MAX_BODIES];

/** @brief Global configuration structure */
Config cfg;

/**
 * @brief Compute gravitational forces between all celestial bodies
 * 
 * Calculates pairwise gravitational forces using Newton's law of gravitation.
 * Uses the optimization that force on A due to B is equal and opposite to
 * force on B due to A (Newton's third law), so we only need to compute each
 * pair once.
 * 
 * Forces are accumulated in each body's force vector and will be used
 * in the next physics update step.
 * 
 * @param bodies Array of pointers to celestial bodies
 * @param count Number of bodies in the array
 */
void compute_forces(Sphere *bodies[], int count)
{
    // Reset all forces
    for (int i = 0; i < count; i++)
    {
        bodies[i]->force = (Vector){0, 0, 0};
    }

    // Compute pairwise gravitational forces
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            Vector f = gforce(bodies[i], bodies[j]);

            // Apply Newton's third law
            bodies[i]->force = vec_add(bodies[i]->force, f);
            bodies[j]->force = vec_sub(bodies[j]->force, f);
        }
    }
}

/**
 * @brief Main entry point for the solar system simulation
 * 
 * The main function performs the following steps:
 * 1. Loads configuration from file
 * 2. Initializes all celestial bodies
 * 3. Creates the X11 display window
 * 4. Runs the main simulation loop:
 *    - Processes user input
 *    - Computes gravitational forces
 *    - Updates momentum and positions
 *    - Renders all bodies
 * 5. Cleans up resources on exit
 * 
 * @return int 0 on successful exit, 1 on error
 */
int main()
{
    // Initialize logging
    log_info("Loading Configuration");

    // Load config
    if (!load_config("config.cfg", &cfg))
    {
        log_error("Failed to load configuration.");
        return 1;
    }
    log_info("Starting simulation");
    CURRENT_LOG_LEVEL = cfg.log_Level;
    log_info("No. of bodies %d", cfg.planet_count);

    const float dt = (float) cfg.timestep/10000.0;

    // Initialize planet state
    for (int i = 0; i < cfg.planet_count; i++)
    {
        planets[i] = sphere_create(cfg.bodies[i].position, cfg.bodies[i].radius, cfg.bodies[i].color, cfg.bodies[i].mass, cfg.bodies[i].momentum);
    }

    // Initialize display
    X11Disp x11;
    if (!init_x(&x11, cfg.resolution, cfg.resolution))
    {
        log_error("X11 initialization failed.");
        return 1;
    }

    while (running)
    {
        handle_x11_events(x11.display, x11.window);

        // Physics step
        compute_forces(planets, cfg.planet_count);
        for (int i = 0; i < cfg.planet_count; i++)
        {
            update_momentum(planets[i], dt);
            update_position(planets[i], dt);

            log_debug("Planet[%d] Pos: (%.2f, %.2f, %.2f)", i,
                      planets[i]->position.x,
                      planets[i]->position.y,
                      planets[i]->position.z);
        }

        // Drawing
        redraw_x(&x11);
        for (int i = 0; i < cfg.planet_count; i++)
        {
            draw_body(planets[i], &x11);
        }
        XFlush(x11.display);

        usleep(cfg.timestep * 1000);
    }

    close_x(&x11);
    log_info("Simulation ended.");

    for (int i = 0; i < cfg.planet_count; i++)
    {
        sphere_free(planets[i]);
    }

    return 0;
}
