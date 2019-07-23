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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */


/* Function Bodies */

void WWDG_DeInit(void) {
  RCC_APB1PeriphResetCmd(2048, 1);
  RCC_APB1PeriphResetCmd(2048, 0);
}


void WWDG_SetPrescaler(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1))), 32, 4);
  var_name_tmp__3 = ((((uint32_t)var_name_load_i32_)) & -385);
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__5 | var_name_tmp__4);
  var_name_tmp__6 = var_name_tmp__3;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1))), (((uint64_t)(uint32_t)var_name_tmp__6)), 32, 4);
}


void WWDG_SetWindowValue(uint8_t var_name_tmp__7) {
  uint8_t var_name_tmp__8;    /* Address-exposed local */
  uint32_t var_name_tmp__9;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__10;
  uint64_t var_name_load_i32_3;
  uint64_t var_name_load_i32_8;

  var_name_tmp__8 = var_name_tmp__7;
  __adin_store_((((uint8_t*)(&var_name_tmp__9))), UINT64_C(0), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__9))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -128))), 32, 4);
  var_name_tmp__10 = var_name_tmp__8;
  var_name_load_i32_3 = __adin_load_((((uint8_t*)(&var_name_tmp__9))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__9))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | ((((uint32_t)(uint8_t)var_name_tmp__10)) & 127)))), 32, 4);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)(&var_name_tmp__9))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field1))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_8)))), 32, 4);
}


void WWDG_EnableIT(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1107656868)), UINT64_C(1), 32, 4);
}


void WWDG_SetCounter(uint8_t var_name_tmp__11) {
  uint8_t var_name_tmp__12;    /* Address-exposed local */
  uint8_t var_name_tmp__13;

  var_name_tmp__12 = var_name_tmp__11;
  var_name_tmp__13 = var_name_tmp__12;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073753088)), (((uint64_t)(uint32_t)((((uint32_t)(uint8_t)var_name_tmp__13)) & 127))), 32, 4);
}


void WWDG_Enable(uint8_t var_name_tmp__14) {
  uint8_t var_name_tmp__15;    /* Address-exposed local */
  uint8_t var_name_tmp__16;

  var_name_tmp__15 = var_name_tmp__14;
  var_name_tmp__16 = var_name_tmp__15;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073753088)), (((uint64_t)(uint32_t)(128 | (((uint32_t)(uint8_t)var_name_tmp__16))))), 32, 4);
}


uint32_t WWDG_GetFlagStatus(void) {
  uint32_t var_name_tmp__17;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__18;

  var_name_tmp__17 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field2))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) != 0u)&1))) {
    goto var_name_tmp__19;
  } else {
    goto var_name_tmp__20;
  }

var_name_tmp__19:
  var_name_tmp__17 = 1;
  goto var_name_tmp__21;

var_name_tmp__20:
  var_name_tmp__17 = 0;
  goto var_name_tmp__21;

var_name_tmp__21:
  var_name_tmp__18 = var_name_tmp__17;
  return var_name_tmp__18;
}


void WWDG_ClearFlag(void) {
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_WWDG_TypeDef*)(uintptr_t)UINT64_C(1073753088))->field2))), UINT64_C(0), 32, 4);
}

