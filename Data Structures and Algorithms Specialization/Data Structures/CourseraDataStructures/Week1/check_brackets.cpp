#include <iostream>
#include <stack>
#include <string>

struct Bracket {
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {

	std::string text;
	getline(std::cin, text);

	std::stack <Bracket> opening_brackets_stack;
	for (int position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			opening_brackets_stack.push(Bracket(next, position));
		}

		if (next == ')' || next == ']' || next == '}') {
			if (opening_brackets_stack.empty()) {
				std::cout << position + 1;
				return 0;
			}
			char top = opening_brackets_stack.top().type;
			if ((next == ')' && top != '(') || (next == ']' && top != '[') || (next == '}' && top != '{')) {
				std::cout << position + 1;
				return 0;
			}
			opening_brackets_stack.pop();
		}
	}
	if (!opening_brackets_stack.empty())
		std::cout << opening_brackets_stack.top().position + 1;
	else
		std::cout << "Success";
	return 0;
}
