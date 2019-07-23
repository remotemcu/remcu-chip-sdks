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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


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
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__64;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__65;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__66;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__67;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__68;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__69;
  uint16_t var_name_tmp__70;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__71;
  uint64_t var_name_load_i16_2;
  uint16_t var_name_tmp__72;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__73;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__74;
  uint16_t var_name_tmp__75;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__76;
  uint64_t var_name_load_i16_5;
  uint16_t var_name_tmp__77;
  uint16_t var_name_tmp__78;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__79;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__80;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__81;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__82;
  uint64_t var_name_load_i16_10;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__83;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__84;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__85;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__86;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__87;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__88;

  var_name_tmp__60 = var_name_tmp__58;
  var_name_tmp__61 = var_name_tmp__59;
  var_name_tmp__62 = 0;
  var_name_tmp__63 = var_name_tmp__60;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__63->field0)))), 16, 4);
  var_name_tmp__62 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__64 = var_name_tmp__60;
  if ((((var_name_tmp__64 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__90;
  }

var_name_tmp__90:
  var_name_tmp__65 = var_name_tmp__60;
  if ((((var_name_tmp__65 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__91;
  }

var_name_tmp__91:
  var_name_tmp__66 = var_name_tmp__60;
  if ((((var_name_tmp__66 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073741824)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__92;
  }

var_name_tmp__92:
  var_name_tmp__67 = var_name_tmp__60;
  if ((((var_name_tmp__67 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073742848)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__93;
  }

var_name_tmp__93:
  var_name_tmp__68 = var_name_tmp__60;
  if ((((var_name_tmp__68 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073743872)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__94;
  }

var_name_tmp__94:
  var_name_tmp__69 = var_name_tmp__60;
  if ((((var_name_tmp__69 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073744896)))&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__89:
  var_name_tmp__70 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__70)) & 65423)));
  var_name_tmp__71 = var_name_tmp__61;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__71->field1)))), 16, 2);
  var_name_tmp__72 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__72)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))))));
  goto var_name_tmp__95;

var_name_tmp__95:
  var_name_tmp__73 = var_name_tmp__60;
  if ((((var_name_tmp__73 != ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073745920)))&1))) {
    goto var_name_tmp__96;
  } else {
    goto var_name_tmp__97;
  }

var_name_tmp__96:
  var_name_tmp__74 = var_name_tmp__60;
  if ((((var_name_tmp__74 != ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073746944)))&1))) {
    goto var_name_tmp__98;
  } else {
    goto var_name_tmp__97;
  }

var_name_tmp__98:
  var_name_tmp__75 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__75)) & 64767)));
  var_name_tmp__76 = var_name_tmp__61;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__76->field3)))), 16, 4);
  var_name_tmp__77 = var_name_tmp__62;
  var_name_tmp__62 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__77)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5)))))));
  goto var_name_tmp__97;

var_name_tmp__97:
  var_name_tmp__78 = var_name_tmp__62;
  var_name_tmp__79 = var_name_tmp__60;
  __adin_store_((((uint8_t*)((&var_name_tmp__79->field0)))), (((uint64_t)(uint16_t)var_name_tmp__78)), 16, 4);
  var_name_tmp__80 = var_name_tmp__61;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__80->field2)))), 32, 4);
  var_name_tmp__81 = var_name_tmp__60;
  __adin_store_((((uint8_t*)((&var_name_tmp__81->field21)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__82 = var_name_tmp__61;
  var_name_load_i16_10 = __adin_load_((((uint8_t*)((&var_name_tmp__82->field0)))), 16, 4);
  var_name_tmp__83 = var_name_tmp__60;
  __adin_store_((((uint8_t*)((&var_name_tmp__83->field19)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_load_i16_10)))), 16, 4);
  var_name_tmp__84 = var_name_tmp__60;
  if ((((var_name_tmp__84 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__99;
  } else {
    goto var_name_tmp__100;
  }

var_name_tmp__100:
  var_name_tmp__85 = var_name_tmp__60;
  if ((((var_name_tmp__85 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__99;
  } else {
    goto var_name_tmp__101;
  }

var_name_tmp__99:
  var_name_tmp__86 = var_name_tmp__61;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__86->field4)), 8, 2);
  var_name_tmp__87 = var_name_tmp__60;
  __adin_store_((((uint8_t*)((&var_name_tmp__87->field22)))), (((uint64_t)(uint16_t)(((uint16_t)(uint8_t)(((uint8_t)var_name_load_i8_)))))), 16, 4);
  goto var_name_tmp__101;

var_name_tmp__101:
  var_name_tmp__88 = var_name_tmp__60;
  __adin_store_((((uint8_t*)((&var_name_tmp__88->field10)))), UINT64_C(1), 16, 4);
}


void TIM_TimeBaseStructInit(struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__102) {
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__103;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__104;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__105;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__106;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__107;
  struct l_struct_struct_OC_TIM_TimeBaseInitTypeDef* var_name_tmp__108;

  var_name_tmp__103 = var_name_tmp__102;
  var_name_tmp__104 = var_name_tmp__103;
  __adin_store_((((uint8_t*)((&var_name_tmp__104->field2)))), UINT64_C(4294967295), 32, 4);
  var_name_tmp__105 = var_name_tmp__103;
  __adin_store_((((uint8_t*)((&var_name_tmp__105->field0)))), UINT64_C(0), 16, 4);
  var_name_tmp__106 = var_name_tmp__103;
  __adin_store_((((uint8_t*)((&var_name_tmp__106->field3)))), UINT64_C(0), 16, 4);
  var_name_tmp__107 = var_name_tmp__103;
  __adin_store_((((uint8_t*)((&var_name_tmp__107->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__108 = var_name_tmp__103;
  __adin_store_(((&var_name_tmp__108->field4)), UINT64_C(0), 8, 2);
}


void TIM_PrescalerConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__109, uint16_t var_name_tmp__110, uint16_t var_name_tmp__111) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__112;    /* Address-exposed local */
  uint16_t var_name_tmp__113;    /* Address-exposed local */
  uint16_t var_name_tmp__114;    /* Address-exposed local */
  uint16_t var_name_tmp__115;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__116;
  uint16_t var_name_tmp__117;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__118;

  var_name_tmp__112 = var_name_tmp__109;
  var_name_tmp__113 = var_name_tmp__110;
  var_name_tmp__114 = var_name_tmp__111;
  var_name_tmp__115 = var_name_tmp__113;
  var_name_tmp__116 = var_name_tmp__112;
  __adin_store_((((uint8_t*)((&var_name_tmp__116->field19)))), (((uint64_t)(uint16_t)var_name_tmp__115)), 16, 4);
  var_name_tmp__117 = var_name_tmp__114;
  var_name_tmp__118 = var_name_tmp__112;
  __adin_store_((((uint8_t*)((&var_name_tmp__118->field10)))), (((uint64_t)(uint16_t)var_name_tmp__117)), 16, 4);
}


void TIM_CounterModeConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__119, uint16_t var_name_tmp__120) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__121;    /* Address-exposed local */
  uint16_t var_name_tmp__122;    /* Address-exposed local */
  uint16_t var_name_tmp__123;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__124;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__125;
  uint16_t var_name_tmp__126;
  uint16_t var_name_tmp__127;
  uint16_t var_name_tmp__128;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__129;

  var_name_tmp__121 = var_name_tmp__119;
  var_name_tmp__122 = var_name_tmp__120;
  var_name_tmp__123 = 0;
  var_name_tmp__124 = var_name_tmp__121;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__124->field0)))), 16, 4);
  var_name_tmp__123 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__125 = var_name_tmp__123;
  var_name_tmp__123 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__125)) & 65423)));
  var_name_tmp__126 = var_name_tmp__122;
  var_name_tmp__127 = var_name_tmp__123;
  var_name_tmp__123 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__127)) | (((uint32_t)(uint16_t)var_name_tmp__126)))));
  var_name_tmp__128 = var_name_tmp__123;
  var_name_tmp__129 = var_name_tmp__121;
  __adin_store_((((uint8_t*)((&var_name_tmp__129->field0)))), (((uint64_t)(uint16_t)var_name_tmp__128)), 16, 4);
}


void TIM_SetCounter(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__130, uint32_t var_name_tmp__131) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__132;    /* Address-exposed local */
  uint32_t var_name_tmp__133;    /* Address-exposed local */
  uint32_t var_name_tmp__134;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__135;

  var_name_tmp__132 = var_name_tmp__130;
  var_name_tmp__133 = var_name_tmp__131;
  var_name_tmp__134 = var_name_tmp__133;
  var_name_tmp__135 = var_name_tmp__132;
  __adin_store_((((uint8_t*)((&var_name_tmp__135->field18)))), (((uint64_t)(uint32_t)var_name_tmp__134)), 32, 4);
}


void TIM_SetAutoreload(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__136, uint32_t var_name_tmp__137) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__138;    /* Address-exposed local */
  uint32_t var_name_tmp__139;    /* Address-exposed local */
  uint32_t var_name_tmp__140;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__141;

  var_name_tmp__138 = var_name_tmp__136;
  var_name_tmp__139 = var_name_tmp__137;
  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = var_name_tmp__138;
  __adin_store_((((uint8_t*)((&var_name_tmp__141->field21)))), (((uint64_t)(uint32_t)var_name_tmp__140)), 32, 4);
}


uint32_t TIM_GetCounter(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__142) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__143;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__144;
  uint64_t var_name_load_i32_;

  var_name_tmp__143 = var_name_tmp__142;
  var_name_tmp__144 = var_name_tmp__143;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__144->field18)))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint16_t TIM_GetPrescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__145) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__146;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__147;
  uint64_t var_name_load_i16_;

  var_name_tmp__146 = var_name_tmp__145;
  var_name_tmp__147 = var_name_tmp__146;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__147->field19)))), 16, 4);
  return (((uint16_t)var_name_load_i16_));
}


void TIM_UpdateDisableConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__148, uint32_t var_name_tmp__149) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__150;    /* Address-exposed local */
  uint32_t var_name_tmp__151;    /* Address-exposed local */
  uint32_t var_name_tmp__152;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__153;
  uint16_t* var_name_tmp__154;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__155;
  uint16_t* var_name_tmp__156;
  uint64_t var_name_load_i16_3;

  var_name_tmp__150 = var_name_tmp__148;
  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__152 = var_name_tmp__151;
  if ((((var_name_tmp__152 != 0u)&1))) {
    goto var_name_tmp__157;
  } else {
    goto var_name_tmp__158;
  }

var_name_tmp__157:
  var_name_tmp__153 = var_name_tmp__150;
  var_name_tmp__154 = (&var_name_tmp__153->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__154)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__154)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2))))), 16, 4);
  goto var_name_tmp__159;

var_name_tmp__158:
  var_name_tmp__155 = var_name_tmp__150;
  var_name_tmp__156 = (&var_name_tmp__155->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__156)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__156)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65533))))), 16, 4);
  goto var_name_tmp__159;

var_name_tmp__159:
  return;
}


void TIM_UpdateRequestConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__160, uint16_t var_name_tmp__161) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__162;    /* Address-exposed local */
  uint16_t var_name_tmp__163;    /* Address-exposed local */
  uint16_t var_name_tmp__164;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__165;
  uint16_t* var_name_tmp__166;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__167;
  uint16_t* var_name_tmp__168;
  uint64_t var_name_load_i16_3;

  var_name_tmp__162 = var_name_tmp__160;
  var_name_tmp__163 = var_name_tmp__161;
  var_name_tmp__164 = var_name_tmp__163;
  if (((((((uint32_t)(uint16_t)var_name_tmp__164)) != 0u)&1))) {
    goto var_name_tmp__169;
  } else {
    goto var_name_tmp__170;
  }

var_name_tmp__169:
  var_name_tmp__165 = var_name_tmp__162;
  var_name_tmp__166 = (&var_name_tmp__165->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__166)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__166)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4))))), 16, 4);
  goto var_name_tmp__171;

var_name_tmp__170:
  var_name_tmp__167 = var_name_tmp__162;
  var_name_tmp__168 = (&var_name_tmp__167->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__168)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__168)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65531))))), 16, 4);
  goto var_name_tmp__171;

var_name_tmp__171:
  return;
}


void TIM_ARRPreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__172, uint32_t var_name_tmp__173) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__174;    /* Address-exposed local */
  uint32_t var_name_tmp__175;    /* Address-exposed local */
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__177;
  uint16_t* var_name_tmp__178;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__179;
  uint16_t* var_name_tmp__180;
  uint64_t var_name_load_i16_3;

  var_name_tmp__174 = var_name_tmp__172;
  var_name_tmp__175 = var_name_tmp__173;
  var_name_tmp__176 = var_name_tmp__175;
  if ((((var_name_tmp__176 != 0u)&1))) {
    goto var_name_tmp__181;
  } else {
    goto var_name_tmp__182;
  }

var_name_tmp__181:
  var_name_tmp__177 = var_name_tmp__174;
  var_name_tmp__178 = (&var_name_tmp__177->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__178)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__178)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 128))))), 16, 4);
  goto var_name_tmp__183;

var_name_tmp__182:
  var_name_tmp__179 = var_name_tmp__174;
  var_name_tmp__180 = (&var_name_tmp__179->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__180)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__180)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65407))))), 16, 4);
  goto var_name_tmp__183;

var_name_tmp__183:
  return;
}


void TIM_SelectOnePulseMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__184, uint16_t var_name_tmp__185) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__186;    /* Address-exposed local */
  uint16_t var_name_tmp__187;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__188;
  uint16_t* var_name_tmp__189;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__190;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__191;
  uint16_t* var_name_tmp__192;
  uint64_t var_name_load_i16_3;

  var_name_tmp__186 = var_name_tmp__184;
  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__186;
  var_name_tmp__189 = (&var_name_tmp__188->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__189)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__189)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65527))))), 16, 4);
  var_name_tmp__190 = var_name_tmp__187;
  var_name_tmp__191 = var_name_tmp__186;
  var_name_tmp__192 = (&var_name_tmp__191->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__192)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__192)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__190))))))), 16, 4);
}


void TIM_SetClockDivision(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__193, uint16_t var_name_tmp__194) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__195;    /* Address-exposed local */
  uint16_t var_name_tmp__196;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__197;
  uint16_t* var_name_tmp__198;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__199;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__200;
  uint16_t* var_name_tmp__201;
  uint64_t var_name_load_i16_3;

  var_name_tmp__195 = var_name_tmp__193;
  var_name_tmp__196 = var_name_tmp__194;
  var_name_tmp__197 = var_name_tmp__195;
  var_name_tmp__198 = (&var_name_tmp__197->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__198)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__198)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 64767))))), 16, 4);
  var_name_tmp__199 = var_name_tmp__196;
  var_name_tmp__200 = var_name_tmp__195;
  var_name_tmp__201 = (&var_name_tmp__200->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__201)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__201)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__199))))))), 16, 4);
}


void TIM_Cmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__202, uint32_t var_name_tmp__203) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__204;    /* Address-exposed local */
  uint32_t var_name_tmp__205;    /* Address-exposed local */
  uint32_t var_name_tmp__206;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__207;
  uint16_t* var_name_tmp__208;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__209;
  uint16_t* var_name_tmp__210;
  uint64_t var_name_load_i16_3;

  var_name_tmp__204 = var_name_tmp__202;
  var_name_tmp__205 = var_name_tmp__203;
  var_name_tmp__206 = var_name_tmp__205;
  if ((((var_name_tmp__206 != 0u)&1))) {
    goto var_name_tmp__211;
  } else {
    goto var_name_tmp__212;
  }

var_name_tmp__211:
  var_name_tmp__207 = var_name_tmp__204;
  var_name_tmp__208 = (&var_name_tmp__207->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__208)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__208)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1))))), 16, 4);
  goto var_name_tmp__213;

var_name_tmp__212:
  var_name_tmp__209 = var_name_tmp__204;
  var_name_tmp__210 = (&var_name_tmp__209->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__210)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__210)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65534))))), 16, 4);
  goto var_name_tmp__213;

var_name_tmp__213:
  return;
}


