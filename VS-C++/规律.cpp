#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    double sum = 0.0;
    double a = 2, b = 1; // ��ʼ����a����ĸb
    for (int i = 0; i < n; ++i) {
        sum += a / b;
        double temp = a;
        a = a + b; // �·�����ԭ����+��ĸ
        b = temp;  // �·�ĸ��ԭ����
    }
    cout << fixed << setprecision(2) << sum << endl;
    return 0;
}