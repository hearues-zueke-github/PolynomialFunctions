#ifndef POLYNOMIALFUNCTIONS_UTILS_H
#define POLYNOMIALFUNCTIONS_UTILS_H

#include <ostream>
#include <vector>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, const vector<int32_t>& obj);
ostream& operator<<(ostream& os, const vector<vector<int32_t>>& obj);

ostream& operator<<(ostream& os, const vector<int64_t>& obj);
ostream& operator<<(ostream& os, const vector<vector<int64_t>>& obj);

ostream& operator<<(ostream& os, const vector<vector<string>>& obj);

#endif //POLYNOMIALFUNCTIONS_UTILS_H
