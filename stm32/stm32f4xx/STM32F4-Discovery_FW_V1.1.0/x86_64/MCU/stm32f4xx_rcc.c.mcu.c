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
}


void RCC_HSEConfig(uint8_t var_name_tmp__4) {
  uint8_t var_name_tmp__5;    /* Address-exposed local */
  uint8_t var_name_tmp__6;

  var_name_tmp__5 = var_name_tmp__4;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887234)) = 0;
  var_name_tmp__6 = var_name_tmp__5;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887234)) = var_name_tmp__6;
}


uint32_t RCC_WaitForHSEStartUp(void) {
  uint32_t var_name_tmp__7;    /* Address-exposed local */
  uint32_t var_name_tmp__8;    /* Address-exposed local */
  uint32_t var_name_tmp__9;    /* Address-exposed local */
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;
  bool var_name_tmp__14;
  bool var_name_tmp__14__PHI_TEMPORARY;
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;

  *(volatile uint32_t*)(&var_name_tmp__7) = 0;
  var_name_tmp__8 = 0;
  var_name_tmp__9 = 0;
  goto var_name_tmp__17;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__17:
  var_name_tmp__10 = RCC_GetFlagStatus(49);
  var_name_tmp__9 = var_name_tmp__10;
  var_name_tmp__11 = *(volatile uint32_t*)(&var_name_tmp__7);
  *(volatile uint32_t*)(&var_name_tmp__7) = (llvm_add_u32(var_name_tmp__11, 1));
  goto var_name_tmp__18;

var_name_tmp__18:
  var_name_tmp__12 = *(volatile uint32_t*)(&var_name_tmp__7);
  if ((((var_name_tmp__12 != 1280u)&1))) {
    goto var_name_tmp__19;
  } else {
    var_name_tmp__14__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__20;
  }

var_name_tmp__19:
  var_name_tmp__13 = var_name_tmp__9;
  var_name_tmp__14__PHI_TEMPORARY = (((var_name_tmp__13 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__20;

var_name_tmp__20:
  var_name_tmp__14 = ((var_name_tmp__14__PHI_TEMPORARY)&1);
  if (var_name_tmp__14) {
    goto var_name_tmp__17;
  } else {
    goto var_name_tmp__21;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__21:
  var_name_tmp__15 = RCC_GetFlagStatus(49);
  if ((((var_name_tmp__15 != 0u)&1))) {
    goto var_name_tmp__22;
  } else {
    goto var_name_tmp__23;
  }

var_name_tmp__22:
  var_name_tmp__8 = 1;
  goto var_name_tmp__24;

var_name_tmp__23:
  var_name_tmp__8 = 0;
  goto var_name_tmp__24;

var_name_tmp__24:
  var_name_tmp__16 = var_name_tmp__8;
  return var_name_tmp__16;
}


uint32_t RCC_GetFlagStatus(uint8_t var_name_tmp__25) {
  uint8_t var_name_tmp__26;    /* Address-exposed local */
  uint32_t var_name_tmp__27;    /* Address-exposed local */
  uint32_t var_name_tmp__28;    /* Address-exposed local */
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  uint8_t var_name_tmp__30;
  uint32_t var_name_tmp__31;
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint32_t var_name_tmp__35;
  uint8_t var_name_tmp__36;
  uint32_t var_name_tmp__37;
  uint32_t var_name_tmp__38;
  uint32_t var_name_tmp__39;

  var_name_tmp__26 = var_name_tmp__25;
  var_name_tmp__27 = 0;
  var_name_tmp__28 = 0;
  var_name_tmp__29 = 0;
  var_name_tmp__30 = var_name_tmp__26;
  var_name_tmp__27 = (llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__30)), 5));
  var_name_tmp__31 = var_name_tmp__27;
  if ((((var_name_tmp__31 == 1u)&1))) {
    goto var_name_tmp__40;
  } else {
    goto var_name_tmp__41;
  }

var_name_tmp__40:
  var_name_tmp__32 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  var_name_tmp__28 = var_name_tmp__32;
  goto var_name_tmp__42;

var_name_tmp__41:
  var_name_tmp__33 = var_name_tmp__27;
  if ((((var_name_tmp__33 == 2u)&1))) {
    goto var_name_tmp__43;
  } else {
    goto var_name_tmp__44;
  }

var_name_tmp__43:
  var_name_tmp__34 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25));
  var_name_tmp__28 = var_name_tmp__34;
  goto var_name_tmp__45;

var_name_tmp__44:
  var_name_tmp__35 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26));
  var_name_tmp__28 = var_name_tmp__35;
  goto var_name_tmp__45;

var_name_tmp__45:
  goto var_name_tmp__42;

var_name_tmp__42:
  var_name_tmp__36 = var_name_tmp__26;
  var_name_tmp__27 = ((((uint32_t)(uint8_t)var_name_tmp__36)) & 31);
  var_name_tmp__37 = var_name_tmp__28;
  var_name_tmp__38 = var_name_tmp__27;
  if (((((var_name_tmp__37 & (1 << var_name_tmp__38)) != 0u)&1))) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__47;
  }

var_name_tmp__46:
  var_name_tmp__29 = 1;
  goto var_name_tmp__48;

var_name_tmp__47:
  var_name_tmp__29 = 0;
  goto var_name_tmp__48;

var_name_tmp__48:
  var_name_tmp__39 = var_name_tmp__29;
  return var_name_tmp__39;
}


void RCC_AdjustHSICalibrationValue(uint8_t var_name_tmp__49) {
  uint8_t var_name_tmp__50;    /* Address-exposed local */
  uint32_t var_name_tmp__51;    /* Address-exposed local */
  uint32_t var_name_tmp__52;
  uint32_t var_name_tmp__53;
  uint8_t var_name_tmp__54;
  uint32_t var_name_tmp__55;
  uint32_t var_name_tmp__56;

  var_name_tmp__50 = var_name_tmp__49;
  var_name_tmp__51 = 0;
  var_name_tmp__52 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0));
  var_name_tmp__51 = var_name_tmp__52;
  var_name_tmp__53 = var_name_tmp__51;
  var_name_tmp__51 = (var_name_tmp__53 & -249);
  var_name_tmp__54 = var_name_tmp__50;
  var_name_tmp__55 = var_name_tmp__51;
  var_name_tmp__51 = (var_name_tmp__55 | ((((uint32_t)(uint8_t)var_name_tmp__54)) << 3));
  var_name_tmp__56 = var_name_tmp__51;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field0)) = var_name_tmp__56;
}


