/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#ifndef __cplusplus
typedef unsigned char bool;
#endif

#ifndef _MSC_VER
#define __forceinline __attribute__((always_inline)) inline
#endif

#if defined(__GNUC__)
#define  __ATTRIBUTELIST__(x) __attribute__(x)
#else
#define  __ATTRIBUTELIST__(x)  
#endif

#ifdef _MSC_VER  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#ifdef _MSC_VER
#define __MSALIGN__(X) __declspec(align(X))
#else
#define __MSALIGN__(X)
#endif



/* Global Declarations */

/* Types Declarations */
struct l_struct_struct_OC_RCC_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_array_2_uint32_t {
  uint32_t array[2];
};
struct l_struct_struct_OC_RCC_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint32_t field6;
  uint32_t field7;
  uint32_t field8;
  uint32_t field9;
  struct l_array_2_uint32_t field10;
  uint32_t field11;
  uint32_t field12;
  uint32_t field13;
  uint32_t field14;
  uint32_t field15;
  uint32_t field16;
  struct l_array_2_uint32_t field17;
  uint32_t field18;
  uint32_t field19;
  uint32_t field20;
  uint32_t field21;
  uint32_t field22;
  uint32_t field23;
  struct l_array_2_uint32_t field24;
  uint32_t field25;
  uint32_t field26;
  struct l_array_2_uint32_t field27;
  uint32_t field28;
  uint32_t field29;
};
struct l_array_16_uint8_t {
  uint8_t array[16];
};

/* External Global Variable Declarations */

/* Function Declarations */
void SystemInit(void) __ATTRIBUTELIST__((noinline, nothrow));
static void SetSysClock(void) __ATTRIBUTELIST__((noinline, nothrow));
void SystemCoreClockUpdate(void) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* Global Variable Definitions and Initialization */
uint32_t SystemCoreClock = 30000000;
__MSALIGN__(16) struct l_array_16_uint8_t AHBPrescTable __attribute__((aligned(16))) = { { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9 } };


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_mul_u32(uint32_t a, uint32_t b) {
  uint32_t r = a * b;
  return r;
}
static __forceinline uint32_t llvm_udiv_u32(uint32_t a, uint32_t b) {
  uint32_t r = a / b;
  return r;
}
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void SystemInit(void) {
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), UINT64_C(0), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -17367041))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), UINT64_C(603992080), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & -262145))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field3))), UINT64_C(0), 32, 4);
  SetSysClock();
}


static void SetSysClock(void) {
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_10;
  uint64_t var_name_load_i32_13;
  uint64_t var_name_load_i32_16;
  uint64_t var_name_load_i32_18;
  uint64_t var_name_load_i32_21;
  uint64_t var_name_load_i32_24;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 268435456))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073770496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073770496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -16385))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_4)))), 32, 4);
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_7)))), 32, 4);
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_10)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), UINT64_C(84098064), 32, 4);
  var_name_load_i32_13 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) | 16777216))), 32, 4);
  goto var_name_tmp__1;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__1:
  var_name_load_i32_16 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_16)) & 33554432) == 0u)&1))) {
    goto var_name_tmp__2;
  } else {
    goto var_name_tmp__3;
  }

var_name_tmp__2:
  goto var_name_tmp__1;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__3:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), UINT64_C(1536), 32, 4);
  var_name_load_i32_18 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_18)) & -4))), 32, 4);
  var_name_load_i32_21 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_21)) | 2))), 32, 4);
  goto var_name_tmp__4;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__4:
  var_name_load_i32_24 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_24)) & 12) != 8u)&1))) {
    goto var_name_tmp__5;
  } else {
    goto var_name_tmp__6;
  }

var_name_tmp__5:
  goto var_name_tmp__4;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__6:
  return;
}


void SystemCoreClockUpdate(void) {
  uint32_t var_name_tmp__7;    /* Address-exposed local */
  uint32_t var_name_tmp__8;    /* Address-exposed local */
  uint32_t var_name_tmp__9;    /* Address-exposed local */
  uint32_t var_name_tmp__10;    /* Address-exposed local */
  uint32_t var_name_tmp__11;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__12;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__15;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_9;
  uint32_t var_name_tmp__16;
  uint32_t var_name_tmp__17;
  uint64_t var_name_load_i32_11;
  uint64_t var_name_load_i8_;
  uint32_t var_name_tmp__18;
  uint32_t var_name_tmp__19;

  var_name_tmp__7 = 0;
  var_name_tmp__8 = 0;
  var_name_tmp__9 = 2;
  var_name_tmp__10 = 0;
  var_name_tmp__11 = 2;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__7 = ((((uint32_t)var_name_load_i32_)) & 12);
  var_name_tmp__12 = var_name_tmp__7;
  switch (var_name_tmp__12) {
  default:
    goto var_name_tmp__20;
  case 0u:
    goto var_name_tmp__21;
  case 4u:
    goto var_name_tmp__22;
  case 8u:
    goto var_name_tmp__23;
  }

var_name_tmp__21:
  SystemCoreClock = 16000000;
  goto var_name_tmp__24;

var_name_tmp__22:
  SystemCoreClock = 8000000;
  goto var_name_tmp__24;

var_name_tmp__23:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__10 = (llvm_lshr_u32(((((uint32_t)var_name_load_i32_1)) & 4194304), 22));
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__11 = ((((uint32_t)var_name_load_i32_3)) & 63);
  var_name_tmp__13 = var_name_tmp__10;
  if ((((var_name_tmp__13 != 0u)&1))) {
    goto var_name_tmp__25;
  } else {
    goto var_name_tmp__26;
  }

var_name_tmp__25:
  var_name_tmp__14 = var_name_tmp__11;
  var_name_load_i32_5 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__8 = (llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__14)), (llvm_lshr_u32(((((uint32_t)var_name_load_i32_5)) & 32704), 6))));
  goto var_name_tmp__27;

var_name_tmp__26:
  var_name_tmp__15 = var_name_tmp__11;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__8 = (llvm_mul_u32((llvm_udiv_u32(16000000, var_name_tmp__15)), (llvm_lshr_u32(((((uint32_t)var_name_load_i32_7)) & 32704), 6))));
  goto var_name_tmp__27;

var_name_tmp__27:
  var_name_load_i32_9 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__9 = (llvm_mul_u32((llvm_add_u32((llvm_lshr_u32(((((uint32_t)var_name_load_i32_9)) & 196608), 16)), 1)), 2));
  var_name_tmp__16 = var_name_tmp__8;
  var_name_tmp__17 = var_name_tmp__9;
  SystemCoreClock = (llvm_udiv_u32(var_name_tmp__16, var_name_tmp__17));
  goto var_name_tmp__24;

var_name_tmp__20:
  SystemCoreClock = 16000000;
  goto var_name_tmp__24;

var_name_tmp__24:
  var_name_load_i32_11 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_load_i8_ = __adin_load_(((&AHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)(llvm_lshr_u32(((((uint32_t)var_name_load_i32_11)) & 240), 4)))))])), 8, 1);
  var_name_tmp__7 = (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_))));
  var_name_tmp__18 = var_name_tmp__7;
  var_name_tmp__19 = SystemCoreClock;
  SystemCoreClock = (llvm_lshr_u32(var_name_tmp__19, var_name_tmp__18));
}

