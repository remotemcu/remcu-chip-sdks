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
struct l_struct_struct_OC_USART_TypeDef;
struct l_struct_struct_OC_USART_InitTypeDef;
struct l_struct_struct_OC_RCC_ClocksTypeDef;
struct l_struct_struct_OC_USART_ClockInitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_USART_TypeDef {
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
};
struct l_struct_struct_OC_USART_InitTypeDef {
  uint32_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint16_t field5;
};
struct l_struct_struct_OC_RCC_ClocksTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_USART_ClockInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
};

/* Function Declarations */
void USART_DeInit(struct l_struct_struct_OC_USART_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void USART_Init(struct l_struct_struct_OC_USART_TypeDef*, struct l_struct_struct_OC_USART_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_GetClocksFreq(struct l_struct_struct_OC_RCC_ClocksTypeDef*);
void USART_StructInit(struct l_struct_struct_OC_USART_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ClockInit(struct l_struct_struct_OC_USART_TypeDef*, struct l_struct_struct_OC_USART_ClockInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ClockStructInit(struct l_struct_struct_OC_USART_ClockInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void USART_Cmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SetPrescaler(struct l_struct_struct_OC_USART_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_OverSampling8Cmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_OneBitMethodCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SendData(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t USART_ReceiveData(struct l_struct_struct_OC_USART_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SetAddress(struct l_struct_struct_OC_USART_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ReceiverWakeUpCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_WakeUpConfig(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_LINBreakDetectLengthConfig(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_LINCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SendBreak(struct l_struct_struct_OC_USART_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void USART_HalfDuplexCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SetGuardTime(struct l_struct_struct_OC_USART_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SmartCardCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_SmartCardNACKCmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_IrDAConfig(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_IrDACmd(struct l_struct_struct_OC_USART_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_DMACmd(struct l_struct_struct_OC_USART_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ITConfig(struct l_struct_struct_OC_USART_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t USART_GetFlagStatus(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ClearFlag(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t USART_GetITStatus(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void USART_ClearITPendingBit(struct l_struct_struct_OC_USART_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));


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

void USART_DeInit(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__3;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__4;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__5;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__6;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__7;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__8;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073811456)))&1))) {
    goto var_name_tmp__9;
  } else {
    goto var_name_tmp__10;
  }

var_name_tmp__9:
  RCC_APB2PeriphResetCmd(16, 1);
  RCC_APB2PeriphResetCmd(16, 0);
  goto var_name_tmp__11;

var_name_tmp__10:
  var_name_tmp__4 = var_name_tmp__2;
  if ((((var_name_tmp__4 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073759232)))&1))) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__12:
  RCC_APB1PeriphResetCmd(131072, 1);
  RCC_APB1PeriphResetCmd(131072, 0);
  goto var_name_tmp__14;

var_name_tmp__13:
  var_name_tmp__5 = var_name_tmp__2;
  if ((((var_name_tmp__5 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073760256)))&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  RCC_APB1PeriphResetCmd(262144, 1);
  RCC_APB1PeriphResetCmd(262144, 0);
  goto var_name_tmp__17;

var_name_tmp__16:
  var_name_tmp__6 = var_name_tmp__2;
  if ((((var_name_tmp__6 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073761280)))&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  RCC_APB1PeriphResetCmd(524288, 1);
  RCC_APB1PeriphResetCmd(524288, 0);
  goto var_name_tmp__20;

var_name_tmp__19:
  var_name_tmp__7 = var_name_tmp__2;
  if ((((var_name_tmp__7 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073762304)))&1))) {
    goto var_name_tmp__21;
  } else {
    goto var_name_tmp__22;
  }

var_name_tmp__21:
  RCC_APB1PeriphResetCmd(1048576, 1);
  RCC_APB1PeriphResetCmd(1048576, 0);
  goto var_name_tmp__23;

var_name_tmp__22:
  var_name_tmp__8 = var_name_tmp__2;
  if ((((var_name_tmp__8 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073812480)))&1))) {
    goto var_name_tmp__24;
  } else {
    goto var_name_tmp__25;
  }

var_name_tmp__24:
  RCC_APB2PeriphResetCmd(32, 1);
  RCC_APB2PeriphResetCmd(32, 0);
  goto var_name_tmp__25;

var_name_tmp__25:
  goto var_name_tmp__23;

var_name_tmp__23:
  goto var_name_tmp__20;

var_name_tmp__20:
  goto var_name_tmp__17;

var_name_tmp__17:
  goto var_name_tmp__14;

var_name_tmp__14:
  goto var_name_tmp__11;

var_name_tmp__11:
  return;
}


void USART_Init(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__26, struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__27) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__28;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__29;    /* Address-exposed local */
  uint32_t var_name_tmp__30;    /* Address-exposed local */
  uint32_t var_name_tmp__31;    /* Address-exposed local */
  uint32_t var_name_tmp__32;    /* Address-exposed local */
  uint32_t var_name_tmp__33;    /* Address-exposed local */
  struct l_struct_struct_OC_RCC_ClocksTypeDef var_name_tmp__34;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__35;
  uint16_t var_name_tmp__36;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__37;
  uint16_t var_name_tmp__38;
  uint32_t var_name_tmp__39;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__40;
  uint16_t var_name_tmp__41;
  uint32_t var_name_tmp__42;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__44;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__45;
  uint16_t var_name_tmp__46;
  uint32_t var_name_tmp__47;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__48;
  uint16_t var_name_tmp__49;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__50;
  uint16_t var_name_tmp__51;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__52;
  uint16_t var_name_tmp__53;
  uint32_t var_name_tmp__54;
  uint32_t var_name_tmp__55;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__56;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__57;
  uint16_t var_name_tmp__58;
  uint32_t var_name_tmp__59;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__60;
  uint16_t var_name_tmp__61;
  uint32_t var_name_tmp__62;
  uint32_t var_name_tmp__63;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__64;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__65;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__66;
  uint32_t var_name_tmp__67;
  uint32_t var_name_tmp__68;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__69;
  uint16_t var_name_tmp__70;
  uint32_t var_name_tmp__71;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__72;
  uint32_t var_name_tmp__73;
  uint32_t var_name_tmp__74;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__75;
  uint32_t var_name_tmp__76;
  uint32_t var_name_tmp__77;
  uint32_t var_name_tmp__78;
  uint32_t var_name_tmp__79;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__80;
  uint16_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint32_t var_name_tmp__86;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__87;

  var_name_tmp__28 = var_name_tmp__26;
  var_name_tmp__29 = var_name_tmp__27;
  var_name_tmp__30 = 0;
  var_name_tmp__31 = 0;
  var_name_tmp__32 = 0;
  var_name_tmp__33 = 0;
  var_name_tmp__35 = var_name_tmp__29;
  var_name_tmp__36 = *((&var_name_tmp__35->field5));
  if (((((((uint32_t)(uint16_t)var_name_tmp__36)) != 0u)&1))) {
    goto var_name_tmp__88;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__88:
  goto var_name_tmp__89;

var_name_tmp__89:
  var_name_tmp__37 = var_name_tmp__28;
  var_name_tmp__38 = *(volatile uint16_t*)((&var_name_tmp__37->field8));
  var_name_tmp__30 = (((uint32_t)(uint16_t)var_name_tmp__38));
  var_name_tmp__39 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__39 & -12289);
  var_name_tmp__40 = var_name_tmp__29;
  var_name_tmp__41 = *((&var_name_tmp__40->field2));
  var_name_tmp__42 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__42 | (((uint32_t)(uint16_t)var_name_tmp__41)));
  var_name_tmp__43 = var_name_tmp__30;
  var_name_tmp__44 = var_name_tmp__28;
  *(volatile uint16_t*)((&var_name_tmp__44->field8)) = (((uint16_t)var_name_tmp__43));
  var_name_tmp__45 = var_name_tmp__28;
  var_name_tmp__46 = *(volatile uint16_t*)((&var_name_tmp__45->field6));
  var_name_tmp__30 = (((uint32_t)(uint16_t)var_name_tmp__46));
  var_name_tmp__47 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__47 & -5645);
  var_name_tmp__48 = var_name_tmp__29;
  var_name_tmp__49 = *((&var_name_tmp__48->field1));
  var_name_tmp__50 = var_name_tmp__29;
  var_name_tmp__51 = *((&var_name_tmp__50->field3));
  var_name_tmp__52 = var_name_tmp__29;
  var_name_tmp__53 = *((&var_name_tmp__52->field4));
  var_name_tmp__54 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__54 | (((((uint32_t)(uint16_t)var_name_tmp__49)) | (((uint32_t)(uint16_t)var_name_tmp__51))) | (((uint32_t)(uint16_t)var_name_tmp__53))));
  var_name_tmp__55 = var_name_tmp__30;
  var_name_tmp__56 = var_name_tmp__28;
  *(volatile uint16_t*)((&var_name_tmp__56->field6)) = (((uint16_t)var_name_tmp__55));
  var_name_tmp__57 = var_name_tmp__28;
  var_name_tmp__58 = *(volatile uint16_t*)((&var_name_tmp__57->field10));
  var_name_tmp__30 = (((uint32_t)(uint16_t)var_name_tmp__58));
  var_name_tmp__59 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__59 & -769);
  var_name_tmp__60 = var_name_tmp__29;
  var_name_tmp__61 = *((&var_name_tmp__60->field5));
  var_name_tmp__62 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__62 | (((uint32_t)(uint16_t)var_name_tmp__61)));
  var_name_tmp__63 = var_name_tmp__30;
  var_name_tmp__64 = var_name_tmp__28;
  *(volatile uint16_t*)((&var_name_tmp__64->field10)) = (((uint16_t)var_name_tmp__63));
  RCC_GetClocksFreq((&var_name_tmp__34));
  var_name_tmp__65 = var_name_tmp__28;
  if ((((var_name_tmp__65 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073811456)))&1))) {
    goto var_name_tmp__90;
  } else {
    goto var_name_tmp__91;
  }

var_name_tmp__91:
  var_name_tmp__66 = var_name_tmp__28;
  if ((((var_name_tmp__66 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073812480)))&1))) {
    goto var_name_tmp__90;
  } else {
    goto var_name_tmp__92;
  }

