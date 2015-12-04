//
//  Constants.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "Constants.hpp"

double PLAYER_RADIUS;
double BALL_RADIUS;
double MAX_X;
double MAX_Y;
double KICKER_RADIUS;
double GOAL_POST_Y;
double GOAL_POST_RADIUS;

Coord::Coord(float x, float y) {
  this->x = x;
  this->y = y;
};