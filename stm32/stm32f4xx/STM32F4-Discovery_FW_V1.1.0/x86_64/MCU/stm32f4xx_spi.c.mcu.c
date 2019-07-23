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
  uint16_t var_name_tmp__20;
  uint16_t var_name_tmp__21;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__22;
  uint16_t var_name_tmp__23;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__24;
  uint16_t var_name_tmp__25;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__26;
  uint16_t var_name_tmp__27;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__28;
  uint16_t var_name_tmp__29;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__30;
  uint16_t var_name_tmp__31;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__32;
  uint16_t var_name_tmp__33;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__34;
  uint16_t var_name_tmp__35;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__36;
  uint16_t var_name_tmp__37;
  uint16_t var_name_tmp__38;
  uint16_t var_name_tmp__39;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__40;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__41;
  uint16_t* var_name_tmp__42;
  uint16_t var_name_tmp__43;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__44;
  uint16_t var_name_tmp__45;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__46;

  var_name_tmp__16 = var_name_tmp__14;
  var_name_tmp__17 = var_name_tmp__15;
  var_name_tmp__18 = 0;
  var_name_tmp__19 = var_name_tmp__16;
  var_name_tmp__20 = *(volatile uint16_t*)((&var_name_tmp__19->field0));
  var_name_tmp__18 = var_name_tmp__20;
  var_name_tmp__21 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__21)) & 12352)));
  var_name_tmp__22 = var_name_tmp__17;
  var_name_tmp__23 = *((&var_name_tmp__22->field0));
  var_name_tmp__24 = var_name_tmp__17;
  var_name_tmp__25 = *((&var_name_tmp__24->field1));
  var_name_tmp__26 = var_name_tmp__17;
  var_name_tmp__27 = *((&var_name_tmp__26->field2));
  var_name_tmp__28 = var_name_tmp__17;
  var_name_tmp__29 = *((&var_name_tmp__28->field3));
  var_name_tmp__30 = var_name_tmp__17;
  var_name_tmp__31 = *((&var_name_tmp__30->field4));
  var_name_tmp__32 = var_name_tmp__17;
  var_name_tmp__33 = *((&var_name_tmp__32->field5));
  var_name_tmp__34 = var_name_tmp__17;
  var_name_tmp__35 = *((&var_name_tmp__34->field6));
  var_name_tmp__36 = var_name_tmp__17;
  var_name_tmp__37 = *((&var_name_tmp__36->field7));
  var_name_tmp__38 = var_name_tmp__18;
  var_name_tmp__18 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__38)) | (((uint32_t)(uint16_t)(((uint16_t)((((((((((uint32_t)(uint16_t)var_name_tmp__23)) | (((uint32_t)(uint16_t)var_name_tmp__25))) | (((uint32_t)(uint16_t)var_name_tmp__27))) | (((uint32_t)(uint16_t)var_name_tmp__29))) | (((uint32_t)(uint16_t)var_name_tmp__31))) | (((uint32_t)(uint16_t)var_name_tmp__33))) | (((uint32_t)(uint16_t)var_name_tmp__35))) | (((uint32_t)(uint16_t)var_name_tmp__37))))))))));
  var_name_tmp__39 = var_name_tmp__18;
  var_name_tmp__40 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__40->field0)) = var_name_tmp__39;
  var_name_tmp__41 = var_name_tmp__16;
  var_name_tmp__42 = (&var_name_tmp__41->field14);
  var_name_tmp__43 = *(volatile uint16_t*)var_name_tmp__42;
  *(volatile uint16_t*)var_name_tmp__42 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__43)) & 63487)));
  var_name_tmp__44 = var_name_tmp__17;
  var_name_tmp__45 = *((&var_name_tmp__44->field8));
  var_name_tmp__46 = var_name_tmp__16;
  *(volatile uint16_t*)((&var_name_tmp__46->field8)) = var_name_tmp__45;
}


void I2S_Init(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__47, struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__48) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__49;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__50;    /* Address-exposed local */
  uint16_t var_name_tmp__51;    /* Address-exposed local */
  uint16_t var_name_tmp__52;    /* Address-exposed local */
  uint16_t var_name_tmp__53;    /* Address-exposed local */
  uint16_t var_name_tmp__54;    /* Address-exposed local */
  uint32_t var_name_tmp__55;    /* Address-exposed local */
  uint32_t var_name_tmp__56;    /* Address-exposed local */
  uint32_t var_name_tmp__57;    /* Address-exposed local */
  uint32_t var_name_tmp__58;    /* Address-exposed local */
  uint32_t var_name_tmp__59;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__60;
  uint16_t* var_name_tmp__61;
  uint16_t var_name_tmp__62;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__63;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__64;
  uint16_t var_name_tmp__65;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__66;
  uint32_t var_name_tmp__67;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__68;
  uint16_t var_name_tmp__69;
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;
  uint32_t var_name_tmp__72;
  uint32_t var_name_tmp__73;
  uint32_t var_name_tmp__74;
  uint32_t var_name_tmp__75;
  uint32_t var_name_tmp__76;
  uint32_t var_name_tmp__77;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__78;
  uint16_t var_name_tmp__79;
  uint32_t var_name_tmp__80;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__81;
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint16_t var_name_tmp__84;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__85;
  uint32_t var_name_tmp__86;
  uint32_t var_name_tmp__87;
  uint32_t var_name_tmp__88;
  uint32_t var_name_tmp__89;
  uint16_t var_name_tmp__90;
  uint16_t var_name_tmp__91;
  uint16_t var_name_tmp__92;
  uint16_t var_name_tmp__93;
  uint16_t var_name_tmp__94;
  uint16_t var_name_tmp__95;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__96;
  uint16_t var_name_tmp__97;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__98;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__99;
  uint16_t var_name_tmp__100;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__101;
  uint16_t var_name_tmp__102;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__103;
  uint16_t var_name_tmp__104;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__105;
  uint16_t var_name_tmp__106;
  uint16_t var_name_tmp__107;
  uint16_t var_name_tmp__108;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__109;

  var_name_tmp__49 = var_name_tmp__47;
  var_name_tmp__50 = var_name_tmp__48;
  var_name_tmp__51 = 0;
  var_name_tmp__52 = 2;
  var_name_tmp__53 = 0;
  var_name_tmp__54 = 1;
  var_name_tmp__55 = 0;
  var_name_tmp__56 = 0;
  var_name_tmp__57 = 0;
  var_name_tmp__58 = 0;
  var_name_tmp__59 = 0;
  var_name_tmp__60 = var_name_tmp__49;
  var_name_tmp__61 = (&var_name_tmp__60->field14);
  var_name_tmp__62 = *(volatile uint16_t*)var_name_tmp__61;
  *(volatile uint16_t*)var_name_tmp__61 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__62)) & 61504)));
  var_name_tmp__63 = var_name_tmp__49;
  *(volatile uint16_t*)((&var_name_tmp__63->field16)) = 2;
  var_name_tmp__64 = var_name_tmp__49;
  var_name_tmp__65 = *(volatile uint16_t*)((&var_name_tmp__64->field14));
  var_name_tmp__51 = var_name_tmp__65;
  var_name_tmp__66 = var_name_tmp__50;
  var_name_tmp__67 = *((&var_name_tmp__66->field4));
  if ((((var_name_tmp__67 == 2u)&1))) {
    goto var_name_tmp__110;
  } else {
    goto var_name_tmp__111;
  }

