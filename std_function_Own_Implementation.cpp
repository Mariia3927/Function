#include "pch.h"
#include <iostream>

void func()
{
	std::cout << "func" << std::endl;
}

struct Functor
{
	void operator() () const
	{
		std::cout << "functor" << std::endl;
	}
};

class F
{
public:
	void operator() ()
	{
		func();
	}
private:
	void func()
	{
		std::cout << "class function" << std::endl;
	}
};

int main()
{
	Function<void(void)> function;
	function = func;
	function();

	Functor functorObj;
	function = functorObj;
	function();

	function = []() { std::cout << "lambda" << std::endl; };
	function();

	F f;
	function = f;
	function();

	Function<void(void)> anotherFunction(f);
	anotherFunction();
}