var_name_tmp__90:
  var_name_tmp__67 = *((&var_name_tmp__34.field3));
  var_name_tmp__31 = var_name_tmp__67;
  goto var_name_tmp__93;

var_name_tmp__92:
  var_name_tmp__68 = *((&var_name_tmp__34.field2));
  var_name_tmp__31 = var_name_tmp__68;
  goto var_name_tmp__93;

var_name_tmp__93:
  var_name_tmp__69 = var_name_tmp__28;
  var_name_tmp__70 = *(volatile uint16_t*)((&var_name_tmp__69->field6));
  if ((((((((uint32_t)(uint16_t)var_name_tmp__70)) & 32768) != 0u)&1))) {
    goto var_name_tmp__94;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__94:
  var_name_tmp__71 = var_name_tmp__31;
  var_name_tmp__72 = var_name_tmp__29;
  var_name_tmp__73 = *((&var_name_tmp__72->field0));
  var_name_tmp__32 = (llvm_udiv_u32((llvm_mul_u32(25, var_name_tmp__71)), (llvm_mul_u32(2, var_name_tmp__73))));
  goto var_name_tmp__96;

var_name_tmp__95:
  var_name_tmp__74 = var_name_tmp__31;
  var_name_tmp__75 = var_name_tmp__29;
  var_name_tmp__76 = *((&var_name_tmp__75->field0));
  var_name_tmp__32 = (llvm_udiv_u32((llvm_mul_u32(25, var_name_tmp__74)), (llvm_mul_u32(4, var_name_tmp__76))));
  goto var_name_tmp__96;

var_name_tmp__96:
  var_name_tmp__77 = var_name_tmp__32;
  var_name_tmp__30 = ((llvm_udiv_u32(var_name_tmp__77, 100)) << 4);
  var_name_tmp__78 = var_name_tmp__32;
  var_name_tmp__79 = var_name_tmp__30;
  var_name_tmp__33 = (llvm_sub_u32(var_name_tmp__78, (llvm_mul_u32(100, (llvm_lshr_u32(var_name_tmp__79, 4))))));
  var_name_tmp__80 = var_name_tmp__28;
  var_name_tmp__81 = *(volatile uint16_t*)((&var_name_tmp__80->field6));
  if ((((((((uint32_t)(uint16_t)var_name_tmp__81)) & 32768) != 0u)&1))) {
    goto var_name_tmp__97;
  } else {
    goto var_name_tmp__98;
  }

var_name_tmp__97:
  var_name_tmp__82 = var_name_tmp__33;
  var_name_tmp__83 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__83 | ((llvm_udiv_u32((llvm_add_u32((llvm_mul_u32(var_name_tmp__82, 8)), 50)), 100)) & 7));
  goto var_name_tmp__99;

var_name_tmp__98:
  var_name_tmp__84 = var_name_tmp__33;
  var_name_tmp__85 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__85 | ((llvm_udiv_u32((llvm_add_u32((llvm_mul_u32(var_name_tmp__84, 16)), 50)), 100)) & 15));
  goto var_name_tmp__99;

var_name_tmp__99:
  var_name_tmp__86 = var_name_tmp__30;
  var_name_tmp__87 = var_name_tmp__28;
  *(volatile uint16_t*)((&var_name_tmp__87->field4)) = (((uint16_t)var_name_tmp__86));
}


