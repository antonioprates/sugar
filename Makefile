# --------------------------------------------------------------------------
#
# Sugar C Compiler Makefile
#

ifndef TOP
 TOP = .
 INCLUDED = no
endif

ifeq ($(findstring $(MAKECMDGOALS),clean distclean),)
 include $(TOP)/config.mak
endif

ifeq (-$(GCC_MAJOR)-$(findstring $(GCC_MINOR),56789)-,-4--)
 CFLAGS += -D_FORTIFY_SOURCE=0
endif

LIBSUGAR = libsugar.a
LIBSUGAR1 = libsugar1.a
LINK_LIBSUGAR =
LIBS =
CFLAGS += -I$(TOP)
CFLAGS += $(CPPFLAGS)
VPATH = $(TOPSRC)

ifdef CONFIG_WIN32
 CFG = -win
 ifneq ($(CONFIG_static),yes)
  LIBSUGAR = libsugar$(DLLSUF)
  LIBSUGARDEF = libsugar.def
 endif
 NATIVE_TARGET = $(ARCH)-win$(if $(findstring arm,$(ARCH)),ce,32)
else
 CFG = -unx
 LIBS=-lm -lpthread
 ifneq ($(CONFIG_ldl),no)
  LIBS+=-ldl
 endif
 # make libsugar as static or dynamic library?
 ifeq ($(CONFIG_static),no)
  LIBSUGAR=libsugar$(DLLSUF)
  export LD_LIBRARY_PATH := $(CURDIR)/$(TOP)
  ifneq ($(CONFIG_rpath),no)
    ifndef CONFIG_OSX
      LINK_LIBSUGAR += -Wl,-rpath,"$(libdir)"
    else
      # macOS doesn't support env-vars libdir out of the box - which we need for
      # `make test' when libsugar.dylib is used (configure --disable-static), so
      # we bake a relative path into the binary. $libdir is used after install.
      LINK_LIBSUGAR += -Wl,-rpath,"@executable_path/$(TOP)" -Wl,-rpath,"$(libdir)"
      DYLIBVER += -current_version $(VERSION)
      DYLIBVER += -compatibility_version $(VERSION)
    endif
  endif
 endif
 NATIVE_TARGET = $(ARCH)
 ifdef CONFIG_OSX
  NATIVE_TARGET = $(ARCH)-osx
  ifneq ($(CC_NAME),sugar)
    LDFLAGS += -flat_namespace -undefined warning
  endif
  export MACOSX_DEPLOYMENT_TARGET := 10.6
 endif
endif

# run local version of sugar with local libraries and includes
SUGARFLAGS-unx = -B$(TOP) -I$(TOPSRC)/include -I$(TOPSRC) -I$(TOP)
SUGARFLAGS-win = -B$(TOPSRC)/win32 -I$(TOPSRC)/include -I$(TOPSRC) -I$(TOP) -L$(TOP)
SUGARFLAGS = $(SUGARFLAGS$(CFG))
SUGAR = $(TOP)/sugar$(EXESUF) $(SUGARFLAGS)

# cross compiler targets to build
SUGAR_X = i386 x86_64 i386-win32 x86_64-win32 x86_64-osx arm arm64 arm-wince c67
SUGAR_X += riscv64
# SUGAR_X += arm-fpa arm-fpa-ld arm-vfp arm-eabi

CFLAGS_P = $(CFLAGS) -pg -static -DCONFIG_SUGAR_STATIC -DSUGAR_PROFILE
LIBS_P = $(LIBS)
LDFLAGS_P = $(LDFLAGS)

