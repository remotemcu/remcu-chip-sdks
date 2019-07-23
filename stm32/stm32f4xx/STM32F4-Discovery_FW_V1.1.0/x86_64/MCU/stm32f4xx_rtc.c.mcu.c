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
struct l_struct_struct_OC_RTC_TypeDef;
struct l_struct_struct_OC_RTC_InitTypeDef;
struct l_struct_struct_OC_RTC_TimeTypeDef;
struct l_struct_struct_OC_RTC_DateTypeDef;
struct l_struct_struct_OC_RTC_AlarmTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_RTC_TypeDef {
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
  uint32_t field20;
  uint32_t field21;
  uint32_t field22;
  uint32_t field23;
  uint32_t field24;
  uint32_t field25;
  uint32_t field26;
  uint32_t field27;
  uint32_t field28;
  uint32_t field29;
  uint32_t field30;
  uint32_t field31;
  uint32_t field32;
  uint32_t field33;
  uint32_t field34;
  uint32_t field35;
  uint32_t field36;
  uint32_t field37;
  uint32_t field38;
  uint32_t field39;
};
struct l_struct_struct_OC_RTC_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
};
struct l_struct_struct_OC_RTC_TimeTypeDef {
  uint8_t field0;
  uint8_t field1;
  uint8_t field2;
  uint8_t field3;
};
struct l_struct_struct_OC_RTC_DateTypeDef {
  uint8_t field0;
  uint8_t field1;
  uint8_t field2;
  uint8_t field3;
};
struct l_struct_struct_OC_RTC_AlarmTypeDef {
  struct l_struct_struct_OC_RTC_TimeTypeDef field0;
  uint32_t field1;
  uint32_t field2;
  uint8_t field3;
};

/* Function Declarations */
uint32_t RTC_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_EnterInitMode(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_WaitForSynchro(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_Init(struct l_struct_struct_OC_RTC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_ExitInitMode(void) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_StructInit(struct l_struct_struct_OC_RTC_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_WriteProtectionCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_RefClockCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_BypassShadowCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_SetTime(uint32_t, struct l_struct_struct_OC_RTC_TimeTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
static uint8_t RTC_Bcd2ToByte(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
static uint8_t RTC_ByteToBcd2(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TimeStructInit(struct l_struct_struct_OC_RTC_TimeTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_GetTime(uint32_t, struct l_struct_struct_OC_RTC_TimeTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetSubSecond(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_SetDate(uint32_t, struct l_struct_struct_OC_RTC_DateTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_DateStructInit(struct l_struct_struct_OC_RTC_DateTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_GetDate(uint32_t, struct l_struct_struct_OC_RTC_DateTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_SetAlarm(uint32_t, uint32_t, struct l_struct_struct_OC_RTC_AlarmTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_AlarmStructInit(struct l_struct_struct_OC_RTC_AlarmTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_GetAlarm(uint32_t, uint32_t, struct l_struct_struct_OC_RTC_AlarmTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_AlarmCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_AlarmSubSecondConfig(uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetAlarmSubSecond(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_WakeUpClockConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_SetWakeUpCounter(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetWakeUpCounter(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_WakeUpCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_DayLightSavingConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetStoreOperation(void) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_OutputConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_CoarseCalibConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_CoarseCalibCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_CalibOutputCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_CalibOutputConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_SmoothCalibConfig(uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TimeStampCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_GetTimeStamp(uint32_t, struct l_struct_struct_OC_RTC_TimeTypeDef*, struct l_struct_struct_OC_RTC_DateTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetTimeStampSubSecond(void) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperTriggerConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperFilterConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperSamplingFreqConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperPinsPrechargeDuration(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TimeStampOnTamperDetectionCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperPullUpCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_WriteBackupRegister(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_ReadBackupRegister(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TamperPinSelection(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_TimeStampPinSelection(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_OutputTypeConfig(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_SynchroShiftConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_ITConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetFlagStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_ClearFlag(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t RTC_GetITStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void RTC_ClearITPendingBit(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint8_t llvm_add_u8(uint8_t a, uint8_t b) {
  uint8_t r = a + b;
  return r;
}
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

uint32_t RTC_DeInit(void) {
  uint32_t var_name_tmp__1;    /* Address-exposed local */
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  uint32_t var_name_tmp__9;
  bool var_name_tmp__10;
  bool var_name_tmp__10__PHI_TEMPORARY;
  uint32_t var_name_tmp__11;
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;

  *(volatile uint32_t*)(&var_name_tmp__1) = 0;
  var_name_tmp__2 = 0;
  var_name_tmp__3 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__4 = RTC_EnterInitMode();
  if ((((var_name_tmp__4 == 0u)&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  var_name_tmp__3 = 0;
  goto var_name_tmp__17;

var_name_tmp__16:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field0)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1)) = 8449;
  var_name_tmp__5 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__5 & 7);
  goto var_name_tmp__18;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__18:
  var_name_tmp__6 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__2 = (var_name_tmp__6 & 4);
  var_name_tmp__7 = *(volatile uint32_t*)(&var_name_tmp__1);
  *(volatile uint32_t*)(&var_name_tmp__1) = (llvm_add_u32(var_name_tmp__7, 1));
  goto var_name_tmp__19;

var_name_tmp__19:
  var_name_tmp__8 = *(volatile uint32_t*)(&var_name_tmp__1);
  if ((((var_name_tmp__8 != 65536u)&1))) {
    goto var_name_tmp__20;
  } else {
    var_name_tmp__10__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__21;
  }

var_name_tmp__20:
  var_name_tmp__9 = var_name_tmp__2;
  var_name_tmp__10__PHI_TEMPORARY = (((var_name_tmp__9 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__21;

var_name_tmp__21:
  var_name_tmp__10 = ((var_name_tmp__10__PHI_TEMPORARY)&1);
  if (var_name_tmp__10) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__22;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__22:
  var_name_tmp__11 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__11 & 4) == 0u)&1))) {
    goto var_name_tmp__23;
  } else {
    goto var_name_tmp__24;
  }

var_name_tmp__23:
  var_name_tmp__3 = 0;
  goto var_name_tmp__25;

var_name_tmp__24:
  var_name_tmp__12 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__12 & 0);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5)) = 65535;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4)) = 8323327;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field6)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = 0;
  var_name_tmp__13 = RTC_WaitForSynchro();
  if ((((var_name_tmp__13 == 0u)&1))) {
    goto var_name_tmp__26;
  } else {
    goto var_name_tmp__27;
  }

var_name_tmp__26:
  var_name_tmp__3 = 0;
  goto var_name_tmp__28;

var_name_tmp__27:
  var_name_tmp__3 = 1;
  goto var_name_tmp__28;

var_name_tmp__28:
  goto var_name_tmp__25;

var_name_tmp__25:
  goto var_name_tmp__17;

var_name_tmp__17:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__14 = var_name_tmp__3;
  return var_name_tmp__14;
}


uint32_t RTC_EnterInitMode(void) {
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  uint32_t var_name_tmp__30;    /* Address-exposed local */
  uint32_t var_name_tmp__31;    /* Address-exposed local */
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint32_t var_name_tmp__35;
  uint32_t var_name_tmp__36;
  bool var_name_tmp__37;
  bool var_name_tmp__37__PHI_TEMPORARY;
  uint32_t var_name_tmp__38;
  uint32_t var_name_tmp__39;

  *(volatile uint32_t*)(&var_name_tmp__29) = 0;
  var_name_tmp__30 = 0;
  var_name_tmp__31 = 0;
  var_name_tmp__32 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__32 & 64) == 0u)&1))) {
    goto var_name_tmp__40;
  } else {
    goto var_name_tmp__41;
  }

var_name_tmp__40:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = -1;
  goto var_name_tmp__42;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__42:
  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__31 = (var_name_tmp__33 & 64);
  var_name_tmp__34 = *(volatile uint32_t*)(&var_name_tmp__29);
  *(volatile uint32_t*)(&var_name_tmp__29) = (llvm_add_u32(var_name_tmp__34, 1));
  goto var_name_tmp__43;

var_name_tmp__43:
  var_name_tmp__35 = *(volatile uint32_t*)(&var_name_tmp__29);
  if ((((var_name_tmp__35 != 65536u)&1))) {
    goto var_name_tmp__44;
  } else {
    var_name_tmp__37__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__45;
  }

var_name_tmp__44:
  var_name_tmp__36 = var_name_tmp__31;
  var_name_tmp__37__PHI_TEMPORARY = (((var_name_tmp__36 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__45;

var_name_tmp__45:
  var_name_tmp__37 = ((var_name_tmp__37__PHI_TEMPORARY)&1);
  if (var_name_tmp__37) {
    goto var_name_tmp__42;
  } else {
    goto var_name_tmp__46;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__46:
  var_name_tmp__38 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__38 & 64) != 0u)&1))) {
    goto var_name_tmp__47;
  } else {
    goto var_name_tmp__48;
  }

var_name_tmp__47:
  var_name_tmp__30 = 1;
  goto var_name_tmp__49;

var_name_tmp__48:
  var_name_tmp__30 = 0;
  goto var_name_tmp__49;

var_name_tmp__49:
  goto var_name_tmp__50;

var_name_tmp__41:
  var_name_tmp__30 = 1;
  goto var_name_tmp__50;

var_name_tmp__50:
  var_name_tmp__39 = var_name_tmp__30;
  return var_name_tmp__39;
}


uint32_t RTC_WaitForSynchro(void) {
  uint32_t var_name_tmp__51;    /* Address-exposed local */
  uint32_t var_name_tmp__52;    /* Address-exposed local */
  uint32_t var_name_tmp__53;    /* Address-exposed local */
  uint32_t var_name_tmp__54;
  uint32_t var_name_tmp__55;
  uint32_t var_name_tmp__56;
  uint32_t var_name_tmp__57;
  uint32_t var_name_tmp__58;
  bool var_name_tmp__59;
  bool var_name_tmp__59__PHI_TEMPORARY;
  uint32_t var_name_tmp__60;
  uint32_t var_name_tmp__61;

  *(volatile uint32_t*)(&var_name_tmp__51) = 0;
  var_name_tmp__52 = 0;
  var_name_tmp__53 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__54 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = (var_name_tmp__54 & -161);
  goto var_name_tmp__62;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__62:
  var_name_tmp__55 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__53 = (var_name_tmp__55 & 32);
  var_name_tmp__56 = *(volatile uint32_t*)(&var_name_tmp__51);
  *(volatile uint32_t*)(&var_name_tmp__51) = (llvm_add_u32(var_name_tmp__56, 1));
  goto var_name_tmp__63;

var_name_tmp__63:
  var_name_tmp__57 = *(volatile uint32_t*)(&var_name_tmp__51);
  if ((((var_name_tmp__57 != 131072u)&1))) {
    goto var_name_tmp__64;
  } else {
    var_name_tmp__59__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__65;
  }

var_name_tmp__64:
  var_name_tmp__58 = var_name_tmp__53;
  var_name_tmp__59__PHI_TEMPORARY = (((var_name_tmp__58 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__65;

var_name_tmp__65:
  var_name_tmp__59 = ((var_name_tmp__59__PHI_TEMPORARY)&1);
  if (var_name_tmp__59) {
    goto var_name_tmp__62;
  } else {
    goto var_name_tmp__66;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__66:
  var_name_tmp__60 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__60 & 32) != 0u)&1))) {
    goto var_name_tmp__67;
  } else {
    goto var_name_tmp__68;
  }

var_name_tmp__67:
  var_name_tmp__52 = 1;
  goto var_name_tmp__69;

var_name_tmp__68:
  var_name_tmp__52 = 0;
  goto var_name_tmp__69;

var_name_tmp__69:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__61 = var_name_tmp__52;
  return var_name_tmp__61;
}


uint32_t RTC_Init(struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__70) {
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__71;    /* Address-exposed local */
  uint32_t var_name_tmp__72;    /* Address-exposed local */
  uint32_t var_name_tmp__73;
  uint32_t var_name_tmp__74;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__75;
  uint32_t var_name_tmp__76;
  uint32_t var_name_tmp__77;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__78;
  uint32_t var_name_tmp__79;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__80;
  uint32_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;

  var_name_tmp__71 = var_name_tmp__70;
  var_name_tmp__72 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__73 = RTC_EnterInitMode();
  if ((((var_name_tmp__73 == 0u)&1))) {
    goto var_name_tmp__84;
  } else {
    goto var_name_tmp__85;
  }

var_name_tmp__84:
  var_name_tmp__72 = 0;
  goto var_name_tmp__86;

var_name_tmp__85:
  var_name_tmp__74 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__74 & -65);
  var_name_tmp__75 = var_name_tmp__71;
  var_name_tmp__76 = *((&var_name_tmp__75->field0));
  var_name_tmp__77 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__77 | var_name_tmp__76);
  var_name_tmp__78 = var_name_tmp__71;
  var_name_tmp__79 = *((&var_name_tmp__78->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4)) = var_name_tmp__79;
  var_name_tmp__80 = var_name_tmp__71;
  var_name_tmp__81 = *((&var_name_tmp__80->field1));
  var_name_tmp__82 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4)) = (var_name_tmp__82 | (var_name_tmp__81 << 16));
  RTC_ExitInitMode();
  var_name_tmp__72 = 1;
  goto var_name_tmp__86;

var_name_tmp__86:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__83 = var_name_tmp__72;
  return var_name_tmp__83;
}


void RTC_ExitInitMode(void) {
  uint32_t var_name_tmp__87;

  var_name_tmp__87 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = (var_name_tmp__87 & -129);
}


void RTC_StructInit(struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__88) {
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__89;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__90;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__91;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__92;

  var_name_tmp__89 = var_name_tmp__88;
  var_name_tmp__90 = var_name_tmp__89;
  *((&var_name_tmp__90->field0)) = 0;
  var_name_tmp__91 = var_name_tmp__89;
  *((&var_name_tmp__91->field1)) = 127;
  var_name_tmp__92 = var_name_tmp__89;
  *((&var_name_tmp__92->field2)) = 255;
}


void RTC_WriteProtectionCmd(uint32_t var_name_tmp__93) {
  uint32_t var_name_tmp__94;    /* Address-exposed local */
  uint32_t var_name_tmp__95;

  var_name_tmp__94 = var_name_tmp__93;
  var_name_tmp__95 = var_name_tmp__94;
  if ((((var_name_tmp__95 != 0u)&1))) {
    goto var_name_tmp__96;
  } else {
    goto var_name_tmp__97;
  }

var_name_tmp__96:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  goto var_name_tmp__98;

var_name_tmp__97:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  goto var_name_tmp__98;

var_name_tmp__98:
  return;
}


uint32_t RTC_RefClockCmd(uint32_t var_name_tmp__99) {
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;
  uint32_t var_name_tmp__103;
  uint32_t var_name_tmp__104;
  uint32_t var_name_tmp__105;
  uint32_t var_name_tmp__106;

  var_name_tmp__100 = var_name_tmp__99;
  var_name_tmp__101 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__102 = RTC_EnterInitMode();
  if ((((var_name_tmp__102 == 0u)&1))) {
    goto var_name_tmp__107;
  } else {
    goto var_name_tmp__108;
  }

var_name_tmp__107:
  var_name_tmp__101 = 0;
  goto var_name_tmp__109;

var_name_tmp__108:
  var_name_tmp__103 = var_name_tmp__100;
  if ((((var_name_tmp__103 != 0u)&1))) {
    goto var_name_tmp__110;
  } else {
    goto var_name_tmp__111;
  }

var_name_tmp__110:
  var_name_tmp__104 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__104 | 16);
  goto var_name_tmp__112;

var_name_tmp__111:
  var_name_tmp__105 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__105 & -17);
  goto var_name_tmp__112;

var_name_tmp__112:
  RTC_ExitInitMode();
  var_name_tmp__101 = 1;
  goto var_name_tmp__109;

var_name_tmp__109:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__106 = var_name_tmp__101;
  return var_name_tmp__106;
}


void RTC_BypassShadowCmd(uint32_t var_name_tmp__113) {
  uint32_t var_name_tmp__114;    /* Address-exposed local */
  uint32_t var_name_tmp__115;
  uint32_t var_name_tmp__116;
  uint32_t var_name_tmp__117;

  var_name_tmp__114 = var_name_tmp__113;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__115 = var_name_tmp__114;
  if ((((var_name_tmp__115 != 0u)&1))) {
    goto var_name_tmp__118;
  } else {
    goto var_name_tmp__119;
  }

var_name_tmp__118:
  var_name_tmp__116 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__116 | 32);
  goto var_name_tmp__120;

var_name_tmp__119:
  var_name_tmp__117 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__117 & 223);
  goto var_name_tmp__120;

var_name_tmp__120:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_SetTime(uint32_t var_name_tmp__121, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__122) {
  uint32_t var_name_tmp__123;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;    /* Address-exposed local */
  uint32_t var_name_tmp__126;    /* Address-exposed local */
  uint32_t var_name_tmp__127;
  uint32_t var_name_tmp__128;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__129;
  uint32_t var_name_tmp__130;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__131;
  uint8_t var_name_tmp__132;
  uint8_t var_name_tmp__133;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__134;
  uint32_t var_name_tmp__135;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__136;
  uint8_t var_name_tmp__137;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__138;
  uint8_t var_name_tmp__139;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__140;
  uint8_t var_name_tmp__141;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__142;
  uint8_t var_name_tmp__143;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__144;
  uint8_t var_name_tmp__145;
  uint8_t var_name_tmp__146;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__147;
  uint8_t var_name_tmp__148;
  uint8_t var_name_tmp__149;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__150;
  uint8_t var_name_tmp__151;
  uint8_t var_name_tmp__152;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__153;
  uint8_t var_name_tmp__154;
  uint32_t var_name_tmp__155;
  uint32_t var_name_tmp__156;
  uint32_t var_name_tmp__157;
  uint32_t var_name_tmp__158;

  var_name_tmp__123 = var_name_tmp__121;
  var_name_tmp__124 = var_name_tmp__122;
  var_name_tmp__125 = 0;
  var_name_tmp__126 = 0;
  var_name_tmp__127 = var_name_tmp__123;
  if ((((var_name_tmp__127 == 0u)&1))) {
    goto var_name_tmp__159;
  } else {
    goto var_name_tmp__160;
  }

var_name_tmp__159:
  var_name_tmp__128 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  if (((((var_name_tmp__128 & 64) != 0u)&1))) {
    goto var_name_tmp__161;
  } else {
    goto var_name_tmp__162;
  }

var_name_tmp__161:
  goto var_name_tmp__163;

var_name_tmp__162:
  var_name_tmp__129 = var_name_tmp__124;
  *((&var_name_tmp__129->field3)) = 0;
  goto var_name_tmp__163;

var_name_tmp__163:
  goto var_name_tmp__164;

var_name_tmp__160:
  var_name_tmp__130 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  if (((((var_name_tmp__130 & 64) != 0u)&1))) {
    goto var_name_tmp__165;
  } else {
    goto var_name_tmp__166;
  }

var_name_tmp__165:
  var_name_tmp__131 = var_name_tmp__124;
  var_name_tmp__132 = *((&var_name_tmp__131->field0));
  var_name_tmp__133 = RTC_Bcd2ToByte(var_name_tmp__132);
  var_name_tmp__125 = (((uint32_t)(uint8_t)var_name_tmp__133));
  goto var_name_tmp__167;

var_name_tmp__166:
  var_name_tmp__134 = var_name_tmp__124;
  *((&var_name_tmp__134->field3)) = 0;
  goto var_name_tmp__167;

var_name_tmp__167:
  goto var_name_tmp__164;

var_name_tmp__164:
  var_name_tmp__135 = var_name_tmp__123;
  if ((((var_name_tmp__135 != 0u)&1))) {
    goto var_name_tmp__168;
  } else {
    goto var_name_tmp__169;
  }

var_name_tmp__168:
  var_name_tmp__136 = var_name_tmp__124;
  var_name_tmp__137 = *((&var_name_tmp__136->field0));
  var_name_tmp__138 = var_name_tmp__124;
  var_name_tmp__139 = *((&var_name_tmp__138->field1));
  var_name_tmp__140 = var_name_tmp__124;
  var_name_tmp__141 = *((&var_name_tmp__140->field2));
  var_name_tmp__142 = var_name_tmp__124;
  var_name_tmp__143 = *((&var_name_tmp__142->field3));
  var_name_tmp__125 = (((((((uint32_t)(uint8_t)var_name_tmp__137)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__139)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__141))) | ((((uint32_t)(uint8_t)var_name_tmp__143)) << 16));
  goto var_name_tmp__170;

var_name_tmp__169:
  var_name_tmp__144 = var_name_tmp__124;
  var_name_tmp__145 = *((&var_name_tmp__144->field0));
  var_name_tmp__146 = RTC_ByteToBcd2(var_name_tmp__145);
  var_name_tmp__147 = var_name_tmp__124;
  var_name_tmp__148 = *((&var_name_tmp__147->field1));
  var_name_tmp__149 = RTC_ByteToBcd2(var_name_tmp__148);
  var_name_tmp__150 = var_name_tmp__124;
  var_name_tmp__151 = *((&var_name_tmp__150->field2));
  var_name_tmp__152 = RTC_ByteToBcd2(var_name_tmp__151);
  var_name_tmp__153 = var_name_tmp__124;
  var_name_tmp__154 = *((&var_name_tmp__153->field3));
  var_name_tmp__125 = (((((((uint32_t)(uint8_t)var_name_tmp__146)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__149)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__152))) | ((((uint32_t)(uint8_t)var_name_tmp__154)) << 16));
  goto var_name_tmp__170;

var_name_tmp__170:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__155 = RTC_EnterInitMode();
  if ((((var_name_tmp__155 == 0u)&1))) {
    goto var_name_tmp__171;
  } else {
    goto var_name_tmp__172;
  }

var_name_tmp__171:
  var_name_tmp__126 = 0;
  goto var_name_tmp__173;

var_name_tmp__172:
  var_name_tmp__156 = var_name_tmp__125;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field0)) = (var_name_tmp__156 & 8355711);
  RTC_ExitInitMode();
  var_name_tmp__157 = RTC_WaitForSynchro();
  if ((((var_name_tmp__157 == 0u)&1))) {
    goto var_name_tmp__174;
  } else {
    goto var_name_tmp__175;
  }

var_name_tmp__174:
  var_name_tmp__126 = 0;
  goto var_name_tmp__176;

var_name_tmp__175:
  var_name_tmp__126 = 1;
  goto var_name_tmp__176;

var_name_tmp__176:
  goto var_name_tmp__173;

var_name_tmp__173:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__158 = var_name_tmp__126;
  return var_name_tmp__158;
}


static uint8_t RTC_Bcd2ToByte(uint8_t var_name_tmp__177) {
  uint8_t var_name_tmp__178;    /* Address-exposed local */
  uint8_t var_name_tmp__179;    /* Address-exposed local */
  uint8_t var_name_tmp__180;
  uint8_t var_name_tmp__181;
  uint8_t var_name_tmp__182;

  var_name_tmp__178 = var_name_tmp__177;
  var_name_tmp__179 = 0;
  var_name_tmp__180 = var_name_tmp__178;
  var_name_tmp__179 = (((uint8_t)(llvm_mul_u32((llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__180)) & 240))))), 4)), 10))));
  var_name_tmp__181 = var_name_tmp__179;
  var_name_tmp__182 = var_name_tmp__178;
  return (((uint8_t)(llvm_add_u32((((uint32_t)(uint8_t)var_name_tmp__181)), ((((uint32_t)(uint8_t)var_name_tmp__182)) & 15)))));
}


