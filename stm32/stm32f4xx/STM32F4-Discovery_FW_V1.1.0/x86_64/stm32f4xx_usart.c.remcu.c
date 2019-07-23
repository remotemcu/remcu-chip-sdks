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
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__36;
  uint64_t var_name_load_i16_2;
  uint32_t var_name_tmp__37;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__38;
  uint64_t var_name_load_i16_5;
  uint32_t var_name_tmp__39;
  uint32_t var_name_tmp__40;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__41;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__42;
  uint64_t var_name_load_i16_9;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__44;
  uint64_t var_name_load_i16_12;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__45;
  uint64_t var_name_load_i16_15;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__46;
  uint64_t var_name_load_i16_18;
  uint32_t var_name_tmp__47;
  uint32_t var_name_tmp__48;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__49;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__50;
  uint64_t var_name_load_i16_23;
  uint32_t var_name_tmp__51;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__52;
  uint64_t var_name_load_i16_26;
  uint32_t var_name_tmp__53;
  uint32_t var_name_tmp__54;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__55;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__56;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__57;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_31;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__58;
  uint64_t var_name_load_i16_34;
  uint32_t var_name_tmp__59;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__60;
  uint64_t var_name_load_i32_37;
  uint32_t var_name_tmp__61;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__62;
  uint64_t var_name_load_i32_40;
  uint32_t var_name_tmp__63;
  uint32_t var_name_tmp__64;
  uint32_t var_name_tmp__65;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__66;
  uint64_t var_name_load_i16_43;
  uint32_t var_name_tmp__67;
  uint32_t var_name_tmp__68;
  uint32_t var_name_tmp__69;
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__72;

  var_name_tmp__28 = var_name_tmp__26;
  var_name_tmp__29 = var_name_tmp__27;
  var_name_tmp__30 = 0;
  var_name_tmp__31 = 0;
  var_name_tmp__32 = 0;
  var_name_tmp__33 = 0;
  var_name_tmp__35 = var_name_tmp__29;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__35->field5)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) != 0u)&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  goto var_name_tmp__74;

var_name_tmp__74:
  var_name_tmp__36 = var_name_tmp__28;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__36->field8)))), 16, 2);
  var_name_tmp__30 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2))));
  var_name_tmp__37 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__37 & -12289);
  var_name_tmp__38 = var_name_tmp__29;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__38->field2)))), 16, 2);
  var_name_tmp__39 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__39 | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5)))));
  var_name_tmp__40 = var_name_tmp__30;
  var_name_tmp__41 = var_name_tmp__28;
  __adin_store_((((uint8_t*)((&var_name_tmp__41->field8)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_tmp__40)))), 16, 2);
  var_name_tmp__42 = var_name_tmp__28;
  var_name_load_i16_9 = __adin_load_((((uint8_t*)((&var_name_tmp__42->field6)))), 16, 2);
  var_name_tmp__30 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_9))));
  var_name_tmp__43 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__43 & -5645);
  var_name_tmp__44 = var_name_tmp__29;
  var_name_load_i16_12 = __adin_load_((((uint8_t*)((&var_name_tmp__44->field1)))), 16, 4);
  var_name_tmp__45 = var_name_tmp__29;
  var_name_load_i16_15 = __adin_load_((((uint8_t*)((&var_name_tmp__45->field3)))), 16, 4);
  var_name_tmp__46 = var_name_tmp__29;
  var_name_load_i16_18 = __adin_load_((((uint8_t*)((&var_name_tmp__46->field4)))), 16, 2);
  var_name_tmp__47 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__47 | (((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_12)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_15))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_18))))));
  var_name_tmp__48 = var_name_tmp__30;
  var_name_tmp__49 = var_name_tmp__28;
  __adin_store_((((uint8_t*)((&var_name_tmp__49->field6)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_tmp__48)))), 16, 2);
  var_name_tmp__50 = var_name_tmp__28;
  var_name_load_i16_23 = __adin_load_((((uint8_t*)((&var_name_tmp__50->field10)))), 16, 2);
  var_name_tmp__30 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_23))));
  var_name_tmp__51 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__51 & -769);
  var_name_tmp__52 = var_name_tmp__29;
  var_name_load_i16_26 = __adin_load_((((uint8_t*)((&var_name_tmp__52->field5)))), 16, 4);
  var_name_tmp__53 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__53 | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_26)))));
  var_name_tmp__54 = var_name_tmp__30;
  var_name_tmp__55 = var_name_tmp__28;
  __adin_store_((((uint8_t*)((&var_name_tmp__55->field10)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_tmp__54)))), 16, 2);
  RCC_GetClocksFreq((&var_name_tmp__34));
  var_name_tmp__56 = var_name_tmp__28;
  if ((((var_name_tmp__56 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073811456)))&1))) {
    goto var_name_tmp__75;
  } else {
    goto var_name_tmp__76;
  }

var_name_tmp__76:
  var_name_tmp__57 = var_name_tmp__28;
  if ((((var_name_tmp__57 == ((struct l_struct_struct_OC_USART_TypeDef*)(uintptr_t)UINT64_C(1073812480)))&1))) {
    goto var_name_tmp__75;
  } else {
    goto var_name_tmp__77;
  }

var_name_tmp__75:
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__34.field3)))), 32, 4);
  var_name_tmp__31 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__78;

var_name_tmp__77:
  var_name_load_i32_31 = __adin_load_((((uint8_t*)((&var_name_tmp__34.field2)))), 32, 4);
  var_name_tmp__31 = (((uint32_t)var_name_load_i32_31));
  goto var_name_tmp__78;

