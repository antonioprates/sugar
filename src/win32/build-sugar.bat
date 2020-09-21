@rem ------------------------------------------------------
@rem batch file to build sugar using mingw, msvc or sugar itself
@rem ------------------------------------------------------

@echo off
setlocal
if (%1)==(-clean) goto :cleanup
set CC=gcc
set /p VERSION= < ..\VERSION
set INST=
set BIN=
set DOC=no
set EXES_ONLY=no
goto :a0
:a2
shift
:a3
shift
:a0
if not (%1)==(-c) goto :a1
set CC=%~2
if (%2)==(cl) set CC=@call :cl
goto :a2
:a1
if (%1)==(-t) set T=%2&& goto :a2
if (%1)==(-v) set VERSION=%~2&& goto :a2
if (%1)==(-i) set INST=%2&& goto :a2
if (%1)==(-b) set BIN=%2&& goto :a2
if (%1)==(-d) set DOC=yes&& goto :a3
if (%1)==(-x) set EXES_ONLY=yes&& goto :a3
if (%1)==() goto :p1
:usage
echo usage: build-sugar.bat [ options ... ]
echo options:
echo   -c prog              use prog (gcc/sugar/cl) to compile sugar
echo   -c "prog options"    use prog with options to compile sugar
echo   -t 32/64             force 32/64 bit default target
echo   -v "version"         set sugar version
echo   -i sugardir            install sugar into sugardir
echo   -b bindir            optionally install binaries into bindir elsewhere
echo   -d                   create sugar-doc.html too (needs makeinfo)
echo   -x                   just create the executables
echo   -clean               delete all previously produced files and directories
exit /B 1

@rem ------------------------------------------------------
@rem sub-routines

:cleanup
set LOG=echo
%LOG% removing files:
for %%f in (*sugar.exe libsugar.dll lib\*.a) do call :del_file %%f
for %%f in (..\config.h ..\config.texi) do call :del_file %%f
for %%f in (include\*.h) do @if exist ..\%%f call :del_file %%f
for %%f in (include\sugarlib.h examples\libsugar_test.c) do call :del_file %%f
for %%f in (lib\*.o *.o *.obj *.def *.pdb *.lib *.exp *.ilk) do call :del_file %%f
%LOG% removing directories:
for %%f in (doc libsugar) do call :del_dir %%f
%LOG% done.
exit /B 0
:del_file
if exist %1 del %1 && %LOG%   %1
exit /B 0
:del_dir
if exist %1 rmdir /Q/S %1 && %LOG%   %1
exit /B 0

:cl
@echo off
set CMD=cl
:c0
set ARG=%1
set ARG=%ARG:.dll=.lib%
if (%1)==(-shared) set ARG=-LD
if (%1)==(-o) shift && set ARG=-Fe%2
set CMD=%CMD% %ARG%
shift
if not (%1)==() goto :c0
echo on
%CMD% -O1 -W2 -Zi -MT -GS- -nologo -link -opt:ref,icf
@exit /B %ERRORLEVEL%

@rem ------------------------------------------------------
@rem main program

:p1
if not %T%_==_ goto :p2
set T=32
if %PROCESSOR_ARCHITECTURE%_==AMD64_ set T=64
if %PROCESSOR_ARCHITEW6432%_==AMD64_ set T=64
:p2
if "%CC:~-3%"=="gcc" set CC=%CC% -Os -s -static
set D32=-DSUGAR_TARGET_PE -DSUGAR_TARGET_I386
set D64=-DSUGAR_TARGET_PE -DSUGAR_TARGET_X86_64
set P32=i386-win32
set P64=x86_64-win32
if %T%==64 goto :t64
set D=%D32%
set DX=%D64%
set PX=%P64%
goto :p3
:t64
set D=%D64%
set DX=%D32%
set PX=%P32%
goto :p3

:p3
@echo on

:config.h
echo>..\config.h #define SUGAR_VERSION "%VERSION%"
echo>> ..\config.h #ifdef SUGAR_TARGET_X86_64
echo>> ..\config.h #define SUGAR_LIBSUGAR1 "libsugar1-64.a"
echo>> ..\config.h #else
echo>> ..\config.h #define SUGAR_LIBSUGAR1 "libsugar1-32.a"
echo>> ..\config.h #endif

