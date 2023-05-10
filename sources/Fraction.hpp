#ifndef FRACTION_
#define FRACTION_

#include <iostream>


namespace ariel
{
    class Fraction
    {
        int numerator;
        int denominator;
        public:
            // constructors
            Fraction(int numerator, int denominator);
            Fraction(float number);
            Fraction();


            // Getters
            int getNumerator() const;
            int getDenominator() const;

            // regular operators
            Fraction operator+(const Fraction& otherFraction) const;
            Fraction operator-(const Fraction& otherFraction) const;
            Fraction operator*(const Fraction& otherFraction) const;
            Fraction operator/(const Fraction& otherFraction) const;

            // these are the == , > , < , >= , <= operators
            bool operator==(const Fraction& otherFraction) const;
            bool operator>(const Fraction& otherFraction) const;
            bool operator<(const Fraction& otherFraction) const;
            bool operator>=(const Fraction& otherFraction) const;
            bool operator<=(const Fraction& otherFraction) const;

            // these are incrementing operators , post and pre
            Fraction operator++();
            Fraction operator++(int);
            Fraction operator--();
            Fraction operator--(int);

            // these are << and >> operators and other friend functions for previously defined functions
            friend std::ostream& operator<<(std::ostream& ost , const Fraction& otherFraction);
            friend std::istream& operator>>(std::istream& ist , Fraction& otherFraction);

            friend Fraction operator+(const Fraction& otherFraction , float number);
            friend Fraction operator-(const Fraction& otherFraction , float number);
            friend Fraction operator*(const Fraction& otherFraction , float number);
            friend Fraction operator/(const Fraction& otherFraction , float number);

            friend Fraction operator+(float number , const Fraction& otherFraction );
            friend Fraction operator-(float number , const Fraction& otherFraction);
            friend Fraction operator*(float number , const Fraction& otherFraction);
            friend Fraction operator/(float number , const Fraction& otherFraction);

            friend bool operator==(const Fraction& otherFraction , float otherFraction2);
            friend bool operator>(const Fraction& otherFraction , float otherFraction2) ;
            friend bool operator<(const Fraction& otherFraction , float otherFraction2);
            friend bool operator>=(const Fraction& otherFraction , float otherFraction2);
            friend bool operator<=(const Fraction& otherFraction , float otherFraction2);

            friend bool operator==(float otherFraction2 , const Fraction& otherFraction);
            friend bool operator>(float otherFraction2 , const Fraction& otherFraction) ;
            friend bool operator<(float otherFraction2 , const Fraction& otherFraction);
            friend bool operator>=(float otherFraction2, const Fraction& otherFraction);
            friend bool operator<=(float otherFraction2 , const Fraction& otherFraction);

            // General
            void reduction();
            int gcd(int first , int second);
        private:
    };
}


#endif 