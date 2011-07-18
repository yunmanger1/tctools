#include <iostream>
#include <vector>
#include <string>

#include "TCAbstractPrototypeGenerator.h"
#include "TCCppPrototypeGenerator.h"
#include "TCJavaPrototypeGenerator.h"

using namespace std;
using namespace tc_utils;

int main(int argc, char *argv[]) {
	if (argc != 5) {
		cout << "Usage: generate_prototype <language> <statement> <class-prototype> <executer-prototype>" << endl;
		return 0;
	}

    string language = argv[1];

	ifstream fin;
    string s;
	
	fin.open(argv[2]);
	vector<string> statement;
	while (getline(fin, s)) statement.push_back(s);
	fin.clear();
	fin.close();

	fin.open(argv[3]);
	vector<string> classPrototype;
	while (getline(fin, s)) classPrototype.push_back(s);
	fin.clear();
	fin.close();
	
	fin.open(argv[4]);
	vector<string> executerPrototype;
	while (getline(fin, s)) executerPrototype.push_back(s);
	fin.clear();
	fin.close();

	vector<string> classDefinition;
	vector<string> executer;

	TCAbstractPrototypeGenerator *pg = 0;
	
	try {
		if (language == "cpp") pg = new TCCppPrototypeGenerator(statement);
		else if (language == "java") pg = new TCJavaPrototypeGenerator(statement);
		else {
			cerr << "Bad language id (use \"cpp\" or \"java\")" << endl;
			return 1;
		}
		classDefinition = pg->fillPrototype(classPrototype);
		executer = pg->fillPrototype(executerPrototype);
	} catch (TCStatementParserException e) {
		cerr << e.getMessage() << endl;
	}

	ofstream fout;

	fout.open(pg->getClassFileName().c_str());
	for (unsigned int i = 0; i < classDefinition.size(); ++i) fout << classDefinition[i] << endl;
	fout.clear();
	fout.close();

	fout.open(pg->getExecuterFileName().c_str());
	for (unsigned int i = 0; i < executer.size(); ++i) fout << executer[i] << endl;
	fout.clear();
	fout.close();

	delete pg;

	return 0;
}
