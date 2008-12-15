/*
 * @(#)AccessControlException.java	1.15 06/10/10
 *
 * Copyright  1990-2008 Sun Microsystems, Inc. All Rights Reserved.  
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER  
 *   
 * This program is free software; you can redistribute it and/or  
 * modify it under the terms of the GNU General Public License version  
 * 2 only, as published by the Free Software Foundation.  
 *   
 * This program is distributed in the hope that it will be useful, but  
 * WITHOUT ANY WARRANTY; without even the implied warranty of  
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
 * General Public License version 2 for more details (a copy is  
 * included at /legal/license.txt).  
 *   
 * You should have received a copy of the GNU General Public License  
 * version 2 along with this work; if not, write to the Free Software  
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  
 * 02110-1301 USA  
 *   
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa  
 * Clara, CA 95054 or visit www.sun.com if you need additional  
 * information or have any questions.
 *
 */
 
package java.security;

/**
 * <p> This exception is thrown by the AccessController to indicate
 * that a requested access (to a critical system resource such as the
 * file system or the network) is denied.
 *
 * <p> The reason to deny access can vary.  For example, the requested
 * permission might be of an incorrect type,  contain an invalid
 * value, or request access that is not allowed according to the
 * security policy.  Such information should be given whenever
 * possible at the time the exception is thrown.
 *
 * @version 	1.9, 02/02/00
 */

public class AccessControlException extends SecurityException {

    // the permission that caused the exeception to be thrown.
    private Permission perm; 

    /**
     * Constructs an <code>AccessControlException</code> with the
     * specified, detailed message. 
     *
     * @param   s   the detail message.
     */
    public AccessControlException(String s) {
        super(s);
    }

    /**
     * Constructs an <code>AccessControlException</code> with the
     * specified, detailed message, and the requested permission that caused
     * the exception. 
     *
     * @param   s   the detail message.
     * @param   p   the permission that caused the exception.
     */
    public AccessControlException(String s, Permission p) {
        super(s);
	perm = p;
    }

    /**
     * Gets the Permission object associated with this exeception, or
     * null if there was no corresponding Permission object.
     *
     * @return the Permission object.
     */
    public Permission getPermission() {
	return perm;
    }
}

