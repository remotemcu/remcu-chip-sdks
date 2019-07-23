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
struct l_struct_struct_OC_TIM_TypeDef;
struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef;
struct l_struct_struct_OC_TIM_OCInitTypeDef;
struct l_struct_struct_OC_TIM_ICInitTypeDef;
struct l_struct_struct_OC_TIM_BDTRInitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_TIM_TypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint16_t field5;
  uint16_t field6;
  uint16_t field7;
  uint16_t field8;
  uint16_t field9;
  uint16_t field10;
  uint16_t field11;
  uint16_t field12;
  uint16_t field13;
  uint16_t field14;
  uint16_t field15;
  uint16_t field16;
  uint16_t field17;
  uint32_t field18;
  uint16_t field19;
  uint16_t field20;
  uint32_t field21;
  uint16_t field22;
  uint16_t field23;
  uint32_t field24;
  uint32_t field25;
  uint32_t field26;
  uint32_t field27;
  uint16_t field28;
  uint16_t field29;
  uint16_t field30;
  uint16_t field31;
  uint16_t field32;
  uint16_t field33;
  uint16_t field34;
  uint16_t field35;
};
struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint32_t field2;
  uint16_t field3;
  uint8_t field4;
};
struct l_struct_struct_OC_TIM_OCInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint32_t field3;
  uint16_t field4;
  uint16_t field5;
  uint16_t field6;
  uint16_t field7;
};
struct l_struct_struct_OC_TIM_ICInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
};
struct l_struct_struct_OC_TIM_BDTRInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint16_t field5;
  uint16_t field6;
};

/* Function Declarations */
void TIM_DeInit(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void TIM_TimeBaseInit(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_TimeBaseStructInit(struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_PrescalerConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_CounterModeConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetCounter(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetAutoreload(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetCounter(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t TIM_GetPrescaler(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_UpdateDisableConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_UpdateRequestConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ARRPreloadConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectOnePulseMode(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetClockDivision(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_Cmd(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC1Init(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_OCInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC2Init(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_OCInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC3Init(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_OCInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC4Init(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_OCInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OCStructInit(struct l_struct_struct_OC_TIM_OCInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectOCxM(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetCompare1(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetCompare2(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetCompare3(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetCompare4(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ForcedOC1Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ForcedOC2Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ForcedOC3Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ForcedOC4Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC1PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC2PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC3PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC4PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC1FastConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC2FastConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC3FastConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC4FastConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearOC1Ref(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearOC2Ref(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearOC3Ref(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearOC4Ref(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC1PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC1NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC2PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC2NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC3PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC3NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_OC4PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_CCxCmd(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_CCxNCmd(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ICInit(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_ICInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
static void TI1_Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetIC1Prescaler(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
static void TI2_Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetIC2Prescaler(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
static void TI3_Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetIC3Prescaler(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
static void TI4_Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SetIC4Prescaler(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ICStructInit(struct l_struct_struct_OC_TIM_ICInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_PWMIConfig(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_ICInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetCapture1(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetCapture2(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetCapture3(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetCapture4(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_BDTRConfig(struct l_struct_struct_OC_TIM_TypeDef*, struct l_struct_struct_OC_TIM_BDTRInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_BDTRStructInit(struct l_struct_struct_OC_TIM_BDTRInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_CtrlPWMOutputs(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectCOM(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_CCPreloadControl(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ITConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_GenerateEvent(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetFlagStatus(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearFlag(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t TIM_GetITStatus(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ClearITPendingBit(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_DMAConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_DMACmd(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectCCDMA(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_InternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ITRxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectInputTrigger(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_TIxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ETRClockMode1Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ETRConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_ETRClockMode2Config(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectOutputTrigger(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectSlaveMode(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectMasterSlaveMode(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_EncoderInterfaceConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t, uint16_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_SelectHallSensor(struct l_struct_struct_OC_TIM_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void TIM_RemapConfig(struct l_struct_struct_OC_TIM_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t get_TIM_CR1(struct l_struct_struct_OC_TIM_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_sub_u32(uint32_t a, uint32_t b) {
  uint32_t r = a - b;
  return r;
}
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void TIM_DeInit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__4;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__5;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__6;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__7;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__8;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__9;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__10;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__11;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__12;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__13;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__14;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__15;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__16;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__17;
  } else {
    goto var_name_tmp__18;
  }

var_name_tmp__17:
  RCC_APB2PeriphResetCmd(1, 1);
  RCC_APB2PeriphResetCmd(1, 0);
  goto var_name_tmp__19;

var_name_tmp__18:
  var_name_tmp__4 = var_name_tmp__2;
  if ((((var_name_tmp__4 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073741824)))&1))) {
    goto var_name_tmp__20;
  } else {
    goto var_name_tmp__21;
  }

var_name_tmp__20:
  RCC_APB1PeriphResetCmd(1, 1);
  RCC_APB1PeriphResetCmd(1, 0);
  goto var_name_tmp__22;

var_name_tmp__21:
  var_name_tmp__5 = var_name_tmp__2;
  if ((((var_name_tmp__5 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073742848)))&1))) {
    goto var_name_tmp__23;
  } else {
    goto var_name_tmp__24;
  }

var_name_tmp__23:
  RCC_APB1PeriphResetCmd(2, 1);
  RCC_APB1PeriphResetCmd(2, 0);
  goto var_name_tmp__25;

var_name_tmp__24:
  var_name_tmp__6 = var_name_tmp__2;
  if ((((var_name_tmp__6 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073743872)))&1))) {
    goto var_name_tmp__26;
  } else {
    goto var_name_tmp__27;
  }

var_name_tmp__26:
  RCC_APB1PeriphResetCmd(4, 1);
  RCC_APB1PeriphResetCmd(4, 0);
  goto var_name_tmp__28;

var_name_tmp__27:
  var_name_tmp__7 = var_name_tmp__2;
  if ((((var_name_tmp__7 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073744896)))&1))) {
    goto var_name_tmp__29;
  } else {
    goto var_name_tmp__30;
  }

var_name_tmp__29:
  RCC_APB1PeriphResetCmd(8, 1);
  RCC_APB1PeriphResetCmd(8, 0);
  goto var_name_tmp__31;

var_name_tmp__30:
  var_name_tmp__8 = var_name_tmp__2;
  if ((((var_name_tmp__8 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073745920)))&1))) {
    goto var_name_tmp__32;
  } else {
    goto var_name_tmp__33;
  }

var_name_tmp__32:
  RCC_APB1PeriphResetCmd(16, 1);
  RCC_APB1PeriphResetCmd(16, 0);
  goto var_name_tmp__34;

var_name_tmp__33:
  var_name_tmp__9 = var_name_tmp__2;
  if ((((var_name_tmp__9 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073746944)))&1))) {
    goto var_name_tmp__35;
  } else {
    goto var_name_tmp__36;
  }

var_name_tmp__35:
  RCC_APB1PeriphResetCmd(32, 1);
  RCC_APB1PeriphResetCmd(32, 0);
  goto var_name_tmp__37;

var_name_tmp__36:
  var_name_tmp__10 = var_name_tmp__2;
  if ((((var_name_tmp__10 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__38;
  } else {
    goto var_name_tmp__39;
  }

var_name_tmp__38:
  RCC_APB2PeriphResetCmd(2, 1);
  RCC_APB2PeriphResetCmd(2, 0);
  goto var_name_tmp__40;

var_name_tmp__39:
  var_name_tmp__11 = var_name_tmp__2;
  if ((((var_name_tmp__11 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073823744)))&1))) {
    goto var_name_tmp__41;
  } else {
    goto var_name_tmp__42;
  }

var_name_tmp__41:
  RCC_APB2PeriphResetCmd(65536, 1);
  RCC_APB2PeriphResetCmd(65536, 0);
  goto var_name_tmp__43;

var_name_tmp__42:
  var_name_tmp__12 = var_name_tmp__2;
  if ((((var_name_tmp__12 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073824768)))&1))) {
    goto var_name_tmp__44;
  } else {
    goto var_name_tmp__45;
  }

var_name_tmp__44:
  RCC_APB2PeriphResetCmd(131072, 1);
  RCC_APB2PeriphResetCmd(131072, 0);
  goto var_name_tmp__46;

var_name_tmp__45:
  var_name_tmp__13 = var_name_tmp__2;
  if ((((var_name_tmp__13 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073825792)))&1))) {
    goto var_name_tmp__47;
  } else {
    goto var_name_tmp__48;
  }

var_name_tmp__47:
  RCC_APB2PeriphResetCmd(262144, 1);
  RCC_APB2PeriphResetCmd(262144, 0);
  goto var_name_tmp__49;

var_name_tmp__48:
  var_name_tmp__14 = var_name_tmp__2;
  if ((((var_name_tmp__14 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073747968)))&1))) {
    goto var_name_tmp__50;
  } else {
    goto var_name_tmp__51;
  }

var_name_tmp__50:
  RCC_APB1PeriphResetCmd(64, 1);
  RCC_APB1PeriphResetCmd(64, 0);
  goto var_name_tmp__52;

var_name_tmp__51:
  var_name_tmp__15 = var_name_tmp__2;
  if ((((var_name_tmp__15 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073748992)))&1))) {
    goto var_name_tmp__53;
  } else {
    goto var_name_tmp__54;
  }

var_name_tmp__53:
  RCC_APB1PeriphResetCmd(128, 1);
  RCC_APB1PeriphResetCmd(128, 0);
  goto var_name_tmp__55;

var_name_tmp__54:
  var_name_tmp__16 = var_name_tmp__2;
  if ((((var_name_tmp__16 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073750016)))&1))) {
    goto var_name_tmp__56;
  } else {
    goto var_name_tmp__57;
  }

var_name_tmp__56:
  RCC_APB1PeriphResetCmd(256, 1);
  RCC_APB1PeriphResetCmd(256, 0);
  goto var_name_tmp__57;

var_name_tmp__57:
  goto var_name_tmp__55;

var_name_tmp__55:
  goto var_name_tmp__52;

var_name_tmp__52:
  goto var_name_tmp__49;

var_name_tmp__49:
  goto var_name_tmp__46;

var_name_tmp__46:
  goto var_name_tmp__43;

var_name_tmp__43:
  goto var_name_tmp__40;

var_name_tmp__40:
  goto var_name_tmp__37;

var_name_tmp__37:
  goto var_name_tmp__34;

var_name_tmp__34:
  goto var_name_tmp__31;

var_name_tmp__31:
  goto var_name_tmp__28;

var_name_tmp__28:
  goto var_name_tmp__25;

var_name_tmp__25:
  goto var_name_tmp__22;

var_name_tmp__22:
  goto var_name_tmp__19;

var_name_tmp__19:
  return;
}


void TIM_TimeBaseInit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__58, struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__59) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__60;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__61;    /* Address-exposed local */
  uint16_t var_name_tmp__62;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__63;
  uint16_t var_name_tmp__64;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__65;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__66;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__67;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__68;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__69;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__70;
  uint16_t var_name_tmp__71;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__72;
  uint16_t var_name_tmp__73;
  uint16_t var_name_tmp__74;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__75;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__76;
  uint16_t var_name_tmp__77;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__78;
  uint16_t var_name_tmp__79;
  uint16_t var_name_tmp__80;
  uint16_t var_name_tmp__81;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__82;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__83;
  uint32_t var_name_tmp__84;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__85;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__86;
  uint16_t var_name_tmp__87;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__88;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__89;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__90;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__91;
  uint8_t var_name_tmp__92;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__93;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__94;

  var_name_tmp__60 = var_name_tmp__58;
  var_name_tmp__61 = var_name_tmp__59;
  var_name_tmp__62 = 0;
  var_name_tmp__63 = var_name_tmp__60;
  var_name_tmp__64 = *(volatile uint16_t*)((&var_name_tmp__63->field0));
  var_name_tmp__62 = var_name_tmp__64;
  var_name_tmp__65 = var_name_tmp__60;
  if ((((var_name_tmp__65 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__96;
  }

var_name_tmp__96:
  var_name_tmp__66 = var_name_tmp__60;
  if ((((var_name_tmp__66 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__97;
  }

var_name_tmp__97:
  var_name_tmp__67 = var_name_tmp__60;
  if ((((var_name_tmp__67 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073741824)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__98;
  }

var_name_tmp__98:
  var_name_tmp__68 = var_name_tmp__60;
  if ((((var_name_tmp__68 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073742848)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__99;
  }

var_name_tmp__99:
  var_name_tmp__69 = var_name_tmp__60;
  if ((((var_name_tmp__69 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073743872)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__100;
  }

var_name_tmp__100:
  var_name_tmp__70 = var_name_tmp__60;
  if ((((var_name_tmp__70 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073744896)))&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__101;
  }

var_name_tmp__95:
  var_name_tmp__71 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__71)) & 65423)));
  var_name_tmp__72 = var_name_tmp__61;
  var_name_tmp__73 = *((&var_name_tmp__72->field1));
  var_name_tmp__74 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__74)) | (((uint32_t)(uint16_t)var_name_tmp__73)))));
  goto var_name_tmp__101;

var_name_tmp__101:
  var_name_tmp__75 = var_name_tmp__60;
  if ((((var_name_tmp__75 != ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073745920)))&1))) {
    goto var_name_tmp__102;
  } else {
    goto var_name_tmp__103;
  }

var_name_tmp__102:
  var_name_tmp__76 = var_name_tmp__60;
  if ((((var_name_tmp__76 != ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073746944)))&1))) {
    goto var_name_tmp__104;
  } else {
    goto var_name_tmp__103;
  }

var_name_tmp__104:
  var_name_tmp__77 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__77)) & 64767)));
  var_name_tmp__78 = var_name_tmp__61;
  var_name_tmp__79 = *((&var_name_tmp__78->field3));
  var_name_tmp__80 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__80)) | (((uint32_t)(uint16_t)var_name_tmp__79)))));
  goto var_name_tmp__103;

var_name_tmp__103:
  var_name_tmp__81 = var_name_tmp__62;
  var_name_tmp__82 = var_name_tmp__60;
  *(volatile uint16_t*)((&var_name_tmp__82->field0)) = var_name_tmp__81;
  var_name_tmp__83 = var_name_tmp__61;
  var_name_tmp__84 = *((&var_name_tmp__83->field2));
  var_name_tmp__85 = var_name_tmp__60;
  *(volatile uint32_t*)((&var_name_tmp__85->field21)) = var_name_tmp__84;
  var_name_tmp__86 = var_name_tmp__61;
  var_name_tmp__87 = *((&var_name_tmp__86->field0));
  var_name_tmp__88 = var_name_tmp__60;
  *(volatile uint16_t*)((&var_name_tmp__88->field19)) = var_name_tmp__87;
  var_name_tmp__89 = var_name_tmp__60;
  if ((((var_name_tmp__89 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__105;
  } else {
    goto var_name_tmp__106;
  }

var_name_tmp__106:
  var_name_tmp__90 = var_name_tmp__60;
  if ((((var_name_tmp__90 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__105;
  } else {
    goto var_name_tmp__107;
  }

var_name_tmp__105:
  var_name_tmp__91 = var_name_tmp__61;
  var_name_tmp__92 = *((&var_name_tmp__91->field4));
  var_name_tmp__93 = var_name_tmp__60;
  *(volatile uint16_t*)((&var_name_tmp__93->field22)) = (((uint16_t)(uint8_t)var_name_tmp__92));
  goto var_name_tmp__107;

var_name_tmp__107:
  var_name_tmp__94 = var_name_tmp__60;
  *(volatile uint16_t*)((&var_name_tmp__94->field10)) = 1;
}


void TIM_TimeBaseStructInit(struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__108) {
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__109;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__112;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__113;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__114;

  var_name_tmp__109 = var_name_tmp__108;
  var_name_tmp__110 = var_name_tmp__109;
  *((&var_name_tmp__110->field2)) = -1;
  var_name_tmp__111 = var_name_tmp__109;
  *((&var_name_tmp__111->field0)) = 0;
  var_name_tmp__112 = var_name_tmp__109;
  *((&var_name_tmp__112->field3)) = 0;
  var_name_tmp__113 = var_name_tmp__109;
  *((&var_name_tmp__113->field1)) = 0;
  var_name_tmp__114 = var_name_tmp__109;
  *((&var_name_tmp__114->field4)) = 0;
}


void TIM_PrescalerConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__115, uint16_t var_name_tmp__116, uint16_t var_name_tmp__117) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__118;    /* Address-exposed local */
  uint16_t var_name_tmp__119;    /* Address-exposed local */
  uint16_t var_name_tmp__120;    /* Address-exposed local */
  uint16_t var_name_tmp__121;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__122;
  uint16_t var_name_tmp__123;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__124;

  var_name_tmp__118 = var_name_tmp__115;
  var_name_tmp__119 = var_name_tmp__116;
  var_name_tmp__120 = var_name_tmp__117;
  var_name_tmp__121 = var_name_tmp__119;
  var_name_tmp__122 = var_name_tmp__118;
  *(volatile uint16_t*)((&var_name_tmp__122->field19)) = var_name_tmp__121;
  var_name_tmp__123 = var_name_tmp__120;
  var_name_tmp__124 = var_name_tmp__118;
  *(volatile uint16_t*)((&var_name_tmp__124->field10)) = var_name_tmp__123;
}


void TIM_CounterModeConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__125, uint16_t var_name_tmp__126) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__127;    /* Address-exposed local */
  uint16_t var_name_tmp__128;    /* Address-exposed local */
  uint16_t var_name_tmp__129;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__130;
  uint16_t var_name_tmp__131;
  uint16_t var_name_tmp__132;
  uint16_t var_name_tmp__133;
  uint16_t var_name_tmp__134;
  uint16_t var_name_tmp__135;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__136;

  var_name_tmp__127 = var_name_tmp__125;
  var_name_tmp__128 = var_name_tmp__126;
  var_name_tmp__129 = 0;
  var_name_tmp__130 = var_name_tmp__127;
  var_name_tmp__131 = *(volatile uint16_t*)((&var_name_tmp__130->field0));
  var_name_tmp__129 = var_name_tmp__131;
  var_name_tmp__132 = var_name_tmp__129;
  var_name_tmp__129 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__132)) & 65423)));
  var_name_tmp__133 = var_name_tmp__128;
  var_name_tmp__134 = var_name_tmp__129;
  var_name_tmp__129 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__134)) | (((uint32_t)(uint16_t)var_name_tmp__133)))));
  var_name_tmp__135 = var_name_tmp__129;
  var_name_tmp__136 = var_name_tmp__127;
  *(volatile uint16_t*)((&var_name_tmp__136->field0)) = var_name_tmp__135;
}


void TIM_SetCounter(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__137, uint32_t var_name_tmp__138) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__139;    /* Address-exposed local */
  uint32_t var_name_tmp__140;    /* Address-exposed local */
  uint32_t var_name_tmp__141;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__142;

  var_name_tmp__139 = var_name_tmp__137;
  var_name_tmp__140 = var_name_tmp__138;
  var_name_tmp__141 = var_name_tmp__140;
  var_name_tmp__142 = var_name_tmp__139;
  *(volatile uint32_t*)((&var_name_tmp__142->field18)) = var_name_tmp__141;
}


void TIM_SetAutoreload(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__143, uint32_t var_name_tmp__144) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__145;    /* Address-exposed local */
  uint32_t var_name_tmp__146;    /* Address-exposed local */
  uint32_t var_name_tmp__147;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__148;

  var_name_tmp__145 = var_name_tmp__143;
  var_name_tmp__146 = var_name_tmp__144;
  var_name_tmp__147 = var_name_tmp__146;
  var_name_tmp__148 = var_name_tmp__145;
  *(volatile uint32_t*)((&var_name_tmp__148->field21)) = var_name_tmp__147;
}


uint32_t TIM_GetCounter(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__149) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__150;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__151;
  uint32_t var_name_tmp__152;

  var_name_tmp__150 = var_name_tmp__149;
  var_name_tmp__151 = var_name_tmp__150;
  var_name_tmp__152 = *(volatile uint32_t*)((&var_name_tmp__151->field18));
  return var_name_tmp__152;
}


uint16_t TIM_GetPrescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__153) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__154;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__155;
  uint16_t var_name_tmp__156;

  var_name_tmp__154 = var_name_tmp__153;
  var_name_tmp__155 = var_name_tmp__154;
  var_name_tmp__156 = *(volatile uint16_t*)((&var_name_tmp__155->field19));
  return var_name_tmp__156;
}


void TIM_UpdateDisableConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__157, uint32_t var_name_tmp__158) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__159;    /* Address-exposed local */
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__162;
  uint16_t* var_name_tmp__163;
  uint16_t var_name_tmp__164;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__165;
  uint16_t* var_name_tmp__166;
  uint16_t var_name_tmp__167;

  var_name_tmp__159 = var_name_tmp__157;
  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__160;
  if ((((var_name_tmp__161 != 0u)&1))) {
    goto var_name_tmp__168;
  } else {
    goto var_name_tmp__169;
  }

var_name_tmp__168:
  var_name_tmp__162 = var_name_tmp__159;
  var_name_tmp__163 = (&var_name_tmp__162->field0);
  var_name_tmp__164 = *(volatile uint16_t*)var_name_tmp__163;
  *(volatile uint16_t*)var_name_tmp__163 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__164)) | 2)));
  goto var_name_tmp__170;

var_name_tmp__169:
  var_name_tmp__165 = var_name_tmp__159;
  var_name_tmp__166 = (&var_name_tmp__165->field0);
  var_name_tmp__167 = *(volatile uint16_t*)var_name_tmp__166;
  *(volatile uint16_t*)var_name_tmp__166 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__167)) & 65533)));
  goto var_name_tmp__170;