void RCC_HSICmd(uint32_t var_name_tmp__57) {
  uint32_t var_name_tmp__58;    /* Address-exposed local */
  uint32_t var_name_tmp__59;

  var_name_tmp__58 = var_name_tmp__57;
  var_name_tmp__59 = var_name_tmp__58;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111949312)) = var_name_tmp__59;
}


void RCC_LSEConfig(uint8_t var_name_tmp__60) {
  uint8_t var_name_tmp__61;    /* Address-exposed local */
  uint8_t var_name_tmp__62;

  var_name_tmp__61 = var_name_tmp__60;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887344)) = 0;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887344)) = 0;
  var_name_tmp__62 = var_name_tmp__61;
  switch ((((uint32_t)(uint8_t)var_name_tmp__62))) {
  default:
    goto var_name_tmp__63;
  case 1u:
    goto var_name_tmp__64;
  case 4u:
    goto var_name_tmp__65;
  }

var_name_tmp__64:
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887344)) = 1;
  goto var_name_tmp__66;

var_name_tmp__65:
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887344)) = 5;
  goto var_name_tmp__66;

var_name_tmp__63:
  goto var_name_tmp__66;

var_name_tmp__66:
  return;
}


void RCC_LSICmd(uint32_t var_name_tmp__67) {
  uint32_t var_name_tmp__68;    /* Address-exposed local */
  uint32_t var_name_tmp__69;

  var_name_tmp__68 = var_name_tmp__67;
  var_name_tmp__69 = var_name_tmp__68;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111953024)) = var_name_tmp__69;
}


void RCC_PLLConfig(uint32_t var_name_tmp__70, uint32_t var_name_tmp__71, uint32_t var_name_tmp__72, uint32_t var_name_tmp__73, uint32_t var_name_tmp__74) {
  uint32_t var_name_tmp__75;    /* Address-exposed local */
  uint32_t var_name_tmp__76;    /* Address-exposed local */
  uint32_t var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;    /* Address-exposed local */
  uint32_t var_name_tmp__79;    /* Address-exposed local */
  uint32_t var_name_tmp__80;
  uint32_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;

  var_name_tmp__75 = var_name_tmp__70;
  var_name_tmp__76 = var_name_tmp__71;
  var_name_tmp__77 = var_name_tmp__72;
  var_name_tmp__78 = var_name_tmp__73;
  var_name_tmp__79 = var_name_tmp__74;
  var_name_tmp__80 = var_name_tmp__76;
  var_name_tmp__81 = var_name_tmp__77;
  var_name_tmp__82 = var_name_tmp__78;
  var_name_tmp__83 = var_name_tmp__75;
  var_name_tmp__84 = var_name_tmp__79;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1)) = ((((var_name_tmp__80 | (var_name_tmp__81 << 6)) | ((llvm_sub_u32((llvm_lshr_u32(var_name_tmp__82, 1)), 1)) << 16)) | var_name_tmp__83) | (var_name_tmp__84 << 24));
}


void RCC_PLLCmd(uint32_t var_name_tmp__85) {
  uint32_t var_name_tmp__86;    /* Address-exposed local */
  uint32_t var_name_tmp__87;

  var_name_tmp__86 = var_name_tmp__85;
  var_name_tmp__87 = var_name_tmp__86;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111949408)) = var_name_tmp__87;
}


void RCC_PLLI2SConfig(uint32_t var_name_tmp__88, uint32_t var_name_tmp__89) {
  uint32_t var_name_tmp__90;    /* Address-exposed local */
  uint32_t var_name_tmp__91;    /* Address-exposed local */
  uint32_t var_name_tmp__92;
  uint32_t var_name_tmp__93;

  var_name_tmp__90 = var_name_tmp__88;
  var_name_tmp__91 = var_name_tmp__89;
  var_name_tmp__92 = var_name_tmp__90;
  var_name_tmp__93 = var_name_tmp__91;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29)) = ((var_name_tmp__92 << 6) | (var_name_tmp__93 << 28));
}


void RCC_PLLI2SCmd(uint32_t var_name_tmp__94) {
  uint32_t var_name_tmp__95;    /* Address-exposed local */
  uint32_t var_name_tmp__96;

  var_name_tmp__95 = var_name_tmp__94;
  var_name_tmp__96 = var_name_tmp__95;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111949416)) = var_name_tmp__96;
}


void RCC_ClockSecuritySystemCmd(uint32_t var_name_tmp__97) {
  uint32_t var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;

  var_name_tmp__98 = var_name_tmp__97;
  var_name_tmp__99 = var_name_tmp__98;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111949388)) = var_name_tmp__99;
}


void RCC_MCO1Config(uint32_t var_name_tmp__100, uint32_t var_name_tmp__101) {
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  uint32_t var_name_tmp__103;    /* Address-exposed local */
  uint32_t var_name_tmp__104;    /* Address-exposed local */
  uint32_t var_name_tmp__105;
  uint32_t var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  uint32_t var_name_tmp__109;
  uint32_t var_name_tmp__110;

  var_name_tmp__102 = var_name_tmp__100;
  var_name_tmp__103 = var_name_tmp__101;
  var_name_tmp__104 = 0;
  var_name_tmp__105 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__104 = var_name_tmp__105;
  var_name_tmp__106 = var_name_tmp__104;
  var_name_tmp__104 = (var_name_tmp__106 & -123731969);
  var_name_tmp__107 = var_name_tmp__102;
  var_name_tmp__108 = var_name_tmp__103;
  var_name_tmp__109 = var_name_tmp__104;
  var_name_tmp__104 = (var_name_tmp__109 | (var_name_tmp__107 | var_name_tmp__108));
  var_name_tmp__110 = var_name_tmp__104;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__110;
}


