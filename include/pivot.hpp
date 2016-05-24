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

#pragma push_macro("USE_WCHAR")
#ifndef USE_WCHAR
#if defined(_MSC_VER)\
|| defined(WCHAR)\
|| defined(UNICODE)\
|| defined(_XSTRING_)\
|| defined(__ATLSTR_H__)
# define USE_WCHAR
#endif
#endif // USE_WCHAR

#pragma push_macro("_PIVOT_LIST")
#pragma push_macro("_PIVOT_VECTOR")
#pragma push_macro("_PIVOT_STRING")

#if defined(_GLIBCXX_LIST) || defined(_LIST_)
#define _PIVOT_LIST
#endif // _GLIBCXX_LIST || _LIST_

#if defined(_GLIBCXX_VECTOR) || defined(_VECTOR_)
#define _PIVOT_VECTOR
#endif // _GLIBCXX_VECTOR || _VECTOR_

#if defined(_GLIBCXX_STRING) || defined(_STRING_)
#define _PIVOT_STRING
#endif // _GLIBCXX_STRING || _STRING_

namespace pivot {
using namespace std;

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
		_This _Myfirst;

		template<class _Tag, class _This2, class... _Rest2>
		constexpr pivot(_Tag
				, _This2&& _This_arg
				, _Rest2&&... _Rest_arg)
			: _Mybase(_Exact_args_t{}
				, forward<_Rest2>(_Rest_arg)...)
				,_Myfirst(forward<_This2>(_This_arg))
		{ }

		template<class _This2 = _This>
		constexpr pivot(const _This& _This_arg
				, const _Rest&... _Rest_arg)
			: _Mybase(_Exact_args_t{}, _Rest_arg...)
				, _Myfirst(_This_arg)
		{ }

		template <typename T>
		inline _Myt& operator=(const T _Right[])
		{
			_Myfirst = _Right[0];
			assign(_Get_rest(), ++_Right);
			return (*this);
		}

#if defined(_PIVOT_LIST) && defined(_PIVOT_STRING)
		inline _Myt& operator=(const list<string>& _Right)
		{
			assigncstr(_Right);
			return (*this);
		}
#ifdef USE_WCHAR
		inline _Myt& operator=(const list<wstring>& _Right)
		{
			assigncstr(_Right);
			return (*this);
		}
#endif // USE_WCHAR
#endif // _PIVOT_LIST && _PIVOT_STRING
#if defined(_PIVOT_VECTOR) && defined(_PIVOT_STRING)
		inline _Myt& operator=(const vector<string>& _Right)
		{
			assigncstr(_Right);
			return (*this);
		}
#ifdef USE_WCHAR
		inline _Myt& operator=(const vector<wstring>& _Right)
		{
			assigncstr(_Right);
			return (*this);
		}
#endif // USE_WCHAR
#endif // _PIVOT_VECTOR && _PIVOT_STRING
#if defined(_PIVOT_LIST)
		template <class T> inline
		_Myt& operator=(const list<T>& _Right)
		{
			assign(_Right);
			return (*this);
		}
#endif //_PIVOT_LIST
#if defined(_PIVOT_VECTOR)
		template <class T> inline
		_Myt& operator=(const vector<T>& _Right)
		{			
			assign(_Right);
			return (*this);
		}
#endif // _PIVOT_VECTOR
		constexpr const _Mybase& _Get_rest() const noexcept
		{
			return (*this);
		}
	private:
		template <class T> inline
			void assigncstr(const T& _Right)
		{
			typedef typename T::const_iterator const_iterator;
			const_iterator it = _Right.cbegin();
			const_iterator cend = _Right.cend();

			if (it != cend)
			{
				_Myfirst = it->c_str();
				assigncstr(_Get_rest(), ++it, cend);
			}
		}
		template <class _Mybase2, class T> inline
		void assigncstr(const _Mybase2& _Left, T it, const T cend)
		{
			if (it == cend) return;
			_Left._Myfirst = it->c_str();
			assigncstr(_Left._Get_rest(), ++it, cend);
		}
		template <class T> inline
		void assigncstr(const pivot<>&, T, const T) { }
		
		template <class T> inline
		void assign(const T& _Right)
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
		void assign(const _Mybase2& _Left, T it, const T cend)
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
#pragma pop_macro("USE_WCHAR")
#pragma pop_macro("_PIVOT_STRING")
#pragma pop_macro("_PIVOT_VECTOR")
#pragma pop_macro("_PIVOT_LIST")
#endif // _PIVOT_
