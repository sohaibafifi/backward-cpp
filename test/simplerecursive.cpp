/*
 * test/simplerecursive.cpp
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

//#define BACKWARD_HAS_UNWIND 1
//#define BACKWARD_SYSTEN_UNKNOWN
#define BACKWARD_HAS_DW 1
//#define BACKWARD_HAS_BFD 1
//#define BACKWARD_HAS_BACKTRACE_SYMBOL 1
//#define BACKWARD_HAS_BACKTRACE 1
//#define BACKWARD_CXX98
#include "backward.hpp"
#include <stdio.h>
#include "test/test.hpp"

using namespace backward;

int some_counter;

typedef StackTraceWithLocals stacktrace_t;

void end_of_our_journey(stacktrace_t& st) {
	if (not st.size()) {
		st.load_here();
	}
}

int rec(stacktrace_t& st, int level) {
	if (level <= 1) {
		end_of_our_journey(st);
		return 0;
	}
	return rec(st, level - 1);
}

namespace toto {

namespace titi {

	struct foo {

		union bar {
			__attribute__((noinline))
			static int trampoline(stacktrace_t& st, int level) {
				return rec(st, level);
			}
		};
 };

} // namespace titi

} // namespace toto

TEST (simplerecursive) {
	{ // lexical scope.
		stacktrace_t st;
		const int input = 3;
		int r = toto::titi::foo::bar::trampoline(st, input);

		std::cout << "rec(" << input << ") == " << r << std::endl;

		Printer printer;
		//    printer.address = true;
		printer.object = true;
		printer.print(st, stdout);
	}
}