void RCC_MCO2Config(uint32_t var_name_tmp__111, uint32_t var_name_tmp__112) {
  uint32_t var_name_tmp__113;    /* Address-exposed local */
  uint32_t var_name_tmp__114;    /* Address-exposed local */
  uint32_t var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;
  uint32_t var_name_tmp__117;
  uint32_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint32_t var_name_tmp__120;
  uint32_t var_name_tmp__121;

  var_name_tmp__113 = var_name_tmp__111;
  var_name_tmp__114 = var_name_tmp__112;
  var_name_tmp__115 = 0;
  var_name_tmp__116 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__115 = var_name_tmp__116;
  var_name_tmp__117 = var_name_tmp__115;
  var_name_tmp__115 = (var_name_tmp__117 & 134217727);
  var_name_tmp__118 = var_name_tmp__113;
  var_name_tmp__119 = var_name_tmp__114;
  var_name_tmp__120 = var_name_tmp__115;
  var_name_tmp__115 = (var_name_tmp__120 | (var_name_tmp__118 | var_name_tmp__119));
  var_name_tmp__121 = var_name_tmp__115;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__121;
}


void RCC_SYSCLKConfig(uint32_t var_name_tmp__122) {
  uint32_t var_name_tmp__123;    /* Address-exposed local */
  uint32_t var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;
  uint32_t var_name_tmp__126;
  uint32_t var_name_tmp__127;
  uint32_t var_name_tmp__128;
  uint32_t var_name_tmp__129;

  var_name_tmp__123 = var_name_tmp__122;
  var_name_tmp__124 = 0;
  var_name_tmp__125 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__124 = var_name_tmp__125;
  var_name_tmp__126 = var_name_tmp__124;
  var_name_tmp__124 = (var_name_tmp__126 & -4);
  var_name_tmp__127 = var_name_tmp__123;
  var_name_tmp__128 = var_name_tmp__124;
  var_name_tmp__124 = (var_name_tmp__128 | var_name_tmp__127);
  var_name_tmp__129 = var_name_tmp__124;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__129;
}


uint8_t RCC_GetSYSCLKSource(void) {
  uint32_t var_name_tmp__130;

  var_name_tmp__130 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  return (((uint8_t)(var_name_tmp__130 & 12)));
}


void RCC_HCLKConfig(uint32_t var_name_tmp__131) {
  uint32_t var_name_tmp__132;    /* Address-exposed local */
  uint32_t var_name_tmp__133;    /* Address-exposed local */
  uint32_t var_name_tmp__134;
  uint32_t var_name_tmp__135;
  uint32_t var_name_tmp__136;
  uint32_t var_name_tmp__137;
  uint32_t var_name_tmp__138;

  var_name_tmp__132 = var_name_tmp__131;
  var_name_tmp__133 = 0;
  var_name_tmp__134 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__133 = var_name_tmp__134;
  var_name_tmp__135 = var_name_tmp__133;
  var_name_tmp__133 = (var_name_tmp__135 & -241);
  var_name_tmp__136 = var_name_tmp__132;
  var_name_tmp__137 = var_name_tmp__133;
  var_name_tmp__133 = (var_name_tmp__137 | var_name_tmp__136);
  var_name_tmp__138 = var_name_tmp__133;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__138;
}


void RCC_PCLK1Config(uint32_t var_name_tmp__139) {
  uint32_t var_name_tmp__140;    /* Address-exposed local */
  uint32_t var_name_tmp__141;    /* Address-exposed local */
  uint32_t var_name_tmp__142;
  uint32_t var_name_tmp__143;
  uint32_t var_name_tmp__144;
  uint32_t var_name_tmp__145;
  uint32_t var_name_tmp__146;

  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = 0;
  var_name_tmp__142 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__141 = var_name_tmp__142;
  var_name_tmp__143 = var_name_tmp__141;
  var_name_tmp__141 = (var_name_tmp__143 & -7169);
  var_name_tmp__144 = var_name_tmp__140;
  var_name_tmp__145 = var_name_tmp__141;
  var_name_tmp__141 = (var_name_tmp__145 | var_name_tmp__144);
  var_name_tmp__146 = var_name_tmp__141;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__146;
}


void RCC_PCLK2Config(uint32_t var_name_tmp__147) {
  uint32_t var_name_tmp__148;    /* Address-exposed local */
  uint32_t var_name_tmp__149;    /* Address-exposed local */
  uint32_t var_name_tmp__150;
  uint32_t var_name_tmp__151;
  uint32_t var_name_tmp__152;
  uint32_t var_name_tmp__153;
  uint32_t var_name_tmp__154;

  var_name_tmp__148 = var_name_tmp__147;
  var_name_tmp__149 = 0;
  var_name_tmp__150 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__149 = var_name_tmp__150;
  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__149 = (var_name_tmp__151 & -57345);
  var_name_tmp__152 = var_name_tmp__148;
  var_name_tmp__153 = var_name_tmp__149;
  var_name_tmp__149 = (var_name_tmp__153 | (var_name_tmp__152 << 3));
  var_name_tmp__154 = var_name_tmp__149;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__154;
}


