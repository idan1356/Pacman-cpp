#include "logger.h"

string Logger::remove_extension(const string& filename) const {
	int lastdot = filename.find_last_of(".");
	if (lastdot == string::npos)
		return filename;

	return filename.substr(0, lastdot);
}

void Logger::newTurn(int count) {
	if (isActivated == false)
		return;

	steps_file << "-----------------------" << endl;
	steps_file << count << endl;
}



