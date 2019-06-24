#include <assert.h>
#include <iostream>

#include "Polynome.h"
#include "Polynomial.h"
#include "Utils.h"

void testSimplePolynomeEmpty();
void testSimplePolynomeAddSubEqual();
void testSimplePolynomeShiftingFactors();
void testSimplePolynome();
void testPolynomeOutput();
void testMultiplication();
void testDivAndModulo();
void testKroneckerAlgorithm();

void testSimplePolynomeEmpty() {
  Polynome p1;
  Polynome p2(vector<int64_t>{0, 0 ,0});
  Polynome p3 = Polynome(vector<int64_t>{0, 0, 0, 0, 0});
  assert(p1.getFactors().size() == 0);
  assert(p2.getFactors().size() == 0);
  assert(p3.getFactors().size() == 0);
  cout << " - Empty Polynomes are working!" << endl;
}

void testSimplePolynomeAddSubEqual() {
  Polynome p4(vector<int64_t>{1});
  Polynome p4_1(vector<int64_t>{1, 0});
  Polynome p4_2(vector<int64_t>{1, 0, 0, 0, 0, 0});
  Polynome p5(vector<int64_t>{-1});
  assert(p4 == p4_1);
  assert(p4 == p4_2);
  assert((p4 + p5).getFactors().size() == 0);
  assert(p4 != p5);
  assert(-p4 == p5);
  assert(p4 - p5 == Polynome(vector<int64_t>{2}));
  assert((+p4) - (-p5) == Polynome(vector<int64_t>{}));
  cout << " - Very simple +, -, == and != are working!" << endl;
}

void testSimplePolynomeShiftingFactors() {
  Polynome p6(vector<int64_t>{0, 1, 2, 3, 5});
  Polynome p6_r(vector<int64_t>{0, 0, 1, 2, 3, 5});
  Polynome p6_r2(vector<int64_t>{0, 0, 0, 1, 2, 3, 5});
  Polynome p6_l(vector<int64_t>{1, 2, 3, 5});
  Polynome p6_l3(vector<int64_t>{3, 5});
  Polynome p6_l6(vector<int64_t>{});
  Polynome p6_shift_r;
  Polynome p6_shift_r2;
  Polynome p6_shift_l;
  Polynome p6_shift_l3;
  Polynome p6_shift_l6;
  p6.shiftFactors(1, true, p6_shift_r);
  assert(p6_shift_r == p6_r);
  p6.shiftFactors(1, false, p6_shift_l);
  assert(p6_shift_l == p6_l);
  p6.shiftFactors(2, true, p6_shift_r2);
  assert(p6_shift_r2 == p6_r2);
  p6.shiftFactors(3, false, p6_shift_l3);
  assert(p6_shift_l3 == p6_l3);
  p6.shiftFactors(6, false, p6_shift_l6);
  assert(p6_shift_l6 == p6_l6);

  Polynome p7(vector<int64_t>{5, 2, 4, 3, 7, 5, 8});
  Polynome p7_s1(vector<int64_t>{0, 5, 2, 4, 3, 7, 5, 8});
  Polynome p7_s2(vector<int64_t>{4, 3, 7, 5, 8});
  Polynome p7_s3(vector<int64_t>{0, 0, 0, 4, 3, 7, 5, 8});
  Polynome p7_s4(vector<int64_t>{5, 8});
  Polynome p7_s5(vector<int64_t>{});
  Polynome p7_s6(vector<int64_t>{});
  Polynome p7_s7(vector<int64_t>{});
  p7.shiftFactors(1);
  assert(p7 == p7_s1);
  p7.shiftFactors(-3);
  assert(p7 == p7_s2);
  p7.shiftFactors(3);
  assert(p7 == p7_s3);
  p7.shiftFactors(-6);
  assert(p7 == p7_s4);
  p7.shiftFactors(-3);
  assert(p7 == p7_s5);
  p7.shiftFactors(10);
  assert(p7 == p7_s6);
  p7.shiftFactors(-20);
  assert(p7 == p7_s7);
  cout << " - Shifting of factors is working!" << endl;
}

void testSimplePolynome() {
  cout << "Test Simple Polynome operations (+, -, unary +, unary -, == !=, etc.):" << endl;

  testSimplePolynomeEmpty();
  testSimplePolynomeAddSubEqual();
  testSimplePolynomeShiftingFactors();
}