var_name_tmp__78:
  var_name_tmp__58 = var_name_tmp__28;
  var_name_load_i16_34 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field6)))), 16, 2);
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_34)))) & 32768) != 0u)&1))) {
    goto var_name_tmp__79;
  } else {
    goto var_name_tmp__80;
  }

var_name_tmp__79:
  var_name_tmp__59 = var_name_tmp__31;
  var_name_tmp__60 = var_name_tmp__29;
  var_name_load_i32_37 = __adin_load_((((uint8_t*)((&var_name_tmp__60->field0)))), 32, 4);
  var_name_tmp__32 = (llvm_udiv_u32((llvm_mul_u32(25, var_name_tmp__59)), (llvm_mul_u32(2, (((uint32_t)var_name_load_i32_37))))));
  goto var_name_tmp__81;

var_name_tmp__80:
  var_name_tmp__61 = var_name_tmp__31;
  var_name_tmp__62 = var_name_tmp__29;
  var_name_load_i32_40 = __adin_load_((((uint8_t*)((&var_name_tmp__62->field0)))), 32, 4);
  var_name_tmp__32 = (llvm_udiv_u32((llvm_mul_u32(25, var_name_tmp__61)), (llvm_mul_u32(4, (((uint32_t)var_name_load_i32_40))))));
  goto var_name_tmp__81;

var_name_tmp__81:
  var_name_tmp__63 = var_name_tmp__32;
  var_name_tmp__30 = ((llvm_udiv_u32(var_name_tmp__63, 100)) << 4);
  var_name_tmp__64 = var_name_tmp__32;
  var_name_tmp__65 = var_name_tmp__30;
  var_name_tmp__33 = (llvm_sub_u32(var_name_tmp__64, (llvm_mul_u32(100, (llvm_lshr_u32(var_name_tmp__65, 4))))));
  var_name_tmp__66 = var_name_tmp__28;
  var_name_load_i16_43 = __adin_load_((((uint8_t*)((&var_name_tmp__66->field6)))), 16, 2);
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_43)))) & 32768) != 0u)&1))) {
    goto var_name_tmp__82;
  } else {
    goto var_name_tmp__83;
  }

var_name_tmp__82:
  var_name_tmp__67 = var_name_tmp__33;
  var_name_tmp__68 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__68 | ((llvm_udiv_u32((llvm_add_u32((llvm_mul_u32(var_name_tmp__67, 8)), 50)), 100)) & 7));
  goto var_name_tmp__84;

var_name_tmp__83:
  var_name_tmp__69 = var_name_tmp__33;
  var_name_tmp__70 = var_name_tmp__30;
  var_name_tmp__30 = (var_name_tmp__70 | ((llvm_udiv_u32((llvm_add_u32((llvm_mul_u32(var_name_tmp__69, 16)), 50)), 100)) & 15));
  goto var_name_tmp__84;

var_name_tmp__84:
  var_name_tmp__71 = var_name_tmp__30;
  var_name_tmp__72 = var_name_tmp__28;
  __adin_store_((((uint8_t*)((&var_name_tmp__72->field4)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_tmp__71)))), 16, 2);
}


void USART_StructInit(struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__85) {
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__86;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__87;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__88;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__89;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__90;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__91;
  struct l_struct_struct_OC_USART_InitTypeDef* var_name_tmp__92;

  var_name_tmp__86 = var_name_tmp__85;
  var_name_tmp__87 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__87->field0)))), UINT64_C(9600), 32, 4);
  var_name_tmp__88 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__88->field1)))), UINT64_C(0), 16, 4);
  var_name_tmp__89 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__89->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__90 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__90->field3)))), UINT64_C(0), 16, 4);
  var_name_tmp__91 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__91->field4)))), UINT64_C(12), 16, 2);
  var_name_tmp__92 = var_name_tmp__86;
  __adin_store_((((uint8_t*)((&var_name_tmp__92->field5)))), UINT64_C(0), 16, 4);
}


void USART_ClockInit(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__93, struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__94) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__95;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__96;    /* Address-exposed local */
  uint32_t var_name_tmp__97;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__98;
  uint64_t var_name_load_i16_;
  uint32_t var_name_tmp__99;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__100;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__101;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__102;
  uint64_t var_name_load_i16_8;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__103;
  uint64_t var_name_load_i16_11;
  uint32_t var_name_tmp__104;
  uint32_t var_name_tmp__105;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__106;

  var_name_tmp__95 = var_name_tmp__93;
  var_name_tmp__96 = var_name_tmp__94;
  var_name_tmp__97 = 0;
  var_name_tmp__98 = var_name_tmp__95;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__98->field8)))), 16, 2);
  var_name_tmp__97 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_))));
  var_name_tmp__99 = var_name_tmp__97;
  var_name_tmp__97 = (var_name_tmp__99 & -3841);
  var_name_tmp__100 = var_name_tmp__96;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__100->field0)))), 16, 2);
  var_name_tmp__101 = var_name_tmp__96;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__101->field1)))), 16, 2);
  var_name_tmp__102 = var_name_tmp__96;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__102->field2)))), 16, 2);
  var_name_tmp__103 = var_name_tmp__96;
  var_name_load_i16_11 = __adin_load_((((uint8_t*)((&var_name_tmp__103->field3)))), 16, 2);
  var_name_tmp__104 = var_name_tmp__97;
  var_name_tmp__97 = (var_name_tmp__104 | ((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_11))))));
  var_name_tmp__105 = var_name_tmp__97;
  var_name_tmp__106 = var_name_tmp__95;
  __adin_store_((((uint8_t*)((&var_name_tmp__106->field8)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_tmp__105)))), 16, 2);
}


