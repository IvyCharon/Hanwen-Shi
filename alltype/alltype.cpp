#include "alltype.h"

alltype operator+(const alltype &a,const alltype &b)
{
    alltype ans;
    if(a.now == 0 && b.now == 0)
    {
        ans.type0 = a.type0 + b.type0;
        ans.now = 0;
        return ans;
    }
    if(a.now == 0 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type0;
        if(b.now)ans.type0 += 1;
        return ans;
    }
    if(a.now == 0 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = (double)a.type0 + b.type2;
        return ans;
    }
    if(a.now == 1 && b.now == 0)
    {
        ans.now = 0;
        ans.type0 = b.type0;
        if(a.now) ans.type0 += 1;
        return ans;
    }
    if(a.now == 1 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type1 + b.type1;
        return ans;
    }
    if(a.now == 1 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = b.type2;
        if(a.type1)ans.type2 += 1;
        return ans;
    }
    if(a.now == 2 && b.now == 0)
    {
        ans.now = 2;
        ans.type2 = a.type2 + (double)b.type1;
        return ans;
    }
    if(a.now == 2 && b.now == 1)
    {
        ans.now = 2;
        ans.type2 = a.type2;
        if(b.type1)ans.type2 += 1;
        return ans;
    }
    if(a.now == 2 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = a.type2 + b.type2;
        return ans;
    }
    if(a.now == 3 && b.now == 3)
    {
        ans.now = 3;
        ans.type3 = a.type3 + b.type3;
        return ans;
    }
}

alltype operator-(const alltype &a,const alltype &b)
{
    alltype ans;
    if(a.now == 0 && b.now == 0)
    {
        ans.type0 = a.type0 - b.type0;
        ans.now = 0;
        return ans;
    }
    if(a.now == 0 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type0;
        if(b.now)ans.type0 -= 1;
        return ans;
    }
    if(a.now == 0 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = (double)a.type0 - b.type2;
        return ans;
    }
    if(a.now == 1 && b.now == 0)
    {
        ans.now = 0;
        ans.type0 = -b.type0;
        if(a.now) ans.type0 += 1;
        return ans;
    }
    if(a.now == 1 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type1 - b.type1;
        return ans;
    }
    if(a.now == 1 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = -b.type2;
        if(a.type1)ans.type2 += 1;
        return ans;
    }
    if(a.now == 2 && b.now == 0)
    {
        ans.now = 2;
        ans.type2 = a.type2 - (double)b.type1;
        return ans;
    }
    if(a.now == 2 && b.now == 1)
    {
        ans.now = 2;
        ans.type2 = a.type2;
        if(b.type1)ans.type2 -= 1;
        return ans;
    }
    if(a.now == 2 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = a.type2 - b.type2;
        return ans;
    }
}

alltype operator*(const alltype &a,const alltype &b)
{
    alltype ans;
    if(a.now == 0 && b.now == 0)
    {
        ans.type0 = a.type0 * b.type0;
        ans.now = 0;
        return ans;
    }
    if(a.now == 0 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type0;
        if(!b.now)ans.type0 = 0;
        return ans;
    }
    if(a.now == 0 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = (double)a.type0 * b.type2;
        return ans;
    }
    if(a.now == 1 && b.now == 0)
    {
        ans.now = 0;
        ans.type0 = b.type0;
        if(!a.now) ans.type0 = 0;
        return ans;
    }
    if(a.now == 1 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type1 * b.type1;
        return ans;
    }
    if(a.now == 1 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = b.type2;
        if(!a.type1)ans.type2 = 0;
        return ans;
    }
    if(a.now == 2 && b.now == 0)
    {
        ans.now = 2;
        ans.type2 = a.type2 * (double)b.type1;
        return ans;
    }
    if(a.now == 2 && b.now == 1)
    {
        ans.now = 2;
        ans.type2 = a.type2;
        if(!b.type1)ans.type2 = 0;
        return ans;
    }
    if(a.now == 2 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = a.type2 * b.type2;
        return ans;
    }
    if(a.now == 3 && b.now == 0)
    {
        ans.now = 3;
        for(integer i = (integer)1;i <= b.type0;++ i)
        {
            ans.type3 += a.type3;
        }
        return ans;
    }
    if(a.now == 0 && b.now == 3)
    {
        ans.now = 3;
        for(integer i = (integer)1;i <= a.type0;++ i)
        {
            ans.type3 += b.type3;
        }
        return ans;
    }
}

