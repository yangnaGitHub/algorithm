#pragma once
#include <iostream>
using namespace std;

class Complex{
public:
    double Re, Im;

    Complex(double Re = 0, double Im = 0);
    ~Complex();
    //+ operator
    /*friend Complex operator +(Complex ParamA, Complex ParamB);
    friend Complex operator +(double ParamA, Complex &ParamB);
    friend Complex operator +(Complex &ParamA, double ParamB);*/
    //- operator
    /*friend Complex operator -(Complex &ParamA, Complex &ParamB);
    friend Complex operator -(double ParamA, Complex &ParamB);
    friend Complex operator -(Complex &ParamA, double ParamB);*/
    //* operator
    friend Complex operator *(Complex &ParamA, Complex &ParamB);
    friend Complex operator *(double ParamA, Complex &ParamB);
    friend Complex operator *(Complex &ParamA, double ParamB);
    //= operator
    /*Complex operator =(Complex &Param);
    Complex operator =(double Param);*/
    //<< operator
    friend ostream & operator <<(ostream &out, Complex &Param);
};
