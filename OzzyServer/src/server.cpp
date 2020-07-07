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

    listen(sock, 1024);

    while(1) {
        int newSocket = accept(sock, NULL, NULL);
        if (newSocket != -1) {
            double number = 0;
            recv(newSocket, &number, sizeof(double),0);
            printf("%f\n", number); 

            double data[N_ELEMENTS];
            for (int i=0 ;i < N_ELEMENTS; i++) { 
                data[i] = number + i;
                cout << data[i] << endl;
            }

            size_t size = sizeof(double)*N_ELEMENTS;
            cout << size << endl;
            send(newSocket, (void*)&size, sizeof(size_t), 0); 
            send(newSocket, (void*)&data, size, 0); 

            close(newSocket);
        }
      
    }
    cout << "Close socket" << endl;
}