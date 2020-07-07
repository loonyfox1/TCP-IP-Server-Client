#pragma once

#include <iostream>
#include <string.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>

using namespace std;

#define N_ELEMENTS 1000000
#define MAX_NUM_SOCKETS 2

void error(char *msg);


class OzzyServer {
private:
    int sock;

    void initSocket(unsigned PORT);
    static void sendData(int pairSock, double number);
    static void* workerThread(void* args);
    void joinThreadPull(pthread_t* threads);

public:
    OzzyServer(unsigned PORT);
    ~OzzyServer();

    void run();
};