#include "Polynome.h"
#include "Polynomial.h"

Polynome::Polynome() : _factors(vector<int64_t>{}) {
  checkZerosFactors();
}

Polynome::Polynome(const vector<int64_t>& factors) : _factors(factors) {
  checkZerosFactors();
}

Polynome::Polynome(const Polynome& obj) : _factors(obj._factors) {
  checkZerosFactors();
}

Polynome::~Polynome() {
  _factors.clear();
}

void Polynome::shiftFactors(int64_t factor) {
  size_t l = _factors.size();

  if (factor > 0 && l > 0) {
    size_t new_l = l + factor;
    _factors.resize(new_l, 0);

    for (size_t i = 0; i < l; ++i) {
      _factors.at(new_l - 1 - i) = _factors.at(l - 1 - i);
      _factors.at(l - 1 - i) = 0;
    }
  } else if (factor < 0) {
    factor = -factor;

    if (l > factor) {
      size_t new_l = l - factor;

      for (size_t i = 0; i < new_l; ++i) {
        _factors.at(i) = _factors.at(i + factor);
      }

      _factors.resize(new_l);
    } else if (l <= factor) {
      _factors.clear();
    }
  }
}

void Polynome::checkZerosFactors() {
  size_t found_zeros = 0;
  size_t l = _factors.size();

  bool is_still_zero = true;
  for (size_t i = l; (i > 0) && is_still_zero; --i) {
    if (_factors.at(i - 1) != 0) {
      is_still_zero = false;
    } else {
      found_zeros += 1;
    }
  }

  if (found_zeros > 0) {
    _factors.resize(l - found_zeros, 0);
  }
}

void Polynome::multiplyWithInt(int64_t factor) {
  size_t l = _factors.size();

  for (size_t i = 0; i < l; ++i) {
    _factors.at(i) *= factor;
  }
}

void Polynome::calcDivMod(const Polynome& lhs, const Polynome& rhs, Polynome& q, Polynome& r) {
  Polynome lhs_change(lhs);
  Polynome rhs_change(rhs);

  size_t s_l = lhs_change._factors.size();
  const size_t s_r = rhs_change._factors.size();

  if (s_l < s_r) {
    q._factors.clear();
  } else {
    // Do the division as it is needed
    int64_t highest_value_denominator = rhs_change._factors.at(s_r - 1);
    rhs_change.shiftFactors(s_l - s_r);

    bool are_factors_divisable = true;
    const size_t max_iterations = s_l - s_r;
    for (size_t i = 0; (i <= max_iterations) && are_factors_divisable; ++i) {
      int64_t highest_value_numerator = lhs_change._factors.at(s_l - 1);
      if (abs(highest_value_numerator) % abs(highest_value_denominator) == 0) {
        int value = highest_value_numerator / highest_value_denominator;
        q._factors.insert(q._factors.begin(), value); // add the values in reverse order!
        lhs_change = lhs_change - (rhs_change * value);
        s_l -= 1;
        lhs_change._factors.resize(s_l);
        rhs_change.shiftFactors(-1);
      } else {
        are_factors_divisable = false;
      }
    }
  }

  r = lhs_change;
}

const vector<int64_t>& Polynome::getFactors() const {
  return _factors;
}

void Polynome::shiftFactors(size_t shift, bool shift_right, Polynome& p) {
  p = *this;
  size_t l = p._factors.size();

  if (shift > 0) {
    if (shift_right) {
      size_t new_l = l + shift;
      p._factors.resize(new_l, 0);

      for (size_t i = 0; i < l; ++i) {
        p._factors.at(new_l - 1 - i) = p._factors.at(l - 1 - i);
        p._factors.at(l - 1 - i) = 0;
      }
    } else {
      if (l > shift) {
        size_t new_l = l - shift;

        for (size_t i = 0; i < new_l; ++i) {
          p._factors.at(i) = p._factors.at(i + shift);
        }

        p._factors.resize(new_l);
      } else if (l <= shift) {
        p._factors.clear();
      }
    }
  }
}

string Polynome::getOutputString() const {
  stringstream ss;
  size_t l = _factors.size();
  size_t written_factors = 0;
  if (l == 0) {
    ss << "0";
  } else {
    int64_t a;
    a = _factors.at(0);
    if (a != 0) {
      written_factors += 1;

      if (a < 0) {
        ss << "(" << a << ")";
      } else {
        ss << a;
      }
    }

    for (size_t i = 1; i < l; ++i) {
      bool print_x = true;
      a = _factors.at(i);

      if (a == 0) {
        print_x = false;
      } else {
        if (written_factors > 0) {
          ss << " + ";
        }
        written_factors += 1;

        if (a < 0) {
          ss << "(" << a << ")*";
        } else if (a != 1) {
          ss << a << "*";
        }
      }

      if (print_x) {
        ss << "x";
        if (i > 1) {
          ss << "^" << i;
        }
      }
    }
  }

  return ss.str();
}

