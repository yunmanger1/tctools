#ifndef TCAbstractStatementParser_h

#define TCAbstractStatementParser_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <stack>

#include "TCStatementParserException.h"

using namespace std;

namespace tc_utils {

	class TCAbstractStatementParser {
	protected:
		vector<string> _statement;

		static void skipSpaces(const string &s, unsigned int &i) {
			while ((i < s.length()) && isspace(s[i])) ++i;
		}

		static void skipSpacesR(const string &s, unsigned int &i) {
			while ((i > 0) && isspace(s[i - 1])) --i;
		}

		static bool isIdChar(const int x) {
			return isalpha(x) || isdigit(x) || (x == '$') || (x == '_');
		}

		static string intToStr(const int x) {
			int y = x;
			string s = "";
			do {
				s = (char)(y % 10 + '0') + s;
				y /= 10;
			} while (y);
			return s;
		}

	public:
		TCAbstractStatementParser(const vector<string> &statement) {
			_statement = statement;
		}

		virtual ~TCAbstractStatementParser() { }
	};
};

#endif
