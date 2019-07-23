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
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  uint32_t var_name_tmp__9;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__10;
  uint32_t var_name_tmp__11;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__12;
  uint32_t var_name_tmp__13;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__14;
  uint32_t var_name_tmp__15;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__16;
  uint32_t var_name_tmp__17;
  uint32_t var_name_tmp__18;
  uint32_t var_name_tmp__19;
  uint32_t var_name_tmp__20;
  uint32_t var_name_tmp__21;

  var_name_tmp__3 = var_name_tmp__1;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = 0;
  var_name_tmp__6 = 0;
  var_name_tmp__7 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  var_name_tmp__5 = var_name_tmp__7;
  var_name_tmp__8 = var_name_tmp__3;
  var_name_tmp__9 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__9 & (~((4094 << var_name_tmp__8))));
  var_name_tmp__10 = var_name_tmp__4;
  var_name_tmp__11 = *((&var_name_tmp__10->field0));
  var_name_tmp__12 = var_name_tmp__4;
  var_name_tmp__13 = *((&var_name_tmp__12->field1));
  var_name_tmp__14 = var_name_tmp__4;
  var_name_tmp__15 = *((&var_name_tmp__14->field2));
  var_name_tmp__16 = var_name_tmp__4;
  var_name_tmp__17 = *((&var_name_tmp__16->field3));
  var_name_tmp__6 = (((var_name_tmp__11 | var_name_tmp__13) | var_name_tmp__15) | var_name_tmp__17);
  var_name_tmp__18 = var_name_tmp__6;
  var_name_tmp__19 = var_name_tmp__3;
  var_name_tmp__20 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__20 | (var_name_tmp__18 << var_name_tmp__19));
  var_name_tmp__21 = var_name_tmp__5;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = var_name_tmp__21;
}


void DAC_StructInit(struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__22) {
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__23;    /* Address-exposed local */
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__24;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__25;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__26;
  struct l_struct_struct_OC_DAC_InitTypeDef* var_name_tmp__27;

  var_name_tmp__23 = var_name_tmp__22;
  var_name_tmp__24 = var_name_tmp__23;
  *((&var_name_tmp__24->field0)) = 0;
  var_name_tmp__25 = var_name_tmp__23;
  *((&var_name_tmp__25->field1)) = 0;
  var_name_tmp__26 = var_name_tmp__23;
  *((&var_name_tmp__26->field2)) = 0;
  var_name_tmp__27 = var_name_tmp__23;
  *((&var_name_tmp__27->field3)) = 0;
}


void DAC_Cmd(uint32_t var_name_tmp__28, uint32_t var_name_tmp__29) {
  uint32_t var_name_tmp__30;    /* Address-exposed local */
  uint32_t var_name_tmp__31;    /* Address-exposed local */
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint32_t var_name_tmp__35;
  uint32_t var_name_tmp__36;

  var_name_tmp__30 = var_name_tmp__28;
  var_name_tmp__31 = var_name_tmp__29;
  var_name_tmp__32 = var_name_tmp__31;
  if ((((var_name_tmp__32 != 0u)&1))) {
    goto var_name_tmp__37;
  } else {
    goto var_name_tmp__38;
  }

var_name_tmp__37:
  var_name_tmp__33 = var_name_tmp__30;
  var_name_tmp__34 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__34 | (1 << var_name_tmp__33));
  goto var_name_tmp__39;

var_name_tmp__38:
  var_name_tmp__35 = var_name_tmp__30;
  var_name_tmp__36 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__36 & (~((1 << var_name_tmp__35))));
  goto var_name_tmp__39;

var_name_tmp__39:
  return;
}