var_name_tmp__170:
  return;
}


void TIM_UpdateRequestConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__171, uint16_t var_name_tmp__172) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__173;    /* Address-exposed local */
  uint16_t var_name_tmp__174;    /* Address-exposed local */
  uint16_t var_name_tmp__175;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__176;
  uint16_t* var_name_tmp__177;
  uint16_t var_name_tmp__178;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__179;
  uint16_t* var_name_tmp__180;
  uint16_t var_name_tmp__181;

  var_name_tmp__173 = var_name_tmp__171;
  var_name_tmp__174 = var_name_tmp__172;
  var_name_tmp__175 = var_name_tmp__174;
  if (((((((uint32_t)(uint16_t)var_name_tmp__175)) != 0u)&1))) {
    goto var_name_tmp__182;
  } else {
    goto var_name_tmp__183;
  }

var_name_tmp__182:
  var_name_tmp__176 = var_name_tmp__173;
  var_name_tmp__177 = (&var_name_tmp__176->field0);
  var_name_tmp__178 = *(volatile uint16_t*)var_name_tmp__177;
  *(volatile uint16_t*)var_name_tmp__177 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__178)) | 4)));
  goto var_name_tmp__184;

var_name_tmp__183:
  var_name_tmp__179 = var_name_tmp__173;
  var_name_tmp__180 = (&var_name_tmp__179->field0);
  var_name_tmp__181 = *(volatile uint16_t*)var_name_tmp__180;
  *(volatile uint16_t*)var_name_tmp__180 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__181)) & 65531)));
  goto var_name_tmp__184;

var_name_tmp__184:
  return;
}


void TIM_ARRPreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__185, uint32_t var_name_tmp__186) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__187;    /* Address-exposed local */
  uint32_t var_name_tmp__188;    /* Address-exposed local */
  uint32_t var_name_tmp__189;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__190;
  uint16_t* var_name_tmp__191;
  uint16_t var_name_tmp__192;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__193;
  uint16_t* var_name_tmp__194;
  uint16_t var_name_tmp__195;

  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__186;
  var_name_tmp__189 = var_name_tmp__188;
  if ((((var_name_tmp__189 != 0u)&1))) {
    goto var_name_tmp__196;
  } else {
    goto var_name_tmp__197;
  }

var_name_tmp__196:
  var_name_tmp__190 = var_name_tmp__187;
  var_name_tmp__191 = (&var_name_tmp__190->field0);
  var_name_tmp__192 = *(volatile uint16_t*)var_name_tmp__191;
  *(volatile uint16_t*)var_name_tmp__191 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__192)) | 128)));
  goto var_name_tmp__198;

var_name_tmp__197:
  var_name_tmp__193 = var_name_tmp__187;
  var_name_tmp__194 = (&var_name_tmp__193->field0);
  var_name_tmp__195 = *(volatile uint16_t*)var_name_tmp__194;
  *(volatile uint16_t*)var_name_tmp__194 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__195)) & 65407)));
  goto var_name_tmp__198;

var_name_tmp__198:
  return;
}


void TIM_SelectOnePulseMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__199, uint16_t var_name_tmp__200) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__201;    /* Address-exposed local */
  uint16_t var_name_tmp__202;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__203;
  uint16_t* var_name_tmp__204;
  uint16_t var_name_tmp__205;
  uint16_t var_name_tmp__206;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__207;
  uint16_t* var_name_tmp__208;
  uint16_t var_name_tmp__209;

  var_name_tmp__201 = var_name_tmp__199;
  var_name_tmp__202 = var_name_tmp__200;
  var_name_tmp__203 = var_name_tmp__201;
  var_name_tmp__204 = (&var_name_tmp__203->field0);
  var_name_tmp__205 = *(volatile uint16_t*)var_name_tmp__204;
  *(volatile uint16_t*)var_name_tmp__204 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__205)) & 65527)));
  var_name_tmp__206 = var_name_tmp__202;
  var_name_tmp__207 = var_name_tmp__201;
  var_name_tmp__208 = (&var_name_tmp__207->field0);
  var_name_tmp__209 = *(volatile uint16_t*)var_name_tmp__208;
  *(volatile uint16_t*)var_name_tmp__208 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__209)) | (((uint32_t)(uint16_t)var_name_tmp__206)))));
}


void TIM_SetClockDivision(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__210, uint16_t var_name_tmp__211) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__212;    /* Address-exposed local */
  uint16_t var_name_tmp__213;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__214;
  uint16_t* var_name_tmp__215;
  uint16_t var_name_tmp__216;
  uint16_t var_name_tmp__217;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__218;
  uint16_t* var_name_tmp__219;
  uint16_t var_name_tmp__220;

  var_name_tmp__212 = var_name_tmp__210;
  var_name_tmp__213 = var_name_tmp__211;
  var_name_tmp__214 = var_name_tmp__212;
  var_name_tmp__215 = (&var_name_tmp__214->field0);
  var_name_tmp__216 = *(volatile uint16_t*)var_name_tmp__215;
  *(volatile uint16_t*)var_name_tmp__215 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__216)) & 64767)));
  var_name_tmp__217 = var_name_tmp__213;
  var_name_tmp__218 = var_name_tmp__212;
  var_name_tmp__219 = (&var_name_tmp__218->field0);
  var_name_tmp__220 = *(volatile uint16_t*)var_name_tmp__219;
  *(volatile uint16_t*)var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__220)) | (((uint32_t)(uint16_t)var_name_tmp__217)))));
}


void TIM_Cmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__221, uint32_t var_name_tmp__222) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__223;    /* Address-exposed local */
  uint32_t var_name_tmp__224;    /* Address-exposed local */
  uint32_t var_name_tmp__225;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__226;
  uint16_t* var_name_tmp__227;
  uint16_t var_name_tmp__228;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__229;
  uint16_t* var_name_tmp__230;
  uint16_t var_name_tmp__231;

  var_name_tmp__223 = var_name_tmp__221;
  var_name_tmp__224 = var_name_tmp__222;
  var_name_tmp__225 = var_name_tmp__224;
  if ((((var_name_tmp__225 != 0u)&1))) {
    goto var_name_tmp__232;
  } else {
    goto var_name_tmp__233;
  }

var_name_tmp__232:
  var_name_tmp__226 = var_name_tmp__223;
  var_name_tmp__227 = (&var_name_tmp__226->field0);
  var_name_tmp__228 = *(volatile uint16_t*)var_name_tmp__227;
  *(volatile uint16_t*)var_name_tmp__227 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__228)) | 1)));
  goto var_name_tmp__234;

var_name_tmp__233:
  var_name_tmp__229 = var_name_tmp__223;
  var_name_tmp__230 = (&var_name_tmp__229->field0);
  var_name_tmp__231 = *(volatile uint16_t*)var_name_tmp__230;
  *(volatile uint16_t*)var_name_tmp__230 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__231)) & 65534)));
  goto var_name_tmp__234;

var_name_tmp__234:
  return;
}


void TIM_OC1Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__235, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__236) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__237;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__238;    /* Address-exposed local */
  uint16_t var_name_tmp__239;    /* Address-exposed local */
  uint16_t var_name_tmp__240;    /* Address-exposed local */
  uint16_t var_name_tmp__241;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__242;
  uint16_t* var_name_tmp__243;
  uint16_t var_name_tmp__244;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__245;
  uint16_t var_name_tmp__246;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__247;
  uint16_t var_name_tmp__248;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__249;
  uint16_t var_name_tmp__250;
  uint16_t var_name_tmp__251;
  uint16_t var_name_tmp__252;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__253;
  uint16_t var_name_tmp__254;
  uint16_t var_name_tmp__255;
  uint16_t var_name_tmp__256;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__257;
  uint16_t var_name_tmp__258;
  uint16_t var_name_tmp__259;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__260;
  uint16_t var_name_tmp__261;
  uint16_t var_name_tmp__262;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__263;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__264;
  uint16_t var_name_tmp__265;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__266;
  uint16_t var_name_tmp__267;
  uint16_t var_name_tmp__268;
  uint16_t var_name_tmp__269;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__270;
  uint16_t var_name_tmp__271;
  uint16_t var_name_tmp__272;
  uint16_t var_name_tmp__273;
  uint16_t var_name_tmp__274;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__275;
  uint16_t var_name_tmp__276;
  uint16_t var_name_tmp__277;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__278;
  uint16_t var_name_tmp__279;
  uint16_t var_name_tmp__280;
  uint16_t var_name_tmp__281;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__282;
  uint16_t var_name_tmp__283;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__284;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__285;
  uint32_t var_name_tmp__286;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__287;
  uint16_t var_name_tmp__288;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__289;

  var_name_tmp__237 = var_name_tmp__235;
  var_name_tmp__238 = var_name_tmp__236;
  var_name_tmp__239 = 0;
  var_name_tmp__240 = 0;
  var_name_tmp__241 = 0;
  var_name_tmp__242 = var_name_tmp__237;
  var_name_tmp__243 = (&var_name_tmp__242->field16);
  var_name_tmp__244 = *(volatile uint16_t*)var_name_tmp__243;
  *(volatile uint16_t*)var_name_tmp__243 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__244)) & 65534)));
  var_name_tmp__245 = var_name_tmp__237;
  var_name_tmp__246 = *(volatile uint16_t*)((&var_name_tmp__245->field16));
  var_name_tmp__240 = var_name_tmp__246;
  var_name_tmp__247 = var_name_tmp__237;
  var_name_tmp__248 = *(volatile uint16_t*)((&var_name_tmp__247->field2));
  var_name_tmp__241 = var_name_tmp__248;
  var_name_tmp__249 = var_name_tmp__237;
  var_name_tmp__250 = *(volatile uint16_t*)((&var_name_tmp__249->field12));
  var_name_tmp__239 = var_name_tmp__250;
  var_name_tmp__251 = var_name_tmp__239;
  var_name_tmp__239 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__251)) & 65423)));
  var_name_tmp__252 = var_name_tmp__239;
  var_name_tmp__239 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__252)) & 65532)));
  var_name_tmp__253 = var_name_tmp__238;
  var_name_tmp__254 = *((&var_name_tmp__253->field0));
  var_name_tmp__255 = var_name_tmp__239;
  var_name_tmp__239 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__255)) | (((uint32_t)(uint16_t)var_name_tmp__254)))));
  var_name_tmp__256 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__256)) & 65533)));
  var_name_tmp__257 = var_name_tmp__238;
  var_name_tmp__258 = *((&var_name_tmp__257->field4));
  var_name_tmp__259 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__259)) | (((uint32_t)(uint16_t)var_name_tmp__258)))));
  var_name_tmp__260 = var_name_tmp__238;
  var_name_tmp__261 = *((&var_name_tmp__260->field1));
  var_name_tmp__262 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__262)) | (((uint32_t)(uint16_t)var_name_tmp__261)))));
  var_name_tmp__263 = var_name_tmp__237;
  if ((((var_name_tmp__263 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__290;
  } else {
    goto var_name_tmp__291;
  }

var_name_tmp__291:
  var_name_tmp__264 = var_name_tmp__237;
  if ((((var_name_tmp__264 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__290;
  } else {
    goto var_name_tmp__292;
  }

var_name_tmp__290:
  var_name_tmp__265 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__265)) & 65527)));
  var_name_tmp__266 = var_name_tmp__238;
  var_name_tmp__267 = *((&var_name_tmp__266->field5));
  var_name_tmp__268 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__268)) | (((uint32_t)(uint16_t)var_name_tmp__267)))));
  var_name_tmp__269 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__269)) & 65531)));
  var_name_tmp__270 = var_name_tmp__238;
  var_name_tmp__271 = *((&var_name_tmp__270->field2));
  var_name_tmp__272 = var_name_tmp__240;
  var_name_tmp__240 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__272)) | (((uint32_t)(uint16_t)var_name_tmp__271)))));
  var_name_tmp__273 = var_name_tmp__241;
  var_name_tmp__241 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__273)) & 65279)));
  var_name_tmp__274 = var_name_tmp__241;
  var_name_tmp__241 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__274)) & 65023)));
  var_name_tmp__275 = var_name_tmp__238;
  var_name_tmp__276 = *((&var_name_tmp__275->field6));
  var_name_tmp__277 = var_name_tmp__241;
  var_name_tmp__241 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__277)) | (((uint32_t)(uint16_t)var_name_tmp__276)))));
  var_name_tmp__278 = var_name_tmp__238;
  var_name_tmp__279 = *((&var_name_tmp__278->field7));
  var_name_tmp__280 = var_name_tmp__241;
  var_name_tmp__241 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__280)) | (((uint32_t)(uint16_t)var_name_tmp__279)))));
  goto var_name_tmp__292;

var_name_tmp__292:
  var_name_tmp__281 = var_name_tmp__241;
  var_name_tmp__282 = var_name_tmp__237;
  *(volatile uint16_t*)((&var_name_tmp__282->field2)) = var_name_tmp__281;
  var_name_tmp__283 = var_name_tmp__239;
  var_name_tmp__284 = var_name_tmp__237;
  *(volatile uint16_t*)((&var_name_tmp__284->field12)) = var_name_tmp__283;
  var_name_tmp__285 = var_name_tmp__238;
  var_name_tmp__286 = *((&var_name_tmp__285->field3));
  var_name_tmp__287 = var_name_tmp__237;
  *(volatile uint32_t*)((&var_name_tmp__287->field24)) = var_name_tmp__286;
  var_name_tmp__288 = var_name_tmp__240;
  var_name_tmp__289 = var_name_tmp__237;
  *(volatile uint16_t*)((&var_name_tmp__289->field16)) = var_name_tmp__288;
}


void TIM_OC2Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__293, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__294) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__295;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__296;    /* Address-exposed local */
  uint16_t var_name_tmp__297;    /* Address-exposed local */
  uint16_t var_name_tmp__298;    /* Address-exposed local */
  uint16_t var_name_tmp__299;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__300;
  uint16_t* var_name_tmp__301;
  uint16_t var_name_tmp__302;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__303;
  uint16_t var_name_tmp__304;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__305;
  uint16_t var_name_tmp__306;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__307;
  uint16_t var_name_tmp__308;
  uint16_t var_name_tmp__309;
  uint16_t var_name_tmp__310;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__311;
  uint16_t var_name_tmp__312;
  uint16_t var_name_tmp__313;
  uint16_t var_name_tmp__314;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__315;
  uint16_t var_name_tmp__316;
  uint16_t var_name_tmp__317;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__318;
  uint16_t var_name_tmp__319;
  uint16_t var_name_tmp__320;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__321;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__322;
  uint16_t var_name_tmp__323;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__324;
  uint16_t var_name_tmp__325;
  uint16_t var_name_tmp__326;
  uint16_t var_name_tmp__327;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__328;
  uint16_t var_name_tmp__329;
  uint16_t var_name_tmp__330;
  uint16_t var_name_tmp__331;
  uint16_t var_name_tmp__332;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__333;
  uint16_t var_name_tmp__334;
  uint16_t var_name_tmp__335;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__336;
  uint16_t var_name_tmp__337;
  uint16_t var_name_tmp__338;
  uint16_t var_name_tmp__339;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__340;
  uint16_t var_name_tmp__341;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__342;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__343;
  uint32_t var_name_tmp__344;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__345;
  uint16_t var_name_tmp__346;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__347;

  var_name_tmp__295 = var_name_tmp__293;
  var_name_tmp__296 = var_name_tmp__294;
  var_name_tmp__297 = 0;
  var_name_tmp__298 = 0;
  var_name_tmp__299 = 0;
  var_name_tmp__300 = var_name_tmp__295;
  var_name_tmp__301 = (&var_name_tmp__300->field16);
  var_name_tmp__302 = *(volatile uint16_t*)var_name_tmp__301;
  *(volatile uint16_t*)var_name_tmp__301 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__302)) & 65519)));
  var_name_tmp__303 = var_name_tmp__295;
  var_name_tmp__304 = *(volatile uint16_t*)((&var_name_tmp__303->field16));
  var_name_tmp__298 = var_name_tmp__304;
  var_name_tmp__305 = var_name_tmp__295;
  var_name_tmp__306 = *(volatile uint16_t*)((&var_name_tmp__305->field2));
  var_name_tmp__299 = var_name_tmp__306;
  var_name_tmp__307 = var_name_tmp__295;
  var_name_tmp__308 = *(volatile uint16_t*)((&var_name_tmp__307->field12));
  var_name_tmp__297 = var_name_tmp__308;
  var_name_tmp__309 = var_name_tmp__297;
  var_name_tmp__297 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__309)) & 36863)));
  var_name_tmp__310 = var_name_tmp__297;
  var_name_tmp__297 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__310)) & 64767)));
  var_name_tmp__311 = var_name_tmp__296;
  var_name_tmp__312 = *((&var_name_tmp__311->field0));
  var_name_tmp__313 = var_name_tmp__297;
  var_name_tmp__297 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__313)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__312)) << 8))))))));
  var_name_tmp__314 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__314)) & 65503)));
  var_name_tmp__315 = var_name_tmp__296;
  var_name_tmp__316 = *((&var_name_tmp__315->field4));
  var_name_tmp__317 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__317)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__316)) << 4))))))));
  var_name_tmp__318 = var_name_tmp__296;
  var_name_tmp__319 = *((&var_name_tmp__318->field1));
  var_name_tmp__320 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__320)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__319)) << 4))))))));
  var_name_tmp__321 = var_name_tmp__295;
  if ((((var_name_tmp__321 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__348;
  } else {
    goto var_name_tmp__349;
  }

var_name_tmp__349:
  var_name_tmp__322 = var_name_tmp__295;
  if ((((var_name_tmp__322 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__348;
  } else {
    goto var_name_tmp__350;
  }

var_name_tmp__348:
  var_name_tmp__323 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__323)) & 65407)));
  var_name_tmp__324 = var_name_tmp__296;
  var_name_tmp__325 = *((&var_name_tmp__324->field5));
  var_name_tmp__326 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__326)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__325)) << 4))))))));
  var_name_tmp__327 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__327)) & 65471)));
  var_name_tmp__328 = var_name_tmp__296;
  var_name_tmp__329 = *((&var_name_tmp__328->field2));
  var_name_tmp__330 = var_name_tmp__298;
  var_name_tmp__298 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__330)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__329)) << 4))))))));
  var_name_tmp__331 = var_name_tmp__299;
  var_name_tmp__299 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__331)) & 64511)));
  var_name_tmp__332 = var_name_tmp__299;
  var_name_tmp__299 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__332)) & 63487)));
  var_name_tmp__333 = var_name_tmp__296;
  var_name_tmp__334 = *((&var_name_tmp__333->field6));
  var_name_tmp__335 = var_name_tmp__299;
  var_name_tmp__299 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__335)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__334)) << 2))))))));
  var_name_tmp__336 = var_name_tmp__296;
  var_name_tmp__337 = *((&var_name_tmp__336->field7));
  var_name_tmp__338 = var_name_tmp__299;
  var_name_tmp__299 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__338)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__337)) << 2))))))));
  goto var_name_tmp__350;

var_name_tmp__350:
  var_name_tmp__339 = var_name_tmp__299;
  var_name_tmp__340 = var_name_tmp__295;
  *(volatile uint16_t*)((&var_name_tmp__340->field2)) = var_name_tmp__339;
  var_name_tmp__341 = var_name_tmp__297;
  var_name_tmp__342 = var_name_tmp__295;
  *(volatile uint16_t*)((&var_name_tmp__342->field12)) = var_name_tmp__341;
  var_name_tmp__343 = var_name_tmp__296;
  var_name_tmp__344 = *((&var_name_tmp__343->field3));
  var_name_tmp__345 = var_name_tmp__295;
  *(volatile uint32_t*)((&var_name_tmp__345->field25)) = var_name_tmp__344;
  var_name_tmp__346 = var_name_tmp__298;
  var_name_tmp__347 = var_name_tmp__295;
  *(volatile uint16_t*)((&var_name_tmp__347->field16)) = var_name_tmp__346;
}


