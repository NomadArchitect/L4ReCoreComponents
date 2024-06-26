// -*- Mode: C++ -*-
// vim:ft=cpp
/**
 * \file
 * \brief  Capability allocator implementation
 */
/*
 * (c) 2008-2009 Alexander Warg <warg@os.inf.tu-dresden.de>
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 */

#pragma once

#include <l4/bid_config.h>

#if defined(CONFIG_L4RE_BITMAP_CAP_ALLOC)

#include <l4/re/util/bitmap_cap_alloc>

namespace L4Re { namespace Util {

typedef Cap_alloc_base _Cap_alloc;

}}

#elif defined(CONFIG_L4RE_COUNTING_CAP_ALLOC)

#include <l4/re/util/counting_cap_alloc>
#include <l4/re/util/debug>

namespace L4Re { namespace Util {

// RISC-V does not natively support subword atomics, such as __atomic_load_1.
// The RISC-V gcc developers have decided to emulate these via libatomic, which
// is automatically linked against.
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1) || defined(ARCH_arm) || defined(ARCH_riscv)
typedef Counting_cap_alloc<L4Re::Util::Counter_atomic<unsigned char>,
                           L4Re::Util::Dbg > _Cap_alloc;
#elif defined(ARCH_sparc)
typedef Counting_cap_alloc<L4Re::Util::Counter<unsigned char>,
                           L4Re::Util::Dbg > _Cap_alloc;
#warning "Thread-safe capability allocator not available!"
#else
#error "Unsupported platform"
#endif

}}

#else
#error "No supported capability allocator selected"
#endif
