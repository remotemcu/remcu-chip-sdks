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
struct l_struct_struct_OC_SPI_TypeDef;
struct l_struct_struct_OC_SPI_InitTypeDef;
struct l_struct_struct_OC_I2S_InitTypeDef;
struct l_struct_struct_OC_RCC_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_SPI_TypeDef {
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
struct l_struct_struct_OC_SPI_InitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint16_t field5;
  uint16_t field6;
  uint16_t field7;
  uint16_t field8;
};
struct l_struct_struct_OC_I2S_InitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint32_t field4;
  uint16_t field5;
};
struct l_array_2_uint32_t {
  uint32_t array[2];
};
struct l_struct_struct_OC_RCC_TypeDef {
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
  struct l_array_2_uint32_t field10;
  uint32_t field11;
  uint32_t field12;
  uint32_t field13;
  uint32_t field14;
  uint32_t field15;
  uint32_t field16;
  struct l_array_2_uint32_t field17;
  uint32_t field18;
  uint32_t field19;
  uint32_t field20;
  uint32_t field21;
  uint32_t field22;
  uint32_t field23;
  struct l_array_2_uint32_t field24;
  uint32_t field25;
  uint32_t field26;
  struct l_array_2_uint32_t field27;
  uint32_t field28;
  uint32_t field29;
};

/* Function Declarations */
void SPI_I2S_DeInit(struct l_struct_struct_OC_SPI_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB2PeriphResetCmd(uint32_t, uint32_t);
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
void SPI_Init(struct l_struct_struct_OC_SPI_TypeDef*, struct l_struct_struct_OC_SPI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void I2S_Init(struct l_struct_struct_OC_SPI_TypeDef*, struct l_struct_struct_OC_I2S_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_StructInit(struct l_struct_struct_OC_SPI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void I2S_StructInit(struct l_struct_struct_OC_I2S_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_Cmd(struct l_struct_struct_OC_SPI_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2S_Cmd(struct l_struct_struct_OC_SPI_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_DataSizeConfig(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_BiDirectionalLineConfig(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_NSSInternalSoftwareConfig(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_SSOutputCmd(struct l_struct_struct_OC_SPI_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_TIModeCmd(struct l_struct_struct_OC_SPI_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void I2S_FullDuplexConfig(struct l_struct_struct_OC_SPI_TypeDef*, struct l_struct_struct_OC_I2S_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t SPI_I2S_ReceiveData(struct l_struct_struct_OC_SPI_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_I2S_SendData(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_CalculateCRC(struct l_struct_struct_OC_SPI_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_TransmitCRC(struct l_struct_struct_OC_SPI_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t SPI_GetCRC(struct l_struct_struct_OC_SPI_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t SPI_GetCRCPolynomial(struct l_struct_struct_OC_SPI_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_I2S_DMACmd(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_I2S_ITConfig(struct l_struct_struct_OC_SPI_TypeDef*, uint8_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SPI_I2S_GetFlagStatus(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_I2S_ClearFlag(struct l_struct_struct_OC_SPI_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t SPI_I2S_GetITStatus(struct l_struct_struct_OC_SPI_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void SPI_I2S_ClearITPendingBit(struct l_struct_struct_OC_SPI_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
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

void SPI_I2S_DeInit(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__3;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__4;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__5;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_SPI_TypeDef*)(uintptr_t)UINT64_C(1073819648)))&1))) {
    goto var_name_tmp__6;
  } else {
    goto var_name_tmp__7;
  }

var_name_tmp__6:
  RCC_APB2PeriphResetCmd(4096, 1);
  RCC_APB2PeriphResetCmd(4096, 0);
  goto var_name_tmp__8;

var_name_tmp__7:
  var_name_tmp__4 = var_name_tmp__2;
  if ((((var_name_tmp__4 == ((struct l_struct_struct_OC_SPI_TypeDef*)(uintptr_t)UINT64_C(1073756160)))&1))) {
    goto var_name_tmp__9;
  } else {
    goto var_name_tmp__10;
  }

var_name_tmp__9:
  RCC_APB1PeriphResetCmd(16384, 1);
  RCC_APB1PeriphResetCmd(16384, 0);
  goto var_name_tmp__11;

var_name_tmp__10:
  var_name_tmp__5 = var_name_tmp__2;
  if ((((var_name_tmp__5 == ((struct l_struct_struct_OC_SPI_TypeDef*)(uintptr_t)UINT64_C(1073757184)))&1))) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__12:
  RCC_APB1PeriphResetCmd(32768, 1);
  RCC_APB1PeriphResetCmd(32768, 0);
  goto var_name_tmp__13;

var_name_tmp__13:
  goto var_name_tmp__11;

var_name_tmp__11:
  goto var_name_tmp__8;

var_name_tmp__8:
  return;
}


void SPI_Init(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__14, struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__15) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__16;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__17;    /* Address-exposed local */
  uint16_t var_name_tmp__18;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__19;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__20;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__21;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__22;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__23;
  uint64_t var_name_load_i16_8;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__24;
  uint64_t var_name_load_i16_11;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__25;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__26;
  uint64_t var_name_load_i16_17;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__27;
  uint64_t var_name_load_i16_20;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__28;
  uint64_t var_name_load_i16_23;
  uint16_t var_name_tmp__29;
  uint16_t var_name_tmp__30;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__31;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__32;
  uint16_t* var_name_tmp__33;
  uint64_t var_name_load_i16_27;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__34;
  uint64_t var_name_load_i16_32;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__35;

  var_name_tmp__16 = var_name_tmp__14;
  var_name_tmp__17 = var_name_tmp__15;
  var_name_tmp__18 = 0;
  var_name_tmp__19 = var_name_tmp__16;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__19->field0)))), 16, 2);
  var_name_tmp__18 = (((uint16_t)var_name_load_i16_));
  var_name_tmp__20 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__20)) & 12352)));
  var_name_tmp__21 = var_name_tmp__17;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__21->field0)))), 16, 2);
  var_name_tmp__22 = var_name_tmp__17;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__22->field1)))), 16, 2);
  var_name_tmp__23 = var_name_tmp__17;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__23->field2)))), 16, 2);
  var_name_tmp__24 = var_name_tmp__17;
  var_name_load_i16_11 = __adin_load_((((uint8_t*)((&var_name_tmp__24->field3)))), 16, 2);
  var_name_tmp__25 = var_name_tmp__17;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&var_name_tmp__25->field4)))), 16, 2);
  var_name_tmp__26 = var_name_tmp__17;
  var_name_load_i16_17 = __adin_load_((((uint8_t*)((&var_name_tmp__26->field5)))), 16, 2);
  var_name_tmp__27 = var_name_tmp__17;
  var_name_load_i16_20 = __adin_load_((((uint8_t*)((&var_name_tmp__27->field6)))), 16, 2);
  var_name_tmp__28 = var_name_tmp__17;
  var_name_load_i16_23 = __adin_load_((((uint8_t*)((&var_name_tmp__28->field7)))), 16, 2);
  var_name_tmp__29 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__29)) | (((uint32_t)(uint16_t)(((uint16_t)((((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_11))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_14))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_17))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_20))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_23))))))))))));
  var_name_tmp__30 = var_name_tmp__18;
  var_name_tmp__31 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__31->field0)))), (((uint64_t)(uint16_t)var_name_tmp__30)), 16, 2);
  var_name_tmp__32 = var_name_tmp__16;
  var_name_tmp__33 = (&var_name_tmp__32->field14);
  var_name_load_i16_27 = __adin_load_((((uint8_t*)var_name_tmp__33)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__33)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_27)))) & 63487))))), 16, 2);
  var_name_tmp__34 = var_name_tmp__17;
  var_name_load_i16_32 = __adin_load_((((uint8_t*)((&var_name_tmp__34->field8)))), 16, 2);
  var_name_tmp__35 = var_name_tmp__16;
  __adin_store_((((uint8_t*)((&var_name_tmp__35->field8)))), (((uint64_t)(uint16_t)(((uint16_t)var_name_load_i16_32)))), 16, 2);
}


