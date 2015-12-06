//
//  Geometry.hpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include "Constants.hpp"

class Geometry {
public:
  static float distance(Coord a, Coord b);
  static Coord vector(Coord a, Coord b);
  static Line findLine(Coord a, Coord b);
  static float distanceFromLine(Coord a, Coord b, Coord c);
  static int circle_circle_intersection(float x0, float y0, float r0, float x1,
                                        float y1, float r1, float *xi,
                                        float *yi, float *xi_prime,
                                        float *yi_prime);
};

#endif /* Geometry_hpp */
