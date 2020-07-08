#pragma once

#include <iostream>
#include <string.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/ioctl.h>
#include <pthread.h>

using namespace std;

#define N_ELEMENTS 1000000
#define MAX_NUM_SOCKETS 50
#define MAX_NUM_THREADS 16

void error(char *msg);

typedef struct {
    int pairSock;
    int ID;
} args_t;

class OzzyServer {
private:
    int sock;

    void initSocket(unsigned PORT, string IP);
    static void sendData(int pairSock, double number);
    static void* workerThread(void* args);
    void joinThreadPull(pthread_t* threads);

public:
    OzzyServer(unsigned PORT, string IP);
    ~OzzyServer();

    void run();
};