void TIM_OC1Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__214, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__215) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__216;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__217;    /* Address-exposed local */
  uint16_t var_name_tmp__218;    /* Address-exposed local */
  uint16_t var_name_tmp__219;    /* Address-exposed local */
  uint16_t var_name_tmp__220;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__221;
  uint16_t* var_name_tmp__222;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__223;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__224;
  uint64_t var_name_load_i16_6;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__225;
  uint64_t var_name_load_i16_9;
  uint16_t var_name_tmp__226;
  uint16_t var_name_tmp__227;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__228;
  uint64_t var_name_load_i16_12;
  uint16_t var_name_tmp__229;
  uint16_t var_name_tmp__230;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__231;
  uint64_t var_name_load_i16_15;
  uint16_t var_name_tmp__232;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__233;
  uint64_t var_name_load_i16_18;
  uint16_t var_name_tmp__234;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__235;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__236;
  uint16_t var_name_tmp__237;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__238;
  uint64_t var_name_load_i16_21;
  uint16_t var_name_tmp__239;
  uint16_t var_name_tmp__240;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__241;
  uint64_t var_name_load_i16_24;
  uint16_t var_name_tmp__242;
  uint16_t var_name_tmp__243;
  uint16_t var_name_tmp__244;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__245;
  uint64_t var_name_load_i16_27;
  uint16_t var_name_tmp__246;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__247;
  uint64_t var_name_load_i16_30;
  uint16_t var_name_tmp__248;
  uint16_t var_name_tmp__249;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__250;
  uint16_t var_name_tmp__251;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__252;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__253;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__254;
  uint16_t var_name_tmp__255;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__256;

  var_name_tmp__216 = var_name_tmp__214;
  var_name_tmp__217 = var_name_tmp__215;
  var_name_tmp__218 = 0;
  var_name_tmp__219 = 0;
  var_name_tmp__220 = 0;
  var_name_tmp__221 = var_name_tmp__216;
  var_name_tmp__222 = (&var_name_tmp__221->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__222)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__222)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65534))))), 16, 4);
  var_name_tmp__223 = var_name_tmp__216;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__223->field16)))), 16, 4);
  var_name_tmp__219 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__224 = var_name_tmp__216;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__224->field2)))), 16, 4);
  var_name_tmp__220 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__225 = var_name_tmp__216;
  var_name_load_i16_9 = __adin_load_((((uint8_t*)((&var_name_tmp__225->field12)))), 16, 4);
  var_name_tmp__218 = (((uint16_t)var_name_load_i16_9));
  var_name_tmp__226 = var_name_tmp__218;
  var_name_tmp__218 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__226)) & 65423)));
  var_name_tmp__227 = var_name_tmp__218;
  var_name_tmp__218 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__227)) & 65532)));
  var_name_tmp__228 = var_name_tmp__217;
  var_name_load_i16_12 = __adin_load_((((uint8_t*)((&var_name_tmp__228->field0)))), 16, 4);
  var_name_tmp__229 = var_name_tmp__218;
  var_name_tmp__218 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__229)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_12)))))));
  var_name_tmp__230 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__230)) & 65533)));
  var_name_tmp__231 = var_name_tmp__217;
  var_name_load_i16_15 = __adin_load_((((uint8_t*)((&var_name_tmp__231->field4)))), 16, 4);
  var_name_tmp__232 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__232)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_15)))))));
  var_name_tmp__233 = var_name_tmp__217;
  var_name_load_i16_18 = __adin_load_((((uint8_t*)((&var_name_tmp__233->field1)))), 16, 2);
  var_name_tmp__234 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__234)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_18)))))));
  var_name_tmp__235 = var_name_tmp__216;
  if ((((var_name_tmp__235 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__257;
  } else {
    goto var_name_tmp__258;
  }

var_name_tmp__258:
  var_name_tmp__236 = var_name_tmp__216;
  if ((((var_name_tmp__236 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__257;
  } else {
    goto var_name_tmp__259;
  }

var_name_tmp__257:
  var_name_tmp__237 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__237)) & 65527)));
  var_name_tmp__238 = var_name_tmp__217;
  var_name_load_i16_21 = __adin_load_((((uint8_t*)((&var_name_tmp__238->field5)))), 16, 2);
  var_name_tmp__239 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__239)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_21)))))));
  var_name_tmp__240 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__240)) & 65531)));
  var_name_tmp__241 = var_name_tmp__217;
  var_name_load_i16_24 = __adin_load_((((uint8_t*)((&var_name_tmp__241->field2)))), 16, 4);
  var_name_tmp__242 = var_name_tmp__219;
  var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__242)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_24)))))));
  var_name_tmp__243 = var_name_tmp__220;
  var_name_tmp__220 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__243)) & 65279)));
  var_name_tmp__244 = var_name_tmp__220;
  var_name_tmp__220 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__244)) & 65023)));
  var_name_tmp__245 = var_name_tmp__217;
  var_name_load_i16_27 = __adin_load_((((uint8_t*)((&var_name_tmp__245->field6)))), 16, 4);
  var_name_tmp__246 = var_name_tmp__220;
  var_name_tmp__220 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__246)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_27)))))));
  var_name_tmp__247 = var_name_tmp__217;
  var_name_load_i16_30 = __adin_load_((((uint8_t*)((&var_name_tmp__247->field7)))), 16, 2);
  var_name_tmp__248 = var_name_tmp__220;
  var_name_tmp__220 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__248)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_30)))))));
  goto var_name_tmp__259;

var_name_tmp__259:
  var_name_tmp__249 = var_name_tmp__220;
  var_name_tmp__250 = var_name_tmp__216;
  __adin_store_((((uint8_t*)((&var_name_tmp__250->field2)))), (((uint64_t)(uint16_t)var_name_tmp__249)), 16, 4);
  var_name_tmp__251 = var_name_tmp__218;
  var_name_tmp__252 = var_name_tmp__216;
  __adin_store_((((uint8_t*)((&var_name_tmp__252->field12)))), (((uint64_t)(uint16_t)var_name_tmp__251)), 16, 4);
  var_name_tmp__253 = var_name_tmp__217;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__253->field3)))), 32, 4);
  var_name_tmp__254 = var_name_tmp__216;
  __adin_store_((((uint8_t*)((&var_name_tmp__254->field24)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__255 = var_name_tmp__219;
  var_name_tmp__256 = var_name_tmp__216;
  __adin_store_((((uint8_t*)((&var_name_tmp__256->field16)))), (((uint64_t)(uint16_t)var_name_tmp__255)), 16, 4);
}


void TIM_OC2Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__260, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__261) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__262;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__263;    /* Address-exposed local */
  uint16_t var_name_tmp__264;    /* Address-exposed local */
  uint16_t var_name_tmp__265;    /* Address-exposed local */
  uint16_t var_name_tmp__266;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__267;
  uint16_t* var_name_tmp__268;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__269;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__270;
  uint64_t var_name_load_i16_6;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__271;
  uint64_t var_name_load_i16_9;
  uint16_t var_name_tmp__272;
  uint16_t var_name_tmp__273;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__274;
  uint64_t var_name_load_i16_12;
  uint16_t var_name_tmp__275;
  uint16_t var_name_tmp__276;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__277;
  uint64_t var_name_load_i16_15;
  uint16_t var_name_tmp__278;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__279;
  uint64_t var_name_load_i16_18;
  uint16_t var_name_tmp__280;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__281;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__282;
  uint16_t var_name_tmp__283;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__284;
  uint64_t var_name_load_i16_21;
  uint16_t var_name_tmp__285;
  uint16_t var_name_tmp__286;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__287;
  uint64_t var_name_load_i16_24;
  uint16_t var_name_tmp__288;
  uint16_t var_name_tmp__289;
  uint16_t var_name_tmp__290;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__291;
  uint64_t var_name_load_i16_27;
  uint16_t var_name_tmp__292;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__293;
  uint64_t var_name_load_i16_30;
  uint16_t var_name_tmp__294;
  uint16_t var_name_tmp__295;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__296;
  uint16_t var_name_tmp__297;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__298;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__299;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__300;
  uint16_t var_name_tmp__301;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__302;

  var_name_tmp__262 = var_name_tmp__260;
  var_name_tmp__263 = var_name_tmp__261;
  var_name_tmp__264 = 0;
  var_name_tmp__265 = 0;
  var_name_tmp__266 = 0;
  var_name_tmp__267 = var_name_tmp__262;
  var_name_tmp__268 = (&var_name_tmp__267->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__268)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__268)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65519))))), 16, 4);
  var_name_tmp__269 = var_name_tmp__262;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__269->field16)))), 16, 4);
  var_name_tmp__265 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__270 = var_name_tmp__262;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__270->field2)))), 16, 4);
  var_name_tmp__266 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__271 = var_name_tmp__262;
  var_name_load_i16_9 = __adin_load_((((uint8_t*)((&var_name_tmp__271->field12)))), 16, 4);
  var_name_tmp__264 = (((uint16_t)var_name_load_i16_9));
  var_name_tmp__272 = var_name_tmp__264;
  var_name_tmp__264 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__272)) & 36863)));
  var_name_tmp__273 = var_name_tmp__264;
  var_name_tmp__264 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__273)) & 64767)));
  var_name_tmp__274 = var_name_tmp__263;
  var_name_load_i16_12 = __adin_load_((((uint8_t*)((&var_name_tmp__274->field0)))), 16, 4);
  var_name_tmp__275 = var_name_tmp__264;
  var_name_tmp__264 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__275)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_12)))) << 8))))))));
  var_name_tmp__276 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__276)) & 65503)));
  var_name_tmp__277 = var_name_tmp__263;
  var_name_load_i16_15 = __adin_load_((((uint8_t*)((&var_name_tmp__277->field4)))), 16, 4);
  var_name_tmp__278 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__278)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_15)))) << 4))))))));
  var_name_tmp__279 = var_name_tmp__263;
  var_name_load_i16_18 = __adin_load_((((uint8_t*)((&var_name_tmp__279->field1)))), 16, 2);
  var_name_tmp__280 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__280)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_18)))) << 4))))))));
  var_name_tmp__281 = var_name_tmp__262;
  if ((((var_name_tmp__281 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__303;
  } else {
    goto var_name_tmp__304;
  }

var_name_tmp__304:
  var_name_tmp__282 = var_name_tmp__262;
  if ((((var_name_tmp__282 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__303;
  } else {
    goto var_name_tmp__305;
  }

var_name_tmp__303:
  var_name_tmp__283 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__283)) & 65407)));
  var_name_tmp__284 = var_name_tmp__263;
  var_name_load_i16_21 = __adin_load_((((uint8_t*)((&var_name_tmp__284->field5)))), 16, 2);
  var_name_tmp__285 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__285)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_21)))) << 4))))))));
  var_name_tmp__286 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__286)) & 65471)));
  var_name_tmp__287 = var_name_tmp__263;
  var_name_load_i16_24 = __adin_load_((((uint8_t*)((&var_name_tmp__287->field2)))), 16, 4);
  var_name_tmp__288 = var_name_tmp__265;
  var_name_tmp__265 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__288)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_24)))) << 4))))))));
  var_name_tmp__289 = var_name_tmp__266;
  var_name_tmp__266 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__289)) & 64511)));
  var_name_tmp__290 = var_name_tmp__266;
  var_name_tmp__266 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__290)) & 63487)));
  var_name_tmp__291 = var_name_tmp__263;
  var_name_load_i16_27 = __adin_load_((((uint8_t*)((&var_name_tmp__291->field6)))), 16, 4);
  var_name_tmp__292 = var_name_tmp__266;
  var_name_tmp__266 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__292)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_27)))) << 2))))))));
  var_name_tmp__293 = var_name_tmp__263;
  var_name_load_i16_30 = __adin_load_((((uint8_t*)((&var_name_tmp__293->field7)))), 16, 2);
  var_name_tmp__294 = var_name_tmp__266;
  var_name_tmp__266 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__294)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_30)))) << 2))))))));
  goto var_name_tmp__305;

var_name_tmp__305:
  var_name_tmp__295 = var_name_tmp__266;
  var_name_tmp__296 = var_name_tmp__262;
  __adin_store_((((uint8_t*)((&var_name_tmp__296->field2)))), (((uint64_t)(uint16_t)var_name_tmp__295)), 16, 4);
  var_name_tmp__297 = var_name_tmp__264;
  var_name_tmp__298 = var_name_tmp__262;
  __adin_store_((((uint8_t*)((&var_name_tmp__298->field12)))), (((uint64_t)(uint16_t)var_name_tmp__297)), 16, 4);
  var_name_tmp__299 = var_name_tmp__263;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__299->field3)))), 32, 4);
  var_name_tmp__300 = var_name_tmp__262;
  __adin_store_((((uint8_t*)((&var_name_tmp__300->field25)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__301 = var_name_tmp__265;
  var_name_tmp__302 = var_name_tmp__262;
  __adin_store_((((uint8_t*)((&var_name_tmp__302->field16)))), (((uint64_t)(uint16_t)var_name_tmp__301)), 16, 4);
}


void TIM_OC3Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__306, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__307) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__308;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__309;    /* Address-exposed local */
  uint16_t var_name_tmp__310;    /* Address-exposed local */
  uint16_t var_name_tmp__311;    /* Address-exposed local */
  uint16_t var_name_tmp__312;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__313;
  uint16_t* var_name_tmp__314;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__315;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__316;
  uint64_t var_name_load_i16_6;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__317;
  uint64_t var_name_load_i16_9;
  uint16_t var_name_tmp__318;
  uint16_t var_name_tmp__319;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__320;
  uint64_t var_name_load_i16_12;
  uint16_t var_name_tmp__321;
  uint16_t var_name_tmp__322;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__323;
  uint64_t var_name_load_i16_15;
  uint16_t var_name_tmp__324;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__325;
  uint64_t var_name_load_i16_18;
  uint16_t var_name_tmp__326;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__327;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__328;
  uint16_t var_name_tmp__329;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__330;
  uint64_t var_name_load_i16_21;
  uint16_t var_name_tmp__331;
  uint16_t var_name_tmp__332;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__333;
  uint64_t var_name_load_i16_24;
  uint16_t var_name_tmp__334;
  uint16_t var_name_tmp__335;
  uint16_t var_name_tmp__336;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__337;
  uint64_t var_name_load_i16_27;
  uint16_t var_name_tmp__338;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__339;
  uint64_t var_name_load_i16_30;
  uint16_t var_name_tmp__340;
  uint16_t var_name_tmp__341;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__342;
  uint16_t var_name_tmp__343;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__344;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__345;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__346;
  uint16_t var_name_tmp__347;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__348;

  var_name_tmp__308 = var_name_tmp__306;
  var_name_tmp__309 = var_name_tmp__307;
  var_name_tmp__310 = 0;
  var_name_tmp__311 = 0;
  var_name_tmp__312 = 0;
  var_name_tmp__313 = var_name_tmp__308;
  var_name_tmp__314 = (&var_name_tmp__313->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__314)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__314)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65279))))), 16, 4);
  var_name_tmp__315 = var_name_tmp__308;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__315->field16)))), 16, 4);
  var_name_tmp__311 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__316 = var_name_tmp__308;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__316->field2)))), 16, 4);
  var_name_tmp__312 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__317 = var_name_tmp__308;
  var_name_load_i16_9 = __adin_load_((((uint8_t*)((&var_name_tmp__317->field14)))), 16, 4);
  var_name_tmp__310 = (((uint16_t)var_name_load_i16_9));
  var_name_tmp__318 = var_name_tmp__310;
  var_name_tmp__310 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__318)) & 65423)));
  var_name_tmp__319 = var_name_tmp__310;
  var_name_tmp__310 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__319)) & 65532)));
  var_name_tmp__320 = var_name_tmp__309;
  var_name_load_i16_12 = __adin_load_((((uint8_t*)((&var_name_tmp__320->field0)))), 16, 4);
  var_name_tmp__321 = var_name_tmp__310;
  var_name_tmp__310 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__321)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_12)))))));
  var_name_tmp__322 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__322)) & 65023)));
  var_name_tmp__323 = var_name_tmp__309;
  var_name_load_i16_15 = __adin_load_((((uint8_t*)((&var_name_tmp__323->field4)))), 16, 4);
  var_name_tmp__324 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__324)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_15)))) << 8))))))));
  var_name_tmp__325 = var_name_tmp__309;
  var_name_load_i16_18 = __adin_load_((((uint8_t*)((&var_name_tmp__325->field1)))), 16, 2);
  var_name_tmp__326 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__326)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_18)))) << 8))))))));
  var_name_tmp__327 = var_name_tmp__308;
  if ((((var_name_tmp__327 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__349;
  } else {
    goto var_name_tmp__350;
  }

var_name_tmp__350:
  var_name_tmp__328 = var_name_tmp__308;
  if ((((var_name_tmp__328 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__349;
  } else {
    goto var_name_tmp__351;
  }

var_name_tmp__349:
  var_name_tmp__329 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__329)) & 63487)));
  var_name_tmp__330 = var_name_tmp__309;
  var_name_load_i16_21 = __adin_load_((((uint8_t*)((&var_name_tmp__330->field5)))), 16, 2);
  var_name_tmp__331 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__331)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_21)))) << 8))))))));
  var_name_tmp__332 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__332)) & 64511)));
  var_name_tmp__333 = var_name_tmp__309;
  var_name_load_i16_24 = __adin_load_((((uint8_t*)((&var_name_tmp__333->field2)))), 16, 4);
  var_name_tmp__334 = var_name_tmp__311;
  var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__334)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_24)))) << 8))))))));
  var_name_tmp__335 = var_name_tmp__312;
  var_name_tmp__312 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__335)) & 61439)));
  var_name_tmp__336 = var_name_tmp__312;
  var_name_tmp__312 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__336)) & 57343)));
  var_name_tmp__337 = var_name_tmp__309;
  var_name_load_i16_27 = __adin_load_((((uint8_t*)((&var_name_tmp__337->field6)))), 16, 4);
  var_name_tmp__338 = var_name_tmp__312;
  var_name_tmp__312 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__338)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_27)))) << 4))))))));
  var_name_tmp__339 = var_name_tmp__309;
  var_name_load_i16_30 = __adin_load_((((uint8_t*)((&var_name_tmp__339->field7)))), 16, 2);
  var_name_tmp__340 = var_name_tmp__312;
  var_name_tmp__312 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__340)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_30)))) << 4))))))));
  goto var_name_tmp__351;

var_name_tmp__351:
  var_name_tmp__341 = var_name_tmp__312;
  var_name_tmp__342 = var_name_tmp__308;
  __adin_store_((((uint8_t*)((&var_name_tmp__342->field2)))), (((uint64_t)(uint16_t)var_name_tmp__341)), 16, 4);
  var_name_tmp__343 = var_name_tmp__310;
  var_name_tmp__344 = var_name_tmp__308;
  __adin_store_((((uint8_t*)((&var_name_tmp__344->field14)))), (((uint64_t)(uint16_t)var_name_tmp__343)), 16, 4);
  var_name_tmp__345 = var_name_tmp__309;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__345->field3)))), 32, 4);
  var_name_tmp__346 = var_name_tmp__308;
  __adin_store_((((uint8_t*)((&var_name_tmp__346->field26)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__347 = var_name_tmp__311;
  var_name_tmp__348 = var_name_tmp__308;
  __adin_store_((((uint8_t*)((&var_name_tmp__348->field16)))), (((uint64_t)(uint16_t)var_name_tmp__347)), 16, 4);
}


void TIM_OC4Init(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__352, struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__353) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__354;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__355;    /* Address-exposed local */
  uint16_t var_name_tmp__356;    /* Address-exposed local */
  uint16_t var_name_tmp__357;    /* Address-exposed local */
  uint16_t var_name_tmp__358;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__359;
  uint16_t* var_name_tmp__360;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__361;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__362;
  uint64_t var_name_load_i16_6;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__363;
  uint64_t var_name_load_i16_9;
  uint16_t var_name_tmp__364;
  uint16_t var_name_tmp__365;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__366;
  uint64_t var_name_load_i16_12;
  uint16_t var_name_tmp__367;
  uint16_t var_name_tmp__368;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__369;
  uint64_t var_name_load_i16_15;
  uint16_t var_name_tmp__370;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__371;
  uint64_t var_name_load_i16_18;
  uint16_t var_name_tmp__372;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__373;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__374;
  uint16_t var_name_tmp__375;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__376;
  uint64_t var_name_load_i16_21;
  uint16_t var_name_tmp__377;
  uint16_t var_name_tmp__378;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__379;
  uint16_t var_name_tmp__380;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__381;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__382;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__383;
  uint16_t var_name_tmp__384;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__385;

  var_name_tmp__354 = var_name_tmp__352;
  var_name_tmp__355 = var_name_tmp__353;
  var_name_tmp__356 = 0;
  var_name_tmp__357 = 0;
  var_name_tmp__358 = 0;
  var_name_tmp__359 = var_name_tmp__354;
  var_name_tmp__360 = (&var_name_tmp__359->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__360)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__360)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 61439))))), 16, 4);
  var_name_tmp__361 = var_name_tmp__354;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__361->field16)))), 16, 4);
  var_name_tmp__357 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__362 = var_name_tmp__354;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__362->field2)))), 16, 4);
  var_name_tmp__358 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__363 = var_name_tmp__354;
  var_name_load_i16_9 = __adin_load_((((uint8_t*)((&var_name_tmp__363->field14)))), 16, 4);
  var_name_tmp__356 = (((uint16_t)var_name_load_i16_9));
  var_name_tmp__364 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__364)) & 36863)));
  var_name_tmp__365 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__365)) & 64767)));
  var_name_tmp__366 = var_name_tmp__355;
  var_name_load_i16_12 = __adin_load_((((uint8_t*)((&var_name_tmp__366->field0)))), 16, 4);
  var_name_tmp__367 = var_name_tmp__356;
  var_name_tmp__356 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__367)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_12)))) << 8))))))));
  var_name_tmp__368 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__368)) & 57343)));
  var_name_tmp__369 = var_name_tmp__355;
  var_name_load_i16_15 = __adin_load_((((uint8_t*)((&var_name_tmp__369->field4)))), 16, 4);
  var_name_tmp__370 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__370)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_15)))) << 12))))))));
  var_name_tmp__371 = var_name_tmp__355;
  var_name_load_i16_18 = __adin_load_((((uint8_t*)((&var_name_tmp__371->field1)))), 16, 2);
  var_name_tmp__372 = var_name_tmp__357;
  var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__372)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_18)))) << 12))))))));
  var_name_tmp__373 = var_name_tmp__354;
  if ((((var_name_tmp__373 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073807360)))&1))) {
    goto var_name_tmp__386;
  } else {
    goto var_name_tmp__387;
  }

