//
//  Logic.hpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 05/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#ifndef Logic_hpp
#define Logic_hpp

#include "GlobalState.hpp"
#include <stdio.h>

class Logic {

  GlobalState *gs;
  Goal *oppGoal;
  Goal *myGoal;
  bool canScore();
  int goTo(Coord a);
  bool canShoot();
  bool ballCloserToOppGoal();
  Coord pointToScore();
  int canReach(Coord a);
  Coord avoidThis(Coord where, Coord avoid);
  bool iAmClosestToTheBall();
  int attack();
  int playD();
  bool onDLine(int num);
  bool closerToMyGoalThenBall();
  int findOppPlayer();
  Coord perfectDSpot(int num);
  int dribbleCount;
    
public:
  int makeDecision();
  Logic(GlobalState *gs);
};

#endif /* Logic_hpp */