void I2S_Init(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__36, struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__37) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__38;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__39;    /* Address-exposed local */
  uint16_t var_name_tmp__40;    /* Address-exposed local */
  uint16_t var_name_tmp__41;    /* Address-exposed local */
  uint16_t var_name_tmp__42;    /* Address-exposed local */
  uint16_t var_name_tmp__43;    /* Address-exposed local */
  uint32_t var_name_tmp__44;    /* Address-exposed local */
  uint32_t var_name_tmp__45;    /* Address-exposed local */
  uint32_t var_name_tmp__46;    /* Address-exposed local */
  uint32_t var_name_tmp__47;    /* Address-exposed local */
  uint32_t var_name_tmp__48;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__49;
  uint16_t* var_name_tmp__50;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__51;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__52;
  uint64_t var_name_load_i16_4;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__53;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__54;
  uint64_t var_name_load_i16_7;
  uint64_t var_name_load_i32_9;
  uint64_t var_name_load_i32_11;
  uint64_t var_name_load_i32_13;
  uint64_t var_name_load_i32_15;
  uint64_t var_name_load_i32_17;
  uint32_t var_name_tmp__55;
  uint32_t var_name_tmp__56;
  uint32_t var_name_tmp__57;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__58;
  uint64_t var_name_load_i16_20;
  uint32_t var_name_tmp__59;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__60;
  uint64_t var_name_load_i32_23;
  uint32_t var_name_tmp__61;
  uint16_t var_name_tmp__62;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__63;
  uint64_t var_name_load_i32_26;
  uint32_t var_name_tmp__64;
  uint32_t var_name_tmp__65;
  uint32_t var_name_tmp__66;
  uint16_t var_name_tmp__67;
  uint16_t var_name_tmp__68;
  uint16_t var_name_tmp__69;
  uint16_t var_name_tmp__70;
  uint16_t var_name_tmp__71;
  uint16_t var_name_tmp__72;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__73;
  uint64_t var_name_load_i16_29;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__74;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__75;
  uint64_t var_name_load_i16_34;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__76;
  uint64_t var_name_load_i16_37;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__77;
  uint64_t var_name_load_i16_40;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__78;
  uint64_t var_name_load_i16_43;
  uint16_t var_name_tmp__79;
  uint16_t var_name_tmp__80;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__81;

  var_name_tmp__38 = var_name_tmp__36;
  var_name_tmp__39 = var_name_tmp__37;
  var_name_tmp__40 = 0;
  var_name_tmp__41 = 2;
  var_name_tmp__42 = 0;
  var_name_tmp__43 = 1;
  var_name_tmp__44 = 0;
  var_name_tmp__45 = 0;
  var_name_tmp__46 = 0;
  var_name_tmp__47 = 0;
  var_name_tmp__48 = 0;
  var_name_tmp__49 = var_name_tmp__38;
  var_name_tmp__50 = (&var_name_tmp__49->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__50)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__50)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 61504))))), 16, 2);
  var_name_tmp__51 = var_name_tmp__38;
  __adin_store_((((uint8_t*)((&var_name_tmp__51->field16)))), UINT64_C(2), 16, 2);
  var_name_tmp__52 = var_name_tmp__38;
  var_name_load_i16_4 = __adin_load_((((uint8_t*)((&var_name_tmp__52->field14)))), 16, 2);
  var_name_tmp__40 = (((uint16_t)var_name_load_i16_4));
  var_name_tmp__53 = var_name_tmp__39;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__53->field4)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) == 2u)&1))) {
    goto var_name_tmp__82;
  } else {
    goto var_name_tmp__83;
  }

