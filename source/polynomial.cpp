#include "polynomial.hpp"
#include <math.h>

void TetoPolynomial::addVar(double c, unsigned long pow)
{
    for(std::size_t i =0; i<length;i++)
    {
        if(vdata[i].pow == pow)
        {
            vdata[i].c+=c;
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
    vdata[length++] = Variable{c, pow};
}


void TetoPolynomial::addVar(Variable var)
{
    addVar(var.c,var.pow);
}

Variable &TetoPolynomial::getVar(unsigned long pow)
{
    Variable* result = nullptr;
    for (std::size_t i = 0;i < length;i++) {
        if (vdata[i].pow == pow) {
            result = &vdata[i];
            break;
        }
    }
    if (result == nullptr) {
        addVar(0, pow);
        result = &vdata[length - 1];
    }
    return *result;
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

double TetoPolynomial::calculate(double val)
{
    double result = 0;
    for (std::size_t i = 0;i < length;i++) {
        result += vdata[i].c * std::pow(val, vdata[i].pow);
    }
    return result;
}

void TetoPolynomial::printData()
{
    for(std::size_t i =0 ; i<length; i++)
    {
        std::cout <<"k = "<< vdata[i].c<<" | " << "pow = " << vdata[i].pow<< std::endl;
    }
}

Variable &TetoPolynomial::at(unsigned long pow)
{
    bool flag = false;
    for(size_t i = 0; i<length; i++)
    {
        if(vdata[i].pow == pow)
        {
            flag = true;
            break;
        }
    }
    if(flag)
    {
        return getVar(pow);
    }
    throw std::runtime_error("err with overloaded func at()");
}

Variable &TetoPolynomial::operator[](unsigned long index) noexcept
{
    return getVar(index);
}

TetoPolynomial &TetoPolynomial::operator=(const TetoPolynomial &rhs)
{
    // TODO: insert return statement here
}

TetoPolynomial &TetoPolynomial::operator=(TetoPolynomial &&rhs) noexcept
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator+=(const TetoPolynomial rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator+=(const Variable &rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator-=(const TetoPolynomial rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator-=(const Variable &rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator-() const -> TetoPolynomial
{
    return TetoPolynomial();
}

auto TetoPolynomial::operator*=(const TetoPolynomial rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator*=(const Variable &rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator/=(const TetoPolynomial rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator/=(const Variable &rhs) -> TetoPolynomial &
{
    // TODO: insert return statement here
}

auto TetoPolynomial::operator%=(const TetoPolynomial rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto TetoPolynomial::operator%=(const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

Variable Variable::operator-() const
{
    return Variable{-c,pow};
}

Variable &Variable::operator=(double _c)
{
    c = _c;
    return *this;
}

bool operator==(const Variable &lhs, const Variable &rhs)
{
    if(lhs.c != rhs.c) return false;
    if(lhs.pow != rhs.pow) return false;
    return true;
}

bool operator!=(const Variable &lhs, const Variable &rhs)
{
    return !operator==(lhs, rhs);
}

Variable operator/(const Variable &lhs, const Variable &rhs)
{
    return Variable();
}

auto operator+(TetoPolynomial lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator+(TetoPolynomial lhs, const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator+(Variable lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator-(TetoPolynomial lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator-(TetoPolynomial lhs, const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator-(Variable lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator*(TetoPolynomial lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator*(TetoPolynomial lhs, const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator*(Variable lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator/(TetoPolynomial lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator/(TetoPolynomial lhs, const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator/(Variable lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator%(TetoPolynomial lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator%(TetoPolynomial lhs, const Variable &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator%(Variable lhs, const TetoPolynomial &rhs) -> TetoPolynomial
{
    return TetoPolynomial();
}

auto operator==(const TetoPolynomial &lhs, const TetoPolynomial &rhs) -> bool
{
    return false;
}

auto operator==(const TetoPolynomial &lhs, const Variable &rhs) -> bool
{
    return false;
}

auto operator==(const Variable &lhs, const TetoPolynomial &rhs) -> bool
{
    return false;
}

auto operator!=(const TetoPolynomial &lhs, const TetoPolynomial &rhs) -> bool
{
    return false;
}

auto operator!=(const TetoPolynomial &lhs, const Variable &rhs) -> bool
{
    return false;
}

auto operator!=(const Variable &lhs, const TetoPolynomial &rhs) -> bool
{
    return false;
}