var_name_tmp__387:
  var_name_tmp__374 = var_name_tmp__354;
  if ((((var_name_tmp__374 == ((struct l_struct_struct_OC_TIM_TypeDef*)(uintptr_t)UINT64_C(1073808384)))&1))) {
    goto var_name_tmp__386;
  } else {
    goto var_name_tmp__388;
  }

var_name_tmp__386:
  var_name_tmp__375 = var_name_tmp__358;
  var_name_tmp__358 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__375)) & 49151)));
  var_name_tmp__376 = var_name_tmp__355;
  var_name_load_i16_21 = __adin_load_((((uint8_t*)((&var_name_tmp__376->field6)))), 16, 4);
  var_name_tmp__377 = var_name_tmp__358;
  var_name_tmp__358 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__377)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_21)))) << 6))))))));
  goto var_name_tmp__388;

var_name_tmp__388:
  var_name_tmp__378 = var_name_tmp__358;
  var_name_tmp__379 = var_name_tmp__354;
  __adin_store_((((uint8_t*)((&var_name_tmp__379->field2)))), (((uint64_t)(uint16_t)var_name_tmp__378)), 16, 4);
  var_name_tmp__380 = var_name_tmp__356;
  var_name_tmp__381 = var_name_tmp__354;
  __adin_store_((((uint8_t*)((&var_name_tmp__381->field14)))), (((uint64_t)(uint16_t)var_name_tmp__380)), 16, 4);
  var_name_tmp__382 = var_name_tmp__355;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__382->field3)))), 32, 4);
  var_name_tmp__383 = var_name_tmp__354;
  __adin_store_((((uint8_t*)((&var_name_tmp__383->field27)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__384 = var_name_tmp__357;
  var_name_tmp__385 = var_name_tmp__354;
  __adin_store_((((uint8_t*)((&var_name_tmp__385->field16)))), (((uint64_t)(uint16_t)var_name_tmp__384)), 16, 4);
}


void TIM_OCStructInit(struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__389) {
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__390;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__391;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__392;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__393;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__394;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__395;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__396;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__397;
  struct l_struct_struct_OC_TIM_OCInitTypeDef* var_name_tmp__398;

  var_name_tmp__390 = var_name_tmp__389;
  var_name_tmp__391 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__391->field0)))), UINT64_C(0), 16, 4);
  var_name_tmp__392 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__392->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__393 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__393->field2)))), UINT64_C(0), 16, 4);
  var_name_tmp__394 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__394->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__395 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__395->field4)))), UINT64_C(0), 16, 4);
  var_name_tmp__396 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__396->field5)))), UINT64_C(0), 16, 2);
  var_name_tmp__397 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__397->field6)))), UINT64_C(0), 16, 4);
  var_name_tmp__398 = var_name_tmp__390;
  __adin_store_((((uint8_t*)((&var_name_tmp__398->field7)))), UINT64_C(0), 16, 2);
}


void TIM_SelectOCxM(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__399, uint16_t var_name_tmp__400, uint16_t var_name_tmp__401) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__402;    /* Address-exposed local */
  uint16_t var_name_tmp__403;    /* Address-exposed local */
  uint16_t var_name_tmp__404;    /* Address-exposed local */
  uint32_t var_name_tmp__405;    /* Address-exposed local */
  uint16_t var_name_tmp__406;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__407;
  uint32_t var_name_tmp__408;
  uint16_t var_name_tmp__409;
  uint16_t var_name_tmp__410;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__411;
  uint16_t* var_name_tmp__412;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__413;
  uint16_t var_name_tmp__414;
  uint16_t var_name_tmp__415;
  uint32_t var_name_tmp__416;
  uint32_t var_name_tmp__417;
  uint32_t* var_name_tmp__418;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__419;
  uint32_t var_name_tmp__420;
  uint32_t* var_name_tmp__421;
  uint64_t var_name_load_i32_4;
  uint16_t var_name_tmp__422;
  uint32_t var_name_tmp__423;
  uint32_t var_name_tmp__424;
  uint32_t* var_name_tmp__425;
  uint64_t var_name_load_i32_9;
  uint16_t var_name_tmp__426;
  uint32_t var_name_tmp__427;
  uint32_t* var_name_tmp__428;
  uint64_t var_name_load_i32_14;

  var_name_tmp__402 = var_name_tmp__399;
  var_name_tmp__403 = var_name_tmp__400;
  var_name_tmp__404 = var_name_tmp__401;
  var_name_tmp__405 = 0;
  var_name_tmp__406 = 0;
  var_name_tmp__407 = var_name_tmp__402;
  var_name_tmp__405 = (((uint32_t)(uintptr_t)var_name_tmp__407));
  var_name_tmp__408 = var_name_tmp__405;
  var_name_tmp__405 = (llvm_add_u32(var_name_tmp__408, 24));
  var_name_tmp__409 = var_name_tmp__403;
  var_name_tmp__406 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__409)))));
  var_name_tmp__410 = var_name_tmp__406;
  var_name_tmp__411 = var_name_tmp__402;
  var_name_tmp__412 = (&var_name_tmp__411->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__412)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__412)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__410))))))))))))), 16, 4);
  var_name_tmp__413 = var_name_tmp__403;
  if (((((((uint32_t)(uint16_t)var_name_tmp__413)) == 0u)&1))) {
    goto var_name_tmp__429;
  } else {
    goto var_name_tmp__430;
  }

var_name_tmp__430:
  var_name_tmp__414 = var_name_tmp__403;
  if (((((((uint32_t)(uint16_t)var_name_tmp__414)) == 8u)&1))) {
    goto var_name_tmp__429;
  } else {
    goto var_name_tmp__431;
  }

var_name_tmp__429:
  var_name_tmp__415 = var_name_tmp__403;
  var_name_tmp__416 = var_name_tmp__405;
  var_name_tmp__405 = (llvm_add_u32(var_name_tmp__416, (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__415)), 1))));
  var_name_tmp__417 = var_name_tmp__405;
  var_name_tmp__418 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__417)));
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__418)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__418)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & 65423))), 32, 4);
  var_name_tmp__419 = var_name_tmp__404;
  var_name_tmp__420 = var_name_tmp__405;
  var_name_tmp__421 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__420)));
  var_name_load_i32_4 = __adin_load_((((uint8_t*)var_name_tmp__421)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__421)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | (((uint32_t)(uint16_t)var_name_tmp__419))))), 32, 4);
  goto var_name_tmp__432;

var_name_tmp__431:
  var_name_tmp__422 = var_name_tmp__403;
  var_name_tmp__423 = var_name_tmp__405;
  var_name_tmp__405 = (llvm_add_u32(var_name_tmp__423, (llvm_ashr_u32((((uint32_t)(uint16_t)(((uint16_t)(llvm_sub_u32((((uint32_t)(uint16_t)var_name_tmp__422)), 4)))))), 1))));
  var_name_tmp__424 = var_name_tmp__405;
  var_name_tmp__425 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__424)));
  var_name_load_i32_9 = __adin_load_((((uint8_t*)var_name_tmp__425)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__425)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_9)) & 36863))), 32, 4);
  var_name_tmp__426 = var_name_tmp__404;
  var_name_tmp__427 = var_name_tmp__405;
  var_name_tmp__428 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__427)));
  var_name_load_i32_14 = __adin_load_((((uint8_t*)var_name_tmp__428)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__428)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_14)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__426)) << 8)))))))), 32, 4);
  goto var_name_tmp__432;

var_name_tmp__432:
  return;
}


void TIM_SetCompare1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__433, uint32_t var_name_tmp__434) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__435;    /* Address-exposed local */
  uint32_t var_name_tmp__436;    /* Address-exposed local */
  uint32_t var_name_tmp__437;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__438;

  var_name_tmp__435 = var_name_tmp__433;
  var_name_tmp__436 = var_name_tmp__434;
  var_name_tmp__437 = var_name_tmp__436;
  var_name_tmp__438 = var_name_tmp__435;
  __adin_store_((((uint8_t*)((&var_name_tmp__438->field24)))), (((uint64_t)(uint32_t)var_name_tmp__437)), 32, 4);
}


void TIM_SetCompare2(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__439, uint32_t var_name_tmp__440) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__441;    /* Address-exposed local */
  uint32_t var_name_tmp__442;    /* Address-exposed local */
  uint32_t var_name_tmp__443;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__444;

  var_name_tmp__441 = var_name_tmp__439;
  var_name_tmp__442 = var_name_tmp__440;
  var_name_tmp__443 = var_name_tmp__442;
  var_name_tmp__444 = var_name_tmp__441;
  __adin_store_((((uint8_t*)((&var_name_tmp__444->field25)))), (((uint64_t)(uint32_t)var_name_tmp__443)), 32, 4);
}


void TIM_SetCompare3(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__445, uint32_t var_name_tmp__446) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__447;    /* Address-exposed local */
  uint32_t var_name_tmp__448;    /* Address-exposed local */
  uint32_t var_name_tmp__449;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__450;

  var_name_tmp__447 = var_name_tmp__445;
  var_name_tmp__448 = var_name_tmp__446;
  var_name_tmp__449 = var_name_tmp__448;
  var_name_tmp__450 = var_name_tmp__447;
  __adin_store_((((uint8_t*)((&var_name_tmp__450->field26)))), (((uint64_t)(uint32_t)var_name_tmp__449)), 32, 4);
}


void TIM_SetCompare4(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__451, uint32_t var_name_tmp__452) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__453;    /* Address-exposed local */
  uint32_t var_name_tmp__454;    /* Address-exposed local */
  uint32_t var_name_tmp__455;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__456;

  var_name_tmp__453 = var_name_tmp__451;
  var_name_tmp__454 = var_name_tmp__452;
  var_name_tmp__455 = var_name_tmp__454;
  var_name_tmp__456 = var_name_tmp__453;
  __adin_store_((((uint8_t*)((&var_name_tmp__456->field27)))), (((uint64_t)(uint32_t)var_name_tmp__455)), 32, 4);
}


void TIM_ForcedOC1Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__457, uint16_t var_name_tmp__458) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__459;    /* Address-exposed local */
  uint16_t var_name_tmp__460;    /* Address-exposed local */
  uint16_t var_name_tmp__461;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__462;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__463;
  uint16_t var_name_tmp__464;
  uint16_t var_name_tmp__465;
  uint16_t var_name_tmp__466;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__467;

  var_name_tmp__459 = var_name_tmp__457;
  var_name_tmp__460 = var_name_tmp__458;
  var_name_tmp__461 = 0;
  var_name_tmp__462 = var_name_tmp__459;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__462->field12)))), 16, 4);
  var_name_tmp__461 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__463 = var_name_tmp__461;
  var_name_tmp__461 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__463)) & 65423)));
  var_name_tmp__464 = var_name_tmp__460;
  var_name_tmp__465 = var_name_tmp__461;
  var_name_tmp__461 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__465)) | (((uint32_t)(uint16_t)var_name_tmp__464)))));
  var_name_tmp__466 = var_name_tmp__461;
  var_name_tmp__467 = var_name_tmp__459;
  __adin_store_((((uint8_t*)((&var_name_tmp__467->field12)))), (((uint64_t)(uint16_t)var_name_tmp__466)), 16, 4);
}


void TIM_ForcedOC2Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__468, uint16_t var_name_tmp__469) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__470;    /* Address-exposed local */
  uint16_t var_name_tmp__471;    /* Address-exposed local */
  uint16_t var_name_tmp__472;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__473;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__474;
  uint16_t var_name_tmp__475;
  uint16_t var_name_tmp__476;
  uint16_t var_name_tmp__477;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__478;

  var_name_tmp__470 = var_name_tmp__468;
  var_name_tmp__471 = var_name_tmp__469;
  var_name_tmp__472 = 0;
  var_name_tmp__473 = var_name_tmp__470;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__473->field12)))), 16, 4);
  var_name_tmp__472 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__474 = var_name_tmp__472;
  var_name_tmp__472 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__474)) & 36863)));
  var_name_tmp__475 = var_name_tmp__471;
  var_name_tmp__476 = var_name_tmp__472;
  var_name_tmp__472 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__476)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__475)) << 8))))))));
  var_name_tmp__477 = var_name_tmp__472;
  var_name_tmp__478 = var_name_tmp__470;
  __adin_store_((((uint8_t*)((&var_name_tmp__478->field12)))), (((uint64_t)(uint16_t)var_name_tmp__477)), 16, 4);
}


void TIM_ForcedOC3Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__479, uint16_t var_name_tmp__480) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__481;    /* Address-exposed local */
  uint16_t var_name_tmp__482;    /* Address-exposed local */
  uint16_t var_name_tmp__483;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__484;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__485;
  uint16_t var_name_tmp__486;
  uint16_t var_name_tmp__487;
  uint16_t var_name_tmp__488;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__489;

  var_name_tmp__481 = var_name_tmp__479;
  var_name_tmp__482 = var_name_tmp__480;
  var_name_tmp__483 = 0;
  var_name_tmp__484 = var_name_tmp__481;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__484->field14)))), 16, 4);
  var_name_tmp__483 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__485 = var_name_tmp__483;
  var_name_tmp__483 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__485)) & 65423)));
  var_name_tmp__486 = var_name_tmp__482;
  var_name_tmp__487 = var_name_tmp__483;
  var_name_tmp__483 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__487)) | (((uint32_t)(uint16_t)var_name_tmp__486)))));
  var_name_tmp__488 = var_name_tmp__483;
  var_name_tmp__489 = var_name_tmp__481;
  __adin_store_((((uint8_t*)((&var_name_tmp__489->field14)))), (((uint64_t)(uint16_t)var_name_tmp__488)), 16, 4);
}


void TIM_ForcedOC4Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__490, uint16_t var_name_tmp__491) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__492;    /* Address-exposed local */
  uint16_t var_name_tmp__493;    /* Address-exposed local */
  uint16_t var_name_tmp__494;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__495;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__496;
  uint16_t var_name_tmp__497;
  uint16_t var_name_tmp__498;
  uint16_t var_name_tmp__499;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__500;

  var_name_tmp__492 = var_name_tmp__490;
  var_name_tmp__493 = var_name_tmp__491;
  var_name_tmp__494 = 0;
  var_name_tmp__495 = var_name_tmp__492;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__495->field14)))), 16, 4);
  var_name_tmp__494 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__496 = var_name_tmp__494;
  var_name_tmp__494 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__496)) & 36863)));
  var_name_tmp__497 = var_name_tmp__493;
  var_name_tmp__498 = var_name_tmp__494;
  var_name_tmp__494 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__498)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__497)) << 8))))))));
  var_name_tmp__499 = var_name_tmp__494;
  var_name_tmp__500 = var_name_tmp__492;
  __adin_store_((((uint8_t*)((&var_name_tmp__500->field14)))), (((uint64_t)(uint16_t)var_name_tmp__499)), 16, 4);
}


void TIM_OC1PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__501, uint16_t var_name_tmp__502) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__503;    /* Address-exposed local */
  uint16_t var_name_tmp__504;    /* Address-exposed local */
  uint16_t var_name_tmp__505;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__506;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__507;
  uint16_t var_name_tmp__508;
  uint16_t var_name_tmp__509;
  uint16_t var_name_tmp__510;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__511;

  var_name_tmp__503 = var_name_tmp__501;
  var_name_tmp__504 = var_name_tmp__502;
  var_name_tmp__505 = 0;
  var_name_tmp__506 = var_name_tmp__503;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__506->field12)))), 16, 4);
  var_name_tmp__505 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__507 = var_name_tmp__505;
  var_name_tmp__505 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__507)) & 65527)));
  var_name_tmp__508 = var_name_tmp__504;
  var_name_tmp__509 = var_name_tmp__505;
  var_name_tmp__505 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__509)) | (((uint32_t)(uint16_t)var_name_tmp__508)))));
  var_name_tmp__510 = var_name_tmp__505;
  var_name_tmp__511 = var_name_tmp__503;
  __adin_store_((((uint8_t*)((&var_name_tmp__511->field12)))), (((uint64_t)(uint16_t)var_name_tmp__510)), 16, 4);
}


