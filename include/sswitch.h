/*
S Switch for C++(SSWitch) v0.1
Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.

guruwand at gmail dot com
*/
#ifndef _SSWITCH_H_
#define _SSWITCH_H_
#include <string.h>
#include <stdarg.h>

#pragma push_macro("USE_SW_WCHAR")
#ifndef USE_SW_WCHAR
#if defined(_MSC_VER)\
|| defined(WCHAR)\
|| defined(UNICODE)\
|| defined(_XSTRING_)\
|| defined(__ATLSTR_H__)
# define USE_SW_WCHAR
#endif // 
#endif // USE_SW_WCHAR

#ifdef __cplusplus
#ifdef __INTELLISENSE__
//  Accelerate intellisense
# define Switch(swv)					{ switch(__COUNTER__)
# define Case(v)						case __COUNTER__
# define Case_Not(v)					case __COUNTER__

# define Case_Greater(n)				case __COUNTER__
# define Case_GreaterEqual(n)			case __COUNTER__
# define Case_Less(n)					case __COUNTER__
# define Case_LessEqual(n)				case __COUNTER__

# define Case_BitOr(i)					case __COUNTER__
# define Case_BitAnd(i)					case __COUNTER__

# define Case_Or(b)						case __COUNTER__
# define Case_And(b)					case __COUNTER__

# define Case_Between(nStart, nEnd)		case __COUNTER__
# define Case_Not_Between(nStart, nEnd)	case __COUNTER__

# define Case_In(v1, ...)				case __COUNTER__
# define Case_Not_In(v1, ...)			case __COUNTER__
# define Case_InNCmp(argc, v1, ...)		case __COUNTER__
# define Case_Not_InNCmp(argc, v1, ...)	case __COUNTER__

# define Case_Else						case __COUNTER__
# define Case_Null						case __COUNTER__
# define Case_Not_Null					case __COUNTER__
# define Case_Empty						case __COUNTER__
# define Case_Not_Empty					case __COUNTER__
#if(0)
# define Case_Like(pstr)				case __COUNTER__
# define Case_Not_Like(pstr)			case __COUNTER__
# define Case_RegExp(pstr)				case __COUNTER__
# define Case_Not_RegExp(pstr)			case __COUNTER__
#endif 
#define Default							default
# define End_SwitchC					}
# define End_Switch						}
#endif

#pragma push_macro("DEPRECATED")
#ifdef _MSC_VER
# undef DEPRECATED
# define DEPRECATED(msg)			__declspec(deprecated(msg))
#else // !_MSC_VER
# define DEPRECATED(msg)			__attribute__((deprecated(msg)))
#endif // !_MSC_VER

class __SSCmp_
{
private:
	inline __SSCmp_(__SSCmp_& v){}
protected:
	union {
		const void* lpcStr;
		int iNum;
		long long llNum;
		float fNum;
		double dNum;
	} m_val;
	enum {
		TYPE_UNKNOWN
		, TYPE_INT
		, TYPE_LONGLONG
		, TYPE_FLOAT
		, TYPE_DOUBLE
		, TYPE_LPCSTR
		, TYPE_LPCWSTR
	} type;
public:
#pragma push_macro("TYPEINIT")
#undef TYPEINIT
#define TYPEINIT(TYPE, VAL) type = TYPE;m_val.VAL = v
	inline __SSCmp_(const int v) { TYPEINIT(TYPE_INT, iNum); }
	inline __SSCmp_(const long long v) { TYPEINIT(TYPE_LONGLONG, llNum); }
	inline __SSCmp_(const float v) { TYPEINIT(TYPE_FLOAT, fNum); }
	inline __SSCmp_(const double v) { TYPEINIT(TYPE_DOUBLE, dNum); }
	inline __SSCmp_(const char* v) { TYPEINIT(TYPE_LPCSTR, lpcStr); }
#ifdef USE_SW_WCHAR
	inline __SSCmp_(const wchar_t* v) { TYPEINIT(TYPE_LPCWSTR, lpcStr); }
#endif // USE_SW_WCHAR
#pragma pop_macro("TYPEINIT")

