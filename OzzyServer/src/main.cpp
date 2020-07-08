#include <iostream>
#include <fstream>

using namespace std;

#include "server.h"

typedef struct {
	unsigned port;
	string ip;
} config_args_t;

config_args_t readConfig(string filename);

int main(int argc, char ** argv) {
	config_args_t cnfg = readConfig(argv[1]);
	OzzyServer* server = new OzzyServer(cnfg.port, cnfg.ip);
	server->run();

	delete server;
	cout << "Server done!" << endl;

	return 0;
}

config_args_t readConfig(string filename){
	ifstream configfile(filename);
	if (!configfile.is_open()) {
		error("Could not open config file");
	}
	else {
		config_args_t cnfg;
		string line, identifier, value;
		size_t sv;
		char* pEnd;

		while (getline(configfile, line)) {
			sv = line.find('=');
			identifier = line.substr(0, sv - 1);
			value = "";
			if (sv != string::npos) {
				value = line.substr(sv + 2, line.find('\n') - sv - 1);
			}

			if (identifier == "PORT") cnfg.port = strtod(value.c_str(), &pEnd);
			else if (identifier == "IP") cnfg.ip = value;
		}
		configfile.close();
		if (cnfg.port == 0)
			cout << "Warning: " << "Could not read PORT in config file. PORT is default 0" << endl;
		if (cnfg.ip == "") {
			cout << "Warning: " << "Could not read ip in config file. ip is default 0.0.0.0" << endl;
			cnfg.ip = "0.0.0.0";
		}
		return cnfg;
	}
}