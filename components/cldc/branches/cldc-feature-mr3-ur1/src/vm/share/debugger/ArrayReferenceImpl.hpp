/*
 *   
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
 */

/** \class ArrayReferenceImpl.hpp
    Handles commands to read/write values in arrays as well as returning the 
    length of the array.
*/
#if ENABLE_JAVA_DEBUGGER

class ArrayReferenceImpl {
public:
  static void *array_reference_cmds[];
  // fix warning in linux arm build
  static void dummy();
private:
  static void array_reference_length(COMMAND_ARGS);
  static void array_reference_get_values(COMMAND_ARGS);
  static void array_reference_set_values(COMMAND_ARGS);

  static void array_getter_setter(COMMAND_ARGS, bool);
};

#endif
