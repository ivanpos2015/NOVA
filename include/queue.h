/*
 * Queue
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

template <typename T>
class Queue
{
    private:
        T *queue;

    public:
        ALWAYS_INLINE
        inline Queue() : queue (0) {}

        ALWAYS_INLINE
        inline T *head() const { return queue; }

        ALWAYS_INLINE
        inline void enqueue (T *t)
        {
            if (!queue)
                queue = t->prev = t->next = t;
            else {
                t->next = queue;
                t->prev = queue->prev;
                t->next->prev = t->prev->next = t;
            }
        }

        ALWAYS_INLINE
        inline T *dequeue()
        {
            T *t = queue;

            if (!t)
                return 0;

            if (t == t->next)
                queue = 0;
            else {
                queue = t->next;
                t->next->prev = t->prev;
                t->prev->next = t->next;
            }

            t->next = t->prev = 0;

            return t;
        }
};
