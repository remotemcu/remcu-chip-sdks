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
struct l_struct_struct_OC_WWDG_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_WWDG_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
};

/* Function Declarations */
void WWDG_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void WWDG_SetPrescaler(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void WWDG_SetWindowValue(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void WWDG_EnableIT(void) __ATTRIBUTELIST__((noinline, nothrow));
void WWDG_SetCounter(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void WWDG_Enable(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t WWDG_GetFlagStatus(void) __ATTRIBUTELIST__((noinline, nothrow));
void WWDG_ClearFlag(void) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void WWDG_DeInit(void) {
  RCC_APB1PeriphResetCmd(2048, 1);
  RCC_APB1PeriphResetCmd(2048, 0);
}


void WWDG_SetPrescaler(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1));
  var_name_tmp__3 = (var_name_tmp__4 & -385);
  var_name_tmp__5 = var_name_tmp__2;
  var_name_tmp__6 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__6 | var_name_tmp__5);
  var_name_tmp__7 = var_name_tmp__3;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1)) = var_name_tmp__7;
}


void WWDG_SetWindowValue(uint8_t var_name_tmp__8) {
  uint8_t var_name_tmp__9;    /* Address-exposed local */
  uint32_t var_name_tmp__10;    /* Address-exposed local */
  uint32_t var_name_tmp__11;
  uint8_t var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;

  var_name_tmp__9 = var_name_tmp__8;
  *(volatile uint32_t*)(&var_name_tmp__10) = 0;
  var_name_tmp__11 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1));
  *(volatile uint32_t*)(&var_name_tmp__10) = (var_name_tmp__11 & -128);
  var_name_tmp__12 = var_name_tmp__9;
  var_name_tmp__13 = *(volatile uint32_t*)(&var_name_tmp__10);
  *(volatile uint32_t*)(&var_name_tmp__10) = (var_name_tmp__13 | ((((uint32_t)(uint8_t)var_name_tmp__12)) & 127));
  var_name_tmp__14 = *(volatile uint32_t*)(&var_name_tmp__10);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1)) = var_name_tmp__14;
}


void WWDG_EnableIT(void) {
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1107656868)) = 1;
}


void WWDG_SetCounter(uint8_t var_name_tmp__15) {
  uint8_t var_name_tmp__16;    /* Address-exposed local */
  uint8_t var_name_tmp__17;

  var_name_tmp__16 = var_name_tmp__15;
  var_name_tmp__17 = var_name_tmp__16;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field0)) = ((((uint32_t)(uint8_t)var_name_tmp__17)) & 127);
}


void WWDG_Enable(uint8_t var_name_tmp__18) {
  uint8_t var_name_tmp__19;    /* Address-exposed local */
  uint8_t var_name_tmp__20;

  var_name_tmp__19 = var_name_tmp__18;
  var_name_tmp__20 = var_name_tmp__19;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field0)) = (128 | (((uint32_t)(uint8_t)var_name_tmp__20)));
}


uint32_t WWDG_GetFlagStatus(void) {
  uint32_t var_name_tmp__21;    /* Address-exposed local */
  uint32_t var_name_tmp__22;
  uint32_t var_name_tmp__23;

  var_name_tmp__21 = 0;
  var_name_tmp__22 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field2));
  if ((((var_name_tmp__22 != 0u)&1))) {
    goto var_name_tmp__24;
  } else {
    goto var_name_tmp__25;
  }

var_name_tmp__24:
  var_name_tmp__21 = 1;
  goto var_name_tmp__26;

var_name_tmp__25:
  var_name_tmp__21 = 0;
  goto var_name_tmp__26;

var_name_tmp__26:
  var_name_tmp__23 = var_name_tmp__21;
  return var_name_tmp__23;
}


void WWDG_ClearFlag(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field2)) = 0;
}

