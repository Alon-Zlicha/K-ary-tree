//Alonz1414@gmail.com
#include "complex.hpp"

Complex::Complex(double r, double i) : real(r), img(i)
{
}

Complex::Complex(double r) : real(r), img(0)
{
}

Complex::Complex() : real(0), img(0)
{
}

Complex::~Complex()
{
}

Complex::Complex(const Complex &c)
{
    this->real = c.real;
    this->img = c.img;
}

Complex &Complex::operator=(const Complex &c)
{
    this->real = c.real;
    this->img = c.img;
    return *this;
}

double Complex::getReal() const
{
    return this->real;
}

double Complex::getImg() const
{
    return this->img;
}

void Complex::setReal(double r)
{
    this->real = r;
}

void Complex::setImg(double i)
{
    this->img = i;
}

bool Complex::operator<(const Complex &c) const
{
    return (this->real < c.real) || (this->real == c.real && this->img < c.img);
}

bool Complex::operator==(const Complex &c) const
{
    return !(*this < c || c < *this);
}

bool Complex::operator>=(const Complex &c) const
{
    return !(*this < c);
}

bool Complex::operator!=(const Complex &c) const
{
    return !(*this == c);
}

bool Complex::operator<=(const Complex &c) const
{
    return !(c < *this);
}

bool Complex::operator>(const Complex &c) const
{
    return c < *this;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    if (c.real == 0 && c.img == 0)
    {
        os << c.real;
    }
    else if (c.real == 0)
    {
        if (c.img == 1)
            os << "i";
        else if (c.img == -1)
            os << "-i";
        else
            os << c.img << "i";
    }
    else
    {
        os << c.real;
        if (c.img > 0)
        {
            if (c.img == 1)
                os << "+i";
            else
                os << "+" << c.img << "i";
        }
        else if (c.img < 0)
        {
            if (c.img == -1)
                os << "-i";
            else
                os << "-" << -c.img << "i";
        }
    }
    return os;
}