void RCC_GetClocksFreq(struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__155) {
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__156;    /* Address-exposed local */
  uint32_t var_name_tmp__157;    /* Address-exposed local */
  uint32_t var_name_tmp__158;    /* Address-exposed local */
  uint32_t var_name_tmp__159;    /* Address-exposed local */
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;    /* Address-exposed local */
  uint32_t var_name_tmp__162;    /* Address-exposed local */
  uint32_t var_name_tmp__163;
  uint32_t var_name_tmp__164;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__165;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__166;
  uint32_t var_name_tmp__167;
  uint32_t var_name_tmp__168;
  uint32_t var_name_tmp__169;
  uint32_t var_name_tmp__170;
  uint32_t var_name_tmp__171;
  uint32_t var_name_tmp__172;
  uint32_t var_name_tmp__173;
  uint32_t var_name_tmp__174;
  uint32_t var_name_tmp__175;
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__177;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__178;
  uint32_t var_name_tmp__179;
  uint32_t var_name_tmp__180;
  uint32_t var_name_tmp__181;
  uint8_t var_name_tmp__182;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__183;
  uint32_t var_name_tmp__184;
  uint32_t var_name_tmp__185;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__186;
  uint32_t var_name_tmp__187;
  uint32_t var_name_tmp__188;
  uint32_t var_name_tmp__189;
  uint8_t var_name_tmp__190;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__191;
  uint32_t var_name_tmp__192;
  uint32_t var_name_tmp__193;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__194;
  uint32_t var_name_tmp__195;
  uint32_t var_name_tmp__196;
  uint32_t var_name_tmp__197;
  uint8_t var_name_tmp__198;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__199;
  uint32_t var_name_tmp__200;
  uint32_t var_name_tmp__201;
  struct l_struct_struct_OC_RCC_ClocksTypeDef* var_name_tmp__202;

  var_name_tmp__156 = var_name_tmp__155;
  var_name_tmp__157 = 0;
  var_name_tmp__158 = 0;
  var_name_tmp__159 = 0;
  var_name_tmp__160 = 2;
  var_name_tmp__161 = 0;
  var_name_tmp__162 = 2;
  var_name_tmp__163 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__157 = (var_name_tmp__163 & 12);
  var_name_tmp__164 = var_name_tmp__157;
  switch (var_name_tmp__164) {
  default:
    goto var_name_tmp__203;
  case 0u:
    goto var_name_tmp__204;
  case 4u:
    goto var_name_tmp__205;
  case 8u:
    goto var_name_tmp__206;
  }

var_name_tmp__204:
  var_name_tmp__165 = var_name_tmp__156;
  *((&var_name_tmp__165->field0)) = 16000000;
  goto var_name_tmp__207;

var_name_tmp__205:
  var_name_tmp__166 = var_name_tmp__156;
  *((&var_name_tmp__166->field0)) = 8000000;
  goto var_name_tmp__207;

var_name_tmp__206:
  var_name_tmp__167 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__161 = (llvm_lshr_u32((var_name_tmp__167 & 4194304), 22));
  var_name_tmp__168 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__162 = (var_name_tmp__168 & 63);
  var_name_tmp__169 = var_name_tmp__161;
  if ((((var_name_tmp__169 != 0u)&1))) {
    goto var_name_tmp__208;
  } else {
    goto var_name_tmp__209;
  }

var_name_tmp__208:
  var_name_tmp__170 = var_name_tmp__162;
  var_name_tmp__171 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__159 = (llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__170)), (llvm_lshr_u32((var_name_tmp__171 & 32704), 6))));
  goto var_name_tmp__210;

var_name_tmp__209:
  var_name_tmp__172 = var_name_tmp__162;
  var_name_tmp__173 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__159 = (llvm_mul_u32((llvm_udiv_u32(16000000, var_name_tmp__172)), (llvm_lshr_u32((var_name_tmp__173 & 32704), 6))));
  goto var_name_tmp__210;

var_name_tmp__210:
  var_name_tmp__174 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__160 = (llvm_mul_u32((llvm_add_u32((llvm_lshr_u32((var_name_tmp__174 & 196608), 16)), 1)), 2));
  var_name_tmp__175 = var_name_tmp__159;
  var_name_tmp__176 = var_name_tmp__160;
  var_name_tmp__177 = var_name_tmp__156;
  *((&var_name_tmp__177->field0)) = (llvm_udiv_u32(var_name_tmp__175, var_name_tmp__176));
  goto var_name_tmp__207;

var_name_tmp__203:
  var_name_tmp__178 = var_name_tmp__156;
  *((&var_name_tmp__178->field0)) = 16000000;
  goto var_name_tmp__207;

var_name_tmp__207:
  var_name_tmp__179 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__157 = (var_name_tmp__179 & 240);
  var_name_tmp__180 = var_name_tmp__157;
  var_name_tmp__157 = (llvm_lshr_u32(var_name_tmp__180, 4));
  var_name_tmp__181 = var_name_tmp__157;
  var_name_tmp__182 = *(volatile uint8_t*)((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__181)))]));
  var_name_tmp__158 = (((uint32_t)(uint8_t)var_name_tmp__182));
  var_name_tmp__183 = var_name_tmp__156;
  var_name_tmp__184 = *((&var_name_tmp__183->field0));
  var_name_tmp__185 = var_name_tmp__158;
  var_name_tmp__186 = var_name_tmp__156;
  *((&var_name_tmp__186->field1)) = (llvm_lshr_u32(var_name_tmp__184, var_name_tmp__185));
  var_name_tmp__187 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__157 = (var_name_tmp__187 & 7168);
  var_name_tmp__188 = var_name_tmp__157;
  var_name_tmp__157 = (llvm_lshr_u32(var_name_tmp__188, 10));
  var_name_tmp__189 = var_name_tmp__157;
  var_name_tmp__190 = *(volatile uint8_t*)((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__189)))]));
  var_name_tmp__158 = (((uint32_t)(uint8_t)var_name_tmp__190));
  var_name_tmp__191 = var_name_tmp__156;
  var_name_tmp__192 = *((&var_name_tmp__191->field1));
  var_name_tmp__193 = var_name_tmp__158;
  var_name_tmp__194 = var_name_tmp__156;
  *((&var_name_tmp__194->field2)) = (llvm_lshr_u32(var_name_tmp__192, var_name_tmp__193));
  var_name_tmp__195 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__157 = (var_name_tmp__195 & 57344);
  var_name_tmp__196 = var_name_tmp__157;
  var_name_tmp__157 = (llvm_lshr_u32(var_name_tmp__196, 13));
  var_name_tmp__197 = var_name_tmp__157;
  var_name_tmp__198 = *(volatile uint8_t*)((&APBAHBPrescTable.array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__197)))]));
  var_name_tmp__158 = (((uint32_t)(uint8_t)var_name_tmp__198));
  var_name_tmp__199 = var_name_tmp__156;
  var_name_tmp__200 = *((&var_name_tmp__199->field1));
  var_name_tmp__201 = var_name_tmp__158;
  var_name_tmp__202 = var_name_tmp__156;
  *((&var_name_tmp__202->field3)) = (llvm_lshr_u32(var_name_tmp__200, var_name_tmp__201));
}


