/**
  * @file SystemOfLinearEquations.h
  * Modul for solving a nxn integer system of linear equations.
  * @author Rostislav Stanek
  */

#ifndef SYSTEMOFLINEAREQUATIONS_H_INCLUDED
#define SYSTEMOFLINEAREQUATIONS_H_INCLUDED

#include <vector>
#include <stdexcept>


/**
 * Solves a nxn integer system of linear equations. If the left hand side matrix is not
 * a square matrix of size at leas 1x1 or if the right hand side vector has not the same
 * size as the left hand side matrix, the function throws a range_error.
 * @param[in] A Left hand side matrix.
 * @param[out] x Solution vector.
 * @param[in] B Right hand sidevector.
 * @return[out]
 *   <ul>
 *     <li>0 The function succeed.</li>
 *     <li>1 The system of linear equations has no unique solution.</li>
 *     <li>2 The system of linear equations has no integer solution.</li>
 *   </ul>
 */
int32_t solveSystemOfLinearEquations(
    const std::vector<std::vector<int64_t> > &A,
    std::vector<int64_t> &x,
    const std::vector<int64_t> &B);


#endif // SYSTEMOFLINEAREQUATIONS_H_INCLUDED
