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
struct l_struct_struct_OC_ADC_TypeDef;
struct l_struct_struct_OC_ADC_InitTypeDef;
struct l_struct_struct_OC_ADC_CommonInitTypeDef;
struct l_struct_struct_OC_ADC_Common_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_ADC_TypeDef {
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
  uint32_t field14;
  uint32_t field15;
  uint32_t field16;
  uint32_t field17;
  uint32_t field18;
  uint32_t field19;
};
struct l_struct_struct_OC_ADC_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint8_t field6;
};
struct l_struct_struct_OC_ADC_CommonInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_ADC_Common_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
};

/* Function Declarations */
void ADC_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void ADC_Init(struct l_struct_struct_OC_ADC_TypeDef*, struct l_struct_struct_OC_ADC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_StructInit(struct l_struct_struct_OC_ADC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_CommonInit(struct l_struct_struct_OC_ADC_CommonInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_CommonStructInit(struct l_struct_struct_OC_ADC_CommonInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_Cmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_AnalogWatchdogCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_AnalogWatchdogThresholdsConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_AnalogWatchdogSingleChannelConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_TempSensorVrefintCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_VBATCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_RegularChannelConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t, uint8_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_SoftwareStartConv(struct l_struct_struct_OC_ADC_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t ADC_GetSoftwareStartConvStatus(struct l_struct_struct_OC_ADC_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_EOCOnEachRegularChannelCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ContinuousModeCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_DiscModeChannelCountConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_DiscModeCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t ADC_GetConversionValue(struct l_struct_struct_OC_ADC_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t ADC_GetMultiModeConversionValue(void) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_DMACmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_DMARequestAfterLastTransferCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_MultiModeDMARequestAfterLastTransferCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_InjectedChannelConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t, uint8_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_InjectedSequencerLengthConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_SetInjectedOffset(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ExternalTrigInjectedConvConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ExternalTrigInjectedConvEdgeConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_SoftwareStartInjectedConv(struct l_struct_struct_OC_ADC_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t ADC_GetSoftwareStartInjectedConvCmdStatus(struct l_struct_struct_OC_ADC_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_AutoInjectedConvCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_InjectedDiscModeCmd(struct l_struct_struct_OC_ADC_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t ADC_GetInjectedConversionValue(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ITConfig(struct l_struct_struct_OC_ADC_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t ADC_GetFlagStatus(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ClearFlag(struct l_struct_struct_OC_ADC_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t ADC_GetITStatus(struct l_struct_struct_OC_ADC_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void ADC_ClearITPendingBit(struct l_struct_struct_OC_ADC_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));


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
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void ADC_DeInit(void) {
  RCC_APB2PeriphResetCmd(256, 1);
  RCC_APB2PeriphResetCmd(256, 0);
}


void ADC_Init(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__1, struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__2) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__3;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__4;    /* Address-exposed local */
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint8_t var_name_tmp__6;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__7;
  uint32_t var_name_tmp__8;
  uint32_t var_name_tmp__9;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__10;
  uint32_t var_name_tmp__11;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;
  uint32_t var_name_tmp__15;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__16;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__17;
  uint32_t var_name_tmp__18;
  uint32_t var_name_tmp__19;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__20;
  uint32_t var_name_tmp__21;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__22;
  uint32_t var_name_tmp__23;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__24;
  uint32_t var_name_tmp__25;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__26;
  uint32_t var_name_tmp__27;
  uint32_t var_name_tmp__28;
  uint32_t var_name_tmp__29;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__30;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__31;
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__34;
  uint8_t var_name_tmp__35;
  uint8_t var_name_tmp__36;
  uint8_t var_name_tmp__37;
  uint32_t var_name_tmp__38;
  uint32_t var_name_tmp__39;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__40;

  var_name_tmp__3 = var_name_tmp__1;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = 0;
  var_name_tmp__6 = 0;
  var_name_tmp__7 = var_name_tmp__3;
  var_name_tmp__8 = *(volatile uint32_t*)((&var_name_tmp__7->field1));
  var_name_tmp__5 = var_name_tmp__8;
  var_name_tmp__9 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__9 & -50331905);
  var_name_tmp__10 = var_name_tmp__4;
  var_name_tmp__11 = *((&var_name_tmp__10->field1));
  var_name_tmp__12 = var_name_tmp__4;
  var_name_tmp__13 = *((&var_name_tmp__12->field0));
  var_name_tmp__14 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__14 | ((var_name_tmp__11 << 8) | var_name_tmp__13));
  var_name_tmp__15 = var_name_tmp__5;
  var_name_tmp__16 = var_name_tmp__3;
  *(volatile uint32_t*)((&var_name_tmp__16->field1)) = var_name_tmp__15;
  var_name_tmp__17 = var_name_tmp__3;
  var_name_tmp__18 = *(volatile uint32_t*)((&var_name_tmp__17->field2));
  var_name_tmp__5 = var_name_tmp__18;
  var_name_tmp__19 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__19 & -1056966659);
  var_name_tmp__20 = var_name_tmp__4;
  var_name_tmp__21 = *((&var_name_tmp__20->field5));
  var_name_tmp__22 = var_name_tmp__4;
  var_name_tmp__23 = *((&var_name_tmp__22->field4));
  var_name_tmp__24 = var_name_tmp__4;
  var_name_tmp__25 = *((&var_name_tmp__24->field3));
  var_name_tmp__26 = var_name_tmp__4;
  var_name_tmp__27 = *((&var_name_tmp__26->field2));
  var_name_tmp__28 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__28 | (((var_name_tmp__21 | var_name_tmp__23) | var_name_tmp__25) | (var_name_tmp__27 << 1)));
  var_name_tmp__29 = var_name_tmp__5;
  var_name_tmp__30 = var_name_tmp__3;
  *(volatile uint32_t*)((&var_name_tmp__30->field2)) = var_name_tmp__29;
  var_name_tmp__31 = var_name_tmp__3;
  var_name_tmp__32 = *(volatile uint32_t*)((&var_name_tmp__31->field11));
  var_name_tmp__5 = var_name_tmp__32;
  var_name_tmp__33 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__33 & -15728641);
  var_name_tmp__34 = var_name_tmp__4;
  var_name_tmp__35 = *((&var_name_tmp__34->field6));
  var_name_tmp__36 = var_name_tmp__6;
  var_name_tmp__6 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__36)) | (((uint32_t)(uint8_t)(((uint8_t)(llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__35)), 1)))))))));
  var_name_tmp__37 = var_name_tmp__6;
  var_name_tmp__38 = var_name_tmp__5;
  var_name_tmp__5 = (var_name_tmp__38 | ((((uint32_t)(uint8_t)var_name_tmp__37)) << 20));
  var_name_tmp__39 = var_name_tmp__5;
  var_name_tmp__40 = var_name_tmp__3;
  *(volatile uint32_t*)((&var_name_tmp__40->field11)) = var_name_tmp__39;
}


void ADC_StructInit(struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__41) {
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__42;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__43;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__44;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__45;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__46;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__47;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__48;
  struct l_struct_struct_OC_ADC_InitTypeDef* var_name_tmp__49;

  var_name_tmp__42 = var_name_tmp__41;
  var_name_tmp__43 = var_name_tmp__42;
  *((&var_name_tmp__43->field0)) = 0;
  var_name_tmp__44 = var_name_tmp__42;
  *((&var_name_tmp__44->field1)) = 0;
  var_name_tmp__45 = var_name_tmp__42;
  *((&var_name_tmp__45->field2)) = 0;
  var_name_tmp__46 = var_name_tmp__42;
  *((&var_name_tmp__46->field3)) = 0;
  var_name_tmp__47 = var_name_tmp__42;
  *((&var_name_tmp__47->field4)) = 0;
  var_name_tmp__48 = var_name_tmp__42;
  *((&var_name_tmp__48->field5)) = 0;
  var_name_tmp__49 = var_name_tmp__42;
  *((&var_name_tmp__49->field6)) = 1;
}


void ADC_CommonInit(struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__50) {
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__51;    /* Address-exposed local */
  uint32_t var_name_tmp__52;    /* Address-exposed local */
  uint32_t var_name_tmp__53;
  uint32_t var_name_tmp__54;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__55;
  uint32_t var_name_tmp__56;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__57;
  uint32_t var_name_tmp__58;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__59;
  uint32_t var_name_tmp__60;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__61;
  uint32_t var_name_tmp__62;
  uint32_t var_name_tmp__63;
  uint32_t var_name_tmp__64;

  var_name_tmp__51 = var_name_tmp__50;
  var_name_tmp__52 = 0;
  var_name_tmp__53 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  var_name_tmp__52 = var_name_tmp__53;
  var_name_tmp__54 = var_name_tmp__52;
  var_name_tmp__52 = (var_name_tmp__54 & -249632);
  var_name_tmp__55 = var_name_tmp__51;
  var_name_tmp__56 = *((&var_name_tmp__55->field0));
  var_name_tmp__57 = var_name_tmp__51;
  var_name_tmp__58 = *((&var_name_tmp__57->field1));
  var_name_tmp__59 = var_name_tmp__51;
  var_name_tmp__60 = *((&var_name_tmp__59->field2));
  var_name_tmp__61 = var_name_tmp__51;
  var_name_tmp__62 = *((&var_name_tmp__61->field3));
  var_name_tmp__63 = var_name_tmp__52;
  var_name_tmp__52 = (var_name_tmp__63 | (((var_name_tmp__56 | var_name_tmp__58) | var_name_tmp__60) | var_name_tmp__62));
  var_name_tmp__64 = var_name_tmp__52;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = var_name_tmp__64;
}


void ADC_CommonStructInit(struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__65) {
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__66;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__67;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__68;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__69;
  struct l_struct_struct_OC_ADC_CommonInitTypeDef* var_name_tmp__70;

  var_name_tmp__66 = var_name_tmp__65;
  var_name_tmp__67 = var_name_tmp__66;
  *((&var_name_tmp__67->field0)) = 0;
  var_name_tmp__68 = var_name_tmp__66;
  *((&var_name_tmp__68->field1)) = 0;
  var_name_tmp__69 = var_name_tmp__66;
  *((&var_name_tmp__69->field2)) = 0;
  var_name_tmp__70 = var_name_tmp__66;
  *((&var_name_tmp__70->field3)) = 0;
}


void ADC_Cmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__71, uint32_t var_name_tmp__72) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__73;    /* Address-exposed local */
  uint32_t var_name_tmp__74;    /* Address-exposed local */
  uint32_t var_name_tmp__75;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__76;
  uint32_t* var_name_tmp__77;
  uint32_t var_name_tmp__78;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__79;
  uint32_t* var_name_tmp__80;
  uint32_t var_name_tmp__81;

  var_name_tmp__73 = var_name_tmp__71;
  var_name_tmp__74 = var_name_tmp__72;
  var_name_tmp__75 = var_name_tmp__74;
  if ((((var_name_tmp__75 != 0u)&1))) {
    goto var_name_tmp__82;
  } else {
    goto var_name_tmp__83;
  }

