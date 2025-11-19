/**
 * @file physics.h
 * @brief Physics calculations for gravitational simulation
 * 
 * This header provides the core physics functions used in the N-body simulation,
 * including gravitational force calculation and state updates.
 */

#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "core.h"

// ---- Physics Functions ----

/**
 * @brief Calculate gravitational force between two spheres
 * 
 * Computes the gravitational force exerted on sphere 'a' by sphere 'b'
 * using Newton's law of universal gravitation: F = G * m1 * m2 / r^2
 * The force is directed from 'a' towards 'b'.
 * 
 * @param a First sphere (force is calculated on this sphere)
 * @param b Second sphere (source of gravitational attraction)
 * @return Vector Gravitational force vector acting on sphere 'a'
 */
static inline Vector gforce(Sphere *a, Sphere *b) {
  Vector r_vec = vec_sub(a->position, b->position);
  float r_mag = vec_mag(r_vec);

  if (r_mag == 0) return (Vector){0, 0, 0};  // Prevent division by zero

  Vector r_hat = vec_normalize(r_vec);
  float force_mag = (GRAVITY_CONSTANT * a->mass * b->mass) / (r_mag * r_mag);
  return vec_scale(r_hat, -force_mag);
}

/**
 * @brief Update the momentum of a sphere based on applied force
 * 
 * Uses the impulse-momentum theorem (Δp = F * Δt) to update the sphere's
 * momentum based on the net force acting on it.
 * 
 * @param body Sphere to update
 * @param dt Time step (delta time) in simulation units
 */
static inline void update_momentum(Sphere *body, float dt) {
  body->momentum = vec_add(body->momentum, vec_scale(body->force, dt));
}

/**
 * @brief Update the position of a sphere based on its momentum
 * 
 * Uses the relationship p = m*v to calculate velocity, then updates
 * position using Δx = v * Δt.
 * 
 * @param body Sphere to update
 * @param dt Time step (delta time) in simulation units
 */
static inline void update_position(Sphere *body, float dt) {
  Vector velocity = vec_scale(body->momentum, 1.0f / body->mass);
  body->position = vec_add(body->position, vec_scale(velocity, dt));
}

#endif