void TIM_OC2PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__512, uint16_t var_name_tmp__513) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__514;    /* Address-exposed local */
  uint16_t var_name_tmp__515;    /* Address-exposed local */
  uint16_t var_name_tmp__516;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__517;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__518;
  uint16_t var_name_tmp__519;
  uint16_t var_name_tmp__520;
  uint16_t var_name_tmp__521;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__522;

  var_name_tmp__514 = var_name_tmp__512;
  var_name_tmp__515 = var_name_tmp__513;
  var_name_tmp__516 = 0;
  var_name_tmp__517 = var_name_tmp__514;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__517->field12)))), 16, 4);
  var_name_tmp__516 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__518 = var_name_tmp__516;
  var_name_tmp__516 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__518)) & 63487)));
  var_name_tmp__519 = var_name_tmp__515;
  var_name_tmp__520 = var_name_tmp__516;
  var_name_tmp__516 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__520)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__519)) << 8))))))));
  var_name_tmp__521 = var_name_tmp__516;
  var_name_tmp__522 = var_name_tmp__514;
  __adin_store_((((uint8_t*)((&var_name_tmp__522->field12)))), (((uint64_t)(uint16_t)var_name_tmp__521)), 16, 4);
}


void TIM_OC3PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__523, uint16_t var_name_tmp__524) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__525;    /* Address-exposed local */
  uint16_t var_name_tmp__526;    /* Address-exposed local */
  uint16_t var_name_tmp__527;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__528;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__529;
  uint16_t var_name_tmp__530;
  uint16_t var_name_tmp__531;
  uint16_t var_name_tmp__532;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__533;

  var_name_tmp__525 = var_name_tmp__523;
  var_name_tmp__526 = var_name_tmp__524;
  var_name_tmp__527 = 0;
  var_name_tmp__528 = var_name_tmp__525;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__528->field14)))), 16, 4);
  var_name_tmp__527 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__529 = var_name_tmp__527;
  var_name_tmp__527 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__529)) & 65527)));
  var_name_tmp__530 = var_name_tmp__526;
  var_name_tmp__531 = var_name_tmp__527;
  var_name_tmp__527 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__531)) | (((uint32_t)(uint16_t)var_name_tmp__530)))));
  var_name_tmp__532 = var_name_tmp__527;
  var_name_tmp__533 = var_name_tmp__525;
  __adin_store_((((uint8_t*)((&var_name_tmp__533->field14)))), (((uint64_t)(uint16_t)var_name_tmp__532)), 16, 4);
}


void TIM_OC4PreloadConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__534, uint16_t var_name_tmp__535) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__536;    /* Address-exposed local */
  uint16_t var_name_tmp__537;    /* Address-exposed local */
  uint16_t var_name_tmp__538;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__539;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__540;
  uint16_t var_name_tmp__541;
  uint16_t var_name_tmp__542;
  uint16_t var_name_tmp__543;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__544;

  var_name_tmp__536 = var_name_tmp__534;
  var_name_tmp__537 = var_name_tmp__535;
  var_name_tmp__538 = 0;
  var_name_tmp__539 = var_name_tmp__536;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__539->field14)))), 16, 4);
  var_name_tmp__538 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__540 = var_name_tmp__538;
  var_name_tmp__538 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__540)) & 63487)));
  var_name_tmp__541 = var_name_tmp__537;
  var_name_tmp__542 = var_name_tmp__538;
  var_name_tmp__538 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__542)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__541)) << 8))))))));
  var_name_tmp__543 = var_name_tmp__538;
  var_name_tmp__544 = var_name_tmp__536;
  __adin_store_((((uint8_t*)((&var_name_tmp__544->field14)))), (((uint64_t)(uint16_t)var_name_tmp__543)), 16, 4);
}


void TIM_OC1FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__545, uint16_t var_name_tmp__546) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__547;    /* Address-exposed local */
  uint16_t var_name_tmp__548;    /* Address-exposed local */
  uint16_t var_name_tmp__549;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__550;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__551;
  uint16_t var_name_tmp__552;
  uint16_t var_name_tmp__553;
  uint16_t var_name_tmp__554;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__555;

  var_name_tmp__547 = var_name_tmp__545;
  var_name_tmp__548 = var_name_tmp__546;
  var_name_tmp__549 = 0;
  var_name_tmp__550 = var_name_tmp__547;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__550->field12)))), 16, 4);
  var_name_tmp__549 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__551 = var_name_tmp__549;
  var_name_tmp__549 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__551)) & 65531)));
  var_name_tmp__552 = var_name_tmp__548;
  var_name_tmp__553 = var_name_tmp__549;
  var_name_tmp__549 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__553)) | (((uint32_t)(uint16_t)var_name_tmp__552)))));
  var_name_tmp__554 = var_name_tmp__549;
  var_name_tmp__555 = var_name_tmp__547;
  __adin_store_((((uint8_t*)((&var_name_tmp__555->field12)))), (((uint64_t)(uint16_t)var_name_tmp__554)), 16, 4);
}


void TIM_OC2FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__556, uint16_t var_name_tmp__557) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__558;    /* Address-exposed local */
  uint16_t var_name_tmp__559;    /* Address-exposed local */
  uint16_t var_name_tmp__560;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__561;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__562;
  uint16_t var_name_tmp__563;
  uint16_t var_name_tmp__564;
  uint16_t var_name_tmp__565;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__566;

  var_name_tmp__558 = var_name_tmp__556;
  var_name_tmp__559 = var_name_tmp__557;
  var_name_tmp__560 = 0;
  var_name_tmp__561 = var_name_tmp__558;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__561->field12)))), 16, 4);
  var_name_tmp__560 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__562 = var_name_tmp__560;
  var_name_tmp__560 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__562)) & 64511)));
  var_name_tmp__563 = var_name_tmp__559;
  var_name_tmp__564 = var_name_tmp__560;
  var_name_tmp__560 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__564)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__563)) << 8))))))));
  var_name_tmp__565 = var_name_tmp__560;
  var_name_tmp__566 = var_name_tmp__558;
  __adin_store_((((uint8_t*)((&var_name_tmp__566->field12)))), (((uint64_t)(uint16_t)var_name_tmp__565)), 16, 4);
}


void TIM_OC3FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__567, uint16_t var_name_tmp__568) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__569;    /* Address-exposed local */
  uint16_t var_name_tmp__570;    /* Address-exposed local */
  uint16_t var_name_tmp__571;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__572;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__573;
  uint16_t var_name_tmp__574;
  uint16_t var_name_tmp__575;
  uint16_t var_name_tmp__576;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__577;

  var_name_tmp__569 = var_name_tmp__567;
  var_name_tmp__570 = var_name_tmp__568;
  var_name_tmp__571 = 0;
  var_name_tmp__572 = var_name_tmp__569;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__572->field14)))), 16, 4);
  var_name_tmp__571 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__573 = var_name_tmp__571;
  var_name_tmp__571 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__573)) & 65531)));
  var_name_tmp__574 = var_name_tmp__570;
  var_name_tmp__575 = var_name_tmp__571;
  var_name_tmp__571 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__575)) | (((uint32_t)(uint16_t)var_name_tmp__574)))));
  var_name_tmp__576 = var_name_tmp__571;
  var_name_tmp__577 = var_name_tmp__569;
  __adin_store_((((uint8_t*)((&var_name_tmp__577->field14)))), (((uint64_t)(uint16_t)var_name_tmp__576)), 16, 4);
}


void TIM_OC4FastConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__578, uint16_t var_name_tmp__579) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__580;    /* Address-exposed local */
  uint16_t var_name_tmp__581;    /* Address-exposed local */
  uint16_t var_name_tmp__582;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__583;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__584;
  uint16_t var_name_tmp__585;
  uint16_t var_name_tmp__586;
  uint16_t var_name_tmp__587;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__588;

  var_name_tmp__580 = var_name_tmp__578;
  var_name_tmp__581 = var_name_tmp__579;
  var_name_tmp__582 = 0;
  var_name_tmp__583 = var_name_tmp__580;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__583->field14)))), 16, 4);
  var_name_tmp__582 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__584 = var_name_tmp__582;
  var_name_tmp__582 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__584)) & 64511)));
  var_name_tmp__585 = var_name_tmp__581;
  var_name_tmp__586 = var_name_tmp__582;
  var_name_tmp__582 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__586)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__585)) << 8))))))));
  var_name_tmp__587 = var_name_tmp__582;
  var_name_tmp__588 = var_name_tmp__580;
  __adin_store_((((uint8_t*)((&var_name_tmp__588->field14)))), (((uint64_t)(uint16_t)var_name_tmp__587)), 16, 4);
}


void TIM_ClearOC1Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__589, uint16_t var_name_tmp__590) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__591;    /* Address-exposed local */
  uint16_t var_name_tmp__592;    /* Address-exposed local */
  uint16_t var_name_tmp__593;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__594;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__595;
  uint16_t var_name_tmp__596;
  uint16_t var_name_tmp__597;
  uint16_t var_name_tmp__598;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__599;

  var_name_tmp__591 = var_name_tmp__589;
  var_name_tmp__592 = var_name_tmp__590;
  var_name_tmp__593 = 0;
  var_name_tmp__594 = var_name_tmp__591;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__594->field12)))), 16, 4);
  var_name_tmp__593 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__595 = var_name_tmp__593;
  var_name_tmp__593 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__595)) & 65407)));
  var_name_tmp__596 = var_name_tmp__592;
  var_name_tmp__597 = var_name_tmp__593;
  var_name_tmp__593 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__597)) | (((uint32_t)(uint16_t)var_name_tmp__596)))));
  var_name_tmp__598 = var_name_tmp__593;
  var_name_tmp__599 = var_name_tmp__591;
  __adin_store_((((uint8_t*)((&var_name_tmp__599->field12)))), (((uint64_t)(uint16_t)var_name_tmp__598)), 16, 4);
}


void TIM_ClearOC2Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__600, uint16_t var_name_tmp__601) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__602;    /* Address-exposed local */
  uint16_t var_name_tmp__603;    /* Address-exposed local */
  uint16_t var_name_tmp__604;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__605;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__606;
  uint16_t var_name_tmp__607;
  uint16_t var_name_tmp__608;
  uint16_t var_name_tmp__609;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__610;

  var_name_tmp__602 = var_name_tmp__600;
  var_name_tmp__603 = var_name_tmp__601;
  var_name_tmp__604 = 0;
  var_name_tmp__605 = var_name_tmp__602;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__605->field12)))), 16, 4);
  var_name_tmp__604 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__606 = var_name_tmp__604;
  var_name_tmp__604 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__606)) & 32767)));
  var_name_tmp__607 = var_name_tmp__603;
  var_name_tmp__608 = var_name_tmp__604;
  var_name_tmp__604 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__608)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__607)) << 8))))))));
  var_name_tmp__609 = var_name_tmp__604;
  var_name_tmp__610 = var_name_tmp__602;
  __adin_store_((((uint8_t*)((&var_name_tmp__610->field12)))), (((uint64_t)(uint16_t)var_name_tmp__609)), 16, 4);
}


void TIM_ClearOC3Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__611, uint16_t var_name_tmp__612) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__613;    /* Address-exposed local */
  uint16_t var_name_tmp__614;    /* Address-exposed local */
  uint16_t var_name_tmp__615;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__616;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__617;
  uint16_t var_name_tmp__618;
  uint16_t var_name_tmp__619;
  uint16_t var_name_tmp__620;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__621;

  var_name_tmp__613 = var_name_tmp__611;
  var_name_tmp__614 = var_name_tmp__612;
  var_name_tmp__615 = 0;
  var_name_tmp__616 = var_name_tmp__613;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__616->field14)))), 16, 4);
  var_name_tmp__615 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__617 = var_name_tmp__615;
  var_name_tmp__615 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__617)) & 65407)));
  var_name_tmp__618 = var_name_tmp__614;
  var_name_tmp__619 = var_name_tmp__615;
  var_name_tmp__615 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__619)) | (((uint32_t)(uint16_t)var_name_tmp__618)))));
  var_name_tmp__620 = var_name_tmp__615;
  var_name_tmp__621 = var_name_tmp__613;
  __adin_store_((((uint8_t*)((&var_name_tmp__621->field14)))), (((uint64_t)(uint16_t)var_name_tmp__620)), 16, 4);
}


void TIM_ClearOC4Ref(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__622, uint16_t var_name_tmp__623) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__624;    /* Address-exposed local */
  uint16_t var_name_tmp__625;    /* Address-exposed local */
  uint16_t var_name_tmp__626;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__627;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__628;
  uint16_t var_name_tmp__629;
  uint16_t var_name_tmp__630;
  uint16_t var_name_tmp__631;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__632;

  var_name_tmp__624 = var_name_tmp__622;
  var_name_tmp__625 = var_name_tmp__623;
  var_name_tmp__626 = 0;
  var_name_tmp__627 = var_name_tmp__624;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__627->field14)))), 16, 4);
  var_name_tmp__626 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__628 = var_name_tmp__626;
  var_name_tmp__626 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__628)) & 32767)));
  var_name_tmp__629 = var_name_tmp__625;
  var_name_tmp__630 = var_name_tmp__626;
  var_name_tmp__626 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__630)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__629)) << 8))))))));
  var_name_tmp__631 = var_name_tmp__626;
  var_name_tmp__632 = var_name_tmp__624;
  __adin_store_((((uint8_t*)((&var_name_tmp__632->field14)))), (((uint64_t)(uint16_t)var_name_tmp__631)), 16, 4);
}


void TIM_OC1PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__633, uint16_t var_name_tmp__634) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__635;    /* Address-exposed local */
  uint16_t var_name_tmp__636;    /* Address-exposed local */
  uint16_t var_name_tmp__637;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__638;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__639;
  uint16_t var_name_tmp__640;
  uint16_t var_name_tmp__641;
  uint16_t var_name_tmp__642;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__643;

  var_name_tmp__635 = var_name_tmp__633;
  var_name_tmp__636 = var_name_tmp__634;
  var_name_tmp__637 = 0;
  var_name_tmp__638 = var_name_tmp__635;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__638->field16)))), 16, 4);
  var_name_tmp__637 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__639 = var_name_tmp__637;
  var_name_tmp__637 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__639)) & 65533)));
  var_name_tmp__640 = var_name_tmp__636;
  var_name_tmp__641 = var_name_tmp__637;
  var_name_tmp__637 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__641)) | (((uint32_t)(uint16_t)var_name_tmp__640)))));
  var_name_tmp__642 = var_name_tmp__637;
  var_name_tmp__643 = var_name_tmp__635;
  __adin_store_((((uint8_t*)((&var_name_tmp__643->field16)))), (((uint64_t)(uint16_t)var_name_tmp__642)), 16, 4);
}


void TIM_OC1NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__644, uint16_t var_name_tmp__645) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__646;    /* Address-exposed local */
  uint16_t var_name_tmp__647;    /* Address-exposed local */
  uint16_t var_name_tmp__648;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__649;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__650;
  uint16_t var_name_tmp__651;
  uint16_t var_name_tmp__652;
  uint16_t var_name_tmp__653;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__654;

  var_name_tmp__646 = var_name_tmp__644;
  var_name_tmp__647 = var_name_tmp__645;
  var_name_tmp__648 = 0;
  var_name_tmp__649 = var_name_tmp__646;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__649->field16)))), 16, 4);
  var_name_tmp__648 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__650 = var_name_tmp__648;
  var_name_tmp__648 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__650)) & 65527)));
  var_name_tmp__651 = var_name_tmp__647;
  var_name_tmp__652 = var_name_tmp__648;
  var_name_tmp__648 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__652)) | (((uint32_t)(uint16_t)var_name_tmp__651)))));
  var_name_tmp__653 = var_name_tmp__648;
  var_name_tmp__654 = var_name_tmp__646;
  __adin_store_((((uint8_t*)((&var_name_tmp__654->field16)))), (((uint64_t)(uint16_t)var_name_tmp__653)), 16, 4);
}


void TIM_OC2PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__655, uint16_t var_name_tmp__656) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__657;    /* Address-exposed local */
  uint16_t var_name_tmp__658;    /* Address-exposed local */
  uint16_t var_name_tmp__659;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__660;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__661;
  uint16_t var_name_tmp__662;
  uint16_t var_name_tmp__663;
  uint16_t var_name_tmp__664;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__665;

  var_name_tmp__657 = var_name_tmp__655;
  var_name_tmp__658 = var_name_tmp__656;
  var_name_tmp__659 = 0;
  var_name_tmp__660 = var_name_tmp__657;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__660->field16)))), 16, 4);
  var_name_tmp__659 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__661 = var_name_tmp__659;
  var_name_tmp__659 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__661)) & 65503)));
  var_name_tmp__662 = var_name_tmp__658;
  var_name_tmp__663 = var_name_tmp__659;
  var_name_tmp__659 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__663)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__662)) << 4))))))));
  var_name_tmp__664 = var_name_tmp__659;
  var_name_tmp__665 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__665->field16)))), (((uint64_t)(uint16_t)var_name_tmp__664)), 16, 4);
}


void TIM_OC2NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__666, uint16_t var_name_tmp__667) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__668;    /* Address-exposed local */
  uint16_t var_name_tmp__669;    /* Address-exposed local */
  uint16_t var_name_tmp__670;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__671;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__672;
  uint16_t var_name_tmp__673;
  uint16_t var_name_tmp__674;
  uint16_t var_name_tmp__675;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__676;

  var_name_tmp__668 = var_name_tmp__666;
  var_name_tmp__669 = var_name_tmp__667;
  var_name_tmp__670 = 0;
  var_name_tmp__671 = var_name_tmp__668;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__671->field16)))), 16, 4);
  var_name_tmp__670 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__672 = var_name_tmp__670;
  var_name_tmp__670 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__672)) & 65407)));
  var_name_tmp__673 = var_name_tmp__669;
  var_name_tmp__674 = var_name_tmp__670;
  var_name_tmp__670 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__674)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__673)) << 4))))))));
  var_name_tmp__675 = var_name_tmp__670;
  var_name_tmp__676 = var_name_tmp__668;
  __adin_store_((((uint8_t*)((&var_name_tmp__676->field16)))), (((uint64_t)(uint16_t)var_name_tmp__675)), 16, 4);
}


