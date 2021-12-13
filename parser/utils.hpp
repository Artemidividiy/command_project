#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <iostream>
#include <map>
#include <regex>

#define DivisionException invalid_argument("Division by zero")

using namespace std;
static map<int, string> priority_map = {{1, "+-"}, {2, "*/"}, {3, "()"}};

struct ICalculatable
{
	virtual float calculate(float x) const = 0;
	virtual ~ICalculatable() = default;
};

using ICalculatableUPtr = std::unique_ptr<ICalculatable>;

class Scalar : public ICalculatable
{
public:
	Scalar(float value)
		: value_{value} {}

	float calculate(float x) const override
	{
		return value_;
	}

private:
  	float value_;
};

class X : public ICalculatable
{
public:
	float calculate(float x) const override
	{
		return x;
	}
};

class BinaryOperator : public ICalculatable
{
public:
	BinaryOperator(ICalculatableUPtr left, ICalculatableUPtr right)
					: left_{std::move(left)},
					right_{std::move(right)}
	{}

	float calculate(float x) const override
	{
		return calculate(left_->calculate(x), right_->calculate(x));
	}

	virtual float calculate(float left, float right) const = 0;

private:
	ICalculatableUPtr left_;
	ICalculatableUPtr right_;
};

class SubtractionOperator: public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	using BinaryOperator::calculate;

	float calculate(float left, float right) const override
	{
		return left - right;
	}

};

class SumOperator: public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	using BinaryOperator::calculate;

	float calculate(float left, float right) const override
	{
		return left + right;
	}

};

class MultiOperator: public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	using BinaryOperator::calculate;

	float calculate(float left, float right) const override
	{
		return left * right;
	}

};

class DivideOperator: public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	using BinaryOperator::calculate;

	float calculate(float left, float right) const override
	{
		if (right)
			return left / right;
		else{
			throw DivisionException;
		}
	}

};

double binary_search(double a, double b, int n, double (*func)(double x));
void find_closest_pos(const std::map<int, std::unique_ptr<ICalculatable>> &calc_map, const int pos, int& closest_right);
std::unique_ptr<ICalculatable> extract(std::map<int, std::unique_ptr<ICalculatable>>& mp, int pos);
bool is_less_priority(char operation, char next_operation);
sregex_iterator find_its_closing_bracket(sregex_iterator it, string s);
string string_inside_brackets(sregex_iterator it, sregex_iterator it_bracket_end, string s);
sregex_iterator find_end_of_subf(sregex_iterator it, string s);
string string_subf(sregex_iterator it, sregex_iterator it_end_of_subf, string s);

#endif // UTILS_HPP