#ifndef TCAbstractPrototypeGenerator_h

#define TCAbstractPrototypeGenerator_h

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

	class TCAbstractPrototypeGenerator: public TCAbstractStatementParser {
	protected:
		string _className;
		string _methodName;
		string _resultType;
		string _methodSignature;
		vector<pair<string, string> > _parameters;

		string getProperty(const string &propertyName) {
			vector<string>::iterator it = _statement.begin();
			while ((it != _statement.end()) && (*it != (propertyName + ":"))) ++it;
			if (it == _statement.end()) throw TCStatementParserException("Cannot find property " + propertyName);
			return *++it;
		}

		virtual bool isIntegerType(const string &type) = 0;
		virtual bool isFloatType(const string &type) = 0;
		virtual bool isStringType(const string &type) = 0;
		virtual bool isBooleanType(const string &type) = 0;

	public:
		TCAbstractPrototypeGenerator(const vector<string> &statement): TCAbstractStatementParser(statement),
			_className(""), _methodName(""), _resultType(""), _methodSignature("") {
			_parameters.push_back(make_pair("", ""));
			loadParameters();
		}

		virtual ~TCAbstractPrototypeGenerator() { }

		string getClassName() {
			if (_className != "") return _className;
			return _className = getProperty("Class");
		}

		string getMethodName() {
			if (_methodName != "") return _methodName;
			return _methodName = getProperty("Method");
		}

		string getResultType() {
			if (_resultType != "") return _resultType;
			return _resultType = getProperty("Returns");
		}

		string getMethodSignature() {
			if (_methodSignature != "") return _methodSignature;
			return _methodSignature = getProperty("Method signature");
		}

		virtual string getTemplateParameter(const string &parameter) {
			string result = "INVALID";
			if (parameter == "class_name") result = getClassName();
			else if (parameter == "method_name") result = getMethodName();
			else if (parameter == "method_signature") result = getMethodSignature();
			else if (parameter == "result_type") result = getResultType();
			else if (parameter == "parameters_list") {
				result = "";
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += ", ";
					result += _parameters[i].second;
				}
			} else if (parameter == "result_initialization") {
				string resultType = getResultType();
				if (isStringType(resultType)) result = " = \"\"";
				else if (isIntegerType(resultType)) result = " = 0";
				else if (isFloatType(resultType)) result = " = 0.0";
				else if (isBooleanType(resultType)) result = " = false";
				else result = "";
			}
			return result;
		}

		virtual void loadParameters() {
			if (_parameters[0].first != "") return;
			_parameters.clear();
			string methodSignature = getMethodSignature();
			for (unsigned int i = methodSignature.find("(") + 1; i < methodSignature.length(); ++i) {
				skipSpaces(methodSignature, i);
				unsigned int j = i;
				stack<int> st;
				while ((j < methodSignature.length()) && (methodSignature[j] != ',') && (methodSignature[j] != ')')) {
					switch (methodSignature[j]) {
						case '<': case '[': st.push(methodSignature[j]); break;
						case '>':
							if ((st.size() > 0) && (st.top() == '<')) st.pop();
							else throw TCStatementParserException("Braces in method signature are not balanced");
							break;
						case ']':
							if ((st.size() > 0) && (st.top() == '[')) st.pop();
							else throw TCStatementParserException("Braces in method signature are not balanced");
							break;
					}
					++j;
				}
				if (st.size() != 0) throw TCStatementParserException("Braces in method signature are not balanced");
				unsigned int t = j;
				while ((j > 0) && !isIdChar(methodSignature[j - 1])) --j;
				unsigned int k = j;
				while ((k > 0) && isIdChar(methodSignature[k - 1])) --k;
				string name = methodSignature.substr(k, j - k);
				skipSpacesR(methodSignature, k);
				string type = methodSignature.substr(i, k - i);
				_parameters.push_back(make_pair(type, name));
				i = t;
			}
		}

		virtual int getTypeComplexity(const string &type) = 0;

		virtual string getSimpleSubtype(const string &type) = 0;

		virtual bool isSimpleParseableType(const string &type) {
			return isStringType(type) || isIntegerType(type) || isFloatType(type) || isBooleanType(type);
		}

		virtual bool isParseableType(const string &type) {
			return isSimpleParseableType(type);
		}

		vector<string> fillPrototype(const vector<string> &prototype) {
			vector<string> result;
			for (unsigned int i = 0; i < prototype.size(); ++i) {
				string s = "";
				for (unsigned int l = 0; l < prototype[i].length(); ++l)
					if (prototype[i][l] == '$') {
						for (unsigned int r = l + 1; r < prototype[i].length(); ++r) if (prototype[i][r] == '$') {
							string parameter = prototype[i].substr(l + 1, r - l - 1);
							s += getTemplateParameter(parameter);
							l = r;
							break;
						}
					} else s += prototype[i][l];
				result.push_back(s);
			}
			return result;
		}

		virtual string getClassFileName() = 0;

		virtual string getExecuterFileName() = 0;
	};
};

#endif