void TIM_OC3Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__351, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__352) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__353;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__354;    /* Address-exposed local */
  uint16_t var_name_tmp__355;    /* Address-exposed local */
  uint16_t var_name_tmp__356;    /* Address-exposed local */
  uint16_t var_name_tmp__357;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__358;
  uint16_t* var_name_tmp__359;
  uint16_t var_name_tmp__360;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__361;
  uint16_t var_name_tmp__362;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__363;
  uint16_t var_name_tmp__364;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__365;
  uint16_t var_name_tmp__366;
  uint16_t var_name_tmp__367;
  uint16_t var_name_tmp__368;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__369;
  uint16_t var_name_tmp__370;
  uint16_t var_name_tmp__371;
  uint16_t var_name_tmp__372;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__373;
  uint16_t var_name_tmp__374;
  uint16_t var_name_tmp__375;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__376;
  uint16_t var_name_tmp__377;
  uint16_t var_name_tmp__378;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__379;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__380;
  uint16_t var_name_tmp__381;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__382;
  uint16_t var_name_tmp__383;
  uint16_t var_name_tmp__384;
  uint16_t var_name_tmp__385;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__386;
  uint16_t var_name_tmp__387;
  uint16_t var_name_tmp__388;
  uint16_t var_name_tmp__389;
  uint16_t var_name_tmp__390;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__391;
  uint16_t var_name_tmp__392;
  uint16_t var_name_tmp__393;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__394;
  uint16_t var_name_tmp__395;
  uint16_t var_name_tmp__396;
  uint16_t var_name_tmp__397;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__398;
  uint16_t var_name_tmp__399;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__400;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__401;
  uint32_t var_name_tmp__402;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__403;
  uint16_t var_name_tmp__404;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__405;

  var_name_tmp__353 = var_name_tmp__351;
  var_name_tmp__354 = var_name_tmp__352;
  var_name_tmp__355 = 0;
  var_name_tmp__356 = 0;
  var_name_tmp__357 = 0;
  var_name_tmp__358 = var_name_tmp__353;
  var_name_tmp__359 = (&var_name_tmp__358->field16);
  var_name_tmp__360 = *(volatile uint16_t*)var_name_tmp__359;
  *(volatile uint16_t*)var_name_tmp__359 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__360)) & 65279)));
  var_name_tmp__361 = var_name_tmp__353;
  var_name_tmp__362 = *(volatile uint16_t*)((&var_name_tmp__361->field16));
  var_name_tmp__356 = var_name_tmp__362;
  var_name_tmp__363 = var_name_tmp__353;
  var_name_tmp__364 = *(volatile uint16_t*)((&var_name_tmp__363->field2));
  var_name_tmp__357 = var_name_tmp__364;
  var_name_tmp__365 = var_name_tmp__353;
  var_name_tmp__366 = *(volatile uint16_t*)((&var_name_tmp__365->field14));
  var_name_tmp__355 = var_name_tmp__366;
  var_name_tmp__367 = var_name_tmp__355;
  var_name_tmp__355 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__367)) & 65423)));
  var_name_tmp__368 = var_name_tmp__355;
  var_name_tmp__355 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__368)) & 65532)));
  var_name_tmp__369 = var_name_tmp__354;
  var_name_tmp__370 = *((&var_name_tmp__369->field0));
  var_name_tmp__371 = var_name_tmp__355;
  var_name_tmp__355 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__371)) | (((uint32_t)(uint16_t)var_name_tmp__370)))));
  var_name_tmp__372 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__372)) & 65023)));
  var_name_tmp__373 = var_name_tmp__354;
  var_name_tmp__374 = *((&var_name_tmp__373->field4));
  var_name_tmp__375 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__375)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__374)) << 8))))))));
  var_name_tmp__376 = var_name_tmp__354;
  var_name_tmp__377 = *((&var_name_tmp__376->field1));
  var_name_tmp__378 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__378)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__377)) << 8))))))));
  var_name_tmp__379 = var_name_tmp__353;
  if ((((var_name_tmp__379 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__406;
  } else {
    goto var_name_tmp__407;
  }

var_name_tmp__407:
  var_name_tmp__380 = var_name_tmp__353;
  if ((((var_name_tmp__380 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__406;
  } else {
    goto var_name_tmp__408;
  }

var_name_tmp__406:
  var_name_tmp__381 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__381)) & 63487)));
  var_name_tmp__382 = var_name_tmp__354;
  var_name_tmp__383 = *((&var_name_tmp__382->field5));
  var_name_tmp__384 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__384)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__383)) << 8))))))));
  var_name_tmp__385 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__385)) & 64511)));
  var_name_tmp__386 = var_name_tmp__354;
  var_name_tmp__387 = *((&var_name_tmp__386->field2));
  var_name_tmp__388 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__388)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__387)) << 8))))))));
  var_name_tmp__389 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__389)) & 61439)));
  var_name_tmp__390 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__390)) & 57343)));
  var_name_tmp__391 = var_name_tmp__354;
  var_name_tmp__392 = *((&var_name_tmp__391->field6));
  var_name_tmp__393 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__393)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__392)) << 4))))))));
  var_name_tmp__394 = var_name_tmp__354;
  var_name_tmp__395 = *((&var_name_tmp__394->field7));
  var_name_tmp__396 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__396)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__395)) << 4))))))));
  goto var_name_tmp__408;

var_name_tmp__408:
  var_name_tmp__397 = var_name_tmp__357;
  var_name_tmp__398 = var_name_tmp__353;
  *(volatile uint16_t*)((&var_name_tmp__398->field2)) = var_name_tmp__397;
  var_name_tmp__399 = var_name_tmp__355;
  var_name_tmp__400 = var_name_tmp__353;
  *(volatile uint16_t*)((&var_name_tmp__400->field14)) = var_name_tmp__399;
  var_name_tmp__401 = var_name_tmp__354;
  var_name_tmp__402 = *((&var_name_tmp__401->field3));
  var_name_tmp__403 = var_name_tmp__353;
  *(volatile uint32_t*)((&var_name_tmp__403->field26)) = var_name_tmp__402;
  var_name_tmp__404 = var_name_tmp__356;
  var_name_tmp__405 = var_name_tmp__353;
  *(volatile uint16_t*)((&var_name_tmp__405->field16)) = var_name_tmp__404;
}


void TIM_OC4Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__409, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__410) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__411;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__412;    /* Address-exposed local */
  uint16_t var_name_tmp__413;    /* Address-exposed local */
  uint16_t var_name_tmp__414;    /* Address-exposed local */
  uint16_t var_name_tmp__415;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__416;
  uint16_t* var_name_tmp__417;
  uint16_t var_name_tmp__418;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__419;
  uint16_t var_name_tmp__420;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__421;
  uint16_t var_name_tmp__422;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__423;
  uint16_t var_name_tmp__424;
  uint16_t var_name_tmp__425;
  uint16_t var_name_tmp__426;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__427;
  uint16_t var_name_tmp__428;
  uint16_t var_name_tmp__429;
  uint16_t var_name_tmp__430;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__431;
  uint16_t var_name_tmp__432;
  uint16_t var_name_tmp__433;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__434;
  uint16_t var_name_tmp__435;
  uint16_t var_name_tmp__436;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__437;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__438;
  uint16_t var_name_tmp__439;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__440;
  uint16_t var_name_tmp__441;
  uint16_t var_name_tmp__442;
  uint16_t var_name_tmp__443;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__444;
  uint16_t var_name_tmp__445;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__446;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__447;
  uint32_t var_name_tmp__448;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__449;
  uint16_t var_name_tmp__450;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__451;

  var_name_tmp__411 = var_name_tmp__409;
  var_name_tmp__412 = var_name_tmp__410;
  var_name_tmp__413 = 0;
  var_name_tmp__414 = 0;
  var_name_tmp__415 = 0;
  var_name_tmp__416 = var_name_tmp__411;
  var_name_tmp__417 = (&var_name_tmp__416->field16);
  var_name_tmp__418 = *(volatile uint16_t*)var_name_tmp__417;
  *(volatile uint16_t*)var_name_tmp__417 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__418)) & 61439)));
  var_name_tmp__419 = var_name_tmp__411;
  var_name_tmp__420 = *(volatile uint16_t*)((&var_name_tmp__419->field16));
  var_name_tmp__414 = var_name_tmp__420;
  var_name_tmp__421 = var_name_tmp__411;
  var_name_tmp__422 = *(volatile uint16_t*)((&var_name_tmp__421->field2));
  var_name_tmp__415 = var_name_tmp__422;
  var_name_tmp__423 = var_name_tmp__411;
  var_name_tmp__424 = *(volatile uint16_t*)((&var_name_tmp__423->field14));
  var_name_tmp__413 = var_name_tmp__424;
  var_name_tmp__425 = var_name_tmp__413;
  var_name_tmp__413 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__425)) & 36863)));
  var_name_tmp__426 = var_name_tmp__413;
  var_name_tmp__413 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__426)) & 64767)));
  var_name_tmp__427 = var_name_tmp__412;
  var_name_tmp__428 = *((&var_name_tmp__427->field0));
  var_name_tmp__429 = var_name_tmp__413;
  var_name_tmp__413 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__429)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__428)) << 8))))))));
  var_name_tmp__430 = var_name_tmp__414;
  var_name_tmp__414 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__430)) & 57343)));
  var_name_tmp__431 = var_name_tmp__412;
  var_name_tmp__432 = *((&var_name_tmp__431->field4));
  var_name_tmp__433 = var_name_tmp__414;
  var_name_tmp__414 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__433)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__432)) << 12))))))));
  var_name_tmp__434 = var_name_tmp__412;
  var_name_tmp__435 = *((&var_name_tmp__434->field1));
  var_name_tmp__436 = var_name_tmp__414;
  var_name_tmp__414 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__436)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__435)) << 12))))))));
  var_name_tmp__437 = var_name_tmp__411;
  if ((((var_name_tmp__437 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__452;
  } else {
    goto var_name_tmp__453;
  }

var_name_tmp__453:
  var_name_tmp__438 = var_name_tmp__411;
  if ((((var_name_tmp__438 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__452;
  } else {
    goto var_name_tmp__454;
  }

var_name_tmp__452:
  var_name_tmp__439 = var_name_tmp__415;
  var_name_tmp__415 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__439)) & 49151)));
  var_name_tmp__440 = var_name_tmp__412;
  var_name_tmp__441 = *((&var_name_tmp__440->field6));
  var_name_tmp__442 = var_name_tmp__415;
  var_name_tmp__415 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__442)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__441)) << 6))))))));
  goto var_name_tmp__454;

var_name_tmp__454:
  var_name_tmp__443 = var_name_tmp__415;
  var_name_tmp__444 = var_name_tmp__411;
  *(volatile uint16_t*)((&var_name_tmp__444->field2)) = var_name_tmp__443;
  var_name_tmp__445 = var_name_tmp__413;
  var_name_tmp__446 = var_name_tmp__411;
  *(volatile uint16_t*)((&var_name_tmp__446->field14)) = var_name_tmp__445;
  var_name_tmp__447 = var_name_tmp__412;
  var_name_tmp__448 = *((&var_name_tmp__447->field3));
  var_name_tmp__449 = var_name_tmp__411;
  *(volatile uint32_t*)((&var_name_tmp__449->field27)) = var_name_tmp__448;
  var_name_tmp__450 = var_name_tmp__414;
  var_name_tmp__451 = var_name_tmp__411;
  *(volatile uint16_t*)((&var_name_tmp__451->field16)) = var_name_tmp__450;
}


void TIM_OCStructInit(struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__455) {
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__456;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__457;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__458;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__459;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__460;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__461;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__462;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__463;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__464;

  var_name_tmp__456 = var_name_tmp__455;
  var_name_tmp__457 = var_name_tmp__456;
  *((&var_name_tmp__457->field0)) = 0;
  var_name_tmp__458 = var_name_tmp__456;
  *((&var_name_tmp__458->field1)) = 0;
  var_name_tmp__459 = var_name_tmp__456;
  *((&var_name_tmp__459->field2)) = 0;
  var_name_tmp__460 = var_name_tmp__456;
  *((&var_name_tmp__460->field3)) = 0;
  var_name_tmp__461 = var_name_tmp__456;
  *((&var_name_tmp__461->field4)) = 0;
  var_name_tmp__462 = var_name_tmp__456;
  *((&var_name_tmp__462->field5)) = 0;
  var_name_tmp__463 = var_name_tmp__456;
  *((&var_name_tmp__463->field6)) = 0;
  var_name_tmp__464 = var_name_tmp__456;
  *((&var_name_tmp__464->field7)) = 0;
}


void TIM_SelectOCxM(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__465, uint16_t var_name_tmp__466, uint16_t var_name_tmp__467) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__468;    /* Address-exposed local */
  uint16_t var_name_tmp__469;    /* Address-exposed local */
  uint16_t var_name_tmp__470;    /* Address-exposed local */
  uint32_t var_name_tmp__471;    /* Address-exposed local */
  uint16_t var_name_tmp__472;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__473;
  uint32_t var_name_tmp__474;
  uint16_t var_name_tmp__475;
  uint16_t var_name_tmp__476;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__477;
  uint16_t* var_name_tmp__478;
  uint16_t var_name_tmp__479;
  uint16_t var_name_tmp__480;
  uint16_t var_name_tmp__481;
  uint16_t var_name_tmp__482;
  uint32_t var_name_tmp__483;
  uint32_t var_name_tmp__484;
  uint32_t* var_name_tmp__485;
  uint32_t var_name_tmp__486;
  uint16_t var_name_tmp__487;
  uint32_t var_name_tmp__488;
  uint32_t* var_name_tmp__489;
  uint32_t var_name_tmp__490;
  uint16_t var_name_tmp__491;
  uint32_t var_name_tmp__492;
  uint32_t var_name_tmp__493;
  uint32_t* var_name_tmp__494;
  uint32_t var_name_tmp__495;
  uint16_t var_name_tmp__496;
  uint32_t var_name_tmp__497;
  uint32_t* var_name_tmp__498;
  uint32_t var_name_tmp__499;

  var_name_tmp__468 = var_name_tmp__465;
  var_name_tmp__469 = var_name_tmp__466;
  var_name_tmp__470 = var_name_tmp__467;
  var_name_tmp__471 = 0;
  var_name_tmp__472 = 0;
  var_name_tmp__473 = var_name_tmp__468;
  var_name_tmp__471 = (((uint32_t)(uintptr_t)var_name_tmp__473));
  var_name_tmp__474 = var_name_tmp__471;
  var_name_tmp__471 = (llvm_add_u32(var_name_tmp__474, 24));
  var_name_tmp__475 = var_name_tmp__469;
  var_name_tmp__472 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__475)))));
  var_name_tmp__476 = var_name_tmp__472;
  var_name_tmp__477 = var_name_tmp__468;
  var_name_tmp__478 = (&var_name_tmp__477->field16);
  var_name_tmp__479 = *(volatile uint16_t*)var_name_tmp__478;
  *(volatile uint16_t*)var_name_tmp__478 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__479)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__476)))))))))));
  var_name_tmp__480 = var_name_tmp__469;
  if (((((((uint32_t)(uint16_t)var_name_tmp__480)) == 0u)&1))) {
    goto var_name_tmp__500;
  } else {
    goto var_name_tmp__501;
  }

var_name_tmp__501:
  var_name_tmp__481 = var_name_tmp__469;
  if (((((((uint32_t)(uint16_t)var_name_tmp__481)) == 8u)&1))) {
    goto var_name_tmp__500;
  } else {
    goto var_name_tmp__502;
  }

var_name_tmp__500:
  var_name_tmp__482 = var_name_tmp__469;
  var_name_tmp__483 = var_name_tmp__471;
  var_name_tmp__471 = (llvm_add_u32(var_name_tmp__483, (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__482)), 1))));
  var_name_tmp__484 = var_name_tmp__471;
  var_name_tmp__485 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__484)));
  var_name_tmp__486 = *(volatile uint32_t*)var_name_tmp__485;
  *(volatile uint32_t*)var_name_tmp__485 = (var_name_tmp__486 & 65423);
  var_name_tmp__487 = var_name_tmp__470;
  var_name_tmp__488 = var_name_tmp__471;
  var_name_tmp__489 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__488)));
  var_name_tmp__490 = *(volatile uint32_t*)var_name_tmp__489;
  *(volatile uint32_t*)var_name_tmp__489 = (var_name_tmp__490 | (((uint32_t)(uint16_t)var_name_tmp__487)));
  goto var_name_tmp__503;

var_name_tmp__502:
  var_name_tmp__491 = var_name_tmp__469;
  var_name_tmp__492 = var_name_tmp__471;
  var_name_tmp__471 = (llvm_add_u32(var_name_tmp__492, (llvm_ashr_u32((((uint32_t)(uint16_t)(((uint16_t)(llvm_sub_u32((((uint32_t)(uint16_t)var_name_tmp__491)), 4)))))), 1))));
  var_name_tmp__493 = var_name_tmp__471;
  var_name_tmp__494 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__493)));
  var_name_tmp__495 = *(volatile uint32_t*)var_name_tmp__494;
  *(volatile uint32_t*)var_name_tmp__494 = (var_name_tmp__495 & 36863);
  var_name_tmp__496 = var_name_tmp__470;
  var_name_tmp__497 = var_name_tmp__471;
  var_name_tmp__498 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__497)));
  var_name_tmp__499 = *(volatile uint32_t*)var_name_tmp__498;
  *(volatile uint32_t*)var_name_tmp__498 = (var_name_tmp__499 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__496)) << 8))))));
  goto var_name_tmp__503;

var_name_tmp__503:
  return;
}


void TIM_SetCompare1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__504, uint32_t var_name_tmp__505) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__506;    /* Address-exposed local */
  uint32_t var_name_tmp__507;    /* Address-exposed local */
  uint32_t var_name_tmp__508;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__509;

  var_name_tmp__506 = var_name_tmp__504;
  var_name_tmp__507 = var_name_tmp__505;
  var_name_tmp__508 = var_name_tmp__507;
  var_name_tmp__509 = var_name_tmp__506;
  *(volatile uint32_t*)((&var_name_tmp__509->field24)) = var_name_tmp__508;
}


void TIM_SetCompare2(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__510, uint32_t var_name_tmp__511) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__512;    /* Address-exposed local */
  uint32_t var_name_tmp__513;    /* Address-exposed local */
  uint32_t var_name_tmp__514;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__515;

  var_name_tmp__512 = var_name_tmp__510;
  var_name_tmp__513 = var_name_tmp__511;
  var_name_tmp__514 = var_name_tmp__513;
  var_name_tmp__515 = var_name_tmp__512;
  *(volatile uint32_t*)((&var_name_tmp__515->field25)) = var_name_tmp__514;
}


void TIM_SetCompare3(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__516, uint32_t var_name_tmp__517) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__518;    /* Address-exposed local */
  uint32_t var_name_tmp__519;    /* Address-exposed local */
  uint32_t var_name_tmp__520;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__521;

  var_name_tmp__518 = var_name_tmp__516;
  var_name_tmp__519 = var_name_tmp__517;
  var_name_tmp__520 = var_name_tmp__519;
  var_name_tmp__521 = var_name_tmp__518;
  *(volatile uint32_t*)((&var_name_tmp__521->field26)) = var_name_tmp__520;
}


void TIM_SetCompare4(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__522, uint32_t var_name_tmp__523) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__524;    /* Address-exposed local */
  uint32_t var_name_tmp__525;    /* Address-exposed local */
  uint32_t var_name_tmp__526;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__527;

  var_name_tmp__524 = var_name_tmp__522;
  var_name_tmp__525 = var_name_tmp__523;
  var_name_tmp__526 = var_name_tmp__525;
  var_name_tmp__527 = var_name_tmp__524;
  *(volatile uint32_t*)((&var_name_tmp__527->field27)) = var_name_tmp__526;
}


void TIM_ForcedOC1Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__528, uint16_t var_name_tmp__529) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__530;    /* Address-exposed local */
  uint16_t var_name_tmp__531;    /* Address-exposed local */
  uint16_t var_name_tmp__532;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__533;
  uint16_t var_name_tmp__534;
  uint16_t var_name_tmp__535;
  uint16_t var_name_tmp__536;
  uint16_t var_name_tmp__537;
  uint16_t var_name_tmp__538;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__539;

  var_name_tmp__530 = var_name_tmp__528;
  var_name_tmp__531 = var_name_tmp__529;
  var_name_tmp__532 = 0;
  var_name_tmp__533 = var_name_tmp__530;
  var_name_tmp__534 = *(volatile uint16_t*)((&var_name_tmp__533->field12));
  var_name_tmp__532 = var_name_tmp__534;
  var_name_tmp__535 = var_name_tmp__532;
  var_name_tmp__532 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__535)) & 65423)));
  var_name_tmp__536 = var_name_tmp__531;
  var_name_tmp__537 = var_name_tmp__532;
  var_name_tmp__532 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__537)) | (((uint32_t)(uint16_t)var_name_tmp__536)))));
  var_name_tmp__538 = var_name_tmp__532;
  var_name_tmp__539 = var_name_tmp__530;
  *(volatile uint16_t*)((&var_name_tmp__539->field12)) = var_name_tmp__538;
}


void TIM_ForcedOC2Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__540, uint16_t var_name_tmp__541) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__542;    /* Address-exposed local */
  uint16_t var_name_tmp__543;    /* Address-exposed local */
  uint16_t var_name_tmp__544;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__545;
  uint16_t var_name_tmp__546;
  uint16_t var_name_tmp__547;
  uint16_t var_name_tmp__548;
  uint16_t var_name_tmp__549;
  uint16_t var_name_tmp__550;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__551;

  var_name_tmp__542 = var_name_tmp__540;
  var_name_tmp__543 = var_name_tmp__541;
  var_name_tmp__544 = 0;
  var_name_tmp__545 = var_name_tmp__542;
  var_name_tmp__546 = *(volatile uint16_t*)((&var_name_tmp__545->field12));
  var_name_tmp__544 = var_name_tmp__546;
  var_name_tmp__547 = var_name_tmp__544;
  var_name_tmp__544 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__547)) & 36863)));
  var_name_tmp__548 = var_name_tmp__543;
  var_name_tmp__549 = var_name_tmp__544;
  var_name_tmp__544 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__549)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__548)) << 8))))))));
  var_name_tmp__550 = var_name_tmp__544;
  var_name_tmp__551 = var_name_tmp__542;
  *(volatile uint16_t*)((&var_name_tmp__551->field12)) = var_name_tmp__550;
}


