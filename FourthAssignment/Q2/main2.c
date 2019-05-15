//David Yakir Ben Hillel 11/5/19.
#include "Header2.h"

int main()

{
    char str[SIZE];
    Tree tr;
    double res;
    BOOL expressionOK;

    printf("Please enter the expression: \n");

    gets(str);  
    expressionOK = buildExpressionTree(str, &tr);

    if (expressionOK == TRUE)

    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
            freeTree(&tr);
    }

    else
    {
        printf("The input expression is not valid\n");
    }
    
        system("pause\n");
}