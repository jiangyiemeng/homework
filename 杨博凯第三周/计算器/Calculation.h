#ifndef _CALCULATION
#define _CALCULATION

#pragma once
#include"Stack.h"

/*����������*/
int _Calculation(Stack* Calculation);
void isException(char** tokens, int capacity);
/*�ӷ�*/
void _Add(char* a, char* b);
/*��*/
void _Minus(char* a, char* b);
/*��*/
void _Multiply(char* a, char* b);
/*��*/
void _Devide(char* a, char* b);
/*ȡ��*/
void _Surplus(char* a, char* b);
/*�η�*/
void _Power(char* a, char* b);
/*����*/
void _Squrt(char* b);
/*�׳�*/
void _Factorial(char* b);
/*����*/
void _Logarithm(char* a, char* b);
/*��ӡ���*/
void _Print(Stack* Calculation, int result);
/*�ͷ�����Ŀռ�*/
void Free(Stack* Calculation, char** tokens, int capacity);
/*�Ƿ��ٴμ���*/
int isAgain(void);
/************/

#endif