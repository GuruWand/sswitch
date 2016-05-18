/*
Statements Like Visual Basic for C++(SLVB) v0.1
Copyright(c) 2016 by GuruWand.
It is freely distributable under the terms of an MIT-style license.

*/

#ifndef _SLVB_H_
#define _SLVB_H_
# define While(A)				while(A){
# define Wend					}

# define DoWhile(A)				while(A){
# define DoUntil(A)				while(!(A)){
# define Loop					}

# define Do						do{
# define LoopWhile(A)			}while(A);
# define LoopUntil(A)			}while(!(A));

# define If						if(
# define Then					){
# define ElseIf					}else if(
# define Else					}else{
# define EndIf					}

#ifdef _SSWITCH_H_
//  Accelerate intellisense
# define Select_Case(EXPR)		Switch(EXPR) if(0){
# define End_Select				} End_Switch
# define End_SelectC			} End_SwitchC

#ifdef __INTELLISENSE__
# define Case_Expr_(EXPR)
# define Case_(v)
# define Case_Not_(v)

# define Case_Greater_(v)
# define Case_GreaterEqual_(v)
# define Case_Less_(v)
# define Case_LessEqual_(v)

# define Case_BitOr_(v)
# define Case_BitAnd_(v)

# define Case_BoolOr_(v)
# define Case_BoolAnd_(v)

# define Case_Between_(start, end)
# define Case_Not_Between_(start, end)

# define Case_In_(v, ...)
# define Case_Not_In_(v, ...)
# define Case_InNCmp_(argc, v1, ...)
# define Case_Not_InNCmp)(argc, v1, ...)

# define Case_Else_
# define Case_Null_
# define Case_Not_Null_
# define Case_Empty_
# define Case_Not_Empty_
#if(0)
# define Case_Like_(str)
# define Case_NotLike_(str)
# define Case_RegExp_(str)
# define Case_NotRegExp_(str)
#endif
# define Default_
#else // !__INTELLISENSE__
# define Case_Expr_(EXPR)		break; __Case_Expr_(EXPR)
# define Case_(v)				Case_Expr_(SwitchValue.Equal(v))
# define Case_Not_(v)			Case_Expr_(!SwitchValue.Equal(v))

# define Case_Greater_(v)		Case_Expr_(SwitchValue.Greater(v))
# define Case_GreaterEqual_(v)	Case_Expr_(SwitchValue.GreaterEqual(v))
# define Case_Less_(v)			Case_Expr_(SwitchValue.Less(v))
# define Case_LessEqual_(v)		Case_Expr_(SwitchValue.LessEqual(v))

# define Case_BitOr_(v)			Case_Expr_(SwitchValue.BitOr(v))
# define Case_BitAnd_(v)		Case_Expr_(SwitchValue.BitAnd(v))

# define Case_BoolOr_(v)		Case_Expr_(SwitchValue.BoolOr(v))
# define Case_BoolAnd_(v)		Case_Expr_(SwitchValue.BoolAnd(v))

# define Case_Between_(s, e)	\
								Case_Expr_(SwitchValue.Between(s, e))
# define Case_Not_Between_(s, e) \
								Case_Expr_(!SwitchValue.Between(s, e))

#ifdef __cpp_variadic_templates
# define Case_In_(v, ...)		Case_Expr_(SwitchValue.In(v, __VA_ARGS__))
# define Case_Not_In_(v, ...)	Case_Expr_(!SwitchValue.In(v, __VA_ARGS__))
#else	// !__cpp_variadic_templates
# define Case_In_(v, ...)		static_assert(0, "Require varadic templates feature of C++11.");
# define Case_Not_In_(v, ...)	static_assert(0, "Require varadic templates feature of C++11.");
#endif	// !__cpp_variadic_templates
# define Case_InNCmp_(argc, v, ...) \
								Case_Expr_(SwitchValue.InNCmp(argc, v, __VA_ARGS__))
# define Case_Not_InNCmp_(argc, v, ...) \
								Case_Expr_(!SwitchValue.InNCmp(argc, v, __VA_ARGS__))

# define Case_Else_				Case_Expr_(true)
# define Case_Null_				Case_Expr_(SwitchValue.Null())
# define Case_Not_Null_			Case_Expr_(!SwitchValue.Null())
# define Case_Empty_			Case_Expr_(SwitchValue.Empty())
# define Case_Not_Empty_		Case_Expr_(!SwitchValue.Empty())
# define Default_				break; } default: if(__nLoopCnt_ > 1) {
#endif // !__INTELLISENSE__
# define Case_GT_				Case_Greater_
# define Case_GE_				Case_GreaterEqual_
# define Case_LT_				Case_Less_
# define Case_LE_				Case_LessEqual_
#else
# define Select_Case(EXPR)		switch(EXPR) {
# define End_Select				}
# define End_SelectC			}
#endif // _SSWITCH_H_

#endif // !_SLVB_H_