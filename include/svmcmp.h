/*
Single Value Multiple Compare for C++(svmcmp) v0.1
Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.

guruwand at gmail dot com
*/
#ifndef _SVMCMP_H_
# define _SVMCMP_H_
#ifndef _SSWITCH_H_
#error Please include sswitch.h header file(_SSWITCH_H_).
#endif
#pragma push_macro("_ASSERT_EXPR")
#ifndef _ASSERT_EXPR
#include <assert.h>
#define _ASSERT_EXPR(expr, msg) assert(msg && expr)
#endif // !_ASSERT_EXPR


#if !defined(__GXX_EXPERIMENTAL_CXX0X__) && _MSC_VER < 1600
#pragma push_macro("static_assert")
#undef static_assert
#define static_assert(expr, msg) assert(msg && expr)
#endif
class svmcmp;
class __ISVOps_
{
public:
	virtual svmcmp& And() = 0;
	virtual svmcmp& Or() = 0;
	virtual __ISVOps_& And(const bool) = 0;
	virtual __ISVOps_& Or(const bool) = 0;
	virtual operator bool() const = 0;
};

class svmcmp : __ISVOps_, private __SSCmp_
{
private:
	enum OP
	{
		OP_UNKNOWN
		, OP_INIT
		, OP_AND
		, OP_OR
	};
	bool mLastCmp;
	bool mNotOp;
	OP mLastOp;

private: // implements __ISVOps_
	inline svmcmp& And()
	{
		mLastOp = OP_AND;
		return *this;
	}
	inline svmcmp& Or()
	{
		mLastOp = OP_OR;
		return *this;
	}
	inline operator bool() const { return mLastCmp; }
public:
	inline svmcmp& Not()
	{
		mNotOp = mNotOp ? 0 : 1;
		return *this;
	}
public:
	template <typename T1>
	inline svmcmp(const T1 v) : __SSCmp_(v)
	{
		mNotOp = 0;
		mLastOp = OP_INIT;
		mLastCmp = (v != (T1)0);
	}

#pragma push_macro("CMPOPTYPE")
#undef CMPOPTYPE
# define CMPOPTYPE(OP) \
if (mLastOp == OP_INIT)\
	mLastCmp = (OP);\
else if(mLastOp == OP_OR)\
	mLastCmp = mLastCmp	|| (mNotOp ? !(OP) : (OP));\
else if(mLastOp == OP_AND)\
	mLastCmp = mLastCmp	&& (mNotOp ? !(OP) : (OP));\
else _ASSERT_EXPR(0, L"Missing operator.");\
mLastOp = OP_UNKNOWN;mNotOp = false;return *this

	template <typename T1>
	inline __ISVOps_& Equal(const T1 v) {
		CMPOPTYPE(__SSCmp_::Equal(v));
	}
	template <typename T1>
	inline __ISVOps_& Greater(const T1 v) {
		CMPOPTYPE(__SSCmp_::Greater(v));
	}
	template <typename T1>
	inline __ISVOps_& GreaterEqual(const T1 v) {
		CMPOPTYPE(__SSCmp_::GreaterEqual(v));
	}
	template <typename T1>
	inline __ISVOps_& GE(const T1 v) {
		CMPOPTYPE(__SSCmp_::GreaterEqual(v));
	}
	template <typename T1>
	inline __ISVOps_& Less(const T1 v)
	{
		CMPOPTYPE(__SSCmp_::Less(v));
	}
	template <typename T1>
	inline __ISVOps_& LessEqual(const T1 v) {
		CMPOPTYPE(__SSCmp_::LessEqual(v));
	}
	template <typename T1>
	inline __ISVOps_& LE(const T1 v) {
		CMPOPTYPE(__SSCmp_::LessEqual(v));
	}

	template <typename T1>
	inline __ISVOps_& BitOr(const T1 v) {
		CMPOPTYPE(__SSCmp_::BitOr(v));
	}
	template <typename T1>
	inline __ISVOps_& BitAnd(const T1 v) {
		CMPOPTYPE(__SSCmp_::BitAnd(v));
	}
	
	inline __ISVOps_& Or(const bool v) {
		Or();CMPOPTYPE(__SSCmp_::Or(v));
	}
	inline __ISVOps_& And(const bool v) {
		And();CMPOPTYPE(__SSCmp_::And(v));
	}

	template <typename T1>
	inline __ISVOps_& Between(const T1 s, const T1 e) {
		CMPOPTYPE(__SSCmp_::Between(s, e));
	}

	inline __ISVOps_& Null() {
		CMPOPTYPE(__SSCmp_::Null());
	}
	inline __ISVOps_& Empty() {
		CMPOPTYPE(__SSCmp_::Empty());
	}

#ifdef __cpp_variadic_templates
	template <typename... Args>
	inline __ISVOps_& In(const Args&... args) {
		CMPOPTYPE(__SSCmp_::In(args...));
	}
#else
	template <typename T1>
	inline __ISVOps_& In(T1 v, ...)
	{
		static_assert(0, "Require variadic templates feature.");
		return *this;
	}
#endif // !__cpp_variadic_templates
	template <typename T1>
	inline __ISVOps_& InNCmp(size_t argc, const T1 v, ...)
	{
		bool b = __SSCmp_::Equal(v);
		if (!b)
		{
			va_list ap;
			va_start(ap, v);
			while (--argc)
			{
				const T1 vn = va_arg(ap, const T1);
				b = __SSCmp_::Equal(vn);
				if (b) break;
			}// end while
		}
		CMPOPTYPE(b);
	}
#pragma pop_macro("CMPOPTYPE")
};// svmcmp

#if !defined(__GXX_EXPERIMENTAL_CXX0X__) && _MSC_VER < 1600
#pragma pop_macro("static_assert")
#endif
#pragma pop_macro("_ASSERT_EXPR")
#endif // !_SVMCMP_H_