var_name_tmp__82:
  var_name_tmp__76 = var_name_tmp__73;
  var_name_tmp__77 = (&var_name_tmp__76->field2);
  var_name_tmp__78 = *(volatile uint32_t*)var_name_tmp__77;
  *(volatile uint32_t*)var_name_tmp__77 = (var_name_tmp__78 | 1);
  goto var_name_tmp__84;

var_name_tmp__83:
  var_name_tmp__79 = var_name_tmp__73;
  var_name_tmp__80 = (&var_name_tmp__79->field2);
  var_name_tmp__81 = *(volatile uint32_t*)var_name_tmp__80;
  *(volatile uint32_t*)var_name_tmp__80 = (var_name_tmp__81 & -2);
  goto var_name_tmp__84;

var_name_tmp__84:
  return;
}


void ADC_AnalogWatchdogCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__85, uint32_t var_name_tmp__86) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__87;    /* Address-exposed local */
  uint32_t var_name_tmp__88;    /* Address-exposed local */
  uint32_t var_name_tmp__89;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint32_t var_name_tmp__92;
  uint32_t var_name_tmp__93;
  uint32_t var_name_tmp__94;
  uint32_t var_name_tmp__95;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__96;

  var_name_tmp__87 = var_name_tmp__85;
  var_name_tmp__88 = var_name_tmp__86;
  var_name_tmp__89 = 0;
  var_name_tmp__90 = var_name_tmp__87;
  var_name_tmp__91 = *(volatile uint32_t*)((&var_name_tmp__90->field1));
  var_name_tmp__89 = var_name_tmp__91;
  var_name_tmp__92 = var_name_tmp__89;
  var_name_tmp__89 = (var_name_tmp__92 & -12583425);
  var_name_tmp__93 = var_name_tmp__88;
  var_name_tmp__94 = var_name_tmp__89;
  var_name_tmp__89 = (var_name_tmp__94 | var_name_tmp__93);
  var_name_tmp__95 = var_name_tmp__89;
  var_name_tmp__96 = var_name_tmp__87;
  *(volatile uint32_t*)((&var_name_tmp__96->field1)) = var_name_tmp__95;
}


void ADC_AnalogWatchdogThresholdsConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__97, uint16_t var_name_tmp__98, uint16_t var_name_tmp__99) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__100;    /* Address-exposed local */
  uint16_t var_name_tmp__101;    /* Address-exposed local */
  uint16_t var_name_tmp__102;    /* Address-exposed local */
  uint16_t var_name_tmp__103;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__104;
  uint16_t var_name_tmp__105;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__106;

  var_name_tmp__100 = var_name_tmp__97;
  var_name_tmp__101 = var_name_tmp__98;
  var_name_tmp__102 = var_name_tmp__99;
  var_name_tmp__103 = var_name_tmp__101;
  var_name_tmp__104 = var_name_tmp__100;
  *(volatile uint32_t*)((&var_name_tmp__104->field9)) = (((uint32_t)(uint16_t)var_name_tmp__103));
  var_name_tmp__105 = var_name_tmp__102;
  var_name_tmp__106 = var_name_tmp__100;
  *(volatile uint32_t*)((&var_name_tmp__106->field10)) = (((uint32_t)(uint16_t)var_name_tmp__105));
}


void ADC_AnalogWatchdogSingleChannelConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__107, uint8_t var_name_tmp__108) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__109;    /* Address-exposed local */
  uint8_t var_name_tmp__110;    /* Address-exposed local */
  uint32_t var_name_tmp__111;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__112;
  uint32_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  uint8_t var_name_tmp__115;
  uint32_t var_name_tmp__116;
  uint32_t var_name_tmp__117;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__118;

  var_name_tmp__109 = var_name_tmp__107;
  var_name_tmp__110 = var_name_tmp__108;
  var_name_tmp__111 = 0;
  var_name_tmp__112 = var_name_tmp__109;
  var_name_tmp__113 = *(volatile uint32_t*)((&var_name_tmp__112->field1));
  var_name_tmp__111 = var_name_tmp__113;
  var_name_tmp__114 = var_name_tmp__111;
  var_name_tmp__111 = (var_name_tmp__114 & -32);
  var_name_tmp__115 = var_name_tmp__110;
  var_name_tmp__116 = var_name_tmp__111;
  var_name_tmp__111 = (var_name_tmp__116 | (((uint32_t)(uint8_t)var_name_tmp__115)));
  var_name_tmp__117 = var_name_tmp__111;
  var_name_tmp__118 = var_name_tmp__109;
  *(volatile uint32_t*)((&var_name_tmp__118->field1)) = var_name_tmp__117;
}


void ADC_TempSensorVrefintCmd(uint32_t var_name_tmp__119) {
  uint32_t var_name_tmp__120;    /* Address-exposed local */
  uint32_t var_name_tmp__121;
  uint32_t var_name_tmp__122;
  uint32_t var_name_tmp__123;

  var_name_tmp__120 = var_name_tmp__119;
  var_name_tmp__121 = var_name_tmp__120;
  if ((((var_name_tmp__121 != 0u)&1))) {
    goto var_name_tmp__124;
  } else {
    goto var_name_tmp__125;
  }

var_name_tmp__124:
  var_name_tmp__122 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__122 | 8388608);
  goto var_name_tmp__126;

