#ifndef TCCppPrototypeGenerator_h

#define TCCppPrototypeGenerator_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

#include "TCAbstractPrototypeGenerator.h"

using namespace std;

namespace tc_utils {

	class TCCppPrototypeGenerator: public TCAbstractPrototypeGenerator {
	public:
		TCCppPrototypeGenerator(const vector<string> &statement): TCAbstractPrototypeGenerator(statement) { }

		virtual bool isIntegerType(const string &type) {
			return (type == "char") || (type == "unsigned char") ||
				   (type == "short") || (type == "unsigned short") ||
				   (type == "short int") || (type == "unsigned short int") ||
				   (type == "int") || (type == "unsigned int") ||
				   (type == "long long") || (type == "unsigned long long");
		}

		virtual bool isFloatType(const string &type) {
			return (type == "float") || (type == "double") || (type == "long double");
		}

		virtual bool isStringType(const string &type) {
			return type == "string";
		}

		virtual bool isBooleanType(const string &type) {
			return type == "bool";
		}

		virtual string getTemplateParameter(const string &parameter) {
			string result = TCAbstractPrototypeGenerator::getTemplateParameter(parameter);
			if (parameter == "result_type") {
				if (result == "double") result = "long double";
			}
			if (result != "INVALID") return result;
			result = "";
			if (parameter == "type_conversion") {
				if (getResultType() == "double") result = "(double)";
			} else if (parameter == "parameters_definition") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += '\n';
					result += "\t" + _parameters[i].first + " " + _parameters[i].second + ";";
				}
			} else if (parameter == "parameters_input") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += '\n';
					result += "\tTCReader::read(" + _parameters[i].second + ");";
				}
			} else if (parameter == "parameters_output") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += "\n";
					result += "\tcout << \"" + _parameters[i].second + " = \"; TCWriter::write(" + _parameters[i].second + "); cout << endl;";
				}
			} else throw TCStatementParserException("Invalid template parameter '" + parameter + "'");
			return result;
		}

		virtual int getTypeComplexity(const string &type) {
			unsigned int i = type.find("<");
			if (i == string::npos) return 0;
			i = type.find("<", i + 1);
			if (i == string::npos) return 1;
			return 2;
		}

		virtual string getSimpleSubtype(const string &type) {
			int i = type.find("<");
			int j = type.find(">");
			++i, --j;
			while (isspace(type[i])) ++i;
			while (isspace(type[j])) --j;
			return type.substr(i, j - i  + 1);
		}

		virtual bool isParseableType(const string &type) {
			if (TCAbstractPrototypeGenerator::isParseableType(type)) return true;
			if (getTypeComplexity(type) <= 1) {
				if (isSimpleParseableType(type)) return true;
				else if (type.find("vector") != string::npos)
					return isSimpleParseableType(getSimpleSubtype(type));
			}
			return false;
		}

		virtual string getClassFileName() {
			return getClassName() + ".h";
		}

		virtual string getExecuterFileName() {
			return getClassName() + ".cpp";
		}
	};
};

#endif
