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
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__6;
  uint8_t var_name_tmp__7;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__8;
  uint32_t var_name_tmp__9;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__10;
  uint32_t var_name_tmp__11;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__12;
  uint32_t var_name_tmp__13;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__14;
  uint32_t var_name_tmp__15;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__16;
  uint32_t var_name_tmp__17;
  uint32_t var_name_tmp__18;
  uint32_t var_name_tmp__19;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field1));
  var_name_tmp__3 = var_name_tmp__4;
  var_name_tmp__5 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__5 & -32512);
  var_name_tmp__6 = var_name_tmp__2;
  var_name_tmp__7 = *((&var_name_tmp__6->field5));
  var_name_tmp__8 = var_name_tmp__2;
  var_name_tmp__9 = *((&var_name_tmp__8->field2));
  var_name_tmp__10 = var_name_tmp__2;
  var_name_tmp__11 = *((&var_name_tmp__10->field1));
  var_name_tmp__12 = var_name_tmp__2;
  var_name_tmp__13 = *((&var_name_tmp__12->field3));
  var_name_tmp__14 = var_name_tmp__2;
  var_name_tmp__15 = *((&var_name_tmp__14->field0));
  var_name_tmp__16 = var_name_tmp__2;
  var_name_tmp__17 = *((&var_name_tmp__16->field4));
  var_name_tmp__18 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__18 | ((((((((uint32_t)(uint8_t)var_name_tmp__7)) | var_name_tmp__9) | var_name_tmp__11) | var_name_tmp__13) | var_name_tmp__15) | var_name_tmp__17));
  var_name_tmp__19 = var_name_tmp__3;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field1)) = var_name_tmp__19;
}


void SDIO_StructInit(struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__20) {
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__21;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__22;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__23;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__24;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__25;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__26;
  struct l_struct_struct_OC_SDIO_InitTypeDef* var_name_tmp__27;

  var_name_tmp__21 = var_name_tmp__20;
  var_name_tmp__22 = var_name_tmp__21;
  *((&var_name_tmp__22->field5)) = 0;
  var_name_tmp__23 = var_name_tmp__21;
  *((&var_name_tmp__23->field0)) = 0;
  var_name_tmp__24 = var_name_tmp__21;
  *((&var_name_tmp__24->field1)) = 0;
  var_name_tmp__25 = var_name_tmp__21;
  *((&var_name_tmp__25->field2)) = 0;
  var_name_tmp__26 = var_name_tmp__21;
  *((&var_name_tmp__26->field3)) = 0;
  var_name_tmp__27 = var_name_tmp__21;
  *((&var_name_tmp__27->field4)) = 0;
}


void SDIO_ClockCmd(uint32_t var_name_tmp__28) {
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  uint32_t var_name_tmp__30;

  var_name_tmp__29 = var_name_tmp__28;
  var_name_tmp__30 = var_name_tmp__29;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109754016)) = var_name_tmp__30;
}


void SDIO_SetPowerState(uint32_t var_name_tmp__31) {
  uint32_t var_name_tmp__32;    /* Address-exposed local */
  uint32_t var_name_tmp__33;

  var_name_tmp__32 = var_name_tmp__31;
  var_name_tmp__33 = var_name_tmp__32;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field0)) = var_name_tmp__33;
}


uint32_t SDIO_GetPowerState(void) {
  uint32_t var_name_tmp__34;

  var_name_tmp__34 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field0));
  return (var_name_tmp__34 & 3);
}


void SDIO_SendCommand(struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__35) {
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__36;    /* Address-exposed local */
  uint32_t var_name_tmp__37;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__38;
  uint32_t var_name_tmp__39;
  uint32_t var_name_tmp__40;
  uint32_t var_name_tmp__41;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__42;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__44;
  uint32_t var_name_tmp__45;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__46;
  uint32_t var_name_tmp__47;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__48;
  uint32_t var_name_tmp__49;
  uint32_t var_name_tmp__50;
  uint32_t var_name_tmp__51;

  var_name_tmp__36 = var_name_tmp__35;
  var_name_tmp__37 = 0;
  var_name_tmp__38 = var_name_tmp__36;
  var_name_tmp__39 = *((&var_name_tmp__38->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field2)) = var_name_tmp__39;
  var_name_tmp__40 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field3));
  var_name_tmp__37 = var_name_tmp__40;
  var_name_tmp__41 = var_name_tmp__37;
  var_name_tmp__37 = (var_name_tmp__41 & -2048);
  var_name_tmp__42 = var_name_tmp__36;
  var_name_tmp__43 = *((&var_name_tmp__42->field1));
  var_name_tmp__44 = var_name_tmp__36;
  var_name_tmp__45 = *((&var_name_tmp__44->field2));
  var_name_tmp__46 = var_name_tmp__36;
  var_name_tmp__47 = *((&var_name_tmp__46->field3));
  var_name_tmp__48 = var_name_tmp__36;
  var_name_tmp__49 = *((&var_name_tmp__48->field4));
  var_name_tmp__50 = var_name_tmp__37;
  var_name_tmp__37 = (var_name_tmp__50 | (((var_name_tmp__43 | var_name_tmp__45) | var_name_tmp__47) | var_name_tmp__49));
  var_name_tmp__51 = var_name_tmp__37;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field3)) = var_name_tmp__51;
}


