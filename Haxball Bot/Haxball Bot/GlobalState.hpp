//
//  GlobalState.hpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#ifndef GlobalState_hpp
#define GlobalState_hpp

#include <map>
#include <vector>
#include "Constants.hpp"

using namespace std;

class Messager;

class GlobalState {
  Messager *messager;
  Result result;

  Result parseResult(string message);
  void parseConstants(string message);
  void parsePlayer(string message);
  void parseKickoffPlayer(string message);
  void parseBall(string message);
  vector<string> parse(string *message, char character);

public:
  std::map<int, Player> homePlayers;
  std::map<int, Player> awayPlayers;
  std::map<int, Player> allPlayers;
  int id;
  string myTeam;
  Ball ball;
  Goal homeGoal();
  Goal awayGoal();

  void parseMessage(char *message);
  GlobalState(Messager *mess);
  void newMessage();
};

#endif /* GlobalState_hpp */