static uint8_t RTC_ByteToBcd2(uint8_t var_name_tmp__183) {
  uint8_t var_name_tmp__184;    /* Address-exposed local */
  uint8_t var_name_tmp__185;    /* Address-exposed local */
  uint8_t var_name_tmp__186;
  uint8_t var_name_tmp__187;
  uint8_t var_name_tmp__188;
  uint8_t var_name_tmp__189;
  uint8_t var_name_tmp__190;

  var_name_tmp__184 = var_name_tmp__183;
  var_name_tmp__185 = 0;
  goto var_name_tmp__191;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__191:
  var_name_tmp__186 = var_name_tmp__184;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__186))) >= ((int32_t)10u))&1))) {
    goto var_name_tmp__192;
  } else {
    goto var_name_tmp__193;
  }

var_name_tmp__192:
  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__185 = (llvm_add_u8(var_name_tmp__187, 1));
  var_name_tmp__188 = var_name_tmp__184;
  var_name_tmp__184 = (((uint8_t)(llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__188)), 10))));
  goto var_name_tmp__191;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__193:
  var_name_tmp__189 = var_name_tmp__185;
  var_name_tmp__190 = var_name_tmp__184;
  return (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__189)) << 4))))) | (((uint32_t)(uint8_t)var_name_tmp__190)))));
}


void RTC_TimeStructInit(struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__194) {
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__195;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__196;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__197;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__198;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__199;

  var_name_tmp__195 = var_name_tmp__194;
  var_name_tmp__196 = var_name_tmp__195;
  *((&var_name_tmp__196->field3)) = 0;
  var_name_tmp__197 = var_name_tmp__195;
  *((&var_name_tmp__197->field0)) = 0;
  var_name_tmp__198 = var_name_tmp__195;
  *((&var_name_tmp__198->field1)) = 0;
  var_name_tmp__199 = var_name_tmp__195;
  *((&var_name_tmp__199->field2)) = 0;
}


