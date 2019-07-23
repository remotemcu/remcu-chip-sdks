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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


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
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__24;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__25;
  uint16_t var_name_tmp__26;
  uint16_t var_name_tmp__27;
  uint16_t var_name_tmp__28;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__29;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__30;
  uint16_t* var_name_tmp__31;
  uint64_t var_name_load_i16_3;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__32;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__33;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__34;
  uint64_t var_name_load_i32_11;
  uint16_t var_name_tmp__35;
  uint16_t var_name_tmp__36;
  uint16_t var_name_tmp__37;
  uint16_t var_name_tmp__38;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__39;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__40;
  uint64_t var_name_load_i16_16;
  uint32_t var_name_tmp__41;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__42;
  uint64_t var_name_load_i32_19;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__44;
  uint64_t var_name_load_i32_22;
  uint16_t var_name_tmp__45;
  uint16_t var_name_tmp__46;
  uint16_t var_name_tmp__47;
  uint16_t var_name_tmp__48;
  uint16_t var_name_tmp__49;
  uint16_t var_name_tmp__50;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__51;
  uint16_t var_name_tmp__52;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__53;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__54;
  uint16_t* var_name_tmp__55;
  uint64_t var_name_load_i16_29;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__56;
  uint64_t var_name_load_i16_34;
  uint16_t var_name_tmp__57;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__58;
  uint64_t var_name_load_i16_37;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__59;
  uint64_t var_name_load_i16_40;
  uint16_t var_name_tmp__60;
  uint16_t var_name_tmp__61;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__62;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__63;
  uint64_t var_name_load_i16_45;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__64;
  uint64_t var_name_load_i16_48;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__65;

  var_name_tmp__16 = var_name_tmp__14;
  var_name_tmp__17 = var_name_tmp__15;
  var_name_tmp__18 = 0;
  var_name_tmp__19 = 0;
  var_name_tmp__20 = 4;
  var_name_tmp__21 = 8000000;
  var_name_tmp__23 = var_name_tmp__16;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__23->field2)))), 16, 2);
  var_name_tmp__18 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__24 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__24)) & 65472)));
  RCC_GetClocksFreq((&var_name_tmp__22));
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__22.field2)))), 32, 4);
  var_name_tmp__21 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__25 = var_name_tmp__21;
  var_name_tmp__19 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__25, 1000000))));
  var_name_tmp__26 = var_name_tmp__19;
  var_name_tmp__27 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__27)) | (((uint32_t)(uint16_t)var_name_tmp__26)))));
  var_name_tmp__28 = var_name_tmp__18;
  var_name_tmp__29 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__29->field2)))), (((uint64_t)(uint16_t)var_name_tmp__28)), 16, 2);
  var_name_tmp__30 = var_name_tmp__16;
  var_name_tmp__31 = (&var_name_tmp__30->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__31)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__31)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65534))))), 16, 2);
  var_name_tmp__18 = 0;
  var_name_tmp__32 = var_name_tmp__17;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__32->field0)))), 32, 4);
  if ((((((uint32_t)(((uint32_t)var_name_load_i32_8))) <= ((uint32_t)100000u))&1))) {
    goto var_name_tmp__66;
  } else {
    goto var_name_tmp__67;
  }

var_name_tmp__66:
  var_name_tmp__33 = var_name_tmp__21;
  var_name_tmp__34 = var_name_tmp__17;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__34->field0)))), 32, 4);
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__33, ((((uint32_t)var_name_load_i32_11)) << 1)))));
  var_name_tmp__35 = var_name_tmp__20;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__35))) < ((int32_t)4u))&1))) {
    goto var_name_tmp__68;
  } else {
    goto var_name_tmp__69;
  }

var_name_tmp__68:
  var_name_tmp__20 = 4;
  goto var_name_tmp__69;

var_name_tmp__69:
  var_name_tmp__36 = var_name_tmp__20;
  var_name_tmp__37 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__37)) | (((uint32_t)(uint16_t)var_name_tmp__36)))));
  var_name_tmp__38 = var_name_tmp__19;
  var_name_tmp__39 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__39->field16)))), (((uint64_t)(uint16_t)(((uint16_t)(llvm_add_u32((((uint32_t)(uint16_t)var_name_tmp__38)), 1)))))), 16, 2);
  goto var_name_tmp__70;

var_name_tmp__67:
  var_name_tmp__40 = var_name_tmp__17;
  var_name_load_i16_16 = __adin_load_((((uint8_t*)((&var_name_tmp__40->field2)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_16)))) == 49151u)&1))) {
    goto var_name_tmp__71;
  } else {
    goto var_name_tmp__72;
  }

var_name_tmp__71:
  var_name_tmp__41 = var_name_tmp__21;
  var_name_tmp__42 = var_name_tmp__17;
  var_name_load_i32_19 = __adin_load_((((uint8_t*)((&var_name_tmp__42->field0)))), 32, 4);
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__41, (llvm_mul_u32((((uint32_t)var_name_load_i32_19)), 3))))));
  goto var_name_tmp__73;

var_name_tmp__72:
  var_name_tmp__43 = var_name_tmp__21;
  var_name_tmp__44 = var_name_tmp__17;
  var_name_load_i32_22 = __adin_load_((((uint8_t*)((&var_name_tmp__44->field0)))), 32, 4);
  var_name_tmp__20 = (((uint16_t)(llvm_udiv_u32(var_name_tmp__43, (llvm_mul_u32((((uint32_t)var_name_load_i32_22)), 25))))));
  var_name_tmp__45 = var_name_tmp__20;
  var_name_tmp__20 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__45)) | 16384)));
  goto var_name_tmp__73;

var_name_tmp__73:
  var_name_tmp__46 = var_name_tmp__20;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__46)) & 4095) == 0u)&1))) {
    goto var_name_tmp__74;
  } else {
    goto var_name_tmp__75;
  }

