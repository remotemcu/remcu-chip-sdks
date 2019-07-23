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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


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
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_9;
  uint32_t var_name_tmp__5;
  bool var_name_tmp__6;
  bool var_name_tmp__6__PHI_TEMPORARY;
  uint64_t var_name_load_i32_11;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;

  __adin_store_((((uint8_t*)(&var_name_tmp__1))), UINT64_C(0), 32, 4);
  var_name_tmp__2 = 0;
  var_name_tmp__3 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__4 = RTC_EnterInitMode();
  if ((((var_name_tmp__4 == 0u)&1))) {
    goto var_name_tmp__9;
  } else {
    goto var_name_tmp__10;
  }

var_name_tmp__9:
  var_name_tmp__3 = 0;
  goto var_name_tmp__11;

var_name_tmp__10:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073752064)), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1))), UINT64_C(8449), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & 7))), 32, 4);
  goto var_name_tmp__12;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__12:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__2 = ((((uint32_t)var_name_load_i32_1)) & 4);
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(&var_name_tmp__1))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__1))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_4)), 1)))), 32, 4);
  goto var_name_tmp__13;

var_name_tmp__13:
  var_name_load_i32_9 = __adin_load_((((uint8_t*)(&var_name_tmp__1))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_9)) != 65536u)&1))) {
    goto var_name_tmp__14;
  } else {
    var_name_tmp__6__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__15;
  }

var_name_tmp__14:
  var_name_tmp__5 = var_name_tmp__2;
  var_name_tmp__6__PHI_TEMPORARY = (((var_name_tmp__5 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__15;

var_name_tmp__15:
  var_name_tmp__6 = ((var_name_tmp__6__PHI_TEMPORARY)&1);
  if (var_name_tmp__6) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__16;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__16:
  var_name_load_i32_11 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_11)) & 4) == 0u)&1))) {
    goto var_name_tmp__17;
  } else {
    goto var_name_tmp__18;
  }

var_name_tmp__17:
  var_name_tmp__3 = 0;
  goto var_name_tmp__19;

var_name_tmp__18:
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) & 0))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5))), UINT64_C(65535), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4))), UINT64_C(8323327), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field6))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), UINT64_C(0), 32, 4);
  var_name_tmp__7 = RTC_WaitForSynchro();
  if ((((var_name_tmp__7 == 0u)&1))) {
    goto var_name_tmp__20;
  } else {
    goto var_name_tmp__21;
  }

var_name_tmp__20:
  var_name_tmp__3 = 0;
  goto var_name_tmp__22;

var_name_tmp__21:
  var_name_tmp__3 = 1;
  goto var_name_tmp__22;

var_name_tmp__22:
  goto var_name_tmp__19;

var_name_tmp__19:
  goto var_name_tmp__11;

var_name_tmp__11:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__8 = var_name_tmp__3;
  return var_name_tmp__8;
}


uint32_t RTC_EnterInitMode(void) {
  uint32_t var_name_tmp__23;    /* Address-exposed local */
  uint32_t var_name_tmp__24;    /* Address-exposed local */
  uint32_t var_name_tmp__25;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__26;
  bool var_name_tmp__27;
  bool var_name_tmp__27__PHI_TEMPORARY;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__28;

  __adin_store_((((uint8_t*)(&var_name_tmp__23))), UINT64_C(0), 32, 4);
  var_name_tmp__24 = 0;
  var_name_tmp__25 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 64) == 0u)&1))) {
    goto var_name_tmp__29;
  } else {
    goto var_name_tmp__30;
  }

var_name_tmp__29:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), UINT64_C(4294967295), 32, 4);
  goto var_name_tmp__31;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__31:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__25 = ((((uint32_t)var_name_load_i32_1)) & 64);
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(&var_name_tmp__23))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__23))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_4)), 1)))), 32, 4);
  goto var_name_tmp__32;

var_name_tmp__32:
  var_name_load_i32_8 = __adin_load_((((uint8_t*)(&var_name_tmp__23))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_8)) != 65536u)&1))) {
    goto var_name_tmp__33;
  } else {
    var_name_tmp__27__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__34;
  }

var_name_tmp__33:
  var_name_tmp__26 = var_name_tmp__25;
  var_name_tmp__27__PHI_TEMPORARY = (((var_name_tmp__26 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__34;

var_name_tmp__34:
  var_name_tmp__27 = ((var_name_tmp__27__PHI_TEMPORARY)&1);
  if (var_name_tmp__27) {
    goto var_name_tmp__31;
  } else {
    goto var_name_tmp__35;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__35:
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_10)) & 64) != 0u)&1))) {
    goto var_name_tmp__36;
  } else {
    goto var_name_tmp__37;
  }

var_name_tmp__36:
  var_name_tmp__24 = 1;
  goto var_name_tmp__38;

var_name_tmp__37:
  var_name_tmp__24 = 0;
  goto var_name_tmp__38;

var_name_tmp__38:
  goto var_name_tmp__39;

var_name_tmp__30:
  var_name_tmp__24 = 1;
  goto var_name_tmp__39;

var_name_tmp__39:
  var_name_tmp__28 = var_name_tmp__24;
  return var_name_tmp__28;
}


uint32_t RTC_WaitForSynchro(void) {
  uint32_t var_name_tmp__40;    /* Address-exposed local */
  uint32_t var_name_tmp__41;    /* Address-exposed local */
  uint32_t var_name_tmp__42;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_9;
  uint32_t var_name_tmp__43;
  bool var_name_tmp__44;
  bool var_name_tmp__44__PHI_TEMPORARY;
  uint64_t var_name_load_i32_11;
  uint32_t var_name_tmp__45;

  __adin_store_((((uint8_t*)(&var_name_tmp__40))), UINT64_C(0), 32, 4);
  var_name_tmp__41 = 0;
  var_name_tmp__42 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -161))), 32, 4);
  goto var_name_tmp__46;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__46:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__42 = ((((uint32_t)var_name_load_i32_1)) & 32);
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(&var_name_tmp__40))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__40))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_4)), 1)))), 32, 4);
  goto var_name_tmp__47;

var_name_tmp__47:
  var_name_load_i32_9 = __adin_load_((((uint8_t*)(&var_name_tmp__40))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_9)) != 131072u)&1))) {
    goto var_name_tmp__48;
  } else {
    var_name_tmp__44__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__49;
  }

var_name_tmp__48:
  var_name_tmp__43 = var_name_tmp__42;
  var_name_tmp__44__PHI_TEMPORARY = (((var_name_tmp__43 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__49;

var_name_tmp__49:
  var_name_tmp__44 = ((var_name_tmp__44__PHI_TEMPORARY)&1);
  if (var_name_tmp__44) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__50;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__50:
  var_name_load_i32_11 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_11)) & 32) != 0u)&1))) {
    goto var_name_tmp__51;
  } else {
    goto var_name_tmp__52;
  }

var_name_tmp__51:
  var_name_tmp__41 = 1;
  goto var_name_tmp__53;

var_name_tmp__52:
  var_name_tmp__41 = 0;
  goto var_name_tmp__53;

var_name_tmp__53:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__45 = var_name_tmp__41;
  return var_name_tmp__45;
}


uint32_t RTC_Init(struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__54) {
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__55;    /* Address-exposed local */
  uint32_t var_name_tmp__56;    /* Address-exposed local */
  uint32_t var_name_tmp__57;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__58;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__59;
  uint64_t var_name_load_i32_7;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__60;
  uint64_t var_name_load_i32_11;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__61;

  var_name_tmp__55 = var_name_tmp__54;
  var_name_tmp__56 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__57 = RTC_EnterInitMode();
  if ((((var_name_tmp__57 == 0u)&1))) {
    goto var_name_tmp__62;
  } else {
    goto var_name_tmp__63;
  }

var_name_tmp__62:
  var_name_tmp__56 = 0;
  goto var_name_tmp__64;

var_name_tmp__63:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -65))), 32, 4);
  var_name_tmp__58 = var_name_tmp__55;
  var_name_load_i32_1 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field0)))), 32, 4);
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | (((uint32_t)var_name_load_i32_1))))), 32, 4);
  var_name_tmp__59 = var_name_tmp__55;
  var_name_load_i32_7 = __adin_load_((((uint8_t*)((&var_name_tmp__59->field2)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_7)))), 32, 4);
  var_name_tmp__60 = var_name_tmp__55;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__60->field1)))), 32, 4);
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) | ((((uint32_t)var_name_load_i32_11)) << 16)))), 32, 4);
  RTC_ExitInitMode();
  var_name_tmp__56 = 1;
  goto var_name_tmp__64;

var_name_tmp__64:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__61 = var_name_tmp__56;
  return var_name_tmp__61;
}


void RTC_ExitInitMode(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -129))), 32, 4);
}


void RTC_StructInit(struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__65) {
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__66;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__67;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__68;
  struct l_struct_struct_OC_RTC_InitTypeDef* var_name_tmp__69;

  var_name_tmp__66 = var_name_tmp__65;
  var_name_tmp__67 = var_name_tmp__66;
  __adin_store_((((uint8_t*)((&var_name_tmp__67->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__68 = var_name_tmp__66;
  __adin_store_((((uint8_t*)((&var_name_tmp__68->field1)))), UINT64_C(127), 32, 4);
  var_name_tmp__69 = var_name_tmp__66;
  __adin_store_((((uint8_t*)((&var_name_tmp__69->field2)))), UINT64_C(255), 32, 4);
}


void RTC_WriteProtectionCmd(uint32_t var_name_tmp__70) {
  uint32_t var_name_tmp__71;    /* Address-exposed local */
  uint32_t var_name_tmp__72;

  var_name_tmp__71 = var_name_tmp__70;
  var_name_tmp__72 = var_name_tmp__71;
  if ((((var_name_tmp__72 != 0u)&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  goto var_name_tmp__75;

var_name_tmp__74:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  goto var_name_tmp__75;

var_name_tmp__75:
  return;
}


uint32_t RTC_RefClockCmd(uint32_t var_name_tmp__76) {
  uint32_t var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;    /* Address-exposed local */
  uint32_t var_name_tmp__79;
  uint32_t var_name_tmp__80;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__81;

  var_name_tmp__77 = var_name_tmp__76;
  var_name_tmp__78 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__79 = RTC_EnterInitMode();
  if ((((var_name_tmp__79 == 0u)&1))) {
    goto var_name_tmp__82;
  } else {
    goto var_name_tmp__83;
  }

var_name_tmp__82:
  var_name_tmp__78 = 0;
  goto var_name_tmp__84;

var_name_tmp__83:
  var_name_tmp__80 = var_name_tmp__77;
  if ((((var_name_tmp__80 != 0u)&1))) {
    goto var_name_tmp__85;
  } else {
    goto var_name_tmp__86;
  }

var_name_tmp__85:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 16))), 32, 4);
  goto var_name_tmp__87;

var_name_tmp__86:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -17))), 32, 4);
  goto var_name_tmp__87;

var_name_tmp__87:
  RTC_ExitInitMode();
  var_name_tmp__78 = 1;
  goto var_name_tmp__84;

var_name_tmp__84:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__81 = var_name_tmp__78;
  return var_name_tmp__81;
}


void RTC_BypassShadowCmd(uint32_t var_name_tmp__88) {
  uint32_t var_name_tmp__89;    /* Address-exposed local */
  uint32_t var_name_tmp__90;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__89 = var_name_tmp__88;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__90 = var_name_tmp__89;
  if ((((var_name_tmp__90 != 0u)&1))) {
    goto var_name_tmp__91;
  } else {
    goto var_name_tmp__92;
  }

var_name_tmp__91:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 32))), 32, 4);
  goto var_name_tmp__93;

