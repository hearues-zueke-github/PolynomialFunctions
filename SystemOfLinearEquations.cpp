/**
  * @file SystemOfLinearEquations.cpp
  * Modul for solving a nxn integer system of linear equations.
  * @author Rostislav Stanek
  */

#include <iostream>

#include "SystemOfLinearEquations.h"

using namespace std;

/**
 * Computes the determinante of a square nxn matrix. If the matrix is not a square matrix of
 * size at leas 1x1, the function throws a range_error.
 * @param[in] A Matrix.
 * @return[out] Determinante.
 */
int64_t determinante(const vector<vector<int64_t>> &A);
int64_t determinante(const vector<vector<int64_t>> &A) {
  if (A.size() == 0) {
    throw std::range_error("A square matrix of size at least 1x1 is requaired!");
  }
  const uint32_t n = A.size();
  for (const vector<int64_t> &a : A) {
    if (a.size() != n) {
      throw std::range_error("A square matrix of size at least 1x1 is requaired!");
    }
  }

  int64_t result = 0;
  switch (n) {
  case 1: {
    result = A[0][0];
    break;
  }
  case 2: {
    result = A[0][0] * A[1][1] - A[1][0] * A[0][1];
    break;
  }
  case 3: {
    result =
      A[0][0] * A[1][1] * A[2][2] +
      A[0][1] * A[1][2] * A[2][0] +
      A[0][2] * A[1][0] * A[2][1] -
      A[2][0] * A[1][1] * A[0][2] -
      A[2][1] * A[1][2] * A[0][0] -
      A[2][2] * A[1][0] * A[0][1];
    break;
  }
  default: {
    for (uint32_t i = 0; i < n; i++) {
      vector<vector<int64_t> > matrixMinor;
      for (uint32_t j = 0; j < n; j++) {
        if (j != i) {
          matrixMinor.push_back(vector<int64_t>(A[j].begin() + 1, A[j].end()));
        }
      }
      if (i % 2 == 0) {
        result += A[i][0] * determinante(matrixMinor);
      }
      else {
        result -= A[i][0] * determinante(matrixMinor);
      }
    }
    break;
  }
  };

  return result;
}

int solveSystemOfLinearEquations(
  const vector<vector<int64_t> > &A,
  vector<int64_t> &x,
  const vector<int64_t> &B) {
  if (A.size() == 0) {
    throw std::range_error("A square matrix of size at least 1x1 is requaired!");
  }
  const uint32_t n = A.size();
  for (const vector<int64_t> &a : A) {
    if (a.size() != n) {
      throw std::range_error("A square matrix of size at least 1x1 is requaired!");
    }
  }
  if (B.size() != n) {
    throw std::range_error(
      "The right hand side vector has to have the same size as the left hand size matrix!");
  }

  int result = 0;
  x.resize(n);
  const int64_t determinanteA = determinante(A);
  if (determinanteA == 0) {
    result = 1;
  } else {
    for (uint32_t i = 0; i < n; i++) {
      if (result == 0) {
        vector<vector<int64_t> > aX;
        for (uint32_t j = 0; j < n; j++) {
          vector<int64_t> aXRow;
          aXRow.insert(aXRow.end(), A[j].begin(), A[j].begin() + i);
          aXRow.push_back(B[j]);
          aXRow.insert(aXRow.end(), A[j].begin() + i + 1, A[j].end());
          aX.push_back(aXRow);
        }

        const int64_t determinanteAX = determinante(aX);
        if (determinanteAX % determinanteA == 0) {
          x[i] = determinanteAX / determinanteA;
        } else {
          result = 2;
        }
      }
    }
  }

  return result;
}

