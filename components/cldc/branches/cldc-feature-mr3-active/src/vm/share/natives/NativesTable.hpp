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

#ifndef _NATIVES_TABLE_HPP_
#define _NATIVES_TABLE_HPP_

#define JVM_NATIVE(name, signature, func) \
              {(char*)name, (char*)signature, (void*)func}

#define JVM_ENTRY(name, signature, func) \
             {(char*)name, (char*)signature, (void*)func,}

#define JVM_TABLE(name, natives, entries) \
             {(char*)name, natives, entries }

struct JvmNativeFunction {
  char* name;
  char* signature;
  void* function;
};

struct JvmNativesTable {
  char*                  name;
  const JvmNativeFunction*  natives;
  const JvmNativeFunction*  entries;
};


struct JvmExecutionEntry {
  unsigned char* addr;
  char *  name;
};

// This table is generated by invoking src/tools/jcc/JavaCodeCompact
// with the parameters {-writer CLDC_HI_Natives -o NativesTable.cpp}

extern const JvmNativesTable   jvm_natives_table[];

// This table is also in the generated NativesTable.cpp. It lists all
// the special 'entry' points that implement fast handling of certain
// APIs in the class library (such as native_system_arraycopy_entry).
extern const JvmExecutionEntry jvm_api_entries[];

#endif /* _NATIVES_TABLE_HPP_ */