CONFIG_$(ARCH) = yes
NATIVE_DEFINES_$(CONFIG_i386) += -DSUGAR_TARGET_I386
NATIVE_DEFINES_$(CONFIG_x86_64) += -DSUGAR_TARGET_X86_64
NATIVE_DEFINES_$(CONFIG_WIN32) += -DSUGAR_TARGET_PE
NATIVE_DEFINES_$(CONFIG_OSX) += -DSUGAR_TARGET_MACHO
NATIVE_DEFINES_$(CONFIG_uClibc) += -DSUGAR_UCLIBC
NATIVE_DEFINES_$(CONFIG_musl) += -DSUGAR_MUSL
NATIVE_DEFINES_$(CONFIG_libgcc) += -DCONFIG_USE_LIBGCC
NATIVE_DEFINES_$(CONFIG_selinux) += -DHAVE_SELINUX
NATIVE_DEFINES_$(CONFIG_arm) += -DSUGAR_TARGET_ARM
NATIVE_DEFINES_$(CONFIG_arm_eabihf) += -DSUGAR_ARM_EABI -DSUGAR_ARM_HARDFLOAT
NATIVE_DEFINES_$(CONFIG_arm_eabi) += -DSUGAR_ARM_EABI
NATIVE_DEFINES_$(CONFIG_arm_vfp) += -DSUGAR_ARM_VFP
NATIVE_DEFINES_$(CONFIG_arm64) += -DSUGAR_TARGET_ARM64
NATIVE_DEFINES_$(CONFIG_riscv64) += -DSUGAR_TARGET_RISCV64
NATIVE_DEFINES += $(NATIVE_DEFINES_yes)

ifeq ($(INCLUDED),no)
# --------------------------------------------------------------------------
# running top Makefile

PROGS = sugar$(EXESUF)
SUGARLIBS = $(LIBSUGARDEF) $(LIBSUGAR) $(LIBSUGAR1)
SUGARDOCS = sugar.1 sugar-doc.html sugar-doc.info

all: $(PROGS) $(SUGARLIBS) $(SUGARDOCS)

# cross libsugar1.a targets to build
LIBSUGAR1_X = i386 x86_64 i386-win32 x86_64-win32 x86_64-osx arm arm64 arm-wince
LIBSUGAR1_X += riscv64

PROGS_CROSS = $(foreach X,$(SUGAR_X),$X-sugar$(EXESUF))
LIBSUGAR1_CROSS = $(foreach X,$(LIBSUGAR1_X),$X-libsugar1.a)

# build cross compilers & libs
cross: $(LIBSUGAR1_CROSS) $(PROGS_CROSS)

# build specific cross compiler & lib
cross-%: %-sugar$(EXESUF) %-libsugar1.a ;

install: ; @$(MAKE) --no-print-directory  install$(CFG)
install-strip: ; @$(MAKE) --no-print-directory  install$(CFG) CONFIG_strip=yes
uninstall: ; @$(MAKE) --no-print-directory uninstall$(CFG)

ifdef CONFIG_cross
all : cross
endif

# --------------------------------------------

T = $(or $(CROSS_TARGET),$(NATIVE_TARGET),unknown)
X = $(if $(CROSS_TARGET),$(CROSS_TARGET)-)

DEF-i386        = -DSUGAR_TARGET_I386
DEF-x86_64      = -DSUGAR_TARGET_X86_64
DEF-i386-win32  = -DSUGAR_TARGET_PE -DSUGAR_TARGET_I386
DEF-x86_64-win32= -DSUGAR_TARGET_PE -DSUGAR_TARGET_X86_64
DEF-x86_64-osx  = -DSUGAR_TARGET_MACHO -DSUGAR_TARGET_X86_64
DEF-arm-wince   = -DSUGAR_TARGET_PE -DSUGAR_TARGET_ARM -DSUGAR_ARM_EABI -DSUGAR_ARM_VFP -DSUGAR_ARM_HARDFLOAT
DEF-arm64       = -DSUGAR_TARGET_ARM64 -Wno-format
DEF-c67         = -DSUGAR_TARGET_C67 -w # disable warnigs
DEF-arm-fpa     = -DSUGAR_TARGET_ARM
DEF-arm-fpa-ld  = -DSUGAR_TARGET_ARM -DLDOUBLE_SIZE=12
DEF-arm-vfp     = -DSUGAR_TARGET_ARM -DSUGAR_ARM_VFP
DEF-arm-eabi    = -DSUGAR_TARGET_ARM -DSUGAR_ARM_VFP -DSUGAR_ARM_EABI
DEF-arm-eabihf  = -DSUGAR_TARGET_ARM -DSUGAR_ARM_VFP -DSUGAR_ARM_EABI -DSUGAR_ARM_HARDFLOAT
DEF-arm         = $(DEF-arm-eabihf)
DEF-riscv64     = -DSUGAR_TARGET_RISCV64
DEF-$(NATIVE_TARGET) = $(NATIVE_DEFINES)

