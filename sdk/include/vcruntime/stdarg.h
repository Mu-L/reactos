/* Copyright (C) 1989, 1997, 1998, 1999, 2000 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* As a special exception, if you include this header file into source
   files compiled by GCC, this header file does not by itself cause
   the resulting executable to be covered by the GNU General Public
   License.  This exception does not however invalidate any other
   reasons why the executable file might be covered by the GNU General
   Public License.  */

/*
 * ISO C Standard:  7.15  Variable arguments  <stdarg.h>
 */

#pragma once

#ifndef _INC_STDARG
#define _INC_STDARG

#include <vcruntime.h>
#include <vadefs.h>

#ifndef _WIN32
#error Only Win32 target is supported!
#endif

#ifndef va_start
#define va_start __crt_va_start
#endif
#ifndef va_arg
#define va_arg __crt_va_arg
#endif
#ifndef va_end
#define va_end __crt_va_end
#endif

#endif
