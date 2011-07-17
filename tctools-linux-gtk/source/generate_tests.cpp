// Generate all sample tests from statement

#include <iostream>
#include <cstdlib>

#include "TCTestGenerator.h"

using namespace std;
using namespace tc_utils;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: generate_tests <statement>" << endl;
		return 0;
	}

	string s;
	ifstream fin(argv[1]);
	vector<string> statement;
	while (getline(fin, s)) statement.push_back(s);
	fin.clear();
	fin.close();

	TCTestGenerator *tg = new TCTestGenerator(statement);
	try {
		for (int i = 0; i < 20; ++i) {
			vector<string> test = tg->generateTest(i);
			if (test.size() == 0) break;
			char testFileName[20];
			sprintf(testFileName, "%02d", i);
			ofstream fout(testFileName);
			for (unsigned int j = 0; j < test.size(); ++j) fout << test[j] << endl;
			fout.clear();
			fout.close();
		}
	} catch (TCStatementParserException e) {
		cerr << e.getMessage() << endl;
	}
	delete tg;

	return 0;
}