void TIM_ForcedOC3Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__552, uint16_t var_name_tmp__553) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__554;    /* Address-exposed local */
  uint16_t var_name_tmp__555;    /* Address-exposed local */
  uint16_t var_name_tmp__556;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__557;
  uint16_t var_name_tmp__558;
  uint16_t var_name_tmp__559;
  uint16_t var_name_tmp__560;
  uint16_t var_name_tmp__561;
  uint16_t var_name_tmp__562;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__563;

  var_name_tmp__554 = var_name_tmp__552;
  var_name_tmp__555 = var_name_tmp__553;
  var_name_tmp__556 = 0;
  var_name_tmp__557 = var_name_tmp__554;
  var_name_tmp__558 = *(volatile uint16_t*)((&var_name_tmp__557->field14));
  var_name_tmp__556 = var_name_tmp__558;
  var_name_tmp__559 = var_name_tmp__556;
  var_name_tmp__556 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__559)) & 65423)));
  var_name_tmp__560 = var_name_tmp__555;
  var_name_tmp__561 = var_name_tmp__556;
  var_name_tmp__556 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__561)) | (((uint32_t)(uint16_t)var_name_tmp__560)))));
  var_name_tmp__562 = var_name_tmp__556;
  var_name_tmp__563 = var_name_tmp__554;
  *(volatile uint16_t*)((&var_name_tmp__563->field14)) = var_name_tmp__562;
}


void TIM_ForcedOC4Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__564, uint16_t var_name_tmp__565) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__566;    /* Address-exposed local */
  uint16_t var_name_tmp__567;    /* Address-exposed local */
  uint16_t var_name_tmp__568;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__569;
  uint16_t var_name_tmp__570;
  uint16_t var_name_tmp__571;
  uint16_t var_name_tmp__572;
  uint16_t var_name_tmp__573;
  uint16_t var_name_tmp__574;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__575;

  var_name_tmp__566 = var_name_tmp__564;
  var_name_tmp__567 = var_name_tmp__565;
  var_name_tmp__568 = 0;
  var_name_tmp__569 = var_name_tmp__566;
  var_name_tmp__570 = *(volatile uint16_t*)((&var_name_tmp__569->field14));
  var_name_tmp__568 = var_name_tmp__570;
  var_name_tmp__571 = var_name_tmp__568;
  var_name_tmp__568 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__571)) & 36863)));
  var_name_tmp__572 = var_name_tmp__567;
  var_name_tmp__573 = var_name_tmp__568;
  var_name_tmp__568 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__573)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__572)) << 8))))))));
  var_name_tmp__574 = var_name_tmp__568;
  var_name_tmp__575 = var_name_tmp__566;
  *(volatile uint16_t*)((&var_name_tmp__575->field14)) = var_name_tmp__574;
}


void TIM_OC1PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__576, uint16_t var_name_tmp__577) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__578;    /* Address-exposed local */
  uint16_t var_name_tmp__579;    /* Address-exposed local */
  uint16_t var_name_tmp__580;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__581;
  uint16_t var_name_tmp__582;
  uint16_t var_name_tmp__583;
  uint16_t var_name_tmp__584;
  uint16_t var_name_tmp__585;
  uint16_t var_name_tmp__586;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__587;

  var_name_tmp__578 = var_name_tmp__576;
  var_name_tmp__579 = var_name_tmp__577;
  var_name_tmp__580 = 0;
  var_name_tmp__581 = var_name_tmp__578;
  var_name_tmp__582 = *(volatile uint16_t*)((&var_name_tmp__581->field12));
  var_name_tmp__580 = var_name_tmp__582;
  var_name_tmp__583 = var_name_tmp__580;
  var_name_tmp__580 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__583)) & 65527)));
  var_name_tmp__584 = var_name_tmp__579;
  var_name_tmp__585 = var_name_tmp__580;
  var_name_tmp__580 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__585)) | (((uint32_t)(uint16_t)var_name_tmp__584)))));
  var_name_tmp__586 = var_name_tmp__580;
  var_name_tmp__587 = var_name_tmp__578;
  *(volatile uint16_t*)((&var_name_tmp__587->field12)) = var_name_tmp__586;
}


void TIM_OC2PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__588, uint16_t var_name_tmp__589) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__590;    /* Address-exposed local */
  uint16_t var_name_tmp__591;    /* Address-exposed local */
  uint16_t var_name_tmp__592;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__593;
  uint16_t var_name_tmp__594;
  uint16_t var_name_tmp__595;
  uint16_t var_name_tmp__596;
  uint16_t var_name_tmp__597;
  uint16_t var_name_tmp__598;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__599;

  var_name_tmp__590 = var_name_tmp__588;
  var_name_tmp__591 = var_name_tmp__589;
  var_name_tmp__592 = 0;
  var_name_tmp__593 = var_name_tmp__590;
  var_name_tmp__594 = *(volatile uint16_t*)((&var_name_tmp__593->field12));
  var_name_tmp__592 = var_name_tmp__594;
  var_name_tmp__595 = var_name_tmp__592;
  var_name_tmp__592 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__595)) & 63487)));
  var_name_tmp__596 = var_name_tmp__591;
  var_name_tmp__597 = var_name_tmp__592;
  var_name_tmp__592 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__597)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__596)) << 8))))))));
  var_name_tmp__598 = var_name_tmp__592;
  var_name_tmp__599 = var_name_tmp__590;
  *(volatile uint16_t*)((&var_name_tmp__599->field12)) = var_name_tmp__598;
}


void TIM_OC3PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__600, uint16_t var_name_tmp__601) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__602;    /* Address-exposed local */
  uint16_t var_name_tmp__603;    /* Address-exposed local */
  uint16_t var_name_tmp__604;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__605;
  uint16_t var_name_tmp__606;
  uint16_t var_name_tmp__607;
  uint16_t var_name_tmp__608;
  uint16_t var_name_tmp__609;
  uint16_t var_name_tmp__610;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__611;

  var_name_tmp__602 = var_name_tmp__600;
  var_name_tmp__603 = var_name_tmp__601;
  var_name_tmp__604 = 0;
  var_name_tmp__605 = var_name_tmp__602;
  var_name_tmp__606 = *(volatile uint16_t*)((&var_name_tmp__605->field14));
  var_name_tmp__604 = var_name_tmp__606;
  var_name_tmp__607 = var_name_tmp__604;
  var_name_tmp__604 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__607)) & 65527)));
  var_name_tmp__608 = var_name_tmp__603;
  var_name_tmp__609 = var_name_tmp__604;
  var_name_tmp__604 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__609)) | (((uint32_t)(uint16_t)var_name_tmp__608)))));
  var_name_tmp__610 = var_name_tmp__604;
  var_name_tmp__611 = var_name_tmp__602;
  *(volatile uint16_t*)((&var_name_tmp__611->field14)) = var_name_tmp__610;
}


void TIM_OC4PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__612, uint16_t var_name_tmp__613) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__614;    /* Address-exposed local */
  uint16_t var_name_tmp__615;    /* Address-exposed local */
  uint16_t var_name_tmp__616;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__617;
  uint16_t var_name_tmp__618;
  uint16_t var_name_tmp__619;
  uint16_t var_name_tmp__620;
  uint16_t var_name_tmp__621;
  uint16_t var_name_tmp__622;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__623;

  var_name_tmp__614 = var_name_tmp__612;
  var_name_tmp__615 = var_name_tmp__613;
  var_name_tmp__616 = 0;
  var_name_tmp__617 = var_name_tmp__614;
  var_name_tmp__618 = *(volatile uint16_t*)((&var_name_tmp__617->field14));
  var_name_tmp__616 = var_name_tmp__618;
  var_name_tmp__619 = var_name_tmp__616;
  var_name_tmp__616 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__619)) & 63487)));
  var_name_tmp__620 = var_name_tmp__615;
  var_name_tmp__621 = var_name_tmp__616;
  var_name_tmp__616 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__621)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__620)) << 8))))))));
  var_name_tmp__622 = var_name_tmp__616;
  var_name_tmp__623 = var_name_tmp__614;
  *(volatile uint16_t*)((&var_name_tmp__623->field14)) = var_name_tmp__622;
}


void TIM_OC1FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__624, uint16_t var_name_tmp__625) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__626;    /* Address-exposed local */
  uint16_t var_name_tmp__627;    /* Address-exposed local */
  uint16_t var_name_tmp__628;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__629;
  uint16_t var_name_tmp__630;
  uint16_t var_name_tmp__631;
  uint16_t var_name_tmp__632;
  uint16_t var_name_tmp__633;
  uint16_t var_name_tmp__634;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__635;

  var_name_tmp__626 = var_name_tmp__624;
  var_name_tmp__627 = var_name_tmp__625;
  var_name_tmp__628 = 0;
  var_name_tmp__629 = var_name_tmp__626;
  var_name_tmp__630 = *(volatile uint16_t*)((&var_name_tmp__629->field12));
  var_name_tmp__628 = var_name_tmp__630;
  var_name_tmp__631 = var_name_tmp__628;
  var_name_tmp__628 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__631)) & 65531)));
  var_name_tmp__632 = var_name_tmp__627;
  var_name_tmp__633 = var_name_tmp__628;
  var_name_tmp__628 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__633)) | (((uint32_t)(uint16_t)var_name_tmp__632)))));
  var_name_tmp__634 = var_name_tmp__628;
  var_name_tmp__635 = var_name_tmp__626;
  *(volatile uint16_t*)((&var_name_tmp__635->field12)) = var_name_tmp__634;
}


void TIM_OC2FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__636, uint16_t var_name_tmp__637) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__638;    /* Address-exposed local */
  uint16_t var_name_tmp__639;    /* Address-exposed local */
  uint16_t var_name_tmp__640;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__641;
  uint16_t var_name_tmp__642;
  uint16_t var_name_tmp__643;
  uint16_t var_name_tmp__644;
  uint16_t var_name_tmp__645;
  uint16_t var_name_tmp__646;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__647;

  var_name_tmp__638 = var_name_tmp__636;
  var_name_tmp__639 = var_name_tmp__637;
  var_name_tmp__640 = 0;
  var_name_tmp__641 = var_name_tmp__638;
  var_name_tmp__642 = *(volatile uint16_t*)((&var_name_tmp__641->field12));
  var_name_tmp__640 = var_name_tmp__642;
  var_name_tmp__643 = var_name_tmp__640;
  var_name_tmp__640 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__643)) & 64511)));
  var_name_tmp__644 = var_name_tmp__639;
  var_name_tmp__645 = var_name_tmp__640;
  var_name_tmp__640 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__645)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__644)) << 8))))))));
  var_name_tmp__646 = var_name_tmp__640;
  var_name_tmp__647 = var_name_tmp__638;
  *(volatile uint16_t*)((&var_name_tmp__647->field12)) = var_name_tmp__646;
}


void TIM_OC3FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__648, uint16_t var_name_tmp__649) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__650;    /* Address-exposed local */
  uint16_t var_name_tmp__651;    /* Address-exposed local */
  uint16_t var_name_tmp__652;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__653;
  uint16_t var_name_tmp__654;
  uint16_t var_name_tmp__655;
  uint16_t var_name_tmp__656;
  uint16_t var_name_tmp__657;
  uint16_t var_name_tmp__658;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__659;

  var_name_tmp__650 = var_name_tmp__648;
  var_name_tmp__651 = var_name_tmp__649;
  var_name_tmp__652 = 0;
  var_name_tmp__653 = var_name_tmp__650;
  var_name_tmp__654 = *(volatile uint16_t*)((&var_name_tmp__653->field14));
  var_name_tmp__652 = var_name_tmp__654;
  var_name_tmp__655 = var_name_tmp__652;
  var_name_tmp__652 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__655)) & 65531)));
  var_name_tmp__656 = var_name_tmp__651;
  var_name_tmp__657 = var_name_tmp__652;
  var_name_tmp__652 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__657)) | (((uint32_t)(uint16_t)var_name_tmp__656)))));
  var_name_tmp__658 = var_name_tmp__652;
  var_name_tmp__659 = var_name_tmp__650;
  *(volatile uint16_t*)((&var_name_tmp__659->field14)) = var_name_tmp__658;
}


void TIM_OC4FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__660, uint16_t var_name_tmp__661) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__662;    /* Address-exposed local */
  uint16_t var_name_tmp__663;    /* Address-exposed local */
  uint16_t var_name_tmp__664;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__665;
  uint16_t var_name_tmp__666;
  uint16_t var_name_tmp__667;
  uint16_t var_name_tmp__668;
  uint16_t var_name_tmp__669;
  uint16_t var_name_tmp__670;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__671;

  var_name_tmp__662 = var_name_tmp__660;
  var_name_tmp__663 = var_name_tmp__661;
  var_name_tmp__664 = 0;
  var_name_tmp__665 = var_name_tmp__662;
  var_name_tmp__666 = *(volatile uint16_t*)((&var_name_tmp__665->field14));
  var_name_tmp__664 = var_name_tmp__666;
  var_name_tmp__667 = var_name_tmp__664;
  var_name_tmp__664 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__667)) & 64511)));
  var_name_tmp__668 = var_name_tmp__663;
  var_name_tmp__669 = var_name_tmp__664;
  var_name_tmp__664 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__669)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__668)) << 8))))))));
  var_name_tmp__670 = var_name_tmp__664;
  var_name_tmp__671 = var_name_tmp__662;
  *(volatile uint16_t*)((&var_name_tmp__671->field14)) = var_name_tmp__670;
}


void TIM_ClearOC1Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__672, uint16_t var_name_tmp__673) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__674;    /* Address-exposed local */
  uint16_t var_name_tmp__675;    /* Address-exposed local */
  uint16_t var_name_tmp__676;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__677;
  uint16_t var_name_tmp__678;
  uint16_t var_name_tmp__679;
  uint16_t var_name_tmp__680;
  uint16_t var_name_tmp__681;
  uint16_t var_name_tmp__682;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__683;

  var_name_tmp__674 = var_name_tmp__672;
  var_name_tmp__675 = var_name_tmp__673;
  var_name_tmp__676 = 0;
  var_name_tmp__677 = var_name_tmp__674;
  var_name_tmp__678 = *(volatile uint16_t*)((&var_name_tmp__677->field12));
  var_name_tmp__676 = var_name_tmp__678;
  var_name_tmp__679 = var_name_tmp__676;
  var_name_tmp__676 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__679)) & 65407)));
  var_name_tmp__680 = var_name_tmp__675;
  var_name_tmp__681 = var_name_tmp__676;
  var_name_tmp__676 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__681)) | (((uint32_t)(uint16_t)var_name_tmp__680)))));
  var_name_tmp__682 = var_name_tmp__676;
  var_name_tmp__683 = var_name_tmp__674;
  *(volatile uint16_t*)((&var_name_tmp__683->field12)) = var_name_tmp__682;
}


void TIM_ClearOC2Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__684, uint16_t var_name_tmp__685) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__686;    /* Address-exposed local */
  uint16_t var_name_tmp__687;    /* Address-exposed local */
  uint16_t var_name_tmp__688;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__689;
  uint16_t var_name_tmp__690;
  uint16_t var_name_tmp__691;
  uint16_t var_name_tmp__692;
  uint16_t var_name_tmp__693;
  uint16_t var_name_tmp__694;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__695;

  var_name_tmp__686 = var_name_tmp__684;
  var_name_tmp__687 = var_name_tmp__685;
  var_name_tmp__688 = 0;
  var_name_tmp__689 = var_name_tmp__686;
  var_name_tmp__690 = *(volatile uint16_t*)((&var_name_tmp__689->field12));
  var_name_tmp__688 = var_name_tmp__690;
  var_name_tmp__691 = var_name_tmp__688;
  var_name_tmp__688 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__691)) & 32767)));
  var_name_tmp__692 = var_name_tmp__687;
  var_name_tmp__693 = var_name_tmp__688;
  var_name_tmp__688 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__693)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__692)) << 8))))))));
  var_name_tmp__694 = var_name_tmp__688;
  var_name_tmp__695 = var_name_tmp__686;
  *(volatile uint16_t*)((&var_name_tmp__695->field12)) = var_name_tmp__694;
}


void TIM_ClearOC3Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__696, uint16_t var_name_tmp__697) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__698;    /* Address-exposed local */
  uint16_t var_name_tmp__699;    /* Address-exposed local */
  uint16_t var_name_tmp__700;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__701;
  uint16_t var_name_tmp__702;
  uint16_t var_name_tmp__703;
  uint16_t var_name_tmp__704;
  uint16_t var_name_tmp__705;
  uint16_t var_name_tmp__706;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__707;

  var_name_tmp__698 = var_name_tmp__696;
  var_name_tmp__699 = var_name_tmp__697;
  var_name_tmp__700 = 0;
  var_name_tmp__701 = var_name_tmp__698;
  var_name_tmp__702 = *(volatile uint16_t*)((&var_name_tmp__701->field14));
  var_name_tmp__700 = var_name_tmp__702;
  var_name_tmp__703 = var_name_tmp__700;
  var_name_tmp__700 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__703)) & 65407)));
  var_name_tmp__704 = var_name_tmp__699;
  var_name_tmp__705 = var_name_tmp__700;
  var_name_tmp__700 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__705)) | (((uint32_t)(uint16_t)var_name_tmp__704)))));
  var_name_tmp__706 = var_name_tmp__700;
  var_name_tmp__707 = var_name_tmp__698;
  *(volatile uint16_t*)((&var_name_tmp__707->field14)) = var_name_tmp__706;
}


void TIM_ClearOC4Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__708, uint16_t var_name_tmp__709) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__710;    /* Address-exposed local */
  uint16_t var_name_tmp__711;    /* Address-exposed local */
  uint16_t var_name_tmp__712;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__713;
  uint16_t var_name_tmp__714;
  uint16_t var_name_tmp__715;
  uint16_t var_name_tmp__716;
  uint16_t var_name_tmp__717;
  uint16_t var_name_tmp__718;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__719;

  var_name_tmp__710 = var_name_tmp__708;
  var_name_tmp__711 = var_name_tmp__709;
  var_name_tmp__712 = 0;
  var_name_tmp__713 = var_name_tmp__710;
  var_name_tmp__714 = *(volatile uint16_t*)((&var_name_tmp__713->field14));
  var_name_tmp__712 = var_name_tmp__714;
  var_name_tmp__715 = var_name_tmp__712;
  var_name_tmp__712 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__715)) & 32767)));
  var_name_tmp__716 = var_name_tmp__711;
  var_name_tmp__717 = var_name_tmp__712;
  var_name_tmp__712 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__717)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__716)) << 8))))))));
  var_name_tmp__718 = var_name_tmp__712;
  var_name_tmp__719 = var_name_tmp__710;
  *(volatile uint16_t*)((&var_name_tmp__719->field14)) = var_name_tmp__718;
}


void TIM_OC1PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__720, uint16_t var_name_tmp__721) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__722;    /* Address-exposed local */
  uint16_t var_name_tmp__723;    /* Address-exposed local */
  uint16_t var_name_tmp__724;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__725;
  uint16_t var_name_tmp__726;
  uint16_t var_name_tmp__727;
  uint16_t var_name_tmp__728;
  uint16_t var_name_tmp__729;
  uint16_t var_name_tmp__730;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__731;

  var_name_tmp__722 = var_name_tmp__720;
  var_name_tmp__723 = var_name_tmp__721;
  var_name_tmp__724 = 0;
  var_name_tmp__725 = var_name_tmp__722;
  var_name_tmp__726 = *(volatile uint16_t*)((&var_name_tmp__725->field16));
  var_name_tmp__724 = var_name_tmp__726;
  var_name_tmp__727 = var_name_tmp__724;
  var_name_tmp__724 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__727)) & 65533)));
  var_name_tmp__728 = var_name_tmp__723;
  var_name_tmp__729 = var_name_tmp__724;
  var_name_tmp__724 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__729)) | (((uint32_t)(uint16_t)var_name_tmp__728)))));
  var_name_tmp__730 = var_name_tmp__724;
  var_name_tmp__731 = var_name_tmp__722;
  *(volatile uint16_t*)((&var_name_tmp__731->field16)) = var_name_tmp__730;
}


void TIM_OC1NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__732, uint16_t var_name_tmp__733) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__734;    /* Address-exposed local */
  uint16_t var_name_tmp__735;    /* Address-exposed local */
  uint16_t var_name_tmp__736;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__737;
  uint16_t var_name_tmp__738;
  uint16_t var_name_tmp__739;
  uint16_t var_name_tmp__740;
  uint16_t var_name_tmp__741;
  uint16_t var_name_tmp__742;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__743;

  var_name_tmp__734 = var_name_tmp__732;
  var_name_tmp__735 = var_name_tmp__733;
  var_name_tmp__736 = 0;
  var_name_tmp__737 = var_name_tmp__734;
  var_name_tmp__738 = *(volatile uint16_t*)((&var_name_tmp__737->field16));
  var_name_tmp__736 = var_name_tmp__738;
  var_name_tmp__739 = var_name_tmp__736;
  var_name_tmp__736 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__739)) & 65527)));
  var_name_tmp__740 = var_name_tmp__735;
  var_name_tmp__741 = var_name_tmp__736;
  var_name_tmp__736 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__741)) | (((uint32_t)(uint16_t)var_name_tmp__740)))));
  var_name_tmp__742 = var_name_tmp__736;
  var_name_tmp__743 = var_name_tmp__734;
  *(volatile uint16_t*)((&var_name_tmp__743->field16)) = var_name_tmp__742;
}


