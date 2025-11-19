/**
 * @file core.c
 * @brief Implementation of sphere lifecycle management
 * 
 * This file implements the creation and destruction of celestial bodies
 * (spheres) used in the solar system simulation.
 */

#include "core.h"

// ---- Sphere Lifecycle ----

/**
 * @brief Create a new sphere with the specified properties
 * 
 * Allocates memory for a new sphere and initializes all its properties.
 * The force is initialized to zero, and trail rendering is disabled by default.
 * 
 * @param position Initial position in 3D space
 * @param radius Visual radius of the sphere
 * @param color RGBA color for rendering
 * @param mass Mass of the celestial body
 * @param momentum Initial momentum vector
 * @return Pointer to newly created Sphere, or NULL if allocation fails
 */
Sphere *sphere_create(PosVec position, float radius, Color color, float mass, MomVec momentum) {
  Sphere *s = (Sphere *)malloc(sizeof(Sphere));
  if (!s) {
    fprintf(stderr, "Error: Failed to allocate memory for sphere.\n");
    return NULL;
  }
  s->position = position;
  s->momentum = momentum;
  s->radius = radius;
  s->mass = mass;
  s->force = (Vector){0, 0, 0};
  s->color = color;
  s->make_trail = 0;
  s->trail_length = 0;
  s->trail = NULL;
  return s;
}

/**
 * @brief Free memory allocated for a sphere
 * 
 * Safely deallocates a sphere and its associated trail data.
 * Does nothing if passed a NULL pointer.
 * 
 * @param s Pointer to the sphere to free
 */
void sphere_free(Sphere *s) {
  if (s) {
    if (s->trail) free(s->trail);
    free(s);
  }
}