var_name_tmp__74:
  var_name_tmp__47 = var_name_tmp__20;
  var_name_tmp__20 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__47)) | 1)));
  goto var_name_tmp__75;

var_name_tmp__75:
  var_name_tmp__48 = var_name_tmp__20;
  var_name_tmp__49 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__49)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__48)) | 32768))))))));
  var_name_tmp__50 = var_name_tmp__19;
  var_name_tmp__51 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__51->field16)))), (((uint64_t)(uint16_t)(((uint16_t)(llvm_add_u32((llvm_sdiv_u32((llvm_mul_u32((((uint32_t)(uint16_t)var_name_tmp__50)), 300)), 1000)), 1)))))), 16, 2);
  goto var_name_tmp__70;

var_name_tmp__70:
  var_name_tmp__52 = var_name_tmp__18;
  var_name_tmp__53 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__53->field14)))), (((uint64_t)(uint16_t)var_name_tmp__52)), 16, 2);
  var_name_tmp__54 = var_name_tmp__16;
  var_name_tmp__55 = (&var_name_tmp__54->field0);
  var_name_load_i16_29 = __adin_load_((((uint8_t*)var_name_tmp__55)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__55)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_29)))) | 1))))), 16, 2);
  var_name_tmp__56 = var_name_tmp__16;
  var_name_load_i16_34 = __adin_load_((((uint8_t*)((&var_name_tmp__56->field0)))), 16, 2);
  var_name_tmp__18 = (((uint16_t)var_name_load_i16_34));
  var_name_tmp__57 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__57)) & 64501)));
  var_name_tmp__58 = var_name_tmp__17;
  var_name_load_i16_37 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field1)))), 16, 4);
  var_name_tmp__59 = var_name_tmp__17;
  var_name_load_i16_40 = __adin_load_((((uint8_t*)((&var_name_tmp__59->field4)))), 16, 2);
  var_name_tmp__60 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__60)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_37)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_40))))))))))));
  var_name_tmp__61 = var_name_tmp__18;
  var_name_tmp__62 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__62->field0)))), (((uint64_t)(uint16_t)var_name_tmp__61)), 16, 2);
  var_name_tmp__63 = var_name_tmp__17;
  var_name_load_i16_45 = __adin_load_((((uint8_t*)((&var_name_tmp__63->field5)))), 16, 4);
  var_name_tmp__64 = var_name_tmp__17;
  var_name_load_i16_48 = __adin_load_((((uint8_t*)((&var_name_tmp__64->field3)))), 16, 4);
  var_name_tmp__65 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__65->field4)))), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_45)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_48))))))))), 16, 2);
}


void I2C_StructInit(struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__76) {
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__77;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__78;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__79;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__80;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__81;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__82;
  struct l_struct_struct_OC_I2C_InitTypeDef* var_name_tmp__83;

  var_name_tmp__77 = var_name_tmp__76;
  var_name_tmp__78 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__78->field0)))), UINT64_C(5000), 32, 4);
  var_name_tmp__79 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__79->field1)))), UINT64_C(0), 16, 4);
  var_name_tmp__80 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__80->field2)))), UINT64_C(49151), 16, 2);
  var_name_tmp__81 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__81->field3)))), UINT64_C(0), 16, 4);
  var_name_tmp__82 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__82->field4)))), UINT64_C(0), 16, 2);
  var_name_tmp__83 = var_name_tmp__77;
  __adin_store_((((uint8_t*)((&var_name_tmp__83->field5)))), UINT64_C(16384), 16, 4);
}


void I2C_Cmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__84, uint32_t var_name_tmp__85) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__86;    /* Address-exposed local */
  uint32_t var_name_tmp__87;    /* Address-exposed local */
  uint32_t var_name_tmp__88;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__89;
  uint16_t* var_name_tmp__90;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__91;
  uint16_t* var_name_tmp__92;
  uint64_t var_name_load_i16_3;

  var_name_tmp__86 = var_name_tmp__84;
  var_name_tmp__87 = var_name_tmp__85;
  var_name_tmp__88 = var_name_tmp__87;
  if ((((var_name_tmp__88 != 0u)&1))) {
    goto var_name_tmp__93;
  } else {
    goto var_name_tmp__94;
  }

var_name_tmp__93:
  var_name_tmp__89 = var_name_tmp__86;
  var_name_tmp__90 = (&var_name_tmp__89->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__90)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__90)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1))))), 16, 2);
  goto var_name_tmp__95;

var_name_tmp__94:
  var_name_tmp__91 = var_name_tmp__86;
  var_name_tmp__92 = (&var_name_tmp__91->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__92)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__92)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65534))))), 16, 2);
  goto var_name_tmp__95;

var_name_tmp__95:
  return;
}


void I2C_GenerateSTART(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__96, uint32_t var_name_tmp__97) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__101;
  uint16_t* var_name_tmp__102;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__103;
  uint16_t* var_name_tmp__104;
  uint64_t var_name_load_i16_3;

  var_name_tmp__98 = var_name_tmp__96;
  var_name_tmp__99 = var_name_tmp__97;
  var_name_tmp__100 = var_name_tmp__99;
  if ((((var_name_tmp__100 != 0u)&1))) {
    goto var_name_tmp__105;
  } else {
    goto var_name_tmp__106;
  }

var_name_tmp__105:
  var_name_tmp__101 = var_name_tmp__98;
  var_name_tmp__102 = (&var_name_tmp__101->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__102)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__102)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 256))))), 16, 2);
  goto var_name_tmp__107;

var_name_tmp__106:
  var_name_tmp__103 = var_name_tmp__98;
  var_name_tmp__104 = (&var_name_tmp__103->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__104)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__104)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65279))))), 16, 2);
  goto var_name_tmp__107;

var_name_tmp__107:
  return;
}


