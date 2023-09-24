#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class LongNum
{
private:
    std::vector<int> number;
    bool sign;

public:
    LongNum();
    LongNum(std::vector<int> &vec, bool sig);
    LongNum(std::string &str);
    LongNum(int n);
    ~LongNum();

    size_t size() const;

    LongNum &operator=(const LongNum &other);
    LongNum &operator=(int &other);

    friend std::ostream &operator<<(std::ostream &out, const LongNum &num);
    int &operator[](int position);

    LongNum operator+(const LongNum &num);
    LongNum operator-(const LongNum &num);
    LongNum operator*(const LongNum &num);
    LongNum operator/(const LongNum &num);
    LongNum operator-();
    LongNum operator+=(const LongNum &num);
    LongNum operator-=(const LongNum &num);
    LongNum operator*=(const LongNum &num);
    LongNum operator/=(const LongNum &num);

    bool operator==(LongNum &second);
    bool operator>(LongNum &second);
    bool operator>=(LongNum &second);
    bool operator<(LongNum &second);
    bool operator<=(LongNum &second);

    LongNum delete_lead_zeros(LongNum &num);
};

LongNum::LongNum()
{
    sign = true;
    number.push_back(0);
}

LongNum::LongNum(std::vector<int> &vec, bool sig = true) : number(vec), sign(sig) {}

LongNum::LongNum(std::string &str)
{
    sign = str[0] != '-';
    if (sign)
    {
        for (int i = str.size() - 1; i >= 0; --i)
        {
            number.push_back(str[i] - '0');
        }
    }
    else
    {
        for (int i = str.size() - 1; i >= 1; --i)
        {
            number.push_back(str[i] - '0');
        }
    }
}