var_name_tmp__125:
  var_name_tmp__123 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__123 & -8388609);
  goto var_name_tmp__126;

var_name_tmp__126:
  return;
}


void ADC_VBATCmd(uint32_t var_name_tmp__127) {
  uint32_t var_name_tmp__128;    /* Address-exposed local */
  uint32_t var_name_tmp__129;
  uint32_t var_name_tmp__130;
  uint32_t var_name_tmp__131;

  var_name_tmp__128 = var_name_tmp__127;
  var_name_tmp__129 = var_name_tmp__128;
  if ((((var_name_tmp__129 != 0u)&1))) {
    goto var_name_tmp__132;
  } else {
    goto var_name_tmp__133;
  }

var_name_tmp__132:
  var_name_tmp__130 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__130 | 4194304);
  goto var_name_tmp__134;

var_name_tmp__133:
  var_name_tmp__131 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__131 & -4194305);
  goto var_name_tmp__134;

var_name_tmp__134:
  return;
}


void ADC_RegularChannelConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__135, uint8_t var_name_tmp__136, uint8_t var_name_tmp__137, uint8_t var_name_tmp__138) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__139;    /* Address-exposed local */
  uint8_t var_name_tmp__140;    /* Address-exposed local */
  uint8_t var_name_tmp__141;    /* Address-exposed local */
  uint8_t var_name_tmp__142;    /* Address-exposed local */
  uint32_t var_name_tmp__143;    /* Address-exposed local */
  uint32_t var_name_tmp__144;    /* Address-exposed local */
  uint8_t var_name_tmp__145;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__146;
  uint32_t var_name_tmp__147;
  uint8_t var_name_tmp__148;
  uint32_t var_name_tmp__149;
  uint32_t var_name_tmp__150;
  uint8_t var_name_tmp__151;
  uint8_t var_name_tmp__152;
  uint32_t var_name_tmp__153;
  uint32_t var_name_tmp__154;
  uint32_t var_name_tmp__155;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__156;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__157;
  uint32_t var_name_tmp__158;
  uint8_t var_name_tmp__159;
  uint32_t var_name_tmp__160;
  uint32_t var_name_tmp__161;
  uint8_t var_name_tmp__162;
  uint8_t var_name_tmp__163;
  uint32_t var_name_tmp__164;
  uint32_t var_name_tmp__165;
  uint32_t var_name_tmp__166;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__167;
  uint8_t var_name_tmp__168;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__169;
  uint32_t var_name_tmp__170;
  uint8_t var_name_tmp__171;
  uint32_t var_name_tmp__172;
  uint32_t var_name_tmp__173;
  uint8_t var_name_tmp__174;
  uint8_t var_name_tmp__175;
  uint32_t var_name_tmp__176;
  uint32_t var_name_tmp__177;
  uint32_t var_name_tmp__178;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__179;
  uint8_t var_name_tmp__180;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__181;
  uint32_t var_name_tmp__182;
  uint8_t var_name_tmp__183;
  uint32_t var_name_tmp__184;
  uint32_t var_name_tmp__185;
  uint8_t var_name_tmp__186;
  uint8_t var_name_tmp__187;
  uint32_t var_name_tmp__188;
  uint32_t var_name_tmp__189;
  uint32_t var_name_tmp__190;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__191;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__192;
  uint32_t var_name_tmp__193;
  uint8_t var_name_tmp__194;
  uint32_t var_name_tmp__195;
  uint32_t var_name_tmp__196;
  uint8_t var_name_tmp__197;
  uint8_t var_name_tmp__198;
  uint32_t var_name_tmp__199;
  uint32_t var_name_tmp__200;
  uint32_t var_name_tmp__201;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__202;

  var_name_tmp__139 = var_name_tmp__135;
  var_name_tmp__140 = var_name_tmp__136;
  var_name_tmp__141 = var_name_tmp__137;
  var_name_tmp__142 = var_name_tmp__138;
  var_name_tmp__143 = 0;
  var_name_tmp__144 = 0;
  var_name_tmp__145 = var_name_tmp__140;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__145))) > ((int32_t)9u))&1))) {
    goto var_name_tmp__203;
  } else {
    goto var_name_tmp__204;
  }

var_name_tmp__203:
  var_name_tmp__146 = var_name_tmp__139;
  var_name_tmp__147 = *(volatile uint32_t*)((&var_name_tmp__146->field3));
  var_name_tmp__143 = var_name_tmp__147;
  var_name_tmp__148 = var_name_tmp__140;
  var_name_tmp__144 = (7 << (llvm_mul_u32(3, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__148)), 10)))));
  var_name_tmp__149 = var_name_tmp__144;
  var_name_tmp__150 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__150 & (~(var_name_tmp__149)));
  var_name_tmp__151 = var_name_tmp__142;
  var_name_tmp__152 = var_name_tmp__140;
  var_name_tmp__144 = ((((uint32_t)(uint8_t)var_name_tmp__151)) << (llvm_mul_u32(3, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__152)), 10)))));
  var_name_tmp__153 = var_name_tmp__144;
  var_name_tmp__154 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__154 | var_name_tmp__153);
  var_name_tmp__155 = var_name_tmp__143;
  var_name_tmp__156 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__156->field3)) = var_name_tmp__155;
  goto var_name_tmp__205;

var_name_tmp__204:
  var_name_tmp__157 = var_name_tmp__139;
  var_name_tmp__158 = *(volatile uint32_t*)((&var_name_tmp__157->field4));
  var_name_tmp__143 = var_name_tmp__158;
  var_name_tmp__159 = var_name_tmp__140;
  var_name_tmp__144 = (7 << (llvm_mul_u32(3, (((uint32_t)(uint8_t)var_name_tmp__159)))));
  var_name_tmp__160 = var_name_tmp__144;
  var_name_tmp__161 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__161 & (~(var_name_tmp__160)));
  var_name_tmp__162 = var_name_tmp__142;
  var_name_tmp__163 = var_name_tmp__140;
  var_name_tmp__144 = ((((uint32_t)(uint8_t)var_name_tmp__162)) << (llvm_mul_u32(3, (((uint32_t)(uint8_t)var_name_tmp__163)))));
  var_name_tmp__164 = var_name_tmp__144;
  var_name_tmp__165 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__165 | var_name_tmp__164);
  var_name_tmp__166 = var_name_tmp__143;
  var_name_tmp__167 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__167->field4)) = var_name_tmp__166;
  goto var_name_tmp__205;

var_name_tmp__205:
  var_name_tmp__168 = var_name_tmp__141;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__168))) < ((int32_t)7u))&1))) {
    goto var_name_tmp__206;
  } else {
    goto var_name_tmp__207;
  }

var_name_tmp__206:
  var_name_tmp__169 = var_name_tmp__139;
  var_name_tmp__170 = *(volatile uint32_t*)((&var_name_tmp__169->field13));
  var_name_tmp__143 = var_name_tmp__170;
  var_name_tmp__171 = var_name_tmp__141;
  var_name_tmp__144 = (31 << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__171)), 1)))));
  var_name_tmp__172 = var_name_tmp__144;
  var_name_tmp__173 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__173 & (~(var_name_tmp__172)));
  var_name_tmp__174 = var_name_tmp__140;
  var_name_tmp__175 = var_name_tmp__141;
  var_name_tmp__144 = ((((uint32_t)(uint8_t)var_name_tmp__174)) << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__175)), 1)))));
  var_name_tmp__176 = var_name_tmp__144;
  var_name_tmp__177 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__177 | var_name_tmp__176);
  var_name_tmp__178 = var_name_tmp__143;
  var_name_tmp__179 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__179->field13)) = var_name_tmp__178;
  goto var_name_tmp__208;

var_name_tmp__207:
  var_name_tmp__180 = var_name_tmp__141;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__180))) < ((int32_t)13u))&1))) {
    goto var_name_tmp__209;
  } else {
    goto var_name_tmp__210;
  }