var_name_tmp__92:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & 223))), 32, 4);
  goto var_name_tmp__93;

var_name_tmp__93:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_SetTime(uint32_t var_name_tmp__94, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__95) {
  uint32_t var_name_tmp__96;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__97;    /* Address-exposed local */
  uint32_t var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__101;
  uint64_t var_name_load_i32_1;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__102;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__103;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__104;
  uint32_t var_name_tmp__105;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__106;
  uint64_t var_name_load_i8_3;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__107;
  uint64_t var_name_load_i8_5;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__108;
  uint64_t var_name_load_i8_7;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__109;
  uint64_t var_name_load_i8_9;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__110;
  uint64_t var_name_load_i8_11;
  uint8_t var_name_tmp__111;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__112;
  uint64_t var_name_load_i8_13;
  uint8_t var_name_tmp__113;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__114;
  uint64_t var_name_load_i8_15;
  uint8_t var_name_tmp__115;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__116;
  uint64_t var_name_load_i8_17;
  uint32_t var_name_tmp__117;
  uint32_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint32_t var_name_tmp__120;

  var_name_tmp__96 = var_name_tmp__94;
  var_name_tmp__97 = var_name_tmp__95;
  var_name_tmp__98 = 0;
  var_name_tmp__99 = 0;
  var_name_tmp__100 = var_name_tmp__96;
  if ((((var_name_tmp__100 == 0u)&1))) {
    goto var_name_tmp__121;
  } else {
    goto var_name_tmp__122;
  }

var_name_tmp__121:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 64) != 0u)&1))) {
    goto var_name_tmp__123;
  } else {
    goto var_name_tmp__124;
  }

var_name_tmp__123:
  goto var_name_tmp__125;

var_name_tmp__124:
  var_name_tmp__101 = var_name_tmp__97;
  __adin_store_(((&var_name_tmp__101->field3)), UINT64_C(0), 8, 1);
  goto var_name_tmp__125;

var_name_tmp__125:
  goto var_name_tmp__126;

var_name_tmp__122:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_1)) & 64) != 0u)&1))) {
    goto var_name_tmp__127;
  } else {
    goto var_name_tmp__128;
  }

var_name_tmp__127:
  var_name_tmp__102 = var_name_tmp__97;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__102->field0)), 8, 1);
  var_name_tmp__103 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__98 = (((uint32_t)(uint8_t)var_name_tmp__103));
  goto var_name_tmp__129;

var_name_tmp__128:
  var_name_tmp__104 = var_name_tmp__97;
  __adin_store_(((&var_name_tmp__104->field3)), UINT64_C(0), 8, 1);
  goto var_name_tmp__129;

var_name_tmp__129:
  goto var_name_tmp__126;

var_name_tmp__126:
  var_name_tmp__105 = var_name_tmp__96;
  if ((((var_name_tmp__105 != 0u)&1))) {
    goto var_name_tmp__130;
  } else {
    goto var_name_tmp__131;
  }

var_name_tmp__130:
  var_name_tmp__106 = var_name_tmp__97;
  var_name_load_i8_3 = __adin_load_(((&var_name_tmp__106->field0)), 8, 1);
  var_name_tmp__107 = var_name_tmp__97;
  var_name_load_i8_5 = __adin_load_(((&var_name_tmp__107->field1)), 8, 1);
  var_name_tmp__108 = var_name_tmp__97;
  var_name_load_i8_7 = __adin_load_(((&var_name_tmp__108->field2)), 8, 1);
  var_name_tmp__109 = var_name_tmp__97;
  var_name_load_i8_9 = __adin_load_(((&var_name_tmp__109->field3)), 8, 1);
  var_name_tmp__98 = (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_3)))) << 16) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_5)))) << 8)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_7))))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_9)))) << 16));
  goto var_name_tmp__132;

var_name_tmp__131:
  var_name_tmp__110 = var_name_tmp__97;
  var_name_load_i8_11 = __adin_load_(((&var_name_tmp__110->field0)), 8, 1);
  var_name_tmp__111 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_11)));
  var_name_tmp__112 = var_name_tmp__97;
  var_name_load_i8_13 = __adin_load_(((&var_name_tmp__112->field1)), 8, 1);
  var_name_tmp__113 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_13)));
  var_name_tmp__114 = var_name_tmp__97;
  var_name_load_i8_15 = __adin_load_(((&var_name_tmp__114->field2)), 8, 1);
  var_name_tmp__115 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_15)));
  var_name_tmp__116 = var_name_tmp__97;
  var_name_load_i8_17 = __adin_load_(((&var_name_tmp__116->field3)), 8, 1);
  var_name_tmp__98 = (((((((uint32_t)(uint8_t)var_name_tmp__111)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__113)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__115))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_17)))) << 16));
  goto var_name_tmp__132;

var_name_tmp__132:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__117 = RTC_EnterInitMode();
  if ((((var_name_tmp__117 == 0u)&1))) {
    goto var_name_tmp__133;
  } else {
    goto var_name_tmp__134;
  }

var_name_tmp__133:
  var_name_tmp__99 = 0;
  goto var_name_tmp__135;

var_name_tmp__134:
  var_name_tmp__118 = var_name_tmp__98;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073752064)), (((uint64_t)(uint32_t)(var_name_tmp__118 & 8355711))), 32, 4);
  RTC_ExitInitMode();
  var_name_tmp__119 = RTC_WaitForSynchro();
  if ((((var_name_tmp__119 == 0u)&1))) {
    goto var_name_tmp__136;
  } else {
    goto var_name_tmp__137;
  }

var_name_tmp__136:
  var_name_tmp__99 = 0;
  goto var_name_tmp__138;

var_name_tmp__137:
  var_name_tmp__99 = 1;
  goto var_name_tmp__138;

var_name_tmp__138:
  goto var_name_tmp__135;

var_name_tmp__135:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__120 = var_name_tmp__99;
  return var_name_tmp__120;
}


static uint8_t RTC_Bcd2ToByte(uint8_t var_name_tmp__139) {
  uint8_t var_name_tmp__140;    /* Address-exposed local */
  uint8_t var_name_tmp__141;    /* Address-exposed local */
  uint8_t var_name_tmp__142;
  uint8_t var_name_tmp__143;
  uint8_t var_name_tmp__144;

  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = 0;
  var_name_tmp__142 = var_name_tmp__140;
  var_name_tmp__141 = (((uint8_t)(llvm_mul_u32((llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__142)) & 240))))), 4)), 10))));
  var_name_tmp__143 = var_name_tmp__141;
  var_name_tmp__144 = var_name_tmp__140;
  return (((uint8_t)(llvm_add_u32((((uint32_t)(uint8_t)var_name_tmp__143)), ((((uint32_t)(uint8_t)var_name_tmp__144)) & 15)))));
}


static uint8_t RTC_ByteToBcd2(uint8_t var_name_tmp__145) {
  uint8_t var_name_tmp__146;    /* Address-exposed local */
  uint8_t var_name_tmp__147;    /* Address-exposed local */
  uint8_t var_name_tmp__148;
  uint8_t var_name_tmp__149;
  uint8_t var_name_tmp__150;
  uint8_t var_name_tmp__151;
  uint8_t var_name_tmp__152;

  var_name_tmp__146 = var_name_tmp__145;
  var_name_tmp__147 = 0;
  goto var_name_tmp__153;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__153:
  var_name_tmp__148 = var_name_tmp__146;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__148))) >= ((int32_t)10u))&1))) {
    goto var_name_tmp__154;
  } else {
    goto var_name_tmp__155;
  }

var_name_tmp__154:
  var_name_tmp__149 = var_name_tmp__147;
  var_name_tmp__147 = (llvm_add_u8(var_name_tmp__149, 1));
  var_name_tmp__150 = var_name_tmp__146;
  var_name_tmp__146 = (((uint8_t)(llvm_sub_u32((((uint32_t)(uint8_t)var_name_tmp__150)), 10))));
  goto var_name_tmp__153;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__155:
  var_name_tmp__151 = var_name_tmp__147;
  var_name_tmp__152 = var_name_tmp__146;
  return (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__151)) << 4))))) | (((uint32_t)(uint8_t)var_name_tmp__152)))));
}


void RTC_TimeStructInit(struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__156) {
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__157;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__158;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__159;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__160;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__161;

  var_name_tmp__157 = var_name_tmp__156;
  var_name_tmp__158 = var_name_tmp__157;
  __adin_store_(((&var_name_tmp__158->field3)), UINT64_C(0), 8, 1);
  var_name_tmp__159 = var_name_tmp__157;
  __adin_store_(((&var_name_tmp__159->field0)), UINT64_C(0), 8, 1);
  var_name_tmp__160 = var_name_tmp__157;
  __adin_store_(((&var_name_tmp__160->field1)), UINT64_C(0), 8, 1);
  var_name_tmp__161 = var_name_tmp__157;
  __adin_store_(((&var_name_tmp__161->field2)), UINT64_C(0), 8, 1);
}


void RTC_GetTime(uint32_t var_name_tmp__162, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__163) {
  uint32_t var_name_tmp__164;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__165;    /* Address-exposed local */
  uint32_t var_name_tmp__166;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__167;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__168;
  uint32_t var_name_tmp__169;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__170;
  uint32_t var_name_tmp__171;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__172;
  uint32_t var_name_tmp__173;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__174;
  uint32_t var_name_tmp__175;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__176;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__177;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__178;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__179;
  uint64_t var_name_load_i8_5;
  uint8_t var_name_tmp__180;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__181;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__182;
  uint64_t var_name_load_i8_8;
  uint8_t var_name_tmp__183;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__184;

  var_name_tmp__164 = var_name_tmp__162;
  var_name_tmp__165 = var_name_tmp__163;
  var_name_tmp__166 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073752064)), 32, 4);
  var_name_tmp__166 = ((((uint32_t)var_name_load_i32_)) & 8355711);
  var_name_tmp__167 = var_name_tmp__166;
  var_name_tmp__168 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__168->field0)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__167 & 4128768), 16)))))), 8, 1);
  var_name_tmp__169 = var_name_tmp__166;
  var_name_tmp__170 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__170->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__169 & 32512), 8)))))), 8, 1);
  var_name_tmp__171 = var_name_tmp__166;
  var_name_tmp__172 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__172->field2)), (((uint64_t)(uint8_t)(((uint8_t)(var_name_tmp__171 & 127))))), 8, 1);
  var_name_tmp__173 = var_name_tmp__166;
  var_name_tmp__174 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__174->field3)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__173 & 4194304), 16)))))), 8, 1);
  var_name_tmp__175 = var_name_tmp__164;
  if ((((var_name_tmp__175 == 0u)&1))) {
    goto var_name_tmp__185;
  } else {
    goto var_name_tmp__186;
  }

var_name_tmp__185:
  var_name_tmp__176 = var_name_tmp__165;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__176->field0)), 8, 1);
  var_name_tmp__177 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__178 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__178->field0)), (((uint64_t)(uint8_t)var_name_tmp__177)), 8, 1);
  var_name_tmp__179 = var_name_tmp__165;
  var_name_load_i8_5 = __adin_load_(((&var_name_tmp__179->field1)), 8, 1);
  var_name_tmp__180 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_5)));
  var_name_tmp__181 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__181->field1)), (((uint64_t)(uint8_t)var_name_tmp__180)), 8, 1);
  var_name_tmp__182 = var_name_tmp__165;
  var_name_load_i8_8 = __adin_load_(((&var_name_tmp__182->field2)), 8, 1);
  var_name_tmp__183 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_8)));
  var_name_tmp__184 = var_name_tmp__165;
  __adin_store_(((&var_name_tmp__184->field2)), (((uint64_t)(uint8_t)var_name_tmp__183)), 8, 1);
  goto var_name_tmp__186;

