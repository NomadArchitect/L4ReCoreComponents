# vi:ft=make

include $(L4DIR)/mk/Makeconf

__NUMBERS := x x x x x x x x x x x x x x x x x x x x

n = $(wordlist 1, $1, $(__NUMBERS))
max = $(subst xx,x,$(join $1,$2))
min = $(subst xx,x,$(filter xx,$(join $1,$2)))
gt = $(filter-out $(words $2),$(words $(call max,$1,$2)))
eq = $(filter $(words $1),$(words $2))
gte = $(call gt,$1,$2)$(call eq,$1,$2)
mul = $(foreach a,$1,$2)


__GCCMAJOR = $(wordlist 1, $(GCCMAJORVERSION), $(__NUMBERS))
__GCCMINOR = $(wordlist 1, $(GCCMINORVERSION), $(__NUMBERS))
__GCCSUBVER= $(wordlist 1, $(GCCSUBVERSION), $(__NUMBERS))

STDCXX_AVAILABLE_VERSIONS = 9 10 11 12 13 14 15

ifeq ("$(GCCVERSION)", "9")
  STDCXX_CONTRIB_VERSION := 9
endif
ifeq ("$(GCCVERSION)", "10")
  STDCXX_CONTRIB_VERSION := 10
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(GCCVERSION)", "11")
  STDCXX_CONTRIB_VERSION := 11
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(GCCVERSION)", "12")
  STDCXX_CONTRIB_VERSION := 12
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(GCCVERSION)", "13")
  STDCXX_CONTRIB_VERSION := 13
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(GCCVERSION)", "14")
  STDCXX_CONTRIB_VERSION := 14
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(GCCVERSION)", "15")
  STDCXX_CONTRIB_VERSION := 15
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif
ifeq ("$(BID_COMPILER_TYPE)", "clang")
  STDCXX_CONTRIB_VERSION := 12
  STDCXX_CONTRIB_VERSION_10_PLUS  := y
endif

STDCXX_CONTRIB_DIR = $(STDCXX_PKG_DIR)/contrib/libstdc++-v3-$(STDCXX_CONTRIB_VERSION)
DEFINES += -Dlinux

CPU_H_x86   := i386
CPU_H_ppc32 := powerpc
CPU_H_arm   := arm
CPU_H_amd64 := i386
CPU_H_mips  := mips
CPU_H_sparc := sparc

CPU_H_generic := config/cpu/generic
CPU_H_arch     = config/cpu/$(CPU_H_$(BUILD_ARCH))

CPU_file = $(word 1, $(wildcard $(STDCXX_CONTRIB_DIR)/$(CPU_H_arch)/$(strip $(1)) $(STDCXX_CONTRIB_DIR)/$(CPU_H_generic)/$(strip $(1))))

ifeq ($(BID_COMPILER_TYPE),clang)
  CCXX_FLAGS += -fsized-deallocation
  DEFINES += -DL4_CLANG_FIXES
endif

#$(info GCC: $(STDCXX_CONTRIB_DIR))