void USART_StructInit(struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__100) {
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__101;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__102;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__103;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__104;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__105;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__106;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__107;

  var_name_tmp__101 = var_name_tmp__100;
  var_name_tmp__102 = var_name_tmp__101;
  *((&var_name_tmp__102->field0)) = 9600;
  var_name_tmp__103 = var_name_tmp__101;
  *((&var_name_tmp__103->field1)) = 0;
  var_name_tmp__104 = var_name_tmp__101;
  *((&var_name_tmp__104->field2)) = 0;
  var_name_tmp__105 = var_name_tmp__101;
  *((&var_name_tmp__105->field3)) = 0;
  var_name_tmp__106 = var_name_tmp__101;
  *((&var_name_tmp__106->field4)) = 12;
  var_name_tmp__107 = var_name_tmp__101;
  *((&var_name_tmp__107->field5)) = 0;
}


void USART_ClockInit(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__108, struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__109) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__110;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__111;    /* Address-exposed local */
  uint32_t var_name_tmp__112;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__113;
  uint16_t var_name_tmp__114;
  uint32_t var_name_tmp__115;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__116;
  uint16_t var_name_tmp__117;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__118;
  uint16_t var_name_tmp__119;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__120;
  uint16_t var_name_tmp__121;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__122;
  uint16_t var_name_tmp__123;
  uint32_t var_name_tmp__124;
  uint32_t var_name_tmp__125;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__126;

  var_name_tmp__110 = var_name_tmp__108;
  var_name_tmp__111 = var_name_tmp__109;
  var_name_tmp__112 = 0;
  var_name_tmp__113 = var_name_tmp__110;
  var_name_tmp__114 = *(volatile uint16_t*)((&var_name_tmp__113->field8));
  var_name_tmp__112 = (((uint32_t)(uint16_t)var_name_tmp__114));
  var_name_tmp__115 = var_name_tmp__112;
  var_name_tmp__112 = (var_name_tmp__115 & -3841);
  var_name_tmp__116 = var_name_tmp__111;
  var_name_tmp__117 = *((&var_name_tmp__116->field0));
  var_name_tmp__118 = var_name_tmp__111;
  var_name_tmp__119 = *((&var_name_tmp__118->field1));
  var_name_tmp__120 = var_name_tmp__111;
  var_name_tmp__121 = *((&var_name_tmp__120->field2));
  var_name_tmp__122 = var_name_tmp__111;
  var_name_tmp__123 = *((&var_name_tmp__122->field3));
  var_name_tmp__124 = var_name_tmp__112;
  var_name_tmp__112 = (var_name_tmp__124 | ((((((uint32_t)(uint16_t)var_name_tmp__117)) | (((uint32_t)(uint16_t)var_name_tmp__119))) | (((uint32_t)(uint16_t)var_name_tmp__121))) | (((uint32_t)(uint16_t)var_name_tmp__123))));
  var_name_tmp__125 = var_name_tmp__112;
  var_name_tmp__126 = var_name_tmp__110;
  *(volatile uint16_t*)((&var_name_tmp__126->field8)) = (((uint16_t)var_name_tmp__125));
}


void USART_ClockStructInit(struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__127) {
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__128;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__129;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__130;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__131;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__132;

  var_name_tmp__128 = var_name_tmp__127;
  var_name_tmp__129 = var_name_tmp__128;
  *((&var_name_tmp__129->field0)) = 0;
  var_name_tmp__130 = var_name_tmp__128;
  *((&var_name_tmp__130->field1)) = 0;
  var_name_tmp__131 = var_name_tmp__128;
  *((&var_name_tmp__131->field2)) = 0;
  var_name_tmp__132 = var_name_tmp__128;
  *((&var_name_tmp__132->field3)) = 0;
}


void USART_Cmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__133, uint32_t var_name_tmp__134) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__135;    /* Address-exposed local */
  uint32_t var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__138;
  uint16_t* var_name_tmp__139;
  uint16_t var_name_tmp__140;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__141;
  uint16_t* var_name_tmp__142;
  uint16_t var_name_tmp__143;

  var_name_tmp__135 = var_name_tmp__133;
  var_name_tmp__136 = var_name_tmp__134;
  var_name_tmp__137 = var_name_tmp__136;
  if ((((var_name_tmp__137 != 0u)&1))) {
    goto var_name_tmp__144;
  } else {
    goto var_name_tmp__145;
  }

var_name_tmp__144:
  var_name_tmp__138 = var_name_tmp__135;
  var_name_tmp__139 = (&var_name_tmp__138->field6);
  var_name_tmp__140 = *(volatile uint16_t*)var_name_tmp__139;
  *(volatile uint16_t*)var_name_tmp__139 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__140)) | 8192)));
  goto var_name_tmp__146;

var_name_tmp__145:
  var_name_tmp__141 = var_name_tmp__135;
  var_name_tmp__142 = (&var_name_tmp__141->field6);
  var_name_tmp__143 = *(volatile uint16_t*)var_name_tmp__142;
  *(volatile uint16_t*)var_name_tmp__142 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__143)) & 57343)));
  goto var_name_tmp__146;

var_name_tmp__146:
  return;
}


void USART_SetPrescaler(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__147, uint8_t var_name_tmp__148) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__149;    /* Address-exposed local */
  uint8_t var_name_tmp__150;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__151;
  uint16_t* var_name_tmp__152;
  uint16_t var_name_tmp__153;
  uint8_t var_name_tmp__154;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__155;
  uint16_t* var_name_tmp__156;
  uint16_t var_name_tmp__157;

  var_name_tmp__149 = var_name_tmp__147;
  var_name_tmp__150 = var_name_tmp__148;
  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__152 = (&var_name_tmp__151->field12);
  var_name_tmp__153 = *(volatile uint16_t*)var_name_tmp__152;
  *(volatile uint16_t*)var_name_tmp__152 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__153)) & 65280)));
  var_name_tmp__154 = var_name_tmp__150;
  var_name_tmp__155 = var_name_tmp__149;
  var_name_tmp__156 = (&var_name_tmp__155->field12);
  var_name_tmp__157 = *(volatile uint16_t*)var_name_tmp__156;
  *(volatile uint16_t*)var_name_tmp__156 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__157)) | (((uint32_t)(uint8_t)var_name_tmp__154)))));
}


void USART_OverSampling8Cmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__158, uint32_t var_name_tmp__159) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;    /* Address-exposed local */
  uint32_t var_name_tmp__162;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__163;
  uint16_t* var_name_tmp__164;
  uint16_t var_name_tmp__165;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__166;
  uint16_t* var_name_tmp__167;
  uint16_t var_name_tmp__168;

  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__159;
  var_name_tmp__162 = var_name_tmp__161;
  if ((((var_name_tmp__162 != 0u)&1))) {
    goto var_name_tmp__169;
  } else {
    goto var_name_tmp__170;
  }

