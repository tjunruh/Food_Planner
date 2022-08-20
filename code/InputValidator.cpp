#include "InputValidator.h"
bool inputValid(std::string input) {
	bool valid = true;
	for (int i = 0; i < input.length(); i++) {
		if ((input[i] == '[') || (input[i] == ']') || (input[i] == '{') || (input[i] == '}') || (input[i] == ',') || (input[i] == ';') || (input[i] == ':') || (input[i] == '!')) {
			valid = false;
			break;
		}
	}
	return valid;
}