var_name_tmp__82:
  var_name_tmp__42 = 0;
  var_name_tmp__41 = 2;
  goto var_name_tmp__84;

var_name_tmp__83:
  var_name_tmp__54 = var_name_tmp__39;
  var_name_load_i16_7 = __adin_load_((((uint8_t*)((&var_name_tmp__54->field2)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_7)))) == 0u)&1))) {
    goto var_name_tmp__85;
  } else {
    goto var_name_tmp__86;
  }

var_name_tmp__85:
  var_name_tmp__43 = 1;
  goto var_name_tmp__87;

var_name_tmp__86:
  var_name_tmp__43 = 2;
  goto var_name_tmp__87;

var_name_tmp__87:
  var_name_load_i32_9 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_9)) & 8388608) != 0u)&1))) {
    goto var_name_tmp__88;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__88:
  var_name_load_i32_11 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_11)) & -8388609))), 32, 4);
  goto var_name_tmp__89;

var_name_tmp__89:
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29))), 32, 4);
  var_name_tmp__47 = ((llvm_lshr_u32(((((uint32_t)var_name_load_i32_13)) & 32704), 6)) & 511);
  var_name_load_i32_15 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29))), 32, 4);
  var_name_tmp__48 = ((llvm_lshr_u32(((((uint32_t)var_name_load_i32_15)) & 1879048192u), 28)) & 7);
  var_name_load_i32_17 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1))), 32, 4);
  var_name_tmp__46 = ((((uint32_t)var_name_load_i32_17)) & 63);
  var_name_tmp__55 = var_name_tmp__46;
  var_name_tmp__56 = var_name_tmp__47;
  var_name_tmp__57 = var_name_tmp__48;
  var_name_tmp__45 = (llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__55)), var_name_tmp__56)), var_name_tmp__57));
  var_name_tmp__58 = var_name_tmp__39;
  var_name_load_i16_20 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field3)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_20)))) == 512u)&1))) {
    goto var_name_tmp__90;
  } else {
    goto var_name_tmp__91;
  }

var_name_tmp__90:
  var_name_tmp__59 = var_name_tmp__45;
  var_name_tmp__60 = var_name_tmp__39;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&var_name_tmp__60->field4)))), 32, 4);
  var_name_tmp__44 = (((uint32_t)(uint16_t)(((uint16_t)(llvm_add_u32((llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(var_name_tmp__59, 256)), 10)), (((uint32_t)var_name_load_i32_23)))), 5))))));
  goto var_name_tmp__92;

var_name_tmp__91:
  var_name_tmp__61 = var_name_tmp__45;
  var_name_tmp__62 = var_name_tmp__43;
  var_name_tmp__63 = var_name_tmp__39;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__63->field4)))), 32, 4);
  var_name_tmp__44 = (((uint32_t)(uint16_t)(((uint16_t)(llvm_add_u32((llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(var_name_tmp__61, (llvm_mul_u32(32, (((uint32_t)(uint16_t)var_name_tmp__62)))))), 10)), (((uint32_t)var_name_load_i32_26)))), 5))))));
  goto var_name_tmp__92;

var_name_tmp__92:
  var_name_tmp__64 = var_name_tmp__44;
  var_name_tmp__44 = (llvm_udiv_u32(var_name_tmp__64, 10));
  var_name_tmp__65 = var_name_tmp__44;
  var_name_tmp__42 = (((uint16_t)(var_name_tmp__65 & 1)));
  var_name_tmp__66 = var_name_tmp__44;
  var_name_tmp__67 = var_name_tmp__42;
  var_name_tmp__41 = (((uint16_t)(llvm_udiv_u32((llvm_sub_u32(var_name_tmp__66, (((uint32_t)(uint16_t)var_name_tmp__67)))), 2))));
  var_name_tmp__68 = var_name_tmp__42;
  var_name_tmp__42 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__68)) << 8)));
  goto var_name_tmp__84;

var_name_tmp__84:
  var_name_tmp__69 = var_name_tmp__41;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__69))) < ((int32_t)2u))&1))) {
    goto var_name_tmp__93;
  } else {
    goto var_name_tmp__94;
  }

var_name_tmp__94:
  var_name_tmp__70 = var_name_tmp__41;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__70))) > ((int32_t)255u))&1))) {
    goto var_name_tmp__93;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__93:
  var_name_tmp__41 = 2;
  var_name_tmp__42 = 0;
  goto var_name_tmp__95;

var_name_tmp__95:
  var_name_tmp__71 = var_name_tmp__41;
  var_name_tmp__72 = var_name_tmp__42;
  var_name_tmp__73 = var_name_tmp__39;
  var_name_load_i16_29 = __adin_load_((((uint8_t*)((&var_name_tmp__73->field3)))), 16, 2);
  var_name_tmp__74 = var_name_tmp__38;
  __adin_store_((((uint8_t*)((&var_name_tmp__74->field16)))), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__71)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__72)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_29)))))))))))))), 16, 2);
  var_name_tmp__75 = var_name_tmp__39;
  var_name_load_i16_34 = __adin_load_((((uint8_t*)((&var_name_tmp__75->field0)))), 16, 4);
  var_name_tmp__76 = var_name_tmp__39;
  var_name_load_i16_37 = __adin_load_((((uint8_t*)((&var_name_tmp__76->field1)))), 16, 2);
  var_name_tmp__77 = var_name_tmp__39;
  var_name_load_i16_40 = __adin_load_((((uint8_t*)((&var_name_tmp__77->field2)))), 16, 4);
  var_name_tmp__78 = var_name_tmp__39;
  var_name_load_i16_43 = __adin_load_((((uint8_t*)((&var_name_tmp__78->field5)))), 16, 4);
  var_name_tmp__79 = var_name_tmp__40;
  var_name_tmp__40 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__79)) | (((uint32_t)(uint16_t)(((uint16_t)(2048 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_34)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_37)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_40)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_43)))))))))))))))))))))))))));
  var_name_tmp__80 = var_name_tmp__40;
  var_name_tmp__81 = var_name_tmp__38;
  __adin_store_((((uint8_t*)((&var_name_tmp__81->field14)))), (((uint64_t)(uint16_t)var_name_tmp__80)), 16, 2);
}


