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
struct l_struct_struct_OC_DAC_InitTypeDef;
struct l_struct_struct_OC_DAC_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_DAC_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_DAC_TypeDef {
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
  uint32_t field10;
  uint32_t field11;
  uint32_t field12;
  uint32_t field13;
};

/* Function Declarations */
void DAC_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void DAC_Init(uint32_t, struct l_struct_struct_OC_DAC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_StructInit(struct l_struct_struct_OC_DAC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_Cmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_SoftwareTriggerCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_DualSoftwareTriggerCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_WaveGenerationCmd(uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_SetChannel1Data(uint32_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_SetChannel2Data(uint32_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_SetDualChannelData(uint32_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t DAC_GetDataOutputValue(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_DMACmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_ITConfig(uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DAC_GetFlagStatus(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_ClearFlag(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DAC_GetITStatus(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DAC_ClearITPendingBit(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void DAC_DeInit(void) {
  RCC_APB1PeriphResetCmd(536870912, 1);
  RCC_APB1PeriphResetCmd(536870912, 0);
}


void DAC_Init(uint32_t var_name_tmp__1, struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__2) {
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__4;    /* Address-exposed local */
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint32_t var_name_tmp__6;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__9;
  uint64_t var_name_load_i32_1;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__10;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__11;
  uint64_t var_name_load_i32_7;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__12;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;

  var_name_tmp__3 = var_name_tmp__1;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = 0;
  var_name_tmp__6 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  var_name_tmp__5 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__7 = var_name_tmp__3;
  var_name_tmp__8 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__8 & (~((4094 << var_name_tmp__7))));
  var_name_tmp__9 = var_name_tmp__4;
  var_name_load_i32_1 = __adin_load_((((uint8_t*)((&var_name_tmp__9->field0)))), 32, 4);
  var_name_tmp__10 = var_name_tmp__4;
  var_name_load_i32_4 = __adin_load_((((uint8_t*)((&var_name_tmp__10->field1)))), 32, 4);
  var_name_tmp__11 = var_name_tmp__4;
  var_name_load_i32_7 = __adin_load_((((uint8_t*)((&var_name_tmp__11->field2)))), 32, 4);
  var_name_tmp__12 = var_name_tmp__4;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__12->field3)))), 32, 4);
  var_name_tmp__6 = ((((((uint32_t)var_name_load_i32_1)) | (((uint32_t)var_name_load_i32_4))) | (((uint32_t)var_name_load_i32_7))) | (((uint32_t)var_name_load_i32_10)));
  var_name_tmp__13 = var_name_tmp__6;
  var_name_tmp__14 = var_name_tmp__3;
  var_name_tmp__15 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__15 | (var_name_tmp__13 << var_name_tmp__14));
  var_name_tmp__16 = var_name_tmp__5;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)var_name_tmp__16)), 32, 4);
}


void DAC_StructInit(struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__17) {
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__18;    /* Address-exposed local */
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__19;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__20;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__21;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__22;

  var_name_tmp__18 = var_name_tmp__17;
  var_name_tmp__19 = var_name_tmp__18;
  __adin_store_((((uint8_t*)((&var_name_tmp__19->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__20 = var_name_tmp__18;
  __adin_store_((((uint8_t*)((&var_name_tmp__20->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__21 = var_name_tmp__18;
  __adin_store_((((uint8_t*)((&var_name_tmp__21->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__22 = var_name_tmp__18;
  __adin_store_((((uint8_t*)((&var_name_tmp__22->field3)))), UINT64_C(0), 32, 4);
}


void DAC_Cmd(uint32_t var_name_tmp__23, uint32_t var_name_tmp__24) {
  uint32_t var_name_tmp__25;    /* Address-exposed local */
  uint32_t var_name_tmp__26;    /* Address-exposed local */
  uint32_t var_name_tmp__27;
  uint32_t var_name_tmp__28;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__29;
  uint64_t var_name_load_i32_1;

  var_name_tmp__25 = var_name_tmp__23;
  var_name_tmp__26 = var_name_tmp__24;
  var_name_tmp__27 = var_name_tmp__26;
  if ((((var_name_tmp__27 != 0u)&1))) {
    goto var_name_tmp__30;
  } else {
    goto var_name_tmp__31;
  }

var_name_tmp__30:
  var_name_tmp__28 = var_name_tmp__25;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (1 << var_name_tmp__28)))), 32, 4);
  goto var_name_tmp__32;

var_name_tmp__31:
  var_name_tmp__29 = var_name_tmp__25;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((1 << var_name_tmp__29)))))), 32, 4);
  goto var_name_tmp__32;

var_name_tmp__32:
  return;
}


void DAC_SoftwareTriggerCmd(uint32_t var_name_tmp__33, uint32_t var_name_tmp__34) {
  uint32_t var_name_tmp__35;    /* Address-exposed local */
  uint32_t var_name_tmp__36;    /* Address-exposed local */
  uint32_t var_name_tmp__37;
  uint32_t var_name_tmp__38;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__39;
  uint64_t var_name_load_i32_1;

  var_name_tmp__35 = var_name_tmp__33;
  var_name_tmp__36 = var_name_tmp__34;
  var_name_tmp__37 = var_name_tmp__36;
  if ((((var_name_tmp__37 != 0u)&1))) {
    goto var_name_tmp__40;
  } else {
    goto var_name_tmp__41;
  }

var_name_tmp__40:
  var_name_tmp__38 = var_name_tmp__35;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (1 << (llvm_lshr_u32(var_name_tmp__38, 4)))))), 32, 4);
  goto var_name_tmp__42;

var_name_tmp__41:
  var_name_tmp__39 = var_name_tmp__35;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((1 << (llvm_lshr_u32(var_name_tmp__39, 4)))))))), 32, 4);
  goto var_name_tmp__42;

