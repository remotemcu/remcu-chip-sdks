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
struct l_struct_struct_OC_SDIO_InitTypeDef;
struct l_struct_struct_OC_SDIO_TypeDef;
struct l_struct_struct_OC_SDIO_CmdInitTypeDef;
struct l_struct_struct_OC_SDIO_DataInitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_SDIO_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint8_t field5;
};
struct l_array_2_uint32_t {
  uint32_t array[2];
};
struct l_array_13_uint32_t {
  uint32_t array[13];
};
struct l_struct_struct_OC_SDIO_TypeDef {
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
  struct l_array_2_uint32_t field16;
  uint32_t field17;
  struct l_array_13_uint32_t field18;
  uint32_t field19;
};
struct l_struct_struct_OC_SDIO_CmdInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
};
struct l_struct_struct_OC_SDIO_DataInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};

/* Function Declarations */
void SDIO_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void SDIO_Init(struct l_struct_struct_OC_SDIO_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_StructInit(struct l_struct_struct_OC_SDIO_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_ClockCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SetPowerState(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetPowerState(void) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SendCommand(struct l_struct_struct_OC_SDIO_CmdInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_CmdStructInit(struct l_struct_struct_OC_SDIO_CmdInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t SDIO_GetCommandResponse(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetResponse(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_DataConfig(struct l_struct_struct_OC_SDIO_DataInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_DataStructInit(struct l_struct_struct_OC_SDIO_DataInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetDataCounter(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_ReadData(void) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_WriteData(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetFIFOCount(void) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_StartSDIOReadWait(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_StopSDIOReadWait(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SetSDIOReadWaitMode(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SetSDIOOperation(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SendSDIOSuspendCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_CommandCompletionCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_CEATAITCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_SendCEATACmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_DMACmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_ITConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetFlagStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_ClearFlag(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SDIO_GetITStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SDIO_ClearITPendingBit(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}


/* Function Bodies */

void SDIO_DeInit(void) {
  RCC_APB2PeriphResetCmd(2048, 1);
  RCC_APB2PeriphResetCmd(2048, 0);
}


void SDIO_Init(struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__4;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__5;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__6;
  uint64_t var_name_load_i32_1;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__7;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__8;
  uint64_t var_name_load_i32_7;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__9;
  uint64_t var_name_load_i32_10;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__10;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__11;
  uint32_t var_name_tmp__12;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field1))), 32, 4);
  var_name_tmp__3 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__4 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__4 & -32512);
  var_name_tmp__5 = var_name_tmp__2;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__5->field5)), 8, 4);
  var_name_tmp__6 = var_name_tmp__2;
  var_name_load_i32_1 = __adin_load_((((uint8_t*)((&var_name_tmp__6->field2)))), 32, 4);
  var_name_tmp__7 = var_name_tmp__2;
  var_name_load_i32_4 = __adin_load_((((uint8_t*)((&var_name_tmp__7->field1)))), 32, 4);
  var_name_tmp__8 = var_name_tmp__2;
  var_name_load_i32_7 = __adin_load_((((uint8_t*)((&var_name_tmp__8->field3)))), 32, 4);
  var_name_tmp__9 = var_name_tmp__2;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__9->field0)))), 32, 4);
  var_name_tmp__10 = var_name_tmp__2;
  var_name_load_i32_13 = __adin_load_((((uint8_t*)((&var_name_tmp__10->field4)))), 32, 4);
  var_name_tmp__11 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__11 | ((((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) | (((uint32_t)var_name_load_i32_1))) | (((uint32_t)var_name_load_i32_4))) | (((uint32_t)var_name_load_i32_7))) | (((uint32_t)var_name_load_i32_10))) | (((uint32_t)var_name_load_i32_13))));
  var_name_tmp__12 = var_name_tmp__3;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field1))), (((uint64_t)(uint32_t)var_name_tmp__12)), 32, 4);
}