void SDIO_CmdStructInit(struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__52) {
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__53;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__54;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__55;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__56;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__57;
  struct l_struct_struct_OC_SDIO_CmdInitTypeDef* var_name_tmp__58;

  var_name_tmp__53 = var_name_tmp__52;
  var_name_tmp__54 = var_name_tmp__53;
  *((&var_name_tmp__54->field0)) = 0;
  var_name_tmp__55 = var_name_tmp__53;
  *((&var_name_tmp__55->field1)) = 0;
  var_name_tmp__56 = var_name_tmp__53;
  *((&var_name_tmp__56->field2)) = 0;
  var_name_tmp__57 = var_name_tmp__53;
  *((&var_name_tmp__57->field3)) = 0;
  var_name_tmp__58 = var_name_tmp__53;
  *((&var_name_tmp__58->field4)) = 0;
}


uint8_t SDIO_GetCommandResponse(void) {
  uint32_t var_name_tmp__59;

  var_name_tmp__59 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field4));
  return (((uint8_t)var_name_tmp__59));
}


uint32_t SDIO_GetResponse(uint32_t var_name_tmp__60) {
  uint32_t var_name_tmp__61;    /* Address-exposed local */
  uint32_t var_name_tmp__62;    /* Address-exposed local */
  uint32_t var_name_tmp__63;
  uint32_t var_name_tmp__64;
  uint32_t var_name_tmp__65;

  var_name_tmp__61 = var_name_tmp__60;
  *(volatile uint32_t*)(&var_name_tmp__62) = 0;
  var_name_tmp__63 = var_name_tmp__61;
  *(volatile uint32_t*)(&var_name_tmp__62) = (llvm_add_u32(1073818644u, var_name_tmp__63));
  var_name_tmp__64 = *(volatile uint32_t*)(&var_name_tmp__62);
  var_name_tmp__65 = *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__64))));
  return var_name_tmp__65;
}


void SDIO_DataConfig(struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__66) {
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__69;
  uint32_t var_name_tmp__70;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__71;
  uint32_t var_name_tmp__72;
  uint32_t var_name_tmp__73;
  uint32_t var_name_tmp__74;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__75;
  uint32_t var_name_tmp__76;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__77;
  uint32_t var_name_tmp__78;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__79;
  uint32_t var_name_tmp__80;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;

  var_name_tmp__67 = var_name_tmp__66;
  var_name_tmp__68 = 0;
  var_name_tmp__69 = var_name_tmp__67;
  var_name_tmp__70 = *((&var_name_tmp__69->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field9)) = var_name_tmp__70;
  var_name_tmp__71 = var_name_tmp__67;
  var_name_tmp__72 = *((&var_name_tmp__71->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field10)) = var_name_tmp__72;
  var_name_tmp__73 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field11));
  var_name_tmp__68 = var_name_tmp__73;
  var_name_tmp__74 = var_name_tmp__68;
  var_name_tmp__68 = (var_name_tmp__74 & -248);
  var_name_tmp__75 = var_name_tmp__67;
  var_name_tmp__76 = *((&var_name_tmp__75->field2));
  var_name_tmp__77 = var_name_tmp__67;
  var_name_tmp__78 = *((&var_name_tmp__77->field3));
  var_name_tmp__79 = var_name_tmp__67;
  var_name_tmp__80 = *((&var_name_tmp__79->field4));
  var_name_tmp__81 = var_name_tmp__67;
  var_name_tmp__82 = *((&var_name_tmp__81->field5));
  var_name_tmp__83 = var_name_tmp__68;
  var_name_tmp__68 = (var_name_tmp__83 | (((var_name_tmp__76 | var_name_tmp__78) | var_name_tmp__80) | var_name_tmp__82));
  var_name_tmp__84 = var_name_tmp__68;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field11)) = var_name_tmp__84;
}


