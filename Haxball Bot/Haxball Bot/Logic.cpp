//
//  Logic.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 05/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "GlobalState.hpp"
#include "Constants.hpp"
#include "Geometry.hpp"
#include "Logic.hpp"
#include <cmath>

Logic::Logic(GlobalState *gs) { this->gs = gs; };

bool Logic::canShoot() {
  if (Geometry::distance(gs->ball.position, gs->allPlayers[gs->id].position) <
      (BALL_RADIUS + KICKER_RADIUS))
    return true;
  return false;
}

bool Logic::ballCloserToOppGoal() {
  if (Geometry::distance(*new Coord(oppGoal->down.x, 0), gs->ball.position) <
      Geometry::distance(*new Coord(oppGoal->down.x, 0),
                         gs->allPlayers[gs->id].position))
    return true;
  return false;
}

bool Logic::canScore() {
  if (canShoot()) {
    if (ballCloserToOppGoal()) {
      // find line with ball and player
      Line line = Geometry::findLine(gs->ball.position,
                                     gs->allPlayers[gs->id].position);

      // if line intersect this in goal, return true
      if (abs(line.a * oppGoal->down.x + line.b) < GOAL_POST_Y) {
        return true;
      }
    }
  }

  return false;
}

Coord Logic::pointToScore() {
  Coord point;

  point.y =
      gs->ball.position.y +
      (BALL_RADIUS * (gs->ball.position.y - 0 /*is goal middle y*/)) /
          Geometry::distance(*new Coord(oppGoal->down.x, 0), gs->ball.position);
  point.x =
      gs->ball.position.x +
      (BALL_RADIUS * (gs->ball.position.x - oppGoal->down.x)) /
          Geometry::distance(*new Coord(oppGoal->down.x, 0), gs->ball.position);

  return point;
}

int Logic::goTo(Coord a) {
  int keys = 0;

  if (a.x - gs->allPlayers[gs->id].position.x < 0) {
    keys |= KEY_LEFT;
  } else {
    keys |= KEY_RIGHT;
  }

  if (a.y - gs->allPlayers[gs->id].position.y < 0) {
    keys |= KEY_DOWN;
  } else {
    keys |= KEY_UP;
  }

  return keys;
}

int Logic::makeDecision() {
  int keys = 0;

  if (gs->myTeam == "Home") {
    myGoal = &gs->homeGoal;
    oppGoal = &gs->awayGoal;
  } else {
    oppGoal = &gs->homeGoal;
    myGoal = &gs->awayGoal;
  }

  if (canScore()) {
    keys |= KEY_SHOOT;
    return keys;
  }

  Coord ab = pointToScore();
  keys |= goTo(ab);

  cerr << "Gde trebam: " << ab.x << ' ' << ab.y << endl;
  cerr << "Gde sam sad: " << gs->allPlayers[gs->id].position.x << ' '
       << gs->allPlayers[gs->id].position.y << endl;
  cerr << "Gde je lopta: " << gs->ball.position.x << ' ' << gs->ball.position.y
       << endl;
  return keys;
}