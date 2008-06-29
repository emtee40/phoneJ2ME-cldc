/*
 *
 *
 * Portions Copyright  2000-2007 Sun Microsystems, Inc. All Rights
 * Reserved.  Use is subject to license terms.
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
 *!c<
 * Copyright 2006 Intel Corporation. All rights reserved.
 *!c>
 */

#if !ENABLE_THUMB_COMPILER

#if !defined(PRODUCT) || USE_COMPILER_DISASSEMBLER

class Disassembler: public StackObj {
 public:
  // creation
  Disassembler(Stream* stream) : _stream(stream) {}

  // accessors
  Stream* stream() const { return _stream; }

  typedef Assembler::Register   Register;
  typedef Assembler::Condition  Condition;
  typedef Assembler::Shift      Shift;
  typedef Assembler::Opcode     Opcode;

  static Register as_register( const unsigned n ) {
    return Assembler::as_register( n );
  }
  static Condition as_condition( const unsigned n ) {
    return Assembler::as_condition( n );
  }
  static Shift as_shift( const unsigned n ) {
    return Assembler::as_shift( n );
  }
  static Opcode as_opcode( const unsigned n ) {
    return Assembler::as_opcode( n );
  }

  // textual representation
  static const char* condition_name     (const Assembler::Condition cond  );
  static const char* shift_name         (const Assembler::Shift     shift );
  static const char* opcode_name        (const Assembler::Opcode    opcode);
  static const char* register_name      (const Assembler::Register  reg   );

  static const char* condition_name ( const unsigned cond ) {
    return condition_name( as_condition( cond ) );
  }
  static const char* shift_name ( const unsigned shift ) {
    return shift_name( as_shift( shift ) );
  }
  static const char* opcode_name ( const unsigned opcode) {
    return opcode_name( as_opcode( opcode ) );
  }
  static const char* register_name ( const unsigned reg ) {
    return register_name( as_register( reg ) );
  }

#if ENABLE_ARM_VFP
  // type is either 's' (float) or 'd' (double)
  static void vfp_reg_name(const char type, unsigned reg, char buff[]);
#endif

  // usage
  enum { NO_OFFSET = -1 };
  void disasm(int* addr, int instr, int instr_offset = NO_OFFSET);

 private:
  Stream* _stream;

  // instruction fields
  static const bool bit(int instr, int i) {
    return (instr >> i & 0x1) == 1;
  }

  static const Assembler::Register  rn_field(int instr) {
    return as_register(instr >> 16 & 0xf);
  }

  static const Assembler::Register  rd_field(int instr) {
    return as_register(instr >> 12 & 0xf);
  }

  static const Assembler::Register  rs_field(int instr)  {
      return as_register(instr >>  8 & 0xf);
  }

  static const Assembler::Register  rm_field(int instr) {
    return as_register(instr & 0xf);
  }

  // disassembler
  void emit_unknown(int instr, const char* comment = NULL);
  void emit_imm_offset(bool u, int imm);
  void emit_shifted_reg(int instr);
  void emit_register_list(int instr);
  void emit_address1(int instr, int instr_offset);
  void emit_address2(int instr, int instr_offset);
  void emit_address3(int instr, int instr_offset);
  void emit_address5(int instr, int instr_offset);


#if ENABLE_XSCALE_WMMX_INSTRUCTIONS
  // To support Xscale WMMX instructions
  static const char* Disassembler::wmmx_align_name(int ww);
  static const char* wmmx_wreg_name(Assembler::WMMXRegister reg);
  static const char* wmmx_wcgreg_name(Assembler::WCGRegister reg);
  void emit_wmmx_instruction(int instr);
#endif

#if ENABLE_ARM_VFP
  void emit_vfp_register_list(int instr);
  void emit_vfp_instruction(int instr, int instr_offset);
  void unknown_vfp_instr(int instr);
#endif
};

#endif // !defined(PRODUCT) || USE_COMPILER_DISASSEMBLER

#endif /*#if !ENABLE_THUMB_COMPILER*/