void SDIO_DataStructInit(struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__85) {
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__86;    /* Address-exposed local */
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__87;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__88;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__89;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__90;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__91;
  struct l_struct_struct_OC_SDIO_DataInitTypeDef* var_name_tmp__92;

  var_name_tmp__86 = var_name_tmp__85;
  var_name_tmp__87 = var_name_tmp__86;
  *((&var_name_tmp__87->field0)) = -1;
  var_name_tmp__88 = var_name_tmp__86;
  *((&var_name_tmp__88->field1)) = 0;
  var_name_tmp__89 = var_name_tmp__86;
  *((&var_name_tmp__89->field2)) = 0;
  var_name_tmp__90 = var_name_tmp__86;
  *((&var_name_tmp__90->field3)) = 0;
  var_name_tmp__91 = var_name_tmp__86;
  *((&var_name_tmp__91->field4)) = 0;
  var_name_tmp__92 = var_name_tmp__86;
  *((&var_name_tmp__92->field5)) = 0;
}


uint32_t SDIO_GetDataCounter(void) {
  uint32_t var_name_tmp__93;

  var_name_tmp__93 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field12));
  return var_name_tmp__93;
}


uint32_t SDIO_ReadData(void) {
  uint32_t var_name_tmp__94;

  var_name_tmp__94 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field19));
  return var_name_tmp__94;
}


void SDIO_WriteData(uint32_t var_name_tmp__95) {
  uint32_t var_name_tmp__96;    /* Address-exposed local */
  uint32_t var_name_tmp__97;

  var_name_tmp__96 = var_name_tmp__95;
  var_name_tmp__97 = var_name_tmp__96;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field19)) = var_name_tmp__97;
}


uint32_t SDIO_GetFIFOCount(void) {
  uint32_t var_name_tmp__98;

  var_name_tmp__98 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field17));
  return var_name_tmp__98;
}


void SDIO_StartSDIOReadWait(uint32_t var_name_tmp__99) {
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;

  var_name_tmp__100 = var_name_tmp__99;
  var_name_tmp__101 = var_name_tmp__100;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109755296)) = var_name_tmp__101;
}


void SDIO_StopSDIOReadWait(uint32_t var_name_tmp__102) {
  uint32_t var_name_tmp__103;    /* Address-exposed local */
  uint32_t var_name_tmp__104;

  var_name_tmp__103 = var_name_tmp__102;
  var_name_tmp__104 = var_name_tmp__103;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109755300)) = var_name_tmp__104;
}


void SDIO_SetSDIOReadWaitMode(uint32_t var_name_tmp__105) {
  uint32_t var_name_tmp__106;    /* Address-exposed local */
  uint32_t var_name_tmp__107;

  var_name_tmp__106 = var_name_tmp__105;
  var_name_tmp__107 = var_name_tmp__106;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109755304)) = var_name_tmp__107;
}


void SDIO_SetSDIOOperation(uint32_t var_name_tmp__108) {
  uint32_t var_name_tmp__109;    /* Address-exposed local */
  uint32_t var_name_tmp__110;

  var_name_tmp__109 = var_name_tmp__108;
  var_name_tmp__110 = var_name_tmp__109;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109755308)) = var_name_tmp__110;
}


void SDIO_SendSDIOSuspendCmd(uint32_t var_name_tmp__111) {
  uint32_t var_name_tmp__112;    /* Address-exposed local */
  uint32_t var_name_tmp__113;

  var_name_tmp__112 = var_name_tmp__111;
  var_name_tmp__113 = var_name_tmp__112;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109754284)) = var_name_tmp__113;
}


void SDIO_CommandCompletionCmd(uint32_t var_name_tmp__114) {
  uint32_t var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;

  var_name_tmp__115 = var_name_tmp__114;
  var_name_tmp__116 = var_name_tmp__115;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109754288)) = var_name_tmp__116;
}


void SDIO_CEATAITCmd(uint32_t var_name_tmp__117) {
  uint32_t var_name_tmp__118;    /* Address-exposed local */
  uint32_t var_name_tmp__119;

  var_name_tmp__118 = var_name_tmp__117;
  var_name_tmp__119 = var_name_tmp__118;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109754292)) = ((~(var_name_tmp__119)) & 1);
}


void SDIO_SendCEATACmd(uint32_t var_name_tmp__120) {
  uint32_t var_name_tmp__121;    /* Address-exposed local */
  uint32_t var_name_tmp__122;

  var_name_tmp__121 = var_name_tmp__120;
  var_name_tmp__122 = var_name_tmp__121;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109754296)) = var_name_tmp__122;
}