ostream& operator<<(ostream& os, const Polynome& obj) {
//  os << "WAS HERE!!!" << endl;
  os << obj.getOutputString();

  return os;
}

Polynome& Polynome::operator=(Polynome const& rhs) {
  if (this != &rhs) {
    Polynome tmp(rhs);
    _factors = tmp._factors;
  }
  return *this;
}

Polynome Polynome::operator+(const Polynome& rhs) {
  vector<int64_t> f1 = _factors;
  vector<int64_t> f2 = rhs._factors;

  size_t l1 = f1.size();
  size_t l2 = f2.size();

  size_t l = l1;

  if (l1 != l2) {
    if (l1 > l2) {
      f2.resize(l1, 0);
    } else {
      f1.resize(l2, 0);
      l = l2;
    }
  }

  for (size_t i = 0; i < l; ++i) {
    f1.at(i) += f2.at(i);
  }

  Polynome p3(f1);
  return p3;
}

Polynome Polynome::operator-(const Polynome& rhs) {
  vector<int64_t> f1 = _factors;
  vector<int64_t> f2 = rhs._factors;

  size_t l1 = f1.size();
  size_t l2 = f2.size();

  size_t l = l1;

  if (l1 != l2) {
    if (l1 > l2) {
      f2.resize(l1, 0);
    } else {
      f1.resize(l2, 0);
      l = l2;
    }
  }

  for (size_t i = 0; i < l; ++i) {
    f1.at(i) -= f2.at(i);
  }

  Polynome p3(f1);
  return p3;
}

Polynome Polynome::operator+() const {
  Polynome p(*this);
  return p;
}

Polynome Polynome::operator-() const {
  Polynome p(*this);
  size_t size = p._factors.size();

  for (size_t i = 0; i < size; ++i) {
    p._factors.at(i) = -p._factors.at(i);
  }

  return p;
}

Polynome operator*(const Polynome& lhs, const int64_t rhs) {
  Polynome p(lhs);
  p.multiplyWithInt(rhs);
  return p;
}

Polynome operator*(const int64_t lhs, const Polynome& rhs) {
  Polynome p(rhs);
  p.multiplyWithInt(lhs);
  return p;
}

Polynome operator*(const Polynome& lhs, const Polynome& rhs) {
  Polynome p = Polynome(vector<int64_t >());

  const vector<int64_t>& factors = rhs._factors;
  size_t l = factors.size();
  for (size_t i = 0; i < l; ++i) {
    int64_t factor = factors.at(i);
    Polynome p1 = lhs * factor;
    p1.shiftFactors(i);
    p = (p + p1);
  }

  return p;
}



Polynome operator/(const Polynome& lhs, const Polynome& rhs) {
  Polynome q(vector<int64_t>({}));
  Polynome r(vector<int64_t>({}));

  q.calcDivMod(lhs, rhs, q, r);

  return q;
}

Polynome operator%(const Polynome& lhs, const Polynome& rhs) {
  Polynome q(vector<int64_t>({}));
  Polynome r(vector<int64_t>({}));

  q.calcDivMod(lhs, rhs, q, r);

  return r;
}

bool operator!=(const Polynome& lhs, const Polynome& rhs) {
  return !(lhs == rhs);
}

bool operator==(const Polynome& lhs, const Polynome& rhs) {
  bool are_equal = true;

  const vector<int64_t> f1 = lhs._factors;
  const vector<int64_t> f2 = rhs._factors;

  size_t l1 = f1.size();
  size_t l2 = f2.size();

  if (l1 != l2) {
    are_equal = false;
  } else {
    for (size_t i = 0; (i < l1) && are_equal; ++i) {
      if (f1.at(i) != f2.at(i)) {
        are_equal = false;
      }
    }
  }

  return are_equal;
}

bool operator==(const Polynome& lhs, const int64_t rhs) {
  return lhs == Polynome(vector<int64_t>{rhs});
}

bool operator==(const int64_t lhs, const Polynome& rhs) {
  return Polynome(vector<int64_t>{lhs}) == rhs;
}

