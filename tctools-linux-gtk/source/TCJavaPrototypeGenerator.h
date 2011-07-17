#ifndef TCJavaPrototypeGenerator_h

#define TCJavaPrototypeGenerator_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

#include "TCAbstractPrototypeGenerator.h"

using namespace std;

namespace tc_utils {

	class TCJavaPrototypeGenerator: public TCAbstractPrototypeGenerator {
	public:
		TCJavaPrototypeGenerator(const vector<string> &statement): TCAbstractPrototypeGenerator(statement) { }

		virtual bool isIntegerType(const string &type) {
			return (type == "char") || (type == "byte") ||
				   (type == "short") || (type == "int") ||
				   (type == "long");
		}

		virtual bool isFloatType(const string &type) {
			return (type == "float") || (type == "double");
		}

		virtual bool isStringType(const string &type) {
			return type == "String";
		}

		virtual bool isBooleanType(const string &type) {
			return type == "boolean";
		}
		
		virtual string markup(string s){
		    int p = s.find("[]");
		    if (p != -1){
		        return s.replace(p,2,"Array");
		    }
		    return s;
		}

		virtual string getTemplateParameter(const string &parameter) {
			string result = TCAbstractPrototypeGenerator::getTemplateParameter(parameter);
			if (result != "INVALID") return result;
			result = "";
			if (parameter == "parameters_definition") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += '\n';
					result += "\t\t" + _parameters[i].first + " " + _parameters[i].second + ";";
				}
			} else if (parameter == "parameters_input") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += '\n';
					result += "\t\t" + _parameters[i].second + " = TCReader.read"+ markup(_parameters[i].first) +"();";
				}
			} else if (parameter == "parameters_output") {
				for (unsigned int i = 0; i < _parameters.size(); ++i) {
					if (i) result += "\n";
					result += "\t\tSystem.out.print(\"" + _parameters[i].second + " = \"); TCWriter.write(" + _parameters[i].second + "); System.out.println("");";
				}
			} else throw TCStatementParserException("Invalid template parameter '" + parameter + "'");
			return result;
		}

		virtual int getTypeComplexity(const string &type) {
			unsigned int i = type.find("[");
			if (i == string::npos) return 0;
			i = type.find("[", i + 1);
			if (i == string::npos) return 1;
			return 2;
		}

		virtual string getSimpleSubtype(const string &type) {
			int i = type.find("[");
			int j = type.find(" ");
			if ((j != -1) && ((i == -1) || (j < i))) i = j;
			return type.substr(0, i);
		}

		virtual bool isParseableType(const string &type) {
			if (TCAbstractPrototypeGenerator::isParseableType(type)) return true;
			if (getTypeComplexity(type) <= 1) {
				if (isSimpleParseableType(type)) return true;
				return isSimpleParseableType(getSimpleSubtype(type));
			}
			return false;
		}

		virtual string getClassFileName() {
			return getClassName() + ".java";
		}

		virtual string getExecuterFileName() {
			return getClassName() + "Executer.java";
		}
	};
};

#endif
