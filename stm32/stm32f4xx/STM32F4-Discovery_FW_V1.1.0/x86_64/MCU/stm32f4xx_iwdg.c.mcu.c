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


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void IWDG_WriteAccessCmd(uint16_t var_name_tmp__1) {
  uint16_t var_name_tmp__2;    /* Address-exposed local */
  uint16_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field0)) = (((uint32_t)(uint16_t)var_name_tmp__3));
}


void IWDG_SetPrescaler(uint8_t var_name_tmp__4) {
  uint8_t var_name_tmp__5;    /* Address-exposed local */
  uint8_t var_name_tmp__6;

  var_name_tmp__5 = var_name_tmp__4;
  var_name_tmp__6 = var_name_tmp__5;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field1)) = (((uint32_t)(uint8_t)var_name_tmp__6));
}


void IWDG_SetReload(uint16_t var_name_tmp__7) {
  uint16_t var_name_tmp__8;    /* Address-exposed local */
  uint16_t var_name_tmp__9;

  var_name_tmp__8 = var_name_tmp__7;
  var_name_tmp__9 = var_name_tmp__8;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field2)) = (((uint32_t)(uint16_t)var_name_tmp__9));
}


void IWDG_ReloadCounter(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field0)) = 43690;
}


void IWDG_Enable(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field0)) = 52428;
}


uint32_t IWDG_GetFlagStatus(uint16_t var_name_tmp__10) {
  uint16_t var_name_tmp__11;    /* Address-exposed local */
  uint32_t var_name_tmp__12;    /* Address-exposed local */
  uint32_t var_name_tmp__13;
  uint16_t var_name_tmp__14;
  uint32_t var_name_tmp__15;

  var_name_tmp__11 = var_name_tmp__10;
  var_name_tmp__12 = 0;
  var_name_tmp__13 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_IWDG_TypeDef*)(uintptr_t)UINT64_C(1073754112))->field3));
  var_name_tmp__14 = var_name_tmp__11;
  if (((((var_name_tmp__13 & (((uint32_t)(uint16_t)var_name_tmp__14))) != 0u)&1))) {
    goto var_name_tmp__16;
  } else {
    goto var_name_tmp__17;
  }

var_name_tmp__16:
  var_name_tmp__12 = 1;
  goto var_name_tmp__18;

var_name_tmp__17:
  var_name_tmp__12 = 0;
  goto var_name_tmp__18;

var_name_tmp__18:
  var_name_tmp__15 = var_name_tmp__12;
  return var_name_tmp__15;
}