void RTC_GetTime(uint32_t var_name_tmp__200, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__201) {
  uint32_t var_name_tmp__202;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__203;    /* Address-exposed local */
  uint32_t var_name_tmp__204;    /* Address-exposed local */
  uint32_t var_name_tmp__205;
  uint32_t var_name_tmp__206;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__207;
  uint32_t var_name_tmp__208;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__209;
  uint32_t var_name_tmp__210;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__211;
  uint32_t var_name_tmp__212;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__213;
  uint32_t var_name_tmp__214;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__215;
  uint8_t var_name_tmp__216;
  uint8_t var_name_tmp__217;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__218;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__219;
  uint8_t var_name_tmp__220;
  uint8_t var_name_tmp__221;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__222;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__223;
  uint8_t var_name_tmp__224;
  uint8_t var_name_tmp__225;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__226;

  var_name_tmp__202 = var_name_tmp__200;
  var_name_tmp__203 = var_name_tmp__201;
  var_name_tmp__204 = 0;
  var_name_tmp__205 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field0));
  var_name_tmp__204 = (var_name_tmp__205 & 8355711);
  var_name_tmp__206 = var_name_tmp__204;
  var_name_tmp__207 = var_name_tmp__203;
  *((&var_name_tmp__207->field0)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__206 & 4128768), 16))));
  var_name_tmp__208 = var_name_tmp__204;
  var_name_tmp__209 = var_name_tmp__203;
  *((&var_name_tmp__209->field1)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__208 & 32512), 8))));
  var_name_tmp__210 = var_name_tmp__204;
  var_name_tmp__211 = var_name_tmp__203;
  *((&var_name_tmp__211->field2)) = (((uint8_t)(var_name_tmp__210 & 127)));
  var_name_tmp__212 = var_name_tmp__204;
  var_name_tmp__213 = var_name_tmp__203;
  *((&var_name_tmp__213->field3)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__212 & 4194304), 16))));
  var_name_tmp__214 = var_name_tmp__202;
  if ((((var_name_tmp__214 == 0u)&1))) {
    goto var_name_tmp__227;
  } else {
    goto var_name_tmp__228;
  }

var_name_tmp__227:
  var_name_tmp__215 = var_name_tmp__203;
  var_name_tmp__216 = *((&var_name_tmp__215->field0));
  var_name_tmp__217 = RTC_Bcd2ToByte(var_name_tmp__216);
  var_name_tmp__218 = var_name_tmp__203;
  *((&var_name_tmp__218->field0)) = var_name_tmp__217;
  var_name_tmp__219 = var_name_tmp__203;
  var_name_tmp__220 = *((&var_name_tmp__219->field1));
  var_name_tmp__221 = RTC_Bcd2ToByte(var_name_tmp__220);
  var_name_tmp__222 = var_name_tmp__203;
  *((&var_name_tmp__222->field1)) = var_name_tmp__221;
  var_name_tmp__223 = var_name_tmp__203;
  var_name_tmp__224 = *((&var_name_tmp__223->field2));
  var_name_tmp__225 = RTC_Bcd2ToByte(var_name_tmp__224);
  var_name_tmp__226 = var_name_tmp__203;
  *((&var_name_tmp__226->field2)) = var_name_tmp__225;
  goto var_name_tmp__228;

var_name_tmp__228:
  return;
}


uint32_t RTC_GetSubSecond(void) {
  uint32_t var_name_tmp__229;    /* Address-exposed local */
  uint32_t var_name_tmp__230;
  uint32_t var_name_tmp__231;
  uint32_t var_name_tmp__232;

  var_name_tmp__229 = 0;
  var_name_tmp__230 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field10));
  var_name_tmp__229 = var_name_tmp__230;
  var_name_tmp__231 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1));
  var_name_tmp__232 = var_name_tmp__229;
  return var_name_tmp__232;
}


uint32_t RTC_SetDate(uint32_t var_name_tmp__233, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__234) {
  uint32_t var_name_tmp__235;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__236;    /* Address-exposed local */
  uint32_t var_name_tmp__237;    /* Address-exposed local */
  uint32_t var_name_tmp__238;    /* Address-exposed local */
  uint32_t var_name_tmp__239;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__240;
  uint8_t var_name_tmp__241;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__242;
  uint8_t var_name_tmp__243;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__244;
  uint32_t var_name_tmp__245;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__246;
  uint8_t var_name_tmp__247;
  uint8_t var_name_tmp__248;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__249;
  uint8_t var_name_tmp__250;
  uint8_t var_name_tmp__251;
  uint32_t var_name_tmp__252;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__253;
  uint8_t var_name_tmp__254;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__255;
  uint8_t var_name_tmp__256;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__257;
  uint8_t var_name_tmp__258;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__259;
  uint8_t var_name_tmp__260;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__261;
  uint8_t var_name_tmp__262;
  uint8_t var_name_tmp__263;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__264;
  uint8_t var_name_tmp__265;
  uint8_t var_name_tmp__266;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__267;
  uint8_t var_name_tmp__268;
  uint8_t var_name_tmp__269;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__270;
  uint8_t var_name_tmp__271;
  uint32_t var_name_tmp__272;
  uint32_t var_name_tmp__273;
  uint32_t var_name_tmp__274;
  uint32_t var_name_tmp__275;

  var_name_tmp__235 = var_name_tmp__233;
  var_name_tmp__236 = var_name_tmp__234;
  var_name_tmp__237 = 0;
  var_name_tmp__238 = 0;
  var_name_tmp__239 = var_name_tmp__235;
  if ((((var_name_tmp__239 == 0u)&1))) {
    goto var_name_tmp__276;
  } else {
    goto var_name_tmp__277;
  }

var_name_tmp__276:
  var_name_tmp__240 = var_name_tmp__236;
  var_name_tmp__241 = *((&var_name_tmp__240->field1));
  if ((((((((uint32_t)(uint8_t)var_name_tmp__241)) & 16) == 16u)&1))) {
    goto var_name_tmp__278;
  } else {
    goto var_name_tmp__277;
  }

var_name_tmp__278:
  var_name_tmp__242 = var_name_tmp__236;
  var_name_tmp__243 = *((&var_name_tmp__242->field1));
  var_name_tmp__244 = var_name_tmp__236;
  *((&var_name_tmp__244->field1)) = (((uint8_t)(llvm_add_u32(((((uint32_t)(uint8_t)var_name_tmp__243)) & -17), 10))));
  goto var_name_tmp__277;

var_name_tmp__277:
  var_name_tmp__245 = var_name_tmp__235;
  if ((((var_name_tmp__245 == 0u)&1))) {
    goto var_name_tmp__279;
  } else {
    goto var_name_tmp__280;
  }

var_name_tmp__279:
  goto var_name_tmp__281;

var_name_tmp__280:
  var_name_tmp__246 = var_name_tmp__236;
  var_name_tmp__247 = *((&var_name_tmp__246->field1));
  var_name_tmp__248 = RTC_Bcd2ToByte(var_name_tmp__247);
  var_name_tmp__237 = (((uint32_t)(uint8_t)var_name_tmp__248));
  var_name_tmp__249 = var_name_tmp__236;
  var_name_tmp__250 = *((&var_name_tmp__249->field2));
  var_name_tmp__251 = RTC_Bcd2ToByte(var_name_tmp__250);
  var_name_tmp__237 = (((uint32_t)(uint8_t)var_name_tmp__251));
  goto var_name_tmp__281;

var_name_tmp__281:
  var_name_tmp__252 = var_name_tmp__235;
  if ((((var_name_tmp__252 != 0u)&1))) {
    goto var_name_tmp__282;
  } else {
    goto var_name_tmp__283;
  }

var_name_tmp__282:
  var_name_tmp__253 = var_name_tmp__236;
  var_name_tmp__254 = *((&var_name_tmp__253->field3));
  var_name_tmp__255 = var_name_tmp__236;
  var_name_tmp__256 = *((&var_name_tmp__255->field1));
  var_name_tmp__257 = var_name_tmp__236;
  var_name_tmp__258 = *((&var_name_tmp__257->field2));
  var_name_tmp__259 = var_name_tmp__236;
  var_name_tmp__260 = *((&var_name_tmp__259->field0));
  var_name_tmp__237 = (((((((uint32_t)(uint8_t)var_name_tmp__254)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__256)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__258))) | ((((uint32_t)(uint8_t)var_name_tmp__260)) << 13));
  goto var_name_tmp__284;

var_name_tmp__283:
  var_name_tmp__261 = var_name_tmp__236;
  var_name_tmp__262 = *((&var_name_tmp__261->field3));
  var_name_tmp__263 = RTC_ByteToBcd2(var_name_tmp__262);
  var_name_tmp__264 = var_name_tmp__236;
  var_name_tmp__265 = *((&var_name_tmp__264->field1));
  var_name_tmp__266 = RTC_ByteToBcd2(var_name_tmp__265);
  var_name_tmp__267 = var_name_tmp__236;
  var_name_tmp__268 = *((&var_name_tmp__267->field2));
  var_name_tmp__269 = RTC_ByteToBcd2(var_name_tmp__268);
  var_name_tmp__270 = var_name_tmp__236;
  var_name_tmp__271 = *((&var_name_tmp__270->field0));
  var_name_tmp__237 = (((((((uint32_t)(uint8_t)var_name_tmp__263)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__266)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__269))) | ((((uint32_t)(uint8_t)var_name_tmp__271)) << 13));
  goto var_name_tmp__284;

var_name_tmp__284:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__272 = RTC_EnterInitMode();
  if ((((var_name_tmp__272 == 0u)&1))) {
    goto var_name_tmp__285;
  } else {
    goto var_name_tmp__286;
  }

var_name_tmp__285:
  var_name_tmp__238 = 0;
  goto var_name_tmp__287;

var_name_tmp__286:
  var_name_tmp__273 = var_name_tmp__237;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1)) = (var_name_tmp__273 & 16777023);
  RTC_ExitInitMode();
  var_name_tmp__274 = RTC_WaitForSynchro();
  if ((((var_name_tmp__274 == 0u)&1))) {
    goto var_name_tmp__288;
  } else {
    goto var_name_tmp__289;
  }

var_name_tmp__288:
  var_name_tmp__238 = 0;
  goto var_name_tmp__290;

var_name_tmp__289:
  var_name_tmp__238 = 1;
  goto var_name_tmp__290;

var_name_tmp__290:
  goto var_name_tmp__287;

var_name_tmp__287:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__275 = var_name_tmp__238;
  return var_name_tmp__275;
}


void RTC_DateStructInit(struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__291) {
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__292;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__293;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__294;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__295;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__296;

  var_name_tmp__292 = var_name_tmp__291;
  var_name_tmp__293 = var_name_tmp__292;
  *((&var_name_tmp__293->field0)) = 1;
  var_name_tmp__294 = var_name_tmp__292;
  *((&var_name_tmp__294->field2)) = 1;
  var_name_tmp__295 = var_name_tmp__292;
  *((&var_name_tmp__295->field1)) = 1;
  var_name_tmp__296 = var_name_tmp__292;
  *((&var_name_tmp__296->field3)) = 0;
}


void RTC_GetDate(uint32_t var_name_tmp__297, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__298) {
  uint32_t var_name_tmp__299;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__300;    /* Address-exposed local */
  uint32_t var_name_tmp__301;    /* Address-exposed local */
  uint32_t var_name_tmp__302;
  uint32_t var_name_tmp__303;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__304;
  uint32_t var_name_tmp__305;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__306;
  uint32_t var_name_tmp__307;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__308;
  uint32_t var_name_tmp__309;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__310;
  uint32_t var_name_tmp__311;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__312;
  uint8_t var_name_tmp__313;
  uint8_t var_name_tmp__314;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__315;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__316;
  uint8_t var_name_tmp__317;
  uint8_t var_name_tmp__318;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__319;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__320;
  uint8_t var_name_tmp__321;
  uint8_t var_name_tmp__322;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__323;

  var_name_tmp__299 = var_name_tmp__297;
  var_name_tmp__300 = var_name_tmp__298;
  var_name_tmp__301 = 0;
  var_name_tmp__302 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1));
  var_name_tmp__301 = (var_name_tmp__302 & 16777023);
  var_name_tmp__303 = var_name_tmp__301;
  var_name_tmp__304 = var_name_tmp__300;
  *((&var_name_tmp__304->field3)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__303 & 16711680), 16))));
  var_name_tmp__305 = var_name_tmp__301;
  var_name_tmp__306 = var_name_tmp__300;
  *((&var_name_tmp__306->field1)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__305 & 7936), 8))));
  var_name_tmp__307 = var_name_tmp__301;
  var_name_tmp__308 = var_name_tmp__300;
  *((&var_name_tmp__308->field2)) = (((uint8_t)(var_name_tmp__307 & 63)));
  var_name_tmp__309 = var_name_tmp__301;
  var_name_tmp__310 = var_name_tmp__300;
  *((&var_name_tmp__310->field0)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__309 & 57344), 13))));
  var_name_tmp__311 = var_name_tmp__299;
  if ((((var_name_tmp__311 == 0u)&1))) {
    goto var_name_tmp__324;
  } else {
    goto var_name_tmp__325;
  }