var_name_tmp__186:
  return;
}


uint32_t RTC_GetSubSecond(void) {
  uint32_t var_name_tmp__187;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_truncated_i32_2;
  uint32_t var_name_tmp__188;

  var_name_tmp__187 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field10))), 32, 4);
  var_name_tmp__187 = (((uint32_t)var_name_load_i32_));
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1))), 32, 4);
  var_name_truncated_i32_2 = ((uint32_t)var_name_load_i32_1);
  var_name_tmp__188 = var_name_tmp__187;
  return var_name_tmp__188;
}


uint32_t RTC_SetDate(uint32_t var_name_tmp__189, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__190) {
  uint32_t var_name_tmp__191;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__192;    /* Address-exposed local */
  uint32_t var_name_tmp__193;    /* Address-exposed local */
  uint32_t var_name_tmp__194;    /* Address-exposed local */
  uint32_t var_name_tmp__195;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__196;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__197;
  uint64_t var_name_load_i8_1;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__198;
  uint32_t var_name_tmp__199;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__200;
  uint64_t var_name_load_i8_3;
  uint8_t var_name_tmp__201;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__202;
  uint64_t var_name_load_i8_5;
  uint8_t var_name_tmp__203;
  uint32_t var_name_tmp__204;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__205;
  uint64_t var_name_load_i8_7;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__206;
  uint64_t var_name_load_i8_9;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__207;
  uint64_t var_name_load_i8_11;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__208;
  uint64_t var_name_load_i8_13;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__209;
  uint64_t var_name_load_i8_15;
  uint8_t var_name_tmp__210;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__211;
  uint64_t var_name_load_i8_17;
  uint8_t var_name_tmp__212;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__213;
  uint64_t var_name_load_i8_19;
  uint8_t var_name_tmp__214;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__215;
  uint64_t var_name_load_i8_21;
  uint32_t var_name_tmp__216;
  uint32_t var_name_tmp__217;
  uint32_t var_name_tmp__218;
  uint32_t var_name_tmp__219;

  var_name_tmp__191 = var_name_tmp__189;
  var_name_tmp__192 = var_name_tmp__190;
  var_name_tmp__193 = 0;
  var_name_tmp__194 = 0;
  var_name_tmp__195 = var_name_tmp__191;
  if ((((var_name_tmp__195 == 0u)&1))) {
    goto var_name_tmp__220;
  } else {
    goto var_name_tmp__221;
  }

var_name_tmp__220:
  var_name_tmp__196 = var_name_tmp__192;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__196->field1)), 8, 1);
  if ((((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) & 16) == 16u)&1))) {
    goto var_name_tmp__222;
  } else {
    goto var_name_tmp__221;
  }

var_name_tmp__222:
  var_name_tmp__197 = var_name_tmp__192;
  var_name_load_i8_1 = __adin_load_(((&var_name_tmp__197->field1)), 8, 1);
  var_name_tmp__198 = var_name_tmp__192;
  __adin_store_(((&var_name_tmp__198->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_add_u32(((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_1)))) & -17), 10)))))), 8, 1);
  goto var_name_tmp__221;

var_name_tmp__221:
  var_name_tmp__199 = var_name_tmp__191;
  if ((((var_name_tmp__199 == 0u)&1))) {
    goto var_name_tmp__223;
  } else {
    goto var_name_tmp__224;
  }

var_name_tmp__223:
  goto var_name_tmp__225;

var_name_tmp__224:
  var_name_tmp__200 = var_name_tmp__192;
  var_name_load_i8_3 = __adin_load_(((&var_name_tmp__200->field1)), 8, 1);
  var_name_tmp__201 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_3)));
  var_name_tmp__193 = (((uint32_t)(uint8_t)var_name_tmp__201));
  var_name_tmp__202 = var_name_tmp__192;
  var_name_load_i8_5 = __adin_load_(((&var_name_tmp__202->field2)), 8, 1);
  var_name_tmp__203 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_5)));
  var_name_tmp__193 = (((uint32_t)(uint8_t)var_name_tmp__203));
  goto var_name_tmp__225;

var_name_tmp__225:
  var_name_tmp__204 = var_name_tmp__191;
  if ((((var_name_tmp__204 != 0u)&1))) {
    goto var_name_tmp__226;
  } else {
    goto var_name_tmp__227;
  }

var_name_tmp__226:
  var_name_tmp__205 = var_name_tmp__192;
  var_name_load_i8_7 = __adin_load_(((&var_name_tmp__205->field3)), 8, 1);
  var_name_tmp__206 = var_name_tmp__192;
  var_name_load_i8_9 = __adin_load_(((&var_name_tmp__206->field1)), 8, 1);
  var_name_tmp__207 = var_name_tmp__192;
  var_name_load_i8_11 = __adin_load_(((&var_name_tmp__207->field2)), 8, 1);
  var_name_tmp__208 = var_name_tmp__192;
  var_name_load_i8_13 = __adin_load_(((&var_name_tmp__208->field0)), 8, 1);
  var_name_tmp__193 = (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_7)))) << 16) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_9)))) << 8)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_11))))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_13)))) << 13));
  goto var_name_tmp__228;

var_name_tmp__227:
  var_name_tmp__209 = var_name_tmp__192;
  var_name_load_i8_15 = __adin_load_(((&var_name_tmp__209->field3)), 8, 1);
  var_name_tmp__210 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_15)));
  var_name_tmp__211 = var_name_tmp__192;
  var_name_load_i8_17 = __adin_load_(((&var_name_tmp__211->field1)), 8, 1);
  var_name_tmp__212 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_17)));
  var_name_tmp__213 = var_name_tmp__192;
  var_name_load_i8_19 = __adin_load_(((&var_name_tmp__213->field2)), 8, 1);
  var_name_tmp__214 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_19)));
  var_name_tmp__215 = var_name_tmp__192;
  var_name_load_i8_21 = __adin_load_(((&var_name_tmp__215->field0)), 8, 1);
  var_name_tmp__193 = (((((((uint32_t)(uint8_t)var_name_tmp__210)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__212)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__214))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_21)))) << 13));
  goto var_name_tmp__228;

var_name_tmp__228:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__216 = RTC_EnterInitMode();
  if ((((var_name_tmp__216 == 0u)&1))) {
    goto var_name_tmp__229;
  } else {
    goto var_name_tmp__230;
  }

var_name_tmp__229:
  var_name_tmp__194 = 0;
  goto var_name_tmp__231;

var_name_tmp__230:
  var_name_tmp__217 = var_name_tmp__193;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1))), (((uint64_t)(uint32_t)(var_name_tmp__217 & 16777023))), 32, 4);
  RTC_ExitInitMode();
  var_name_tmp__218 = RTC_WaitForSynchro();
  if ((((var_name_tmp__218 == 0u)&1))) {
    goto var_name_tmp__232;
  } else {
    goto var_name_tmp__233;
  }

var_name_tmp__232:
  var_name_tmp__194 = 0;
  goto var_name_tmp__234;

var_name_tmp__233:
  var_name_tmp__194 = 1;
  goto var_name_tmp__234;

var_name_tmp__234:
  goto var_name_tmp__231;

var_name_tmp__231:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__219 = var_name_tmp__194;
  return var_name_tmp__219;
}


void RTC_DateStructInit(struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__235) {
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__236;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__237;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__238;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__239;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__240;

  var_name_tmp__236 = var_name_tmp__235;
  var_name_tmp__237 = var_name_tmp__236;
  __adin_store_(((&var_name_tmp__237->field0)), UINT64_C(1), 8, 1);
  var_name_tmp__238 = var_name_tmp__236;
  __adin_store_(((&var_name_tmp__238->field2)), UINT64_C(1), 8, 1);
  var_name_tmp__239 = var_name_tmp__236;
  __adin_store_(((&var_name_tmp__239->field1)), UINT64_C(1), 8, 1);
  var_name_tmp__240 = var_name_tmp__236;
  __adin_store_(((&var_name_tmp__240->field3)), UINT64_C(0), 8, 1);
}


void RTC_GetDate(uint32_t var_name_tmp__241, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__242) {
  uint32_t var_name_tmp__243;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__244;    /* Address-exposed local */
  uint32_t var_name_tmp__245;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__246;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__247;
  uint32_t var_name_tmp__248;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__249;
  uint32_t var_name_tmp__250;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__251;
  uint32_t var_name_tmp__252;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__253;
  uint32_t var_name_tmp__254;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__255;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__256;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__257;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__258;
  uint64_t var_name_load_i8_5;
  uint8_t var_name_tmp__259;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__260;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__261;
  uint64_t var_name_load_i8_8;
  uint8_t var_name_tmp__262;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__263;

  var_name_tmp__243 = var_name_tmp__241;
  var_name_tmp__244 = var_name_tmp__242;
  var_name_tmp__245 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field1))), 32, 4);
  var_name_tmp__245 = ((((uint32_t)var_name_load_i32_)) & 16777023);
  var_name_tmp__246 = var_name_tmp__245;
  var_name_tmp__247 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__247->field3)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__246 & 16711680), 16)))))), 8, 1);
  var_name_tmp__248 = var_name_tmp__245;
  var_name_tmp__249 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__249->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__248 & 7936), 8)))))), 8, 1);
  var_name_tmp__250 = var_name_tmp__245;
  var_name_tmp__251 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__251->field2)), (((uint64_t)(uint8_t)(((uint8_t)(var_name_tmp__250 & 63))))), 8, 1);
  var_name_tmp__252 = var_name_tmp__245;
  var_name_tmp__253 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__253->field0)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__252 & 57344), 13)))))), 8, 1);
  var_name_tmp__254 = var_name_tmp__243;
  if ((((var_name_tmp__254 == 0u)&1))) {
    goto var_name_tmp__264;
  } else {
    goto var_name_tmp__265;
  }

var_name_tmp__264:
  var_name_tmp__255 = var_name_tmp__244;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__255->field3)), 8, 1);
  var_name_tmp__256 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__257 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__257->field3)), (((uint64_t)(uint8_t)var_name_tmp__256)), 8, 1);
  var_name_tmp__258 = var_name_tmp__244;
  var_name_load_i8_5 = __adin_load_(((&var_name_tmp__258->field1)), 8, 1);
  var_name_tmp__259 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_5)));
  var_name_tmp__260 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__260->field1)), (((uint64_t)(uint8_t)var_name_tmp__259)), 8, 1);
  var_name_tmp__261 = var_name_tmp__244;
  var_name_load_i8_8 = __adin_load_(((&var_name_tmp__261->field2)), 8, 1);
  var_name_tmp__262 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_8)));
  var_name_tmp__263 = var_name_tmp__244;
  __adin_store_(((&var_name_tmp__263->field2)), (((uint64_t)(uint8_t)var_name_tmp__262)), 8, 1);
  goto var_name_tmp__265;

var_name_tmp__265:
  return;
}


