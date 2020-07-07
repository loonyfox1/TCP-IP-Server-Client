#include <iostream>

using namespace std;

#include "server.h"

#define CONFIG_FILE "config.ini"

int main(int argc, char ** argv) {

	OzzyServer* server = new OzzyServer();
	delete server;

	cout << "Server done!" << endl;

	return 0;
}