DEFINES += $(DEF-$T) $(DEF-all)
DEFINES += $(if $(ROOT-$T),-DCONFIG_SYSROOT="\"$(ROOT-$T)\"")
DEFINES += $(if $(CRT-$T),-DCONFIG_SUGAR_CRTPREFIX="\"$(CRT-$T)\"")
DEFINES += $(if $(LIB-$T),-DCONFIG_SUGAR_LIBPATHS="\"$(LIB-$T)\"")
DEFINES += $(if $(INC-$T),-DCONFIG_SUGAR_SYSINCLUDEPATHS="\"$(INC-$T)\"")
DEFINES += $(DEF-$(or $(findstring win,$T),unx))

ifneq ($(X),)
ifeq ($(CONFIG_WIN32),yes)
DEF-win += -DSUGAR_LIBSUGAR1="\"$(X)libsugar1.a\""
DEF-unx += -DSUGAR_LIBSUGAR1="\"lib/$(X)libsugar1.a\""
else
DEF-all += -DSUGAR_LIBSUGAR1="\"$(X)libsugar1.a\""
DEF-win += -DCONFIG_SUGARDIR="\"$(sugardir)/win32\""
endif
endif

# include custom configuration (see make help)
-include config-extra.mak

CORE_FILES = sugar.c sugartools.c libsugar.c sugarpp.c sugargen.c sugarelf.c sugarasm.c sugarrun.c
CORE_FILES += sugar.h config.h libsugar.h sugartok.h
i386_FILES = $(CORE_FILES) i386-gen.c i386-link.c i386-asm.c i386-asm.h i386-tok.h
i386-win32_FILES = $(i386_FILES) sugarpe.c
x86_64_FILES = $(CORE_FILES) x86_64-gen.c x86_64-link.c i386-asm.c x86_64-asm.h
x86_64-win32_FILES = $(x86_64_FILES) sugarpe.c
x86_64-osx_FILES = $(x86_64_FILES) sugarmacho.c
arm_FILES = $(CORE_FILES) arm-gen.c arm-link.c arm-asm.c
arm-wince_FILES = $(arm_FILES) sugarpe.c
arm-eabihf_FILES = $(arm_FILES)
arm-fpa_FILES     = $(arm_FILES)
arm-fpa-ld_FILES  = $(arm_FILES)
arm-vfp_FILES     = $(arm_FILES)
arm-eabi_FILES    = $(arm_FILES)
arm-eabihf_FILES  = $(arm_FILES)
arm64_FILES = $(CORE_FILES) arm64-gen.c arm64-link.c arm-asm.c
c67_FILES = $(CORE_FILES) c67-gen.c c67-link.c sugarcoff.c
riscv64_FILES = $(CORE_FILES) riscv64-gen.c riscv64-link.c riscv64-asm.c

# libsugar sources
LIBSUGAR_SRC = $(filter-out sugar.c sugartools.c,$(filter %.c,$($T_FILES)))

ifeq ($(ONE_SOURCE),yes)
LIBSUGAR_OBJ = $(X)libsugar.o
LIBSUGAR_INC = $($T_FILES)
SUGAR_FILES = $(X)sugar.o
sugar.o : DEFINES += -DONE_SOURCE=0
else
LIBSUGAR_OBJ = $(patsubst %.c,$(X)%.o,$(LIBSUGAR_SRC))
LIBSUGAR_INC = $(filter %.h %-gen.c %-link.c,$($T_FILES))
SUGAR_FILES = $(X)sugar.o $(LIBSUGAR_OBJ)
$(SUGAR_FILES) : DEFINES += -DONE_SOURCE=0
endif