int64_t Polynome::f(const int64_t x) const {
  size_t size = _factors.size();
  int64_t s = 0;
  int64_t x_pow = 1;

  for (size_t i = 0; i < size; ++i) {
    s += _factors.at(i) * x_pow;
    x_pow *= x;
  }

  return s;
}

int64_t Polynome::getIntSqrt(const int64_t n) {
  int64_t n_prev_2 = n;
  int64_t n_prev = n;
  int64_t n_next = int((n + n / n) / 2);

  while ((n_prev != n_next) && (n_prev_2 != n_next)) {
    n_prev_2 = n_prev;
    n_prev = n_next;
    n_next = int((n_prev + n / n_prev) / 2);
  }

  return n_next;
}

void Polynome::getPrimes(const int64_t n, vector<int64_t>& ps) {
  ps.clear();
  ps.push_back(2);
  ps.push_back(3);
  ps.push_back(5);
  size_t ps_size = 3;

  int64_t p = 7;
  while (p <= n) {
    const int64_t p_sqrt = getIntSqrt(p) + 1;
    bool is_prime = true;
    bool not_finish_loop = true;
    for (size_t i = 0; (i < ps_size) && not_finish_loop; ++i) {
      const int64_t p2 = ps.at(i);
      if (p2 > p_sqrt) {
        not_finish_loop = false;
      } else if (p % p2 == 0) {
        is_prime = false;
        not_finish_loop = false;
      }
    }

    if (is_prime) {
      ps_size += 1;
      ps.push_back(p);
    }

    p += 2;
  }
}

void Polynome::getAllFactorsPosNeg(const int64_t n, const vector<int64_t>& ps, vector<int64_t>& factors) {
  if (n == 0) {
    factors = {0};
  } else if (n == 1 || n == -1) {
    factors = {1, -1};
  } else {
    factors.resize(0);
    int64_t n_pos = (n < 0 ? -n : n);

    // get all prime factors of the number n_pos
    vector<int64_t> p_factors;
    vector<int64_t> p_exp_factors;

    const size_t ps_size = ps.size();
    bool is_not_finished = true;
    for (size_t i = 0; (i < ps_size) && is_not_finished; ++i) {
      const int64_t p = ps.at(i);

      int64_t len = 0;
      while (n_pos % p == 0) {
        n_pos /= p;
        len += 1;
      }

      if (len > 0) {
        p_factors.push_back(p);
        p_exp_factors.push_back(len);

        if (n_pos == 1) {
          is_not_finished = false;
        }
      }
    }

    if (p_factors.size() == 0) {
      p_factors.push_back(n);
      p_exp_factors.push_back(1);
    }

    // now go all possible combinations of the p_factors to get all factors of the number n!
    const size_t p_fac_size = p_factors.size();
    vector<int64_t> exponents;
    exponents.resize(p_fac_size, 0);
    exponents.at(0) = -1;

    bool is_finished_cycle = false;
    while (!is_finished_cycle) {
      size_t i = 0;
      bool need_more_cycles = true;
      while (i < p_fac_size && need_more_cycles) {
        exponents.at(i) += 1;
        if (exponents.at(i) > p_exp_factors.at(i)) {
          exponents.at(i) = 0;
          i += 1;
        } else {
          need_more_cycles = false;
        }
      }

      if (i >= p_fac_size) {
          is_finished_cycle = true;
      } else {
        int64_t prod = 1;
        for (size_t j = 0; j < p_fac_size; ++j) {
          const int64_t p = p_factors.at(j);
          int64_t p_pow = 1;
          const int64_t exp = exponents.at(j);
          for (int64_t k = 0; k < exp; ++k) {
            p_pow *= p;
          }
          prod *= p_pow;
        }
        factors.push_back(prod);
      }
    }

    const size_t factors_size_pos = factors.size();

    for (size_t i = 0; i < factors_size_pos; ++i) {
      factors.push_back(-factors.at(i));
    }
  }
}