void I2C_GenerateSTOP(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__108, uint32_t var_name_tmp__109) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__110;    /* Address-exposed local */
  uint32_t var_name_tmp__111;    /* Address-exposed local */
  uint32_t var_name_tmp__112;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__113;
  uint16_t* var_name_tmp__114;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__115;
  uint16_t* var_name_tmp__116;
  uint64_t var_name_load_i16_3;

  var_name_tmp__110 = var_name_tmp__108;
  var_name_tmp__111 = var_name_tmp__109;
  var_name_tmp__112 = var_name_tmp__111;
  if ((((var_name_tmp__112 != 0u)&1))) {
    goto var_name_tmp__117;
  } else {
    goto var_name_tmp__118;
  }

var_name_tmp__117:
  var_name_tmp__113 = var_name_tmp__110;
  var_name_tmp__114 = (&var_name_tmp__113->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__114)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__114)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 512))))), 16, 2);
  goto var_name_tmp__119;

var_name_tmp__118:
  var_name_tmp__115 = var_name_tmp__110;
  var_name_tmp__116 = (&var_name_tmp__115->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__116)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__116)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65023))))), 16, 2);
  goto var_name_tmp__119;

var_name_tmp__119:
  return;
}


void I2C_Send7bitAddress(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__120, uint8_t var_name_tmp__121, uint8_t var_name_tmp__122) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__123;    /* Address-exposed local */
  uint8_t var_name_tmp__124;    /* Address-exposed local */
  uint8_t var_name_tmp__125;    /* Address-exposed local */
  uint8_t var_name_tmp__126;
  uint8_t var_name_tmp__127;
  uint8_t var_name_tmp__128;
  uint8_t var_name_tmp__129;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__130;

  var_name_tmp__123 = var_name_tmp__120;
  var_name_tmp__124 = var_name_tmp__121;
  var_name_tmp__125 = var_name_tmp__122;
  var_name_tmp__126 = var_name_tmp__125;
  if (((((((uint32_t)(uint8_t)var_name_tmp__126)) != 0u)&1))) {
    goto var_name_tmp__131;
  } else {
    goto var_name_tmp__132;
  }

var_name_tmp__131:
  var_name_tmp__127 = var_name_tmp__124;
  var_name_tmp__124 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__127)) | 1)));
  goto var_name_tmp__133;

var_name_tmp__132:
  var_name_tmp__128 = var_name_tmp__124;
  var_name_tmp__124 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__128)) & 254)));
  goto var_name_tmp__133;

var_name_tmp__133:
  var_name_tmp__129 = var_name_tmp__124;
  var_name_tmp__130 = var_name_tmp__123;
  __adin_store_((((uint8_t*)((&var_name_tmp__130->field8)))), (((uint64_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__129)))), 16, 2);
}


void I2C_AcknowledgeConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__134, uint32_t var_name_tmp__135) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;    /* Address-exposed local */
  uint32_t var_name_tmp__138;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__139;
  uint16_t* var_name_tmp__140;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__141;
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
  var_name_tmp__140 = (&var_name_tmp__139->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__140)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__140)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1024))))), 16, 2);
  goto var_name_tmp__145;

var_name_tmp__144:
  var_name_tmp__141 = var_name_tmp__136;
  var_name_tmp__142 = (&var_name_tmp__141->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__142)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__142)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 64511))))), 16, 2);
  goto var_name_tmp__145;

var_name_tmp__145:
  return;
}


void I2C_OwnAddress2Config(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__146, uint8_t var_name_tmp__147) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__148;    /* Address-exposed local */
  uint8_t var_name_tmp__149;    /* Address-exposed local */
  uint16_t var_name_tmp__150;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__151;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__152;
  uint8_t var_name_tmp__153;
  uint16_t var_name_tmp__154;
  uint16_t var_name_tmp__155;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__156;

  var_name_tmp__148 = var_name_tmp__146;
  var_name_tmp__149 = var_name_tmp__147;
  var_name_tmp__150 = 0;
  var_name_tmp__151 = var_name_tmp__148;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__151->field6)))), 16, 2);
  var_name_tmp__150 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__152 = var_name_tmp__150;
  var_name_tmp__150 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__152)) & 65281)));
  var_name_tmp__153 = var_name_tmp__149;
  var_name_tmp__154 = var_name_tmp__150;
  var_name_tmp__150 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__154)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__153)))) & 254))))))));
  var_name_tmp__155 = var_name_tmp__150;
  var_name_tmp__156 = var_name_tmp__148;
  __adin_store_((((uint8_t*)((&var_name_tmp__156->field6)))), (((uint64_t)(uint16_t)var_name_tmp__155)), 16, 2);
}


void I2C_DualAddressCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__157, uint32_t var_name_tmp__158) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__159;    /* Address-exposed local */
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__162;
  uint16_t* var_name_tmp__163;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__164;
  uint16_t* var_name_tmp__165;
  uint64_t var_name_load_i16_3;

  var_name_tmp__159 = var_name_tmp__157;
  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__160;
  if ((((var_name_tmp__161 != 0u)&1))) {
    goto var_name_tmp__166;
  } else {
    goto var_name_tmp__167;
  }

var_name_tmp__166:
  var_name_tmp__162 = var_name_tmp__159;
  var_name_tmp__163 = (&var_name_tmp__162->field6);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__163)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__163)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1))))), 16, 2);
  goto var_name_tmp__168;

var_name_tmp__167:
  var_name_tmp__164 = var_name_tmp__159;
  var_name_tmp__165 = (&var_name_tmp__164->field6);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__165)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__165)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65534))))), 16, 2);
  goto var_name_tmp__168;

var_name_tmp__168:
  return;
}


void I2C_GeneralCallCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__169, uint32_t var_name_tmp__170) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__171;    /* Address-exposed local */
  uint32_t var_name_tmp__172;    /* Address-exposed local */
  uint32_t var_name_tmp__173;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__174;
  uint16_t* var_name_tmp__175;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__176;
  uint16_t* var_name_tmp__177;
  uint64_t var_name_load_i16_3;

  var_name_tmp__171 = var_name_tmp__169;
  var_name_tmp__172 = var_name_tmp__170;
  var_name_tmp__173 = var_name_tmp__172;
  if ((((var_name_tmp__173 != 0u)&1))) {
    goto var_name_tmp__178;
  } else {
    goto var_name_tmp__179;
  }

