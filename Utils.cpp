#include "Utils.h"

ostream& operator<<(ostream& os, const vector<int32_t>& obj) {
  const size_t size = obj.size();
  os << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const vector<vector<int32_t>>& obj) {
  const size_t size = obj.size();
  os << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const vector<int64_t>& obj) {
  const size_t size = obj.size();
  os << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const vector<vector<int64_t>>& obj) {
  const size_t size = obj.size();
  os << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const vector<string>& obj) {
  const size_t size = obj.size();
  os << "[";
  for (size_t i = 0; i < size; ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << "]";
  return os;
}