var_name_tmp__324:
  var_name_tmp__312 = var_name_tmp__300;
  var_name_tmp__313 = *((&var_name_tmp__312->field3));
  var_name_tmp__314 = RTC_Bcd2ToByte(var_name_tmp__313);
  var_name_tmp__315 = var_name_tmp__300;
  *((&var_name_tmp__315->field3)) = var_name_tmp__314;
  var_name_tmp__316 = var_name_tmp__300;
  var_name_tmp__317 = *((&var_name_tmp__316->field1));
  var_name_tmp__318 = RTC_Bcd2ToByte(var_name_tmp__317);
  var_name_tmp__319 = var_name_tmp__300;
  *((&var_name_tmp__319->field1)) = var_name_tmp__318;
  var_name_tmp__320 = var_name_tmp__300;
  var_name_tmp__321 = *((&var_name_tmp__320->field2));
  var_name_tmp__322 = RTC_Bcd2ToByte(var_name_tmp__321);
  var_name_tmp__323 = var_name_tmp__300;
  *((&var_name_tmp__323->field2)) = var_name_tmp__322;
  goto var_name_tmp__325;

var_name_tmp__325:
  return;
}


void RTC_SetAlarm(uint32_t var_name_tmp__326, uint32_t var_name_tmp__327, struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__328) {
  uint32_t var_name_tmp__329;    /* Address-exposed local */
  uint32_t var_name_tmp__330;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__331;    /* Address-exposed local */
  uint32_t var_name_tmp__332;    /* Address-exposed local */
  uint32_t var_name_tmp__333;
  uint32_t var_name_tmp__334;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__335;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__336;
  uint32_t var_name_tmp__337;
  uint32_t var_name_tmp__338;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__339;
  uint8_t var_name_tmp__340;
  uint8_t var_name_tmp__341;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__342;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__343;
  uint32_t var_name_tmp__344;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__345;
  uint8_t var_name_tmp__346;
  uint8_t var_name_tmp__347;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__348;
  uint8_t var_name_tmp__349;
  uint8_t var_name_tmp__350;
  uint32_t var_name_tmp__351;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__352;
  uint8_t var_name_tmp__353;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__354;
  uint8_t var_name_tmp__355;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__356;
  uint8_t var_name_tmp__357;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__358;
  uint8_t var_name_tmp__359;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__360;
  uint8_t var_name_tmp__361;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__362;
  uint32_t var_name_tmp__363;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__364;
  uint32_t var_name_tmp__365;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__366;
  uint8_t var_name_tmp__367;
  uint8_t var_name_tmp__368;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__369;
  uint8_t var_name_tmp__370;
  uint8_t var_name_tmp__371;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__372;
  uint8_t var_name_tmp__373;
  uint8_t var_name_tmp__374;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__375;
  uint8_t var_name_tmp__376;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__377;
  uint8_t var_name_tmp__378;
  uint8_t var_name_tmp__379;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__380;
  uint32_t var_name_tmp__381;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__382;
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint32_t var_name_tmp__385;
  uint32_t var_name_tmp__386;

  var_name_tmp__329 = var_name_tmp__326;
  var_name_tmp__330 = var_name_tmp__327;
  var_name_tmp__331 = var_name_tmp__328;
  var_name_tmp__332 = 0;
  var_name_tmp__333 = var_name_tmp__329;
  if ((((var_name_tmp__333 == 0u)&1))) {
    goto var_name_tmp__387;
  } else {
    goto var_name_tmp__388;
  }

var_name_tmp__387:
  var_name_tmp__334 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  if (((((var_name_tmp__334 & 64) != 0u)&1))) {
    goto var_name_tmp__389;
  } else {
    goto var_name_tmp__390;
  }

var_name_tmp__389:
  goto var_name_tmp__391;

var_name_tmp__390:
  var_name_tmp__335 = var_name_tmp__331;
  *((&((&var_name_tmp__335->field0))->field3)) = 0;
  goto var_name_tmp__391;

var_name_tmp__391:
  var_name_tmp__336 = var_name_tmp__331;
  var_name_tmp__337 = *((&var_name_tmp__336->field2));
  if ((((var_name_tmp__337 == 0u)&1))) {
    goto var_name_tmp__392;
  } else {
    goto var_name_tmp__393;
  }

var_name_tmp__392:
  goto var_name_tmp__394;

var_name_tmp__393:
  goto var_name_tmp__394;

var_name_tmp__394:
  goto var_name_tmp__395;

var_name_tmp__388:
  var_name_tmp__338 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  if (((((var_name_tmp__338 & 64) != 0u)&1))) {
    goto var_name_tmp__396;
  } else {
    goto var_name_tmp__397;
  }

var_name_tmp__396:
  var_name_tmp__339 = var_name_tmp__331;
  var_name_tmp__340 = *((&((&var_name_tmp__339->field0))->field0));
  var_name_tmp__341 = RTC_Bcd2ToByte(var_name_tmp__340);
  var_name_tmp__332 = (((uint32_t)(uint8_t)var_name_tmp__341));
  goto var_name_tmp__398;

var_name_tmp__397:
  var_name_tmp__342 = var_name_tmp__331;
  *((&((&var_name_tmp__342->field0))->field3)) = 0;
  goto var_name_tmp__398;

var_name_tmp__398:
  var_name_tmp__343 = var_name_tmp__331;
  var_name_tmp__344 = *((&var_name_tmp__343->field2));
  if ((((var_name_tmp__344 == 0u)&1))) {
    goto var_name_tmp__399;
  } else {
    goto var_name_tmp__400;
  }

var_name_tmp__399:
  var_name_tmp__345 = var_name_tmp__331;
  var_name_tmp__346 = *((&var_name_tmp__345->field3));
  var_name_tmp__347 = RTC_Bcd2ToByte(var_name_tmp__346);
  var_name_tmp__332 = (((uint32_t)(uint8_t)var_name_tmp__347));
  goto var_name_tmp__401;

var_name_tmp__400:
  var_name_tmp__348 = var_name_tmp__331;
  var_name_tmp__349 = *((&var_name_tmp__348->field3));
  var_name_tmp__350 = RTC_Bcd2ToByte(var_name_tmp__349);
  var_name_tmp__332 = (((uint32_t)(uint8_t)var_name_tmp__350));
  goto var_name_tmp__401;

var_name_tmp__401:
  goto var_name_tmp__395;

var_name_tmp__395:
  var_name_tmp__351 = var_name_tmp__329;
  if ((((var_name_tmp__351 != 0u)&1))) {
    goto var_name_tmp__402;
  } else {
    goto var_name_tmp__403;
  }

var_name_tmp__402:
  var_name_tmp__352 = var_name_tmp__331;
  var_name_tmp__353 = *((&((&var_name_tmp__352->field0))->field0));
  var_name_tmp__354 = var_name_tmp__331;
  var_name_tmp__355 = *((&((&var_name_tmp__354->field0))->field1));
  var_name_tmp__356 = var_name_tmp__331;
  var_name_tmp__357 = *((&((&var_name_tmp__356->field0))->field2));
  var_name_tmp__358 = var_name_tmp__331;
  var_name_tmp__359 = *((&((&var_name_tmp__358->field0))->field3));
  var_name_tmp__360 = var_name_tmp__331;
  var_name_tmp__361 = *((&var_name_tmp__360->field3));
  var_name_tmp__362 = var_name_tmp__331;
  var_name_tmp__363 = *((&var_name_tmp__362->field2));
  var_name_tmp__364 = var_name_tmp__331;
  var_name_tmp__365 = *((&var_name_tmp__364->field1));
  var_name_tmp__332 = ((((((((((uint32_t)(uint8_t)var_name_tmp__353)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__355)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__357))) | ((((uint32_t)(uint8_t)var_name_tmp__359)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__361)) << 24)) | var_name_tmp__363) | var_name_tmp__365);
  goto var_name_tmp__404;

var_name_tmp__403:
  var_name_tmp__366 = var_name_tmp__331;
  var_name_tmp__367 = *((&((&var_name_tmp__366->field0))->field0));
  var_name_tmp__368 = RTC_ByteToBcd2(var_name_tmp__367);
  var_name_tmp__369 = var_name_tmp__331;
  var_name_tmp__370 = *((&((&var_name_tmp__369->field0))->field1));
  var_name_tmp__371 = RTC_ByteToBcd2(var_name_tmp__370);
  var_name_tmp__372 = var_name_tmp__331;
  var_name_tmp__373 = *((&((&var_name_tmp__372->field0))->field2));
  var_name_tmp__374 = RTC_ByteToBcd2(var_name_tmp__373);
  var_name_tmp__375 = var_name_tmp__331;
  var_name_tmp__376 = *((&((&var_name_tmp__375->field0))->field3));
  var_name_tmp__377 = var_name_tmp__331;
  var_name_tmp__378 = *((&var_name_tmp__377->field3));
  var_name_tmp__379 = RTC_ByteToBcd2(var_name_tmp__378);
  var_name_tmp__380 = var_name_tmp__331;
  var_name_tmp__381 = *((&var_name_tmp__380->field2));
  var_name_tmp__382 = var_name_tmp__331;
  var_name_tmp__383 = *((&var_name_tmp__382->field1));
  var_name_tmp__332 = ((((((((((uint32_t)(uint8_t)var_name_tmp__368)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__371)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__374))) | ((((uint32_t)(uint8_t)var_name_tmp__376)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__379)) << 24)) | var_name_tmp__381) | var_name_tmp__383);
  goto var_name_tmp__404;

var_name_tmp__404:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__384 = var_name_tmp__330;
  if ((((var_name_tmp__384 == 256u)&1))) {
    goto var_name_tmp__405;
  } else {
    goto var_name_tmp__406;
  }

var_name_tmp__405:
  var_name_tmp__385 = var_name_tmp__332;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7)) = var_name_tmp__385;
  goto var_name_tmp__407;

var_name_tmp__406:
  var_name_tmp__386 = var_name_tmp__332;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8)) = var_name_tmp__386;
  goto var_name_tmp__407;

var_name_tmp__407:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


void RTC_AlarmStructInit(struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__408) {
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__409;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__410;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__411;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__412;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__413;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__414;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__415;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__416;

  var_name_tmp__409 = var_name_tmp__408;
  var_name_tmp__410 = var_name_tmp__409;
  *((&((&var_name_tmp__410->field0))->field3)) = 0;
  var_name_tmp__411 = var_name_tmp__409;
  *((&((&var_name_tmp__411->field0))->field0)) = 0;
  var_name_tmp__412 = var_name_tmp__409;
  *((&((&var_name_tmp__412->field0))->field1)) = 0;
  var_name_tmp__413 = var_name_tmp__409;
  *((&((&var_name_tmp__413->field0))->field2)) = 0;
  var_name_tmp__414 = var_name_tmp__409;
  *((&var_name_tmp__414->field2)) = 0;
  var_name_tmp__415 = var_name_tmp__409;
  *((&var_name_tmp__415->field3)) = 1;
  var_name_tmp__416 = var_name_tmp__409;
  *((&var_name_tmp__416->field1)) = 0;
}


void RTC_GetAlarm(uint32_t var_name_tmp__417, uint32_t var_name_tmp__418, struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__419) {
  uint32_t var_name_tmp__420;    /* Address-exposed local */
  uint32_t var_name_tmp__421;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__422;    /* Address-exposed local */
  uint32_t var_name_tmp__423;    /* Address-exposed local */
  uint32_t var_name_tmp__424;
  uint32_t var_name_tmp__425;
  uint32_t var_name_tmp__426;
  uint32_t var_name_tmp__427;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__428;
  uint32_t var_name_tmp__429;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__430;
  uint32_t var_name_tmp__431;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__432;
  uint32_t var_name_tmp__433;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__434;
  uint32_t var_name_tmp__435;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__436;
  uint32_t var_name_tmp__437;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__438;
  uint32_t var_name_tmp__439;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__440;
  uint32_t var_name_tmp__441;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__442;
  uint8_t var_name_tmp__443;
  uint8_t var_name_tmp__444;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__445;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__446;
  uint8_t var_name_tmp__447;
  uint8_t var_name_tmp__448;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__449;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__450;
  uint8_t var_name_tmp__451;
  uint8_t var_name_tmp__452;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__453;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__454;
  uint8_t var_name_tmp__455;
  uint8_t var_name_tmp__456;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__457;

  var_name_tmp__420 = var_name_tmp__417;
  var_name_tmp__421 = var_name_tmp__418;
  var_name_tmp__422 = var_name_tmp__419;
  var_name_tmp__423 = 0;
  var_name_tmp__424 = var_name_tmp__421;
  if ((((var_name_tmp__424 == 256u)&1))) {
    goto var_name_tmp__458;
  } else {
    goto var_name_tmp__459;
  }

var_name_tmp__458:
  var_name_tmp__425 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7));
  var_name_tmp__423 = var_name_tmp__425;
  goto var_name_tmp__460;

