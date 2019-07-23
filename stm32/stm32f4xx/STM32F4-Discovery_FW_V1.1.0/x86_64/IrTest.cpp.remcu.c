/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#ifndef __cplusplus
typedef unsigned char bool;
#endif

#if defined(__GNUC__)
#define  __ATTRIBUTELIST__(x) __attribute__(x)
#else
#define  __ATTRIBUTELIST__(x)  
#endif

#ifdef _MSC_VER  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif



/* Global Declarations */

/* Types Declarations */
struct l_struct_struct_OC_anon;
struct l_struct_struct_OC_test_unpack_struct;
struct l_struct_struct_OC_test_pack_struct;
struct l_struct_struct_OC_MemCpyStruct;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_anon {
  uint32_t field0;
  uint32_t field1;
};
struct l_struct_struct_OC_test_unpack_struct {
  uint8_t field0;
  uint16_t field1;
  uint32_t field2;
};
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif
struct l_struct_struct_OC_test_pack_struct {
  uint8_t field0;
  uint16_t field1;
  uint32_t field2;
} __attribute__ ((packed));
#ifdef _MSC_VER
#pragma pack(pop)
#endif
struct l_array_1_uint8_t {
  uint8_t array[1];
};
struct l_struct_struct_OC_MemCpyStruct {
  struct l_array_1_uint8_t field0;
  struct l_struct_struct_OC_test_unpack_struct field1;
};
struct l_array_36_uint8_t {
  uint8_t array[36];
};
struct l_array_38_uint8_t {
  uint8_t array[38];
};
struct l_array_35_uint8_t {
  uint8_t array[35];
};
struct l_array_40_uint8_t {
  uint8_t array[40];
};
struct l_array_42_uint8_t {
  uint8_t array[42];
};
struct l_array_31_uint8_t {
  uint8_t array[31];
};
struct l_array_32_uint8_t {
  uint8_t array[32];
};
struct l_array_30_uint8_t {
  uint8_t array[30];
};
struct l_array_21_uint8_t {
  uint8_t array[21];
};
struct l_array_20_uint8_t {
  uint8_t array[20];
};
struct l_array_43_uint8_t {
  uint8_t array[43];
};
struct l_array_23_uint8_t {
  uint8_t array[23];
};
struct l_array_59_uint8_t {
  uint8_t array[59];
};

/* External Global Variable Declarations */

/* Function Declarations */
uint8_t* _Z10IR_RamTestPi(uint32_t*) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* Global Variable Definitions and Initialization */
static struct l_array_36_uint8_t _OC_str = { "getMemCpyStruct.field_1_8 == VALUE8" };
static struct l_array_38_uint8_t _OC_str_OC_1 = { "getMemCpyStruct.field_2_16 == VALUE16" };
static struct l_array_38_uint8_t _OC_str_OC_2 = { "getMemCpyStruct.field_3_32 == VALUE32" };
static struct l_array_35_uint8_t _OC_str_OC_3 = { "memcpy_struct->test.field_1_8 == 0" };
static struct l_array_36_uint8_t _OC_str_OC_4 = { "memcpy_struct->test.field_2_16 == 0" };
static struct l_array_36_uint8_t _OC_str_OC_5 = { "memcpy_struct->test.field_3_32 == 0" };
static struct l_array_40_uint8_t _OC_str_OC_6 = { "memcpy_struct->test.field_1_8 == VALUE8" };
static struct l_array_42_uint8_t _OC_str_OC_7 = { "memcpy_struct->test.field_2_16 == VALUE16" };
static struct l_array_42_uint8_t _OC_str_OC_8 = { "memcpy_struct->test.field_3_32 == VALUE32" };
static struct l_array_31_uint8_t _OC_str_OC_9 = { "getMemCpyStruct.field_1_8 == 0" };
static struct l_array_32_uint8_t _OC_str_OC_10 = { "getMemCpyStruct.field_2_16 == 0" };
static struct l_array_32_uint8_t _OC_str_OC_11 = { "getMemCpyStruct.field_3_32 == 0" };
static uint64_t _ZL15test_global_var = UINT64_C(81985529216486895);
static struct l_array_30_uint8_t _OC_str_OC_12 = { "test_global_var == LONG_VALUE" };
static struct l_struct_struct_OC_anon _ZL16test_struct_load = { 305419896, 2271560481u };
static struct l_array_32_uint8_t _OC_str_OC_13 = { "test_struct_load.a1 == A1_VALUE" };
static struct l_array_21_uint8_t _OC_str_OC_14 = { "*rem_addr == VALUE32" };
static struct l_array_20_uint8_t _OC_str_OC_15 = { "*rem_addr == VALUE8" };
static struct l_array_21_uint8_t _OC_str_OC_16 = { "*rem_addr == VALUE16" };
static struct l_array_43_uint8_t _OC_str_OC_17 = { "rem_addr[0] == ( (VALUE16 << 16) | VALUE8)" };
static struct l_array_23_uint8_t _OC_str_OC_18 = { "rem_addr[1] == VALUE32" };
static struct l_array_59_uint8_t _OC_str_OC_19 = { "rem_addr[0] == ((VALUE32 << 24) | (VALUE16 << 8) | VALUE8)" };
static struct l_array_30_uint8_t _OC_str_OC_20 = { "rem_addr[1] == (VALUE32 >> 8)" };


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

