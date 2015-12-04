//
//  main.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "GlobalState.hpp"
#include "Constants.hpp"
#include "Messager.hpp"
#include "Geometry.hpp"
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, const char *argv[]) {
  Messager *messager =
      new Messager("localhost", 15000, 44444, string(USERNAME));

  GlobalState gs(messager);
  int keys = 0;

  sleep(.2);

  while (true) {
    gs.newMessage();
    // if (abs(gs.ball.position.x - gs.allPlayers[gs.id].position.x)
    // >abs(gs.ball.position.y - gs.allPlayers[gs.id].position.y))

    if (gs.ball.position.x - gs.allPlayers[gs.id].position.x < 0) {
      keys |= KEY_LEFT;
    } else {
      keys |= KEY_RIGHT;
    }

    if (gs.ball.position.y - gs.allPlayers[gs.id].position.y < 0) {
      keys |= KEY_DOWN;
    } else {
      keys |= KEY_UP;
    }

    if (Geometry::distance(gs.ball.position, gs.allPlayers[gs.id].position) <
        (BALL_RADIUS + PLAYER_RADIUS) / 2 + 0.2)
      keys |= KEY_SHOOT;

    messager->sendCommand(keys);
  }

  return 0;
}
