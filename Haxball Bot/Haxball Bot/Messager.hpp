//
//  Messager.hpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#ifndef Messager_hpp
#define Messager_hpp

#include <stdio.h>

#include "PracticalSocket.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cstdlib>
#include <set>

#define BUFFSIZE 10000
#define HOME 0
#define AWAY 1

class GlobalState;

class Messager {
  string serverHostname;
  string username;
  short serverBroadcastPort, serverListenPort;
  char receivedMessage[BUFFSIZE];

  void sendRaw(const char *message);
  char *receiveRaw();

  friend GlobalState;

public:
  void sendLogin();
  void sendCommand(int keys);
  Messager(string serverHostname, short serverBroadcastPort,
           short serverListenPort, string username);
};

#endif /* Messager_hpp */