void TIM_OC3PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__677, uint16_t var_name_tmp__678) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__679;    /* Address-exposed local */
  uint16_t var_name_tmp__680;    /* Address-exposed local */
  uint16_t var_name_tmp__681;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__682;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__683;
  uint16_t var_name_tmp__684;
  uint16_t var_name_tmp__685;
  uint16_t var_name_tmp__686;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__687;

  var_name_tmp__679 = var_name_tmp__677;
  var_name_tmp__680 = var_name_tmp__678;
  var_name_tmp__681 = 0;
  var_name_tmp__682 = var_name_tmp__679;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__682->field16)))), 16, 4);
  var_name_tmp__681 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__683 = var_name_tmp__681;
  var_name_tmp__681 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__683)) & 65023)));
  var_name_tmp__684 = var_name_tmp__680;
  var_name_tmp__685 = var_name_tmp__681;
  var_name_tmp__681 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__685)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__684)) << 8))))))));
  var_name_tmp__686 = var_name_tmp__681;
  var_name_tmp__687 = var_name_tmp__679;
  __adin_store_((((uint8_t*)((&var_name_tmp__687->field16)))), (((uint64_t)(uint16_t)var_name_tmp__686)), 16, 4);
}


void TIM_OC3NPolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__688, uint16_t var_name_tmp__689) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__690;    /* Address-exposed local */
  uint16_t var_name_tmp__691;    /* Address-exposed local */
  uint16_t var_name_tmp__692;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__693;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__694;
  uint16_t var_name_tmp__695;
  uint16_t var_name_tmp__696;
  uint16_t var_name_tmp__697;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__698;

  var_name_tmp__690 = var_name_tmp__688;
  var_name_tmp__691 = var_name_tmp__689;
  var_name_tmp__692 = 0;
  var_name_tmp__693 = var_name_tmp__690;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__693->field16)))), 16, 4);
  var_name_tmp__692 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__694 = var_name_tmp__692;
  var_name_tmp__692 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__694)) & 63487)));
  var_name_tmp__695 = var_name_tmp__691;
  var_name_tmp__696 = var_name_tmp__692;
  var_name_tmp__692 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__696)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__695)) << 8))))))));
  var_name_tmp__697 = var_name_tmp__692;
  var_name_tmp__698 = var_name_tmp__690;
  __adin_store_((((uint8_t*)((&var_name_tmp__698->field16)))), (((uint64_t)(uint16_t)var_name_tmp__697)), 16, 4);
}


void TIM_OC4PolarityConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__699, uint16_t var_name_tmp__700) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__701;    /* Address-exposed local */
  uint16_t var_name_tmp__702;    /* Address-exposed local */
  uint16_t var_name_tmp__703;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__704;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__705;
  uint16_t var_name_tmp__706;
  uint16_t var_name_tmp__707;
  uint16_t var_name_tmp__708;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__709;

  var_name_tmp__701 = var_name_tmp__699;
  var_name_tmp__702 = var_name_tmp__700;
  var_name_tmp__703 = 0;
  var_name_tmp__704 = var_name_tmp__701;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__704->field16)))), 16, 4);
  var_name_tmp__703 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__705 = var_name_tmp__703;
  var_name_tmp__703 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__705)) & 57343)));
  var_name_tmp__706 = var_name_tmp__702;
  var_name_tmp__707 = var_name_tmp__703;
  var_name_tmp__703 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__707)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__706)) << 12))))))));
  var_name_tmp__708 = var_name_tmp__703;
  var_name_tmp__709 = var_name_tmp__701;
  __adin_store_((((uint8_t*)((&var_name_tmp__709->field16)))), (((uint64_t)(uint16_t)var_name_tmp__708)), 16, 4);
}


void TIM_CCxCmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__710, uint16_t var_name_tmp__711, uint16_t var_name_tmp__712) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__713;    /* Address-exposed local */
  uint16_t var_name_tmp__714;    /* Address-exposed local */
  uint16_t var_name_tmp__715;    /* Address-exposed local */
  uint16_t var_name_tmp__716;    /* Address-exposed local */
  uint16_t var_name_tmp__717;
  uint16_t var_name_tmp__718;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__719;
  uint16_t* var_name_tmp__720;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__721;
  uint16_t var_name_tmp__722;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__723;
  uint16_t* var_name_tmp__724;
  uint64_t var_name_load_i16_3;

  var_name_tmp__713 = var_name_tmp__710;
  var_name_tmp__714 = var_name_tmp__711;
  var_name_tmp__715 = var_name_tmp__712;
  var_name_tmp__716 = 0;
  var_name_tmp__717 = var_name_tmp__714;
  var_name_tmp__716 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__717)))));
  var_name_tmp__718 = var_name_tmp__716;
  var_name_tmp__719 = var_name_tmp__713;
  var_name_tmp__720 = (&var_name_tmp__719->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__720)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__720)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__718))))))))))))), 16, 4);
  var_name_tmp__721 = var_name_tmp__715;
  var_name_tmp__722 = var_name_tmp__714;
  var_name_tmp__723 = var_name_tmp__713;
  var_name_tmp__724 = (&var_name_tmp__723->field16);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__724)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__724)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__721)) << (((uint32_t)(uint16_t)var_name_tmp__722)))))))))))), 16, 4);
}


void TIM_CCxNCmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__725, uint16_t var_name_tmp__726, uint16_t var_name_tmp__727) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__728;    /* Address-exposed local */
  uint16_t var_name_tmp__729;    /* Address-exposed local */
  uint16_t var_name_tmp__730;    /* Address-exposed local */
  uint16_t var_name_tmp__731;    /* Address-exposed local */
  uint16_t var_name_tmp__732;
  uint16_t var_name_tmp__733;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__734;
  uint16_t* var_name_tmp__735;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__736;
  uint16_t var_name_tmp__737;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__738;
  uint16_t* var_name_tmp__739;
  uint64_t var_name_load_i16_3;

  var_name_tmp__728 = var_name_tmp__725;
  var_name_tmp__729 = var_name_tmp__726;
  var_name_tmp__730 = var_name_tmp__727;
  var_name_tmp__731 = 0;
  var_name_tmp__732 = var_name_tmp__729;
  var_name_tmp__731 = (((uint16_t)(4 << (((uint32_t)(uint16_t)var_name_tmp__732)))));
  var_name_tmp__733 = var_name_tmp__731;
  var_name_tmp__734 = var_name_tmp__728;
  var_name_tmp__735 = (&var_name_tmp__734->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__735)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__735)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__733))))))))))))), 16, 4);
  var_name_tmp__736 = var_name_tmp__730;
  var_name_tmp__737 = var_name_tmp__729;
  var_name_tmp__738 = var_name_tmp__728;
  var_name_tmp__739 = (&var_name_tmp__738->field16);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__739)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__739)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__736)) << (((uint32_t)(uint16_t)var_name_tmp__737)))))))))))), 16, 4);
}


void TIM_ICInit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__740, struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__741) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__742;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__743;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__744;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__745;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__746;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__747;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__748;
  uint64_t var_name_load_i16_8;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__749;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__750;
  uint64_t var_name_load_i16_11;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__751;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__752;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__753;
  uint64_t var_name_load_i16_17;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__754;
  uint64_t var_name_load_i16_20;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__755;
  uint64_t var_name_load_i16_23;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__756;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__757;
  uint64_t var_name_load_i16_26;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__758;
  uint64_t var_name_load_i16_29;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__759;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__760;
  uint64_t var_name_load_i16_32;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__761;
  uint64_t var_name_load_i16_35;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__762;
  uint64_t var_name_load_i16_38;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__763;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__764;
  uint64_t var_name_load_i16_41;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__765;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__766;
  uint64_t var_name_load_i16_44;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__767;
  uint64_t var_name_load_i16_47;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__768;
  uint64_t var_name_load_i16_50;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__769;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__770;
  uint64_t var_name_load_i16_53;

  var_name_tmp__742 = var_name_tmp__740;
  var_name_tmp__743 = var_name_tmp__741;
  var_name_tmp__744 = var_name_tmp__743;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__744->field0)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) == 0u)&1))) {
    goto var_name_tmp__771;
  } else {
    goto var_name_tmp__772;
  }

var_name_tmp__771:
  var_name_tmp__745 = var_name_tmp__742;
  var_name_tmp__746 = var_name_tmp__743;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__746->field1)))), 16, 2);
  var_name_tmp__747 = var_name_tmp__743;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__747->field2)))), 16, 2);
  var_name_tmp__748 = var_name_tmp__743;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__748->field4)))), 16, 2);
  TI1_Config(var_name_tmp__745, (((uint16_t)var_name_load_i16_2)), (((uint16_t)var_name_load_i16_5)), (((uint16_t)var_name_load_i16_8)));
  var_name_tmp__749 = var_name_tmp__742;
  var_name_tmp__750 = var_name_tmp__743;
  var_name_load_i16_11 = __adin_load_((((uint8_t*)((&var_name_tmp__750->field3)))), 16, 2);
  TIM_SetIC1Prescaler(var_name_tmp__749, (((uint16_t)var_name_load_i16_11)));
  goto var_name_tmp__773;

var_name_tmp__772:
  var_name_tmp__751 = var_name_tmp__743;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&var_name_tmp__751->field0)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_14)))) == 4u)&1))) {
    goto var_name_tmp__774;
  } else {
    goto var_name_tmp__775;
  }

var_name_tmp__774:
  var_name_tmp__752 = var_name_tmp__742;
  var_name_tmp__753 = var_name_tmp__743;
  var_name_load_i16_17 = __adin_load_((((uint8_t*)((&var_name_tmp__753->field1)))), 16, 2);
  var_name_tmp__754 = var_name_tmp__743;
  var_name_load_i16_20 = __adin_load_((((uint8_t*)((&var_name_tmp__754->field2)))), 16, 2);
  var_name_tmp__755 = var_name_tmp__743;
  var_name_load_i16_23 = __adin_load_((((uint8_t*)((&var_name_tmp__755->field4)))), 16, 2);
  TI2_Config(var_name_tmp__752, (((uint16_t)var_name_load_i16_17)), (((uint16_t)var_name_load_i16_20)), (((uint16_t)var_name_load_i16_23)));
  var_name_tmp__756 = var_name_tmp__742;
  var_name_tmp__757 = var_name_tmp__743;
  var_name_load_i16_26 = __adin_load_((((uint8_t*)((&var_name_tmp__757->field3)))), 16, 2);
  TIM_SetIC2Prescaler(var_name_tmp__756, (((uint16_t)var_name_load_i16_26)));
  goto var_name_tmp__776;

var_name_tmp__775:
  var_name_tmp__758 = var_name_tmp__743;
  var_name_load_i16_29 = __adin_load_((((uint8_t*)((&var_name_tmp__758->field0)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_29)))) == 8u)&1))) {
    goto var_name_tmp__777;
  } else {
    goto var_name_tmp__778;
  }

var_name_tmp__777:
  var_name_tmp__759 = var_name_tmp__742;
  var_name_tmp__760 = var_name_tmp__743;
  var_name_load_i16_32 = __adin_load_((((uint8_t*)((&var_name_tmp__760->field1)))), 16, 2);
  var_name_tmp__761 = var_name_tmp__743;
  var_name_load_i16_35 = __adin_load_((((uint8_t*)((&var_name_tmp__761->field2)))), 16, 2);
  var_name_tmp__762 = var_name_tmp__743;
  var_name_load_i16_38 = __adin_load_((((uint8_t*)((&var_name_tmp__762->field4)))), 16, 2);
  TI3_Config(var_name_tmp__759, (((uint16_t)var_name_load_i16_32)), (((uint16_t)var_name_load_i16_35)), (((uint16_t)var_name_load_i16_38)));
  var_name_tmp__763 = var_name_tmp__742;
  var_name_tmp__764 = var_name_tmp__743;
  var_name_load_i16_41 = __adin_load_((((uint8_t*)((&var_name_tmp__764->field3)))), 16, 2);
  TIM_SetIC3Prescaler(var_name_tmp__763, (((uint16_t)var_name_load_i16_41)));
  goto var_name_tmp__779;

var_name_tmp__778:
  var_name_tmp__765 = var_name_tmp__742;
  var_name_tmp__766 = var_name_tmp__743;
  var_name_load_i16_44 = __adin_load_((((uint8_t*)((&var_name_tmp__766->field1)))), 16, 2);
  var_name_tmp__767 = var_name_tmp__743;
  var_name_load_i16_47 = __adin_load_((((uint8_t*)((&var_name_tmp__767->field2)))), 16, 2);
  var_name_tmp__768 = var_name_tmp__743;
  var_name_load_i16_50 = __adin_load_((((uint8_t*)((&var_name_tmp__768->field4)))), 16, 2);
  TI4_Config(var_name_tmp__765, (((uint16_t)var_name_load_i16_44)), (((uint16_t)var_name_load_i16_47)), (((uint16_t)var_name_load_i16_50)));
  var_name_tmp__769 = var_name_tmp__742;
  var_name_tmp__770 = var_name_tmp__743;
  var_name_load_i16_53 = __adin_load_((((uint8_t*)((&var_name_tmp__770->field3)))), 16, 2);
  TIM_SetIC4Prescaler(var_name_tmp__769, (((uint16_t)var_name_load_i16_53)));
  goto var_name_tmp__779;

var_name_tmp__779:
  goto var_name_tmp__776;

var_name_tmp__776:
  goto var_name_tmp__773;

var_name_tmp__773:
  return;
}


static void TI1_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__780, uint16_t var_name_tmp__781, uint16_t var_name_tmp__782, uint16_t var_name_tmp__783) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__784;    /* Address-exposed local */
  uint16_t var_name_tmp__785;    /* Address-exposed local */
  uint16_t var_name_tmp__786;    /* Address-exposed local */
  uint16_t var_name_tmp__787;    /* Address-exposed local */
  uint16_t var_name_tmp__788;    /* Address-exposed local */
  uint16_t var_name_tmp__789;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__790;
  uint16_t* var_name_tmp__791;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__792;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__793;
  uint64_t var_name_load_i16_6;
  uint16_t var_name_tmp__794;
  uint16_t var_name_tmp__795;
  uint16_t var_name_tmp__796;
  uint16_t var_name_tmp__797;
  uint16_t var_name_tmp__798;
  uint16_t var_name_tmp__799;
  uint16_t var_name_tmp__800;
  uint16_t var_name_tmp__801;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__802;
  uint16_t var_name_tmp__803;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__804;

  var_name_tmp__784 = var_name_tmp__780;
  var_name_tmp__785 = var_name_tmp__781;
  var_name_tmp__786 = var_name_tmp__782;
  var_name_tmp__787 = var_name_tmp__783;
  var_name_tmp__788 = 0;
  var_name_tmp__789 = 0;
  var_name_tmp__790 = var_name_tmp__784;
  var_name_tmp__791 = (&var_name_tmp__790->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__791)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__791)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65534))))), 16, 4);
  var_name_tmp__792 = var_name_tmp__784;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__792->field12)))), 16, 4);
  var_name_tmp__788 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__793 = var_name_tmp__784;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__793->field16)))), 16, 4);
  var_name_tmp__789 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__794 = var_name_tmp__788;
  var_name_tmp__788 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__794)) & 65292)));
  var_name_tmp__795 = var_name_tmp__786;
  var_name_tmp__796 = var_name_tmp__787;
  var_name_tmp__797 = var_name_tmp__788;
  var_name_tmp__788 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__797)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__795)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__796)) << 4)))))))))))));
  var_name_tmp__798 = var_name_tmp__789;
  var_name_tmp__789 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__798)) & 65525)));
  var_name_tmp__799 = var_name_tmp__785;
  var_name_tmp__800 = var_name_tmp__789;
  var_name_tmp__789 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__800)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__799)) | 1))))))));
  var_name_tmp__801 = var_name_tmp__788;
  var_name_tmp__802 = var_name_tmp__784;
  __adin_store_((((uint8_t*)((&var_name_tmp__802->field12)))), (((uint64_t)(uint16_t)var_name_tmp__801)), 16, 4);
  var_name_tmp__803 = var_name_tmp__789;
  var_name_tmp__804 = var_name_tmp__784;
  __adin_store_((((uint8_t*)((&var_name_tmp__804->field16)))), (((uint64_t)(uint16_t)var_name_tmp__803)), 16, 4);
}


void TIM_SetIC1Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__805, uint16_t var_name_tmp__806) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__807;    /* Address-exposed local */
  uint16_t var_name_tmp__808;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__809;
  uint16_t* var_name_tmp__810;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__811;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__812;
  uint16_t* var_name_tmp__813;
  uint64_t var_name_load_i16_3;

  var_name_tmp__807 = var_name_tmp__805;
  var_name_tmp__808 = var_name_tmp__806;
  var_name_tmp__809 = var_name_tmp__807;
  var_name_tmp__810 = (&var_name_tmp__809->field12);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__810)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__810)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65523))))), 16, 4);
  var_name_tmp__811 = var_name_tmp__808;
  var_name_tmp__812 = var_name_tmp__807;
  var_name_tmp__813 = (&var_name_tmp__812->field12);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__813)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__813)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__811))))))), 16, 4);
}


