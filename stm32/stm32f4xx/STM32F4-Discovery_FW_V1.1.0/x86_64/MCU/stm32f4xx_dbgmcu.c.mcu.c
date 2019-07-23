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


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

uint32_t DBGMCU_GetREVID(void) {
  uint32_t var_name_tmp__1;

  var_name_tmp__1 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field0));
  return (llvm_lshr_u32(var_name_tmp__1, 16));
}


uint32_t DBGMCU_GetDEVID(void) {
  uint32_t var_name_tmp__2;

  var_name_tmp__2 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field0));
  return (var_name_tmp__2 & 4095);
}


void DBGMCU_Config(uint32_t var_name_tmp__3, uint32_t var_name_tmp__4) {
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint32_t var_name_tmp__6;    /* Address-exposed local */
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  uint32_t var_name_tmp__9;
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;

  var_name_tmp__5 = var_name_tmp__3;
  var_name_tmp__6 = var_name_tmp__4;
  var_name_tmp__7 = var_name_tmp__6;
  if ((((var_name_tmp__7 != 0u)&1))) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__12:
  var_name_tmp__8 = var_name_tmp__5;
  var_name_tmp__9 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1)) = (var_name_tmp__9 | var_name_tmp__8);
  goto var_name_tmp__14;

var_name_tmp__13:
  var_name_tmp__10 = var_name_tmp__5;
  var_name_tmp__11 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field1)) = (var_name_tmp__11 & (~(var_name_tmp__10)));
  goto var_name_tmp__14;

var_name_tmp__14:
  return;
}


void DBGMCU_APB1PeriphConfig(uint32_t var_name_tmp__15, uint32_t var_name_tmp__16) {
  uint32_t var_name_tmp__17;    /* Address-exposed local */
  uint32_t var_name_tmp__18;    /* Address-exposed local */
  uint32_t var_name_tmp__19;
  uint32_t var_name_tmp__20;
  uint32_t var_name_tmp__21;
  uint32_t var_name_tmp__22;
  uint32_t var_name_tmp__23;

  var_name_tmp__17 = var_name_tmp__15;
  var_name_tmp__18 = var_name_tmp__16;
  var_name_tmp__19 = var_name_tmp__18;
  if ((((var_name_tmp__19 != 0u)&1))) {
    goto var_name_tmp__24;
  } else {
    goto var_name_tmp__25;
  }

var_name_tmp__24:
  var_name_tmp__20 = var_name_tmp__17;
  var_name_tmp__21 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2)) = (var_name_tmp__21 | var_name_tmp__20);
  goto var_name_tmp__26;

var_name_tmp__25:
  var_name_tmp__22 = var_name_tmp__17;
  var_name_tmp__23 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field2)) = (var_name_tmp__23 & (~(var_name_tmp__22)));
  goto var_name_tmp__26;

var_name_tmp__26:
  return;
}


void DBGMCU_APB2PeriphConfig(uint32_t var_name_tmp__27, uint32_t var_name_tmp__28) {
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  uint32_t var_name_tmp__30;    /* Address-exposed local */
  uint32_t var_name_tmp__31;
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint32_t var_name_tmp__35;

  var_name_tmp__29 = var_name_tmp__27;
  var_name_tmp__30 = var_name_tmp__28;
  var_name_tmp__31 = var_name_tmp__30;
  if ((((var_name_tmp__31 != 0u)&1))) {
    goto var_name_tmp__36;
  } else {
    goto var_name_tmp__37;
  }

var_name_tmp__36:
  var_name_tmp__32 = var_name_tmp__29;
  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3)) = (var_name_tmp__33 | var_name_tmp__32);
  goto var_name_tmp__38;

var_name_tmp__37:
  var_name_tmp__34 = var_name_tmp__29;
  var_name_tmp__35 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DBGMCU_TypeDef*)(uintptr_t)UINT64_C(3758366720))->field3)) = (var_name_tmp__35 & (~(var_name_tmp__34)));
  goto var_name_tmp__38;

var_name_tmp__38:
  return;
}

