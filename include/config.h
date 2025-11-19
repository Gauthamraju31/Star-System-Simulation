/**
 * @file config.h
 * @brief Configuration file parsing and data structures
 * 
 * This header defines the configuration structure and functions for loading
 * simulation parameters from a configuration file.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdbool.h>
#include "core.h"
#include "vector.h"

/** @brief Target frame time in milliseconds (~60 FPS) */
#define FRAME_TIME_MS 16

/** @brief Default window width */
#define WIDTH 720

/** @brief Default window height */
#define HEIGHT 720

/** @brief Maximum number of celestial bodies in the simulation */
#define MAX_BODIES 10

/**
 * @brief Configuration structure for the simulation
 * 
 * Contains all runtime parameters loaded from the configuration file,
 * including simulation settings and initial states for celestial bodies.
 */
typedef struct {
    unsigned int timestep;     /**< Time step between frames in milliseconds */
    unsigned int resolution;   /**< Window resolution (width and height) */
    float gravity;             /**< Gravitational constant multiplier */
    int planet_count;          /**< Number of celestial bodies to simulate */
    unsigned int log_Level;    /**< Logging verbosity level */
    
    /**
     * @brief Array of celestial body configurations
     * 
     * Each body has initial conditions including mass, position,
     * momentum, size, and visual appearance.
     */
    struct {
        float mass;         /**< Mass of the body */
        Vector position;    /**< Initial position (x, y, z) */
        Vector momentum;    /**< Initial momentum (px, py, pz) */
        float radius;       /**< Visual radius */
        Color color;        /**< RGBA color */
    } bodies[MAX_BODIES];
} Config;

/**
 * @brief Load configuration from a file
 * 
 * Parses a configuration file in key=value format and populates the
 * Config structure. Supports comments (lines starting with #) and
 * planet-specific properties using the format "planetN.property=value".
 * 
 * @param filename Path to the configuration file
 * @param cfg Pointer to Config structure to populate
 * @return bool true if configuration was loaded successfully, false otherwise
 */
bool load_config(const char *filename, Config *cfg);

#endif
