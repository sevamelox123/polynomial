#include "polynomial.hpp"
#include <math.h>

void TetoPolynomial::addVar(double c, unsigned long pow)
{
    for (std::size_t i = 0; i < length; i++)
    {
        if (vdata[i].pow == pow)
        {
            vdata[i].c += c;
            return;
        }
    }
    if (vdata == nullptr)
    {
        vdata = new Variable[1];
        length = 0;
    }
    else
    {
        if ((vdata = (Variable *)std::realloc(vdata, sizeof(Variable) * (length + 1))) == nullptr)
        {
            throw std::bad_alloc();
        }
    }
    vdata[length++] = Variable{c, pow};
}

void TetoPolynomial::addVar(Variable var)
{
    addVar(var.c, var.pow);
}

Variable &TetoPolynomial::getVar(unsigned long pow)
{
    Variable *result = nullptr;
    for (std::size_t i = 0; i < length; i++)
    {
        if (vdata[i].pow == pow)
        {
            result = &vdata[i];
            break;
        }
    }
    if (result == nullptr)
    {
        addVar(0, pow);
        result = &vdata[length - 1];
    }
    return *result;
}

void TetoPolynomial::reset()
{
    if (vdata != nullptr)
    {
        delete[] vdata;
        vdata = nullptr;
    }
    length = 0;
}

TetoPolynomial::TetoPolynomial(Variable var)
{
    addVar(var);
}

TetoPolynomial::TetoPolynomial(const TetoPolynomial &obj) : length(obj.length)
{
    vdata = new Variable[obj.length];
    std::copy(obj.vdata, obj.vdata + obj.length, vdata);
}

TetoPolynomial::TetoPolynomial(TetoPolynomial &&obj) noexcept : length(obj.length)
{
    vdata = obj.vdata;
    obj.vdata = nullptr;
}