var_name_tmp__459:
  var_name_tmp__426 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8));
  var_name_tmp__423 = var_name_tmp__426;
  goto var_name_tmp__460;

var_name_tmp__460:
  var_name_tmp__427 = var_name_tmp__423;
  var_name_tmp__428 = var_name_tmp__422;
  *((&((&var_name_tmp__428->field0))->field0)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__427 & 4128768), 16))));
  var_name_tmp__429 = var_name_tmp__423;
  var_name_tmp__430 = var_name_tmp__422;
  *((&((&var_name_tmp__430->field0))->field1)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__429 & 32512), 8))));
  var_name_tmp__431 = var_name_tmp__423;
  var_name_tmp__432 = var_name_tmp__422;
  *((&((&var_name_tmp__432->field0))->field2)) = (((uint8_t)(var_name_tmp__431 & 127)));
  var_name_tmp__433 = var_name_tmp__423;
  var_name_tmp__434 = var_name_tmp__422;
  *((&((&var_name_tmp__434->field0))->field3)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__433 & 4194304), 16))));
  var_name_tmp__435 = var_name_tmp__423;
  var_name_tmp__436 = var_name_tmp__422;
  *((&var_name_tmp__436->field3)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__435 & 1056964608), 24))));
  var_name_tmp__437 = var_name_tmp__423;
  var_name_tmp__438 = var_name_tmp__422;
  *((&var_name_tmp__438->field2)) = (var_name_tmp__437 & 1073741824u);
  var_name_tmp__439 = var_name_tmp__423;
  var_name_tmp__440 = var_name_tmp__422;
  *((&var_name_tmp__440->field1)) = (var_name_tmp__439 & 2155905152u);
  var_name_tmp__441 = var_name_tmp__420;
  if ((((var_name_tmp__441 == 0u)&1))) {
    goto var_name_tmp__461;
  } else {
    goto var_name_tmp__462;
  }

var_name_tmp__461:
  var_name_tmp__442 = var_name_tmp__422;
  var_name_tmp__443 = *((&((&var_name_tmp__442->field0))->field0));
  var_name_tmp__444 = RTC_Bcd2ToByte(var_name_tmp__443);
  var_name_tmp__445 = var_name_tmp__422;
  *((&((&var_name_tmp__445->field0))->field0)) = var_name_tmp__444;
  var_name_tmp__446 = var_name_tmp__422;
  var_name_tmp__447 = *((&((&var_name_tmp__446->field0))->field1));
  var_name_tmp__448 = RTC_Bcd2ToByte(var_name_tmp__447);
  var_name_tmp__449 = var_name_tmp__422;
  *((&((&var_name_tmp__449->field0))->field1)) = var_name_tmp__448;
  var_name_tmp__450 = var_name_tmp__422;
  var_name_tmp__451 = *((&((&var_name_tmp__450->field0))->field2));
  var_name_tmp__452 = RTC_Bcd2ToByte(var_name_tmp__451);
  var_name_tmp__453 = var_name_tmp__422;
  *((&((&var_name_tmp__453->field0))->field2)) = var_name_tmp__452;
  var_name_tmp__454 = var_name_tmp__422;
  var_name_tmp__455 = *((&var_name_tmp__454->field3));
  var_name_tmp__456 = RTC_Bcd2ToByte(var_name_tmp__455);
  var_name_tmp__457 = var_name_tmp__422;
  *((&var_name_tmp__457->field3)) = var_name_tmp__456;
  goto var_name_tmp__462;

var_name_tmp__462:
  return;
}


uint32_t RTC_AlarmCmd(uint32_t var_name_tmp__463, uint32_t var_name_tmp__464) {
  uint32_t var_name_tmp__465;    /* Address-exposed local */
  uint32_t var_name_tmp__466;    /* Address-exposed local */
  uint32_t var_name_tmp__467;    /* Address-exposed local */
  uint32_t var_name_tmp__468;    /* Address-exposed local */
  uint32_t var_name_tmp__469;    /* Address-exposed local */
  uint32_t var_name_tmp__470;
  uint32_t var_name_tmp__471;
  uint32_t var_name_tmp__472;
  uint32_t var_name_tmp__473;
  uint32_t var_name_tmp__474;
  uint32_t var_name_tmp__475;
  uint32_t var_name_tmp__476;
  uint32_t var_name_tmp__477;
  uint32_t var_name_tmp__478;
  uint32_t var_name_tmp__479;
  bool var_name_tmp__480;
  bool var_name_tmp__480__PHI_TEMPORARY;
  uint32_t var_name_tmp__481;
  uint32_t var_name_tmp__482;
  uint32_t var_name_tmp__483;

  var_name_tmp__465 = var_name_tmp__463;
  var_name_tmp__466 = var_name_tmp__464;
  *(volatile uint32_t*)(&var_name_tmp__467) = 0;
  var_name_tmp__468 = 0;
  var_name_tmp__469 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__470 = var_name_tmp__466;
  if ((((var_name_tmp__470 != 0u)&1))) {
    goto var_name_tmp__484;
  } else {
    goto var_name_tmp__485;
  }

var_name_tmp__484:
  var_name_tmp__471 = var_name_tmp__465;
  var_name_tmp__472 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__472 | var_name_tmp__471);
  var_name_tmp__469 = 1;
  goto var_name_tmp__486;

var_name_tmp__485:
  var_name_tmp__473 = var_name_tmp__465;
  var_name_tmp__474 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__474 & (~(var_name_tmp__473)));
  goto var_name_tmp__487;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__487:
  var_name_tmp__475 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__476 = var_name_tmp__465;
  var_name_tmp__468 = (var_name_tmp__475 & (llvm_lshr_u32(var_name_tmp__476, 8)));
  var_name_tmp__477 = *(volatile uint32_t*)(&var_name_tmp__467);
  *(volatile uint32_t*)(&var_name_tmp__467) = (llvm_add_u32(var_name_tmp__477, 1));
  goto var_name_tmp__488;

var_name_tmp__488:
  var_name_tmp__478 = *(volatile uint32_t*)(&var_name_tmp__467);
  if ((((var_name_tmp__478 != 65536u)&1))) {
    goto var_name_tmp__489;
  } else {
    var_name_tmp__480__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__490;
  }

var_name_tmp__489:
  var_name_tmp__479 = var_name_tmp__468;
  var_name_tmp__480__PHI_TEMPORARY = (((var_name_tmp__479 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__490;

var_name_tmp__490:
  var_name_tmp__480 = ((var_name_tmp__480__PHI_TEMPORARY)&1);
  if (var_name_tmp__480) {
    goto var_name_tmp__487;
  } else {
    goto var_name_tmp__491;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__491:
  var_name_tmp__481 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__482 = var_name_tmp__465;
  if (((((var_name_tmp__481 & (llvm_lshr_u32(var_name_tmp__482, 8))) == 0u)&1))) {
    goto var_name_tmp__492;
  } else {
    goto var_name_tmp__493;
  }

var_name_tmp__492:
  var_name_tmp__469 = 0;
  goto var_name_tmp__494;

var_name_tmp__493:
  var_name_tmp__469 = 1;
  goto var_name_tmp__494;

var_name_tmp__494:
  goto var_name_tmp__486;

var_name_tmp__486:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__483 = var_name_tmp__469;
  return var_name_tmp__483;
}


void RTC_AlarmSubSecondConfig(uint32_t var_name_tmp__495, uint32_t var_name_tmp__496, uint32_t var_name_tmp__497) {
  uint32_t var_name_tmp__498;    /* Address-exposed local */
  uint32_t var_name_tmp__499;    /* Address-exposed local */
  uint32_t var_name_tmp__500;    /* Address-exposed local */
  uint32_t var_name_tmp__501;    /* Address-exposed local */
  uint32_t var_name_tmp__502;
  uint32_t var_name_tmp__503;
  uint32_t var_name_tmp__504;
  uint32_t var_name_tmp__505;
  uint32_t var_name_tmp__506;

  var_name_tmp__498 = var_name_tmp__495;
  var_name_tmp__499 = var_name_tmp__496;
  var_name_tmp__500 = var_name_tmp__497;
  var_name_tmp__501 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__502 = var_name_tmp__499;
  var_name_tmp__503 = var_name_tmp__500;
  var_name_tmp__501 = (var_name_tmp__502 | var_name_tmp__503);
  var_name_tmp__504 = var_name_tmp__498;
  if ((((var_name_tmp__504 == 256u)&1))) {
    goto var_name_tmp__507;
  } else {
    goto var_name_tmp__508;
  }

var_name_tmp__507:
  var_name_tmp__505 = var_name_tmp__501;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field17)) = var_name_tmp__505;
  goto var_name_tmp__509;

var_name_tmp__508:
  var_name_tmp__506 = var_name_tmp__501;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field18)) = var_name_tmp__506;
  goto var_name_tmp__509;

var_name_tmp__509:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_GetAlarmSubSecond(uint32_t var_name_tmp__510) {
  uint32_t var_name_tmp__511;    /* Address-exposed local */
  uint32_t var_name_tmp__512;    /* Address-exposed local */
  uint32_t var_name_tmp__513;
  uint32_t var_name_tmp__514;
  uint32_t var_name_tmp__515;
  uint32_t var_name_tmp__516;

  var_name_tmp__511 = var_name_tmp__510;
  var_name_tmp__512 = 0;
  var_name_tmp__513 = var_name_tmp__511;
  if ((((var_name_tmp__513 == 256u)&1))) {
    goto var_name_tmp__517;
  } else {
    goto var_name_tmp__518;
  }

var_name_tmp__517:
  var_name_tmp__514 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field17));
  var_name_tmp__512 = (var_name_tmp__514 & 32767);
  goto var_name_tmp__519;

var_name_tmp__518:
  var_name_tmp__515 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field18));
  var_name_tmp__512 = (var_name_tmp__515 & 32767);
  goto var_name_tmp__519;

var_name_tmp__519:
  var_name_tmp__516 = var_name_tmp__512;
  return var_name_tmp__516;
}


void RTC_WakeUpClockConfig(uint32_t var_name_tmp__520) {
  uint32_t var_name_tmp__521;    /* Address-exposed local */
  uint32_t var_name_tmp__522;
  uint32_t var_name_tmp__523;
  uint32_t var_name_tmp__524;

  var_name_tmp__521 = var_name_tmp__520;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__522 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__522 & -8);
  var_name_tmp__523 = var_name_tmp__521;
  var_name_tmp__524 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__524 | var_name_tmp__523);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


void RTC_SetWakeUpCounter(uint32_t var_name_tmp__525) {
  uint32_t var_name_tmp__526;    /* Address-exposed local */
  uint32_t var_name_tmp__527;

  var_name_tmp__526 = var_name_tmp__525;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__527 = var_name_tmp__526;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5)) = var_name_tmp__527;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_GetWakeUpCounter(void) {
  uint32_t var_name_tmp__528;

  var_name_tmp__528 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5));
  return (var_name_tmp__528 & 65535);
}


uint32_t RTC_WakeUpCmd(uint32_t var_name_tmp__529) {
  uint32_t var_name_tmp__530;    /* Address-exposed local */
  uint32_t var_name_tmp__531;    /* Address-exposed local */
  uint32_t var_name_tmp__532;    /* Address-exposed local */
  uint32_t var_name_tmp__533;    /* Address-exposed local */
  uint32_t var_name_tmp__534;
  uint32_t var_name_tmp__535;
  uint32_t var_name_tmp__536;
  uint32_t var_name_tmp__537;
  uint32_t var_name_tmp__538;
  uint32_t var_name_tmp__539;
  uint32_t var_name_tmp__540;
  bool var_name_tmp__541;
  bool var_name_tmp__541__PHI_TEMPORARY;
  uint32_t var_name_tmp__542;
  uint32_t var_name_tmp__543;

  var_name_tmp__530 = var_name_tmp__529;
  *(volatile uint32_t*)(&var_name_tmp__531) = 0;
  var_name_tmp__532 = 0;
  var_name_tmp__533 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__534 = var_name_tmp__530;
  if ((((var_name_tmp__534 != 0u)&1))) {
    goto var_name_tmp__544;
  } else {
    goto var_name_tmp__545;
  }

var_name_tmp__544:
  var_name_tmp__535 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__535 | 1024);
  var_name_tmp__533 = 1;
  goto var_name_tmp__546;

