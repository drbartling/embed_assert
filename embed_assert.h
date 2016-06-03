/*******************************************************************************
 * Embedded Assert
 *
 * Author:
 *  Ryan Bartling
 *
 * File Name:
 *  embed_assert.h
 *
 * Summary:
 *  Low resource platform agnostic assert
 *
 * Description:
 *  Assert in C generates long strings with each use, and can consume valuable
 *  program memory on small microcontrollers.
 *
 *  Sometimes it is useful to write code that can be tested on the developers
 *  computer against test data.  This file is intended to provide debugging
 *  functionality with low overhead for the microcontroller and map to assert()
 *  when compiled for an x86 machine.
 *
 ******************************************************************************/

/*******************************************************************************
The MIT License (MIT)
Copyright (c) 2016 David Ryan Bartling
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#ifndef EMBED_ASSERT_H    // Guards against multiple inclusion
#define EMBED_ASSERT_H

//
// Section: Included Files
//

#include <assert.h>

//
// Section: API
//

// Use E_ASSERT(exp) liberally for debugging
// Define void EmbeddedAssert(void) in application to specify runtime behavior.

#ifdef __XC // TODO: Use compiler specific define for your embedded platoform

// TODO: Use compiler built-in breakpoint for debug tool chain
#define E_BREAKPOINT() __builtin_software_breakpoint() 

void EmbeddedAssert(void);

#if defined(NDEBUG)
#define E_ASSERT(exp) ((void)0)
#else // NDEBUG

#if defined(__DEBUG)
#define E_ASSERT(exp)	\
	((exp) ? ((void)0) : E_BREAKPOINT())
#else // __DEBUG
#define E_ASSERT(exp)	\
	((exp) ? ((void)0) : EmbeddedAssert())
#endif // __DEBUG
#endif // NDEBUG

#else // __XC

#define E_ASSERT(exp) assert(exp);

#endif // __XC

#endif // FILE_NAME_H

//
// End of File
//
