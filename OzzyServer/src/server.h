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

using namespace std;

#define N_ELEMENTS 10

void error(char *msg);

class OzzyServer {
private:
    int sock;

    void initSocket(unsigned PORT);

public:
    OzzyServer(unsigned PORT);
    ~OzzyServer();
};