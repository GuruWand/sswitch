# sswitch
* sswitch for C++
* Single Value Multiple Compare for C++

## Installing
* nuget.org : PM> Install-Package cppsswitch
* github.com : Clone or download > download ZIP

## Tested compilers

* clang++ 3.6.0 (c++, c++98, c++0x, c++11, c++14, c++1z)
* g++ 4.9.2 (c++, c++98, c++0x, c++11, c++14)
* Visual Studio 2010(v100), 2015(v140)
* Clang 3.7 with Microsoft CodeGen (v140_clang_3_7)

## Reserved keywords

**Description**

* sv: SwitchValue (string, wstring, int, long long, float, double)
* v : Variable    (string, wstring, int, long long, float, double)
* i : Interger    (int, long long)
* n : Number    (int, long long, float, double)
* b : Boolean    (bool)
* expr: Expression


```C++
Switch(sv) {
Case(v):                           // sv equal v
Case_Not(v):                       // sv not equal v
Case_Greater(n):                   // sv > n
Case_GreaterEqual(n):              // sv >= n
Case_Less(n):                      // sv < n
Case_LessEqual(n):                 // sv <= n

Case_GT(n):                        // Alias of Case_Greater(n)
Case_GE(n):                        // Alias of Case_GreaterEqual(n)
Case_LT(n):                        // Alias of Case_Less(n)
Case_LE(n):                        // Alias of Case_LessEqual(n)

Case_BitOr(i):                     // sv | i
Case_BitAnd(i):                    // sv & i

Case_Or(b):                        // sv || b
Case_And(b):                       // sv && b

Case_Between(nStart, nEnd):        // sv between nStart and nEnd
Case_Not_Between(nStart, nEnd):    // sv not between nStart and nEnd

Case_In(v1, ...):                  /* sv in (v1, v2, v3, v4, ...)
                                   Require varadic templates feature. */
Case_Not_In(v1, ...):              /* sv not in (v1, v2, v3, v4, ...)
                                   Require varadic templates feature */

Case_InNCmp(argc, v1, ...):        // sv in (v1, v2, v3, v4, vargc...)
Case_Not_InNCmp(argc, v1, ...):    // sv not in (v1, v2, v3, v4, vargc...)


Case_Expr(expr): // expr    (Execute when expression result into True)

Case_Else:       // true    (Execute when all the above Case statements result into False)
Default:         /* Notice: "default:" is not available in the "Switch" statement.
                 (Execute when all the Case statements result into False) */

Case_Null:       // sv is null string pointer (char *, wchar_t *)
Case_Not_Null:   // sv is not null string pointer
Case_Empty:      // sv is empty string ("", L"")
Case_Not_Empty:  // sv is not empty string
} End_SwitchC    // If you use this keyword, you can use the "continue" in the "Switch" statement.
// or
} End_Switch     // If you do not use "continue" in the "Switch" statement, then use this keyword.
```