void RTC_SetAlarm(uint32_t var_name_tmp__266, uint32_t var_name_tmp__267, struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__268) {
  uint32_t var_name_tmp__269;    /* Address-exposed local */
  uint32_t var_name_tmp__270;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__271;    /* Address-exposed local */
  uint32_t var_name_tmp__272;    /* Address-exposed local */
  uint32_t var_name_tmp__273;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__274;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__275;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__276;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__277;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__278;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__279;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__280;
  uint64_t var_name_load_i8_8;
  uint8_t var_name_tmp__281;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__282;
  uint64_t var_name_load_i8_10;
  uint8_t var_name_tmp__283;
  uint32_t var_name_tmp__284;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__285;
  uint64_t var_name_load_i8_12;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__286;
  uint64_t var_name_load_i8_14;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__287;
  uint64_t var_name_load_i8_16;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__288;
  uint64_t var_name_load_i8_18;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__289;
  uint64_t var_name_load_i8_20;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__290;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__291;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__292;
  uint64_t var_name_load_i8_28;
  uint8_t var_name_tmp__293;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__294;
  uint64_t var_name_load_i8_30;
  uint8_t var_name_tmp__295;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__296;
  uint64_t var_name_load_i8_32;
  uint8_t var_name_tmp__297;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__298;
  uint64_t var_name_load_i8_34;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__299;
  uint64_t var_name_load_i8_36;
  uint8_t var_name_tmp__300;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__301;
  uint64_t var_name_load_i32_39;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__302;
  uint64_t var_name_load_i32_42;
  uint32_t var_name_tmp__303;
  uint32_t var_name_tmp__304;
  uint32_t var_name_tmp__305;

  var_name_tmp__269 = var_name_tmp__266;
  var_name_tmp__270 = var_name_tmp__267;
  var_name_tmp__271 = var_name_tmp__268;
  var_name_tmp__272 = 0;
  var_name_tmp__273 = var_name_tmp__269;
  if ((((var_name_tmp__273 == 0u)&1))) {
    goto var_name_tmp__306;
  } else {
    goto var_name_tmp__307;
  }

var_name_tmp__306:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 64) != 0u)&1))) {
    goto var_name_tmp__308;
  } else {
    goto var_name_tmp__309;
  }

var_name_tmp__308:
  goto var_name_tmp__310;

var_name_tmp__309:
  var_name_tmp__274 = var_name_tmp__271;
  __adin_store_(((&((&var_name_tmp__274->field0))->field3)), UINT64_C(0), 8, 1);
  goto var_name_tmp__310;

var_name_tmp__310:
  var_name_tmp__275 = var_name_tmp__271;
  var_name_load_i32_1 = __adin_load_((((uint8_t*)((&var_name_tmp__275->field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_1)) == 0u)&1))) {
    goto var_name_tmp__311;
  } else {
    goto var_name_tmp__312;
  }

var_name_tmp__311:
  goto var_name_tmp__313;

var_name_tmp__312:
  goto var_name_tmp__313;

var_name_tmp__313:
  goto var_name_tmp__314;

var_name_tmp__307:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 64) != 0u)&1))) {
    goto var_name_tmp__315;
  } else {
    goto var_name_tmp__316;
  }

var_name_tmp__315:
  var_name_tmp__276 = var_name_tmp__271;
  var_name_load_i8_ = __adin_load_(((&((&var_name_tmp__276->field0))->field0)), 8, 4);
  var_name_tmp__277 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__272 = (((uint32_t)(uint8_t)var_name_tmp__277));
  goto var_name_tmp__317;

var_name_tmp__316:
  var_name_tmp__278 = var_name_tmp__271;
  __adin_store_(((&((&var_name_tmp__278->field0))->field3)), UINT64_C(0), 8, 1);
  goto var_name_tmp__317;

var_name_tmp__317:
  var_name_tmp__279 = var_name_tmp__271;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__279->field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_6)) == 0u)&1))) {
    goto var_name_tmp__318;
  } else {
    goto var_name_tmp__319;
  }

var_name_tmp__318:
  var_name_tmp__280 = var_name_tmp__271;
  var_name_load_i8_8 = __adin_load_(((&var_name_tmp__280->field3)), 8, 4);
  var_name_tmp__281 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_8)));
  var_name_tmp__272 = (((uint32_t)(uint8_t)var_name_tmp__281));
  goto var_name_tmp__320;

var_name_tmp__319:
  var_name_tmp__282 = var_name_tmp__271;
  var_name_load_i8_10 = __adin_load_(((&var_name_tmp__282->field3)), 8, 4);
  var_name_tmp__283 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_10)));
  var_name_tmp__272 = (((uint32_t)(uint8_t)var_name_tmp__283));
  goto var_name_tmp__320;

var_name_tmp__320:
  goto var_name_tmp__314;

var_name_tmp__314:
  var_name_tmp__284 = var_name_tmp__269;
  if ((((var_name_tmp__284 != 0u)&1))) {
    goto var_name_tmp__321;
  } else {
    goto var_name_tmp__322;
  }

var_name_tmp__321:
  var_name_tmp__285 = var_name_tmp__271;
  var_name_load_i8_12 = __adin_load_(((&((&var_name_tmp__285->field0))->field0)), 8, 4);
  var_name_tmp__286 = var_name_tmp__271;
  var_name_load_i8_14 = __adin_load_(((&((&var_name_tmp__286->field0))->field1)), 8, 1);
  var_name_tmp__287 = var_name_tmp__271;
  var_name_load_i8_16 = __adin_load_(((&((&var_name_tmp__287->field0))->field2)), 8, 2);
  var_name_tmp__288 = var_name_tmp__271;
  var_name_load_i8_18 = __adin_load_(((&((&var_name_tmp__288->field0))->field3)), 8, 1);
  var_name_tmp__289 = var_name_tmp__271;
  var_name_load_i8_20 = __adin_load_(((&var_name_tmp__289->field3)), 8, 4);
  var_name_tmp__290 = var_name_tmp__271;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&var_name_tmp__290->field2)))), 32, 4);
  var_name_tmp__291 = var_name_tmp__271;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__291->field1)))), 32, 4);
  var_name_tmp__272 = ((((((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_12)))) << 16) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_14)))) << 8)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_16))))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_18)))) << 16)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_20)))) << 24)) | (((uint32_t)var_name_load_i32_23))) | (((uint32_t)var_name_load_i32_26)));
  goto var_name_tmp__323;

var_name_tmp__322:
  var_name_tmp__292 = var_name_tmp__271;
  var_name_load_i8_28 = __adin_load_(((&((&var_name_tmp__292->field0))->field0)), 8, 4);
  var_name_tmp__293 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_28)));
  var_name_tmp__294 = var_name_tmp__271;
  var_name_load_i8_30 = __adin_load_(((&((&var_name_tmp__294->field0))->field1)), 8, 1);
  var_name_tmp__295 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_30)));
  var_name_tmp__296 = var_name_tmp__271;
  var_name_load_i8_32 = __adin_load_(((&((&var_name_tmp__296->field0))->field2)), 8, 2);
  var_name_tmp__297 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_32)));
  var_name_tmp__298 = var_name_tmp__271;
  var_name_load_i8_34 = __adin_load_(((&((&var_name_tmp__298->field0))->field3)), 8, 1);
  var_name_tmp__299 = var_name_tmp__271;
  var_name_load_i8_36 = __adin_load_(((&var_name_tmp__299->field3)), 8, 4);
  var_name_tmp__300 = RTC_ByteToBcd2((((uint8_t)var_name_load_i8_36)));
  var_name_tmp__301 = var_name_tmp__271;
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&var_name_tmp__301->field2)))), 32, 4);
  var_name_tmp__302 = var_name_tmp__271;
  var_name_load_i32_42 = __adin_load_((((uint8_t*)((&var_name_tmp__302->field1)))), 32, 4);
  var_name_tmp__272 = ((((((((((uint32_t)(uint8_t)var_name_tmp__293)) << 16) | ((((uint32_t)(uint8_t)var_name_tmp__295)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__297))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_34)))) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__300)) << 24)) | (((uint32_t)var_name_load_i32_39))) | (((uint32_t)var_name_load_i32_42)));
  goto var_name_tmp__323;

var_name_tmp__323:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__303 = var_name_tmp__270;
  if ((((var_name_tmp__303 == 256u)&1))) {
    goto var_name_tmp__324;
  } else {
    goto var_name_tmp__325;
  }

var_name_tmp__324:
  var_name_tmp__304 = var_name_tmp__272;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7))), (((uint64_t)(uint32_t)var_name_tmp__304)), 32, 4);
  goto var_name_tmp__326;

var_name_tmp__325:
  var_name_tmp__305 = var_name_tmp__272;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8))), (((uint64_t)(uint32_t)var_name_tmp__305)), 32, 4);
  goto var_name_tmp__326;

var_name_tmp__326:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


void RTC_AlarmStructInit(struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__327) {
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__328;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__329;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__330;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__331;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__332;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__333;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__334;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__335;

  var_name_tmp__328 = var_name_tmp__327;
  var_name_tmp__329 = var_name_tmp__328;
  __adin_store_(((&((&var_name_tmp__329->field0))->field3)), UINT64_C(0), 8, 1);
  var_name_tmp__330 = var_name_tmp__328;
  __adin_store_(((&((&var_name_tmp__330->field0))->field0)), UINT64_C(0), 8, 4);
  var_name_tmp__331 = var_name_tmp__328;
  __adin_store_(((&((&var_name_tmp__331->field0))->field1)), UINT64_C(0), 8, 1);
  var_name_tmp__332 = var_name_tmp__328;
  __adin_store_(((&((&var_name_tmp__332->field0))->field2)), UINT64_C(0), 8, 2);
  var_name_tmp__333 = var_name_tmp__328;
  __adin_store_((((uint8_t*)((&var_name_tmp__333->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__334 = var_name_tmp__328;
  __adin_store_(((&var_name_tmp__334->field3)), UINT64_C(1), 8, 4);
  var_name_tmp__335 = var_name_tmp__328;
  __adin_store_((((uint8_t*)((&var_name_tmp__335->field1)))), UINT64_C(0), 32, 4);
}


void RTC_GetAlarm(uint32_t var_name_tmp__336, uint32_t var_name_tmp__337, struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__338) {
  uint32_t var_name_tmp__339;    /* Address-exposed local */
  uint32_t var_name_tmp__340;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__341;    /* Address-exposed local */
  uint32_t var_name_tmp__342;    /* Address-exposed local */
  uint32_t var_name_tmp__343;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__344;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__345;
  uint32_t var_name_tmp__346;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__347;
  uint32_t var_name_tmp__348;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__349;
  uint32_t var_name_tmp__350;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__351;
  uint32_t var_name_tmp__352;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__353;
  uint32_t var_name_tmp__354;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__355;
  uint32_t var_name_tmp__356;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__357;
  uint32_t var_name_tmp__358;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__359;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__360;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__361;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__362;
  uint64_t var_name_load_i8_10;
  uint8_t var_name_tmp__363;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__364;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__365;
  uint64_t var_name_load_i8_13;
  uint8_t var_name_tmp__366;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__367;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__368;
  uint64_t var_name_load_i8_16;
  uint8_t var_name_tmp__369;
  struct l_struct_struct_OC_RTC_AlarmTypeDef* var_name_tmp__370;

  var_name_tmp__339 = var_name_tmp__336;
  var_name_tmp__340 = var_name_tmp__337;
  var_name_tmp__341 = var_name_tmp__338;
  var_name_tmp__342 = 0;
  var_name_tmp__343 = var_name_tmp__340;
  if ((((var_name_tmp__343 == 256u)&1))) {
    goto var_name_tmp__371;
  } else {
    goto var_name_tmp__372;
  }

var_name_tmp__371:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field7))), 32, 4);
  var_name_tmp__342 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__373;

var_name_tmp__372:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field8))), 32, 4);
  var_name_tmp__342 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__373;

