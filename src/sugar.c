/*
 * SUGAR by Antonio Prates, <antonioprates@gmailc.com, 2020
 * is a fork of:
 * 
 * TCC - Tiny C Compiler
 * Copyright (c) 2001-2004 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "sugar.h"
#if ONE_SOURCE
# include "libsugar.c"
#endif
#include "sugartools.c"

static const char help[] =
    "SUGAR C " SUGAR_VERSION " - a different flavour of tinycc "  "\n"
    "\n"
    "Usage: sugar [FILE.c [ARGUMENTS]]                   run source\n"
    "   or: sugar [OPTIONS] -dev [FILE.c [ARGUMENTS]]    run with debug\n"
    "   or: sugar [OPTIONS] [-o OUTFILE] [-c FILE(s).c]  compile to out\n"
    "\n"
    "Option   Long option   Meaning\n"
    "  -o                   set output filename\n"
    "  -c                   compile infile(s) filename(s)\n"
    "  -run                 run in memory with other options\n"
    "  -w                   disable all warnings\n"
    "  -v     --version     show version\n"
    "  -vv                  show search paths or loaded files\n"
    "  -h -hh --help        show this, show more help\n"
    "  -bench               show compilation statistics\n"
    "  -g                   generate runtime debug info\n"
#ifdef CONFIG_SUGAR_BCHECK
    "  -b                   add memory & bounds checker (implies -g)\n"
    "  -dev                 run with bounds checker (implies -b -run)\n"
#endif
#ifdef CONFIG_SUGAR_BACKTRACE
    "  -bt[N]               configure backtrace [show max N callers]\n"
#endif
    "  -E                   preprocess only\n";

static const char help2[] =
    "Special options:\n"
    "  -P -P1                        with -E: no/alternative #line output\n"
    "  -dD -dM                       with -E: output #define directives\n"
    "  -pthread                      same as -D_REENTRANT and -lpthread\n"
    "  -On                           same as -D__OPTIMIZE__ for n > 0\n"
    "  -Wp,-opt                      same as -opt\n"
    "  -include file                 include 'file' above each input file\n"
    "  -isystem dir                  add 'dir' to system include path\n"
    "  -static                       link to static libraries (not recommended)\n"
    "  -dumpversion                  print version\n"
    "  -print-search-dirs            print search paths\n"
    "  -dt                           with -run/-E: auto-define 'test_...' macros\n"
    "Ignored options:\n"
    "  --param  -pedantic  -pipe  -s  -traditional\n"
    "-W[no-]... warnings:\n"
    "  all                           turn on some (*) warnings\n"
    "  error                         stop after first warning\n"
    "  unsupported                   warn about ignored options, pragmas, etc.\n"
    "  write-strings                 strings are const\n"
    "  implicit-function-declaration warn for missing prototype (*)\n"
    "-f[no-]... flags:\n"
    "  unsigned-char                 default char is unsigned\n"
    "  signed-char                   default char is signed\n"
    "  common                        use common section instead of bss\n"
    "  leading-underscore            decorate extern symbols\n"
    "  ms-extensions                 allow anonymous struct in struct\n"
    "  dollars-in-identifiers        allow '$' in C symbols\n"
    "-m... target specific options:\n"
    "  ms-bitfields                  use MSVC bitfield layout\n"
#ifdef SUGAR_TARGET_ARM
    "  float-abi                     hard/softfp on arm\n"
#endif
#ifdef SUGAR_TARGET_X86_64
    "  no-sse                        disable floats on x86_64\n"
#endif
    "-Wl,... linker options:\n"
    "  -nostdlib                     do not link with standard crt/libs\n"
    "  -[no-]whole-archive           load lib(s) fully/only as needed\n"
    "  -export-all-symbols           same as -rdynamic\n"
    "  -export-dynamic               same as -rdynamic\n"
    "  -image-base= -Ttext=          set base address of executable\n"
    "  -section-alignment=           set section alignment in executable\n"
#ifdef SUGAR_TARGET_PE
    "  -file-alignment=              set PE file alignment\n"
    "  -stack=                       set PE stack reserve\n"
    "  -large-address-aware          set related PE option\n"
    "  -subsystem=[console/windows]  set PE subsystem\n"
    "  -oformat=[pe-* binary]        set executable output format\n"
    "Predefined macros:\n"
    "  sugar -E -dM - < nul\n"
#else
    "  -rpath=                       set dynamic library search path\n"
    "  -enable-new-dtags             set DT_RUNPATH instead of DT_RPATH\n"
    "  -soname=                      set DT_SONAME elf tag\n"
    "  -Bsymbolic                    set DT_SYMBOLIC elf tag\n"
    "  -oformat=[elf32/64-* binary]  set executable output format\n"
    "  -init= -fini= -as-needed -O   (ignored)\n"
    "Predefined macros:\n"
    "  sugar -E -dM - < /dev/null\n"
#endif
    "Preprocessor options:\n"
    "  -Idir        add include path 'dir'\n"
    "  -Dsym[=val]  define 'sym' with value 'val'\n"
    "  -Usym        undefine 'sym'\n"
    "  -E           preprocess only\n"
    "Linker options:\n"
    "  -Ldir        add library path 'dir'\n"
    "  -llib        link with dynamic or static library 'lib'\n"
    "  -r           generate (relocatable) object file\n"
    "  -shared      generate a shared library/dll\n"
    "  -rdynamic    export all global symbols to dynamic linker\n"
    "  -soname      set name for shared library to be used at runtime\n"
    "  -Wl,-opt[=val]  set linker option (see sugar -hh)\n"
    "Misc. options:\n"
    "  -            use stdin pipe as infile\n"
    "  @listfile    read arguments from listfile\n"
    "  -std=c99     Conform to the ISO 1999 C standard (default).\n"
    "  -std=c11     Conform to the ISO 2011 C standard.\n"
    "  -x[c|a|b|n]  specify type of the next infile (C,ASM,BIN,NONE)\n"
    "  -nostdinc    do not use standard system include paths\n"
    "  -nostdlib    do not link with standard crt and libraries\n"
    "  -Bdir        set sugar's private include/library dir\n"
    "  -MD          generate dependency file for make\n"
    "  -MF file     specify dependency file name\n"
#if defined(SUGAR_TARGET_I386) || defined(SUGAR_TARGET_X86_64)
    "  -m32/64      defer to i386/x86_64 cross compiler\n"
#endif
    "Tools:\n"
    "  create library  : sugar -ar [rcsv] lib.a files\n"
#ifdef SUGAR_TARGET_PE
    "  create def file : sugar -impdef lib.dll [-v] [-o lib.def]\n"
#endif
    "See also the manual for more details.\n";

static const char version[] =
"    ___ _   _  __ _  __ _ _ __   ____\n"
"   / __| | | |/ _` |/ _` | '_/  / __/\n"
"   \\__ \\ |_| | (_| | (_| | |   | (__\n"
"   |___/\\__,_|\\__, |\\__,_|_|    \\___\\\n"
"              |___/       " SUGAR_VERSION "\n"
"   [tcc-" TINYC_VERSION "-"
#ifdef SUGAR_TARGET_I386
    "386"
#elif defined SUGAR_TARGET_X86_64
    "x86"
#elif defined SUGAR_TARGET_C67
    "c67"
#elif defined SUGAR_TARGET_ARM
    "arm"
#elif defined SUGAR_TARGET_ARM64
    "a64"
#elif defined SUGAR_TARGET_RISCV64
    "rsc"
#endif
#ifdef SUGAR_ARM_HARDFLOAT
    "-hdf"
#endif
#ifdef SUGAR_TARGET_PE
    "-win"
#elif defined(SUGAR_TARGET_MACHO)
    "-osx"
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    "-bsd"
#else
    "-lnx"
#endif
    "]\n\n";

static void print_dirs(const char *msg, char **paths, int nb_paths)
{
    int i;
    printf("%s:\n%s", msg, nb_paths ? "" : "  -\n");
    for(i = 0; i < nb_paths; i++)
        printf("  %s\n", paths[i]);
}

static void print_search_dirs(SUGARState *s)
{
    printf("install: %s\n", s->sugar_lib_path);
    /* print_dirs("programs", NULL, 0); */
    print_dirs("include", s->sysinclude_paths, s->nb_sysinclude_paths);
    print_dirs("libraries", s->library_paths, s->nb_library_paths);
