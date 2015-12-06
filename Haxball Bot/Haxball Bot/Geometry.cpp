//
//  Geometry.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "Geometry.hpp"
#include <cmath>

float Geometry::distance(Coord a, Coord b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
};

Coord Geometry::vector(Coord a, Coord b) {
  return Coord(b.x - a.x, b.y - a.y);
};

Line Geometry::findLine(Coord a, Coord b) {
  float m = (b.y - a.y) / (b.x - a.x);
  Line line = *new Line(m, -m * b.x + b.y);
  return line;
};

float Geometry::distanceFromLine(Coord a, Coord b, Coord c) {
  return abs((b.y - a.y) * c.x - (b.x - a.x) * c.y + b.x * a.y - b.y * a.x) /
         sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
};

int Geometry::circle_circle_intersection(float x0, float y0, float r0, float x1,
                                         float y1, float r1, float *xi,
                                         float *yi, float *xi_prime,
                                         float *yi_prime) {
  float a, dx, dy, d, h, rx, ry;
  float x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  // d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx, dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1)) {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1)) {
    /* no solution. one circle is contained in the other */
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0 * r0) - (r1 * r1) + (d * d)) / (2.0 * d);

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a / d);
  y2 = y0 + (dy * a / d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0 * r0) - (a * a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h / d);
  ry = dx * (h / d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;

  return 1;
}