var_name_tmp__209:
  var_name_tmp__181 = var_name_tmp__139;
  var_name_tmp__182 = *(volatile uint32_t*)((&var_name_tmp__181->field12));
  var_name_tmp__143 = var_name_tmp__182;
  var_name_tmp__183 = var_name_tmp__141;
  var_name_tmp__144 = (31 << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__183)), 7)))));
  var_name_tmp__184 = var_name_tmp__144;
  var_name_tmp__185 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__185 & (~(var_name_tmp__184)));
  var_name_tmp__186 = var_name_tmp__140;
  var_name_tmp__187 = var_name_tmp__141;
  var_name_tmp__144 = ((((uint32_t)(uint8_t)var_name_tmp__186)) << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__187)), 7)))));
  var_name_tmp__188 = var_name_tmp__144;
  var_name_tmp__189 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__189 | var_name_tmp__188);
  var_name_tmp__190 = var_name_tmp__143;
  var_name_tmp__191 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__191->field12)) = var_name_tmp__190;
  goto var_name_tmp__211;

var_name_tmp__210:
  var_name_tmp__192 = var_name_tmp__139;
  var_name_tmp__193 = *(volatile uint32_t*)((&var_name_tmp__192->field11));
  var_name_tmp__143 = var_name_tmp__193;
  var_name_tmp__194 = var_name_tmp__141;
  var_name_tmp__144 = (31 << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__194)), 13)))));
  var_name_tmp__195 = var_name_tmp__144;
  var_name_tmp__196 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__196 & (~(var_name_tmp__195)));
  var_name_tmp__197 = var_name_tmp__140;
  var_name_tmp__198 = var_name_tmp__141;
  var_name_tmp__144 = ((((uint32_t)(uint8_t)var_name_tmp__197)) << (llvm_mul_u32(5, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__198)), 13)))));
  var_name_tmp__199 = var_name_tmp__144;
  var_name_tmp__200 = var_name_tmp__143;
  var_name_tmp__143 = (var_name_tmp__200 | var_name_tmp__199);
  var_name_tmp__201 = var_name_tmp__143;
  var_name_tmp__202 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__202->field11)) = var_name_tmp__201;
  goto var_name_tmp__211;

var_name_tmp__211:
  goto var_name_tmp__208;

var_name_tmp__208:
  return;
}


void ADC_SoftwareStartConv(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__212) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__213;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__214;
  uint32_t* var_name_tmp__215;
  uint32_t var_name_tmp__216;

  var_name_tmp__213 = var_name_tmp__212;
  var_name_tmp__214 = var_name_tmp__213;
  var_name_tmp__215 = (&var_name_tmp__214->field2);
  var_name_tmp__216 = *(volatile uint32_t*)var_name_tmp__215;
  *(volatile uint32_t*)var_name_tmp__215 = (var_name_tmp__216 | 1073741824u);
}


uint32_t ADC_GetSoftwareStartConvStatus(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__217) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__218;    /* Address-exposed local */
  uint32_t var_name_tmp__219;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__220;
  uint32_t var_name_tmp__221;
  uint32_t var_name_tmp__222;

  var_name_tmp__218 = var_name_tmp__217;
  var_name_tmp__219 = 0;
  var_name_tmp__220 = var_name_tmp__218;
  var_name_tmp__221 = *(volatile uint32_t*)((&var_name_tmp__220->field2));
  if (((((var_name_tmp__221 & 4194304) != 0u)&1))) {
    goto var_name_tmp__223;
  } else {
    goto var_name_tmp__224;
  }

var_name_tmp__223:
  var_name_tmp__219 = 1;
  goto var_name_tmp__225;

var_name_tmp__224:
  var_name_tmp__219 = 0;
  goto var_name_tmp__225;

var_name_tmp__225:
  var_name_tmp__222 = var_name_tmp__219;
  return var_name_tmp__222;
}


void ADC_EOCOnEachRegularChannelCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__226, uint32_t var_name_tmp__227) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__228;    /* Address-exposed local */
  uint32_t var_name_tmp__229;    /* Address-exposed local */
  uint32_t var_name_tmp__230;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__231;
  uint32_t* var_name_tmp__232;
  uint32_t var_name_tmp__233;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__234;
  uint32_t* var_name_tmp__235;
  uint32_t var_name_tmp__236;

  var_name_tmp__228 = var_name_tmp__226;
  var_name_tmp__229 = var_name_tmp__227;
  var_name_tmp__230 = var_name_tmp__229;
  if ((((var_name_tmp__230 != 0u)&1))) {
    goto var_name_tmp__237;
  } else {
    goto var_name_tmp__238;
  }

var_name_tmp__237:
  var_name_tmp__231 = var_name_tmp__228;
  var_name_tmp__232 = (&var_name_tmp__231->field2);
  var_name_tmp__233 = *(volatile uint32_t*)var_name_tmp__232;
  *(volatile uint32_t*)var_name_tmp__232 = (var_name_tmp__233 | 1024);
  goto var_name_tmp__239;

var_name_tmp__238:
  var_name_tmp__234 = var_name_tmp__228;
  var_name_tmp__235 = (&var_name_tmp__234->field2);
  var_name_tmp__236 = *(volatile uint32_t*)var_name_tmp__235;
  *(volatile uint32_t*)var_name_tmp__235 = (var_name_tmp__236 & -1025);
  goto var_name_tmp__239;

var_name_tmp__239:
  return;
}


void ADC_ContinuousModeCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__240, uint32_t var_name_tmp__241) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__242;    /* Address-exposed local */
  uint32_t var_name_tmp__243;    /* Address-exposed local */
  uint32_t var_name_tmp__244;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__245;
  uint32_t* var_name_tmp__246;
  uint32_t var_name_tmp__247;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__248;
  uint32_t* var_name_tmp__249;
  uint32_t var_name_tmp__250;

  var_name_tmp__242 = var_name_tmp__240;
  var_name_tmp__243 = var_name_tmp__241;
  var_name_tmp__244 = var_name_tmp__243;
  if ((((var_name_tmp__244 != 0u)&1))) {
    goto var_name_tmp__251;
  } else {
    goto var_name_tmp__252;
  }

var_name_tmp__251:
  var_name_tmp__245 = var_name_tmp__242;
  var_name_tmp__246 = (&var_name_tmp__245->field2);
  var_name_tmp__247 = *(volatile uint32_t*)var_name_tmp__246;
  *(volatile uint32_t*)var_name_tmp__246 = (var_name_tmp__247 | 2);
  goto var_name_tmp__253;

var_name_tmp__252:
  var_name_tmp__248 = var_name_tmp__242;
  var_name_tmp__249 = (&var_name_tmp__248->field2);
  var_name_tmp__250 = *(volatile uint32_t*)var_name_tmp__249;
  *(volatile uint32_t*)var_name_tmp__249 = (var_name_tmp__250 & -3);
  goto var_name_tmp__253;

var_name_tmp__253:
  return;
}


void ADC_DiscModeChannelCountConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__254, uint8_t var_name_tmp__255) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__256;    /* Address-exposed local */
  uint8_t var_name_tmp__257;    /* Address-exposed local */
  uint32_t var_name_tmp__258;    /* Address-exposed local */
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__260;
  uint32_t var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint8_t var_name_tmp__263;
  uint32_t var_name_tmp__264;
  uint32_t var_name_tmp__265;
  uint32_t var_name_tmp__266;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__267;

  var_name_tmp__256 = var_name_tmp__254;
  var_name_tmp__257 = var_name_tmp__255;
  var_name_tmp__258 = 0;
  var_name_tmp__259 = 0;
  var_name_tmp__260 = var_name_tmp__256;
  var_name_tmp__261 = *(volatile uint32_t*)((&var_name_tmp__260->field1));
  var_name_tmp__258 = var_name_tmp__261;
  var_name_tmp__262 = var_name_tmp__258;
  var_name_tmp__258 = (var_name_tmp__262 & -57345);
  var_name_tmp__263 = var_name_tmp__257;
  var_name_tmp__259 = (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__263)), 1));
  var_name_tmp__264 = var_name_tmp__259;
  var_name_tmp__265 = var_name_tmp__258;
  var_name_tmp__258 = (var_name_tmp__265 | (var_name_tmp__264 << 13));
  var_name_tmp__266 = var_name_tmp__258;
  var_name_tmp__267 = var_name_tmp__256;
  *(volatile uint32_t*)((&var_name_tmp__267->field1)) = var_name_tmp__266;
}