var_name_tmp__110:
  var_name_tmp__53 = 0;
  var_name_tmp__52 = 2;
  goto var_name_tmp__112;

var_name_tmp__111:
  var_name_tmp__68 = var_name_tmp__50;
  var_name_tmp__69 = *((&var_name_tmp__68->field2));
  if (((((((uint32_t)(uint16_t)var_name_tmp__69)) == 0u)&1))) {
    goto var_name_tmp__113;
  } else {
    goto var_name_tmp__114;
  }

var_name_tmp__113:
  var_name_tmp__54 = 1;
  goto var_name_tmp__115;

var_name_tmp__114:
  var_name_tmp__54 = 2;
  goto var_name_tmp__115;

var_name_tmp__115:
  var_name_tmp__70 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  if (((((var_name_tmp__70 & 8388608) != 0u)&1))) {
    goto var_name_tmp__116;
  } else {
    goto var_name_tmp__117;
  }

var_name_tmp__116:
  var_name_tmp__71 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field2)) = (var_name_tmp__71 & -8388609);
  goto var_name_tmp__117;

var_name_tmp__117:
  var_name_tmp__72 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29));
  var_name_tmp__58 = ((llvm_lshr_u32((var_name_tmp__72 & 32704), 6)) & 511);
  var_name_tmp__73 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field29));
  var_name_tmp__59 = ((llvm_lshr_u32((var_name_tmp__73 & 1879048192u), 28)) & 7);
  var_name_tmp__74 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_RCC_TypeDef*)(uintptr_t)UINT64_C(1073887232))->field1));
  var_name_tmp__57 = (var_name_tmp__74 & 63);
  var_name_tmp__75 = var_name_tmp__57;
  var_name_tmp__76 = var_name_tmp__58;
  var_name_tmp__77 = var_name_tmp__59;
  var_name_tmp__56 = (llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(8000000, var_name_tmp__75)), var_name_tmp__76)), var_name_tmp__77));
  var_name_tmp__78 = var_name_tmp__50;
  var_name_tmp__79 = *((&var_name_tmp__78->field3));
  if (((((((uint32_t)(uint16_t)var_name_tmp__79)) == 512u)&1))) {
    goto var_name_tmp__118;
  } else {
    goto var_name_tmp__119;
  }

var_name_tmp__118:
  var_name_tmp__80 = var_name_tmp__56;
  var_name_tmp__81 = var_name_tmp__50;
  var_name_tmp__82 = *((&var_name_tmp__81->field4));
  var_name_tmp__55 = (((uint32_t)(uint16_t)(((uint16_t)(llvm_add_u32((llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(var_name_tmp__80, 256)), 10)), var_name_tmp__82)), 5))))));
  goto var_name_tmp__120;

var_name_tmp__119:
  var_name_tmp__83 = var_name_tmp__56;
  var_name_tmp__84 = var_name_tmp__54;
  var_name_tmp__85 = var_name_tmp__50;
  var_name_tmp__86 = *((&var_name_tmp__85->field4));
  var_name_tmp__55 = (((uint32_t)(uint16_t)(((uint16_t)(llvm_add_u32((llvm_udiv_u32((llvm_mul_u32((llvm_udiv_u32(var_name_tmp__83, (llvm_mul_u32(32, (((uint32_t)(uint16_t)var_name_tmp__84)))))), 10)), var_name_tmp__86)), 5))))));
  goto var_name_tmp__120;

var_name_tmp__120:
  var_name_tmp__87 = var_name_tmp__55;
  var_name_tmp__55 = (llvm_udiv_u32(var_name_tmp__87, 10));
  var_name_tmp__88 = var_name_tmp__55;
  var_name_tmp__53 = (((uint16_t)(var_name_tmp__88 & 1)));
  var_name_tmp__89 = var_name_tmp__55;
  var_name_tmp__90 = var_name_tmp__53;
  var_name_tmp__52 = (((uint16_t)(llvm_udiv_u32((llvm_sub_u32(var_name_tmp__89, (((uint32_t)(uint16_t)var_name_tmp__90)))), 2))));
  var_name_tmp__91 = var_name_tmp__53;
  var_name_tmp__53 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__91)) << 8)));
  goto var_name_tmp__112;

