#include "integer.h"

bool operator==(const integer &a,const integer &b)
{
    if(a.number.size() != b.number.size())return false;
    if(a.zhf != b.zhf)return false;
    for(int i = 0;i <= a.number.size() - 1;++ i)
    {
        if(a.number[i] != b.number[i])return false;
    }
    return true;
}

bool operator>(const integer &a,const integer &b)
{
    if(a.zhf == 1 && b.zhf == 0)return true;
    if(a.zhf == 0 && b.zhf == 1)return false;
    if(a.zhf == 1 && b.zhf == 1)
    {
        if(a.number.size() > b.number.size())return true;
        else if(a.number.size() < b.number.size())return false;
        else
        {
            for(int i = a.number.size() - 1;i >= 0;-- i)
            {
                if(a.number[i] > b.number[i])return true;
                if(a.number[i] < b.number[i])return false;
            }
        }
    }
    if(a.zhf == 0 && b.zhf == 0)
    {
        if(a.number.size() < b.number.size())return true;
        else if(a.number.size() > b.number.size())return false;
        else
        {
            for(int i = a.number.size() - 1;i >= 0;-- i)
            {
                if(a.number[i] > b.number[i])return false;
            }
        }
    }
    if(a == b)return false;
    return true;
}

bool operator<(const integer &a,const integer &b)
{
    if(a == b)return false;
    else if(a > b)return false;
    else return true;
}

bool operator>=(const integer &a,const integer &b)
{
    if(a > b || a == b)return true;
    return false;
}

bool operator<=(const integer &a,const integer &b)
{
    if(a > b)return false;
    return true;
}

bool operator!=(const integer &a,const integer &b)
{
    if(a == b)return false;
    else return true;
}

integer operator-(const integer &a)
{
    if(a == (integer)0)return a;
    integer aa;
    aa = a;
    if(aa.zhf == 1)aa.zhf = 0;
    else aa.zhf = 1;
    return aa;
}

integer operator+(const integer &a,const integer &b)
{
    integer ans;
    if(a.zhf == 1 && b.zhf == 1)ans.zhf = 1;
    if(a.zhf == 0 && b.zhf == 0)ans.zhf = 0;
    if(a.zhf == 1 && b.zhf == 0)return a - (-b);
    if(a.zhf == 0 && b.zhf == 1)return b - (-a);
    int n;
    n = (a.number.size() > b.number.size()) ? a.number.size() : b.number.size();
    int ed = 0;
    for(int i = 0;i <= n - 1;++ i)
    {
        if(i < a.number.size()) ed += a.number[i];
        if(i < b.number.size()) ed += b.number[i];
        //cout<<ed<<endl;
        ans.number.push_back(ed % 10);
        ed = ed / 10;
    }
    if(ed) ans.number.push_back(ed);
    return ans;
}

integer operator-(const integer &a,const integer &b)
{
    integer ans;
    if(a == b)
    {
        ans.zhf = 1;
        ans.number.push_back(0);
        return ans;
    }
    if(a.zhf == 1 && b.zhf == 0)return a + (-b);
    if(a.zhf == 0 && b.zhf == 1)return a + (-b);
    if(a.zhf == 0 && b.zhf == 0)return (-b) - (-a);
    int n,t = 0;
    n = b.number.size();
    if(a > b)
    {
        ans.zhf = 1;
        for(int i = 0;i < n;++ i)
        {
            if(a.number[i] - t < b.number[i])
            {
                ans.number.push_back(a.number[i] - t + 10 - b.number[i]);
                t = 1;
            }
            else
            {
                ans.number.push_back(a.number[i] - b.number[i] - t);
                t = 0;
            }
        }
        if(a.number.size() > n)
        {
            ans.number.push_back(a.number[n] - t);
            for(int i = n + 1;i < a.number.size();++ i)ans.number.push_back(a.number[i]);
        }
        while(ans.number[ans.number.size() - 1] == 0)ans.number.pop_back();
        return ans;
    }
    else return -(b - a); 
}

integer operator*(const integer &a,const integer &b)
{
    integer ans;
    if(a == (integer)0 || b == (integer)0)
    {
        ans.zhf = 1;
        ans.number.push_back(0);
        return ans;
    }
    if(a.zhf == b.zhf)ans.zhf = 1;
    else ans.zhf = 0;
    int t = 0;
    for(int i = 0;i < a.number.size() + b.number.size();++ i)ans.number.push_back(0);
    for(int i = 0;i < a.number.size() + b.number.size() - 1;++ i)
    {
        for(int j = 0;j < a.number.size() + b.number.size() - 1;++ j)
        {
            if(i < a.number.size() && j < b.number.size())ans.number[i + j] += a.number[i] * b.number[j];
        }
    }
    for(int i = 0;i < ans.number.size() - 1;++ i)
    {
        ans.number[i + 1] += ans.number[i] / 10;
        ans.number[i] = ans.number[i] % 10;
    }
    while(ans.number[ans.number.size() - 1] >= 10)
    {
        t = ans.number[ans.number.size() - 1] / 10;
        ans.number[ans.number.size() - 1] = ans.number[ans.number.size() - 1] % 10;
        ans.number.push_back(t);
    }
    if(ans.number[a.number.size() + b.number.size() - 1] == 0)ans.number.pop_back();
    return ans;
}