var_name_tmp__42:
  return;
}


void DAC_DualSoftwareTriggerCmd(uint32_t var_name_tmp__43) {
  uint32_t var_name_tmp__44;    /* Address-exposed local */
  uint32_t var_name_tmp__45;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__44 = var_name_tmp__43;
  var_name_tmp__45 = var_name_tmp__44;
  if ((((var_name_tmp__45 != 0u)&1))) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__47;
  }

var_name_tmp__46:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 3))), 32, 4);
  goto var_name_tmp__48;

var_name_tmp__47:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -4))), 32, 4);
  goto var_name_tmp__48;

var_name_tmp__48:
  return;
}


void DAC_WaveGenerationCmd(uint32_t var_name_tmp__49, uint32_t var_name_tmp__50, uint32_t var_name_tmp__51) {
  uint32_t var_name_tmp__52;    /* Address-exposed local */
  uint32_t var_name_tmp__53;    /* Address-exposed local */
  uint32_t var_name_tmp__54;    /* Address-exposed local */
  uint32_t var_name_tmp__55;
  uint32_t var_name_tmp__56;
  uint32_t var_name_tmp__57;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__58;
  uint32_t var_name_tmp__59;
  uint64_t var_name_load_i32_1;

  var_name_tmp__52 = var_name_tmp__49;
  var_name_tmp__53 = var_name_tmp__50;
  var_name_tmp__54 = var_name_tmp__51;
  var_name_tmp__55 = var_name_tmp__54;
  if ((((var_name_tmp__55 != 0u)&1))) {
    goto var_name_tmp__60;
  } else {
    goto var_name_tmp__61;
  }

var_name_tmp__60:
  var_name_tmp__56 = var_name_tmp__53;
  var_name_tmp__57 = var_name_tmp__52;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (var_name_tmp__56 << var_name_tmp__57)))), 32, 4);
  goto var_name_tmp__62;

var_name_tmp__61:
  var_name_tmp__58 = var_name_tmp__53;
  var_name_tmp__59 = var_name_tmp__52;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((var_name_tmp__58 << var_name_tmp__59)))))), 32, 4);
  goto var_name_tmp__62;

var_name_tmp__62:
  return;
}


