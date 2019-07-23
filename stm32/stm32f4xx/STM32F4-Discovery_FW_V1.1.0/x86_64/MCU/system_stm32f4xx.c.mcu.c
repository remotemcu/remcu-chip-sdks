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
struct l_struct_struct_OC_PWR_TypeDef;
struct l_struct_struct_OC_FLASH_TypeDef;

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
struct l_struct_struct_OC_PWR_TypeDef {
  uint32_t field0;
  uint32_t field1;
};
struct l_struct_struct_OC_FLASH_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};
struct l_array_16_uint8_t {
  uint8_t array[16];
};

/* External Global Variable Declarations */

/* Function Declarations */
void SystemInit(void) __ATTRIBUTELIST__((noinline, nothrow));
static void SetSysClock(void) __ATTRIBUTELIST__((noinline, nothrow));
void SystemCoreClockUpdate(void) __ATTRIBUTELIST__((noinline, nothrow));


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
  uint32_t var_name_tmp__1;
  uint32_t var_name_tmp__2;
  uint32_t var_name_tmp__3;

  var_name_tmp__1 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0)) = (var_name_tmp__1 | 1);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = 0;
  var_name_tmp__2 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0)) = (var_name_tmp__2 & -17367041);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1)) = 603992080;
  var_name_tmp__3 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0)) = (var_name_tmp__3 & -262145);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field3)) = 0;
  SetSysClock();
}


static void SetSysClock(void) {
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  uint32_t var_name_tmp__9;
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;

  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15)) = (var_name_tmp__4 | 268435456);
  var_name_tmp__5 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_PWR_TypeDef*)(uintptr_t)UINT64_C(1073770496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_PWR_TypeDef*)(uintptr_t)UINT64_C(1073770496))->field0)) = (var_name_tmp__5 & -16385);
  var_name_tmp__6 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__6;
  var_name_tmp__7 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__7;
  var_name_tmp__8 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__8;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1)) = 84098064;
  var_name_tmp__9 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0)) = (var_name_tmp__9 | 16777216);
  goto var_name_tmp__14;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__14:
  var_name_tmp__10 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  if (((((var_name_tmp__10 & 33554432) == 0u)&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  goto var_name_tmp__14;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__16:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = 1536;
  var_name_tmp__11 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = (var_name_tmp__11 & -4);
  var_name_tmp__12 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = (var_name_tmp__12 | 2);
  goto var_name_tmp__17;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__17:
  var_name_tmp__13 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  if (((((var_name_tmp__13 & 12) != 8u)&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  goto var_name_tmp__17;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__19:
  return;
}


void SystemCoreClockUpdate(void) {
  uint32_t var_name_tmp__20;    /* Address-exposed local */
  uint32_t var_name_tmp__21;    /* Address-exposed local */
  uint32_t var_name_tmp__22;    /* Address-exposed local */
  uint32_t var_name_tmp__23;    /* Address-exposed local */
  uint32_t var_name_tmp__24;    /* Address-exposed local */
  uint32_t var_name_tmp__25;
  uint32_t var_name_tmp__26;
  uint32_t var_name_tmp__27;
  uint32_t var_name_tmp__28;
  uint32_t var_name_tmp__29;
  uint32_t var_name_tmp__30;
  uint32_t var_name_tmp__31;
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint32_t var_name_tmp__35;
  uint32_t var_name_tmp__36;
  uint32_t var_name_tmp__37;
  uint8_t var_name_tmp__38;
  uint32_t var_name_tmp__39;
  uint32_t var_name_tmp__40;

  var_name_tmp__20 = 0;
  var_name_tmp__21 = 0;
  var_name_tmp__22 = 2;
  var_name_tmp__23 = 0;
  var_name_tmp__24 = 2;
  var_name_tmp__25 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__20 = (var_name_tmp__25 & 12);
  var_name_tmp__26 = var_name_tmp__20;
  switch (var_name_tmp__26) {
  default:
    goto var_name_tmp__41;
  case 0u:
    goto var_name_tmp__42;
  case 4u:
    goto var_name_tmp__43;
  case 8u:
    goto var_name_tmp__44;
  }

var_name_tmp__42:
  SystemCoreClock = 16000000;
  goto var_name_tmp__45;

var_name_tmp__43:
  SystemCoreClock = 8000000;
  goto var_name_tmp__45;

var_name_tmp__44:
  var_name_tmp__27 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__23 = (llvm_lshr_u32((var_name_tmp__27 & 4194304), 22));
  var_name_tmp__28 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__24 = (var_name_tmp__28 & 63);
  var_name_tmp__29 = var_name_tmp__23;
  if ((((var_name_tmp__29 != 0u)&1))) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__47;
  }

var_name_tmp__46:
  var_name_tmp__30 = var_name_tmp__24;
  var_name_tmp__31 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__21 = (llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__30)), (llvm_lshr_u32((var_name_tmp__31 & 32704), 6))));
  goto var_name_tmp__48;

var_name_tmp__47:
  var_name_tmp__32 = var_name_tmp__24;
  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__21 = (llvm_mul_u32((llvm_udiv_u32(16000000, var_name_tmp__32)), (llvm_lshr_u32((var_name_tmp__33 & 32704), 6))));
  goto var_name_tmp__48;

var_name_tmp__48:
  var_name_tmp__34 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__22 = (llvm_mul_u32((llvm_add_u32((llvm_lshr_u32((var_name_tmp__34 & 196608), 16)), 1)), 2));
  var_name_tmp__35 = var_name_tmp__21;
  var_name_tmp__36 = var_name_tmp__22;
  SystemCoreClock = (llvm_udiv_u32(var_name_tmp__35, var_name_tmp__36));
  goto var_name_tmp__45;

var_name_tmp__41:
  SystemCoreClock = 16000000;
  goto var_name_tmp__45;

var_name_tmp__45:
  var_name_tmp__37 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__38 = *(volatile uint8_t*)((&AHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)(llvm_lshr_u32((var_name_tmp__37 & 240), 4)))))]));
  var_name_tmp__20 = (((uint32_t)(uint8_t)var_name_tmp__38));
  var_name_tmp__39 = var_name_tmp__20;
  var_name_tmp__40 = SystemCoreClock;
  SystemCoreClock = (llvm_lshr_u32(var_name_tmp__40, var_name_tmp__39));
}