uint8_t* _Z10IR_RamTestPi(uint32_t* var_name_tmp__1) {
  uint8_t* var_name_tmp__2;    /* Address-exposed local */
  uint32_t* var_name_tmp__3;    /* Address-exposed local */
  uint32_t var_name_tmp__4;    /* Address-exposed local */
  uint8_t var_name_tmp__5;    /* Address-exposed local */
  uint16_t var_name_tmp__6;    /* Address-exposed local */
  struct l_struct_struct_OC_test_unpack_struct* var_name_tmp__7;    /* Address-exposed local */
  struct l_struct_struct_OC_test_pack_struct* var_name_tmp__8;    /* Address-exposed local */
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__9;    /* Address-exposed local */
  struct l_struct_struct_OC_test_unpack_struct var_name_tmp__10;    /* Address-exposed local */
  uint32_t* var_name_tmp__11;
  uint32_t* var_name_tmp__12;
  uint32_t* var_name_tmp__13;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__14;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__15;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__16;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__17;
  uint64_t var_name_load_i8_;
  uint64_t var_name_load_i16_;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__18;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__19;
  uint64_t var_name_load_i8_3;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__20;
  uint64_t var_name_load_i16_6;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__21;
  uint64_t var_name_load_i32_9;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__22;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__23;
  uint64_t var_name_load_i8_11;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__24;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_MemCpyStruct* var_name_tmp__25;
  uint64_t var_name_load_i32_17;
  uint64_t var_name_load_i8_19;
  uint64_t var_name_load_i16_22;
  uint64_t var_name_load_i32_25;
  uint64_t var_name_tmp__26;
  uint64_t var_name_load_i32_27;
  uint32_t* var_name_tmp__27;
  uint32_t* var_name_tmp__28;
  uint32_t* var_name_tmp__29;
  uint64_t var_name_load_i32_32;
  uint32_t* var_name_tmp__30;
  uint32_t* var_name_tmp__31;
  uint32_t* var_name_tmp__32;
  uint64_t var_name_load_i32_36;
  uint32_t* var_name_tmp__33;
  uint32_t* var_name_tmp__34;
  uint32_t* var_name_tmp__35;
  uint64_t var_name_load_i32_41;
  uint32_t* var_name_tmp__36;
  uint32_t* var_name_tmp__37;
  struct l_struct_struct_OC_test_unpack_struct* var_name_tmp__38;
  struct l_struct_struct_OC_test_unpack_struct* var_name_tmp__39;
  struct l_struct_struct_OC_test_unpack_struct* var_name_tmp__40;
  uint32_t* var_name_tmp__41;
  uint64_t var_name_load_i32_48;
  uint32_t* var_name_tmp__42;
  uint64_t var_name_load_i32_51;
  uint32_t* var_name_tmp__43;
  uint32_t* var_name_tmp__44;
  struct l_struct_struct_OC_test_pack_struct* var_name_tmp__45;
  struct l_struct_struct_OC_test_pack_struct* var_name_tmp__46;
  struct l_struct_struct_OC_test_pack_struct* var_name_tmp__47;
  uint32_t* var_name_tmp__48;
  uint64_t var_name_load_i32_58;
  uint32_t* var_name_tmp__49;
  uint64_t var_name_load_i32_61;
  uint32_t* var_name_tmp__50;
  uint8_t* var_name_tmp__51;

  var_name_tmp__3 = var_name_tmp__1;
  var_name_tmp__4 = 305419896;
  var_name_tmp__5 = 120u;
  var_name_tmp__6 = 22136u;
  var_name_tmp__11 = var_name_tmp__3;
  var_name_tmp__7 = (((struct l_struct_struct_OC_test_unpack_struct*)var_name_tmp__11));
  var_name_tmp__12 = var_name_tmp__3;
  var_name_tmp__8 = (((struct l_struct_struct_OC_test_pack_struct*)var_name_tmp__12));
  var_name_tmp__13 = var_name_tmp__3;
  var_name_tmp__9 = (((struct l_struct_struct_OC_MemCpyStruct*)var_name_tmp__13));
  var_name_tmp__14 = var_name_tmp__9;
  __adin_store_(((&((&var_name_tmp__14->field1))->field0)), UINT64_C(120), 8, 4);
  var_name_tmp__15 = var_name_tmp__9;
  __adin_store_((((uint8_t*)((&((&var_name_tmp__15->field1))->field1)))), UINT64_C(22136), 16, 2);
  var_name_tmp__16 = var_name_tmp__9;
  __adin_store_((((uint8_t*)((&((&var_name_tmp__16->field1))->field2)))), UINT64_C(305419896), 32, 4);
  var_name_tmp__17 = var_name_tmp__9;
  __adin_memcpy_((((uint8_t*)(&var_name_tmp__10))), (((uint8_t*)((&var_name_tmp__17->field1)))), 8);
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__10.field0)), 8, 4);
  if (((((((int32_t)(int8_t)(((uint8_t)var_name_load_i8_)))) == 120u)&1))) {
    goto var_name_tmp__52;
  } else {
    goto var_name_tmp__53;
  }

