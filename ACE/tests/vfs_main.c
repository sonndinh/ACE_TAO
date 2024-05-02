/*
 *                          Copyright 2000-2011                      
 *                         Green Hills Software                      
 *
 *    This program is the property of Green Hills Software, its
 *    contents are proprietary information and no part of it is to be
 *    disclosed to anyone except employees of Green Hills Software,
 *    or as agreed in writing signed by the President of Green Hills
 *    Software.
 *
 */

#include <INTEGRITY.h>
#include <stdio.h>
#include <unistd.h>

/* This file is part of the INTEGRITY virtual file system source code.  It provides
 * the entry point (main) for a virtual AddressSpace and calls the internal file system
 * function, __fs_init(), to start the file system tasks.
 *
 * This file is only used by the virtual AddressSpace version of the file
 * system.  A file system virtual AddressSpace must contain this file to ensure that
 * the file system is configured correctly.  The contents of this file may change
 * in future versions.
 */

/* Set the common variable to 1 so that link-time optimizations can be made */
const char __fs_is_virtual = 1;

/* Purposely avoid pulling in vfs_server.h, which only exists in source
 * distributions.
 */
extern Error __fs_init(void);

void main(void) {
    Error theError;
   
    if ((theError = __fs_init()) != Success) {
	fprintf(console, "Failed to start the file system, Error %d\n", theError);
    }

    Exit(0);
}
