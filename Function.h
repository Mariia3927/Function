#pragma once
#include "pch.h"

template <typename T>
class Function;

template <typename ReturnValue, typename... Args>
class Function<ReturnValue(Args...)>
{
public:

	Function() {}
	template<typename T>
	Function(const T& t) : m_function(std::make_unique< Callable<T> >(t)) {}

	template <typename T>
	Function& operator=(T t)
	{
		m_function = std::make_unique< Callable<T> >(t);
		return *this;
	}

	ReturnValue operator() (Args... args) const
	{
		assert(m_function);
		return m_function->Invoke(args...);
	}

private:
	class ICallable 
	{
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) = 0;
	};

	template <typename T>
	class Callable : public ICallable
	{
	public:
		Callable(const T& t) : m_callable(t) { }
		~Callable() override = default;

		ReturnValue Invoke(Args... args) override { return m_callable(args...); }
	private:
		T m_callable;
	};

	std::unique_ptr<ICallable> m_function;
};



