// Check whether prototype already generated

#include <iostream>

#include "TCAbstractPrototypeGenerator.h"
#include "TCCppPrototypeGenerator.h"
#include "TCJavaPrototypeGenerator.h"

using namespace std;
using namespace tc_utils;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Usage: is_solution_exists <language> <statement>" << endl;
		return 0;
	}

    string language = argv[1];

	string s;
	ifstream fin(argv[2]);
	vector<string> statement;
	while (getline(fin, s)) statement.push_back(s);
	fin.clear();
	fin.close();

	bool yes = false;
	TCAbstractPrototypeGenerator *sp = 0;
	try {
		if (language == "cpp") sp = new TCCppPrototypeGenerator(statement);
		else if (language == "java") sp = new TCJavaPrototypeGenerator(statement);
		else {
			cerr << "Bad language id (use \"cpp\" or \"java\")" << endl;
			return 1;
		}
		if (access(sp->getClassFileName().c_str(), 0) != -1) yes = true;
		if (access(sp->getExecuterFileName().c_str(), 0) != -1) yes = true;
	} catch (TCStatementParserException e) {
		cerr << e.getMessage() << endl;
	}
	delete sp;

	if (yes) return 1;

	return 0;
}