var_name_tmp__178:
  var_name_tmp__174 = var_name_tmp__171;
  var_name_tmp__175 = (&var_name_tmp__174->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__175)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__175)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 64))))), 16, 2);
  goto var_name_tmp__180;

var_name_tmp__179:
  var_name_tmp__176 = var_name_tmp__171;
  var_name_tmp__177 = (&var_name_tmp__176->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__177)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__177)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65471))))), 16, 2);
  goto var_name_tmp__180;

var_name_tmp__180:
  return;
}


void I2C_SoftwareResetCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__181, uint32_t var_name_tmp__182) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__183;    /* Address-exposed local */
  uint32_t var_name_tmp__184;    /* Address-exposed local */
  uint32_t var_name_tmp__185;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__186;
  uint16_t* var_name_tmp__187;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__188;
  uint16_t* var_name_tmp__189;
  uint64_t var_name_load_i16_3;

  var_name_tmp__183 = var_name_tmp__181;
  var_name_tmp__184 = var_name_tmp__182;
  var_name_tmp__185 = var_name_tmp__184;
  if ((((var_name_tmp__185 != 0u)&1))) {
    goto var_name_tmp__190;
  } else {
    goto var_name_tmp__191;
  }

var_name_tmp__190:
  var_name_tmp__186 = var_name_tmp__183;
  var_name_tmp__187 = (&var_name_tmp__186->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__187)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__187)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 32768))))), 16, 2);
  goto var_name_tmp__192;

var_name_tmp__191:
  var_name_tmp__188 = var_name_tmp__183;
  var_name_tmp__189 = (&var_name_tmp__188->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__189)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__189)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 32767))))), 16, 2);
  goto var_name_tmp__192;

var_name_tmp__192:
  return;
}


void I2C_StretchClockCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__193, uint32_t var_name_tmp__194) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__195;    /* Address-exposed local */
  uint32_t var_name_tmp__196;    /* Address-exposed local */
  uint32_t var_name_tmp__197;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__198;
  uint16_t* var_name_tmp__199;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__200;
  uint16_t* var_name_tmp__201;
  uint64_t var_name_load_i16_3;

  var_name_tmp__195 = var_name_tmp__193;
  var_name_tmp__196 = var_name_tmp__194;
  var_name_tmp__197 = var_name_tmp__196;
  if ((((var_name_tmp__197 == 0u)&1))) {
    goto var_name_tmp__202;
  } else {
    goto var_name_tmp__203;
  }

var_name_tmp__202:
  var_name_tmp__198 = var_name_tmp__195;
  var_name_tmp__199 = (&var_name_tmp__198->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__199)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__199)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 128))))), 16, 2);
  goto var_name_tmp__204;

var_name_tmp__203:
  var_name_tmp__200 = var_name_tmp__195;
  var_name_tmp__201 = (&var_name_tmp__200->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__201)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__201)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65407))))), 16, 2);
  goto var_name_tmp__204;

var_name_tmp__204:
  return;
}


void I2C_FastModeDutyCycleConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__205, uint16_t var_name_tmp__206) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__207;    /* Address-exposed local */
  uint16_t var_name_tmp__208;    /* Address-exposed local */
  uint16_t var_name_tmp__209;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__210;
  uint16_t* var_name_tmp__211;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__212;
  uint16_t* var_name_tmp__213;
  uint64_t var_name_load_i16_3;

  var_name_tmp__207 = var_name_tmp__205;
  var_name_tmp__208 = var_name_tmp__206;
  var_name_tmp__209 = var_name_tmp__208;
  if (((((((uint32_t)(uint16_t)var_name_tmp__209)) != 16384u)&1))) {
    goto var_name_tmp__214;
  } else {
    goto var_name_tmp__215;
  }

var_name_tmp__214:
  var_name_tmp__210 = var_name_tmp__207;
  var_name_tmp__211 = (&var_name_tmp__210->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__211)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__211)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 49151))))), 16, 2);
  goto var_name_tmp__216;

var_name_tmp__215:
  var_name_tmp__212 = var_name_tmp__207;
  var_name_tmp__213 = (&var_name_tmp__212->field14);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__213)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__213)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | 16384))))), 16, 2);
  goto var_name_tmp__216;

var_name_tmp__216:
  return;
}


void I2C_NACKPositionConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__217, uint16_t var_name_tmp__218) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__219;    /* Address-exposed local */
  uint16_t var_name_tmp__220;    /* Address-exposed local */
  uint16_t var_name_tmp__221;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__222;
  uint16_t* var_name_tmp__223;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__224;
  uint16_t* var_name_tmp__225;
  uint64_t var_name_load_i16_3;

  var_name_tmp__219 = var_name_tmp__217;
  var_name_tmp__220 = var_name_tmp__218;
  var_name_tmp__221 = var_name_tmp__220;
  if (((((((uint32_t)(uint16_t)var_name_tmp__221)) == 2048u)&1))) {
    goto var_name_tmp__226;
  } else {
    goto var_name_tmp__227;
  }

var_name_tmp__226:
  var_name_tmp__222 = var_name_tmp__219;
  var_name_tmp__223 = (&var_name_tmp__222->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__223)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__223)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2048))))), 16, 2);
  goto var_name_tmp__228;

var_name_tmp__227:
  var_name_tmp__224 = var_name_tmp__219;
  var_name_tmp__225 = (&var_name_tmp__224->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__225)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__225)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 63487))))), 16, 2);
  goto var_name_tmp__228;

var_name_tmp__228:
  return;
}


