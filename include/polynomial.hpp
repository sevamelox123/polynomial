#pragma once
#include <iostream>
#include <sstream>
struct Variable
{
    double c;
    unsigned long pow;
    Variable(){c=0; pow =0; }
    Variable(double x){c=x; pow  =0; }
    Variable(double c, unsigned long pow){this->c=c; this->pow  =pow; }
    Variable operator-() const;
    Variable &operator=(double _c);
    friend bool operator==(const Variable &lhs, const Variable &rhs);
    friend bool operator!=(const Variable &lhs, const Variable &rhs);
    friend Variable operator/(const Variable &lhs, const Variable &rhs);

    
};

bool operator==(const Variable &lhs, const Variable &rhs);
bool operator!=(const Variable &lhs, const Variable &rhs);
Variable operator/(const Variable &lhs, const Variable &rhs);


class TetoPolynomial
{
private:
    Variable *vdata = nullptr;
    std::size_t length = 0;
    void addVar(double c, unsigned long pow);
    void addVar(Variable var);
    Variable &getVar(unsigned long pow);




    void reset();

public:
    /**
     * @brief Default constructor.
     */
    TetoPolynomial() = default;
    /**
     * @brief Constructor that accepts Variable and add it into the poly.
     */
    TetoPolynomial(Variable var);
    TetoPolynomial(double var){addVar(var);}
    TetoPolynomial(const TetoPolynomial &obj);
    TetoPolynomial(TetoPolynomial &&obj) noexcept;
    TetoPolynomial(float *pol, std::size_t size);
    TetoPolynomial(double *pol, std::size_t size);
    //TetoPolynomial(std::initializer_list<float> pol);
    TetoPolynomial(std::initializer_list<double> pol);
    TetoPolynomial(std::initializer_list<Variable> pol);
    ~TetoPolynomial();
    /**
     * @brief Debug func that print poly in the format c = ... | pow = ... where c is coefficient and pow is power
     */
    void printData();
    /**
     * @brief Func that calculate poly using value in the format c*(value)^power + c*(value)^power-1 + ...
     * @param val is value that accepts in poly to calculate
     * @return the result of calculations
     */
    [[nodiscard]] double calculate(double val);
    /**
     * @brief Overloaded at()
     * @param pow power of variable
     * @return c or pow if
     * @throw std::runtime_error if something incorrect with data
     */
    [[nodiscard]] Variable &at(unsigned long pow);
    /**
     * @brief Overloaded []
     * @param pow power of variable
     * @return c or pow if needed
     */
    [[nodiscard]] Variable &operator[](unsigned long index) noexcept;//2


    [[nodiscard]] long unsigned getMaxPow() const;


    TetoPolynomial& operator=(const TetoPolynomial& rhs);
    TetoPolynomial& operator=(TetoPolynomial&& rhs) noexcept;
    TetoPolynomial& operator+=(const TetoPolynomial rhs);
    TetoPolynomial& operator+=(const Variable& rhs);
    friend TetoPolynomial operator+(TetoPolynomial lhs, const TetoPolynomial& rhs);
    TetoPolynomial& operator-=(const TetoPolynomial rhs);
    TetoPolynomial& operator-=(const Variable& rhs);
    friend TetoPolynomial operator-(TetoPolynomial lhs, const TetoPolynomial& rhs);
    TetoPolynomial& operator-() const;
    TetoPolynomial& operator*=(const TetoPolynomial rhs);
    TetoPolynomial& operator*=(const Variable& rhs);
    friend TetoPolynomial operator*(TetoPolynomial lhs, const TetoPolynomial& rhs);
    TetoPolynomial& operator/=(const TetoPolynomial rhs);
    TetoPolynomial& operator/=(const Variable& rhs);
    friend TetoPolynomial operator/(TetoPolynomial lhs, const TetoPolynomial& rhs);
    TetoPolynomial& operator%=(const TetoPolynomial rhs);
    TetoPolynomial& operator%=(const Variable& rhs);
    friend TetoPolynomial operator%(TetoPolynomial lhs, const TetoPolynomial& rhs);

    friend bool operator==(const TetoPolynomial& lhs, const TetoPolynomial& rhs);
    friend bool operator!=(const TetoPolynomial& lhs, const TetoPolynomial& rhs);

    //friend TetoPolynomial operator+(TetoPolynomial lhs, int rhs);
    //friend TetoPolynomial operator+(int lhs, const TetoPolynomial& rhs);
    operator std::string ();
    friend auto operator<<(std::ostream& out, const TetoPolynomial& pol) -> std::ostream&;
};