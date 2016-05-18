/*
Simple Operators for C++0x(SOPS) v0.1
Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.

*/
#ifndef _SOPS_H_
#define _SOPS_H_

#if !defined(__GXX_EXPERIMENTAL_CXX0X__) && _MSC_VER < 1600
#error "Require C++0x or above"
#endif

#ifdef __cplusplus
template <typename T1, typename T2>
class SBetweenOperator
{
private:
	T1 m_start;
	T2 m_end;
public:
	inline SBetweenOperator(T1 start, T2 end)
	{
		m_start = start;
		m_end = end;
	}
	template <typename T>
	inline bool Compare(T num)
	{
		return m_start <= num && num <= m_end;
	}
};

template <typename T>
inline bool operator ==(T num, SBetweenOperator<T, T> se) {
	return se.Compare(num);
}

template <typename T>
inline bool operator !=(T num, SBetweenOperator<T, T> se) {
	return !se.Compare(num);
}
#define sbetween(s,e) == SBetweenOperator<decltype(s), decltype(e)>(s,e)
#define not_sbetween(s,e) != SBetweenOperator<decltype(s), decltype(e)>(s,e)
#ifndef between
# define between sbetween
# define not_between not_sbetween
#endif //!between

#else // !__cplusplus
#endif // !__cplusplus
#endif // !_SOPS_H_