void USART_ClockStructInit(struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__107) {
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__108;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__109;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_USART_ClockInitTypeDef* var_name_tmp__112;

  var_name_tmp__108 = var_name_tmp__107;
  var_name_tmp__109 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__109->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__110 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__110->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__111 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__111->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__112 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__112->field3)))), UINT64_C(0), 16, 2);
}


void USART_Cmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__113, uint32_t var_name_tmp__114) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;    /* Address-exposed local */
  uint32_t var_name_tmp__117;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__118;
  uint16_t* var_name_tmp__119;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__120;
  uint16_t* var_name_tmp__121;
  uint64_t var_name_load_i16_3;

  var_name_tmp__115 = var_name_tmp__113;
  var_name_tmp__116 = var_name_tmp__114;
  var_name_tmp__117 = var_name_tmp__116;
  if ((((var_name_tmp__117 != 0u)&1))) {
    goto var_name_tmp__122;
  } else {
    goto var_name_tmp__123;
  }

var_name_tmp__122:
  var_name_tmp__118 = var_name_tmp__115;
  var_name_tmp__119 = (&var_name_tmp__118->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__119)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__119)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 8192))))), 16, 2);
  goto var_name_tmp__124;

var_name_tmp__123:
  var_name_tmp__120 = var_name_tmp__115;
  var_name_tmp__121 = (&var_name_tmp__120->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__121)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__121)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 57343))))), 16, 2);
  goto var_name_tmp__124;

var_name_tmp__124:
  return;
}


void USART_SetPrescaler(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__125, uint8_t var_name_tmp__126) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__127;    /* Address-exposed local */
  uint8_t var_name_tmp__128;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__129;
  uint16_t* var_name_tmp__130;
  uint64_t var_name_load_i16_;
  uint8_t var_name_tmp__131;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__132;
  uint16_t* var_name_tmp__133;
  uint64_t var_name_load_i16_3;

  var_name_tmp__127 = var_name_tmp__125;
  var_name_tmp__128 = var_name_tmp__126;
  var_name_tmp__129 = var_name_tmp__127;
  var_name_tmp__130 = (&var_name_tmp__129->field12);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__130)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__130)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65280))))), 16, 2);
  var_name_tmp__131 = var_name_tmp__128;
  var_name_tmp__132 = var_name_tmp__127;
  var_name_tmp__133 = (&var_name_tmp__132->field12);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__133)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__133)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint8_t)var_name_tmp__131))))))), 16, 2);
}


void USART_OverSampling8Cmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__134, uint32_t var_name_tmp__135) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;    /* Address-exposed local */
  uint32_t var_name_tmp__138;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__139;
  uint16_t* var_name_tmp__140;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__141;
  uint16_t* var_name_tmp__142;
  uint64_t var_name_load_i16_3;

  var_name_tmp__136 = var_name_tmp__134;
  var_name_tmp__137 = var_name_tmp__135;
  var_name_tmp__138 = var_name_tmp__137;
  if ((((var_name_tmp__138 != 0u)&1))) {
    goto var_name_tmp__143;
  } else {
    goto var_name_tmp__144;
  }

var_name_tmp__143:
  var_name_tmp__139 = var_name_tmp__136;
  var_name_tmp__140 = (&var_name_tmp__139->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__140)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__140)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 32768))))), 16, 2);
  goto var_name_tmp__145;

var_name_tmp__144:
  var_name_tmp__141 = var_name_tmp__136;
  var_name_tmp__142 = (&var_name_tmp__141->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__142)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__142)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 32767))))), 16, 2);
  goto var_name_tmp__145;

var_name_tmp__145:
  return;
}


void USART_OneBitMethodCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__146, uint32_t var_name_tmp__147) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__148;    /* Address-exposed local */
  uint32_t var_name_tmp__149;    /* Address-exposed local */
  uint32_t var_name_tmp__150;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__151;
  uint16_t* var_name_tmp__152;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__153;
  uint16_t* var_name_tmp__154;
  uint64_t var_name_load_i16_3;

  var_name_tmp__148 = var_name_tmp__146;
  var_name_tmp__149 = var_name_tmp__147;
  var_name_tmp__150 = var_name_tmp__149;
  if ((((var_name_tmp__150 != 0u)&1))) {
    goto var_name_tmp__155;
  } else {
    goto var_name_tmp__156;
  }

var_name_tmp__155:
  var_name_tmp__151 = var_name_tmp__148;
  var_name_tmp__152 = (&var_name_tmp__151->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__152)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__152)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2048))))), 16, 2);
  goto var_name_tmp__157;

var_name_tmp__156:
  var_name_tmp__153 = var_name_tmp__148;
  var_name_tmp__154 = (&var_name_tmp__153->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__154)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__154)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 63487))))), 16, 2);
  goto var_name_tmp__157;

var_name_tmp__157:
  return;
}


void USART_SendData(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__158, uint16_t var_name_tmp__159) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__160;    /* Address-exposed local */
  uint16_t var_name_tmp__161;    /* Address-exposed local */
  uint16_t var_name_tmp__162;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__163;

  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__159;
  var_name_tmp__162 = var_name_tmp__161;
  var_name_tmp__163 = var_name_tmp__160;
  __adin_store_((((uint8_t*)((&var_name_tmp__163->field2)))), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__162)) & 511))))), 16, 2);
}