var_name_tmp__52:
  goto var_name_tmp__54;

var_name_tmp__53:
  var_name_tmp__2 = ((&_OC_str.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__54:
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__10.field1)))), 16, 2);
  if (((((((int32_t)(int16_t)(((uint16_t)var_name_load_i16_)))) == 22136u)&1))) {
    goto var_name_tmp__56;
  } else {
    goto var_name_tmp__57;
  }

var_name_tmp__56:
  goto var_name_tmp__58;

var_name_tmp__57:
  var_name_tmp__2 = ((&_OC_str_OC_1.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__58:
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__10.field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) == 305419896u)&1))) {
    goto var_name_tmp__59;
  } else {
    goto var_name_tmp__60;
  }

var_name_tmp__59:
  goto var_name_tmp__61;

var_name_tmp__60:
  var_name_tmp__2 = ((&_OC_str_OC_2.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__61:
  var_name_tmp__18 = var_name_tmp__9;
  __adin_memset_((((uint8_t*)var_name_tmp__18)), 0, 12);
  var_name_tmp__19 = var_name_tmp__9;
  var_name_load_i8_3 = __adin_load_(((&((&var_name_tmp__19->field1))->field0)), 8, 4);
  if (((((((int32_t)(int8_t)(((uint8_t)var_name_load_i8_3)))) == 0u)&1))) {
    goto var_name_tmp__62;
  } else {
    goto var_name_tmp__63;
  }

var_name_tmp__62:
  goto var_name_tmp__64;

var_name_tmp__63:
  var_name_tmp__2 = ((&_OC_str_OC_3.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__64:
  var_name_tmp__20 = var_name_tmp__9;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&((&var_name_tmp__20->field1))->field1)))), 16, 2);
  if (((((((int32_t)(int16_t)(((uint16_t)var_name_load_i16_6)))) == 0u)&1))) {
    goto var_name_tmp__65;
  } else {
    goto var_name_tmp__66;
  }