void DAC_SoftwareTriggerCmd(uint32_t var_name_tmp__40, uint32_t var_name_tmp__41) {
  uint32_t var_name_tmp__42;    /* Address-exposed local */
  uint32_t var_name_tmp__43;    /* Address-exposed local */
  uint32_t var_name_tmp__44;
  uint32_t var_name_tmp__45;
  uint32_t var_name_tmp__46;
  uint32_t var_name_tmp__47;
  uint32_t var_name_tmp__48;

  var_name_tmp__42 = var_name_tmp__40;
  var_name_tmp__43 = var_name_tmp__41;
  var_name_tmp__44 = var_name_tmp__43;
  if ((((var_name_tmp__44 != 0u)&1))) {
    goto var_name_tmp__49;
  } else {
    goto var_name_tmp__50;
  }

var_name_tmp__49:
  var_name_tmp__45 = var_name_tmp__42;
  var_name_tmp__46 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1)) = (var_name_tmp__46 | (1 << (llvm_lshr_u32(var_name_tmp__45, 4))));
  goto var_name_tmp__51;

var_name_tmp__50:
  var_name_tmp__47 = var_name_tmp__42;
  var_name_tmp__48 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1)) = (var_name_tmp__48 & (~((1 << (llvm_lshr_u32(var_name_tmp__47, 4))))));
  goto var_name_tmp__51;

var_name_tmp__51:
  return;
}


void DAC_DualSoftwareTriggerCmd(uint32_t var_name_tmp__52) {
  uint32_t var_name_tmp__53;    /* Address-exposed local */
  uint32_t var_name_tmp__54;
  uint32_t var_name_tmp__55;
  uint32_t var_name_tmp__56;

  var_name_tmp__53 = var_name_tmp__52;
  var_name_tmp__54 = var_name_tmp__53;
  if ((((var_name_tmp__54 != 0u)&1))) {
    goto var_name_tmp__57;
  } else {
    goto var_name_tmp__58;
  }

var_name_tmp__57:
  var_name_tmp__55 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1)) = (var_name_tmp__55 | 3);
  goto var_name_tmp__59;

var_name_tmp__58:
  var_name_tmp__56 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field1)) = (var_name_tmp__56 & -4);
  goto var_name_tmp__59;

var_name_tmp__59:
  return;
}


void DAC_WaveGenerationCmd(uint32_t var_name_tmp__60, uint32_t var_name_tmp__61, uint32_t var_name_tmp__62) {
  uint32_t var_name_tmp__63;    /* Address-exposed local */
  uint32_t var_name_tmp__64;    /* Address-exposed local */
  uint32_t var_name_tmp__65;    /* Address-exposed local */
  uint32_t var_name_tmp__66;
  uint32_t var_name_tmp__67;
  uint32_t var_name_tmp__68;
  uint32_t var_name_tmp__69;
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;
  uint32_t var_name_tmp__72;

  var_name_tmp__63 = var_name_tmp__60;
  var_name_tmp__64 = var_name_tmp__61;
  var_name_tmp__65 = var_name_tmp__62;
  var_name_tmp__66 = var_name_tmp__65;
  if ((((var_name_tmp__66 != 0u)&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  var_name_tmp__67 = var_name_tmp__64;
  var_name_tmp__68 = var_name_tmp__63;
  var_name_tmp__69 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__69 | (var_name_tmp__67 << var_name_tmp__68));
  goto var_name_tmp__75;

var_name_tmp__74:
  var_name_tmp__70 = var_name_tmp__64;
  var_name_tmp__71 = var_name_tmp__63;
  var_name_tmp__72 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__72 & (~((var_name_tmp__70 << var_name_tmp__71))));
  goto var_name_tmp__75;

var_name_tmp__75:
  return;
}


void DAC_SetChannel1Data(uint32_t var_name_tmp__76, uint16_t var_name_tmp__77) {
  uint32_t var_name_tmp__78;    /* Address-exposed local */
  uint16_t var_name_tmp__79;    /* Address-exposed local */
  uint32_t var_name_tmp__80;    /* Address-exposed local */
  uint32_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint16_t var_name_tmp__83;
  uint32_t var_name_tmp__84;

  var_name_tmp__78 = var_name_tmp__76;
  var_name_tmp__79 = var_name_tmp__77;
  *(volatile uint32_t*)(&var_name_tmp__80) = 0;
  *(volatile uint32_t*)(&var_name_tmp__80) = 1073771520u;
  var_name_tmp__81 = var_name_tmp__78;
  var_name_tmp__82 = *(volatile uint32_t*)(&var_name_tmp__80);
  *(volatile uint32_t*)(&var_name_tmp__80) = (llvm_add_u32(var_name_tmp__82, (llvm_add_u32(8, var_name_tmp__81))));
  var_name_tmp__83 = var_name_tmp__79;
  var_name_tmp__84 = *(volatile uint32_t*)(&var_name_tmp__80);
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__84)))) = (((uint32_t)(uint16_t)var_name_tmp__83));
}