void testPolynomeOutput() {
  cout << "Test Polynome Outputs:" << endl;
  vector<Polynome> polynomes = {
    Polynome(vector<int64_t >{}),
    Polynome(vector<int64_t >{1}),
    Polynome(vector<int64_t >{-1}),
    Polynome(vector<int64_t >{0, 1}),
    Polynome(vector<int64_t >{0, -1}),
    Polynome(vector<int64_t >{0, 0, 1}),
    Polynome(vector<int64_t >{0, 0, -1}),
    Polynome(vector<int64_t >{3, 0, -2}),
    Polynome(vector<int64_t >{-4, 0, 0, 5}),
    Polynome(vector<int64_t >{1, 1, 1, 1}),
    Polynome(vector<int64_t >{-1, -1, -1, -1})
  };

  vector<string> outputs = {
    "0",
    "1",
    "(-1)",
    "x",
    "(-1)*x",
    "x^2",
    "(-1)*x^2",
    "3 + (-2)*x^2",
    "(-4) + 5*x^3",
    "1 + x + x^2 + x^3",
    "(-1) + (-1)*x + (-1)*x^2 + (-1)*x^3"
  };

  uint32_t matching_strings = 0;
  for (size_t i = 0; i < polynomes.size(); ++i) {
    string test_string = outputs.at(i);
    string current_string = polynomes.at(i).getOutputString();
    cout << "i: " << i << ", current_string: '" << current_string << "', test_string: '" << test_string << "'" << ", factors: " << polynomes.at(i).getFactors() << endl;
    if (current_string == test_string) {
      matching_strings += 1;
    }
  }

  cout << "RESULTS:" << endl;
  cout << "matching_strings / total_matches: " << matching_strings  << " / " << polynomes.size() << endl;

  assert(matching_strings == polynomes.size());
}

void testMultiplication() {
  cout << "Check for multiplication:" << endl;
  Polynome p1_l1 = Polynome(vector<int64_t >{-1, 1});
  Polynome p1_l2 = Polynome(vector<int64_t >{-2, 1});
  Polynome p1_r = Polynome(vector<int64_t >{2, -3, 1});

  cout << "--- Polynom check Nr. 1 ---" << endl;
  cout << " - p1_l1: " << p1_l1 << endl;
  cout << " - p1_l2: " << p1_l2 << endl;
  cout << " - p1_l1 * p1_l2: " << (p1_l1 * p1_l2) << endl;
  cout << " - p1_r: " << p1_r << endl;
  cout << " - (p1_l1 * p1_l2) == p1_r ? " << (((p1_l1 * p1_l2) == p1_r) ? "Yes!" : "NOO!!!") << endl;

  Polynome p2_l1 = Polynome(vector<int64_t>{6, -5, 1});
  Polynome p2_l2 = Polynome(vector<int64_t>{-1, 1, -1, 1});
  Polynome p2_r = Polynome(vector<int64_t>{-6, 11, -12, 12, -6, 1});

  cout << "--- Polynom check Nr. 2 ---" << endl;
  cout << " - p2_l1: " << p2_l1 << endl;
  cout << " - p2_l2: " << p2_l2 << endl;
  cout << " - p2_l1 * p2_l2: " << (p2_l1 * p2_l2) << endl;
  cout << " - p2_r: " << p2_r << endl;
  cout << " - (p2_l1 * p2_l2) == p2_r ? " << (((p2_l1 * p2_l2) == p2_r) ? "Yes!" : "NOO!!!") << endl;

  assert((p1_l1 * p1_l2) == p1_r);
  assert((p2_l1 * p2_l2) == p2_r);
}

// TODO: do div and modulo (/ %)
void testDivAndModulo() {
  cout << "Check for divide and modulo:" << endl;
  Polynome p3_l1 = Polynome(vector<int64_t >{1, 1, 1, 1});
  Polynome p3_l2 = Polynome(vector<int64_t >{1, -1, 1});
  Polynome p3_r1 = Polynome(vector<int64_t >{2, 1});
  Polynome p3_r2= Polynome(vector<int64_t >{-1, 2});

  cout << "--- Polynom check Nr. 3 ---" << endl;
  cout << " - p3_l1: " << p3_l1 << endl;
  cout << " - p3_l2: " << p3_l2 << endl;
  cout << " - p3_l1 / p3_l2: " << (p3_l1 / p3_l2) << endl;
  cout << " - p3_r1: " << p3_r1 << endl;
  cout << " - (p3_l1 / p3_l2) == p3_r1 ? " << (((p3_l1 / p3_l2) == p3_r1) ? "Yes!" : "NOO!!!") << endl;
  cout << " - p3_l1 % p3_l2: " << (p3_l1 % p3_l2) << endl;
  cout << " - p3_r2: " << p3_r2 << endl;
  cout << " - (p3_l1 % p3_l2) == p3_r2 ? " << (((p3_l1 % p3_l2) == p3_r2) ? "Yes!" : "NOO!!!") << endl;

  Polynome p4_l1 = Polynome(vector<int64_t >{-6, 11, -12, 12, -6, 1});
  Polynome p4_l2 = Polynome(vector<int64_t >{6, -5, 1});
  Polynome p4_r1 = Polynome(vector<int64_t >{-1, 1, -1, 1});
  Polynome p4_r2= Polynome(vector<int64_t >{});

  cout << "--- Polynom check Nr. 4 ---" << endl;
  cout << " - p4_l1: " << p4_l1 << endl;
  cout << " - p4_l2: " << p4_l2 << endl;
  cout << " - p4_l1 / p4_l2: " << (p4_l1 / p4_l2) << endl;
  cout << " - p4_r1: " << p4_r1 << endl;
  cout << " - (p4_l1 / p4_l2) == p4_r1 ? " << (((p4_l1 / p4_l2) == p4_r1) ? "Yes!" : "NOO!!!") << endl;
  cout << " - p4_l1 % p4_l2: " << (p4_l1 % p4_l2) << endl;
  cout << " - p4_r2: " << p4_r2 << endl;
  cout << " - (p4_l1 % p4_l2) == p4_r2 ? " << (((p4_l1 % p4_l2) == p4_r2) ? "Yes!" : "NOO!!!") << endl;

  assert((p3_l1 / p3_l2) == p3_r1);
  assert((p3_l1 % p3_l2) == p3_r2);
  assert((p4_l1 / p4_l2) == p4_r1);
  assert((p4_l1 % p4_l2) == p4_r2);
}