var_name_tmp__112:
  var_name_tmp__92 = var_name_tmp__52;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__92))) < ((int32_t)2u))&1))) {
    goto var_name_tmp__121;
  } else {
    goto var_name_tmp__122;
  }

var_name_tmp__122:
  var_name_tmp__93 = var_name_tmp__52;
  if ((((((int32_t)(((uint32_t)(uint16_t)var_name_tmp__93))) > ((int32_t)255u))&1))) {
    goto var_name_tmp__121;
  } else {
    goto var_name_tmp__123;
  }

var_name_tmp__121:
  var_name_tmp__52 = 2;
  var_name_tmp__53 = 0;
  goto var_name_tmp__123;

var_name_tmp__123:
  var_name_tmp__94 = var_name_tmp__52;
  var_name_tmp__95 = var_name_tmp__53;
  var_name_tmp__96 = var_name_tmp__50;
  var_name_tmp__97 = *((&var_name_tmp__96->field3));
  var_name_tmp__98 = var_name_tmp__49;
  *(volatile uint16_t*)((&var_name_tmp__98->field16)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__94)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__95)) | (((uint32_t)(uint16_t)var_name_tmp__97))))))))));
  var_name_tmp__99 = var_name_tmp__50;
  var_name_tmp__100 = *((&var_name_tmp__99->field0));
  var_name_tmp__101 = var_name_tmp__50;
  var_name_tmp__102 = *((&var_name_tmp__101->field1));
  var_name_tmp__103 = var_name_tmp__50;
  var_name_tmp__104 = *((&var_name_tmp__103->field2));
  var_name_tmp__105 = var_name_tmp__50;
  var_name_tmp__106 = *((&var_name_tmp__105->field5));
  var_name_tmp__107 = var_name_tmp__51;
  var_name_tmp__51 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__107)) | (((uint32_t)(uint16_t)(((uint16_t)(2048 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__100)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__102)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__104)) | (((uint32_t)(uint16_t)var_name_tmp__106)))))))))))))))))))))))));
  var_name_tmp__108 = var_name_tmp__51;
  var_name_tmp__109 = var_name_tmp__49;
  *(volatile uint16_t*)((&var_name_tmp__109->field14)) = var_name_tmp__108;
}


void SPI_StructInit(struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__124) {
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__125;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__126;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__127;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__128;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__129;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__130;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__131;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__132;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__133;
  struct l_struct_struct_OC_SPI_InitTypeDef* var_name_tmp__134;

  var_name_tmp__125 = var_name_tmp__124;
  var_name_tmp__126 = var_name_tmp__125;
  *((&var_name_tmp__126->field0)) = 0;
  var_name_tmp__127 = var_name_tmp__125;
  *((&var_name_tmp__127->field1)) = 0;
  var_name_tmp__128 = var_name_tmp__125;
  *((&var_name_tmp__128->field2)) = 0;
  var_name_tmp__129 = var_name_tmp__125;
  *((&var_name_tmp__129->field3)) = 0;
  var_name_tmp__130 = var_name_tmp__125;
  *((&var_name_tmp__130->field4)) = 0;
  var_name_tmp__131 = var_name_tmp__125;
  *((&var_name_tmp__131->field5)) = 0;
  var_name_tmp__132 = var_name_tmp__125;
  *((&var_name_tmp__132->field6)) = 0;
  var_name_tmp__133 = var_name_tmp__125;
  *((&var_name_tmp__133->field7)) = 0;
  var_name_tmp__134 = var_name_tmp__125;
  *((&var_name_tmp__134->field8)) = 7;
}


void I2S_StructInit(struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__135) {
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__136;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__137;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__138;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__139;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__140;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__141;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__142;

  var_name_tmp__136 = var_name_tmp__135;
  var_name_tmp__137 = var_name_tmp__136;
  *((&var_name_tmp__137->field0)) = 0;
  var_name_tmp__138 = var_name_tmp__136;
  *((&var_name_tmp__138->field1)) = 0;
  var_name_tmp__139 = var_name_tmp__136;
  *((&var_name_tmp__139->field2)) = 0;
  var_name_tmp__140 = var_name_tmp__136;
  *((&var_name_tmp__140->field3)) = 0;
  var_name_tmp__141 = var_name_tmp__136;
  *((&var_name_tmp__141->field4)) = 2;
  var_name_tmp__142 = var_name_tmp__136;
  *((&var_name_tmp__142->field5)) = 0;
}


void SPI_Cmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__143, uint32_t var_name_tmp__144) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__145;    /* Address-exposed local */
  uint32_t var_name_tmp__146;    /* Address-exposed local */
  uint32_t var_name_tmp__147;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__148;
  uint16_t* var_name_tmp__149;
  uint16_t var_name_tmp__150;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__151;
  uint16_t* var_name_tmp__152;
  uint16_t var_name_tmp__153;

  var_name_tmp__145 = var_name_tmp__143;
  var_name_tmp__146 = var_name_tmp__144;
  var_name_tmp__147 = var_name_tmp__146;
  if ((((var_name_tmp__147 != 0u)&1))) {
    goto var_name_tmp__154;
  } else {
    goto var_name_tmp__155;
  }

var_name_tmp__154:
  var_name_tmp__148 = var_name_tmp__145;
  var_name_tmp__149 = (&var_name_tmp__148->field0);
  var_name_tmp__150 = *(volatile uint16_t*)var_name_tmp__149;
  *(volatile uint16_t*)var_name_tmp__149 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__150)) | 64)));
  goto var_name_tmp__156;