	inline bool Null() const
	{
		bool b;
		if (type == TYPE_LPCSTR) b = (m_val.lpcStr == NULL);
		else if (type == TYPE_LPCWSTR) b = (m_val.lpcStr == NULL);
		else b = false;
		return b;
	}
	inline bool Empty() const
	{
		bool b;
		if (m_val.lpcStr == NULL) b = false;
		else if (type == TYPE_LPCSTR)
			b = (*((const char*)m_val.lpcStr) == (const char)NULL);
		else if (type == TYPE_LPCWSTR)
			b =  (*((const wchar_t*)m_val.lpcStr) == (const wchar_t )NULL);
		else b = false;
		return b;
	}
	inline bool Equal(const char* s) const
	{
		bool b;
		if (type != TYPE_LPCSTR) b = false;
		else if (m_val.lpcStr == s) b = true;
		else if (m_val.lpcStr == NULL || s == NULL) b = false;
		else {
			const char* lpcStr = (const char*)m_val.lpcStr;
			b = strcmp(lpcStr, s) == 0;
		}
		return b;
	}
#if defined(USE_SW_WCHAR)
	inline bool Equal(const wchar_t* s) const
	{
		bool b;
		if (type != TYPE_LPCWSTR) b = false;
		else if (m_val.lpcStr == s) b = true;
		else if (m_val.lpcStr == NULL || s == NULL) b = false;
		else {
			const wchar_t* lpcStr = (const wchar_t*)m_val.lpcStr;
			b = wcscmp(lpcStr, s) == 0;
		}
		return b;
	}
#endif // USE_SW_WCHAR

#pragma push_macro("CMPSWTYPE")
#undef CMPSWTYPE
#define CMPSWTYPE(OP)\
bool b;\
if(type == TYPE_INT) b = (m_val.iNum OP v);\
else if(type == TYPE_LONGLONG) b = (m_val.llNum OP v);\
else if(type == TYPE_FLOAT) b = (m_val.fNum OP v);\
else if(type == TYPE_DOUBLE) b = (m_val.dNum OP v);\
else b = false;\
return b
	template <typename T1>
	inline bool Equal(const T1 v) const { CMPSWTYPE(== ); }
	template <typename T1>
	inline bool Greater(const T1 v) const { CMPSWTYPE(> ); }
	template <typename T1>
	inline bool GreaterEqual(const T1 v) const { CMPSWTYPE(>= ); }
	template <typename T1>
	inline bool Less(const T1 v) const { CMPSWTYPE(< ); }
	template <typename T1>
	inline bool LessEqual(const T1 v) const { CMPSWTYPE(<= ); }
	template <typename T1>
	inline bool BitOr(const T1 v) const { CMPSWTYPE(| ); }
	template <typename T1>
	inline bool BitAnd(const T1 v) const { CMPSWTYPE(&); }
	inline bool Or(const bool v) const { CMPSWTYPE(|| ); }
	inline bool And(const bool v) const { CMPSWTYPE(&&); }
#pragma pop_macro("CMPSWTYPE")

#pragma push_macro("BETWEEN")
#undef BETWEEN
#define BETWEEN(exp, s,e)		((s <= (exp)) && ((exp) <= e))
	template <typename T1, typename T2>
	inline bool Between(const T1 s, const T2 e) const
	{
		bool b;
		if (type == TYPE_INT) 
			b = BETWEEN(m_val.iNum, s, e);
		else if (type == TYPE_LONGLONG)
			b = BETWEEN(m_val.llNum, s, e);
		else if (type == TYPE_FLOAT)
			b = BETWEEN(m_val.fNum, s, e);
		else if (type == TYPE_DOUBLE)
			b = BETWEEN(m_val.dNum, s, e);
		else b = false;
		return b;
	}
#pragma pop_macro("BETWEEN")

#if defined(__cpp_variadic_templates) || defined(_HAS_VARIADIC_TEMPLATES)
	template <typename T1, typename... Args>
	inline bool In(const T1 v, const Args&... args) const {
		return Equal(v) || In(args...);
	} inline bool In() const {return false;}
#endif // __cpp_variadic_templates
	template <typename T1>
	inline bool InNCmp(size_t argc, const T1 v, ...) const
	{
		if (Equal(v)) return true;
		va_list ap;
		va_start(ap, v);
		while (--argc)
		{
			T1 vn = va_arg(ap, T1);
			if (Equal(vn)) return true;
		}// end while
		return false;
	}
};// __SSCmp_
#ifndef __INTELLISENSE__
# define Switch(swv) \
{\
int __nLoopCnt_;\
int __nKey_;\
__SSCmp_ SwitchValue(swv);\
__nLoopCnt_ = 0;\
__nKey_ = -1;\
while (++__nLoopCnt_ <= 2) {\
switch (__nKey_) {\
case -1:\
	 if(__nLoopCnt_ > 1){\
		__nKey_ = -2;\
		__nLoopCnt_ = 1;\
		continue;\
	}

# define __END_SWITCH_EXPR_(END_WHILE_EXPR) }\
if (__nLoopCnt_ == 1) {\
	continue;\
} break;\
} END_WHILE_EXPR;\
}

# define End_SwitchC			__END_SWITCH_EXPR_(if(__nLoopCnt_ > 2) continue)
# define End_Switch				__END_SWITCH_EXPR_(void())

# define __Case_Expr_(EXPR)	}\
case __COUNTER__ + 1:\
	if(__nLoopCnt_ == 1) {\
		if(EXPR)\
		{\
			__nKey_ = __COUNTER__;\
			break;\
		}\
	} else {
# define Case_Expr(EXPR)		; __Case_Expr_(EXPR) case __COUNTER__

# define Case(v)				Case_Expr(SwitchValue.Equal(v))
# define Case_Not(v)			Case_Expr(!SwitchValue.Equal(v))

# define Case_Greater(n)		Case_Expr(SwitchValue.Greater(n))
# define Case_GreaterEqual(n)	Case_Expr(SwitchValue.GreaterEqual(n))
# define Case_Less(n)			Case_Expr(SwitchValue.Less(n))
# define Case_LessEqual(n)		Case_Expr(SwitchValue.LessEqual(n))

# define Case_BitOr(i)			Case_Expr(SwitchValue.BitOr(i))
# define Case_BitAnd(i)			Case_Expr(SwitchValue.BitAnd(i))

# define Case_Or(b)				Case_Expr(SwitchValue.Or(b))
# define Case_And(b)			Case_Expr(SwitchValue.And(b))

# define Case_Between(s, e)		Case_Expr(SwitchValue.Between(s, e))
# define Case_Not_Between(s, e)	Case_Expr(!SwitchValue.Between(s, e))

#if defined(__cpp_variadic_templates) || defined(_HAS_VARIADIC_TEMPLATES)
# define Case_In(...)			Case_Expr(SwitchValue.In(__VA_ARGS__))
# define Case_Not_In(...)		Case_Expr(!SwitchValue.In(__VA_ARGS__))
#else // !__cpp_variadic_templates

#pragma push_macro("static_assert")
#if !defined(__GXX_EXPERIMENTAL_CXX0X__) && _MSC_VER < 1600
#undef static_assert
#define static_assert assert(msg && expr)
#endif
# define Case_In(...)			static_assert(0, "Require variadic templates feature."); case __COUNTER__
# define Case_Not_In(...)		static_assert(0, "Require variadic templates feature."); case __COUNTER__
#pragma pop_macro("static_assert")
#endif // !__cpp_variadic_templates
# define Case_InNCmp(argc, ...) Case_Expr(SwitchValue.InNCmp(argc, __VA_ARGS__))
# define Case_Not_InNCmp(argc, ...) \
								Case_Expr(!SwitchValue.InNCmp(argc, __VA_ARGS__))

# define Case_Else				Case_Expr(true)
# define Case_Null				Case_Expr(SwitchValue.Null())
# define Case_Not_Null			Case_Expr(!SwitchValue.Null())
# define Case_Empty				Case_Expr(SwitchValue.Empty())
# define Case_Not_Empty			Case_Expr(!SwitchValue.Empty())
# define Default				;} default: if(__nLoopCnt_ > 1) { case __COUNTER__
#endif // !__INTELLISENSE__
# define Case_GT				Case_Greater
# define Case_GE				Case_GreaterEqual
# define Case_LT				Case_Less
# define Case_LE				Case_LessEqual

#pragma pop_macro("DEPRECATED")

#endif // __cplusplus

inline int swstrcmp(const char* pStr, ...)
{
	if (pStr == NULL) return 0;
	va_list ap;
	const char * pStrDest = NULL;
	va_start(ap, pStr);
	int i = 1;
	while ((pStrDest = va_arg(ap, const char*)) != NULL)
	{
		if (!strcmp(pStr, pStrDest))
			return i;
		i++;
	}// end while
	return -1;
}

#ifdef USE_SW_WCHAR
inline int swwcscmp(const wchar_t* pStr, ...)
{
	if (pStr == NULL) return 0;
	va_list ap;
	const wchar_t * pStrDest = NULL;
	va_start(ap, pStr);
	int i = 1;
	while ((pStrDest = va_arg(ap, const wchar_t*)) != NULL)
	{
		if (!wcscmp(pStr, pStrDest))
			return i;
		i++;
	}// end while
	return -1;
}
#endif // USE_SW_WCHAR

#ifdef UNICODE
#define swtcscmp	swwcscmp
#else // !UNICODE
#define swtcscmp	swstrcmp
#endif // !UNICODE

#pragma pop_macro("USE_SW_WCHAR")
#endif // !_SSWITCH_H_
