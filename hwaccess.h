/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2009 Carl-Daniel Hailfinger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

/*
 * Header file for hardware access and OS abstraction. Included from flash.h.
 */

#ifndef __HWACCESS_H__
#define __HWACCESS_H__ 1

#include "config.h"

#if !(	defined(__i386__) || \
	defined(__x86_64__) || defined(__amd64) || \
	defined (__mips) || defined (__mips__) || defined (_mips) || defined (mips) || \
	defined(__powerpc__) || defined(__powerpc64__) || defined(__ppc__) || defined(__ppc64__))
#error Unknown architecture
#endif

#if defined (HAVE_SYS_IO_H)
#include <sys/io.h>
#endif /* defined (HAVE_SYS_IO_H) */

#if defined (HAVE_LIBPCI)
/*
 * libpci headers use the variable name "index" which triggers shadowing
 * warnings on systems which have the index() function in a default #include
 * or as builtin.
 */
#define index shadow_workaround_index
#include <pci/pci.h>
#undef index

#if defined (HAVE_STRINGS_H)
#include <strings.h>
#endif /* defined (HAVE_STRINGS_H) */

#if defined (HAVE_STDINT_H)
#include <stdint.h>
#endif /* defined (HAVE_STDINT_H) */

#if defined (HAVE_SYS_TYPES_H)
#include <sys/types.h>
#endif /* defined (HAVE_SYS_TYPES_H) */

#if defined (HAVE_MACHINE_SYSARCH_H)
#include <machine/sysarch.h>
#endif /* defined (HAVE_MACHINE_SYSARCH_H) */

#if defined (HAVE_MACHINE_CPUFUNC_H)
#include <machine/cpufunc.h>
#endif /* defined (HAVE_MACHINE_CPUFUNC_H) */

/* for iopl and outb under Solaris */
#if defined HAVE_ASM_SUNDDI_H
#include <asm/sunddi.h>
#endif /* defined HAVE_ASM_SUNDDI_H */
#if defined HAVE_SYS_SYSI86_H
#include <sys/sysi86.h>
#endif /* defined HAVE_SYS_SYSI86_H */
#if defined HAVE_SYS_PSW_H
#include <sys/psw.h>
#endif /* defined HAVE_SYS_PSW_H */

#ifdef __DJGPP__
#include <pc.h>
#endif /* __DJGPP__ */

#if defined HAVE_DIRECTIO_DARWINIO_H
#include <DirectIO/darwinio.h>
#endif /* defined HAVE_DIRECTIO_DARWINIO_H */

#endif /* defined (HAVE_LIBPCI) */

#define ___constant_swab8(x) ((uint8_t) (				\
	(((uint8_t)(x) & (uint8_t)0xffU))))

