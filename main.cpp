#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class BigInt
{
public:
	explicit BigInt(const std::string& n) 
	{
		for (auto it = n.rbegin(); it != n.rend(); ++it)
		{
			number.push_back(*it - '0');
		}
	}
	friend std::ostream& operator << (std::ostream& out, const BigInt& n);
	friend BigInt operator + (const BigInt& a, const BigInt& b);
private:
	BigInt(std::vector<int> number)
	{
		this->number = std::move(number);
	}
	std::vector<int> number;
};

BigInt operator + (const BigInt& a, const BigInt& b)
{
	std::vector<int> result;
	int carry = 0;
	if (a.number.size() >= b.number.size())
	{
		result.reserve(a.number.size() + 1);
		for (size_t i = 0; i < b.number.size(); ++i)
		{
			int sum = a.number[i] + b.number[i] + carry;
			if(sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result.push_back(sum);
		}
		for (size_t i = 0; i < a.number.size() - b.number.size(); ++i)
		{
			int sum = a.number[i + b.number.size()] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result.push_back(sum);
		}
	}
	else
	{
		result.reserve(b.number.size() + 1);
		for (size_t i = 0; i < a.number.size(); ++i)
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
			result.push_back(sum);
		}
		for (size_t i = 0; i < b.number.size() - a.number.size(); ++i)
		{
			int sum = b.number[i + a.number.size()] + carry;
			if (sum > 9)
			{
				carry = 1;
				sum -= 10;
			}
			else
			{
				carry = 0;
			}
			result.push_back(sum);
		}
	}
	if (carry)
	{
		result.push_back(1);
	}
	return result;
}
/*
BigInt operator * (const BigInt& a, const BigInt& b)
{
	std::string result = "0", t_res;
	for (int i = 1; i <= b.length(); i++)
	{
		int l = b[b.length() - i];
		t_res = "0";
		for (int i1 = '0'; i1 < l; i1++)
		{
			t_res = addition(a, t_res);
		}
		result = addition(result, t_res);
		a = a + "0";
	}
	return	result;
}
*/

std::ostream& operator << (std::ostream& out, const BigInt& n)
{
	for (auto it = n.number.rbegin(); it != n.number.rend(); ++it)
	{
		out << *it;
	}
	return out;
}

BigInt fibonacci(int n)
{
	BigInt a("0");
	BigInt b("1");
	BigInt c("0");
	for (int i = 1; i < n; ++i)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

int main()
{
	auto time_begin = std::chrono::high_resolution_clock::now();
	BigInt f = fibonacci(500000);
	auto time_end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count() << std::endl;
	std::cout << f << std::endl;
	return 0;
}