var_name_tmp__155:
  var_name_tmp__151 = var_name_tmp__145;
  var_name_tmp__152 = (&var_name_tmp__151->field0);
  var_name_tmp__153 = *(volatile uint16_t*)var_name_tmp__152;
  *(volatile uint16_t*)var_name_tmp__152 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__153)) & 65471)));
  goto var_name_tmp__156;

var_name_tmp__156:
  return;
}


void I2S_Cmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__157, uint32_t var_name_tmp__158) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__159;    /* Address-exposed local */
  uint32_t var_name_tmp__160;    /* Address-exposed local */
  uint32_t var_name_tmp__161;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__162;
  uint16_t* var_name_tmp__163;
  uint16_t var_name_tmp__164;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__165;
  uint16_t* var_name_tmp__166;
  uint16_t var_name_tmp__167;

  var_name_tmp__159 = var_name_tmp__157;
  var_name_tmp__160 = var_name_tmp__158;
  var_name_tmp__161 = var_name_tmp__160;
  if ((((var_name_tmp__161 != 0u)&1))) {
    goto var_name_tmp__168;
  } else {
    goto var_name_tmp__169;
  }

var_name_tmp__168:
  var_name_tmp__162 = var_name_tmp__159;
  var_name_tmp__163 = (&var_name_tmp__162->field14);
  var_name_tmp__164 = *(volatile uint16_t*)var_name_tmp__163;
  *(volatile uint16_t*)var_name_tmp__163 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__164)) | 1024)));
  goto var_name_tmp__170;

var_name_tmp__169:
  var_name_tmp__165 = var_name_tmp__159;
  var_name_tmp__166 = (&var_name_tmp__165->field14);
  var_name_tmp__167 = *(volatile uint16_t*)var_name_tmp__166;
  *(volatile uint16_t*)var_name_tmp__166 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__167)) & 64511)));
  goto var_name_tmp__170;

var_name_tmp__170:
  return;
}


void SPI_DataSizeConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__171, uint16_t var_name_tmp__172) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__173;    /* Address-exposed local */
  uint16_t var_name_tmp__174;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__175;
  uint16_t* var_name_tmp__176;
  uint16_t var_name_tmp__177;
  uint16_t var_name_tmp__178;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__179;
  uint16_t* var_name_tmp__180;
  uint16_t var_name_tmp__181;

  var_name_tmp__173 = var_name_tmp__171;
  var_name_tmp__174 = var_name_tmp__172;
  var_name_tmp__175 = var_name_tmp__173;
  var_name_tmp__176 = (&var_name_tmp__175->field0);
  var_name_tmp__177 = *(volatile uint16_t*)var_name_tmp__176;
  *(volatile uint16_t*)var_name_tmp__176 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__177)) & 63487)));
  var_name_tmp__178 = var_name_tmp__174;
  var_name_tmp__179 = var_name_tmp__173;
  var_name_tmp__180 = (&var_name_tmp__179->field0);
  var_name_tmp__181 = *(volatile uint16_t*)var_name_tmp__180;
  *(volatile uint16_t*)var_name_tmp__180 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__181)) | (((uint32_t)(uint16_t)var_name_tmp__178)))));
}


void SPI_BiDirectionalLineConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__182, uint16_t var_name_tmp__183) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__184;    /* Address-exposed local */
  uint16_t var_name_tmp__185;    /* Address-exposed local */
  uint16_t var_name_tmp__186;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__187;
  uint16_t* var_name_tmp__188;
  uint16_t var_name_tmp__189;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__190;
  uint16_t* var_name_tmp__191;
  uint16_t var_name_tmp__192;

  var_name_tmp__184 = var_name_tmp__182;
  var_name_tmp__185 = var_name_tmp__183;
  var_name_tmp__186 = var_name_tmp__185;
  if (((((((uint32_t)(uint16_t)var_name_tmp__186)) == 16384u)&1))) {
    goto var_name_tmp__193;
  } else {
    goto var_name_tmp__194;
  }

var_name_tmp__193:
  var_name_tmp__187 = var_name_tmp__184;
  var_name_tmp__188 = (&var_name_tmp__187->field0);
  var_name_tmp__189 = *(volatile uint16_t*)var_name_tmp__188;
  *(volatile uint16_t*)var_name_tmp__188 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__189)) | 16384)));
  goto var_name_tmp__195;

var_name_tmp__194:
  var_name_tmp__190 = var_name_tmp__184;
  var_name_tmp__191 = (&var_name_tmp__190->field0);
  var_name_tmp__192 = *(volatile uint16_t*)var_name_tmp__191;
  *(volatile uint16_t*)var_name_tmp__191 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__192)) & 49151)));
  goto var_name_tmp__195;

var_name_tmp__195:
  return;
}


void SPI_NSSInternalSoftwareConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__196, uint16_t var_name_tmp__197) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__198;    /* Address-exposed local */
  uint16_t var_name_tmp__199;    /* Address-exposed local */
  uint16_t var_name_tmp__200;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__201;
  uint16_t* var_name_tmp__202;
  uint16_t var_name_tmp__203;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__204;
  uint16_t* var_name_tmp__205;
  uint16_t var_name_tmp__206;

  var_name_tmp__198 = var_name_tmp__196;
  var_name_tmp__199 = var_name_tmp__197;
  var_name_tmp__200 = var_name_tmp__199;
  if (((((((uint32_t)(uint16_t)var_name_tmp__200)) != 65279u)&1))) {
    goto var_name_tmp__207;
  } else {
    goto var_name_tmp__208;
  }

var_name_tmp__207:
  var_name_tmp__201 = var_name_tmp__198;
  var_name_tmp__202 = (&var_name_tmp__201->field0);
  var_name_tmp__203 = *(volatile uint16_t*)var_name_tmp__202;
  *(volatile uint16_t*)var_name_tmp__202 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__203)) | 256)));
  goto var_name_tmp__209;