var_name_tmp__169:
  var_name_tmp__163 = var_name_tmp__160;
  var_name_tmp__164 = (&var_name_tmp__163->field6);
  var_name_tmp__165 = *(volatile uint16_t*)var_name_tmp__164;
  *(volatile uint16_t*)var_name_tmp__164 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__165)) | 32768)));
  goto var_name_tmp__171;

var_name_tmp__170:
  var_name_tmp__166 = var_name_tmp__160;
  var_name_tmp__167 = (&var_name_tmp__166->field6);
  var_name_tmp__168 = *(volatile uint16_t*)var_name_tmp__167;
  *(volatile uint16_t*)var_name_tmp__167 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__168)) & 32767)));
  goto var_name_tmp__171;

var_name_tmp__171:
  return;
}


void USART_OneBitMethodCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__172, uint32_t var_name_tmp__173) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__174;    /* Address-exposed local */
  uint32_t var_name_tmp__175;    /* Address-exposed local */
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__177;
  uint16_t* var_name_tmp__178;
  uint16_t var_name_tmp__179;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__180;
  uint16_t* var_name_tmp__181;
  uint16_t var_name_tmp__182;

  var_name_tmp__174 = var_name_tmp__172;
  var_name_tmp__175 = var_name_tmp__173;
  var_name_tmp__176 = var_name_tmp__175;
  if ((((var_name_tmp__176 != 0u)&1))) {
    goto var_name_tmp__183;
  } else {
    goto var_name_tmp__184;
  }

var_name_tmp__183:
  var_name_tmp__177 = var_name_tmp__174;
  var_name_tmp__178 = (&var_name_tmp__177->field10);
  var_name_tmp__179 = *(volatile uint16_t*)var_name_tmp__178;
  *(volatile uint16_t*)var_name_tmp__178 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__179)) | 2048)));
  goto var_name_tmp__185;

var_name_tmp__184:
  var_name_tmp__180 = var_name_tmp__174;
  var_name_tmp__181 = (&var_name_tmp__180->field10);
  var_name_tmp__182 = *(volatile uint16_t*)var_name_tmp__181;
  *(volatile uint16_t*)var_name_tmp__181 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__182)) & 63487)));
  goto var_name_tmp__185;

var_name_tmp__185:
  return;
}


void USART_SendData(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__186, uint16_t var_name_tmp__187) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__188;    /* Address-exposed local */
  uint16_t var_name_tmp__189;    /* Address-exposed local */
  uint16_t var_name_tmp__190;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__191;

  var_name_tmp__188 = var_name_tmp__186;
  var_name_tmp__189 = var_name_tmp__187;
  var_name_tmp__190 = var_name_tmp__189;
  var_name_tmp__191 = var_name_tmp__188;
  *(volatile uint16_t*)((&var_name_tmp__191->field2)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__190)) & 511)));
}


uint16_t USART_ReceiveData(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__192) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__193;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__194;
  uint16_t var_name_tmp__195;

  var_name_tmp__193 = var_name_tmp__192;
  var_name_tmp__194 = var_name_tmp__193;
  var_name_tmp__195 = *(volatile uint16_t*)((&var_name_tmp__194->field2));
  return (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__195)) & 511)));
}


void USART_SetAddress(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__196, uint8_t var_name_tmp__197) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__198;    /* Address-exposed local */
  uint8_t var_name_tmp__199;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__200;
  uint16_t* var_name_tmp__201;
  uint16_t var_name_tmp__202;
  uint8_t var_name_tmp__203;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__204;
  uint16_t* var_name_tmp__205;
  uint16_t var_name_tmp__206;

  var_name_tmp__198 = var_name_tmp__196;
  var_name_tmp__199 = var_name_tmp__197;
  var_name_tmp__200 = var_name_tmp__198;
  var_name_tmp__201 = (&var_name_tmp__200->field8);
  var_name_tmp__202 = *(volatile uint16_t*)var_name_tmp__201;
  *(volatile uint16_t*)var_name_tmp__201 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__202)) & 65520)));
  var_name_tmp__203 = var_name_tmp__199;
  var_name_tmp__204 = var_name_tmp__198;
  var_name_tmp__205 = (&var_name_tmp__204->field8);
  var_name_tmp__206 = *(volatile uint16_t*)var_name_tmp__205;
  *(volatile uint16_t*)var_name_tmp__205 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__206)) | (((uint32_t)(uint8_t)var_name_tmp__203)))));
}


void USART_ReceiverWakeUpCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__207, uint32_t var_name_tmp__208) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__209;    /* Address-exposed local */
  uint32_t var_name_tmp__210;    /* Address-exposed local */
  uint32_t var_name_tmp__211;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__212;
  uint16_t* var_name_tmp__213;
  uint16_t var_name_tmp__214;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__215;
  uint16_t* var_name_tmp__216;
  uint16_t var_name_tmp__217;

  var_name_tmp__209 = var_name_tmp__207;
  var_name_tmp__210 = var_name_tmp__208;
  var_name_tmp__211 = var_name_tmp__210;
  if ((((var_name_tmp__211 != 0u)&1))) {
    goto var_name_tmp__218;
  } else {
    goto var_name_tmp__219;
  }

var_name_tmp__218:
  var_name_tmp__212 = var_name_tmp__209;
  var_name_tmp__213 = (&var_name_tmp__212->field6);
  var_name_tmp__214 = *(volatile uint16_t*)var_name_tmp__213;
  *(volatile uint16_t*)var_name_tmp__213 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__214)) | 2)));
  goto var_name_tmp__220;

var_name_tmp__219:
  var_name_tmp__215 = var_name_tmp__209;
  var_name_tmp__216 = (&var_name_tmp__215->field6);
  var_name_tmp__217 = *(volatile uint16_t*)var_name_tmp__216;
  *(volatile uint16_t*)var_name_tmp__216 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__217)) & 65533)));
  goto var_name_tmp__220;

var_name_tmp__220:
  return;
}


void USART_WakeUpConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__221, uint16_t var_name_tmp__222) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__223;    /* Address-exposed local */
  uint16_t var_name_tmp__224;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__225;
  uint16_t* var_name_tmp__226;
  uint16_t var_name_tmp__227;
  uint16_t var_name_tmp__228;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__229;
  uint16_t* var_name_tmp__230;
  uint16_t var_name_tmp__231;

  var_name_tmp__223 = var_name_tmp__221;
  var_name_tmp__224 = var_name_tmp__222;
  var_name_tmp__225 = var_name_tmp__223;
  var_name_tmp__226 = (&var_name_tmp__225->field6);
  var_name_tmp__227 = *(volatile uint16_t*)var_name_tmp__226;
  *(volatile uint16_t*)var_name_tmp__226 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__227)) & 63487)));
  var_name_tmp__228 = var_name_tmp__224;
  var_name_tmp__229 = var_name_tmp__223;
  var_name_tmp__230 = (&var_name_tmp__229->field6);
  var_name_tmp__231 = *(volatile uint16_t*)var_name_tmp__230;
  *(volatile uint16_t*)var_name_tmp__230 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__231)) | (((uint32_t)(uint16_t)var_name_tmp__228)))));
}