void TIM_OC2PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__744, uint16_t var_name_tmp__745) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__746;    /* Address-exposed local */
  uint16_t var_name_tmp__747;    /* Address-exposed local */
  uint16_t var_name_tmp__748;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__749;
  uint16_t var_name_tmp__750;
  uint16_t var_name_tmp__751;
  uint16_t var_name_tmp__752;
  uint16_t var_name_tmp__753;
  uint16_t var_name_tmp__754;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__755;

  var_name_tmp__746 = var_name_tmp__744;
  var_name_tmp__747 = var_name_tmp__745;
  var_name_tmp__748 = 0;
  var_name_tmp__749 = var_name_tmp__746;
  var_name_tmp__750 = *(volatile uint16_t*)((&var_name_tmp__749->field16));
  var_name_tmp__748 = var_name_tmp__750;
  var_name_tmp__751 = var_name_tmp__748;
  var_name_tmp__748 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__751)) & 65503)));
  var_name_tmp__752 = var_name_tmp__747;
  var_name_tmp__753 = var_name_tmp__748;
  var_name_tmp__748 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__753)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__752)) << 4))))))));
  var_name_tmp__754 = var_name_tmp__748;
  var_name_tmp__755 = var_name_tmp__746;
  *(volatile uint16_t*)((&var_name_tmp__755->field16)) = var_name_tmp__754;
}


void TIM_OC2NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__756, uint16_t var_name_tmp__757) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__758;    /* Address-exposed local */
  uint16_t var_name_tmp__759;    /* Address-exposed local */
  uint16_t var_name_tmp__760;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__761;
  uint16_t var_name_tmp__762;
  uint16_t var_name_tmp__763;
  uint16_t var_name_tmp__764;
  uint16_t var_name_tmp__765;
  uint16_t var_name_tmp__766;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__767;

  var_name_tmp__758 = var_name_tmp__756;
  var_name_tmp__759 = var_name_tmp__757;
  var_name_tmp__760 = 0;
  var_name_tmp__761 = var_name_tmp__758;
  var_name_tmp__762 = *(volatile uint16_t*)((&var_name_tmp__761->field16));
  var_name_tmp__760 = var_name_tmp__762;
  var_name_tmp__763 = var_name_tmp__760;
  var_name_tmp__760 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__763)) & 65407)));
  var_name_tmp__764 = var_name_tmp__759;
  var_name_tmp__765 = var_name_tmp__760;
  var_name_tmp__760 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__765)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__764)) << 4))))))));
  var_name_tmp__766 = var_name_tmp__760;
  var_name_tmp__767 = var_name_tmp__758;
  *(volatile uint16_t*)((&var_name_tmp__767->field16)) = var_name_tmp__766;
}


void TIM_OC3PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__768, uint16_t var_name_tmp__769) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__770;    /* Address-exposed local */
  uint16_t var_name_tmp__771;    /* Address-exposed local */
  uint16_t var_name_tmp__772;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__773;
  uint16_t var_name_tmp__774;
  uint16_t var_name_tmp__775;
  uint16_t var_name_tmp__776;
  uint16_t var_name_tmp__777;
  uint16_t var_name_tmp__778;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__779;

  var_name_tmp__770 = var_name_tmp__768;
  var_name_tmp__771 = var_name_tmp__769;
  var_name_tmp__772 = 0;
  var_name_tmp__773 = var_name_tmp__770;
  var_name_tmp__774 = *(volatile uint16_t*)((&var_name_tmp__773->field16));
  var_name_tmp__772 = var_name_tmp__774;
  var_name_tmp__775 = var_name_tmp__772;
  var_name_tmp__772 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__775)) & 65023)));
  var_name_tmp__776 = var_name_tmp__771;
  var_name_tmp__777 = var_name_tmp__772;
  var_name_tmp__772 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__777)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__776)) << 8))))))));
  var_name_tmp__778 = var_name_tmp__772;
  var_name_tmp__779 = var_name_tmp__770;
  *(volatile uint16_t*)((&var_name_tmp__779->field16)) = var_name_tmp__778;
}


void TIM_OC3NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__780, uint16_t var_name_tmp__781) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__782;    /* Address-exposed local */
  uint16_t var_name_tmp__783;    /* Address-exposed local */
  uint16_t var_name_tmp__784;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__785;
  uint16_t var_name_tmp__786;
  uint16_t var_name_tmp__787;
  uint16_t var_name_tmp__788;
  uint16_t var_name_tmp__789;
  uint16_t var_name_tmp__790;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__791;

  var_name_tmp__782 = var_name_tmp__780;
  var_name_tmp__783 = var_name_tmp__781;
  var_name_tmp__784 = 0;
  var_name_tmp__785 = var_name_tmp__782;
  var_name_tmp__786 = *(volatile uint16_t*)((&var_name_tmp__785->field16));
  var_name_tmp__784 = var_name_tmp__786;
  var_name_tmp__787 = var_name_tmp__784;
  var_name_tmp__784 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__787)) & 63487)));
  var_name_tmp__788 = var_name_tmp__783;
  var_name_tmp__789 = var_name_tmp__784;
  var_name_tmp__784 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__789)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__788)) << 8))))))));
  var_name_tmp__790 = var_name_tmp__784;
  var_name_tmp__791 = var_name_tmp__782;
  *(volatile uint16_t*)((&var_name_tmp__791->field16)) = var_name_tmp__790;
}


void TIM_OC4PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__792, uint16_t var_name_tmp__793) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__794;    /* Address-exposed local */
  uint16_t var_name_tmp__795;    /* Address-exposed local */
  uint16_t var_name_tmp__796;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__797;
  uint16_t var_name_tmp__798;
  uint16_t var_name_tmp__799;
  uint16_t var_name_tmp__800;
  uint16_t var_name_tmp__801;
  uint16_t var_name_tmp__802;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__803;

  var_name_tmp__794 = var_name_tmp__792;
  var_name_tmp__795 = var_name_tmp__793;
  var_name_tmp__796 = 0;
  var_name_tmp__797 = var_name_tmp__794;
  var_name_tmp__798 = *(volatile uint16_t*)((&var_name_tmp__797->field16));
  var_name_tmp__796 = var_name_tmp__798;
  var_name_tmp__799 = var_name_tmp__796;
  var_name_tmp__796 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__799)) & 57343)));
  var_name_tmp__800 = var_name_tmp__795;
  var_name_tmp__801 = var_name_tmp__796;
  var_name_tmp__796 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__801)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__800)) << 12))))))));
  var_name_tmp__802 = var_name_tmp__796;
  var_name_tmp__803 = var_name_tmp__794;
  *(volatile uint16_t*)((&var_name_tmp__803->field16)) = var_name_tmp__802;
}


void TIM_CCxCmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__804, uint16_t var_name_tmp__805, uint16_t var_name_tmp__806) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__807;    /* Address-exposed local */
  uint16_t var_name_tmp__808;    /* Address-exposed local */
  uint16_t var_name_tmp__809;    /* Address-exposed local */
  uint16_t var_name_tmp__810;    /* Address-exposed local */
  uint16_t var_name_tmp__811;
  uint16_t var_name_tmp__812;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__813;
  uint16_t* var_name_tmp__814;
  uint16_t var_name_tmp__815;
  uint16_t var_name_tmp__816;
  uint16_t var_name_tmp__817;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__818;
  uint16_t* var_name_tmp__819;
  uint16_t var_name_tmp__820;

  var_name_tmp__807 = var_name_tmp__804;
  var_name_tmp__808 = var_name_tmp__805;
  var_name_tmp__809 = var_name_tmp__806;
  var_name_tmp__810 = 0;
  var_name_tmp__811 = var_name_tmp__808;
  var_name_tmp__810 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__811)))));
  var_name_tmp__812 = var_name_tmp__810;
  var_name_tmp__813 = var_name_tmp__807;
  var_name_tmp__814 = (&var_name_tmp__813->field16);
  var_name_tmp__815 = *(volatile uint16_t*)var_name_tmp__814;
  *(volatile uint16_t*)var_name_tmp__814 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__815)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__812)))))))))));
  var_name_tmp__816 = var_name_tmp__809;
  var_name_tmp__817 = var_name_tmp__808;
  var_name_tmp__818 = var_name_tmp__807;
  var_name_tmp__819 = (&var_name_tmp__818->field16);
  var_name_tmp__820 = *(volatile uint16_t*)var_name_tmp__819;
  *(volatile uint16_t*)var_name_tmp__819 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__820)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__816)) << (((uint32_t)(uint16_t)var_name_tmp__817))))))))));
}


void TIM_CCxNCmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__821, uint16_t var_name_tmp__822, uint16_t var_name_tmp__823) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__824;    /* Address-exposed local */
  uint16_t var_name_tmp__825;    /* Address-exposed local */
  uint16_t var_name_tmp__826;    /* Address-exposed local */
  uint16_t var_name_tmp__827;    /* Address-exposed local */
  uint16_t var_name_tmp__828;
  uint16_t var_name_tmp__829;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__830;
  uint16_t* var_name_tmp__831;
  uint16_t var_name_tmp__832;
  uint16_t var_name_tmp__833;
  uint16_t var_name_tmp__834;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__835;
  uint16_t* var_name_tmp__836;
  uint16_t var_name_tmp__837;

  var_name_tmp__824 = var_name_tmp__821;
  var_name_tmp__825 = var_name_tmp__822;
  var_name_tmp__826 = var_name_tmp__823;
  var_name_tmp__827 = 0;
  var_name_tmp__828 = var_name_tmp__825;
  var_name_tmp__827 = (((uint16_t)(4 << (((uint32_t)(uint16_t)var_name_tmp__828)))));
  var_name_tmp__829 = var_name_tmp__827;
  var_name_tmp__830 = var_name_tmp__824;
  var_name_tmp__831 = (&var_name_tmp__830->field16);
  var_name_tmp__832 = *(volatile uint16_t*)var_name_tmp__831;
  *(volatile uint16_t*)var_name_tmp__831 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__832)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__829)))))))))));
  var_name_tmp__833 = var_name_tmp__826;
  var_name_tmp__834 = var_name_tmp__825;
  var_name_tmp__835 = var_name_tmp__824;
  var_name_tmp__836 = (&var_name_tmp__835->field16);
  var_name_tmp__837 = *(volatile uint16_t*)var_name_tmp__836;
  *(volatile uint16_t*)var_name_tmp__836 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__837)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__833)) << (((uint32_t)(uint16_t)var_name_tmp__834))))))))));
}


void TIM_ICInit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__838, struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__839) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__840;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__841;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__842;
  uint16_t var_name_tmp__843;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__844;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__845;
  uint16_t var_name_tmp__846;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__847;
  uint16_t var_name_tmp__848;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__849;
  uint16_t var_name_tmp__850;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__851;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__852;
  uint16_t var_name_tmp__853;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__854;
  uint16_t var_name_tmp__855;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__856;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__857;
  uint16_t var_name_tmp__858;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__859;
  uint16_t var_name_tmp__860;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__861;
  uint16_t var_name_tmp__862;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__863;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__864;
  uint16_t var_name_tmp__865;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__866;
  uint16_t var_name_tmp__867;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__868;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__869;
  uint16_t var_name_tmp__870;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__871;
  uint16_t var_name_tmp__872;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__873;
  uint16_t var_name_tmp__874;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__875;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__876;
  uint16_t var_name_tmp__877;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__878;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__879;
  uint16_t var_name_tmp__880;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__881;
  uint16_t var_name_tmp__882;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__883;
  uint16_t var_name_tmp__884;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__885;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__886;
  uint16_t var_name_tmp__887;

  var_name_tmp__840 = var_name_tmp__838;
  var_name_tmp__841 = var_name_tmp__839;
  var_name_tmp__842 = var_name_tmp__841;
  var_name_tmp__843 = *((&var_name_tmp__842->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__843)) == 0u)&1))) {
    goto var_name_tmp__888;
  } else {
    goto var_name_tmp__889;
  }

var_name_tmp__888:
  var_name_tmp__844 = var_name_tmp__840;
  var_name_tmp__845 = var_name_tmp__841;
  var_name_tmp__846 = *((&var_name_tmp__845->field1));
  var_name_tmp__847 = var_name_tmp__841;
  var_name_tmp__848 = *((&var_name_tmp__847->field2));
  var_name_tmp__849 = var_name_tmp__841;
  var_name_tmp__850 = *((&var_name_tmp__849->field4));
  TI1_Config(var_name_tmp__844, var_name_tmp__846, var_name_tmp__848, var_name_tmp__850);
  var_name_tmp__851 = var_name_tmp__840;
  var_name_tmp__852 = var_name_tmp__841;
  var_name_tmp__853 = *((&var_name_tmp__852->field3));
  TIM_SetIC1Prescaler(var_name_tmp__851, var_name_tmp__853);
  goto var_name_tmp__890;

var_name_tmp__889:
  var_name_tmp__854 = var_name_tmp__841;
  var_name_tmp__855 = *((&var_name_tmp__854->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__855)) == 4u)&1))) {
    goto var_name_tmp__891;
  } else {
    goto var_name_tmp__892;
  }

var_name_tmp__891:
  var_name_tmp__856 = var_name_tmp__840;
  var_name_tmp__857 = var_name_tmp__841;
  var_name_tmp__858 = *((&var_name_tmp__857->field1));
  var_name_tmp__859 = var_name_tmp__841;
  var_name_tmp__860 = *((&var_name_tmp__859->field2));
  var_name_tmp__861 = var_name_tmp__841;
  var_name_tmp__862 = *((&var_name_tmp__861->field4));
  TI2_Config(var_name_tmp__856, var_name_tmp__858, var_name_tmp__860, var_name_tmp__862);
  var_name_tmp__863 = var_name_tmp__840;
  var_name_tmp__864 = var_name_tmp__841;
  var_name_tmp__865 = *((&var_name_tmp__864->field3));
  TIM_SetIC2Prescaler(var_name_tmp__863, var_name_tmp__865);
  goto var_name_tmp__893;

var_name_tmp__892:
  var_name_tmp__866 = var_name_tmp__841;
  var_name_tmp__867 = *((&var_name_tmp__866->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__867)) == 8u)&1))) {
    goto var_name_tmp__894;
  } else {
    goto var_name_tmp__895;
  }

var_name_tmp__894:
  var_name_tmp__868 = var_name_tmp__840;
  var_name_tmp__869 = var_name_tmp__841;
  var_name_tmp__870 = *((&var_name_tmp__869->field1));
  var_name_tmp__871 = var_name_tmp__841;
  var_name_tmp__872 = *((&var_name_tmp__871->field2));
  var_name_tmp__873 = var_name_tmp__841;
  var_name_tmp__874 = *((&var_name_tmp__873->field4));
  TI3_Config(var_name_tmp__868, var_name_tmp__870, var_name_tmp__872, var_name_tmp__874);
  var_name_tmp__875 = var_name_tmp__840;
  var_name_tmp__876 = var_name_tmp__841;
  var_name_tmp__877 = *((&var_name_tmp__876->field3));
  TIM_SetIC3Prescaler(var_name_tmp__875, var_name_tmp__877);
  goto var_name_tmp__896;

var_name_tmp__895:
  var_name_tmp__878 = var_name_tmp__840;
  var_name_tmp__879 = var_name_tmp__841;
  var_name_tmp__880 = *((&var_name_tmp__879->field1));
  var_name_tmp__881 = var_name_tmp__841;
  var_name_tmp__882 = *((&var_name_tmp__881->field2));
  var_name_tmp__883 = var_name_tmp__841;
  var_name_tmp__884 = *((&var_name_tmp__883->field4));
  TI4_Config(var_name_tmp__878, var_name_tmp__880, var_name_tmp__882, var_name_tmp__884);
  var_name_tmp__885 = var_name_tmp__840;
  var_name_tmp__886 = var_name_tmp__841;
  var_name_tmp__887 = *((&var_name_tmp__886->field3));
  TIM_SetIC4Prescaler(var_name_tmp__885, var_name_tmp__887);
  goto var_name_tmp__896;

var_name_tmp__896:
  goto var_name_tmp__893;

var_name_tmp__893:
  goto var_name_tmp__890;

var_name_tmp__890:
  return;
}


static void TI1_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__897, uint16_t var_name_tmp__898, uint16_t var_name_tmp__899, uint16_t var_name_tmp__900) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__901;    /* Address-exposed local */
  uint16_t var_name_tmp__902;    /* Address-exposed local */
  uint16_t var_name_tmp__903;    /* Address-exposed local */
  uint16_t var_name_tmp__904;    /* Address-exposed local */
  uint16_t var_name_tmp__905;    /* Address-exposed local */
  uint16_t var_name_tmp__906;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__907;
  uint16_t* var_name_tmp__908;
  uint16_t var_name_tmp__909;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__910;
  uint16_t var_name_tmp__911;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__912;
  uint16_t var_name_tmp__913;
  uint16_t var_name_tmp__914;
  uint16_t var_name_tmp__915;
  uint16_t var_name_tmp__916;
  uint16_t var_name_tmp__917;
  uint16_t var_name_tmp__918;
  uint16_t var_name_tmp__919;
  uint16_t var_name_tmp__920;
  uint16_t var_name_tmp__921;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__922;
  uint16_t var_name_tmp__923;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__924;

  var_name_tmp__901 = var_name_tmp__897;
  var_name_tmp__902 = var_name_tmp__898;
  var_name_tmp__903 = var_name_tmp__899;
  var_name_tmp__904 = var_name_tmp__900;
  var_name_tmp__905 = 0;
  var_name_tmp__906 = 0;
  var_name_tmp__907 = var_name_tmp__901;
  var_name_tmp__908 = (&var_name_tmp__907->field16);
  var_name_tmp__909 = *(volatile uint16_t*)var_name_tmp__908;
  *(volatile uint16_t*)var_name_tmp__908 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__909)) & 65534)));
  var_name_tmp__910 = var_name_tmp__901;
  var_name_tmp__911 = *(volatile uint16_t*)((&var_name_tmp__910->field12));
  var_name_tmp__905 = var_name_tmp__911;
  var_name_tmp__912 = var_name_tmp__901;
  var_name_tmp__913 = *(volatile uint16_t*)((&var_name_tmp__912->field16));
  var_name_tmp__906 = var_name_tmp__913;
  var_name_tmp__914 = var_name_tmp__905;
  var_name_tmp__905 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__914)) & 65292)));
  var_name_tmp__915 = var_name_tmp__903;
  var_name_tmp__916 = var_name_tmp__904;
  var_name_tmp__917 = var_name_tmp__905;
  var_name_tmp__905 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__917)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__915)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__916)) << 4)))))))))))));
  var_name_tmp__918 = var_name_tmp__906;
  var_name_tmp__906 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__918)) & 65525)));
  var_name_tmp__919 = var_name_tmp__902;
  var_name_tmp__920 = var_name_tmp__906;
  var_name_tmp__906 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__920)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__919)) | 1))))))));
  var_name_tmp__921 = var_name_tmp__905;
  var_name_tmp__922 = var_name_tmp__901;
  *(volatile uint16_t*)((&var_name_tmp__922->field12)) = var_name_tmp__921;
  var_name_tmp__923 = var_name_tmp__906;
  var_name_tmp__924 = var_name_tmp__901;
  *(volatile uint16_t*)((&var_name_tmp__924->field16)) = var_name_tmp__923;
}


void TIM_SetIC1Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__925, uint16_t var_name_tmp__926) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__927;    /* Address-exposed local */
  uint16_t var_name_tmp__928;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__929;
  uint16_t* var_name_tmp__930;
  uint16_t var_name_tmp__931;
  uint16_t var_name_tmp__932;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__933;
  uint16_t* var_name_tmp__934;
  uint16_t var_name_tmp__935;

  var_name_tmp__927 = var_name_tmp__925;
  var_name_tmp__928 = var_name_tmp__926;
  var_name_tmp__929 = var_name_tmp__927;
  var_name_tmp__930 = (&var_name_tmp__929->field12);
  var_name_tmp__931 = *(volatile uint16_t*)var_name_tmp__930;
  *(volatile uint16_t*)var_name_tmp__930 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__931)) & 65523)));
  var_name_tmp__932 = var_name_tmp__928;
  var_name_tmp__933 = var_name_tmp__927;
  var_name_tmp__934 = (&var_name_tmp__933->field12);
  var_name_tmp__935 = *(volatile uint16_t*)var_name_tmp__934;
  *(volatile uint16_t*)var_name_tmp__934 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__935)) | (((uint32_t)(uint16_t)var_name_tmp__932)))));
}