void SPI_StructInit(struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__96) {
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__97;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__98;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__99;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__100;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__101;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__102;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__103;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__104;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__105;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__106;

  var_name_tmp__97 = var_name_tmp__96;
  var_name_tmp__98 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__98->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__99 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__99->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__100 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__100->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__101 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__101->field3)))), UINT64_C(0), 16, 2);
  var_name_tmp__102 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__102->field4)))), UINT64_C(0), 16, 2);
  var_name_tmp__103 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__103->field5)))), UINT64_C(0), 16, 2);
  var_name_tmp__104 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__104->field6)))), UINT64_C(0), 16, 2);
  var_name_tmp__105 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__105->field7)))), UINT64_C(0), 16, 2);
  var_name_tmp__106 = var_name_tmp__97;
  __adin_store_((((uint8_t*)((&var_name_tmp__106->field8)))), UINT64_C(7), 16, 2);
}


void I2S_StructInit(struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__107) {
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__108;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__109;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__112;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__113;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__114;

  var_name_tmp__108 = var_name_tmp__107;
  var_name_tmp__109 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__109->field0)))), UINT64_C(0), 16, 4);
  var_name_tmp__110 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__110->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__111 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__111->field2)))), UINT64_C(0), 16, 4);
  var_name_tmp__112 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__112->field3)))), UINT64_C(0), 16, 2);
  var_name_tmp__113 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__113->field4)))), UINT64_C(2), 32, 4);
  var_name_tmp__114 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__114->field5)))), UINT64_C(0), 16, 4);
}


void SPI_Cmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__115, uint32_t var_name_tmp__116) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__117;    /* Address-exposed local */
  uint32_t var_name_tmp__118;    /* Address-exposed local */
  uint32_t var_name_tmp__119;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__120;
  uint16_t* var_name_tmp__121;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__122;
  uint16_t* var_name_tmp__123;
  uint64_t var_name_load_i16_3;

  var_name_tmp__117 = var_name_tmp__115;
  var_name_tmp__118 = var_name_tmp__116;
  var_name_tmp__119 = var_name_tmp__118;
  if ((((var_name_tmp__119 != 0u)&1))) {
    goto var_name_tmp__124;
  } else {
    goto var_name_tmp__125;
  }

var_name_tmp__124:
  var_name_tmp__120 = var_name_tmp__117;
  var_name_tmp__121 = (&var_name_tmp__120->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__121)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__121)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 64))))), 16, 2);
  goto var_name_tmp__126;

var_name_tmp__125:
  var_name_tmp__122 = var_name_tmp__117;
  var_name_tmp__123 = (&var_name_tmp__122->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__123)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__123)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65471))))), 16, 2);
  goto var_name_tmp__126;

var_name_tmp__126:
  return;
}


void I2S_Cmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__127, uint32_t var_name_tmp__128) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__129;    /* Address-exposed local */
  uint32_t var_name_tmp__130;    /* Address-exposed local */
  uint32_t var_name_tmp__131;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__132;
  uint16_t* var_name_tmp__133;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__134;
  uint16_t* var_name_tmp__135;
  uint64_t var_name_load_i16_3;

  var_name_tmp__129 = var_name_tmp__127;
  var_name_tmp__130 = var_name_tmp__128;
  var_name_tmp__131 = var_name_tmp__130;
  if ((((var_name_tmp__131 != 0u)&1))) {
    goto var_name_tmp__136;
  } else {
    goto var_name_tmp__137;
  }

var_name_tmp__136:
  var_name_tmp__132 = var_name_tmp__129;
  var_name_tmp__133 = (&var_name_tmp__132->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__133)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__133)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 1024))))), 16, 2);
  goto var_name_tmp__138;

var_name_tmp__137:
  var_name_tmp__134 = var_name_tmp__129;
  var_name_tmp__135 = (&var_name_tmp__134->field14);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__135)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__135)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 64511))))), 16, 2);
  goto var_name_tmp__138;

var_name_tmp__138:
  return;
}


void SPI_DataSizeConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__139, uint16_t var_name_tmp__140) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__141;    /* Address-exposed local */
  uint16_t var_name_tmp__142;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__143;
  uint16_t* var_name_tmp__144;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__145;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__146;
  uint16_t* var_name_tmp__147;
  uint64_t var_name_load_i16_3;

  var_name_tmp__141 = var_name_tmp__139;
  var_name_tmp__142 = var_name_tmp__140;
  var_name_tmp__143 = var_name_tmp__141;
  var_name_tmp__144 = (&var_name_tmp__143->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__144)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__144)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 63487))))), 16, 2);
  var_name_tmp__145 = var_name_tmp__142;
  var_name_tmp__146 = var_name_tmp__141;
  var_name_tmp__147 = (&var_name_tmp__146->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__147)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__147)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) | (((uint32_t)(uint16_t)var_name_tmp__145))))))), 16, 2);
}