var_name_tmp__208:
  var_name_tmp__204 = var_name_tmp__198;
  var_name_tmp__205 = (&var_name_tmp__204->field0);
  var_name_tmp__206 = *(volatile uint16_t*)var_name_tmp__205;
  *(volatile uint16_t*)var_name_tmp__205 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__206)) & 65279)));
  goto var_name_tmp__209;

var_name_tmp__209:
  return;
}


void SPI_SSOutputCmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__210, uint32_t var_name_tmp__211) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__212;    /* Address-exposed local */
  uint32_t var_name_tmp__213;    /* Address-exposed local */
  uint32_t var_name_tmp__214;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__215;
  uint16_t* var_name_tmp__216;
  uint16_t var_name_tmp__217;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__218;
  uint16_t* var_name_tmp__219;
  uint16_t var_name_tmp__220;

  var_name_tmp__212 = var_name_tmp__210;
  var_name_tmp__213 = var_name_tmp__211;
  var_name_tmp__214 = var_name_tmp__213;
  if ((((var_name_tmp__214 != 0u)&1))) {
    goto var_name_tmp__221;
  } else {
    goto var_name_tmp__222;
  }

var_name_tmp__221:
  var_name_tmp__215 = var_name_tmp__212;
  var_name_tmp__216 = (&var_name_tmp__215->field2);
  var_name_tmp__217 = *(volatile uint16_t*)var_name_tmp__216;
  *(volatile uint16_t*)var_name_tmp__216 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__217)) | 4)));
  goto var_name_tmp__223;

var_name_tmp__222:
  var_name_tmp__218 = var_name_tmp__212;
  var_name_tmp__219 = (&var_name_tmp__218->field2);
  var_name_tmp__220 = *(volatile uint16_t*)var_name_tmp__219;
  *(volatile uint16_t*)var_name_tmp__219 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__220)) & 65531)));
  goto var_name_tmp__223;

var_name_tmp__223:
  return;
}


void SPI_TIModeCmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__224, uint32_t var_name_tmp__225) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__226;    /* Address-exposed local */
  uint32_t var_name_tmp__227;    /* Address-exposed local */
  uint32_t var_name_tmp__228;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__229;
  uint16_t* var_name_tmp__230;
  uint16_t var_name_tmp__231;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__232;
  uint16_t* var_name_tmp__233;
  uint16_t var_name_tmp__234;

  var_name_tmp__226 = var_name_tmp__224;
  var_name_tmp__227 = var_name_tmp__225;
  var_name_tmp__228 = var_name_tmp__227;
  if ((((var_name_tmp__228 != 0u)&1))) {
    goto var_name_tmp__235;
  } else {
    goto var_name_tmp__236;
  }

var_name_tmp__235:
  var_name_tmp__229 = var_name_tmp__226;
  var_name_tmp__230 = (&var_name_tmp__229->field2);
  var_name_tmp__231 = *(volatile uint16_t*)var_name_tmp__230;
  *(volatile uint16_t*)var_name_tmp__230 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__231)) | 16)));
  goto var_name_tmp__237;

var_name_tmp__236:
  var_name_tmp__232 = var_name_tmp__226;
  var_name_tmp__233 = (&var_name_tmp__232->field2);
  var_name_tmp__234 = *(volatile uint16_t*)var_name_tmp__233;
  *(volatile uint16_t*)var_name_tmp__233 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__234)) & 65519)));
  goto var_name_tmp__237;

var_name_tmp__237:
  return;
}


void I2S_FullDuplexConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__238, struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__239) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__240;    /* Address-exposed local */
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__241;    /* Address-exposed local */
  uint16_t var_name_tmp__242;    /* Address-exposed local */
  uint16_t var_name_tmp__243;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__244;
  uint16_t* var_name_tmp__245;
  uint16_t var_name_tmp__246;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__247;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__248;
  uint16_t var_name_tmp__249;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__250;
  uint16_t var_name_tmp__251;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__252;
  uint16_t var_name_tmp__253;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__254;
  uint16_t var_name_tmp__255;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__256;
  uint16_t var_name_tmp__257;
  uint16_t var_name_tmp__258;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__259;
  uint16_t var_name_tmp__260;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__261;
  uint16_t var_name_tmp__262;
  struct l_struct_struct_OC_I2S_InitTypeDef* var_name_tmp__263;
  uint16_t var_name_tmp__264;
  uint16_t var_name_tmp__265;
  uint16_t var_name_tmp__266;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__267;

  var_name_tmp__240 = var_name_tmp__238;
  var_name_tmp__241 = var_name_tmp__239;
  var_name_tmp__242 = 0;
  var_name_tmp__243 = 0;
  var_name_tmp__244 = var_name_tmp__240;
  var_name_tmp__245 = (&var_name_tmp__244->field14);
  var_name_tmp__246 = *(volatile uint16_t*)var_name_tmp__245;
  *(volatile uint16_t*)var_name_tmp__245 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__246)) & 61504)));
  var_name_tmp__247 = var_name_tmp__240;
  *(volatile uint16_t*)((&var_name_tmp__247->field16)) = 2;
  var_name_tmp__248 = var_name_tmp__240;
  var_name_tmp__249 = *(volatile uint16_t*)((&var_name_tmp__248->field14));
  var_name_tmp__242 = var_name_tmp__249;
  var_name_tmp__250 = var_name_tmp__241;
  var_name_tmp__251 = *((&var_name_tmp__250->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__251)) == 512u)&1))) {
    goto var_name_tmp__268;
  } else {
    goto var_name_tmp__269;
  }

var_name_tmp__269:
  var_name_tmp__252 = var_name_tmp__241;
  var_name_tmp__253 = *((&var_name_tmp__252->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__253)) == 0u)&1))) {
    goto var_name_tmp__268;
  } else {
    goto var_name_tmp__270;
  }