void USART_LINBreakDetectLengthConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__232, uint16_t var_name_tmp__233) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__234;    /* Address-exposed local */
  uint16_t var_name_tmp__235;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__236;
  uint16_t* var_name_tmp__237;
  uint16_t var_name_tmp__238;
  uint16_t var_name_tmp__239;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__240;
  uint16_t* var_name_tmp__241;
  uint16_t var_name_tmp__242;

  var_name_tmp__234 = var_name_tmp__232;
  var_name_tmp__235 = var_name_tmp__233;
  var_name_tmp__236 = var_name_tmp__234;
  var_name_tmp__237 = (&var_name_tmp__236->field8);
  var_name_tmp__238 = *(volatile uint16_t*)var_name_tmp__237;
  *(volatile uint16_t*)var_name_tmp__237 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__238)) & 65503)));
  var_name_tmp__239 = var_name_tmp__235;
  var_name_tmp__240 = var_name_tmp__234;
  var_name_tmp__241 = (&var_name_tmp__240->field8);
  var_name_tmp__242 = *(volatile uint16_t*)var_name_tmp__241;
  *(volatile uint16_t*)var_name_tmp__241 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__242)) | (((uint32_t)(uint16_t)var_name_tmp__239)))));
}


void USART_LINCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__243, uint32_t var_name_tmp__244) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__245;    /* Address-exposed local */
  uint32_t var_name_tmp__246;    /* Address-exposed local */
  uint32_t var_name_tmp__247;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__248;
  uint16_t* var_name_tmp__249;
  uint16_t var_name_tmp__250;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__251;
  uint16_t* var_name_tmp__252;
  uint16_t var_name_tmp__253;

  var_name_tmp__245 = var_name_tmp__243;
  var_name_tmp__246 = var_name_tmp__244;
  var_name_tmp__247 = var_name_tmp__246;
  if ((((var_name_tmp__247 != 0u)&1))) {
    goto var_name_tmp__254;
  } else {
    goto var_name_tmp__255;
  }

var_name_tmp__254:
  var_name_tmp__248 = var_name_tmp__245;
  var_name_tmp__249 = (&var_name_tmp__248->field8);
  var_name_tmp__250 = *(volatile uint16_t*)var_name_tmp__249;
  *(volatile uint16_t*)var_name_tmp__249 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__250)) | 16384)));
  goto var_name_tmp__256;

var_name_tmp__255:
  var_name_tmp__251 = var_name_tmp__245;
  var_name_tmp__252 = (&var_name_tmp__251->field8);
  var_name_tmp__253 = *(volatile uint16_t*)var_name_tmp__252;
  *(volatile uint16_t*)var_name_tmp__252 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__253)) & 49151)));
  goto var_name_tmp__256;

var_name_tmp__256:
  return;
}


void USART_SendBreak(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__257) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__258;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__259;
  uint16_t* var_name_tmp__260;
  uint16_t var_name_tmp__261;

  var_name_tmp__258 = var_name_tmp__257;
  var_name_tmp__259 = var_name_tmp__258;
  var_name_tmp__260 = (&var_name_tmp__259->field6);
  var_name_tmp__261 = *(volatile uint16_t*)var_name_tmp__260;
  *(volatile uint16_t*)var_name_tmp__260 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__261)) | 1)));
}


void USART_HalfDuplexCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__262, uint32_t var_name_tmp__263) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__264;    /* Address-exposed local */
  uint32_t var_name_tmp__265;    /* Address-exposed local */
  uint32_t var_name_tmp__266;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__267;
  uint16_t* var_name_tmp__268;
  uint16_t var_name_tmp__269;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__270;
  uint16_t* var_name_tmp__271;
  uint16_t var_name_tmp__272;

  var_name_tmp__264 = var_name_tmp__262;
  var_name_tmp__265 = var_name_tmp__263;
  var_name_tmp__266 = var_name_tmp__265;
  if ((((var_name_tmp__266 != 0u)&1))) {
    goto var_name_tmp__273;
  } else {
    goto var_name_tmp__274;
  }

var_name_tmp__273:
  var_name_tmp__267 = var_name_tmp__264;
  var_name_tmp__268 = (&var_name_tmp__267->field10);
  var_name_tmp__269 = *(volatile uint16_t*)var_name_tmp__268;
  *(volatile uint16_t*)var_name_tmp__268 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__269)) | 8)));
  goto var_name_tmp__275;

var_name_tmp__274:
  var_name_tmp__270 = var_name_tmp__264;
  var_name_tmp__271 = (&var_name_tmp__270->field10);
  var_name_tmp__272 = *(volatile uint16_t*)var_name_tmp__271;
  *(volatile uint16_t*)var_name_tmp__271 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__272)) & 65527)));
  goto var_name_tmp__275;

var_name_tmp__275:
  return;
}


void USART_SetGuardTime(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__276, uint8_t var_name_tmp__277) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__278;    /* Address-exposed local */
  uint8_t var_name_tmp__279;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__280;
  uint16_t* var_name_tmp__281;
  uint16_t var_name_tmp__282;
  uint8_t var_name_tmp__283;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__284;
  uint16_t* var_name_tmp__285;
  uint16_t var_name_tmp__286;

  var_name_tmp__278 = var_name_tmp__276;
  var_name_tmp__279 = var_name_tmp__277;
  var_name_tmp__280 = var_name_tmp__278;
  var_name_tmp__281 = (&var_name_tmp__280->field12);
  var_name_tmp__282 = *(volatile uint16_t*)var_name_tmp__281;
  *(volatile uint16_t*)var_name_tmp__281 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__282)) & 255)));
  var_name_tmp__283 = var_name_tmp__279;
  var_name_tmp__284 = var_name_tmp__278;
  var_name_tmp__285 = (&var_name_tmp__284->field12);
  var_name_tmp__286 = *(volatile uint16_t*)var_name_tmp__285;
  *(volatile uint16_t*)var_name_tmp__285 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__286)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__283)))) << 8))))))));
}


void USART_SmartCardCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__287, uint32_t var_name_tmp__288) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__289;    /* Address-exposed local */
  uint32_t var_name_tmp__290;    /* Address-exposed local */
  uint32_t var_name_tmp__291;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__292;
  uint16_t* var_name_tmp__293;
  uint16_t var_name_tmp__294;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__295;
  uint16_t* var_name_tmp__296;
  uint16_t var_name_tmp__297;

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
  var_name_tmp__293 = (&var_name_tmp__292->field10);
  var_name_tmp__294 = *(volatile uint16_t*)var_name_tmp__293;
  *(volatile uint16_t*)var_name_tmp__293 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__294)) | 32)));
  goto var_name_tmp__300;