void SPI_BiDirectionalLineConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__148, uint16_t var_name_tmp__149) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__150;    /* Address-exposed local */
  uint16_t var_name_tmp__151;    /* Address-exposed local */
  uint16_t var_name_tmp__152;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__153;
  uint16_t* var_name_tmp__154;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__155;
  uint16_t* var_name_tmp__156;
  uint64_t var_name_load_i16_3;

  var_name_tmp__150 = var_name_tmp__148;
  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__152 = var_name_tmp__151;
  if (((((((uint32_t)(uint16_t)var_name_tmp__152)) == 16384u)&1))) {
    goto var_name_tmp__157;
  } else {
    goto var_name_tmp__158;
  }

var_name_tmp__157:
  var_name_tmp__153 = var_name_tmp__150;
  var_name_tmp__154 = (&var_name_tmp__153->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__154)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__154)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16384))))), 16, 2);
  goto var_name_tmp__159;

var_name_tmp__158:
  var_name_tmp__155 = var_name_tmp__150;
  var_name_tmp__156 = (&var_name_tmp__155->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__156)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__156)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 49151))))), 16, 2);
  goto var_name_tmp__159;

var_name_tmp__159:
  return;
}


void SPI_NSSInternalSoftwareConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__160, uint16_t var_name_tmp__161) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__162;    /* Address-exposed local */
  uint16_t var_name_tmp__163;    /* Address-exposed local */
  uint16_t var_name_tmp__164;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__165;
  uint16_t* var_name_tmp__166;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__167;
  uint16_t* var_name_tmp__168;
  uint64_t var_name_load_i16_3;

  var_name_tmp__162 = var_name_tmp__160;
  var_name_tmp__163 = var_name_tmp__161;
  var_name_tmp__164 = var_name_tmp__163;
  if (((((((uint32_t)(uint16_t)var_name_tmp__164)) != 65279u)&1))) {
    goto var_name_tmp__169;
  } else {
    goto var_name_tmp__170;
  }

var_name_tmp__169:
  var_name_tmp__165 = var_name_tmp__162;
  var_name_tmp__166 = (&var_name_tmp__165->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__166)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__166)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 256))))), 16, 2);
  goto var_name_tmp__171;

var_name_tmp__170:
  var_name_tmp__167 = var_name_tmp__162;
  var_name_tmp__168 = (&var_name_tmp__167->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__168)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__168)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65279))))), 16, 2);
  goto var_name_tmp__171;

var_name_tmp__171:
  return;
}


void SPI_SSOutputCmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__172, uint32_t var_name_tmp__173) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__174;    /* Address-exposed local */
  uint32_t var_name_tmp__175;    /* Address-exposed local */
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__177;
  uint16_t* var_name_tmp__178;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__179;
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
  var_name_tmp__178 = (&var_name_tmp__177->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__178)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__178)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4))))), 16, 2);
  goto var_name_tmp__183;

var_name_tmp__182:
  var_name_tmp__179 = var_name_tmp__174;
  var_name_tmp__180 = (&var_name_tmp__179->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__180)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__180)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65531))))), 16, 2);
  goto var_name_tmp__183;

var_name_tmp__183:
  return;
}


void SPI_TIModeCmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__184, uint32_t var_name_tmp__185) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__186;    /* Address-exposed local */
  uint32_t var_name_tmp__187;    /* Address-exposed local */
  uint32_t var_name_tmp__188;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__189;
  uint16_t* var_name_tmp__190;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__191;
  uint16_t* var_name_tmp__192;
  uint64_t var_name_load_i16_3;

  var_name_tmp__186 = var_name_tmp__184;
  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__187;
  if ((((var_name_tmp__188 != 0u)&1))) {
    goto var_name_tmp__193;
  } else {
    goto var_name_tmp__194;
  }

var_name_tmp__193:
  var_name_tmp__189 = var_name_tmp__186;
  var_name_tmp__190 = (&var_name_tmp__189->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__190)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__190)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 16))))), 16, 2);
  goto var_name_tmp__195;

var_name_tmp__194:
  var_name_tmp__191 = var_name_tmp__186;
  var_name_tmp__192 = (&var_name_tmp__191->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__192)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__192)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 65519))))), 16, 2);
  goto var_name_tmp__195;

var_name_tmp__195:
  return;
}


void I2S_FullDuplexConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__196, struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__197) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__198;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__199;    /* Address-exposed local */
  uint16_t var_name_tmp__200;    /* Address-exposed local */
  uint16_t var_name_tmp__201;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__202;
  uint16_t* var_name_tmp__203;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__204;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__205;
  uint64_t var_name_load_i16_4;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__206;
  uint64_t var_name_load_i16_7;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__207;
  uint64_t var_name_load_i16_10;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__208;
  uint64_t var_name_load_i16_13;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__209;
  uint64_t var_name_load_i16_16;
  uint16_t var_name_tmp__210;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__211;
  uint64_t var_name_load_i16_19;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__212;
  uint64_t var_name_load_i16_22;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__213;
  uint64_t var_name_load_i16_25;
  uint16_t var_name_tmp__214;
  uint16_t var_name_tmp__215;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__216;

  var_name_tmp__198 = var_name_tmp__196;
  var_name_tmp__199 = var_name_tmp__197;
  var_name_tmp__200 = 0;
  var_name_tmp__201 = 0;
  var_name_tmp__202 = var_name_tmp__198;
  var_name_tmp__203 = (&var_name_tmp__202->field14);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__203)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__203)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & 61504))))), 16, 2);
  var_name_tmp__204 = var_name_tmp__198;
  __adin_store_((((uint8_t*)((&var_name_tmp__204->field16)))), UINT64_C(2), 16, 2);
  var_name_tmp__205 = var_name_tmp__198;
  var_name_load_i16_4 = __adin_load_((((uint8_t*)((&var_name_tmp__205->field14)))), 16, 2);
  var_name_tmp__200 = (((uint16_t)var_name_load_i16_4));
  var_name_tmp__206 = var_name_tmp__199;
  var_name_load_i16_7 = __adin_load_((((uint8_t*)((&var_name_tmp__206->field0)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_7)))) == 512u)&1))) {
    goto var_name_tmp__217;
  } else {
    goto var_name_tmp__218;
  }

