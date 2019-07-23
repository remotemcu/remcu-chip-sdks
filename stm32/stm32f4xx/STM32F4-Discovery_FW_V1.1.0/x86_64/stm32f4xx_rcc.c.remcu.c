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
struct l_struct_struct_OC_RCC_ClocksTypeDef;

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
struct l_struct_struct_OC_RCC_ClocksTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_array_16_uint8_t {
  uint8_t array[16];
};

/* External Global Variable Declarations */

/* Function Declarations */
void RCC_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_HSEConfig(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RCC_WaitForHSEStartUp(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RCC_GetFlagStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AdjustHSICalibrationValue(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_HSICmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_LSEConfig(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_LSICmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PLLConfig(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PLLCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PLLI2SConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PLLI2SCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_ClockSecuritySystemCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_MCO1Config(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_MCO2Config(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_SYSCLKConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t RCC_GetSYSCLKSource(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_HCLKConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PCLK1Config(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_PCLK2Config(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_GetClocksFreq(struct l_struct_struct_OC_RCC_ClocksTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_RTCCLKConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_RTCCLKCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_BackupResetCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_I2SCLKConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB1PeriphClockCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphClockCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB3PeriphClockCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphClockCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphClockCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB1PeriphResetCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphResetCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB3PeriphResetCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB1PeriphClockLPModeCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphClockLPModeCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB3PeriphClockLPModeCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphClockLPModeCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphClockLPModeCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_ITConfig(uint8_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_ClearFlag(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RCC_GetITStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_ClearITPendingBit(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* Global Variable Definitions and Initialization */
static __MSALIGN__(16) struct l_array_16_uint8_t APBAHBPrescTable __attribute__((aligned(16))) = { { 0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9 } };


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_sub_u32(uint32_t a, uint32_t b) {
  uint32_t r = a - b;
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
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void RCC_DeInit(void) {
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), UINT64_C(0), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -17367041))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), UINT64_C(603992080), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & -262145))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field3))), UINT64_C(0), 32, 4);
}


void RCC_HSEConfig(uint8_t var_name_tmp__1) {
  uint8_t var_name_tmp__2;    /* Address-exposed local */
  uint8_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887234)), UINT64_C(0), 8, 1);
  var_name_tmp__3 = var_name_tmp__2;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887234)), (((uint64_t)(uint8_t)var_name_tmp__3)), 8, 1);
}


uint32_t RCC_WaitForHSEStartUp(void) {
  uint32_t var_name_tmp__4;    /* Address-exposed local */
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint32_t var_name_tmp__6;    /* Address-exposed local */
  uint32_t var_name_tmp__7;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__8;
  bool var_name_tmp__9;
  bool var_name_tmp__9__PHI_TEMPORARY;
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;

  __adin_store_((((uint8_t*)(&var_name_tmp__4))), UINT64_C(0), 32, 4);
  var_name_tmp__5 = 0;
  var_name_tmp__6 = 0;
  goto var_name_tmp__12;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__12:
  var_name_tmp__7 = RCC_GetFlagStatus(49);
  var_name_tmp__6 = var_name_tmp__7;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__4))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__4))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), 1)))), 32, 4);
  goto var_name_tmp__13;

var_name_tmp__13:
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(&var_name_tmp__4))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_4)) != 1280u)&1))) {
    goto var_name_tmp__14;
  } else {
    var_name_tmp__9__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__15;
  }

var_name_tmp__14:
  var_name_tmp__8 = var_name_tmp__6;
  var_name_tmp__9__PHI_TEMPORARY = (((var_name_tmp__8 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__15;

var_name_tmp__15:
  var_name_tmp__9 = ((var_name_tmp__9__PHI_TEMPORARY)&1);
  if (var_name_tmp__9) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__16;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__16:
  var_name_tmp__10 = RCC_GetFlagStatus(49);
  if ((((var_name_tmp__10 != 0u)&1))) {
    goto var_name_tmp__17;
  } else {
    goto var_name_tmp__18;
  }

var_name_tmp__17:
  var_name_tmp__5 = 1;
  goto var_name_tmp__19;

var_name_tmp__18:
  var_name_tmp__5 = 0;
  goto var_name_tmp__19;

var_name_tmp__19:
  var_name_tmp__11 = var_name_tmp__5;
  return var_name_tmp__11;
}


uint32_t RCC_GetFlagStatus(uint8_t var_name_tmp__20) {
  uint8_t var_name_tmp__21;    /* Address-exposed local */
  uint32_t var_name_tmp__22;    /* Address-exposed local */
  uint32_t var_name_tmp__23;    /* Address-exposed local */
  uint32_t var_name_tmp__24;    /* Address-exposed local */
  uint8_t var_name_tmp__25;
  uint32_t var_name_tmp__26;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__27;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint8_t var_name_tmp__28;
  uint32_t var_name_tmp__29;
  uint32_t var_name_tmp__30;
  uint32_t var_name_tmp__31;

  var_name_tmp__21 = var_name_tmp__20;
  var_name_tmp__22 = 0;
  var_name_tmp__23 = 0;
  var_name_tmp__24 = 0;
  var_name_tmp__25 = var_name_tmp__21;
  var_name_tmp__22 = (llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__25)), 5));
  var_name_tmp__26 = var_name_tmp__22;
  if ((((var_name_tmp__26 == 1u)&1))) {
    goto var_name_tmp__32;
  } else {
    goto var_name_tmp__33;
  }

var_name_tmp__32:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  var_name_tmp__23 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__34;

var_name_tmp__33:
  var_name_tmp__27 = var_name_tmp__22;
  if ((((var_name_tmp__27 == 2u)&1))) {
    goto var_name_tmp__35;
  } else {
    goto var_name_tmp__36;
  }

var_name_tmp__35:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25))), 32, 4);
  var_name_tmp__23 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__37;