uint16_t USART_ReceiveData(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__164) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__165;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__166;
  uint64_t var_name_load_i16_;

  var_name_tmp__165 = var_name_tmp__164;
  var_name_tmp__166 = var_name_tmp__165;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__166->field2)))), 16, 2);
  return (((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 511)));
}


void USART_SetAddress(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__167, uint8_t var_name_tmp__168) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__169;    /* Address-exposed local */
  uint8_t var_name_tmp__170;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__171;
  uint16_t* var_name_tmp__172;
  uint64_t var_name_load_i16_;
  uint8_t var_name_tmp__173;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__174;
  uint16_t* var_name_tmp__175;
  uint64_t var_name_load_i16_3;

  var_name_tmp__169 = var_name_tmp__167;
  var_name_tmp__170 = var_name_tmp__168;
  var_name_tmp__171 = var_name_tmp__169;
  var_name_tmp__172 = (&var_name_tmp__171->field8);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__172)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__172)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65520))))), 16, 2);
  var_name_tmp__173 = var_name_tmp__170;
  var_name_tmp__174 = var_name_tmp__169;
  var_name_tmp__175 = (&var_name_tmp__174->field8);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__175)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__175)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint8_t)var_name_tmp__173))))))), 16, 2);
}


void USART_ReceiverWakeUpCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__176, uint32_t var_name_tmp__177) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__178;    /* Address-exposed local */
  uint32_t var_name_tmp__179;    /* Address-exposed local */
  uint32_t var_name_tmp__180;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__181;
  uint16_t* var_name_tmp__182;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__183;
  uint16_t* var_name_tmp__184;
  uint64_t var_name_load_i16_3;

  var_name_tmp__178 = var_name_tmp__176;
  var_name_tmp__179 = var_name_tmp__177;
  var_name_tmp__180 = var_name_tmp__179;
  if ((((var_name_tmp__180 != 0u)&1))) {
    goto var_name_tmp__185;
  } else {
    goto var_name_tmp__186;
  }

var_name_tmp__185:
  var_name_tmp__181 = var_name_tmp__178;
  var_name_tmp__182 = (&var_name_tmp__181->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__182)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__182)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2))))), 16, 2);
  goto var_name_tmp__187;

var_name_tmp__186:
  var_name_tmp__183 = var_name_tmp__178;
  var_name_tmp__184 = (&var_name_tmp__183->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__184)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__184)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65533))))), 16, 2);
  goto var_name_tmp__187;

var_name_tmp__187:
  return;
}


void USART_WakeUpConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__188, uint16_t var_name_tmp__189) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__190;    /* Address-exposed local */
  uint16_t var_name_tmp__191;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__192;
  uint16_t* var_name_tmp__193;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__194;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__195;
  uint16_t* var_name_tmp__196;
  uint64_t var_name_load_i16_3;

  var_name_tmp__190 = var_name_tmp__188;
  var_name_tmp__191 = var_name_tmp__189;
  var_name_tmp__192 = var_name_tmp__190;
  var_name_tmp__193 = (&var_name_tmp__192->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__193)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__193)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 63487))))), 16, 2);
  var_name_tmp__194 = var_name_tmp__191;
  var_name_tmp__195 = var_name_tmp__190;
  var_name_tmp__196 = (&var_name_tmp__195->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__196)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__196)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__194))))))), 16, 2);
}


void USART_LINBreakDetectLengthConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__197, uint16_t var_name_tmp__198) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__199;    /* Address-exposed local */
  uint16_t var_name_tmp__200;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__201;
  uint16_t* var_name_tmp__202;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__203;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__204;
  uint16_t* var_name_tmp__205;
  uint64_t var_name_load_i16_3;

  var_name_tmp__199 = var_name_tmp__197;
  var_name_tmp__200 = var_name_tmp__198;
  var_name_tmp__201 = var_name_tmp__199;
  var_name_tmp__202 = (&var_name_tmp__201->field8);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__202)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__202)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65503))))), 16, 2);
  var_name_tmp__203 = var_name_tmp__200;
  var_name_tmp__204 = var_name_tmp__199;
  var_name_tmp__205 = (&var_name_tmp__204->field8);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__205)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__205)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__203))))))), 16, 2);
}


void USART_LINCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__206, uint32_t var_name_tmp__207) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__208;    /* Address-exposed local */
  uint32_t var_name_tmp__209;    /* Address-exposed local */
  uint32_t var_name_tmp__210;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__211;
  uint16_t* var_name_tmp__212;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__213;
  uint16_t* var_name_tmp__214;
  uint64_t var_name_load_i16_3;

  var_name_tmp__208 = var_name_tmp__206;
  var_name_tmp__209 = var_name_tmp__207;
  var_name_tmp__210 = var_name_tmp__209;
  if ((((var_name_tmp__210 != 0u)&1))) {
    goto var_name_tmp__215;
  } else {
    goto var_name_tmp__216;
  }

var_name_tmp__215:
  var_name_tmp__211 = var_name_tmp__208;
  var_name_tmp__212 = (&var_name_tmp__211->field8);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__212)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__212)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16384))))), 16, 2);
  goto var_name_tmp__217;

var_name_tmp__216:
  var_name_tmp__213 = var_name_tmp__208;
  var_name_tmp__214 = (&var_name_tmp__213->field8);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__214)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__214)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 49151))))), 16, 2);
  goto var_name_tmp__217;

var_name_tmp__217:
  return;
}