var_name_tmp__268:
  var_name_tmp__243 = 256;
  goto var_name_tmp__271;

var_name_tmp__270:
  var_name_tmp__254 = var_name_tmp__241;
  var_name_tmp__255 = *((&var_name_tmp__254->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__255)) == 768u)&1))) {
    goto var_name_tmp__272;
  } else {
    goto var_name_tmp__273;
  }

var_name_tmp__273:
  var_name_tmp__256 = var_name_tmp__241;
  var_name_tmp__257 = *((&var_name_tmp__256->field0));
  if (((((((uint32_t)(uint16_t)var_name_tmp__257)) == 256u)&1))) {
    goto var_name_tmp__272;
  } else {
    goto var_name_tmp__274;
  }

var_name_tmp__272:
  var_name_tmp__243 = 0;
  goto var_name_tmp__274;

var_name_tmp__274:
  goto var_name_tmp__271;

var_name_tmp__271:
  var_name_tmp__258 = var_name_tmp__243;
  var_name_tmp__259 = var_name_tmp__241;
  var_name_tmp__260 = *((&var_name_tmp__259->field1));
  var_name_tmp__261 = var_name_tmp__241;
  var_name_tmp__262 = *((&var_name_tmp__261->field2));
  var_name_tmp__263 = var_name_tmp__241;
  var_name_tmp__264 = *((&var_name_tmp__263->field5));
  var_name_tmp__265 = var_name_tmp__242;
  var_name_tmp__242 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__265)) | (((uint32_t)(uint16_t)(((uint16_t)(2048 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__258)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__260)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__262)) | (((uint32_t)(uint16_t)var_name_tmp__264)))))))))))))))))))))))));
  var_name_tmp__266 = var_name_tmp__242;
  var_name_tmp__267 = var_name_tmp__240;
  *(volatile uint16_t*)((&var_name_tmp__267->field14)) = var_name_tmp__266;
}


uint16_t SPI_I2S_ReceiveData(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__275) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__276;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__277;
  uint16_t var_name_tmp__278;

  var_name_tmp__276 = var_name_tmp__275;
  var_name_tmp__277 = var_name_tmp__276;
  var_name_tmp__278 = *(volatile uint16_t*)((&var_name_tmp__277->field6));
  return var_name_tmp__278;
}


void SPI_I2S_SendData(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__279, uint16_t var_name_tmp__280) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__281;    /* Address-exposed local */
  uint16_t var_name_tmp__282;    /* Address-exposed local */
  uint16_t var_name_tmp__283;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__284;

  var_name_tmp__281 = var_name_tmp__279;
  var_name_tmp__282 = var_name_tmp__280;
  var_name_tmp__283 = var_name_tmp__282;
  var_name_tmp__284 = var_name_tmp__281;
  *(volatile uint16_t*)((&var_name_tmp__284->field6)) = var_name_tmp__283;
}


void SPI_CalculateCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__285, uint32_t var_name_tmp__286) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__287;    /* Address-exposed local */
  uint32_t var_name_tmp__288;    /* Address-exposed local */
  uint32_t var_name_tmp__289;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__290;
  uint16_t* var_name_tmp__291;
  uint16_t var_name_tmp__292;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__293;
  uint16_t* var_name_tmp__294;
  uint16_t var_name_tmp__295;

  var_name_tmp__287 = var_name_tmp__285;
  var_name_tmp__288 = var_name_tmp__286;
  var_name_tmp__289 = var_name_tmp__288;
  if ((((var_name_tmp__289 != 0u)&1))) {
    goto var_name_tmp__296;
  } else {
    goto var_name_tmp__297;
  }

var_name_tmp__296:
  var_name_tmp__290 = var_name_tmp__287;
  var_name_tmp__291 = (&var_name_tmp__290->field0);
  var_name_tmp__292 = *(volatile uint16_t*)var_name_tmp__291;
  *(volatile uint16_t*)var_name_tmp__291 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__292)) | 8192)));
  goto var_name_tmp__298;

var_name_tmp__297:
  var_name_tmp__293 = var_name_tmp__287;
  var_name_tmp__294 = (&var_name_tmp__293->field0);
  var_name_tmp__295 = *(volatile uint16_t*)var_name_tmp__294;
  *(volatile uint16_t*)var_name_tmp__294 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__295)) & 57343)));
  goto var_name_tmp__298;

var_name_tmp__298:
  return;
}


void SPI_TransmitCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__299) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__300;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__301;
  uint16_t* var_name_tmp__302;
  uint16_t var_name_tmp__303;

  var_name_tmp__300 = var_name_tmp__299;
  var_name_tmp__301 = var_name_tmp__300;
  var_name_tmp__302 = (&var_name_tmp__301->field0);
  var_name_tmp__303 = *(volatile uint16_t*)var_name_tmp__302;
  *(volatile uint16_t*)var_name_tmp__302 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__303)) | 4096)));
}


uint16_t SPI_GetCRC(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__304, uint8_t var_name_tmp__305) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__306;    /* Address-exposed local */
  uint8_t var_name_tmp__307;    /* Address-exposed local */
  uint16_t var_name_tmp__308;    /* Address-exposed local */
  uint8_t var_name_tmp__309;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__310;
  uint16_t var_name_tmp__311;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__312;
  uint16_t var_name_tmp__313;
  uint16_t var_name_tmp__314;

  var_name_tmp__306 = var_name_tmp__304;
  var_name_tmp__307 = var_name_tmp__305;
  var_name_tmp__308 = 0;
  var_name_tmp__309 = var_name_tmp__307;
  if (((((((uint32_t)(uint8_t)var_name_tmp__309)) != 1u)&1))) {
    goto var_name_tmp__315;
  } else {
    goto var_name_tmp__316;
  }

