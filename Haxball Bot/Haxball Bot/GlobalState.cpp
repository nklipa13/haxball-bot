//
//  GlobalState.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "GlobalState.hpp"
#include "Messager.hpp"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

void GlobalState::newMessage() {
  char *message = messager->receiveRaw();
  parseMessage(message);
}

GlobalState::GlobalState(Messager *mess) : messager(mess) {
  messager->sendLogin();
  char *message = messager->receiveRaw();
  parseMessage(message);
}

void GlobalState::parseMessage(char *message) {
  vector<string> allMessages = GlobalState::parse(new string(message), ';');

  if (allMessages[0] == "k") {
    parseConstants(allMessages[1]);
    long size = allMessages.size();
    for (long i = 2; i < size; i++) {
      parseKickoffPlayer(allMessages[i]);
    }
  } else if (allMessages[0] == "g") {
    parseResult(allMessages[1]);
    parseBall(allMessages[2]);
    long size = allMessages.size();
    for (long i = 3; i < size; i++) {
      parsePlayer(allMessages[i]);
    }

  } else if (allMessages[0] == "p") {
    parseBall(allMessages[1]);
    long size = allMessages.size();
    for (long i = 2; i < size; i++) {
      parsePlayer(allMessages[i]);
    }
  }
};

vector<string> GlobalState::parse(string *message, char character) {
  vector<string> strings;
  string s = *message;
  char delimiter = character;

  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    strings.push_back(token);
    s.erase(0, pos + 1);
  }

  strings.push_back(s);
  return strings;
};

Result GlobalState::parseResult(string message) {
  Result res;

  sscanf(message.c_str(), "%d:%d", &res.home, &res.away);

  return res;
};

void GlobalState::parsePlayer(string message) {
  vector<string> info = GlobalState::parse(&message, ',');
  Player *player;
  Coord pos;
  Coord vel;
  int pid;
  sscanf(message.c_str(), "%d,%f,%f,%f,%f", &pid, &pos.x, &pos.y, &vel.x,
         &vel.y);

  player = &allPlayers[pid];
  player->position = pos;
  player->velocity = vel;
};

void GlobalState::parseKickoffPlayer(string message) {
  vector<string> info = GlobalState::parse(&message, ',');
  Player *player;
  player->id = stoi(info[1]);
  if (USERNAME == info[2]) {
    id = player->id;
    myTeam = info[0];
  }

  if (info[0] == "Home") {
    homePlayers[stoi(info[1])] = *player;
  } else {
    awayPlayers[stoi(info[1])] = *player;
  }
  allPlayers[stoi(info[1])] = *player;
};

void GlobalState::parseBall(string message) {
  sscanf(message.c_str(), "%f,%f,%f,%f", &ball.position.x, &ball.position.y,
         &ball.velocity.x, &ball.velocity.y);
};

void GlobalState::parseConstants(string message) {
  sscanf(message.c_str(), "%lf,%lf,%lf,%lf,%lf,%lf,%lf", &MAX_X, &MAX_Y,
         &GOAL_POST_Y, &GOAL_POST_RADIUS, &BALL_RADIUS, &PLAYER_RADIUS,
         &KICKER_RADIUS);
}