integer operator/(const integer &a,const integer &b)
{
    integer ans,ANS;
    if(a.zhf == b.zhf)ans.zhf = 1;
    else ans.zhf = 0;
    if(a == (integer)0)
    {
        ans.zhf = 1;
        ans.number.push_back(0);
        return ans;
    }
    if((a.zhf && b.zhf && a < b)||(!a.zhf && !b.zhf && a > b))
    {
        ans.number.push_back(0);
        return ans;
    }
    if((a.zhf && !b.zhf && a < -b) || (!a.zhf && b.zhf && a > -b))
    {
        ans.number.push_back(1);
        return ans;
    }
    integer tmp,bb,aa;
    tmp.zhf = 1;
    bb = b;
    aa = a;
    int li,former,later;
    li = bb.number.size();
    if(aa.zhf == 0)aa.zhf = 1;
    if(bb.zhf == 0)bb.zhf = 1;
    bool kj = true;
    while(aa.number.size() != 0 && aa >= bb)
    {
        int k =  aa.number.size();
        for(int i = k - 1;i >= k - li;-- i)
        {
            tmp.number.push_back(aa.number[i]);
            aa.number.pop_back();
        }
        later = k - li;
        integer biu;
        biu.zhf = 1;
        for(int i = tmp.number.size() - 1;i >= 0;-- i)biu.number.push_back(tmp.number[i]);
        if(biu < bb)
        {
            tmp.number.push_back(aa.number[aa.number.size() - 1]);
            aa.number.pop_back();
            biu.number.clear();
            for(int i = tmp.number.size() - 1;i >= 0;-- i)biu.number.push_back(tmp.number[i]);
            later -= 1;
        }
        if(kj)former = later;
        for(int i = 1;i <= former - later - 1;++ i)ans.number.push_back(0);
        int n = 0;
        while(biu >= bb)
        {
            biu = biu - bb;
            n += 1;
        }
        ans.number.push_back(n);       
        if(biu.number[biu.number.size() - 1] != 0)
        {
            for(int i = 0;i <= biu.number.size() - 1;++ i)aa.number.push_back(biu.number[i]);
        }
        kj = false;
        former = later;
        tmp.number.clear();
        biu.number.clear();
    }
    for(int i = 1;i <= later;++ i)ans.number.push_back(0);
    ANS.zhf = ans.zhf;
    for(int i = ans.number.size() - 1;i >= 0;-- i)ANS.number.push_back(ans.number[i]);
    if(ans.zhf == 0 && aa > (integer)0)
    {
        ANS = ANS - (integer)1;
    }
    if(ANS.number[ANS.number.size() - 1] == 0)ANS.number.pop_back();
    return ANS;
}

integer operator%(const integer &a,const integer &b)
{
    return a - ((a / b) * b);
}

integer integer::operator+=(const integer &b)
{
    *this = *this + b;
    return *this;
}

integer integer::operator-=(const integer &b)
{
    *this = *this - b;
    return *this;
}

integer integer::operator*=(const integer &b)
{
    *this = *this * b;
    return *this;
}

integer integer::operator/=(const integer &b)
{
    *this = *this / b;
    return *this;
}

integer &integer::operator++()
{
    integer biu;
    biu.zhf = 1;
    biu.number.push_back(1);
    *this = *this + biu;
    return *this;
}

integer integer::operator++(int x)
{
    integer tmp;
    tmp = *this;
    integer biu;
    biu.zhf = 1;
    biu.number.push_back(1);
    *this = *this + biu;
    return tmp;
}

integer &integer::operator--()
{
    integer biu;
    biu.zhf = 1;
    biu.number.push_back(1);
    *this = *this - biu;
    return *this;
}

integer integer::operator--(int x)
{
    integer tmp;
    tmp = *this;
    integer biu;
    biu.zhf = 1;
    biu.number.push_back(1);
    *this = *this - biu;
    return tmp;
}

std::ostream &operator<<(std::ostream &os,const integer &obj)
{
    if(obj.zhf == 0)os<<'-';
    for(int i = obj.number.size() - 1;i >= 0;-- i)os<<obj.number[i];
    return os;
}

std::istream &operator>>(std::istream &is,integer &obj)
{
    std::string biu;
    is>>biu;
    int len = biu.length();
    if(biu[0] == '-')
    {
        obj.zhf = 0;
        for(int i = len - 1;i >= 1;-- i)obj.number.push_back(biu[i] - '0');
    }
    else
    {
        obj.zhf = 1;
        for(int i = len - 1;i >= 0;-- i)obj.number.push_back(biu[i] - '0'); 
    }
    return is;
}

integer::operator double () const
{
    double out = 0;
    double biu = 0;
    for(int i = 0;i < number.size();++ i)
    {
        biu = number[i];
        for(int j = 1;j <= i;++ j) biu = (double)biu * 10;
        out += biu;
    }
    return out;
}

integer::operator bool () const
{
    if(zhf == 1 && number.size() == 1 && number[0] == 0)return false;
    else return true;
}

integer::operator std::string () const
{
    std::string out = "";
    if(zhf == 0)out += '-';
    for(int i = number.size() - 1;i >= 0;-- i)out += number[i] + '0';
    return out;
}