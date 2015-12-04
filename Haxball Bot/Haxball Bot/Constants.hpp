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

#define PLAYER_RADIUS 2.75
#define BALL_RADIUS 1.225
#define USERNAME "KlipaBot"

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

#endif /* Constants_hpp */
