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
struct l_struct_struct_OC_RNG_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_RNG_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
};

/* Function Declarations */
void RNG_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphResetCmd(uint32_t, uint32_t);
void RNG_Cmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RNG_GetRandomNumber(void) __ATTRIBUTELIST__((noinline, nothrow));
void RNG_ITConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RNG_GetFlagStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RNG_ClearFlag(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RNG_GetITStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RNG_ClearITPendingBit(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void RNG_DeInit(void) {
  RCC_AHB2PeriphResetCmd(64, 1);
  RCC_AHB2PeriphResetCmd(64, 0);
}


void RNG_Cmd(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 != 0u)&1))) {
    goto var_name_tmp__6;
  } else {
    goto var_name_tmp__7;
  }

var_name_tmp__6:
  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0)) = (var_name_tmp__4 | 4);
  goto var_name_tmp__8;

var_name_tmp__7:
  var_name_tmp__5 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0)) = (var_name_tmp__5 & -5);
  goto var_name_tmp__8;

var_name_tmp__8:
  return;
}


uint32_t RNG_GetRandomNumber(void) {
  uint32_t var_name_tmp__9;

  var_name_tmp__9 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field2));
  return var_name_tmp__9;
}


void RNG_ITConfig(uint32_t var_name_tmp__10) {
  uint32_t var_name_tmp__11;    /* Address-exposed local */
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;

  var_name_tmp__11 = var_name_tmp__10;
  var_name_tmp__12 = var_name_tmp__11;
  if ((((var_name_tmp__12 != 0u)&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  var_name_tmp__13 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0)) = (var_name_tmp__13 | 8);
  goto var_name_tmp__17;

var_name_tmp__16:
  var_name_tmp__14 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field0)) = (var_name_tmp__14 & -9);
  goto var_name_tmp__17;

var_name_tmp__17:
  return;
}


uint32_t RNG_GetFlagStatus(uint8_t var_name_tmp__18) {
  uint8_t var_name_tmp__19;    /* Address-exposed local */
  uint32_t var_name_tmp__20;    /* Address-exposed local */
  uint32_t var_name_tmp__21;
  uint8_t var_name_tmp__22;
  uint32_t var_name_tmp__23;

  var_name_tmp__19 = var_name_tmp__18;
  var_name_tmp__20 = 0;
  var_name_tmp__21 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1));
  var_name_tmp__22 = var_name_tmp__19;
  if (((((var_name_tmp__21 & (((uint32_t)(uint8_t)var_name_tmp__22))) != 0u)&1))) {
    goto var_name_tmp__24;
  } else {
    goto var_name_tmp__25;
  }

var_name_tmp__24:
  var_name_tmp__20 = 1;
  goto var_name_tmp__26;

var_name_tmp__25:
  var_name_tmp__20 = 0;
  goto var_name_tmp__26;

var_name_tmp__26:
  var_name_tmp__23 = var_name_tmp__20;
  return var_name_tmp__23;
}


void RNG_ClearFlag(uint8_t var_name_tmp__27) {
  uint8_t var_name_tmp__28;    /* Address-exposed local */
  uint8_t var_name_tmp__29;

  var_name_tmp__28 = var_name_tmp__27;
  var_name_tmp__29 = var_name_tmp__28;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1)) = (~(((((uint32_t)(uint8_t)var_name_tmp__29)) << 4)));
}


uint32_t RNG_GetITStatus(uint8_t var_name_tmp__30) {
  uint8_t var_name_tmp__31;    /* Address-exposed local */
  uint32_t var_name_tmp__32;    /* Address-exposed local */
  uint32_t var_name_tmp__33;
  uint8_t var_name_tmp__34;
  uint32_t var_name_tmp__35;

  var_name_tmp__31 = var_name_tmp__30;
  var_name_tmp__32 = 0;
  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1));
  var_name_tmp__34 = var_name_tmp__31;
  if (((((var_name_tmp__33 & (((uint32_t)(uint8_t)var_name_tmp__34))) != 0u)&1))) {
    goto var_name_tmp__36;
  } else {
    goto var_name_tmp__37;
  }

var_name_tmp__36:
  var_name_tmp__32 = 1;
  goto var_name_tmp__38;

var_name_tmp__37:
  var_name_tmp__32 = 0;
  goto var_name_tmp__38;

var_name_tmp__38:
  var_name_tmp__35 = var_name_tmp__32;
  return var_name_tmp__35;
}


void RNG_ClearITPendingBit(uint8_t var_name_tmp__39) {
  uint8_t var_name_tmp__40;    /* Address-exposed local */
  uint8_t var_name_tmp__41;

  var_name_tmp__40 = var_name_tmp__39;
  var_name_tmp__41 = var_name_tmp__40;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1)) = (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__41))))))));
}