void SDIO_StructInit(struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__13) {
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__14;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__15;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__16;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__17;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__18;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__19;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__20;

  var_name_tmp__14 = var_name_tmp__13;
  var_name_tmp__15 = var_name_tmp__14;
  __adin_store_(((&var_name_tmp__15->field5)), UINT64_C(0), 8, 4);
  var_name_tmp__16 = var_name_tmp__14;
  __adin_store_((((uint8_t*)((&var_name_tmp__16->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__17 = var_name_tmp__14;
  __adin_store_((((uint8_t*)((&var_name_tmp__17->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__18 = var_name_tmp__14;
  __adin_store_((((uint8_t*)((&var_name_tmp__18->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__19 = var_name_tmp__14;
  __adin_store_((((uint8_t*)((&var_name_tmp__19->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__20 = var_name_tmp__14;
  __adin_store_((((uint8_t*)((&var_name_tmp__20->field4)))), UINT64_C(0), 32, 4);
}


void SDIO_ClockCmd(uint32_t var_name_tmp__21) {
  uint32_t var_name_tmp__22;    /* Address-exposed local */
  uint32_t var_name_tmp__23;

  var_name_tmp__22 = var_name_tmp__21;
  var_name_tmp__23 = var_name_tmp__22;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109754016)), (((uint64_t)(uint32_t)var_name_tmp__23)), 32, 4);
}


void SDIO_SetPowerState(uint32_t var_name_tmp__24) {
  uint32_t var_name_tmp__25;    /* Address-exposed local */
  uint32_t var_name_tmp__26;

  var_name_tmp__25 = var_name_tmp__24;
  var_name_tmp__26 = var_name_tmp__25;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073818624)), (((uint64_t)(uint32_t)var_name_tmp__26)), 32, 4);
}


uint32_t SDIO_GetPowerState(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073818624)), 32, 4);
  return ((((uint32_t)var_name_load_i32_)) & 3);
}


void SDIO_SendCommand(struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__27) {
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__28;    /* Address-exposed local */
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__30;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__31;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__32;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__33;
  uint64_t var_name_load_i32_7;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__34;
  uint64_t var_name_load_i32_10;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__35;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__36;
  uint32_t var_name_tmp__37;

  var_name_tmp__28 = var_name_tmp__27;
  var_name_tmp__29 = 0;
  var_name_tmp__30 = var_name_tmp__28;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__30->field0)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field2))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field3))), 32, 4);
  var_name_tmp__29 = (((uint32_t)var_name_load_i32_1));
  var_name_tmp__31 = var_name_tmp__29;
  var_name_tmp__29 = (var_name_tmp__31 & -2048);
  var_name_tmp__32 = var_name_tmp__28;
  var_name_load_i32_4 = __adin_load_((((uint8_t*)((&var_name_tmp__32->field1)))), 32, 4);
  var_name_tmp__33 = var_name_tmp__28;
  var_name_load_i32_7 = __adin_load_((((uint8_t*)((&var_name_tmp__33->field2)))), 32, 4);
  var_name_tmp__34 = var_name_tmp__28;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__34->field3)))), 32, 4);
  var_name_tmp__35 = var_name_tmp__28;
  var_name_load_i32_13 = __adin_load_((((uint8_t*)((&var_name_tmp__35->field4)))), 32, 4);
  var_name_tmp__36 = var_name_tmp__29;
  var_name_tmp__29 = (var_name_tmp__36 | ((((((uint32_t)var_name_load_i32_4)) | (((uint32_t)var_name_load_i32_7))) | (((uint32_t)var_name_load_i32_10))) | (((uint32_t)var_name_load_i32_13))));
  var_name_tmp__37 = var_name_tmp__29;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field3))), (((uint64_t)(uint32_t)var_name_tmp__37)), 32, 4);
}


