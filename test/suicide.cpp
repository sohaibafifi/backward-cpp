/*
 * test/suicide.cpp
 * Copyright 2013 Google Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//#define BACKWARD_SYSTEN_UNKNOWN
//#define BACKWARD_HAS_UNWIND 0
//#define BACKWARD_CXX98

#include "backward.hpp"

#include <stdio.h>
#include "test/test.hpp"

using namespace backward;

void abort_abort_I_repeat_abort_abort()
{
	std::cout << "Jumping off the boat!" << std::endl;
	abort();
}

TEST (invalid_read)
{
	SignalHandling sh;
	std::cout << std::boolalpha << "sh.loaded() == " << sh.loaded() << std::endl;
	abort_abort_I_repeat_abort_abort();
}
