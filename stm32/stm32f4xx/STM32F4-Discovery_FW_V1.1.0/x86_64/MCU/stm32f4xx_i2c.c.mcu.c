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
struct l_struct_struct_OC_I2C_TypeDef;
struct l_struct_struct_OC_I2C_InitTypeDef;
struct l_struct_struct_OC_RCC_ClocksTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_I2C_TypeDef {
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
};
struct l_struct_struct_OC_I2C_InitTypeDef {
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

/* Function Declarations */
void I2C_DeInit(struct l_struct_struct_OC_I2C_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void I2C_Init(struct l_struct_struct_OC_I2C_TypeDef*, struct l_struct_struct_OC_I2C_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_GetClocksFreq(struct l_struct_struct_OC_RCC_ClocksTypeDef*);
void I2C_StructInit(struct l_struct_struct_OC_I2C_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_Cmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_GenerateSTART(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_GenerateSTOP(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_Send7bitAddress(struct l_struct_struct_OC_I2C_TypeDef*, uint8_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_AcknowledgeConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_OwnAddress2Config(struct l_struct_struct_OC_I2C_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_DualAddressCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_GeneralCallCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_SoftwareResetCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_StretchClockCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_FastModeDutyCycleConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_NACKPositionConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_SMBusAlertConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_ARPCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_SendData(struct l_struct_struct_OC_I2C_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t I2C_ReceiveData(struct l_struct_struct_OC_I2C_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_TransmitPEC(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_PECPositionConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_CalculatePEC(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t I2C_GetPEC(struct l_struct_struct_OC_I2C_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_DMACmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_DMALastTransferCmd(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t I2C_ReadRegister(struct l_struct_struct_OC_I2C_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_ITConfig(struct l_struct_struct_OC_I2C_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t I2C_CheckEvent(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t I2C_GetLastEvent(struct l_struct_struct_OC_I2C_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t I2C_GetFlagStatus(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_ClearFlag(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t I2C_GetITStatus(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2C_ClearITPendingBit(struct l_struct_struct_OC_I2C_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
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
static __forceinline uint32_t llvm_sdiv_u32(int32_t a, int32_t b) {
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

void I2C_DeInit(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__3;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__4;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__5;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_I2C_TypeDef*)(uintptr_t)UINT64_C(1073763328)))&1))) {
    goto var_name_tmp__6;
  } else {
    goto var_name_tmp__7;
  }

var_name_tmp__6:
  RCC_APB1PeriphResetCmd(2097152, 1);
  RCC_APB1PeriphResetCmd(2097152, 0);
  goto var_name_tmp__8;

var_name_tmp__7:
  var_name_tmp__4 = var_name_tmp__2;
  if ((((var_name_tmp__4 == ((struct l_struct_struct_OC_I2C_TypeDef*)(uintptr_t)UINT64_C(1073764352)))&1))) {
    goto var_name_tmp__9;
  } else {
    goto var_name_tmp__10;
  }

var_name_tmp__9:
  RCC_APB1PeriphResetCmd(4194304, 1);
  RCC_APB1PeriphResetCmd(4194304, 0);
  goto var_name_tmp__11;

var_name_tmp__10:
  var_name_tmp__5 = var_name_tmp__2;
  if ((((var_name_tmp__5 == ((struct l_struct_struct_OC_I2C_TypeDef*)(uintptr_t)UINT64_C(1073765376)))&1))) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__12:
  RCC_APB1PeriphResetCmd(8388608, 1);
  RCC_APB1PeriphResetCmd(8388608, 0);
  goto var_name_tmp__13;

var_name_tmp__13:
  goto var_name_tmp__11;

var_name_tmp__11:
  goto var_name_tmp__8;

var_name_tmp__8:
  return;
}


void I2C_Init(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__14, struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__15) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__16;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__17;    /* Address-exposed local */
  uint16_t var_name_tmp__18;    /* Address-exposed local */
  uint16_t var_name_tmp__19;    /* Address-exposed local */
  uint16_t var_name_tmp__20;    /* Address-exposed local */
  uint32_t var_name_tmp__21;    /* Address-exposed local */
  struct l_struct_struct_OC_RCC_ClocksTypeDef var_name_tmp__22;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__23;
  uint16_t var_name_tmp__24;
  uint16_t var_name_tmp__25;
  uint32_t var_name_tmp__26;
  uint32_t var_name_tmp__27;
  uint16_t var_name_tmp__28;
  uint16_t var_name_tmp__29;
  uint16_t var_name_tmp__30;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__31;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__32;
  uint16_t* var_name_tmp__33;
  uint16_t var_name_tmp__34;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__35;
  uint32_t var_name_tmp__36;
  uint32_t var_name_tmp__37;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__38;
  uint32_t var_name_tmp__39;
  uint16_t var_name_tmp__40;
  uint16_t var_name_tmp__41;
  uint16_t var_name_tmp__42;
  uint16_t var_name_tmp__43;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__44;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__45;
  uint16_t var_name_tmp__46;
  uint32_t var_name_tmp__47;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__48;
  uint32_t var_name_tmp__49;
  uint32_t var_name_tmp__50;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__51;
  uint32_t var_name_tmp__52;
  uint16_t var_name_tmp__53;
  uint16_t var_name_tmp__54;
  uint16_t var_name_tmp__55;
  uint16_t var_name_tmp__56;
  uint16_t var_name_tmp__57;
  uint16_t var_name_tmp__58;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__59;
  uint16_t var_name_tmp__60;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__61;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__62;
  uint16_t* var_name_tmp__63;
  uint16_t var_name_tmp__64;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__65;
  uint16_t var_name_tmp__66;
  uint16_t var_name_tmp__67;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__68;
  uint16_t var_name_tmp__69;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__70;
  uint16_t var_name_tmp__71;
  uint16_t var_name_tmp__72;
  uint16_t var_name_tmp__73;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__74;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__75;
  uint16_t var_name_tmp__76;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__77;
  uint16_t var_name_tmp__78;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__79;

  var_name_tmp__16 = var_name_tmp__14;
  var_name_tmp__17 = var_name_tmp__15;
  var_name_tmp__18 = 0;
  var_name_tmp__19 = 0;
  var_name_tmp__20 = 4;
  var_name_tmp__21 = 8000000;
  var_name_tmp__23 = var_name_tmp__16;
  var_name_tmp__24 = *(volatile uint16_t*)((&var_name_tmp__23->field2));
  var_name_tmp__18 = var_name_tmp__24;
  var_name_tmp__25 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__25)) & 65472)));
  RCC_GetClocksFreq((&var_name_tmp__22));
  var_name_tmp__26 = *((&var_name_tmp__22.field2));
  var_name_tmp__21 = var_name_tmp__26;
  var_name_tmp__27 = var_name_tmp__21;
  var_name_tmp__19 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__27, 1000000))));
  var_name_tmp__28 = var_name_tmp__19;
  var_name_tmp__29 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__29)) | (((uint32_t)(uint16_t)var_name_tmp__28)))));
  var_name_tmp__30 = var_name_tmp__18;
  var_name_tmp__31 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__31->field2)) = var_name_tmp__30;
  var_name_tmp__32 = var_name_tmp__16;
  var_name_tmp__33 = (&var_name_tmp__32->field0);
  var_name_tmp__34 = *(volatile uint16_t*)var_name_tmp__33;
  *(volatile uint16_t*)var_name_tmp__33 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__34)) & 65534)));
  var_name_tmp__18 = 0;
  var_name_tmp__35 = var_name_tmp__17;
  var_name_tmp__36 = *((&var_name_tmp__35->field0));
  if ((((((uint32_t)var_name_tmp__36) <= ((uint32_t)100000u))&1))) {
    goto var_name_tmp__80;
  } else {
    goto var_name_tmp__81;
  }