var_name_tmp__315:
  var_name_tmp__310 = var_name_tmp__306;
  var_name_tmp__311 = *(volatile uint16_t*)((&var_name_tmp__310->field12));
  var_name_tmp__308 = var_name_tmp__311;
  goto var_name_tmp__317;

var_name_tmp__316:
  var_name_tmp__312 = var_name_tmp__306;
  var_name_tmp__313 = *(volatile uint16_t*)((&var_name_tmp__312->field10));
  var_name_tmp__308 = var_name_tmp__313;
  goto var_name_tmp__317;

var_name_tmp__317:
  var_name_tmp__314 = var_name_tmp__308;
  return var_name_tmp__314;
}


uint16_t SPI_GetCRCPolynomial(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__318) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__319;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__320;
  uint16_t var_name_tmp__321;

  var_name_tmp__319 = var_name_tmp__318;
  var_name_tmp__320 = var_name_tmp__319;
  var_name_tmp__321 = *(volatile uint16_t*)((&var_name_tmp__320->field8));
  return var_name_tmp__321;
}


void SPI_I2S_DMACmd(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__322, uint16_t var_name_tmp__323, uint32_t var_name_tmp__324) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__325;    /* Address-exposed local */
  uint16_t var_name_tmp__326;    /* Address-exposed local */
  uint32_t var_name_tmp__327;    /* Address-exposed local */
  uint32_t var_name_tmp__328;
  uint16_t var_name_tmp__329;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__330;
  uint16_t* var_name_tmp__331;
  uint16_t var_name_tmp__332;
  uint16_t var_name_tmp__333;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__334;
  uint16_t* var_name_tmp__335;
  uint16_t var_name_tmp__336;

  var_name_tmp__325 = var_name_tmp__322;
  var_name_tmp__326 = var_name_tmp__323;
  var_name_tmp__327 = var_name_tmp__324;
  var_name_tmp__328 = var_name_tmp__327;
  if ((((var_name_tmp__328 != 0u)&1))) {
    goto var_name_tmp__337;
  } else {
    goto var_name_tmp__338;
  }

var_name_tmp__337:
  var_name_tmp__329 = var_name_tmp__326;
  var_name_tmp__330 = var_name_tmp__325;
  var_name_tmp__331 = (&var_name_tmp__330->field2);
  var_name_tmp__332 = *(volatile uint16_t*)var_name_tmp__331;
  *(volatile uint16_t*)var_name_tmp__331 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__332)) | (((uint32_t)(uint16_t)var_name_tmp__329)))));
  goto var_name_tmp__339;

var_name_tmp__338:
  var_name_tmp__333 = var_name_tmp__326;
  var_name_tmp__334 = var_name_tmp__325;
  var_name_tmp__335 = (&var_name_tmp__334->field2);
  var_name_tmp__336 = *(volatile uint16_t*)var_name_tmp__335;
  *(volatile uint16_t*)var_name_tmp__335 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__336)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__333)))))))))));
  goto var_name_tmp__339;

var_name_tmp__339:
  return;
}


void SPI_I2S_ITConfig(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__340, uint8_t var_name_tmp__341, uint32_t var_name_tmp__342) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__343;    /* Address-exposed local */
  uint8_t var_name_tmp__344;    /* Address-exposed local */
  uint32_t var_name_tmp__345;    /* Address-exposed local */
  uint16_t var_name_tmp__346;    /* Address-exposed local */
  uint16_t var_name_tmp__347;    /* Address-exposed local */
  uint8_t var_name_tmp__348;
  uint16_t var_name_tmp__349;
  uint32_t var_name_tmp__350;
  uint16_t var_name_tmp__351;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__352;
  uint16_t* var_name_tmp__353;
  uint16_t var_name_tmp__354;
  uint16_t var_name_tmp__355;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__356;
  uint16_t* var_name_tmp__357;
  uint16_t var_name_tmp__358;

  var_name_tmp__343 = var_name_tmp__340;
  var_name_tmp__344 = var_name_tmp__341;
  var_name_tmp__345 = var_name_tmp__342;
  var_name_tmp__346 = 0;
  var_name_tmp__347 = 0;
  var_name_tmp__348 = var_name_tmp__344;
  var_name_tmp__346 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__348)), 4))));
  var_name_tmp__349 = var_name_tmp__346;
  var_name_tmp__347 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__349)))));
  var_name_tmp__350 = var_name_tmp__345;
  if ((((var_name_tmp__350 != 0u)&1))) {
    goto var_name_tmp__359;
  } else {
    goto var_name_tmp__360;
  }

var_name_tmp__359:
  var_name_tmp__351 = var_name_tmp__347;
  var_name_tmp__352 = var_name_tmp__343;
  var_name_tmp__353 = (&var_name_tmp__352->field2);
  var_name_tmp__354 = *(volatile uint16_t*)var_name_tmp__353;
  *(volatile uint16_t*)var_name_tmp__353 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__354)) | (((uint32_t)(uint16_t)var_name_tmp__351)))));
  goto var_name_tmp__361;

var_name_tmp__360:
  var_name_tmp__355 = var_name_tmp__347;
  var_name_tmp__356 = var_name_tmp__343;
  var_name_tmp__357 = (&var_name_tmp__356->field2);
  var_name_tmp__358 = *(volatile uint16_t*)var_name_tmp__357;
  *(volatile uint16_t*)var_name_tmp__357 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__358)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__355)))))))))));
  goto var_name_tmp__361;

var_name_tmp__361:
  return;
}


