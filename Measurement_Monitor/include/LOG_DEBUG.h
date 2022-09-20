#ifndef _LOG_DEBUG_H_
#define _LOG_DEBUG_H_
//encoding:utf-8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define CAPI_VERSION	"v0.3.5"

static unsigned long long global_last_error_code = 0;
static char *global_last_error_code_str_desc;
#define GetLastErrorCode() global_last_error_code
#define GetLastErrorCodeName() global_last_error_code_str_desc
#define SetLastErrorCode(errcode) do { global_last_error_code = errcode; } while(0)
#define SetLastErrorCodeName(errcodeEnumName) do { global_last_error_code_str_desc = #errcodeEnumName; } while(0)

#define LOG_DEBUG_ON
#ifndef LOG_DEBUG_ON
// #define log_print_debug(...) printf(__VA_ARGS__)
#define log_print_debug(...) 0
#else
#ifndef DEBUG_INFO_INTOFILE
#define log_print_debug(...)                                                             \
    do                                                                                   \
    {                                                                                    \
        time_t ts = time(NULL);                                                          \
        struct tm *ptm = localtime(&ts);                                                 \
        int y, m, d, h, n, s;                                                            \
        y = ptm->tm_year + 1900;                                                         \
        m = ptm->tm_mon + 1;                                                             \
        d = ptm->tm_mday;                                                                \
        h = ptm->tm_hour;                                                                \
        n = ptm->tm_min;                                                                 \
        s = ptm->tm_sec;                                                                 \
        char dateFileName[64] = {0};                                                     \
        char strDateTime[64] = {0};                                                      \
        memset(dateFileName, 0, sizeof(dateFileName));                                   \
        memset(strDateTime, 0, sizeof(strDateTime));                                     \
        sprintf(dateFileName, "%d%02d%02d_error.log", y, m, d);                          \
        sprintf(strDateTime, "%02d:%02d:%02d", h, n, s);                                 \
        /* 输出到控制台 */                                                         \
        fprintf(stderr, "DEBUG:VERSION:%s:%s:File:%s:Func:%s:Line:%d:",           \
                CAPI_VERSION, strDateTime, __FILE__, __FUNCTION__, __LINE__);          \
        fprintf(stderr, __VA_ARGS__);                                                    \
    } while (0)
#else
#endif //ifndef DEBUG_INFO_INTOFILE
#endif //ifndef LOG_DEBUG_ON

#define log_print_verbose(...)                                                             \
    do                                                                                   \
    {                                                                                    \
        time_t ts = time(NULL);                                                          \
        struct tm *ptm = localtime(&ts);                                                 \
        int y, m, d, h, n, s;                                                            \
        y = ptm->tm_year + 1900;                                                         \
        m = ptm->tm_mon + 1;                                                             \
        d = ptm->tm_mday;                                                                \
        h = ptm->tm_hour;                                                                \
        n = ptm->tm_min;                                                                 \
        s = ptm->tm_sec;                                                                 \
        char dateFileName[64] = {0};                                                     \
        char strDateTime[64] = {0};                                                      \
        memset(dateFileName, 0, sizeof(dateFileName));                                   \
        memset(strDateTime, 0, sizeof(strDateTime));                                     \
        sprintf(dateFileName, "%d%02d%02d_verbose.log", y, m, d);                          \
        sprintf(strDateTime, "%02d:%02d:%02d", h, n, s);                                 \
        /* 输出到控制台 */                                                         \
        fprintf(stderr, "VERBOSE:CAPI_VERSION:%s:%s:File:%s:Func:%s:Line:%d:",           \
                CAPI_VERSION, strDateTime, __FILE__, __FUNCTION__, __LINE__);          \
        fprintf(stderr, __VA_ARGS__);                                                    \
        FILE *fp_log = fopen(dateFileName, "a+");                                        \
        if (fp_log != NULL)                                                              \
        {                                                                                \
            /* 输出到日志文件 */                                                  \
            fprintf(fp_log, "VERBOSE:CAPI_VERSION:%s:%s:File:%s:Func:%s:Line:%d:",       \
                    CAPI_VERSION, strDateTime, __FILE__, __FUNCTION__, __LINE__);      \
            fprintf(fp_log, __VA_ARGS__);                                                \
            fclose(fp_log);                                                              \
            fp_log = NULL;                                                               \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            fprintf(stderr, "fopen log file error(sysErrDesc:%s)\r\n", strerror(errno)); \
            exit(-1);                                                                    \
        }                                                                                \
    } while (0)

