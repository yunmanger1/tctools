#ifndef TCStatementParserException_h

#define TCStatementParserException_h

#include <string>

using namespace std;

namespace tc_utils {
	class TCStatementParserException {
	private:
		string _message;
	public:
		TCStatementParserException(const string &message) {
			_message = message;
		}
		string getMessage() const {
			return _message;
		}
	};
};

#endif