void ADC_DiscModeCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__268, uint32_t var_name_tmp__269) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__270;    /* Address-exposed local */
  uint32_t var_name_tmp__271;    /* Address-exposed local */
  uint32_t var_name_tmp__272;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__273;
  uint32_t* var_name_tmp__274;
  uint32_t var_name_tmp__275;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__276;
  uint32_t* var_name_tmp__277;
  uint32_t var_name_tmp__278;

  var_name_tmp__270 = var_name_tmp__268;
  var_name_tmp__271 = var_name_tmp__269;
  var_name_tmp__272 = var_name_tmp__271;
  if ((((var_name_tmp__272 != 0u)&1))) {
    goto var_name_tmp__279;
  } else {
    goto var_name_tmp__280;
  }

var_name_tmp__279:
  var_name_tmp__273 = var_name_tmp__270;
  var_name_tmp__274 = (&var_name_tmp__273->field1);
  var_name_tmp__275 = *(volatile uint32_t*)var_name_tmp__274;
  *(volatile uint32_t*)var_name_tmp__274 = (var_name_tmp__275 | 2048);
  goto var_name_tmp__281;

var_name_tmp__280:
  var_name_tmp__276 = var_name_tmp__270;
  var_name_tmp__277 = (&var_name_tmp__276->field1);
  var_name_tmp__278 = *(volatile uint32_t*)var_name_tmp__277;
  *(volatile uint32_t*)var_name_tmp__277 = (var_name_tmp__278 & -2049);
  goto var_name_tmp__281;

var_name_tmp__281:
  return;
}


uint16_t ADC_GetConversionValue(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__282) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__283;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__284;
  uint32_t var_name_tmp__285;

  var_name_tmp__283 = var_name_tmp__282;
  var_name_tmp__284 = var_name_tmp__283;
  var_name_tmp__285 = *(volatile uint32_t*)((&var_name_tmp__284->field19));
  return (((uint16_t)var_name_tmp__285));
}


uint32_t ADC_GetMultiModeConversionValue(void) {
  uint32_t var_name_tmp__286;

  var_name_tmp__286 = *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1073816328));
  return var_name_tmp__286;
}


void ADC_DMACmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__287, uint32_t var_name_tmp__288) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__289;    /* Address-exposed local */
  uint32_t var_name_tmp__290;    /* Address-exposed local */
  uint32_t var_name_tmp__291;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__292;
  uint32_t* var_name_tmp__293;
  uint32_t var_name_tmp__294;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__295;
  uint32_t* var_name_tmp__296;
  uint32_t var_name_tmp__297;

  var_name_tmp__289 = var_name_tmp__287;
  var_name_tmp__290 = var_name_tmp__288;
  var_name_tmp__291 = var_name_tmp__290;
  if ((((var_name_tmp__291 != 0u)&1))) {
    goto var_name_tmp__298;
  } else {
    goto var_name_tmp__299;
  }

var_name_tmp__298:
  var_name_tmp__292 = var_name_tmp__289;
  var_name_tmp__293 = (&var_name_tmp__292->field2);
  var_name_tmp__294 = *(volatile uint32_t*)var_name_tmp__293;
  *(volatile uint32_t*)var_name_tmp__293 = (var_name_tmp__294 | 256);
  goto var_name_tmp__300;

var_name_tmp__299:
  var_name_tmp__295 = var_name_tmp__289;
  var_name_tmp__296 = (&var_name_tmp__295->field2);
  var_name_tmp__297 = *(volatile uint32_t*)var_name_tmp__296;
  *(volatile uint32_t*)var_name_tmp__296 = (var_name_tmp__297 & -257);
  goto var_name_tmp__300;

var_name_tmp__300:
  return;
}


void ADC_DMARequestAfterLastTransferCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__301, uint32_t var_name_tmp__302) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__303;    /* Address-exposed local */
  uint32_t var_name_tmp__304;    /* Address-exposed local */
  uint32_t var_name_tmp__305;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__306;
  uint32_t* var_name_tmp__307;
  uint32_t var_name_tmp__308;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__309;
  uint32_t* var_name_tmp__310;
  uint32_t var_name_tmp__311;

  var_name_tmp__303 = var_name_tmp__301;
  var_name_tmp__304 = var_name_tmp__302;
  var_name_tmp__305 = var_name_tmp__304;
  if ((((var_name_tmp__305 != 0u)&1))) {
    goto var_name_tmp__312;
  } else {
    goto var_name_tmp__313;
  }

var_name_tmp__312:
  var_name_tmp__306 = var_name_tmp__303;
  var_name_tmp__307 = (&var_name_tmp__306->field2);
  var_name_tmp__308 = *(volatile uint32_t*)var_name_tmp__307;
  *(volatile uint32_t*)var_name_tmp__307 = (var_name_tmp__308 | 512);
  goto var_name_tmp__314;

var_name_tmp__313:
  var_name_tmp__309 = var_name_tmp__303;
  var_name_tmp__310 = (&var_name_tmp__309->field2);
  var_name_tmp__311 = *(volatile uint32_t*)var_name_tmp__310;
  *(volatile uint32_t*)var_name_tmp__310 = (var_name_tmp__311 & -513);
  goto var_name_tmp__314;

var_name_tmp__314:
  return;
}


void ADC_MultiModeDMARequestAfterLastTransferCmd(uint32_t var_name_tmp__315) {
  uint32_t var_name_tmp__316;    /* Address-exposed local */
  uint32_t var_name_tmp__317;
  uint32_t var_name_tmp__318;
  uint32_t var_name_tmp__319;

  var_name_tmp__316 = var_name_tmp__315;
  var_name_tmp__317 = var_name_tmp__316;
  if ((((var_name_tmp__317 != 0u)&1))) {
    goto var_name_tmp__320;
  } else {
    goto var_name_tmp__321;
  }

var_name_tmp__320:
  var_name_tmp__318 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__318 | 8192);
  goto var_name_tmp__322;

var_name_tmp__321:
  var_name_tmp__319 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_ADC_Common_TypeDef*)(uintptr_t)UINT64_C(1073816320))->field1)) = (var_name_tmp__319 & -8193);
  goto var_name_tmp__322;

var_name_tmp__322:
  return;
}


void ADC_InjectedChannelConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__323, uint8_t var_name_tmp__324, uint8_t var_name_tmp__325, uint8_t var_name_tmp__326) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__327;    /* Address-exposed local */
  uint8_t var_name_tmp__328;    /* Address-exposed local */
  uint8_t var_name_tmp__329;    /* Address-exposed local */
  uint8_t var_name_tmp__330;    /* Address-exposed local */
  uint32_t var_name_tmp__331;    /* Address-exposed local */
  uint32_t var_name_tmp__332;    /* Address-exposed local */
  uint32_t var_name_tmp__333;    /* Address-exposed local */
  uint8_t var_name_tmp__334;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__335;
  uint32_t var_name_tmp__336;
  uint8_t var_name_tmp__337;
  uint32_t var_name_tmp__338;
  uint32_t var_name_tmp__339;
  uint8_t var_name_tmp__340;
  uint8_t var_name_tmp__341;
  uint32_t var_name_tmp__342;
  uint32_t var_name_tmp__343;
  uint32_t var_name_tmp__344;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__345;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__346;
  uint32_t var_name_tmp__347;
  uint8_t var_name_tmp__348;
  uint32_t var_name_tmp__349;
  uint32_t var_name_tmp__350;
  uint8_t var_name_tmp__351;
  uint8_t var_name_tmp__352;
  uint32_t var_name_tmp__353;
  uint32_t var_name_tmp__354;
  uint32_t var_name_tmp__355;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__356;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__357;
  uint32_t var_name_tmp__358;
  uint32_t var_name_tmp__359;
  uint8_t var_name_tmp__360;
  uint32_t var_name_tmp__361;
  uint32_t var_name_tmp__362;
  uint32_t var_name_tmp__363;
  uint8_t var_name_tmp__364;
  uint8_t var_name_tmp__365;
  uint32_t var_name_tmp__366;
  uint32_t var_name_tmp__367;
  uint32_t var_name_tmp__368;
  uint32_t var_name_tmp__369;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__370;

  var_name_tmp__327 = var_name_tmp__323;
  var_name_tmp__328 = var_name_tmp__324;
  var_name_tmp__329 = var_name_tmp__325;
  var_name_tmp__330 = var_name_tmp__326;
  var_name_tmp__331 = 0;
  var_name_tmp__332 = 0;
  var_name_tmp__333 = 0;
  var_name_tmp__334 = var_name_tmp__328;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__334))) > ((int32_t)9u))&1))) {
    goto var_name_tmp__371;
  } else {
    goto var_name_tmp__372;
  }

