/**
 * @file core.h
 * @brief Core data structures and sphere management for the simulation
 * 
 * This header defines the fundamental structures used in the solar system simulation,
 * including celestial bodies (spheres) and their properties.
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"

/** @brief Gravitational constant for the simulation */
#define GRAVITY_CONSTANT 1

/**
 * @brief RGBA color structure
 * 
 * Represents a color with red, green, blue, and alpha (transparency) components.
 * Each component ranges from 0 to 255.
 */
typedef struct {
  unsigned int r, g, b, a;
} Color;

/**
 * @brief Sphere structure representing a celestial body
 * 
 * Contains all physical and visual properties of a celestial body in the simulation.
 */
typedef struct {
  PosVec position;           /**< Current position in 3D space */
  MomVec momentum;           /**< Current momentum (mass * velocity) */
  float radius;              /**< Visual radius of the sphere */
  float mass;                /**< Mass of the celestial body */
  ForceVec force;            /**< Net force acting on the body */
  Color color;               /**< Display color of the body */
  unsigned int make_trail;   /**< Flag to enable/disable trail rendering */
  unsigned int trail_length; /**< Length of the trail to render */
  Vector *trail;             /**< Array of positions forming the trail */
} Sphere;

/**
 * @brief Create a new sphere (celestial body)
 * 
 * Allocates and initializes a new Sphere structure with the given properties.
 * 
 * @param position Initial position vector
 * @param radius Visual radius of the sphere
 * @param color Display color
 * @param mass Mass of the body
 * @param momentum Initial momentum vector
 * @return Sphere* Pointer to the newly created sphere, or NULL on allocation failure
 */
Sphere* sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum);

/**
 * @brief Free a sphere and its associated resources
 * 
 * Deallocates the memory used by a sphere, including any trail data.
 * Safe to call with NULL pointer.
 * 
 * @param sphere Pointer to the sphere to free
 */
void sphere_free(Sphere *sphere);

#endif