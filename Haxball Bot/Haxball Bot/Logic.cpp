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
      if (abs(line.a * oppGoal->down.x + line.b) <
          GOAL_POST_Y - GOAL_POST_RADIUS - BALL_RADIUS) {
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

Coord Logic::avoidThis(Coord avoid, Coord finalGoal) {
  Coord pointA;
  Coord pointB;
  float howFar = PLAYER_RADIUS * 1.3;
  float dist = Geometry::distance(avoid, finalGoal);
  Geometry::circle_circle_intersection(
      avoid.x, avoid.y, sqrt(dist * dist + howFar * howFar), finalGoal.x,
      finalGoal.y, howFar, &pointA.x, &pointA.y, &pointB.x, &pointB.y);

  if (Geometry::distance(gs->allPlayers[gs->id].position, pointA) <
      Geometry::distance(gs->allPlayers[gs->id].position, pointB)) {
    return pointA;
  } else {
    return pointB;
  }
}

int Logic::canReach(Coord a) {
  float dist = Geometry::distance(gs->allPlayers[gs->id].position, a);

  for (auto const &ent1 : gs->allPlayers) {
    if (Geometry::distance(ent1.second.position,
                           gs->allPlayers[gs->id].position) <
        PLAYER_RADIUS * 3) {
      if (Geometry::distance(ent1.second.position, a) < dist) {
        if (Geometry::distanceFromLine(gs->allPlayers[gs->id].position, a,
                                       ent1.second.position) <
            PLAYER_RADIUS * 2.5) {
          return ent1.first;
        }
      }
    }
  }

  if (Geometry::distance(gs->ball.position, gs->allPlayers[gs->id].position) <
      PLAYER_RADIUS * 3) {
    if (Geometry::distance(gs->ball.position, gs->allPlayers[gs->id].position) <
        dist) {
      if (Geometry::distanceFromLine(gs->allPlayers[gs->id].position, a,
                                     gs->ball.position) < PLAYER_RADIUS * 2.5) {
        return -1;
      }
    }
  }

  return -2;
}

bool Logic::iAmClosestToTheBall() {
  float dist =
      Geometry::distance(gs->allPlayers[gs->id].position, gs->ball.position);
  for (auto const &ent1 : gs->allPlayers) {
    if (Geometry::distance(ent1.second.position, gs->ball.position) < dist) {
      return false;
    }
  }
  return true;
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

  if (dribbleCount > 0){
      dribbleCount++;
      float xCoord = 0;
      if (dribbleCount < 20){
          if (abs(oppGoal->down.x-(gs->allPlayers[gs->id].position.x+1)) < abs(oppGoal->down.x-(gs->allPlayers[gs->id].position.x-1))){
              xCoord = gs->allPlayers[gs->id].position.x+10;
          }else{
              xCoord = (gs->allPlayers[gs->id].position.x-10);
          }
          keys |= goTo(*new Coord(xCoord, gs->allPlayers[gs->id].position.y));
          return keys;
      }else{
          dribbleCount = 0;
      }
  }
    
  if (canScore()) {
    keys |= KEY_SHOOT;
    return keys;
  }

  if (canShoot()){
      if (closerToMyGoalThenBall()){
          int opp = findOppPlayer();
          if (Geometry::distance(gs->allPlayers[gs->id].position, gs->allPlayers[opp].position)<10){
              dribbleCount = 1;
              keys |= KEY_SHOOT;
              cerr << "Sutiram ga";
              return keys;
          }
      }
  }

  if (iAmClosestToTheBall()) {
      keys |= attack();
  } else {
      keys |= playD();
  }
  /*
   cerr << "Gde trebam: " << pointToReach.x << ' ' << pointToReach.y << endl;
  cerr << "Gde sam sad: " << gs->allPlayers[gs->id].position.x << ' '
       << gs->allPlayers[gs->id].position.y << endl;
  cerr << "Gde je lopta: " << gs->ball.position.x << ' ' << gs->ball.position.y
       << endl;
*/
  return keys;
}

int Logic::attack(){
    
    Coord pointToReach = pointToScore();
    
    int num = canReach(pointToScore());
    
    if (num != -2) {
        if (num == -1) {
            pointToReach = avoidThis(gs->ball.position, pointToReach);
        } else {
            pointToReach = avoidThis(gs->allPlayers[num].position, pointToReach);
        }
    }
    
    return goTo(pointToReach);
}

bool Logic::onDLine(int num){
    return false;
}

bool Logic::closerToMyGoalThenBall(){
    if (abs(myGoal->down.x-(gs->allPlayers[gs->id].position.x)) < abs(myGoal->down.x-(gs->ball.position.x))){
        return true;
    }else{
        return false;
    }
}

int Logic::findOppPlayer(){
    for (auto const &ent1 : gs->allPlayers){
        if (ent1.first != gs->id) return ent1.first;
    }
    return -1;
}

Coord Logic::perfectDSpot(int num){
    Coord point;
    
    point.y =
    gs->ball.position.y +
    (BALL_RADIUS * (gs->ball.position.y - gs->allPlayers[num].position.y /*is goal middle y*/)) /
    Geometry::distance(*new Coord(gs->allPlayers[num].position.x, gs->allPlayers[num].position.y), gs->ball.position);
    point.x =
    gs->ball.position.x +
    (BALL_RADIUS * (gs->ball.position.x - gs->allPlayers[num].position.x)) /
    Geometry::distance(*new Coord(gs->allPlayers[num].position.x, gs->allPlayers[num].position.y), gs->ball.position);
    
    return point;
    
}

int Logic::playD(){
    int pl = findOppPlayer();
    if (pl == -1) return 0;
    
    Coord pointToReach = perfectDSpot(pl);
    
    return goTo(pointToReach);
}