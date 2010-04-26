/*
 * Virtual Memory Area
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
#include "slab.h"
#include "util.h"

class Pd;

class Vma
{
    private:
        static Slab_cache cache;

    public:
        Spinlock    lock;
        Vma *       list_prev;
        Vma *       list_next;
        Vma *       tree_prev;
        Vma *       tree_next;
        unsigned    depth;

        Pd *  const node_pd;
        mword const node_base;
        mword const node_order;
        mword const node_type;
        mword const node_attr;

    public:
        ALWAYS_INLINE
        static inline void *operator new (size_t) { return cache.alloc(); }

        ALWAYS_INLINE
        static inline void operator delete (void *ptr) { cache.free (ptr); }

        // Sentinel
        explicit Vma() : list_prev (this), list_next (this), tree_prev (this), tree_next (this), depth (-1U), node_pd (0), node_base (0), node_order (0), node_type (0), node_attr (0) {}

        explicit Vma (Pd *, mword, mword = 0, mword = 0, mword = 0);

        ALWAYS_INLINE
        inline static bool collide (mword b1, mword b2, mword o1, mword o2)
        {
            return (b1 ^ b2) >> max (o1, o2) == 0;
        }

        bool insert (Vma *, Vma *);

        void dump();
};
