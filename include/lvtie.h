/*
Implement tie for list and vector.

Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.
guruwand at gmail dot com
*/

#pragma once
#ifndef _LVTIE_
#define _LVTIE_
#include <tuple>
namespace lv {
	using namespace std;
	template<class _This, class... _Rest>
	class lvtuple : private tuple<_This, _Rest...>
	{
	public:
		template<class... T> inline explicit
		lvtuple(T&... args) : tuple<T&...>(args...) {}

		template <class T> inline
		 _Myt& operator=(const list<T>& _Right)
		{
			typedef list<T>::const_iterator const_iterator;
			const_iterator it = _Right.cbegin();
			const_iterator cend = _Right.cend();
			if (it != cend)
			{
				_Myfirst._Val = *it;
				assign(_Get_rest(), ++it, cend);
			}
			return (*this);
		}
		template <class T> inline
		_Myt& operator=(const vector<T>& _Right)
		{
			typedef vector<T>::const_iterator const_iterator;
			const_iterator it = _Right.cbegin();
			const_iterator cend = _Right.cend();
			if (it != cend)
			{
				_Myfirst._Val = *it;
				assign(_Get_rest(), ++it, cend);
			}
			return (*this);
		}

	private:
		template <class _Mybase2, class T> inline
		void assign(const _Mybase2& _Left, T it, T cend)
		{
			if (it == cend) return;
			_Left._Myfirst._Val = *it;
			assign(_Left._Get_rest(), ++it, cend);
		}
		template <class T> inline
		void assign(const tuple<>&, T, T) {}
	};

	template<class... _Types> inline
		_CONST_FUN lvtuple<_Types&...>
		tie(_Types&... _Args) _NOEXCEPT
	{
		typedef lvtuple<_Types&...> _Ttype;
		return (_Ttype(_Args...));
	}
}
#endif // _LVTIE_