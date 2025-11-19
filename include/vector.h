/**
 * @file vector.h
 * @brief Vector mathematics operations for 3D space
 * 
 * This header provides basic vector operations used throughout the simulation
 * including addition, subtraction, scaling, magnitude calculation, and normalization.
 */

#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>

/**
 * @brief 3D vector structure
 * 
 * Represents a point or direction in 3D space with x, y, z components.
 */
typedef struct {
  float x, y, z;
} Vector;

/** @brief Alias for Vector used to represent position */
typedef Vector PosVec;

/** @brief Alias for Vector used to represent momentum */
typedef Vector MomVec;

/** @brief Alias for Vector used to represent force */
typedef Vector ForceVec;

// ---- Vector Helpers ----

/**
 * @brief Subtract vector b from vector a
 * 
 * @param a First vector
 * @param b Second vector to subtract
 * @return Vector Result of a - b
 */
static inline Vector vec_sub(Vector a, Vector b) {
  return (Vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

/**
 * @brief Add two vectors
 * 
 * @param a First vector
 * @param b Second vector
 * @return Vector Result of a + b
 */
static inline Vector vec_add(Vector a, Vector b) {
  return (Vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

/**
 * @brief Scale a vector by a scalar value
 * 
 * @param v Vector to scale
 * @param s Scalar multiplier
 * @return Vector Scaled vector (v * s)
 */
static inline Vector vec_scale(Vector v, float s) {
  return (Vector){v.x * s, v.y * s, v.z * s};
}

/**
 * @brief Calculate the magnitude (length) of a vector
 * 
 * @param v Vector to measure
 * @return float Magnitude of the vector
 */
static inline float vec_mag(Vector v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/**
 * @brief Normalize a vector to unit length
 * 
 * Returns a vector pointing in the same direction as v but with magnitude 1.
 * If the input vector has zero magnitude, returns a zero vector.
 * 
 * @param v Vector to normalize
 * @return Vector Normalized vector
 */
static inline Vector vec_normalize(Vector v) {
  float mag = vec_mag(v);
  if (mag == 0) return (Vector){0, 0, 0};
  return vec_scale(v, 1.0f / mag);
}

#endif