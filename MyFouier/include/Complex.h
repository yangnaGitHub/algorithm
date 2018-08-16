#ifndef COMPLEX_H
#define COMPLEX_H


class Complex
{
    public:
        Complex();
        virtual ~Complex();
        double GetRE() { return RE; }
        void SetRE(double val) { RE = val; }
        double GetIM() { return IM; }
        void SetIM(double val) { IM = val; }
    private:
        double RE;
        double IM;
};

#endif // COMPLEX_H