void DAC_SetChannel2Data(uint32_t var_name_tmp__85, uint16_t var_name_tmp__86) {
  uint32_t var_name_tmp__87;    /* Address-exposed local */
  uint16_t var_name_tmp__88;    /* Address-exposed local */
  uint32_t var_name_tmp__89;    /* Address-exposed local */
  uint32_t var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint16_t var_name_tmp__92;
  uint32_t var_name_tmp__93;

  var_name_tmp__87 = var_name_tmp__85;
  var_name_tmp__88 = var_name_tmp__86;
  *(volatile uint32_t*)(&var_name_tmp__89) = 0;
  *(volatile uint32_t*)(&var_name_tmp__89) = 1073771520u;
  var_name_tmp__90 = var_name_tmp__87;
  var_name_tmp__91 = *(volatile uint32_t*)(&var_name_tmp__89);
  *(volatile uint32_t*)(&var_name_tmp__89) = (llvm_add_u32(var_name_tmp__91, (llvm_add_u32(20, var_name_tmp__90))));
  var_name_tmp__92 = var_name_tmp__88;
  var_name_tmp__93 = *(volatile uint32_t*)(&var_name_tmp__89);
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__93)))) = (((uint32_t)(uint16_t)var_name_tmp__92));
}


void DAC_SetDualChannelData(uint32_t var_name_tmp__94, uint16_t var_name_tmp__95, uint16_t var_name_tmp__96) {
  uint32_t var_name_tmp__97;    /* Address-exposed local */
  uint16_t var_name_tmp__98;    /* Address-exposed local */
  uint16_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;
  uint16_t var_name_tmp__103;
  uint16_t var_name_tmp__104;
  uint16_t var_name_tmp__105;
  uint16_t var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  uint32_t var_name_tmp__109;
  uint32_t var_name_tmp__110;

  var_name_tmp__97 = var_name_tmp__94;
  var_name_tmp__98 = var_name_tmp__95;
  var_name_tmp__99 = var_name_tmp__96;
  var_name_tmp__100 = 0;
  var_name_tmp__101 = 0;
  var_name_tmp__102 = var_name_tmp__97;
  if ((((var_name_tmp__102 == 8u)&1))) {
    goto var_name_tmp__111;
  } else {
    goto var_name_tmp__112;
  }

var_name_tmp__111:
  var_name_tmp__103 = var_name_tmp__98;
  var_name_tmp__104 = var_name_tmp__99;
  var_name_tmp__100 = (((((uint32_t)(uint16_t)var_name_tmp__103)) << 8) | (((uint32_t)(uint16_t)var_name_tmp__104)));
  goto var_name_tmp__113;

var_name_tmp__112:
  var_name_tmp__105 = var_name_tmp__98;
  var_name_tmp__106 = var_name_tmp__99;
  var_name_tmp__100 = (((((uint32_t)(uint16_t)var_name_tmp__105)) << 16) | (((uint32_t)(uint16_t)var_name_tmp__106)));
  goto var_name_tmp__113;

var_name_tmp__113:
  var_name_tmp__101 = 1073771520u;
  var_name_tmp__107 = var_name_tmp__97;
  var_name_tmp__108 = var_name_tmp__101;
  var_name_tmp__101 = (llvm_add_u32(var_name_tmp__108, (llvm_add_u32(32, var_name_tmp__107))));
  var_name_tmp__109 = var_name_tmp__100;
  var_name_tmp__110 = var_name_tmp__101;
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__110)))) = var_name_tmp__109;
}