#ifdef SUGAR_TARGET_PE
    printf("libsugar1:\n  %s/lib/"SUGAR_LIBSUGAR1"\n", s->sugar_lib_path);
#else
    printf("libsugar1:\n  %s/"SUGAR_LIBSUGAR1"\n", s->sugar_lib_path);
    print_dirs("crt", s->crt_paths, s->nb_crt_paths);
    printf("elfinterp:\n  %s\n",  DEFAULT_ELFINTERP(s));
#endif
}

static void set_environment(SUGARState *s)
{
    char * path;

    path = getenv("C_INCLUDE_PATH");
    if(path != NULL) {
        sugar_add_sysinclude_path(s, path);
    }
    path = getenv("CPATH");
    if(path != NULL) {
        sugar_add_include_path(s, path);
    }
    path = getenv("LIBRARY_PATH");
    if(path != NULL) {
        sugar_add_library_path(s, path);
    }
}

static char *default_outputfile(SUGARState *s, const char *first_file)
{
    char buf[1024];
    char *ext;
    const char *name = "a";

    if (first_file && strcmp(first_file, "-"))
        name = sugar_basename(first_file);
    snprintf(buf, sizeof(buf), "%s", name);
    ext = sugar_fileextension(buf);
#ifdef SUGAR_TARGET_PE
    if (s->output_type == SUGAR_OUTPUT_DLL)
        strcpy(ext, ".dll");
    else
    if (s->output_type == SUGAR_OUTPUT_EXE)
        strcpy(ext, ".exe");
    else
#endif
    if (s->output_type == SUGAR_OUTPUT_OBJ && !s->option_r && *ext)
        strcpy(ext, ".o");
    else
        strcpy(buf, "a.out");
    return sugar_strdup(buf);
}

