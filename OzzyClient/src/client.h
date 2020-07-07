#pragma once

#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

using namespace std;

#define WAIT_TIME 3 //sec

void error(char *msg);

class OzzyClient {
private:
    int sock;
    double* data;
    unsigned N;

    void initSocket();
    void connectToServer(const unsigned port, const string HOST);
    void waitFor(double TIME);

public:
    OzzyClient(const unsigned PORT, const string HOST);
    ~OzzyClient();

    void sendRequst(const double NUMBER);
    void getResult();
    void writeResultToFile(string filename);
};