void DAC_SetChannel1Data(uint32_t var_name_tmp__63, uint16_t var_name_tmp__64) {
  uint32_t var_name_tmp__65;    /* Address-exposed local */
  uint16_t var_name_tmp__66;    /* Address-exposed local */
  uint32_t var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__69;
  uint64_t var_name_load_i32_5;

  var_name_tmp__65 = var_name_tmp__63;
  var_name_tmp__66 = var_name_tmp__64;
  __adin_store_((((uint8_t*)(&var_name_tmp__67))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__67))), UINT64_C(1073771520), 32, 4);
  var_name_tmp__68 = var_name_tmp__65;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__67))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__67))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (llvm_add_u32(8, var_name_tmp__68)))))), 32, 4);
  var_name_tmp__69 = var_name_tmp__66;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)(&var_name_tmp__67))), 32, 4);
  __adin_store_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_5)))))))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__69)))), 32, 4);
}


void DAC_SetChannel2Data(uint32_t var_name_tmp__70, uint16_t var_name_tmp__71) {
  uint32_t var_name_tmp__72;    /* Address-exposed local */
  uint16_t var_name_tmp__73;    /* Address-exposed local */
  uint32_t var_name_tmp__74;    /* Address-exposed local */
  uint32_t var_name_tmp__75;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__76;
  uint64_t var_name_load_i32_5;

  var_name_tmp__72 = var_name_tmp__70;
  var_name_tmp__73 = var_name_tmp__71;
  __adin_store_((((uint8_t*)(&var_name_tmp__74))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__74))), UINT64_C(1073771520), 32, 4);
  var_name_tmp__75 = var_name_tmp__72;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__74))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__74))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (llvm_add_u32(20, var_name_tmp__75)))))), 32, 4);
  var_name_tmp__76 = var_name_tmp__73;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)(&var_name_tmp__74))), 32, 4);
  __adin_store_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_5)))))))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__76)))), 32, 4);
}


void DAC_SetDualChannelData(uint32_t var_name_tmp__77, uint16_t var_name_tmp__78, uint16_t var_name_tmp__79) {
  uint32_t var_name_tmp__80;    /* Address-exposed local */
  uint16_t var_name_tmp__81;    /* Address-exposed local */
  uint16_t var_name_tmp__82;    /* Address-exposed local */
  uint32_t var_name_tmp__83;    /* Address-exposed local */
  uint32_t var_name_tmp__84;    /* Address-exposed local */
  uint32_t var_name_tmp__85;
  uint16_t var_name_tmp__86;
  uint16_t var_name_tmp__87;
  uint16_t var_name_tmp__88;
  uint16_t var_name_tmp__89;
  uint32_t var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint32_t var_name_tmp__92;
  uint32_t var_name_tmp__93;

  var_name_tmp__80 = var_name_tmp__77;
  var_name_tmp__81 = var_name_tmp__78;
  var_name_tmp__82 = var_name_tmp__79;
  var_name_tmp__83 = 0;
  var_name_tmp__84 = 0;
  var_name_tmp__85 = var_name_tmp__80;
  if ((((var_name_tmp__85 == 8u)&1))) {
    goto var_name_tmp__94;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__94:
  var_name_tmp__86 = var_name_tmp__81;
  var_name_tmp__87 = var_name_tmp__82;
  var_name_tmp__83 = (((((uint32_t)(uint16_t)var_name_tmp__86)) << 8) | (((uint32_t)(uint16_t)var_name_tmp__87)));
  goto var_name_tmp__96;

var_name_tmp__95:
  var_name_tmp__88 = var_name_tmp__81;
  var_name_tmp__89 = var_name_tmp__82;
  var_name_tmp__83 = (((((uint32_t)(uint16_t)var_name_tmp__88)) << 16) | (((uint32_t)(uint16_t)var_name_tmp__89)));
  goto var_name_tmp__96;

var_name_tmp__96:
  var_name_tmp__84 = 1073771520u;
  var_name_tmp__90 = var_name_tmp__80;
  var_name_tmp__91 = var_name_tmp__84;
  var_name_tmp__84 = (llvm_add_u32(var_name_tmp__91, (llvm_add_u32(32, var_name_tmp__90))));
  var_name_tmp__92 = var_name_tmp__83;
  var_name_tmp__93 = var_name_tmp__84;
  __adin_store_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__93)))))), (((uint64_t)(uint32_t)var_name_tmp__92)), 32, 4);
}