#define log_print_error(...)                                                             \
    do                                                                                   \
    {                                                                                    \
        time_t ts = time(NULL);                                                          \
        struct tm *ptm = localtime(&ts);                                                 \
        int y, m, d, h, n, s;                                                            \
        y = ptm->tm_year + 1900;                                                         \
        m = ptm->tm_mon + 1;                                                             \
        d = ptm->tm_mday;                                                                \
        h = ptm->tm_hour;                                                                \
        n = ptm->tm_min;                                                                 \
        s = ptm->tm_sec;                                                                 \
        char dateFileName[64] = {0};                                                     \
        char strDateTime[64] = {0};                                                      \
        memset(dateFileName, 0, sizeof(dateFileName));                                   \
        memset(strDateTime, 0, sizeof(strDateTime));                                     \
        sprintf(dateFileName, "%d%02d%02d_error.log", y, m, d);                          \
        sprintf(strDateTime, "%02d:%02d:%02d", h, n, s);                                 \
        /* 输出到控制台 */                                                         \
        fprintf(stderr, "ERROR:CAPI_VERSION:%s:%s:File:%s:Func:%s:Line:%d:",           \
                CAPI_VERSION, strDateTime, __FILE__, __FUNCTION__, __LINE__);          \
        fprintf(stderr, __VA_ARGS__);                                                    \
        FILE *fp_log = fopen(dateFileName, "a+");                                        \
        if (fp_log != NULL)                                                              \
        {                                                                                \
            /* 输出到日志文件 */                                                  \
            fprintf(fp_log, "ERROR:CAPI_VERSION:%s:%s:File:%s:Func:%s:Line:%d:",       \
                    CAPI_VERSION, strDateTime, __FILE__, __FUNCTION__, __LINE__);      \
            fprintf(fp_log, __VA_ARGS__);                                                \
            fclose(fp_log);                                                              \
            fp_log = NULL;                                                               \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            fprintf(stderr, "fopen log file error(sysErrDesc:%s)\r\n", strerror(errno)); \
            exit(-1);                                                                    \
        }                                                                                \
    } while (0)

