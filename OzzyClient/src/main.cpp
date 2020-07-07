#include <iostream>
#include <fstream>

using namespace std;

#include "client.h"

typedef struct {
	unsigned port;
	string host;
	double number;
} config_args_t;

config_args_t readConfig(string filename);	

int main(int argc, char ** argv) {
	config_args_t cnfg = readConfig(argv[1]);
	OzzyClient* client = new OzzyClient(cnfg.port, cnfg.host);
	client->sendRequst(cnfg.number);
	client->getResult();
	client->writeResultToFile("data.bin");

	delete client;
	cout << "Client done!" << endl;

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
			else if (identifier == "HOST"){
				cnfg.host = value;
			}
			else if (identifier == "NUMBER") cnfg.number = strtod(value.c_str(), &pEnd);
		}
		configfile.close();
		if (cnfg.port == 0)
			cout << "Warning: " << "Could not read PORT in config file. PORT is default 0" << endl;
		if (cnfg.number == 0) {
			cout << "Warning: " << "Could not read NUMBER in config file. NUMBER is default 1000" << endl;
			cnfg.number = 1000;
		}
		if (cnfg.host == "") {
			cout << "Warning: " << "Could not read HOST in config file. HOST is default 127.0.0.1" << endl;
			cnfg.host = "127.0.0.1";
		}
	

		return cnfg;
	}
}