var_name_tmp__299:
  var_name_tmp__295 = var_name_tmp__289;
  var_name_tmp__296 = (&var_name_tmp__295->field10);
  var_name_tmp__297 = *(volatile uint16_t*)var_name_tmp__296;
  *(volatile uint16_t*)var_name_tmp__296 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__297)) & 65503)));
  goto var_name_tmp__300;

var_name_tmp__300:
  return;
}


void USART_SmartCardNACKCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__301, uint32_t var_name_tmp__302) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__303;    /* Address-exposed local */
  uint32_t var_name_tmp__304;    /* Address-exposed local */
  uint32_t var_name_tmp__305;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__306;
  uint16_t* var_name_tmp__307;
  uint16_t var_name_tmp__308;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__309;
  uint16_t* var_name_tmp__310;
  uint16_t var_name_tmp__311;

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
  var_name_tmp__307 = (&var_name_tmp__306->field10);
  var_name_tmp__308 = *(volatile uint16_t*)var_name_tmp__307;
  *(volatile uint16_t*)var_name_tmp__307 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__308)) | 16)));
  goto var_name_tmp__314;

var_name_tmp__313:
  var_name_tmp__309 = var_name_tmp__303;
  var_name_tmp__310 = (&var_name_tmp__309->field10);
  var_name_tmp__311 = *(volatile uint16_t*)var_name_tmp__310;
  *(volatile uint16_t*)var_name_tmp__310 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__311)) & 65519)));
  goto var_name_tmp__314;

var_name_tmp__314:
  return;
}


void USART_IrDAConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__315, uint16_t var_name_tmp__316) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__317;    /* Address-exposed local */
  uint16_t var_name_tmp__318;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__319;
  uint16_t* var_name_tmp__320;
  uint16_t var_name_tmp__321;
  uint16_t var_name_tmp__322;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__323;
  uint16_t* var_name_tmp__324;
  uint16_t var_name_tmp__325;

  var_name_tmp__317 = var_name_tmp__315;
  var_name_tmp__318 = var_name_tmp__316;
  var_name_tmp__319 = var_name_tmp__317;
  var_name_tmp__320 = (&var_name_tmp__319->field10);
  var_name_tmp__321 = *(volatile uint16_t*)var_name_tmp__320;
  *(volatile uint16_t*)var_name_tmp__320 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__321)) & 65531)));
  var_name_tmp__322 = var_name_tmp__318;
  var_name_tmp__323 = var_name_tmp__317;
  var_name_tmp__324 = (&var_name_tmp__323->field10);
  var_name_tmp__325 = *(volatile uint16_t*)var_name_tmp__324;
  *(volatile uint16_t*)var_name_tmp__324 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__325)) | (((uint32_t)(uint16_t)var_name_tmp__322)))));
}


void USART_IrDACmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__326, uint32_t var_name_tmp__327) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__328;    /* Address-exposed local */
  uint32_t var_name_tmp__329;    /* Address-exposed local */
  uint32_t var_name_tmp__330;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__331;
  uint16_t* var_name_tmp__332;
  uint16_t var_name_tmp__333;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__334;
  uint16_t* var_name_tmp__335;
  uint16_t var_name_tmp__336;

  var_name_tmp__328 = var_name_tmp__326;
  var_name_tmp__329 = var_name_tmp__327;
  var_name_tmp__330 = var_name_tmp__329;
  if ((((var_name_tmp__330 != 0u)&1))) {
    goto var_name_tmp__337;
  } else {
    goto var_name_tmp__338;
  }

var_name_tmp__337:
  var_name_tmp__331 = var_name_tmp__328;
  var_name_tmp__332 = (&var_name_tmp__331->field10);
  var_name_tmp__333 = *(volatile uint16_t*)var_name_tmp__332;
  *(volatile uint16_t*)var_name_tmp__332 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__333)) | 2)));
  goto var_name_tmp__339;

var_name_tmp__338:
  var_name_tmp__334 = var_name_tmp__328;
  var_name_tmp__335 = (&var_name_tmp__334->field10);
  var_name_tmp__336 = *(volatile uint16_t*)var_name_tmp__335;
  *(volatile uint16_t*)var_name_tmp__335 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__336)) & 65533)));
  goto var_name_tmp__339;

var_name_tmp__339:
  return;
}


void USART_DMACmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__340, uint16_t var_name_tmp__341, uint32_t var_name_tmp__342) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__343;    /* Address-exposed local */
  uint16_t var_name_tmp__344;    /* Address-exposed local */
  uint32_t var_name_tmp__345;    /* Address-exposed local */
  uint32_t var_name_tmp__346;
  uint16_t var_name_tmp__347;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__348;
  uint16_t* var_name_tmp__349;
  uint16_t var_name_tmp__350;
  uint16_t var_name_tmp__351;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__352;
  uint16_t* var_name_tmp__353;
  uint16_t var_name_tmp__354;

  var_name_tmp__343 = var_name_tmp__340;
  var_name_tmp__344 = var_name_tmp__341;
  var_name_tmp__345 = var_name_tmp__342;
  var_name_tmp__346 = var_name_tmp__345;
  if ((((var_name_tmp__346 != 0u)&1))) {
    goto var_name_tmp__355;
  } else {
    goto var_name_tmp__356;
  }

var_name_tmp__355:
  var_name_tmp__347 = var_name_tmp__344;
  var_name_tmp__348 = var_name_tmp__343;
  var_name_tmp__349 = (&var_name_tmp__348->field10);
  var_name_tmp__350 = *(volatile uint16_t*)var_name_tmp__349;
  *(volatile uint16_t*)var_name_tmp__349 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__350)) | (((uint32_t)(uint16_t)var_name_tmp__347)))));
  goto var_name_tmp__357;

var_name_tmp__356:
  var_name_tmp__351 = var_name_tmp__344;
  var_name_tmp__352 = var_name_tmp__343;
  var_name_tmp__353 = (&var_name_tmp__352->field10);
  var_name_tmp__354 = *(volatile uint16_t*)var_name_tmp__353;
  *(volatile uint16_t*)var_name_tmp__353 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__354)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__351)))))))))));
  goto var_name_tmp__357;

var_name_tmp__357:
  return;
}