var_name_tmp__373:
  var_name_tmp__344 = var_name_tmp__342;
  var_name_tmp__345 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__345->field0))->field0)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__344 & 4128768), 16)))))), 8, 4);
  var_name_tmp__346 = var_name_tmp__342;
  var_name_tmp__347 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__347->field0))->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__346 & 32512), 8)))))), 8, 1);
  var_name_tmp__348 = var_name_tmp__342;
  var_name_tmp__349 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__349->field0))->field2)), (((uint64_t)(uint8_t)(((uint8_t)(var_name_tmp__348 & 127))))), 8, 2);
  var_name_tmp__350 = var_name_tmp__342;
  var_name_tmp__351 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__351->field0))->field3)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__350 & 4194304), 16)))))), 8, 1);
  var_name_tmp__352 = var_name_tmp__342;
  var_name_tmp__353 = var_name_tmp__341;
  __adin_store_(((&var_name_tmp__353->field3)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__352 & 1056964608), 24)))))), 8, 4);
  var_name_tmp__354 = var_name_tmp__342;
  var_name_tmp__355 = var_name_tmp__341;
  __adin_store_((((uint8_t*)((&var_name_tmp__355->field2)))), (((uint64_t)(uint32_t)(var_name_tmp__354 & 1073741824u))), 32, 4);
  var_name_tmp__356 = var_name_tmp__342;
  var_name_tmp__357 = var_name_tmp__341;
  __adin_store_((((uint8_t*)((&var_name_tmp__357->field1)))), (((uint64_t)(uint32_t)(var_name_tmp__356 & 2155905152u))), 32, 4);
  var_name_tmp__358 = var_name_tmp__339;
  if ((((var_name_tmp__358 == 0u)&1))) {
    goto var_name_tmp__374;
  } else {
    goto var_name_tmp__375;
  }

var_name_tmp__374:
  var_name_tmp__359 = var_name_tmp__341;
  var_name_load_i8_ = __adin_load_(((&((&var_name_tmp__359->field0))->field0)), 8, 4);
  var_name_tmp__360 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__361 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__361->field0))->field0)), (((uint64_t)(uint8_t)var_name_tmp__360)), 8, 4);
  var_name_tmp__362 = var_name_tmp__341;
  var_name_load_i8_10 = __adin_load_(((&((&var_name_tmp__362->field0))->field1)), 8, 1);
  var_name_tmp__363 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_10)));
  var_name_tmp__364 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__364->field0))->field1)), (((uint64_t)(uint8_t)var_name_tmp__363)), 8, 1);
  var_name_tmp__365 = var_name_tmp__341;
  var_name_load_i8_13 = __adin_load_(((&((&var_name_tmp__365->field0))->field2)), 8, 2);
  var_name_tmp__366 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_13)));
  var_name_tmp__367 = var_name_tmp__341;
  __adin_store_(((&((&var_name_tmp__367->field0))->field2)), (((uint64_t)(uint8_t)var_name_tmp__366)), 8, 2);
  var_name_tmp__368 = var_name_tmp__341;
  var_name_load_i8_16 = __adin_load_(((&var_name_tmp__368->field3)), 8, 4);
  var_name_tmp__369 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_16)));
  var_name_tmp__370 = var_name_tmp__341;
  __adin_store_(((&var_name_tmp__370->field3)), (((uint64_t)(uint8_t)var_name_tmp__369)), 8, 4);
  goto var_name_tmp__375;

var_name_tmp__375:
  return;
}


uint32_t RTC_AlarmCmd(uint32_t var_name_tmp__376, uint32_t var_name_tmp__377) {
  uint32_t var_name_tmp__378;    /* Address-exposed local */
  uint32_t var_name_tmp__379;    /* Address-exposed local */
  uint32_t var_name_tmp__380;    /* Address-exposed local */
  uint32_t var_name_tmp__381;    /* Address-exposed local */
  uint32_t var_name_tmp__382;    /* Address-exposed local */
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__385;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__386;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_12;
  uint32_t var_name_tmp__387;
  bool var_name_tmp__388;
  bool var_name_tmp__388__PHI_TEMPORARY;
  uint64_t var_name_load_i32_14;
  uint32_t var_name_tmp__389;
  uint32_t var_name_tmp__390;

  var_name_tmp__378 = var_name_tmp__376;
  var_name_tmp__379 = var_name_tmp__377;
  __adin_store_((((uint8_t*)(&var_name_tmp__380))), UINT64_C(0), 32, 4);
  var_name_tmp__381 = 0;
  var_name_tmp__382 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__383 = var_name_tmp__379;
  if ((((var_name_tmp__383 != 0u)&1))) {
    goto var_name_tmp__391;
  } else {
    goto var_name_tmp__392;
  }

var_name_tmp__391:
  var_name_tmp__384 = var_name_tmp__378;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__384))), 32, 4);
  var_name_tmp__382 = 1;
  goto var_name_tmp__393;

var_name_tmp__392:
  var_name_tmp__385 = var_name_tmp__378;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__385))))), 32, 4);
  goto var_name_tmp__394;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__394:
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__386 = var_name_tmp__378;
  var_name_tmp__381 = ((((uint32_t)var_name_load_i32_4)) & (llvm_lshr_u32(var_name_tmp__386, 8)));
  var_name_load_i32_7 = __adin_load_((((uint8_t*)(&var_name_tmp__380))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__380))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_7)), 1)))), 32, 4);
  goto var_name_tmp__395;

var_name_tmp__395:
  var_name_load_i32_12 = __adin_load_((((uint8_t*)(&var_name_tmp__380))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_12)) != 65536u)&1))) {
    goto var_name_tmp__396;
  } else {
    var_name_tmp__388__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__397;
  }

var_name_tmp__396:
  var_name_tmp__387 = var_name_tmp__381;
  var_name_tmp__388__PHI_TEMPORARY = (((var_name_tmp__387 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__397;

var_name_tmp__397:
  var_name_tmp__388 = ((var_name_tmp__388__PHI_TEMPORARY)&1);
  if (var_name_tmp__388) {
    goto var_name_tmp__394;
  } else {
    goto var_name_tmp__398;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__398:
  var_name_load_i32_14 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__389 = var_name_tmp__378;
  if ((((((((uint32_t)var_name_load_i32_14)) & (llvm_lshr_u32(var_name_tmp__389, 8))) == 0u)&1))) {
    goto var_name_tmp__399;
  } else {
    goto var_name_tmp__400;
  }

var_name_tmp__399:
  var_name_tmp__382 = 0;
  goto var_name_tmp__401;

var_name_tmp__400:
  var_name_tmp__382 = 1;
  goto var_name_tmp__401;

var_name_tmp__401:
  goto var_name_tmp__393;

var_name_tmp__393:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__390 = var_name_tmp__382;
  return var_name_tmp__390;
}


void RTC_AlarmSubSecondConfig(uint32_t var_name_tmp__402, uint32_t var_name_tmp__403, uint32_t var_name_tmp__404) {
  uint32_t var_name_tmp__405;    /* Address-exposed local */
  uint32_t var_name_tmp__406;    /* Address-exposed local */
  uint32_t var_name_tmp__407;    /* Address-exposed local */
  uint32_t var_name_tmp__408;    /* Address-exposed local */
  uint32_t var_name_tmp__409;
  uint32_t var_name_tmp__410;
  uint32_t var_name_tmp__411;
  uint32_t var_name_tmp__412;
  uint32_t var_name_tmp__413;

  var_name_tmp__405 = var_name_tmp__402;
  var_name_tmp__406 = var_name_tmp__403;
  var_name_tmp__407 = var_name_tmp__404;
  var_name_tmp__408 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__409 = var_name_tmp__406;
  var_name_tmp__410 = var_name_tmp__407;
  var_name_tmp__408 = (var_name_tmp__409 | var_name_tmp__410);
  var_name_tmp__411 = var_name_tmp__405;
  if ((((var_name_tmp__411 == 256u)&1))) {
    goto var_name_tmp__414;
  } else {
    goto var_name_tmp__415;
  }

var_name_tmp__414:
  var_name_tmp__412 = var_name_tmp__408;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field17))), (((uint64_t)(uint32_t)var_name_tmp__412)), 32, 4);
  goto var_name_tmp__416;

var_name_tmp__415:
  var_name_tmp__413 = var_name_tmp__408;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field18))), (((uint64_t)(uint32_t)var_name_tmp__413)), 32, 4);
  goto var_name_tmp__416;

var_name_tmp__416:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_GetAlarmSubSecond(uint32_t var_name_tmp__417) {
  uint32_t var_name_tmp__418;    /* Address-exposed local */
  uint32_t var_name_tmp__419;    /* Address-exposed local */
  uint32_t var_name_tmp__420;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__421;

  var_name_tmp__418 = var_name_tmp__417;
  var_name_tmp__419 = 0;
  var_name_tmp__420 = var_name_tmp__418;
  if ((((var_name_tmp__420 == 256u)&1))) {
    goto var_name_tmp__422;
  } else {
    goto var_name_tmp__423;
  }

var_name_tmp__422:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field17))), 32, 4);
  var_name_tmp__419 = ((((uint32_t)var_name_load_i32_)) & 32767);
  goto var_name_tmp__424;

var_name_tmp__423:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field18))), 32, 4);
  var_name_tmp__419 = ((((uint32_t)var_name_load_i32_1)) & 32767);
  goto var_name_tmp__424;

var_name_tmp__424:
  var_name_tmp__421 = var_name_tmp__419;
  return var_name_tmp__421;
}


void RTC_WakeUpClockConfig(uint32_t var_name_tmp__425) {
  uint32_t var_name_tmp__426;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__427;
  uint64_t var_name_load_i32_1;

  var_name_tmp__426 = var_name_tmp__425;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -8))), 32, 4);
  var_name_tmp__427 = var_name_tmp__426;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__427))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


void RTC_SetWakeUpCounter(uint32_t var_name_tmp__428) {
  uint32_t var_name_tmp__429;    /* Address-exposed local */
  uint32_t var_name_tmp__430;

  var_name_tmp__429 = var_name_tmp__428;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__430 = var_name_tmp__429;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5))), (((uint64_t)(uint32_t)var_name_tmp__430)), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_GetWakeUpCounter(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field5))), 32, 4);
  return ((((uint32_t)var_name_load_i32_)) & 65535);
}


uint32_t RTC_WakeUpCmd(uint32_t var_name_tmp__431) {
  uint32_t var_name_tmp__432;    /* Address-exposed local */
  uint32_t var_name_tmp__433;    /* Address-exposed local */
  uint32_t var_name_tmp__434;    /* Address-exposed local */
  uint32_t var_name_tmp__435;    /* Address-exposed local */
  uint32_t var_name_tmp__436;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_12;
  uint32_t var_name_tmp__437;
  bool var_name_tmp__438;
  bool var_name_tmp__438__PHI_TEMPORARY;
  uint64_t var_name_load_i32_14;
  uint32_t var_name_tmp__439;

  var_name_tmp__432 = var_name_tmp__431;
  __adin_store_((((uint8_t*)(&var_name_tmp__433))), UINT64_C(0), 32, 4);
  var_name_tmp__434 = 0;
  var_name_tmp__435 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__436 = var_name_tmp__432;
  if ((((var_name_tmp__436 != 0u)&1))) {
    goto var_name_tmp__440;
  } else {
    goto var_name_tmp__441;
  }

var_name_tmp__440:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1024))), 32, 4);
  var_name_tmp__435 = 1;
  goto var_name_tmp__442;

