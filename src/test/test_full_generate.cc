/** @file test_full_generate.cc
 * 
 * Generates byte arrays used for the test_full.c testcases.
 * 
 * Copyright 2009 Simon Kallweit
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define __STDC_LIMIT_MACROS
#include "generated/test_full.pb.h"
#include <inttypes.h>

using namespace foo;

#define protobuf_c_boolean bool
#define TEST_ENUM_SMALL_TYPE_NAME  TestEnumSmall
#define TEST_ENUM_SMALL(NAME)      foo::NAME
#define TEST_ENUM_TYPE_NAME        TestEnum
#define TEST_ENUM(NAME)            foo::NAME
#include "test_full_arrays.h"
#define N_ELEMENTS(arr)   (sizeof(arr)/sizeof((arr)[0]))

static void
dump_message_bytes(google::protobuf::Message *message,
                   const char *label)
{
  std::string rv;
  unsigned char *bytes;
  unsigned len;
  if (!message->SerializeToString(&rv))
    assert(0);
  bytes = (unsigned char *) rv.data();
  len = rv.size();
  printf ("static const u8_t %s[%u] = { ", label, len);
  for (unsigned i = 0; i < len; i++) {
    if (i)
      printf (", ");
    printf ("0x%02x", bytes[i]);
  }
  printf (" };\n");
}

static void
dump_test_enum_small (void)
{
  TestMessRequiredEnumSmall es;
  es.set_test(VALUE);
  dump_message_bytes(&es, "test_enum_small_VALUE");
  es.set_test(OTHER_VALUE);
  dump_message_bytes(&es, "test_enum_small_OTHER_VALUE");
}
static void
dump_test_enum_big (void)
{
  TestMessRequiredEnum eb;
  eb.set_test(VALUE0); dump_message_bytes(&eb, "test_enum_big_VALUE0");
  eb.set_test(VALUE127); dump_message_bytes(&eb, "test_enum_big_VALUE127");
  eb.set_test(VALUE128); dump_message_bytes(&eb, "test_enum_big_VALUE128");
  eb.set_test(VALUE16383); dump_message_bytes(&eb, "test_enum_big_VALUE16383");
  eb.set_test(VALUE16384); dump_message_bytes(&eb, "test_enum_big_VALUE16384");
  eb.set_test(VALUE2097151); dump_message_bytes(&eb, "test_enum_big_VALUE2097151");
  eb.set_test(VALUE2097152); dump_message_bytes(&eb, "test_enum_big_VALUE2097152");
  eb.set_test(VALUE268435455); dump_message_bytes(&eb, "test_enum_big_VALUE268435455");
  eb.set_test(VALUE268435456); dump_message_bytes(&eb, "test_enum_big_VALUE268435456");
}

static void
dump_test_field_numbers (void)
{
#define DUMP_ONE(num) \
  { TestFieldNo##num f; \
    f.set_test("tst"); \
    dump_message_bytes(&f, "test_field_number_" #num); }
  DUMP_ONE (15)
  DUMP_ONE (16)
  DUMP_ONE (2047)
  DUMP_ONE (2048)
  DUMP_ONE (262143)
  DUMP_ONE (262144)
  DUMP_ONE (33554431)
  DUMP_ONE (33554432)
#undef DUMP_ONE
} 

static void dump_test_required_int32 (void)
{
  TestMessRequiredInt32 mess;
  mess.set_test (INT32_MIN);
  dump_message_bytes (&mess, "test_required_int32_min");
  mess.set_test (-1000);
  dump_message_bytes (&mess, "test_required_int32_m1000");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_int32_0");
  mess.set_test (INT32_MAX);
  dump_message_bytes (&mess, "test_required_int32_max");
}

static void dump_test_required_sint32 (void)
{
  TestMessRequiredSInt32 mess;
  mess.set_test (INT32_MIN);
  dump_message_bytes (&mess, "test_required_sint32_min");
  mess.set_test (-1000);
  dump_message_bytes (&mess, "test_required_sint32_m1000");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_sint32_0");
  mess.set_test (INT32_MAX);
  dump_message_bytes (&mess, "test_required_sint32_max");
}

static void dump_test_required_sfixed32 (void)
{
  TestMessRequiredSFixed32 mess;
  mess.set_test (INT32_MIN);
  dump_message_bytes (&mess, "test_required_sfixed32_min");
  mess.set_test (-1000);
  dump_message_bytes (&mess, "test_required_sfixed32_m1000");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_sfixed32_0");
  mess.set_test (INT32_MAX);
  dump_message_bytes (&mess, "test_required_sfixed32_max");
}

static void dump_test_required_uint32 (void)
{
  TestMessRequiredUInt32 mess;
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_uint32_0");
  mess.set_test (MILLION);
  dump_message_bytes (&mess, "test_required_uint32_million");
  mess.set_test (UINT32_MAX);
  dump_message_bytes (&mess, "test_required_uint32_max");
}

static void dump_test_required_fixed32 (void)
{
  TestMessRequiredFixed32 mess;
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_fixed32_0");
  mess.set_test (MILLION);
  dump_message_bytes (&mess, "test_required_fixed32_million");
  mess.set_test (UINT32_MAX);
  dump_message_bytes (&mess, "test_required_fixed32_max");
}

static void dump_test_required_int64 (void)
{
  TestMessRequiredInt64 mess;
  mess.set_test (INT64_MIN);
  dump_message_bytes (&mess, "test_required_int64_min");
  mess.set_test (-TRILLION);
  dump_message_bytes (&mess, "test_required_int64_mtril");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_int64_0");
  mess.set_test (QUADRILLION);
  dump_message_bytes (&mess, "test_required_int64_quad");
  mess.set_test (INT64_MAX);
  dump_message_bytes (&mess, "test_required_int64_max");
}

static void dump_test_required_sint64 (void)
{
  TestMessRequiredSInt64 mess;
  mess.set_test (INT64_MIN);
  dump_message_bytes (&mess, "test_required_sint64_min");
  mess.set_test (-TRILLION);
  dump_message_bytes (&mess, "test_required_sint64_mtril");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_sint64_0");
  mess.set_test (QUADRILLION);
  dump_message_bytes (&mess, "test_required_sint64_quad");
  mess.set_test (INT64_MAX);
  dump_message_bytes (&mess, "test_required_sint64_max");
}

static void dump_test_required_sfixed64 (void)
{
  TestMessRequiredSFixed64 mess;
  mess.set_test (INT64_MIN);
  dump_message_bytes (&mess, "test_required_sfixed64_min");
  mess.set_test (-TRILLION);
  dump_message_bytes (&mess, "test_required_sfixed64_mtril");
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_sfixed64_0");
  mess.set_test (QUADRILLION);
  dump_message_bytes (&mess, "test_required_sfixed64_quad");
  mess.set_test (INT64_MAX);
  dump_message_bytes (&mess, "test_required_sfixed64_max");
}

static void dump_test_required_uint64 (void)
{
  TestMessRequiredUInt64 mess;
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_uint64_0");
  mess.set_test (THOUSAND);
  dump_message_bytes (&mess, "test_required_uint64_thou");
  mess.set_test (MILLION);
  dump_message_bytes (&mess, "test_required_uint64_mill");
  mess.set_test (BILLION);
  dump_message_bytes (&mess, "test_required_uint64_bill");
  mess.set_test (TRILLION);
  dump_message_bytes (&mess, "test_required_uint64_tril");
  mess.set_test (QUADRILLION);
  dump_message_bytes (&mess, "test_required_uint64_quad");
  mess.set_test (QUINTILLION);
  dump_message_bytes (&mess, "test_required_uint64_quint");
  mess.set_test (UINT64_MAX);
  dump_message_bytes (&mess, "test_required_uint64_max");
}

static void dump_test_required_fixed64 (void)
{
  TestMessRequiredFixed64 mess;
  mess.set_test (0);
  dump_message_bytes (&mess, "test_required_fixed64_0");
  mess.set_test (THOUSAND);
  dump_message_bytes (&mess, "test_required_fixed64_thou");
  mess.set_test (MILLION);
  dump_message_bytes (&mess, "test_required_fixed64_mill");
  mess.set_test (BILLION);
  dump_message_bytes (&mess, "test_required_fixed64_bill");
  mess.set_test (TRILLION);
  dump_message_bytes (&mess, "test_required_fixed64_tril");
  mess.set_test (QUADRILLION);
  dump_message_bytes (&mess, "test_required_fixed64_quad");
  mess.set_test (QUINTILLION);
  dump_message_bytes (&mess, "test_required_fixed64_quint");
  mess.set_test (UINT64_MAX);
  dump_message_bytes (&mess, "test_required_fixed64_max");
}

static void dump_test_required_float (void)
{
  TestMessRequiredFloat mess;
  mess.set_test(-THOUSAND);
  dump_message_bytes (&mess, "test_required_float_mthou");
  mess.set_test(0);
  dump_message_bytes (&mess, "test_required_float_0");
  mess.set_test(420);
  dump_message_bytes (&mess, "test_required_float_420");
}

static void dump_test_required_double (void)
{
  TestMessRequiredDouble mess;
  mess.set_test(-THOUSAND);
  dump_message_bytes (&mess, "test_required_double_mthou");
  mess.set_test(0);
  dump_message_bytes (&mess, "test_required_double_0");
  mess.set_test(420);
  dump_message_bytes (&mess, "test_required_double_420");
}

static void dump_test_required_bool (void)
{
  TestMessRequiredBool mess;
  mess.set_test(false);
  dump_message_bytes (&mess, "test_required_bool_0");
  mess.set_test(true);
  dump_message_bytes (&mess, "test_required_bool_1");
}

static void dump_test_required_enum_small (void)
{
  TestMessRequiredEnumSmall mess;
  mess.set_test(VALUE);
  dump_message_bytes (&mess, "test_required_enum_small_VALUE");
  mess.set_test(OTHER_VALUE);
  dump_message_bytes (&mess, "test_required_enum_small_OTHER_VALUE");
}

static void dump_test_required_enum (void)
{
  TestMessRequiredEnum mess;
  mess.set_test (VALUE0);
  dump_message_bytes (&mess, "test_required_enum_0");
  mess.set_test (VALUE1);
  dump_message_bytes (&mess, "test_required_enum_1");
  mess.set_test (VALUE127);
  dump_message_bytes (&mess, "test_required_enum_127");
  mess.set_test (VALUE128);
  dump_message_bytes (&mess, "test_required_enum_128");
  mess.set_test (VALUE16383);
  dump_message_bytes (&mess, "test_required_enum_16383");
  mess.set_test (VALUE16384);
  dump_message_bytes (&mess, "test_required_enum_16384");
  mess.set_test (VALUE2097151);
  dump_message_bytes (&mess, "test_required_enum_2097151");
  mess.set_test (VALUE2097152);
  dump_message_bytes (&mess, "test_required_enum_2097152");
  mess.set_test (VALUE268435455);
  dump_message_bytes (&mess, "test_required_enum_268435455");
  mess.set_test (VALUE268435456);
  dump_message_bytes (&mess, "test_required_enum_268435456");
}

static void dump_test_required_string (void)
{
  TestMessRequiredString mess;
  mess.set_test ("");
  dump_message_bytes(&mess, "test_required_string_empty");
  mess.set_test ("hello");
  dump_message_bytes(&mess, "test_required_string_hello");
  mess.set_test ("two hundred xs follow: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  dump_message_bytes(&mess, "test_required_string_long");
}

static void dump_test_required_bytes (void)
{
  TestMessRequiredBytes mess;
  mess.set_test ("");
  dump_message_bytes (&mess, "test_required_bytes_empty");
  mess.set_test ("hello");
  dump_message_bytes (&mess, "test_required_bytes_hello");
  mess.set_test (std::string("\1") + '\0' + "\375\2\4");
  dump_message_bytes (&mess, "test_required_bytes_random");
}

static void dump_test_required_message (void)
{
  TestMessRequiredMessage mess;
  mess.mutable_test()->set_test(0);
  dump_message_bytes (&mess, "test_required_submess_0");
  mess.mutable_test()->set_test(42);
  dump_message_bytes (&mess, "test_required_submess_42");
}

static void dump_test_optional_int32 (void)
{
  TestMessOptional opt;
  opt.set_test_int32 (INT32_MIN);
  dump_message_bytes (&opt, "test_optional_int32_min");
  opt.set_test_int32 (-1);
  dump_message_bytes (&opt, "test_optional_int32_m1");
  opt.set_test_int32 (0);
  dump_message_bytes (&opt, "test_optional_int32_0");
  opt.set_test_int32 (666);
  dump_message_bytes (&opt, "test_optional_int32_666");
  opt.set_test_int32 (INT32_MAX);
  dump_message_bytes (&opt, "test_optional_int32_max");
}

static void dump_test_optional_sint32 (void)
{
  TestMessOptional opt;
  opt.set_test_sint32 (INT32_MIN);
  dump_message_bytes (&opt, "test_optional_sint32_min");
  opt.set_test_sint32 (-1);
  dump_message_bytes (&opt, "test_optional_sint32_m1");
  opt.set_test_sint32 (0);
  dump_message_bytes (&opt, "test_optional_sint32_0");
  opt.set_test_sint32 (666);
  dump_message_bytes (&opt, "test_optional_sint32_666");
  opt.set_test_sint32 (INT32_MAX);
  dump_message_bytes (&opt, "test_optional_sint32_max");
}

static void dump_test_optional_sfixed32 (void)
{
  TestMessOptional opt;
  opt.set_test_sfixed32 (INT32_MIN);
  dump_message_bytes (&opt, "test_optional_sfixed32_min");
  opt.set_test_sfixed32 (-1);
  dump_message_bytes (&opt, "test_optional_sfixed32_m1");
  opt.set_test_sfixed32 (0);
  dump_message_bytes (&opt, "test_optional_sfixed32_0");
  opt.set_test_sfixed32 (666);
  dump_message_bytes (&opt, "test_optional_sfixed32_666");
  opt.set_test_sfixed32 (INT32_MAX);
  dump_message_bytes (&opt, "test_optional_sfixed32_max");
}

static void dump_test_optional_int64 (void)
{
  TestMessOptional opt;
  opt.set_test_int64 (INT64_MIN);
  dump_message_bytes (&opt, "test_optional_int64_min");
  opt.set_test_int64 (-1111111111LL);
  dump_message_bytes (&opt, "test_optional_int64_m1111111111LL");
  opt.set_test_int64 (0);
  dump_message_bytes (&opt, "test_optional_int64_0");
  opt.set_test_int64 (QUINTILLION);
  dump_message_bytes (&opt, "test_optional_int64_quintillion");
  opt.set_test_int64 (INT64_MAX);
  dump_message_bytes (&opt, "test_optional_int64_max");
}
static void dump_test_optional_sint64 (void)
{
  TestMessOptional opt;
  opt.set_test_sint64 (INT64_MIN);
  dump_message_bytes (&opt, "test_optional_sint64_min");
  opt.set_test_sint64 (-1111111111LL);
  dump_message_bytes (&opt, "test_optional_sint64_m1111111111LL");
  opt.set_test_sint64 (0);
  dump_message_bytes (&opt, "test_optional_sint64_0");
  opt.set_test_sint64 (QUINTILLION);
  dump_message_bytes (&opt, "test_optional_sint64_quintillion");
  opt.set_test_sint64 (INT64_MAX);
  dump_message_bytes (&opt, "test_optional_sint64_max");
}
static void dump_test_optional_sfixed64 (void)
{
  TestMessOptional opt;
  opt.set_test_sfixed64 (INT64_MIN);
  dump_message_bytes (&opt, "test_optional_sfixed64_min");
  opt.set_test_sfixed64 (-1111111111LL);
  dump_message_bytes (&opt, "test_optional_sfixed64_m1111111111LL");
  opt.set_test_sfixed64 (0);
  dump_message_bytes (&opt, "test_optional_sfixed64_0");
  opt.set_test_sfixed64 (QUINTILLION);
  dump_message_bytes (&opt, "test_optional_sfixed64_quintillion");
  opt.set_test_sfixed64 (INT64_MAX);
  dump_message_bytes (&opt, "test_optional_sfixed64_max");
}
static void dump_test_optional_uint32 (void)
{
  TestMessOptional opt;
  opt.set_test_uint32(0);
  dump_message_bytes (&opt, "test_optional_uint32_0");
  opt.set_test_uint32(669);
  dump_message_bytes (&opt, "test_optional_uint32_669");
  opt.set_test_uint32(UINT32_MAX);
  dump_message_bytes (&opt, "test_optional_uint32_max");
}
static void dump_test_optional_fixed32 (void)
{
  TestMessOptional opt;
  opt.set_test_fixed32(0);
  dump_message_bytes (&opt, "test_optional_fixed32_0");
  opt.set_test_fixed32(669);
  dump_message_bytes (&opt, "test_optional_fixed32_669");
  opt.set_test_fixed32(UINT32_MAX);
  dump_message_bytes (&opt, "test_optional_fixed32_max");
}

static void dump_test_optional_uint64 (void)
{
  TestMessOptional opt;
  opt.set_test_uint64(0);
  dump_message_bytes (&opt, "test_optional_uint64_0");
  opt.set_test_uint64(669669669669669ULL);
  dump_message_bytes (&opt, "test_optional_uint64_669669669669669");
  opt.set_test_uint64(UINT64_MAX);
  dump_message_bytes (&opt, "test_optional_uint64_max");
}

static void dump_test_optional_fixed64 (void)
{
  TestMessOptional opt;
  opt.set_test_fixed64(0);
  dump_message_bytes (&opt, "test_optional_fixed64_0");
  opt.set_test_fixed64(669669669669669ULL);
  dump_message_bytes (&opt, "test_optional_fixed64_669669669669669");
  opt.set_test_fixed64(UINT64_MAX);
  dump_message_bytes (&opt, "test_optional_fixed64_max");
}

static void dump_test_optional_float (void)
{
  TestMessOptional opt;
  opt.set_test_float (-100);
  dump_message_bytes (&opt, "test_optional_float_m100");
  opt.set_test_float (0);
  dump_message_bytes (&opt, "test_optional_float_0");
  opt.set_test_float (141243);
  dump_message_bytes (&opt, "test_optional_float_141243");
}

static void dump_test_optional_double (void)
{
  TestMessOptional opt;
  opt.set_test_double (-100);
  dump_message_bytes (&opt, "test_optional_double_m100");
  opt.set_test_double (0);
  dump_message_bytes (&opt, "test_optional_double_0");
  opt.set_test_double (141243);
  dump_message_bytes (&opt, "test_optional_double_141243");
}

static void dump_test_optional_bool (void)
{
  TestMessOptional opt;
  opt.set_test_boolean (false);
  dump_message_bytes (&opt, "test_optional_bool_0");
  opt.set_test_boolean (true);
  dump_message_bytes (&opt, "test_optional_bool_1");
}

static void dump_test_optional_enum_small (void)
{
  TestMessOptional opt;
  opt.set_test_enum_small (VALUE);
  dump_message_bytes (&opt, "test_optional_enum_small_0");
  opt.set_test_enum_small (OTHER_VALUE);
  dump_message_bytes (&opt, "test_optional_enum_small_1");
}
static void dump_test_optional_enum (void)
{
  TestMessOptional opt;
//for a in 0 1 127 128 16383 16384 2097151 2097152 268435455 268435456 ; do
//echo '    opt.set_test_enum (VALUE'$a');
//dump_message_bytes (&opt, "test_optional_enum_'$a'");'
//done
    opt.set_test_enum (VALUE0);
    dump_message_bytes (&opt, "test_optional_enum_0");
    opt.set_test_enum (VALUE1);
    dump_message_bytes (&opt, "test_optional_enum_1");
    opt.set_test_enum (VALUE127);
    dump_message_bytes (&opt, "test_optional_enum_127");
    opt.set_test_enum (VALUE128);
    dump_message_bytes (&opt, "test_optional_enum_128");
    opt.set_test_enum (VALUE16383);
    dump_message_bytes (&opt, "test_optional_enum_16383");
    opt.set_test_enum (VALUE16384);
    dump_message_bytes (&opt, "test_optional_enum_16384");
    opt.set_test_enum (VALUE2097151);
    dump_message_bytes (&opt, "test_optional_enum_2097151");
    opt.set_test_enum (VALUE2097152);
    dump_message_bytes (&opt, "test_optional_enum_2097152");
    opt.set_test_enum (VALUE268435455);
    dump_message_bytes (&opt, "test_optional_enum_268435455");
    opt.set_test_enum (VALUE268435456);
    dump_message_bytes (&opt, "test_optional_enum_268435456");
}
static void dump_test_optional_string (void)
{
  TestMessOptional opt;
  opt.set_test_string ("");
  dump_message_bytes (&opt, "test_optional_string_empty");
  opt.set_test_string ("hello");
  dump_message_bytes (&opt, "test_optional_string_hello");
}
static void dump_test_optional_bytes (void)
{
  TestMessOptional opt;
  opt.set_test_bytes ("");
  dump_message_bytes (&opt, "test_optional_bytes_empty");
  opt.set_test_bytes ("hello");
  dump_message_bytes (&opt, "test_optional_bytes_hello");
  opt.set_test_bytes (std::string("\1") + '\0' + "\375\2\4");
  dump_message_bytes (&opt, "test_optional_bytes_random");
}
static void dump_test_optional_message (void)
{
  TestMessOptional opt;
  opt.mutable_test_message()->set_test(0);
  dump_message_bytes (&opt, "test_optional_submess_0");
  opt.mutable_test_message()->set_test(42);
  dump_message_bytes (&opt, "test_optional_submess_42");
}

#define DUMP_STATIC_ARRAY_GENERIC(member, static_array, output_array_name) \
  do{ \
    TestMess mess; \
    for (unsigned i = 0; i < N_ELEMENTS (static_array); i++) \
      mess.add_##member(static_array[i]); \
    dump_message_bytes(&mess, output_array_name); \
  }while(0)
static void dump_test_repeated_int32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_int32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_repeated_int32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_repeated_int32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_repeated_int32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_sint32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sint32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_repeated_sint32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_repeated_sint32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_repeated_sint32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_uint32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_uint32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (uint32_roundnumbers, "test_repeated_uint32_roundnumbers");
  DUMP_STATIC_ARRAY (uint32_0_max, "test_repeated_uint32_0_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_sfixed32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sfixed32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_repeated_sfixed32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_repeated_sfixed32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_repeated_sfixed32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_fixed32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_fixed32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (uint32_roundnumbers, "test_repeated_fixed32_roundnumbers");
  DUMP_STATIC_ARRAY (uint32_0_max, "test_repeated_fixed32_0_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_int64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_int64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_repeated_int64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_repeated_int64_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_sint64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sint64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_repeated_sint64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_repeated_sint64_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_sfixed64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sfixed64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_repeated_sfixed64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_repeated_sfixed64_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_uint64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_uint64, static_array, output_array_name)

  DUMP_STATIC_ARRAY(uint64_roundnumbers, "test_repeated_uint64_roundnumbers");
  DUMP_STATIC_ARRAY(uint64_0_1_max, "test_repeated_uint64_0_1_max");
  DUMP_STATIC_ARRAY(uint64_random, "test_repeated_uint64_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_fixed64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_fixed64, static_array, output_array_name)

  DUMP_STATIC_ARRAY(uint64_roundnumbers, "test_repeated_fixed64_roundnumbers");
  DUMP_STATIC_ARRAY(uint64_0_1_max, "test_repeated_fixed64_0_1_max");
  DUMP_STATIC_ARRAY(uint64_random, "test_repeated_fixed64_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_float (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_float, static_array, output_array_name)

  DUMP_STATIC_ARRAY(float_random, "test_repeated_float_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_double (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_double, static_array, output_array_name)

  DUMP_STATIC_ARRAY(double_random, "test_repeated_double_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_boolean (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_boolean, static_array, output_array_name)

  DUMP_STATIC_ARRAY(boolean_0, "test_repeated_boolean_0");
  DUMP_STATIC_ARRAY(boolean_1, "test_repeated_boolean_1");
  DUMP_STATIC_ARRAY(boolean_random, "test_repeated_boolean_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_repeated_enum_small (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_enum_small, static_array, output_array_name)

  DUMP_STATIC_ARRAY (enum_small_0, "test_repeated_enum_small_0");
  DUMP_STATIC_ARRAY (enum_small_1, "test_repeated_enum_small_1");
  DUMP_STATIC_ARRAY (enum_small_random, "test_repeated_enum_small_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_enum (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_enum, static_array, output_array_name)

  DUMP_STATIC_ARRAY (enum_0, "test_repeated_enum_0");
  DUMP_STATIC_ARRAY (enum_1, "test_repeated_enum_1");
  DUMP_STATIC_ARRAY (enum_random, "test_repeated_enum_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_string (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_string, static_array, output_array_name)

  DUMP_STATIC_ARRAY (repeated_strings_0, "test_repeated_strings_0");
  DUMP_STATIC_ARRAY (repeated_strings_1, "test_repeated_strings_1");
  DUMP_STATIC_ARRAY (repeated_strings_2, "test_repeated_strings_2");
  DUMP_STATIC_ARRAY (repeated_strings_3, "test_repeated_strings_3");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_repeated_bytes (void)
{
  TestMess mess;
  mess.add_test_bytes(std::string("text"));
  mess.add_test_bytes(std::string("str\1\2\3\4\5") + '\0');
  mess.add_test_bytes(std::string("gobble") + '\0' + "foo");
  dump_message_bytes(&mess, "test_repeated_bytes_0");
}

static void dump_test_repeated_SubMess (void)
{
  TestMess mess;
  mess.add_test_message()->set_test(0);
  mess.add_test_message()->set_test(0);
  mess.add_test_message()->set_test(0);
  dump_message_bytes(&mess, "test_repeated_submess_0");

  mess.clear_test_message();
  mess.add_test_message()->set_test(42);
  mess.add_test_message()->set_test(-10000);
  mess.add_test_message()->set_test(667);
  dump_message_bytes(&mess, "test_repeated_submess_1");
}

#undef DUMP_STATIC_ARRAY_GENERIC


#define DUMP_STATIC_ARRAY_GENERIC(member, static_array, output_array_name) \
  do{ \
    TestMessPacked mess; \
    for (unsigned i = 0; i < N_ELEMENTS (static_array); i++) \
      mess.add_##member(static_array[i]); \
    dump_message_bytes(&mess, output_array_name); \
  }while(0)
static void dump_test_packed_repeated_int32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_int32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_packed_repeated_int32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_packed_repeated_int32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_packed_repeated_int32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_sint32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sint32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_packed_repeated_sint32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_packed_repeated_sint32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_packed_repeated_sint32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_uint32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_uint32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (uint32_roundnumbers, "test_packed_repeated_uint32_roundnumbers");
  DUMP_STATIC_ARRAY (uint32_0_max, "test_packed_repeated_uint32_0_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_sfixed32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sfixed32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int32_arr0, "test_packed_repeated_sfixed32_arr0");
  DUMP_STATIC_ARRAY (int32_arr1, "test_packed_repeated_sfixed32_arr1");
  DUMP_STATIC_ARRAY (int32_arr_min_max, "test_packed_repeated_sfixed32_arr_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_fixed32 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_fixed32, static_array, output_array_name)

  DUMP_STATIC_ARRAY (uint32_roundnumbers, "test_packed_repeated_fixed32_roundnumbers");
  DUMP_STATIC_ARRAY (uint32_0_max, "test_packed_repeated_fixed32_0_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_int64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_int64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_packed_repeated_int64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_packed_repeated_int64_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_sint64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sint64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_packed_repeated_sint64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_packed_repeated_sint64_min_max");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_sfixed64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_sfixed64, static_array, output_array_name)

  DUMP_STATIC_ARRAY (int64_roundnumbers, "test_packed_repeated_sfixed64_roundnumbers");
  DUMP_STATIC_ARRAY (int64_min_max, "test_packed_repeated_sfixed64_min_max");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_uint64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_uint64, static_array, output_array_name)

  DUMP_STATIC_ARRAY(uint64_roundnumbers, "test_packed_repeated_uint64_roundnumbers");
  DUMP_STATIC_ARRAY(uint64_0_1_max, "test_packed_repeated_uint64_0_1_max");
  DUMP_STATIC_ARRAY(uint64_random, "test_packed_repeated_uint64_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_fixed64 (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_fixed64, static_array, output_array_name)

  DUMP_STATIC_ARRAY(uint64_roundnumbers, "test_packed_repeated_fixed64_roundnumbers");
  DUMP_STATIC_ARRAY(uint64_0_1_max, "test_packed_repeated_fixed64_0_1_max");
  DUMP_STATIC_ARRAY(uint64_random, "test_packed_repeated_fixed64_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_float (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_float, static_array, output_array_name)

  DUMP_STATIC_ARRAY(float_random, "test_packed_repeated_float_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_double (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_double, static_array, output_array_name)

  DUMP_STATIC_ARRAY(double_random, "test_packed_repeated_double_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_boolean (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC(test_boolean, static_array, output_array_name)

  DUMP_STATIC_ARRAY(boolean_0, "test_packed_repeated_boolean_0");
  DUMP_STATIC_ARRAY(boolean_1, "test_packed_repeated_boolean_1");
  DUMP_STATIC_ARRAY(boolean_random, "test_packed_repeated_boolean_random");

#undef DUMP_STATIC_ARRAY
}
static void dump_test_packed_repeated_enum_small (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_enum_small, static_array, output_array_name)

  DUMP_STATIC_ARRAY (enum_small_0, "test_packed_repeated_enum_small_0");
  DUMP_STATIC_ARRAY (enum_small_1, "test_packed_repeated_enum_small_1");
  DUMP_STATIC_ARRAY (enum_small_random, "test_packed_repeated_enum_small_random");

#undef DUMP_STATIC_ARRAY
}

static void dump_test_packed_repeated_enum (void)
{
#define DUMP_STATIC_ARRAY(static_array, output_array_name) \
  DUMP_STATIC_ARRAY_GENERIC (test_enum, static_array, output_array_name)

  DUMP_STATIC_ARRAY (enum_0, "test_packed_repeated_enum_0");
  DUMP_STATIC_ARRAY (enum_1, "test_packed_repeated_enum_1");
  DUMP_STATIC_ARRAY (enum_random, "test_packed_repeated_enum_random");

#undef DUMP_STATIC_ARRAY
}

#undef DUMP_STATIC_ARRAY_GENERIC



#if 0

static void dump_test_unknown_fields (void)
{
  EmptyMess mess;
  const google::protobuf::Message::Reflection *reflection = mess.GetReflection();
  google::protobuf::UnknownFieldSet *fs = reflection->MutableUnknownFields(&mess);
  google::protobuf::UnknownField *f;
  f = fs->AddField(5454);
  f->add_varint(255);
  f = fs->AddField(5555);
  f->add_fixed32(260);
  dump_message_bytes (&mess, "test_unknown_fields_0");

  fs->Clear();
  f = fs->AddField(6666);
  f->add_length_delimited("xxxxxxxx");
  f = fs->AddField(7777);
  f->add_fixed64(0x10101);
  dump_message_bytes (&mess, "test_unknown_fields_1");
}

#endif

int main()
{
  dump_test_enum_small ();
  dump_test_enum_big ();
  dump_test_field_numbers ();
  
  dump_test_required_int32 ();
  dump_test_required_sint32 ();
  dump_test_required_sfixed32 ();
  dump_test_required_uint32 ();
  dump_test_required_fixed32 ();
  dump_test_required_int64 ();
  dump_test_required_sint64 ();
  dump_test_required_sfixed64 ();
  dump_test_required_uint64 ();
  dump_test_required_fixed64 ();
  dump_test_required_float ();
  dump_test_required_double ();
  dump_test_required_bool ();
  dump_test_required_enum_small ();
  dump_test_required_enum ();
  dump_test_required_string ();
  dump_test_required_bytes ();
  dump_test_required_message ();
  
  dump_test_optional_int32 ();
  dump_test_optional_sint32 ();
  dump_test_optional_sfixed32 ();
  dump_test_optional_int64 ();
  dump_test_optional_sint64 ();
  dump_test_optional_sfixed64 ();
  dump_test_optional_uint32 ();
  dump_test_optional_fixed32 ();
  dump_test_optional_uint64 ();
  dump_test_optional_fixed64 ();
  dump_test_optional_float ();
  dump_test_optional_double ();
  dump_test_optional_bool ();
  dump_test_optional_enum_small ();
  dump_test_optional_enum ();
  dump_test_optional_string ();
  dump_test_optional_bytes ();
  dump_test_optional_message ();
  
  dump_test_repeated_int32 ();
  dump_test_repeated_sint32 ();
  dump_test_repeated_uint32 ();
  dump_test_repeated_sfixed32 ();
  dump_test_repeated_fixed32 ();
  dump_test_repeated_int64 ();
  dump_test_repeated_sint64 ();
  dump_test_repeated_sfixed64 ();
  dump_test_repeated_uint64 ();
  dump_test_repeated_fixed64 ();
  dump_test_repeated_float ();
  dump_test_repeated_double ();
  dump_test_repeated_boolean ();
  dump_test_repeated_enum_small ();
  dump_test_repeated_enum ();
  dump_test_repeated_string ();
  dump_test_repeated_bytes ();
  dump_test_repeated_SubMess ();
  
  dump_test_packed_repeated_int32 ();
  dump_test_packed_repeated_sint32 ();
  dump_test_packed_repeated_uint32 ();
  dump_test_packed_repeated_sfixed32 ();
  dump_test_packed_repeated_fixed32 ();
  dump_test_packed_repeated_int64 ();
  dump_test_packed_repeated_sint64 ();
  dump_test_packed_repeated_sfixed64 ();
  dump_test_packed_repeated_uint64 ();
  dump_test_packed_repeated_fixed64 ();
  dump_test_packed_repeated_float ();
  dump_test_packed_repeated_double ();
  dump_test_packed_repeated_boolean ();
  dump_test_packed_repeated_enum_small ();
  dump_test_packed_repeated_enum ();
  
//  dump_test_unknown_fields ();
  return 0;
}