uint32_t SPI_I2S_GetFlagStatus(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__362, uint16_t var_name_tmp__363) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__364;    /* Address-exposed local */
  uint16_t var_name_tmp__365;    /* Address-exposed local */
  uint32_t var_name_tmp__366;    /* Address-exposed local */
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__367;
  uint16_t var_name_tmp__368;
  uint16_t var_name_tmp__369;
  uint32_t var_name_tmp__370;

  var_name_tmp__364 = var_name_tmp__362;
  var_name_tmp__365 = var_name_tmp__363;
  var_name_tmp__366 = 0;
  var_name_tmp__367 = var_name_tmp__364;
  var_name_tmp__368 = *(volatile uint16_t*)((&var_name_tmp__367->field4));
  var_name_tmp__369 = var_name_tmp__365;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__368)) & (((uint32_t)(uint16_t)var_name_tmp__369))) != 0u)&1))) {
    goto var_name_tmp__371;
  } else {
    goto var_name_tmp__372;
  }

var_name_tmp__371:
  var_name_tmp__366 = 1;
  goto var_name_tmp__373;

var_name_tmp__372:
  var_name_tmp__366 = 0;
  goto var_name_tmp__373;

var_name_tmp__373:
  var_name_tmp__370 = var_name_tmp__366;
  return var_name_tmp__370;
}


void SPI_I2S_ClearFlag(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__374, uint16_t var_name_tmp__375) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__376;    /* Address-exposed local */
  uint16_t var_name_tmp__377;    /* Address-exposed local */
  uint16_t var_name_tmp__378;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__379;

  var_name_tmp__376 = var_name_tmp__374;
  var_name_tmp__377 = var_name_tmp__375;
  var_name_tmp__378 = var_name_tmp__377;
  var_name_tmp__379 = var_name_tmp__376;
  *(volatile uint16_t*)((&var_name_tmp__379->field4)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__378))))));
}


uint32_t SPI_I2S_GetITStatus(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__380, uint8_t var_name_tmp__381) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__382;    /* Address-exposed local */
  uint8_t var_name_tmp__383;    /* Address-exposed local */
  uint32_t var_name_tmp__384;    /* Address-exposed local */
  uint16_t var_name_tmp__385;    /* Address-exposed local */
  uint16_t var_name_tmp__386;    /* Address-exposed local */
  uint16_t var_name_tmp__387;    /* Address-exposed local */
  uint8_t var_name_tmp__388;
  uint8_t var_name_tmp__389;
  uint16_t var_name_tmp__390;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__391;
  uint16_t var_name_tmp__392;
  uint16_t var_name_tmp__393;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__394;
  uint16_t var_name_tmp__395;
  uint16_t var_name_tmp__396;
  uint16_t var_name_tmp__397;
  uint32_t var_name_tmp__398;

  var_name_tmp__382 = var_name_tmp__380;
  var_name_tmp__383 = var_name_tmp__381;
  var_name_tmp__384 = 0;
  var_name_tmp__385 = 0;
  var_name_tmp__386 = 0;
  var_name_tmp__387 = 0;
  var_name_tmp__388 = var_name_tmp__383;
  var_name_tmp__385 = (((uint16_t)(1 << ((((uint32_t)(uint8_t)var_name_tmp__388)) & 15))));
  var_name_tmp__389 = var_name_tmp__383;
  var_name_tmp__386 = (((uint16_t)(llvm_ashr_u32((((uint32_t)(uint8_t)var_name_tmp__389)), 4))));
  var_name_tmp__390 = var_name_tmp__386;
  var_name_tmp__386 = (((uint16_t)(1 << (((uint32_t)(uint16_t)var_name_tmp__390)))));
  var_name_tmp__391 = var_name_tmp__382;
  var_name_tmp__392 = *(volatile uint16_t*)((&var_name_tmp__391->field2));
  var_name_tmp__393 = var_name_tmp__386;
  var_name_tmp__387 = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__392)) & (((uint32_t)(uint16_t)var_name_tmp__393)))));
  var_name_tmp__394 = var_name_tmp__382;
  var_name_tmp__395 = *(volatile uint16_t*)((&var_name_tmp__394->field4));
  var_name_tmp__396 = var_name_tmp__385;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__395)) & (((uint32_t)(uint16_t)var_name_tmp__396))) != 0u)&1))) {
    goto var_name_tmp__399;
  } else {
    goto var_name_tmp__400;
  }

var_name_tmp__399:
  var_name_tmp__397 = var_name_tmp__387;
  if (((((((uint32_t)(uint16_t)var_name_tmp__397)) != 0u)&1))) {
    goto var_name_tmp__401;
  } else {
    goto var_name_tmp__400;
  }

var_name_tmp__401:
  var_name_tmp__384 = 1;
  goto var_name_tmp__402;

var_name_tmp__400:
  var_name_tmp__384 = 0;
  goto var_name_tmp__402;

var_name_tmp__402:
  var_name_tmp__398 = var_name_tmp__384;
  return var_name_tmp__398;
}


void SPI_I2S_ClearITPendingBit(struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__403, uint8_t var_name_tmp__404) {
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__405;    /* Address-exposed local */
  uint8_t var_name_tmp__406;    /* Address-exposed local */
  uint16_t var_name_tmp__407;    /* Address-exposed local */
  uint8_t var_name_tmp__408;
  uint16_t var_name_tmp__409;
  struct l_struct_struct_OC_SPI_TypeDef* var_name_tmp__410;

  var_name_tmp__405 = var_name_tmp__403;
  var_name_tmp__406 = var_name_tmp__404;
  var_name_tmp__407 = 0;
  var_name_tmp__408 = var_name_tmp__406;
  var_name_tmp__407 = (((uint16_t)(1 << ((((uint32_t)(uint8_t)var_name_tmp__408)) & 15))));
  var_name_tmp__409 = var_name_tmp__407;
  var_name_tmp__410 = var_name_tmp__405;
  *(volatile uint16_t*)((&var_name_tmp__410->field4)) = (((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__409))))));
}

