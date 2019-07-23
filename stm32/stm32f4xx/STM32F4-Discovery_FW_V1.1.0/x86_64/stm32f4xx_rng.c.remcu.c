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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void RNG_DeInit(void) {
  RCC_AHB2PeriphResetCmd(64, 1);
  RCC_AHB2PeriphResetCmd(64, 0);
}


void RNG_Cmd(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 != 0u)&1))) {
    goto var_name_tmp__4;
  } else {
    goto var_name_tmp__5;
  }

var_name_tmp__4:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 4))), 32, 4);
  goto var_name_tmp__6;

var_name_tmp__5:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -5))), 32, 4);
  goto var_name_tmp__6;

var_name_tmp__6:
  return;
}


uint32_t RNG_GetRandomNumber(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field2))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void RNG_ITConfig(uint32_t var_name_tmp__7) {
  uint32_t var_name_tmp__8;    /* Address-exposed local */
  uint32_t var_name_tmp__9;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__8 = var_name_tmp__7;
  var_name_tmp__9 = var_name_tmp__8;
  if ((((var_name_tmp__9 != 0u)&1))) {
    goto var_name_tmp__10;
  } else {
    goto var_name_tmp__11;
  }

var_name_tmp__10:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 8))), 32, 4);
  goto var_name_tmp__12;

var_name_tmp__11:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342572544)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -9))), 32, 4);
  goto var_name_tmp__12;

var_name_tmp__12:
  return;
}


uint32_t RNG_GetFlagStatus(uint8_t var_name_tmp__13) {
  uint8_t var_name_tmp__14;    /* Address-exposed local */
  uint32_t var_name_tmp__15;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__16;
  uint32_t var_name_tmp__17;

  var_name_tmp__14 = var_name_tmp__13;
  var_name_tmp__15 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1))), 32, 4);
  var_name_tmp__16 = var_name_tmp__14;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint8_t)var_name_tmp__16))) != 0u)&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  var_name_tmp__15 = 1;
  goto var_name_tmp__20;

var_name_tmp__19:
  var_name_tmp__15 = 0;
  goto var_name_tmp__20;

var_name_tmp__20:
  var_name_tmp__17 = var_name_tmp__15;
  return var_name_tmp__17;
}


void RNG_ClearFlag(uint8_t var_name_tmp__21) {
  uint8_t var_name_tmp__22;    /* Address-exposed local */
  uint8_t var_name_tmp__23;

  var_name_tmp__22 = var_name_tmp__21;
  var_name_tmp__23 = var_name_tmp__22;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1))), (((uint64_t)(uint32_t)(~(((((uint32_t)(uint8_t)var_name_tmp__23)) << 4))))), 32, 4);
}


uint32_t RNG_GetITStatus(uint8_t var_name_tmp__24) {
  uint8_t var_name_tmp__25;    /* Address-exposed local */
  uint32_t var_name_tmp__26;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__27;
  uint32_t var_name_tmp__28;

  var_name_tmp__25 = var_name_tmp__24;
  var_name_tmp__26 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1))), 32, 4);
  var_name_tmp__27 = var_name_tmp__25;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint8_t)var_name_tmp__27))) != 0u)&1))) {
    goto var_name_tmp__29;
  } else {
    goto var_name_tmp__30;
  }

var_name_tmp__29:
  var_name_tmp__26 = 1;
  goto var_name_tmp__31;

var_name_tmp__30:
  var_name_tmp__26 = 0;
  goto var_name_tmp__31;

var_name_tmp__31:
  var_name_tmp__28 = var_name_tmp__26;
  return var_name_tmp__28;
}


void RNG_ClearITPendingBit(uint8_t var_name_tmp__32) {
  uint8_t var_name_tmp__33;    /* Address-exposed local */
  uint8_t var_name_tmp__34;

  var_name_tmp__33 = var_name_tmp__32;
  var_name_tmp__34 = var_name_tmp__33;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RNG_TypeDef*)(uintptr_t)UINT64_C(1342572544))->field1))), (((uint64_t)(uint32_t)(((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__34)))))))))), 32, 4);
}