var_name_tmp__371:
  var_name_tmp__335 = var_name_tmp__327;
  var_name_tmp__336 = *(volatile uint32_t*)((&var_name_tmp__335->field3));
  var_name_tmp__331 = var_name_tmp__336;
  var_name_tmp__337 = var_name_tmp__328;
  var_name_tmp__332 = (7 << (llvm_mul_u32(3, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__337)), 10)))));
  var_name_tmp__338 = var_name_tmp__332;
  var_name_tmp__339 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__339 & (~(var_name_tmp__338)));
  var_name_tmp__340 = var_name_tmp__330;
  var_name_tmp__341 = var_name_tmp__328;
  var_name_tmp__332 = ((((uint32_t)(uint8_t)var_name_tmp__340)) << (llvm_mul_u32(3, (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__341)), 10)))));
  var_name_tmp__342 = var_name_tmp__332;
  var_name_tmp__343 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__343 | var_name_tmp__342);
  var_name_tmp__344 = var_name_tmp__331;
  var_name_tmp__345 = var_name_tmp__327;
  *(volatile uint32_t*)((&var_name_tmp__345->field3)) = var_name_tmp__344;
  goto var_name_tmp__373;

var_name_tmp__372:
  var_name_tmp__346 = var_name_tmp__327;
  var_name_tmp__347 = *(volatile uint32_t*)((&var_name_tmp__346->field4));
  var_name_tmp__331 = var_name_tmp__347;
  var_name_tmp__348 = var_name_tmp__328;
  var_name_tmp__332 = (7 << (llvm_mul_u32(3, (((uint32_t)(uint8_t)var_name_tmp__348)))));
  var_name_tmp__349 = var_name_tmp__332;
  var_name_tmp__350 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__350 & (~(var_name_tmp__349)));
  var_name_tmp__351 = var_name_tmp__330;
  var_name_tmp__352 = var_name_tmp__328;
  var_name_tmp__332 = ((((uint32_t)(uint8_t)var_name_tmp__351)) << (llvm_mul_u32(3, (((uint32_t)(uint8_t)var_name_tmp__352)))));
  var_name_tmp__353 = var_name_tmp__332;
  var_name_tmp__354 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__354 | var_name_tmp__353);
  var_name_tmp__355 = var_name_tmp__331;
  var_name_tmp__356 = var_name_tmp__327;
  *(volatile uint32_t*)((&var_name_tmp__356->field4)) = var_name_tmp__355;
  goto var_name_tmp__373;

var_name_tmp__373:
  var_name_tmp__357 = var_name_tmp__327;
  var_name_tmp__358 = *(volatile uint32_t*)((&var_name_tmp__357->field14));
  var_name_tmp__331 = var_name_tmp__358;
  var_name_tmp__359 = var_name_tmp__331;
  var_name_tmp__333 = (llvm_lshr_u32((var_name_tmp__359 & 3145728), 20));
  var_name_tmp__360 = var_name_tmp__329;
  var_name_tmp__361 = var_name_tmp__333;
  var_name_tmp__332 = (31 << (llvm_mul_u32(5, (((uint32_t)(uint8_t)(((uint8_t)(llvm_sub_u32((llvm_add_u32((((uint32_t)(uint8_t)var_name_tmp__360)), 3)), (llvm_add_u32(var_name_tmp__361, 1)))))))))));
  var_name_tmp__362 = var_name_tmp__332;
  var_name_tmp__363 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__363 & (~(var_name_tmp__362)));
  var_name_tmp__364 = var_name_tmp__328;
  var_name_tmp__365 = var_name_tmp__329;
  var_name_tmp__366 = var_name_tmp__333;
  var_name_tmp__332 = ((((uint32_t)(uint8_t)var_name_tmp__364)) << (llvm_mul_u32(5, (((uint32_t)(uint8_t)(((uint8_t)(llvm_sub_u32((llvm_add_u32((((uint32_t)(uint8_t)var_name_tmp__365)), 3)), (llvm_add_u32(var_name_tmp__366, 1)))))))))));
  var_name_tmp__367 = var_name_tmp__332;
  var_name_tmp__368 = var_name_tmp__331;
  var_name_tmp__331 = (var_name_tmp__368 | var_name_tmp__367);
  var_name_tmp__369 = var_name_tmp__331;
  var_name_tmp__370 = var_name_tmp__327;
  *(volatile uint32_t*)((&var_name_tmp__370->field14)) = var_name_tmp__369;
}


void ADC_InjectedSequencerLengthConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__374, uint8_t var_name_tmp__375) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__376;    /* Address-exposed local */
  uint8_t var_name_tmp__377;    /* Address-exposed local */
  uint32_t var_name_tmp__378;    /* Address-exposed local */
  uint32_t var_name_tmp__379;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__380;
  uint32_t var_name_tmp__381;
  uint32_t var_name_tmp__382;
  uint8_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint32_t var_name_tmp__385;
  uint32_t var_name_tmp__386;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__387;

  var_name_tmp__376 = var_name_tmp__374;
  var_name_tmp__377 = var_name_tmp__375;
  var_name_tmp__378 = 0;
  var_name_tmp__379 = 0;
  var_name_tmp__380 = var_name_tmp__376;
  var_name_tmp__381 = *(volatile uint32_t*)((&var_name_tmp__380->field14));
  var_name_tmp__378 = var_name_tmp__381;
  var_name_tmp__382 = var_name_tmp__378;
  var_name_tmp__378 = (var_name_tmp__382 & -3145729);
  var_name_tmp__383 = var_name_tmp__377;
  var_name_tmp__379 = (llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__383)), 1));
  var_name_tmp__384 = var_name_tmp__379;
  var_name_tmp__385 = var_name_tmp__378;
  var_name_tmp__378 = (var_name_tmp__385 | (var_name_tmp__384 << 20));
  var_name_tmp__386 = var_name_tmp__378;
  var_name_tmp__387 = var_name_tmp__376;
  *(volatile uint32_t*)((&var_name_tmp__387->field14)) = var_name_tmp__386;
}


void ADC_SetInjectedOffset(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__388, uint8_t var_name_tmp__389, uint16_t var_name_tmp__390) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__391;    /* Address-exposed local */
  uint8_t var_name_tmp__392;    /* Address-exposed local */
  uint16_t var_name_tmp__393;    /* Address-exposed local */
  uint32_t var_name_tmp__394;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__395;
  uint8_t var_name_tmp__396;
  uint32_t var_name_tmp__397;
  uint16_t var_name_tmp__398;
  uint32_t var_name_tmp__399;

  var_name_tmp__391 = var_name_tmp__388;
  var_name_tmp__392 = var_name_tmp__389;
  var_name_tmp__393 = var_name_tmp__390;
  *(volatile uint32_t*)(&var_name_tmp__394) = 0;
  var_name_tmp__395 = var_name_tmp__391;
  *(volatile uint32_t*)(&var_name_tmp__394) = (((uint32_t)(uintptr_t)var_name_tmp__395));
  var_name_tmp__396 = var_name_tmp__392;
  var_name_tmp__397 = *(volatile uint32_t*)(&var_name_tmp__394);
  *(volatile uint32_t*)(&var_name_tmp__394) = (llvm_add_u32(var_name_tmp__397, (((uint32_t)(uint8_t)var_name_tmp__396))));
  var_name_tmp__398 = var_name_tmp__393;
  var_name_tmp__399 = *(volatile uint32_t*)(&var_name_tmp__394);
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__399)))) = (((uint32_t)(uint16_t)var_name_tmp__398));
}


void ADC_ExternalTrigInjectedConvConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__400, uint32_t var_name_tmp__401) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__402;    /* Address-exposed local */
  uint32_t var_name_tmp__403;    /* Address-exposed local */
  uint32_t var_name_tmp__404;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__405;
  uint32_t var_name_tmp__406;
  uint32_t var_name_tmp__407;
  uint32_t var_name_tmp__408;
  uint32_t var_name_tmp__409;
  uint32_t var_name_tmp__410;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__411;

  var_name_tmp__402 = var_name_tmp__400;
  var_name_tmp__403 = var_name_tmp__401;
  var_name_tmp__404 = 0;
  var_name_tmp__405 = var_name_tmp__402;
  var_name_tmp__406 = *(volatile uint32_t*)((&var_name_tmp__405->field2));
  var_name_tmp__404 = var_name_tmp__406;
  var_name_tmp__407 = var_name_tmp__404;
  var_name_tmp__404 = (var_name_tmp__407 & -983041);
  var_name_tmp__408 = var_name_tmp__403;
  var_name_tmp__409 = var_name_tmp__404;
  var_name_tmp__404 = (var_name_tmp__409 | var_name_tmp__408);
  var_name_tmp__410 = var_name_tmp__404;
  var_name_tmp__411 = var_name_tmp__402;
  *(volatile uint32_t*)((&var_name_tmp__411->field2)) = var_name_tmp__410;
}


void ADC_ExternalTrigInjectedConvEdgeConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__412, uint32_t var_name_tmp__413) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__414;    /* Address-exposed local */
  uint32_t var_name_tmp__415;    /* Address-exposed local */
  uint32_t var_name_tmp__416;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__417;
  uint32_t var_name_tmp__418;
  uint32_t var_name_tmp__419;
  uint32_t var_name_tmp__420;
  uint32_t var_name_tmp__421;
  uint32_t var_name_tmp__422;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__423;

  var_name_tmp__414 = var_name_tmp__412;
  var_name_tmp__415 = var_name_tmp__413;
  var_name_tmp__416 = 0;
  var_name_tmp__417 = var_name_tmp__414;
  var_name_tmp__418 = *(volatile uint32_t*)((&var_name_tmp__417->field2));
  var_name_tmp__416 = var_name_tmp__418;
  var_name_tmp__419 = var_name_tmp__416;
  var_name_tmp__416 = (var_name_tmp__419 & -3145729);
  var_name_tmp__420 = var_name_tmp__415;
  var_name_tmp__421 = var_name_tmp__416;
  var_name_tmp__416 = (var_name_tmp__421 | var_name_tmp__420);
  var_name_tmp__422 = var_name_tmp__416;
  var_name_tmp__423 = var_name_tmp__414;
  *(volatile uint32_t*)((&var_name_tmp__423->field2)) = var_name_tmp__422;
}


void ADC_SoftwareStartInjectedConv(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__424) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__425;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__426;
  uint32_t* var_name_tmp__427;
  uint32_t var_name_tmp__428;

  var_name_tmp__425 = var_name_tmp__424;
  var_name_tmp__426 = var_name_tmp__425;
  var_name_tmp__427 = (&var_name_tmp__426->field2);
  var_name_tmp__428 = *(volatile uint32_t*)var_name_tmp__427;
  *(volatile uint32_t*)var_name_tmp__427 = (var_name_tmp__428 | 4194304);
}


uint32_t ADC_GetSoftwareStartInjectedConvCmdStatus(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__429) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__430;    /* Address-exposed local */
  uint32_t var_name_tmp__431;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__432;
  uint32_t var_name_tmp__433;
  uint32_t var_name_tmp__434;

  var_name_tmp__430 = var_name_tmp__429;
  var_name_tmp__431 = 0;
  var_name_tmp__432 = var_name_tmp__430;
  var_name_tmp__433 = *(volatile uint32_t*)((&var_name_tmp__432->field2));
  if (((((var_name_tmp__433 & 4194304) != 0u)&1))) {
    goto var_name_tmp__435;
  } else {
    goto var_name_tmp__436;
  }

var_name_tmp__435:
  var_name_tmp__431 = 1;
  goto var_name_tmp__437;

var_name_tmp__436:
  var_name_tmp__431 = 0;
  goto var_name_tmp__437;

var_name_tmp__437:
  var_name_tmp__434 = var_name_tmp__431;
  return var_name_tmp__434;
}


void ADC_AutoInjectedConvCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__438, uint32_t var_name_tmp__439) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__440;    /* Address-exposed local */
  uint32_t var_name_tmp__441;    /* Address-exposed local */
  uint32_t var_name_tmp__442;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__443;
  uint32_t* var_name_tmp__444;
  uint32_t var_name_tmp__445;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__446;
  uint32_t* var_name_tmp__447;
  uint32_t var_name_tmp__448;

  var_name_tmp__440 = var_name_tmp__438;
  var_name_tmp__441 = var_name_tmp__439;
  var_name_tmp__442 = var_name_tmp__441;
  if ((((var_name_tmp__442 != 0u)&1))) {
    goto var_name_tmp__449;
  } else {
    goto var_name_tmp__450;
  }

var_name_tmp__449:
  var_name_tmp__443 = var_name_tmp__440;
  var_name_tmp__444 = (&var_name_tmp__443->field1);
  var_name_tmp__445 = *(volatile uint32_t*)var_name_tmp__444;
  *(volatile uint32_t*)var_name_tmp__444 = (var_name_tmp__445 | 1024);
  goto var_name_tmp__451;

var_name_tmp__450:
  var_name_tmp__446 = var_name_tmp__440;
  var_name_tmp__447 = (&var_name_tmp__446->field1);
  var_name_tmp__448 = *(volatile uint32_t*)var_name_tmp__447;
  *(volatile uint32_t*)var_name_tmp__447 = (var_name_tmp__448 & -1025);
  goto var_name_tmp__451;

var_name_tmp__451:
  return;
}


void ADC_InjectedDiscModeCmd(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__452, uint32_t var_name_tmp__453) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__454;    /* Address-exposed local */
  uint32_t var_name_tmp__455;    /* Address-exposed local */
  uint32_t var_name_tmp__456;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__457;
  uint32_t* var_name_tmp__458;
  uint32_t var_name_tmp__459;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__460;
  uint32_t* var_name_tmp__461;
  uint32_t var_name_tmp__462;

  var_name_tmp__454 = var_name_tmp__452;
  var_name_tmp__455 = var_name_tmp__453;
  var_name_tmp__456 = var_name_tmp__455;
  if ((((var_name_tmp__456 != 0u)&1))) {
    goto var_name_tmp__463;
  } else {
    goto var_name_tmp__464;
  }

var_name_tmp__463:
  var_name_tmp__457 = var_name_tmp__454;
  var_name_tmp__458 = (&var_name_tmp__457->field1);
  var_name_tmp__459 = *(volatile uint32_t*)var_name_tmp__458;
  *(volatile uint32_t*)var_name_tmp__458 = (var_name_tmp__459 | 4096);
  goto var_name_tmp__465;

var_name_tmp__464:
  var_name_tmp__460 = var_name_tmp__454;
  var_name_tmp__461 = (&var_name_tmp__460->field1);
  var_name_tmp__462 = *(volatile uint32_t*)var_name_tmp__461;
  *(volatile uint32_t*)var_name_tmp__461 = (var_name_tmp__462 & -4097);
  goto var_name_tmp__465;

var_name_tmp__465:
  return;
}


uint16_t ADC_GetInjectedConversionValue(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__466, uint8_t var_name_tmp__467) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__468;    /* Address-exposed local */
  uint8_t var_name_tmp__469;    /* Address-exposed local */
  uint32_t var_name_tmp__470;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__471;
  uint8_t var_name_tmp__472;
  uint32_t var_name_tmp__473;
  uint32_t var_name_tmp__474;
  uint32_t var_name_tmp__475;

  var_name_tmp__468 = var_name_tmp__466;
  var_name_tmp__469 = var_name_tmp__467;
  *(volatile uint32_t*)(&var_name_tmp__470) = 0;
  var_name_tmp__471 = var_name_tmp__468;
  *(volatile uint32_t*)(&var_name_tmp__470) = (((uint32_t)(uintptr_t)var_name_tmp__471));
  var_name_tmp__472 = var_name_tmp__469;
  var_name_tmp__473 = *(volatile uint32_t*)(&var_name_tmp__470);
  *(volatile uint32_t*)(&var_name_tmp__470) = (llvm_add_u32(var_name_tmp__473, (llvm_add_u32((((uint32_t)(uint8_t)var_name_tmp__472)), 40))));
  var_name_tmp__474 = *(volatile uint32_t*)(&var_name_tmp__470);
  var_name_tmp__475 = *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__474))));
  return (((uint16_t)var_name_tmp__475));
}


