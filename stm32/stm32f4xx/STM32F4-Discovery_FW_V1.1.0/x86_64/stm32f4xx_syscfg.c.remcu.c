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
struct l_struct_struct_OC_SYSCFG_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_array_4_uint32_t {
  uint32_t array[4];
};
struct l_array_2_uint32_t {
  uint32_t array[2];
};
struct l_struct_struct_OC_SYSCFG_TypeDef {
  uint32_t field0;
  uint32_t field1;
  struct l_array_4_uint32_t field2;
  struct l_array_2_uint32_t field3;
  uint32_t field4;
};

/* Function Declarations */
void SYSCFG_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void SYSCFG_MemoryRemapConfig(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void SYSCFG_EXTILineConfig(uint8_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void SYSCFG_ETH_MediaInterfaceConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SYSCFG_CompensationCellCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SYSCFG_GetCompensationCellStatus(void) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_mul_u32(uint32_t a, uint32_t b) {
  uint32_t r = a * b;
  return r;
}
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void SYSCFG_DeInit(void) {
  RCC_APB2PeriphResetCmd(16384, 1);
  RCC_APB2PeriphResetCmd(16384, 0);
}


void SYSCFG_MemoryRemapConfig(uint8_t var_name_tmp__1) {
  uint8_t var_name_tmp__2;    /* Address-exposed local */
  uint8_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073821696)), (((uint64_t)(uint32_t)(((uint32_t)(uint8_t)var_name_tmp__3)))), 32, 4);
}


void SYSCFG_EXTILineConfig(uint8_t var_name_tmp__4, uint8_t var_name_tmp__5) {
  uint8_t var_name_tmp__6;    /* Address-exposed local */
  uint8_t var_name_tmp__7;    /* Address-exposed local */
  uint32_t var_name_tmp__8;    /* Address-exposed local */
  uint8_t var_name_tmp__9;
  uint32_t var_name_tmp__10;
  uint8_t var_name_tmp__11;
  uint32_t* var_name_tmp__12;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__13;
  uint8_t var_name_tmp__14;
  uint8_t var_name_tmp__15;
  uint32_t* var_name_tmp__16;
  uint64_t var_name_load_i32_3;

  var_name_tmp__6 = var_name_tmp__4;
  var_name_tmp__7 = var_name_tmp__5;
  var_name_tmp__8 = 0;
  var_name_tmp__9 = var_name_tmp__7;
  var_name_tmp__8 = (15 << (llvm_mul_u32(4, ((((uint32_t)(uint8_t)var_name_tmp__9)) & 3))));
  var_name_tmp__10 = var_name_tmp__8;
  var_name_tmp__11 = var_name_tmp__7;
  var_name_tmp__12 = (&(*((&((struct l_struct_struct_OC_SYSCFG_TypeDef*)(uintptr_t)UINT64_C(1073821696))->field2))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__11)), 2)))))]);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__12)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__12)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & (~(var_name_tmp__10))))), 32, 4);
  var_name_tmp__13 = var_name_tmp__6;
  var_name_tmp__14 = var_name_tmp__7;
  var_name_tmp__15 = var_name_tmp__7;
  var_name_tmp__16 = (&(*((&((struct l_struct_struct_OC_SYSCFG_TypeDef*)(uintptr_t)UINT64_C(1073821696))->field2))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__15)), 2)))))]);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__16)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__16)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | ((((uint32_t)(uint8_t)var_name_tmp__13)) << (llvm_mul_u32(4, ((((uint32_t)(uint8_t)var_name_tmp__14)) & 3))))))), 32, 4);
}


void SYSCFG_ETH_MediaInterfaceConfig(uint32_t var_name_tmp__17) {
  uint32_t var_name_tmp__18;    /* Address-exposed local */
  uint32_t var_name_tmp__19;

  var_name_tmp__18 = var_name_tmp__17;
  var_name_tmp__19 = var_name_tmp__18;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109852380)), (((uint64_t)(uint32_t)var_name_tmp__19)), 32, 4);
}


void SYSCFG_CompensationCellCmd(uint32_t var_name_tmp__20) {
  uint32_t var_name_tmp__21;    /* Address-exposed local */
  uint32_t var_name_tmp__22;

  var_name_tmp__21 = var_name_tmp__20;
  var_name_tmp__22 = var_name_tmp__21;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109853184)), (((uint64_t)(uint32_t)var_name_tmp__22)), 32, 4);
}


uint32_t SYSCFG_GetCompensationCellStatus(void) {
  uint32_t var_name_tmp__23;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__24;

  var_name_tmp__23 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SYSCFG_TypeDef*)(uintptr_t)UINT64_C(1073821696))->field4))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 256) != 0u)&1))) {
    goto var_name_tmp__25;
  } else {
    goto var_name_tmp__26;
  }

var_name_tmp__25:
  var_name_tmp__23 = 1;
  goto var_name_tmp__27;

var_name_tmp__26:
  var_name_tmp__23 = 0;
  goto var_name_tmp__27;

var_name_tmp__27:
  var_name_tmp__24 = var_name_tmp__23;
  return var_name_tmp__24;
}