var_name_tmp__80:
  var_name_tmp__37 = var_name_tmp__21;
  var_name_tmp__38 = var_name_tmp__17;
  var_name_tmp__39 = *((&var_name_tmp__38->field0));
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__37, (var_name_tmp__39 << 1)))));
  var_name_tmp__40 = var_name_tmp__20;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__40))) < ((int32_t)4u))&1))) {
    goto var_name_tmp__82;
  } else {
    goto var_name_tmp__83;
  }

var_name_tmp__82:
  var_name_tmp__20 = 4;
  goto var_name_tmp__83;

var_name_tmp__83:
  var_name_tmp__41 = var_name_tmp__20;
  var_name_tmp__42 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__42)) | (((uint32_t)(uint16_t)var_name_tmp__41)))));
  var_name_tmp__43 = var_name_tmp__19;
  var_name_tmp__44 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__44->field16)) = (((uint16_t)(llvm_add_u32((((uint32_t)(uint16_t)var_name_tmp__43)), 1))));
  goto var_name_tmp__84;

var_name_tmp__81:
  var_name_tmp__45 = var_name_tmp__17;
  var_name_tmp__46 = *((&var_name_tmp__45->field2));
  if (((((((uint32_t)(uint16_t)var_name_tmp__46)) == 49151u)&1))) {
    goto var_name_tmp__85;
  } else {
    goto var_name_tmp__86;
  }

var_name_tmp__85:
  var_name_tmp__47 = var_name_tmp__21;
  var_name_tmp__48 = var_name_tmp__17;
  var_name_tmp__49 = *((&var_name_tmp__48->field0));
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__47, (llvm_mul_u32(var_name_tmp__49, 3))))));
  goto var_name_tmp__87;

var_name_tmp__86:
  var_name_tmp__50 = var_name_tmp__21;
  var_name_tmp__51 = var_name_tmp__17;
  var_name_tmp__52 = *((&var_name_tmp__51->field0));
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__50, (llvm_mul_u32(var_name_tmp__52, 25))))));
  var_name_tmp__53 = var_name_tmp__20;
  var_name_tmp__20 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__53)) | 16384)));
  goto var_name_tmp__87;

var_name_tmp__87:
  var_name_tmp__54 = var_name_tmp__20;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__54)) & 4095) == 0u)&1))) {
    goto var_name_tmp__88;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__88:
  var_name_tmp__55 = var_name_tmp__20;
  var_name_tmp__20 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__55)) | 1)));
  goto var_name_tmp__89;

var_name_tmp__89:
  var_name_tmp__56 = var_name_tmp__20;
  var_name_tmp__57 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__57)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__56)) | 32768))))))));
  var_name_tmp__58 = var_name_tmp__19;
  var_name_tmp__59 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__59->field16)) = (((uint16_t)(llvm_add_u32((llvm_sdiv_u32((llvm_mul_u32((((uint32_t)(uint16_t)var_name_tmp__58)), 300)), 1000)), 1))));
  goto var_name_tmp__84;

var_name_tmp__84:
  var_name_tmp__60 = var_name_tmp__18;
  var_name_tmp__61 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__61->field14)) = var_name_tmp__60;
  var_name_tmp__62 = var_name_tmp__16;
  var_name_tmp__63 = (&var_name_tmp__62->field0);
  var_name_tmp__64 = *(volatile uint16_t*)var_name_tmp__63;
  *(volatile uint16_t*)var_name_tmp__63 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__64)) | 1)));
  var_name_tmp__65 = var_name_tmp__16;
  var_name_tmp__66 = *(volatile uint16_t*)((&var_name_tmp__65->field0));
  var_name_tmp__18 = var_name_tmp__66;
  var_name_tmp__67 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__67)) & 64501)));
  var_name_tmp__68 = var_name_tmp__17;
  var_name_tmp__69 = *((&var_name_tmp__68->field1));
  var_name_tmp__70 = var_name_tmp__17;
  var_name_tmp__71 = *((&var_name_tmp__70->field4));
  var_name_tmp__72 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__72)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__69)) | (((uint32_t)(uint16_t)var_name_tmp__71))))))))));
  var_name_tmp__73 = var_name_tmp__18;
  var_name_tmp__74 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__74->field0)) = var_name_tmp__73;
  var_name_tmp__75 = var_name_tmp__17;
  var_name_tmp__76 = *((&var_name_tmp__75->field5));
  var_name_tmp__77 = var_name_tmp__17;
  var_name_tmp__78 = *((&var_name_tmp__77->field3));
  var_name_tmp__79 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__79->field4)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__76)) | (((uint32_t)(uint16_t)var_name_tmp__78)))));
}


void I2C_StructInit(struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__90) {
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__91;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__92;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__93;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__94;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__95;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__96;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__97;

  var_name_tmp__91 = var_name_tmp__90;
  var_name_tmp__92 = var_name_tmp__91;
  *((&var_name_tmp__92->field0)) = 5000;
  var_name_tmp__93 = var_name_tmp__91;
  *((&var_name_tmp__93->field1)) = 0;
  var_name_tmp__94 = var_name_tmp__91;
  *((&var_name_tmp__94->field2)) = 49151u;
  var_name_tmp__95 = var_name_tmp__91;
  *((&var_name_tmp__95->field3)) = 0;
  var_name_tmp__96 = var_name_tmp__91;
  *((&var_name_tmp__96->field4)) = 0;
  var_name_tmp__97 = var_name_tmp__91;
  *((&var_name_tmp__97->field5)) = 16384u;
}


void I2C_Cmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__98, uint32_t var_name_tmp__99) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__103;
  uint16_t* var_name_tmp__104;
  uint16_t var_name_tmp__105;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__106;
  uint16_t* var_name_tmp__107;
  uint16_t var_name_tmp__108;

  var_name_tmp__100 = var_name_tmp__98;
  var_name_tmp__101 = var_name_tmp__99;
  var_name_tmp__102 = var_name_tmp__101;
  if ((((var_name_tmp__102 != 0u)&1))) {
    goto var_name_tmp__109;
  } else {
    goto var_name_tmp__110;
  }

var_name_tmp__109:
  var_name_tmp__103 = var_name_tmp__100;
  var_name_tmp__104 = (&var_name_tmp__103->field0);
  var_name_tmp__105 = *(volatile uint16_t*)var_name_tmp__104;
  *(volatile uint16_t*)var_name_tmp__104 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__105)) | 1)));
  goto var_name_tmp__111;

var_name_tmp__110:
  var_name_tmp__106 = var_name_tmp__100;
  var_name_tmp__107 = (&var_name_tmp__106->field0);
  var_name_tmp__108 = *(volatile uint16_t*)var_name_tmp__107;
  *(volatile uint16_t*)var_name_tmp__107 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__108)) & 65534)));
  goto var_name_tmp__111;