void RCC_RTCCLKConfig(uint32_t var_name_tmp__211) {
  uint32_t var_name_tmp__212;    /* Address-exposed local */
  uint32_t var_name_tmp__213;    /* Address-exposed local */
  uint32_t var_name_tmp__214;
  uint32_t var_name_tmp__215;
  uint32_t var_name_tmp__216;
  uint32_t var_name_tmp__217;
  uint32_t var_name_tmp__218;
  uint32_t var_name_tmp__219;
  uint32_t var_name_tmp__220;
  uint32_t var_name_tmp__221;

  var_name_tmp__212 = var_name_tmp__211;
  var_name_tmp__213 = 0;
  var_name_tmp__214 = var_name_tmp__212;
  if (((((var_name_tmp__214 & 768) == 768u)&1))) {
    goto var_name_tmp__222;
  } else {
    goto var_name_tmp__223;
  }

var_name_tmp__222:
  var_name_tmp__215 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  var_name_tmp__213 = var_name_tmp__215;
  var_name_tmp__216 = var_name_tmp__213;
  var_name_tmp__213 = (var_name_tmp__216 & -2031617);
  var_name_tmp__217 = var_name_tmp__212;
  var_name_tmp__218 = var_name_tmp__213;
  var_name_tmp__213 = (var_name_tmp__218 | (var_name_tmp__217 & 268434687));
  var_name_tmp__219 = var_name_tmp__213;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = var_name_tmp__219;
  goto var_name_tmp__223;

var_name_tmp__223:
  var_name_tmp__220 = var_name_tmp__212;
  var_name_tmp__221 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field25)) = (var_name_tmp__221 | (var_name_tmp__220 & 4095));
}


void RCC_RTCCLKCmd(uint32_t var_name_tmp__224) {
  uint32_t var_name_tmp__225;    /* Address-exposed local */
  uint32_t var_name_tmp__226;

  var_name_tmp__225 = var_name_tmp__224;
  var_name_tmp__226 = var_name_tmp__225;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111952956)) = var_name_tmp__226;
}


void RCC_BackupResetCmd(uint32_t var_name_tmp__227) {
  uint32_t var_name_tmp__228;    /* Address-exposed local */
  uint32_t var_name_tmp__229;

  var_name_tmp__228 = var_name_tmp__227;
  var_name_tmp__229 = var_name_tmp__228;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111952960)) = var_name_tmp__229;
}


void RCC_I2SCLKConfig(uint32_t var_name_tmp__230) {
  uint32_t var_name_tmp__231;    /* Address-exposed local */
  uint32_t var_name_tmp__232;

  var_name_tmp__231 = var_name_tmp__230;
  var_name_tmp__232 = var_name_tmp__231;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1111949660)) = var_name_tmp__232;
}


void RCC_AHB1PeriphClockCmd(uint32_t var_name_tmp__233, uint32_t var_name_tmp__234) {
  uint32_t var_name_tmp__235;    /* Address-exposed local */
  uint32_t var_name_tmp__236;    /* Address-exposed local */
  uint32_t var_name_tmp__237;
  uint32_t var_name_tmp__238;
  uint32_t var_name_tmp__239;
  uint32_t var_name_tmp__240;
  uint32_t var_name_tmp__241;

  var_name_tmp__235 = var_name_tmp__233;
  var_name_tmp__236 = var_name_tmp__234;
  var_name_tmp__237 = var_name_tmp__236;
  if ((((var_name_tmp__237 != 0u)&1))) {
    goto var_name_tmp__242;
  } else {
    goto var_name_tmp__243;
  }

var_name_tmp__242:
  var_name_tmp__238 = var_name_tmp__235;
  var_name_tmp__239 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11)) = (var_name_tmp__239 | var_name_tmp__238);
  goto var_name_tmp__244;

var_name_tmp__243:
  var_name_tmp__240 = var_name_tmp__235;
  var_name_tmp__241 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field11)) = (var_name_tmp__241 & (~(var_name_tmp__240)));
  goto var_name_tmp__244;

var_name_tmp__244:
  return;
}


void RCC_AHB2PeriphClockCmd(uint32_t var_name_tmp__245, uint32_t var_name_tmp__246) {
  uint32_t var_name_tmp__247;    /* Address-exposed local */
  uint32_t var_name_tmp__248;    /* Address-exposed local */
  uint32_t var_name_tmp__249;
  uint32_t var_name_tmp__250;
  uint32_t var_name_tmp__251;
  uint32_t var_name_tmp__252;
  uint32_t var_name_tmp__253;

  var_name_tmp__247 = var_name_tmp__245;
  var_name_tmp__248 = var_name_tmp__246;
  var_name_tmp__249 = var_name_tmp__248;
  if ((((var_name_tmp__249 != 0u)&1))) {
    goto var_name_tmp__254;
  } else {
    goto var_name_tmp__255;
  }

var_name_tmp__254:
  var_name_tmp__250 = var_name_tmp__247;
  var_name_tmp__251 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12)) = (var_name_tmp__251 | var_name_tmp__250);
  goto var_name_tmp__256;

var_name_tmp__255:
  var_name_tmp__252 = var_name_tmp__247;
  var_name_tmp__253 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field12)) = (var_name_tmp__253 & (~(var_name_tmp__252)));
  goto var_name_tmp__256;

var_name_tmp__256:
  return;
}


void RCC_AHB3PeriphClockCmd(uint32_t var_name_tmp__257, uint32_t var_name_tmp__258) {
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  uint32_t var_name_tmp__260;    /* Address-exposed local */
  uint32_t var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint32_t var_name_tmp__263;
  uint32_t var_name_tmp__264;
  uint32_t var_name_tmp__265;

  var_name_tmp__259 = var_name_tmp__257;
  var_name_tmp__260 = var_name_tmp__258;
  var_name_tmp__261 = var_name_tmp__260;
  if ((((var_name_tmp__261 != 0u)&1))) {
    goto var_name_tmp__266;
  } else {
    goto var_name_tmp__267;
  }

var_name_tmp__266:
  var_name_tmp__262 = var_name_tmp__259;
  var_name_tmp__263 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13)) = (var_name_tmp__263 | var_name_tmp__262);
  goto var_name_tmp__268;

var_name_tmp__267:
  var_name_tmp__264 = var_name_tmp__259;
  var_name_tmp__265 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field13)) = (var_name_tmp__265 & (~(var_name_tmp__264)));
  goto var_name_tmp__268;

