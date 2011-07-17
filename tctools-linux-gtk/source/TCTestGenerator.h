#ifndef TCTestGenerator_h

#define TCTestGenerator_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <stack>

#include "TCAbstractStatementParser.h"
#include "TCStatementParserException.h"

using namespace std;

namespace tc_utils {

	class TCTestGenerator: public TCAbstractStatementParser {
	public:
		TCTestGenerator(const vector<string> &statement): TCAbstractStatementParser(statement) {
		}

		virtual ~TCTestGenerator() { }

		vector<string> generateTest(const int testNumber) {
			vector<string> test;
			vector<string>::iterator it = _statement.begin();
			while ((it != _statement.end()) && (*it != "Examples")) ++it;
			if (it == _statement.end()) return test;
			string strTestNumber = intToStr(testNumber) + ')';
			while ((it != _statement.end()) && (*it != strTestNumber)) ++it;
			if (it == _statement.end()) return test;
			it += 3;
			string nextTest = intToStr(testNumber + 1) + ')';
			while (it->substr(0, 8) != "Returns:") test.push_back(*it++);
			test.push_back("Expected:");
			test.push_back(it->substr(9)); ++it;
			while ((*it != nextTest) && (*it != "This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved."))
				test.push_back(*it++);
			return test;
		}
	};
};

#endif
