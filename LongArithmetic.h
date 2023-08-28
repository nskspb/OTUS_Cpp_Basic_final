#pragma once

#include <iostream>
#include <vector>
#include <algorithm>


class LongNum {
    private: 
    std::vector <int> number;
    bool sign;

    public:

    LongNum();
    LongNum(std::vector<int>& vec, bool sig);
    LongNum( std::string & str);
    LongNum(int n);
    ~LongNum();

    size_t size() const;
    
    friend std::ostream& operator<<(std::ostream& out, const LongNum& num);
    int &operator[](int position) ;

    LongNum operator+(const LongNum& second);
    LongNum operator-(const LongNum& second);
    LongNum operator*(const LongNum& second);
    LongNum operator-();
    
    bool operator==(LongNum& second);
    bool operator>(LongNum& second);
    bool operator>=(LongNum& second);
    bool operator<(LongNum& second);
    bool operator<=(LongNum& second);
};

LongNum::LongNum()
{
  sign = true;
  number.push_back(0);
} 

LongNum::LongNum(std::vector<int>& vec, bool sig = true): number(vec), sign(sig) {}


LongNum::LongNum( std::string & str)
{
    sign = str[0]!='-';
    if (sign)
    {
      for (int i=str.size()-1; i>=0; --i)
        {
            number.push_back(str[i] - '0');
        }  
    }
    else
    {
        for (int i=str.size()-1; i>=1; --i)
        {
            number.push_back(str[i] - '0');
        }  
    }
}

LongNum::LongNum(int n)
{
    sign = n>=0;
    if (n==0) number.push_back(0);
    while (n>0)
    {
        number.push_back(n%10);
        n/10;
    }
}

LongNum::~LongNum()
{
    number.clear();
}

size_t LongNum::size() const
{
    return number.size();
}

std::ostream& operator<<(std::ostream& out, const LongNum& num) 
{   
    if (!num.sign) out << "-";
    for (auto it = num.number.rbegin(); it != num.number.rend(); it++) {
        out << *it;
    }
    return out;
}

 int &LongNum::operator[](int position) 
    {
        return number[position];
    }

LongNum LongNum::operator+(const LongNum& num)
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
        if (!sign)
        {
            if (!num.sign)
            {
                LongNum res = first + second;
                res.sign = false;
                return res;
            }
            else
            {
                LongNum res = second - first;
                return res;
            } 
        }
        else if (!num.sign)
            {
                LongNum res = first - second;
                return res;       
            }
    int c = 0, t=0;
    if (first >= second)
    {
       for (size_t i=0; i<=second.size()-1;i++)
    {
        t = first[i] + second[i] + c;
        c = t >= 10;
        first[i] = t%10;
    }
    if (c==1) 
    {
        if ((first.size()-second.size())>=1)
        {
            first.number[second.size()]++;
        }
        else first.number.push_back(1);
    }
    return first; 
    }
    return second + first;
}


LongNum LongNum::operator-(const LongNum& num)
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
        if (!sign)
        {
            if (!num.sign)
            {
                LongNum res = second - first;
                return res;
            }
            else
            {
                LongNum res = first + second;
                res.sign = false;
                return res;
            } 
        }
        else if (!num.sign)
            {
                LongNum res = first + second;
                return res;       
            }
    int c = 0, t=0;
    int s = second.size();
    if (first==second) return LongNum(0);
    if (first > second)
    {
       for(size_t i= s; i<first.size();++i)
       {
        second.number.push_back(0);
       }
       for (size_t i=0; i<=s-1;i++)
    {
        t = first[i] - second[i] - c;
        if (t<0)
        {
         c = 1;  
         first[i] = t + 10;
        }
        else
        {
         c = 0;  
         first[i] = t;
        }
    }
    if (c==1) first.number.pop_back();
    while (first.number[first.size()-1] == 0) first.number.pop_back();
    return first; 
    }
    LongNum res = second - first;
    res.sign = false;
    return res;
}

LongNum LongNum::operator*(const LongNum& num) // Дореализовать
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
        if (!sign)
        {
            if (!num.sign)
            {
                LongNum res = first + second;
                res.sign = false;
                return res;
            }
            else
            {
                LongNum res = second - first;
                return res;
            } 
        }
        else if (!num.sign)
            {
                LongNum res = first - second;
                return res;       
            }
    int c = 0, t=0;
    if (first >= second)
    {
       for (size_t i=0; i<=second.size()-1;i++)
    {
        t = first[i] + second[i] + c;
        c = t >= 10;
        first[i] = t%10;
    }
    if (c==1) 
    {
        if ((first.size()-second.size())>=1)
        {
            first.number[second.size()]++;
        }
        else first.number.push_back(1);
    }
    return first; 
    }
    return second + first;
}

LongNum LongNum::operator-()
{
    LongNum res = *this;
    res.sign = !res.sign;
    return res;
}

bool LongNum::operator==(LongNum& second)
{
    if (sign != second.sign) return false;
    if (number.size() > second.size()) return false;
    if (number.size() < second.size()) return false;
    for (int i=0; i<= number.size()-1;++i)
    {
        if (number[i]!=second[i]) return false;
    }
    return true;
}

 bool LongNum::operator>(LongNum& second)
{
    if (sign > second.sign) return true;
    if (sign < second.sign) return false;
    if (number.size() > second.size()) return sign;
    if (number.size() < second.size()) return !sign;
    for (int i = number.size() - 1; i >= 0; --i)
    {
        if (number[i] > second[i]) return sign;
        if (number[i] < second[i]) return !sign;
    }
    return false;
}


 bool LongNum::operator>=(LongNum& second)
{
    return !(*this<second);
}

 bool LongNum::operator<(LongNum& second)
{
    if (sign > second.sign) return false;
    if (sign < second.sign) return true;
    if (number.size() < second.size()) return sign;
    if (number.size() > second.size()) return !sign;
    for (int i = number.size() - 1; i >= 0; --i)
    {
        if (number[i] < second[i]) return sign;
        if (number[i] > second[i]) return !sign;
    }
    return false;
}

 bool LongNum::operator<=(LongNum& second)
{
    return !(*this>second);
}