void SDIO_DMACmd(uint32_t var_name_tmp__123) {
  uint32_t var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;

  var_name_tmp__124 = var_name_tmp__123;
  var_name_tmp__125 = var_name_tmp__124;
  *(volatile uint32_t*)((uint32_t*)(uintptr_t)UINT64_C(1109755276)) = var_name_tmp__125;
}


void SDIO_ITConfig(uint32_t var_name_tmp__126, uint32_t var_name_tmp__127) {
  uint32_t var_name_tmp__128;    /* Address-exposed local */
  uint32_t var_name_tmp__129;    /* Address-exposed local */
  uint32_t var_name_tmp__130;
  uint32_t var_name_tmp__131;
  uint32_t var_name_tmp__132;
  uint32_t var_name_tmp__133;
  uint32_t var_name_tmp__134;

  var_name_tmp__128 = var_name_tmp__126;
  var_name_tmp__129 = var_name_tmp__127;
  var_name_tmp__130 = var_name_tmp__129;
  if ((((var_name_tmp__130 != 0u)&1))) {
    goto var_name_tmp__135;
  } else {
    goto var_name_tmp__136;
  }

var_name_tmp__135:
  var_name_tmp__131 = var_name_tmp__128;
  var_name_tmp__132 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15)) = (var_name_tmp__132 | var_name_tmp__131);
  goto var_name_tmp__137;

var_name_tmp__136:
  var_name_tmp__133 = var_name_tmp__128;
  var_name_tmp__134 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field15)) = (var_name_tmp__134 & (~(var_name_tmp__133)));
  goto var_name_tmp__137;

var_name_tmp__137:
  return;
}


uint32_t SDIO_GetFlagStatus(uint32_t var_name_tmp__138) {
  uint32_t var_name_tmp__139;    /* Address-exposed local */
  uint32_t var_name_tmp__140;    /* Address-exposed local */
  uint32_t var_name_tmp__141;
  uint32_t var_name_tmp__142;
  uint32_t var_name_tmp__143;

  var_name_tmp__139 = var_name_tmp__138;
  var_name_tmp__140 = 0;
  var_name_tmp__141 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field13));
  var_name_tmp__142 = var_name_tmp__139;
  if (((((var_name_tmp__141 & var_name_tmp__142) != 0u)&1))) {
    goto var_name_tmp__144;
  } else {
    goto var_name_tmp__145;
  }

var_name_tmp__144:
  var_name_tmp__140 = 1;
  goto var_name_tmp__146;

var_name_tmp__145:
  var_name_tmp__140 = 0;
  goto var_name_tmp__146;

var_name_tmp__146:
  var_name_tmp__143 = var_name_tmp__140;
  return var_name_tmp__143;
}


void SDIO_ClearFlag(uint32_t var_name_tmp__147) {
  uint32_t var_name_tmp__148;    /* Address-exposed local */
  uint32_t var_name_tmp__149;

  var_name_tmp__148 = var_name_tmp__147;
  var_name_tmp__149 = var_name_tmp__148;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field14)) = var_name_tmp__149;
}


uint32_t SDIO_GetITStatus(uint32_t var_name_tmp__150) {
  uint32_t var_name_tmp__151;    /* Address-exposed local */
  uint32_t var_name_tmp__152;    /* Address-exposed local */
  uint32_t var_name_tmp__153;
  uint32_t var_name_tmp__154;
  uint32_t var_name_tmp__155;

  var_name_tmp__151 = var_name_tmp__150;
  var_name_tmp__152 = 0;
  var_name_tmp__153 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field13));
  var_name_tmp__154 = var_name_tmp__151;
  if (((((var_name_tmp__153 & var_name_tmp__154) != 0u)&1))) {
    goto var_name_tmp__156;
  } else {
    goto var_name_tmp__157;
  }

var_name_tmp__156:
  var_name_tmp__152 = 1;
  goto var_name_tmp__158;

var_name_tmp__157:
  var_name_tmp__152 = 0;
  goto var_name_tmp__158;

var_name_tmp__158:
  var_name_tmp__155 = var_name_tmp__152;
  return var_name_tmp__155;
}


void SDIO_ClearITPendingBit(uint32_t var_name_tmp__159) {
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;

  var_name_tmp__160 = var_name_tmp__159;
  var_name_tmp__161 = var_name_tmp__160;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_SDIO_TypeDef*)(uintptr_t)UINT64_C(1073818624))->field14)) = var_name_tmp__161;
}

