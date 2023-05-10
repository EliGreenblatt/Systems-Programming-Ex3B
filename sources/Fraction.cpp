#include <iostream>
#include "Fraction.hpp"
#include <math.h>

using namespace std;
namespace ariel
{
    // CONSTRUCTORS
    // constructor taking two integers
    Fraction::Fraction(int numerator, int denominator)
    {
        if(denominator == 0)
        {
            throw std::invalid_argument("Denominator can't be zero");
        }
        if (numerator == 0)
        {
            denominator = 1;
        }
        this->numerator = numerator;
        this->denominator = denominator;

        reduction();

    }

    Fraction::Fraction(float number)
    {
        int temp = (int) number;
        int numerator2 = round((number - temp) * 1000);
        int denominator2 = 1000;
        if (numerator2 == 0)
        {
            numerator = (int)number;
            denominator = 1;
        }
        else
        {
            int greatestDivider = gcd(numerator2 , denominator2);
            numerator = ( temp * denominator2 + numerator2) / greatestDivider;
            denominator = denominator2 / greatestDivider;
        }

        reduction();
        
    }

    Fraction::Fraction()
    {
        numerator = 0;
        denominator = 1;
    }
    // Getters

    int Fraction::getNumerator() const
    {
        return numerator;
    }
    int Fraction::getDenominator() const
    {
        return denominator;
    }
    // THE FOLLOWING OPERATORS ARE THE SIMPLE MATH + , - , * , /

    // we add the first const to the signature because we don't want to change the fraction we receive
    // so no need to copy it , the second const means we don't want to change THIS instance of fraction
    Fraction Fraction::operator+(const Fraction& otherFraction) const
    {
        if(numerator > 0 && otherFraction.getNumerator() > numeric_limits<int>::max() - numerator
        || numerator < 0 && otherFraction.getNumerator() < numeric_limits<int>::min() - numerator)
        {
            throw overflow_error("Error ~ overflow\n");
        }

        int newDenominator = otherFraction.getDenominator() * denominator;
        int newNumerator = otherFraction.getDenominator() * numerator + otherFraction.getNumerator() * denominator;
        return Fraction(newNumerator , newDenominator);
    }

    // the reason for the const keyword is the same as previous functions
    Fraction Fraction::operator-(const Fraction& otherFraction) const
    {
        // here we cast the ints to 64 bits so we have more space to check if there originally was an 
        // overflow
        int64_t newDenominator = static_cast<int64_t>(denominator) * otherFraction.getDenominator();
        int64_t newNumerator = static_cast<int64_t>(otherFraction.getDenominator()) * numerator
        - static_cast<int64_t>(denominator) * otherFraction.getNumerator();

        
        if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min()
            || newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow detected in fraction subtraction.");
        }

        // here we cast them back to regular ints so we can build a Fraction object 
        // out of them
        return Fraction(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    }

    // the reason for the const keyword is the same as previous functions
   Fraction Fraction::operator*(const Fraction& otherFraction) const
    {
        int64_t newDenominator = static_cast<int64_t>(denominator) * otherFraction.getDenominator();
        int64_t newNumerator = static_cast<int64_t>(numerator) * otherFraction.getNumerator();

        if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min()
        || newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min()) 
        {
            throw std::overflow_error("Error ~ overflow\n");
        }
        return Fraction(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    }
    // the reason for the const keyword is the same as previous functions
    Fraction Fraction::operator/(const Fraction& otherFraction) const
    {
        if(otherFraction.getNumerator() == 0)
        {
            throw std::runtime_error("Can't divide by zero\n");
        }
        Fraction tempFrac = Fraction(otherFraction.getDenominator() , otherFraction.getNumerator());
        return *this * tempFrac;
    }


    // THE FOLLOWING OPERATORS ARE FOR DECIDING GREATER/LESS/EQUAL

    // the reason for the const keyword is the same as previous functions
    bool Fraction::operator==(const Fraction& otherFraction) const
    {
        const float epsilon = 1000.0;
        int opt1 = (int)(((float)numerator/(float)denominator) * epsilon);
        int opt2 = (int)(((float)otherFraction.getNumerator()/(float)otherFraction.getDenominator())*epsilon);
    
        return (opt1 == opt2);
    }

    // the reason for the const keyword is the same as previous functions
    bool Fraction::operator>(const Fraction& otherFraction) const
    {
        return numerator * otherFraction.denominator > otherFraction.numerator * denominator;
    }

    // the reason for the const keyword is the same as previous functions
    bool Fraction::operator<(const Fraction& otherFraction) const
    {
        return numerator * otherFraction.denominator < otherFraction.numerator * denominator;
    }