var_name_tmp__111:
  return;
}


void I2C_GenerateSTART(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__112, uint32_t var_name_tmp__113) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__114;    /* Address-exposed local */
  uint32_t var_name_tmp__115;    /* Address-exposed local */
  uint32_t var_name_tmp__116;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__117;
  uint16_t* var_name_tmp__118;
  uint16_t var_name_tmp__119;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__120;
  uint16_t* var_name_tmp__121;
  uint16_t var_name_tmp__122;

  var_name_tmp__114 = var_name_tmp__112;
  var_name_tmp__115 = var_name_tmp__113;
  var_name_tmp__116 = var_name_tmp__115;
  if ((((var_name_tmp__116 != 0u)&1))) {
    goto var_name_tmp__123;
  } else {
    goto var_name_tmp__124;
  }

var_name_tmp__123:
  var_name_tmp__117 = var_name_tmp__114;
  var_name_tmp__118 = (&var_name_tmp__117->field0);
  var_name_tmp__119 = *(volatile uint16_t*)var_name_tmp__118;
  *(volatile uint16_t*)var_name_tmp__118 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__119)) | 256)));
  goto var_name_tmp__125;

var_name_tmp__124:
  var_name_tmp__120 = var_name_tmp__114;
  var_name_tmp__121 = (&var_name_tmp__120->field0);
  var_name_tmp__122 = *(volatile uint16_t*)var_name_tmp__121;
  *(volatile uint16_t*)var_name_tmp__121 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__122)) & 65279)));
  goto var_name_tmp__125;

var_name_tmp__125:
  return;
}


void I2C_GenerateSTOP(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__126, uint32_t var_name_tmp__127) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__128;    /* Address-exposed local */
  uint32_t var_name_tmp__129;    /* Address-exposed local */
  uint32_t var_name_tmp__130;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__131;
  uint16_t* var_name_tmp__132;
  uint16_t var_name_tmp__133;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__134;
  uint16_t* var_name_tmp__135;
  uint16_t var_name_tmp__136;

  var_name_tmp__128 = var_name_tmp__126;
  var_name_tmp__129 = var_name_tmp__127;
  var_name_tmp__130 = var_name_tmp__129;
  if ((((var_name_tmp__130 != 0u)&1))) {
    goto var_name_tmp__137;
  } else {
    goto var_name_tmp__138;
  }

var_name_tmp__137:
  var_name_tmp__131 = var_name_tmp__128;
  var_name_tmp__132 = (&var_name_tmp__131->field0);
  var_name_tmp__133 = *(volatile uint16_t*)var_name_tmp__132;
  *(volatile uint16_t*)var_name_tmp__132 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__133)) | 512)));
  goto var_name_tmp__139;

var_name_tmp__138:
  var_name_tmp__134 = var_name_tmp__128;
  var_name_tmp__135 = (&var_name_tmp__134->field0);
  var_name_tmp__136 = *(volatile uint16_t*)var_name_tmp__135;
  *(volatile uint16_t*)var_name_tmp__135 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__136)) & 65023)));
  goto var_name_tmp__139;

var_name_tmp__139:
  return;
}


void I2C_Send7bitAddress(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__140, uint8_t var_name_tmp__141, uint8_t var_name_tmp__142) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__143;    /* Address-exposed local */
  uint8_t var_name_tmp__144;    /* Address-exposed local */
  uint8_t var_name_tmp__145;    /* Address-exposed local */
  uint8_t var_name_tmp__146;
  uint8_t var_name_tmp__147;
  uint8_t var_name_tmp__148;
  uint8_t var_name_tmp__149;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__150;

  var_name_tmp__143 = var_name_tmp__140;
  var_name_tmp__144 = var_name_tmp__141;
  var_name_tmp__145 = var_name_tmp__142;
  var_name_tmp__146 = var_name_tmp__145;
  if (((((((uint32_t)(uint8_t)var_name_tmp__146)) != 0u)&1))) {
    goto var_name_tmp__151;
  } else {
    goto var_name_tmp__152;
  }

var_name_tmp__151:
  var_name_tmp__147 = var_name_tmp__144;
  var_name_tmp__144 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__147)) | 1)));
  goto var_name_tmp__153;

var_name_tmp__152:
  var_name_tmp__148 = var_name_tmp__144;
  var_name_tmp__144 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__148)) & 254)));
  goto var_name_tmp__153;

var_name_tmp__153:
  var_name_tmp__149 = var_name_tmp__144;
  var_name_tmp__150 = var_name_tmp__143;
  *(volatile uint16_t*)((&var_name_tmp__150->field8)) = (((uint16_t)(uint8_t)var_name_tmp__149));
}


void I2C_AcknowledgeConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__154, uint32_t var_name_tmp__155) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__156;    /* Address-exposed local */
  uint32_t var_name_tmp__157;    /* Address-exposed local */
  uint32_t var_name_tmp__158;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__159;
  uint16_t* var_name_tmp__160;
  uint16_t var_name_tmp__161;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__162;
  uint16_t* var_name_tmp__163;
  uint16_t var_name_tmp__164;

  var_name_tmp__156 = var_name_tmp__154;
  var_name_tmp__157 = var_name_tmp__155;
  var_name_tmp__158 = var_name_tmp__157;
  if ((((var_name_tmp__158 != 0u)&1))) {
    goto var_name_tmp__165;
  } else {
    goto var_name_tmp__166;
  }

var_name_tmp__165:
  var_name_tmp__159 = var_name_tmp__156;
  var_name_tmp__160 = (&var_name_tmp__159->field0);
  var_name_tmp__161 = *(volatile uint16_t*)var_name_tmp__160;
  *(volatile uint16_t*)var_name_tmp__160 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__161)) | 1024)));
  goto var_name_tmp__167;

var_name_tmp__166:
  var_name_tmp__162 = var_name_tmp__156;
  var_name_tmp__163 = (&var_name_tmp__162->field0);
  var_name_tmp__164 = *(volatile uint16_t*)var_name_tmp__163;
  *(volatile uint16_t*)var_name_tmp__163 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__164)) & 64511)));
  goto var_name_tmp__167;

var_name_tmp__167:
  return;
}


void I2C_OwnAddress2Config(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__168, uint8_t var_name_tmp__169) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__170;    /* Address-exposed local */
  uint8_t var_name_tmp__171;    /* Address-exposed local */
  uint16_t var_name_tmp__172;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__173;
  uint16_t var_name_tmp__174;
  uint16_t var_name_tmp__175;
  uint8_t var_name_tmp__176;
  uint16_t var_name_tmp__177;
  uint16_t var_name_tmp__178;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__179;

  var_name_tmp__170 = var_name_tmp__168;
  var_name_tmp__171 = var_name_tmp__169;
  var_name_tmp__172 = 0;
  var_name_tmp__173 = var_name_tmp__170;
  var_name_tmp__174 = *(volatile uint16_t*)((&var_name_tmp__173->field6));
  var_name_tmp__172 = var_name_tmp__174;
  var_name_tmp__175 = var_name_tmp__172;
  var_name_tmp__172 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__175)) & 65281)));
  var_name_tmp__176 = var_name_tmp__171;
  var_name_tmp__177 = var_name_tmp__172;
  var_name_tmp__172 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__177)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__176)))) & 254))))))));
  var_name_tmp__178 = var_name_tmp__172;
  var_name_tmp__179 = var_name_tmp__170;
  *(volatile uint16_t*)((&var_name_tmp__179->field6)) = var_name_tmp__178;
}