void SDIO_CmdStructInit(struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__38) {
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__39;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__40;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__41;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__42;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__43;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__44;

  var_name_tmp__39 = var_name_tmp__38;
  var_name_tmp__40 = var_name_tmp__39;
  __adin_store_((((uint8_t*)((&var_name_tmp__40->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__41 = var_name_tmp__39;
  __adin_store_((((uint8_t*)((&var_name_tmp__41->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__42 = var_name_tmp__39;
  __adin_store_((((uint8_t*)((&var_name_tmp__42->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__43 = var_name_tmp__39;
  __adin_store_((((uint8_t*)((&var_name_tmp__43->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__44 = var_name_tmp__39;
  __adin_store_((((uint8_t*)((&var_name_tmp__44->field4)))), UINT64_C(0), 32, 4);
}


uint8_t SDIO_GetCommandResponse(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field4))), 32, 4);
  return (((uint8_t)(((uint32_t)var_name_load_i32_))));
}


uint32_t SDIO_GetResponse(uint32_t var_name_tmp__45) {
  uint32_t var_name_tmp__46;    /* Address-exposed local */
  uint32_t var_name_tmp__47;    /* Address-exposed local */
  uint32_t var_name_tmp__48;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_4;

  var_name_tmp__46 = var_name_tmp__45;
  __adin_store_((((uint8_t*)(&var_name_tmp__47))), UINT64_C(0), 32, 4);
  var_name_tmp__48 = var_name_tmp__46;
  __adin_store_((((uint8_t*)(&var_name_tmp__47))), (((uint64_t)(uint32_t)(llvm_add_u32(1073818644u, var_name_tmp__48)))), 32, 4);
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__47))), 32, 4);
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))))))), 32, 4);
  return (((uint32_t)var_name_load_i32_4));
}


void SDIO_DataConfig(struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__49) {
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__50;    /* Address-exposed local */
  uint32_t var_name_tmp__51;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__52;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__53;
  uint64_t var_name_load_i32_2;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__54;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__55;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__56;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__57;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__58;
  uint64_t var_name_load_i32_17;
  uint32_t var_name_tmp__59;
  uint32_t var_name_tmp__60;

  var_name_tmp__50 = var_name_tmp__49;
  var_name_tmp__51 = 0;
  var_name_tmp__52 = var_name_tmp__50;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__52->field0)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field9))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__53 = var_name_tmp__50;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__53->field1)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field10))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_2)))), 32, 4);
  var_name_load_i32_5 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field11))), 32, 4);
  var_name_tmp__51 = (((uint32_t)var_name_load_i32_5));
  var_name_tmp__54 = var_name_tmp__51;
  var_name_tmp__51 = (var_name_tmp__54 & -248);
  var_name_tmp__55 = var_name_tmp__50;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__55->field2)))), 32, 4);
  var_name_tmp__56 = var_name_tmp__50;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__56->field3)))), 32, 4);
  var_name_tmp__57 = var_name_tmp__50;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__57->field4)))), 32, 4);
  var_name_tmp__58 = var_name_tmp__50;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field5)))), 32, 4);
  var_name_tmp__59 = var_name_tmp__51;
  var_name_tmp__51 = (var_name_tmp__59 | ((((((uint32_t)var_name_load_i32_8)) | (((uint32_t)var_name_load_i32_11))) | (((uint32_t)var_name_load_i32_14))) | (((uint32_t)var_name_load_i32_17))));
  var_name_tmp__60 = var_name_tmp__51;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field11))), (((uint64_t)(uint32_t)var_name_tmp__60)), 32, 4);
}


void SDIO_DataStructInit(struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__61) {
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__62;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__63;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__64;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__65;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__66;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__67;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__68;

  var_name_tmp__62 = var_name_tmp__61;
  var_name_tmp__63 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__63->field0)))), UINT64_C(4294967295), 32, 4);
  var_name_tmp__64 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__64->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__65 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__65->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__66 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__66->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__67 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__67->field4)))), UINT64_C(0), 32, 4);
  var_name_tmp__68 = var_name_tmp__62;
  __adin_store_((((uint8_t*)((&var_name_tmp__68->field5)))), UINT64_C(0), 32, 4);
}


