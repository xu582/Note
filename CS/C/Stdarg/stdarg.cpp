#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define SIZE 50

char *make_message(const char *fmt, ...)
{
    /* 初始时假设我们只需要不超过100字节大小的空间 */
    int n;
    char *p;

    va_list ap;
    if ((p = (char *)malloc(SIZE * sizeof(char))) == NULL)
        return NULL;
    while (1)
    {
        /* 尝试在申请的空间中进行打印操作 */
        va_start(ap, fmt);
        n = vsnprintf(p, SIZE, fmt, ap);
        va_end(ap);

        /* 如果vsnprintf调用成功，返回该字符串 */
        if (n > -1 && n < SIZE)
            return p;
        /* vsnprintf调用失败(n<0)，或者p的空间不足够容纳size大小的字符串(n>=size)，尝试申请更大的空间*/
        //if ((p = (char *)realloc(sizeof(char) * SIZE)) == NULL)
            //return NULL;
    }

    return NULL;
}

int mon_log(char *fmt, ...)
{
    char str[SIZE];
    int i = 0;

    va_list arg;        //定义一个va_list型的变量,这个变量是指向参数的指针.
    va_start(arg, fmt); //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
    i = vsnprintf(str, SIZE, fmt, arg);
    va_end(arg);

    return i;
}

int main()
{
    //int i = mon_log("%s,%d,%d,%d", "asd", 2, 3, 4);
    //printf("%d\n", i);
    char *str = make_message("%d,%d,%d,%d", 5, 6, 7, 8);
    char *pstr = make_message("%d",1,2,3,4);
    printf("%s,%d\n", str, sizeof(str));
    free(str);

    return 0;
}