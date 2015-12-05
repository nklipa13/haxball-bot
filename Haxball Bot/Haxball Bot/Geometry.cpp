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