#include <iostream>
#include <vector>

class BigInteger
{
public:
	explicit BigInteger(const std::string& n)
	{
		for (auto it = n.rbegin(); it != n.rend(); ++it)
		{
			number.push_back(*it - '0');
		}
	}
	friend std::ostream& operator << (std::ostream& out, const BigInteger& n);
	friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
private:
	BigInteger(std::vector<int> number)
	{
		this->number = std::move(number);
	}
	std::vector<int> number;
};

BigInteger operator + (const BigInteger& a, const BigInteger& b)
{
	int carry = 0, aSize = a.number.size(), bSize = b.number.size();
	std::vector<int> result(aSize > bSize ? aSize : bSize);
	
	if (aSize > bSize)
	{
		for (size_t i = 0; i < bSize; ++i)
		{
			int sum = a.number[i] + b.number[i] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result[i] = sum;
		}
		for (size_t i = bSize; i < aSize; ++i)
		{
			int sum = a.number[i] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result[i] = sum;
		}
	}
	else
	{
		for (size_t i = 0; i < aSize; ++i)
		{
			int sum = a.number[i] + b.number[i] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result[i] = sum;
		}
		for (size_t i = aSize; i < bSize; ++i)
		{
			int sum = b.number[i] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result[i] = sum;
		}
	}
	if (carry)
	{
		result.push_back(1);
	}
	return result;
}


std::ostream& operator << (std::ostream& out, const BigInteger& n)
{
	for (auto it = n.number.rbegin(); it != n.number.rend(); ++it)
	{
		out << *it;
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
