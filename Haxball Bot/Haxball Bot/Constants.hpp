//
//  Constants.hpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <iostream>

using namespace std;

#define KEY_UP 1
#define KEY_RIGHT 2
#define KEY_DOWN 4
#define KEY_LEFT 8
#define KEY_SHOOT 16

#define USERNAME "KlipaBot"

extern double PLAYER_RADIUS;
extern double BALL_RADIUS;
extern double MAX_X;
extern double MAX_Y;
extern double KICKER_RADIUS;
extern double GOAL_POST_Y;
extern double GOAL_POST_RADIUS;

struct Coord {
  float x, y;
  Coord(float x, float y);
  Coord() = default;
};

struct Goal {
  Coord up, down;
};

struct Player {
  Coord position, velocity;
  int id;

  bool const operator==(const Player &other) { return (id == other.id); }

  Player() = default;
};

struct Result {
  int home, away;
};

struct Ball {
  Coord position, velocity;
};

struct Line {
  // line is y = ax + b;
  float a, b;
  Line(float a, float b);
  Line() = default;
};

#endif /* Constants_hpp */
