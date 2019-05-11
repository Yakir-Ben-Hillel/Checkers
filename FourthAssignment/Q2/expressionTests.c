#include "Header2.h"
/*Static Declartions*/
static BOOL barrackChecker(char *str);
static BOOL find_amount(int amount);
static BOOL isInputVaild(char *str);
/*Static Declartions*/

 BOOL isVaildExpression(char *str)
{
	int length;
	length = strlen(str);
	if ((isAnOperator(str[0] == TRUE) || (!barrackChecker(str))) || (!isInputVaild(str)))
		return FALSE;

	for (int i = 0; i < length; i++)
	{ //Tests for aritmetic problems.

		if ((isAnOperator(str[i])) && (isAnOperator(str[i + 1])))
		{ //TEST 1:two aritmetics in a row.
			return FALSE;
		}
		if ((str[i] == '(') && (str[i + 1] == ')'))
		{ //TEST 2: ()
			return FALSE;
		}
		if ((isAnumber(str[i])) && (isAnumber(str[i + 1])))
		{ //TEST 3: number higher than 9.
			return FALSE;
		}
		if (i > 0)
		{
			if ((isAnOperator(str[i]) && (str[i - 1] == '(') && (str[i + 1] == ')')))
			{ //TEST 4: (OPERTAOR)
				return FALSE;
			}
			if ((isAnumber(str[i])) && (str[i - 1] == '(') && (str[i + 1] == ')'))
			{ //TEST 5: (NUMBER)
				return FALSE;
			}
			if ((isAnumber(str[i]) && (isAnOperator(str[i - 1])) && (isAnOperator(str[i + 1]))))
			{ //TEST 6: (OPERTAOR,NUM,OPERATOR).
				return FALSE;
			}
		}
	}
	return TRUE;
}

 BOOL isAnOperator(char c)
{
	switch (c)
	{
	case '*':
	case '/':
	case '+':
	case '-':
	case '%':
		return TRUE;
	default:
		return FALSE;
	}
}
BOOL isAnumber(char c)
{
	if ((((int)c) >= 48) && ((int)c) <= 57)
		return TRUE;
	else
		return FALSE;
}
static BOOL isInputVaild(char *str)
{
	BOOL flag = TRUE;
	for (int i = 0; i < strlen(str); i++)
	{
		if (flag == FALSE)
			return FALSE;
		switch (str[i])
		{//Only inputs which are vaild.
		case '*':
		case '/':
		case '+':
		case '-':
		case '%':
		case '(':
		case ')':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			flag = TRUE;
			break;
		default:
			flag = FALSE;
			break;
		}
	}
	return TRUE;
}
static BOOL barrackChecker(char *str)
{//Checks if opening barrack are equal to closing barracks.
	int amount;
	amount = -1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
		{
			amount++;
		}
		else if (str[i] == ')')
		{
			amount--;
		}
	}
	return find_amount(amount);
}
static BOOL find_amount(int amount)
{
	if (amount == -1)
		return TRUE;
	else
		return FALSE;
}
