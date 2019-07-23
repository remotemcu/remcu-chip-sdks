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



/* Global Declarations */

/* Types Declarations */
struct l_struct_struct_OC_DBGMCU_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_DBGMCU_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};

/* Function Declarations */
uint32_t DBGMCU_GetREVID(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DBGMCU_GetDEVID(void) __ATTRIBUTELIST__((noinline, nothrow));
void DBGMCU_Config(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DBGMCU_APB1PeriphConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DBGMCU_APB2PeriphConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

uint32_t DBGMCU_GetREVID(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(3758366720)), 32, 4);
  return (llvm_lshr_u32((((uint32_t)var_name_load_i32_)), 16));
}


uint32_t DBGMCU_GetDEVID(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(3758366720)), 32, 4);
  return ((((uint32_t)var_name_load_i32_)) & 4095);
}


void DBGMCU_Config(uint32_t var_name_tmp__1, uint32_t var_name_tmp__2) {
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint32_t var_name_tmp__4;    /* Address-exposed local */
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__7;
  uint64_t var_name_load_i32_1;

  var_name_tmp__3 = var_name_tmp__1;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = var_name_tmp__4;
  if ((((var_name_tmp__5 != 0u)&1))) {
    goto var_name_tmp__8;
  } else {
    goto var_name_tmp__9;
  }

var_name_tmp__8:
  var_name_tmp__6 = var_name_tmp__3;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__6))), 32, 4);
  goto var_name_tmp__10;

var_name_tmp__9:
  var_name_tmp__7 = var_name_tmp__3;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__7))))), 32, 4);
  goto var_name_tmp__10;

var_name_tmp__10:
  return;
}


void DBGMCU_APB1PeriphConfig(uint32_t var_name_tmp__11, uint32_t var_name_tmp__12) {
  uint32_t var_name_tmp__13;    /* Address-exposed local */
  uint32_t var_name_tmp__14;    /* Address-exposed local */
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__17;
  uint64_t var_name_load_i32_1;

  var_name_tmp__13 = var_name_tmp__11;
  var_name_tmp__14 = var_name_tmp__12;
  var_name_tmp__15 = var_name_tmp__14;
  if ((((var_name_tmp__15 != 0u)&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  var_name_tmp__16 = var_name_tmp__13;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__16))), 32, 4);
  goto var_name_tmp__20;

var_name_tmp__19:
  var_name_tmp__17 = var_name_tmp__13;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__17))))), 32, 4);
  goto var_name_tmp__20;

var_name_tmp__20:
  return;
}


void DBGMCU_APB2PeriphConfig(uint32_t var_name_tmp__21, uint32_t var_name_tmp__22) {
  uint32_t var_name_tmp__23;    /* Address-exposed local */
  uint32_t var_name_tmp__24;    /* Address-exposed local */
  uint32_t var_name_tmp__25;
  uint32_t var_name_tmp__26;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__27;
  uint64_t var_name_load_i32_1;

  var_name_tmp__23 = var_name_tmp__21;
  var_name_tmp__24 = var_name_tmp__22;
  var_name_tmp__25 = var_name_tmp__24;
  if ((((var_name_tmp__25 != 0u)&1))) {
    goto var_name_tmp__28;
  } else {
    goto var_name_tmp__29;
  }

var_name_tmp__28:
  var_name_tmp__26 = var_name_tmp__23;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__26))), 32, 4);
  goto var_name_tmp__30;

var_name_tmp__29:
  var_name_tmp__27 = var_name_tmp__23;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__27))))), 32, 4);
  goto var_name_tmp__30;

var_name_tmp__30:
  return;
}

