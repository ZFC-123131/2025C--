#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
void yanghui(int n)
{
    vector<vector<int>>a(n, vector<int>(n, 0));
    
    for(int i=0;i<n;i++){
        a[i][0]=a[i][i]=1;
        for(int j=1;j<i;j++){
            a[i][j]=a[i-1][j-1]+a[i-1][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int k=0;k<n-i;k++){//����ÿ��ǰ���������ʹ������ǳ������Ρ�
            cout<<"  ";
        }
        for(int j=0;j<=i;j++){
            cout<<setw(4)<<a[i][j];//setw()��������������
        }
        cout<<endl;
    }
}
int main()
{
    int n;
    cin>>n;
    yanghui(n);
    return 0;
}