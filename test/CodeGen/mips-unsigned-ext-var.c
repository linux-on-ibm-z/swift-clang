// RUN: %clang -target mips64-unknown-linux -O2 -mabi=n64 -S -emit-llvm %s -o - | FileCheck %s -check-prefix=N64
// RUN: %clang -target mips64-unknown-linux -O2 -mabi=n32 -S -emit-llvm %s -o - | FileCheck %s -check-prefix=N32
// RUN: %clang -target mips-unknown-linux -O2 -mabi=o32 -S -emit-llvm %s -o - | FileCheck %s -check-prefix=O32 

#include <stdarg.h>

unsigned foo(int x, ...) {
  va_list valist;
  va_start(valist, x);
  unsigned a;
  a = va_arg(valist, unsigned);
  return a;
}

void foo1() {
  unsigned f = 0xffffffe0;
  foo(1,f);
}

//N64: call i32 (i32, ...) @foo(i32 signext undef, i32 signext -32)
//N32: call i32 (i32, ...) @foo(i32 signext undef, i32 signext -32)
//O32: call i32 (i32, ...) @foo(i32 signext undef, i32 signext -32)