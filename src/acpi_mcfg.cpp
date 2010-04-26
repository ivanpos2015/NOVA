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

#include "acpi_mcfg.h"
#include "pci.h"

void Acpi_table_mcfg::parse() const
{
    for (Acpi_mcfg const *x = mcfg; x < reinterpret_cast<Acpi_mcfg *>(reinterpret_cast<mword>(this) + length); x++)
        if (!x->seg)
            Pci::cfg_base = static_cast<Paddr>(x->addr);

    Pci::init();
}