void I2C_DualAddressCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__180, uint32_t var_name_tmp__181) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__182;    /* Address-exposed local */
  uint32_t var_name_tmp__183;    /* Address-exposed local */
  uint32_t var_name_tmp__184;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__185;
  uint16_t* var_name_tmp__186;
  uint16_t var_name_tmp__187;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__188;
  uint16_t* var_name_tmp__189;
  uint16_t var_name_tmp__190;

  var_name_tmp__182 = var_name_tmp__180;
  var_name_tmp__183 = var_name_tmp__181;
  var_name_tmp__184 = var_name_tmp__183;
  if ((((var_name_tmp__184 != 0u)&1))) {
    goto var_name_tmp__191;
  } else {
    goto var_name_tmp__192;
  }

var_name_tmp__191:
  var_name_tmp__185 = var_name_tmp__182;
  var_name_tmp__186 = (&var_name_tmp__185->field6);
  var_name_tmp__187 = *(volatile uint16_t*)var_name_tmp__186;
  *(volatile uint16_t*)var_name_tmp__186 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__187)) | 1)));
  goto var_name_tmp__193;

var_name_tmp__192:
  var_name_tmp__188 = var_name_tmp__182;
  var_name_tmp__189 = (&var_name_tmp__188->field6);
  var_name_tmp__190 = *(volatile uint16_t*)var_name_tmp__189;
  *(volatile uint16_t*)var_name_tmp__189 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__190)) & 65534)));
  goto var_name_tmp__193;

var_name_tmp__193:
  return;
}


void I2C_GeneralCallCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__194, uint32_t var_name_tmp__195) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__196;    /* Address-exposed local */
  uint32_t var_name_tmp__197;    /* Address-exposed local */
  uint32_t var_name_tmp__198;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__199;
  uint16_t* var_name_tmp__200;
  uint16_t var_name_tmp__201;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__202;
  uint16_t* var_name_tmp__203;
  uint16_t var_name_tmp__204;

  var_name_tmp__196 = var_name_tmp__194;
  var_name_tmp__197 = var_name_tmp__195;
  var_name_tmp__198 = var_name_tmp__197;
  if ((((var_name_tmp__198 != 0u)&1))) {
    goto var_name_tmp__205;
  } else {
    goto var_name_tmp__206;
  }

var_name_tmp__205:
  var_name_tmp__199 = var_name_tmp__196;
  var_name_tmp__200 = (&var_name_tmp__199->field0);
  var_name_tmp__201 = *(volatile uint16_t*)var_name_tmp__200;
  *(volatile uint16_t*)var_name_tmp__200 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__201)) | 64)));
  goto var_name_tmp__207;

var_name_tmp__206:
  var_name_tmp__202 = var_name_tmp__196;
  var_name_tmp__203 = (&var_name_tmp__202->field0);
  var_name_tmp__204 = *(volatile uint16_t*)var_name_tmp__203;
  *(volatile uint16_t*)var_name_tmp__203 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__204)) & 65471)));
  goto var_name_tmp__207;

var_name_tmp__207:
  return;
}


void I2C_SoftwareResetCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__208, uint32_t var_name_tmp__209) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__210;    /* Address-exposed local */
  uint32_t var_name_tmp__211;    /* Address-exposed local */
  uint32_t var_name_tmp__212;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__213;
  uint16_t* var_name_tmp__214;
  uint16_t var_name_tmp__215;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__216;
  uint16_t* var_name_tmp__217;
  uint16_t var_name_tmp__218;

  var_name_tmp__210 = var_name_tmp__208;
  var_name_tmp__211 = var_name_tmp__209;
  var_name_tmp__212 = var_name_tmp__211;
  if ((((var_name_tmp__212 != 0u)&1))) {
    goto var_name_tmp__219;
  } else {
    goto var_name_tmp__220;
  }

var_name_tmp__219:
  var_name_tmp__213 = var_name_tmp__210;
  var_name_tmp__214 = (&var_name_tmp__213->field0);
  var_name_tmp__215 = *(volatile uint16_t*)var_name_tmp__214;
  *(volatile uint16_t*)var_name_tmp__214 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__215)) | 32768)));
  goto var_name_tmp__221;

var_name_tmp__220:
  var_name_tmp__216 = var_name_tmp__210;
  var_name_tmp__217 = (&var_name_tmp__216->field0);
  var_name_tmp__218 = *(volatile uint16_t*)var_name_tmp__217;
  *(volatile uint16_t*)var_name_tmp__217 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__218)) & 32767)));
  goto var_name_tmp__221;

var_name_tmp__221:
  return;
}


void I2C_StretchClockCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__222, uint32_t var_name_tmp__223) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__224;    /* Address-exposed local */
  uint32_t var_name_tmp__225;    /* Address-exposed local */
  uint32_t var_name_tmp__226;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__227;
  uint16_t* var_name_tmp__228;
  uint16_t var_name_tmp__229;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__230;
  uint16_t* var_name_tmp__231;
  uint16_t var_name_tmp__232;

  var_name_tmp__224 = var_name_tmp__222;
  var_name_tmp__225 = var_name_tmp__223;
  var_name_tmp__226 = var_name_tmp__225;
  if ((((var_name_tmp__226 == 0u)&1))) {
    goto var_name_tmp__233;
  } else {
    goto var_name_tmp__234;
  }

var_name_tmp__233:
  var_name_tmp__227 = var_name_tmp__224;
  var_name_tmp__228 = (&var_name_tmp__227->field0);
  var_name_tmp__229 = *(volatile uint16_t*)var_name_tmp__228;
  *(volatile uint16_t*)var_name_tmp__228 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__229)) | 128)));
  goto var_name_tmp__235;

var_name_tmp__234:
  var_name_tmp__230 = var_name_tmp__224;
  var_name_tmp__231 = (&var_name_tmp__230->field0);
  var_name_tmp__232 = *(volatile uint16_t*)var_name_tmp__231;
  *(volatile uint16_t*)var_name_tmp__231 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__232)) & 65407)));
  goto var_name_tmp__235;

var_name_tmp__235:
  return;
}


void I2C_FastModeDutyCycleConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__236, uint16_t var_name_tmp__237) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__238;    /* Address-exposed local */
  uint16_t var_name_tmp__239;    /* Address-exposed local */
  uint16_t var_name_tmp__240;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__241;
  uint16_t* var_name_tmp__242;
  uint16_t var_name_tmp__243;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__244;
  uint16_t* var_name_tmp__245;
  uint16_t var_name_tmp__246;

  var_name_tmp__238 = var_name_tmp__236;
  var_name_tmp__239 = var_name_tmp__237;
  var_name_tmp__240 = var_name_tmp__239;
  if (((((((uint32_t)(uint16_t)var_name_tmp__240)) != 16384u)&1))) {
    goto var_name_tmp__247;
  } else {
    goto var_name_tmp__248;
  }