for %%f in (*sugar.exe *sugar.dll) do @del %%f

:compiler
%CC% -o libsugar.dll -shared ..\libsugar.c %D% -DLIBSUGAR_AS_DLL
@if errorlevel 1 goto :the_end
%CC% -o sugar.exe ..\sugar.c libsugar.dll %D% -DONE_SOURCE"=0"
%CC% -o %PX%-sugar.exe ..\sugar.c %DX%

@if (%EXES_ONLY%)==(yes) goto :files-done

if not exist libsugar mkdir libsugar
if not exist doc mkdir doc
copy>nul ..\include\*.h include
copy>nul ..\sugarlib.h include
copy>nul ..\libsugar.h libsugar
copy>nul ..\tests\libsugar_test.c examples
copy>nul sugar-win32.txt doc

.\sugar -impdef libsugar.dll -o libsugar\libsugar.def
@if errorlevel 1 goto :the_end

:libsugar1.a
@set O1=libsugar1.o crt1.o crt1w.o wincrt1.o wincrt1w.o dllcrt1.o dllmain.o chkstk.o
.\sugar -m32 -c ../lib/libsugar1.c
.\sugar -m32 -c lib/crt1.c
.\sugar -m32 -c lib/crt1w.c
.\sugar -m32 -c lib/wincrt1.c
.\sugar -m32 -c lib/wincrt1w.c
.\sugar -m32 -c lib/dllcrt1.c
.\sugar -m32 -c lib/dllmain.c
.\sugar -m32 -c lib/chkstk.S
.\sugar -m32 -c ../lib/alloca86.S
.\sugar -m32 -c ../lib/alloca86-bt.S
.\sugar -m32 -ar lib/libsugar1-32.a %O1% alloca86.o alloca86-bt.o
@if errorlevel 1 goto :the_end
.\sugar -m64 -c ../lib/libsugar1.c
.\sugar -m64 -c lib/crt1.c
.\sugar -m64 -c lib/crt1w.c
.\sugar -m64 -c lib/wincrt1.c
.\sugar -m64 -c lib/wincrt1w.c
.\sugar -m64 -c lib/dllcrt1.c
.\sugar -m64 -c lib/dllmain.c
.\sugar -m64 -c lib/chkstk.S
.\sugar -m64 -c ../lib/alloca86_64.S
.\sugar -m64 -c ../lib/alloca86_64-bt.S
.\sugar -m64 -ar lib/libsugar1-64.a %O1% alloca86_64.o alloca86_64-bt.o
@if errorlevel 1 goto :the_end
.\sugar -m%T% -c ../lib/bcheck.c -o lib/bcheck.o -g
.\sugar -m%T% -c ../lib/bt-exe.c -o lib/bt-exe.o
.\sugar -m%T% -c ../lib/bt-log.c -o lib/bt-log.o
.\sugar -m%T% -c ../lib/bt-dll.c -o lib/bt-dll.o

:sugar-doc.html
@if not (%DOC%)==(yes) goto :doc-done
echo>..\config.texi @set VERSION %VERSION%
cmd /c makeinfo --html --no-split ../sugar-doc.texi -o doc/sugar-doc.html
:doc-done

:files-done
for %%f in (*.o *.def) do @del %%f

:copy-install
@if (%INST%)==() goto :the_end
if not exist %INST% mkdir %INST%
@if (%BIN%)==() set BIN=%INST%
if not exist %BIN% mkdir %BIN%
for %%f in (*sugar.exe *sugar.dll) do @copy>nul %%f %BIN%\%%f
@if not exist %INST%\lib mkdir %INST%\lib
for %%f in (lib\*.a lib\*.o lib\*.def) do @copy>nul %%f %INST%\%%f
for %%f in (include examples libsugar doc) do @xcopy>nul /s/i/q/y %%f %INST%\%%f

:the_end
exit /B %ERRORLEVEL%