var_name_tmp__36:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26))), 32, 4);
  var_name_tmp__23 = (((uint32_t)var_name_load_i32_3));
  goto var_name_tmp__37;

var_name_tmp__37:
  goto var_name_tmp__34;

var_name_tmp__34:
  var_name_tmp__28 = var_name_tmp__21;
  var_name_tmp__22 = ((((uint32_t)(uint8_t)var_name_tmp__28)) & 31);
  var_name_tmp__29 = var_name_tmp__23;
  var_name_tmp__30 = var_name_tmp__22;
  if (((((var_name_tmp__29 & (1 << var_name_tmp__30)) != 0u)&1))) {
    goto var_name_tmp__38;
  } else {
    goto var_name_tmp__39;
  }

var_name_tmp__38:
  var_name_tmp__24 = 1;
  goto var_name_tmp__40;

var_name_tmp__39:
  var_name_tmp__24 = 0;
  goto var_name_tmp__40;

var_name_tmp__40:
  var_name_tmp__31 = var_name_tmp__24;
  return var_name_tmp__31;
}


void RCC_AdjustHSICalibrationValue(uint8_t var_name_tmp__41) {
  uint8_t var_name_tmp__42;    /* Address-exposed local */
  uint32_t var_name_tmp__43;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__44;
  uint8_t var_name_tmp__45;
  uint32_t var_name_tmp__46;
  uint32_t var_name_tmp__47;

  var_name_tmp__42 = var_name_tmp__41;
  var_name_tmp__43 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), 32, 4);
  var_name_tmp__43 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__44 = var_name_tmp__43;
  var_name_tmp__43 = (var_name_tmp__44 & -249);
  var_name_tmp__45 = var_name_tmp__42;
  var_name_tmp__46 = var_name_tmp__43;
  var_name_tmp__43 = (var_name_tmp__46 | ((((uint32_t)(uint8_t)var_name_tmp__45)) << 3));
  var_name_tmp__47 = var_name_tmp__43;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887232)), (((uint64_t)(uint32_t)var_name_tmp__47)), 32, 4);
}


void RCC_HSICmd(uint32_t var_name_tmp__48) {
  uint32_t var_name_tmp__49;    /* Address-exposed local */
  uint32_t var_name_tmp__50;

  var_name_tmp__49 = var_name_tmp__48;
  var_name_tmp__50 = var_name_tmp__49;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111949312)), (((uint64_t)(uint32_t)var_name_tmp__50)), 32, 4);
}


void RCC_LSEConfig(uint8_t var_name_tmp__51) {
  uint8_t var_name_tmp__52;    /* Address-exposed local */
  uint8_t var_name_tmp__53;

  var_name_tmp__52 = var_name_tmp__51;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887344)), UINT64_C(0), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887344)), UINT64_C(0), 8, 1);
  var_name_tmp__53 = var_name_tmp__52;
  switch ((((uint32_t)(uint8_t)var_name_tmp__53))) {
  default:
    goto var_name_tmp__54;
  case 1u:
    goto var_name_tmp__55;
  case 4u:
    goto var_name_tmp__56;
  }

var_name_tmp__55:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887344)), UINT64_C(1), 8, 1);
  goto var_name_tmp__57;

var_name_tmp__56:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887344)), UINT64_C(5), 8, 1);
  goto var_name_tmp__57;

var_name_tmp__54:
  goto var_name_tmp__57;

var_name_tmp__57:
  return;
}


void RCC_LSICmd(uint32_t var_name_tmp__58) {
  uint32_t var_name_tmp__59;    /* Address-exposed local */
  uint32_t var_name_tmp__60;

  var_name_tmp__59 = var_name_tmp__58;
  var_name_tmp__60 = var_name_tmp__59;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111953024)), (((uint64_t)(uint32_t)var_name_tmp__60)), 32, 4);
}


void RCC_PLLConfig(uint32_t var_name_tmp__61, uint32_t var_name_tmp__62, uint32_t var_name_tmp__63, uint32_t var_name_tmp__64, uint32_t var_name_tmp__65) {
  uint32_t var_name_tmp__66;    /* Address-exposed local */
  uint32_t var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;    /* Address-exposed local */
  uint32_t var_name_tmp__69;    /* Address-exposed local */
  uint32_t var_name_tmp__70;    /* Address-exposed local */
  uint32_t var_name_tmp__71;
  uint32_t var_name_tmp__72;
  uint32_t var_name_tmp__73;
  uint32_t var_name_tmp__74;
  uint32_t var_name_tmp__75;

  var_name_tmp__66 = var_name_tmp__61;
  var_name_tmp__67 = var_name_tmp__62;
  var_name_tmp__68 = var_name_tmp__63;
  var_name_tmp__69 = var_name_tmp__64;
  var_name_tmp__70 = var_name_tmp__65;
  var_name_tmp__71 = var_name_tmp__67;
  var_name_tmp__72 = var_name_tmp__68;
  var_name_tmp__73 = var_name_tmp__69;
  var_name_tmp__74 = var_name_tmp__66;
  var_name_tmp__75 = var_name_tmp__70;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), (((uint64_t)(uint32_t)((((var_name_tmp__71 | (var_name_tmp__72 << 6)) | ((llvm_sub_u32((llvm_lshr_u32(var_name_tmp__73, 1)), 1)) << 16)) | var_name_tmp__74) | (var_name_tmp__75 << 24)))), 32, 4);
}


void RCC_PLLCmd(uint32_t var_name_tmp__76) {
  uint32_t var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;

  var_name_tmp__77 = var_name_tmp__76;
  var_name_tmp__78 = var_name_tmp__77;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111949408)), (((uint64_t)(uint32_t)var_name_tmp__78)), 32, 4);
}