TetoPolynomial::TetoPolynomial(float *pol, std::size_t size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        addVar(pol[i], size - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(double *pol, std::size_t size)
{
    for (std::size_t i = 0; i < size; i++)
    {
        addVar(pol[i], size - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<float> pol)
{
    for (std::size_t i = 0; i < pol.size(); i++)
    {
        addVar(pol.begin()[i], pol.size() - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<double> pol)
{
    for (std::size_t i = 0; i < pol.size(); i++)
    {
        addVar(pol.begin()[i], pol.size() - i - 1);
    }
}

TetoPolynomial::TetoPolynomial(std::initializer_list<Variable> pol)
{
    for (std::size_t i = 0; i < pol.size(); i++)
    {
        addVar(pol.begin()[i]);
    }
}

TetoPolynomial::~TetoPolynomial()
{
    if (vdata != nullptr)
    {
        delete[] vdata;
    }
}

double TetoPolynomial::calculate(double val)
{
    double result = 0;
    for (std::size_t i = 0; i < length; i++)
    {
        result += vdata[i].c * std::pow(val, vdata[i].pow);
    }
    return result;
}

void TetoPolynomial::printData()
{
    for (std::size_t i = 0; i < length; i++)
    {
        std::cout << "k = " << vdata[i].c << " | " << "pow = " << vdata[i].pow << std::endl;
    }
}

Variable &TetoPolynomial::at(unsigned long pow)
{
    bool flag = false;
    for (size_t i = 0; i < length; i++)
    {
        if (vdata[i].pow == pow)
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        return getVar(pow);
    }
    throw std::runtime_error("err with overloaded func at()");
}

Variable &TetoPolynomial::operator[](unsigned long index) noexcept
{
    return getVar(index);
}

long unsigned TetoPolynomial::getMaxPow() const
{
    unsigned long max_power = 0;
    for (std::size_t i = 0; i < length; i++)
    {
        if (vdata[i].pow > max_power && vdata[i].c != 0)
        {
            max_power = vdata[i].pow;
        }
    }
    return max_power;
}

TetoPolynomial &TetoPolynomial::operator=(const TetoPolynomial &rhs)
{
    if (vdata != nullptr)
        delete[] vdata;
    vdata = new Variable[rhs.length];
    std::copy(rhs.vdata, rhs.vdata + rhs.length, vdata);
    return *this;
}

TetoPolynomial &TetoPolynomial::operator=(TetoPolynomial &&rhs) noexcept
{
    if (vdata != nullptr)
        delete[] vdata;
    vdata = rhs.vdata;
    rhs.vdata = nullptr;
    length = rhs.length;

    return *this;
}

TetoPolynomial &TetoPolynomial::operator+=(const TetoPolynomial rhs)
{
    for (std::size_t i = 0; i < rhs.length; i++)
    {
        addVar(rhs.vdata[i]);
    }

    return *this;
}

TetoPolynomial &TetoPolynomial::operator+=(const Variable &rhs)
{
    addVar(rhs);
    return *this;
}

TetoPolynomial &TetoPolynomial::operator-=(const TetoPolynomial rhs)
{
    for (std::size_t i = 0; i < rhs.length; i++)
    {
        addVar(-rhs.vdata[i]);
    }

    return *this;
}

TetoPolynomial &TetoPolynomial::operator-=(const Variable &rhs)
{
    addVar(-rhs);
    return *this;
}

TetoPolynomial &TetoPolynomial::operator-() const
{
    TetoPolynomial ret(*this);
    for (std::size_t i = 0; i < ret.length; i++)
    {
        ret.vdata[i] = -ret.vdata[i];
    }
    return ret;
}

TetoPolynomial &TetoPolynomial::operator*=(const TetoPolynomial rhs)
{
    Variable *var_data_copy = new Variable[length];
    std::size_t length_copy = length;
    std::copy(vdata, vdata + length, var_data_copy);
    reset();
    for (std::size_t i = 0; i < length_copy; i++)
    {
        for (std::size_t j = 0; j < rhs.length; j++)
        {
            addVar(Variable{var_data_copy[i].c * rhs.vdata[j].c, var_data_copy[i].pow + rhs.vdata[j].pow});
        }
    }
    delete[] var_data_copy;
    return *this;
}

TetoPolynomial &TetoPolynomial::operator*=(const Variable &rhs)
{
    for (std::size_t i = 0; i < length; i++)
    {
        vdata[i] = Variable{vdata[i].c * rhs.c, vdata[i].pow + rhs.pow};
    }
    return *this;
}

TetoPolynomial &TetoPolynomial::operator/=(const TetoPolynomial rhs)
{
    if (length < 1 || rhs.length < 1)
        throw std::runtime_error("Empty polynomial passed!");
    if (getMaxPow() < rhs.getMaxPow())
    {
        reset();
        addVar(0, 0);
        return *this;
    }
    TetoPolynomial copy(*this);
    TetoPolynomial rhsCopy(rhs);
    reset();
    while (copy.getMaxPow() > 0 && copy.getMaxPow() >= rhsCopy.getMaxPow())
    {
        Variable var = copy[copy.getMaxPow()] / rhsCopy[rhsCopy.getMaxPow()];
        copy -= (rhsCopy * var);
        addVar(var);
    }
    return *this;
}

TetoPolynomial &TetoPolynomial::operator/=(const Variable &rhs)
{
    if (rhs.c == 0)
        throw std::overflow_error("Zero division error!");
    if (getMaxPow() < rhs.pow)
    {
        reset();
        addVar(0, 0);
        return *this;
    }
    Variable *var_data_copy = new Variable[length];
    std::size_t length_copy = length;
    std::copy(vdata, vdata + length, var_data_copy);
    reset();
    for (std::size_t i = 0; i < length_copy; i++)
    {
        if (var_data_copy[i].pow >= rhs.pow)
        {
            addVar(Variable{var_data_copy[i].c / rhs.c, var_data_copy[i].pow - rhs.pow});
        }
    }
    delete[] var_data_copy;
    return *this;
}
TetoPolynomial &TetoPolynomial::operator%=(const TetoPolynomial rhs)
{
    if (length < 1 || rhs.length < 1)
        throw std::runtime_error("Empty polynomial passed!");
    if (getMaxPow() < rhs.getMaxPow())
    {
        return *this;
    }
    TetoPolynomial copy(*this);
    TetoPolynomial rhsCopy(rhs);
    reset();
    while (copy.getMaxPow() > 0 && copy.getMaxPow() >= rhsCopy.getMaxPow())
    {
        Variable var = copy[copy.getMaxPow()] / rhsCopy[rhsCopy.getMaxPow()];
        copy -= (rhsCopy * var);
    }
    *this += copy;
    return *this;
}

TetoPolynomial &TetoPolynomial::operator%=(const Variable &rhs)
{
    if (rhs.c == 0)
        throw std::overflow_error("Zero division error!");
    if (getMaxPow() < rhs.pow)
    {
        return *this;
    }
    Variable *var_data_copy = new Variable[length];
    std::size_t length_copy = length;
    std::copy(vdata, vdata + length, var_data_copy);
    reset();
    for (std::size_t i = 0; i < length_copy; i++)
    {
        if (var_data_copy[i].pow < rhs.pow)
        {
            addVar(var_data_copy[i]);
        }
    }
    delete[] var_data_copy;
    return *this;
}


TetoPolynomial::operator std::string()
{
    if(length < 1) return "0";
    std::stringstream ss;
    bool first_element = true;
    for (std::size_t i = 0;i < length;i++) {
        if (vdata[i].c >= 0 && !first_element) {
            ss << "+";
        } else if (vdata[i].c < 0) {
            ss << "-";
        }
        first_element = false;
        ss << "(" << std::abs(vdata[i].c) << "x" << "^" << vdata[i].pow << ")";
    }
    return ss.str();
}

Variable Variable::operator-() const
{
    return Variable{-c, pow};
}

Variable &Variable::operator=(double _c)
{
    c = _c;
    return *this;
}

bool operator==(const Variable &lhs, const Variable &rhs)
{
    if (lhs.c != rhs.c)
        return false;
    if (lhs.pow != rhs.pow)
        return false;
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

TetoPolynomial operator+(TetoPolynomial lhs, const TetoPolynomial &rhs)
{
    lhs += rhs;
    return lhs;
}

TetoPolynomial operator-(TetoPolynomial lhs, const TetoPolynomial &rhs)
{
    lhs -= rhs;
    return lhs;
}

TetoPolynomial operator*(TetoPolynomial lhs, const TetoPolynomial &rhs)
{
    lhs *= rhs;
    return lhs;
}

TetoPolynomial operator/(TetoPolynomial lhs, const TetoPolynomial &rhs)
{
    lhs /= rhs;
    return lhs;
}

TetoPolynomial operator%(TetoPolynomial lhs, const TetoPolynomial &rhs)
{
    lhs %= rhs;
    return lhs;
}

bool operator==(const TetoPolynomial &lhs, const TetoPolynomial &rhs)
{
    if (lhs.length != rhs.length)
        return false;
    bool *flags = new bool[lhs.length];
    for (std::size_t i = 0; i < lhs.length; i++)
    {
        flags[i] = false;
        for (std::size_t j = 0; j < rhs.length; j++)
        {
            if (lhs.vdata[i] == rhs.vdata[j])
            {
                flags[i] = true;
                break;
            }
        }
    }
    for (std::size_t i = 0; i < lhs.length; i++)
    {
        if (flags[i] == false)
            return false;
    }
    return true;
}

bool operator!=(const TetoPolynomial &lhs, const TetoPolynomial &rhs)
{
    return !operator==(lhs, rhs);
}

auto operator<<(std::ostream &out, const TetoPolynomial &pol) -> std::ostream &
{
    TetoPolynomial copy(pol);
    out << std::string(copy);
    return out;
}
