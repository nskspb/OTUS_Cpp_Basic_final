#pragma once

#include <iostream>
#include <vector>

class LongNum
{
private:
    std::vector<int> number;
    bool sign;

public:
    LongNum();
    LongNum(std::vector<int> &vec, bool sig);
    LongNum(std::string &str);
    LongNum(long long n);
    ~LongNum();

    size_t size() const;
    bool isOne() const;
    bool isZero() const;

    LongNum &operator=(const LongNum &other);
    LongNum &operator=(int &other);

    friend std::ostream &operator<<(std::ostream &out, const LongNum &num);
    int &operator[](int position);

    LongNum operator+(const LongNum &num);
    LongNum operator-(const LongNum &num);
    LongNum operator*(const LongNum &num);
    friend LongNum mult(const LongNum &firstNum, const LongNum &num);
    friend LongNum KaratsubaAlg(const LongNum &firstNum, const LongNum &secondNum);
    LongNum operator/(const LongNum &num);
    LongNum operator-();
    LongNum operator%(const LongNum &num);
    LongNum operator+=(const LongNum &num);
    LongNum operator-=(const LongNum &num);
    LongNum operator*=(const LongNum &num);
    LongNum operator/=(const LongNum &num);
    friend LongNum pow(const LongNum &firstNum, const LongNum &secondNum);

    bool operator==(LongNum &second);
    bool operator!=(LongNum &second);
    bool operator>(LongNum &second);
    bool operator>=(LongNum &second);
    bool operator<(LongNum &second);
    bool operator<=(LongNum &second);

    friend LongNum delete_lead_zeros(LongNum &num);
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

LongNum::LongNum(long long n)
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

bool LongNum::isOne() const
{
    if ((number.size() == 1) and (number[0] == 1) and (sign == true))
    {
        return true;
    }
    return false;
}

bool LongNum::isZero() const
{
    if ((number.size() == 1) and (number[0] == 0))
    {
        return true;
    }
    return false;
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
    LongNum res(0);
    res = KaratsubaAlg(*this, num);
    return res;
}

LongNum mult(const LongNum &firstNum, const LongNum &num)
{
    LongNum first = firstNum;
    LongNum second = num;
    first.sign = true;
    second.sign = true;
    LongNum res(0);
    if ((first.isZero()) || (second.isZero()))
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
    res.sign = !(firstNum.sign ^ num.sign);
    return res;
}

LongNum KaratsubaAlg(const LongNum &firstNum, const LongNum &secondNum)
{
    LongNum first = firstNum;
    LongNum second = secondNum;
    LongNum res(0);

    if ((first.size() < 10) or (second.size() < 10))
    {
        res = mult(first, second);
        return res;
    }

    auto base = std::max(first.size(), second.size());
    auto halfbase = base / 2;
    LongNum A = first / pow(LongNum(10), halfbase);
    LongNum B = first % pow(LongNum(10), halfbase);
    LongNum C = second / pow(LongNum(10), halfbase);
    LongNum D = second % pow(LongNum(10), halfbase);

    LongNum AC = KaratsubaAlg(A, C);
    LongNum BD = KaratsubaAlg(B, D);
    LongNum Plus = KaratsubaAlg(A + B, C + D) - AC - BD;

    res = mult(AC, pow(LongNum(10), halfbase * 2)) + mult(Plus, pow(LongNum(10), halfbase)) + BD;
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
        if (second.isZero())
        {
            throw std::runtime_error("ERROR: division by zero!");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        return LongNum(0);
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

LongNum LongNum::operator%(const LongNum &num)
{
    LongNum buf = *this / num;
    return *this - buf * num;
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

LongNum pow(const LongNum &firstNum, const LongNum &secondNum)
{
    LongNum res(0);

    LongNum first = firstNum;
    LongNum second = secondNum;

    try
    {
        if (!secondNum.sign)
        {
            throw std::runtime_error("Let the power will be positive!");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        return LongNum(0);
    }

    if (second.isZero())
    {
        return LongNum(1);
    }

    if (second.isOne())
    {
        return firstNum;
    }

    if (first.isZero())
    {
        return LongNum(0);
    }

    if (first.isOne())
    {
        return LongNum(1);
    }

    res = pow(first * first, second / 2);

    if (second.number[0] % 2 == 1)
    {
        res *= first;
    }
    return res;
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

bool LongNum::operator!=(LongNum &second)
{
    LongNum first = *this;

    return !(first == second);
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

LongNum delete_lead_zeros(LongNum &num)
{
    if ((num.number[0] == 0) and (num.size() == 1))
    {
        return num;
    }

    while (*num.number.rbegin() == 0)
    {
        num.number.pop_back();
    }
    return num;
}