void RCC_PLLI2SConfig(uint32_t var_name_tmp__79, uint32_t var_name_tmp__80) {
  uint32_t var_name_tmp__81;    /* Address-exposed local */
  uint32_t var_name_tmp__82;    /* Address-exposed local */
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;

  var_name_tmp__81 = var_name_tmp__79;
  var_name_tmp__82 = var_name_tmp__80;
  var_name_tmp__83 = var_name_tmp__81;
  var_name_tmp__84 = var_name_tmp__82;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29))), (((uint64_t)(uint32_t)((var_name_tmp__83 << 6) | (var_name_tmp__84 << 28)))), 32, 4);
}


void RCC_PLLI2SCmd(uint32_t var_name_tmp__85) {
  uint32_t var_name_tmp__86;    /* Address-exposed local */
  uint32_t var_name_tmp__87;

  var_name_tmp__86 = var_name_tmp__85;
  var_name_tmp__87 = var_name_tmp__86;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111949416)), (((uint64_t)(uint32_t)var_name_tmp__87)), 32, 4);
}


void RCC_ClockSecuritySystemCmd(uint32_t var_name_tmp__88) {
  uint32_t var_name_tmp__89;    /* Address-exposed local */
  uint32_t var_name_tmp__90;

  var_name_tmp__89 = var_name_tmp__88;
  var_name_tmp__90 = var_name_tmp__89;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111949388)), (((uint64_t)(uint32_t)var_name_tmp__90)), 32, 4);
}


void RCC_MCO1Config(uint32_t var_name_tmp__91, uint32_t var_name_tmp__92) {
  uint32_t var_name_tmp__93;    /* Address-exposed local */
  uint32_t var_name_tmp__94;    /* Address-exposed local */
  uint32_t var_name_tmp__95;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__96;
  uint32_t var_name_tmp__97;
  uint32_t var_name_tmp__98;
  uint32_t var_name_tmp__99;
  uint32_t var_name_tmp__100;

  var_name_tmp__93 = var_name_tmp__91;
  var_name_tmp__94 = var_name_tmp__92;
  var_name_tmp__95 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__95 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__96 = var_name_tmp__95;
  var_name_tmp__95 = (var_name_tmp__96 & -123731969);
  var_name_tmp__97 = var_name_tmp__93;
  var_name_tmp__98 = var_name_tmp__94;
  var_name_tmp__99 = var_name_tmp__95;
  var_name_tmp__95 = (var_name_tmp__99 | (var_name_tmp__97 | var_name_tmp__98));
  var_name_tmp__100 = var_name_tmp__95;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__100)), 32, 4);
}


void RCC_MCO2Config(uint32_t var_name_tmp__101, uint32_t var_name_tmp__102) {
  uint32_t var_name_tmp__103;    /* Address-exposed local */
  uint32_t var_name_tmp__104;    /* Address-exposed local */
  uint32_t var_name_tmp__105;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  uint32_t var_name_tmp__109;
  uint32_t var_name_tmp__110;

  var_name_tmp__103 = var_name_tmp__101;
  var_name_tmp__104 = var_name_tmp__102;
  var_name_tmp__105 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__105 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__106 = var_name_tmp__105;
  var_name_tmp__105 = (var_name_tmp__106 & 134217727);
  var_name_tmp__107 = var_name_tmp__103;
  var_name_tmp__108 = var_name_tmp__104;
  var_name_tmp__109 = var_name_tmp__105;
  var_name_tmp__105 = (var_name_tmp__109 | (var_name_tmp__107 | var_name_tmp__108));
  var_name_tmp__110 = var_name_tmp__105;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__110)), 32, 4);
}


void RCC_SYSCLKConfig(uint32_t var_name_tmp__111) {
  uint32_t var_name_tmp__112;    /* Address-exposed local */
  uint32_t var_name_tmp__113;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__114;
  uint32_t var_name_tmp__115;
  uint32_t var_name_tmp__116;
  uint32_t var_name_tmp__117;

  var_name_tmp__112 = var_name_tmp__111;
  var_name_tmp__113 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__113 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__114 = var_name_tmp__113;
  var_name_tmp__113 = (var_name_tmp__114 & -4);
  var_name_tmp__115 = var_name_tmp__112;
  var_name_tmp__116 = var_name_tmp__113;
  var_name_tmp__113 = (var_name_tmp__116 | var_name_tmp__115);
  var_name_tmp__117 = var_name_tmp__113;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__117)), 32, 4);
}


uint8_t RCC_GetSYSCLKSource(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  return (((uint8_t)((((uint32_t)var_name_load_i32_)) & 12)));
}


void RCC_HCLKConfig(uint32_t var_name_tmp__118) {
  uint32_t var_name_tmp__119;    /* Address-exposed local */
  uint32_t var_name_tmp__120;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__121;
  uint32_t var_name_tmp__122;
  uint32_t var_name_tmp__123;
  uint32_t var_name_tmp__124;

  var_name_tmp__119 = var_name_tmp__118;
  var_name_tmp__120 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__120 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__121 = var_name_tmp__120;
  var_name_tmp__120 = (var_name_tmp__121 & -241);
  var_name_tmp__122 = var_name_tmp__119;
  var_name_tmp__123 = var_name_tmp__120;
  var_name_tmp__120 = (var_name_tmp__123 | var_name_tmp__122);
  var_name_tmp__124 = var_name_tmp__120;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__124)), 32, 4);
}


void RCC_PCLK1Config(uint32_t var_name_tmp__125) {
  uint32_t var_name_tmp__126;    /* Address-exposed local */
  uint32_t var_name_tmp__127;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__128;
  uint32_t var_name_tmp__129;
  uint32_t var_name_tmp__130;
  uint32_t var_name_tmp__131;

  var_name_tmp__126 = var_name_tmp__125;
  var_name_tmp__127 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__127 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__128 = var_name_tmp__127;
  var_name_tmp__127 = (var_name_tmp__128 & -7169);
  var_name_tmp__129 = var_name_tmp__126;
  var_name_tmp__130 = var_name_tmp__127;
  var_name_tmp__127 = (var_name_tmp__130 | var_name_tmp__129);
  var_name_tmp__131 = var_name_tmp__127;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__131)), 32, 4);
}


