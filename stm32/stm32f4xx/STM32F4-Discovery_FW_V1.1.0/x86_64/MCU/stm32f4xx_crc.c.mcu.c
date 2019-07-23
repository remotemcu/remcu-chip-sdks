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
struct l_struct_struct_OC_CRC_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_CRC_TypeDef {
  uint32_t field0;
  uint8_t field1;
  uint8_t field2;
  uint16_t field3;
  uint32_t field4;
};

/* Function Declarations */
void CRC_ResetDR(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRC_CalcCRC(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRC_CalcBlockCRC(uint32_t*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRC_GetCRC(void) __ATTRIBUTELIST__((noinline, nothrow));
void CRC_SetIDRegister(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CRC_GetIDRegister(void) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}


/* Function Bodies */

void CRC_ResetDR(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field4)) = 1;
}


uint32_t CRC_CalcCRC(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  uint32_t var_name_tmp__4;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field0)) = var_name_tmp__3;
  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field0));
  return var_name_tmp__4;
}


uint32_t CRC_CalcBlockCRC(uint32_t* var_name_tmp__5, uint32_t var_name_tmp__6) {
  uint32_t* var_name_tmp__7;    /* Address-exposed local */
  uint32_t var_name_tmp__8;    /* Address-exposed local */
  uint32_t var_name_tmp__9;    /* Address-exposed local */
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;
  uint32_t* var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;

  var_name_tmp__7 = var_name_tmp__5;
  var_name_tmp__8 = var_name_tmp__6;
  var_name_tmp__9 = 0;
  var_name_tmp__9 = 0;
  goto var_name_tmp__17;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__17:
  var_name_tmp__10 = var_name_tmp__9;
  var_name_tmp__11 = var_name_tmp__8;
  if ((((((uint32_t)var_name_tmp__10) < ((uint32_t)var_name_tmp__11))&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  var_name_tmp__12 = var_name_tmp__7;
  var_name_tmp__13 = var_name_tmp__9;
  var_name_tmp__14 = *((&var_name_tmp__12[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__13)))]));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field0)) = var_name_tmp__14;
  goto var_name_tmp__20;

var_name_tmp__20:
  var_name_tmp__15 = var_name_tmp__9;
  var_name_tmp__9 = (llvm_add_u32(var_name_tmp__15, 1));
  goto var_name_tmp__17;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__19:
  var_name_tmp__16 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field0));
  return var_name_tmp__16;
}


uint32_t CRC_GetCRC(void) {
  uint32_t var_name_tmp__21;

  var_name_tmp__21 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field0));
  return var_name_tmp__21;
}


void CRC_SetIDRegister(uint8_t var_name_tmp__22) {
  uint8_t var_name_tmp__23;    /* Address-exposed local */
  uint8_t var_name_tmp__24;

  var_name_tmp__23 = var_name_tmp__22;
  var_name_tmp__24 = var_name_tmp__23;
  *(volatile uint8_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field1)) = var_name_tmp__24;
}


uint8_t CRC_GetIDRegister(void) {
  uint8_t var_name_tmp__25;

  var_name_tmp__25 = *(volatile uint8_t*)((&((struct l_struct_struct_OC_CRC_TypeDef*)(uintptr_t)UINT64_C(1073885184))->field1));
  return var_name_tmp__25;
}

