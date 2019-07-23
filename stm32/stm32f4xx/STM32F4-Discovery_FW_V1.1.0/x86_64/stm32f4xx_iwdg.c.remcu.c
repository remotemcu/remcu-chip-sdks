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
struct l_struct_struct_OC_IWDG_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_IWDG_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};

/* Function Declarations */
void IWDG_WriteAccessCmd(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void IWDG_SetPrescaler(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void IWDG_SetReload(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void IWDG_ReloadCounter(void) __ATTRIBUTELIST__((noinline, nothrow));
void IWDG_Enable(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t IWDG_GetFlagStatus(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void IWDG_WriteAccessCmd(uint16_t var_name_tmp__1) {
  uint16_t var_name_tmp__2;    /* Address-exposed local */
  uint16_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073754112)), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__3)))), 32, 4);
}


void IWDG_SetPrescaler(uint8_t var_name_tmp__4) {
  uint8_t var_name_tmp__5;    /* Address-exposed local */
  uint8_t var_name_tmp__6;

  var_name_tmp__5 = var_name_tmp__4;
  var_name_tmp__6 = var_name_tmp__5;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field1))), (((uint64_t)(uint32_t)(((uint32_t)(uint8_t)var_name_tmp__6)))), 32, 4);
}


void IWDG_SetReload(uint16_t var_name_tmp__7) {
  uint16_t var_name_tmp__8;    /* Address-exposed local */
  uint16_t var_name_tmp__9;

  var_name_tmp__8 = var_name_tmp__7;
  var_name_tmp__9 = var_name_tmp__8;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field2))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__9)))), 32, 4);
}


void IWDG_ReloadCounter(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073754112)), UINT64_C(43690), 32, 4);
}


void IWDG_Enable(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073754112)), UINT64_C(52428), 32, 4);
}


uint32_t IWDG_GetFlagStatus(uint16_t var_name_tmp__10) {
  uint16_t var_name_tmp__11;    /* Address-exposed local */
  uint32_t var_name_tmp__12;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__13;
  uint32_t var_name_tmp__14;

  var_name_tmp__11 = var_name_tmp__10;
  var_name_tmp__12 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field3))), 32, 4);
  var_name_tmp__13 = var_name_tmp__11;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint16_t)var_name_tmp__13))) != 0u)&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  var_name_tmp__12 = 1;
  goto var_name_tmp__17;

var_name_tmp__16:
  var_name_tmp__12 = 0;
  goto var_name_tmp__17;

var_name_tmp__17:
  var_name_tmp__14 = var_name_tmp__12;
  return var_name_tmp__14;
}

