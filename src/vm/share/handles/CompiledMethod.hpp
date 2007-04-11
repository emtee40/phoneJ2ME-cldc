/*
 *   
 *
 * Portions Copyright  2000-2006 Sun Microsystems, Inc. All Rights Reserved.
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

// A CompiledMethod contains the generated native code generated by
// the compiler. It contains two parts
// - the generated instructions (located at the start of the dynamic part)
// - relocation information     (located at the end of the dynamic part)
// The relocation information is PIC making it easy to truncate the object
// after completed code generation.

class CompiledMethod : public Oop {
 public:
  // Offset where compiled code begins
  static int base_offset() {
   return CompiledMethodDesc::header_size();
  }
  static int entry_offset() {
   return CompiledMethodDesc::entry_offset();
  }
  // To avoid endless lists of friends the static offset computation
  // routines are all public.
  static int method_offset() {
    return FIELD_OFFSET(CompiledMethodDesc, _method);
  }
  static int flags_and_size_offset() {
    return FIELD_OFFSET(CompiledMethodDesc, _flags_and_size);
  }

#if ENABLE_JVMPI_PROFILE
  static int jvmpi_code_size_offset() {
    return FIELD_OFFSET(CompiledMethodDesc, _jvmpi_code_size);
  }
#endif


  HANDLE_DEFINITION_CHECK(CompiledMethod, Oop);
 
  // Returns the method causing this code
  // ^ Method
  ReturnOop method() const {
    return obj_field(method_offset());
  }
  void set_method(Oop* value) {
    obj_field_put(method_offset(), value);
  }

  // Returns the size of the dynamic part
  jint size() const {
    return ((CompiledMethodDesc*)obj())->code_size();
  }

private:
  juint flags_and_size() {
    return uint_field(flags_and_size_offset());
  }
  void set_flags_and_size(const juint value) {
    uint_field_put(flags_and_size_offset(), value);
  }

public:
  void set_has_branch_relocation() {
    juint fs = flags_and_size();
    fs |= CompiledMethodDesc::HAS_BRANCH_RELOCATION_MASK;
    set_flags_and_size(fs);
  }

#if ENABLE_JVMPI_PROFILE
  // Return the compiled code size    
  jint jvmpi_code_size() const {
    return ((CompiledMethodDesc*)obj())->jvmpi_get_code_size();
  }
#endif

  // Returns the end_offset for the object (used by RelocationStream)
  jint end_offset() const {
    return base_offset() + size();
  }

  // Return the address of the entry.
  address entry() const {
    return ((CompiledMethodDesc*)obj())->entry();
  }

  // Shrinks the compiled method to remove wasted padding (used at end
  // of code generation)
  void shrink(jint code_size, jint relocation_size);

  // Expand the compiled methid in-place (by moving the relocation data 
  // to higher address). This works only when this method is being
  // compiled, and compiler_area is enabled.
  // Returns true if successful; false if there's insufficient space
  // in the compiler_area to accomodate the request, in which case
  // the size of this compiled method is not changed.
  bool expand_compiled_code_space(jint delta, jint relocation_size);

#if ENABLE_APPENDED_CALLINFO
  bool expand_callinfo_table(int delta);
  void shrink_callinfo_table(int delta);
#endif

  // Flushes the icache portion corresponding to the generated code
  void flush_icache();

#if ENABLE_ROM_GENERATOR
  int generate_fieldmap(TypeArray* field_map);
#endif

#if !defined(PRODUCT) || ENABLE_TTY_TRACE
  void print_code_on(Stream* st);
  void print_code_on(Stream* st, jint start, jint end);  // x86
  void print_comment_for(int code_offset, Stream* st);
  void print_relocation_on(Stream* st);
  void iterate(OopVisitor* visitor);
  void print_value_on(Stream* st);
  void print_name_on(Stream* st);
  static void iterate_oopmaps(oopmaps_doer do_map, void* param);
#endif
};

#if ENABLE_APPENDED_CALLINFO
class CallInfoWriter {
 private:
  CompiledMethod * _compiled_method;
  int _current_callinfo_code_offset;
  int _current_record_offset; // Offset from end of compiled method.
  int _current_record_header_size; 
  int _compressed_stackmap_length;
  int _previous_stackmap_offset; // Offset from end of compiled method.
  int _previous_stackmap_size;

  CompiledMethod * compiled_method() const {
    return _compiled_method;
  }

  int current_record_offset() const {
    return _current_record_offset;
  }

  int compressed_stackmap_length() const {
    return _compressed_stackmap_length;
  }

  void update_current_record_offset(jint delta);
  void update_method_end_based_offsets(jint delta);

  void set_record_header_size(int size);
  int record_header_size() const;

  void set_previous_stackmap_offset(int offset);
  int previous_stackmap_offset() const;

  void set_previous_stackmap_size(int size);
  int previous_stackmap_size() const;

  bool stackmap_same_as_previous(int stackmap_offset, 
                                 int stackmap_size) const;

  int callinfo_code_offset() const {
    return _current_callinfo_code_offset;
  }
  void set_callinfo_code_offset(int offset) {
    _current_callinfo_code_offset = offset;
  }
  // Returns the length of this record header.
  int write_record_header(int code_offset_from_previous, 
                          int bci, int stackmap_size JVM_TRAPS);
  // Encodes the value, writes it into the compiled method at the given offset
  // and returns the number of bytes written.
  int write_encoded_value(int value, int offset);
  // Returns the size of encoded value for the given value.
  int encoded_value_size(int value);
  void allocate_record(size_t record_size JVM_TRAPS);
  void adjust_table_size(int delta JVM_TRAPS);
  enum {
    EXPANSION_DELTA = 256
  };
 public:
  void initialize(CompiledMethod * const compiled_method);
  // Returns false if failed to allocate a new record in the table.
  void start_record(int code_offset, int bci, int stackmap_size JVM_TRAPS);
  void write_oop_tag_at(const int index);
  void commit_record();
  void commit_table();
};

class CallInfoRecord {
 private:
  const CompiledMethod * _compiled_method;
  int _current_record_offset;
  int _current_record_code_offset;
  int _current_record_bci;
  int _current_record_stackmap_offset;
  int _current_record_stackmap_size;
  int _current_record_size;

  const CompiledMethod * compiled_method() const {
    return _compiled_method;
  }
  int record_offset() const {
    return _current_record_offset;
  }
  jubyte record_ubyte_at(int offset) const {
    return compiled_method()->ubyte_field(record_offset() + offset);
  }

  // Reads the encoded value at the given offset, decodes it and returns and
  // returns the number of bytes read.
  int read_encoded_value(int& value, int offset);
  int compute_stackmap_size(int stackmap_offset);

  int stackmap_size() const;
  int stackmap_offset() const;
  int record_code_offset() const;
  int record_size() const;
  void read_record();
  void next_record();
  void init(const CompiledMethod * const compiled_method,
            const address return_address);
 public:
  CallInfoRecord(const CompiledMethod * const compiled_method,
                 const address return_address) {
    // NB. init() is used here to fix CR 6297942.
    init(compiled_method, return_address);
  }

  int bci() const {
    return _current_record_bci;
  }
  bool oop_tag_at(int index) const;

  static void index_to_offsets(int index, int& byte_offset, int& bit_offset);

  enum {
    same_stackmap_bit = 0x1,
    value_end_bit     = 0x80
  };

  // Table header layout.
  enum {
    length_width = 12,
    type_width   = 4,
    length_start = 0,
    type_start   = length_start + length_width,
    table_header_size = 2
  };
};
#endif // ENABLE_APPENDED_CALLINFO