static void TI2_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__936, uint16_t var_name_tmp__937, uint16_t var_name_tmp__938, uint16_t var_name_tmp__939) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__940;    /* Address-exposed local */
  uint16_t var_name_tmp__941;    /* Address-exposed local */
  uint16_t var_name_tmp__942;    /* Address-exposed local */
  uint16_t var_name_tmp__943;    /* Address-exposed local */
  uint16_t var_name_tmp__944;    /* Address-exposed local */
  uint16_t var_name_tmp__945;    /* Address-exposed local */
  uint16_t var_name_tmp__946;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__947;
  uint16_t* var_name_tmp__948;
  uint16_t var_name_tmp__949;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__950;
  uint16_t var_name_tmp__951;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__952;
  uint16_t var_name_tmp__953;
  uint16_t var_name_tmp__954;
  uint16_t var_name_tmp__955;
  uint16_t var_name_tmp__956;
  uint16_t var_name_tmp__957;
  uint16_t var_name_tmp__958;
  uint16_t var_name_tmp__959;
  uint16_t var_name_tmp__960;
  uint16_t var_name_tmp__961;
  uint16_t var_name_tmp__962;
  uint16_t var_name_tmp__963;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__964;
  uint16_t var_name_tmp__965;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__966;

  var_name_tmp__940 = var_name_tmp__936;
  var_name_tmp__941 = var_name_tmp__937;
  var_name_tmp__942 = var_name_tmp__938;
  var_name_tmp__943 = var_name_tmp__939;
  var_name_tmp__944 = 0;
  var_name_tmp__945 = 0;
  var_name_tmp__946 = 0;
  var_name_tmp__947 = var_name_tmp__940;
  var_name_tmp__948 = (&var_name_tmp__947->field16);
  var_name_tmp__949 = *(volatile uint16_t*)var_name_tmp__948;
  *(volatile uint16_t*)var_name_tmp__948 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__949)) & 65519)));
  var_name_tmp__950 = var_name_tmp__940;
  var_name_tmp__951 = *(volatile uint16_t*)((&var_name_tmp__950->field12));
  var_name_tmp__944 = var_name_tmp__951;
  var_name_tmp__952 = var_name_tmp__940;
  var_name_tmp__953 = *(volatile uint16_t*)((&var_name_tmp__952->field16));
  var_name_tmp__945 = var_name_tmp__953;
  var_name_tmp__954 = var_name_tmp__941;
  var_name_tmp__946 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__954)) << 4)));
  var_name_tmp__955 = var_name_tmp__944;
  var_name_tmp__944 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__955)) & 3327)));
  var_name_tmp__956 = var_name_tmp__943;
  var_name_tmp__957 = var_name_tmp__944;
  var_name_tmp__944 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__957)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__956)) << 12))))))));
  var_name_tmp__958 = var_name_tmp__942;
  var_name_tmp__959 = var_name_tmp__944;
  var_name_tmp__944 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__959)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__958)) << 8))))))));
  var_name_tmp__960 = var_name_tmp__945;
  var_name_tmp__945 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__960)) & 65375)));
  var_name_tmp__961 = var_name_tmp__946;
  var_name_tmp__962 = var_name_tmp__945;
  var_name_tmp__945 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__962)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__961)) | 16))))))));
  var_name_tmp__963 = var_name_tmp__944;
  var_name_tmp__964 = var_name_tmp__940;
  *(volatile uint16_t*)((&var_name_tmp__964->field12)) = var_name_tmp__963;
  var_name_tmp__965 = var_name_tmp__945;
  var_name_tmp__966 = var_name_tmp__940;
  *(volatile uint16_t*)((&var_name_tmp__966->field16)) = var_name_tmp__965;
}


void TIM_SetIC2Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__967, uint16_t var_name_tmp__968) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__969;    /* Address-exposed local */
  uint16_t var_name_tmp__970;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__971;
  uint16_t* var_name_tmp__972;
  uint16_t var_name_tmp__973;
  uint16_t var_name_tmp__974;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__975;
  uint16_t* var_name_tmp__976;
  uint16_t var_name_tmp__977;

  var_name_tmp__969 = var_name_tmp__967;
  var_name_tmp__970 = var_name_tmp__968;
  var_name_tmp__971 = var_name_tmp__969;
  var_name_tmp__972 = (&var_name_tmp__971->field12);
  var_name_tmp__973 = *(volatile uint16_t*)var_name_tmp__972;
  *(volatile uint16_t*)var_name_tmp__972 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__973)) & 62463)));
  var_name_tmp__974 = var_name_tmp__970;
  var_name_tmp__975 = var_name_tmp__969;
  var_name_tmp__976 = (&var_name_tmp__975->field12);
  var_name_tmp__977 = *(volatile uint16_t*)var_name_tmp__976;
  *(volatile uint16_t*)var_name_tmp__976 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__977)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__974)) << 8))))))));
}


static void TI3_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__978, uint16_t var_name_tmp__979, uint16_t var_name_tmp__980, uint16_t var_name_tmp__981) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__982;    /* Address-exposed local */
  uint16_t var_name_tmp__983;    /* Address-exposed local */
  uint16_t var_name_tmp__984;    /* Address-exposed local */
  uint16_t var_name_tmp__985;    /* Address-exposed local */
  uint16_t var_name_tmp__986;    /* Address-exposed local */
  uint16_t var_name_tmp__987;    /* Address-exposed local */
  uint16_t var_name_tmp__988;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__989;
  uint16_t* var_name_tmp__990;
  uint16_t var_name_tmp__991;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__992;
  uint16_t var_name_tmp__993;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__994;
  uint16_t var_name_tmp__995;
  uint16_t var_name_tmp__996;
  uint16_t var_name_tmp__997;
  uint16_t var_name_tmp__998;
  uint16_t var_name_tmp__999;
  uint16_t var_name_tmp__1000;
  uint16_t var_name_tmp__1001;
  uint16_t var_name_tmp__1002;
  uint16_t var_name_tmp__1003;
  uint16_t var_name_tmp__1004;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1005;
  uint16_t var_name_tmp__1006;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1007;

  var_name_tmp__982 = var_name_tmp__978;
  var_name_tmp__983 = var_name_tmp__979;
  var_name_tmp__984 = var_name_tmp__980;
  var_name_tmp__985 = var_name_tmp__981;
  var_name_tmp__986 = 0;
  var_name_tmp__987 = 0;
  var_name_tmp__988 = 0;
  var_name_tmp__989 = var_name_tmp__982;
  var_name_tmp__990 = (&var_name_tmp__989->field16);
  var_name_tmp__991 = *(volatile uint16_t*)var_name_tmp__990;
  *(volatile uint16_t*)var_name_tmp__990 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__991)) & 65279)));
  var_name_tmp__992 = var_name_tmp__982;
  var_name_tmp__993 = *(volatile uint16_t*)((&var_name_tmp__992->field14));
  var_name_tmp__986 = var_name_tmp__993;
  var_name_tmp__994 = var_name_tmp__982;
  var_name_tmp__995 = *(volatile uint16_t*)((&var_name_tmp__994->field16));
  var_name_tmp__987 = var_name_tmp__995;
  var_name_tmp__996 = var_name_tmp__983;
  var_name_tmp__988 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__996)) << 8)));
  var_name_tmp__997 = var_name_tmp__986;
  var_name_tmp__986 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__997)) & 65292)));
  var_name_tmp__998 = var_name_tmp__984;
  var_name_tmp__999 = var_name_tmp__985;
  var_name_tmp__1000 = var_name_tmp__986;
  var_name_tmp__986 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1000)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__998)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__999)) << 4)))))))))))));
  var_name_tmp__1001 = var_name_tmp__987;
  var_name_tmp__987 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1001)) & 62975)));
  var_name_tmp__1002 = var_name_tmp__988;
  var_name_tmp__1003 = var_name_tmp__987;
  var_name_tmp__987 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1003)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1002)) | 256))))))));
  var_name_tmp__1004 = var_name_tmp__986;
  var_name_tmp__1005 = var_name_tmp__982;
  *(volatile uint16_t*)((&var_name_tmp__1005->field14)) = var_name_tmp__1004;
  var_name_tmp__1006 = var_name_tmp__987;
  var_name_tmp__1007 = var_name_tmp__982;
  *(volatile uint16_t*)((&var_name_tmp__1007->field16)) = var_name_tmp__1006;
}


void TIM_SetIC3Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1008, uint16_t var_name_tmp__1009) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1010;    /* Address-exposed local */
  uint16_t var_name_tmp__1011;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1012;
  uint16_t* var_name_tmp__1013;
  uint16_t var_name_tmp__1014;
  uint16_t var_name_tmp__1015;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1016;
  uint16_t* var_name_tmp__1017;
  uint16_t var_name_tmp__1018;

  var_name_tmp__1010 = var_name_tmp__1008;
  var_name_tmp__1011 = var_name_tmp__1009;
  var_name_tmp__1012 = var_name_tmp__1010;
  var_name_tmp__1013 = (&var_name_tmp__1012->field14);
  var_name_tmp__1014 = *(volatile uint16_t*)var_name_tmp__1013;
  *(volatile uint16_t*)var_name_tmp__1013 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1014)) & 65523)));
  var_name_tmp__1015 = var_name_tmp__1011;
  var_name_tmp__1016 = var_name_tmp__1010;
  var_name_tmp__1017 = (&var_name_tmp__1016->field14);
  var_name_tmp__1018 = *(volatile uint16_t*)var_name_tmp__1017;
  *(volatile uint16_t*)var_name_tmp__1017 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1018)) | (((uint32_t)(uint16_t)var_name_tmp__1015)))));
}


static void TI4_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1019, uint16_t var_name_tmp__1020, uint16_t var_name_tmp__1021, uint16_t var_name_tmp__1022) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1023;    /* Address-exposed local */
  uint16_t var_name_tmp__1024;    /* Address-exposed local */
  uint16_t var_name_tmp__1025;    /* Address-exposed local */
  uint16_t var_name_tmp__1026;    /* Address-exposed local */
  uint16_t var_name_tmp__1027;    /* Address-exposed local */
  uint16_t var_name_tmp__1028;    /* Address-exposed local */
  uint16_t var_name_tmp__1029;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1030;
  uint16_t* var_name_tmp__1031;
  uint16_t var_name_tmp__1032;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1033;
  uint16_t var_name_tmp__1034;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1035;
  uint16_t var_name_tmp__1036;
  uint16_t var_name_tmp__1037;
  uint16_t var_name_tmp__1038;
  uint16_t var_name_tmp__1039;
  uint16_t var_name_tmp__1040;
  uint16_t var_name_tmp__1041;
  uint16_t var_name_tmp__1042;
  uint16_t var_name_tmp__1043;
  uint16_t var_name_tmp__1044;
  uint16_t var_name_tmp__1045;
  uint16_t var_name_tmp__1046;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1047;
  uint16_t var_name_tmp__1048;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1049;

  var_name_tmp__1023 = var_name_tmp__1019;
  var_name_tmp__1024 = var_name_tmp__1020;
  var_name_tmp__1025 = var_name_tmp__1021;
  var_name_tmp__1026 = var_name_tmp__1022;
  var_name_tmp__1027 = 0;
  var_name_tmp__1028 = 0;
  var_name_tmp__1029 = 0;
  var_name_tmp__1030 = var_name_tmp__1023;
  var_name_tmp__1031 = (&var_name_tmp__1030->field16);
  var_name_tmp__1032 = *(volatile uint16_t*)var_name_tmp__1031;
  *(volatile uint16_t*)var_name_tmp__1031 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1032)) & 61439)));
  var_name_tmp__1033 = var_name_tmp__1023;
  var_name_tmp__1034 = *(volatile uint16_t*)((&var_name_tmp__1033->field14));
  var_name_tmp__1027 = var_name_tmp__1034;
  var_name_tmp__1035 = var_name_tmp__1023;
  var_name_tmp__1036 = *(volatile uint16_t*)((&var_name_tmp__1035->field16));
  var_name_tmp__1028 = var_name_tmp__1036;
  var_name_tmp__1037 = var_name_tmp__1024;
  var_name_tmp__1029 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1037)) << 12)));
  var_name_tmp__1038 = var_name_tmp__1027;
  var_name_tmp__1027 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1038)) & 3327)));
  var_name_tmp__1039 = var_name_tmp__1025;
  var_name_tmp__1040 = var_name_tmp__1027;
  var_name_tmp__1027 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1040)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1039)) << 8))))))));
  var_name_tmp__1041 = var_name_tmp__1026;
  var_name_tmp__1042 = var_name_tmp__1027;
  var_name_tmp__1027 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1042)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1041)) << 12))))))));
  var_name_tmp__1043 = var_name_tmp__1028;
  var_name_tmp__1028 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1043)) & 24575)));
  var_name_tmp__1044 = var_name_tmp__1029;
  var_name_tmp__1045 = var_name_tmp__1028;
  var_name_tmp__1028 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1045)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1044)) | 4096))))))));
  var_name_tmp__1046 = var_name_tmp__1027;
  var_name_tmp__1047 = var_name_tmp__1023;
  *(volatile uint16_t*)((&var_name_tmp__1047->field14)) = var_name_tmp__1046;
  var_name_tmp__1048 = var_name_tmp__1028;
  var_name_tmp__1049 = var_name_tmp__1023;
  *(volatile uint16_t*)((&var_name_tmp__1049->field16)) = var_name_tmp__1048;
}


void TIM_SetIC4Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1050, uint16_t var_name_tmp__1051) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1052;    /* Address-exposed local */
  uint16_t var_name_tmp__1053;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1054;
  uint16_t* var_name_tmp__1055;
  uint16_t var_name_tmp__1056;
  uint16_t var_name_tmp__1057;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1058;
  uint16_t* var_name_tmp__1059;
  uint16_t var_name_tmp__1060;

  var_name_tmp__1052 = var_name_tmp__1050;
  var_name_tmp__1053 = var_name_tmp__1051;
  var_name_tmp__1054 = var_name_tmp__1052;
  var_name_tmp__1055 = (&var_name_tmp__1054->field14);
  var_name_tmp__1056 = *(volatile uint16_t*)var_name_tmp__1055;
  *(volatile uint16_t*)var_name_tmp__1055 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1056)) & 62463)));
  var_name_tmp__1057 = var_name_tmp__1053;
  var_name_tmp__1058 = var_name_tmp__1052;
  var_name_tmp__1059 = (&var_name_tmp__1058->field14);
  var_name_tmp__1060 = *(volatile uint16_t*)var_name_tmp__1059;
  *(volatile uint16_t*)var_name_tmp__1059 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1060)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1057)) << 8))))))));
}


void TIM_ICStructInit(struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1061) {
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1062;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1063;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1064;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1065;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1066;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1067;

  var_name_tmp__1062 = var_name_tmp__1061;
  var_name_tmp__1063 = var_name_tmp__1062;
  *((&var_name_tmp__1063->field0)) = 0;
  var_name_tmp__1064 = var_name_tmp__1062;
  *((&var_name_tmp__1064->field1)) = 0;
  var_name_tmp__1065 = var_name_tmp__1062;
  *((&var_name_tmp__1065->field2)) = 1;
  var_name_tmp__1066 = var_name_tmp__1062;
  *((&var_name_tmp__1066->field3)) = 0;
  var_name_tmp__1067 = var_name_tmp__1062;
  *((&var_name_tmp__1067->field4)) = 0;
}


void TIM_PWMIConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1068, struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1069) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1070;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1071;    /* Address-exposed local */
  uint16_t var_name_tmp__1072;    /* Address-exposed local */
  uint16_t var_name_tmp__1073;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1074;
  uint16_t var_name_tmp__1075;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1076;
  uint16_t var_name_tmp__1077;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1078;
  uint16_t var_name_tmp__1079;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1080;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1081;
  uint16_t var_name_tmp__1082;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1083;
  uint16_t var_name_tmp__1084;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1085;
  uint16_t var_name_tmp__1086;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1087;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1088;
  uint16_t var_name_tmp__1089;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1090;
  uint16_t var_name_tmp__1091;
  uint16_t var_name_tmp__1092;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1093;
  uint16_t var_name_tmp__1094;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1095;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1096;
  uint16_t var_name_tmp__1097;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1098;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1099;
  uint16_t var_name_tmp__1100;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1101;
  uint16_t var_name_tmp__1102;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1103;
  uint16_t var_name_tmp__1104;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1105;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1106;
  uint16_t var_name_tmp__1107;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1108;
  uint16_t var_name_tmp__1109;
  uint16_t var_name_tmp__1110;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1111;
  uint16_t var_name_tmp__1112;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1113;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__1114;
  uint16_t var_name_tmp__1115;

  var_name_tmp__1070 = var_name_tmp__1068;
  var_name_tmp__1071 = var_name_tmp__1069;
  var_name_tmp__1072 = 0;
  var_name_tmp__1073 = 1;
  var_name_tmp__1074 = var_name_tmp__1071;
  var_name_tmp__1075 = *((&var_name_tmp__1074->field1));
  if (((((((uint32_t)(uint16_t)var_name_tmp__1075)) == 0u)&1))) {
    goto var_name_tmp__1116;
  } else {
    goto var_name_tmp__1117;
  }

var_name_tmp__1116:
  var_name_tmp__1072 = 2;
  goto var_name_tmp__1118;

var_name_tmp__1117:
  var_name_tmp__1072 = 0;
  goto var_name_tmp__1118;

var_name_tmp__1118:
  var_name_tmp__1076 = var_name_tmp__1071;
  var_name_tmp__1077 = *((&var_name_tmp__1076->field2));
  if (((((((uint32_t)(uint16_t)var_name_tmp__1077)) == 1u)&1))) {
    goto var_name_tmp__1119;
  } else {
    goto var_name_tmp__1120;
  }

var_name_tmp__1119:
  var_name_tmp__1073 = 2;
  goto var_name_tmp__1121;

var_name_tmp__1120:
  var_name_tmp__1073 = 1;
  goto var_name_tmp__1121;

var_name_tmp__1121:
  var_name_tmp__1078 = var_name_tmp__1071;
  var_name_tmp__1079 = *((&var_name_tmp__1078->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__1079)) == 0u)&1))) {
    goto var_name_tmp__1122;
  } else {
    goto var_name_tmp__1123;
  }

var_name_tmp__1122:
  var_name_tmp__1080 = var_name_tmp__1070;
  var_name_tmp__1081 = var_name_tmp__1071;
  var_name_tmp__1082 = *((&var_name_tmp__1081->field1));
  var_name_tmp__1083 = var_name_tmp__1071;
  var_name_tmp__1084 = *((&var_name_tmp__1083->field2));
  var_name_tmp__1085 = var_name_tmp__1071;
  var_name_tmp__1086 = *((&var_name_tmp__1085->field4));
  TI1_Config(var_name_tmp__1080, var_name_tmp__1082, var_name_tmp__1084, var_name_tmp__1086);
  var_name_tmp__1087 = var_name_tmp__1070;
  var_name_tmp__1088 = var_name_tmp__1071;
  var_name_tmp__1089 = *((&var_name_tmp__1088->field3));
  TIM_SetIC1Prescaler(var_name_tmp__1087, var_name_tmp__1089);
  var_name_tmp__1090 = var_name_tmp__1070;
  var_name_tmp__1091 = var_name_tmp__1072;
  var_name_tmp__1092 = var_name_tmp__1073;
  var_name_tmp__1093 = var_name_tmp__1071;
  var_name_tmp__1094 = *((&var_name_tmp__1093->field4));
  TI2_Config(var_name_tmp__1090, var_name_tmp__1091, var_name_tmp__1092, var_name_tmp__1094);
  var_name_tmp__1095 = var_name_tmp__1070;
  var_name_tmp__1096 = var_name_tmp__1071;
  var_name_tmp__1097 = *((&var_name_tmp__1096->field3));
  TIM_SetIC2Prescaler(var_name_tmp__1095, var_name_tmp__1097);
  goto var_name_tmp__1124;

var_name_tmp__1123:
  var_name_tmp__1098 = var_name_tmp__1070;
  var_name_tmp__1099 = var_name_tmp__1071;
  var_name_tmp__1100 = *((&var_name_tmp__1099->field1));
  var_name_tmp__1101 = var_name_tmp__1071;
  var_name_tmp__1102 = *((&var_name_tmp__1101->field2));
  var_name_tmp__1103 = var_name_tmp__1071;
  var_name_tmp__1104 = *((&var_name_tmp__1103->field4));
  TI2_Config(var_name_tmp__1098, var_name_tmp__1100, var_name_tmp__1102, var_name_tmp__1104);
  var_name_tmp__1105 = var_name_tmp__1070;
  var_name_tmp__1106 = var_name_tmp__1071;
  var_name_tmp__1107 = *((&var_name_tmp__1106->field3));
  TIM_SetIC2Prescaler(var_name_tmp__1105, var_name_tmp__1107);
  var_name_tmp__1108 = var_name_tmp__1070;
  var_name_tmp__1109 = var_name_tmp__1072;
  var_name_tmp__1110 = var_name_tmp__1073;
  var_name_tmp__1111 = var_name_tmp__1071;
  var_name_tmp__1112 = *((&var_name_tmp__1111->field4));
  TI1_Config(var_name_tmp__1108, var_name_tmp__1109, var_name_tmp__1110, var_name_tmp__1112);
  var_name_tmp__1113 = var_name_tmp__1070;
  var_name_tmp__1114 = var_name_tmp__1071;
  var_name_tmp__1115 = *((&var_name_tmp__1114->field3));
  TIM_SetIC1Prescaler(var_name_tmp__1113, var_name_tmp__1115);
  goto var_name_tmp__1124;

var_name_tmp__1124:
  return;
}


uint32_t TIM_GetCapture1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1125) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1126;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1127;
  uint32_t var_name_tmp__1128;

  var_name_tmp__1126 = var_name_tmp__1125;
  var_name_tmp__1127 = var_name_tmp__1126;
  var_name_tmp__1128 = *(volatile uint32_t*)((&var_name_tmp__1127->field24));
  return var_name_tmp__1128;
}