void I2C_SMBusAlertConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__229, uint16_t var_name_tmp__230) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__231;    /* Address-exposed local */
  uint16_t var_name_tmp__232;    /* Address-exposed local */
  uint16_t var_name_tmp__233;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__234;
  uint16_t* var_name_tmp__235;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__236;
  uint16_t* var_name_tmp__237;
  uint64_t var_name_load_i16_3;

  var_name_tmp__231 = var_name_tmp__229;
  var_name_tmp__232 = var_name_tmp__230;
  var_name_tmp__233 = var_name_tmp__232;
  if (((((((uint32_t)(uint16_t)var_name_tmp__233)) == 8192u)&1))) {
    goto var_name_tmp__238;
  } else {
    goto var_name_tmp__239;
  }

var_name_tmp__238:
  var_name_tmp__234 = var_name_tmp__231;
  var_name_tmp__235 = (&var_name_tmp__234->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__235)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__235)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 8192))))), 16, 2);
  goto var_name_tmp__240;

var_name_tmp__239:
  var_name_tmp__236 = var_name_tmp__231;
  var_name_tmp__237 = (&var_name_tmp__236->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__237)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__237)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 57343))))), 16, 2);
  goto var_name_tmp__240;

var_name_tmp__240:
  return;
}


void I2C_ARPCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__241, uint32_t var_name_tmp__242) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__243;    /* Address-exposed local */
  uint32_t var_name_tmp__244;    /* Address-exposed local */
  uint32_t var_name_tmp__245;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__246;
  uint16_t* var_name_tmp__247;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__248;
  uint16_t* var_name_tmp__249;
  uint64_t var_name_load_i16_3;

  var_name_tmp__243 = var_name_tmp__241;
  var_name_tmp__244 = var_name_tmp__242;
  var_name_tmp__245 = var_name_tmp__244;
  if ((((var_name_tmp__245 != 0u)&1))) {
    goto var_name_tmp__250;
  } else {
    goto var_name_tmp__251;
  }

var_name_tmp__250:
  var_name_tmp__246 = var_name_tmp__243;
  var_name_tmp__247 = (&var_name_tmp__246->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__247)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__247)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16))))), 16, 2);
  goto var_name_tmp__252;

var_name_tmp__251:
  var_name_tmp__248 = var_name_tmp__243;
  var_name_tmp__249 = (&var_name_tmp__248->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__249)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__249)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65519))))), 16, 2);
  goto var_name_tmp__252;

var_name_tmp__252:
  return;
}


void I2C_SendData(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__253, uint8_t var_name_tmp__254) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__255;    /* Address-exposed local */
  uint8_t var_name_tmp__256;    /* Address-exposed local */
  uint8_t var_name_tmp__257;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__258;

  var_name_tmp__255 = var_name_tmp__253;
  var_name_tmp__256 = var_name_tmp__254;
  var_name_tmp__257 = var_name_tmp__256;
  var_name_tmp__258 = var_name_tmp__255;
  __adin_store_((((uint8_t*)((&var_name_tmp__258->field8)))), (((uint64_t)(uint16_t)(((uint16_t)(uint8_t)var_name_tmp__257)))), 16, 2);
}


uint8_t I2C_ReceiveData(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__259) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__260;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__261;
  uint64_t var_name_load_i16_;

  var_name_tmp__260 = var_name_tmp__259;
  var_name_tmp__261 = var_name_tmp__260;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__261->field8)))), 16, 2);
  return (((uint8_t)(((uint16_t)var_name_load_i16_))));
}


void I2C_TransmitPEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__262, uint32_t var_name_tmp__263) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__264;    /* Address-exposed local */
  uint32_t var_name_tmp__265;    /* Address-exposed local */
  uint32_t var_name_tmp__266;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__267;
  uint16_t* var_name_tmp__268;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__269;
  uint16_t* var_name_tmp__270;
  uint64_t var_name_load_i16_3;

  var_name_tmp__264 = var_name_tmp__262;
  var_name_tmp__265 = var_name_tmp__263;
  var_name_tmp__266 = var_name_tmp__265;
  if ((((var_name_tmp__266 != 0u)&1))) {
    goto var_name_tmp__271;
  } else {
    goto var_name_tmp__272;
  }

var_name_tmp__271:
  var_name_tmp__267 = var_name_tmp__264;
  var_name_tmp__268 = (&var_name_tmp__267->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__268)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__268)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4096))))), 16, 2);
  goto var_name_tmp__273;

var_name_tmp__272:
  var_name_tmp__269 = var_name_tmp__264;
  var_name_tmp__270 = (&var_name_tmp__269->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__270)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__270)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 61439))))), 16, 2);
  goto var_name_tmp__273;

var_name_tmp__273:
  return;
}


void I2C_PECPositionConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__274, uint16_t var_name_tmp__275) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__276;    /* Address-exposed local */
  uint16_t var_name_tmp__277;    /* Address-exposed local */
  uint16_t var_name_tmp__278;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__279;
  uint16_t* var_name_tmp__280;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__281;
  uint16_t* var_name_tmp__282;
  uint64_t var_name_load_i16_3;

  var_name_tmp__276 = var_name_tmp__274;
  var_name_tmp__277 = var_name_tmp__275;
  var_name_tmp__278 = var_name_tmp__277;
  if (((((((uint32_t)(uint16_t)var_name_tmp__278)) == 2048u)&1))) {
    goto var_name_tmp__283;
  } else {
    goto var_name_tmp__284;
  }

var_name_tmp__283:
  var_name_tmp__279 = var_name_tmp__276;
  var_name_tmp__280 = (&var_name_tmp__279->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__280)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__280)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2048))))), 16, 2);
  goto var_name_tmp__285;

var_name_tmp__284:
  var_name_tmp__281 = var_name_tmp__276;
  var_name_tmp__282 = (&var_name_tmp__281->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__282)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__282)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 63487))))), 16, 2);
  goto var_name_tmp__285;

var_name_tmp__285:
  return;
}


