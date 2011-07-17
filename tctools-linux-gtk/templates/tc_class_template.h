#include <algorithm>
#include <functional>
#include <utility>

#include <cmath>
#include <numeric>
#include <complex>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include <iomanip>
#include <sstream>

#include <cctype>
#include <cstring>
#include <string>

#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <set>
#include <map>

#include <ext/hash_map>
#include <ext/hash_set>

using namespace std;
using namespace __gnu_cxx;

typedef unsigned char uchar;
typedef short int sint;
typedef unsigned short int usint;
typedef unsigned int uint;
typedef long long i64;
typedef unsigned long long ui64;
typedef double dbl;
typedef long double ldbl;

#define pb push_back
#define mp make_pair

#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

#define _fill(x, v) memset(x, v, sizeof(x))
#define _for(i, a, b) for (__typeof(b) i = (a); i < (b); ++i)
#define _fori(i, a, b) for (int i = (a); i < (b); ++i)
#define _fore(i, a, b) for (__typeof(b) i = (a); i <= (b); ++i)
#define _forei(i, a, b) for (int i = (a); i <= (b); ++i)
#define _forr(i, a, b) for (__typeof(b) i = (a); i >= (b); --i)
#define _forri(i, a, b) for (int i = (a); i >= (b); --i)
#define _foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define _foreachr(i, v) for (__typeof((v).end()) i = (v).end(); i != (v).begin(); --i)
#define _forever while (true)
#define _all(v) v.begin(), v.end()
#define _sort(v) sort(v.begin(), v.end())
#define _uniquev(v) v.resize(unique(v.begin(), v.end()) - v.begin())
#define _unique(v, n) n = unique(v, v + n) - v

const long double EPS = 1e-9;
const int iINF = INT_MAX;
const long double ldblINF = 1e100;

const int dd[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int dd2[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

class $class_name$ {
public:
	$method_signature$ {
		$result_type$ result$result_initialization$;
		return $type_conversion$result;
	}
};