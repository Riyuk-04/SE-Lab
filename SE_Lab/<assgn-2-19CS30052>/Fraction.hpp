#ifndef FRACTION_h
#define FRACTION_h
#include<iostream>
using namespace std;

class Fraction{
private:
    //****Data Members****
    //Int to represent numerator(Can be both +ve and -ve)
    int numerator;
    //Unsigned Int to represent denominator(Can be only +ve)
    unsigned int denominator;
    public:
    //Function to reduce fraction to normalised form by dividing numerator and denominator by their GCD
    void norm(){
        int x = gcd(abs(numerator), denominator);
        numerator /= x;
        denominator /= x;
    }

public:
    //****Static constants****
    //Constant to represent 1 as 1/1
    static const Fraction sc_fUnity;
    //Constant to represent 0 as 0/1
    static const Fraction sc_fZero;

    //****Constructors****
    //Take inputs of type int defaulted to 1
    Fraction(int, int);
    Fraction();
    //Take input of type double
    Fraction(double d);
    //Copy Constructor takes input a referance of type Fraction
    Fraction(const Fraction& f);

    //****Destructor****
    ~Fraction();

    //****Utility Functions****
    //Function to compute GCD using "recursion" thus "not inlined"
    static int gcd(int x, int y);
    //Function to compute LCM using property lcm(x,y)*gcd(x,y) = x*y (inline)
    static inline int lcm(int x, int y){
        return x*y/gcd(x,y);
    }
    //Function to return the precision value (inline)
    static inline int precision(){
        return 10000;
    }

    //****Unary Operators****
    //Copy Assignment Operator takes referance of type Fraction
    Fraction& operator =(const Fraction& f);
    //Unary minus operator to get (-1)*fraction
    Fraction operator-();
    //Unary plus operator to get (+1)*fraction
    Fraction& operator+();
    //Prefix pre-decrement operator for dividendo returns
    Fraction& operator--();
    //Prefix pre-increment operator for componendo returns
    Fraction& operator++();
    //Postfix post-decrement operator for lazy dividendo returns
    Fraction operator--(int);
    //Postfix post-increment operator for lazy componendo returns
    Fraction operator++(int);

    //****Binary Arithmetic Operators****
    //Addition: Adding the First operand to the Second operand
    friend Fraction operator+(const Fraction&, const Fraction&);
    //Subtraction: Subtracting the Second operand from the First operand
    friend Fraction operator-(const Fraction&, const Fraction&);
    //Multiplication: Multiplying the First operand with the Second operand
    friend Fraction operator*(const Fraction&, const Fraction&);
    //Division: Dividing the First operand by the Second operand and throws an exception if the
    //divider (Second operand) is zero
    friend Fraction operator/(const Fraction&, const Fraction&);
    //Remainder: Remainder of division of the First operand by the Second operand and throws
    //an exception if the divider (Second operand) is zero
    friend Fraction operator%(const Fraction&, const Fraction&);

    //****Binary Relational Operators****
    //Operands are Equal
    friend bool operator==(const Fraction&, const Fraction&);
    //Operands are Not Equal
    friend bool operator!=(const Fraction&, const Fraction&);
    //First operand is Less than Second operand
    friend bool operator<(const Fraction&, const Fraction&);
    //First operand is Less than or Equal to Second operand
    friend bool operator<=(const Fraction&, const Fraction&);
    //First operand is More than Second operand
    friend bool operator>(const Fraction&, const Fraction&);
    //First operand is More than or Equal to Second operand
    friend bool operator>=(const Fraction&, const Fraction&);

    //****Special Operators****
    //The negation(!) operator to invert a fraction i.e p/q -> q/p and throws exception if fraction is 0
    Fraction operator!();

    //****I/O Operators****
    //Output: Streaming to ostream pq to be output as p / q
    friend ostream& operator<<(ostream&, const Fraction&);
    //Input: Streaming from istream a pair of int p and q, form p/q and normalize
    friend istream& operator>>(istream& ,Fraction&);

    //****Extra inline function****
    //Function to convert fraction to double(used for comparison)
    inline double convert() const{
        return ((double)numerator)/denominator;
    }
};
#endif