void I2C_CalculatePEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__286, uint32_t var_name_tmp__287) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__288;    /* Address-exposed local */
  uint32_t var_name_tmp__289;    /* Address-exposed local */
  uint32_t var_name_tmp__290;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__291;
  uint16_t* var_name_tmp__292;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__293;
  uint16_t* var_name_tmp__294;
  uint64_t var_name_load_i16_3;

  var_name_tmp__288 = var_name_tmp__286;
  var_name_tmp__289 = var_name_tmp__287;
  var_name_tmp__290 = var_name_tmp__289;
  if ((((var_name_tmp__290 != 0u)&1))) {
    goto var_name_tmp__295;
  } else {
    goto var_name_tmp__296;
  }

var_name_tmp__295:
  var_name_tmp__291 = var_name_tmp__288;
  var_name_tmp__292 = (&var_name_tmp__291->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__292)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__292)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 32))))), 16, 2);
  goto var_name_tmp__297;

var_name_tmp__296:
  var_name_tmp__293 = var_name_tmp__288;
  var_name_tmp__294 = (&var_name_tmp__293->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__294)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__294)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65503))))), 16, 2);
  goto var_name_tmp__297;

var_name_tmp__297:
  return;
}


uint8_t I2C_GetPEC(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__298) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__299;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__300;
  uint64_t var_name_load_i16_;

  var_name_tmp__299 = var_name_tmp__298;
  var_name_tmp__300 = var_name_tmp__299;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__300->field12)))), 16, 2);
  return (((uint8_t)(llvm_ashr_u32((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))), 8))));
}


void I2C_DMACmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__301, uint32_t var_name_tmp__302) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__303;    /* Address-exposed local */
  uint32_t var_name_tmp__304;    /* Address-exposed local */
  uint32_t var_name_tmp__305;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__306;
  uint16_t* var_name_tmp__307;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__308;
  uint16_t* var_name_tmp__309;
  uint64_t var_name_load_i16_3;

  var_name_tmp__303 = var_name_tmp__301;
  var_name_tmp__304 = var_name_tmp__302;
  var_name_tmp__305 = var_name_tmp__304;
  if ((((var_name_tmp__305 != 0u)&1))) {
    goto var_name_tmp__310;
  } else {
    goto var_name_tmp__311;
  }

var_name_tmp__310:
  var_name_tmp__306 = var_name_tmp__303;
  var_name_tmp__307 = (&var_name_tmp__306->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__307)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__307)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 2048))))), 16, 2);
  goto var_name_tmp__312;

var_name_tmp__311:
  var_name_tmp__308 = var_name_tmp__303;
  var_name_tmp__309 = (&var_name_tmp__308->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__309)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__309)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 63487))))), 16, 2);
  goto var_name_tmp__312;

var_name_tmp__312:
  return;
}


void I2C_DMALastTransferCmd(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__313, uint32_t var_name_tmp__314) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__315;    /* Address-exposed local */
  uint32_t var_name_tmp__316;    /* Address-exposed local */
  uint32_t var_name_tmp__317;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__318;
  uint16_t* var_name_tmp__319;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__320;
  uint16_t* var_name_tmp__321;
  uint64_t var_name_load_i16_3;

  var_name_tmp__315 = var_name_tmp__313;
  var_name_tmp__316 = var_name_tmp__314;
  var_name_tmp__317 = var_name_tmp__316;
  if ((((var_name_tmp__317 != 0u)&1))) {
    goto var_name_tmp__322;
  } else {
    goto var_name_tmp__323;
  }

var_name_tmp__322:
  var_name_tmp__318 = var_name_tmp__315;
  var_name_tmp__319 = (&var_name_tmp__318->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__319)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__319)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4096))))), 16, 2);
  goto var_name_tmp__324;

var_name_tmp__323:
  var_name_tmp__320 = var_name_tmp__315;
  var_name_tmp__321 = (&var_name_tmp__320->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__321)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__321)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 61439))))), 16, 2);
  goto var_name_tmp__324;

var_name_tmp__324:
  return;
}


uint16_t I2C_ReadRegister(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__325, uint8_t var_name_tmp__326) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__327;    /* Address-exposed local */
  uint8_t var_name_tmp__328;    /* Address-exposed local */
  uint32_t var_name_tmp__329;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__330;
  uint8_t var_name_tmp__331;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_6;
  uint64_t var_name_load_i16_;

  var_name_tmp__327 = var_name_tmp__325;
  var_name_tmp__328 = var_name_tmp__326;
  __adin_store_((((uint8_t*)(&var_name_tmp__329))), UINT64_C(0), 32, 4);
  var_name_tmp__330 = var_name_tmp__327;
  __adin_store_((((uint8_t*)(&var_name_tmp__329))), (((uint64_t)(uint32_t)(((uint32_t)(uintptr_t)var_name_tmp__330)))), 32, 4);
  var_name_tmp__331 = var_name_tmp__328;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__329))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__329))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_)), (((uint32_t)(uint8_t)var_name_tmp__331)))))), 32, 4);
  var_name_load_i32_6 = __adin_load_((((uint8_t*)(&var_name_tmp__329))), 32, 4);
  var_name_load_i16_ = __adin_load_((((uint8_t*)(((uint16_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_6)))))))), 16, 2);
  return (((uint16_t)var_name_load_i16_));
}


void I2C_ITConfig(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__332, uint16_t var_name_tmp__333, uint32_t var_name_tmp__334) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__335;    /* Address-exposed local */
  uint16_t var_name_tmp__336;    /* Address-exposed local */
  uint32_t var_name_tmp__337;    /* Address-exposed local */
  uint32_t var_name_tmp__338;
  uint16_t var_name_tmp__339;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__340;
  uint16_t* var_name_tmp__341;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__342;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__343;
  uint16_t* var_name_tmp__344;
  uint64_t var_name_load_i16_3;

  var_name_tmp__335 = var_name_tmp__332;
  var_name_tmp__336 = var_name_tmp__333;
  var_name_tmp__337 = var_name_tmp__334;
  var_name_tmp__338 = var_name_tmp__337;
  if ((((var_name_tmp__338 != 0u)&1))) {
    goto var_name_tmp__345;
  } else {
    goto var_name_tmp__346;
  }