uint32_t SDIO_GetDataCounter(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field12))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint32_t SDIO_ReadData(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field19))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void SDIO_WriteData(uint32_t var_name_tmp__69) {
  uint32_t var_name_tmp__70;    /* Address-exposed local */
  uint32_t var_name_tmp__71;

  var_name_tmp__70 = var_name_tmp__69;
  var_name_tmp__71 = var_name_tmp__70;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field19))), (((uint64_t)(uint32_t)var_name_tmp__71)), 32, 4);
}


uint32_t SDIO_GetFIFOCount(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field17))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void SDIO_StartSDIOReadWait(uint32_t var_name_tmp__72) {
  uint32_t var_name_tmp__73;    /* Address-exposed local */
  uint32_t var_name_tmp__74;

  var_name_tmp__73 = var_name_tmp__72;
  var_name_tmp__74 = var_name_tmp__73;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109755296)), (((uint64_t)(uint32_t)var_name_tmp__74)), 32, 4);
}


void SDIO_StopSDIOReadWait(uint32_t var_name_tmp__75) {
  uint32_t var_name_tmp__76;    /* Address-exposed local */
  uint32_t var_name_tmp__77;

  var_name_tmp__76 = var_name_tmp__75;
  var_name_tmp__77 = var_name_tmp__76;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109755300)), (((uint64_t)(uint32_t)var_name_tmp__77)), 32, 4);
}


void SDIO_SetSDIOReadWaitMode(uint32_t var_name_tmp__78) {
  uint32_t var_name_tmp__79;    /* Address-exposed local */
  uint32_t var_name_tmp__80;

  var_name_tmp__79 = var_name_tmp__78;
  var_name_tmp__80 = var_name_tmp__79;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109755304)), (((uint64_t)(uint32_t)var_name_tmp__80)), 32, 4);
}


void SDIO_SetSDIOOperation(uint32_t var_name_tmp__81) {
  uint32_t var_name_tmp__82;    /* Address-exposed local */
  uint32_t var_name_tmp__83;

  var_name_tmp__82 = var_name_tmp__81;
  var_name_tmp__83 = var_name_tmp__82;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109755308)), (((uint64_t)(uint32_t)var_name_tmp__83)), 32, 4);
}


void SDIO_SendSDIOSuspendCmd(uint32_t var_name_tmp__84) {
  uint32_t var_name_tmp__85;    /* Address-exposed local */
  uint32_t var_name_tmp__86;

  var_name_tmp__85 = var_name_tmp__84;
  var_name_tmp__86 = var_name_tmp__85;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109754284)), (((uint64_t)(uint32_t)var_name_tmp__86)), 32, 4);
}


void SDIO_CommandCompletionCmd(uint32_t var_name_tmp__87) {
  uint32_t var_name_tmp__88;    /* Address-exposed local */
  uint32_t var_name_tmp__89;

  var_name_tmp__88 = var_name_tmp__87;
  var_name_tmp__89 = var_name_tmp__88;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109754288)), (((uint64_t)(uint32_t)var_name_tmp__89)), 32, 4);
}


void SDIO_CEATAITCmd(uint32_t var_name_tmp__90) {
  uint32_t var_name_tmp__91;    /* Address-exposed local */
  uint32_t var_name_tmp__92;

  var_name_tmp__91 = var_name_tmp__90;
  var_name_tmp__92 = var_name_tmp__91;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109754292)), (((uint64_t)(uint32_t)((~(var_name_tmp__92)) & 1))), 32, 4);
}


void SDIO_SendCEATACmd(uint32_t var_name_tmp__93) {
  uint32_t var_name_tmp__94;    /* Address-exposed local */
  uint32_t var_name_tmp__95;

  var_name_tmp__94 = var_name_tmp__93;
  var_name_tmp__95 = var_name_tmp__94;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109754296)), (((uint64_t)(uint32_t)var_name_tmp__95)), 32, 4);
}