void RCC_PCLK2Config(uint32_t var_name_tmp__132) {
  uint32_t var_name_tmp__133;    /* Address-exposed local */
  uint32_t var_name_tmp__134;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__135;
  uint32_t var_name_tmp__136;
  uint32_t var_name_tmp__137;
  uint32_t var_name_tmp__138;

  var_name_tmp__133 = var_name_tmp__132;
  var_name_tmp__134 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__134 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__135 = var_name_tmp__134;
  var_name_tmp__134 = (var_name_tmp__135 & -57345);
  var_name_tmp__136 = var_name_tmp__133;
  var_name_tmp__137 = var_name_tmp__134;
  var_name_tmp__134 = (var_name_tmp__137 | (var_name_tmp__136 << 3));
  var_name_tmp__138 = var_name_tmp__134;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__138)), 32, 4);
}


void RCC_GetClocksFreq(struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__139) {
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__140;    /* Address-exposed local */
  uint32_t var_name_tmp__141;    /* Address-exposed local */
  uint32_t var_name_tmp__142;    /* Address-exposed local */
  uint32_t var_name_tmp__143;    /* Address-exposed local */
  uint32_t var_name_tmp__144;    /* Address-exposed local */
  uint32_t var_name_tmp__145;    /* Address-exposed local */
  uint32_t var_name_tmp__146;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__147;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__148;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__149;
  uint64_t var_name_load_i32_2;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__150;
  uint32_t var_name_tmp__151;
  uint64_t var_name_load_i32_6;
  uint32_t var_name_tmp__152;
  uint64_t var_name_load_i32_8;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__153;
  uint32_t var_name_tmp__154;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__155;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__156;
  uint64_t var_name_load_i32_14;
  uint32_t var_name_tmp__157;
  uint32_t var_name_tmp__158;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__159;
  uint64_t var_name_load_i32_17;
  uint32_t var_name_tmp__160;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__161;
  uint64_t var_name_load_i32_21;
  uint32_t var_name_tmp__162;
  uint32_t var_name_tmp__163;
  uint64_t var_name_load_i8_23;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__164;
  uint64_t var_name_load_i32_26;
  uint32_t var_name_tmp__165;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__166;
  uint64_t var_name_load_i32_30;
  uint32_t var_name_tmp__167;
  uint32_t var_name_tmp__168;
  uint64_t var_name_load_i8_32;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__169;
  uint64_t var_name_load_i32_35;
  uint32_t var_name_tmp__170;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__171;

  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = 0;
  var_name_tmp__142 = 0;
  var_name_tmp__143 = 0;
  var_name_tmp__144 = 2;
  var_name_tmp__145 = 0;
  var_name_tmp__146 = 2;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__141 = ((((uint32_t)var_name_load_i32_)) & 12);
  var_name_tmp__147 = var_name_tmp__141;
  switch (var_name_tmp__147) {
  default:
    goto var_name_tmp__172;
  case 0u:
    goto var_name_tmp__173;
  case 4u:
    goto var_name_tmp__174;
  case 8u:
    goto var_name_tmp__175;
  }

var_name_tmp__173:
  var_name_tmp__148 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__148->field0)))), UINT64_C(16000000), 32, 4);
  goto var_name_tmp__176;

var_name_tmp__174:
  var_name_tmp__149 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__149->field0)))), UINT64_C(8000000), 32, 4);
  goto var_name_tmp__176;

var_name_tmp__175:
  var_name_load_i32_2 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__145 = (llvm_lshr_u32(((((uint32_t)var_name_load_i32_2)) & 4194304), 22));
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__146 = ((((uint32_t)var_name_load_i32_4)) & 63);
  var_name_tmp__150 = var_name_tmp__145;
  if ((((var_name_tmp__150 != 0u)&1))) {
    goto var_name_tmp__177;
  } else {
    goto var_name_tmp__178;
  }

var_name_tmp__177:
  var_name_tmp__151 = var_name_tmp__146;
  var_name_load_i32_6 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__143 = (llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__151)), (llvm_lshr_u32(((((uint32_t)var_name_load_i32_6)) & 32704), 6))));
  goto var_name_tmp__179;

var_name_tmp__178:
  var_name_tmp__152 = var_name_tmp__146;
  var_name_load_i32_8 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__143 = (llvm_mul_u32((llvm_udiv_u32(16000000, var_name_tmp__152)), (llvm_lshr_u32(((((uint32_t)var_name_load_i32_8)) & 32704), 6))));
  goto var_name_tmp__179;

var_name_tmp__179:
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__144 = (llvm_mul_u32((llvm_add_u32((llvm_lshr_u32(((((uint32_t)var_name_load_i32_10)) & 196608), 16)), 1)), 2));
  var_name_tmp__153 = var_name_tmp__143;
  var_name_tmp__154 = var_name_tmp__144;
  var_name_tmp__155 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__155->field0)))), (((uint64_t)(uint32_t)(llvm_udiv_u32(var_name_tmp__153, var_name_tmp__154)))), 32, 4);
  goto var_name_tmp__176;

var_name_tmp__172:
  var_name_tmp__156 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__156->field0)))), UINT64_C(16000000), 32, 4);
  goto var_name_tmp__176;

