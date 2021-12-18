#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <iostream>
#include <map>
#include <regex>
#include <math.h>

using std::map;
using std::make_pair;
using std::string;
using std::invalid_argument;
using std::regex;
using std::sregex_iterator;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::smatch;

#define DefaultException invalid_argument("Something went wrong")
#define DivisionException invalid_argument("Division by zero")
#define RootFromNegativeException invalid_argument("Root from negative number")

#define END_OF_STRING -1
#define MINUS 1
#define PLUS 2
#define MULTIPLY 10
#define DIVIDE 11
#define SQRT 20
#define COS 21
#define SIN 22
#define BRACKET 30
#define CLOSED_BRACKET 31

static map<string, int> operations_map = {{"+", PLUS}, {"-", MINUS}, {"*", MULTIPLY}, {"/", DIVIDE}, 
                                   {"sqrt", SQRT}, {"sin", SIN}, {"cos", COS}, {"(", BRACKET},{")", CLOSED_BRACKET},
                                   {"\0", END_OF_STRING}};

struct ICalculatable
{
	virtual float calculate(float x) const = 0;
	virtual ~ICalculatable() = default;
};

using ICalculatableUPtr = unique_ptr<ICalculatable>;

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
	{
		if ((left == nullptr) || (right == nullptr))
			throw DefaultException;
		else{
			left_ = move(left);
			right_ = move(right);
		}
	}

	float calculate(float x) const override
	{
		return calculate(left_->calculate(x), right_->calculate(x));
	}

	virtual float calculate(float left, float right) const = 0;

private:
	ICalculatableUPtr left_;
	ICalculatableUPtr right_;
};

class UnaryOperator : public ICalculatable
{
public:
	UnaryOperator(ICalculatableUPtr ptr_to_calculate_)
	{
		if (!ptr_to_calculate_)
			throw DefaultException;
		else
			ptr_to_calculate = move(ptr_to_calculate_);
	}

	virtual float calculate(float x) const  = 0;

protected:
	ICalculatableUPtr ptr_to_calculate;
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

class Sqrt : public UnaryOperator
{
public:
	using UnaryOperator::UnaryOperator;
	using UnaryOperator::calculate;

	float calculate(float x) const override
	{	
		float argument = ptr_to_calculate->calculate(x);
		if(argument >= 0)
			return pow(argument, 0.5);
		else
			throw RootFromNegativeException;		
	}
};

class Sin : public UnaryOperator
{
public:
	using UnaryOperator::UnaryOperator;
	using UnaryOperator::calculate;

	float calculate(float x) const override
	{	
		return sin(ptr_to_calculate->calculate(x));		
	}
};

class Cos : public UnaryOperator
{
public:
	using UnaryOperator::UnaryOperator;
	using UnaryOperator::calculate;

	float calculate(float x) const override
	{	
		return cos(ptr_to_calculate->calculate(x));		
	}
};

void find_closest_pos(const std::map<int, std::unique_ptr<ICalculatable>> &calc_map, const int pos, int& closest_right);
unique_ptr<ICalculatable> extract(std::map<int, unique_ptr<ICalculatable>>& mp, int pos);
bool is_less_priority(int operation_key, int next_operation_key);
sregex_iterator find_its_closing_bracket(sregex_iterator it, string s);
string string_inside_brackets(sregex_iterator it, sregex_iterator it_bracket_end, string s);
sregex_iterator find_end_of_subf(sregex_iterator it, string s);
string string_subf(sregex_iterator it, sregex_iterator it_end_of_subf, string s);

#endif // UTILS_HPP