uint32_t TIM_GetCapture2(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1129) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1130;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1131;
  uint32_t var_name_tmp__1132;

  var_name_tmp__1130 = var_name_tmp__1129;
  var_name_tmp__1131 = var_name_tmp__1130;
  var_name_tmp__1132 = *(volatile uint32_t*)((&var_name_tmp__1131->field25));
  return var_name_tmp__1132;
}


uint32_t TIM_GetCapture3(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1133) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1134;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1135;
  uint32_t var_name_tmp__1136;

  var_name_tmp__1134 = var_name_tmp__1133;
  var_name_tmp__1135 = var_name_tmp__1134;
  var_name_tmp__1136 = *(volatile uint32_t*)((&var_name_tmp__1135->field26));
  return var_name_tmp__1136;
}


uint32_t TIM_GetCapture4(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1137) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1138;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1139;
  uint32_t var_name_tmp__1140;

  var_name_tmp__1138 = var_name_tmp__1137;
  var_name_tmp__1139 = var_name_tmp__1138;
  var_name_tmp__1140 = *(volatile uint32_t*)((&var_name_tmp__1139->field27));
  return var_name_tmp__1140;
}


void TIM_BDTRConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1141, struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1142) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1143;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1144;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1145;
  uint16_t var_name_tmp__1146;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1147;
  uint16_t var_name_tmp__1148;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1149;
  uint16_t var_name_tmp__1150;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1151;
  uint16_t var_name_tmp__1152;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1153;
  uint16_t var_name_tmp__1154;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1155;
  uint16_t var_name_tmp__1156;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1157;
  uint16_t var_name_tmp__1158;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1159;

  var_name_tmp__1143 = var_name_tmp__1141;
  var_name_tmp__1144 = var_name_tmp__1142;
  var_name_tmp__1145 = var_name_tmp__1144;
  var_name_tmp__1146 = *((&var_name_tmp__1145->field0));
  var_name_tmp__1147 = var_name_tmp__1144;
  var_name_tmp__1148 = *((&var_name_tmp__1147->field1));
  var_name_tmp__1149 = var_name_tmp__1144;
  var_name_tmp__1150 = *((&var_name_tmp__1149->field2));
  var_name_tmp__1151 = var_name_tmp__1144;
  var_name_tmp__1152 = *((&var_name_tmp__1151->field3));
  var_name_tmp__1153 = var_name_tmp__1144;
  var_name_tmp__1154 = *((&var_name_tmp__1153->field4));
  var_name_tmp__1155 = var_name_tmp__1144;
  var_name_tmp__1156 = *((&var_name_tmp__1155->field5));
  var_name_tmp__1157 = var_name_tmp__1144;
  var_name_tmp__1158 = *((&var_name_tmp__1157->field6));
  var_name_tmp__1159 = var_name_tmp__1143;
  *(volatile uint16_t*)((&var_name_tmp__1159->field28)) = (((uint16_t)(((((((((uint32_t)(uint16_t)var_name_tmp__1146)) | (((uint32_t)(uint16_t)var_name_tmp__1148))) | (((uint32_t)(uint16_t)var_name_tmp__1150))) | (((uint32_t)(uint16_t)var_name_tmp__1152))) | (((uint32_t)(uint16_t)var_name_tmp__1154))) | (((uint32_t)(uint16_t)var_name_tmp__1156))) | (((uint32_t)(uint16_t)var_name_tmp__1158)))));
}


void TIM_BDTRStructInit(struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1160) {
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1161;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1162;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1163;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1164;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1165;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1166;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1167;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1168;

  var_name_tmp__1161 = var_name_tmp__1160;
  var_name_tmp__1162 = var_name_tmp__1161;
  *((&var_name_tmp__1162->field0)) = 0;
  var_name_tmp__1163 = var_name_tmp__1161;
  *((&var_name_tmp__1163->field1)) = 0;
  var_name_tmp__1164 = var_name_tmp__1161;
  *((&var_name_tmp__1164->field2)) = 0;
  var_name_tmp__1165 = var_name_tmp__1161;
  *((&var_name_tmp__1165->field3)) = 0;
  var_name_tmp__1166 = var_name_tmp__1161;
  *((&var_name_tmp__1166->field4)) = 0;
  var_name_tmp__1167 = var_name_tmp__1161;
  *((&var_name_tmp__1167->field5)) = 0;
  var_name_tmp__1168 = var_name_tmp__1161;
  *((&var_name_tmp__1168->field6)) = 0;
}


void TIM_CtrlPWMOutputs(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1169, uint32_t var_name_tmp__1170) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1171;    /* Address-exposed local */
  uint32_t var_name_tmp__1172;    /* Address-exposed local */
  uint32_t var_name_tmp__1173;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1174;
  uint16_t* var_name_tmp__1175;
  uint16_t var_name_tmp__1176;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1177;
  uint16_t* var_name_tmp__1178;
  uint16_t var_name_tmp__1179;

  var_name_tmp__1171 = var_name_tmp__1169;
  var_name_tmp__1172 = var_name_tmp__1170;
  var_name_tmp__1173 = var_name_tmp__1172;
  if ((((var_name_tmp__1173 != 0u)&1))) {
    goto var_name_tmp__1180;
  } else {
    goto var_name_tmp__1181;
  }

var_name_tmp__1180:
  var_name_tmp__1174 = var_name_tmp__1171;
  var_name_tmp__1175 = (&var_name_tmp__1174->field28);
  var_name_tmp__1176 = *(volatile uint16_t*)var_name_tmp__1175;
  *(volatile uint16_t*)var_name_tmp__1175 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1176)) | 32768)));
  goto var_name_tmp__1182;

var_name_tmp__1181:
  var_name_tmp__1177 = var_name_tmp__1171;
  var_name_tmp__1178 = (&var_name_tmp__1177->field28);
  var_name_tmp__1179 = *(volatile uint16_t*)var_name_tmp__1178;
  *(volatile uint16_t*)var_name_tmp__1178 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1179)) & 32767)));
  goto var_name_tmp__1182;

var_name_tmp__1182:
  return;
}


void TIM_SelectCOM(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1183, uint32_t var_name_tmp__1184) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1185;    /* Address-exposed local */
  uint32_t var_name_tmp__1186;    /* Address-exposed local */
  uint32_t var_name_tmp__1187;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1188;
  uint16_t* var_name_tmp__1189;
  uint16_t var_name_tmp__1190;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1191;
  uint16_t* var_name_tmp__1192;
  uint16_t var_name_tmp__1193;

  var_name_tmp__1185 = var_name_tmp__1183;
  var_name_tmp__1186 = var_name_tmp__1184;
  var_name_tmp__1187 = var_name_tmp__1186;
  if ((((var_name_tmp__1187 != 0u)&1))) {
    goto var_name_tmp__1194;
  } else {
    goto var_name_tmp__1195;
  }

var_name_tmp__1194:
  var_name_tmp__1188 = var_name_tmp__1185;
  var_name_tmp__1189 = (&var_name_tmp__1188->field2);
  var_name_tmp__1190 = *(volatile uint16_t*)var_name_tmp__1189;
  *(volatile uint16_t*)var_name_tmp__1189 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1190)) | 4)));
  goto var_name_tmp__1196;

var_name_tmp__1195:
  var_name_tmp__1191 = var_name_tmp__1185;
  var_name_tmp__1192 = (&var_name_tmp__1191->field2);
  var_name_tmp__1193 = *(volatile uint16_t*)var_name_tmp__1192;
  *(volatile uint16_t*)var_name_tmp__1192 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1193)) & 65531)));
  goto var_name_tmp__1196;

var_name_tmp__1196:
  return;
}


void TIM_CCPreloadControl(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1197, uint32_t var_name_tmp__1198) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1199;    /* Address-exposed local */
  uint32_t var_name_tmp__1200;    /* Address-exposed local */
  uint32_t var_name_tmp__1201;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1202;
  uint16_t* var_name_tmp__1203;
  uint16_t var_name_tmp__1204;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1205;
  uint16_t* var_name_tmp__1206;
  uint16_t var_name_tmp__1207;

  var_name_tmp__1199 = var_name_tmp__1197;
  var_name_tmp__1200 = var_name_tmp__1198;
  var_name_tmp__1201 = var_name_tmp__1200;
  if ((((var_name_tmp__1201 != 0u)&1))) {
    goto var_name_tmp__1208;
  } else {
    goto var_name_tmp__1209;
  }

var_name_tmp__1208:
  var_name_tmp__1202 = var_name_tmp__1199;
  var_name_tmp__1203 = (&var_name_tmp__1202->field2);
  var_name_tmp__1204 = *(volatile uint16_t*)var_name_tmp__1203;
  *(volatile uint16_t*)var_name_tmp__1203 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1204)) | 1)));
  goto var_name_tmp__1210;

var_name_tmp__1209:
  var_name_tmp__1205 = var_name_tmp__1199;
  var_name_tmp__1206 = (&var_name_tmp__1205->field2);
  var_name_tmp__1207 = *(volatile uint16_t*)var_name_tmp__1206;
  *(volatile uint16_t*)var_name_tmp__1206 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1207)) & 65534)));
  goto var_name_tmp__1210;

var_name_tmp__1210:
  return;
}


void TIM_ITConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1211, uint16_t var_name_tmp__1212, uint32_t var_name_tmp__1213) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1214;    /* Address-exposed local */
  uint16_t var_name_tmp__1215;    /* Address-exposed local */
  uint32_t var_name_tmp__1216;    /* Address-exposed local */
  uint32_t var_name_tmp__1217;
  uint16_t var_name_tmp__1218;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1219;
  uint16_t* var_name_tmp__1220;
  uint16_t var_name_tmp__1221;
  uint16_t var_name_tmp__1222;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1223;
  uint16_t* var_name_tmp__1224;
  uint16_t var_name_tmp__1225;

  var_name_tmp__1214 = var_name_tmp__1211;
  var_name_tmp__1215 = var_name_tmp__1212;
  var_name_tmp__1216 = var_name_tmp__1213;
  var_name_tmp__1217 = var_name_tmp__1216;
  if ((((var_name_tmp__1217 != 0u)&1))) {
    goto var_name_tmp__1226;
  } else {
    goto var_name_tmp__1227;
  }

var_name_tmp__1226:
  var_name_tmp__1218 = var_name_tmp__1215;
  var_name_tmp__1219 = var_name_tmp__1214;
  var_name_tmp__1220 = (&var_name_tmp__1219->field6);
  var_name_tmp__1221 = *(volatile uint16_t*)var_name_tmp__1220;
  *(volatile uint16_t*)var_name_tmp__1220 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1221)) | (((uint32_t)(uint16_t)var_name_tmp__1218)))));
  goto var_name_tmp__1228;

var_name_tmp__1227:
  var_name_tmp__1222 = var_name_tmp__1215;
  var_name_tmp__1223 = var_name_tmp__1214;
  var_name_tmp__1224 = (&var_name_tmp__1223->field6);
  var_name_tmp__1225 = *(volatile uint16_t*)var_name_tmp__1224;
  *(volatile uint16_t*)var_name_tmp__1224 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1225)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1222)))))))))));
  goto var_name_tmp__1228;

var_name_tmp__1228:
  return;
}


void TIM_GenerateEvent(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1229, uint16_t var_name_tmp__1230) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1231;    /* Address-exposed local */
  uint16_t var_name_tmp__1232;    /* Address-exposed local */
  uint16_t var_name_tmp__1233;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1234;

  var_name_tmp__1231 = var_name_tmp__1229;
  var_name_tmp__1232 = var_name_tmp__1230;
  var_name_tmp__1233 = var_name_tmp__1232;
  var_name_tmp__1234 = var_name_tmp__1231;
  *(volatile uint16_t*)((&var_name_tmp__1234->field10)) = var_name_tmp__1233;
}


uint32_t TIM_GetFlagStatus(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1235, uint16_t var_name_tmp__1236) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1237;    /* Address-exposed local */
  uint16_t var_name_tmp__1238;    /* Address-exposed local */
  uint32_t var_name_tmp__1239;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1240;
  uint16_t var_name_tmp__1241;
  uint16_t var_name_tmp__1242;
  uint32_t var_name_tmp__1243;

  var_name_tmp__1237 = var_name_tmp__1235;
  var_name_tmp__1238 = var_name_tmp__1236;
  var_name_tmp__1239 = 0;
  var_name_tmp__1240 = var_name_tmp__1237;
  var_name_tmp__1241 = *(volatile uint16_t*)((&var_name_tmp__1240->field8));
  var_name_tmp__1242 = var_name_tmp__1238;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__1241)) & (((uint32_t)(uint16_t)var_name_tmp__1242))) != 0u)&1))) {
    goto var_name_tmp__1244;
  } else {
    goto var_name_tmp__1245;
  }

var_name_tmp__1244:
  var_name_tmp__1239 = 1;
  goto var_name_tmp__1246;

var_name_tmp__1245:
  var_name_tmp__1239 = 0;
  goto var_name_tmp__1246;

var_name_tmp__1246:
  var_name_tmp__1243 = var_name_tmp__1239;
  return var_name_tmp__1243;
}


void TIM_ClearFlag(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1247, uint16_t var_name_tmp__1248) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1249;    /* Address-exposed local */
  uint16_t var_name_tmp__1250;    /* Address-exposed local */
  uint16_t var_name_tmp__1251;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1252;

  var_name_tmp__1249 = var_name_tmp__1247;
  var_name_tmp__1250 = var_name_tmp__1248;
  var_name_tmp__1251 = var_name_tmp__1250;
  var_name_tmp__1252 = var_name_tmp__1249;
  *(volatile uint16_t*)((&var_name_tmp__1252->field8)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1251))))));
}


uint32_t TIM_GetITStatus(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1253, uint16_t var_name_tmp__1254) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1255;    /* Address-exposed local */
  uint16_t var_name_tmp__1256;    /* Address-exposed local */
  uint32_t var_name_tmp__1257;    /* Address-exposed local */
  uint16_t var_name_tmp__1258;    /* Address-exposed local */
  uint16_t var_name_tmp__1259;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1260;
  uint16_t var_name_tmp__1261;
  uint16_t var_name_tmp__1262;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1263;
  uint16_t var_name_tmp__1264;
  uint16_t var_name_tmp__1265;
  uint16_t var_name_tmp__1266;
  uint16_t var_name_tmp__1267;
  uint32_t var_name_tmp__1268;

  var_name_tmp__1255 = var_name_tmp__1253;
  var_name_tmp__1256 = var_name_tmp__1254;
  var_name_tmp__1257 = 0;
  var_name_tmp__1258 = 0;
  var_name_tmp__1259 = 0;
  var_name_tmp__1260 = var_name_tmp__1255;
  var_name_tmp__1261 = *(volatile uint16_t*)((&var_name_tmp__1260->field8));
  var_name_tmp__1262 = var_name_tmp__1256;
  var_name_tmp__1258 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1261)) & (((uint32_t)(uint16_t)var_name_tmp__1262)))));
  var_name_tmp__1263 = var_name_tmp__1255;
  var_name_tmp__1264 = *(volatile uint16_t*)((&var_name_tmp__1263->field6));
  var_name_tmp__1265 = var_name_tmp__1256;
  var_name_tmp__1259 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1264)) & (((uint32_t)(uint16_t)var_name_tmp__1265)))));
  var_name_tmp__1266 = var_name_tmp__1258;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1266)) != 0u)&1))) {
    goto var_name_tmp__1269;
  } else {
    goto var_name_tmp__1270;
  }

var_name_tmp__1269:
  var_name_tmp__1267 = var_name_tmp__1259;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1267)) != 0u)&1))) {
    goto var_name_tmp__1271;
  } else {
    goto var_name_tmp__1270;
  }

var_name_tmp__1271:
  var_name_tmp__1257 = 1;
  goto var_name_tmp__1272;

var_name_tmp__1270:
  var_name_tmp__1257 = 0;
  goto var_name_tmp__1272;

var_name_tmp__1272:
  var_name_tmp__1268 = var_name_tmp__1257;
  return var_name_tmp__1268;
}


void TIM_ClearITPendingBit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1273, uint16_t var_name_tmp__1274) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1275;    /* Address-exposed local */
  uint16_t var_name_tmp__1276;    /* Address-exposed local */
  uint16_t var_name_tmp__1277;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1278;

  var_name_tmp__1275 = var_name_tmp__1273;
  var_name_tmp__1276 = var_name_tmp__1274;
  var_name_tmp__1277 = var_name_tmp__1276;
  var_name_tmp__1278 = var_name_tmp__1275;
  *(volatile uint16_t*)((&var_name_tmp__1278->field8)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1277))))));
}


void TIM_DMAConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1279, uint16_t var_name_tmp__1280, uint16_t var_name_tmp__1281) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1282;    /* Address-exposed local */
  uint16_t var_name_tmp__1283;    /* Address-exposed local */
  uint16_t var_name_tmp__1284;    /* Address-exposed local */
  uint16_t var_name_tmp__1285;
  uint16_t var_name_tmp__1286;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1287;

  var_name_tmp__1282 = var_name_tmp__1279;
  var_name_tmp__1283 = var_name_tmp__1280;
  var_name_tmp__1284 = var_name_tmp__1281;
  var_name_tmp__1285 = var_name_tmp__1283;
  var_name_tmp__1286 = var_name_tmp__1284;
  var_name_tmp__1287 = var_name_tmp__1282;
  *(volatile uint16_t*)((&var_name_tmp__1287->field30)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1285)) | (((uint32_t)(uint16_t)var_name_tmp__1286)))));
}


void TIM_DMACmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1288, uint16_t var_name_tmp__1289, uint32_t var_name_tmp__1290) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1291;    /* Address-exposed local */
  uint16_t var_name_tmp__1292;    /* Address-exposed local */
  uint32_t var_name_tmp__1293;    /* Address-exposed local */
  uint32_t var_name_tmp__1294;
  uint16_t var_name_tmp__1295;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1296;
  uint16_t* var_name_tmp__1297;
  uint16_t var_name_tmp__1298;
  uint16_t var_name_tmp__1299;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1300;
  uint16_t* var_name_tmp__1301;
  uint16_t var_name_tmp__1302;

  var_name_tmp__1291 = var_name_tmp__1288;
  var_name_tmp__1292 = var_name_tmp__1289;
  var_name_tmp__1293 = var_name_tmp__1290;
  var_name_tmp__1294 = var_name_tmp__1293;
  if ((((var_name_tmp__1294 != 0u)&1))) {
    goto var_name_tmp__1303;
  } else {
    goto var_name_tmp__1304;
  }

var_name_tmp__1303:
  var_name_tmp__1295 = var_name_tmp__1292;
  var_name_tmp__1296 = var_name_tmp__1291;
  var_name_tmp__1297 = (&var_name_tmp__1296->field6);
  var_name_tmp__1298 = *(volatile uint16_t*)var_name_tmp__1297;
  *(volatile uint16_t*)var_name_tmp__1297 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1298)) | (((uint32_t)(uint16_t)var_name_tmp__1295)))));
  goto var_name_tmp__1305;

var_name_tmp__1304:
  var_name_tmp__1299 = var_name_tmp__1292;
  var_name_tmp__1300 = var_name_tmp__1291;
  var_name_tmp__1301 = (&var_name_tmp__1300->field6);
  var_name_tmp__1302 = *(volatile uint16_t*)var_name_tmp__1301;
  *(volatile uint16_t*)var_name_tmp__1301 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1302)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1299)))))))))));
  goto var_name_tmp__1305;

var_name_tmp__1305:
  return;
}


void TIM_SelectCCDMA(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1306, uint32_t var_name_tmp__1307) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1308;    /* Address-exposed local */
  uint32_t var_name_tmp__1309;    /* Address-exposed local */
  uint32_t var_name_tmp__1310;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1311;
  uint16_t* var_name_tmp__1312;
  uint16_t var_name_tmp__1313;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1314;
  uint16_t* var_name_tmp__1315;
  uint16_t var_name_tmp__1316;

  var_name_tmp__1308 = var_name_tmp__1306;
  var_name_tmp__1309 = var_name_tmp__1307;
  var_name_tmp__1310 = var_name_tmp__1309;
  if ((((var_name_tmp__1310 != 0u)&1))) {
    goto var_name_tmp__1317;
  } else {
    goto var_name_tmp__1318;
  }

var_name_tmp__1317:
  var_name_tmp__1311 = var_name_tmp__1308;
  var_name_tmp__1312 = (&var_name_tmp__1311->field2);
  var_name_tmp__1313 = *(volatile uint16_t*)var_name_tmp__1312;
  *(volatile uint16_t*)var_name_tmp__1312 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1313)) | 8)));
  goto var_name_tmp__1319;

var_name_tmp__1318:
  var_name_tmp__1314 = var_name_tmp__1308;
  var_name_tmp__1315 = (&var_name_tmp__1314->field2);
  var_name_tmp__1316 = *(volatile uint16_t*)var_name_tmp__1315;
  *(volatile uint16_t*)var_name_tmp__1315 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1316)) & 65527)));
  goto var_name_tmp__1319;

var_name_tmp__1319:
  return;
}


void TIM_InternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1320) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1321;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1322;
  uint16_t* var_name_tmp__1323;
  uint16_t var_name_tmp__1324;

  var_name_tmp__1321 = var_name_tmp__1320;
  var_name_tmp__1322 = var_name_tmp__1321;
  var_name_tmp__1323 = (&var_name_tmp__1322->field4);
  var_name_tmp__1324 = *(volatile uint16_t*)var_name_tmp__1323;
  *(volatile uint16_t*)var_name_tmp__1323 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1324)) & 65528)));
}


