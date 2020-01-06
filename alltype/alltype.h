#ifndef alltype_h
#define alltype_h
#include "integer.h"
#include <cstring>
#include <iostream>
#include <stdio.h>
class alltype
{
    friend alltype operator+(const alltype &a,const alltype &b);
    friend alltype operator-(const alltype &a,const alltype &b);
    friend alltype operator*(const alltype &a,const alltype &b);
    friend alltype operator/(const alltype &a,const alltype &b);
    friend alltype operator%(const alltype &a,const alltype &b);
    friend alltype operator-(const alltype &a);
    friend bool operator||(const alltype &a,const alltype &b);
    friend bool operator&&(const alltype &a,const alltype &b);
    friend bool operator!(const alltype &a);
    friend bool operator>(const alltype &a,const alltype &b);
    friend bool operator<(const alltype &a,const alltype &b);
    friend bool operator==(const alltype &a,const alltype &b);
    friend bool operator!=(const alltype &a,const alltype &b);
    friend bool operator>=(const alltype &a,const alltype &b);
    friend bool operator<=(const alltype &a,const alltype &b);
    friend void print(const alltype &a);

public:
    integer type0;
    bool type1;
    double type2;
    std::string type3;
    std::string name;
    int now;
    alltype(int t = -1,std::string k = "") : now(t)
    {
        type0 = NULL; type1 = NULL; type2 = NULL; type3 = "";
        if(t == 0)type0 = (integer)k;
        if(t == 3)type3 = k;
        if(t == 1)
        {
            if(k == "true")type1 = 1;
            else if(k == "false")type1 = 0;
        }
        if(t == 2)
        {
            double yu,flag = 1;
            int w;
            for(w = 0;w < k.length();++ w)
            {
                if(k[w] == '.')break;
            }
            if(k[0] == '-')
            {
                for(int i = w - 1;i > 0;-- i)
                {
                    yu += flag * (k[i] + '0');
                    flag *= 10;
                }
                flag = 0.1;
                for(int i = w + 1;i < k.length();++ i)
                {
                    yu += flag * (k[i] + '0');
                    flag /= 10;
                }
                yu = - yu;
            }
            else
            {
                flag = 1;
                for(int i = w - 1;i >= 0;-- i)
                {
                    yu += flag * (k[i] + '0');
                    flag *= 10;
                }
                flag = 0.1;
                for(int i = w + 1;i < k.length();++ i)
                {
                    yu += flag * (k[i] + '0');
                    flag /= 10;
                }
                yu = - yu;
            }
            type2 = yu;
        }
    }
    alltype &operator=(const alltype &a)
    {
        type0 = a.type0;
        type1 = a.type1;
        type2 = a.type2;
        type3 = a.type3;
        now = a.now;
    }
    alltype(double t)
    {
        now = 2;
        type2 = t;
    }
    operator bool() const;
    operator double() const;
};

#endif