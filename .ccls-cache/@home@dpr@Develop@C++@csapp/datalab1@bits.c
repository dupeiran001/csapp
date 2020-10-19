/*
 * CS:APP Data Lab
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "tests.h"
/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info. //struct {dupeiran ,id[ 2019, 300 , 003 , 090 ]} char *s, 
 */

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;	

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 *
 */
/* NO:1
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /*  bitAnd is the same as bitOr after bitNot */
  return ~(~x | ~y);
}

/* NO:2
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  /*  bitNor equals to bitAnd after bitNot */
  return (~x & ~y);
}
/* NO:3
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  /*  set the high bit the same as the least bit of x */
   int tmp = x << 31;
  /*
   * arithmetically right shift adds the sign bit (that is the highest bit of tmp)
   * fill all bits of tmp with it's sign bit
   */
   return tmp >> 31;
}
/* NO:4
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int evenBits(void) {
  /* init the pattern string with 0x0000 0000;*/
  int pattern = 0;
  /*  the following 4 lines set pattern to 0x5555 5555 using bitOr and left shift */
  pattern |= 0x55 ;
  pattern |= 0x55 << 8;
  pattern |= 0x55 << 16;
  pattern |= 0x55 << 24;
  return pattern;
}
/* NO:5
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  /* init the pattern with 0xFFFF FFFF using left shift and right shift*/
  int pattern = 0xFF;
  pattern = pattern << 24;
  pattern = pattern >> 24;
  /* form a pattern string that high n bits set to 0 and low 32-n bits set to 1 */
  pattern = ~(pattern <<(32 + ~n +1));
  /* pattern bitAnd arithmetically shifted x to get the logicalShift */
  return (x>>n) & pattern;
  
}
/* NO:6
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  /* 
   * bitOr to each bit and if result is 1, there must be some bit that is set to be 1,
   * just return the reverse result  is equal to !x
   */
  int tmp = x;
  x = x | (x >>16);
  /* now the lower 2 byte of x is defined */
  tmp = x;
  x = x | (x >>8);
  /* now only lower 1 byte is defined */
  tmp = x;
  x = x | (x >> 4);
  /* 4 bits left */
  tmp = x;
  x = x | (x >> 2);
  /*2bits */
  tmp = x;
  x = x | (x >> 1);
  /* now the last bit is the reverse of result*/
  x += 1;
  int pattern = 0x01;
  return pattern & x;
}
/* NO:7
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4
 */
int leastBitPos(int x) {
  /*
   * x-1 makes 0 after the least 1 became 1, and the least 1 became 0 
   * so ~(x-1) & x only leave the least 1's bit 1.
   */
  int tmp = 0xFF;
  tmp = (tmp << 24 ) >> 24;
  return ~(x+tmp) & x;
}
/* NO:8
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Ratng: 1
 */
int tmax(void) {
  /* it should return 0x7FFFFFFF */
  int result = 0xFF;
  result = result << (31);
  result = ~result;
  return result;
}
/* NO:9
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* in 2's complement substract , minus is the same as add 1 after bitNot ,including 0x0000 and 0x8000 */
  return ~x+1;
}
/* NO:10
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*
   * in 2's complement substract, only 0x00 and 0x80 equals to itself
   * we need to figure out 0,so we need a 2's complement substract of x
   * only x that x has sign bit 0 and -x has sign bit 1 can definitely tell that x>0
   */

  /*
   * (~x+1)>>31 is true only when -x has sign bit 1. but 0 has sign bit 0,so there is no 0
   */
  return ((~x+1)>>31 & 0x01) & (~(x>>31))&0x01;
}
/* NO:11
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  /* if x has a sign bit of 0, x is no negative. so just get the minus sign bit and return */
  return ~(x>>31)& 0x01;
}
/* NO:12
 * sum3 - x+y+z using only a single '+'
 *   Example: sum3(3, 4, 5) = 12
 *   Legal ops: ! ~ & ^ | << >>
 *   Max ops: 16
 *   Rating: 3
 */
/* A helper routine to perform the addition.  Don't change this code */
static int sum(int x, int y) {
  return x+y;
}
int sum3(int x, int y, int z) {
  int word1 = 0;
  int word2 = 0;
  /**************************************************************
     Fill in code below that computes values for word1 and word2
     without using any '+' operations
  ***************************************************************/
  word1 = x^y^z;
  word2 = (x&y) | (x&z) | (y&z);
  word2 = word2 << 1;
  /**************************************************************
     Don't change anything below here
  ***************************************************************/
  return sum(word1,word2);
}
/* NO:13
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  /* if the sign of x + y is not the same as x and y, it's overflow */
  int signx = (x>>31) & 0x01;
  int nsignx = ~(x>>31) & 0x01;
  int signy = (y>>31) & 0x01;
  int nsigny = ~(y>>31) & 0x01;
  int signr = ((x+y)>>31) & 0x01;
  int nsignr = ~((x+y)>>31) & 0x01;
  /* only when (sx ,sy ,sr) = (0 , 0 , 1)or(1 , 1 , 0) , return 0 */
  return (signx | signy | nsignr) & (nsignx | nsigny | signr);
}
/* NO:14
 * logicalAbs - absolute value of x (except returns TMin for TMin)
 *   Example: abs(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int logicalAbs(int x) {
  /* the operation of -x = ~x +1 = x ^ pattern + signbit */
  int signbit = (x >> 31) & 0x01;
  int pattern = x >> 31;
  return (x^pattern) + signbit;
}
/* NO:15
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int isNonZero(int x) {
  /* bitor all bits, and the result is 0 only when x =0 */
  int tmp = x;
  x = tmp | (x >> 16);
  /* now last 2 bytes useful*/
  tmp = x;
  x = tmp | (x >> 8);
  /* last 1 byte */
  tmp = x;
  x = tmp | (x >> 4);
  /* last 4bits */
  tmp = x;
  x = tmp | (x >> 2);
  /* last 2bits */
  tmp = x;
  x = tmp | (x >> 1);
  /* last bit of x is the result */
  return x & 0x01;
}