uint16_t DAC_GetDataOutputValue(uint32_t var_name_tmp__114) {
  uint32_t var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;    /* Address-exposed local */
  uint32_t var_name_tmp__117;
  uint32_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint32_t var_name_tmp__120;

  var_name_tmp__115 = var_name_tmp__114;
  *(volatile uint32_t*)(&var_name_tmp__116) = 0;
  *(volatile uint32_t*)(&var_name_tmp__116) = 1073771520u;
  var_name_tmp__117 = var_name_tmp__115;
  var_name_tmp__118 = *(volatile uint32_t*)(&var_name_tmp__116);
  *(volatile uint32_t*)(&var_name_tmp__116) = (llvm_add_u32(var_name_tmp__118, (llvm_add_u32(44, (llvm_lshr_u32(var_name_tmp__117, 2))))));
  var_name_tmp__119 = *(volatile uint32_t*)(&var_name_tmp__116);
  var_name_tmp__120 = *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__119))));
  return (((uint16_t)var_name_tmp__120));
}


void DAC_DMACmd(uint32_t var_name_tmp__121, uint32_t var_name_tmp__122) {
  uint32_t var_name_tmp__123;    /* Address-exposed local */
  uint32_t var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;
  uint32_t var_name_tmp__126;
  uint32_t var_name_tmp__127;
  uint32_t var_name_tmp__128;
  uint32_t var_name_tmp__129;

  var_name_tmp__123 = var_name_tmp__121;
  var_name_tmp__124 = var_name_tmp__122;
  var_name_tmp__125 = var_name_tmp__124;
  if ((((var_name_tmp__125 != 0u)&1))) {
    goto var_name_tmp__130;
  } else {
    goto var_name_tmp__131;
  }

var_name_tmp__130:
  var_name_tmp__126 = var_name_tmp__123;
  var_name_tmp__127 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__127 | (4096 << var_name_tmp__126));
  goto var_name_tmp__132;

var_name_tmp__131:
  var_name_tmp__128 = var_name_tmp__123;
  var_name_tmp__129 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__129 & (~((4096 << var_name_tmp__128))));
  goto var_name_tmp__132;

var_name_tmp__132:
  return;
}


void DAC_ITConfig(uint32_t var_name_tmp__133, uint32_t var_name_tmp__134, uint32_t var_name_tmp__135) {
  uint32_t var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;    /* Address-exposed local */
  uint32_t var_name_tmp__138;    /* Address-exposed local */
  uint32_t var_name_tmp__139;
  uint32_t var_name_tmp__140;
  uint32_t var_name_tmp__141;
  uint32_t var_name_tmp__142;
  uint32_t var_name_tmp__143;
  uint32_t var_name_tmp__144;
  uint32_t var_name_tmp__145;

  var_name_tmp__136 = var_name_tmp__133;
  var_name_tmp__137 = var_name_tmp__134;
  var_name_tmp__138 = var_name_tmp__135;
  var_name_tmp__139 = var_name_tmp__138;
  if ((((var_name_tmp__139 != 0u)&1))) {
    goto var_name_tmp__146;
  } else {
    goto var_name_tmp__147;
  }

var_name_tmp__146:
  var_name_tmp__140 = var_name_tmp__137;
  var_name_tmp__141 = var_name_tmp__136;
  var_name_tmp__142 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__142 | (var_name_tmp__140 << var_name_tmp__141));
  goto var_name_tmp__148;

var_name_tmp__147:
  var_name_tmp__143 = var_name_tmp__137;
  var_name_tmp__144 = var_name_tmp__136;
  var_name_tmp__145 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0)) = (var_name_tmp__145 & (~((var_name_tmp__143 << var_name_tmp__144))));
  goto var_name_tmp__148;

var_name_tmp__148:
  return;
}


uint32_t DAC_GetFlagStatus(uint32_t var_name_tmp__149, uint32_t var_name_tmp__150) {
  uint32_t var_name_tmp__151;    /* Address-exposed local */
  uint32_t var_name_tmp__152;    /* Address-exposed local */
  uint32_t var_name_tmp__153;    /* Address-exposed local */
  uint32_t var_name_tmp__154;
  uint32_t var_name_tmp__155;
  uint32_t var_name_tmp__156;
  uint32_t var_name_tmp__157;

  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__152 = var_name_tmp__150;
  var_name_tmp__153 = 0;
  var_name_tmp__154 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13));
  var_name_tmp__155 = var_name_tmp__152;
  var_name_tmp__156 = var_name_tmp__151;
  if (((((var_name_tmp__154 & (var_name_tmp__155 << var_name_tmp__156)) != 0u)&1))) {
    goto var_name_tmp__158;
  } else {
    goto var_name_tmp__159;
  }