var_name_tmp__268:
  return;
}


void RCC_APB1PeriphClockCmd(uint32_t var_name_tmp__269, uint32_t var_name_tmp__270) {
  uint32_t var_name_tmp__271;    /* Address-exposed local */
  uint32_t var_name_tmp__272;    /* Address-exposed local */
  uint32_t var_name_tmp__273;
  uint32_t var_name_tmp__274;
  uint32_t var_name_tmp__275;
  uint32_t var_name_tmp__276;
  uint32_t var_name_tmp__277;

  var_name_tmp__271 = var_name_tmp__269;
  var_name_tmp__272 = var_name_tmp__270;
  var_name_tmp__273 = var_name_tmp__272;
  if ((((var_name_tmp__273 != 0u)&1))) {
    goto var_name_tmp__278;
  } else {
    goto var_name_tmp__279;
  }

var_name_tmp__278:
  var_name_tmp__274 = var_name_tmp__271;
  var_name_tmp__275 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15)) = (var_name_tmp__275 | var_name_tmp__274);
  goto var_name_tmp__280;

var_name_tmp__279:
  var_name_tmp__276 = var_name_tmp__271;
  var_name_tmp__277 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field15)) = (var_name_tmp__277 & (~(var_name_tmp__276)));
  goto var_name_tmp__280;

var_name_tmp__280:
  return;
}


void RCC_APB2PeriphClockCmd(uint32_t var_name_tmp__281, uint32_t var_name_tmp__282) {
  uint32_t var_name_tmp__283;    /* Address-exposed local */
  uint32_t var_name_tmp__284;    /* Address-exposed local */
  uint32_t var_name_tmp__285;
  uint32_t var_name_tmp__286;
  uint32_t var_name_tmp__287;
  uint32_t var_name_tmp__288;
  uint32_t var_name_tmp__289;

  var_name_tmp__283 = var_name_tmp__281;
  var_name_tmp__284 = var_name_tmp__282;
  var_name_tmp__285 = var_name_tmp__284;
  if ((((var_name_tmp__285 != 0u)&1))) {
    goto var_name_tmp__290;
  } else {
    goto var_name_tmp__291;
  }

var_name_tmp__290:
  var_name_tmp__286 = var_name_tmp__283;
  var_name_tmp__287 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16)) = (var_name_tmp__287 | var_name_tmp__286);
  goto var_name_tmp__292;

var_name_tmp__291:
  var_name_tmp__288 = var_name_tmp__283;
  var_name_tmp__289 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field16)) = (var_name_tmp__289 & (~(var_name_tmp__288)));
  goto var_name_tmp__292;

var_name_tmp__292:
  return;
}


void RCC_AHB1PeriphResetCmd(uint32_t var_name_tmp__293, uint32_t var_name_tmp__294) {
  uint32_t var_name_tmp__295;    /* Address-exposed local */
  uint32_t var_name_tmp__296;    /* Address-exposed local */
  uint32_t var_name_tmp__297;
  uint32_t var_name_tmp__298;
  uint32_t var_name_tmp__299;
  uint32_t var_name_tmp__300;
  uint32_t var_name_tmp__301;

  var_name_tmp__295 = var_name_tmp__293;
  var_name_tmp__296 = var_name_tmp__294;
  var_name_tmp__297 = var_name_tmp__296;
  if ((((var_name_tmp__297 != 0u)&1))) {
    goto var_name_tmp__302;
  } else {
    goto var_name_tmp__303;
  }

var_name_tmp__302:
  var_name_tmp__298 = var_name_tmp__295;
  var_name_tmp__299 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4)) = (var_name_tmp__299 | var_name_tmp__298);
  goto var_name_tmp__304;

var_name_tmp__303:
  var_name_tmp__300 = var_name_tmp__295;
  var_name_tmp__301 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field4)) = (var_name_tmp__301 & (~(var_name_tmp__300)));
  goto var_name_tmp__304;

var_name_tmp__304:
  return;
}


void RCC_AHB2PeriphResetCmd(uint32_t var_name_tmp__305, uint32_t var_name_tmp__306) {
  uint32_t var_name_tmp__307;    /* Address-exposed local */
  uint32_t var_name_tmp__308;    /* Address-exposed local */
  uint32_t var_name_tmp__309;
  uint32_t var_name_tmp__310;
  uint32_t var_name_tmp__311;
  uint32_t var_name_tmp__312;
  uint32_t var_name_tmp__313;

  var_name_tmp__307 = var_name_tmp__305;
  var_name_tmp__308 = var_name_tmp__306;
  var_name_tmp__309 = var_name_tmp__308;
  if ((((var_name_tmp__309 != 0u)&1))) {
    goto var_name_tmp__314;
  } else {
    goto var_name_tmp__315;
  }

var_name_tmp__314:
  var_name_tmp__310 = var_name_tmp__307;
  var_name_tmp__311 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5)) = (var_name_tmp__311 | var_name_tmp__310);
  goto var_name_tmp__316;

var_name_tmp__315:
  var_name_tmp__312 = var_name_tmp__307;
  var_name_tmp__313 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field5)) = (var_name_tmp__313 & (~(var_name_tmp__312)));
  goto var_name_tmp__316;

var_name_tmp__316:
  return;
}


void RCC_AHB3PeriphResetCmd(uint32_t var_name_tmp__317, uint32_t var_name_tmp__318) {
  uint32_t var_name_tmp__319;    /* Address-exposed local */
  uint32_t var_name_tmp__320;    /* Address-exposed local */
  uint32_t var_name_tmp__321;
  uint32_t var_name_tmp__322;
  uint32_t var_name_tmp__323;
  uint32_t var_name_tmp__324;
  uint32_t var_name_tmp__325;

  var_name_tmp__319 = var_name_tmp__317;
  var_name_tmp__320 = var_name_tmp__318;
  var_name_tmp__321 = var_name_tmp__320;
  if ((((var_name_tmp__321 != 0u)&1))) {
    goto var_name_tmp__326;
  } else {
    goto var_name_tmp__327;
  }

var_name_tmp__326:
  var_name_tmp__322 = var_name_tmp__319;
  var_name_tmp__323 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6)) = (var_name_tmp__323 | var_name_tmp__322);
  goto var_name_tmp__328;