var_name_tmp__247:
  var_name_tmp__241 = var_name_tmp__238;
  var_name_tmp__242 = (&var_name_tmp__241->field14);
  var_name_tmp__243 = *(volatile uint16_t*)var_name_tmp__242;
  *(volatile uint16_t*)var_name_tmp__242 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__243)) & 49151)));
  goto var_name_tmp__249;

var_name_tmp__248:
  var_name_tmp__244 = var_name_tmp__238;
  var_name_tmp__245 = (&var_name_tmp__244->field14);
  var_name_tmp__246 = *(volatile uint16_t*)var_name_tmp__245;
  *(volatile uint16_t*)var_name_tmp__245 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__246)) | 16384)));
  goto var_name_tmp__249;

var_name_tmp__249:
  return;
}


void I2C_NACKPositionConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__250, uint16_t var_name_tmp__251) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__252;    /* Address-exposed local */
  uint16_t var_name_tmp__253;    /* Address-exposed local */
  uint16_t var_name_tmp__254;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__255;
  uint16_t* var_name_tmp__256;
  uint16_t var_name_tmp__257;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__258;
  uint16_t* var_name_tmp__259;
  uint16_t var_name_tmp__260;

  var_name_tmp__252 = var_name_tmp__250;
  var_name_tmp__253 = var_name_tmp__251;
  var_name_tmp__254 = var_name_tmp__253;
  if (((((((uint32_t)(uint16_t)var_name_tmp__254)) == 2048u)&1))) {
    goto var_name_tmp__261;
  } else {
    goto var_name_tmp__262;
  }

var_name_tmp__261:
  var_name_tmp__255 = var_name_tmp__252;
  var_name_tmp__256 = (&var_name_tmp__255->field0);
  var_name_tmp__257 = *(volatile uint16_t*)var_name_tmp__256;
  *(volatile uint16_t*)var_name_tmp__256 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__257)) | 2048)));
  goto var_name_tmp__263;

var_name_tmp__262:
  var_name_tmp__258 = var_name_tmp__252;
  var_name_tmp__259 = (&var_name_tmp__258->field0);
  var_name_tmp__260 = *(volatile uint16_t*)var_name_tmp__259;
  *(volatile uint16_t*)var_name_tmp__259 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__260)) & 63487)));
  goto var_name_tmp__263;

var_name_tmp__263:
  return;
}


void I2C_SMBusAlertConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__264, uint16_t var_name_tmp__265) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__266;    /* Address-exposed local */
  uint16_t var_name_tmp__267;    /* Address-exposed local */
  uint16_t var_name_tmp__268;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__269;
  uint16_t* var_name_tmp__270;
  uint16_t var_name_tmp__271;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__272;
  uint16_t* var_name_tmp__273;
  uint16_t var_name_tmp__274;

  var_name_tmp__266 = var_name_tmp__264;
  var_name_tmp__267 = var_name_tmp__265;
  var_name_tmp__268 = var_name_tmp__267;
  if (((((((uint32_t)(uint16_t)var_name_tmp__268)) == 8192u)&1))) {
    goto var_name_tmp__275;
  } else {
    goto var_name_tmp__276;
  }

var_name_tmp__275:
  var_name_tmp__269 = var_name_tmp__266;
  var_name_tmp__270 = (&var_name_tmp__269->field0);
  var_name_tmp__271 = *(volatile uint16_t*)var_name_tmp__270;
  *(volatile uint16_t*)var_name_tmp__270 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__271)) | 8192)));
  goto var_name_tmp__277;

var_name_tmp__276:
  var_name_tmp__272 = var_name_tmp__266;
  var_name_tmp__273 = (&var_name_tmp__272->field0);
  var_name_tmp__274 = *(volatile uint16_t*)var_name_tmp__273;
  *(volatile uint16_t*)var_name_tmp__273 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__274)) & 57343)));
  goto var_name_tmp__277;

var_name_tmp__277:
  return;
}


void I2C_ARPCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__278, uint32_t var_name_tmp__279) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__280;    /* Address-exposed local */
  uint32_t var_name_tmp__281;    /* Address-exposed local */
  uint32_t var_name_tmp__282;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__283;
  uint16_t* var_name_tmp__284;
  uint16_t var_name_tmp__285;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__286;
  uint16_t* var_name_tmp__287;
  uint16_t var_name_tmp__288;

  var_name_tmp__280 = var_name_tmp__278;
  var_name_tmp__281 = var_name_tmp__279;
  var_name_tmp__282 = var_name_tmp__281;
  if ((((var_name_tmp__282 != 0u)&1))) {
    goto var_name_tmp__289;
  } else {
    goto var_name_tmp__290;
  }

var_name_tmp__289:
  var_name_tmp__283 = var_name_tmp__280;
  var_name_tmp__284 = (&var_name_tmp__283->field0);
  var_name_tmp__285 = *(volatile uint16_t*)var_name_tmp__284;
  *(volatile uint16_t*)var_name_tmp__284 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__285)) | 16)));
  goto var_name_tmp__291;

var_name_tmp__290:
  var_name_tmp__286 = var_name_tmp__280;
  var_name_tmp__287 = (&var_name_tmp__286->field0);
  var_name_tmp__288 = *(volatile uint16_t*)var_name_tmp__287;
  *(volatile uint16_t*)var_name_tmp__287 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__288)) & 65519)));
  goto var_name_tmp__291;

var_name_tmp__291:
  return;
}


void I2C_SendData(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__292, uint8_t var_name_tmp__293) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__294;    /* Address-exposed local */
  uint8_t var_name_tmp__295;    /* Address-exposed local */
  uint8_t var_name_tmp__296;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__297;

  var_name_tmp__294 = var_name_tmp__292;
  var_name_tmp__295 = var_name_tmp__293;
  var_name_tmp__296 = var_name_tmp__295;
  var_name_tmp__297 = var_name_tmp__294;
  *(volatile uint16_t*)((&var_name_tmp__297->field8)) = (((uint16_t)(uint8_t)var_name_tmp__296));
}


uint8_t I2C_ReceiveData(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__298) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__299;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__300;
  uint16_t var_name_tmp__301;

  var_name_tmp__299 = var_name_tmp__298;
  var_name_tmp__300 = var_name_tmp__299;
  var_name_tmp__301 = *(volatile uint16_t*)((&var_name_tmp__300->field8));
  return (((uint8_t)var_name_tmp__301));
}


void I2C_TransmitPEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__302, uint32_t var_name_tmp__303) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__304;    /* Address-exposed local */
  uint32_t var_name_tmp__305;    /* Address-exposed local */
  uint32_t var_name_tmp__306;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__307;
  uint16_t* var_name_tmp__308;
  uint16_t var_name_tmp__309;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__310;
  uint16_t* var_name_tmp__311;
  uint16_t var_name_tmp__312;

  var_name_tmp__304 = var_name_tmp__302;
  var_name_tmp__305 = var_name_tmp__303;
  var_name_tmp__306 = var_name_tmp__305;
  if ((((var_name_tmp__306 != 0u)&1))) {
    goto var_name_tmp__313;
  } else {
    goto var_name_tmp__314;
  }

var_name_tmp__313:
  var_name_tmp__307 = var_name_tmp__304;
  var_name_tmp__308 = (&var_name_tmp__307->field0);
  var_name_tmp__309 = *(volatile uint16_t*)var_name_tmp__308;
  *(volatile uint16_t*)var_name_tmp__308 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__309)) | 4096)));
  goto var_name_tmp__315;

