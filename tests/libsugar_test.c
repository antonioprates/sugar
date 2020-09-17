/*
 * Simple Test program for libsugar
 *
 * libsugar can be useful to use sugar as a "backend" for a code generator.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "libsugar.h"

void handle_error(void *opaque, const char *msg)
{
    fprintf(opaque, "%s\n", msg);
}

/* this function is called by the generated code */
int add(int a, int b)
{
    return a + b;
}

/* this strinc is referenced by the generated code */
const char hello[] = "Hello World!";

char my_program[] =
"#include <sugarlib.h>\n" /* include the "Simple libc header for SUGAR" */
"extern int add(int a, int b);\n"
"#ifdef _WIN32\n" /* dynamically linked data needs 'dllimport' */
" __attribute__((dllimport))\n"
"#endif\n"
"extern const char hello[];\n"
"int fib(int n)\n"
"{\n"
"    if (n <= 2)\n"
"        return 1;\n"
"    else\n"
"        return fib(n-1) + fib(n-2);\n"
"}\n"
"\n"
"int foo(int n)\n"
"{\n"
"    printf(\"%s\\n\", hello);\n"
"    printf(\"fib(%d) = %d\\n\", n, fib(n));\n"
"    printf(\"add(%d, %d) = %d\\n\", n, 2 * n, add(n, 2 * n));\n"
"    return 0;\n"
"}\n";

int main(int argc, char **argv)
{
    SUGARState *s;
    int i;
    int (*func)(int);

    s = sugar_new();
    if (!s) {
        fprintf(stderr, "Could not create sugar state\n");
        exit(1);
    }

    assert(sugar_get_error_func(s) == NULL);
    assert(sugar_get_error_opaque(s) == NULL);

    sugar_set_error_func(s, stderr, handle_error);

    assert(sugar_get_error_func(s) == handle_error);
    assert(sugar_get_error_opaque(s) == stderr);

    /* if sugarlib.h and libsugar1.a are not installed, where can we find them */
    for (i = 1; i < argc; ++i) {
        char *a = argv[i];
        if (a[0] == '-') {
            if (a[1] == 'B')
                sugar_set_lib_path(s, a+2);
            else if (a[1] == 'I')
                sugar_add_include_path(s, a+2);
            else if (a[1] == 'L')
                sugar_add_library_path(s, a+2);
        }
    }

    /* MUST BE CALLED before any compilation */
    sugar_set_output_type(s, SUGAR_OUTPUT_MEMORY);

    if (sugar_compile_string(s, my_program) == -1)
        return 1;

    /* as a test, we add symbols that the compiled program can use.
       You may also open a dll with sugar_add_dll() and use symbols from that */
    sugar_add_symbol(s, "add", add);
    sugar_add_symbol(s, "hello", hello);

    /* relocate the code */
    if (sugar_relocate(s, SUGAR_RELOCATE_AUTO) < 0)
        return 1;

    /* get entry symbol */
    func = sugar_get_symbol(s, "foo");
    if (!func)
        return 1;

    /* run the code */
    func(32);

    /* delete the state */
    sugar_delete(s);

    return 0;
}
