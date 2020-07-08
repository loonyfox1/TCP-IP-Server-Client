#include "server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg) {
  perror(msg);
  exit(1);
}

OzzyServer::OzzyServer(unsigned PORT, string IP){
    initSocket(PORT, IP);
}

OzzyServer::~OzzyServer() {
    close(sock);
}

void OzzyServer::initSocket(unsigned PORT, string IP) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Could not open socket");
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP.c_str(), &addr.sin_addr) <= 0)  { 
        error("Invalid HOST address"); 
    } 

    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        error("Could not bind socket");
    }  
}

void OzzyServer::run(){
    listen(sock, MAX_NUM_SOCKETS);

    pthread_t threads[MAX_NUM_THREADS];
    int i = 0;

    while(1) {
        int pairSock = accept(sock, NULL, NULL);

        if (pairSock != -1) {
            args_t* args = new args_t();
            args->pairSock = pairSock;
            args->ID = i;

            int thr = pthread_create(&threads[i++], NULL, workerThread, args);
            if (thr != 0) {
                error("Failed to create thread");
            }
        }

        if (i >= MAX_NUM_THREADS){
            joinThreadPull(threads);
            i = 0;
        }
    }
}

void OzzyServer::joinThreadPull(pthread_t* threads){
    void *status;
    for (int i = 0; i < MAX_NUM_THREADS; i++){
        pthread_join(threads[i], &status);
    }
}

void* OzzyServer::workerThread(void* args) {
    args_t ar = *static_cast<args_t*>(args);
    double number = 0;

    if (recv(ar.pairSock, &number, sizeof(double), 0) < 0){
        fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
        error("Failed receive number from client");
    }

    cout.precision(6);    
    cout << "Worker " << ar.ID << " get number " << fixed << number << " from socket ID " << ar.pairSock << endl;

    sendData(ar.pairSock, number);
    close(ar.pairSock);
    pthread_exit(0);
}

void OzzyServer::sendData(int pairSock, double number) {
    double data[N_ELEMENTS];
    for (int i=0 ;i < N_ELEMENTS; i++) { 
        data[i] = number + i;
    }

    int size = sizeof(double)*N_ELEMENTS;

    if (send(pairSock, (void*)&size, sizeof(size_t), 0) == -1) 
        error("Cound not send size of data to client");
    
    if (send(pairSock, (void*)&data, size, 0) == -1)
        error("Cound not send data to client");

}