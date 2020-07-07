#include "server.h"

void error(char *msg) {
  perror(msg);
  exit(1);
}

OzzyServer::OzzyServer(unsigned PORT){
    initSocket(PORT);
}

OzzyServer::~OzzyServer() {}

void OzzyServer::initSocket(unsigned PORT) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Could not open socket");
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        error("Could not bind socket");
    }  
}

void OzzyServer::run(){
    listen(sock, MAX_NUM_SOCKETS);

    pthread_t threads[MAX_NUM_SOCKETS];
    int i = 0;
    while(1) {
        int pairSock = accept(sock, NULL, NULL);

        if (pairSock != -1) {
            int thr = pthread_create(&threads[i], NULL, workerThread, &pairSock);
            if (thr != 0) {
                error("Failed to create thread");
            }
            else {
                cout << "Create thread ID " << i << endl;
                i++;
            }
        }

        if (i >= MAX_NUM_SOCKETS){
            joinThreadPull(threads);
            i = 0;
        }
    }
}

void OzzyServer::joinThreadPull(pthread_t* threads){
    for (int i = 0; i < MAX_NUM_SOCKETS; i++){
        pthread_join(threads[i], NULL);
        cout << "Join thread ID " << i << endl;
    }
}

void* OzzyServer::workerThread(void* args) {
    int pairSock = *((int*)args);
    double number = 0;
    recv(pairSock, &number, sizeof(double),0);
    cout << "Worker get " << number << endl;

    sendData(pairSock, number);
    close(pairSock);
    pthread_exit(NULL);
}

void OzzyServer::sendData(int pairSock, double number) {
    double data[N_ELEMENTS];
    for (int i=0 ;i < N_ELEMENTS; i++) { 
        data[i] = number + i;
    }

    int size = sizeof(double)*N_ELEMENTS;
    send(pairSock, (void*)&size, sizeof(size_t), 0); 
    send(pairSock, (void*)&data, size, 0);
}