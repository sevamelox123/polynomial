#pragma once
#include <iostream>
struct Variable
{
    double k;
    unsigned long pow;
};
class TetoPolynomial
{
private:
    Variable *vdata = nullptr;
    std::size_t lenght = 0;
    void addVar(double k, unsigned long pow);
    void addVar(Variable var);
    

public:
    TetoPolynomial() = default;
    TetoPolynomial(Variable var); //?
    TetoPolynomial(const TetoPolynomial &obj);
    TetoPolynomial(TetoPolynomial &&obj) noexcept;
};