/*
    MIT License

    Copyright (c) 2018 WigWag Inc.

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
*/

/*
 * local_strdup.c
 *
 *  Created on: May 22, 2015
 *      Author: ed
 * (c) 2015, WigWag Inc.

	A simple work around for strdup() when also using XSI compatible functions - strerror_r
 */

#include <string.h>
#include <stdio.h>


#define MAX_STRDUP 4096

char *local_strdup_safe(const char *s) {
	char *ret = NULL;
	if(s) {
		int n = strlen(s);
		if(n > MAX_STRDUP) {
			printf("Overflow on local_strdup_safe() %d\n",n);
			n = MAX_STRDUP;
		}
		ret = (char *) malloc(n + 1);
		memcpy(ret,s,n);
		*(ret+n) = '\0';
	}
	return ret;
}