alltype operator/(const alltype &a,const alltype &b)
{
    alltype ans;
    if(a.now == 0 && b.now == 0)
    {
        ans.type0 = a.type0 / b.type0;
        ans.now = 0;
        return ans;
    }
    if(a.now == 0 && b.now == 1)
    {
        ans.now = 0;
        ans.type0 = a.type0;
        return ans;
    }
    if(a.now == 0 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = (double)a.type0 / b.type2;
        return ans;
    }
    if(a.now == 1 && b.now == 0)
    {
        ans.now = 0;
        ans.type0 = 0;
        if(a.now)ans.type0 = (integer)1 / b.type0;
        return ans;
    }
    if(a.now == 1 && b.now == 1)
    {
        ans.now = 0;
        if(!a.type1)ans.type0 = 0;
        if(a.type1)ans.type0 = 1;
        return ans;
    }
    if(a.now == 1 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = a.type1 / b.type2;
        return ans;
    }
    if(a.now == 2 && b.now == 0)
    {
        ans.now = 2;
        ans.type2 = a.type2 / (double)b.type1;
        return ans;
    }
    if(a.now == 2 && b.now == 1)
    {
        ans.now = 2;
        ans.type2 = a.type2;
        return ans;
    }
    if(a.now == 2 && b.now == 2)
    {
        ans.now = 2;
        ans.type2 = a.type2 / b.type2;
        return ans;
    }
}

alltype operator%(const alltype &a,const alltype &b)
{
    alltype ans,aa = a,bb = b;
    if(a.now == 1)
    {
        aa.now = 0;
        aa.type0 = a.type1;
    }
    if(b.now == 1)
    {
        bb.now = 0;
        bb.type0 = b.type1;
    }
    ans.now = 0;
    ans.type0 = aa.type0 % bb.type0;
    return ans;
}

alltype operator-(const alltype &a)
{
    alltype ans;
    int op = a.now;
    switch(op)
    {
        case 0:
            ans.now = 0;
            ans.type0 = -a.type0;
            break;
        case 1:
            ans.now = 0;
            if(a.type1)ans.type0 = -(integer)1;
            else ans.type0 = (integer)0;
            break;
        case 2:
            ans.now = 2;
            ans.type2 = -a.type2;
            break;
    }
    return ans;
}

bool operator||(const alltype &a,const alltype &b)
{
    if((bool)a || (bool)b)return 1;
    else return 0;
}

bool operator&&(const alltype &a,const alltype &b)
{
    if((bool)a && (bool)b)return 1;
    else return 0;
}

bool operator!(const alltype &a)
{
    return !(bool)a;
}

bool operator>(const alltype &a,const alltype &b)
{
    if(a.now == 0 && b.now == 0)
    {
        if(a.type0 > b.type0)return true;
        else return false;
    }
    if(a.now == 0 && b.now == 1)
    {
        if(a.type0 > (integer)b.type1)return true;
        else return false;
    }
    if(a.now == 0 && b.now == 2)
    {
        if((double)a.type0 > b.type2)return true;
        else return false;
    }
    if(a.now == 1 && b.now == 0)
    {
        if((integer)a.type1 > b.type0)return true;
        else return false;
    }
    if(a.now == 1 && b.now == 1)
    {
        if(a.type1 > b.type1)return true;
        else return false;
    }
    if(a.now == 1 && b.now == 2)
    {
        if(a.type1 > b.type2)return true;
        else return false;
    }
    if(a.now == 2 && b.now == 0)
    {
        if(a.type2 > (double)b.type0)return true;
        else return false;
    }
    if(a.now == 2 && b.now == 1)
    {
        if(a.type2 > b.type1)return true;
        else return false;
    }
    if(a.now == 2 && b.now == 2)
    {
        if(a.type2 > b.type2)return true;
        else return false;
    }
    if(a.now == 3 && b.now == 3)
    {
        if(a.type3 > b.type3)return true;
        else return false;
    }
}

bool operator==(const alltype &a,const alltype &b)
{
    if(a.now != b.now) return false;
    int op = a.now;
    switch (op)
    {
        case 0:
            if(a.type0 != b.type0)return false;
            break;
        case 1:
            if(a.type1 != b.type1)return false;
            break;
        case 2:
            if(a.type2 != b.type2)return false;
            break;
        case 3:
            if(a.type3 != b.type3)return false;
            break;
    }
    return true;
}

bool operator<(const alltype &a,const alltype &b)
{
    if(a == b || a > b)return false;
    else return true;
}

bool operator!=(const alltype &a,const alltype &b)
{
    if(a == b)return false;
    else return true;
}

bool operator>=(const alltype &a,const alltype &b)
{
    if(a > b || a == b)return true;
    else return false;
}

bool operator<=(const alltype &a,const alltype &b)
{
    if(a > b)return false;
    else return true;
}

alltype::operator double() const
{
    if(now == 2)return type2;
    if(now == 0)return double(type0);
    if(now == 1)return double(type1);
}

void print(const alltype &a)
{
    int op = a.now;
    switch (op)
    {
        case 0:
            std::cout<<a.type0;
            break;
        case 1:
            if(a.type1)std::cout<<std::string("True");
            else std::cout<<std::string("False");
            break;
        case 2:
            printf("%.6lf",a.type2);
            break;
        case 3:
            std::cout<<a.type3;
            break;
    }
    return;
}

alltype::operator bool() const
{
    int op = now;
    switch (op)
    {
        case 0:
            if(type0)return true;
            else return false;
        case 1:
            return type1;
        case 2:
            if(type2 == 0)return false;
            else return true;
        case 3:
            if(type3.empty())return false;
            else return true;
    }

}