int Polynome::findOnePolynomeFactorForDegreeN(const Polynome &p, const int64_t n, Polynome &p_factor) {
  int ret_val = 1;
  // first get the x and f values for x = {0, 1, 2, ... , degree of polynome}
  vector<int64_t> xs;
  vector<int64_t> fs;
  int64_t max_f = p.f(0);
  for (int64_t x = 0; x < n; ++x) {
    xs.push_back(x);

    int64_t f_x = p.f(x);
    if (f_x < 0) {
      f_x = -f_x;
    }
    fs.push_back(f_x);

    if (max_f < f_x) {
      max_f = f_x;
    }
  }

//  cout << "max_f:" << max_f << endl;
//  cout << "xs: " << xs << endl;
//  cout << "fs: " << fs << endl;

  vector<int64_t> ps;
  getPrimes(getIntSqrt(max_f)+1, ps);

//  cout << "ps: " << ps << endl;

  vector<vector<int64_t>> fs_factors;
  vector<size_t> fs_factors_lens;
  for (int64_t j = 0; j < n; ++j) {
    const int64_t fx = fs.at(j);
    vector<int64_t> f_factors;

    getAllFactorsPosNeg(fx, ps, f_factors);
//    cout << "fx: " << fx << endl;
//    cout << "f_factors: " << f_factors << endl;

    fs_factors.push_back(f_factors);
    fs_factors_lens.push_back(f_factors.size());
  }

  vector<int64_t> row(n);
  vector<vector<int64_t>> A;
  vector<int64_t> B(n);
  for (int64_t j = 0; j < n; ++j) {
    const int64_t x = xs.at(j);

    if (x == 0) {
      row.at(0) = 1;
    }

    int64_t x_pow = 1;
    for (int64_t i = 1; i < n; ++i) {
      x_pow *= x;
      row.at(i) = x_pow;
    }

    A.push_back(row);
  }

//  cout << "A: " << A << endl;

  const size_t fs_fac_size = fs_factors.size();
  vector<int64_t> positions;
  positions.resize(fs_fac_size, 0);
  positions.at(0) = -1;

//  cout << "fs_factors: " << fs_factors << endl;

  bool is_finished_cycle = false;
  while (!is_finished_cycle) {
    size_t i = 0;
    bool need_more_cycles = true;
    while (i < fs_fac_size && need_more_cycles) {
      positions.at(i) += 1;
      if (positions.at(i) >= fs_factors_lens.at(i)) {
        positions.at(i) = 0;
        i += 1;
      } else {
        need_more_cycles = false;
      }
    }

    if (i >= fs_fac_size) {
      is_finished_cycle = true;
    } else {
      for (size_t j = 0; j < fs_fac_size; ++j) {
        B.at(j) = fs_factors.at(j).at(positions.at(j));
      }
//      cout << "B: " << B << endl;
      vector<int64_t> x;
      int ret_val_2 = solveSystemOfLinearEquations(A, x, B);
      if (ret_val_2 == 0) {
//        cout << "  x was found!" << endl;
//        cout << "  x: " << x << endl;
        Polynome p_x = Polynome(x);

//        cout << "  p_x: " << p_x << endl;
        Polynome p_div = p / p_x;
        Polynome p_rest = p % p_x;
//        cout << "  p_div: " << p_div << endl;
//        cout << "  p_rest._factors: " << p_rest._factors << endl;
        if ((p_x._factors.size() > 1) &&
            (p_rest._factors.size() == 0) &&
            (p_div._factors.size() > 1 ||
             ((p_div._factors.size() == 1) && (p_div._factors.at(0) != 1 || p_div._factors.at(0) != -1)))
          ) {
//          cout << "FOUND THE TRUE POLYNOME DIVISION!" << endl;
          is_finished_cycle = true;
          ret_val = 0;
          p_factor = x;
        }
      }
    }
  }

  return ret_val;
}

int Polynome::findOnePolynomeFactor(const Polynome& p, Polynome& p_factor) {
  int ret_val = 1;

  p_factor._factors.resize(0);
  if (p._factors.size() > 0) {
    const int64_t max_degree = p._factors.size() / 2 + 2;
//    cout << "max_degree: " << max_degree << endl;
    for (int64_t n = 2; (n < max_degree) && (ret_val > 0); ++n) {
//      cout << "n: " << n << endl;
      ret_val = findOnePolynomeFactorForDegreeN(p, n, p_factor);
    }
  }

  return ret_val;
}

// Kronecker Algorithm!
void Polynome::findAllPolynomeFactors(Polynomial& polynomial)
{
  Polynome p(*this);
  vector<Polynome> p_factors;
  int ret_val = 0;

  while (ret_val == 0) {
    Polynome p_one_factor;
    ret_val = p.findOnePolynomeFactor(p, p_one_factor);
    if (ret_val == 0) {
      const vector<int64_t>& poly_factors = p_one_factor.getFactors();
      if (poly_factors.size() == 1) {
        ret_val = 1;
      } else {
      p = p / p_one_factor;
      p_factors.push_back(p_one_factor);
      if (p.getFactors().size() < 3) {
      ret_val = 1;
      p_factors.push_back(p);
      }
      }
    } else {
    p_factors.push_back(p);
    ret_val = 1;
    }
  }

  polynomial.setPolynomes(p_factors);
}