uint16_t DAC_GetDataOutputValue(uint32_t var_name_tmp__97) {
  uint32_t var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_5;
  uint64_t var_name_load_i32_8;

  var_name_tmp__98 = var_name_tmp__97;
  __adin_store_((((uint8_t*)(&var_name_tmp__99))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__99))), UINT64_C(1073771520), 32, 4);
  var_name_tmp__100 = var_name_tmp__98;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__99))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__99))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (llvm_add_u32(44, (llvm_lshr_u32(var_name_tmp__100, 2)))))))), 32, 4);
  var_name_load_i32_5 = __adin_load_((((uint8_t*)(&var_name_tmp__99))), 32, 4);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_5)))))))), 32, 4);
  return (((uint16_t)(((uint32_t)var_name_load_i32_8))));
}


void DAC_DMACmd(uint32_t var_name_tmp__101, uint32_t var_name_tmp__102) {
  uint32_t var_name_tmp__103;    /* Address-exposed local */
  uint32_t var_name_tmp__104;    /* Address-exposed local */
  uint32_t var_name_tmp__105;
  uint32_t var_name_tmp__106;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__107;
  uint64_t var_name_load_i32_1;

  var_name_tmp__103 = var_name_tmp__101;
  var_name_tmp__104 = var_name_tmp__102;
  var_name_tmp__105 = var_name_tmp__104;
  if ((((var_name_tmp__105 != 0u)&1))) {
    goto var_name_tmp__108;
  } else {
    goto var_name_tmp__109;
  }

var_name_tmp__108:
  var_name_tmp__106 = var_name_tmp__103;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (4096 << var_name_tmp__106)))), 32, 4);
  goto var_name_tmp__110;

var_name_tmp__109:
  var_name_tmp__107 = var_name_tmp__103;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((4096 << var_name_tmp__107)))))), 32, 4);
  goto var_name_tmp__110;

var_name_tmp__110:
  return;
}


void DAC_ITConfig(uint32_t var_name_tmp__111, uint32_t var_name_tmp__112, uint32_t var_name_tmp__113) {
  uint32_t var_name_tmp__114;    /* Address-exposed local */
  uint32_t var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;    /* Address-exposed local */
  uint32_t var_name_tmp__117;
  uint32_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__120;
  uint32_t var_name_tmp__121;
  uint64_t var_name_load_i32_1;

  var_name_tmp__114 = var_name_tmp__111;
  var_name_tmp__115 = var_name_tmp__112;
  var_name_tmp__116 = var_name_tmp__113;
  var_name_tmp__117 = var_name_tmp__116;
  if ((((var_name_tmp__117 != 0u)&1))) {
    goto var_name_tmp__122;
  } else {
    goto var_name_tmp__123;
  }

var_name_tmp__122:
  var_name_tmp__118 = var_name_tmp__115;
  var_name_tmp__119 = var_name_tmp__114;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (var_name_tmp__118 << var_name_tmp__119)))), 32, 4);
  goto var_name_tmp__124;

var_name_tmp__123:
  var_name_tmp__120 = var_name_tmp__115;
  var_name_tmp__121 = var_name_tmp__114;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((var_name_tmp__120 << var_name_tmp__121)))))), 32, 4);
  goto var_name_tmp__124;

var_name_tmp__124:
  return;
}


