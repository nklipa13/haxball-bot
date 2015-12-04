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
};

#endif /* Geometry_hpp */