var_name_tmp__441:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -1025))), 32, 4);
  goto var_name_tmp__443;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__443:
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__434 = ((((uint32_t)var_name_load_i32_4)) & 4);
  var_name_load_i32_7 = __adin_load_((((uint8_t*)(&var_name_tmp__433))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__433))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_7)), 1)))), 32, 4);
  goto var_name_tmp__444;

var_name_tmp__444:
  var_name_load_i32_12 = __adin_load_((((uint8_t*)(&var_name_tmp__433))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_12)) != 65536u)&1))) {
    goto var_name_tmp__445;
  } else {
    var_name_tmp__438__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__446;
  }

var_name_tmp__445:
  var_name_tmp__437 = var_name_tmp__434;
  var_name_tmp__438__PHI_TEMPORARY = (((var_name_tmp__437 == 0u)&1));   /* for PHI node */
  goto var_name_tmp__446;

var_name_tmp__446:
  var_name_tmp__438 = ((var_name_tmp__438__PHI_TEMPORARY)&1);
  if (var_name_tmp__438) {
    goto var_name_tmp__443;
  } else {
    goto var_name_tmp__447;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__447:
  var_name_load_i32_14 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_14)) & 4) == 0u)&1))) {
    goto var_name_tmp__448;
  } else {
    goto var_name_tmp__449;
  }

var_name_tmp__448:
  var_name_tmp__435 = 0;
  goto var_name_tmp__450;

var_name_tmp__449:
  var_name_tmp__435 = 1;
  goto var_name_tmp__450;

var_name_tmp__450:
  goto var_name_tmp__442;

var_name_tmp__442:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__439 = var_name_tmp__435;
  return var_name_tmp__439;
}


void RTC_DayLightSavingConfig(uint32_t var_name_tmp__451, uint32_t var_name_tmp__452) {
  uint32_t var_name_tmp__453;    /* Address-exposed local */
  uint32_t var_name_tmp__454;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__455;
  uint32_t var_name_tmp__456;
  uint64_t var_name_load_i32_1;

  var_name_tmp__453 = var_name_tmp__451;
  var_name_tmp__454 = var_name_tmp__452;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -262145))), 32, 4);
  var_name_tmp__455 = var_name_tmp__453;
  var_name_tmp__456 = var_name_tmp__454;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (var_name_tmp__455 | var_name_tmp__456)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_GetStoreOperation(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  return ((((uint32_t)var_name_load_i32_)) & 262144);
}


void RTC_OutputConfig(uint32_t var_name_tmp__457, uint32_t var_name_tmp__458) {
  uint32_t var_name_tmp__459;    /* Address-exposed local */
  uint32_t var_name_tmp__460;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__461;
  uint32_t var_name_tmp__462;
  uint64_t var_name_load_i32_1;

  var_name_tmp__459 = var_name_tmp__457;
  var_name_tmp__460 = var_name_tmp__458;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -7340033))), 32, 4);
  var_name_tmp__461 = var_name_tmp__459;
  var_name_tmp__462 = var_name_tmp__460;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (var_name_tmp__461 | var_name_tmp__462)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_CoarseCalibConfig(uint32_t var_name_tmp__463, uint32_t var_name_tmp__464) {
  uint32_t var_name_tmp__465;    /* Address-exposed local */
  uint32_t var_name_tmp__466;    /* Address-exposed local */
  uint32_t var_name_tmp__467;    /* Address-exposed local */
  uint32_t var_name_tmp__468;
  uint32_t var_name_tmp__469;
  uint32_t var_name_tmp__470;
  uint32_t var_name_tmp__471;

  var_name_tmp__465 = var_name_tmp__463;
  var_name_tmp__466 = var_name_tmp__464;
  var_name_tmp__467 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__468 = RTC_EnterInitMode();
  if ((((var_name_tmp__468 == 0u)&1))) {
    goto var_name_tmp__472;
  } else {
    goto var_name_tmp__473;
  }

var_name_tmp__472:
  var_name_tmp__467 = 0;
  goto var_name_tmp__474;

var_name_tmp__473:
  var_name_tmp__469 = var_name_tmp__465;
  var_name_tmp__470 = var_name_tmp__466;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field6))), (((uint64_t)(uint32_t)(var_name_tmp__469 | var_name_tmp__470))), 32, 4);
  RTC_ExitInitMode();
  var_name_tmp__467 = 1;
  goto var_name_tmp__474;

var_name_tmp__474:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__471 = var_name_tmp__467;
  return var_name_tmp__471;
}


uint32_t RTC_CoarseCalibCmd(uint32_t var_name_tmp__475) {
  uint32_t var_name_tmp__476;    /* Address-exposed local */
  uint32_t var_name_tmp__477;    /* Address-exposed local */
  uint32_t var_name_tmp__478;
  uint32_t var_name_tmp__479;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__480;

  var_name_tmp__476 = var_name_tmp__475;
  var_name_tmp__477 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__478 = RTC_EnterInitMode();
  if ((((var_name_tmp__478 == 0u)&1))) {
    goto var_name_tmp__481;
  } else {
    goto var_name_tmp__482;
  }

var_name_tmp__481:
  var_name_tmp__477 = 0;
  goto var_name_tmp__483;

var_name_tmp__482:
  var_name_tmp__479 = var_name_tmp__476;
  if ((((var_name_tmp__479 != 0u)&1))) {
    goto var_name_tmp__484;
  } else {
    goto var_name_tmp__485;
  }

var_name_tmp__484:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 128))), 32, 4);
  goto var_name_tmp__486;

var_name_tmp__485:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -129))), 32, 4);
  goto var_name_tmp__486;

var_name_tmp__486:
  RTC_ExitInitMode();
  var_name_tmp__477 = 1;
  goto var_name_tmp__483;

var_name_tmp__483:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__480 = var_name_tmp__477;
  return var_name_tmp__480;
}


void RTC_CalibOutputCmd(uint32_t var_name_tmp__487) {
  uint32_t var_name_tmp__488;    /* Address-exposed local */
  uint32_t var_name_tmp__489;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__488 = var_name_tmp__487;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__489 = var_name_tmp__488;
  if ((((var_name_tmp__489 != 0u)&1))) {
    goto var_name_tmp__490;
  } else {
    goto var_name_tmp__491;
  }

var_name_tmp__490:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 8388608))), 32, 4);
  goto var_name_tmp__492;

var_name_tmp__491:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -8388609))), 32, 4);
  goto var_name_tmp__492;

var_name_tmp__492:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


void RTC_CalibOutputConfig(uint32_t var_name_tmp__493) {
  uint32_t var_name_tmp__494;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__495;
  uint64_t var_name_load_i32_1;

  var_name_tmp__494 = var_name_tmp__493;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -524289))), 32, 4);
  var_name_tmp__495 = var_name_tmp__494;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__495))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_SmoothCalibConfig(uint32_t var_name_tmp__496, uint32_t var_name_tmp__497, uint32_t var_name_tmp__498) {
  uint32_t var_name_tmp__499;    /* Address-exposed local */
  uint32_t var_name_tmp__500;    /* Address-exposed local */
  uint32_t var_name_tmp__501;    /* Address-exposed local */
  uint32_t var_name_tmp__502;    /* Address-exposed local */
  uint32_t var_name_tmp__503;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__504;
  bool var_name_tmp__505;
  bool var_name_tmp__505__PHI_TEMPORARY;
  uint32_t var_name_tmp__506;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__507;
  uint32_t var_name_tmp__508;
  uint32_t var_name_tmp__509;
  uint32_t var_name_tmp__510;

  var_name_tmp__499 = var_name_tmp__496;
  var_name_tmp__500 = var_name_tmp__497;
  var_name_tmp__501 = var_name_tmp__498;
  var_name_tmp__502 = 0;
  var_name_tmp__503 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 65536) != 0u)&1))) {
    goto var_name_tmp__511;
  } else {
    goto var_name_tmp__512;
  }

var_name_tmp__511:
  goto var_name_tmp__513;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__513:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_1)) & 65536) != 0u)&1))) {
    goto var_name_tmp__514;
  } else {
    var_name_tmp__505__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__515;
  }

var_name_tmp__514:
  var_name_tmp__504 = var_name_tmp__503;
  var_name_tmp__505__PHI_TEMPORARY = (((var_name_tmp__504 != 131072u)&1));   /* for PHI node */
  goto var_name_tmp__515;

var_name_tmp__515:
  var_name_tmp__505 = ((var_name_tmp__505__PHI_TEMPORARY)&1);
  if (var_name_tmp__505) {
    goto var_name_tmp__516;
  } else {
    goto var_name_tmp__517;
  }

var_name_tmp__516:
  var_name_tmp__506 = var_name_tmp__503;
  var_name_tmp__503 = (llvm_add_u32(var_name_tmp__506, 1));
  goto var_name_tmp__513;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__517:
  goto var_name_tmp__512;

var_name_tmp__512:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 65536) == 0u)&1))) {
    goto var_name_tmp__518;
  } else {
    goto var_name_tmp__519;
  }

var_name_tmp__518:
  var_name_tmp__507 = var_name_tmp__499;
  var_name_tmp__508 = var_name_tmp__500;
  var_name_tmp__509 = var_name_tmp__501;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field15))), (((uint64_t)(uint32_t)((var_name_tmp__507 | var_name_tmp__508) | var_name_tmp__509))), 32, 4);
  var_name_tmp__502 = 1;
  goto var_name_tmp__520;

var_name_tmp__519:
  var_name_tmp__502 = 0;
  goto var_name_tmp__520;

var_name_tmp__520:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__510 = var_name_tmp__502;
  return var_name_tmp__510;
}


void RTC_TimeStampCmd(uint32_t var_name_tmp__521, uint32_t var_name_tmp__522) {
  uint32_t var_name_tmp__523;    /* Address-exposed local */
  uint32_t var_name_tmp__524;    /* Address-exposed local */
  uint32_t var_name_tmp__525;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__526;
  uint32_t var_name_tmp__527;
  uint32_t var_name_tmp__528;
  uint32_t var_name_tmp__529;
  uint32_t var_name_tmp__530;
  uint32_t var_name_tmp__531;

  var_name_tmp__523 = var_name_tmp__521;
  var_name_tmp__524 = var_name_tmp__522;
  var_name_tmp__525 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  var_name_tmp__525 = ((((uint32_t)var_name_load_i32_)) & -2057);
  var_name_tmp__526 = var_name_tmp__524;
  if ((((var_name_tmp__526 != 0u)&1))) {
    goto var_name_tmp__532;
  } else {
    goto var_name_tmp__533;
  }

var_name_tmp__532:
  var_name_tmp__527 = var_name_tmp__523;
  var_name_tmp__528 = var_name_tmp__525;
  var_name_tmp__525 = (var_name_tmp__528 | (var_name_tmp__527 | 2048));
  goto var_name_tmp__534;

var_name_tmp__533:
  var_name_tmp__529 = var_name_tmp__523;
  var_name_tmp__530 = var_name_tmp__525;
  var_name_tmp__525 = (var_name_tmp__530 | var_name_tmp__529);
  goto var_name_tmp__534;

var_name_tmp__534:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__531 = var_name_tmp__525;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)var_name_tmp__531)), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


