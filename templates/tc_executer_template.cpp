#include <ctime>

#include "TCUtils.h"
#include "$class_name$.h"

using namespace std;
using namespace tc_utils;

int main() {
$parameters_definition$

$parameters_input$

	int __c = getchar(); while (__c != ':') __c = getchar();

	$result_type$ __answer;
	TCReader::read(__answer);

	TCWriter::setColor(LIGHTBLUE);
	cout << "Input:" << endl;
	TCWriter::setColor(WHITE);

$parameters_output$

	TCWriter::setColor(GRAY);
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Output:" << endl;
	TCWriter::setColor(GRAY);
	$class_name$ *__task = new $class_name$();
	int __start = std::clock();
	$result_type$ __result = __task->$method_name$($parameters_list$);
	int __finish = std::clock();
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Answer:" << endl;
	TCWriter::setColor(WHITE);
	TCWriter::write(__result); cout << endl;
	TCWriter::setColor(GRAY);
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Expected:" << endl;
	TCWriter::setColor(WHITE);
	TCWriter::write(__answer); cout << endl;
	TCWriter::setColor(GRAY);
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Result:" << endl;
	TCWriter::setColor(WHITE);
	if (TCChecker::check(__result, __answer)) {
		TCWriter::setColor(GREEN);
		cout << "Yes" << endl;
	} else {
		TCWriter::setColor(RED);
		cout << "No" << endl;
	}
	TCWriter::setColor(GRAY);
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Running time:" << endl;
	TCWriter::setColor(WHITE);
	cout << fixed << setprecision(3) << double(__finish - __start) / double(CLOCKS_PER_SEC) << "s" << endl;
	TCWriter::setColor(GRAY);
	cout << "======================================================================================" << endl;

	TCWriter::setColor(LIGHTBLUE);
	cout << "Comments:" << endl;
	TCWriter::setColor(GRAY);
	return 0;
}