var_name_tmp__176:
  var_name_load_i32_14 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__141 = ((((uint32_t)var_name_load_i32_14)) & 240);
  var_name_tmp__157 = var_name_tmp__141;
  var_name_tmp__141 = (llvm_lshr_u32(var_name_tmp__157, 4));
  var_name_tmp__158 = var_name_tmp__141;
  var_name_load_i8_ = __adin_load_(((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__158)))])), 8, 1);
  var_name_tmp__142 = (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_))));
  var_name_tmp__159 = var_name_tmp__140;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__159->field0)))), 32, 4);
  var_name_tmp__160 = var_name_tmp__142;
  var_name_tmp__161 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__161->field1)))), (((uint64_t)(uint32_t)(llvm_lshr_u32((((uint32_t)var_name_load_i32_17)), var_name_tmp__160)))), 32, 4);
  var_name_load_i32_21 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__141 = ((((uint32_t)var_name_load_i32_21)) & 7168);
  var_name_tmp__162 = var_name_tmp__141;
  var_name_tmp__141 = (llvm_lshr_u32(var_name_tmp__162, 10));
  var_name_tmp__163 = var_name_tmp__141;
  var_name_load_i8_23 = __adin_load_(((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__163)))])), 8, 1);
  var_name_tmp__142 = (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_23))));
  var_name_tmp__164 = var_name_tmp__140;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__164->field1)))), 32, 4);
  var_name_tmp__165 = var_name_tmp__142;
  var_name_tmp__166 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__166->field2)))), (((uint64_t)(uint32_t)(llvm_lshr_u32((((uint32_t)var_name_load_i32_26)), var_name_tmp__165)))), 32, 4);
  var_name_load_i32_30 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__141 = ((((uint32_t)var_name_load_i32_30)) & 57344);
  var_name_tmp__167 = var_name_tmp__141;
  var_name_tmp__141 = (llvm_lshr_u32(var_name_tmp__167, 13));
  var_name_tmp__168 = var_name_tmp__141;
  var_name_load_i8_32 = __adin_load_(((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__168)))])), 8, 1);
  var_name_tmp__142 = (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_32))));
  var_name_tmp__169 = var_name_tmp__140;
  var_name_load_i32_35 = __adin_load_((((uint8_t*)((&var_name_tmp__169->field1)))), 32, 4);
  var_name_tmp__170 = var_name_tmp__142;
  var_name_tmp__171 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__171->field3)))), (((uint64_t)(uint32_t)(llvm_lshr_u32((((uint32_t)var_name_load_i32_35)), var_name_tmp__170)))), 32, 4);
}


void RCC_RTCCLKConfig(uint32_t var_name_tmp__180) {
  uint32_t var_name_tmp__181;    /* Address-exposed local */
  uint32_t var_name_tmp__182;    /* Address-exposed local */
  uint32_t var_name_tmp__183;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__184;
  uint32_t var_name_tmp__185;
  uint32_t var_name_tmp__186;
  uint32_t var_name_tmp__187;
  uint32_t var_name_tmp__188;
  uint64_t var_name_load_i32_1;

  var_name_tmp__181 = var_name_tmp__180;
  var_name_tmp__182 = 0;
  var_name_tmp__183 = var_name_tmp__181;
  if (((((var_name_tmp__183 & 768) == 768u)&1))) {
    goto var_name_tmp__189;
  } else {
    goto var_name_tmp__190;
  }

var_name_tmp__189:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  var_name_tmp__182 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__184 = var_name_tmp__182;
  var_name_tmp__182 = (var_name_tmp__184 & -2031617);
  var_name_tmp__185 = var_name_tmp__181;
  var_name_tmp__186 = var_name_tmp__182;
  var_name_tmp__182 = (var_name_tmp__186 | (var_name_tmp__185 & 268434687));
  var_name_tmp__187 = var_name_tmp__182;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)var_name_tmp__187)), 32, 4);
  goto var_name_tmp__190;

var_name_tmp__190:
  var_name_tmp__188 = var_name_tmp__181;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (var_name_tmp__188 & 4095)))), 32, 4);
}


void RCC_RTCCLKCmd(uint32_t var_name_tmp__191) {
  uint32_t var_name_tmp__192;    /* Address-exposed local */
  uint32_t var_name_tmp__193;

  var_name_tmp__192 = var_name_tmp__191;
  var_name_tmp__193 = var_name_tmp__192;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111952956)), (((uint64_t)(uint32_t)var_name_tmp__193)), 32, 4);
}


void RCC_BackupResetCmd(uint32_t var_name_tmp__194) {
  uint32_t var_name_tmp__195;    /* Address-exposed local */
  uint32_t var_name_tmp__196;

  var_name_tmp__195 = var_name_tmp__194;
  var_name_tmp__196 = var_name_tmp__195;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111952960)), (((uint64_t)(uint32_t)var_name_tmp__196)), 32, 4);
}


void RCC_I2SCLKConfig(uint32_t var_name_tmp__197) {
  uint32_t var_name_tmp__198;    /* Address-exposed local */
  uint32_t var_name_tmp__199;

  var_name_tmp__198 = var_name_tmp__197;
  var_name_tmp__199 = var_name_tmp__198;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1111949660)), (((uint64_t)(uint32_t)var_name_tmp__199)), 32, 4);
}


void RCC_AHB1PeriphClockCmd(uint32_t var_name_tmp__200, uint32_t var_name_tmp__201) {
  uint32_t var_name_tmp__202;    /* Address-exposed local */
  uint32_t var_name_tmp__203;    /* Address-exposed local */
  uint32_t var_name_tmp__204;
  uint32_t var_name_tmp__205;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__206;
  uint64_t var_name_load_i32_1;

  var_name_tmp__202 = var_name_tmp__200;
  var_name_tmp__203 = var_name_tmp__201;
  var_name_tmp__204 = var_name_tmp__203;
  if ((((var_name_tmp__204 != 0u)&1))) {
    goto var_name_tmp__207;
  } else {
    goto var_name_tmp__208;
  }

var_name_tmp__207:
  var_name_tmp__205 = var_name_tmp__202;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__205))), 32, 4);
  goto var_name_tmp__209;

var_name_tmp__208:
  var_name_tmp__206 = var_name_tmp__202;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__206))))), 32, 4);
  goto var_name_tmp__209;

var_name_tmp__209:
  return;
}