var_name_tmp__218:
  var_name_tmp__207 = var_name_tmp__199;
  var_name_load_i16_10 = __adin_load_((((uint8_t*)((&var_name_tmp__207->field0)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_10)))) == 0u)&1))) {
    goto var_name_tmp__217;
  } else {
    goto var_name_tmp__219;
  }

var_name_tmp__217:
  var_name_tmp__201 = 256;
  goto var_name_tmp__220;

var_name_tmp__219:
  var_name_tmp__208 = var_name_tmp__199;
  var_name_load_i16_13 = __adin_load_((((uint8_t*)((&var_name_tmp__208->field0)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_13)))) == 768u)&1))) {
    goto var_name_tmp__221;
  } else {
    goto var_name_tmp__222;
  }

var_name_tmp__222:
  var_name_tmp__209 = var_name_tmp__199;
  var_name_load_i16_16 = __adin_load_((((uint8_t*)((&var_name_tmp__209->field0)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_16)))) == 256u)&1))) {
    goto var_name_tmp__221;
  } else {
    goto var_name_tmp__223;
  }

var_name_tmp__221:
  var_name_tmp__201 = 0;
  goto var_name_tmp__223;

var_name_tmp__223:
  goto var_name_tmp__220;

var_name_tmp__220:
  var_name_tmp__210 = var_name_tmp__201;
  var_name_tmp__211 = var_name_tmp__199;
  var_name_load_i16_19 = __adin_load_((((uint8_t*)((&var_name_tmp__211->field1)))), 16, 2);
  var_name_tmp__212 = var_name_tmp__199;
  var_name_load_i16_22 = __adin_load_((((uint8_t*)((&var_name_tmp__212->field2)))), 16, 4);
  var_name_tmp__213 = var_name_tmp__199;
  var_name_load_i16_25 = __adin_load_((((uint8_t*)((&var_name_tmp__213->field5)))), 16, 4);
  var_name_tmp__214 = var_name_tmp__200;
  var_name_tmp__200 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__214)) | (((uint32_t)(uint16_t)(((uint16_t)(2048 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__210)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_19)))) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_22)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_25)))))))))))))))))))))))))));
  var_name_tmp__215 = var_name_tmp__200;
  var_name_tmp__216 = var_name_tmp__198;
  __adin_store_((((uint8_t*)((&var_name_tmp__216->field14)))), (((uint64_t)(uint16_t)var_name_tmp__215)), 16, 2);
}


uint16_t SPI_I2S_ReceiveData(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__224) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__225;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__226;
  uint64_t var_name_load_i16_;

  var_name_tmp__225 = var_name_tmp__224;
  var_name_tmp__226 = var_name_tmp__225;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__226->field6)))), 16, 2);
  return (((uint16_t)var_name_load_i16_));
}


void SPI_I2S_SendData(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__227, uint16_t var_name_tmp__228) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__229;    /* Address-exposed local */
  uint16_t var_name_tmp__230;    /* Address-exposed local */
  uint16_t var_name_tmp__231;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__232;

  var_name_tmp__229 = var_name_tmp__227;
  var_name_tmp__230 = var_name_tmp__228;
  var_name_tmp__231 = var_name_tmp__230;
  var_name_tmp__232 = var_name_tmp__229;
  __adin_store_((((uint8_t*)((&var_name_tmp__232->field6)))), (((uint64_t)(uint16_t)var_name_tmp__231)), 16, 2);
}


void SPI_CalculateCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__233, uint32_t var_name_tmp__234) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__235;    /* Address-exposed local */
  uint32_t var_name_tmp__236;    /* Address-exposed local */
  uint32_t var_name_tmp__237;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__238;
  uint16_t* var_name_tmp__239;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__240;
  uint16_t* var_name_tmp__241;
  uint64_t var_name_load_i16_3;

  var_name_tmp__235 = var_name_tmp__233;
  var_name_tmp__236 = var_name_tmp__234;
  var_name_tmp__237 = var_name_tmp__236;
  if ((((var_name_tmp__237 != 0u)&1))) {
    goto var_name_tmp__242;
  } else {
    goto var_name_tmp__243;
  }

var_name_tmp__242:
  var_name_tmp__238 = var_name_tmp__235;
  var_name_tmp__239 = (&var_name_tmp__238->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__239)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__239)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 8192))))), 16, 2);
  goto var_name_tmp__244;

var_name_tmp__243:
  var_name_tmp__240 = var_name_tmp__235;
  var_name_tmp__241 = (&var_name_tmp__240->field0);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__241)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__241)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & 57343))))), 16, 2);
  goto var_name_tmp__244;

var_name_tmp__244:
  return;
}


void SPI_TransmitCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__245) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__246;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__247;
  uint16_t* var_name_tmp__248;
  uint64_t var_name_load_i16_;

  var_name_tmp__246 = var_name_tmp__245;
  var_name_tmp__247 = var_name_tmp__246;
  var_name_tmp__248 = (&var_name_tmp__247->field0);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__248)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__248)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | 4096))))), 16, 2);
}