var_name_tmp__314:
  var_name_tmp__310 = var_name_tmp__304;
  var_name_tmp__311 = (&var_name_tmp__310->field0);
  var_name_tmp__312 = *(volatile uint16_t*)var_name_tmp__311;
  *(volatile uint16_t*)var_name_tmp__311 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__312)) & 61439)));
  goto var_name_tmp__315;

var_name_tmp__315:
  return;
}


void I2C_PECPositionConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__316, uint16_t var_name_tmp__317) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__318;    /* Address-exposed local */
  uint16_t var_name_tmp__319;    /* Address-exposed local */
  uint16_t var_name_tmp__320;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__321;
  uint16_t* var_name_tmp__322;
  uint16_t var_name_tmp__323;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__324;
  uint16_t* var_name_tmp__325;
  uint16_t var_name_tmp__326;

  var_name_tmp__318 = var_name_tmp__316;
  var_name_tmp__319 = var_name_tmp__317;
  var_name_tmp__320 = var_name_tmp__319;
  if (((((((uint32_t)(uint16_t)var_name_tmp__320)) == 2048u)&1))) {
    goto var_name_tmp__327;
  } else {
    goto var_name_tmp__328;
  }

var_name_tmp__327:
  var_name_tmp__321 = var_name_tmp__318;
  var_name_tmp__322 = (&var_name_tmp__321->field0);
  var_name_tmp__323 = *(volatile uint16_t*)var_name_tmp__322;
  *(volatile uint16_t*)var_name_tmp__322 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__323)) | 2048)));
  goto var_name_tmp__329;

var_name_tmp__328:
  var_name_tmp__324 = var_name_tmp__318;
  var_name_tmp__325 = (&var_name_tmp__324->field0);
  var_name_tmp__326 = *(volatile uint16_t*)var_name_tmp__325;
  *(volatile uint16_t*)var_name_tmp__325 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__326)) & 63487)));
  goto var_name_tmp__329;

var_name_tmp__329:
  return;
}


void I2C_CalculatePEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__330, uint32_t var_name_tmp__331) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__332;    /* Address-exposed local */
  uint32_t var_name_tmp__333;    /* Address-exposed local */
  uint32_t var_name_tmp__334;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__335;
  uint16_t* var_name_tmp__336;
  uint16_t var_name_tmp__337;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__338;
  uint16_t* var_name_tmp__339;
  uint16_t var_name_tmp__340;

  var_name_tmp__332 = var_name_tmp__330;
  var_name_tmp__333 = var_name_tmp__331;
  var_name_tmp__334 = var_name_tmp__333;
  if ((((var_name_tmp__334 != 0u)&1))) {
    goto var_name_tmp__341;
  } else {
    goto var_name_tmp__342;
  }

var_name_tmp__341:
  var_name_tmp__335 = var_name_tmp__332;
  var_name_tmp__336 = (&var_name_tmp__335->field0);
  var_name_tmp__337 = *(volatile uint16_t*)var_name_tmp__336;
  *(volatile uint16_t*)var_name_tmp__336 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__337)) | 32)));
  goto var_name_tmp__343;

var_name_tmp__342:
  var_name_tmp__338 = var_name_tmp__332;
  var_name_tmp__339 = (&var_name_tmp__338->field0);
  var_name_tmp__340 = *(volatile uint16_t*)var_name_tmp__339;
  *(volatile uint16_t*)var_name_tmp__339 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__340)) & 65503)));
  goto var_name_tmp__343;

var_name_tmp__343:
  return;
}


uint8_t I2C_GetPEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__344) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__345;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__346;
  uint16_t var_name_tmp__347;

  var_name_tmp__345 = var_name_tmp__344;
  var_name_tmp__346 = var_name_tmp__345;
  var_name_tmp__347 = *(volatile uint16_t*)((&var_name_tmp__346->field12));
  return (((uint8_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__347)), 8))));
}


void I2C_DMACmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__348, uint32_t var_name_tmp__349) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__350;    /* Address-exposed local */
  uint32_t var_name_tmp__351;    /* Address-exposed local */
  uint32_t var_name_tmp__352;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__353;
  uint16_t* var_name_tmp__354;
  uint16_t var_name_tmp__355;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__356;
  uint16_t* var_name_tmp__357;
  uint16_t var_name_tmp__358;

  var_name_tmp__350 = var_name_tmp__348;
  var_name_tmp__351 = var_name_tmp__349;
  var_name_tmp__352 = var_name_tmp__351;
  if ((((var_name_tmp__352 != 0u)&1))) {
    goto var_name_tmp__359;
  } else {
    goto var_name_tmp__360;
  }

var_name_tmp__359:
  var_name_tmp__353 = var_name_tmp__350;
  var_name_tmp__354 = (&var_name_tmp__353->field2);
  var_name_tmp__355 = *(volatile uint16_t*)var_name_tmp__354;
  *(volatile uint16_t*)var_name_tmp__354 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__355)) | 2048)));
  goto var_name_tmp__361;

var_name_tmp__360:
  var_name_tmp__356 = var_name_tmp__350;
  var_name_tmp__357 = (&var_name_tmp__356->field2);
  var_name_tmp__358 = *(volatile uint16_t*)var_name_tmp__357;
  *(volatile uint16_t*)var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__358)) & 63487)));
  goto var_name_tmp__361;

var_name_tmp__361:
  return;
}


void I2C_DMALastTransferCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__362, uint32_t var_name_tmp__363) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__364;    /* Address-exposed local */
  uint32_t var_name_tmp__365;    /* Address-exposed local */
  uint32_t var_name_tmp__366;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__367;
  uint16_t* var_name_tmp__368;
  uint16_t var_name_tmp__369;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__370;
  uint16_t* var_name_tmp__371;
  uint16_t var_name_tmp__372;

  var_name_tmp__364 = var_name_tmp__362;
  var_name_tmp__365 = var_name_tmp__363;
  var_name_tmp__366 = var_name_tmp__365;
  if ((((var_name_tmp__366 != 0u)&1))) {
    goto var_name_tmp__373;
  } else {
    goto var_name_tmp__374;
  }

var_name_tmp__373:
  var_name_tmp__367 = var_name_tmp__364;
  var_name_tmp__368 = (&var_name_tmp__367->field2);
  var_name_tmp__369 = *(volatile uint16_t*)var_name_tmp__368;
  *(volatile uint16_t*)var_name_tmp__368 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__369)) | 4096)));
  goto var_name_tmp__375;

var_name_tmp__374:
  var_name_tmp__370 = var_name_tmp__364;
  var_name_tmp__371 = (&var_name_tmp__370->field2);
  var_name_tmp__372 = *(volatile uint16_t*)var_name_tmp__371;
  *(volatile uint16_t*)var_name_tmp__371 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__372)) & 61439)));
  goto var_name_tmp__375;

var_name_tmp__375:
  return;
}


