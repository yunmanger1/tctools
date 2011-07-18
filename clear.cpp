#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

bool isTokenChar(int c) {
	return isalpha(c) || isdigit(c) || (c == '_') || (c == '$');
}

string getDefineName(string s) {
    string name = "";
	int i = 0;
	while (!isspace(s[i])) ++i;
	while (isspace(s[i])) ++i;
	while ((i < s.length()) && !isspace(s[i]) && (s[i] != '(')) name += s[i++];
	return name;
}

string getTypedefName(string s) {
    string name = "";
    int i = s.length() - 1;
    while (true) {
    	if (s[i] == ']') {
    		while (s[i] != '[') --i;
    	} else if (isTokenChar(s[i])) break;
    	--i;
    }
    while (isTokenChar(s[i])) name = (char)s[i--] + name;
	return name;
}

string getConstName(string s) {
    string name = "";
    int i = s.find("=");
    while (true) {
    	if (s[i] == ']') {
    		while (s[i] != '[') --i;
    	} else if (isTokenChar(s[i])) break;
    	--i;
    }
    while (isTokenChar(s[i])) name = s[i--] + name;
	return name;
}

int main() {
	vector<string> code;
	string s;
	while (getline(cin, s)) code.push_back(s);

	bool bAssert = false, bOutput = false;
	vector<string> temp;
	for (int i = 0; i < code.size(); ++i) {
		bool ba = false, bo = false;
		string w = "";
		for (int k = 0; k <= code[i].length(); ++k) {
			if (isTokenChar(code[i][k]))
				w += code[i][k];
			else if (w != "") {
				if (w == "assert") ba = true;
				if ((w == "cout") || (w == "cerr") || (w == "printf")) bo = true;
				w = "";
			}
		}
		
		if ((code[i].find("#define") == 0) ||
			(code[i].find("typedef") == 0) ||
			(code[i].find("const") == 0)) {
			string name = "";
			if (code[i].find("#define") != string::npos) name = getDefineName(code[i]);
			else if (code[i].find("typedef") != string::npos) name = getTypedefName(code[i]);
			else name = getConstName(code[i]);
			bool used = false;
			for (int j = i + 1; !used && (j < code.size()); ++j) {
				string w = "";
				for (int k = 0; !used && (k <= code[j].length()); ++k) {
					if (isalpha(code[j][k]) || isdigit(code[j][k]) || (code[j][k] == '_') || (code[j][k] == '$'))
						w += code[j][k];
					else if (w != "") {
						if (w == name) used = true;
						w = "";
					}
				}
			}
			if (used) temp.push_back(code[i]), bAssert |= ba, bOutput |= bo;
		} else temp.push_back(code[i]), bAssert |= ba, bOutput |= bo;
	}
	code = temp;
	temp.clear();

	bool comment = false;
	bool empty = true;
	for (int i = 0; i < code.size(); ++i) {
		string s = "";
		for (int j = 0; j < code[i].length(); ++j) {
			bool f = false;
			if (code[i][j] == '\\') {
				if (!comment) s += code[i][j], s += code[i][j + 1], ++j;
			} else if (comment) {
				if (j < code[i].length() - 1) {
					if ((code[i][j] == '*') && (code[i][j + 1] == '/')) {
						comment = false;
						++j;
					}
				}
			} else {
				if (j < code[i].length() - 1) {
					if (code[i][j] == '/') {
						if (code[i][j + 1] == '/') break;
						else if (code[i][j + 1] == '*') {
							comment = true;
							++j;
						} else s += code[i][j];
					} else f = true;
				} else f = true;
			}
			if (f) s += code[i][j];
		}
		if (!empty || (s != "")) {
			cout << s << endl;
			empty = s == "";
		}
	}

	if (bAssert) cerr << "Warning: Some assert's are used" << endl;
	if (bOutput) cerr << "Warning: Display output is used." << endl;

	return 0;
}