void TIM_ITRxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1325, uint16_t var_name_tmp__1326) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1327;    /* Address-exposed local */
  uint16_t var_name_tmp__1328;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1329;
  uint16_t var_name_tmp__1330;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1331;
  uint16_t* var_name_tmp__1332;
  uint16_t var_name_tmp__1333;

  var_name_tmp__1327 = var_name_tmp__1325;
  var_name_tmp__1328 = var_name_tmp__1326;
  var_name_tmp__1329 = var_name_tmp__1327;
  var_name_tmp__1330 = var_name_tmp__1328;
  TIM_SelectInputTrigger(var_name_tmp__1329, var_name_tmp__1330);
  var_name_tmp__1331 = var_name_tmp__1327;
  var_name_tmp__1332 = (&var_name_tmp__1331->field4);
  var_name_tmp__1333 = *(volatile uint16_t*)var_name_tmp__1332;
  *(volatile uint16_t*)var_name_tmp__1332 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1333)) | 7)));
}


void TIM_SelectInputTrigger(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1334, uint16_t var_name_tmp__1335) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1336;    /* Address-exposed local */
  uint16_t var_name_tmp__1337;    /* Address-exposed local */
  uint16_t var_name_tmp__1338;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1339;
  uint16_t var_name_tmp__1340;
  uint16_t var_name_tmp__1341;
  uint16_t var_name_tmp__1342;
  uint16_t var_name_tmp__1343;
  uint16_t var_name_tmp__1344;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1345;

  var_name_tmp__1336 = var_name_tmp__1334;
  var_name_tmp__1337 = var_name_tmp__1335;
  var_name_tmp__1338 = 0;
  var_name_tmp__1339 = var_name_tmp__1336;
  var_name_tmp__1340 = *(volatile uint16_t*)((&var_name_tmp__1339->field4));
  var_name_tmp__1338 = var_name_tmp__1340;
  var_name_tmp__1341 = var_name_tmp__1338;
  var_name_tmp__1338 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1341)) & 65423)));
  var_name_tmp__1342 = var_name_tmp__1337;
  var_name_tmp__1343 = var_name_tmp__1338;
  var_name_tmp__1338 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1343)) | (((uint32_t)(uint16_t)var_name_tmp__1342)))));
  var_name_tmp__1344 = var_name_tmp__1338;
  var_name_tmp__1345 = var_name_tmp__1336;
  *(volatile uint16_t*)((&var_name_tmp__1345->field4)) = var_name_tmp__1344;
}


void TIM_TIxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1346, uint16_t var_name_tmp__1347, uint16_t var_name_tmp__1348, uint16_t var_name_tmp__1349) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1350;    /* Address-exposed local */
  uint16_t var_name_tmp__1351;    /* Address-exposed local */
  uint16_t var_name_tmp__1352;    /* Address-exposed local */
  uint16_t var_name_tmp__1353;    /* Address-exposed local */
  uint16_t var_name_tmp__1354;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1355;
  uint16_t var_name_tmp__1356;
  uint16_t var_name_tmp__1357;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1358;
  uint16_t var_name_tmp__1359;
  uint16_t var_name_tmp__1360;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1361;
  uint16_t var_name_tmp__1362;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1363;
  uint16_t* var_name_tmp__1364;
  uint16_t var_name_tmp__1365;

  var_name_tmp__1350 = var_name_tmp__1346;
  var_name_tmp__1351 = var_name_tmp__1347;
  var_name_tmp__1352 = var_name_tmp__1348;
  var_name_tmp__1353 = var_name_tmp__1349;
  var_name_tmp__1354 = var_name_tmp__1351;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1354)) == 96u)&1))) {
    goto var_name_tmp__1366;
  } else {
    goto var_name_tmp__1367;
  }

var_name_tmp__1366:
  var_name_tmp__1355 = var_name_tmp__1350;
  var_name_tmp__1356 = var_name_tmp__1352;
  var_name_tmp__1357 = var_name_tmp__1353;
  TI2_Config(var_name_tmp__1355, var_name_tmp__1356, 1, var_name_tmp__1357);
  goto var_name_tmp__1368;

var_name_tmp__1367:
  var_name_tmp__1358 = var_name_tmp__1350;
  var_name_tmp__1359 = var_name_tmp__1352;
  var_name_tmp__1360 = var_name_tmp__1353;
  TI1_Config(var_name_tmp__1358, var_name_tmp__1359, 1, var_name_tmp__1360);
  goto var_name_tmp__1368;

var_name_tmp__1368:
  var_name_tmp__1361 = var_name_tmp__1350;
  var_name_tmp__1362 = var_name_tmp__1351;
  TIM_SelectInputTrigger(var_name_tmp__1361, var_name_tmp__1362);
  var_name_tmp__1363 = var_name_tmp__1350;
  var_name_tmp__1364 = (&var_name_tmp__1363->field4);
  var_name_tmp__1365 = *(volatile uint16_t*)var_name_tmp__1364;
  *(volatile uint16_t*)var_name_tmp__1364 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1365)) | 7)));
}


void TIM_ETRClockMode1Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1369, uint16_t var_name_tmp__1370, uint16_t var_name_tmp__1371, uint16_t var_name_tmp__1372) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1373;    /* Address-exposed local */
  uint16_t var_name_tmp__1374;    /* Address-exposed local */
  uint16_t var_name_tmp__1375;    /* Address-exposed local */
  uint16_t var_name_tmp__1376;    /* Address-exposed local */
  uint16_t var_name_tmp__1377;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1378;
  uint16_t var_name_tmp__1379;
  uint16_t var_name_tmp__1380;
  uint16_t var_name_tmp__1381;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1382;
  uint16_t var_name_tmp__1383;
  uint16_t var_name_tmp__1384;
  uint16_t var_name_tmp__1385;
  uint16_t var_name_tmp__1386;
  uint16_t var_name_tmp__1387;
  uint16_t var_name_tmp__1388;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1389;

  var_name_tmp__1373 = var_name_tmp__1369;
  var_name_tmp__1374 = var_name_tmp__1370;
  var_name_tmp__1375 = var_name_tmp__1371;
  var_name_tmp__1376 = var_name_tmp__1372;
  var_name_tmp__1377 = 0;
  var_name_tmp__1378 = var_name_tmp__1373;
  var_name_tmp__1379 = var_name_tmp__1374;
  var_name_tmp__1380 = var_name_tmp__1375;
  var_name_tmp__1381 = var_name_tmp__1376;
  TIM_ETRConfig(var_name_tmp__1378, var_name_tmp__1379, var_name_tmp__1380, var_name_tmp__1381);
  var_name_tmp__1382 = var_name_tmp__1373;
  var_name_tmp__1383 = *(volatile uint16_t*)((&var_name_tmp__1382->field4));
  var_name_tmp__1377 = var_name_tmp__1383;
  var_name_tmp__1384 = var_name_tmp__1377;
  var_name_tmp__1377 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1384)) & 65528)));
  var_name_tmp__1385 = var_name_tmp__1377;
  var_name_tmp__1377 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1385)) | 7)));
  var_name_tmp__1386 = var_name_tmp__1377;
  var_name_tmp__1377 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1386)) & 65423)));
  var_name_tmp__1387 = var_name_tmp__1377;
  var_name_tmp__1377 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1387)) | 112)));
  var_name_tmp__1388 = var_name_tmp__1377;
  var_name_tmp__1389 = var_name_tmp__1373;
  *(volatile uint16_t*)((&var_name_tmp__1389->field4)) = var_name_tmp__1388;
}


void TIM_ETRConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1390, uint16_t var_name_tmp__1391, uint16_t var_name_tmp__1392, uint16_t var_name_tmp__1393) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1394;    /* Address-exposed local */
  uint16_t var_name_tmp__1395;    /* Address-exposed local */
  uint16_t var_name_tmp__1396;    /* Address-exposed local */
  uint16_t var_name_tmp__1397;    /* Address-exposed local */
  uint16_t var_name_tmp__1398;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1399;
  uint16_t var_name_tmp__1400;
  uint16_t var_name_tmp__1401;
  uint16_t var_name_tmp__1402;
  uint16_t var_name_tmp__1403;
  uint16_t var_name_tmp__1404;
  uint16_t var_name_tmp__1405;
  uint16_t var_name_tmp__1406;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1407;

  var_name_tmp__1394 = var_name_tmp__1390;
  var_name_tmp__1395 = var_name_tmp__1391;
  var_name_tmp__1396 = var_name_tmp__1392;
  var_name_tmp__1397 = var_name_tmp__1393;
  var_name_tmp__1398 = 0;
  var_name_tmp__1399 = var_name_tmp__1394;
  var_name_tmp__1400 = *(volatile uint16_t*)((&var_name_tmp__1399->field4));
  var_name_tmp__1398 = var_name_tmp__1400;
  var_name_tmp__1401 = var_name_tmp__1398;
  var_name_tmp__1398 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1401)) & 255)));
  var_name_tmp__1402 = var_name_tmp__1395;
  var_name_tmp__1403 = var_name_tmp__1396;
  var_name_tmp__1404 = var_name_tmp__1397;
  var_name_tmp__1405 = var_name_tmp__1398;
  var_name_tmp__1398 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1405)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1402)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1403)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1404)) << 8))))))))))))))))));
  var_name_tmp__1406 = var_name_tmp__1398;
  var_name_tmp__1407 = var_name_tmp__1394;
  *(volatile uint16_t*)((&var_name_tmp__1407->field4)) = var_name_tmp__1406;
}


void TIM_ETRClockMode2Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1408, uint16_t var_name_tmp__1409, uint16_t var_name_tmp__1410, uint16_t var_name_tmp__1411) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1412;    /* Address-exposed local */
  uint16_t var_name_tmp__1413;    /* Address-exposed local */
  uint16_t var_name_tmp__1414;    /* Address-exposed local */
  uint16_t var_name_tmp__1415;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1416;
  uint16_t var_name_tmp__1417;
  uint16_t var_name_tmp__1418;
  uint16_t var_name_tmp__1419;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1420;
  uint16_t* var_name_tmp__1421;
  uint16_t var_name_tmp__1422;

  var_name_tmp__1412 = var_name_tmp__1408;
  var_name_tmp__1413 = var_name_tmp__1409;
  var_name_tmp__1414 = var_name_tmp__1410;
  var_name_tmp__1415 = var_name_tmp__1411;
  var_name_tmp__1416 = var_name_tmp__1412;
  var_name_tmp__1417 = var_name_tmp__1413;
  var_name_tmp__1418 = var_name_tmp__1414;
  var_name_tmp__1419 = var_name_tmp__1415;
  TIM_ETRConfig(var_name_tmp__1416, var_name_tmp__1417, var_name_tmp__1418, var_name_tmp__1419);
  var_name_tmp__1420 = var_name_tmp__1412;
  var_name_tmp__1421 = (&var_name_tmp__1420->field4);
  var_name_tmp__1422 = *(volatile uint16_t*)var_name_tmp__1421;
  *(volatile uint16_t*)var_name_tmp__1421 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1422)) | 16384)));
}


void TIM_SelectOutputTrigger(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1423, uint16_t var_name_tmp__1424) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1425;    /* Address-exposed local */
  uint16_t var_name_tmp__1426;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1427;
  uint16_t* var_name_tmp__1428;
  uint16_t var_name_tmp__1429;
  uint16_t var_name_tmp__1430;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1431;
  uint16_t* var_name_tmp__1432;
  uint16_t var_name_tmp__1433;

  var_name_tmp__1425 = var_name_tmp__1423;
  var_name_tmp__1426 = var_name_tmp__1424;
  var_name_tmp__1427 = var_name_tmp__1425;
  var_name_tmp__1428 = (&var_name_tmp__1427->field2);
  var_name_tmp__1429 = *(volatile uint16_t*)var_name_tmp__1428;
  *(volatile uint16_t*)var_name_tmp__1428 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1429)) & 65423)));
  var_name_tmp__1430 = var_name_tmp__1426;
  var_name_tmp__1431 = var_name_tmp__1425;
  var_name_tmp__1432 = (&var_name_tmp__1431->field2);
  var_name_tmp__1433 = *(volatile uint16_t*)var_name_tmp__1432;
  *(volatile uint16_t*)var_name_tmp__1432 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1433)) | (((uint32_t)(uint16_t)var_name_tmp__1430)))));
}


void TIM_SelectSlaveMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1434, uint16_t var_name_tmp__1435) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1436;    /* Address-exposed local */
  uint16_t var_name_tmp__1437;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1438;
  uint16_t* var_name_tmp__1439;
  uint16_t var_name_tmp__1440;
  uint16_t var_name_tmp__1441;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1442;
  uint16_t* var_name_tmp__1443;
  uint16_t var_name_tmp__1444;

  var_name_tmp__1436 = var_name_tmp__1434;
  var_name_tmp__1437 = var_name_tmp__1435;
  var_name_tmp__1438 = var_name_tmp__1436;
  var_name_tmp__1439 = (&var_name_tmp__1438->field4);
  var_name_tmp__1440 = *(volatile uint16_t*)var_name_tmp__1439;
  *(volatile uint16_t*)var_name_tmp__1439 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1440)) & 65528)));
  var_name_tmp__1441 = var_name_tmp__1437;
  var_name_tmp__1442 = var_name_tmp__1436;
  var_name_tmp__1443 = (&var_name_tmp__1442->field4);
  var_name_tmp__1444 = *(volatile uint16_t*)var_name_tmp__1443;
  *(volatile uint16_t*)var_name_tmp__1443 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1444)) | (((uint32_t)(uint16_t)var_name_tmp__1441)))));
}


void TIM_SelectMasterSlaveMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1445, uint16_t var_name_tmp__1446) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1447;    /* Address-exposed local */
  uint16_t var_name_tmp__1448;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1449;
  uint16_t* var_name_tmp__1450;
  uint16_t var_name_tmp__1451;
  uint16_t var_name_tmp__1452;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1453;
  uint16_t* var_name_tmp__1454;
  uint16_t var_name_tmp__1455;

  var_name_tmp__1447 = var_name_tmp__1445;
  var_name_tmp__1448 = var_name_tmp__1446;
  var_name_tmp__1449 = var_name_tmp__1447;
  var_name_tmp__1450 = (&var_name_tmp__1449->field4);
  var_name_tmp__1451 = *(volatile uint16_t*)var_name_tmp__1450;
  *(volatile uint16_t*)var_name_tmp__1450 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1451)) & 65407)));
  var_name_tmp__1452 = var_name_tmp__1448;
  var_name_tmp__1453 = var_name_tmp__1447;
  var_name_tmp__1454 = (&var_name_tmp__1453->field4);
  var_name_tmp__1455 = *(volatile uint16_t*)var_name_tmp__1454;
  *(volatile uint16_t*)var_name_tmp__1454 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1455)) | (((uint32_t)(uint16_t)var_name_tmp__1452)))));
}


void TIM_EncoderInterfaceConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1456, uint16_t var_name_tmp__1457, uint16_t var_name_tmp__1458, uint16_t var_name_tmp__1459) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1460;    /* Address-exposed local */
  uint16_t var_name_tmp__1461;    /* Address-exposed local */
  uint16_t var_name_tmp__1462;    /* Address-exposed local */
  uint16_t var_name_tmp__1463;    /* Address-exposed local */
  uint16_t var_name_tmp__1464;    /* Address-exposed local */
  uint16_t var_name_tmp__1465;    /* Address-exposed local */
  uint16_t var_name_tmp__1466;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1467;
  uint16_t var_name_tmp__1468;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1469;
  uint16_t var_name_tmp__1470;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1471;
  uint16_t var_name_tmp__1472;
  uint16_t var_name_tmp__1473;
  uint16_t var_name_tmp__1474;
  uint16_t var_name_tmp__1475;
  uint16_t var_name_tmp__1476;
  uint16_t var_name_tmp__1477;
  uint16_t var_name_tmp__1478;
  uint16_t var_name_tmp__1479;
  uint16_t var_name_tmp__1480;
  uint16_t var_name_tmp__1481;
  uint16_t var_name_tmp__1482;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1483;
  uint16_t var_name_tmp__1484;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1485;
  uint16_t var_name_tmp__1486;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1487;

  var_name_tmp__1460 = var_name_tmp__1456;
  var_name_tmp__1461 = var_name_tmp__1457;
  var_name_tmp__1462 = var_name_tmp__1458;
  var_name_tmp__1463 = var_name_tmp__1459;
  var_name_tmp__1464 = 0;
  var_name_tmp__1465 = 0;
  var_name_tmp__1466 = 0;
  var_name_tmp__1467 = var_name_tmp__1460;
  var_name_tmp__1468 = *(volatile uint16_t*)((&var_name_tmp__1467->field4));
  var_name_tmp__1464 = var_name_tmp__1468;
  var_name_tmp__1469 = var_name_tmp__1460;
  var_name_tmp__1470 = *(volatile uint16_t*)((&var_name_tmp__1469->field12));
  var_name_tmp__1465 = var_name_tmp__1470;
  var_name_tmp__1471 = var_name_tmp__1460;
  var_name_tmp__1472 = *(volatile uint16_t*)((&var_name_tmp__1471->field16));
  var_name_tmp__1466 = var_name_tmp__1472;
  var_name_tmp__1473 = var_name_tmp__1464;
  var_name_tmp__1464 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1473)) & 65528)));
  var_name_tmp__1474 = var_name_tmp__1461;
  var_name_tmp__1475 = var_name_tmp__1464;
  var_name_tmp__1464 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1475)) | (((uint32_t)(uint16_t)var_name_tmp__1474)))));
  var_name_tmp__1476 = var_name_tmp__1465;
  var_name_tmp__1465 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1476)) & 64764)));
  var_name_tmp__1477 = var_name_tmp__1465;
  var_name_tmp__1465 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1477)) | 257)));
  var_name_tmp__1478 = var_name_tmp__1466;
  var_name_tmp__1466 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1478)) & 65501)));
  var_name_tmp__1479 = var_name_tmp__1462;
  var_name_tmp__1480 = var_name_tmp__1463;
  var_name_tmp__1481 = var_name_tmp__1466;
  var_name_tmp__1466 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1481)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1479)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1480)) << 4)))))))))))));
  var_name_tmp__1482 = var_name_tmp__1464;
  var_name_tmp__1483 = var_name_tmp__1460;
  *(volatile uint16_t*)((&var_name_tmp__1483->field4)) = var_name_tmp__1482;
  var_name_tmp__1484 = var_name_tmp__1465;
  var_name_tmp__1485 = var_name_tmp__1460;
  *(volatile uint16_t*)((&var_name_tmp__1485->field12)) = var_name_tmp__1484;
  var_name_tmp__1486 = var_name_tmp__1466;
  var_name_tmp__1487 = var_name_tmp__1460;
  *(volatile uint16_t*)((&var_name_tmp__1487->field16)) = var_name_tmp__1486;
}


void TIM_SelectHallSensor(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1488, uint32_t var_name_tmp__1489) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1490;    /* Address-exposed local */
  uint32_t var_name_tmp__1491;    /* Address-exposed local */
  uint32_t var_name_tmp__1492;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1493;
  uint16_t* var_name_tmp__1494;
  uint16_t var_name_tmp__1495;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1496;
  uint16_t* var_name_tmp__1497;
  uint16_t var_name_tmp__1498;

  var_name_tmp__1490 = var_name_tmp__1488;
  var_name_tmp__1491 = var_name_tmp__1489;
  var_name_tmp__1492 = var_name_tmp__1491;
  if ((((var_name_tmp__1492 != 0u)&1))) {
    goto var_name_tmp__1499;
  } else {
    goto var_name_tmp__1500;
  }

var_name_tmp__1499:
  var_name_tmp__1493 = var_name_tmp__1490;
  var_name_tmp__1494 = (&var_name_tmp__1493->field2);
  var_name_tmp__1495 = *(volatile uint16_t*)var_name_tmp__1494;
  *(volatile uint16_t*)var_name_tmp__1494 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1495)) | 128)));
  goto var_name_tmp__1501;

var_name_tmp__1500:
  var_name_tmp__1496 = var_name_tmp__1490;
  var_name_tmp__1497 = (&var_name_tmp__1496->field2);
  var_name_tmp__1498 = *(volatile uint16_t*)var_name_tmp__1497;
  *(volatile uint16_t*)var_name_tmp__1497 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1498)) & 65407)));
  goto var_name_tmp__1501;

var_name_tmp__1501:
  return;
}


void TIM_RemapConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1502, uint16_t var_name_tmp__1503) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1504;    /* Address-exposed local */
  uint16_t var_name_tmp__1505;    /* Address-exposed local */
  uint16_t var_name_tmp__1506;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1507;

  var_name_tmp__1504 = var_name_tmp__1502;
  var_name_tmp__1505 = var_name_tmp__1503;
  var_name_tmp__1506 = var_name_tmp__1505;
  var_name_tmp__1507 = var_name_tmp__1504;
  *(volatile uint16_t*)((&var_name_tmp__1507->field34)) = var_name_tmp__1506;
}


uint16_t get_TIM_CR1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1508) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1509;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1510;
  uint16_t var_name_tmp__1511;

  var_name_tmp__1509 = var_name_tmp__1508;
  var_name_tmp__1510 = var_name_tmp__1509;
  var_name_tmp__1511 = *(volatile uint16_t*)((&var_name_tmp__1510->field0));
  return var_name_tmp__1511;
}