void RTC_GetTimeStamp(uint32_t var_name_tmp__535, struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__536, struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__537) {
  uint32_t var_name_tmp__538;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__539;    /* Address-exposed local */
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__540;    /* Address-exposed local */
  uint32_t var_name_tmp__541;    /* Address-exposed local */
  uint32_t var_name_tmp__542;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__543;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__544;
  uint32_t var_name_tmp__545;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__546;
  uint32_t var_name_tmp__547;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__548;
  uint32_t var_name_tmp__549;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__550;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__551;
  uint32_t var_name_tmp__552;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__553;
  uint32_t var_name_tmp__554;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__555;
  uint32_t var_name_tmp__556;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__557;
  uint32_t var_name_tmp__558;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__559;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__560;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__561;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__562;
  uint64_t var_name_load_i8_10;
  uint8_t var_name_tmp__563;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__564;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__565;
  uint64_t var_name_load_i8_13;
  uint8_t var_name_tmp__566;
  struct l_struct_struct_OC_RTC_TimeTypeDef* var_name_tmp__567;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__568;
  uint64_t var_name_load_i8_16;
  uint8_t var_name_tmp__569;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__570;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__571;
  uint64_t var_name_load_i8_19;
  uint8_t var_name_tmp__572;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__573;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__574;
  uint64_t var_name_load_i8_22;
  uint8_t var_name_tmp__575;
  struct l_struct_struct_OC_RTC_DateTypeDef* var_name_tmp__576;

  var_name_tmp__538 = var_name_tmp__535;
  var_name_tmp__539 = var_name_tmp__536;
  var_name_tmp__540 = var_name_tmp__537;
  var_name_tmp__541 = 0;
  var_name_tmp__542 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field12))), 32, 4);
  var_name_tmp__541 = ((((uint32_t)var_name_load_i32_)) & 8355711);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field13))), 32, 4);
  var_name_tmp__542 = ((((uint32_t)var_name_load_i32_1)) & 16777023);
  var_name_tmp__543 = var_name_tmp__541;
  var_name_tmp__544 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__544->field0)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__543 & 4128768), 16)))))), 8, 1);
  var_name_tmp__545 = var_name_tmp__541;
  var_name_tmp__546 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__546->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__545 & 32512), 8)))))), 8, 1);
  var_name_tmp__547 = var_name_tmp__541;
  var_name_tmp__548 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__548->field2)), (((uint64_t)(uint8_t)(((uint8_t)(var_name_tmp__547 & 127))))), 8, 1);
  var_name_tmp__549 = var_name_tmp__541;
  var_name_tmp__550 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__550->field3)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__549 & 4194304), 16)))))), 8, 1);
  var_name_tmp__551 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__551->field3)), UINT64_C(0), 8, 1);
  var_name_tmp__552 = var_name_tmp__542;
  var_name_tmp__553 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__553->field1)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__552 & 7936), 8)))))), 8, 1);
  var_name_tmp__554 = var_name_tmp__542;
  var_name_tmp__555 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__555->field2)), (((uint64_t)(uint8_t)(((uint8_t)(var_name_tmp__554 & 63))))), 8, 1);
  var_name_tmp__556 = var_name_tmp__542;
  var_name_tmp__557 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__557->field0)), (((uint64_t)(uint8_t)(((uint8_t)(llvm_lshr_u32((var_name_tmp__556 & 57344), 13)))))), 8, 1);
  var_name_tmp__558 = var_name_tmp__538;
  if ((((var_name_tmp__558 == 0u)&1))) {
    goto var_name_tmp__577;
  } else {
    goto var_name_tmp__578;
  }

var_name_tmp__577:
  var_name_tmp__559 = var_name_tmp__539;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__559->field0)), 8, 1);
  var_name_tmp__560 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_)));
  var_name_tmp__561 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__561->field0)), (((uint64_t)(uint8_t)var_name_tmp__560)), 8, 1);
  var_name_tmp__562 = var_name_tmp__539;
  var_name_load_i8_10 = __adin_load_(((&var_name_tmp__562->field1)), 8, 1);
  var_name_tmp__563 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_10)));
  var_name_tmp__564 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__564->field1)), (((uint64_t)(uint8_t)var_name_tmp__563)), 8, 1);
  var_name_tmp__565 = var_name_tmp__539;
  var_name_load_i8_13 = __adin_load_(((&var_name_tmp__565->field2)), 8, 1);
  var_name_tmp__566 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_13)));
  var_name_tmp__567 = var_name_tmp__539;
  __adin_store_(((&var_name_tmp__567->field2)), (((uint64_t)(uint8_t)var_name_tmp__566)), 8, 1);
  var_name_tmp__568 = var_name_tmp__540;
  var_name_load_i8_16 = __adin_load_(((&var_name_tmp__568->field1)), 8, 1);
  var_name_tmp__569 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_16)));
  var_name_tmp__570 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__570->field1)), (((uint64_t)(uint8_t)var_name_tmp__569)), 8, 1);
  var_name_tmp__571 = var_name_tmp__540;
  var_name_load_i8_19 = __adin_load_(((&var_name_tmp__571->field2)), 8, 1);
  var_name_tmp__572 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_19)));
  var_name_tmp__573 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__573->field2)), (((uint64_t)(uint8_t)var_name_tmp__572)), 8, 1);
  var_name_tmp__574 = var_name_tmp__540;
  var_name_load_i8_22 = __adin_load_(((&var_name_tmp__574->field0)), 8, 1);
  var_name_tmp__575 = RTC_Bcd2ToByte((((uint8_t)var_name_load_i8_22)));
  var_name_tmp__576 = var_name_tmp__540;
  __adin_store_(((&var_name_tmp__576->field0)), (((uint64_t)(uint8_t)var_name_tmp__575)), 8, 1);
  goto var_name_tmp__578;

var_name_tmp__578:
  return;
}


uint32_t RTC_GetTimeStampSubSecond(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field14))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void RTC_TamperTriggerConfig(uint32_t var_name_tmp__579, uint32_t var_name_tmp__580) {
  uint32_t var_name_tmp__581;    /* Address-exposed local */
  uint32_t var_name_tmp__582;    /* Address-exposed local */
  uint32_t var_name_tmp__583;
  uint32_t var_name_tmp__584;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__585;
  uint64_t var_name_load_i32_1;

  var_name_tmp__581 = var_name_tmp__579;
  var_name_tmp__582 = var_name_tmp__580;
  var_name_tmp__583 = var_name_tmp__582;
  if ((((var_name_tmp__583 == 0u)&1))) {
    goto var_name_tmp__586;
  } else {
    goto var_name_tmp__587;
  }

var_name_tmp__586:
  var_name_tmp__584 = var_name_tmp__581;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & (~((var_name_tmp__584 << 1)))))), 32, 4);
  goto var_name_tmp__588;

var_name_tmp__587:
  var_name_tmp__585 = var_name_tmp__581;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (var_name_tmp__585 << 1)))), 32, 4);
  goto var_name_tmp__588;

var_name_tmp__588:
  return;
}


void RTC_TamperCmd(uint32_t var_name_tmp__589, uint32_t var_name_tmp__590) {
  uint32_t var_name_tmp__591;    /* Address-exposed local */
  uint32_t var_name_tmp__592;    /* Address-exposed local */
  uint32_t var_name_tmp__593;
  uint32_t var_name_tmp__594;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__595;
  uint64_t var_name_load_i32_1;

  var_name_tmp__591 = var_name_tmp__589;
  var_name_tmp__592 = var_name_tmp__590;
  var_name_tmp__593 = var_name_tmp__592;
  if ((((var_name_tmp__593 != 0u)&1))) {
    goto var_name_tmp__596;
  } else {
    goto var_name_tmp__597;
  }

var_name_tmp__596:
  var_name_tmp__594 = var_name_tmp__591;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__594))), 32, 4);
  goto var_name_tmp__598;

var_name_tmp__597:
  var_name_tmp__595 = var_name_tmp__591;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__595))))), 32, 4);
  goto var_name_tmp__598;

var_name_tmp__598:
  return;
}


void RTC_TamperFilterConfig(uint32_t var_name_tmp__599) {
  uint32_t var_name_tmp__600;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__601;
  uint64_t var_name_load_i32_1;

  var_name_tmp__600 = var_name_tmp__599;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -6145))), 32, 4);
  var_name_tmp__601 = var_name_tmp__600;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__601))), 32, 4);
}


void RTC_TamperSamplingFreqConfig(uint32_t var_name_tmp__602) {
  uint32_t var_name_tmp__603;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__604;
  uint64_t var_name_load_i32_1;

  var_name_tmp__603 = var_name_tmp__602;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -1793))), 32, 4);
  var_name_tmp__604 = var_name_tmp__603;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__604))), 32, 4);
}


void RTC_TamperPinsPrechargeDuration(uint32_t var_name_tmp__605) {
  uint32_t var_name_tmp__606;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__607;
  uint64_t var_name_load_i32_1;

  var_name_tmp__606 = var_name_tmp__605;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -24577))), 32, 4);
  var_name_tmp__607 = var_name_tmp__606;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__607))), 32, 4);
}


void RTC_TimeStampOnTamperDetectionCmd(uint32_t var_name_tmp__608) {
  uint32_t var_name_tmp__609;    /* Address-exposed local */
  uint32_t var_name_tmp__610;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__609 = var_name_tmp__608;
  var_name_tmp__610 = var_name_tmp__609;
  if ((((var_name_tmp__610 != 0u)&1))) {
    goto var_name_tmp__611;
  } else {
    goto var_name_tmp__612;
  }

var_name_tmp__611:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 128))), 32, 4);
  goto var_name_tmp__613;

var_name_tmp__612:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -129))), 32, 4);
  goto var_name_tmp__613;

var_name_tmp__613:
  return;
}


void RTC_TamperPullUpCmd(uint32_t var_name_tmp__614) {
  uint32_t var_name_tmp__615;    /* Address-exposed local */
  uint32_t var_name_tmp__616;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__615 = var_name_tmp__614;
  var_name_tmp__616 = var_name_tmp__615;
  if ((((var_name_tmp__616 != 0u)&1))) {
    goto var_name_tmp__617;
  } else {
    goto var_name_tmp__618;
  }

var_name_tmp__617:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -32769))), 32, 4);
  goto var_name_tmp__619;

var_name_tmp__618:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 32768))), 32, 4);
  goto var_name_tmp__619;

var_name_tmp__619:
  return;
}


void RTC_WriteBackupRegister(uint32_t var_name_tmp__620, uint32_t var_name_tmp__621) {
  uint32_t var_name_tmp__622;    /* Address-exposed local */
  uint32_t var_name_tmp__623;    /* Address-exposed local */
  uint32_t var_name_tmp__624;    /* Address-exposed local */
  uint32_t var_name_tmp__625;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__626;
  uint64_t var_name_load_i32_5;

  var_name_tmp__622 = var_name_tmp__620;
  var_name_tmp__623 = var_name_tmp__621;
  __adin_store_((((uint8_t*)(&var_name_tmp__624))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__624))), UINT64_C(1073752144), 32, 4);
  var_name_tmp__625 = var_name_tmp__622;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__624))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__624))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (llvm_mul_u32(var_name_tmp__625, 4)))))), 32, 4);
  var_name_tmp__626 = var_name_tmp__623;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)(&var_name_tmp__624))), 32, 4);
  __adin_store_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_5)))))))), (((uint64_t)(uint32_t)var_name_tmp__626)), 32, 4);
}