var_name_tmp__65:
  goto var_name_tmp__67;

var_name_tmp__66:
  var_name_tmp__2 = ((&_OC_str_OC_4.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__67:
  var_name_tmp__21 = var_name_tmp__9;
  var_name_load_i32_9 = __adin_load_((((uint8_t*)((&((&var_name_tmp__21->field1))->field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_9)) == 0u)&1))) {
    goto var_name_tmp__68;
  } else {
    goto var_name_tmp__69;
  }

var_name_tmp__68:
  goto var_name_tmp__70;

var_name_tmp__69:
  var_name_tmp__2 = ((&_OC_str_OC_5.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__70:
  var_name_tmp__22 = var_name_tmp__9;
  __adin_memcpy_((((uint8_t*)((&var_name_tmp__22->field1)))), (((uint8_t*)(&var_name_tmp__10))), 8);
  var_name_tmp__23 = var_name_tmp__9;
  var_name_load_i8_11 = __adin_load_(((&((&var_name_tmp__23->field1))->field0)), 8, 4);
  if (((((((int32_t)(int8_t)(((uint8_t)var_name_load_i8_11)))) == 120u)&1))) {
    goto var_name_tmp__71;
  } else {
    goto var_name_tmp__72;
  }

var_name_tmp__71:
  goto var_name_tmp__73;

var_name_tmp__72:
  var_name_tmp__2 = ((&_OC_str_OC_6.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__73:
  var_name_tmp__24 = var_name_tmp__9;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&((&var_name_tmp__24->field1))->field1)))), 16, 2);
  if (((((((int32_t)(int16_t)(((uint16_t)var_name_load_i16_14)))) == 22136u)&1))) {
    goto var_name_tmp__74;
  } else {
    goto var_name_tmp__75;
  }

var_name_tmp__74:
  goto var_name_tmp__76;

var_name_tmp__75:
  var_name_tmp__2 = ((&_OC_str_OC_7.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__76:
  var_name_tmp__25 = var_name_tmp__9;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&((&var_name_tmp__25->field1))->field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_17)) == 305419896u)&1))) {
    goto var_name_tmp__77;
  } else {
    goto var_name_tmp__78;
  }

var_name_tmp__77:
  goto var_name_tmp__79;