static void TI2_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__814, uint16_t var_name_tmp__815, uint16_t var_name_tmp__816, uint16_t var_name_tmp__817) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__818;    /* Address-exposed local */
  uint16_t var_name_tmp__819;    /* Address-exposed local */
  uint16_t var_name_tmp__820;    /* Address-exposed local */
  uint16_t var_name_tmp__821;    /* Address-exposed local */
  uint16_t var_name_tmp__822;    /* Address-exposed local */
  uint16_t var_name_tmp__823;    /* Address-exposed local */
  uint16_t var_name_tmp__824;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__825;
  uint16_t* var_name_tmp__826;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__827;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__828;
  uint64_t var_name_load_i16_6;
  uint16_t var_name_tmp__829;
  uint16_t var_name_tmp__830;
  uint16_t var_name_tmp__831;
  uint16_t var_name_tmp__832;
  uint16_t var_name_tmp__833;
  uint16_t var_name_tmp__834;
  uint16_t var_name_tmp__835;
  uint16_t var_name_tmp__836;
  uint16_t var_name_tmp__837;
  uint16_t var_name_tmp__838;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__839;
  uint16_t var_name_tmp__840;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__841;

  var_name_tmp__818 = var_name_tmp__814;
  var_name_tmp__819 = var_name_tmp__815;
  var_name_tmp__820 = var_name_tmp__816;
  var_name_tmp__821 = var_name_tmp__817;
  var_name_tmp__822 = 0;
  var_name_tmp__823 = 0;
  var_name_tmp__824 = 0;
  var_name_tmp__825 = var_name_tmp__818;
  var_name_tmp__826 = (&var_name_tmp__825->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__826)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__826)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65519))))), 16, 4);
  var_name_tmp__827 = var_name_tmp__818;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__827->field12)))), 16, 4);
  var_name_tmp__822 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__828 = var_name_tmp__818;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__828->field16)))), 16, 4);
  var_name_tmp__823 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__829 = var_name_tmp__819;
  var_name_tmp__824 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__829)) << 4)));
  var_name_tmp__830 = var_name_tmp__822;
  var_name_tmp__822 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__830)) & 3327)));
  var_name_tmp__831 = var_name_tmp__821;
  var_name_tmp__832 = var_name_tmp__822;
  var_name_tmp__822 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__832)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__831)) << 12))))))));
  var_name_tmp__833 = var_name_tmp__820;
  var_name_tmp__834 = var_name_tmp__822;
  var_name_tmp__822 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__834)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__833)) << 8))))))));
  var_name_tmp__835 = var_name_tmp__823;
  var_name_tmp__823 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__835)) & 65375)));
  var_name_tmp__836 = var_name_tmp__824;
  var_name_tmp__837 = var_name_tmp__823;
  var_name_tmp__823 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__837)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__836)) | 16))))))));
  var_name_tmp__838 = var_name_tmp__822;
  var_name_tmp__839 = var_name_tmp__818;
  __adin_store_((((uint8_t*)((&var_name_tmp__839->field12)))), (((uint64_t)(uint16_t)var_name_tmp__838)), 16, 4);
  var_name_tmp__840 = var_name_tmp__823;
  var_name_tmp__841 = var_name_tmp__818;
  __adin_store_((((uint8_t*)((&var_name_tmp__841->field16)))), (((uint64_t)(uint16_t)var_name_tmp__840)), 16, 4);
}


void TIM_SetIC2Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__842, uint16_t var_name_tmp__843) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__844;    /* Address-exposed local */
  uint16_t var_name_tmp__845;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__846;
  uint16_t* var_name_tmp__847;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__848;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__849;
  uint16_t* var_name_tmp__850;
  uint64_t var_name_load_i16_3;

  var_name_tmp__844 = var_name_tmp__842;
  var_name_tmp__845 = var_name_tmp__843;
  var_name_tmp__846 = var_name_tmp__844;
  var_name_tmp__847 = (&var_name_tmp__846->field12);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__847)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__847)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 62463))))), 16, 4);
  var_name_tmp__848 = var_name_tmp__845;
  var_name_tmp__849 = var_name_tmp__844;
  var_name_tmp__850 = (&var_name_tmp__849->field12);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__850)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__850)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__848)) << 8)))))))))), 16, 4);
}


static void TI3_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__851, uint16_t var_name_tmp__852, uint16_t var_name_tmp__853, uint16_t var_name_tmp__854) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__855;    /* Address-exposed local */
  uint16_t var_name_tmp__856;    /* Address-exposed local */
  uint16_t var_name_tmp__857;    /* Address-exposed local */
  uint16_t var_name_tmp__858;    /* Address-exposed local */
  uint16_t var_name_tmp__859;    /* Address-exposed local */
  uint16_t var_name_tmp__860;    /* Address-exposed local */
  uint16_t var_name_tmp__861;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__862;
  uint16_t* var_name_tmp__863;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__864;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__865;
  uint64_t var_name_load_i16_6;
  uint16_t var_name_tmp__866;
  uint16_t var_name_tmp__867;
  uint16_t var_name_tmp__868;
  uint16_t var_name_tmp__869;
  uint16_t var_name_tmp__870;
  uint16_t var_name_tmp__871;
  uint16_t var_name_tmp__872;
  uint16_t var_name_tmp__873;
  uint16_t var_name_tmp__874;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__875;
  uint16_t var_name_tmp__876;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__877;

  var_name_tmp__855 = var_name_tmp__851;
  var_name_tmp__856 = var_name_tmp__852;
  var_name_tmp__857 = var_name_tmp__853;
  var_name_tmp__858 = var_name_tmp__854;
  var_name_tmp__859 = 0;
  var_name_tmp__860 = 0;
  var_name_tmp__861 = 0;
  var_name_tmp__862 = var_name_tmp__855;
  var_name_tmp__863 = (&var_name_tmp__862->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__863)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__863)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65279))))), 16, 4);
  var_name_tmp__864 = var_name_tmp__855;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__864->field14)))), 16, 4);
  var_name_tmp__859 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__865 = var_name_tmp__855;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__865->field16)))), 16, 4);
  var_name_tmp__860 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__866 = var_name_tmp__856;
  var_name_tmp__861 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__866)) << 8)));
  var_name_tmp__867 = var_name_tmp__859;
  var_name_tmp__859 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__867)) & 65292)));
  var_name_tmp__868 = var_name_tmp__857;
  var_name_tmp__869 = var_name_tmp__858;
  var_name_tmp__870 = var_name_tmp__859;
  var_name_tmp__859 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__870)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__868)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__869)) << 4)))))))))))));
  var_name_tmp__871 = var_name_tmp__860;
  var_name_tmp__860 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__871)) & 62975)));
  var_name_tmp__872 = var_name_tmp__861;
  var_name_tmp__873 = var_name_tmp__860;
  var_name_tmp__860 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__873)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__872)) | 256))))))));
  var_name_tmp__874 = var_name_tmp__859;
  var_name_tmp__875 = var_name_tmp__855;
  __adin_store_((((uint8_t*)((&var_name_tmp__875->field14)))), (((uint64_t)(uint16_t)var_name_tmp__874)), 16, 4);
  var_name_tmp__876 = var_name_tmp__860;
  var_name_tmp__877 = var_name_tmp__855;
  __adin_store_((((uint8_t*)((&var_name_tmp__877->field16)))), (((uint64_t)(uint16_t)var_name_tmp__876)), 16, 4);
}


void TIM_SetIC3Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__878, uint16_t var_name_tmp__879) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__880;    /* Address-exposed local */
  uint16_t var_name_tmp__881;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__882;
  uint16_t* var_name_tmp__883;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__884;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__885;
  uint16_t* var_name_tmp__886;
  uint64_t var_name_load_i16_3;

  var_name_tmp__880 = var_name_tmp__878;
  var_name_tmp__881 = var_name_tmp__879;
  var_name_tmp__882 = var_name_tmp__880;
  var_name_tmp__883 = (&var_name_tmp__882->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__883)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__883)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65523))))), 16, 4);
  var_name_tmp__884 = var_name_tmp__881;
  var_name_tmp__885 = var_name_tmp__880;
  var_name_tmp__886 = (&var_name_tmp__885->field14);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__886)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__886)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__884))))))), 16, 4);
}


static void TI4_Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__887, uint16_t var_name_tmp__888, uint16_t var_name_tmp__889, uint16_t var_name_tmp__890) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__891;    /* Address-exposed local */
  uint16_t var_name_tmp__892;    /* Address-exposed local */
  uint16_t var_name_tmp__893;    /* Address-exposed local */
  uint16_t var_name_tmp__894;    /* Address-exposed local */
  uint16_t var_name_tmp__895;    /* Address-exposed local */
  uint16_t var_name_tmp__896;    /* Address-exposed local */
  uint16_t var_name_tmp__897;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__898;
  uint16_t* var_name_tmp__899;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__900;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__901;
  uint64_t var_name_load_i16_6;
  uint16_t var_name_tmp__902;
  uint16_t var_name_tmp__903;
  uint16_t var_name_tmp__904;
  uint16_t var_name_tmp__905;
  uint16_t var_name_tmp__906;
  uint16_t var_name_tmp__907;
  uint16_t var_name_tmp__908;
  uint16_t var_name_tmp__909;
  uint16_t var_name_tmp__910;
  uint16_t var_name_tmp__911;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__912;
  uint16_t var_name_tmp__913;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__914;

  var_name_tmp__891 = var_name_tmp__887;
  var_name_tmp__892 = var_name_tmp__888;
  var_name_tmp__893 = var_name_tmp__889;
  var_name_tmp__894 = var_name_tmp__890;
  var_name_tmp__895 = 0;
  var_name_tmp__896 = 0;
  var_name_tmp__897 = 0;
  var_name_tmp__898 = var_name_tmp__891;
  var_name_tmp__899 = (&var_name_tmp__898->field16);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__899)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__899)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 61439))))), 16, 4);
  var_name_tmp__900 = var_name_tmp__891;
  var_name_load_i16_3 = __adin_load_((((uint8_t*)((&var_name_tmp__900->field14)))), 16, 4);
  var_name_tmp__895 = (((uint16_t)var_name_load_i16_3));
  var_name_tmp__901 = var_name_tmp__891;
  var_name_load_i16_6 = __adin_load_((((uint8_t*)((&var_name_tmp__901->field16)))), 16, 4);
  var_name_tmp__896 = (((uint16_t)var_name_load_i16_6));
  var_name_tmp__902 = var_name_tmp__892;
  var_name_tmp__897 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__902)) << 12)));
  var_name_tmp__903 = var_name_tmp__895;
  var_name_tmp__895 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__903)) & 3327)));
  var_name_tmp__904 = var_name_tmp__893;
  var_name_tmp__905 = var_name_tmp__895;
  var_name_tmp__895 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__905)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__904)) << 8))))))));
  var_name_tmp__906 = var_name_tmp__894;
  var_name_tmp__907 = var_name_tmp__895;
  var_name_tmp__895 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__907)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__906)) << 12))))))));
  var_name_tmp__908 = var_name_tmp__896;
  var_name_tmp__896 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__908)) & 24575)));
  var_name_tmp__909 = var_name_tmp__897;
  var_name_tmp__910 = var_name_tmp__896;
  var_name_tmp__896 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__910)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__909)) | 4096))))))));
  var_name_tmp__911 = var_name_tmp__895;
  var_name_tmp__912 = var_name_tmp__891;
  __adin_store_((((uint8_t*)((&var_name_tmp__912->field14)))), (((uint64_t)(uint16_t)var_name_tmp__911)), 16, 4);
  var_name_tmp__913 = var_name_tmp__896;
  var_name_tmp__914 = var_name_tmp__891;
  __adin_store_((((uint8_t*)((&var_name_tmp__914->field16)))), (((uint64_t)(uint16_t)var_name_tmp__913)), 16, 4);
}


void TIM_SetIC4Prescaler(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__915, uint16_t var_name_tmp__916) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__917;    /* Address-exposed local */
  uint16_t var_name_tmp__918;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__919;
  uint16_t* var_name_tmp__920;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__921;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__922;
  uint16_t* var_name_tmp__923;
  uint64_t var_name_load_i16_3;

  var_name_tmp__917 = var_name_tmp__915;
  var_name_tmp__918 = var_name_tmp__916;
  var_name_tmp__919 = var_name_tmp__917;
  var_name_tmp__920 = (&var_name_tmp__919->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__920)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__920)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 62463))))), 16, 4);
  var_name_tmp__921 = var_name_tmp__918;
  var_name_tmp__922 = var_name_tmp__917;
  var_name_tmp__923 = (&var_name_tmp__922->field14);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__923)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__923)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__921)) << 8)))))))))), 16, 4);
}


void TIM_ICStructInit(struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__924) {
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__925;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__926;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__927;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__928;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__929;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__930;

  var_name_tmp__925 = var_name_tmp__924;
  var_name_tmp__926 = var_name_tmp__925;
  __adin_store_((((uint8_t*)((&var_name_tmp__926->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__927 = var_name_tmp__925;
  __adin_store_((((uint8_t*)((&var_name_tmp__927->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__928 = var_name_tmp__925;
  __adin_store_((((uint8_t*)((&var_name_tmp__928->field2)))), UINT64_C(1), 16, 2);
  var_name_tmp__929 = var_name_tmp__925;
  __adin_store_((((uint8_t*)((&var_name_tmp__929->field3)))), UINT64_C(0), 16, 2);
  var_name_tmp__930 = var_name_tmp__925;
  __adin_store_((((uint8_t*)((&var_name_tmp__930->field4)))), UINT64_C(0), 16, 2);
}


void TIM_PWMIConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__931, struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__932) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__933;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__934;    /* Address-exposed local */
  uint16_t var_name_tmp__935;    /* Address-exposed local */
  uint16_t var_name_tmp__936;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__937;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__938;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__939;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__940;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__941;
  uint64_t var_name_load_i16_8;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__942;
  uint64_t var_name_load_i16_11;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__943;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__944;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__945;
  uint64_t var_name_load_i16_17;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__946;
  uint16_t var_name_tmp__947;
  uint16_t var_name_tmp__948;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__949;
  uint64_t var_name_load_i16_20;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__950;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__951;
  uint64_t var_name_load_i16_23;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__952;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__953;
  uint64_t var_name_load_i16_26;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__954;
  uint64_t var_name_load_i16_29;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__955;
  uint64_t var_name_load_i16_32;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__956;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__957;
  uint64_t var_name_load_i16_35;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__958;
  uint16_t var_name_tmp__959;
  uint16_t var_name_tmp__960;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__961;
  uint64_t var_name_load_i16_38;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__962;
  struct l_struct_struct_OC_TIM_ICInitTypeDef* var_name_tmp__963;
  uint64_t var_name_load_i16_41;

  var_name_tmp__933 = var_name_tmp__931;
  var_name_tmp__934 = var_name_tmp__932;
  var_name_tmp__935 = 0;
  var_name_tmp__936 = 1;
  var_name_tmp__937 = var_name_tmp__934;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__937->field1)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) == 0u)&1))) {
    goto var_name_tmp__964;
  } else {
    goto var_name_tmp__965;
  }

var_name_tmp__964:
  var_name_tmp__935 = 2;
  goto var_name_tmp__966;

var_name_tmp__965:
  var_name_tmp__935 = 0;
  goto var_name_tmp__966;

var_name_tmp__966:
  var_name_tmp__938 = var_name_tmp__934;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__938->field2)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) == 1u)&1))) {
    goto var_name_tmp__967;
  } else {
    goto var_name_tmp__968;
  }

var_name_tmp__967:
  var_name_tmp__936 = 2;
  goto var_name_tmp__969;

var_name_tmp__968:
  var_name_tmp__936 = 1;
  goto var_name_tmp__969;

var_name_tmp__969:
  var_name_tmp__939 = var_name_tmp__934;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__939->field0)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5)))) == 0u)&1))) {
    goto var_name_tmp__970;
  } else {
    goto var_name_tmp__971;
  }

var_name_tmp__970:
  var_name_tmp__940 = var_name_tmp__933;
  var_name_tmp__941 = var_name_tmp__934;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__941->field1)))), 16, 2);
  var_name_tmp__942 = var_name_tmp__934;
  var_name_load_i16_11 = __adin_load_((((uint8_t*)((&var_name_tmp__942->field2)))), 16, 2);
  var_name_tmp__943 = var_name_tmp__934;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&var_name_tmp__943->field4)))), 16, 2);
  TI1_Config(var_name_tmp__940, (((uint16_t)var_name_load_i16_8)), (((uint16_t)var_name_load_i16_11)), (((uint16_t)var_name_load_i16_14)));
  var_name_tmp__944 = var_name_tmp__933;
  var_name_tmp__945 = var_name_tmp__934;
  var_name_load_i16_17 = __adin_load_((((uint8_t*)((&var_name_tmp__945->field3)))), 16, 2);
  TIM_SetIC1Prescaler(var_name_tmp__944, (((uint16_t)var_name_load_i16_17)));
  var_name_tmp__946 = var_name_tmp__933;
  var_name_tmp__947 = var_name_tmp__935;
  var_name_tmp__948 = var_name_tmp__936;
  var_name_tmp__949 = var_name_tmp__934;
  var_name_load_i16_20 = __adin_load_((((uint8_t*)((&var_name_tmp__949->field4)))), 16, 2);
  TI2_Config(var_name_tmp__946, var_name_tmp__947, var_name_tmp__948, (((uint16_t)var_name_load_i16_20)));
  var_name_tmp__950 = var_name_tmp__933;
  var_name_tmp__951 = var_name_tmp__934;
  var_name_load_i16_23 = __adin_load_((((uint8_t*)((&var_name_tmp__951->field3)))), 16, 2);
  TIM_SetIC2Prescaler(var_name_tmp__950, (((uint16_t)var_name_load_i16_23)));
  goto var_name_tmp__972;

var_name_tmp__971:
  var_name_tmp__952 = var_name_tmp__933;
  var_name_tmp__953 = var_name_tmp__934;
  var_name_load_i16_26 = __adin_load_((((uint8_t*)((&var_name_tmp__953->field1)))), 16, 2);
  var_name_tmp__954 = var_name_tmp__934;
  var_name_load_i16_29 = __adin_load_((((uint8_t*)((&var_name_tmp__954->field2)))), 16, 2);
  var_name_tmp__955 = var_name_tmp__934;
  var_name_load_i16_32 = __adin_load_((((uint8_t*)((&var_name_tmp__955->field4)))), 16, 2);
  TI2_Config(var_name_tmp__952, (((uint16_t)var_name_load_i16_26)), (((uint16_t)var_name_load_i16_29)), (((uint16_t)var_name_load_i16_32)));
  var_name_tmp__956 = var_name_tmp__933;
  var_name_tmp__957 = var_name_tmp__934;
  var_name_load_i16_35 = __adin_load_((((uint8_t*)((&var_name_tmp__957->field3)))), 16, 2);
  TIM_SetIC2Prescaler(var_name_tmp__956, (((uint16_t)var_name_load_i16_35)));
  var_name_tmp__958 = var_name_tmp__933;
  var_name_tmp__959 = var_name_tmp__935;
  var_name_tmp__960 = var_name_tmp__936;
  var_name_tmp__961 = var_name_tmp__934;
  var_name_load_i16_38 = __adin_load_((((uint8_t*)((&var_name_tmp__961->field4)))), 16, 2);
  TI1_Config(var_name_tmp__958, var_name_tmp__959, var_name_tmp__960, (((uint16_t)var_name_load_i16_38)));
  var_name_tmp__962 = var_name_tmp__933;
  var_name_tmp__963 = var_name_tmp__934;
  var_name_load_i16_41 = __adin_load_((((uint8_t*)((&var_name_tmp__963->field3)))), 16, 2);
  TIM_SetIC1Prescaler(var_name_tmp__962, (((uint16_t)var_name_load_i16_41)));
  goto var_name_tmp__972;

var_name_tmp__972:
  return;
}


