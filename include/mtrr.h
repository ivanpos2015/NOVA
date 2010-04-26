/*
 * Memory Type Range Registers (MTRR)
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
#include "types.h"

class Mtrr
{
    public:
        uint32 count;
        uint32 dtype;

        struct {
            uint64  base;
            uint64  mask;
        } var[8];

        static Mtrr mtrr;

        INIT
        static void init();

        INIT
        static unsigned memtype (Paddr);
};
