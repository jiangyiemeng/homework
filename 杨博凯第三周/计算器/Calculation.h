#ifndef _CALCULATION
#define _CALCULATION

#pragma once
#include"Stack.h"

/*函数定义区*/
int _Calculation(Stack* Calculation);
void isException(char** tokens, int capacity);
/*加法*/
void _Add(char* a, char* b);
/*减*/
void _Minus(char* a, char* b);
/*乘*/
void _Multiply(char* a, char* b);
/*除*/
void _Devide(char* a, char* b);
/*取余*/
void _Surplus(char* a, char* b);
/*次方*/
void _Power(char* a, char* b);
/*开方*/
void _Squrt(char* b);
/*阶乘*/
void _Factorial(char* b);
/*对数*/
void _Logarithm(char* a, char* b);
/*打印结果*/
void _Print(Stack* Calculation, int result);
/*释放申请的空间*/
void Free(Stack* Calculation, char** tokens, int capacity);
/*是否再次计算*/
int isAgain(void);
/************/

#endif