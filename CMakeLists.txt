cmake_minimum_required(VERSION 3.14)
project(PolynomialFunctions)

set(CMAKE_CXX_STANDARD 11)

add_executable(
	PolynomialFunctions
	main.cpp
	src/Polynome.cpp
	src/Polynomial.cpp
	src/Utils.cpp
	src/SystemOfLinearEquations.cpp
)
target_include_directories(PolynomialFunctions PUBLIC "include")