uint16_t SPI_GetCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__249, uint8_t var_name_tmp__250) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__251;    /* Address-exposed local */
  uint8_t var_name_tmp__252;    /* Address-exposed local */
  uint16_t var_name_tmp__253;    /* Address-exposed local */
  uint8_t var_name_tmp__254;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__255;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__256;
  uint64_t var_name_load_i16_2;
  uint16_t var_name_tmp__257;

  var_name_tmp__251 = var_name_tmp__249;
  var_name_tmp__252 = var_name_tmp__250;
  var_name_tmp__253 = 0;
  var_name_tmp__254 = var_name_tmp__252;
  if (((((((uint32_t)(uint8_t)var_name_tmp__254)) != 1u)&1))) {
    goto var_name_tmp__258;
  } else {
    goto var_name_tmp__259;
  }

var_name_tmp__258:
  var_name_tmp__255 = var_name_tmp__251;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__255->field12)))), 16, 2);
  var_name_tmp__253 = (((uint16_t)var_name_load_i16_));
  goto var_name_tmp__260;

var_name_tmp__259:
  var_name_tmp__256 = var_name_tmp__251;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__256->field10)))), 16, 2);
  var_name_tmp__253 = (((uint16_t)var_name_load_i16_2));
  goto var_name_tmp__260;

var_name_tmp__260:
  var_name_tmp__257 = var_name_tmp__253;
  return var_name_tmp__257;
}


uint16_t SPI_GetCRCPolynomial(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__261) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__262;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__263;
  uint64_t var_name_load_i16_;

  var_name_tmp__262 = var_name_tmp__261;
  var_name_tmp__263 = var_name_tmp__262;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__263->field8)))), 16, 2);
  return (((uint16_t)var_name_load_i16_));
}


void SPI_I2S_DMACmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__264, uint16_t var_name_tmp__265, uint32_t var_name_tmp__266) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__267;    /* Address-exposed local */
  uint16_t var_name_tmp__268;    /* Address-exposed local */
  uint32_t var_name_tmp__269;    /* Address-exposed local */
  uint32_t var_name_tmp__270;
  uint16_t var_name_tmp__271;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__272;
  uint16_t* var_name_tmp__273;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__274;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__275;
  uint16_t* var_name_tmp__276;
  uint64_t var_name_load_i16_3;

  var_name_tmp__267 = var_name_tmp__264;
  var_name_tmp__268 = var_name_tmp__265;
  var_name_tmp__269 = var_name_tmp__266;
  var_name_tmp__270 = var_name_tmp__269;
  if ((((var_name_tmp__270 != 0u)&1))) {
    goto var_name_tmp__277;
  } else {
    goto var_name_tmp__278;
  }

var_name_tmp__277:
  var_name_tmp__271 = var_name_tmp__268;
  var_name_tmp__272 = var_name_tmp__267;
  var_name_tmp__273 = (&var_name_tmp__272->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__273)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__273)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__271))))))), 16, 2);
  goto var_name_tmp__279;

var_name_tmp__278:
  var_name_tmp__274 = var_name_tmp__268;
  var_name_tmp__275 = var_name_tmp__267;
  var_name_tmp__276 = (&var_name_tmp__275->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__276)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__276)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__274))))))))))))), 16, 2);
  goto var_name_tmp__279;

var_name_tmp__279:
  return;
}


void SPI_I2S_ITConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__280, uint8_t var_name_tmp__281, uint32_t var_name_tmp__282) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__283;    /* Address-exposed local */
  uint8_t var_name_tmp__284;    /* Address-exposed local */
  uint32_t var_name_tmp__285;    /* Address-exposed local */
  uint16_t var_name_tmp__286;    /* Address-exposed local */
  uint16_t var_name_tmp__287;    /* Address-exposed local */
  uint8_t var_name_tmp__288;
  uint16_t var_name_tmp__289;
  uint32_t var_name_tmp__290;
  uint16_t var_name_tmp__291;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__292;
  uint16_t* var_name_tmp__293;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__294;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__295;
  uint16_t* var_name_tmp__296;
  uint64_t var_name_load_i16_3;

  var_name_tmp__283 = var_name_tmp__280;
  var_name_tmp__284 = var_name_tmp__281;
  var_name_tmp__285 = var_name_tmp__282;
  var_name_tmp__286 = 0;
  var_name_tmp__287 = 0;
  var_name_tmp__288 = var_name_tmp__284;
  var_name_tmp__286 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__288)), 4))));
  var_name_tmp__289 = var_name_tmp__286;
  var_name_tmp__287 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__289)))));
  var_name_tmp__290 = var_name_tmp__285;
  if ((((var_name_tmp__290 != 0u)&1))) {
    goto var_name_tmp__297;
  } else {
    goto var_name_tmp__298;
  }

var_name_tmp__297:
  var_name_tmp__291 = var_name_tmp__287;
  var_name_tmp__292 = var_name_tmp__283;
  var_name_tmp__293 = (&var_name_tmp__292->field2);
  var_name_load_i16_ = __adin_load_((((uint8_t*)var_name_tmp__293)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__293)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)var_name_tmp__291))))))), 16, 2);
  goto var_name_tmp__299;

var_name_tmp__298:
  var_name_tmp__294 = var_name_tmp__287;
  var_name_tmp__295 = var_name_tmp__283;
  var_name_tmp__296 = (&var_name_tmp__295->field2);
  var_name_load_i16_3 = __adin_load_((((uint8_t*)var_name_tmp__296)), 16, 2);
  __adin_store_((((uint8_t*)var_name_tmp__296)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_3)))) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__294))))))))))))), 16, 2);
  goto var_name_tmp__299;

