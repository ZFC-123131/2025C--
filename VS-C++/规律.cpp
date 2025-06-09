#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    double sum = 0.0;
    double a = 2, b = 1; // 初始分子a，分母b
    for (int i = 0; i < n; ++i) {
        sum += a / b;
        double temp = a;
        a = a + b; // 新分子是原分子+分母
        b = temp;  // 新分母是原分子
    }
    cout << fixed << setprecision(2) << sum << endl;
    return 0;
}