void ADC_ITConfig(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__476, uint16_t var_name_tmp__477, uint32_t var_name_tmp__478) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__479;    /* Address-exposed local */
  uint16_t var_name_tmp__480;    /* Address-exposed local */
  uint32_t var_name_tmp__481;    /* Address-exposed local */
  uint32_t var_name_tmp__482;    /* Address-exposed local */
  uint16_t var_name_tmp__483;
  uint32_t var_name_tmp__484;
  uint32_t var_name_tmp__485;
  uint32_t var_name_tmp__486;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__487;
  uint32_t* var_name_tmp__488;
  uint32_t var_name_tmp__489;
  uint32_t var_name_tmp__490;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__491;
  uint32_t* var_name_tmp__492;
  uint32_t var_name_tmp__493;

  var_name_tmp__479 = var_name_tmp__476;
  var_name_tmp__480 = var_name_tmp__477;
  var_name_tmp__481 = var_name_tmp__478;
  var_name_tmp__482 = 0;
  var_name_tmp__483 = var_name_tmp__480;
  var_name_tmp__482 = (((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__483))));
  var_name_tmp__484 = var_name_tmp__482;
  var_name_tmp__482 = (1 << var_name_tmp__484);
  var_name_tmp__485 = var_name_tmp__481;
  if ((((var_name_tmp__485 != 0u)&1))) {
    goto var_name_tmp__494;
  } else {
    goto var_name_tmp__495;
  }

var_name_tmp__494:
  var_name_tmp__486 = var_name_tmp__482;
  var_name_tmp__487 = var_name_tmp__479;
  var_name_tmp__488 = (&var_name_tmp__487->field1);
  var_name_tmp__489 = *(volatile uint32_t*)var_name_tmp__488;
  *(volatile uint32_t*)var_name_tmp__488 = (var_name_tmp__489 | var_name_tmp__486);
  goto var_name_tmp__496;

var_name_tmp__495:
  var_name_tmp__490 = var_name_tmp__482;
  var_name_tmp__491 = var_name_tmp__479;
  var_name_tmp__492 = (&var_name_tmp__491->field1);
  var_name_tmp__493 = *(volatile uint32_t*)var_name_tmp__492;
  *(volatile uint32_t*)var_name_tmp__492 = (var_name_tmp__493 & (~(var_name_tmp__490)));
  goto var_name_tmp__496;

var_name_tmp__496:
  return;
}


uint32_t ADC_GetFlagStatus(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__497, uint8_t var_name_tmp__498) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__499;    /* Address-exposed local */
  uint8_t var_name_tmp__500;    /* Address-exposed local */
  uint32_t var_name_tmp__501;    /* Address-exposed local */
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__502;
  uint32_t var_name_tmp__503;
  uint8_t var_name_tmp__504;
  uint32_t var_name_tmp__505;

  var_name_tmp__499 = var_name_tmp__497;
  var_name_tmp__500 = var_name_tmp__498;
  var_name_tmp__501 = 0;
  var_name_tmp__502 = var_name_tmp__499;
  var_name_tmp__503 = *(volatile uint32_t*)((&var_name_tmp__502->field0));
  var_name_tmp__504 = var_name_tmp__500;
  if (((((var_name_tmp__503 & (((uint32_t)(uint8_t)var_name_tmp__504))) != 0u)&1))) {
    goto var_name_tmp__506;
  } else {
    goto var_name_tmp__507;
  }

var_name_tmp__506:
  var_name_tmp__501 = 1;
  goto var_name_tmp__508;

var_name_tmp__507:
  var_name_tmp__501 = 0;
  goto var_name_tmp__508;

var_name_tmp__508:
  var_name_tmp__505 = var_name_tmp__501;
  return var_name_tmp__505;
}


void ADC_ClearFlag(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__509, uint8_t var_name_tmp__510) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__511;    /* Address-exposed local */
  uint8_t var_name_tmp__512;    /* Address-exposed local */
  uint8_t var_name_tmp__513;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__514;

  var_name_tmp__511 = var_name_tmp__509;
  var_name_tmp__512 = var_name_tmp__510;
  var_name_tmp__513 = var_name_tmp__512;
  var_name_tmp__514 = var_name_tmp__511;
  *(volatile uint32_t*)((&var_name_tmp__514->field0)) = (~((((uint32_t)(uint8_t)var_name_tmp__513))));
}


uint32_t ADC_GetITStatus(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__515, uint16_t var_name_tmp__516) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__517;    /* Address-exposed local */
  uint16_t var_name_tmp__518;    /* Address-exposed local */
  uint32_t var_name_tmp__519;    /* Address-exposed local */
  uint32_t var_name_tmp__520;    /* Address-exposed local */
  uint32_t var_name_tmp__521;    /* Address-exposed local */
  uint16_t var_name_tmp__522;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__523;
  uint32_t var_name_tmp__524;
  uint16_t var_name_tmp__525;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__526;
  uint32_t var_name_tmp__527;
  uint32_t var_name_tmp__528;
  uint32_t var_name_tmp__529;
  uint32_t var_name_tmp__530;

  var_name_tmp__517 = var_name_tmp__515;
  var_name_tmp__518 = var_name_tmp__516;
  var_name_tmp__519 = 0;
  var_name_tmp__520 = 0;
  var_name_tmp__521 = 0;
  var_name_tmp__522 = var_name_tmp__518;
  var_name_tmp__520 = (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__522)), 8));
  var_name_tmp__523 = var_name_tmp__517;
  var_name_tmp__524 = *(volatile uint32_t*)((&var_name_tmp__523->field1));
  var_name_tmp__525 = var_name_tmp__518;
  var_name_tmp__521 = (var_name_tmp__524 & (1 << (((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__525))))));
  var_name_tmp__526 = var_name_tmp__517;
  var_name_tmp__527 = *(volatile uint32_t*)((&var_name_tmp__526->field0));
  var_name_tmp__528 = var_name_tmp__520;
  if (((((var_name_tmp__527 & var_name_tmp__528) != 0u)&1))) {
    goto var_name_tmp__531;
  } else {
    goto var_name_tmp__532;
  }

var_name_tmp__531:
  var_name_tmp__529 = var_name_tmp__521;
  if ((((var_name_tmp__529 != 0u)&1))) {
    goto var_name_tmp__533;
  } else {
    goto var_name_tmp__532;
  }

var_name_tmp__533:
  var_name_tmp__519 = 1;
  goto var_name_tmp__534;

var_name_tmp__532:
  var_name_tmp__519 = 0;
  goto var_name_tmp__534;

var_name_tmp__534:
  var_name_tmp__530 = var_name_tmp__519;
  return var_name_tmp__530;
}


void ADC_ClearITPendingBit(struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__535, uint16_t var_name_tmp__536) {
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__537;    /* Address-exposed local */
  uint16_t var_name_tmp__538;    /* Address-exposed local */
  uint8_t var_name_tmp__539;    /* Address-exposed local */
  uint16_t var_name_tmp__540;
  uint8_t var_name_tmp__541;
  struct l_struct_struct_OC_ADC_TypeDef* var_name_tmp__542;

  var_name_tmp__537 = var_name_tmp__535;
  var_name_tmp__538 = var_name_tmp__536;
  var_name_tmp__539 = 0;
  var_name_tmp__540 = var_name_tmp__538;
  var_name_tmp__539 = (((uint8_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__540)), 8))));
  var_name_tmp__541 = var_name_tmp__539;
  var_name_tmp__542 = var_name_tmp__537;
  *(volatile uint32_t*)((&var_name_tmp__542->field0)) = (~((((uint32_t)(uint8_t)var_name_tmp__541))));
}