void RCC_AHB2PeriphClockCmd(uint32_t var_name_tmp__210, uint32_t var_name_tmp__211) {
  uint32_t var_name_tmp__212;    /* Address-exposed local */
  uint32_t var_name_tmp__213;    /* Address-exposed local */
  uint32_t var_name_tmp__214;
  uint32_t var_name_tmp__215;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__216;
  uint64_t var_name_load_i32_1;

  var_name_tmp__212 = var_name_tmp__210;
  var_name_tmp__213 = var_name_tmp__211;
  var_name_tmp__214 = var_name_tmp__213;
  if ((((var_name_tmp__214 != 0u)&1))) {
    goto var_name_tmp__217;
  } else {
    goto var_name_tmp__218;
  }

var_name_tmp__217:
  var_name_tmp__215 = var_name_tmp__212;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__215))), 32, 4);
  goto var_name_tmp__219;

var_name_tmp__218:
  var_name_tmp__216 = var_name_tmp__212;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__216))))), 32, 4);
  goto var_name_tmp__219;

var_name_tmp__219:
  return;
}


void RCC_AHB3PeriphClockCmd(uint32_t var_name_tmp__220, uint32_t var_name_tmp__221) {
  uint32_t var_name_tmp__222;    /* Address-exposed local */
  uint32_t var_name_tmp__223;    /* Address-exposed local */
  uint32_t var_name_tmp__224;
  uint32_t var_name_tmp__225;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__226;
  uint64_t var_name_load_i32_1;

  var_name_tmp__222 = var_name_tmp__220;
  var_name_tmp__223 = var_name_tmp__221;
  var_name_tmp__224 = var_name_tmp__223;
  if ((((var_name_tmp__224 != 0u)&1))) {
    goto var_name_tmp__227;
  } else {
    goto var_name_tmp__228;
  }

var_name_tmp__227:
  var_name_tmp__225 = var_name_tmp__222;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__225))), 32, 4);
  goto var_name_tmp__229;

var_name_tmp__228:
  var_name_tmp__226 = var_name_tmp__222;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__226))))), 32, 4);
  goto var_name_tmp__229;

var_name_tmp__229:
  return;
}


void RCC_APB1PeriphClockCmd(uint32_t var_name_tmp__230, uint32_t var_name_tmp__231) {
  uint32_t var_name_tmp__232;    /* Address-exposed local */
  uint32_t var_name_tmp__233;    /* Address-exposed local */
  uint32_t var_name_tmp__234;
  uint32_t var_name_tmp__235;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__236;
  uint64_t var_name_load_i32_1;

  var_name_tmp__232 = var_name_tmp__230;
  var_name_tmp__233 = var_name_tmp__231;
  var_name_tmp__234 = var_name_tmp__233;
  if ((((var_name_tmp__234 != 0u)&1))) {
    goto var_name_tmp__237;
  } else {
    goto var_name_tmp__238;
  }

var_name_tmp__237:
  var_name_tmp__235 = var_name_tmp__232;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__235))), 32, 4);
  goto var_name_tmp__239;

var_name_tmp__238:
  var_name_tmp__236 = var_name_tmp__232;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__236))))), 32, 4);
  goto var_name_tmp__239;

var_name_tmp__239:
  return;
}


void RCC_APB2PeriphClockCmd(uint32_t var_name_tmp__240, uint32_t var_name_tmp__241) {
  uint32_t var_name_tmp__242;    /* Address-exposed local */
  uint32_t var_name_tmp__243;    /* Address-exposed local */
  uint32_t var_name_tmp__244;
  uint32_t var_name_tmp__245;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__246;
  uint64_t var_name_load_i32_1;

  var_name_tmp__242 = var_name_tmp__240;
  var_name_tmp__243 = var_name_tmp__241;
  var_name_tmp__244 = var_name_tmp__243;
  if ((((var_name_tmp__244 != 0u)&1))) {
    goto var_name_tmp__247;
  } else {
    goto var_name_tmp__248;
  }

var_name_tmp__247:
  var_name_tmp__245 = var_name_tmp__242;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__245))), 32, 4);
  goto var_name_tmp__249;

var_name_tmp__248:
  var_name_tmp__246 = var_name_tmp__242;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__246))))), 32, 4);
  goto var_name_tmp__249;

var_name_tmp__249:
  return;
}


void RCC_AHB1PeriphResetCmd(uint32_t var_name_tmp__250, uint32_t var_name_tmp__251) {
  uint32_t var_name_tmp__252;    /* Address-exposed local */
  uint32_t var_name_tmp__253;    /* Address-exposed local */
  uint32_t var_name_tmp__254;
  uint32_t var_name_tmp__255;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__256;
  uint64_t var_name_load_i32_1;

  var_name_tmp__252 = var_name_tmp__250;
  var_name_tmp__253 = var_name_tmp__251;
  var_name_tmp__254 = var_name_tmp__253;
  if ((((var_name_tmp__254 != 0u)&1))) {
    goto var_name_tmp__257;
  } else {
    goto var_name_tmp__258;
  }

var_name_tmp__257:
  var_name_tmp__255 = var_name_tmp__252;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__255))), 32, 4);
  goto var_name_tmp__259;

var_name_tmp__258:
  var_name_tmp__256 = var_name_tmp__252;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__256))))), 32, 4);
  goto var_name_tmp__259;

var_name_tmp__259:
  return;
}


void RCC_AHB2PeriphResetCmd(uint32_t var_name_tmp__260, uint32_t var_name_tmp__261) {
  uint32_t var_name_tmp__262;    /* Address-exposed local */
  uint32_t var_name_tmp__263;    /* Address-exposed local */
  uint32_t var_name_tmp__264;
  uint32_t var_name_tmp__265;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__266;
  uint64_t var_name_load_i32_1;

  var_name_tmp__262 = var_name_tmp__260;
  var_name_tmp__263 = var_name_tmp__261;
  var_name_tmp__264 = var_name_tmp__263;
  if ((((var_name_tmp__264 != 0u)&1))) {
    goto var_name_tmp__267;
  } else {
    goto var_name_tmp__268;
  }

var_name_tmp__267:
  var_name_tmp__265 = var_name_tmp__262;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__265))), 32, 4);
  goto var_name_tmp__269;

