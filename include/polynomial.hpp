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
    std::size_t length = 0;
    void addVar(double k, unsigned long pow);
    void addVar(Variable var);
    Variable& getVar(unsigned long pow);


public:
    TetoPolynomial() = default;
    TetoPolynomial(Variable var);
    TetoPolynomial(const TetoPolynomial &obj);
    TetoPolynomial(TetoPolynomial &&obj) noexcept;
    TetoPolynomial(float *pol, std::size_t size);
    TetoPolynomial(double *pol, std::size_t size);
    TetoPolynomial(std::initializer_list<float> pol);
    TetoPolynomial(std::initializer_list<double> pol);
    TetoPolynomial(std::initializer_list<Variable> pol);
    ~TetoPolynomial();

    void printData();


    
    [[nodiscard]] double Calculate(double val);
    [[nodiscard]] Variable& at(unsigned long pow);
    [[nodiscard]] Variable& operator[](unsigned long index);



};