void USART_SendBreak(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__218) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__219;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__220;
  uint16_t* var_name_tmp__221;
  uint64_t var_name_load_i16_;

  var_name_tmp__219 = var_name_tmp__218;
  var_name_tmp__220 = var_name_tmp__219;
  var_name_tmp__221 = (&var_name_tmp__220->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__221)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__221)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1))))), 16, 2);
}


void USART_HalfDuplexCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__222, uint32_t var_name_tmp__223) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__224;    /* Address-exposed local */
  uint32_t var_name_tmp__225;    /* Address-exposed local */
  uint32_t var_name_tmp__226;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__227;
  uint16_t* var_name_tmp__228;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__229;
  uint16_t* var_name_tmp__230;
  uint64_t var_name_load_i16_3;

  var_name_tmp__224 = var_name_tmp__222;
  var_name_tmp__225 = var_name_tmp__223;
  var_name_tmp__226 = var_name_tmp__225;
  if ((((var_name_tmp__226 != 0u)&1))) {
    goto var_name_tmp__231;
  } else {
    goto var_name_tmp__232;
  }

var_name_tmp__231:
  var_name_tmp__227 = var_name_tmp__224;
  var_name_tmp__228 = (&var_name_tmp__227->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__228)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__228)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 8))))), 16, 2);
  goto var_name_tmp__233;

var_name_tmp__232:
  var_name_tmp__229 = var_name_tmp__224;
  var_name_tmp__230 = (&var_name_tmp__229->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__230)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__230)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65527))))), 16, 2);
  goto var_name_tmp__233;

var_name_tmp__233:
  return;
}


void USART_SetGuardTime(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__234, uint8_t var_name_tmp__235) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__236;    /* Address-exposed local */
  uint8_t var_name_tmp__237;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__238;
  uint16_t* var_name_tmp__239;
  uint64_t var_name_load_i16_;
  uint8_t var_name_tmp__240;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__241;
  uint16_t* var_name_tmp__242;
  uint64_t var_name_load_i16_3;

  var_name_tmp__236 = var_name_tmp__234;
  var_name_tmp__237 = var_name_tmp__235;
  var_name_tmp__238 = var_name_tmp__236;
  var_name_tmp__239 = (&var_name_tmp__238->field12);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__239)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__239)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 255))))), 16, 2);
  var_name_tmp__240 = var_name_tmp__237;
  var_name_tmp__241 = var_name_tmp__236;
  var_name_tmp__242 = (&var_name_tmp__241->field12);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__242)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__242)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__240)))) << 8)))))))))), 16, 2);
}


void USART_SmartCardCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__243, uint32_t var_name_tmp__244) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__245;    /* Address-exposed local */
  uint32_t var_name_tmp__246;    /* Address-exposed local */
  uint32_t var_name_tmp__247;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__248;
  uint16_t* var_name_tmp__249;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__250;
  uint16_t* var_name_tmp__251;
  uint64_t var_name_load_i16_3;

  var_name_tmp__245 = var_name_tmp__243;
  var_name_tmp__246 = var_name_tmp__244;
  var_name_tmp__247 = var_name_tmp__246;
  if ((((var_name_tmp__247 != 0u)&1))) {
    goto var_name_tmp__252;
  } else {
    goto var_name_tmp__253;
  }

var_name_tmp__252:
  var_name_tmp__248 = var_name_tmp__245;
  var_name_tmp__249 = (&var_name_tmp__248->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__249)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__249)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 32))))), 16, 2);
  goto var_name_tmp__254;

var_name_tmp__253:
  var_name_tmp__250 = var_name_tmp__245;
  var_name_tmp__251 = (&var_name_tmp__250->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__251)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__251)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65503))))), 16, 2);
  goto var_name_tmp__254;

var_name_tmp__254:
  return;
}


void USART_SmartCardNACKCmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__255, uint32_t var_name_tmp__256) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__257;    /* Address-exposed local */
  uint32_t var_name_tmp__258;    /* Address-exposed local */
  uint32_t var_name_tmp__259;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__260;
  uint16_t* var_name_tmp__261;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__262;
  uint16_t* var_name_tmp__263;
  uint64_t var_name_load_i16_3;

  var_name_tmp__257 = var_name_tmp__255;
  var_name_tmp__258 = var_name_tmp__256;
  var_name_tmp__259 = var_name_tmp__258;
  if ((((var_name_tmp__259 != 0u)&1))) {
    goto var_name_tmp__264;
  } else {
    goto var_name_tmp__265;
  }

var_name_tmp__264:
  var_name_tmp__260 = var_name_tmp__257;
  var_name_tmp__261 = (&var_name_tmp__260->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__261)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__261)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16))))), 16, 2);
  goto var_name_tmp__266;

var_name_tmp__265:
  var_name_tmp__262 = var_name_tmp__257;
  var_name_tmp__263 = (&var_name_tmp__262->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__263)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__263)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65519))))), 16, 2);
  goto var_name_tmp__266;

var_name_tmp__266:
  return;
}


void USART_IrDAConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__267, uint16_t var_name_tmp__268) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__269;    /* Address-exposed local */
  uint16_t var_name_tmp__270;    /* Address-exposed local */
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__271;
  uint16_t* var_name_tmp__272;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__273;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__274;
  uint16_t* var_name_tmp__275;
  uint64_t var_name_load_i16_3;

  var_name_tmp__269 = var_name_tmp__267;
  var_name_tmp__270 = var_name_tmp__268;
  var_name_tmp__271 = var_name_tmp__269;
  var_name_tmp__272 = (&var_name_tmp__271->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__272)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__272)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 65531))))), 16, 2);
  var_name_tmp__273 = var_name_tmp__270;
  var_name_tmp__274 = var_name_tmp__269;
  var_name_tmp__275 = (&var_name_tmp__274->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__275)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__275)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__273))))))), 16, 2);
}