ifeq ($(CONFIG_strip),no)
CFLAGS += -g
LDFLAGS += -g
else
CONFIG_strip = yes
ifndef CONFIG_OSX
LDFLAGS += -s
endif
endif

# target specific object rule
$(X)%.o : %.c $(LIBSUGAR_INC)
	$S$(CC) -o $@ -c $< $(DEFINES) $(CFLAGS)

# additional dependencies
$(X)sugar.o : sugartools.c

# Host Sugar C Compiler
sugar$(EXESUF): sugar.o $(LIBSUGAR)
	$S$(CC) -o $@ $^ $(LIBS) $(LDFLAGS) $(LINK_LIBSUGAR)

# Cross Sugar C Compilers
%-sugar$(EXESUF): FORCE
	@$(MAKE) --no-print-directory $@ CROSS_TARGET=$* ONE_SOURCE=$(or $(ONE_SOURCE),yes)

$(CROSS_TARGET)-sugar$(EXESUF): $(SUGAR_FILES)
	$S$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# profiling version
sugar_p$(EXESUF): $($T_FILES)
	$S$(CC) -o $@ $< $(DEFINES) $(CFLAGS_P) $(LIBS_P) $(LDFLAGS_P)

# static libsugar library
libsugar.a: $(LIBSUGAR_OBJ)
	$S$(AR) rcs $@ $^

# dynamic libsugar library
libsugar.so: $(LIBSUGAR_OBJ)
	$S$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)

libsugar.so: CFLAGS+=-fPIC
libsugar.so: LDFLAGS+=-fPIC

# OSX dynamic libsugar library
libsugar.dylib: $(LIBSUGAR_OBJ)
	$S$(CC) -dynamiclib $(DYLIBVER) -install_name @rpath/$@ -o $@ $^ $(LDFLAGS) 

# OSX libsugar.dylib (without rpath/ prefix)
libsugar.osx: $(LIBSUGAR_OBJ)
	$S$(CC) -shared -install_name libsugar.dylib -o libsugar.dylib $^ $(LDFLAGS) 

# windows dynamic libsugar library
libsugar.dll : $(LIBSUGAR_OBJ)
	$S$(CC) -shared -o $@ $^ $(LDFLAGS)
libsugar.dll : DEFINES += -DLIBSUGAR_AS_DLL

# import file for windows libsugar.dll
libsugar.def : libsugar.dll sugar$(EXESUF)
	$S$(XSUGAR) -impdef $< -o $@
XSUGAR ?= ./sugar$(EXESUF)

# SugarC runtime libraries
libsugar1.a : sugar$(EXESUF) FORCE
	@$(MAKE) -C lib

# Cross libsugar1.a
%-libsugar1.a : %-sugar$(EXESUF) FORCE
	@$(MAKE) -C lib CROSS_TARGET=$*

.PRECIOUS: %-libsugar1.a
FORCE:

run-if = $(if $(shell which $1),$S $1 $2)
S = $(if $(findstring yes,$(SILENT)),@$(info * $@))

# --------------------------------------------------------------------------
# documentation and man page
sugar-doc.html: sugar-doc.texi
	$(call run-if,makeinfo,--no-split --html --number-sections -o $@ $<)

sugar-doc.info: sugar-doc.texi
	$(call run-if,makeinfo,$< || true)

sugar.1 : sugar-doc.pod
	$(call run-if,pod2man,--section=1 --center="Sugar C Compiler" \
		--release="$(VERSION)" $< >$@ && rm -f $<)
%.pod : %.texi
	$(call run-if,perl,$(TOPSRC)/texi2pod.pl $< $@)

# --------------------------------------------------------------------------
# install

INSTALL = install -m644
INSTALLBIN = install -m755 $(STRIP_$(CONFIG_strip))
STRIP_yes = -s

LIBSUGAR1_W = $(filter %-win32-libsugar1.a %-wince-libsugar1.a,$(LIBSUGAR1_CROSS))
LIBSUGAR1_U = $(filter-out $(LIBSUGAR1_W),$(LIBSUGAR1_CROSS))
IB = $(if $1,$(IM) mkdir -p $2 && $(INSTALLBIN) $1 $2)
IBw = $(call IB,$(wildcard $1),$2)
IF = $(if $1,$(IM) mkdir -p $2 && $(INSTALL) $1 $2)
IFw = $(call IF,$(wildcard $1),$2)
IR = $(IM) mkdir -p $2 && cp -r $1/. $2
IM = $(info -> $2 : $1)@