var_name_tmp__158:
  var_name_tmp__153 = 1;
  goto var_name_tmp__160;

var_name_tmp__159:
  var_name_tmp__153 = 0;
  goto var_name_tmp__160;

var_name_tmp__160:
  var_name_tmp__157 = var_name_tmp__153;
  return var_name_tmp__157;
}


void DAC_ClearFlag(uint32_t var_name_tmp__161, uint32_t var_name_tmp__162) {
  uint32_t var_name_tmp__163;    /* Address-exposed local */
  uint32_t var_name_tmp__164;    /* Address-exposed local */
  uint32_t var_name_tmp__165;
  uint32_t var_name_tmp__166;

  var_name_tmp__163 = var_name_tmp__161;
  var_name_tmp__164 = var_name_tmp__162;
  var_name_tmp__165 = var_name_tmp__164;
  var_name_tmp__166 = var_name_tmp__163;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13)) = (var_name_tmp__165 << var_name_tmp__166);
}


uint32_t DAC_GetITStatus(uint32_t var_name_tmp__167, uint32_t var_name_tmp__168) {
  uint32_t var_name_tmp__169;    /* Address-exposed local */
  uint32_t var_name_tmp__170;    /* Address-exposed local */
  uint32_t var_name_tmp__171;    /* Address-exposed local */
  uint32_t var_name_tmp__172;    /* Address-exposed local */
  uint32_t var_name_tmp__173;
  uint32_t var_name_tmp__174;
  uint32_t var_name_tmp__175;
  uint32_t var_name_tmp__176;
  uint32_t var_name_tmp__177;
  uint32_t var_name_tmp__178;
  uint32_t var_name_tmp__179;
  uint32_t var_name_tmp__180;

  var_name_tmp__169 = var_name_tmp__167;
  var_name_tmp__170 = var_name_tmp__168;
  var_name_tmp__171 = 0;
  var_name_tmp__172 = 0;
  var_name_tmp__173 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field0));
  var_name_tmp__174 = var_name_tmp__170;
  var_name_tmp__175 = var_name_tmp__169;
  var_name_tmp__172 = (var_name_tmp__173 & (var_name_tmp__174 << var_name_tmp__175));
  var_name_tmp__176 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13));
  var_name_tmp__177 = var_name_tmp__170;
  var_name_tmp__178 = var_name_tmp__169;
  if (((((var_name_tmp__176 & (var_name_tmp__177 << var_name_tmp__178)) != 0u)&1))) {
    goto var_name_tmp__181;
  } else {
    goto var_name_tmp__182;
  }

var_name_tmp__181:
  var_name_tmp__179 = var_name_tmp__172;
  if ((((var_name_tmp__179 != 0u)&1))) {
    goto var_name_tmp__183;
  } else {
    goto var_name_tmp__182;
  }

var_name_tmp__183:
  var_name_tmp__171 = 1;
  goto var_name_tmp__184;

var_name_tmp__182:
  var_name_tmp__171 = 0;
  goto var_name_tmp__184;

var_name_tmp__184:
  var_name_tmp__180 = var_name_tmp__171;
  return var_name_tmp__180;
}


void DAC_ClearITPendingBit(uint32_t var_name_tmp__185, uint32_t var_name_tmp__186) {
  uint32_t var_name_tmp__187;    /* Address-exposed local */
  uint32_t var_name_tmp__188;    /* Address-exposed local */
  uint32_t var_name_tmp__189;
  uint32_t var_name_tmp__190;

  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__186;
  var_name_tmp__189 = var_name_tmp__188;
  var_name_tmp__190 = var_name_tmp__187;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DAC_TypeDef*)(uintptr_t)UINT64_C(1073771520))->field13)) = (var_name_tmp__189 << var_name_tmp__190);
}