void USART_IrDACmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__276, uint32_t var_name_tmp__277) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__278;    /* Address-exposed local */
  uint32_t var_name_tmp__279;    /* Address-exposed local */
  uint32_t var_name_tmp__280;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__281;
  uint16_t* var_name_tmp__282;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__283;
  uint16_t* var_name_tmp__284;
  uint64_t var_name_load_i16_3;

  var_name_tmp__278 = var_name_tmp__276;
  var_name_tmp__279 = var_name_tmp__277;
  var_name_tmp__280 = var_name_tmp__279;
  if ((((var_name_tmp__280 != 0u)&1))) {
    goto var_name_tmp__285;
  } else {
    goto var_name_tmp__286;
  }

var_name_tmp__285:
  var_name_tmp__281 = var_name_tmp__278;
  var_name_tmp__282 = (&var_name_tmp__281->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__282)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__282)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2))))), 16, 2);
  goto var_name_tmp__287;

var_name_tmp__286:
  var_name_tmp__283 = var_name_tmp__278;
  var_name_tmp__284 = (&var_name_tmp__283->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__284)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__284)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65533))))), 16, 2);
  goto var_name_tmp__287;

var_name_tmp__287:
  return;
}


void USART_DMACmd(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__288, uint16_t var_name_tmp__289, uint32_t var_name_tmp__290) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__291;    /* Address-exposed local */
  uint16_t var_name_tmp__292;    /* Address-exposed local */
  uint32_t var_name_tmp__293;    /* Address-exposed local */
  uint32_t var_name_tmp__294;
  uint16_t var_name_tmp__295;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__296;
  uint16_t* var_name_tmp__297;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__298;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__299;
  uint16_t* var_name_tmp__300;
  uint64_t var_name_load_i16_3;

  var_name_tmp__291 = var_name_tmp__288;
  var_name_tmp__292 = var_name_tmp__289;
  var_name_tmp__293 = var_name_tmp__290;
  var_name_tmp__294 = var_name_tmp__293;
  if ((((var_name_tmp__294 != 0u)&1))) {
    goto var_name_tmp__301;
  } else {
    goto var_name_tmp__302;
  }

var_name_tmp__301:
  var_name_tmp__295 = var_name_tmp__292;
  var_name_tmp__296 = var_name_tmp__291;
  var_name_tmp__297 = (&var_name_tmp__296->field10);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__297)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__297)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__295))))))), 16, 2);
  goto var_name_tmp__303;

var_name_tmp__302:
  var_name_tmp__298 = var_name_tmp__292;
  var_name_tmp__299 = var_name_tmp__291;
  var_name_tmp__300 = (&var_name_tmp__299->field10);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__300)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__300)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__298))))))))))))), 16, 2);
  goto var_name_tmp__303;

var_name_tmp__303:
  return;
}


void USART_ITConfig(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__304, uint16_t var_name_tmp__305, uint32_t var_name_tmp__306) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__307;    /* Address-exposed local */
  uint16_t var_name_tmp__308;    /* Address-exposed local */
  uint32_t var_name_tmp__309;    /* Address-exposed local */
  uint32_t var_name_tmp__310;    /* Address-exposed local */
  uint32_t var_name_tmp__311;    /* Address-exposed local */
  uint32_t var_name_tmp__312;    /* Address-exposed local */
  uint32_t var_name_tmp__313;    /* Address-exposed local */
  uint16_t var_name_tmp__314;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__315;
  uint16_t var_name_tmp__316;
  uint16_t var_name_tmp__317;
  uint32_t var_name_tmp__318;
  uint32_t var_name_tmp__319;
  uint32_t var_name_tmp__320;
  uint32_t var_name_tmp__321;
  uint32_t var_name_tmp__322;
  uint32_t var_name_tmp__323;
  uint32_t var_name_tmp__324;
  uint32_t var_name_tmp__325;
  uint32_t var_name_tmp__326;
  uint32_t* var_name_tmp__327;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__328;
  uint32_t var_name_tmp__329;
  uint32_t* var_name_tmp__330;
  uint64_t var_name_load_i32_3;

  var_name_tmp__307 = var_name_tmp__304;
  var_name_tmp__308 = var_name_tmp__305;
  var_name_tmp__309 = var_name_tmp__306;
  var_name_tmp__310 = 0;
  var_name_tmp__311 = 0;
  var_name_tmp__312 = 0;
  var_name_tmp__313 = 0;
  var_name_tmp__314 = var_name_tmp__308;
  if (((((((uint32_t)(uint16_t)var_name_tmp__314)) == 2410u)&1))) {
    goto var_name_tmp__331;
  } else {
    goto var_name_tmp__332;
  }

var_name_tmp__331:
  goto var_name_tmp__332;

var_name_tmp__332:
  var_name_tmp__315 = var_name_tmp__307;
  var_name_tmp__313 = (((uint32_t)(uintptr_t)var_name_tmp__315));
  var_name_tmp__316 = var_name_tmp__308;
  var_name_tmp__310 = (llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__316)))), 5));
  var_name_tmp__317 = var_name_tmp__308;
  var_name_tmp__311 = ((((uint32_t)(uint16_t)var_name_tmp__317)) & 31);
  var_name_tmp__318 = var_name_tmp__311;
  var_name_tmp__312 = (1 << var_name_tmp__318);
  var_name_tmp__319 = var_name_tmp__310;
  if ((((var_name_tmp__319 == 1u)&1))) {
    goto var_name_tmp__333;
  } else {
    goto var_name_tmp__334;
  }

