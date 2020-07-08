#include "client.h"

void error(char *msg) {
  perror(msg);
  exit(1);
}

OzzyClient::OzzyClient(const unsigned PORT, const string HOST){
    initSocket();
    connectToServer(PORT, HOST); 
    waitFor(WAIT_TIME);
}

OzzyClient::~OzzyClient() {
    delete[] data;
}

void OzzyClient::initSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Could not open socket");
    }
}

void OzzyClient::connectToServer(const unsigned PORT, const string HOST) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, HOST.c_str(), &addr.sin_addr) <= 0)  { 
        error("Invalid HOST address"); 
    } 

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) { 
        error("Could not connect to server"); 
    } 
}

void OzzyClient::waitFor(double TIME) {
    sleep(TIME);
}

void OzzyClient::sendRequst(const double number) {
    if (send(sock, (void*)&number, sizeof(double), 0) < 0) {
        fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
    }
    cout.precision(6);    
    cout << "Send number " << fixed << number << " to server" << endl;
}

void OzzyClient::getResult(){
    int size = 0;
    recv(sock, &size, sizeof(size_t), 0);
    N = size / sizeof(double);
    
    data = new double [N];
    int nBytes = recv(sock, &data[0], size, 0);
    
    if (nBytes <= 0){
        error("Failed receive data");
    }
}

void OzzyClient::writeResultToFile(string filename){
    ofstream file(filename);
    file.write(reinterpret_cast<const char*>(&data[0]), sizeof(double) * N);
    file.flush();
    cout << "Write to file " << filename.c_str() << " " << N << " samples" << endl;
}



