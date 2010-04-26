/*
 * Advanced Configuration and Power Interface (ACPI)
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

#include "acpi_table.h"

class Acpi_mcfg
{
    public:
        uint64      addr;
        uint16      seg;
        uint8       bus_s;
        uint8       bus_e;
        uint32      reserved;
};

class Acpi_table_mcfg : public Acpi_table
{
    public:
        uint64      reserved;
        Acpi_mcfg   mcfg[];

        INIT
        void parse() const;
};