// TODO: x^2+4*x^1+1 -> (x+1)^2 is missing!
void testKroneckerAlgorithm() {
  cout << "Check for Kronecker algorithm:" << endl;

  Polynome p5_l = Polynome(vector<int64_t >{-6, 11, -12, 12, -6, 1});
  Polynomial p5_l_poly;
  p5_l.findAllPolynomeFactors(p5_l_poly);
  Polynomial p5_r_poly(vector<Polynome>{
    Polynome(vector<int64_t>{-3, 1}),
    Polynome(vector<int64_t>{-2, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{1, 0, 1})
  });
  Polynome p5_r;
  p5_r_poly.multiplyPolynomials(p5_r);
  cout << "--- Polynom check Nr. 5 ---" << endl;
  cout << " - p5_l: " << p5_l << endl;
  cout << " - p5_l_poly: " << p5_l_poly << endl;
  cout << " - p5_r_poly: " << p5_r_poly << endl;
  cout << " - p5_r: " << p5_r << endl;
  cout << " - (p5_l == p5_r) ? " << (((p5_l == p5_r)) ? "Yes!" : "NOO!!!") << endl;
  cout << " - (p5_l_poly == p5_r_poly) ? " << (((p5_l_poly == p5_r_poly)) ? "Yes!" : "NOO!!!") << endl;

  Polynome p6_l = Polynome(vector<int64_t >{-2, 9, 18, -73, 45, -27, 10});
  Polynomial p6_l_poly;
  p6_l.findAllPolynomeFactors(p6_l_poly);
  Polynomial p6_r_poly(vector<Polynome>{
    Polynome(vector<int64_t>{-2, 1}),
    Polynome(vector<int64_t>{-1, 5}),
    Polynome(vector<int64_t>{-1, 2}),
    Polynome(vector<int64_t>{1, 3, 0, 1})
  });
  Polynome p6_r;
  p6_r_poly.multiplyPolynomials(p6_r);
  cout << "--- Polynom check Nr. 5 ---" << endl;
  cout << " - p6_l: " << p6_l << endl;
  cout << " - p6_l_poly: " << p6_l_poly << endl;
  cout << " - p6_r_poly: " << p6_r_poly << endl;
  cout << " - p6_r: " << p6_r << endl;
  cout << " - (p6_l == p6_r) ? " << (((p6_l == p6_r)) ? "Yes!" : "NOO!!!") << endl;
  cout << " - (p6_l_poly == p6_r_poly) ? " << (((p6_l_poly == p6_r_poly)) ? "Yes!" : "NOO!!!") << endl;

  Polynome p7_l = Polynome(vector<int64_t >{-1, 7, -21, 35, -35, 21, -7, 1});
  Polynomial p7_l_poly;
  p7_l.findAllPolynomeFactors(p7_l_poly);
  Polynomial p7_r_poly(vector<Polynome>{
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1}),
    Polynome(vector<int64_t>{-1, 1})
  });
  Polynome p7_r;
  p7_r_poly.multiplyPolynomials(p7_r);
  cout << "--- Polynom check Nr. 5 ---" << endl;
  cout << " - p7_l: " << p7_l << endl;
  cout << " - p7_l_poly: " << p7_l_poly << endl;
  cout << " - p7_r_poly: " << p7_r_poly << endl;
  cout << " - p7_r: " << p7_r << endl;
  cout << " - (p7_l == p7_r) ? " << (((p7_l == p7_r)) ? "Yes!" : "NOO!!!") << endl;
  cout << " - (p7_l_poly == p7_r_poly) ? " << (((p7_l_poly == p7_r_poly)) ? "Yes!" : "NOO!!!") << endl;

  assert(p5_l == p5_r);
  assert(p5_l_poly == p5_r_poly);
  assert(p6_l == p6_r);
  assert(p6_l_poly == p6_r_poly);
  assert(p7_l == p7_r);
  assert(p7_l_poly == p7_r_poly);
}

int main() {
  testSimplePolynome();

  cout << endl;
  testPolynomeOutput();

  cout << endl;
  testMultiplication();

  cout << endl;
  testDivAndModulo();

  cout << endl;
  testKroneckerAlgorithm();

  return 0;
}