uint16_t I2C_ReadRegister(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__376, uint8_t var_name_tmp__377) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__378;    /* Address-exposed local */
  uint8_t var_name_tmp__379;    /* Address-exposed local */
  uint32_t var_name_tmp__380;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__381;
  uint8_t var_name_tmp__382;
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint16_t var_name_tmp__385;

  var_name_tmp__378 = var_name_tmp__376;
  var_name_tmp__379 = var_name_tmp__377;
  *(volatile uint32_t*)(&var_name_tmp__380) = 0;
  var_name_tmp__381 = var_name_tmp__378;
  *(volatile uint32_t*)(&var_name_tmp__380) = (((uint32_t)(uintptr_t)var_name_tmp__381));
  var_name_tmp__382 = var_name_tmp__379;
  var_name_tmp__383 = *(volatile uint32_t*)(&var_name_tmp__380);
  *(volatile uint32_t*)(&var_name_tmp__380) = (llvm_add_u32(var_name_tmp__383, (((uint32_t)(uint8_t)var_name_tmp__382))));
  var_name_tmp__384 = *(volatile uint32_t*)(&var_name_tmp__380);
  var_name_tmp__385 = *(volatile uint16_t*)(((uint16_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__384))));
  return var_name_tmp__385;
}


void I2C_ITConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__386, uint16_t var_name_tmp__387, uint32_t var_name_tmp__388) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__389;    /* Address-exposed local */
  uint16_t var_name_tmp__390;    /* Address-exposed local */
  uint32_t var_name_tmp__391;    /* Address-exposed local */
  uint32_t var_name_tmp__392;
  uint16_t var_name_tmp__393;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__394;
  uint16_t* var_name_tmp__395;
  uint16_t var_name_tmp__396;
  uint16_t var_name_tmp__397;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__398;
  uint16_t* var_name_tmp__399;
  uint16_t var_name_tmp__400;

  var_name_tmp__389 = var_name_tmp__386;
  var_name_tmp__390 = var_name_tmp__387;
  var_name_tmp__391 = var_name_tmp__388;
  var_name_tmp__392 = var_name_tmp__391;
  if ((((var_name_tmp__392 != 0u)&1))) {
    goto var_name_tmp__401;
  } else {
    goto var_name_tmp__402;
  }

var_name_tmp__401:
  var_name_tmp__393 = var_name_tmp__390;
  var_name_tmp__394 = var_name_tmp__389;
  var_name_tmp__395 = (&var_name_tmp__394->field2);
  var_name_tmp__396 = *(volatile uint16_t*)var_name_tmp__395;
  *(volatile uint16_t*)var_name_tmp__395 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__396)) | (((uint32_t)(uint16_t)var_name_tmp__393)))));
  goto var_name_tmp__403;

var_name_tmp__402:
  var_name_tmp__397 = var_name_tmp__390;
  var_name_tmp__398 = var_name_tmp__389;
  var_name_tmp__399 = (&var_name_tmp__398->field2);
  var_name_tmp__400 = *(volatile uint16_t*)var_name_tmp__399;
  *(volatile uint16_t*)var_name_tmp__399 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__400)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__397)))))))))));
  goto var_name_tmp__403;

var_name_tmp__403:
  return;
}


uint32_t I2C_CheckEvent(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__404, uint32_t var_name_tmp__405) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__406;    /* Address-exposed local */
  uint32_t var_name_tmp__407;    /* Address-exposed local */
  uint32_t var_name_tmp__408;    /* Address-exposed local */
  uint32_t var_name_tmp__409;    /* Address-exposed local */
  uint32_t var_name_tmp__410;    /* Address-exposed local */
  uint32_t var_name_tmp__411;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__412;
  uint16_t var_name_tmp__413;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__414;
  uint16_t var_name_tmp__415;
  uint32_t var_name_tmp__416;
  uint32_t var_name_tmp__417;
  uint32_t var_name_tmp__418;
  uint32_t var_name_tmp__419;
  uint32_t var_name_tmp__420;
  uint32_t var_name_tmp__421;
  uint32_t var_name_tmp__422;

  var_name_tmp__406 = var_name_tmp__404;
  var_name_tmp__407 = var_name_tmp__405;
  var_name_tmp__408 = 0;
  var_name_tmp__409 = 0;
  var_name_tmp__410 = 0;
  var_name_tmp__411 = 0;
  var_name_tmp__412 = var_name_tmp__406;
  var_name_tmp__413 = *(volatile uint16_t*)((&var_name_tmp__412->field10));
  var_name_tmp__409 = (((uint32_t)(uint16_t)var_name_tmp__413));
  var_name_tmp__414 = var_name_tmp__406;
  var_name_tmp__415 = *(volatile uint16_t*)((&var_name_tmp__414->field12));
  var_name_tmp__410 = (((uint32_t)(uint16_t)var_name_tmp__415));
  var_name_tmp__416 = var_name_tmp__410;
  var_name_tmp__410 = (var_name_tmp__416 << 16);
  var_name_tmp__417 = var_name_tmp__409;
  var_name_tmp__418 = var_name_tmp__410;
  var_name_tmp__408 = ((var_name_tmp__417 | var_name_tmp__418) & 16777215);
  var_name_tmp__419 = var_name_tmp__408;
  var_name_tmp__420 = var_name_tmp__407;
  var_name_tmp__421 = var_name_tmp__407;
  if (((((var_name_tmp__419 & var_name_tmp__420) == var_name_tmp__421)&1))) {
    goto var_name_tmp__423;
  } else {
    goto var_name_tmp__424;
  }

var_name_tmp__423:
  var_name_tmp__411 = 1;
  goto var_name_tmp__425;

var_name_tmp__424:
  var_name_tmp__411 = 0;
  goto var_name_tmp__425;

var_name_tmp__425:
  var_name_tmp__422 = var_name_tmp__411;
  return var_name_tmp__422;
}


uint32_t I2C_GetLastEvent(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__426) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__427;    /* Address-exposed local */
  uint32_t var_name_tmp__428;    /* Address-exposed local */
  uint32_t var_name_tmp__429;    /* Address-exposed local */
  uint32_t var_name_tmp__430;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__431;
  uint16_t var_name_tmp__432;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__433;
  uint16_t var_name_tmp__434;
  uint32_t var_name_tmp__435;
  uint32_t var_name_tmp__436;
  uint32_t var_name_tmp__437;
  uint32_t var_name_tmp__438;

  var_name_tmp__427 = var_name_tmp__426;
  var_name_tmp__428 = 0;
  var_name_tmp__429 = 0;
  var_name_tmp__430 = 0;
  var_name_tmp__431 = var_name_tmp__427;
  var_name_tmp__432 = *(volatile uint16_t*)((&var_name_tmp__431->field10));
  var_name_tmp__429 = (((uint32_t)(uint16_t)var_name_tmp__432));
  var_name_tmp__433 = var_name_tmp__427;
  var_name_tmp__434 = *(volatile uint16_t*)((&var_name_tmp__433->field12));
  var_name_tmp__430 = (((uint32_t)(uint16_t)var_name_tmp__434));
  var_name_tmp__435 = var_name_tmp__430;
  var_name_tmp__430 = (var_name_tmp__435 << 16);
  var_name_tmp__436 = var_name_tmp__429;
  var_name_tmp__437 = var_name_tmp__430;
  var_name_tmp__428 = ((var_name_tmp__436 | var_name_tmp__437) & 16777215);
  var_name_tmp__438 = var_name_tmp__428;
  return var_name_tmp__438;
}