LongNum::LongNum(int n)
{
    sign = n >= 0;
    if (n == 0)
        number.push_back(0);

    n = abs(n);
    while (n > 0)
    {
        number.push_back(n % 10);
        n /= 10;
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

LongNum &LongNum::operator=(const LongNum &other)
{
    sign = other.sign;
    number = other.number;
    return *this;
}

LongNum &LongNum::operator=(int &other)
{
    sign = other >= 0;
    LongNum tmp{other};
    *this = tmp;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const LongNum &num)
{
    if (!num.sign)
        out << "-";
    for (auto it = num.number.rbegin(); it != num.number.rend(); it++)
    {
        out << *it;
    }
    return out;
}

int &LongNum::operator[](int position)
{
    return number[position];
}

LongNum LongNum::operator+(const LongNum &num)
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
    if (!sign) // Знак первого выражения отрицательный
    {
        if (!num.sign) // Знак второго выражения отрицательный
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
    int c = 0, t = 0;
    long k = first.size() - second.size();
    long z = second.size();
    if (first >= second)
    {
        for (size_t i = 0; i <= second.size() - 1; i++)
        {
            t = first[i] + second[i] + c;
            c = t >= 10;
            first[i] = t % 10;
        }
        while (c == 1)
        {
            if (k >= 1)
            {
                if (first.number[z] == 9)
                {
                    first.number[z] = 0;
                    z++;
                    k--;
                    c = 1;
                }
                else
                {
                    first.number[z]++;
                    c = 0;
                }
            }
            else
            {
                first.number.push_back(1);
                c = 0;
            }
        }
        return first;
    }
    return second + first;
}

LongNum LongNum::operator-(const LongNum &num)
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
    int c = 0, t = 0;
    if (first == second)
        return LongNum(0);
    if (first > second)
    {
        int s = second.size();
        for (size_t i = s; i < first.size(); ++i)
        {
            second.number.push_back(0);
        }
        for (size_t i = 0; i <= first.size() - 1; i++)
        {
            t = first[i] - second[i] - c;
            if (t < 0)
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
        delete_lead_zeros(first);
        return first;
    }
    LongNum res = second - first;
    res.sign = false;
    return res;
}

LongNum LongNum::operator*(const LongNum &num)
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
    LongNum res(0);
    if ((first == res) || (second == res))
        return LongNum(0);

    if (first > second)
    {
        for (size_t i = second.size(); i < first.size(); ++i)
        {
            second.number.push_back(0);
        }
    }
    else
    {
        for (size_t i = first.size(); i < second.size(); ++i)
        {
            first.number.push_back(0);
        }
    }
    int n = first.size();
    int c = 0, t = 0;
    std::vector<int> w(n + n, 0);
    for (int i = 0; i < n; ++i)
    {
        c = 0;
        for (int j = 0; j < n; ++j)
        {
            t = w[i + j] + first[j] * second[i] + c;
            w[i + j] = t % 10;
            c = t / 10;
        }
        w[n + i] = c;
    }
    res = w;
    delete_lead_zeros(res);
    res.sign = !(sign ^ num.sign);
    return res;
}

LongNum LongNum::operator/(const LongNum &num)
{
    LongNum first = *this;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
    LongNum res(0);
    long k = second.size();
    long s = first.size() - second.size() + 1;
    try
    {
        if (second == res)
        {
            throw std::runtime_error("ERROR: division by zero!");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }

    if (first == second)
    {
        res = 1;
        res.sign = !(sign ^ num.sign);
        return res;
    }
    else if (first < second)
    {
        res = 0;
        return res;
    }

    std::vector<int> w(s, 0);

    while (second.size() < first.size())
    {
        second.number.insert(second.number.begin(), 0);
    }

    while (true)
    {
        if (second.size() < k)
        {
            break;
        }

        while (first >= second)
        {
            first -= second;
            w[s - 1]++;
        }
        s--;
        second.number.erase(second.number.begin());
    }

    res = w;
    delete_lead_zeros(res);
    res.sign = !(sign ^ num.sign);
    return res;
}

LongNum LongNum::operator-()
{
    LongNum res = *this;
    res.sign = !res.sign;
    return res;
}

LongNum LongNum::operator+=(const LongNum &num)
{
    *this = *this + num;
    return *this;
}

LongNum LongNum::operator-=(const LongNum &num)
{
    *this = *this - num;
    return *this;
}

LongNum LongNum::operator*=(const LongNum &num)
{
    *this = *this * num;
    return *this;
}

LongNum LongNum::operator/=(const LongNum &num)
{
    *this = *this / num;
    return *this;
}

bool LongNum::operator==(LongNum &second)
{
    if (sign != second.sign)
        return false;
    if (number.size() > second.size())
        return false;
    if (number.size() < second.size())
        return false;
    for (int i = 0; i <= number.size() - 1; ++i)
    {
        if (number[i] != second[i])
            return false;
    }
    return true;
}

bool LongNum::operator>(LongNum &second)
{
    if (sign > second.sign)
        return true;
    if (sign < second.sign)
        return false;
    if (number.size() > second.size())
        return sign;
    if (number.size() < second.size())
        return !sign;
    for (int i = number.size() - 1; i >= 0; --i)
    {
        if (number[i] > second[i])
            return sign;
        if (number[i] < second[i])
            return !sign;
    }
    return false;
}

bool LongNum::operator>=(LongNum &second)
{
    return !(*this < second);
}

bool LongNum::operator<(LongNum &second)
{
    if (sign > second.sign)
        return false;
    if (sign < second.sign)
        return true;
    if (number.size() < second.size())
        return sign;
    if (number.size() > second.size())
        return !sign;
    for (int i = number.size() - 1; i >= 0; --i)
    {
        if (number[i] < second[i])
            return sign;
        if (number[i] > second[i])
            return !sign;
    }
    return false;
}

bool LongNum::operator<=(LongNum &second)
{
    return !(*this > second);
}

LongNum LongNum::delete_lead_zeros(LongNum &num)
{
    while (*num.number.rbegin() == 0)
    {
        num.number.pop_back();
    }
    return num;
}