uint32_t TIM_GetCapture1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__973) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__974;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__975;
  uint64_t var_name_load_i32_;

  var_name_tmp__974 = var_name_tmp__973;
  var_name_tmp__975 = var_name_tmp__974;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__975->field24)))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint32_t TIM_GetCapture2(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__976) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__977;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__978;
  uint64_t var_name_load_i32_;

  var_name_tmp__977 = var_name_tmp__976;
  var_name_tmp__978 = var_name_tmp__977;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__978->field25)))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint32_t TIM_GetCapture3(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__979) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__980;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__981;
  uint64_t var_name_load_i32_;

  var_name_tmp__980 = var_name_tmp__979;
  var_name_tmp__981 = var_name_tmp__980;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__981->field26)))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint32_t TIM_GetCapture4(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__982) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__983;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__984;
  uint64_t var_name_load_i32_;

  var_name_tmp__983 = var_name_tmp__982;
  var_name_tmp__984 = var_name_tmp__983;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__984->field27)))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void TIM_BDTRConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__985, struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__986) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__987;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__988;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__989;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__990;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__991;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__992;
  uint64_t var_name_load_i16_8;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__993;
  uint64_t var_name_load_i16_11;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__994;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__995;
  uint64_t var_name_load_i16_17;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__996;

  var_name_tmp__987 = var_name_tmp__985;
  var_name_tmp__988 = var_name_tmp__986;
  var_name_tmp__989 = var_name_tmp__988;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__989->field0)))), 16, 2);
  var_name_tmp__990 = var_name_tmp__988;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__990->field1)))), 16, 2);
  var_name_tmp__991 = var_name_tmp__988;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__991->field2)))), 16, 2);
  var_name_tmp__992 = var_name_tmp__988;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__992->field3)))), 16, 2);
  var_name_tmp__993 = var_name_tmp__988;
  var_name_load_i16_11 = __adin_load_((((uint8_t*)((&var_name_tmp__993->field4)))), 16, 2);
  var_name_tmp__994 = var_name_tmp__988;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&var_name_tmp__994->field5)))), 16, 2);
  var_name_tmp__995 = var_name_tmp__988;
  var_name_load_i16_17 = __adin_load_((((uint8_t*)((&var_name_tmp__995->field6)))), 16, 2);
  var_name_tmp__996 = var_name_tmp__987;
  __adin_store_((((uint8_t*)((&var_name_tmp__996->field28)))), (((uint64_t)(uint16_t)(((uint16_t)(((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_11))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_14))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_17))))))))), 16, 4);
}


void TIM_BDTRStructInit(struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__997) {
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__998;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__999;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1000;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1001;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1002;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1003;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1004;
  struct l_struct_struct_OC_TIM_BDTRInitTypeDef* var_name_tmp__1005;

  var_name_tmp__998 = var_name_tmp__997;
  var_name_tmp__999 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__999->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__1000 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1000->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__1001 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1001->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__1002 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1002->field3)))), UINT64_C(0), 16, 2);
  var_name_tmp__1003 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1003->field4)))), UINT64_C(0), 16, 2);
  var_name_tmp__1004 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1004->field5)))), UINT64_C(0), 16, 2);
  var_name_tmp__1005 = var_name_tmp__998;
  __adin_store_((((uint8_t*)((&var_name_tmp__1005->field6)))), UINT64_C(0), 16, 2);
}


void TIM_CtrlPWMOutputs(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1006, uint32_t var_name_tmp__1007) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1008;    /* Address-exposed local */
  uint32_t var_name_tmp__1009;    /* Address-exposed local */
  uint32_t var_name_tmp__1010;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1011;
  uint16_t* var_name_tmp__1012;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1013;
  uint16_t* var_name_tmp__1014;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1008 = var_name_tmp__1006;
  var_name_tmp__1009 = var_name_tmp__1007;
  var_name_tmp__1010 = var_name_tmp__1009;
  if ((((var_name_tmp__1010 != 0u)&1))) {
    goto var_name_tmp__1015;
  } else {
    goto var_name_tmp__1016;
  }

var_name_tmp__1015:
  var_name_tmp__1011 = var_name_tmp__1008;
  var_name_tmp__1012 = (&var_name_tmp__1011->field28);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1012)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1012)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 32768))))), 16, 4);
  goto var_name_tmp__1017;

var_name_tmp__1016:
  var_name_tmp__1013 = var_name_tmp__1008;
  var_name_tmp__1014 = (&var_name_tmp__1013->field28);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1014)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1014)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 32767))))), 16, 4);
  goto var_name_tmp__1017;

var_name_tmp__1017:
  return;
}


void TIM_SelectCOM(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1018, uint32_t var_name_tmp__1019) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1020;    /* Address-exposed local */
  uint32_t var_name_tmp__1021;    /* Address-exposed local */
  uint32_t var_name_tmp__1022;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1023;
  uint16_t* var_name_tmp__1024;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1025;
  uint16_t* var_name_tmp__1026;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1020 = var_name_tmp__1018;
  var_name_tmp__1021 = var_name_tmp__1019;
  var_name_tmp__1022 = var_name_tmp__1021;
  if ((((var_name_tmp__1022 != 0u)&1))) {
    goto var_name_tmp__1027;
  } else {
    goto var_name_tmp__1028;
  }

var_name_tmp__1027:
  var_name_tmp__1023 = var_name_tmp__1020;
  var_name_tmp__1024 = (&var_name_tmp__1023->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1024)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1024)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4))))), 16, 4);
  goto var_name_tmp__1029;

var_name_tmp__1028:
  var_name_tmp__1025 = var_name_tmp__1020;
  var_name_tmp__1026 = (&var_name_tmp__1025->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1026)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1026)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65531))))), 16, 4);
  goto var_name_tmp__1029;

var_name_tmp__1029:
  return;
}


void TIM_CCPreloadControl(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1030, uint32_t var_name_tmp__1031) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1032;    /* Address-exposed local */
  uint32_t var_name_tmp__1033;    /* Address-exposed local */
  uint32_t var_name_tmp__1034;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1035;
  uint16_t* var_name_tmp__1036;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1037;
  uint16_t* var_name_tmp__1038;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1032 = var_name_tmp__1030;
  var_name_tmp__1033 = var_name_tmp__1031;
  var_name_tmp__1034 = var_name_tmp__1033;
  if ((((var_name_tmp__1034 != 0u)&1))) {
    goto var_name_tmp__1039;
  } else {
    goto var_name_tmp__1040;
  }

var_name_tmp__1039:
  var_name_tmp__1035 = var_name_tmp__1032;
  var_name_tmp__1036 = (&var_name_tmp__1035->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1036)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1036)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1))))), 16, 4);
  goto var_name_tmp__1041;

var_name_tmp__1040:
  var_name_tmp__1037 = var_name_tmp__1032;
  var_name_tmp__1038 = (&var_name_tmp__1037->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1038)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1038)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65534))))), 16, 4);
  goto var_name_tmp__1041;

var_name_tmp__1041:
  return;
}


void TIM_ITConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1042, uint16_t var_name_tmp__1043, uint32_t var_name_tmp__1044) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1045;    /* Address-exposed local */
  uint16_t var_name_tmp__1046;    /* Address-exposed local */
  uint32_t var_name_tmp__1047;    /* Address-exposed local */
  uint32_t var_name_tmp__1048;
  uint16_t var_name_tmp__1049;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1050;
  uint16_t* var_name_tmp__1051;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1052;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1053;
  uint16_t* var_name_tmp__1054;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1045 = var_name_tmp__1042;
  var_name_tmp__1046 = var_name_tmp__1043;
  var_name_tmp__1047 = var_name_tmp__1044;
  var_name_tmp__1048 = var_name_tmp__1047;
  if ((((var_name_tmp__1048 != 0u)&1))) {
    goto var_name_tmp__1055;
  } else {
    goto var_name_tmp__1056;
  }

var_name_tmp__1055:
  var_name_tmp__1049 = var_name_tmp__1046;
  var_name_tmp__1050 = var_name_tmp__1045;
  var_name_tmp__1051 = (&var_name_tmp__1050->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1051)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1051)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__1049))))))), 16, 4);
  goto var_name_tmp__1057;

var_name_tmp__1056:
  var_name_tmp__1052 = var_name_tmp__1046;
  var_name_tmp__1053 = var_name_tmp__1045;
  var_name_tmp__1054 = (&var_name_tmp__1053->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1054)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1054)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1052))))))))))))), 16, 4);
  goto var_name_tmp__1057;

var_name_tmp__1057:
  return;
}


void TIM_GenerateEvent(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1058, uint16_t var_name_tmp__1059) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1060;    /* Address-exposed local */
  uint16_t var_name_tmp__1061;    /* Address-exposed local */
  uint16_t var_name_tmp__1062;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1063;

  var_name_tmp__1060 = var_name_tmp__1058;
  var_name_tmp__1061 = var_name_tmp__1059;
  var_name_tmp__1062 = var_name_tmp__1061;
  var_name_tmp__1063 = var_name_tmp__1060;
  __adin_store_((((uint8_t*)((&var_name_tmp__1063->field10)))), (((uint64_t)(uint16_t)var_name_tmp__1062)), 16, 4);
}


uint32_t TIM_GetFlagStatus(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1064, uint16_t var_name_tmp__1065) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1066;    /* Address-exposed local */
  uint16_t var_name_tmp__1067;    /* Address-exposed local */
  uint32_t var_name_tmp__1068;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1069;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1070;
  uint32_t var_name_tmp__1071;

  var_name_tmp__1066 = var_name_tmp__1064;
  var_name_tmp__1067 = var_name_tmp__1065;
  var_name_tmp__1068 = 0;
  var_name_tmp__1069 = var_name_tmp__1066;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1069->field8)))), 16, 4);
  var_name_tmp__1070 = var_name_tmp__1067;
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)var_name_tmp__1070))) != 0u)&1))) {
    goto var_name_tmp__1072;
  } else {
    goto var_name_tmp__1073;
  }

var_name_tmp__1072:
  var_name_tmp__1068 = 1;
  goto var_name_tmp__1074;

var_name_tmp__1073:
  var_name_tmp__1068 = 0;
  goto var_name_tmp__1074;

var_name_tmp__1074:
  var_name_tmp__1071 = var_name_tmp__1068;
  return var_name_tmp__1071;
}


void TIM_ClearFlag(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1075, uint16_t var_name_tmp__1076) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1077;    /* Address-exposed local */
  uint16_t var_name_tmp__1078;    /* Address-exposed local */
  uint16_t var_name_tmp__1079;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1080;

  var_name_tmp__1077 = var_name_tmp__1075;
  var_name_tmp__1078 = var_name_tmp__1076;
  var_name_tmp__1079 = var_name_tmp__1078;
  var_name_tmp__1080 = var_name_tmp__1077;
  __adin_store_((((uint8_t*)((&var_name_tmp__1080->field8)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1079)))))))), 16, 4);
}


uint32_t TIM_GetITStatus(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1081, uint16_t var_name_tmp__1082) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1083;    /* Address-exposed local */
  uint16_t var_name_tmp__1084;    /* Address-exposed local */
  uint32_t var_name_tmp__1085;    /* Address-exposed local */
  uint16_t var_name_tmp__1086;    /* Address-exposed local */
  uint16_t var_name_tmp__1087;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1088;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1089;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1090;
  uint64_t var_name_load_i16_2;
  uint16_t var_name_tmp__1091;
  uint16_t var_name_tmp__1092;
  uint16_t var_name_tmp__1093;
  uint32_t var_name_tmp__1094;

  var_name_tmp__1083 = var_name_tmp__1081;
  var_name_tmp__1084 = var_name_tmp__1082;
  var_name_tmp__1085 = 0;
  var_name_tmp__1086 = 0;
  var_name_tmp__1087 = 0;
  var_name_tmp__1088 = var_name_tmp__1083;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1088->field8)))), 16, 4);
  var_name_tmp__1089 = var_name_tmp__1084;
  var_name_tmp__1086 = (((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)var_name_tmp__1089)))));
  var_name_tmp__1090 = var_name_tmp__1083;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__1090->field6)))), 16, 4);
  var_name_tmp__1091 = var_name_tmp__1084;
  var_name_tmp__1087 = (((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) & (((uint32_t)(uint16_t)var_name_tmp__1091)))));
  var_name_tmp__1092 = var_name_tmp__1086;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1092)) != 0u)&1))) {
    goto var_name_tmp__1095;
  } else {
    goto var_name_tmp__1096;
  }

var_name_tmp__1095:
  var_name_tmp__1093 = var_name_tmp__1087;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1093)) != 0u)&1))) {
    goto var_name_tmp__1097;
  } else {
    goto var_name_tmp__1096;
  }

var_name_tmp__1097:
  var_name_tmp__1085 = 1;
  goto var_name_tmp__1098;

var_name_tmp__1096:
  var_name_tmp__1085 = 0;
  goto var_name_tmp__1098;

var_name_tmp__1098:
  var_name_tmp__1094 = var_name_tmp__1085;
  return var_name_tmp__1094;
}


void TIM_ClearITPendingBit(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1099, uint16_t var_name_tmp__1100) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1101;    /* Address-exposed local */
  uint16_t var_name_tmp__1102;    /* Address-exposed local */
  uint16_t var_name_tmp__1103;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1104;

  var_name_tmp__1101 = var_name_tmp__1099;
  var_name_tmp__1102 = var_name_tmp__1100;
  var_name_tmp__1103 = var_name_tmp__1102;
  var_name_tmp__1104 = var_name_tmp__1101;
  __adin_store_((((uint8_t*)((&var_name_tmp__1104->field8)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1103)))))))), 16, 4);
}


void TIM_DMAConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1105, uint16_t var_name_tmp__1106, uint16_t var_name_tmp__1107) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1108;    /* Address-exposed local */
  uint16_t var_name_tmp__1109;    /* Address-exposed local */
  uint16_t var_name_tmp__1110;    /* Address-exposed local */
  uint16_t var_name_tmp__1111;
  uint16_t var_name_tmp__1112;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1113;

  var_name_tmp__1108 = var_name_tmp__1105;
  var_name_tmp__1109 = var_name_tmp__1106;
  var_name_tmp__1110 = var_name_tmp__1107;
  var_name_tmp__1111 = var_name_tmp__1109;
  var_name_tmp__1112 = var_name_tmp__1110;
  var_name_tmp__1113 = var_name_tmp__1108;
  __adin_store_((((uint8_t*)((&var_name_tmp__1113->field30)))), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1111)) | (((uint32_t)(uint16_t)var_name_tmp__1112))))))), 16, 4);
}


void TIM_DMACmd(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1114, uint16_t var_name_tmp__1115, uint32_t var_name_tmp__1116) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1117;    /* Address-exposed local */
  uint16_t var_name_tmp__1118;    /* Address-exposed local */
  uint32_t var_name_tmp__1119;    /* Address-exposed local */
  uint32_t var_name_tmp__1120;
  uint16_t var_name_tmp__1121;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1122;
  uint16_t* var_name_tmp__1123;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1124;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1125;
  uint16_t* var_name_tmp__1126;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1117 = var_name_tmp__1114;
  var_name_tmp__1118 = var_name_tmp__1115;
  var_name_tmp__1119 = var_name_tmp__1116;
  var_name_tmp__1120 = var_name_tmp__1119;
  if ((((var_name_tmp__1120 != 0u)&1))) {
    goto var_name_tmp__1127;
  } else {
    goto var_name_tmp__1128;
  }

var_name_tmp__1127:
  var_name_tmp__1121 = var_name_tmp__1118;
  var_name_tmp__1122 = var_name_tmp__1117;
  var_name_tmp__1123 = (&var_name_tmp__1122->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1123)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1123)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__1121))))))), 16, 4);
  goto var_name_tmp__1129;

var_name_tmp__1128:
  var_name_tmp__1124 = var_name_tmp__1118;
  var_name_tmp__1125 = var_name_tmp__1117;
  var_name_tmp__1126 = (&var_name_tmp__1125->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1126)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1126)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__1124))))))))))))), 16, 4);
  goto var_name_tmp__1129;

var_name_tmp__1129:
  return;
}


void TIM_SelectCCDMA(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1130, uint32_t var_name_tmp__1131) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1132;    /* Address-exposed local */
  uint32_t var_name_tmp__1133;    /* Address-exposed local */
  uint32_t var_name_tmp__1134;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1135;
  uint16_t* var_name_tmp__1136;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1137;
  uint16_t* var_name_tmp__1138;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1132 = var_name_tmp__1130;
  var_name_tmp__1133 = var_name_tmp__1131;
  var_name_tmp__1134 = var_name_tmp__1133;
  if ((((var_name_tmp__1134 != 0u)&1))) {
    goto var_name_tmp__1139;
  } else {
    goto var_name_tmp__1140;
  }

var_name_tmp__1139:
  var_name_tmp__1135 = var_name_tmp__1132;
  var_name_tmp__1136 = (&var_name_tmp__1135->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1136)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1136)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 8))))), 16, 4);
  goto var_name_tmp__1141;

var_name_tmp__1140:
  var_name_tmp__1137 = var_name_tmp__1132;
  var_name_tmp__1138 = (&var_name_tmp__1137->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1138)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1138)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65527))))), 16, 4);
  goto var_name_tmp__1141;

var_name_tmp__1141:
  return;
}


void TIM_InternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1142) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1143;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1144;
  uint16_t* var_name_tmp__1145;
  uint64_t var_name_load_i16_;

  var_name_tmp__1143 = var_name_tmp__1142;
  var_name_tmp__1144 = var_name_tmp__1143;
  var_name_tmp__1145 = (&var_name_tmp__1144->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1145)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1145)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65528))))), 16, 4);
}


void TIM_ITRxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1146, uint16_t var_name_tmp__1147) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1148;    /* Address-exposed local */
  uint16_t var_name_tmp__1149;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1150;
  uint16_t var_name_tmp__1151;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1152;
  uint16_t* var_name_tmp__1153;
  uint64_t var_name_load_i16_;

  var_name_tmp__1148 = var_name_tmp__1146;
  var_name_tmp__1149 = var_name_tmp__1147;
  var_name_tmp__1150 = var_name_tmp__1148;
  var_name_tmp__1151 = var_name_tmp__1149;
  TIM_SelectInputTrigger(var_name_tmp__1150, var_name_tmp__1151);
  var_name_tmp__1152 = var_name_tmp__1148;
  var_name_tmp__1153 = (&var_name_tmp__1152->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1153)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1153)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 7))))), 16, 4);
}