static unsigned getclock_ms(void)
{
#ifdef _WIN32
    return GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000 + (tv.tv_usec+500)/1000;
#endif
}

int main(int argc0, char **argv0)
{
    SUGARState *s, *s1;
    int ret, opt, n = 0, t = 0, done;
    unsigned start_time = 0;
    const char *first_file;
    int argc; char **argv;
    FILE *ppfp = stdout;

redo:
    argc = argc0, argv = argv0;
    s = s1 = sugar_new();
    opt = sugar_parse_args(s, &argc, &argv, 1);

    if (n == 0) {
#ifdef SUGAR_IS_NATIVE
        if(!opt && !(s->outfile) && argc > 1 && argv[1][0] != '-' && s->output_type != SUGAR_OUTPUT_MEMORY) {
            set_environment(s);
            sugar_set_output_type(s, SUGAR_OUTPUT_MEMORY);
            if (sugar_add_file(s, argv[1]) < 0)
                return 1;
            else
                return sugar_run(s, argc-1, argv+1);     
        }
#endif
        if (opt == OPT_HELP) {
            fputs(help, stdout);
            return 0;
        }
        if (opt == OPT_HELP2) {
            fputs(help2, stdout);
            return 0;
        }
        if (opt == OPT_M32 || opt == OPT_M64)
            sugar_tool_cross(s, argv, opt); /* never returns */
        if (s->verbose)
            printf(version);
        if (opt == OPT_AR)
            return sugar_tool_ar(s, argc, argv);
#ifdef SUGAR_TARGET_PE
        if (opt == OPT_IMPDEF)
            return sugar_tool_impdef(s, argc, argv);
#endif
        if (opt == OPT_V)
            return 0;
        if (opt == OPT_PRINT_DIRS) {
            /* initialize search dirs */
            set_environment(s);
            sugar_set_output_type(s, SUGAR_OUTPUT_MEMORY);
            print_search_dirs(s);
            return 0;
        }

        if (s->nb_files == 0)
            sugar_error("no input files\n");

        if (s->output_type == SUGAR_OUTPUT_PREPROCESS) {
            if (s->outfile && 0!=strcmp("-",s->outfile)) {
                ppfp = fopen(s->outfile, "w");
                if (!ppfp)
                    sugar_error("could not write '%s'", s->outfile);
            }
        } else if (s->output_type == SUGAR_OUTPUT_OBJ && !s->option_r) {
            if (s->nb_libraries)
                sugar_error("cannot specify libraries with -c");
            if (s->nb_files > 1 && s->outfile)
                sugar_error("cannot specify output file with -c many files");
        }

        if (s->do_bench)
            start_time = getclock_ms();
    }

    set_environment(s);
    if (s->output_type == 0)
        s->output_type = SUGAR_OUTPUT_EXE;
    sugar_set_output_type(s, s->output_type);
    s->ppfp = ppfp;

    if ((s->output_type == SUGAR_OUTPUT_MEMORY
      || s->output_type == SUGAR_OUTPUT_PREPROCESS)
        && (s->dflag & 16)) { /* -dt option */
        if (t)
            s->dflag |= 32;
        s->run_test = ++t;
        if (n)
            --n;
    }

    /* compile or add each files or library */
    first_file = NULL, ret = 0;
    do {
        struct filespec *f = s->files[n];
        s->filetype = f->type;
        if (f->type & AFF_TYPE_LIB) {
            if (sugar_add_library_err(s, f->name) < 0)
                ret = 1;
        } else {
            if (1 == s->verbose)
                printf("-> %s\n", f->name);
            if (!first_file)
                first_file = f->name;
            if (sugar_add_file(s, f->name) < 0)
                ret = 1;
        }
        done = ret || ++n >= s->nb_files;
    } while (!done && (s->output_type != SUGAR_OUTPUT_OBJ || s->option_r));

    if (s->run_test) {
        t = 0;
    } else if (s->output_type == SUGAR_OUTPUT_PREPROCESS) {
        ;
    } else if (0 == ret) {
        if (s->output_type == SUGAR_OUTPUT_MEMORY) {
#ifdef SUGAR_IS_NATIVE
            ret = sugar_run(s, argc, argv);
#endif
        } else {
            if (!s->outfile)
                s->outfile = default_outputfile(s, first_file);
            if (sugar_output_file(s, s->outfile))
                ret = 1;
            else if (s->gen_deps)
                gen_makedeps(s, s->outfile, s->deps_outfile);
        }
    }

    if (s->do_bench && done && !(t | ret))
        sugar_print_stats(s, getclock_ms() - start_time);
    sugar_delete(s);
    if (!done)
        goto redo; /* compile more files with -c */
    if (t)
        goto redo; /* run more tests with -dt -run */
    if (ppfp && ppfp != stdout)
        fclose(ppfp);
    return ret;
}