var_name_tmp__299:
  return;
}


uint32_t SPI_I2S_GetFlagStatus(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__300, uint16_t var_name_tmp__301) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__302;    /* Address-exposed local */
  uint16_t var_name_tmp__303;    /* Address-exposed local */
  uint32_t var_name_tmp__304;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__305;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__306;
  uint32_t var_name_tmp__307;

  var_name_tmp__302 = var_name_tmp__300;
  var_name_tmp__303 = var_name_tmp__301;
  var_name_tmp__304 = 0;
  var_name_tmp__305 = var_name_tmp__302;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__305->field4)))), 16, 2);
  var_name_tmp__306 = var_name_tmp__303;
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)var_name_tmp__306))) != 0u)&1))) {
    goto var_name_tmp__308;
  } else {
    goto var_name_tmp__309;
  }

var_name_tmp__308:
  var_name_tmp__304 = 1;
  goto var_name_tmp__310;

var_name_tmp__309:
  var_name_tmp__304 = 0;
  goto var_name_tmp__310;

var_name_tmp__310:
  var_name_tmp__307 = var_name_tmp__304;
  return var_name_tmp__307;
}


void SPI_I2S_ClearFlag(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__311, uint16_t var_name_tmp__312) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__313;    /* Address-exposed local */
  uint16_t var_name_tmp__314;    /* Address-exposed local */
  uint16_t var_name_tmp__315;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__316;

  var_name_tmp__313 = var_name_tmp__311;
  var_name_tmp__314 = var_name_tmp__312;
  var_name_tmp__315 = var_name_tmp__314;
  var_name_tmp__316 = var_name_tmp__313;
  __adin_store_((((uint8_t*)((&var_name_tmp__316->field4)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__315)))))))), 16, 2);
}


uint32_t SPI_I2S_GetITStatus(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__317, uint8_t var_name_tmp__318) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__319;    /* Address-exposed local */
  uint8_t var_name_tmp__320;    /* Address-exposed local */
  uint32_t var_name_tmp__321;    /* Address-exposed local */
  uint16_t var_name_tmp__322;    /* Address-exposed local */
  uint16_t var_name_tmp__323;    /* Address-exposed local */
  uint16_t var_name_tmp__324;    /* Address-exposed local */
  uint8_t var_name_tmp__325;
  uint8_t var_name_tmp__326;
  uint16_t var_name_tmp__327;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__328;
  uint64_t var_name_load_i16_;
  uint16_t var_name_tmp__329;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__330;
  uint64_t var_name_load_i16_2;
  uint16_t var_name_tmp__331;
  uint16_t var_name_tmp__332;
  uint32_t var_name_tmp__333;

  var_name_tmp__319 = var_name_tmp__317;
  var_name_tmp__320 = var_name_tmp__318;
  var_name_tmp__321 = 0;
  var_name_tmp__322 = 0;
  var_name_tmp__323 = 0;
  var_name_tmp__324 = 0;
  var_name_tmp__325 = var_name_tmp__320;
  var_name_tmp__322 = (((uint16_t)(1 << ((((uint32_t)(uint8_t)var_name_tmp__325)) & 15))));
  var_name_tmp__326 = var_name_tmp__320;
  var_name_tmp__323 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__326)), 4))));
  var_name_tmp__327 = var_name_tmp__323;
  var_name_tmp__323 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__327)))));
  var_name_tmp__328 = var_name_tmp__319;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__328->field2)))), 16, 2);
  var_name_tmp__329 = var_name_tmp__323;
  var_name_tmp__324 = (((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (((uint32_t)(uint16_t)var_name_tmp__329)))));
  var_name_tmp__330 = var_name_tmp__319;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__330->field4)))), 16, 2);
  var_name_tmp__331 = var_name_tmp__322;
  if ((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) & (((uint32_t)(uint16_t)var_name_tmp__331))) != 0u)&1))) {
    goto var_name_tmp__334;
  } else {
    goto var_name_tmp__335;
  }

var_name_tmp__334:
  var_name_tmp__332 = var_name_tmp__324;
  if (((((((uint32_t)(uint16_t)var_name_tmp__332)) != 0u)&1))) {
    goto var_name_tmp__336;
  } else {
    goto var_name_tmp__335;
  }

var_name_tmp__336:
  var_name_tmp__321 = 1;
  goto var_name_tmp__337;

var_name_tmp__335:
  var_name_tmp__321 = 0;
  goto var_name_tmp__337;

var_name_tmp__337:
  var_name_tmp__333 = var_name_tmp__321;
  return var_name_tmp__333;
}


void SPI_I2S_ClearITPendingBit(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__338, uint8_t var_name_tmp__339) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__340;    /* Address-exposed local */
  uint8_t var_name_tmp__341;    /* Address-exposed local */
  uint16_t var_name_tmp__342;    /* Address-exposed local */
  uint8_t var_name_tmp__343;
  uint16_t var_name_tmp__344;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__345;

  var_name_tmp__340 = var_name_tmp__338;
  var_name_tmp__341 = var_name_tmp__339;
  var_name_tmp__342 = 0;
  var_name_tmp__343 = var_name_tmp__341;
  var_name_tmp__342 = (((uint16_t)(1 << ((((uint32_t)(uint8_t)var_name_tmp__343)) & 15))));
  var_name_tmp__344 = var_name_tmp__342;
  var_name_tmp__345 = var_name_tmp__340;
  __adin_store_((((uint8_t*)((&var_name_tmp__345->field4)))), (((uint64_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__344)))))))), 16, 2);
}

