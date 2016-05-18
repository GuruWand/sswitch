# sswitch
sswitch for C++, Single Value Multiple Compare for C++

## Tested compilers

* Visual Studio 2010, 2015
* Clang 3.7 with Microsoft CodeGen (v140_clang_3_7)
* g++ 4.9.2 (c++, c++98, c++0x, c++11, c++14)
* clang++ 3.6.0 (c++, c++98, c++0x, c++11, c++14, c++1z)

## Reserved keywords

**Description**

* sv: SwitchValue
* v : Variable    (string, wstring, int, long long, float, double, ...)
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
                                   Require varadic templates feature of C++11. */
Case_Not_In(v1, ...):              /* sv not in (v1, v2, v3, v4, ...)
                                   Require varadic templates feature of C++11. */

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
Switch(std::string("test").c_str())
{
Case(std::string("test").c_str()):
Case("test"):
    cout << "Error!" << endl;
    break;
Default:
    cout "Important: For the performance"
    << "Switch statement is not suppote string pointer of the rvalue instance." << endl;
    break;
} End_Switch

std::string str1 = "test";
Switch(str1.c_str())
{
Case(std::wstring(L"test").c_str()):
Default:
    cout << "Error!" << endl;
    break;
Case(std::string("test").c_str()):
    cout << "True!" << endl;
    break;

} End_Switch


Switch("123")
{
Default:
    cout << "Not matched" << endl;
break;
#if defined(__cpp_variadic_templates)
Case_In("1123", 1234, "123", 123.1f, 123.2):
    cout << "Matched!" << endl;
#else  // !__cpp_variadic_templates
Case_InNCmp(4, "1123", "1223", "123", "1234") :
    cout << "Matched!" << endl;
#endif // !__cpp_variadic_templates
break;
} End_Switch;
```