    // the reason for the const keyword is the same as previous functions
    bool Fraction::operator>=(const Fraction& otherFraction) const
    {
        return numerator * otherFraction.getDenominator() >= otherFraction.getNumerator() * denominator;
    }

    // the reason for the const keyword is the same as previous functions
    bool Fraction::operator<=(const Fraction& otherFraction) const
    {
        return numerator * otherFraction.denominator <= otherFraction.numerator * denominator;
    }

    // THE FOLLOWING ARE POST AND PRE INCREMENTING OPERATORS


    Fraction Fraction::operator++()
    {
        numerator = numerator + denominator;
        reduction();
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction temp = *this;
        operator++();
        return temp;
    }

    Fraction Fraction::operator--()
    {
        numerator = numerator - denominator;
        reduction();
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction temp = *this;
        operator--();
        return temp;
    }

    // these are the << and >> operators
    std::ostream& operator<<(std::ostream& ost, const Fraction& otherFraction)
    {
        ost << otherFraction.getNumerator() << "/" << otherFraction.getDenominator();
        return ost;
    }

    istream& operator>>(istream &ist, Fraction& otherFraction) 
    {

        int num, den;
        if (!(ist >> num >> den))
        {
            throw runtime_error("Invalid input\n");
        } 
        if( den == 0) 
        {
            throw runtime_error("demon cant be 0!");
        }
        
        otherFraction = Fraction(num, den);
        return ist;
    }


    // the following are friend operators , same as before just that they are defined outside the scope of the class

    Fraction operator+(const Fraction& otherFraction, float number) 
    {
        return otherFraction + Fraction(number);
    }

    Fraction operator-(const Fraction& otherFraction, float number) 
    {
        return otherFraction - Fraction(number);
    }

    Fraction operator*(const Fraction& otherFraction, float number) 
    {
        return otherFraction * Fraction(number);
    }

    Fraction operator/(const Fraction& otherFraction, float number) 
    {
        if(number == 0)
        {
            throw std::runtime_error("Error can't divide by zero\n");
        }
        return otherFraction / Fraction(number);
    }

    Fraction operator+(float number, const Fraction& otherFraction) 
    {
       return operator+(otherFraction , number);
    }

    Fraction operator-(float number, const Fraction& otherFraction) 
    {
        return -1 * ( operator-(otherFraction , number));
    }

    Fraction operator*(float number, const Fraction& otherFraction) 
    {
        return operator*(otherFraction , number);
    }

    Fraction operator/(float number, const Fraction& otherFraction) 
    {
        if (number == 0)
        {
            return Fraction(0,1);
        }
        Fraction temp = operator/(otherFraction , number);
        return Fraction(temp.getDenominator() , temp.getNumerator());
    }

    bool operator==(const Fraction& otherFraction, float otherFraction2) 
    {
        return otherFraction == Fraction(otherFraction2);
    }

    bool operator>(const Fraction& otherFraction, float otherFraction2) 
    {
       return otherFraction > Fraction(otherFraction2);
    }

    bool operator<(const Fraction& otherFraction, float otherFraction2) 
    {
        return otherFraction < Fraction(otherFraction2);
    }

    bool operator>=(const Fraction& otherFraction, float otherFraction2) 
    {
        return otherFraction >= Fraction(otherFraction2);
    }

    bool operator<=(const Fraction& otherFraction, float otherFraction2) 
    {
        return otherFraction <= Fraction(otherFraction2);
    }

    bool operator==(float otherFraction2, const Fraction& otherFraction) 
    {
        return otherFraction == Fraction(otherFraction2);
    }

    bool operator>(float otherFraction2, const Fraction& otherFraction) 
    {
        return otherFraction < Fraction(otherFraction2);
    }

    bool operator<(float otherFraction2, const Fraction& otherFraction) 
    {
        return otherFraction > Fraction(otherFraction2);
    }

    bool operator>=(float otherFraction2, const Fraction& otherFraction) 
    {
        return Fraction(otherFraction2) >= otherFraction;
    }

    bool operator<=(float otherFraction2, const Fraction& otherFraction) 
    {
        return Fraction(otherFraction2) <= otherFraction;
    }
    
    // we search for the gcd so we can reduce the fraction to its correct form
    int Fraction::gcd(int first , int second)
    {
        if( second == 0 )
        {
            return first;
        }
        else
        {
           return gcd(second , first % second);
        }
    }
    
    // this function will reduce the fraction to its correct form
    void Fraction::reduction()
    {
        if(denominator == 0)
        {
            throw invalid_argument("Denominator is zero\n");
        }
        if(numerator == 0)
        {
            denominator = 1;
        }
        else
        {
            int greatestDivider = gcd((numerator) ,(denominator));
            numerator = numerator / greatestDivider;
            denominator = denominator / greatestDivider;
        }
        if(denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    ;
}

