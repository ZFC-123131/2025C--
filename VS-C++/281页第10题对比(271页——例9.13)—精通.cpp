#include<iostream>
using namespace std;
//前向声明
class Date;
class Time;
//定义display函数（类外普通函数）
void display(const Time&,const Date&);

class Time
{
    public:
    Time(int,int,int);
    // 声明类外的 display 函数为友元
    friend void display(const Time&,const Date&);
    private:
    int hour;
    int minute;
    int sec;
};
class Date
{
    public:
    Date(int,int,int);
    // 声明类外的 display 函数为友元
    friend void display(const Time&,const Date&);
    private:
    int month;
    int day;
    int year;
};
Time::Time(int h,int m,int s)
{
    hour=h;
    minute=m;
    sec=s;
}
Date::Date(int m,int d,int y)
{
    month=m;
    day=d;
    year=y;
}
// 类外普通函数 display 的定义
void display(const Time& t,const Date& d)
{
    cout<<d.month<<"/"<<d.day<<"/"<<d.year<<endl;
    cout<<t.hour<<":"<<t.minute<<":"<<t.sec<<endl;
}

int main()
{
    Time t1(10,13,56);
    Date d1(12,25,2004);
    display(t1,d1);
    return 0;
}