void SDIO_DMACmd(uint32_t var_name_tmp__96) {
  uint32_t var_name_tmp__97;    /* Address-exposed local */
  uint32_t var_name_tmp__98;

  var_name_tmp__97 = var_name_tmp__96;
  var_name_tmp__98 = var_name_tmp__97;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1109755276)), (((uint64_t)(uint32_t)var_name_tmp__98)), 32, 4);
}


void SDIO_ITConfig(uint32_t var_name_tmp__99, uint32_t var_name_tmp__100) {
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  uint32_t var_name_tmp__103;
  uint32_t var_name_tmp__104;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__105;
  uint64_t var_name_load_i32_1;

  var_name_tmp__101 = var_name_tmp__99;
  var_name_tmp__102 = var_name_tmp__100;
  var_name_tmp__103 = var_name_tmp__102;
  if ((((var_name_tmp__103 != 0u)&1))) {
    goto var_name_tmp__106;
  } else {
    goto var_name_tmp__107;
  }

var_name_tmp__106:
  var_name_tmp__104 = var_name_tmp__101;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__104))), 32, 4);
  goto var_name_tmp__108;

var_name_tmp__107:
  var_name_tmp__105 = var_name_tmp__101;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__105))))), 32, 4);
  goto var_name_tmp__108;

var_name_tmp__108:
  return;
}


uint32_t SDIO_GetFlagStatus(uint32_t var_name_tmp__109) {
  uint32_t var_name_tmp__110;    /* Address-exposed local */
  uint32_t var_name_tmp__111;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__112;
  uint32_t var_name_tmp__113;

  var_name_tmp__110 = var_name_tmp__109;
  var_name_tmp__111 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field13))), 32, 4);
  var_name_tmp__112 = var_name_tmp__110;
  if ((((((((uint32_t)var_name_load_i32_)) & var_name_tmp__112) != 0u)&1))) {
    goto var_name_tmp__114;
  } else {
    goto var_name_tmp__115;
  }

var_name_tmp__114:
  var_name_tmp__111 = 1;
  goto var_name_tmp__116;

var_name_tmp__115:
  var_name_tmp__111 = 0;
  goto var_name_tmp__116;

var_name_tmp__116:
  var_name_tmp__113 = var_name_tmp__111;
  return var_name_tmp__113;
}


void SDIO_ClearFlag(uint32_t var_name_tmp__117) {
  uint32_t var_name_tmp__118;    /* Address-exposed local */
  uint32_t var_name_tmp__119;

  var_name_tmp__118 = var_name_tmp__117;
  var_name_tmp__119 = var_name_tmp__118;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field14))), (((uint64_t)(uint32_t)var_name_tmp__119)), 32, 4);
}


uint32_t SDIO_GetITStatus(uint32_t var_name_tmp__120) {
  uint32_t var_name_tmp__121;    /* Address-exposed local */
  uint32_t var_name_tmp__122;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__123;
  uint32_t var_name_tmp__124;

  var_name_tmp__121 = var_name_tmp__120;
  var_name_tmp__122 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field13))), 32, 4);
  var_name_tmp__123 = var_name_tmp__121;
  if ((((((((uint32_t)var_name_load_i32_)) & var_name_tmp__123) != 0u)&1))) {
    goto var_name_tmp__125;
  } else {
    goto var_name_tmp__126;
  }

var_name_tmp__125:
  var_name_tmp__122 = 1;
  goto var_name_tmp__127;

var_name_tmp__126:
  var_name_tmp__122 = 0;
  goto var_name_tmp__127;

var_name_tmp__127:
  var_name_tmp__124 = var_name_tmp__122;
  return var_name_tmp__124;
}


void SDIO_ClearITPendingBit(uint32_t var_name_tmp__128) {
  uint32_t var_name_tmp__129;    /* Address-exposed local */
  uint32_t var_name_tmp__130;

  var_name_tmp__129 = var_name_tmp__128;
  var_name_tmp__130 = var_name_tmp__129;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field14))), (((uint64_t)(uint32_t)var_name_tmp__130)), 32, 4);
}