var_name_tmp__545:
  var_name_tmp__536 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__536 & -1025);
  goto var_name_tmp__547;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__547:
  var_name_tmp__537 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__532 = (var_name_tmp__537 & 4);
  var_name_tmp__538 = *(volatile uint32_t*)(&var_name_tmp__531);
  *(volatile uint32_t*)(&var_name_tmp__531) = (llvm_add_u32(var_name_tmp__538, 1));
  goto var_name_tmp__548;

var_name_tmp__548:
  var_name_tmp__539 = *(volatile uint32_t*)(&var_name_tmp__531);
  if ((((var_name_tmp__539 != 65536u)&1))) {
    goto var_name_tmp__549;
  } else {
    var_name_tmp__541__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__550;
  }

var_name_tmp__549:
  var_name_tmp__540 = var_name_tmp__532;
  var_name_tmp__541__PHI_TEMPORARY = (((var_name_tmp__540 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__550;

var_name_tmp__550:
  var_name_tmp__541 = ((var_name_tmp__541__PHI_TEMPORARY)&1);
  if (var_name_tmp__541) {
    goto var_name_tmp__547;
  } else {
    goto var_name_tmp__551;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__551:
  var_name_tmp__542 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__542 & 4) == 0u)&1))) {
    goto var_name_tmp__552;
  } else {
    goto var_name_tmp__553;
  }

var_name_tmp__552:
  var_name_tmp__533 = 0;
  goto var_name_tmp__554;

var_name_tmp__553:
  var_name_tmp__533 = 1;
  goto var_name_tmp__554;

var_name_tmp__554:
  goto var_name_tmp__546;

var_name_tmp__546:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__543 = var_name_tmp__533;
  return var_name_tmp__543;
}


void RTC_DayLightSavingConfig(uint32_t var_name_tmp__555, uint32_t var_name_tmp__556) {
  uint32_t var_name_tmp__557;    /* Address-exposed local */
  uint32_t var_name_tmp__558;    /* Address-exposed local */
  uint32_t var_name_tmp__559;
  uint32_t var_name_tmp__560;
  uint32_t var_name_tmp__561;
  uint32_t var_name_tmp__562;

  var_name_tmp__557 = var_name_tmp__555;
  var_name_tmp__558 = var_name_tmp__556;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__559 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__559 & -262145);
  var_name_tmp__560 = var_name_tmp__557;
  var_name_tmp__561 = var_name_tmp__558;
  var_name_tmp__562 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__562 | (var_name_tmp__560 | var_name_tmp__561));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_GetStoreOperation(void) {
  uint32_t var_name_tmp__563;

  var_name_tmp__563 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  return (var_name_tmp__563 & 262144);
}


void RTC_OutputConfig(uint32_t var_name_tmp__564, uint32_t var_name_tmp__565) {
  uint32_t var_name_tmp__566;    /* Address-exposed local */
  uint32_t var_name_tmp__567;    /* Address-exposed local */
  uint32_t var_name_tmp__568;
  uint32_t var_name_tmp__569;
  uint32_t var_name_tmp__570;
  uint32_t var_name_tmp__571;

  var_name_tmp__566 = var_name_tmp__564;
  var_name_tmp__567 = var_name_tmp__565;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__568 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__568 & -7340033);
  var_name_tmp__569 = var_name_tmp__566;
  var_name_tmp__570 = var_name_tmp__567;
  var_name_tmp__571 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__571 | (var_name_tmp__569 | var_name_tmp__570));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_CoarseCalibConfig(uint32_t var_name_tmp__572, uint32_t var_name_tmp__573) {
  uint32_t var_name_tmp__574;    /* Address-exposed local */
  uint32_t var_name_tmp__575;    /* Address-exposed local */
  uint32_t var_name_tmp__576;    /* Address-exposed local */
  uint32_t var_name_tmp__577;
  uint32_t var_name_tmp__578;
  uint32_t var_name_tmp__579;
  uint32_t var_name_tmp__580;

  var_name_tmp__574 = var_name_tmp__572;
  var_name_tmp__575 = var_name_tmp__573;
  var_name_tmp__576 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__577 = RTC_EnterInitMode();
  if ((((var_name_tmp__577 == 0u)&1))) {
    goto var_name_tmp__581;
  } else {
    goto var_name_tmp__582;
  }

var_name_tmp__581:
  var_name_tmp__576 = 0;
  goto var_name_tmp__583;

var_name_tmp__582:
  var_name_tmp__578 = var_name_tmp__574;
  var_name_tmp__579 = var_name_tmp__575;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field6)) = (var_name_tmp__578 | var_name_tmp__579);
  RTC_ExitInitMode();
  var_name_tmp__576 = 1;
  goto var_name_tmp__583;

var_name_tmp__583:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__580 = var_name_tmp__576;
  return var_name_tmp__580;
}


uint32_t RTC_CoarseCalibCmd(uint32_t var_name_tmp__584) {
  uint32_t var_name_tmp__585;    /* Address-exposed local */
  uint32_t var_name_tmp__586;    /* Address-exposed local */
  uint32_t var_name_tmp__587;
  uint32_t var_name_tmp__588;
  uint32_t var_name_tmp__589;
  uint32_t var_name_tmp__590;
  uint32_t var_name_tmp__591;

  var_name_tmp__585 = var_name_tmp__584;
  var_name_tmp__586 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__587 = RTC_EnterInitMode();
  if ((((var_name_tmp__587 == 0u)&1))) {
    goto var_name_tmp__592;
  } else {
    goto var_name_tmp__593;
  }

var_name_tmp__592:
  var_name_tmp__586 = 0;
  goto var_name_tmp__594;

var_name_tmp__593:
  var_name_tmp__588 = var_name_tmp__585;
  if ((((var_name_tmp__588 != 0u)&1))) {
    goto var_name_tmp__595;
  } else {
    goto var_name_tmp__596;
  }

var_name_tmp__595:
  var_name_tmp__589 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__589 | 128);
  goto var_name_tmp__597;

var_name_tmp__596:
  var_name_tmp__590 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__590 & -129);
  goto var_name_tmp__597;

var_name_tmp__597:
  RTC_ExitInitMode();
  var_name_tmp__586 = 1;
  goto var_name_tmp__594;

var_name_tmp__594:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__591 = var_name_tmp__586;
  return var_name_tmp__591;
}


void RTC_CalibOutputCmd(uint32_t var_name_tmp__598) {
  uint32_t var_name_tmp__599;    /* Address-exposed local */
  uint32_t var_name_tmp__600;
  uint32_t var_name_tmp__601;
  uint32_t var_name_tmp__602;

  var_name_tmp__599 = var_name_tmp__598;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__600 = var_name_tmp__599;
  if ((((var_name_tmp__600 != 0u)&1))) {
    goto var_name_tmp__603;
  } else {
    goto var_name_tmp__604;
  }

var_name_tmp__603:
  var_name_tmp__601 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__601 | 8388608);
  goto var_name_tmp__605;

var_name_tmp__604:
  var_name_tmp__602 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__602 & -8388609);
  goto var_name_tmp__605;

var_name_tmp__605:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


void RTC_CalibOutputConfig(uint32_t var_name_tmp__606) {
  uint32_t var_name_tmp__607;    /* Address-exposed local */
  uint32_t var_name_tmp__608;
  uint32_t var_name_tmp__609;
  uint32_t var_name_tmp__610;

  var_name_tmp__607 = var_name_tmp__606;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__608 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__608 & -524289);
  var_name_tmp__609 = var_name_tmp__607;
  var_name_tmp__610 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__610 | var_name_tmp__609);
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_SmoothCalibConfig(uint32_t var_name_tmp__611, uint32_t var_name_tmp__612, uint32_t var_name_tmp__613) {
  uint32_t var_name_tmp__614;    /* Address-exposed local */
  uint32_t var_name_tmp__615;    /* Address-exposed local */
  uint32_t var_name_tmp__616;    /* Address-exposed local */
  uint32_t var_name_tmp__617;    /* Address-exposed local */
  uint32_t var_name_tmp__618;    /* Address-exposed local */
  uint32_t var_name_tmp__619;
  uint32_t var_name_tmp__620;
  uint32_t var_name_tmp__621;
  bool var_name_tmp__622;
  bool var_name_tmp__622__PHI_TEMPORARY;
  uint32_t var_name_tmp__623;
  uint32_t var_name_tmp__624;
  uint32_t var_name_tmp__625;
  uint32_t var_name_tmp__626;
  uint32_t var_name_tmp__627;
  uint32_t var_name_tmp__628;

  var_name_tmp__614 = var_name_tmp__611;
  var_name_tmp__615 = var_name_tmp__612;
  var_name_tmp__616 = var_name_tmp__613;
  var_name_tmp__617 = 0;
  var_name_tmp__618 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__619 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__619 & 65536) != 0u)&1))) {
    goto var_name_tmp__629;
  } else {
    goto var_name_tmp__630;
  }

var_name_tmp__629:
  goto var_name_tmp__631;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__631:
  var_name_tmp__620 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__620 & 65536) != 0u)&1))) {
    goto var_name_tmp__632;
  } else {
    var_name_tmp__622__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__633;
  }

var_name_tmp__632:
  var_name_tmp__621 = var_name_tmp__618;
  var_name_tmp__622__PHI_TEMPORARY = (((var_name_tmp__621 != 131072u)&1));   /* for PHI node */
  goto var_name_tmp__633;

var_name_tmp__633:
  var_name_tmp__622 = ((var_name_tmp__622__PHI_TEMPORARY)&1);
  if (var_name_tmp__622) {
    goto var_name_tmp__634;
  } else {
    goto var_name_tmp__635;
  }

var_name_tmp__634:
  var_name_tmp__623 = var_name_tmp__618;
  var_name_tmp__618 = (llvm_add_u32(var_name_tmp__623, 1));
  goto var_name_tmp__631;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__635:
  goto var_name_tmp__630;

var_name_tmp__630:
  var_name_tmp__624 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__624 & 65536) == 0u)&1))) {
    goto var_name_tmp__636;
  } else {
    goto var_name_tmp__637;
  }

var_name_tmp__636:
  var_name_tmp__625 = var_name_tmp__614;
  var_name_tmp__626 = var_name_tmp__615;
  var_name_tmp__627 = var_name_tmp__616;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field15)) = ((var_name_tmp__625 | var_name_tmp__626) | var_name_tmp__627);
  var_name_tmp__617 = 1;
  goto var_name_tmp__638;

var_name_tmp__637:
  var_name_tmp__617 = 0;
  goto var_name_tmp__638;

var_name_tmp__638:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__628 = var_name_tmp__617;
  return var_name_tmp__628;
}