uint32_t RTC_ReadBackupRegister(uint32_t var_name_tmp__627) {
  uint32_t var_name_tmp__628;    /* Address-exposed local */
  uint32_t var_name_tmp__629;    /* Address-exposed local */
  uint32_t var_name_tmp__630;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_5;
  uint64_t var_name_load_i32_8;

  var_name_tmp__628 = var_name_tmp__627;
  __adin_store_((((uint8_t*)(&var_name_tmp__629))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__629))), UINT64_C(1073752144), 32, 4);
  var_name_tmp__630 = var_name_tmp__628;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__629))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__629))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (llvm_mul_u32(var_name_tmp__630, 4)))))), 32, 4);
  var_name_load_i32_5 = __adin_load_((((uint8_t*)(&var_name_tmp__629))), 32, 4);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_5)))))))), 32, 4);
  return (((uint32_t)var_name_load_i32_8));
}


void RTC_TamperPinSelection(uint32_t var_name_tmp__631) {
  uint32_t var_name_tmp__632;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__633;
  uint64_t var_name_load_i32_1;

  var_name_tmp__632 = var_name_tmp__631;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -65537))), 32, 4);
  var_name_tmp__633 = var_name_tmp__632;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__633))), 32, 4);
}


void RTC_TimeStampPinSelection(uint32_t var_name_tmp__634) {
  uint32_t var_name_tmp__635;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__636;
  uint64_t var_name_load_i32_1;

  var_name_tmp__635 = var_name_tmp__634;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -131073))), 32, 4);
  var_name_tmp__636 = var_name_tmp__635;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__636))), 32, 4);
}


void RTC_OutputTypeConfig(uint32_t var_name_tmp__637) {
  uint32_t var_name_tmp__638;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__639;
  uint64_t var_name_load_i32_1;

  var_name_tmp__638 = var_name_tmp__637;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -262145))), 32, 4);
  var_name_tmp__639 = var_name_tmp__638;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__639))), 32, 4);
}


uint32_t RTC_SynchroShiftConfig(uint32_t var_name_tmp__640, uint32_t var_name_tmp__641) {
  uint32_t var_name_tmp__642;    /* Address-exposed local */
  uint32_t var_name_tmp__643;    /* Address-exposed local */
  uint32_t var_name_tmp__644;    /* Address-exposed local */
  uint32_t var_name_tmp__645;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__646;
  bool var_name_tmp__647;
  bool var_name_tmp__647__PHI_TEMPORARY;
  uint32_t var_name_tmp__648;
  uint64_t var_name_load_i32_3;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__649;
  uint32_t var_name_tmp__650;
  uint32_t var_name_tmp__651;
  uint32_t var_name_tmp__652;

  var_name_tmp__642 = var_name_tmp__640;
  var_name_tmp__643 = var_name_tmp__641;
  var_name_tmp__644 = 0;
  var_name_tmp__645 = 0;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 8) != 0u)&1))) {
    goto var_name_tmp__653;
  } else {
    goto var_name_tmp__654;
  }

var_name_tmp__653:
  goto var_name_tmp__655;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__655:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_1)) & 8) != 0u)&1))) {
    goto var_name_tmp__656;
  } else {
    var_name_tmp__647__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__657;
  }

var_name_tmp__656:
  var_name_tmp__646 = var_name_tmp__645;
  var_name_tmp__647__PHI_TEMPORARY = (((var_name_tmp__646 != 4096u)&1));   /* for PHI node */
  goto var_name_tmp__657;

var_name_tmp__657:
  var_name_tmp__647 = ((var_name_tmp__647__PHI_TEMPORARY)&1);
  if (var_name_tmp__647) {
    goto var_name_tmp__658;
  } else {
    goto var_name_tmp__659;
  }

var_name_tmp__658:
  var_name_tmp__648 = var_name_tmp__645;
  var_name_tmp__645 = (llvm_add_u32(var_name_tmp__648, 1));
  goto var_name_tmp__655;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__659:
  goto var_name_tmp__654;

var_name_tmp__654:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 8) == 0u)&1))) {
    goto var_name_tmp__660;
  } else {
    goto var_name_tmp__661;
  }

var_name_tmp__660:
  var_name_load_i32_5 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_5)) & 16) == 0u)&1))) {
    goto var_name_tmp__662;
  } else {
    goto var_name_tmp__663;
  }

var_name_tmp__662:
  var_name_tmp__649 = var_name_tmp__643;
  var_name_tmp__650 = var_name_tmp__642;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field11))), (((uint64_t)(uint32_t)(var_name_tmp__649 | var_name_tmp__650))), 32, 4);
  var_name_tmp__651 = RTC_WaitForSynchro();
  if ((((var_name_tmp__651 == 0u)&1))) {
    goto var_name_tmp__664;
  } else {
    goto var_name_tmp__665;
  }

var_name_tmp__664:
  var_name_tmp__644 = 0;
  goto var_name_tmp__666;

var_name_tmp__665:
  var_name_tmp__644 = 1;
  goto var_name_tmp__666;

var_name_tmp__666:
  goto var_name_tmp__667;

var_name_tmp__663:
  var_name_tmp__644 = 0;
  goto var_name_tmp__667;

var_name_tmp__667:
  goto var_name_tmp__668;

var_name_tmp__661:
  var_name_tmp__644 = 0;
  goto var_name_tmp__668;

var_name_tmp__668:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
  var_name_tmp__652 = var_name_tmp__644;
  return var_name_tmp__652;
}


void RTC_ITConfig(uint32_t var_name_tmp__669, uint32_t var_name_tmp__670) {
  uint32_t var_name_tmp__671;    /* Address-exposed local */
  uint32_t var_name_tmp__672;    /* Address-exposed local */
  uint32_t var_name_tmp__673;
  uint32_t var_name_tmp__674;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__675;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__676;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__677;
  uint64_t var_name_load_i32_7;

  var_name_tmp__671 = var_name_tmp__669;
  var_name_tmp__672 = var_name_tmp__670;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(202), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(83), 32, 4);
  var_name_tmp__673 = var_name_tmp__672;
  if ((((var_name_tmp__673 != 0u)&1))) {
    goto var_name_tmp__678;
  } else {
    goto var_name_tmp__679;
  }

var_name_tmp__678:
  var_name_tmp__674 = var_name_tmp__671;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (var_name_tmp__674 & -5)))), 32, 4);
  var_name_tmp__675 = var_name_tmp__671;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (var_name_tmp__675 & 4)))), 32, 4);
  goto var_name_tmp__680;

var_name_tmp__679:
  var_name_tmp__676 = var_name_tmp__671;
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & (~((var_name_tmp__676 & -5)))))), 32, 4);
  var_name_tmp__677 = var_name_tmp__671;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & (~((var_name_tmp__677 & 4)))))), 32, 4);
  goto var_name_tmp__680;

var_name_tmp__680:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field9))), UINT64_C(255), 32, 4);
}


uint32_t RTC_GetFlagStatus(uint32_t var_name_tmp__681) {
  uint32_t var_name_tmp__682;    /* Address-exposed local */
  uint32_t var_name_tmp__683;    /* Address-exposed local */
  uint32_t var_name_tmp__684;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__685;
  uint32_t var_name_tmp__686;
  uint32_t var_name_tmp__687;

  var_name_tmp__682 = var_name_tmp__681;
  var_name_tmp__683 = 0;
  var_name_tmp__684 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__684 = ((((uint32_t)var_name_load_i32_)) & 16247);
  var_name_tmp__685 = var_name_tmp__684;
  var_name_tmp__686 = var_name_tmp__682;
  if (((((var_name_tmp__685 & var_name_tmp__686) != 0u)&1))) {
    goto var_name_tmp__688;
  } else {
    goto var_name_tmp__689;
  }

var_name_tmp__688:
  var_name_tmp__683 = 1;
  goto var_name_tmp__690;

var_name_tmp__689:
  var_name_tmp__683 = 0;
  goto var_name_tmp__690;

var_name_tmp__690:
  var_name_tmp__687 = var_name_tmp__683;
  return var_name_tmp__687;
}


void RTC_ClearFlag(uint32_t var_name_tmp__691) {
  uint32_t var_name_tmp__692;    /* Address-exposed local */
  uint32_t var_name_tmp__693;
  uint64_t var_name_load_i32_;

  var_name_tmp__692 = var_name_tmp__691;
  var_name_tmp__693 = var_name_tmp__692;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), (((uint64_t)(uint32_t)((~(((var_name_tmp__693 | 128) & 65535))) | ((((uint32_t)var_name_load_i32_)) & 128)))), 32, 4);
}


uint32_t RTC_GetITStatus(uint32_t var_name_tmp__694) {
  uint32_t var_name_tmp__695;    /* Address-exposed local */
  uint32_t var_name_tmp__696;    /* Address-exposed local */
  uint32_t var_name_tmp__697;    /* Address-exposed local */
  uint32_t var_name_tmp__698;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__699;
  uint32_t var_name_tmp__700;
  uint32_t var_name_tmp__701;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__702;
  uint32_t var_name_tmp__703;
  uint32_t var_name_tmp__704;
  uint32_t var_name_tmp__705;

  var_name_tmp__695 = var_name_tmp__694;
  var_name_tmp__696 = 0;
  var_name_tmp__697 = 0;
  var_name_tmp__698 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field16))), 32, 4);
  var_name_tmp__697 = ((((uint32_t)var_name_load_i32_)) & 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field2))), 32, 4);
  var_name_tmp__699 = var_name_tmp__695;
  var_name_tmp__700 = var_name_tmp__697;
  var_name_tmp__701 = var_name_tmp__695;
  var_name_tmp__698 = (((((uint32_t)var_name_load_i32_1)) & var_name_tmp__699) | (var_name_tmp__700 & (llvm_lshr_u32(var_name_tmp__701, 15))));
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  var_name_tmp__702 = var_name_tmp__695;
  var_name_tmp__697 = ((((uint32_t)var_name_load_i32_3)) & (llvm_lshr_u32(var_name_tmp__702, 4)));
  var_name_tmp__703 = var_name_tmp__698;
  if ((((var_name_tmp__703 != 0u)&1))) {
    goto var_name_tmp__706;
  } else {
    goto var_name_tmp__707;
  }

var_name_tmp__706:
  var_name_tmp__704 = var_name_tmp__697;
  if (((((var_name_tmp__704 & 65535) != 0u)&1))) {
    goto var_name_tmp__708;
  } else {
    goto var_name_tmp__707;
  }

var_name_tmp__708:
  var_name_tmp__696 = 1;
  goto var_name_tmp__709;

var_name_tmp__707:
  var_name_tmp__696 = 0;
  goto var_name_tmp__709;

var_name_tmp__709:
  var_name_tmp__705 = var_name_tmp__696;
  return var_name_tmp__705;
}


void RTC_ClearITPendingBit(uint32_t var_name_tmp__710) {
  uint32_t var_name_tmp__711;    /* Address-exposed local */
  uint32_t var_name_tmp__712;    /* Address-exposed local */
  uint32_t var_name_tmp__713;
  uint32_t var_name_tmp__714;
  uint64_t var_name_load_i32_;

  var_name_tmp__711 = var_name_tmp__710;
  var_name_tmp__712 = 0;
  var_name_tmp__713 = var_name_tmp__711;
  var_name_tmp__712 = (llvm_lshr_u32(var_name_tmp__713, 4));
  var_name_tmp__714 = var_name_tmp__712;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RTC_TypeDef*)(uintptr_t)UINT64_C(1073752064))->field3))), (((uint64_t)(uint32_t)((~(((var_name_tmp__714 | 128) & 65535))) | ((((uint32_t)var_name_load_i32_)) & 128)))), 32, 4);
}

