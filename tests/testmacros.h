#ifndef TEST_MACROS_H
#define TEST_MACROS_H

struct int8_t;

typedef int8_t Test;
#define TEST_RESULT(x)                                  \
        if(x != 0){ printf("Test error!");              \
            return -1;                                  \
        }

#define TEST_END()  \
        printf("----------------------\n");

#define TEST_EXEC(title, x)                             \
        printf("Started " title " test\n");             \
        TEST_RESULT(x);                                 \
        printf(title " = success\n");                   \
        TEST_END();

#endif