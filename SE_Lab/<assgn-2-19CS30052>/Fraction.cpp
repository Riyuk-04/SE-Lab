#include <iostream>
#include <cstdlib>
#include "Fraction.hpp"
#include <cmath>
using namespace std;

//****Constructors****
//Constructor that takes int as input with default parameters
Fraction::Fraction(int n = 1, int d = 1): numerator(abs(n)),denominator(abs(d)){
    if(d==0) exit(1);
    if(n*d < 0)	numerator *= -1;;
    if(n==0) denominator = 1;
    norm();
}
//Default parameter
Fraction::Fraction(){
    numerator = 1;
    denominator = 1;
}

Fraction::Fraction(double x){
    numerator = floor(x*precision());
    denominator = precision();
    norm();
}

//****Copy Constructor****
Fraction::Fraction(const Fraction& f): numerator(f.numerator), denominator(f.denominator) {}

//****Destructor****
Fraction::~Fraction(){}

//****Static constants****
const Fraction Fraction::sc_fUnity = Fraction(1);
const Fraction Fraction::sc_fZero = Fraction(0);

//****Utility Functions****
//GCD Function computed recursively
int Fraction::gcd(int x, int y){
    if(y==0) return x;
    else return gcd(y,x%y);
}

//****Unary Operators****
//Copy Assignment Operator
Fraction& Fraction::operator =(const Fraction& f){
    this->numerator = f.numerator;
    this->denominator = f.denominator;
    return *this;
}
//Unary minus operator
Fraction Fraction::operator-(){
    return Fraction((this->numerator)*(-1), this->denominator);
}
//Unary plus operator
Fraction& Fraction::operator+(){
    return *this;
}    
//Prefix pre-decrement operator
Fraction& Fraction::operator--(){
    this->numerator -= this->denominator;
    return *this;
}
//Prefix pre-increment operator
Fraction& Fraction::operator++(){
    this->numerator += this->denominator;
    return *this;
}
//Postfix post-decrement operator
Fraction Fraction::operator--(int){
	Fraction x = *this;
	this->numerator -= this->denominator;
    return x;
}
//Postfix post-increment operator
Fraction Fraction::operator++(int){
    Fraction x = *this;
	this->numerator += this->denominator;
    return x;
}

//****Binary Arithmetic Operators****
//Addition: Adding the First operand to the Second operand
Fraction operator+(const Fraction& f1, const Fraction& f2){
    return Fraction(f1.numerator*f2.denominator + f1.denominator*f2.numerator, f1.denominator*f2.denominator);
}
//Subtraction: Subtracting the Second operand from the First operand
Fraction operator-(const Fraction& f1, const Fraction& f2){
    return Fraction(f1.numerator*f2.denominator - f1.denominator*f2.numerator, f1.denominator*f2.denominator);
}
//Multiplication: Multiplying the First operand with the Second operand
Fraction operator*(const Fraction& f1, const Fraction& f2){
    return Fraction(f1.numerator*f2.numerator, f1.denominator*f2.denominator);
}
//Division: Dividing the First operand by the Second operand and throws an exception if the divider (Second operand) is zero
Fraction operator/(const Fraction& f1, const Fraction& f2){
    if(f2.numerator*f1.denominator == 0){
    	cout<<"ERROR: Division by zero"<<endl;
    	return 0;
    }
    return Fraction(f1.numerator*f2.denominator, f1.denominator*f2.numerator);
}
//Remainder: Remainder of division of the First operand by the Second operand and throws an exception if the divider (Second operand) is zero
Fraction operator%(const Fraction& f1, const Fraction& f2){
    if(f2.numerator == 0){
    	cout<<"ERROR: Division by zero"<<endl;
    	return 0;
    }
    return Fraction(remainder(f1.convert(), f2.convert()));
}

//****Binary Relational Operators****
//Operands are Equal
bool operator==(const Fraction& f1, const Fraction& f2){
    if(abs((f1-f2).convert())<1e-6) return true;
    else return false;
}
//Operands are Not Equal
bool operator!=(const Fraction& f1, const Fraction& f2){
    if(abs((f1-f2).convert())<1e-6) return false;
    else return true;
}
//First operand is Less than Second operand
bool operator<(const Fraction& f1, const Fraction& f2){
    if((f1 - f2).convert() < 0) return true;
    else return false;
}
//First operand is Less than or Equal to Second operan
bool operator<=(const Fraction& f1, const Fraction& f2){
    if((f1 - f2).convert() <= 0) return true;
    else return false;
}
//First operand is More than Second operand
bool operator>(const Fraction& f1, const Fraction& f2){
    if((f1 - f2).convert() > 0) return true;
    else return false;
}
//First operand is More than or Equal to Second operand
bool operator>=(const Fraction& f1, const Fraction& f2){
    if((f1 - f2).convert() >= 0) return true;
    else return false;
}
//****Special Operators****
//The negation(!) operator to invert a fraction i.e p/q -> q/p and throws exception if fraction is 0
Fraction Fraction::operator!(){
    if(this->numerator == 0){
    	cout<<"ERROR: Division by zero"<<endl;
    	return 0;
    }
    return Fraction(this->denominator, this->numerator);
}
//****I/O Operators****
//Output: Streaming to ostream pq to be output as p / q
ostream& operator<<(ostream& stream,const Fraction& f){
    if(f.denominator == 1)	stream<<f.numerator;
    else	stream<<f.numerator<<"/"<<f.denominator;
    return stream;
}
//Input: Streaming from istream a pair of int p and q, form p/q and normalize
istream& operator>>(istream& stream,Fraction& f){
    int x, y;
    stream>>x>>y;
    Fraction temp = Fraction(x, y);
    f = temp;
    return stream;
}