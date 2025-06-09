#include<iostream>
using namespace std;
#define i_1 100000
#define i_2 200000
#define i_3 400000
#define i_4 600000
#define i_5 1000000
int main()
{
    int i,j;
    cout<<"一个整数，当月利润:";
    cin>>i;
    if(i<=i_1){
        cout<<"一个整数,奖金:"<<i*(float)10/100;
    }
    return 0;
}