#pragma once
#include "Complex.hpp"
class Fouier{
    Complex *Data;
    void FFT(int start, int step, int len);
    void Trans(int index, int Count, Complex& Ret);
public:
    Fouier(void);
    ~Fouier(void);
    void FFT();
};
