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

using namespace std;

void GlobalState::newMessage() {
  char *message = messager->receiveRaw();
  parseMessage(message);
}

GlobalState::GlobalState(Messager *mess) : messager(mess) {
  cerr << "tu";
  messager->sendLogin();
  cerr << "waiting;";
  char *message = messager->receiveRaw();
  cerr << message;
  parseMessage(message);
}

void GlobalState::parseMessage(char *message) {
  vector<string> allMessages = GlobalState::parse(new string(message), ';');

  if (allMessages[0] == "k") {
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
  vector<string> nums = GlobalState::parse(&message, '-');
  res.home = atoi(nums[0].c_str());
  res.away = atoi(nums[1].c_str());
  return res;
};

void GlobalState::parsePlayer(string message) {
  vector<string> info = GlobalState::parse(&message, ',');
  Player *player;
  player = &allPlayers[atoi(info[0].c_str())];

  player->position.x = atof(info[1].c_str());
  player->position.y = atof(info[2].c_str());
  player->velocity.x = atof(info[3].c_str());
  player->velocity.y = atof(info[4].c_str());
};

void GlobalState::parseKickoffPlayer(string message) {
  vector<string> info = GlobalState::parse(&message, ',');
  Player *player;
  player->id = atoi(info[1].c_str());
  if (USERNAME == info[2]) {
    id = player->id;
    myTeam = info[0];
  }

  if (info[0] == "Home") {
    homePlayers[atoi(info[1].c_str())] = *player;
  } else {
    awayPlayers[atoi(info[1].c_str())] = *player;
  }
  allPlayers[atoi(info[1].c_str())] = *player;
};

void GlobalState::parseBall(string message) {
  vector<string> info = GlobalState::parse(&message, ',');
  ball.position.x = atof(info[0].c_str());
  ball.position.y = atof(info[1].c_str());
  ball.velocity.x = atof(info[2].c_str());
  ball.velocity.y = atof(info[3].c_str());
};