var_name_tmp__345:
  var_name_tmp__339 = var_name_tmp__336;
  var_name_tmp__340 = var_name_tmp__335;
  var_name_tmp__341 = (&var_name_tmp__340->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__341)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__341)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__339))))))), 16, 2);
  goto var_name_tmp__347;

var_name_tmp__346:
  var_name_tmp__342 = var_name_tmp__336;
  var_name_tmp__343 = var_name_tmp__335;
  var_name_tmp__344 = (&var_name_tmp__343->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__344)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__344)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__342))))))))))))), 16, 2);
  goto var_name_tmp__347;

var_name_tmp__347:
  return;
}


uint32_t I2C_CheckEvent(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__348, uint32_t var_name_tmp__349) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__350;    /* Address-exposed local */
  uint32_t var_name_tmp__351;    /* Address-exposed local */
  uint32_t var_name_tmp__352;    /* Address-exposed local */
  uint32_t var_name_tmp__353;    /* Address-exposed local */
  uint32_t var_name_tmp__354;    /* Address-exposed local */
  uint32_t var_name_tmp__355;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__356;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__357;
  uint64_t var_name_load_i16_2;
  uint32_t var_name_tmp__358;
  uint32_t var_name_tmp__359;
  uint32_t var_name_tmp__360;
  uint32_t var_name_tmp__361;
  uint32_t var_name_tmp__362;
  uint32_t var_name_tmp__363;
  uint32_t var_name_tmp__364;

  var_name_tmp__350 = var_name_tmp__348;
  var_name_tmp__351 = var_name_tmp__349;
  var_name_tmp__352 = 0;
  var_name_tmp__353 = 0;
  var_name_tmp__354 = 0;
  var_name_tmp__355 = 0;
  var_name_tmp__356 = var_name_tmp__350;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__356->field10)))), 16, 2);
  var_name_tmp__353 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_))));
  var_name_tmp__357 = var_name_tmp__350;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__357->field12)))), 16, 2);
  var_name_tmp__354 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2))));
  var_name_tmp__358 = var_name_tmp__354;
  var_name_tmp__354 = (var_name_tmp__358 << 16);
  var_name_tmp__359 = var_name_tmp__353;
  var_name_tmp__360 = var_name_tmp__354;
  var_name_tmp__352 = ((var_name_tmp__359 | var_name_tmp__360) & 16777215);
  var_name_tmp__361 = var_name_tmp__352;
  var_name_tmp__362 = var_name_tmp__351;
  var_name_tmp__363 = var_name_tmp__351;
  if (((((var_name_tmp__361 & var_name_tmp__362) == var_name_tmp__363)&1))) {
    goto var_name_tmp__365;
  } else {
    goto var_name_tmp__366;
  }

var_name_tmp__365:
  var_name_tmp__355 = 1;
  goto var_name_tmp__367;

var_name_tmp__366:
  var_name_tmp__355 = 0;
  goto var_name_tmp__367;

var_name_tmp__367:
  var_name_tmp__364 = var_name_tmp__355;
  return var_name_tmp__364;
}


uint32_t I2C_GetLastEvent(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__368) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__369;    /* Address-exposed local */
  uint32_t var_name_tmp__370;    /* Address-exposed local */
  uint32_t var_name_tmp__371;    /* Address-exposed local */
  uint32_t var_name_tmp__372;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__373;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__374;
  uint64_t var_name_load_i16_2;
  uint32_t var_name_tmp__375;
  uint32_t var_name_tmp__376;
  uint32_t var_name_tmp__377;
  uint32_t var_name_tmp__378;

  var_name_tmp__369 = var_name_tmp__368;
  var_name_tmp__370 = 0;
  var_name_tmp__371 = 0;
  var_name_tmp__372 = 0;
  var_name_tmp__373 = var_name_tmp__369;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__373->field10)))), 16, 2);
  var_name_tmp__371 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_))));
  var_name_tmp__374 = var_name_tmp__369;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__374->field12)))), 16, 2);
  var_name_tmp__372 = (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2))));
  var_name_tmp__375 = var_name_tmp__372;
  var_name_tmp__372 = (var_name_tmp__375 << 16);
  var_name_tmp__376 = var_name_tmp__371;
  var_name_tmp__377 = var_name_tmp__372;
  var_name_tmp__370 = ((var_name_tmp__376 | var_name_tmp__377) & 16777215);
  var_name_tmp__378 = var_name_tmp__370;
  return var_name_tmp__378;
}


uint32_t I2C_GetFlagStatus(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__379, uint32_t var_name_tmp__380) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__381;    /* Address-exposed local */
  uint32_t var_name_tmp__382;    /* Address-exposed local */
  uint32_t var_name_tmp__383;    /* Address-exposed local */
  uint32_t var_name_tmp__384;    /* Address-exposed local */
  uint32_t var_name_tmp__385;    /* Address-exposed local */
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__386;
  uint32_t var_name_tmp__387;
  uint32_t var_name_tmp__388;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__389;
  uint64_t var_name_load_i32_12;
  uint64_t var_name_load_i32_17;
  uint64_t var_name_load_i32_20;
  uint32_t var_name_tmp__390;
  uint32_t var_name_tmp__391;

  var_name_tmp__381 = var_name_tmp__379;
  var_name_tmp__382 = var_name_tmp__380;
  var_name_tmp__383 = 0;
  __adin_store_((((uint8_t*)(&var_name_tmp__384))), UINT64_C(0), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__385))), UINT64_C(0), 32, 4);
  var_name_tmp__386 = var_name_tmp__381;
  __adin_store_((((uint8_t*)(&var_name_tmp__385))), (((uint64_t)(uint32_t)(((uint32_t)(uintptr_t)var_name_tmp__386)))), 32, 4);
  var_name_tmp__387 = var_name_tmp__382;
  __adin_store_((((uint8_t*)(&var_name_tmp__384))), (((uint64_t)(uint32_t)(llvm_lshr_u32(var_name_tmp__387, 28)))), 32, 4);
  var_name_tmp__388 = var_name_tmp__382;
  var_name_tmp__382 = (var_name_tmp__388 & 16777215);
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__384))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) != 0u)&1))) {
    goto var_name_tmp__392;
  } else {
    goto var_name_tmp__393;
  }

