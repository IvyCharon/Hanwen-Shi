#ifndef integer_h
#define integer_h
#include<vector>
#include<cmath>
#include<iostream>
#include<cstring>
#include<stdlib.h>

class integer
{
    friend std::ostream &operator<<(std::ostream &os,const integer &obj);
    friend std::istream &operator>>(std::istream &is,integer &obj);
    friend integer operator+(const integer &a,const integer &b);
    friend integer operator-(const integer &a,const integer &b);
    friend integer operator*(const integer &a,const integer &b);
    friend integer operator/(const integer &a,const integer &b);
    friend integer operator%(const integer &a,const integer &b);
    friend integer operator-(const integer &a);
    friend bool operator==(const integer &a,const integer &b);
    friend bool operator>(const integer &a,const integer &b);
    friend bool operator<(const integer &a,const integer &b);
    friend bool operator>=(const integer &a,const integer &b);
    friend bool operator<=(const integer &a,const integer &b);
    friend bool operator!=(const integer &a,const integer &b);

private:
    std::vector<int> number;
    bool zhf;

public:
    integer(std::string biu = "")
    {
        int len = biu.length();
        if(len == 0)zhf = 1;
        else if(biu[0] == '-')
        {
            zhf = 0;
            for(int i = len - 1;i >= 1;-- i)
            {
                if(biu[i] == '.')break;
                number.push_back(biu[i] - '0');
            }
        }
        else
        {
            zhf = 1;
            for(int i = len - 1;i >= 0;-- i)
            {
                if(biu[i] == '.')break;
                else number.push_back(biu[i] - '0');
            }
        }
    }
    integer(int t)
    {
        int tmp = 1,k = t;
        if(t >= 0)zhf = 1;
        else
        {
            zhf = 0;
            k = - k;
        }
        while(k / tmp >= 1)
        {
            number.push_back((k % (tmp * 10) - k % tmp) / tmp);
            tmp *= 10;
        }
        if(t == 0)number.push_back(0);
    }
    integer &operator=(const integer &obj)
    {
        zhf = obj.zhf;
        number.clear();
        for(int i = 0;i < obj.number.size();++ i)number.push_back(obj.number[i]);
    }
    integer(const integer &obj)
    {
        zhf = obj.zhf;
        for(int i = 0;i < obj.number.size();++ i)number.push_back(obj.number[i]);
    }
    integer operator+=(const integer &b);
    integer operator-=(const integer &b);
    integer operator*=(const integer &b);
    integer operator/=(const integer &b);
    integer &operator++();
    integer operator++(int x);
    integer &operator--();
    integer operator--(int x);
    operator double () const;
    operator std::string () const;
    operator bool () const;
};
#endif