/**
* @brief 返回值检查:如果表达式返回值 COP 于期望返回值，则返回指定返回值，并把错误码更新至LastError, 并把详细错误细节写入错误日志文件；
* @details 错误日志记录包含表达式比较记录、自定义错误码记录、系统调用错误码记录、以及用户自定义的错误描述信息。
* @details 用法1：CHECK_COP_RET(buffer, !=, 0, ERRCODE_FUNC_INVALID_PARAMETER, "");
* @details 用法2：CHECK_COP_RET(fp = fopen(filename, "rb"), ==, 0, ERRCODE_NO_SUCH_FILE, "current filename:%s\r\n", filename);
* @param   exp 被检查的表达式，检查其返回值.
* @param   cop 比较符(Comparison operator)，当前支持：>, <, ==, >=, <=, !=；调用方法例如：int data=10; CHECK_COP_RET(data, <=, 10, ERRCODE_XXX, "");
* @param   expret  期望的返回值(expect return value)，即调用者希望表达式应当返回的值.
* @param   ret 返回指定值，即如果 CHECK_COP_RET 满足，则返回指定值。
* @param   errcode  把LastError更新为指定错误码，例如： ERRCODE_FUNC_INVALID_PARAMETER；-1表示不更新LastError最后错误码。
* @param   不定参数    用法和printf一样了，比如：CHECK_COP_XXX(,,,,,"my name is %s, %d years old\r\n", "xiaoming", 20)，当不用时，传入空字符串""即可。
*/
#define CHECK_COP_RET(exp, cop, expret, ret, errcode, ...)           \
    do \
    { \
        if ((exp) cop (expret)) \
        { \
            log_print_error("expression: `%s` %s %ld (0x%lx)\r\n", #exp, #cop, expret, expret);\
            log_print_error("error code: %s 0x%lx (%ld)\r\n", #errcode, errcode, errcode);\
            log_print_error("system call standard library global errno: %d (%s)\r\n", errno, strerror(errno));\
            if (errcode == -1) { SetLastErrorCode(errcode); } \
            if ((strnlen(#__VA_ARGS__, 4096) - 2) > 0)\
            {\
                log_print_error(__VA_ARGS__);\
            }\
            return (ret); \
        } \
    } while(0)

/**
* @brief 返回值检查:如果表达式返回值 COP 于期望返回值，则执行跳出语句break,并把错误码更新至LastError, 并把详细错误细节写入错误日志文件；
* @details 错误日志记录包含表达式比较记录、自定义错误码记录、系统调用错误码记录、以及用户自定义的错误描述信息。
* @details 用法1：CHECK_COP_RET(buffer, !=, 0, ERRCODE_FUNC_INVALID_PARAMETER, "");
* @details 用法2：CHECK_COP_RET(fp = fopen(filename, "rb"), ==, 0, ERRCODE_NO_SUCH_FILE, "current filename:%s\r\n", filename);
* @param   exp 被检查的表达式，检查其返回值.
* @param   cop 比较符(Comparison operator)，当前支持：>, <, ==, >=, <=, !=；调用方法例如：int data=10; CHECK_COP_RET(data, <=, 10, ERRCODE_XXX, "");
* @param   expret  期望的返回值(expect return value)，即调用者希望表达式应当返回的值.
* @param   errcode  指定错误码，-1=不指定错误码，例如： ERRCODE_FUNC_INVALID_PARAMETER.
* @param   不定参数    用法和printf一样了，比如：CHECK_COP_XXX(,,,,,"my name is %s, %d years old\r\n", "xiaoming", 20)，当不用时，传入空字符串""即可。
*/
#define CHECK_COP_BREAK(exp, cop, expret, errcode, ...)           \
        if ((exp) cop (expret)) \
        { \
            log_print_error("expression: `%s` %s %ld (0x%lx)\r\n", #exp, #cop, expret, expret);\
            log_print_error("error code: %s 0x%lx (%ld)\r\n", #errcode, errcode, errcode);\
            log_print_error("system call standard library global errno: %d (%s)\r\n", errno, strerror(errno));\
            if (errcode == -1) { SetLastErrorCode(errcode); } \
            if ((strnlen(#__VA_ARGS__, 4096) - 2) > 0)\
            {\
                log_print_error(__VA_ARGS__);\
            }\
            break; \
        }

/**
* @brief 返回值检查:如果表达式返回值 COP 于期望返回值，则跳转到指定标签,并把错误码更新至LastError, 并把详细错误细节写入错误日志文件；
* @details 错误日志记录包含表达式比较记录、自定义错误码记录、系统调用错误码记录、以及用户自定义的错误描述信息。
* @details 用法1：CHECK_COP_RET(buffer, !=, 0, ERRCODE_FUNC_INVALID_PARAMETER, "");
* @details 用法2：CHECK_COP_RET(fp = fopen(filename, "rb"), ==, 0, ERRCODE_NO_SUCH_FILE, "current filename:%s\r\n", filename);
* @param   exp 被检查的表达式，检查其返回值.
* @param   cop 比较符(Comparison Operator)，当前支持：>, <, ==, >=, <=, !=；调用方法例如：int data=10; CHECK_COP_RET(data, <=, 10, ERRCODE_XXX, "");
* @param   expret  期望的返回值(expect return value)，即调用者希望表达式应当返回的值.
* @param   errcode  指定错误码，-1=不指定错误码，例如： ERRCODE_FUNC_INVALID_PARAMETER.
* @param   gotosym  将要跳转的目标标签.
* @param   不定参数    用法和printf一样了，比如：CHECK_COP_XXX(,,,,,"my name is %s, %d years old\r\n", "xiaoming", 20)，当不用时，传入空字符串""即可。
*/
#define CHECK_COP_GOTO(exp, cop, expret, errcode, gotosym, ...)           \
        if ((exp) cop (expret)) \
        { \
            log_print_error("expression: `%s` %s %ld (0x%lx)\r\n", #exp, #cop, expret, expret);\
            log_print_error("error code: %s 0x%lx (%ld)\r\n", #errcode, errcode, errcode);\
            log_print_error("system call standard library global errno: %d (%s)\r\n", errno, strerror(errno));\
            if (errcode == -1) { SetLastErrorCode(errcode); } \
            if ((strnlen(#__VA_ARGS__, 4096) - 2) > 0)\
            {\
                log_print_error(__VA_ARGS__);\
            }\
            goto gotosym; \
        }

#endif //_LOG_DEBUG_H_
