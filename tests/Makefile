#
# Sugar C Compiler Makefile - tests
#

TOP = ..
include $(TOP)/Makefile
VPATH = $(TOPSRC)/tests $(TOPSRC) $(TOP)
CFLAGS := $(filter-out -W% -g% -O%,$(CFLAGS)) -I$(TOPSRC) $(LDFLAGS)

# what tests to run
TESTS = \
 hello-exe \
 hello-run \
 libtest \
 libtest_mt \
 test3 \
 memtest \
 dlltest \
 abitest \
 asm-c-connect-test \
 vla_test-run \
 cross-test \
 tests2-dir \
 pp-dir

BTESTS = btest test1b
# test4_static -- Not all relocation types are implemented yet.
# asmtest / asmtest2 -- minor differences with gcc

# bounds-checking is supported on i386 and x86_64 on linux and windows
ifeq (-$(CONFIG_musl)-, --)
ifeq ($(ARCH),i386)
 TESTS += $(BTESTS)
endif
ifeq ($(ARCH),x86_64)
 TESTS += $(BTESTS)
endif
ifeq ($(ARCH),arm)
 TESTS += $(BTESTS)
endif
ifeq ($(ARCH),arm64)
 TESTS += $(BTESTS)
endif
ifeq ($(ARCH),riscv64)
 TESTS += $(BTESTS)
endif
endif
ifdef CONFIG_OSX # some don't work yet
 TESTS := $(filter-out dlltest, $(TESTS))
endif
ifeq (,$(filter arm64 i386 x86_64,$(ARCH)))
 TESTS := $(filter-out vla_test-run,$(TESTS))
endif
ifeq ($(CONFIG_arm_eabi),yes)
 TESTS := $(filter-out test3,$(TESTS))
endif
ifeq (,$(filter i386 x86_64,$(ARCH)))
 TESTS := $(filter-out dlltest asm-c-connect-test,$(TESTS))
endif

ifeq ($(OS),Windows_NT) # for libsugar_test to find libsugar.dll
 PATH := $(CURDIR)/$(TOP)$(if $(findstring ;,$(PATH)),;,:)$(PATH)
endif

ifdef CONFIG_OSX
LIBS += $(LINK_LIBSUGAR)
endif


ifeq ($(ARCH),arm)
# sugartest refers to the alignment of functions, and with thumb mode
# the low bit of code addresses selects the mode, so the "alignment"
# of functions via bit masking comes out as 1.  Just disable thumb.
test.ref: CFLAGS+=-marm
endif
ifeq ($(ARCH),i386)
# sugartest.c:get_asm_string uses a construct that is checked too strictly
# by GCC in 32bit mode when PIC is enabled.
test.ref: CFLAGS+=-fno-PIC -fno-PIE
endif
ifeq ($(CC_NAME),msvc)
test.ref abitest : CC = gcc
endif

RUN_SUGAR = $(NATIVE_DEFINES) -run $(TOPSRC)/sugar.c $(SUGARFLAGS)
DISAS = objdump -d
ifdef CONFIG_OSX
DUMPSUGAR = (set -x; $(TOP)/sugar -vv; otool -L $(TOP)/sugar; exit 1)
else
DUMPSUGAR = (set -x; $(TOP)/sugar -vv; ldd $(TOP)/sugar; exit 1)
endif

all test :
	@$(MAKE) --no-print-directory -s clean
	@$(MAKE) --no-print-directory -s -r $(TESTS)

hello-exe: ../examples/ex1.c
	@echo ------------ $@ ------------
	$(SUGAR) $< -o hello$(EXESUF) && ./hello$(EXESUF) || $(DUMPSUGAR)

hello-run: ../examples/ex1.c
	@echo ------------ $@ ------------
	$(SUGAR) -run $< || $(DUMPSUGAR)

libtes%: libsugar_tes%$(EXESUF)
	@echo ------------ $@ ------------
	./libsugar_tes$*$(EXESUF) $(TOPSRC)/sugar.c $(SUGARFLAGS) $(NATIVE_DEFINES)