var_name_tmp__392:
  var_name_load_i32_7 = __adin_load_((((uint8_t*)(&var_name_tmp__385))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__385))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_7)), 20)))), 32, 4);
  goto var_name_tmp__394;

var_name_tmp__393:
  var_name_tmp__389 = var_name_tmp__382;
  var_name_tmp__382 = (llvm_lshr_u32(var_name_tmp__389, 16));
  var_name_load_i32_12 = __adin_load_((((uint8_t*)(&var_name_tmp__385))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__385))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_12)), 24)))), 32, 4);
  goto var_name_tmp__394;

var_name_tmp__394:
  var_name_load_i32_17 = __adin_load_((((uint8_t*)(&var_name_tmp__385))), 32, 4);
  var_name_load_i32_20 = __adin_load_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_17)))))))), 32, 4);
  var_name_tmp__390 = var_name_tmp__382;
  if ((((((((uint32_t)var_name_load_i32_20)) & var_name_tmp__390) != 0u)&1))) {
    goto var_name_tmp__395;
  } else {
    goto var_name_tmp__396;
  }

var_name_tmp__395:
  var_name_tmp__383 = 1;
  goto var_name_tmp__397;

var_name_tmp__396:
  var_name_tmp__383 = 0;
  goto var_name_tmp__397;

var_name_tmp__397:
  var_name_tmp__391 = var_name_tmp__383;
  return var_name_tmp__391;
}


void I2C_ClearFlag(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__398, uint32_t var_name_tmp__399) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__400;    /* Address-exposed local */
  uint32_t var_name_tmp__401;    /* Address-exposed local */
  uint32_t var_name_tmp__402;    /* Address-exposed local */
  uint32_t var_name_tmp__403;
  uint32_t var_name_tmp__404;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__405;

  var_name_tmp__400 = var_name_tmp__398;
  var_name_tmp__401 = var_name_tmp__399;
  var_name_tmp__402 = 0;
  var_name_tmp__403 = var_name_tmp__401;
  var_name_tmp__402 = (var_name_tmp__403 & 16777215);
  var_name_tmp__404 = var_name_tmp__402;
  var_name_tmp__405 = var_name_tmp__400;
  __adin_store_((((uint8_t*)((&var_name_tmp__405->field10)))), (((uint64_t)(uint16_t)(((uint16_t)(~(var_name_tmp__404)))))), 16, 2);
}


uint32_t I2C_GetITStatus(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__406, uint32_t var_name_tmp__407) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__408;    /* Address-exposed local */
  uint32_t var_name_tmp__409;    /* Address-exposed local */
  uint32_t var_name_tmp__410;    /* Address-exposed local */
  uint32_t var_name_tmp__411;    /* Address-exposed local */
  uint32_t var_name_tmp__412;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__413;
  uint64_t var_name_load_i16_;
  uint32_t var_name_tmp__414;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__415;
  uint64_t var_name_load_i16_2;
  uint32_t var_name_tmp__416;
  uint32_t var_name_tmp__417;
  uint32_t var_name_tmp__418;

  var_name_tmp__408 = var_name_tmp__406;
  var_name_tmp__409 = var_name_tmp__407;
  var_name_tmp__410 = 0;
  var_name_tmp__411 = 0;
  var_name_tmp__412 = var_name_tmp__409;
  var_name_tmp__413 = var_name_tmp__408;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__413->field2)))), 16, 2);
  var_name_tmp__411 = ((llvm_lshr_u32((var_name_tmp__412 & 117440512), 16)) & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))));
  var_name_tmp__414 = var_name_tmp__409;
  var_name_tmp__409 = (var_name_tmp__414 & 16777215);
  var_name_tmp__415 = var_name_tmp__408;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__415->field10)))), 16, 2);
  var_name_tmp__416 = var_name_tmp__409;
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) & var_name_tmp__416) != 0u)&1))) {
    goto var_name_tmp__419;
  } else {
    goto var_name_tmp__420;
  }

var_name_tmp__419:
  var_name_tmp__417 = var_name_tmp__411;
  if ((((var_name_tmp__417 != 0u)&1))) {
    goto var_name_tmp__421;
  } else {
    goto var_name_tmp__420;
  }

var_name_tmp__421:
  var_name_tmp__410 = 1;
  goto var_name_tmp__422;

var_name_tmp__420:
  var_name_tmp__410 = 0;
  goto var_name_tmp__422;

var_name_tmp__422:
  var_name_tmp__418 = var_name_tmp__410;
  return var_name_tmp__418;
}


void I2C_ClearITPendingBit(struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__423, uint32_t var_name_tmp__424) {
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__425;    /* Address-exposed local */
  uint32_t var_name_tmp__426;    /* Address-exposed local */
  uint32_t var_name_tmp__427;    /* Address-exposed local */
  uint32_t var_name_tmp__428;
  uint32_t var_name_tmp__429;
  struct l_struct_struct_OC_I2C_TypeDef* var_name_tmp__430;

  var_name_tmp__425 = var_name_tmp__423;
  var_name_tmp__426 = var_name_tmp__424;
  var_name_tmp__427 = 0;
  var_name_tmp__428 = var_name_tmp__426;
  var_name_tmp__427 = (var_name_tmp__428 & 16777215);
  var_name_tmp__429 = var_name_tmp__427;
  var_name_tmp__430 = var_name_tmp__425;
  __adin_store_((((uint8_t*)((&var_name_tmp__430->field10)))), (((uint64_t)(uint16_t)(((uint16_t)(~(var_name_tmp__429)))))), 16, 2);
}

