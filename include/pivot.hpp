/*
Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.
guruwand at gmail dot com
*/

#pragma once
#ifndef _PIVOT_
#define _PIVOT_

#if !defined(__cpp_variadic_templates)\
	&& !defined(_HAS_VARIADIC_TEMPLATES)
#error Require variadic templates feature.
#endif // !_HAS_VARIADIC_TEMPLATES

namespace pivot {
using namespace std;

template<class _Ty>
struct _Tuple_val
{
private:
	template <typename T>
	struct has_c_str_fn
	{
		typedef char(&yes)[1];
		typedef char(&no)[2];

		template <typename C> static yes check(decltype(&C::c_str));
		template <typename> static no check(...);

		static bool const value = sizeof(check<T>(0)) == sizeof(yes);
	};
	template <typename T>
	struct has_GetString_fn
	{
		typedef char(&yes)[1];
		typedef char(&no)[2];

		template <typename C> static yes check(decltype(&C::GetString));
		template <typename> static no check(...);

		static bool const value = sizeof(check<T>(0)) == sizeof(yes);
	};
public:
	template<class _Other> inline
	_CONST_FUN _Tuple_val(_Other&& _Arg)
		: _Val(_STD forward<_Other>(_Arg))
	{ }
	
	template <typename T, typename = enable_if_t<has_c_str_fn<T>::value>>
	inline _Tuple_val& operator=(const T& _Right)
	{
		_Val = _Right.c_str();
		return (*this);
	}

	template <typename T, typename = enable_if_t<has_GetString_fn<T>::value>>
	inline _Tuple_val& operator=(const T&& _Right)
	{
		_Val = _Right.GetString();
		return (*this);
	}
	
	template<typename _Other> inline
	_Tuple_val& operator=(_Other&& _Right)
	{
		_Val = forward<_Other>(_Right);
		return (*this);
	}
	_Ty _Val;
};

struct _Exact_args_t{};

	template<class... _Types>
	class pivot;

	template<>
	class pivot<>
	{
	public:
		template<class _Tag>
		constexpr pivot(_Tag) noexcept { }
	};

	template<class _This, class... _Rest>
	class pivot<_This, _Rest...>
		: private pivot<_Rest...>
	{
	public:
		typedef pivot<_This, _Rest...> _Myt;
		typedef pivot<_Rest...> _Mybase;
		mutable _Tuple_val<_This> _Myfirst;

		template<class _Tag, class _This2, class... _Rest2> inline
		constexpr pivot(_Tag
				, _This2&& _This_arg
				, _Rest2&&... _Rest_arg)
			: _Mybase(_Exact_args_t{}
				, forward<_Rest2>(_Rest_arg)...)
				, _Myfirst(forward<_This2>(_This_arg))
		{ }

		template<class _This2 = _This> inline
		constexpr pivot(const _This& _This_arg
				, const _Rest&... _Rest_arg)
			: _Mybase(_Exact_args_t{}, _Rest_arg...)
				, _Myfirst(_This_arg)
		{ }
		
		template <typename T> inline
		_Myt& operator=(const T _Right[])
		{
			_Myfirst = _Right[0];
			assign(_Get_rest(), ++_Right);
			return (*this);
		}
		
		template <class T> inline
			_Myt& operator=(const T& _Right)
		{
			assign(_Right);
			return (*this);
		}

		constexpr const _Mybase& _Get_rest() const noexcept
		{
			return (*this);
		}
	private:
		template <class T> inline
		void assign(T& _Right)
		{
			typedef typename T::const_iterator const_iterator;
			const_iterator it = _Right.cbegin();
			const_iterator cend = _Right.cend();
			if (it != cend)
			{
				_Myfirst = *it;
				assign(_Get_rest(), ++it, cend);
			}
		}

		template <class _Mybase2, class T> inline
		void assign(_Mybase2& _Left, T it, const T cend)
		{
			if (it == cend) return;
			_Left._Myfirst = *it;
			assign(_Left._Get_rest(), ++it, cend);
		}
		template <class T> inline
		void assign(const pivot<>&, T, const T) {}


		template <class _Mybase2, typename T> inline
			void assign(const _Mybase2& _Left, const T _Right[])
		{
			_Left._Myfirst = _Right[0];
			assign(_Left._Get_rest(), ++_Right);
		}
		template <typename T> inline
		void assign(const pivot<>&, const T[]) {}
	};
	template<typename... _Types> inline
	constexpr pivot<_Types&...>
	tie(_Types&... __args) noexcept
	{
		return pivot<_Types&...>(__args...);
	}
}
#endif // _PIVOT_