libsugar_test$(EXESUF): libsugar_test.c $(LIBSUGAR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

libsugar_test_mt$(EXESUF): libsugar_test_mt.c $(LIBSUGAR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%-dir:
	@echo ------------ $@ ------------
	$(MAKE) -k -C $*

# test.ref - generate using cc
test.ref: sugartest.c
	$(CC) -o sugartest.gcc $< $(NATIVE_DEFINES) $(CFLAGS) -w -O0 -std=gnu99 -fno-omit-frame-pointer
	./sugartest.gcc > $@

# auto test
test1 test1b: sugartest.c test.ref
	@echo ------------ $@ ------------
	$(SUGAR) $(RUN_SUGAR) -w -run $< > test.out1
	@diff -u test.ref test.out1 && echo "$(AUTO_TEST) OK"

# iterated test2 (compile sugar then compile sugartest.c !)
test2 test2b: sugartest.c test.ref
	@echo ------------ $@ ------------
	$(SUGAR) $(RUN_SUGAR) $(RUN_SUGAR) -w -run $< > test.out2
	@diff -u test.ref test.out2 && echo "$(AUTO_TEST)2 OK"

# iterated test3 (compile sugar then compile sugar then compile sugartest.c !)
test3 test3b: sugartest.c test.ref
	@echo ------------ $@ ------------
	$(SUGAR) $(RUN_SUGAR) $(RUN_SUGAR) $(RUN_SUGAR) -w -run $< > test.out3
	@diff -u test.ref test.out3 && echo "$(AUTO_TEST)3 OK"

AUTO_TEST = Auto Test
test%b : SUGARFLAGS += -b -bt1
test%b : AUTO_TEST = Auto Bound-Test

# binary output test
test4: sugartest.c test.ref
	@echo ------------ $@ ------------
# object + link output
	$(SUGAR) -c -o sugartest3.o $<
	$(SUGAR) -o sugartest3 sugartest3.o
	./sugartest3 > test3.out
	@if diff -u test.ref test3.out ; then echo "Object $(AUTO_TEST) OK"; fi
# dynamic output
	$(SUGAR) -o sugartest1 $<
	./sugartest1 > test1.out
	@if diff -u test.ref test1.out ; then echo "Dynamic $(AUTO_TEST) OK"; fi
# dynamic output + bound check
	$(SUGAR) -b -o sugartest4 $<
	./sugartest4 > test4.out
	@if diff -u test.ref test4.out ; then echo "BCheck $(AUTO_TEST) OK"; fi

test4_static: sugartest.c test.ref
	@echo ------------ $@ ------------
# static output.
	$(SUGAR) -static -o sugartest2 $<
	./sugartest2 > test2.out
	@if diff -u test.ref test2.out ; then echo "Static $(AUTO_TEST) OK"; fi

# use sugar to create libsugar.so/.dll and the sugar(.exe) frontend and run them
dlltest:
	@echo ------------ $@ ------------
	$(SUGAR) $(NATIVE_DEFINES) -DLIBSUGAR_AS_DLL $(TOPSRC)/libsugar.c $(LIBS) -shared -o libsugar2$(DLLSUF)
	$(SUGAR) $(NATIVE_DEFINES) -DONE_SOURCE=0 $(TOPSRC)/sugar.c libsugar2$(DLLSUF) $(LIBS) -Wl,-rpath=. -o sugar2$(EXESUF)
	./sugar2$(EXESUF) $(SUGARFLAGS) $(RUN_SUGAR) -run $(TOPSRC)/examples/ex1.c
ifndef CONFIG_WIN32
	@echo ------------ $@ with PIC ------------
	$(CC) $(CFLAGS) -fPIC $(NATIVE_DEFINES) -DLIBSUGAR_AS_DLL -c $(TOPSRC)/libsugar.c
	$(SUGAR) libsugar.o $(LIBS) -shared -o libsugar2$(DLLSUF)
	$(SUGAR) $(NATIVE_DEFINES) -DONE_SOURCE=0 $(TOPSRC)/sugar.c libsugar2$(DLLSUF) $(LIBS) -Wl,-rpath=. -o sugar2$(EXESUF)
	./sugar2$(EXESUF) $(SUGARFLAGS) $(RUN_SUGAR) -run $(TOPSRC)/examples/ex1.c
endif
	@rm sugar2$(EXESUF) libsugar2$(DLLSUF)

memtest:
	@echo ------------ $@ ------------
	$(CC) $(CFLAGS) $(NATIVE_DEFINES) -DMEM_DEBUG=2 $(TOPSRC)/sugar.c $(LIBS) -o memtest-sugar$(EXESUF)
	./memtest-sugar$(EXESUF) $(SUGARFLAGS) $(NATIVE_DEFINES) $(TOPSRC)/sugar.c $(LIBS)
	./memtest-sugar$(EXESUF) $(SUGARFLAGS) $(NATIVE_DEFINES) -run $(TOPSRC)/sugar.c $(SUGARFLAGS) -w $(TOPSRC)/tests/sugartest.c
	@echo OK

# memory and bound check auto test
BOUNDS_OK  = 1 4 8 10 14 16
BOUNDS_FAIL= 2 5 6 7 9 11 12 13 15 17 18

btest: boundtest.c
	@echo ------------ $@ ------------
	@for i in $(BOUNDS_OK); do \
	   if $(SUGAR) -b -run $< $$i >/dev/null 2>&1 ; then \
	       echo "Test $$i succeeded as expected" ; \
	   else\
	       echo "Failed positive test $$i" ; exit 1 ; \
	   fi ;\
	done ;\
	for i in $(BOUNDS_FAIL); do \
	   if $(SUGAR) -b -bt1 -run $< $$i >/dev/null 2>&1 ; then \
	       echo "Failed negative test $$i" ; exit 1 ;\
	   else\
	       echo "Test $$i failed as expected" ; \
	   fi ;\
	done ;\
	echo Bound test OK

# speed test
speedtest: ex2 ex3
	@echo ------------ $@ ------------
	time ./ex2 1238 2 3 4 10 13 4
	time $(SUGAR) -run $(TOPSRC)/examples/ex2.c 1238 2 3 4 10 13 4
	time ./ex3 35
	time $(SUGAR) -run $(TOPSRC)/examples/ex3.c 35

weaktest: sugartest.c test.ref
	@echo ------------ $@ ------------
	$(SUGAR) -c $< -o weaktest.sugar.o
	$(CC) -c $< -o weaktest.gcc.o $(NATIVE_DEFINES) $(CFLAGS) -w -O0 -std=gnu99 -fno-omit-frame-pointer
	objdump -t weaktest.sugar.o | grep ' w ' | sed -e 's/.* \([a-zA-Z0-9_]*\)$$/\1/' | LC_ALL=C sort > weaktest.sugar.o.txt
	objdump -t weaktest.gcc.o | grep ' w ' | sed -e 's/.* \([a-zA-Z0-9_]*\)$$/\1/' | LC_ALL=C sort > weaktest.gcc.o.txt
	diff weaktest.gcc.o.txt weaktest.sugar.o.txt && echo "Weak Auto Test OK"

ex%: $(TOPSRC)/examples/ex%.c
	$(CC) -o $@ $< $(CFLAGS)

# tiny assembler testing
asmtest.ref: asmtest.S
	$(CC) -Wa,-W -o asmtest.ref.o -c asmtest.S
	objdump -D asmtest.ref.o > asmtest.ref

asmtest asmtest2: asmtest.ref
	@echo ------------ $@ ------------
	$(SUGAR) $(MAYBE_RUN_SUGAR) -c asmtest.S
	objdump -D asmtest.o > asmtest.out
	@if diff -u --ignore-matching-lines="file format" asmtest.ref asmtest.out ; then echo "ASM Auto Test OK"; fi

# test assembler with sugar compiled by itself
asmtest2: MAYBE_RUN_SUGAR = $(RUN_SUGAR)

# Check that code generated by libsugar is binary compatible with
# that generated by CC
abitest-cc.exe: abitest.c $(LIBSUGAR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -w

abitest-sugar.exe: abitest.c libsugar.c
	$(SUGAR) -o $@ $^ $(NATIVE_DEFINES) $(LIBS)

abitest-% : abitest-%.exe
	@echo ------------ $@ ------------
	./$< $(SUGARFLAGS)

abitest: abitest-cc
ifneq ($(CONFIG_arm_eabi),yes) # not ARM soft-float
abitest: abitest-sugar
endif

vla_test$(EXESUF): vla_test.c
	$(SUGAR) -o $@ $^

vla_test-run: vla_test$(EXESUF)
	@echo ------------ $@ ------------
	./vla_test$(EXESUF)

asm-c-connect$(EXESUF): asm-c-connect-1.c asm-c-connect-2.c
	$(SUGAR) -o $@ $^

asm-c-connect-%.o: asm-c-connect-%.c
	$(SUGAR) -c -o $@ $<

asm-c-connect-sep$(EXESUF): asm-c-connect-1.o asm-c-connect-2.o
	$(SUGAR) -o $@ $^

asm-c-connect-test: asm-c-connect$(EXESUF) asm-c-connect-sep$(EXESUF)
	@echo ------------ $@ ------------
	./asm-c-connect$(EXESUF) > asm-c-connect.out1 && cat asm-c-connect.out1
	./asm-c-connect-sep$(EXESUF) > asm-c-connect.out2 && cat asm-c-connect.out2
	@diff -u asm-c-connect.out1 asm-c-connect.out2 || (echo "error"; exit 1)

SUGAR_YY = $(foreach T,$(SUGAR_X),$(if $(wildcard $(TOP)/$T-sugar$(EXESUF)),$T))

cross-test :
	$(if $(strip $(SUGAR_YY)),\
	    $(MAKE) $(foreach T,$(SUGAR_YY),cross-$T.test) --no-print-directory,:)

cross-%.test :
	@echo ------------ $@ ------------
	$(TOP)/$*-sugar$(EXESUF) -v $(SUGARFLAGS-$(if $(findstring win,$*),win,unx))\
	    -c $(TOPSRC)/examples/ex3.c

# targets for development
%.bin: %.c sugar
	$(SUGAR) -g -o $@ $<
	$(DISAS) $@

instr: instr.o
	objdump -d instr.o

instr.o: instr.S
	$(CC) -o $@ -c $< -O2 -Wall -g

cache: sugar_g
	cachegrind ./sugar_g -o /tmp/linpack -lm bench/linpack.c
	vg_annotate sugar.c > /tmp/linpack.cache.log

# clean
clean:
	rm -f *~ *.o *.a *.bin *.i *.ref *.out *.out? *.out?b *.cc *.gcc
	rm -f *-cc *-gcc *-sugar *.exe hello libsugar_test vla_test sugartest[1234]
	rm -f asm-c-connect$(EXESUF) asm-c-connect-sep$(EXESUF)
	rm -f ex? sugar_g weaktest.*.txt *.def *.pdb *.obj libsugar_test_mt
	@$(MAKE) -C tests2 $@
	@$(MAKE) -C pp $@

