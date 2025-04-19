#include "polynomial.hpp"
#include <math.h>

void TetoPolynomial::addVar(double k, unsigned long pow)
{
    for(std::size_t i =0; i<length;i++)
    {
        if(vdata[i].pow == pow)
        {
            vdata[i].k+=k;
            return;
        }
    }
    if (vdata == nullptr) {
        vdata = new Variable[1];
        length = 0;
    }
    else {
        if ((vdata = (Variable*)std::realloc(vdata, sizeof(Variable) * (length + 1))) == nullptr) {
            throw std::bad_alloc();
        }
    }
    vdata[length++] = Variable{k, pow};
}


void TetoPolynomial::addVar(Variable var)
{
    addVar(var.k,var.pow);
}

TetoPolynomial::TetoPolynomial(Variable var)
{
    addVar(var);
}

TetoPolynomial::TetoPolynomial(const TetoPolynomial &obj) : length(obj.length)
{
    vdata = new Variable[obj.length];
    std::copy(obj.vdata, obj.vdata+obj.length,vdata);
}

TetoPolynomial::TetoPolynomial(TetoPolynomial &&obj) noexcept : length(obj.length)
{
    vdata = obj.vdata;
    obj.vdata = nullptr;
}

TetoPolynomial::TetoPolynomial(float *pol, std::size_t size)
{
    for(std::size_t i = 0; i<size; i++)
    {
        addVar(pol[i],size - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(double *pol, std::size_t size)
{
    for(std::size_t i = 0; i<size; i++)
    {
        addVar(pol[i],size - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<float> pol)
{
    for(std::size_t i = 0; i<pol.size(); i++)
    {
        addVar(pol.begin()[i], pol.size() - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<double> pol)
{
    for(std::size_t i = 0; i<pol.size(); i++)
    {
        addVar(pol.begin()[i], pol.size() - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<Variable> pol)
{
    for(std::size_t i = 0; i<pol.size(); i++)
    {
        addVar(pol.begin()[i]);
    }
}

TetoPolynomial::~TetoPolynomial()
{
    if(vdata != nullptr)
    {
        delete[] vdata;
    }
}

double TetoPolynomial::Calculate(double val)
{
    double result = 0;
    for (std::size_t i = 0;i < length;i++) {
        result += vdata[i].k * std::pow(val, vdata[i].pow);
    }
    return result;
}

int TetoPolynomial::getLength()
{
    return length;
}
