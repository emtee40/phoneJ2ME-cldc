/*
 *   
 *
 * Copyright  1990-2007 Sun Microsystems, Inc. All Rights Reserved.
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

#include "incls/_precompiled.incl"
#include "incls/_LiteralPoolElement.cpp.incl"

#if USE_LITERAL_POOL
ReturnOop LiteralPoolElement::allocate(const Oop* oop, int imm32 JVM_TRAPS) {
  if( ObjectHeap::free_memory_for_compiler_without_gc() > allocation_size() ) {
    // We can allocate only if we have enough space -- there are
    // many RawLocation operations in VirtualStackFrame that would
    // fail if a GC happens.
    AllocationDisabler allocation_not_allowed_in_this_block;
    LiteralPoolElement::Raw result = Universe::new_mixed_oop_in_compiler_area(
                                MixedOopDesc::Type_LiteralPoolElement,
                                LiteralPoolElementDesc::allocation_size(),
                                LiteralPoolElementDesc::pointer_count()
                                JVM_MUST_SUCCEED);

    result().set_literal_int(imm32);
    result().set_literal_oop(oop);
    result().set_bci(not_yet_defined_bci);

    return result;
  } else {
    // IMPL_NOTE: We ought to set a flag that just says to recompile this
    // Or get the code to work even when a GC happens
    CodeGenerator* cg = Compiler::current()->code_generator();
    while (!cg->has_overflown_compiled_method()) {
      cg->nop(); cg->nop();
    }
    return NULL;
  }
}

#if !defined(PRODUCT) || USE_COMPILER_COMMENTS

void LiteralPoolElement::print_value_on( Stream* s ) const {
#if USE_COMPILER_COMMENTS
  s->print("<LiteralPoolElement: ");
  if (is_bound()) { 
    s->print("bci=%d, ", bci());
  } else { 
    s->print("unbound, ", bci());
  }
  UsingFastOops fast_oops;
  Oop::Fast oop = literal_oop();
  int imm32     = literal_int();
  if (oop.is_null()) { 
    s->print("imm32=%d >", imm32);
  } else { 
    s->print("immoop=[");
    oop.print_value_on(s);
    if (imm32 != 0) { 
      s->print(" + %d", imm32);
    }
    s->print("] >");
  }
#endif
}

// This method is called by MixedOop::iterate() after iterating the
// header part of MixedOop
void LiteralPoolElement::iterate(OopVisitor* visitor) {
  if (literal_oop() != NULL) {
    NamedField id("oop", true);
    visitor->do_oop(&id, literal_oop_offset(), true);
  }
  if (is_bound()) { 
    NamedField id("bound bci", true);
    visitor->do_int(&id, bci_offset(), true);
  }
  if (literal_oop() == NULL) { 
    NamedField id("imm32", true);
    visitor->do_int(&id, literal_int_offset(), true);
  }
  {
    NamedField id("label", true);
    visitor->do_int(&id, label_offset(), true);
  }

  // IMPL_NOTE: use OopPrinter API
  {
    BinaryLabel lab = label();
    lab.print_value_on(tty);
  }
}

#endif

#endif