B_O = bcheck.o bt-exe.o bt-log.o bt-dll.o

# install progs & libs
install-unx:
	$(call IBw,$(PROGS) $(PROGS_CROSS),"$(bindir)")
	$(call IFw,$(LIBSUGAR1) $(B_O) $(LIBSUGAR1_U),"$(sugardir)")
	$(call IF,$(TOPSRC)/include/*.h $(TOPSRC)/sugarlib.h,"$(sugardir)/include")
	$(call $(if $(findstring .so,$(LIBSUGAR)),IBw,IFw),$(LIBSUGAR),"$(libdir)")
	$(call IF,$(TOPSRC)/libsugar.h,"$(includedir)")
	$(call IFw,sugar.1,"$(mandir)/man1")
	$(call IFw,sugar-doc.info,"$(infodir)")
	$(call IFw,sugar-doc.html,"$(docdir)")
ifneq "$(wildcard $(LIBSUGAR1_W))" ""
	$(call IFw,$(TOPSRC)/win32/lib/*.def $(LIBSUGAR1_W),"$(sugardir)/win32/lib")
	$(call IR,$(TOPSRC)/win32/include,"$(sugardir)/win32/include")
	$(call IF,$(TOPSRC)/include/*.h $(TOPSRC)/sugarlib.h,"$(sugardir)/win32/include")
endif

# uninstall
uninstall-unx:
	@rm -fv $(foreach P,$(PROGS) $(PROGS_CROSS),"$(bindir)/$P")
	@rm -fv "$(libdir)/libsugar.a" "$(libdir)/libsugar.so" "$(libdir)/libsugar.dylib" "$(includedir)/libsugar.h"
	@rm -fv "$(mandir)/man1/sugar.1" "$(infodir)/sugar-doc.info"
	@rm -fv "$(docdir)/sugar-doc.html"
	@rm -frv "$(sugardir)"

# install progs & libs on windows
install-win:
	$(call IBw,$(PROGS) $(PROGS_CROSS) $(subst libsugar.a,,$(LIBSUGAR)),"$(bindir)")
	$(call IF,$(TOPSRC)/win32/lib/*.def,"$(sugardir)/lib")
	$(call IFw,libsugar1.a $(B_O) $(LIBSUGAR1_W),"$(sugardir)/lib")
	$(call IF,$(TOPSRC)/include/*.h $(TOPSRC)/sugarlib.h,"$(sugardir)/include")
	$(call IR,$(TOPSRC)/win32/include,"$(sugardir)/include")
	$(call IR,$(TOPSRC)/win32/examples,"$(sugardir)/examples")
	$(call IF,$(TOPSRC)/tests/libsugar_test.c,"$(sugardir)/examples")
	$(call IFw,$(TOPSRC)/libsugar.h $(subst .dll,.def,$(LIBSUGAR)),"$(libdir)")
	$(call IFw,$(TOPSRC)/win32/sugar-win32.txt sugar-doc.html,"$(docdir)")
ifneq "$(wildcard $(LIBSUGAR1_U))" ""
	$(call IFw,$(LIBSUGAR1_U),"$(sugardir)/lib")
	$(call IF,$(TOPSRC)/include/*.h $(TOPSRC)/sugarlib.h,"$(sugardir)/lib/include")
endif

# the msys-git shell works to configure && make except it does not have install
ifeq ($(CONFIG_WIN32)-$(shell which install || echo no),yes-no)
install-win : INSTALL = cp
install-win : INSTALLBIN = cp
endif

# uninstall on windows
uninstall-win:
	@rm -fv $(foreach P,libsugar.dll $(PROGS) *-sugar.exe,"$(bindir)"/$P)
	@rm -fr $(foreach P,doc examples include lib libsugar,"$(sugardir)/$P"/*)
	@rm -frv $(foreach P,doc examples include lib libsugar,"$(sugardir)/$P")

# --------------------------------------------------------------------------
# other stuff

TAGFILES = *.[ch] include/*.h lib/*.[chS]
tags : ; ctags $(TAGFILES)
# cannot have both tags and TAGS on windows
ETAGS : ; etags $(TAGFILES)

# create release tarball from *current* git branch (including sugar-doc.html
# and converting two files to CRLF)
SUGAR-VERSION = sugar-$(VERSION)
SUGAR-VERSION = sucarc-mob-$(shell git rev-parse --short=7 HEAD)
tar:    sugar-doc.html
	mkdir -p $(SUGAR-VERSION)
	( cd $(SUGAR-VERSION) && git --git-dir ../.git checkout -f )
	cp sugar-doc.html $(SUGAR-VERSION)
	for f in sugar-win32.txt build-sugar.bat ; do \
	    cat win32/$$f | sed 's,\(.*\),\1\r,g' > $(SUGAR-VERSION)/win32/$$f ; \
	done
	tar cjf $(SUGAR-VERSION).tar.bz2 $(SUGAR-VERSION)
	rm -rf $(SUGAR-VERSION)
	git reset

config.mak:
	$(if $(wildcard $@),,@echo "Please run ./configure." && exit 1)

# run all tests
test:
	@$(MAKE) -C tests
# run test(s) from tests2 subdir (see make help)
tests2.%:
	@$(MAKE) -C tests/tests2 $@

testspp.%:
	@$(MAKE) -C tests/pp $@

clean:
	@rm -f sugar$(EXESUF) sugar_p$(EXESUF) *-sugar$(EXESUF) sugar.pod
	@rm -f *.o *.a *.so* *.out *.log lib*.def *.exe *.dll a.out tags TAGS *.dylib
	@$(MAKE) -s -C lib $@
	@$(MAKE) -s -C tests $@

distclean: clean
	@rm -fv config.h config.mak config.texi sugar.1 sugar-doc.info sugar-doc.html

.PHONY: all clean test tar tags ETAGS distclean install uninstall FORCE

help:
	@echo "make"
	@echo "   build native compiler (from separate objects)"
	@echo ""
	@echo "make cross"
	@echo "   build cross compilers (from one source)"
	@echo ""
	@echo "make ONE_SOURCE=no/yes SILENT=no/yes"
	@echo "   force building from separate/one object(s), less/more silently"
	@echo ""
	@echo "make cross-TARGET"
	@echo "   build one specific cross compiler for 'TARGET'. Currently supported:"
	@echo "      $(wordlist 1,6,$(SUGAR_X))"
	@echo "      $(wordlist 7,99,$(SUGAR_X))"
	@echo ""
	@echo "make test"
	@echo "   run all tests"
	@echo ""
	@echo "make tests2.all / make tests2.37 / make tests2.37+"
	@echo "   run all/single test(s) from tests2, optionally update .expect"
	@echo ""
	@echo "make testspp.all / make testspp.17"
	@echo "   run all/single test(s) from tests/pp"
	@echo ""
	@echo "Other supported make targets:"
	@echo "   install install-strip doc clean tags ETAGS tar distclean help"
	@echo ""
	@echo "Custom configuration:"
	@echo "   The makefile includes a file 'config-extra.mak' if it is present."
	@echo "   This file may contain some custom configuration.  For example:"
	@echo "      NATIVE_DEFINES += -D..."
	@echo "   Or for example to configure the search paths for a cross-compiler"
	@echo "   that expects the linux files in <sugardir>/i386-linux:"
	@echo "      ROOT-i386 = {B}/i386-linux"
	@echo "      CRT-i386  = {B}/i386-linux/usr/lib"
	@echo "      LIB-i386  = {B}/i386-linux/lib:{B}/i386-linux/usr/lib"
	@echo "      INC-i386  = {B}/lib/include:{B}/i386-linux/usr/include"
	@echo "      DEF-i386  += -D__linux__"

# --------------------------------------------------------------------------
endif # ($(INCLUDED),no)
