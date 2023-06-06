#ifndef SIMPLEVECTORPRINTS_POLYNOME_H
#define SIMPLEVECTORPRINTS_POLYNOME_H

#include <vector>
#include <sstream>
#include <iostream>

#include "SystemOfLinearEquations.h"
#include "Utils.h"

using namespace std;

class Polynomial;

class Polynome {
private:
  friend class Polynomial;
  vector<int64_t> _factors;
  void checkZerosFactors();
  void multiplyWithInt(int64_t factor);
  void calcDivMod(const Polynome& lhs, const Polynome& rhs, Polynome& q, Polynome& r);

  int64_t getIntSqrt(const int64_t n);
  void getPrimes(const int64_t n, vector<int64_t>& ps);
  void getAllFactorsPosNeg(const int64_t n, const vector<int64_t>& ps, vector<int64_t>& factors);
  int findOnePolynomeFactorForDegreeN(const Polynome &p, const int64_t n, Polynome &p_factor);
  int findOnePolynomeFactor(const Polynome& p, Polynome& p_factor);
public:
  Polynome();
  Polynome(const vector<int64_t>& factors);
  Polynome(const Polynome& obj);
  virtual ~Polynome();

  const vector<int64_t>& getFactors() const;

  void shiftFactors(int64_t factor);
  void shiftFactors(size_t shift, bool shift_right, Polynome& p);
  string getOutputString() const;

  friend ostream& operator<<(ostream& os, const Polynome& obj);
  Polynome& operator=(const Polynome& rhs);
  Polynome operator+(const Polynome& rhs);
  Polynome operator-(const Polynome& rhs);
  Polynome operator+() const;
  Polynome operator-() const;
  friend Polynome operator*(const Polynome& lhs, const int64_t rhs);
  friend Polynome operator*(const int64_t lhs, const Polynome& rhs);
  friend Polynome operator*(const Polynome& lhs, const Polynome& rhs);
  friend Polynome operator/(const Polynome& lhs, const Polynome& rhs);
  friend Polynome operator%(const Polynome& lhs, const Polynome& rhs);
  friend bool operator!=(const Polynome& lhs, const Polynome& rhs);
  friend bool operator==(const Polynome& lhs, const Polynome& rhs);
  friend bool operator==(const Polynome& lhs, const int64_t rhs);
  friend bool operator==(const int64_t lhs, const Polynome& rhs);

  int64_t f(const int64_t x) const;
  void findAllPolynomeFactors(Polynomial& polynomial);
};


#endif //SIMPLEVECTORPRINTS_POLYNOME_H
