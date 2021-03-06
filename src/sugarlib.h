/* Simple libc header for SUGAR
 *
 * Add any function you want from the libc there. This file is here
 * only for your convenience so that you do not need to put the whole
 * glibc include files on your floppy disk
 */
#ifndef _SUGARLIB_H
#define _SUGARLIB_H

#include <stddef.h>
#include <stdarg.h>

/* stdlib.h */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
int atoi(const char *nptr);
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
void exit(int);
int system(const char* command);
int rand(void);
void srand(unsigned seed);

/* stdio.h */
#ifndef _STDIO_H_
#define _STDIO_H_
#ifndef _STDIO_H
#define _STDIO_H
typedef struct __FILE FILE;
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
FILE *fopen(const char *path, const char *mode);
FILE *fdopen(int fildes, const char *mode);
FILE *freopen(const  char *path, const char *mode, FILE *stream);
int fclose(FILE *stream);
size_t  fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t  fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
int fgetc(FILE *stream);
char *fgets(char *s, int size, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *s);
int ungetc(int c, FILE *stream);
int fflush(FILE *stream);
int putchar (int c);
int fputs(const char *str, FILE *stream);
int fseek(FILE *stream, long int offset, int whence);
long int ftell(FILE *stream);

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const  char  *format, ...);
int asprintf(char **strp, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int vprintf(const char *format, va_list ap);
int vfprintf(FILE  *stream,  const  char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char  *format, va_list ap);
int vasprintf(char  **strp,  const  char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);

void perror(const char *s);
#endif /* _STDIO_H */
#endif /* _STDIO_H_ */

/* string.h */
int strcmp(const char *str1, const char *str2);
char *strtok(char *str, const char *delim);
char *strstr(const char *haystack, const char *needle);
char *strcat(char *dest, const char *src);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strcpy(char *dest, const char *src);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strdup(const char *s);
size_t strlen(const char *s);

/* dlfcn.h */
#define RTLD_LAZY       0x001
#define RTLD_NOW        0x002
#define RTLD_GLOBAL     0x100

void *dlopen(const char *filename, int flag);
const char *dlerror(void);
void *dlsym(void *handle, char *symbol);
int dlclose(void *handle);

#endif /* _SUGARLIB_H */