var_name_tmp__327:
  var_name_tmp__324 = var_name_tmp__319;
  var_name_tmp__325 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field6)) = (var_name_tmp__325 & (~(var_name_tmp__324)));
  goto var_name_tmp__328;

var_name_tmp__328:
  return;
}


void RCC_APB1PeriphResetCmd(uint32_t var_name_tmp__329, uint32_t var_name_tmp__330) {
  uint32_t var_name_tmp__331;    /* Address-exposed local */
  uint32_t var_name_tmp__332;    /* Address-exposed local */
  uint32_t var_name_tmp__333;
  uint32_t var_name_tmp__334;
  uint32_t var_name_tmp__335;
  uint32_t var_name_tmp__336;
  uint32_t var_name_tmp__337;

  var_name_tmp__331 = var_name_tmp__329;
  var_name_tmp__332 = var_name_tmp__330;
  var_name_tmp__333 = var_name_tmp__332;
  if ((((var_name_tmp__333 != 0u)&1))) {
    goto var_name_tmp__338;
  } else {
    goto var_name_tmp__339;
  }

var_name_tmp__338:
  var_name_tmp__334 = var_name_tmp__331;
  var_name_tmp__335 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8)) = (var_name_tmp__335 | var_name_tmp__334);
  goto var_name_tmp__340;

var_name_tmp__339:
  var_name_tmp__336 = var_name_tmp__331;
  var_name_tmp__337 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field8)) = (var_name_tmp__337 & (~(var_name_tmp__336)));
  goto var_name_tmp__340;

var_name_tmp__340:
  return;
}


void RCC_APB2PeriphResetCmd(uint32_t var_name_tmp__341, uint32_t var_name_tmp__342) {
  uint32_t var_name_tmp__343;    /* Address-exposed local */
  uint32_t var_name_tmp__344;    /* Address-exposed local */
  uint32_t var_name_tmp__345;
  uint32_t var_name_tmp__346;
  uint32_t var_name_tmp__347;
  uint32_t var_name_tmp__348;
  uint32_t var_name_tmp__349;

  var_name_tmp__343 = var_name_tmp__341;
  var_name_tmp__344 = var_name_tmp__342;
  var_name_tmp__345 = var_name_tmp__344;
  if ((((var_name_tmp__345 != 0u)&1))) {
    goto var_name_tmp__350;
  } else {
    goto var_name_tmp__351;
  }

var_name_tmp__350:
  var_name_tmp__346 = var_name_tmp__343;
  var_name_tmp__347 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9)) = (var_name_tmp__347 | var_name_tmp__346);
  goto var_name_tmp__352;

var_name_tmp__351:
  var_name_tmp__348 = var_name_tmp__343;
  var_name_tmp__349 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field9)) = (var_name_tmp__349 & (~(var_name_tmp__348)));
  goto var_name_tmp__352;

var_name_tmp__352:
  return;
}


void RCC_AHB1PeriphClockLPModeCmd(uint32_t var_name_tmp__353, uint32_t var_name_tmp__354) {
  uint32_t var_name_tmp__355;    /* Address-exposed local */
  uint32_t var_name_tmp__356;    /* Address-exposed local */
  uint32_t var_name_tmp__357;
  uint32_t var_name_tmp__358;
  uint32_t var_name_tmp__359;
  uint32_t var_name_tmp__360;
  uint32_t var_name_tmp__361;

  var_name_tmp__355 = var_name_tmp__353;
  var_name_tmp__356 = var_name_tmp__354;
  var_name_tmp__357 = var_name_tmp__356;
  if ((((var_name_tmp__357 != 0u)&1))) {
    goto var_name_tmp__362;
  } else {
    goto var_name_tmp__363;
  }

var_name_tmp__362:
  var_name_tmp__358 = var_name_tmp__355;
  var_name_tmp__359 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18)) = (var_name_tmp__359 | var_name_tmp__358);
  goto var_name_tmp__364;

var_name_tmp__363:
  var_name_tmp__360 = var_name_tmp__355;
  var_name_tmp__361 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field18)) = (var_name_tmp__361 & (~(var_name_tmp__360)));
  goto var_name_tmp__364;

var_name_tmp__364:
  return;
}


void RCC_AHB2PeriphClockLPModeCmd(uint32_t var_name_tmp__365, uint32_t var_name_tmp__366) {
  uint32_t var_name_tmp__367;    /* Address-exposed local */
  uint32_t var_name_tmp__368;    /* Address-exposed local */
  uint32_t var_name_tmp__369;
  uint32_t var_name_tmp__370;
  uint32_t var_name_tmp__371;
  uint32_t var_name_tmp__372;
  uint32_t var_name_tmp__373;

  var_name_tmp__367 = var_name_tmp__365;
  var_name_tmp__368 = var_name_tmp__366;
  var_name_tmp__369 = var_name_tmp__368;
  if ((((var_name_tmp__369 != 0u)&1))) {
    goto var_name_tmp__374;
  } else {
    goto var_name_tmp__375;
  }

var_name_tmp__374:
  var_name_tmp__370 = var_name_tmp__367;
  var_name_tmp__371 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19)) = (var_name_tmp__371 | var_name_tmp__370);
  goto var_name_tmp__376;

var_name_tmp__375:
  var_name_tmp__372 = var_name_tmp__367;
  var_name_tmp__373 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field19)) = (var_name_tmp__373 & (~(var_name_tmp__372)));
  goto var_name_tmp__376;

var_name_tmp__376:
  return;
}


void RCC_AHB3PeriphClockLPModeCmd(uint32_t var_name_tmp__377, uint32_t var_name_tmp__378) {
  uint32_t var_name_tmp__379;    /* Address-exposed local */
  uint32_t var_name_tmp__380;    /* Address-exposed local */
  uint32_t var_name_tmp__381;
  uint32_t var_name_tmp__382;
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint32_t var_name_tmp__385;

  var_name_tmp__379 = var_name_tmp__377;
  var_name_tmp__380 = var_name_tmp__378;
  var_name_tmp__381 = var_name_tmp__380;
  if ((((var_name_tmp__381 != 0u)&1))) {
    goto var_name_tmp__386;
  } else {
    goto var_name_tmp__387;
  }

var_name_tmp__386:
  var_name_tmp__382 = var_name_tmp__379;
  var_name_tmp__383 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20)) = (var_name_tmp__383 | var_name_tmp__382);
  goto var_name_tmp__388;

