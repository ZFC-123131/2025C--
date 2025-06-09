#include<iostream>
using namespace std;
class Complex
{
    public:
    Complex(double r=0,double i=0):real(r),imag(i){}
    operator double(){return real;}
    private:
    double real;
    double imag;
};
int main()
{
    Complex c1(21,5),c2(2,5);
    double dl;
    dl=21.2+c1;
    cout<<dl<<endl;
    dl=12.3+c2;
    cout<<dl<<endl;
    return 0;
}