void TIM_SelectInputTrigger(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1154, uint16_t var_name_tmp__1155) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1156;    /* Address-exposed local */
  uint16_t var_name_tmp__1157;    /* Address-exposed local */
  uint16_t var_name_tmp__1158;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1159;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1160;
  uint16_t var_name_tmp__1161;
  uint16_t var_name_tmp__1162;
  uint16_t var_name_tmp__1163;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1164;

  var_name_tmp__1156 = var_name_tmp__1154;
  var_name_tmp__1157 = var_name_tmp__1155;
  var_name_tmp__1158 = 0;
  var_name_tmp__1159 = var_name_tmp__1156;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1159->field4)))), 16, 4);
  var_name_tmp__1158 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__1160 = var_name_tmp__1158;
  var_name_tmp__1158 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1160)) & 65423)));
  var_name_tmp__1161 = var_name_tmp__1157;
  var_name_tmp__1162 = var_name_tmp__1158;
  var_name_tmp__1158 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1162)) | (((uint32_t)(uint16_t)var_name_tmp__1161)))));
  var_name_tmp__1163 = var_name_tmp__1158;
  var_name_tmp__1164 = var_name_tmp__1156;
  __adin_store_((((uint8_t*)((&var_name_tmp__1164->field4)))), (((uint64_t)(uint16_t)var_name_tmp__1163)), 16, 4);
}


void TIM_TIxExternalClockConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1165, uint16_t var_name_tmp__1166, uint16_t var_name_tmp__1167, uint16_t var_name_tmp__1168) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1169;    /* Address-exposed local */
  uint16_t var_name_tmp__1170;    /* Address-exposed local */
  uint16_t var_name_tmp__1171;    /* Address-exposed local */
  uint16_t var_name_tmp__1172;    /* Address-exposed local */
  uint16_t var_name_tmp__1173;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1174;
  uint16_t var_name_tmp__1175;
  uint16_t var_name_tmp__1176;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1177;
  uint16_t var_name_tmp__1178;
  uint16_t var_name_tmp__1179;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1180;
  uint16_t var_name_tmp__1181;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1182;
  uint16_t* var_name_tmp__1183;
  uint64_t var_name_load_i16_;

  var_name_tmp__1169 = var_name_tmp__1165;
  var_name_tmp__1170 = var_name_tmp__1166;
  var_name_tmp__1171 = var_name_tmp__1167;
  var_name_tmp__1172 = var_name_tmp__1168;
  var_name_tmp__1173 = var_name_tmp__1170;
  if (((((((uint32_t)(uint16_t)var_name_tmp__1173)) == 96u)&1))) {
    goto var_name_tmp__1184;
  } else {
    goto var_name_tmp__1185;
  }

var_name_tmp__1184:
  var_name_tmp__1174 = var_name_tmp__1169;
  var_name_tmp__1175 = var_name_tmp__1171;
  var_name_tmp__1176 = var_name_tmp__1172;
  TI2_Config(var_name_tmp__1174, var_name_tmp__1175, 1, var_name_tmp__1176);
  goto var_name_tmp__1186;

var_name_tmp__1185:
  var_name_tmp__1177 = var_name_tmp__1169;
  var_name_tmp__1178 = var_name_tmp__1171;
  var_name_tmp__1179 = var_name_tmp__1172;
  TI1_Config(var_name_tmp__1177, var_name_tmp__1178, 1, var_name_tmp__1179);
  goto var_name_tmp__1186;

var_name_tmp__1186:
  var_name_tmp__1180 = var_name_tmp__1169;
  var_name_tmp__1181 = var_name_tmp__1170;
  TIM_SelectInputTrigger(var_name_tmp__1180, var_name_tmp__1181);
  var_name_tmp__1182 = var_name_tmp__1169;
  var_name_tmp__1183 = (&var_name_tmp__1182->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1183)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1183)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 7))))), 16, 4);
}


void TIM_ETRClockMode1Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1187, uint16_t var_name_tmp__1188, uint16_t var_name_tmp__1189, uint16_t var_name_tmp__1190) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1191;    /* Address-exposed local */
  uint16_t var_name_tmp__1192;    /* Address-exposed local */
  uint16_t var_name_tmp__1193;    /* Address-exposed local */
  uint16_t var_name_tmp__1194;    /* Address-exposed local */
  uint16_t var_name_tmp__1195;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1196;
  uint16_t var_name_tmp__1197;
  uint16_t var_name_tmp__1198;
  uint16_t var_name_tmp__1199;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1200;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1201;
  uint16_t var_name_tmp__1202;
  uint16_t var_name_tmp__1203;
  uint16_t var_name_tmp__1204;
  uint16_t var_name_tmp__1205;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1206;

  var_name_tmp__1191 = var_name_tmp__1187;
  var_name_tmp__1192 = var_name_tmp__1188;
  var_name_tmp__1193 = var_name_tmp__1189;
  var_name_tmp__1194 = var_name_tmp__1190;
  var_name_tmp__1195 = 0;
  var_name_tmp__1196 = var_name_tmp__1191;
  var_name_tmp__1197 = var_name_tmp__1192;
  var_name_tmp__1198 = var_name_tmp__1193;
  var_name_tmp__1199 = var_name_tmp__1194;
  TIM_ETRConfig(var_name_tmp__1196, var_name_tmp__1197, var_name_tmp__1198, var_name_tmp__1199);
  var_name_tmp__1200 = var_name_tmp__1191;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1200->field4)))), 16, 4);
  var_name_tmp__1195 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__1201 = var_name_tmp__1195;
  var_name_tmp__1195 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1201)) & 65528)));
  var_name_tmp__1202 = var_name_tmp__1195;
  var_name_tmp__1195 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1202)) | 7)));
  var_name_tmp__1203 = var_name_tmp__1195;
  var_name_tmp__1195 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1203)) & 65423)));
  var_name_tmp__1204 = var_name_tmp__1195;
  var_name_tmp__1195 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1204)) | 112)));
  var_name_tmp__1205 = var_name_tmp__1195;
  var_name_tmp__1206 = var_name_tmp__1191;
  __adin_store_((((uint8_t*)((&var_name_tmp__1206->field4)))), (((uint64_t)(uint16_t)var_name_tmp__1205)), 16, 4);
}


void TIM_ETRConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1207, uint16_t var_name_tmp__1208, uint16_t var_name_tmp__1209, uint16_t var_name_tmp__1210) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1211;    /* Address-exposed local */
  uint16_t var_name_tmp__1212;    /* Address-exposed local */
  uint16_t var_name_tmp__1213;    /* Address-exposed local */
  uint16_t var_name_tmp__1214;    /* Address-exposed local */
  uint16_t var_name_tmp__1215;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1216;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1217;
  uint16_t var_name_tmp__1218;
  uint16_t var_name_tmp__1219;
  uint16_t var_name_tmp__1220;
  uint16_t var_name_tmp__1221;
  uint16_t var_name_tmp__1222;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1223;

  var_name_tmp__1211 = var_name_tmp__1207;
  var_name_tmp__1212 = var_name_tmp__1208;
  var_name_tmp__1213 = var_name_tmp__1209;
  var_name_tmp__1214 = var_name_tmp__1210;
  var_name_tmp__1215 = 0;
  var_name_tmp__1216 = var_name_tmp__1211;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1216->field4)))), 16, 4);
  var_name_tmp__1215 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__1217 = var_name_tmp__1215;
  var_name_tmp__1215 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1217)) & 255)));
  var_name_tmp__1218 = var_name_tmp__1212;
  var_name_tmp__1219 = var_name_tmp__1213;
  var_name_tmp__1220 = var_name_tmp__1214;
  var_name_tmp__1221 = var_name_tmp__1215;
  var_name_tmp__1215 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1221)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1218)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1219)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1220)) << 8))))))))))))))))));
  var_name_tmp__1222 = var_name_tmp__1215;
  var_name_tmp__1223 = var_name_tmp__1211;
  __adin_store_((((uint8_t*)((&var_name_tmp__1223->field4)))), (((uint64_t)(uint16_t)var_name_tmp__1222)), 16, 4);
}


void TIM_ETRClockMode2Config(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1224, uint16_t var_name_tmp__1225, uint16_t var_name_tmp__1226, uint16_t var_name_tmp__1227) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1228;    /* Address-exposed local */
  uint16_t var_name_tmp__1229;    /* Address-exposed local */
  uint16_t var_name_tmp__1230;    /* Address-exposed local */
  uint16_t var_name_tmp__1231;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1232;
  uint16_t var_name_tmp__1233;
  uint16_t var_name_tmp__1234;
  uint16_t var_name_tmp__1235;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1236;
  uint16_t* var_name_tmp__1237;
  uint64_t var_name_load_i16_;

  var_name_tmp__1228 = var_name_tmp__1224;
  var_name_tmp__1229 = var_name_tmp__1225;
  var_name_tmp__1230 = var_name_tmp__1226;
  var_name_tmp__1231 = var_name_tmp__1227;
  var_name_tmp__1232 = var_name_tmp__1228;
  var_name_tmp__1233 = var_name_tmp__1229;
  var_name_tmp__1234 = var_name_tmp__1230;
  var_name_tmp__1235 = var_name_tmp__1231;
  TIM_ETRConfig(var_name_tmp__1232, var_name_tmp__1233, var_name_tmp__1234, var_name_tmp__1235);
  var_name_tmp__1236 = var_name_tmp__1228;
  var_name_tmp__1237 = (&var_name_tmp__1236->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1237)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1237)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16384))))), 16, 4);
}


void TIM_SelectOutputTrigger(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1238, uint16_t var_name_tmp__1239) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1240;    /* Address-exposed local */
  uint16_t var_name_tmp__1241;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1242;
  uint16_t* var_name_tmp__1243;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1244;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1245;
  uint16_t* var_name_tmp__1246;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1240 = var_name_tmp__1238;
  var_name_tmp__1241 = var_name_tmp__1239;
  var_name_tmp__1242 = var_name_tmp__1240;
  var_name_tmp__1243 = (&var_name_tmp__1242->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1243)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1243)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65423))))), 16, 4);
  var_name_tmp__1244 = var_name_tmp__1241;
  var_name_tmp__1245 = var_name_tmp__1240;
  var_name_tmp__1246 = (&var_name_tmp__1245->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1246)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1246)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__1244))))))), 16, 4);
}


void TIM_SelectSlaveMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1247, uint16_t var_name_tmp__1248) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1249;    /* Address-exposed local */
  uint16_t var_name_tmp__1250;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1251;
  uint16_t* var_name_tmp__1252;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1253;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1254;
  uint16_t* var_name_tmp__1255;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1249 = var_name_tmp__1247;
  var_name_tmp__1250 = var_name_tmp__1248;
  var_name_tmp__1251 = var_name_tmp__1249;
  var_name_tmp__1252 = (&var_name_tmp__1251->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1252)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1252)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65528))))), 16, 4);
  var_name_tmp__1253 = var_name_tmp__1250;
  var_name_tmp__1254 = var_name_tmp__1249;
  var_name_tmp__1255 = (&var_name_tmp__1254->field4);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1255)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1255)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__1253))))))), 16, 4);
}


void TIM_SelectMasterSlaveMode(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1256, uint16_t var_name_tmp__1257) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1258;    /* Address-exposed local */
  uint16_t var_name_tmp__1259;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1260;
  uint16_t* var_name_tmp__1261;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__1262;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1263;
  uint16_t* var_name_tmp__1264;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1258 = var_name_tmp__1256;
  var_name_tmp__1259 = var_name_tmp__1257;
  var_name_tmp__1260 = var_name_tmp__1258;
  var_name_tmp__1261 = (&var_name_tmp__1260->field4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1261)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1261)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65407))))), 16, 4);
  var_name_tmp__1262 = var_name_tmp__1259;
  var_name_tmp__1263 = var_name_tmp__1258;
  var_name_tmp__1264 = (&var_name_tmp__1263->field4);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1264)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1264)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__1262))))))), 16, 4);
}


void TIM_EncoderInterfaceConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1265, uint16_t var_name_tmp__1266, uint16_t var_name_tmp__1267, uint16_t var_name_tmp__1268) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1269;    /* Address-exposed local */
  uint16_t var_name_tmp__1270;    /* Address-exposed local */
  uint16_t var_name_tmp__1271;    /* Address-exposed local */
  uint16_t var_name_tmp__1272;    /* Address-exposed local */
  uint16_t var_name_tmp__1273;    /* Address-exposed local */
  uint16_t var_name_tmp__1274;    /* Address-exposed local */
  uint16_t var_name_tmp__1275;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1276;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1277;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1278;
  uint64_t var_name_load_i16_5;
  uint16_t var_name_tmp__1279;
  uint16_t var_name_tmp__1280;
  uint16_t var_name_tmp__1281;
  uint16_t var_name_tmp__1282;
  uint16_t var_name_tmp__1283;
  uint16_t var_name_tmp__1284;
  uint16_t var_name_tmp__1285;
  uint16_t var_name_tmp__1286;
  uint16_t var_name_tmp__1287;
  uint16_t var_name_tmp__1288;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1289;
  uint16_t var_name_tmp__1290;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1291;
  uint16_t var_name_tmp__1292;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1293;

  var_name_tmp__1269 = var_name_tmp__1265;
  var_name_tmp__1270 = var_name_tmp__1266;
  var_name_tmp__1271 = var_name_tmp__1267;
  var_name_tmp__1272 = var_name_tmp__1268;
  var_name_tmp__1273 = 0;
  var_name_tmp__1274 = 0;
  var_name_tmp__1275 = 0;
  var_name_tmp__1276 = var_name_tmp__1269;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1276->field4)))), 16, 4);
  var_name_tmp__1273 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__1277 = var_name_tmp__1269;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__1277->field12)))), 16, 4);
  var_name_tmp__1274 = (((uint16_t)var_name_load_i16_2));
  var_name_tmp__1278 = var_name_tmp__1269;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__1278->field16)))), 16, 4);
  var_name_tmp__1275 = (((uint16_t)var_name_load_i16_5));
  var_name_tmp__1279 = var_name_tmp__1273;
  var_name_tmp__1273 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1279)) & 65528)));
  var_name_tmp__1280 = var_name_tmp__1270;
  var_name_tmp__1281 = var_name_tmp__1273;
  var_name_tmp__1273 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1281)) | (((uint32_t)(uint16_t)var_name_tmp__1280)))));
  var_name_tmp__1282 = var_name_tmp__1274;
  var_name_tmp__1274 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1282)) & 64764)));
  var_name_tmp__1283 = var_name_tmp__1274;
  var_name_tmp__1274 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1283)) | 257)));
  var_name_tmp__1284 = var_name_tmp__1275;
  var_name_tmp__1275 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1284)) & 65501)));
  var_name_tmp__1285 = var_name_tmp__1271;
  var_name_tmp__1286 = var_name_tmp__1272;
  var_name_tmp__1287 = var_name_tmp__1275;
  var_name_tmp__1275 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1287)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1285)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__1286)) << 4)))))))))))));
  var_name_tmp__1288 = var_name_tmp__1273;
  var_name_tmp__1289 = var_name_tmp__1269;
  __adin_store_((((uint8_t*)((&var_name_tmp__1289->field4)))), (((uint64_t)(uint16_t)var_name_tmp__1288)), 16, 4);
  var_name_tmp__1290 = var_name_tmp__1274;
  var_name_tmp__1291 = var_name_tmp__1269;
  __adin_store_((((uint8_t*)((&var_name_tmp__1291->field12)))), (((uint64_t)(uint16_t)var_name_tmp__1290)), 16, 4);
  var_name_tmp__1292 = var_name_tmp__1275;
  var_name_tmp__1293 = var_name_tmp__1269;
  __adin_store_((((uint8_t*)((&var_name_tmp__1293->field16)))), (((uint64_t)(uint16_t)var_name_tmp__1292)), 16, 4);
}


void TIM_SelectHallSensor(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1294, uint32_t var_name_tmp__1295) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1296;    /* Address-exposed local */
  uint32_t var_name_tmp__1297;    /* Address-exposed local */
  uint32_t var_name_tmp__1298;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1299;
  uint16_t* var_name_tmp__1300;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1301;
  uint16_t* var_name_tmp__1302;
  uint64_t var_name_load_i16_3;

  var_name_tmp__1296 = var_name_tmp__1294;
  var_name_tmp__1297 = var_name_tmp__1295;
  var_name_tmp__1298 = var_name_tmp__1297;
  if ((((var_name_tmp__1298 != 0u)&1))) {
    goto var_name_tmp__1303;
  } else {
    goto var_name_tmp__1304;
  }

var_name_tmp__1303:
  var_name_tmp__1299 = var_name_tmp__1296;
  var_name_tmp__1300 = (&var_name_tmp__1299->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__1300)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1300)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 128))))), 16, 4);
  goto var_name_tmp__1305;

var_name_tmp__1304:
  var_name_tmp__1301 = var_name_tmp__1296;
  var_name_tmp__1302 = (&var_name_tmp__1301->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__1302)), 16, 4);
  __adin_store_((((uint8_t*)var_name_tmp__1302)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65407))))), 16, 4);
  goto var_name_tmp__1305;

var_name_tmp__1305:
  return;
}


void TIM_RemapConfig(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1306, uint16_t var_name_tmp__1307) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1308;    /* Address-exposed local */
  uint16_t var_name_tmp__1309;    /* Address-exposed local */
  uint16_t var_name_tmp__1310;
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1311;

  var_name_tmp__1308 = var_name_tmp__1306;
  var_name_tmp__1309 = var_name_tmp__1307;
  var_name_tmp__1310 = var_name_tmp__1309;
  var_name_tmp__1311 = var_name_tmp__1308;
  __adin_store_((((uint8_t*)((&var_name_tmp__1311->field34)))), (((uint64_t)(uint16_t)var_name_tmp__1310)), 16, 4);
}


uint16_t get_TIM_CR1(struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1312) {
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1313;    /* Address-exposed local */
  struct l_struct_struct_OC_TIM_TypeDef* var_name_tmp__1314;
  uint64_t var_name_load_i16_;

  var_name_tmp__1313 = var_name_tmp__1312;
  var_name_tmp__1314 = var_name_tmp__1313;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__1314->field0)))), 16, 4);
  return (((uint16_t)var_name_load_i16_));
}

