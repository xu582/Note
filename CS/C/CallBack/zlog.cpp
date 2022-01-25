/*
 * @Author: Kinoko 
 * @Date: 2021-12-26 17:43:26 
 * @Last Modified by: Kinoko
 * @Last Modified time: 2022-01-25 10:57:03
 */
#include <stdio.h>
#include <stdarg.h>

#define OPEN_LOG 1
#define LOG_LEVEL LOG_WARN

typedef enum
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
} E_LogLEVEL;

char *EM_LOGLevelGet(const int level)
{
    if (level == LOG_DEBUG)
    {
        return "DEBUG";
    }
    else if (level == LOG_INFO)
    {
        return "INFO";
    }
    else if (level == LOG_WARN)
    {
        return "WARN";
    }
    else if (level == LOG_ERROR)
    {
        return "ERROR";
    }

    return "UNKNOW";
}

void EM_LOG(const int level, const char *fun, const int line, const char *fmt, ...)
{
#ifdef OPEN_LOG
    va_list arg;
    va_start(arg, fmt);
    char buf[1 + vsnprintf(NULL, 0, fmt, arg)];
    vsnprintf(buf, sizeof(buf), fmt, arg);
    va_end(arg);
    if (level >= LOG_LEVEL)
        printf("[%s] [%s %d]%s\n", EM_LOGLevelGet(level), fun, line, buf);
    //TODO 存储
#endif
}

#define EMLOG(level, fmt, ...) EM_LOG(level, __FUNCTION__, __LINE__, fmt)

int main()
{
    printf("Zlog...\n");
    //test_1("", 12, 'f', 9);
    // EM_LOG(LOG_DEBUG, "app start");
    // EM_LOG(LOG_INFO, "app start");
    // EM_LOG(LOG_WARN, "app start");
    // EM_LOG(LOG_ERROR, "app start");
    EM_LOG(LOG_DEBUG, __FUNCTION__, __LINE__, "app start");
    EM_LOG(LOG_INFO, __FUNCTION__, __LINE__, "app start");
    EM_LOG(LOG_WARN, __FUNCTION__, __LINE__, "app start");
    EM_LOG(LOG_ERROR, __FUNCTION__, __LINE__, "app start");
    return 0;
}