var_name_tmp__387:
  var_name_tmp__384 = var_name_tmp__379;
  var_name_tmp__385 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field20)) = (var_name_tmp__385 & (~(var_name_tmp__384)));
  goto var_name_tmp__388;

var_name_tmp__388:
  return;
}


void RCC_APB1PeriphClockLPModeCmd(uint32_t var_name_tmp__389, uint32_t var_name_tmp__390) {
  uint32_t var_name_tmp__391;    /* Address-exposed local */
  uint32_t var_name_tmp__392;    /* Address-exposed local */
  uint32_t var_name_tmp__393;
  uint32_t var_name_tmp__394;
  uint32_t var_name_tmp__395;
  uint32_t var_name_tmp__396;
  uint32_t var_name_tmp__397;

  var_name_tmp__391 = var_name_tmp__389;
  var_name_tmp__392 = var_name_tmp__390;
  var_name_tmp__393 = var_name_tmp__392;
  if ((((var_name_tmp__393 != 0u)&1))) {
    goto var_name_tmp__398;
  } else {
    goto var_name_tmp__399;
  }

var_name_tmp__398:
  var_name_tmp__394 = var_name_tmp__391;
  var_name_tmp__395 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22)) = (var_name_tmp__395 | var_name_tmp__394);
  goto var_name_tmp__400;

var_name_tmp__399:
  var_name_tmp__396 = var_name_tmp__391;
  var_name_tmp__397 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field22)) = (var_name_tmp__397 & (~(var_name_tmp__396)));
  goto var_name_tmp__400;

var_name_tmp__400:
  return;
}


void RCC_APB2PeriphClockLPModeCmd(uint32_t var_name_tmp__401, uint32_t var_name_tmp__402) {
  uint32_t var_name_tmp__403;    /* Address-exposed local */
  uint32_t var_name_tmp__404;    /* Address-exposed local */
  uint32_t var_name_tmp__405;
  uint32_t var_name_tmp__406;
  uint32_t var_name_tmp__407;
  uint32_t var_name_tmp__408;
  uint32_t var_name_tmp__409;

  var_name_tmp__403 = var_name_tmp__401;
  var_name_tmp__404 = var_name_tmp__402;
  var_name_tmp__405 = var_name_tmp__404;
  if ((((var_name_tmp__405 != 0u)&1))) {
    goto var_name_tmp__410;
  } else {
    goto var_name_tmp__411;
  }

var_name_tmp__410:
  var_name_tmp__406 = var_name_tmp__403;
  var_name_tmp__407 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23)) = (var_name_tmp__407 | var_name_tmp__406);
  goto var_name_tmp__412;

var_name_tmp__411:
  var_name_tmp__408 = var_name_tmp__403;
  var_name_tmp__409 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field23)) = (var_name_tmp__409 & (~(var_name_tmp__408)));
  goto var_name_tmp__412;

var_name_tmp__412:
  return;
}


void RCC_ITConfig(uint8_t var_name_tmp__413, uint32_t var_name_tmp__414) {
  uint8_t var_name_tmp__415;    /* Address-exposed local */
  uint32_t var_name_tmp__416;    /* Address-exposed local */
  uint32_t var_name_tmp__417;
  uint8_t var_name_tmp__418;
  uint8_t var_name_tmp__419;
  uint8_t var_name_tmp__420;
  uint8_t var_name_tmp__421;

  var_name_tmp__415 = var_name_tmp__413;
  var_name_tmp__416 = var_name_tmp__414;
  var_name_tmp__417 = var_name_tmp__416;
  if ((((var_name_tmp__417 != 0u)&1))) {
    goto var_name_tmp__422;
  } else {
    goto var_name_tmp__423;
  }

var_name_tmp__422:
  var_name_tmp__418 = var_name_tmp__415;
  var_name_tmp__419 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887245));
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887245)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__419)) | (((uint32_t)(uint8_t)var_name_tmp__418)))));
  goto var_name_tmp__424;

var_name_tmp__423:
  var_name_tmp__420 = var_name_tmp__415;
  var_name_tmp__421 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887245));
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887245)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__421)) & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__420)))))))))));
  goto var_name_tmp__424;

var_name_tmp__424:
  return;
}


void RCC_ClearFlag(void) {
  uint32_t var_name_tmp__425;

  var_name_tmp__425 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field26)) = (var_name_tmp__425 | 16777216);
}


uint32_t RCC_GetITStatus(uint8_t var_name_tmp__426) {
  uint8_t var_name_tmp__427;    /* Address-exposed local */
  uint32_t var_name_tmp__428;    /* Address-exposed local */
  uint32_t var_name_tmp__429;
  uint8_t var_name_tmp__430;
  uint32_t var_name_tmp__431;

  var_name_tmp__427 = var_name_tmp__426;
  var_name_tmp__428 = 0;
  var_name_tmp__429 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field3));
  var_name_tmp__430 = var_name_tmp__427;
  if (((((var_name_tmp__429 & (((uint32_t)(uint8_t)var_name_tmp__430))) != 0u)&1))) {
    goto var_name_tmp__432;
  } else {
    goto var_name_tmp__433;
  }

var_name_tmp__432:
  var_name_tmp__428 = 1;
  goto var_name_tmp__434;

var_name_tmp__433:
  var_name_tmp__428 = 0;
  goto var_name_tmp__434;

var_name_tmp__434:
  var_name_tmp__431 = var_name_tmp__428;
  return var_name_tmp__431;
}


void RCC_ClearITPendingBit(uint8_t var_name_tmp__435) {
  uint8_t var_name_tmp__436;    /* Address-exposed local */
  uint8_t var_name_tmp__437;

  var_name_tmp__436 = var_name_tmp__435;
  var_name_tmp__437 = var_name_tmp__436;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073887246)) = var_name_tmp__437;
}

