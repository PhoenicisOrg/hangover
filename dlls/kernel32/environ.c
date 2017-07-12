/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetStartupInfo
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI GetStartupInfoA(STARTUPINFOA *info)
{
    struct qemu_GetStartupInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTARTUPINFOA);
    call.info = (uint64_t)info;
    qemu_syscall(&call.super);
}

#else

void qemu_GetStartupInfoA(struct qemu_syscall *call)
{
    struct qemu_GetStartupInfo *c = (struct qemu_GetStartupInfo *)call;
    WINE_TRACE("\n");
    GetStartupInfoA(QEMU_G2H(c->info));
}

#endif

struct qemu_GetStartupInfoW
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI GetStartupInfoW(STARTUPINFOW *info)
{
    struct qemu_GetStartupInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTARTUPINFOW);
    call.info = (uint64_t)info;
    qemu_syscall(&call.super);
}

#else

void qemu_GetStartupInfoW(struct qemu_syscall *call)
{
    struct qemu_GetStartupInfoW *c = (struct qemu_GetStartupInfoW *)call;
    WINE_TRACE("\n");
    GetStartupInfoW(QEMU_G2H(c->info));
}

#endif

struct qemu_GetStdHandle
{
    struct qemu_syscall super;
    uint64_t std_handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetStdHandle(DWORD std_handle)
{
    struct qemu_GetStdHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTDHANDLE);
    call.std_handle = std_handle;
    qemu_syscall(&call.super);
    return (HANDLE)call.super.iret;
}

#else

void qemu_GetStdHandle(struct qemu_syscall *call)
{
    struct qemu_GetStdHandle *c = (struct qemu_GetStdHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetStdHandle(c->std_handle);
}

#endif