var_name_tmp__268:
  var_name_tmp__266 = var_name_tmp__262;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__266))))), 32, 4);
  goto var_name_tmp__269;

var_name_tmp__269:
  return;
}


void RCC_AHB3PeriphResetCmd(uint32_t var_name_tmp__270, uint32_t var_name_tmp__271) {
  uint32_t var_name_tmp__272;    /* Address-exposed local */
  uint32_t var_name_tmp__273;    /* Address-exposed local */
  uint32_t var_name_tmp__274;
  uint32_t var_name_tmp__275;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__276;
  uint64_t var_name_load_i32_1;

  var_name_tmp__272 = var_name_tmp__270;
  var_name_tmp__273 = var_name_tmp__271;
  var_name_tmp__274 = var_name_tmp__273;
  if ((((var_name_tmp__274 != 0u)&1))) {
    goto var_name_tmp__277;
  } else {
    goto var_name_tmp__278;
  }

var_name_tmp__277:
  var_name_tmp__275 = var_name_tmp__272;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__275))), 32, 4);
  goto var_name_tmp__279;

var_name_tmp__278:
  var_name_tmp__276 = var_name_tmp__272;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__276))))), 32, 4);
  goto var_name_tmp__279;

var_name_tmp__279:
  return;
}


void RCC_APB1PeriphResetCmd(uint32_t var_name_tmp__280, uint32_t var_name_tmp__281) {
  uint32_t var_name_tmp__282;    /* Address-exposed local */
  uint32_t var_name_tmp__283;    /* Address-exposed local */
  uint32_t var_name_tmp__284;
  uint32_t var_name_tmp__285;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__286;
  uint64_t var_name_load_i32_1;

  var_name_tmp__282 = var_name_tmp__280;
  var_name_tmp__283 = var_name_tmp__281;
  var_name_tmp__284 = var_name_tmp__283;
  if ((((var_name_tmp__284 != 0u)&1))) {
    goto var_name_tmp__287;
  } else {
    goto var_name_tmp__288;
  }

var_name_tmp__287:
  var_name_tmp__285 = var_name_tmp__282;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__285))), 32, 4);
  goto var_name_tmp__289;

var_name_tmp__288:
  var_name_tmp__286 = var_name_tmp__282;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__286))))), 32, 4);
  goto var_name_tmp__289;

var_name_tmp__289:
  return;
}


void RCC_APB2PeriphResetCmd(uint32_t var_name_tmp__290, uint32_t var_name_tmp__291) {
  uint32_t var_name_tmp__292;    /* Address-exposed local */
  uint32_t var_name_tmp__293;    /* Address-exposed local */
  uint32_t var_name_tmp__294;
  uint32_t var_name_tmp__295;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__296;
  uint64_t var_name_load_i32_1;

  var_name_tmp__292 = var_name_tmp__290;
  var_name_tmp__293 = var_name_tmp__291;
  var_name_tmp__294 = var_name_tmp__293;
  if ((((var_name_tmp__294 != 0u)&1))) {
    goto var_name_tmp__297;
  } else {
    goto var_name_tmp__298;
  }

var_name_tmp__297:
  var_name_tmp__295 = var_name_tmp__292;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__295))), 32, 4);
  goto var_name_tmp__299;

var_name_tmp__298:
  var_name_tmp__296 = var_name_tmp__292;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__296))))), 32, 4);
  goto var_name_tmp__299;

var_name_tmp__299:
  return;
}


void RCC_AHB1PeriphClockLPModeCmd(uint32_t var_name_tmp__300, uint32_t var_name_tmp__301) {
  uint32_t var_name_tmp__302;    /* Address-exposed local */
  uint32_t var_name_tmp__303;    /* Address-exposed local */
  uint32_t var_name_tmp__304;
  uint32_t var_name_tmp__305;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__306;
  uint64_t var_name_load_i32_1;

  var_name_tmp__302 = var_name_tmp__300;
  var_name_tmp__303 = var_name_tmp__301;
  var_name_tmp__304 = var_name_tmp__303;
  if ((((var_name_tmp__304 != 0u)&1))) {
    goto var_name_tmp__307;
  } else {
    goto var_name_tmp__308;
  }

var_name_tmp__307:
  var_name_tmp__305 = var_name_tmp__302;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__305))), 32, 4);
  goto var_name_tmp__309;

var_name_tmp__308:
  var_name_tmp__306 = var_name_tmp__302;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__306))))), 32, 4);
  goto var_name_tmp__309;

var_name_tmp__309:
  return;
}


void RCC_AHB2PeriphClockLPModeCmd(uint32_t var_name_tmp__310, uint32_t var_name_tmp__311) {
  uint32_t var_name_tmp__312;    /* Address-exposed local */
  uint32_t var_name_tmp__313;    /* Address-exposed local */
  uint32_t var_name_tmp__314;
  uint32_t var_name_tmp__315;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__316;
  uint64_t var_name_load_i32_1;

  var_name_tmp__312 = var_name_tmp__310;
  var_name_tmp__313 = var_name_tmp__311;
  var_name_tmp__314 = var_name_tmp__313;
  if ((((var_name_tmp__314 != 0u)&1))) {
    goto var_name_tmp__317;
  } else {
    goto var_name_tmp__318;
  }

var_name_tmp__317:
  var_name_tmp__315 = var_name_tmp__312;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__315))), 32, 4);
  goto var_name_tmp__319;

var_name_tmp__318:
  var_name_tmp__316 = var_name_tmp__312;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__316))))), 32, 4);
  goto var_name_tmp__319;

var_name_tmp__319:
  return;
}


