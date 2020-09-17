#ifndef LIBSUGAR_H
#define LIBSUGAR_H

#ifndef LIBSUGARAPI
# define LIBSUGARAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct SUGARState;

typedef struct SUGARState SUGARState;

typedef void (*SUGARErrorFunc)(void *opaque, const char *msg);

/* create a new SUGAR compilation context */
LIBSUGARAPI SUGARState *sugar_new(void);

/* free a SUGAR compilation context */
LIBSUGARAPI void sugar_delete(SUGARState *s);

/* set CONFIG_SUGARDIR at runtime */
LIBSUGARAPI void sugar_set_lib_path(SUGARState *s, const char *path);

/* set error/warning display callback */
LIBSUGARAPI void sugar_set_error_func(SUGARState *s, void *error_opaque, SUGARErrorFunc error_func);

/* return error/warning callback */
LIBSUGARAPI SUGARErrorFunc sugar_get_error_func(SUGARState *s);

/* return error/warning callback opaque pointer */
LIBSUGARAPI void *sugar_get_error_opaque(SUGARState *s);

/* set options as from command line (multiple supported) */
LIBSUGARAPI void sugar_set_options(SUGARState *s, const char *str);

/*****************************/
/* preprocessor */

/* add include path */
LIBSUGARAPI int sugar_add_include_path(SUGARState *s, const char *pathname);

/* add in system include path */
LIBSUGARAPI int sugar_add_sysinclude_path(SUGARState *s, const char *pathname);

/* define preprocessor symbol 'sym'. value can be NULL, sym can be "sym=val" */
LIBSUGARAPI void sugar_define_symbol(SUGARState *s, const char *sym, const char *value);

/* undefine preprocess symbol 'sym' */
LIBSUGARAPI void sugar_undefine_symbol(SUGARState *s, const char *sym);

/*****************************/
/* compiling */

/* add a file (C file, dll, object, library, ld script). Return -1 if error. */
LIBSUGARAPI int sugar_add_file(SUGARState *s, const char *filename);

/* compile a string containing a C source. Return -1 if error. */
LIBSUGARAPI int sugar_compile_string(SUGARState *s, const char *buf);

/*****************************/
/* linking commands */

/* set output type. MUST BE CALLED before any compilation */
LIBSUGARAPI int sugar_set_output_type(SUGARState *s, int output_type);
#define SUGAR_OUTPUT_MEMORY   1 /* output will be run in memory (default) */
#define SUGAR_OUTPUT_EXE      2 /* executable file */
#define SUGAR_OUTPUT_DLL      3 /* dynamic library */
#define SUGAR_OUTPUT_OBJ      4 /* object file */
#define SUGAR_OUTPUT_PREPROCESS 5 /* only preprocess (used internally) */

/* equivalent to -Lpath option */
LIBSUGARAPI int sugar_add_library_path(SUGARState *s, const char *pathname);

/* the library name is the same as the argument of the '-l' option */
LIBSUGARAPI int sugar_add_library(SUGARState *s, const char *libraryname);

/* add a symbol to the compiled program */
LIBSUGARAPI int sugar_add_symbol(SUGARState *s, const char *name, const void *val);

/* output an executable, library or object file. DO NOT call
   sugar_relocate() before. */
LIBSUGARAPI int sugar_output_file(SUGARState *s, const char *filename);

/* link and run main() function and return its value. DO NOT call
   sugar_relocate() before. */
LIBSUGARAPI int sugar_run(SUGARState *s, int argc, char **argv);

/* do all relocations (needed before using sugar_get_symbol()) */
LIBSUGARAPI int sugar_relocate(SUGARState *s1, void *ptr);
/* possible values for 'ptr':
   - SUGAR_RELOCATE_AUTO : Allocate and manage memory internally
   - NULL              : return required memory size for the step below
   - memory address    : copy code to memory passed by the caller
   returns -1 if error. */
#define SUGAR_RELOCATE_AUTO (void*)1

/* return symbol value or NULL if not found */
LIBSUGARAPI void *sugar_get_symbol(SUGARState *s, const char *name);

/* return symbol value or NULL if not found */
LIBSUGARAPI void sugar_list_symbols(SUGARState *s, void *ctx,
    void (*symbol_cb)(void *ctx, const char *name, const void *val));

#ifdef __cplusplus
}
#endif

#endif
