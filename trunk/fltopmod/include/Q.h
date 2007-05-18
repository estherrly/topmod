/*
 * Q.h -  support for ForAll, ThereExists, Count and Sum (i.e. quantifiers).
 *
 * Portability: this file uses the GNU C Statement Expression extension and
 *    so requires GCC/C++ with extensions enabled (this is checked by the
 *    header file).
 * 
 * Copyright (c) 1997 Phil Maker
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: Q.h,v 1.1 2006/09/04 19:22:53 stuart Exp $
 */


#ifndef _Q_h_
#define _Q_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WITHOUT_NANA 

#ifndef __GNUC__ /* not compiling with GCC/G++ extensions */
error 
This file requires the GNU C/C++ "statement expression" extension;
so use GCC/G++ with extensions enabled. If you have not got GCC then 
misery follows though we may be able to do something about it
in the future.
#endif

/*
 * A(i,c,n,a) - true iff a is true for all values generated by for(i;c;n) 
 * 
 * Note: local variables can be introduced in this statement even in C.
 */

#define A(i,c,n,a) /* ForAll */ \
	({ \
		int _A_result = 1; \
		i; \
		while(c) { \
			if(!(a)) { \
				_A_result = 0; \
				break; \
			} \
			n; \
		} \
		_A_result; \
	})

/* 
 * E(i,c,n,a) - true iff exists any true a for values generated by for(i;c;n)
 */

#define E(i,c,n,a) /* Exists */ \
	({ \
		int _E_result = 0; \
		i; \
		while(c) { \
			if(a) { \
				_E_result = 1; \
				break; \
			} \
			n; \
		} \
		_E_result; \
	})

/* 
 * C(i,c,n,a) - count the number of times a is true over the values
 * generated by for(i;c;n)
 */

#define C(i,c,n,a) /* Count */ \
	({ \
		long _C_result = 0; \
		i; \
		while(c) { \
			if(a) { \
				_C_result++; \
			} \
			n; \
		} \
		_C_result; \
	})

/*
 * E1(i,c,n,a) - exists a single value generated by for(i;c;n)
 * suchthat i is true.
 */

#define E1(i,c,n,a) (C(i,c,n,a) == 1) /* There Exists 1 */

/*
 * S(i,c,n,v) - sum of v over the values generated by for(i;c;n)
 */

#define S(i,c,n,v) \
	({ \
		i; \
		typeof(v) _S_result = 0; \
		while(c) { \
			_S_result += (v); \
			n; \
		} \
		_S_result; \
	})

/*
 * P(i,c,n,v) - product of v over the values generated by for(i;c;n)
 */

#define P(i,c,n,v) \
	({ \
		i; \
		typeof(v) _P_result = 1; \
		while(c) { \
			_P_result *= (v); \
			n; \
		} \
		_P_result; \
	})

#else /* defined(WITHOUT_NANA) */

/*
 * we don't produce any empty stubs for Q.h when compiling without nana
 * since calls to A(...), etc should only occur in stubbed out code such
 * as I(...).
 */

#endif /* !defined(WITHOUT_NANA) */
#ifdef __cplusplus
}
#endif

#endif /* _Q_h_ */

