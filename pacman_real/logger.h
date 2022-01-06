#pragma once
#ifndef _LOGGER_H_
#define _LOGGER_H_
#include "io_utils.h"

class Logger {
private:
	fstream result_file;
	fstream steps_file;
	bool	 isActivated = false;

public:
	Logger(const string& screen_name) : result_file(remove_extension(screen_name) + ".result"),
								        steps_file(remove_extension(screen_name) + ".steps") {
	};

	Logger() {};
								

	string remove_extension(const string& filename) const;
	void newTurn(int count);
	void activate() { isActivated = true; };
	
	void logToRes(string&& str) {
		if (isActivated == false)
			return; 
		result_file << str << endl;
	};


	void logToStep(string&& str) {
		if (isActivated == false)
			return;
		steps_file << str << endl;
	};

	void write(const string& mapName) {
		result_file.open(remove_extension(mapName) + ".result", std::fstream::in | std::fstream::out | std::fstream::trunc);
		steps_file.open(remove_extension(mapName) + ".steps", std::fstream::in | std::fstream::out | std::fstream::trunc);
	}

	void close() {
		result_file.close();
		steps_file.close();
	}
};

#endif