#include "Complex.hpp"

Complex::Complex(double Re, double Im){
    this->Re = Re;
    this->Im = Im;
}

Complex::~Complex(void){}

/*Complex operator+(Complex Pa, Complex Pb){
    return Complex(Pa.Re + Pb.Re, Pa.Im + Pb.Im);
}

Complex operator+(double Pa, Complex &Pb){
    return Complex(Pa + Pb.Re, Pb.Im);
}

Complex operator+(Complex &Pa, double Pb){
    return Complex(Pa.Re + Pb, Pa.Im);
}

Complex operator-(Complex &Pa, Complex &Pb){
    return Complex(Pa.Re - Pb.Re, Pa.Im - Pb.Im);
}

Complex operator-(double Pa, Complex &Pb){
    return Complex(Pa - Pb.Re, -Pb.Im);
}

Complex operator-(Complex &Pa, double Pb){
    return Complex(Pa.Re - Pb, Pa.Im);
}*/

Complex operator*(Complex &Pa, Complex &Pb){
    return Complex(Pa.Re * Pb.Re - Pa.Im * Pb.Im, Pa.Re * Pb.Im + Pa.Im * Pb.Re);
}

Complex operator*(double Pa, Complex &Pb){
    return Complex(Pa * Pb.Re, Pa * Pb.Im);
}

Complex operator*(Complex &Pa, double Pb){
    return Complex(Pa.Re * Pb, Pa.Im * Pb);
}

/*Complex Complex::operator=(Complex &Pa){
    this->Re = Pa.Re;
    this->Im = Pa.Im;
    return *this;
}

Complex Complex::operator=(double Pa){
    this->Re = Pa;
    this->Im = 0;
    return *this;
}*/

ostream& operator<<(ostream &out, Complex &Pa){
    if(Pa.Re || (!Pa.Re && !Pa.Im))
        out << Pa.Re;
    if(Pa.Im){
        if(0 < Pa.Im)
            out << "+";
        if(1 != Pa.Im)
            out << Pa.Im;
        out << "i";
    }
    return out;
}
