#include <iostream>
#include <vector>
#include <string>
using namespace std;

#if _M_X64
 typedef __int64 int_t;
 constexpr __int64 NUMBER = 999'999'999'999'999'999;
 constexpr __int64 NUMBER2 = 1'000'000'000'000'000'000;
 constexpr __int32 LENGTH = 18;
#else
 typedef __int32 int_t;
 constexpr __int32 NUMBER = 999'999'999;
 constexpr __int32 NUMBER2 = 1'000'000'000;
 constexpr __int32 LENGTH = 9;
#endif

class BigInteger
{
public:
	BigInteger(const string& s) 
	{
		int count = 0;
		int_t shift = 1;
		int_t sum = 0;
		for (auto it = s.rbegin(); it != s.rend(); ++it)
		{
			sum += (*it - '0') * shift;
			++count;
			shift *= 10;
			if (count == LENGTH)
			{
				v.push_back(sum);
				count = 0;
				shift = 1;
				sum = 0;
			}
		}
		if (count)
		{
			v.push_back(sum);
		}
	}
private:
	friend std::ostream& operator << (std::ostream& out, const BigInteger& b);
	friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
	BigInteger(std::vector<int_t>& v)
	{
		this->v = std::move(v);
	}
	vector<int_t> v;
};

BigInteger operator + (const BigInteger& a, const BigInteger& b)
{
	size_t carry = 0, aSize = a.v.size(), bSize = b.v.size();
	vector<int_t> vRes(aSize > bSize ? aSize : bSize);
	if (aSize > bSize)
	{
		for (int i = 0; i < bSize; ++i)
		{
			int_t sum = a.v[i] + b.v[i] + carry;
			if (sum > NUMBER)
			{
				sum -= NUMBER2;
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			vRes[i] = sum;
		}
		for (size_t i = bSize; i < aSize; ++i)
		{
			int_t sum = a.v[i] + carry;
			if (sum > NUMBER)
			{
				carry = 1;
				sum -= NUMBER2;
			}
			else
			{
				carry = 0;
			}
			vRes[i] = sum;
		}

	}
	else
	{
		for (size_t i = 0; i < aSize; ++i)
		{
			int_t sum = a.v[i] + b.v[i] + carry;
			if (sum > NUMBER)
			{
				carry = 1;
				sum -= NUMBER2;
			}
			else
			{
				carry = 0;
			}
			vRes[i] = sum;
		}
		for (size_t i = aSize; i < bSize; ++i)
		{
			int_t sum = b.v[i] + carry;
			if (sum > NUMBER)
			{
				carry = 1;
				sum -= NUMBER2;
			}
			else
			{
				carry = 0;
			}
			vRes[i] = sum;
		}
	}
	if (carry)
	{
		vRes.push_back(1);
	}
	return vRes;
}

std::ostream& operator << (std::ostream& out, const BigInteger& b)
{
	for (auto it = b.v.rbegin(); it != b.v.rend(); ++it)
	{
		std::string s = std::to_string(*it);
		if (s.length() < LENGTH && it != b.v.rbegin())
		{
			out << std::string(LENGTH - s.length(), '0');
		}
		out << s;
	}
	return out;
}

BigInteger fibonacci(int n)
{
	BigInteger a("0");
	BigInteger b("1");
	BigInteger c("0");
	for (int i = 1; i < n; ++i)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
