#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Fouier.hpp"

#define DATALEN 32
#define MAXVALUE 10000
#define PI 3.14159265358979323846

using namespace std;

Fouier::Fouier(void){
    Data = new Complex[DATALEN];
    int index = 0;
    //srand(unsigned int(time(0)));
    cout << "Source Data:" << endl;
    while(index < DATALEN){
        Data[index] = (rand() % MAXVALUE)/(double)(rand() % MAXVALUE + 1);
        cout << Data[index++] << " ";
        /*if(!(index % 5))
            cout << endl;*/
    }
    cout << endl;
}

Fouier::~Fouier(void){
    delete[] Data;
}

void Fouier::Trans(int index, int Count, Complex& Ret){
    double alpha = -2 * PI * index / Count;
    Complex RetTemp = Complex(cos(alpha), sin(alpha));
    Ret = RetTemp;
}

void Fouier::FFT(int start, int step, int len){
    if(1 == len)
        return;
    cout << "start to step * 2 start" << " " << start << " " << step * 2 << " " << len/2 << endl;
    FFT(start, step * 2, len / 2);
    cout << "start + step to step * 2 start" << " " << start + step << " " << step * 2 << " " << len/2 << endl;
    FFT(start + step, step * 2, len / 2);
    Complex Xa, Xb, Xc, Xtemp;
    cout << "Loop Start" << " " << start << " " << len << endl;
    for(int index = 0; index < (len / 2); index++){
        Xa = Data[start + step * index * 2];
        Xb = Data[start + step * (index * 2 + 1)];
        Trans(index, len, Xc);
        (Data[start + step * index]).Re = Xa.Re + Xc.Re;
        (Data[start + step * index]).Im = Xa.Im + Xc.Im;
        (Data[start + step * (index + len / 2)]).Re = Xa.Re - (Xc * Xb).Re;
        (Data[start + step * (index + len / 2)]).Im = Xa.Im - (Xc * Xb).Im;
        cout << start + step * index * 2 << " " << Xa << start + step * (index * 2 + 1) << " " << Xb << "\t";
        cout << index << " " << Xc << endl;
        cout << start + step * index << " " << Data[start + step * index];
        cout << start + step * (index + len / 2) << " " << Data[start + step * (index + len / 2)] << endl;
    }
    cout << "Loop end" << endl;
}

void Fouier::FFT(){
    int index = 0;
    FFT(0, 1, DATALEN);
    cout << "Transfer Data:" << endl;
    while(index < DATALEN)
        cout << Data[index++] << " ";
}
