/*
 * Task State Segment (TSS)
 *
 * Author: Udo Steinberg <udo@hypervisor.org>
 * TU Dresden, Operating Systems Group
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#pragma once

#include "compiler.h"
#include "selectors.h"

class Tss
{
    public:
        uint32  : 32;                   // 0x0

        uint32  sp0;                    // 0x4
        uint16  ss0;  uint16 : 16;      // 0x8
        uint32  sp1;                    // 0xc
        uint16  ss1;  uint16 : 16;      // 0x10
        uint32  sp2;                    // 0x14
        uint16  ss2;  uint16 : 16;      // 0x18
        uint32  cr3;                    // 0x1c
        uint32  eip;                    // 0x20
        uint32  eflags;                 // 0x24
        uint32  eax;                    // 0x28
        uint32  ecx;                    // 0x2c
        uint32  edx;                    // 0x30
        uint32  ebx;                    // 0x34
        uint32  esp;                    // 0x38
        uint32  ebp;                    // 0x3c
        uint32  esi;                    // 0x40
        uint32  edi;                    // 0x44
        uint16  es;   uint16 : 16;      // 0x48
        uint16  cs;   uint16 : 16;      // 0x4c
        uint16  ss;   uint16 : 16;      // 0x50
        uint16  ds;   uint16 : 16;      // 0x54
        uint16  fs;   uint16 : 16;      // 0x58
        uint16  gs;   uint16 : 16;      // 0x5c
        uint16  ldt;  uint16 : 16;      // 0x60

        uint16  trap;                   // 0x64
        uint16  iobm;                   // 0x66

        static Tss run ALIGNED(8) CPULOCAL;
        static Tss dbf ALIGNED(8) CPULOCAL;

        static void build();

        ALWAYS_INLINE
        static inline void load()
        {
            asm volatile ("ltr %w0" : : "rm" (SEL_TSS_RUN));
        }
};