var_name_tmp__78:
  var_name_tmp__2 = ((&_OC_str_OC_8.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__79:
  __adin_memset_((((uint8_t*)(&var_name_tmp__10))), 0, 8);
  var_name_load_i8_19 = __adin_load_(((&var_name_tmp__10.field0)), 8, 4);
  if (((((((int32_t)(int8_t)(((uint8_t)var_name_load_i8_19)))) == 0u)&1))) {
    goto var_name_tmp__80;
  } else {
    goto var_name_tmp__81;
  }

var_name_tmp__80:
  goto var_name_tmp__82;

var_name_tmp__81:
  var_name_tmp__2 = ((&_OC_str_OC_9.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__82:
  var_name_load_i16_22 = __adin_load_((((uint8_t*)((&var_name_tmp__10.field1)))), 16, 2);
  if (((((((int32_t)(int16_t)(((uint16_t)var_name_load_i16_22)))) == 0u)&1))) {
    goto var_name_tmp__83;
  } else {
    goto var_name_tmp__84;
  }

var_name_tmp__83:
  goto var_name_tmp__85;

var_name_tmp__84:
  var_name_tmp__2 = ((&_OC_str_OC_10.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__85:
  var_name_load_i32_25 = __adin_load_((((uint8_t*)((&var_name_tmp__10.field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_25)) == 0u)&1))) {
    goto var_name_tmp__86;
  } else {
    goto var_name_tmp__87;
  }

var_name_tmp__86:
  goto var_name_tmp__88;

var_name_tmp__87:
  var_name_tmp__2 = ((&_OC_str_OC_11.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__88:
  var_name_tmp__26 = _ZL15test_global_var;
  if ((((var_name_tmp__26 == UINT64_C(81985529216486895))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__90;
  }

var_name_tmp__89:
  goto var_name_tmp__91;

var_name_tmp__90:
  var_name_tmp__2 = ((&_OC_str_OC_12.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__91:
  var_name_load_i32_27 = __adin_load_(((uint8_t*)(&_ZL16test_struct_load)), 32, 4);
  if (((((((uint32_t)var_name_load_i32_27)) == 305419896u)&1))) {
    goto var_name_tmp__92;
  } else {
    goto var_name_tmp__93;
  }

var_name_tmp__92:
  goto var_name_tmp__94;

var_name_tmp__93:
  var_name_tmp__2 = ((&_OC_str_OC_13.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__94:
  var_name_tmp__27 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__27)), UINT64_C(0), 32, 4);
  var_name_tmp__28 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__28)), UINT64_C(305419896), 32, 4);
  var_name_tmp__29 = var_name_tmp__3;
  var_name_load_i32_32 = __adin_load_((((uint8_t*)var_name_tmp__29)), 32, 4);
  if (((((((uint32_t)var_name_load_i32_32)) == 305419896u)&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__96;
  }

var_name_tmp__95:
  goto var_name_tmp__97;

var_name_tmp__96:
  var_name_tmp__2 = ((&_OC_str_OC_14.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__97:
  var_name_tmp__30 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__30)), UINT64_C(0), 32, 4);
  var_name_tmp__31 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__31)), UINT64_C(120), 8, 1);
  var_name_tmp__32 = var_name_tmp__3;
  var_name_load_i32_36 = __adin_load_((((uint8_t*)var_name_tmp__32)), 32, 4);
  if (((((((uint32_t)var_name_load_i32_36)) == 120u)&1))) {
    goto var_name_tmp__98;
  } else {
    goto var_name_tmp__99;
  }

var_name_tmp__98:
  goto var_name_tmp__100;

var_name_tmp__99:
  var_name_tmp__2 = ((&_OC_str_OC_15.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__100:
  var_name_tmp__33 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__33)), UINT64_C(0), 32, 4);
  var_name_tmp__34 = var_name_tmp__3;
  __adin_store_((((uint8_t*)(((uint16_t*)var_name_tmp__34)))), UINT64_C(22136), 16, 2);
  var_name_tmp__35 = var_name_tmp__3;
  var_name_load_i32_41 = __adin_load_((((uint8_t*)var_name_tmp__35)), 32, 4);
  if (((((((uint32_t)var_name_load_i32_41)) == 22136u)&1))) {
    goto var_name_tmp__101;
  } else {
    goto var_name_tmp__102;
  }

var_name_tmp__101:
  goto var_name_tmp__103;

var_name_tmp__102:
  var_name_tmp__2 = ((&_OC_str_OC_16.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__103:
  var_name_tmp__36 = var_name_tmp__3;
  __adin_store_((((uint8_t*)((&(*var_name_tmp__36))))), UINT64_C(0), 32, 4);
  var_name_tmp__37 = var_name_tmp__3;
  __adin_store_((((uint8_t*)((&var_name_tmp__37[((int64_t)UINT64_C(1))])))), UINT64_C(0), 32, 4);
  var_name_tmp__38 = var_name_tmp__7;
  __adin_store_(((&var_name_tmp__38->field0)), UINT64_C(120), 8, 4);
  var_name_tmp__39 = var_name_tmp__7;
  __adin_store_((((uint8_t*)((&var_name_tmp__39->field1)))), UINT64_C(22136), 16, 2);
  var_name_tmp__40 = var_name_tmp__7;
  __adin_store_((((uint8_t*)((&var_name_tmp__40->field2)))), UINT64_C(305419896), 32, 4);
  var_name_tmp__41 = var_name_tmp__3;
  var_name_load_i32_48 = __adin_load_((((uint8_t*)((&(*var_name_tmp__41))))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_48)) == 1450705016u)&1))) {
    goto var_name_tmp__104;
  } else {
    goto var_name_tmp__105;
  }

var_name_tmp__104:
  goto var_name_tmp__106;

var_name_tmp__105:
  var_name_tmp__2 = ((&_OC_str_OC_17.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__106:
  var_name_tmp__42 = var_name_tmp__3;
  var_name_load_i32_51 = __adin_load_((((uint8_t*)((&var_name_tmp__42[((int64_t)UINT64_C(1))])))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_51)) == 305419896u)&1))) {
    goto var_name_tmp__107;
  } else {
    goto var_name_tmp__108;
  }