var_name_tmp__333:
  var_name_tmp__320 = var_name_tmp__313;
  var_name_tmp__313 = (llvm_add_u32(var_name_tmp__320, 12));
  goto var_name_tmp__335;

var_name_tmp__334:
  var_name_tmp__321 = var_name_tmp__310;
  if ((((var_name_tmp__321 == 2u)&1))) {
    goto var_name_tmp__336;
  } else {
    goto var_name_tmp__337;
  }

var_name_tmp__336:
  var_name_tmp__322 = var_name_tmp__313;
  var_name_tmp__313 = (llvm_add_u32(var_name_tmp__322, 16));
  goto var_name_tmp__338;

var_name_tmp__337:
  var_name_tmp__323 = var_name_tmp__313;
  var_name_tmp__313 = (llvm_add_u32(var_name_tmp__323, 20));
  goto var_name_tmp__338;

var_name_tmp__338:
  goto var_name_tmp__335;

var_name_tmp__335:
  var_name_tmp__324 = var_name_tmp__309;
  if ((((var_name_tmp__324 != 0u)&1))) {
    goto var_name_tmp__339;
  } else {
    goto var_name_tmp__340;
  }

var_name_tmp__339:
  var_name_tmp__325 = var_name_tmp__312;
  var_name_tmp__326 = var_name_tmp__313;
  var_name_tmp__327 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__326)));
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__327)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__327)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__325))), 32, 4);
  goto var_name_tmp__341;

var_name_tmp__340:
  var_name_tmp__328 = var_name_tmp__312;
  var_name_tmp__329 = var_name_tmp__313;
  var_name_tmp__330 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__329)));
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__330)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__330)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & (~(var_name_tmp__328))))), 32, 4);
  goto var_name_tmp__341;

var_name_tmp__341:
  return;
}


uint32_t USART_GetFlagStatus(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__342, uint16_t var_name_tmp__343) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__344;    /* Address-exposed local */
  uint16_t var_name_tmp__345;    /* Address-exposed local */
  uint32_t var_name_tmp__346;    /* Address-exposed local */
  uint16_t var_name_tmp__347;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__348;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__349;
  uint32_t var_name_tmp__350;

  var_name_tmp__344 = var_name_tmp__342;
  var_name_tmp__345 = var_name_tmp__343;
  var_name_tmp__346 = 0;
  var_name_tmp__347 = var_name_tmp__345;
  if (((((((uint32_t)(uint16_t)var_name_tmp__347)) == 512u)&1))) {
    goto var_name_tmp__351;
  } else {
    goto var_name_tmp__352;
  }

var_name_tmp__351:
  goto var_name_tmp__352;

var_name_tmp__352:
  var_name_tmp__348 = var_name_tmp__344;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__348->field0)))), 16, 2);
  var_name_tmp__349 = var_name_tmp__345;
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)var_name_tmp__349))) != 0u)&1))) {
    goto var_name_tmp__353;
  } else {
    goto var_name_tmp__354;
  }

var_name_tmp__353:
  var_name_tmp__346 = 1;
  goto var_name_tmp__355;

var_name_tmp__354:
  var_name_tmp__346 = 0;
  goto var_name_tmp__355;

var_name_tmp__355:
  var_name_tmp__350 = var_name_tmp__346;
  return var_name_tmp__350;
}


void USART_ClearFlag(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__356, uint16_t var_name_tmp__357) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__358;    /* Address-exposed local */
  uint16_t var_name_tmp__359;    /* Address-exposed local */
  uint16_t var_name_tmp__360;
  uint16_t var_name_tmp__361;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__362;

  var_name_tmp__358 = var_name_tmp__356;
  var_name_tmp__359 = var_name_tmp__357;
  var_name_tmp__360 = var_name_tmp__359;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__360)) & 512) == 512u)&1))) {
    goto var_name_tmp__363;
  } else {
    goto var_name_tmp__364;
  }

var_name_tmp__363:
  goto var_name_tmp__364;

var_name_tmp__364:
  var_name_tmp__361 = var_name_tmp__359;
  var_name_tmp__362 = var_name_tmp__358;
  __adin_store_((((uint8_t*)((&var_name_tmp__362->field0)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__361)))))))), 16, 2);
}


uint32_t USART_GetITStatus(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__365, uint16_t var_name_tmp__366) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__367;    /* Address-exposed local */
  uint16_t var_name_tmp__368;    /* Address-exposed local */
  uint32_t var_name_tmp__369;    /* Address-exposed local */
  uint32_t var_name_tmp__370;    /* Address-exposed local */
  uint32_t var_name_tmp__371;    /* Address-exposed local */
  uint32_t var_name_tmp__372;    /* Address-exposed local */
  uint16_t var_name_tmp__373;
  uint16_t var_name_tmp__374;
  uint16_t var_name_tmp__375;
  uint32_t var_name_tmp__376;
  uint32_t var_name_tmp__377;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__378;
  uint64_t var_name_load_i16_;
  uint32_t var_name_tmp__379;
  uint32_t var_name_tmp__380;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__381;
  uint64_t var_name_load_i16_2;
  uint32_t var_name_tmp__382;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__383;
  uint64_t var_name_load_i16_5;
  uint32_t var_name_tmp__384;
  uint16_t var_name_tmp__385;
  uint32_t var_name_tmp__386;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__387;
  uint64_t var_name_load_i16_8;
  uint32_t var_name_tmp__388;
  uint32_t var_name_tmp__389;
  uint32_t var_name_tmp__390;
  uint32_t var_name_tmp__391;

  var_name_tmp__367 = var_name_tmp__365;
  var_name_tmp__368 = var_name_tmp__366;
  var_name_tmp__369 = 0;
  var_name_tmp__370 = 0;
  var_name_tmp__371 = 0;
  var_name_tmp__372 = 0;
  var_name_tmp__373 = var_name_tmp__368;
  if (((((((uint32_t)(uint16_t)var_name_tmp__373)) == 2410u)&1))) {
    goto var_name_tmp__392;
  } else {
    goto var_name_tmp__393;
  }