void RCC_AHB3PeriphClockLPModeCmd(uint32_t var_name_tmp__320, uint32_t var_name_tmp__321) {
  uint32_t var_name_tmp__322;    /* Address-exposed local */
  uint32_t var_name_tmp__323;    /* Address-exposed local */
  uint32_t var_name_tmp__324;
  uint32_t var_name_tmp__325;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__326;
  uint64_t var_name_load_i32_1;

  var_name_tmp__322 = var_name_tmp__320;
  var_name_tmp__323 = var_name_tmp__321;
  var_name_tmp__324 = var_name_tmp__323;
  if ((((var_name_tmp__324 != 0u)&1))) {
    goto var_name_tmp__327;
  } else {
    goto var_name_tmp__328;
  }

var_name_tmp__327:
  var_name_tmp__325 = var_name_tmp__322;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__325))), 32, 4);
  goto var_name_tmp__329;

var_name_tmp__328:
  var_name_tmp__326 = var_name_tmp__322;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__326))))), 32, 4);
  goto var_name_tmp__329;

var_name_tmp__329:
  return;
}


void RCC_APB1PeriphClockLPModeCmd(uint32_t var_name_tmp__330, uint32_t var_name_tmp__331) {
  uint32_t var_name_tmp__332;    /* Address-exposed local */
  uint32_t var_name_tmp__333;    /* Address-exposed local */
  uint32_t var_name_tmp__334;
  uint32_t var_name_tmp__335;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__336;
  uint64_t var_name_load_i32_1;

  var_name_tmp__332 = var_name_tmp__330;
  var_name_tmp__333 = var_name_tmp__331;
  var_name_tmp__334 = var_name_tmp__333;
  if ((((var_name_tmp__334 != 0u)&1))) {
    goto var_name_tmp__337;
  } else {
    goto var_name_tmp__338;
  }

var_name_tmp__337:
  var_name_tmp__335 = var_name_tmp__332;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__335))), 32, 4);
  goto var_name_tmp__339;

var_name_tmp__338:
  var_name_tmp__336 = var_name_tmp__332;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__336))))), 32, 4);
  goto var_name_tmp__339;

var_name_tmp__339:
  return;
}


void RCC_APB2PeriphClockLPModeCmd(uint32_t var_name_tmp__340, uint32_t var_name_tmp__341) {
  uint32_t var_name_tmp__342;    /* Address-exposed local */
  uint32_t var_name_tmp__343;    /* Address-exposed local */
  uint32_t var_name_tmp__344;
  uint32_t var_name_tmp__345;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__346;
  uint64_t var_name_load_i32_1;

  var_name_tmp__342 = var_name_tmp__340;
  var_name_tmp__343 = var_name_tmp__341;
  var_name_tmp__344 = var_name_tmp__343;
  if ((((var_name_tmp__344 != 0u)&1))) {
    goto var_name_tmp__347;
  } else {
    goto var_name_tmp__348;
  }

var_name_tmp__347:
  var_name_tmp__345 = var_name_tmp__342;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__345))), 32, 4);
  goto var_name_tmp__349;

var_name_tmp__348:
  var_name_tmp__346 = var_name_tmp__342;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__346))))), 32, 4);
  goto var_name_tmp__349;

var_name_tmp__349:
  return;
}


void RCC_ITConfig(uint8_t var_name_tmp__350, uint32_t var_name_tmp__351) {
  uint8_t var_name_tmp__352;    /* Address-exposed local */
  uint32_t var_name_tmp__353;    /* Address-exposed local */
  uint32_t var_name_tmp__354;
  uint8_t var_name_tmp__355;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__356;
  uint64_t var_name_load_i8_1;

  var_name_tmp__352 = var_name_tmp__350;
  var_name_tmp__353 = var_name_tmp__351;
  var_name_tmp__354 = var_name_tmp__353;
  if ((((var_name_tmp__354 != 0u)&1))) {
    goto var_name_tmp__357;
  } else {
    goto var_name_tmp__358;
  }

var_name_tmp__357:
  var_name_tmp__355 = var_name_tmp__352;
  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887245)), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887245)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) | (((uint32_t)(uint8_t)var_name_tmp__355))))))), 8, 1);
  goto var_name_tmp__359;

var_name_tmp__358:
  var_name_tmp__356 = var_name_tmp__352;
  var_name_load_i8_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073887245)), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887245)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_1)))) & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__356))))))))))))), 8, 1);
  goto var_name_tmp__359;

var_name_tmp__359:
  return;
}


void RCC_ClearFlag(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 16777216))), 32, 4);
}


uint32_t RCC_GetITStatus(uint8_t var_name_tmp__360) {
  uint8_t var_name_tmp__361;    /* Address-exposed local */
  uint32_t var_name_tmp__362;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__363;
  uint32_t var_name_tmp__364;

  var_name_tmp__361 = var_name_tmp__360;
  var_name_tmp__362 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field3))), 32, 4);
  var_name_tmp__363 = var_name_tmp__361;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint8_t)var_name_tmp__363))) != 0u)&1))) {
    goto var_name_tmp__365;
  } else {
    goto var_name_tmp__366;
  }

var_name_tmp__365:
  var_name_tmp__362 = 1;
  goto var_name_tmp__367;

var_name_tmp__366:
  var_name_tmp__362 = 0;
  goto var_name_tmp__367;

var_name_tmp__367:
  var_name_tmp__364 = var_name_tmp__362;
  return var_name_tmp__364;
}


void RCC_ClearITPendingBit(uint8_t var_name_tmp__368) {
  uint8_t var_name_tmp__369;    /* Address-exposed local */
  uint8_t var_name_tmp__370;

  var_name_tmp__369 = var_name_tmp__368;
  var_name_tmp__370 = var_name_tmp__369;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073887246)), (((uint64_t)(uint8_t)var_name_tmp__370)), 8, 1);
}