void USART_ITConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__358, uint16_t var_name_tmp__359, uint32_t var_name_tmp__360) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__361;    /* Address-exposed local */
  uint16_t var_name_tmp__362;    /* Address-exposed local */
  uint32_t var_name_tmp__363;    /* Address-exposed local */
  uint32_t var_name_tmp__364;    /* Address-exposed local */
  uint32_t var_name_tmp__365;    /* Address-exposed local */
  uint32_t var_name_tmp__366;    /* Address-exposed local */
  uint32_t var_name_tmp__367;    /* Address-exposed local */
  uint16_t var_name_tmp__368;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__369;
  uint16_t var_name_tmp__370;
  uint16_t var_name_tmp__371;
  uint32_t var_name_tmp__372;
  uint32_t var_name_tmp__373;
  uint32_t var_name_tmp__374;
  uint32_t var_name_tmp__375;
  uint32_t var_name_tmp__376;
  uint32_t var_name_tmp__377;
  uint32_t var_name_tmp__378;
  uint32_t var_name_tmp__379;
  uint32_t var_name_tmp__380;
  uint32_t* var_name_tmp__381;
  uint32_t var_name_tmp__382;
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint32_t* var_name_tmp__385;
  uint32_t var_name_tmp__386;

  var_name_tmp__361 = var_name_tmp__358;
  var_name_tmp__362 = var_name_tmp__359;
  var_name_tmp__363 = var_name_tmp__360;
  var_name_tmp__364 = 0;
  var_name_tmp__365 = 0;
  var_name_tmp__366 = 0;
  var_name_tmp__367 = 0;
  var_name_tmp__368 = var_name_tmp__362;
  if (((((((uint32_t)(uint16_t)var_name_tmp__368)) == 2410u)&1))) {
    goto var_name_tmp__387;
  } else {
    goto var_name_tmp__388;
  }

var_name_tmp__387:
  goto var_name_tmp__388;

var_name_tmp__388:
  var_name_tmp__369 = var_name_tmp__361;
  var_name_tmp__367 = (((uint32_t)(uintptr_t)var_name_tmp__369));
  var_name_tmp__370 = var_name_tmp__362;
  var_name_tmp__364 = (llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__370)))), 5));
  var_name_tmp__371 = var_name_tmp__362;
  var_name_tmp__365 = ((((uint32_t)(uint16_t)var_name_tmp__371)) & 31);
  var_name_tmp__372 = var_name_tmp__365;
  var_name_tmp__366 = (1 << var_name_tmp__372);
  var_name_tmp__373 = var_name_tmp__364;
  if ((((var_name_tmp__373 == 1u)&1))) {
    goto var_name_tmp__389;
  } else {
    goto var_name_tmp__390;
  }

var_name_tmp__389:
  var_name_tmp__374 = var_name_tmp__367;
  var_name_tmp__367 = (llvm_add_u32(var_name_tmp__374, 12));
  goto var_name_tmp__391;

var_name_tmp__390:
  var_name_tmp__375 = var_name_tmp__364;
  if ((((var_name_tmp__375 == 2u)&1))) {
    goto var_name_tmp__392;
  } else {
    goto var_name_tmp__393;
  }

var_name_tmp__392:
  var_name_tmp__376 = var_name_tmp__367;
  var_name_tmp__367 = (llvm_add_u32(var_name_tmp__376, 16));
  goto var_name_tmp__394;

var_name_tmp__393:
  var_name_tmp__377 = var_name_tmp__367;
  var_name_tmp__367 = (llvm_add_u32(var_name_tmp__377, 20));
  goto var_name_tmp__394;

var_name_tmp__394:
  goto var_name_tmp__391;

var_name_tmp__391:
  var_name_tmp__378 = var_name_tmp__363;
  if ((((var_name_tmp__378 != 0u)&1))) {
    goto var_name_tmp__395;
  } else {
    goto var_name_tmp__396;
  }

var_name_tmp__395:
  var_name_tmp__379 = var_name_tmp__366;
  var_name_tmp__380 = var_name_tmp__367;
  var_name_tmp__381 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__380)));
  var_name_tmp__382 = *(volatile uint32_t*)var_name_tmp__381;
  *(volatile uint32_t*)var_name_tmp__381 = (var_name_tmp__382 | var_name_tmp__379);
  goto var_name_tmp__397;

var_name_tmp__396:
  var_name_tmp__383 = var_name_tmp__366;
  var_name_tmp__384 = var_name_tmp__367;
  var_name_tmp__385 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__384)));
  var_name_tmp__386 = *(volatile uint32_t*)var_name_tmp__385;
  *(volatile uint32_t*)var_name_tmp__385 = (var_name_tmp__386 & (~(var_name_tmp__383)));
  goto var_name_tmp__397;

var_name_tmp__397:
  return;
}


uint32_t USART_GetFlagStatus(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__398, uint16_t var_name_tmp__399) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__400;    /* Address-exposed local */
  uint16_t var_name_tmp__401;    /* Address-exposed local */
  uint32_t var_name_tmp__402;    /* Address-exposed local */
  uint16_t var_name_tmp__403;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__404;
  uint16_t var_name_tmp__405;
  uint16_t var_name_tmp__406;
  uint32_t var_name_tmp__407;

  var_name_tmp__400 = var_name_tmp__398;
  var_name_tmp__401 = var_name_tmp__399;
  var_name_tmp__402 = 0;
  var_name_tmp__403 = var_name_tmp__401;
  if (((((((uint32_t)(uint16_t)var_name_tmp__403)) == 512u)&1))) {
    goto var_name_tmp__408;
  } else {
    goto var_name_tmp__409;
  }

var_name_tmp__408:
  goto var_name_tmp__409;

var_name_tmp__409:
  var_name_tmp__404 = var_name_tmp__400;
  var_name_tmp__405 = *(volatile uint16_t*)((&var_name_tmp__404->field0));
  var_name_tmp__406 = var_name_tmp__401;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__405)) & (((uint32_t)(uint16_t)var_name_tmp__406))) != 0u)&1))) {
    goto var_name_tmp__410;
  } else {
    goto var_name_tmp__411;
  }

var_name_tmp__410:
  var_name_tmp__402 = 1;
  goto var_name_tmp__412;

var_name_tmp__411:
  var_name_tmp__402 = 0;
  goto var_name_tmp__412;

var_name_tmp__412:
  var_name_tmp__407 = var_name_tmp__402;
  return var_name_tmp__407;
}


void USART_ClearFlag(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__413, uint16_t var_name_tmp__414) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__415;    /* Address-exposed local */
  uint16_t var_name_tmp__416;    /* Address-exposed local */
  uint16_t var_name_tmp__417;
  uint16_t var_name_tmp__418;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__419;

  var_name_tmp__415 = var_name_tmp__413;
  var_name_tmp__416 = var_name_tmp__414;
  var_name_tmp__417 = var_name_tmp__416;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__417)) & 512) == 512u)&1))) {
    goto var_name_tmp__420;
  } else {
    goto var_name_tmp__421;
  }

var_name_tmp__420:
  goto var_name_tmp__421;

var_name_tmp__421:
  var_name_tmp__418 = var_name_tmp__416;
  var_name_tmp__419 = var_name_tmp__415;
  *(volatile uint16_t*)((&var_name_tmp__419->field0)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__418))))));
}