## Examples
```C++
#include <iostream>
#include <stdio.h>
#include "sswitch.h"
#include "svmcmp.h"   // Single Value Multiple Compare
#include "slvb.h"     // Statements Like Visual Basic(useless)
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || _MSC_VER >= 1600
#include "sops.h"     // Simple Operators(more useless)
#endif

using namespace std;
void testcase1()
{
#ifdef _SOPS_H_
	1 between(1, 3);
#endif // _SOPS_H_
	Switch(std::string("test").c_str())
	{
	Case(std::string("test").c_str()) :
	Case("test") :
		cout << "Error!" << endl;
	break;
	Default:
		cout << "Important: For the performance, "
			<< "Switch statement is not support string pointer of the rvalue instance."
			<< endl;
		break;
	} End_Switch

	std::string str1 = "test";
	Switch(str1.c_str())
	{
	Case(std::wstring(L"test").c_str()) :
	Default:
		cout << "Error!" << endl;
	break;
	Case(std::string("test").c_str()) :
		cout << "True!" << endl;
	break;
	} End_Switch

	Switch("123")
	{
	Default:
		cout << "Not matched" << endl;
		break;
		Case_InNCmp(3, 123, 234, 456) :
			cerr << "Wrong matched" << endl;
		break;
		Case_InNCmp(3, 123.0, 234.0, 456.0) :
			cerr << "Wrong matched" << endl;
		break;
#if defined(__cpp_variadic_templates)
		Case_In("1123", 1234, "123", 123.1f, 123.2) :
			cout << "Matched with varadic template" << endl;
		break;
#endif // !__cpp_variadic_templates
		Case_InNCmp(3, "1123", "1223", "1234", "123") :
			cerr << "Wrong matched" << endl;
		break;
		Case_InNCmp(4, "1123", "1223", "1234", "123") :
			cout << "Matched" << endl;
		break;
	} End_Switch;

	int a = 0;
	string s1("Age");
	wstring sw1(L"Age");
	for (int i = 0; i < 2; i++)
	{
		Switch(i)
		{
#ifdef _MSC_VER
			Case(wstring(L"Age").c_str()) : Case(L"Age") :
				a = 50;
			break;
#endif // _MSC_VER
			Case_Between(1, 3) :
				a += 1200;
			break;
			Case("Name") :
				a = 100;
			break;
			Case("Age") :
				a += 200;
			Case("Age1") :
			Default:
			a += 300;
			continue;
			Case_Not_Between(1.1, 3.5) :
				a += 800;
			Switch(s1.c_str())
			{
#ifdef _MSC_VER
				Case(wstring(L"Age").c_str()) :
				Case(L"Age") :
					a = 50;
				break;
#endif // _MSC_VER
				Case_Between(1, 3.0) :
					a += 1200;
				break;
				Case("Name") :
					a = 100;
				break;
				Case("Age") :
					a += 200;
				Case("Age1") :
				Default:
				a += 300;
				continue;
				Case_Not_Between(1.1, 3.5) :
					a += 800;
				break;
				Case(string("Age").c_str()) :
					break;
			} End_SwitchC // support "continue"
				break;
			Case(string("Age").c_str()) :
				break;
		} End_SwitchC // support "continue"
		// Like Visual Basic
		Select_Case(s1.c_str())
#ifdef _MSC_VER
		Case_(wstring(L"Age").c_str())
		Case_(L"Age")
			a = 50;
#endif // _MSC_VER
		Case_Between_(1, 3.0)
			a += 1200;
		Case_("Name")
			a = 100;
		Case_("Age")
			a += 200;
		Case_("Age1")
			Default_
			a += 300;
		continue; // Next
		Case_Not_Between_(1.1, 3.5)
			a += 800;
		Case_(string("Age").c_str())
			End_SelectC // support "continue"
	}
	cout << "Result: " << a << endl;
}

void testcase2()
{
#ifdef _SVMCMP_H_
#define PRINT_EXPR_RESULT(expr) \
cout << endl << #expr << endl << " == ";\
if(expr) cout << "True" << endl;\
else cerr << "False" << endl;

	if (svmcmp(50).Not().Between(10, 100)
		.Or().Between(10, 100)
		.And().Greater(1)
		.And().Not().Less(1))
		cout << "Result: True" << endl;
	else cerr << "Result: False" << endl;

	PRINT_EXPR_RESULT(svmcmp(70).Between(10, 100)
		.And().Not().Between(40, 60)
		.And().Equal(70.0).And().Not().And(false));
#if defined(__cpp_variadic_templates)
	PRINT_EXPR_RESULT(svmcmp("123")
		.In("1234", "123", (const char*)NULL, 345.2, ""));
	PRINT_EXPR_RESULT(svmcmp((const char*)0)
		.In("1234", "123", (const char*)NULL, 345.2, ""));
	PRINT_EXPR_RESULT(!svmcmp((const char*)0)
		.In("1234", "123", NULL, 345.2, ""));
	PRINT_EXPR_RESULT(!svmcmp(0)
		.In("1234", "123", (const char*)NULL, 345.2, ""));
	PRINT_EXPR_RESULT(svmcmp(0)
		.In("1234", "123", 0.0f, 345.2, ""));
#endif // __cpp_variadic_templates
	cout << endl;
#endif // _SVMCMP_H_
}

void testcase3()
{
	// Only support string pointer
	int sw;
	sw = swstrcmp("a234" // SwitchValue
		, "a234" // case 1
		, "a123" // case 2
		, "a789" // case 3
		, NULL); // case 0
#ifdef _MSC_VER
	sw = swwcscmp(L"a234" // SwitchValue
		, L"a234" // case 1
		, L"a123" // case 2
		, L"a789" // case 3
		, NULL); // case 0
#endif // _MVC_VER
#ifdef _T
	sw = swtcscmp(_T("a234") // SwitchValue
		, _T("a234") // case 1
		, _T("a123") // case 2
		, _T("a789") // case 3
		, NULL); // case 0
#endif // _T
	int b = 0;
	switch (sw)
	{
	case NULL:
		b = 0;
		break;
	case 1:
		b = 100;
		break;
	case 2:
		b = 200;
	case 4:
		b += 300;
		break;
	default: case -1:
		b += 500;
		break;
	}
	printf("Result: %d \n", b);
}
```
