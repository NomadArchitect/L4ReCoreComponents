PKGDIR          ?= ../..
L4DIR           ?= $(PKGDIR)/../../..

TARGET          = moe
DEFAULT_RELOC   = 0x00240000
DEFAULT_RELOC_arm64 = 0x00640000
RELOC_PHYS      = y
SRC_CC          = main.cc page_alloc.cc dataspace.cc dataspace_cont.cc \
                  dataspace_anon.cc globals.cc \
                  alloc.cc boot_fs.cc dataspace_util.cc \
                  region.cc debug.cc malloc.cc quota.cc \
                  loader.cc loader_elf.cc \
                  app_task.cc dataspace_noncont.cc pages.cc \
                  name_space.cc mem.cc log.cc sched_proxy.cc \
                  delete.cc server_obj.cc \
                  dma_space.cc

SRC_CC-$(CONFIG_MOE_VESA_FB)  = vesa_fb.cc

SRC_S          := ARCH-$(ARCH)/crt0.S
MODE            = sigma0

CAN_PIE_amd64   := y
CAN_PIE_arm     := y
CAN_PIE_arm64   := y
BID_CAN_PIE      = $(CAN_PIE_$(ARCH))

REQUIRES_LIBS  := libkproxy libloader libsigma0 \
                  cxx_io cxx_libc_io libsupc++_minimal \
                  libc_minimal libc_minimal_l4re
DEFINES        += -DL4_CXX_NO_EXCEPTION_BACKTRACE -DL4_MINIMAL_LIBC
LDFLAGS        += --entry=_real_start

DEFAULT_HEAP_SIZE = 0
DEFAULT_STACK_SIZE = 0

include $(L4DIR)/mk/prog.mk
