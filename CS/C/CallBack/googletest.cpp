/*
 * @Author: Kinoko 
 * @Date: 2021-12-26 18:26:26 
 * @Last Modified by: Kinoko
 * @Last Modified time: 2021-12-26 18:35:03
 */

#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct
{
    int output;
    int a;
    int b;
    int (*TestEMFunc)(int, int);
} T_EMTest;

T_EMTest *addFunc(int (*TestEMFunc)(int, int), int a, int b, int output)
{
    T_EMTest *m_EMTest = (T_EMTest *)malloc(sizeof(T_EMTest));
    m_EMTest->a = a;
    m_EMTest->b = b;
    m_EMTest->output = output;
    m_EMTest->TestEMFunc = TestEMFunc;
    return m_EMTest;
}

void runEMTest(T_EMTest *p_EMTest)
{
    if (p_EMTest != NULL)
    {
        int count = p_EMTest->TestEMFunc(p_EMTest->a, p_EMTest->b);
        if (count == p_EMTest->output)
        {
            printf(" succes \n");
        }
        else
        {
            printf(" fail %d != %d \n", count, p_EMTest->output);
        }
    }
}

int add(int a, int b)
{
    //TODO
    return a + b;
}

int main()
{
    printf("app start\n");
    T_EMTest *m_EMTest = addFunc(add, 1, 2, 3);
    runEMTest(m_EMTest);
    return 0;
}