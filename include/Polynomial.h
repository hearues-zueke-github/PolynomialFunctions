//
// Created by doublepmcl on 06.06.19.
//

#ifndef SIMPLEVECTORPRINTS_POLYNOMIAL_H
#define SIMPLEVECTORPRINTS_POLYNOMIAL_H


#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "Utils.h"

class Polynome;

using namespace std;

class Polynomial {
private:
    vector<Polynome> _polynomes;
    vector<int64_t> _occurences;
public:
  Polynomial();
  Polynomial(const vector<Polynome>& polynomes);
  Polynomial(const Polynomial& obj);
  virtual ~Polynomial();

  const vector<Polynome>& getPolynomes() const;
  void setPolynomes(const vector<Polynome>& polynomes);

  void multiplyPolynomials(Polynome &p);

  friend ostream& operator<<(ostream& os, const Polynomial& obj);

  friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
};

#endif //SIMPLEVECTORPRINTS_POLYNOMIAL_H