var_name_tmp__392:
  goto var_name_tmp__393;

var_name_tmp__393:
  var_name_tmp__374 = var_name_tmp__368;
  var_name_tmp__371 = (llvm_ashr_u32((((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__374)))), 5));
  var_name_tmp__375 = var_name_tmp__368;
  var_name_tmp__370 = ((((uint32_t)(uint16_t)var_name_tmp__375)) & 31);
  var_name_tmp__376 = var_name_tmp__370;
  var_name_tmp__370 = (1 << var_name_tmp__376);
  var_name_tmp__377 = var_name_tmp__371;
  if ((((var_name_tmp__377 == 1u)&1))) {
    goto var_name_tmp__394;
  } else {
    goto var_name_tmp__395;
  }

var_name_tmp__394:
  var_name_tmp__378 = var_name_tmp__367;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__378->field6)))), 16, 2);
  var_name_tmp__379 = var_name_tmp__370;
  var_name_tmp__370 = (var_name_tmp__379 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))));
  goto var_name_tmp__396;

var_name_tmp__395:
  var_name_tmp__380 = var_name_tmp__371;
  if ((((var_name_tmp__380 == 2u)&1))) {
    goto var_name_tmp__397;
  } else {
    goto var_name_tmp__398;
  }

var_name_tmp__397:
  var_name_tmp__381 = var_name_tmp__367;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__381->field8)))), 16, 2);
  var_name_tmp__382 = var_name_tmp__370;
  var_name_tmp__370 = (var_name_tmp__382 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))));
  goto var_name_tmp__399;

var_name_tmp__398:
  var_name_tmp__383 = var_name_tmp__367;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__383->field10)))), 16, 2);
  var_name_tmp__384 = var_name_tmp__370;
  var_name_tmp__370 = (var_name_tmp__384 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5)))));
  goto var_name_tmp__399;

var_name_tmp__399:
  goto var_name_tmp__396;

var_name_tmp__396:
  var_name_tmp__385 = var_name_tmp__368;
  var_name_tmp__369 = (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__385)), 8));
  var_name_tmp__386 = var_name_tmp__369;
  var_name_tmp__369 = (1 << var_name_tmp__386);
  var_name_tmp__387 = var_name_tmp__367;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__387->field0)))), 16, 2);
  var_name_tmp__388 = var_name_tmp__369;
  var_name_tmp__369 = (var_name_tmp__388 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8)))));
  var_name_tmp__389 = var_name_tmp__370;
  if ((((var_name_tmp__389 != 0u)&1))) {
    goto var_name_tmp__400;
  } else {
    goto var_name_tmp__401;
  }

var_name_tmp__400:
  var_name_tmp__390 = var_name_tmp__369;
  if ((((var_name_tmp__390 != 0u)&1))) {
    goto var_name_tmp__402;
  } else {
    goto var_name_tmp__401;
  }

var_name_tmp__402:
  var_name_tmp__372 = 1;
  goto var_name_tmp__403;

var_name_tmp__401:
  var_name_tmp__372 = 0;
  goto var_name_tmp__403;

var_name_tmp__403:
  var_name_tmp__391 = var_name_tmp__372;
  return var_name_tmp__391;
}


void USART_ClearITPendingBit(struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__404, uint16_t var_name_tmp__405) {
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__406;    /* Address-exposed local */
  uint16_t var_name_tmp__407;    /* Address-exposed local */
  uint16_t var_name_tmp__408;    /* Address-exposed local */
  uint16_t var_name_tmp__409;    /* Address-exposed local */
  uint16_t var_name_tmp__410;
  uint16_t var_name_tmp__411;
  uint16_t var_name_tmp__412;
  uint16_t var_name_tmp__413;
  struct l_struct_struct_OC_USART_TypeDef* var_name_tmp__414;

  var_name_tmp__406 = var_name_tmp__404;
  var_name_tmp__407 = var_name_tmp__405;
  var_name_tmp__408 = 0;
  var_name_tmp__409 = 0;
  var_name_tmp__410 = var_name_tmp__407;
  if (((((((uint32_t)(uint16_t)var_name_tmp__410)) == 2410u)&1))) {
    goto var_name_tmp__415;
  } else {
    goto var_name_tmp__416;
  }

var_name_tmp__415:
  goto var_name_tmp__416;

var_name_tmp__416:
  var_name_tmp__411 = var_name_tmp__407;
  var_name_tmp__408 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__411)), 8))));
  var_name_tmp__412 = var_name_tmp__408;
  var_name_tmp__409 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__412)))));
  var_name_tmp__413 = var_name_tmp__409;
  var_name_tmp__414 = var_name_tmp__406;
  __adin_store_((((uint8_t*)((&var_name_tmp__414->field0)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__413)))))))), 16, 2);
}