void RTC_TimeStampCmd(uint32_t var_name_tmp__639, uint32_t var_name_tmp__640) {
  uint32_t var_name_tmp__641;    /* Address-exposed local */
  uint32_t var_name_tmp__642;    /* Address-exposed local */
  uint32_t var_name_tmp__643;    /* Address-exposed local */
  uint32_t var_name_tmp__644;
  uint32_t var_name_tmp__645;
  uint32_t var_name_tmp__646;
  uint32_t var_name_tmp__647;
  uint32_t var_name_tmp__648;
  uint32_t var_name_tmp__649;
  uint32_t var_name_tmp__650;

  var_name_tmp__641 = var_name_tmp__639;
  var_name_tmp__642 = var_name_tmp__640;
  var_name_tmp__643 = 0;
  var_name_tmp__644 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  var_name_tmp__643 = (var_name_tmp__644 & -2057);
  var_name_tmp__645 = var_name_tmp__642;
  if ((((var_name_tmp__645 != 0u)&1))) {
    goto var_name_tmp__651;
  } else {
    goto var_name_tmp__652;
  }

var_name_tmp__651:
  var_name_tmp__646 = var_name_tmp__641;
  var_name_tmp__647 = var_name_tmp__643;
  var_name_tmp__643 = (var_name_tmp__647 | (var_name_tmp__646 | 2048));
  goto var_name_tmp__653;

var_name_tmp__652:
  var_name_tmp__648 = var_name_tmp__641;
  var_name_tmp__649 = var_name_tmp__643;
  var_name_tmp__643 = (var_name_tmp__649 | var_name_tmp__648);
  goto var_name_tmp__653;

var_name_tmp__653:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__650 = var_name_tmp__643;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = var_name_tmp__650;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


void RTC_GetTimeStamp(uint32_t var_name_tmp__654, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__655, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__656) {
  uint32_t var_name_tmp__657;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__658;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__659;    /* Address-exposed local */
  uint32_t var_name_tmp__660;    /* Address-exposed local */
  uint32_t var_name_tmp__661;    /* Address-exposed local */
  uint32_t var_name_tmp__662;
  uint32_t var_name_tmp__663;
  uint32_t var_name_tmp__664;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__665;
  uint32_t var_name_tmp__666;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__667;
  uint32_t var_name_tmp__668;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__669;
  uint32_t var_name_tmp__670;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__671;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__672;
  uint32_t var_name_tmp__673;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__674;
  uint32_t var_name_tmp__675;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__676;
  uint32_t var_name_tmp__677;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__678;
  uint32_t var_name_tmp__679;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__680;
  uint8_t var_name_tmp__681;
  uint8_t var_name_tmp__682;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__683;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__684;
  uint8_t var_name_tmp__685;
  uint8_t var_name_tmp__686;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__687;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__688;
  uint8_t var_name_tmp__689;
  uint8_t var_name_tmp__690;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__691;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__692;
  uint8_t var_name_tmp__693;
  uint8_t var_name_tmp__694;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__695;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__696;
  uint8_t var_name_tmp__697;
  uint8_t var_name_tmp__698;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__699;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__700;
  uint8_t var_name_tmp__701;
  uint8_t var_name_tmp__702;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__703;

  var_name_tmp__657 = var_name_tmp__654;
  var_name_tmp__658 = var_name_tmp__655;
  var_name_tmp__659 = var_name_tmp__656;
  var_name_tmp__660 = 0;
  var_name_tmp__661 = 0;
  var_name_tmp__662 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field12));
  var_name_tmp__660 = (var_name_tmp__662 & 8355711);
  var_name_tmp__663 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field13));
  var_name_tmp__661 = (var_name_tmp__663 & 16777023);
  var_name_tmp__664 = var_name_tmp__660;
  var_name_tmp__665 = var_name_tmp__658;
  *((&var_name_tmp__665->field0)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__664 & 4128768), 16))));
  var_name_tmp__666 = var_name_tmp__660;
  var_name_tmp__667 = var_name_tmp__658;
  *((&var_name_tmp__667->field1)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__666 & 32512), 8))));
  var_name_tmp__668 = var_name_tmp__660;
  var_name_tmp__669 = var_name_tmp__658;
  *((&var_name_tmp__669->field2)) = (((uint8_t)(var_name_tmp__668 & 127)));
  var_name_tmp__670 = var_name_tmp__660;
  var_name_tmp__671 = var_name_tmp__658;
  *((&var_name_tmp__671->field3)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__670 & 4194304), 16))));
  var_name_tmp__672 = var_name_tmp__659;
  *((&var_name_tmp__672->field3)) = 0;
  var_name_tmp__673 = var_name_tmp__661;
  var_name_tmp__674 = var_name_tmp__659;
  *((&var_name_tmp__674->field1)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__673 & 7936), 8))));
  var_name_tmp__675 = var_name_tmp__661;
  var_name_tmp__676 = var_name_tmp__659;
  *((&var_name_tmp__676->field2)) = (((uint8_t)(var_name_tmp__675 & 63)));
  var_name_tmp__677 = var_name_tmp__661;
  var_name_tmp__678 = var_name_tmp__659;
  *((&var_name_tmp__678->field0)) = (((uint8_t)(llvm_lshr_u32((var_name_tmp__677 & 57344), 13))));
  var_name_tmp__679 = var_name_tmp__657;
  if ((((var_name_tmp__679 == 0u)&1))) {
    goto var_name_tmp__704;
  } else {
    goto var_name_tmp__705;
  }

var_name_tmp__704:
  var_name_tmp__680 = var_name_tmp__658;
  var_name_tmp__681 = *((&var_name_tmp__680->field0));
  var_name_tmp__682 = RTC_Bcd2ToByte(var_name_tmp__681);
  var_name_tmp__683 = var_name_tmp__658;
  *((&var_name_tmp__683->field0)) = var_name_tmp__682;
  var_name_tmp__684 = var_name_tmp__658;
  var_name_tmp__685 = *((&var_name_tmp__684->field1));
  var_name_tmp__686 = RTC_Bcd2ToByte(var_name_tmp__685);
  var_name_tmp__687 = var_name_tmp__658;
  *((&var_name_tmp__687->field1)) = var_name_tmp__686;
  var_name_tmp__688 = var_name_tmp__658;
  var_name_tmp__689 = *((&var_name_tmp__688->field2));
  var_name_tmp__690 = RTC_Bcd2ToByte(var_name_tmp__689);
  var_name_tmp__691 = var_name_tmp__658;
  *((&var_name_tmp__691->field2)) = var_name_tmp__690;
  var_name_tmp__692 = var_name_tmp__659;
  var_name_tmp__693 = *((&var_name_tmp__692->field1));
  var_name_tmp__694 = RTC_Bcd2ToByte(var_name_tmp__693);
  var_name_tmp__695 = var_name_tmp__659;
  *((&var_name_tmp__695->field1)) = var_name_tmp__694;
  var_name_tmp__696 = var_name_tmp__659;
  var_name_tmp__697 = *((&var_name_tmp__696->field2));
  var_name_tmp__698 = RTC_Bcd2ToByte(var_name_tmp__697);
  var_name_tmp__699 = var_name_tmp__659;
  *((&var_name_tmp__699->field2)) = var_name_tmp__698;
  var_name_tmp__700 = var_name_tmp__659;
  var_name_tmp__701 = *((&var_name_tmp__700->field0));
  var_name_tmp__702 = RTC_Bcd2ToByte(var_name_tmp__701);
  var_name_tmp__703 = var_name_tmp__659;
  *((&var_name_tmp__703->field0)) = var_name_tmp__702;
  goto var_name_tmp__705;

var_name_tmp__705:
  return;
}


uint32_t RTC_GetTimeStampSubSecond(void) {
  uint32_t var_name_tmp__706;

  var_name_tmp__706 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field14));
  return var_name_tmp__706;
}


void RTC_TamperTriggerConfig(uint32_t var_name_tmp__707, uint32_t var_name_tmp__708) {
  uint32_t var_name_tmp__709;    /* Address-exposed local */
  uint32_t var_name_tmp__710;    /* Address-exposed local */
  uint32_t var_name_tmp__711;
  uint32_t var_name_tmp__712;
  uint32_t var_name_tmp__713;
  uint32_t var_name_tmp__714;
  uint32_t var_name_tmp__715;

  var_name_tmp__709 = var_name_tmp__707;
  var_name_tmp__710 = var_name_tmp__708;
  var_name_tmp__711 = var_name_tmp__710;
  if ((((var_name_tmp__711 == 0u)&1))) {
    goto var_name_tmp__716;
  } else {
    goto var_name_tmp__717;
  }

var_name_tmp__716:
  var_name_tmp__712 = var_name_tmp__709;
  var_name_tmp__713 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__713 & (~((var_name_tmp__712 << 1))));
  goto var_name_tmp__718;

var_name_tmp__717:
  var_name_tmp__714 = var_name_tmp__709;
  var_name_tmp__715 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__715 | (var_name_tmp__714 << 1));
  goto var_name_tmp__718;

var_name_tmp__718:
  return;
}


void RTC_TamperCmd(uint32_t var_name_tmp__719, uint32_t var_name_tmp__720) {
  uint32_t var_name_tmp__721;    /* Address-exposed local */
  uint32_t var_name_tmp__722;    /* Address-exposed local */
  uint32_t var_name_tmp__723;
  uint32_t var_name_tmp__724;
  uint32_t var_name_tmp__725;
  uint32_t var_name_tmp__726;
  uint32_t var_name_tmp__727;

  var_name_tmp__721 = var_name_tmp__719;
  var_name_tmp__722 = var_name_tmp__720;
  var_name_tmp__723 = var_name_tmp__722;
  if ((((var_name_tmp__723 != 0u)&1))) {
    goto var_name_tmp__728;
  } else {
    goto var_name_tmp__729;
  }

var_name_tmp__728:
  var_name_tmp__724 = var_name_tmp__721;
  var_name_tmp__725 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__725 | var_name_tmp__724);
  goto var_name_tmp__730;

var_name_tmp__729:
  var_name_tmp__726 = var_name_tmp__721;
  var_name_tmp__727 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__727 & (~(var_name_tmp__726)));
  goto var_name_tmp__730;

var_name_tmp__730:
  return;
}


void RTC_TamperFilterConfig(uint32_t var_name_tmp__731) {
  uint32_t var_name_tmp__732;    /* Address-exposed local */
  uint32_t var_name_tmp__733;
  uint32_t var_name_tmp__734;
  uint32_t var_name_tmp__735;

  var_name_tmp__732 = var_name_tmp__731;
  var_name_tmp__733 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__733 & -6145);
  var_name_tmp__734 = var_name_tmp__732;
  var_name_tmp__735 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__735 | var_name_tmp__734);
}


void RTC_TamperSamplingFreqConfig(uint32_t var_name_tmp__736) {
  uint32_t var_name_tmp__737;    /* Address-exposed local */
  uint32_t var_name_tmp__738;
  uint32_t var_name_tmp__739;
  uint32_t var_name_tmp__740;

  var_name_tmp__737 = var_name_tmp__736;
  var_name_tmp__738 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__738 & -1793);
  var_name_tmp__739 = var_name_tmp__737;
  var_name_tmp__740 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__740 | var_name_tmp__739);
}


void RTC_TamperPinsPrechargeDuration(uint32_t var_name_tmp__741) {
  uint32_t var_name_tmp__742;    /* Address-exposed local */
  uint32_t var_name_tmp__743;
  uint32_t var_name_tmp__744;
  uint32_t var_name_tmp__745;

  var_name_tmp__742 = var_name_tmp__741;
  var_name_tmp__743 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__743 & -24577);
  var_name_tmp__744 = var_name_tmp__742;
  var_name_tmp__745 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__745 | var_name_tmp__744);
}


void RTC_TimeStampOnTamperDetectionCmd(uint32_t var_name_tmp__746) {
  uint32_t var_name_tmp__747;    /* Address-exposed local */
  uint32_t var_name_tmp__748;
  uint32_t var_name_tmp__749;
  uint32_t var_name_tmp__750;

  var_name_tmp__747 = var_name_tmp__746;
  var_name_tmp__748 = var_name_tmp__747;
  if ((((var_name_tmp__748 != 0u)&1))) {
    goto var_name_tmp__751;
  } else {
    goto var_name_tmp__752;
  }

var_name_tmp__751:
  var_name_tmp__749 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__749 | 128);
  goto var_name_tmp__753;

var_name_tmp__752:
  var_name_tmp__750 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__750 & -129);
  goto var_name_tmp__753;

var_name_tmp__753:
  return;
}


void RTC_TamperPullUpCmd(uint32_t var_name_tmp__754) {
  uint32_t var_name_tmp__755;    /* Address-exposed local */
  uint32_t var_name_tmp__756;
  uint32_t var_name_tmp__757;
  uint32_t var_name_tmp__758;

  var_name_tmp__755 = var_name_tmp__754;
  var_name_tmp__756 = var_name_tmp__755;
  if ((((var_name_tmp__756 != 0u)&1))) {
    goto var_name_tmp__759;
  } else {
    goto var_name_tmp__760;
  }

var_name_tmp__759:
  var_name_tmp__757 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__757 & -32769);
  goto var_name_tmp__761;

var_name_tmp__760:
  var_name_tmp__758 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__758 | 32768);
  goto var_name_tmp__761;

var_name_tmp__761:
  return;
}


void RTC_WriteBackupRegister(uint32_t var_name_tmp__762, uint32_t var_name_tmp__763) {
  uint32_t var_name_tmp__764;    /* Address-exposed local */
  uint32_t var_name_tmp__765;    /* Address-exposed local */
  uint32_t var_name_tmp__766;    /* Address-exposed local */
  uint32_t var_name_tmp__767;
  uint32_t var_name_tmp__768;
  uint32_t var_name_tmp__769;
  uint32_t var_name_tmp__770;

  var_name_tmp__764 = var_name_tmp__762;
  var_name_tmp__765 = var_name_tmp__763;
  *(volatile uint32_t*)(&var_name_tmp__766) = 0;
  *(volatile uint32_t*)(&var_name_tmp__766) = 1073752144u;
  var_name_tmp__767 = var_name_tmp__764;
  var_name_tmp__768 = *(volatile uint32_t*)(&var_name_tmp__766);
  *(volatile uint32_t*)(&var_name_tmp__766) = (llvm_add_u32(var_name_tmp__768, (llvm_mul_u32(var_name_tmp__767, 4))));
  var_name_tmp__769 = var_name_tmp__765;
  var_name_tmp__770 = *(volatile uint32_t*)(&var_name_tmp__766);
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__770)))) = var_name_tmp__769;
}