var_name_tmp__107:
  goto var_name_tmp__109;

var_name_tmp__108:
  var_name_tmp__2 = ((&_OC_str_OC_18.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__109:
  var_name_tmp__43 = var_name_tmp__3;
  __adin_store_((((uint8_t*)((&(*var_name_tmp__43))))), UINT64_C(0), 32, 4);
  var_name_tmp__44 = var_name_tmp__3;
  __adin_store_((((uint8_t*)((&var_name_tmp__44[((int64_t)UINT64_C(1))])))), UINT64_C(0), 32, 4);
  var_name_tmp__45 = var_name_tmp__8;
  __adin_store_(((&var_name_tmp__45->field0)), UINT64_C(120), 8, 1);
  var_name_tmp__46 = var_name_tmp__8;
  __adin_store_((((uint8_t*)((&var_name_tmp__46->field1)))), UINT64_C(22136), 16, 1);
  var_name_tmp__47 = var_name_tmp__8;
  __adin_store_((((uint8_t*)((&var_name_tmp__47->field2)))), UINT64_C(305419896), 32, 1);
  var_name_tmp__48 = var_name_tmp__3;
  var_name_load_i32_58 = __adin_load_((((uint8_t*)((&(*var_name_tmp__48))))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_58)) == 2018932856u)&1))) {
    goto var_name_tmp__110;
  } else {
    goto var_name_tmp__111;
  }

var_name_tmp__110:
  goto var_name_tmp__112;

var_name_tmp__111:
  var_name_tmp__2 = ((&_OC_str_OC_19.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__112:
  var_name_tmp__49 = var_name_tmp__3;
  var_name_load_i32_61 = __adin_load_((((uint8_t*)((&var_name_tmp__49[((int64_t)UINT64_C(1))])))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_61)) == 1193046u)&1))) {
    goto var_name_tmp__113;
  } else {
    goto var_name_tmp__114;
  }

var_name_tmp__113:
  goto var_name_tmp__115;

var_name_tmp__114:
  var_name_tmp__2 = ((&_OC_str_OC_20.array[((int32_t)0)]));
  goto var_name_tmp__55;

var_name_tmp__115:
  var_name_tmp__50 = var_name_tmp__3;
  __adin_store_((((uint8_t*)var_name_tmp__50)), UINT64_C(0), 32, 4);
  var_name_tmp__2 = ((uint8_t*)/*NULL*/0);
  goto var_name_tmp__55;

var_name_tmp__55:
  var_name_tmp__51 = var_name_tmp__2;
  return var_name_tmp__51;
}