#define ___constant_swab16(x) ((uint16_t) (				\
	(((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |			\
	(((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define ___constant_swab32(x) ((uint32_t) (				\
	(((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |		\
	(((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |		\
	(((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |		\
	(((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define ___constant_swab64(x) ((uint64_t) (				\
	(((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) |	\
	(((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) |	\
	(((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) |	\
	(((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) |	\
	(((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) |	\
	(((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) |	\
	(((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) |	\
	(((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

#if defined (__FLASHROM_BIG_ENDIAN__)

#define cpu_to_le(bits)							\
static inline uint##bits##_t cpu_to_le##bits(uint##bits##_t val)	\
{									\
	return ___constant_swab##bits(val);				\
}

cpu_to_le(8)
cpu_to_le(16)
cpu_to_le(32)
cpu_to_le(64)

#define cpu_to_be8
#define cpu_to_be16
#define cpu_to_be32
#define cpu_to_be64

#else /* defined (__FLASHROM_BIG_ENDIAN__) */

#define cpu_to_be(bits)							\
static inline uint##bits##_t cpu_to_be##bits(uint##bits##_t val)	\
{									\
	return ___constant_swab##bits(val);				\
}

cpu_to_be(8)
cpu_to_be(16)
cpu_to_be(32)
cpu_to_be(64)

#define cpu_to_le8
#define cpu_to_le16
#define cpu_to_le32
#define cpu_to_le64

#endif /* defined (__FLASHROM_BIG_ENDIAN__) */

#define be_to_cpu8 cpu_to_be8
#define be_to_cpu16 cpu_to_be16
#define be_to_cpu32 cpu_to_be32
#define be_to_cpu64 cpu_to_be64
#define le_to_cpu8 cpu_to_le8
#define le_to_cpu16 cpu_to_le16
#define le_to_cpu32 cpu_to_le32
#define le_to_cpu64 cpu_to_le64

#if HAVE_LIBPCI == 1

/* PCI port I/O is not yet implemented on PowerPC. */
/* PCI port I/O is not yet implemented on MIPS. */
#if defined (__i386__) || defined (__x86_64__)

#define __FLASHROM_HAVE_OUTB__ 1

#if (defined(__MACH__) && defined(__APPLE__))
#define __DARWIN__
#endif

/* Clarification about OUTB/OUTW/OUTL argument order:
 * OUT[BWL](val, port)
 */

#if defined(__FreeBSD__) || defined(__DragonFly__)
  #define off64_t off_t
  #define lseek64 lseek
  #define OUTB(x, y) do { u_int outb_tmp = (y); outb(outb_tmp, (x)); } while (0)
  #define OUTW(x, y) do { u_int outw_tmp = (y); outw(outw_tmp, (x)); } while (0)
  #define OUTL(x, y) do { u_int outl_tmp = (y); outl(outl_tmp, (x)); } while (0)
  #define INB(x) __extension__ ({ u_int inb_tmp = (x); inb(inb_tmp); })
  #define INW(x) __extension__ ({ u_int inw_tmp = (x); inw(inw_tmp); })
  #define INL(x) __extension__ ({ u_int inl_tmp = (x); inl(inl_tmp); })
#else
#if defined(__DARWIN__)
    /* Header is part of the DirectHW library. */
    #include <DirectIO/darwinio.h>
    #define off64_t off_t
    #define lseek64 lseek
#endif
#if defined (__sun)
  /* Note different order for outb */
  #define OUTB(x,y) outb(y, x)
  #define OUTW(x,y) outw(y, x)
  #define OUTL(x,y) outl(y, x)
  #define INB  inb
  #define INW  inw
  #define INL  inl
#else

#ifdef __DJGPP__

  #define OUTB(x,y) outportb(y, x)
  #define OUTW(x,y) outportw(y, x)
  #define OUTL(x,y) outportl(y, x)

  #define INB  inportb
  #define INW  inportw
  #define INL  inportl

#else 

  #define OUTB outb
  #define OUTW outw
  #define OUTL outl
  #define INB  inb
  #define INW  inw
  #define INL  inl

#endif

#endif
#endif

#if defined(__NetBSD__) || defined (__OpenBSD__)
  #define off64_t off_t
  #define lseek64 lseek
  #if defined(__i386__) || defined(__x86_64__)
#if defined(__NetBSD__)
    #if defined(__i386__)
      #define iopl i386_iopl
    #elif defined(__x86_64__)
      #define iopl x86_64_iopl
    #endif
#elif defined (__OpenBSD__)
    #if defined(__i386__)
      #define iopl i386_iopl
    #elif defined(__amd64__)
      #define iopl amd64_iopl
    #endif
#endif

static inline void outb(uint8_t value, uint16_t port)
{
	asm volatile ("outb %b0,%w1": :"a" (value), "Nd" (port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t value;
	asm volatile ("inb %w1,%0":"=a" (value):"Nd" (port));
	return value;
}

static inline void outw(uint16_t value, uint16_t port)
{
	asm volatile ("outw %w0,%w1": :"a" (value), "Nd" (port));
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t value;
	asm volatile ("inw %w1,%0":"=a" (value):"Nd" (port));
	return value;
}

static inline void outl(uint32_t value, uint16_t port)
{
	asm volatile ("outl %0,%w1": :"a" (value), "Nd" (port));
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile ("inl %1,%0":"=a" (value):"Nd" (port));
	return value;
}
  #endif
#endif

#if !defined(__DARWIN__) && !defined(__FreeBSD__) && !defined(__DragonFly__) && !defined(__LIBPAYLOAD__)
typedef struct { uint32_t hi, lo; } msr_t;
msr_t rdmsr(int addr);
int wrmsr(int addr, msr_t msr);
#endif /* !defined(__DARWIN__) && !defined(__FreeBSD__) && !defined(__DragonFly__) */

#if defined(__FreeBSD__) || defined(__DragonFly__)
/* FreeBSD already has conflicting definitions for wrmsr/rdmsr. */
#undef rdmsr
#undef wrmsr
#define rdmsr freebsd_rdmsr
#define wrmsr freebsd_wrmsr
typedef struct { uint32_t hi, lo; } msr_t;
msr_t freebsd_rdmsr(int addr);
int freebsd_wrmsr(int addr, msr_t msr);
#endif /* defined(__FreeBSD__) || defined(__DragonFly__) */

#if defined(__LIBPAYLOAD__)
#include <arch/io.h>
#include <arch/msr.h>
typedef struct { uint32_t hi, lo; } msr_t;
msr_t libpayload_rdmsr(int addr);
int libpayload_wrmsr(int addr, msr_t msr);
#undef rdmsr
#define rdmsr libpayload_rdmsr
#define wrmsr libpayload_wrmsr
#endif

#endif
#endif

#endif /* !__HWACCESS_H__ */
