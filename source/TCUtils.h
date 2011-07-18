#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

#ifdef _WINDOWS_
#include <windows.h>
#endif

using namespace std;

namespace tc_utils {
#ifdef _WINDOWS_
	const int LIGHTBLUE = 11;
	const int WHITE = 15;
	const int GRAY = 7;
	const int GREEN = 10;
	const int RED = 12;
#else
	const int RESET = 0;
	const int BRIGHT = 1;
	const int DIM = 2;
	const int UNDERLINE = 3;
	const int BLINK = 4;
	const int REVERSE = 7;
	const int HIDDEN = 8;
	const int BLACK = 0;
	const int RED = 1;
	const int GREEN = 2;
	const int YELLOW = 3;
	const int BLUE = 4;
	const int MAGENTA = 5;
	const int CYAN = 6;
	const int WHITE = 7;
	const int LIGHTBLUE = (BRIGHT << 8) + BLUE;
	const int GRAY = WHITE;
#endif

	class TCReader {
	public:
		static void read(bool &x) {
			string temp;
			do {
				getline(cin, temp);
			} while (temp == "");
			x = (temp == "true");
		}

		static void read(char &x) {
			string temp;
			do {
				getline(cin, temp);
			} while (temp == "");
			x = temp[1];
		}

		static void read(string &x) {
			string temp;
			do {
				getline(cin, temp);
			} while (temp == "");
			int l = temp.find('\"'), r = temp.rfind('\"');
			x = temp.substr(l + 1, r - l - 1);
		}

		template <class T> static void read(T &x) {
			string temp;
			do {
				getline(cin, temp);
			} while (temp == "");
			istringstream iss(temp);
			iss >> x;
		}

		static void read(vector<bool> &x) {
			string temp;
			bool finished = false;
			string token = "";
			while (!finished) {
				do {
					getline(cin, temp);
				} while (temp == "");
				for (int i = temp.find("{") + 1; i < (int)temp.length(); ++i) {
					if (temp[i] == '\\') ++i;
					else if ((temp[i] == ',') || (temp[i] == '}')) {
						if (temp[i] == '}') finished = true;
						bool empty = true;
						for (int j = 0; j < (int)token.length(); ++j)
							if (!isspace(token[j])) empty = false;
						if (!empty) {
							string t;
							istringstream iss(token);
							iss >> t;
							x.push_back(t == "true");
						}
						token = "";
					} else token += temp[i];
				}
			}
		}

		static void read(vector<char> &x) {
			string temp;
			bool finished = false;
			string token = "";
			bool hasToken = false;
			while (!finished) {
				do {
					getline(cin, temp);
				} while (temp == "");
				bool open = false;
				for (int i = temp.find("{") + 1; i < (int)temp.length(); ++i) {
					if (temp[i] == '\\') token += temp[++i];
					else if (!open && ((temp[i] == ',') || (temp[i] == '}'))) {
						if (temp[i] == '}') finished = true;
						if (hasToken) x.push_back(token[0]);
						token = "";
						hasToken = false;
					} else if (temp[i] == '\'') {
						open = !open;
						if (open) hasToken = true;
					} else if (open) token += temp[i];
				}
			}
		}

		static void read(vector<string> &x) {
			string temp;
			bool finished = false;
			string token = "";
			bool hasToken = false;
			while (!finished) {
				do {
					getline(cin, temp);
				} while (temp == "");
				bool open = false;
				for (int i = 0; i < (int)temp.length(); ++i) {
					if (!open && ((temp[i] == ',') || (temp[i] == '}'))) {
						if (temp[i] == '}') finished = true;
						if (hasToken) x.push_back(token);
						hasToken = false;
						token = "";
					} else if (temp[i] == '"') {
						open = !open;
						if (open) hasToken = true;
					} else if (open) {
						if (temp[i] == '\\') token += temp[++i];
						else token += temp[i];
					}
				}
			}
		}

		template <class T> static void read(vector<T> &x) {
			string temp;
			bool finished = false;
			string token = "";
			while (!finished) {
				do {
					getline(cin, temp);
				} while (temp == "");
				for (int i = temp.find("{") + 1; i < (int)temp.length(); ++i) {
					if (temp[i] == '\\') ++i;
					else if ((temp[i] == ',') || (temp[i] == '}')) {
						if (temp[i] == '}') finished = true;
						bool empty = true;
						for (int j = 0; j < (int)token.length(); ++j)
							if (!isspace(token[j])) empty = false;
						if (!empty) {
							T t;
							istringstream iss(token);
							iss >> t;
							x.push_back(t);
						}
						token = "";
					} else token += temp[i];
				}
			}
		}

	};

	class TCWriter {
#ifdef _WINDOWS_
		static HANDLE hConsole;
#endif
	public:
		static void setColor(int color) {
#ifdef _WINDOWS_
			if (!hConsole) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
#else
			char command[13];
			sprintf(command, "%c[%d;%d;%dm", 0x1B, color >> 8, (color & 255) + 30, BLACK + 40);
			printf("%s", command);
#endif
		}
		static void write(char x) {
			cout << '\'' << x << '\'';
		}

		static void write(string x) {
			cout << '"' << x << '"';
		}

		template <class T> static void write(T x) {
			cout << fixed << setprecision(16) << x;
		}

		template <class T> static void write(vector<T> x) {
			cout << '{';
			bool first = true;
			for (typename vector<T>::iterator it = x.begin(); it != x.end(); ++it) {
				if (!first) cout << ", "; else first = false;
				write(*it);
			}
			cout << '}';
		}
	};

#ifdef _WINDOWS_
	HANDLE TCWriter::hConsole = 0;
#endif

	class TCChecker {
		const static double EPS;
	public:
		static bool check(const double &x, const double &y) {
			return (x < y + EPS) && (y < x + EPS);
		}

		template <class T> static bool check(const T &x, const T &y) {
			return x == y;
		}
	};

	const double TCChecker::EPS = 1e-9;
};