uint32_t USART_GetITStatus(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__422, uint16_t var_name_tmp__423) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__424;    /* Address-exposed local */
  uint16_t var_name_tmp__425;    /* Address-exposed local */
  uint32_t var_name_tmp__426;    /* Address-exposed local */
  uint32_t var_name_tmp__427;    /* Address-exposed local */
  uint32_t var_name_tmp__428;    /* Address-exposed local */
  uint32_t var_name_tmp__429;    /* Address-exposed local */
  uint16_t var_name_tmp__430;
  uint16_t var_name_tmp__431;
  uint16_t var_name_tmp__432;
  uint32_t var_name_tmp__433;
  uint32_t var_name_tmp__434;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__435;
  uint16_t var_name_tmp__436;
  uint32_t var_name_tmp__437;
  uint32_t var_name_tmp__438;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__439;
  uint16_t var_name_tmp__440;
  uint32_t var_name_tmp__441;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__442;
  uint16_t var_name_tmp__443;
  uint32_t var_name_tmp__444;
  uint16_t var_name_tmp__445;
  uint32_t var_name_tmp__446;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__447;
  uint16_t var_name_tmp__448;
  uint32_t var_name_tmp__449;
  uint32_t var_name_tmp__450;
  uint32_t var_name_tmp__451;
  uint32_t var_name_tmp__452;

  var_name_tmp__424 = var_name_tmp__422;
  var_name_tmp__425 = var_name_tmp__423;
  var_name_tmp__426 = 0;
  var_name_tmp__427 = 0;
  var_name_tmp__428 = 0;
  var_name_tmp__429 = 0;
  var_name_tmp__430 = var_name_tmp__425;
  if (((((((uint32_t)(uint16_t)var_name_tmp__430)) == 2410u)&1))) {
    goto var_name_tmp__453;
  } else {
    goto var_name_tmp__454;
  }

var_name_tmp__453:
  goto var_name_tmp__454;

var_name_tmp__454:
  var_name_tmp__431 = var_name_tmp__425;
  var_name_tmp__428 = (llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__431)))), 5));
  var_name_tmp__432 = var_name_tmp__425;
  var_name_tmp__427 = ((((uint32_t)(uint16_t)var_name_tmp__432)) & 31);
  var_name_tmp__433 = var_name_tmp__427;
  var_name_tmp__427 = (1 << var_name_tmp__433);
  var_name_tmp__434 = var_name_tmp__428;
  if ((((var_name_tmp__434 == 1u)&1))) {
    goto var_name_tmp__455;
  } else {
    goto var_name_tmp__456;
  }

var_name_tmp__455:
  var_name_tmp__435 = var_name_tmp__424;
  var_name_tmp__436 = *(volatile uint16_t*)((&var_name_tmp__435->field6));
  var_name_tmp__437 = var_name_tmp__427;
  var_name_tmp__427 = (var_name_tmp__437 & (((uint32_t)(uint16_t)var_name_tmp__436)));
  goto var_name_tmp__457;

var_name_tmp__456:
  var_name_tmp__438 = var_name_tmp__428;
  if ((((var_name_tmp__438 == 2u)&1))) {
    goto var_name_tmp__458;
  } else {
    goto var_name_tmp__459;
  }

var_name_tmp__458:
  var_name_tmp__439 = var_name_tmp__424;
  var_name_tmp__440 = *(volatile uint16_t*)((&var_name_tmp__439->field8));
  var_name_tmp__441 = var_name_tmp__427;
  var_name_tmp__427 = (var_name_tmp__441 & (((uint32_t)(uint16_t)var_name_tmp__440)));
  goto var_name_tmp__460;

var_name_tmp__459:
  var_name_tmp__442 = var_name_tmp__424;
  var_name_tmp__443 = *(volatile uint16_t*)((&var_name_tmp__442->field10));
  var_name_tmp__444 = var_name_tmp__427;
  var_name_tmp__427 = (var_name_tmp__444 & (((uint32_t)(uint16_t)var_name_tmp__443)));
  goto var_name_tmp__460;

var_name_tmp__460:
  goto var_name_tmp__457;

var_name_tmp__457:
  var_name_tmp__445 = var_name_tmp__425;
  var_name_tmp__426 = (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__445)), 8));
  var_name_tmp__446 = var_name_tmp__426;
  var_name_tmp__426 = (1 << var_name_tmp__446);
  var_name_tmp__447 = var_name_tmp__424;
  var_name_tmp__448 = *(volatile uint16_t*)((&var_name_tmp__447->field0));
  var_name_tmp__449 = var_name_tmp__426;
  var_name_tmp__426 = (var_name_tmp__449 & (((uint32_t)(uint16_t)var_name_tmp__448)));
  var_name_tmp__450 = var_name_tmp__427;
  if ((((var_name_tmp__450 != 0u)&1))) {
    goto var_name_tmp__461;
  } else {
    goto var_name_tmp__462;
  }

var_name_tmp__461:
  var_name_tmp__451 = var_name_tmp__426;
  if ((((var_name_tmp__451 != 0u)&1))) {
    goto var_name_tmp__463;
  } else {
    goto var_name_tmp__462;
  }

var_name_tmp__463:
  var_name_tmp__429 = 1;
  goto var_name_tmp__464;

var_name_tmp__462:
  var_name_tmp__429 = 0;
  goto var_name_tmp__464;

var_name_tmp__464:
  var_name_tmp__452 = var_name_tmp__429;
  return var_name_tmp__452;
}


void USART_ClearITPendingBit(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__465, uint16_t var_name_tmp__466) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__467;    /* Address-exposed local */
  uint16_t var_name_tmp__468;    /* Address-exposed local */
  uint16_t var_name_tmp__469;    /* Address-exposed local */
  uint16_t var_name_tmp__470;    /* Address-exposed local */
  uint16_t var_name_tmp__471;
  uint16_t var_name_tmp__472;
  uint16_t var_name_tmp__473;
  uint16_t var_name_tmp__474;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__475;

  var_name_tmp__467 = var_name_tmp__465;
  var_name_tmp__468 = var_name_tmp__466;
  var_name_tmp__469 = 0;
  var_name_tmp__470 = 0;
  var_name_tmp__471 = var_name_tmp__468;
  if (((((((uint32_t)(uint16_t)var_name_tmp__471)) == 2410u)&1))) {
    goto var_name_tmp__476;
  } else {
    goto var_name_tmp__477;
  }

var_name_tmp__476:
  goto var_name_tmp__477;

var_name_tmp__477:
  var_name_tmp__472 = var_name_tmp__468;
  var_name_tmp__469 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__472)), 8))));
  var_name_tmp__473 = var_name_tmp__469;
  var_name_tmp__470 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__473)))));
  var_name_tmp__474 = var_name_tmp__470;
  var_name_tmp__475 = var_name_tmp__467;
  *(volatile uint16_t*)((&var_name_tmp__475->field0)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__474))))));
}