uint32_t RTC_ReadBackupRegister(uint32_t var_name_tmp__771) {
  uint32_t var_name_tmp__772;    /* Address-exposed local */
  uint32_t var_name_tmp__773;    /* Address-exposed local */
  uint32_t var_name_tmp__774;
  uint32_t var_name_tmp__775;
  uint32_t var_name_tmp__776;
  uint32_t var_name_tmp__777;

  var_name_tmp__772 = var_name_tmp__771;
  *(volatile uint32_t*)(&var_name_tmp__773) = 0;
  *(volatile uint32_t*)(&var_name_tmp__773) = 1073752144u;
  var_name_tmp__774 = var_name_tmp__772;
  var_name_tmp__775 = *(volatile uint32_t*)(&var_name_tmp__773);
  *(volatile uint32_t*)(&var_name_tmp__773) = (llvm_add_u32(var_name_tmp__775, (llvm_mul_u32(var_name_tmp__774, 4))));
  var_name_tmp__776 = *(volatile uint32_t*)(&var_name_tmp__773);
  var_name_tmp__777 = *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__776))));
  return var_name_tmp__777;
}


void RTC_TamperPinSelection(uint32_t var_name_tmp__778) {
  uint32_t var_name_tmp__779;    /* Address-exposed local */
  uint32_t var_name_tmp__780;
  uint32_t var_name_tmp__781;
  uint32_t var_name_tmp__782;

  var_name_tmp__779 = var_name_tmp__778;
  var_name_tmp__780 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__780 & -65537);
  var_name_tmp__781 = var_name_tmp__779;
  var_name_tmp__782 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__782 | var_name_tmp__781);
}


void RTC_TimeStampPinSelection(uint32_t var_name_tmp__783) {
  uint32_t var_name_tmp__784;    /* Address-exposed local */
  uint32_t var_name_tmp__785;
  uint32_t var_name_tmp__786;
  uint32_t var_name_tmp__787;

  var_name_tmp__784 = var_name_tmp__783;
  var_name_tmp__785 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__785 & -131073);
  var_name_tmp__786 = var_name_tmp__784;
  var_name_tmp__787 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__787 | var_name_tmp__786);
}


void RTC_OutputTypeConfig(uint32_t var_name_tmp__788) {
  uint32_t var_name_tmp__789;    /* Address-exposed local */
  uint32_t var_name_tmp__790;
  uint32_t var_name_tmp__791;
  uint32_t var_name_tmp__792;

  var_name_tmp__789 = var_name_tmp__788;
  var_name_tmp__790 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__790 & -262145);
  var_name_tmp__791 = var_name_tmp__789;
  var_name_tmp__792 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__792 | var_name_tmp__791);
}


uint32_t RTC_SynchroShiftConfig(uint32_t var_name_tmp__793, uint32_t var_name_tmp__794) {
  uint32_t var_name_tmp__795;    /* Address-exposed local */
  uint32_t var_name_tmp__796;    /* Address-exposed local */
  uint32_t var_name_tmp__797;    /* Address-exposed local */
  uint32_t var_name_tmp__798;    /* Address-exposed local */
  uint32_t var_name_tmp__799;
  uint32_t var_name_tmp__800;
  uint32_t var_name_tmp__801;
  bool var_name_tmp__802;
  bool var_name_tmp__802__PHI_TEMPORARY;
  uint32_t var_name_tmp__803;
  uint32_t var_name_tmp__804;
  uint32_t var_name_tmp__805;
  uint32_t var_name_tmp__806;
  uint32_t var_name_tmp__807;
  uint32_t var_name_tmp__808;
  uint32_t var_name_tmp__809;

  var_name_tmp__795 = var_name_tmp__793;
  var_name_tmp__796 = var_name_tmp__794;
  var_name_tmp__797 = 0;
  var_name_tmp__798 = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__799 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__799 & 8) != 0u)&1))) {
    goto var_name_tmp__810;
  } else {
    goto var_name_tmp__811;
  }

var_name_tmp__810:
  goto var_name_tmp__812;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__812:
  var_name_tmp__800 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__800 & 8) != 0u)&1))) {
    goto var_name_tmp__813;
  } else {
    var_name_tmp__802__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__814;
  }

var_name_tmp__813:
  var_name_tmp__801 = var_name_tmp__798;
  var_name_tmp__802__PHI_TEMPORARY = (((var_name_tmp__801 != 4096u)&1));   /* for PHI node */
  goto var_name_tmp__814;

var_name_tmp__814:
  var_name_tmp__802 = ((var_name_tmp__802__PHI_TEMPORARY)&1);
  if (var_name_tmp__802) {
    goto var_name_tmp__815;
  } else {
    goto var_name_tmp__816;
  }

var_name_tmp__815:
  var_name_tmp__803 = var_name_tmp__798;
  var_name_tmp__798 = (llvm_add_u32(var_name_tmp__803, 1));
  goto var_name_tmp__812;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__816:
  goto var_name_tmp__811;

var_name_tmp__811:
  var_name_tmp__804 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  if (((((var_name_tmp__804 & 8) == 0u)&1))) {
    goto var_name_tmp__817;
  } else {
    goto var_name_tmp__818;
  }

var_name_tmp__817:
  var_name_tmp__805 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  if (((((var_name_tmp__805 & 16) == 0u)&1))) {
    goto var_name_tmp__819;
  } else {
    goto var_name_tmp__820;
  }

var_name_tmp__819:
  var_name_tmp__806 = var_name_tmp__796;
  var_name_tmp__807 = var_name_tmp__795;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field11)) = (var_name_tmp__806 | var_name_tmp__807);
  var_name_tmp__808 = RTC_WaitForSynchro();
  if ((((var_name_tmp__808 == 0u)&1))) {
    goto var_name_tmp__821;
  } else {
    goto var_name_tmp__822;
  }

var_name_tmp__821:
  var_name_tmp__797 = 0;
  goto var_name_tmp__823;

var_name_tmp__822:
  var_name_tmp__797 = 1;
  goto var_name_tmp__823;

var_name_tmp__823:
  goto var_name_tmp__824;

var_name_tmp__820:
  var_name_tmp__797 = 0;
  goto var_name_tmp__824;

var_name_tmp__824:
  goto var_name_tmp__825;

var_name_tmp__818:
  var_name_tmp__797 = 0;
  goto var_name_tmp__825;

var_name_tmp__825:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
  var_name_tmp__809 = var_name_tmp__797;
  return var_name_tmp__809;
}


void RTC_ITConfig(uint32_t var_name_tmp__826, uint32_t var_name_tmp__827) {
  uint32_t var_name_tmp__828;    /* Address-exposed local */
  uint32_t var_name_tmp__829;    /* Address-exposed local */
  uint32_t var_name_tmp__830;
  uint32_t var_name_tmp__831;
  uint32_t var_name_tmp__832;
  uint32_t var_name_tmp__833;
  uint32_t var_name_tmp__834;
  uint32_t var_name_tmp__835;
  uint32_t var_name_tmp__836;
  uint32_t var_name_tmp__837;
  uint32_t var_name_tmp__838;

  var_name_tmp__828 = var_name_tmp__826;
  var_name_tmp__829 = var_name_tmp__827;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 202;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 83;
  var_name_tmp__830 = var_name_tmp__829;
  if ((((var_name_tmp__830 != 0u)&1))) {
    goto var_name_tmp__839;
  } else {
    goto var_name_tmp__840;
  }

var_name_tmp__839:
  var_name_tmp__831 = var_name_tmp__828;
  var_name_tmp__832 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__832 | (var_name_tmp__831 & -5));
  var_name_tmp__833 = var_name_tmp__828;
  var_name_tmp__834 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__834 | (var_name_tmp__833 & 4));
  goto var_name_tmp__841;

var_name_tmp__840:
  var_name_tmp__835 = var_name_tmp__828;
  var_name_tmp__836 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2)) = (var_name_tmp__836 & (~((var_name_tmp__835 & -5))));
  var_name_tmp__837 = var_name_tmp__828;
  var_name_tmp__838 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16)) = (var_name_tmp__838 & (~((var_name_tmp__837 & 4))));
  goto var_name_tmp__841;

var_name_tmp__841:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9)) = 255;
}


uint32_t RTC_GetFlagStatus(uint32_t var_name_tmp__842) {
  uint32_t var_name_tmp__843;    /* Address-exposed local */
  uint32_t var_name_tmp__844;    /* Address-exposed local */
  uint32_t var_name_tmp__845;    /* Address-exposed local */
  uint32_t var_name_tmp__846;
  uint32_t var_name_tmp__847;
  uint32_t var_name_tmp__848;
  uint32_t var_name_tmp__849;

  var_name_tmp__843 = var_name_tmp__842;
  var_name_tmp__844 = 0;
  var_name_tmp__845 = 0;
  var_name_tmp__846 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__845 = (var_name_tmp__846 & 16247);
  var_name_tmp__847 = var_name_tmp__845;
  var_name_tmp__848 = var_name_tmp__843;
  if (((((var_name_tmp__847 & var_name_tmp__848) != 0u)&1))) {
    goto var_name_tmp__850;
  } else {
    goto var_name_tmp__851;
  }

var_name_tmp__850:
  var_name_tmp__844 = 1;
  goto var_name_tmp__852;

var_name_tmp__851:
  var_name_tmp__844 = 0;
  goto var_name_tmp__852;

var_name_tmp__852:
  var_name_tmp__849 = var_name_tmp__844;
  return var_name_tmp__849;
}


void RTC_ClearFlag(uint32_t var_name_tmp__853) {
  uint32_t var_name_tmp__854;    /* Address-exposed local */
  uint32_t var_name_tmp__855;
  uint32_t var_name_tmp__856;

  var_name_tmp__854 = var_name_tmp__853;
  var_name_tmp__855 = var_name_tmp__854;
  var_name_tmp__856 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = ((~(((var_name_tmp__855 | 128) & 65535))) | (var_name_tmp__856 & 128));
}


uint32_t RTC_GetITStatus(uint32_t var_name_tmp__857) {
  uint32_t var_name_tmp__858;    /* Address-exposed local */
  uint32_t var_name_tmp__859;    /* Address-exposed local */
  uint32_t var_name_tmp__860;    /* Address-exposed local */
  uint32_t var_name_tmp__861;    /* Address-exposed local */
  uint32_t var_name_tmp__862;
  uint32_t var_name_tmp__863;
  uint32_t var_name_tmp__864;
  uint32_t var_name_tmp__865;
  uint32_t var_name_tmp__866;
  uint32_t var_name_tmp__867;
  uint32_t var_name_tmp__868;
  uint32_t var_name_tmp__869;
  uint32_t var_name_tmp__870;
  uint32_t var_name_tmp__871;

  var_name_tmp__858 = var_name_tmp__857;
  var_name_tmp__859 = 0;
  var_name_tmp__860 = 0;
  var_name_tmp__861 = 0;
  var_name_tmp__862 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16));
  var_name_tmp__860 = (var_name_tmp__862 & 4);
  var_name_tmp__863 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2));
  var_name_tmp__864 = var_name_tmp__858;
  var_name_tmp__865 = var_name_tmp__860;
  var_name_tmp__866 = var_name_tmp__858;
  var_name_tmp__861 = ((var_name_tmp__863 & var_name_tmp__864) | (var_name_tmp__865 & (llvm_lshr_u32(var_name_tmp__866, 15))));
  var_name_tmp__867 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  var_name_tmp__868 = var_name_tmp__858;
  var_name_tmp__860 = (var_name_tmp__867 & (llvm_lshr_u32(var_name_tmp__868, 4)));
  var_name_tmp__869 = var_name_tmp__861;
  if ((((var_name_tmp__869 != 0u)&1))) {
    goto var_name_tmp__872;
  } else {
    goto var_name_tmp__873;
  }

var_name_tmp__872:
  var_name_tmp__870 = var_name_tmp__860;
  if (((((var_name_tmp__870 & 65535) != 0u)&1))) {
    goto var_name_tmp__874;
  } else {
    goto var_name_tmp__873;
  }

var_name_tmp__874:
  var_name_tmp__859 = 1;
  goto var_name_tmp__875;

var_name_tmp__873:
  var_name_tmp__859 = 0;
  goto var_name_tmp__875;

var_name_tmp__875:
  var_name_tmp__871 = var_name_tmp__859;
  return var_name_tmp__871;
}


void RTC_ClearITPendingBit(uint32_t var_name_tmp__876) {
  uint32_t var_name_tmp__877;    /* Address-exposed local */
  uint32_t var_name_tmp__878;    /* Address-exposed local */
  uint32_t var_name_tmp__879;
  uint32_t var_name_tmp__880;
  uint32_t var_name_tmp__881;

  var_name_tmp__877 = var_name_tmp__876;
  var_name_tmp__878 = 0;
  var_name_tmp__879 = var_name_tmp__877;
  var_name_tmp__878 = (llvm_lshr_u32(var_name_tmp__879, 4));
  var_name_tmp__880 = var_name_tmp__878;
  var_name_tmp__881 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3)) = ((~(((var_name_tmp__880 | 128) & 65535))) | (var_name_tmp__881 & 128));
}

