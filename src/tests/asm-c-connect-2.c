#include <stdio.h>

#if (defined _WIN32 || defined __APPLE__) && (!defined __SUGARC__ || defined __leading_underscore)
# define _ "_"
#else
# define _
#endif

#ifdef __clang__
/* clang needs some help tp not throw functions away even at -O0 */
#define __USED __attribute__((__used__))
#else
#define __USED
#endif

int x3(void)
{
    printf(" x3");
    return 3;
}

/* That callx4 is defined globally (as if ".globl callx4")
   is a SUGAR extension.  GCC doesn't behave like this.  */
void callx4(void);
__asm__(_"callx4: call "_"x4; ret;"
#ifndef __SUGARC__
    " .global "_"callx4"
#endif
);

extern void x5(void);

void callx5_again(void);
void callx5_again(void)
{
    x5();
    asm("call "_"x6");
}

static void __USED x6()
{
    printf(" x6-2");
}