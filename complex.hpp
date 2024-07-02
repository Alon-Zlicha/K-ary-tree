//Alonz1414@gmail.com
#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <math.h>

class Complex
{
private:
    double real;
    double img;
public:    
    Complex(double r, double i);
    Complex(double r);
    Complex();
    ~Complex();
    Complex(const Complex &c);
    Complex &operator=(const Complex &c);
    double getReal() const;
    double getImg() const;
    void setReal(double r);
    void setImg(double i);
    bool operator<(const Complex &c) const;
    bool operator==(const Complex &c) const;
    bool operator>=(const Complex &c) const;
    bool operator!=(const Complex &c) const;
    bool operator<=(const Complex &c) const;
    bool operator>(const Complex &c) const;
    friend std::ostream &operator<<(std::ostream &os, const Complex &c);
};
#endif
