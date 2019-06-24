#include "Polynome.h"
#include "Polynomial.h"

Polynomial::Polynomial() : _polynomes(vector<Polynome>{}), _occurences() {
}

Polynomial::Polynomial(const vector<Polynome>& polynomes) : _polynomes(polynomes), _occurences() {
  _occurences.resize(_polynomes.size(), 1);
}

Polynomial::Polynomial(const Polynomial& obj) : _polynomes(obj._polynomes), _occurences(obj._occurences) {
}

Polynomial::~Polynomial() {
  _polynomes.clear();
}

const vector<Polynome>& Polynomial::getPolynomes() const {
  return _polynomes;
}

void Polynomial::setPolynomes(const vector<Polynome>& polynomes) {
  _polynomes = polynomes;
  _occurences.resize(polynomes.size(), 1);
}

void Polynomial::multiplyPolynomials(Polynome &p) {
  p = Polynome(vector<int64_t>{1});

  size_t l = _polynomes.size();
  for (size_t i = 0; i < l; ++i) {
    p = p * _polynomes.at(i);
  }
}

ostream& operator<<(ostream& os, const Polynomial& obj) {
  size_t size = obj._polynomes.size();

  if (size == 0) {
    os << "0";
  } else if (size == 1) {
    int64_t times = obj._occurences.at(0);
    const Polynome& p = obj._polynomes.at(0);
    if (times == 1) {
      os << p;
    } else {
      os << "(" << p << ")^" << times;
    }
  } else {
    for (size_t i = 0; i < size; ++i) {
      int64_t times = obj._occurences.at(i);
      const Polynome& p = obj._polynomes.at(i);
      if (i > 0) {
        os << " * ";
      }
      os << "(" << p << ")";
      if (times > 1) {
        os << "^" << times;
      }
    }
  }

  return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
  bool are_equal = true;

  vector<Polynome> polynomes_l(lhs._polynomes); // will stay the same with signs
  vector<Polynome> polynomes_r(rhs._polynomes); // will change two signs if needed!

  bool is_loop_finished = false;
  while (are_equal && !is_loop_finished) {
    if (polynomes_l.size() != polynomes_r.size()) {
      is_loop_finished = true;
      are_equal = false;
    } else if (polynomes_l.size() == 0 && polynomes_r.size() == 0) {
      is_loop_finished = true;
    } else {
      const Polynome& p_l = polynomes_l.at(0);

      bool is_inner_loop_finished = false;
      const size_t size = polynomes_r.size();
      for (size_t i = 0; i < size && !is_inner_loop_finished; ++i) {
        const Polynome& p_r = polynomes_r.at(i);

        if (p_l == p_r) {
          polynomes_r.erase(find(polynomes_r.begin(), polynomes_r.end(), p_r));
          is_inner_loop_finished = true;
        } else if (p_l == -p_r) {
          polynomes_r.erase(find(polynomes_r.begin(), polynomes_r.end(), p_r));
          is_inner_loop_finished = true;

          if (polynomes_r.size() == 0) {
            is_loop_finished = true;
            are_equal = false;
          } else {
            polynomes_r.at(0) = -polynomes_r.at(0);
          }
        }
      }
      polynomes_l.erase(find(polynomes_l.begin(), polynomes_l.end(), p_l));
    }
  }

  return are_equal;
}