uint32_t DAC_GetFlagStatus(uint32_t var_name_tmp__125, uint32_t var_name_tmp__126) {
  uint32_t var_name_tmp__127;    /* Address-exposed local */
  uint32_t var_name_tmp__128;    /* Address-exposed local */
  uint32_t var_name_tmp__129;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__130;
  uint32_t var_name_tmp__131;
  uint32_t var_name_tmp__132;

  var_name_tmp__127 = var_name_tmp__125;
  var_name_tmp__128 = var_name_tmp__126;
  var_name_tmp__129 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13))), 32, 4);
  var_name_tmp__130 = var_name_tmp__128;
  var_name_tmp__131 = var_name_tmp__127;
  if ((((((((uint32_t)var_name_load_i32_)) & (var_name_tmp__130 << var_name_tmp__131)) != 0u)&1))) {
    goto var_name_tmp__133;
  } else {
    goto var_name_tmp__134;
  }

var_name_tmp__133:
  var_name_tmp__129 = 1;
  goto var_name_tmp__135;

var_name_tmp__134:
  var_name_tmp__129 = 0;
  goto var_name_tmp__135;

var_name_tmp__135:
  var_name_tmp__132 = var_name_tmp__129;
  return var_name_tmp__132;
}


void DAC_ClearFlag(uint32_t var_name_tmp__136, uint32_t var_name_tmp__137) {
  uint32_t var_name_tmp__138;    /* Address-exposed local */
  uint32_t var_name_tmp__139;    /* Address-exposed local */
  uint32_t var_name_tmp__140;
  uint32_t var_name_tmp__141;

  var_name_tmp__138 = var_name_tmp__136;
  var_name_tmp__139 = var_name_tmp__137;
  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = var_name_tmp__138;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13))), (((uint64_t)(uint32_t)(var_name_tmp__140 << var_name_tmp__141))), 32, 4);
}


uint32_t DAC_GetITStatus(uint32_t var_name_tmp__142, uint32_t var_name_tmp__143) {
  uint32_t var_name_tmp__144;    /* Address-exposed local */
  uint32_t var_name_tmp__145;    /* Address-exposed local */
  uint32_t var_name_tmp__146;    /* Address-exposed local */
  uint32_t var_name_tmp__147;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__148;
  uint32_t var_name_tmp__149;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__150;
  uint32_t var_name_tmp__151;
  uint32_t var_name_tmp__152;
  uint32_t var_name_tmp__153;

  var_name_tmp__144 = var_name_tmp__142;
  var_name_tmp__145 = var_name_tmp__143;
  var_name_tmp__146 = 0;
  var_name_tmp__147 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073771520)), 32, 4);
  var_name_tmp__148 = var_name_tmp__145;
  var_name_tmp__149 = var_name_tmp__144;
  var_name_tmp__147 = ((((uint32_t)var_name_load_i32_)) & (var_name_tmp__148 << var_name_tmp__149));
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13))), 32, 4);
  var_name_tmp__150 = var_name_tmp__145;
  var_name_tmp__151 = var_name_tmp__144;
  if ((((((((uint32_t)var_name_load_i32_1)) & (var_name_tmp__150 << var_name_tmp__151)) != 0u)&1))) {
    goto var_name_tmp__154;
  } else {
    goto var_name_tmp__155;
  }

var_name_tmp__154:
  var_name_tmp__152 = var_name_tmp__147;
  if ((((var_name_tmp__152 != 0u)&1))) {
    goto var_name_tmp__156;
  } else {
    goto var_name_tmp__155;
  }

var_name_tmp__156:
  var_name_tmp__146 = 1;
  goto var_name_tmp__157;

var_name_tmp__155:
  var_name_tmp__146 = 0;
  goto var_name_tmp__157;

var_name_tmp__157:
  var_name_tmp__153 = var_name_tmp__146;
  return var_name_tmp__153;
}


void DAC_ClearITPendingBit(uint32_t var_name_tmp__158, uint32_t var_name_tmp__159) {
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;    /* Address-exposed local */
  uint32_t var_name_tmp__162;
  uint32_t var_name_tmp__163;

  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__159;
  var_name_tmp__162 = var_name_tmp__161;
  var_name_tmp__163 = var_name_tmp__160;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13))), (((uint64_t)(uint32_t)(var_name_tmp__162 << var_name_tmp__163))), 32, 4);
}