uint32_t I2C_GetFlagStatus(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__439, uint32_t var_name_tmp__440) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__441;    /* Address-exposed local */
  uint32_t var_name_tmp__442;    /* Address-exposed local */
  uint32_t var_name_tmp__443;    /* Address-exposed local */
  uint32_t var_name_tmp__444;    /* Address-exposed local */
  uint32_t var_name_tmp__445;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__446;
  uint32_t var_name_tmp__447;
  uint32_t var_name_tmp__448;
  uint32_t var_name_tmp__449;
  uint32_t var_name_tmp__450;
  uint32_t var_name_tmp__451;
  uint32_t var_name_tmp__452;
  uint32_t var_name_tmp__453;
  uint32_t var_name_tmp__454;
  uint32_t var_name_tmp__455;
  uint32_t var_name_tmp__456;

  var_name_tmp__441 = var_name_tmp__439;
  var_name_tmp__442 = var_name_tmp__440;
  var_name_tmp__443 = 0;
  *(volatile uint32_t*)(&var_name_tmp__444) = 0;
  *(volatile uint32_t*)(&var_name_tmp__445) = 0;
  var_name_tmp__446 = var_name_tmp__441;
  *(volatile uint32_t*)(&var_name_tmp__445) = (((uint32_t)(uintptr_t)var_name_tmp__446));
  var_name_tmp__447 = var_name_tmp__442;
  *(volatile uint32_t*)(&var_name_tmp__444) = (llvm_lshr_u32(var_name_tmp__447, 28));
  var_name_tmp__448 = var_name_tmp__442;
  var_name_tmp__442 = (var_name_tmp__448 & 16777215);
  var_name_tmp__449 = *(volatile uint32_t*)(&var_name_tmp__444);
  if ((((var_name_tmp__449 != 0u)&1))) {
    goto var_name_tmp__457;
  } else {
    goto var_name_tmp__458;
  }

var_name_tmp__457:
  var_name_tmp__450 = *(volatile uint32_t*)(&var_name_tmp__445);
  *(volatile uint32_t*)(&var_name_tmp__445) = (llvm_add_u32(var_name_tmp__450, 20));
  goto var_name_tmp__459;

var_name_tmp__458:
  var_name_tmp__451 = var_name_tmp__442;
  var_name_tmp__442 = (llvm_lshr_u32(var_name_tmp__451, 16));
  var_name_tmp__452 = *(volatile uint32_t*)(&var_name_tmp__445);
  *(volatile uint32_t*)(&var_name_tmp__445) = (llvm_add_u32(var_name_tmp__452, 24));
  goto var_name_tmp__459;

var_name_tmp__459:
  var_name_tmp__453 = *(volatile uint32_t*)(&var_name_tmp__445);
  var_name_tmp__454 = *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__453))));
  var_name_tmp__455 = var_name_tmp__442;
  if (((((var_name_tmp__454 & var_name_tmp__455) != 0u)&1))) {
    goto var_name_tmp__460;
  } else {
    goto var_name_tmp__461;
  }

var_name_tmp__460:
  var_name_tmp__443 = 1;
  goto var_name_tmp__462;

var_name_tmp__461:
  var_name_tmp__443 = 0;
  goto var_name_tmp__462;

var_name_tmp__462:
  var_name_tmp__456 = var_name_tmp__443;
  return var_name_tmp__456;
}


void I2C_ClearFlag(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__463, uint32_t var_name_tmp__464) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__465;    /* Address-exposed local */
  uint32_t var_name_tmp__466;    /* Address-exposed local */
  uint32_t var_name_tmp__467;    /* Address-exposed local */
  uint32_t var_name_tmp__468;
  uint32_t var_name_tmp__469;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__470;

  var_name_tmp__465 = var_name_tmp__463;
  var_name_tmp__466 = var_name_tmp__464;
  var_name_tmp__467 = 0;
  var_name_tmp__468 = var_name_tmp__466;
  var_name_tmp__467 = (var_name_tmp__468 & 16777215);
  var_name_tmp__469 = var_name_tmp__467;
  var_name_tmp__470 = var_name_tmp__465;
  *(volatile uint16_t*)((&var_name_tmp__470->field10)) = (((uint16_t)(~(var_name_tmp__469))));
}


uint32_t I2C_GetITStatus(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__471, uint32_t var_name_tmp__472) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__473;    /* Address-exposed local */
  uint32_t var_name_tmp__474;    /* Address-exposed local */
  uint32_t var_name_tmp__475;    /* Address-exposed local */
  uint32_t var_name_tmp__476;    /* Address-exposed local */
  uint32_t var_name_tmp__477;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__478;
  uint16_t var_name_tmp__479;
  uint32_t var_name_tmp__480;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__481;
  uint16_t var_name_tmp__482;
  uint32_t var_name_tmp__483;
  uint32_t var_name_tmp__484;
  uint32_t var_name_tmp__485;

  var_name_tmp__473 = var_name_tmp__471;
  var_name_tmp__474 = var_name_tmp__472;
  var_name_tmp__475 = 0;
  var_name_tmp__476 = 0;
  var_name_tmp__477 = var_name_tmp__474;
  var_name_tmp__478 = var_name_tmp__473;
  var_name_tmp__479 = *(volatile uint16_t*)((&var_name_tmp__478->field2));
  var_name_tmp__476 = ((llvm_lshr_u32((var_name_tmp__477 & 117440512), 16)) & (((uint32_t)(uint16_t)var_name_tmp__479)));
  var_name_tmp__480 = var_name_tmp__474;
  var_name_tmp__474 = (var_name_tmp__480 & 16777215);
  var_name_tmp__481 = var_name_tmp__473;
  var_name_tmp__482 = *(volatile uint16_t*)((&var_name_tmp__481->field10));
  var_name_tmp__483 = var_name_tmp__474;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__482)) & var_name_tmp__483) != 0u)&1))) {
    goto var_name_tmp__486;
  } else {
    goto var_name_tmp__487;
  }

var_name_tmp__486:
  var_name_tmp__484 = var_name_tmp__476;
  if ((((var_name_tmp__484 != 0u)&1))) {
    goto var_name_tmp__488;
  } else {
    goto var_name_tmp__487;
  }

var_name_tmp__488:
  var_name_tmp__475 = 1;
  goto var_name_tmp__489;

var_name_tmp__487:
  var_name_tmp__475 = 0;
  goto var_name_tmp__489;

var_name_tmp__489:
  var_name_tmp__485 = var_name_tmp__475;
  return var_name_tmp__485;
}


void I2C_ClearITPendingBit(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__490, uint32_t var_name_tmp__491) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__492;    /* Address-exposed local */
  uint32_t var_name_tmp__493;    /* Address-exposed local */
  uint32_t var_name_tmp__494;    /* Address-exposed local */
  uint32_t var_name_tmp__495;
  uint32_t var_name_tmp__496;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__497;

  var_name_tmp__492 = var_name_tmp__490;
  var_name_tmp__493 = var_name_tmp__491;
  var_name_tmp__494 = 0;
  var_name_tmp__495 = var_name_tmp__493;
  var_name_tmp__494 = (var_name_tmp__495 & 16777215);
  var_name_tmp__496 = var_name_tmp__494;
  var_name_tmp__497 = var_name_tmp__492;
  *(volatile uint16_t*)((&var_name_tmp__497->field10)) = (((uint16_t)(~(var_name_tmp__496))));
}

