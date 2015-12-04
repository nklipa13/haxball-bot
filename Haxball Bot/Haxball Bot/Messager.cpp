//
//  Messager.cpp
//  Haxball Bot
//
//  Created by Nikola Klipa on 01/12/2015.
//  Copyright © 2015 Nikola Klipa. All rights reserved.
//

#include "Messager.hpp"

Messager::Messager(string serverHostname, short serverBroadcastPort,
                   short serverListenPort, string username)
    : serverHostname(serverHostname), serverBroadcastPort(serverBroadcastPort),
      serverListenPort(serverListenPort), username(username) {}

void Messager::sendLogin() {
  long messageLen = string(USERNAME).length() + 2;
  char message[messageLen];
  sprintf(message, "l;%s", string(USERNAME).c_str());
  sendRaw(message);
}

void Messager::sendCommand(int keys) {
  long messageLen = username.length() + 10;
  char message[messageLen];
  sprintf(message, "p;%s;%d", string(USERNAME).c_str(), keys);
  sendRaw(message);
}

void Messager::sendRaw(const char *message) {

  long messageLen = strlen(message);

  try {
    UDPSocket sock;
    sock.sendTo(message, (int)messageLen, serverHostname, serverListenPort);
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

char *Messager::receiveRaw() {

  try {
    UDPSocket sock(serverBroadcastPort);

    string sourceAddress;
    unsigned short sourcePort;
    // cerr << "cekam" << endl;
    int bytesRcvd =
        sock.recvFrom(receivedMessage, BUFFSIZE, sourceAddress, sourcePort);
    // cerr << "stigla poruka" << endl;
    receivedMessage[bytesRcvd] = '\0';

    // cerr << "Received from " << sourceAddress << ":" << sourcePort;

  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
  return receivedMessage;
}