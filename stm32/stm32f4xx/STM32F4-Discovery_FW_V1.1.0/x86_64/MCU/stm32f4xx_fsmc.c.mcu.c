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
struct l_struct_struct_OC_FSMC_Bank1_TypeDef;
struct l_struct_struct_OC_FSMC_Bank1E_TypeDef;
struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef;
struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef;
struct l_struct_struct_OC_FSMC_Bank2_TypeDef;
struct l_struct_struct_OC_FSMC_Bank3_TypeDef;
struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef;
struct l_struct_struct_OC_FSMC_NANDInitTypeDef;
struct l_struct_struct_OC_FSMC_Bank4_TypeDef;
struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_array_8_uint32_t {
  uint32_t array[8];
};
struct l_struct_struct_OC_FSMC_Bank1_TypeDef {
  struct l_array_8_uint32_t field0;
};
struct l_array_7_uint32_t {
  uint32_t array[7];
};
struct l_struct_struct_OC_FSMC_Bank1E_TypeDef {
  struct l_array_7_uint32_t field0;
};
struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint32_t field6;
};
struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef {
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
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* field13;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* field14;
};
struct l_struct_struct_OC_FSMC_Bank2_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};
struct l_struct_struct_OC_FSMC_Bank3_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};
struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_FSMC_NANDInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint32_t field6;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* field7;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* field8;
};
struct l_struct_struct_OC_FSMC_Bank4_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
};
struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* field3;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* field4;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* field5;
};

/* Function Declarations */
void FSMC_NORSRAMDeInit(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NORSRAMInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NORSRAMStructInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NORSRAMCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NANDDeInit(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NANDInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NANDStructInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NANDCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_NANDECCCmd(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FSMC_GetECC(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_PCCARDDeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_PCCARDInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_PCCARDStructInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_PCCARDCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_ITConfig(uint32_t, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FSMC_GetFlagStatus(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_ClearFlag(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FSMC_GetITStatus(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FSMC_ClearITPendingBit(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void FSMC_NORSRAMDeInit(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == 0u)&1))) {
    goto var_name_tmp__8;
  } else {
    goto var_name_tmp__9;
  }

var_name_tmp__8:
  var_name_tmp__4 = var_name_tmp__2;
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__4)))])) = 12507;
  goto var_name_tmp__10;

var_name_tmp__9:
  var_name_tmp__5 = var_name_tmp__2;
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__5)))])) = 12498;
  goto var_name_tmp__10;

var_name_tmp__10:
  var_name_tmp__6 = var_name_tmp__2;
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(llvm_add_u32(var_name_tmp__6, 1)))))])) = 268435455;
  var_name_tmp__7 = var_name_tmp__2;
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__7)))])) = 268435455;
}


void FSMC_NORSRAMInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__11) {
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__12;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__13;
  uint32_t var_name_tmp__14;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__15;
  uint32_t var_name_tmp__16;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__17;
  uint32_t var_name_tmp__18;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__19;
  uint32_t var_name_tmp__20;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__21;
  uint32_t var_name_tmp__22;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__23;
  uint32_t var_name_tmp__24;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__25;
  uint32_t var_name_tmp__26;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__27;
  uint32_t var_name_tmp__28;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__29;
  uint32_t var_name_tmp__30;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__31;
  uint32_t var_name_tmp__32;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__33;
  uint32_t var_name_tmp__34;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__35;
  uint32_t var_name_tmp__36;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__37;
  uint32_t var_name_tmp__38;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__39;
  uint32_t var_name_tmp__40;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__41;
  uint32_t var_name_tmp__42;
  uint32_t* var_name_tmp__43;
  uint32_t var_name_tmp__44;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__45;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__46;
  uint32_t var_name_tmp__47;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__48;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__49;
  uint32_t var_name_tmp__50;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__51;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__52;
  uint32_t var_name_tmp__53;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__54;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__55;
  uint32_t var_name_tmp__56;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__57;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__58;
  uint32_t var_name_tmp__59;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__60;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__61;
  uint32_t var_name_tmp__62;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__63;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__64;
  uint32_t var_name_tmp__65;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__66;
  uint32_t var_name_tmp__67;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__68;
  uint32_t var_name_tmp__69;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__70;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__71;
  uint32_t var_name_tmp__72;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__73;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__74;
  uint32_t var_name_tmp__75;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__76;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__77;
  uint32_t var_name_tmp__78;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__79;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__80;
  uint32_t var_name_tmp__81;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__82;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__83;
  uint32_t var_name_tmp__84;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__85;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__86;
  uint32_t var_name_tmp__87;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__88;
  uint32_t var_name_tmp__89;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__90;
  uint32_t var_name_tmp__91;

  var_name_tmp__12 = var_name_tmp__11;
  var_name_tmp__13 = var_name_tmp__12;
  var_name_tmp__14 = *((&var_name_tmp__13->field1));
  var_name_tmp__15 = var_name_tmp__12;
  var_name_tmp__16 = *((&var_name_tmp__15->field2));
  var_name_tmp__17 = var_name_tmp__12;
  var_name_tmp__18 = *((&var_name_tmp__17->field3));
  var_name_tmp__19 = var_name_tmp__12;
  var_name_tmp__20 = *((&var_name_tmp__19->field4));
  var_name_tmp__21 = var_name_tmp__12;
  var_name_tmp__22 = *((&var_name_tmp__21->field5));
  var_name_tmp__23 = var_name_tmp__12;
  var_name_tmp__24 = *((&var_name_tmp__23->field6));
  var_name_tmp__25 = var_name_tmp__12;
  var_name_tmp__26 = *((&var_name_tmp__25->field7));
  var_name_tmp__27 = var_name_tmp__12;
  var_name_tmp__28 = *((&var_name_tmp__27->field8));
  var_name_tmp__29 = var_name_tmp__12;
  var_name_tmp__30 = *((&var_name_tmp__29->field9));
  var_name_tmp__31 = var_name_tmp__12;
  var_name_tmp__32 = *((&var_name_tmp__31->field10));
  var_name_tmp__33 = var_name_tmp__12;
  var_name_tmp__34 = *((&var_name_tmp__33->field11));
  var_name_tmp__35 = var_name_tmp__12;
  var_name_tmp__36 = *((&var_name_tmp__35->field12));
  var_name_tmp__37 = var_name_tmp__12;
  var_name_tmp__38 = *((&var_name_tmp__37->field0));
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__38)))])) = (((((((((((var_name_tmp__14 | var_name_tmp__16) | var_name_tmp__18) | var_name_tmp__20) | var_name_tmp__22) | var_name_tmp__24) | var_name_tmp__26) | var_name_tmp__28) | var_name_tmp__30) | var_name_tmp__32) | var_name_tmp__34) | var_name_tmp__36);
  var_name_tmp__39 = var_name_tmp__12;
  var_name_tmp__40 = *((&var_name_tmp__39->field2));
  if ((((var_name_tmp__40 == 8u)&1))) {
    goto var_name_tmp__92;
  } else {
    goto var_name_tmp__93;
  }

var_name_tmp__92:
  var_name_tmp__41 = var_name_tmp__12;
  var_name_tmp__42 = *((&var_name_tmp__41->field0));
  var_name_tmp__43 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__42)))]);
  var_name_tmp__44 = *(volatile uint32_t*)var_name_tmp__43;
  *(volatile uint32_t*)var_name_tmp__43 = (var_name_tmp__44 | 64);
  goto var_name_tmp__93;

var_name_tmp__93:
  var_name_tmp__45 = var_name_tmp__12;
  var_name_tmp__46 = *((&var_name_tmp__45->field13));
  var_name_tmp__47 = *((&var_name_tmp__46->field0));
  var_name_tmp__48 = var_name_tmp__12;
  var_name_tmp__49 = *((&var_name_tmp__48->field13));
  var_name_tmp__50 = *((&var_name_tmp__49->field1));
  var_name_tmp__51 = var_name_tmp__12;
  var_name_tmp__52 = *((&var_name_tmp__51->field13));
  var_name_tmp__53 = *((&var_name_tmp__52->field2));
  var_name_tmp__54 = var_name_tmp__12;
  var_name_tmp__55 = *((&var_name_tmp__54->field13));
  var_name_tmp__56 = *((&var_name_tmp__55->field3));
  var_name_tmp__57 = var_name_tmp__12;
  var_name_tmp__58 = *((&var_name_tmp__57->field13));
  var_name_tmp__59 = *((&var_name_tmp__58->field4));
  var_name_tmp__60 = var_name_tmp__12;
  var_name_tmp__61 = *((&var_name_tmp__60->field13));
  var_name_tmp__62 = *((&var_name_tmp__61->field5));
  var_name_tmp__63 = var_name_tmp__12;
  var_name_tmp__64 = *((&var_name_tmp__63->field13));
  var_name_tmp__65 = *((&var_name_tmp__64->field6));
  var_name_tmp__66 = var_name_tmp__12;
  var_name_tmp__67 = *((&var_name_tmp__66->field0));
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(llvm_add_u32(var_name_tmp__67, 1)))))])) = ((((((var_name_tmp__47 | (var_name_tmp__50 << 4)) | (var_name_tmp__53 << 8)) | (var_name_tmp__56 << 16)) | (var_name_tmp__59 << 20)) | (var_name_tmp__62 << 24)) | var_name_tmp__65);
  var_name_tmp__68 = var_name_tmp__12;
  var_name_tmp__69 = *((&var_name_tmp__68->field11));
  if ((((var_name_tmp__69 == 16384u)&1))) {
    goto var_name_tmp__94;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__94:
  var_name_tmp__70 = var_name_tmp__12;
  var_name_tmp__71 = *((&var_name_tmp__70->field14));
  var_name_tmp__72 = *((&var_name_tmp__71->field0));
  var_name_tmp__73 = var_name_tmp__12;
  var_name_tmp__74 = *((&var_name_tmp__73->field14));
  var_name_tmp__75 = *((&var_name_tmp__74->field1));
  var_name_tmp__76 = var_name_tmp__12;
  var_name_tmp__77 = *((&var_name_tmp__76->field14));
  var_name_tmp__78 = *((&var_name_tmp__77->field2));
  var_name_tmp__79 = var_name_tmp__12;
  var_name_tmp__80 = *((&var_name_tmp__79->field14));
  var_name_tmp__81 = *((&var_name_tmp__80->field4));
  var_name_tmp__82 = var_name_tmp__12;
  var_name_tmp__83 = *((&var_name_tmp__82->field14));
  var_name_tmp__84 = *((&var_name_tmp__83->field5));
  var_name_tmp__85 = var_name_tmp__12;
  var_name_tmp__86 = *((&var_name_tmp__85->field14));
  var_name_tmp__87 = *((&var_name_tmp__86->field6));
  var_name_tmp__88 = var_name_tmp__12;
  var_name_tmp__89 = *((&var_name_tmp__88->field0));
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__89)))])) = (((((var_name_tmp__72 | (var_name_tmp__75 << 4)) | (var_name_tmp__78 << 8)) | (var_name_tmp__81 << 20)) | (var_name_tmp__84 << 24)) | var_name_tmp__87);
  goto var_name_tmp__96;

var_name_tmp__95:
  var_name_tmp__90 = var_name_tmp__12;
  var_name_tmp__91 = *((&var_name_tmp__90->field0));
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__91)))])) = 268435455;
  goto var_name_tmp__96;

var_name_tmp__96:
  return;
}


void FSMC_NORSRAMStructInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__97) {
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__98;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__99;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__100;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__101;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__102;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__103;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__104;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__105;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__106;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__107;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__108;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__109;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__112;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__113;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__114;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__115;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__116;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__117;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__118;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__119;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__120;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__121;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__122;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__123;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__124;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__125;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__126;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__127;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__128;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__129;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__130;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__131;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__132;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__133;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__134;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__135;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__136;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__137;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__138;
  struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef* var_name_tmp__139;

  var_name_tmp__98 = var_name_tmp__97;
  var_name_tmp__99 = var_name_tmp__98;
  *((&var_name_tmp__99->field0)) = 0;
  var_name_tmp__100 = var_name_tmp__98;
  *((&var_name_tmp__100->field1)) = 2;
  var_name_tmp__101 = var_name_tmp__98;
  *((&var_name_tmp__101->field2)) = 0;
  var_name_tmp__102 = var_name_tmp__98;
  *((&var_name_tmp__102->field3)) = 0;
  var_name_tmp__103 = var_name_tmp__98;
  *((&var_name_tmp__103->field4)) = 0;
  var_name_tmp__104 = var_name_tmp__98;
  *((&var_name_tmp__104->field5)) = 0;
  var_name_tmp__105 = var_name_tmp__98;
  *((&var_name_tmp__105->field6)) = 0;
  var_name_tmp__106 = var_name_tmp__98;
  *((&var_name_tmp__106->field7)) = 0;
  var_name_tmp__107 = var_name_tmp__98;
  *((&var_name_tmp__107->field8)) = 0;
  var_name_tmp__108 = var_name_tmp__98;
  *((&var_name_tmp__108->field9)) = 4096;
  var_name_tmp__109 = var_name_tmp__98;
  *((&var_name_tmp__109->field10)) = 8192;
  var_name_tmp__110 = var_name_tmp__98;
  *((&var_name_tmp__110->field11)) = 0;
  var_name_tmp__111 = var_name_tmp__98;
  *((&var_name_tmp__111->field12)) = 0;
  var_name_tmp__112 = var_name_tmp__98;
  var_name_tmp__113 = *((&var_name_tmp__112->field13));
  *((&var_name_tmp__113->field0)) = 15;
  var_name_tmp__114 = var_name_tmp__98;
  var_name_tmp__115 = *((&var_name_tmp__114->field13));
  *((&var_name_tmp__115->field1)) = 15;
  var_name_tmp__116 = var_name_tmp__98;
  var_name_tmp__117 = *((&var_name_tmp__116->field13));
  *((&var_name_tmp__117->field2)) = 255;
  var_name_tmp__118 = var_name_tmp__98;
  var_name_tmp__119 = *((&var_name_tmp__118->field13));
  *((&var_name_tmp__119->field3)) = 15;
  var_name_tmp__120 = var_name_tmp__98;
  var_name_tmp__121 = *((&var_name_tmp__120->field13));
  *((&var_name_tmp__121->field4)) = 15;
  var_name_tmp__122 = var_name_tmp__98;
  var_name_tmp__123 = *((&var_name_tmp__122->field13));
  *((&var_name_tmp__123->field5)) = 15;
  var_name_tmp__124 = var_name_tmp__98;
  var_name_tmp__125 = *((&var_name_tmp__124->field13));
  *((&var_name_tmp__125->field6)) = 0;
  var_name_tmp__126 = var_name_tmp__98;
  var_name_tmp__127 = *((&var_name_tmp__126->field14));
  *((&var_name_tmp__127->field0)) = 15;
  var_name_tmp__128 = var_name_tmp__98;
  var_name_tmp__129 = *((&var_name_tmp__128->field14));
  *((&var_name_tmp__129->field1)) = 15;
  var_name_tmp__130 = var_name_tmp__98;
  var_name_tmp__131 = *((&var_name_tmp__130->field14));
  *((&var_name_tmp__131->field2)) = 255;
  var_name_tmp__132 = var_name_tmp__98;
  var_name_tmp__133 = *((&var_name_tmp__132->field14));
  *((&var_name_tmp__133->field3)) = 15;
  var_name_tmp__134 = var_name_tmp__98;
  var_name_tmp__135 = *((&var_name_tmp__134->field14));
  *((&var_name_tmp__135->field4)) = 15;
  var_name_tmp__136 = var_name_tmp__98;
  var_name_tmp__137 = *((&var_name_tmp__136->field14));
  *((&var_name_tmp__137->field5)) = 15;
  var_name_tmp__138 = var_name_tmp__98;
  var_name_tmp__139 = *((&var_name_tmp__138->field14));
  *((&var_name_tmp__139->field6)) = 0;
}


void FSMC_NORSRAMCmd(uint32_t var_name_tmp__140, uint32_t var_name_tmp__141) {
  uint32_t var_name_tmp__142;    /* Address-exposed local */
  uint32_t var_name_tmp__143;    /* Address-exposed local */
  uint32_t var_name_tmp__144;
  uint32_t var_name_tmp__145;
  uint32_t* var_name_tmp__146;
  uint32_t var_name_tmp__147;
  uint32_t var_name_tmp__148;
  uint32_t* var_name_tmp__149;
  uint32_t var_name_tmp__150;

  var_name_tmp__142 = var_name_tmp__140;
  var_name_tmp__143 = var_name_tmp__141;
  var_name_tmp__144 = var_name_tmp__143;
  if ((((var_name_tmp__144 != 0u)&1))) {
    goto var_name_tmp__151;
  } else {
    goto var_name_tmp__152;
  }

var_name_tmp__151:
  var_name_tmp__145 = var_name_tmp__142;
  var_name_tmp__146 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__145)))]);
  var_name_tmp__147 = *(volatile uint32_t*)var_name_tmp__146;
  *(volatile uint32_t*)var_name_tmp__146 = (var_name_tmp__147 | 1);
  goto var_name_tmp__153;

var_name_tmp__152:
  var_name_tmp__148 = var_name_tmp__142;
  var_name_tmp__149 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__148)))]);
  var_name_tmp__150 = *(volatile uint32_t*)var_name_tmp__149;
  *(volatile uint32_t*)var_name_tmp__149 = (var_name_tmp__150 & 1048574);
  goto var_name_tmp__153;

var_name_tmp__153:
  return;
}


void FSMC_NANDDeInit(uint32_t var_name_tmp__154) {
  uint32_t var_name_tmp__155;    /* Address-exposed local */
  uint32_t var_name_tmp__156;

  var_name_tmp__155 = var_name_tmp__154;
  var_name_tmp__156 = var_name_tmp__155;
  if ((((var_name_tmp__156 == 16u)&1))) {
    goto var_name_tmp__157;
  } else {
    goto var_name_tmp__158;
  }

var_name_tmp__157:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = 24;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1)) = 64;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field2)) = -50529028;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field3)) = -50529028;
  goto var_name_tmp__159;

var_name_tmp__158:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = 24;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1)) = 64;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field2)) = -50529028;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field3)) = -50529028;
  goto var_name_tmp__159;

var_name_tmp__159:
  return;
}


void FSMC_NANDInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__160) {
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__161;    /* Address-exposed local */
  uint32_t var_name_tmp__162;    /* Address-exposed local */
  uint32_t var_name_tmp__163;    /* Address-exposed local */
  uint32_t var_name_tmp__164;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__165;
  uint32_t var_name_tmp__166;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__167;
  uint32_t var_name_tmp__168;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__169;
  uint32_t var_name_tmp__170;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__171;
  uint32_t var_name_tmp__172;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__173;
  uint32_t var_name_tmp__174;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__175;
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__177;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__178;
  uint32_t var_name_tmp__179;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__180;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__181;
  uint32_t var_name_tmp__182;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__183;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__184;
  uint32_t var_name_tmp__185;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__186;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__187;
  uint32_t var_name_tmp__188;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__189;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__190;
  uint32_t var_name_tmp__191;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__192;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__193;
  uint32_t var_name_tmp__194;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__195;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__196;
  uint32_t var_name_tmp__197;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__198;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__199;
  uint32_t var_name_tmp__200;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__201;
  uint32_t var_name_tmp__202;
  uint32_t var_name_tmp__203;
  uint32_t var_name_tmp__204;
  uint32_t var_name_tmp__205;
  uint32_t var_name_tmp__206;
  uint32_t var_name_tmp__207;
  uint32_t var_name_tmp__208;

  var_name_tmp__161 = var_name_tmp__160;
  var_name_tmp__162 = 0;
  var_name_tmp__163 = 0;
  var_name_tmp__164 = 0;
  var_name_tmp__165 = var_name_tmp__161;
  var_name_tmp__166 = *((&var_name_tmp__165->field1));
  var_name_tmp__167 = var_name_tmp__161;
  var_name_tmp__168 = *((&var_name_tmp__167->field2));
  var_name_tmp__169 = var_name_tmp__161;
  var_name_tmp__170 = *((&var_name_tmp__169->field3));
  var_name_tmp__171 = var_name_tmp__161;
  var_name_tmp__172 = *((&var_name_tmp__171->field4));
  var_name_tmp__173 = var_name_tmp__161;
  var_name_tmp__174 = *((&var_name_tmp__173->field5));
  var_name_tmp__175 = var_name_tmp__161;
  var_name_tmp__176 = *((&var_name_tmp__175->field6));
  var_name_tmp__162 = ((((((var_name_tmp__166 | 8) | var_name_tmp__168) | var_name_tmp__170) | var_name_tmp__172) | (var_name_tmp__174 << 9)) | (var_name_tmp__176 << 13));
  var_name_tmp__177 = var_name_tmp__161;
  var_name_tmp__178 = *((&var_name_tmp__177->field7));
  var_name_tmp__179 = *((&var_name_tmp__178->field0));
  var_name_tmp__180 = var_name_tmp__161;
  var_name_tmp__181 = *((&var_name_tmp__180->field7));
  var_name_tmp__182 = *((&var_name_tmp__181->field1));
  var_name_tmp__183 = var_name_tmp__161;
  var_name_tmp__184 = *((&var_name_tmp__183->field7));
  var_name_tmp__185 = *((&var_name_tmp__184->field2));
  var_name_tmp__186 = var_name_tmp__161;
  var_name_tmp__187 = *((&var_name_tmp__186->field7));
  var_name_tmp__188 = *((&var_name_tmp__187->field3));
  var_name_tmp__163 = (((var_name_tmp__179 | (var_name_tmp__182 << 8)) | (var_name_tmp__185 << 16)) | (var_name_tmp__188 << 24));
  var_name_tmp__189 = var_name_tmp__161;
  var_name_tmp__190 = *((&var_name_tmp__189->field8));
  var_name_tmp__191 = *((&var_name_tmp__190->field0));
  var_name_tmp__192 = var_name_tmp__161;
  var_name_tmp__193 = *((&var_name_tmp__192->field8));
  var_name_tmp__194 = *((&var_name_tmp__193->field1));
  var_name_tmp__195 = var_name_tmp__161;
  var_name_tmp__196 = *((&var_name_tmp__195->field8));
  var_name_tmp__197 = *((&var_name_tmp__196->field2));
  var_name_tmp__198 = var_name_tmp__161;
  var_name_tmp__199 = *((&var_name_tmp__198->field8));
  var_name_tmp__200 = *((&var_name_tmp__199->field3));
  var_name_tmp__164 = (((var_name_tmp__191 | (var_name_tmp__194 << 8)) | (var_name_tmp__197 << 16)) | (var_name_tmp__200 << 24));
  var_name_tmp__201 = var_name_tmp__161;
  var_name_tmp__202 = *((&var_name_tmp__201->field0));
  if ((((var_name_tmp__202 == 16u)&1))) {
    goto var_name_tmp__209;
  } else {
    goto var_name_tmp__210;
  }

var_name_tmp__209:
  var_name_tmp__203 = var_name_tmp__162;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = var_name_tmp__203;
  var_name_tmp__204 = var_name_tmp__163;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field2)) = var_name_tmp__204;
  var_name_tmp__205 = var_name_tmp__164;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field3)) = var_name_tmp__205;
  goto var_name_tmp__211;

var_name_tmp__210:
  var_name_tmp__206 = var_name_tmp__162;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = var_name_tmp__206;
  var_name_tmp__207 = var_name_tmp__163;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field2)) = var_name_tmp__207;
  var_name_tmp__208 = var_name_tmp__164;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field3)) = var_name_tmp__208;
  goto var_name_tmp__211;

var_name_tmp__211:
  return;
}


void FSMC_NANDStructInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__212) {
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__213;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__214;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__215;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__216;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__217;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__218;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__219;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__220;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__221;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__222;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__223;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__224;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__225;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__226;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__227;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__228;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__229;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__230;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__231;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__232;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__233;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__234;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__235;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__236;

  var_name_tmp__213 = var_name_tmp__212;
  var_name_tmp__214 = var_name_tmp__213;
  *((&var_name_tmp__214->field0)) = 16;
  var_name_tmp__215 = var_name_tmp__213;
  *((&var_name_tmp__215->field1)) = 0;
  var_name_tmp__216 = var_name_tmp__213;
  *((&var_name_tmp__216->field2)) = 0;
  var_name_tmp__217 = var_name_tmp__213;
  *((&var_name_tmp__217->field3)) = 0;
  var_name_tmp__218 = var_name_tmp__213;
  *((&var_name_tmp__218->field4)) = 0;
  var_name_tmp__219 = var_name_tmp__213;
  *((&var_name_tmp__219->field5)) = 0;
  var_name_tmp__220 = var_name_tmp__213;
  *((&var_name_tmp__220->field6)) = 0;
  var_name_tmp__221 = var_name_tmp__213;
  var_name_tmp__222 = *((&var_name_tmp__221->field7));
  *((&var_name_tmp__222->field0)) = 252;
  var_name_tmp__223 = var_name_tmp__213;
  var_name_tmp__224 = *((&var_name_tmp__223->field7));
  *((&var_name_tmp__224->field1)) = 252;
  var_name_tmp__225 = var_name_tmp__213;
  var_name_tmp__226 = *((&var_name_tmp__225->field7));
  *((&var_name_tmp__226->field2)) = 252;
  var_name_tmp__227 = var_name_tmp__213;
  var_name_tmp__228 = *((&var_name_tmp__227->field7));
  *((&var_name_tmp__228->field3)) = 252;
  var_name_tmp__229 = var_name_tmp__213;
  var_name_tmp__230 = *((&var_name_tmp__229->field8));
  *((&var_name_tmp__230->field0)) = 252;
  var_name_tmp__231 = var_name_tmp__213;
  var_name_tmp__232 = *((&var_name_tmp__231->field8));
  *((&var_name_tmp__232->field1)) = 252;
  var_name_tmp__233 = var_name_tmp__213;
  var_name_tmp__234 = *((&var_name_tmp__233->field8));
  *((&var_name_tmp__234->field2)) = 252;
  var_name_tmp__235 = var_name_tmp__213;
  var_name_tmp__236 = *((&var_name_tmp__235->field8));
  *((&var_name_tmp__236->field3)) = 252;
}


void FSMC_NANDCmd(uint32_t var_name_tmp__237, uint32_t var_name_tmp__238) {
  uint32_t var_name_tmp__239;    /* Address-exposed local */
  uint32_t var_name_tmp__240;    /* Address-exposed local */
  uint32_t var_name_tmp__241;
  uint32_t var_name_tmp__242;
  uint32_t var_name_tmp__243;
  uint32_t var_name_tmp__244;
  uint32_t var_name_tmp__245;
  uint32_t var_name_tmp__246;
  uint32_t var_name_tmp__247;

  var_name_tmp__239 = var_name_tmp__237;
  var_name_tmp__240 = var_name_tmp__238;
  var_name_tmp__241 = var_name_tmp__240;
  if ((((var_name_tmp__241 != 0u)&1))) {
    goto var_name_tmp__248;
  } else {
    goto var_name_tmp__249;
  }

var_name_tmp__248:
  var_name_tmp__242 = var_name_tmp__239;
  if ((((var_name_tmp__242 == 16u)&1))) {
    goto var_name_tmp__250;
  } else {
    goto var_name_tmp__251;
  }

var_name_tmp__250:
  var_name_tmp__243 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = (var_name_tmp__243 | 4);
  goto var_name_tmp__252;

var_name_tmp__251:
  var_name_tmp__244 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = (var_name_tmp__244 | 4);
  goto var_name_tmp__252;

var_name_tmp__252:
  goto var_name_tmp__253;

var_name_tmp__249:
  var_name_tmp__245 = var_name_tmp__239;
  if ((((var_name_tmp__245 == 16u)&1))) {
    goto var_name_tmp__254;
  } else {
    goto var_name_tmp__255;
  }

var_name_tmp__254:
  var_name_tmp__246 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = (var_name_tmp__246 & 1048571);
  goto var_name_tmp__256;

var_name_tmp__255:
  var_name_tmp__247 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = (var_name_tmp__247 & 1048571);
  goto var_name_tmp__256;

var_name_tmp__256:
  goto var_name_tmp__253;

var_name_tmp__253:
  return;
}


void FSMC_NANDECCCmd(uint32_t var_name_tmp__257, uint32_t var_name_tmp__258) {
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  uint32_t var_name_tmp__260;    /* Address-exposed local */
  uint32_t var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint32_t var_name_tmp__263;
  uint32_t var_name_tmp__264;
  uint32_t var_name_tmp__265;
  uint32_t var_name_tmp__266;
  uint32_t var_name_tmp__267;

  var_name_tmp__259 = var_name_tmp__257;
  var_name_tmp__260 = var_name_tmp__258;
  var_name_tmp__261 = var_name_tmp__260;
  if ((((var_name_tmp__261 != 0u)&1))) {
    goto var_name_tmp__268;
  } else {
    goto var_name_tmp__269;
  }

var_name_tmp__268:
  var_name_tmp__262 = var_name_tmp__259;
  if ((((var_name_tmp__262 == 16u)&1))) {
    goto var_name_tmp__270;
  } else {
    goto var_name_tmp__271;
  }

var_name_tmp__270:
  var_name_tmp__263 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = (var_name_tmp__263 | 64);
  goto var_name_tmp__272;

var_name_tmp__271:
  var_name_tmp__264 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = (var_name_tmp__264 | 64);
  goto var_name_tmp__272;

var_name_tmp__272:
  goto var_name_tmp__273;

var_name_tmp__269:
  var_name_tmp__265 = var_name_tmp__259;
  if ((((var_name_tmp__265 == 16u)&1))) {
    goto var_name_tmp__274;
  } else {
    goto var_name_tmp__275;
  }

var_name_tmp__274:
  var_name_tmp__266 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field0)) = (var_name_tmp__266 & 1048511);
  goto var_name_tmp__276;

var_name_tmp__275:
  var_name_tmp__267 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field0)) = (var_name_tmp__267 & 1048511);
  goto var_name_tmp__276;

var_name_tmp__276:
  goto var_name_tmp__273;

var_name_tmp__273:
  return;
}


uint32_t FSMC_GetECC(uint32_t var_name_tmp__277) {
  uint32_t var_name_tmp__278;    /* Address-exposed local */
  uint32_t var_name_tmp__279;    /* Address-exposed local */
  uint32_t var_name_tmp__280;
  uint32_t var_name_tmp__281;
  uint32_t var_name_tmp__282;
  uint32_t var_name_tmp__283;

  var_name_tmp__278 = var_name_tmp__277;
  var_name_tmp__279 = 0;
  var_name_tmp__280 = var_name_tmp__278;
  if ((((var_name_tmp__280 == 16u)&1))) {
    goto var_name_tmp__284;
  } else {
    goto var_name_tmp__285;
  }

var_name_tmp__284:
  var_name_tmp__281 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field5));
  var_name_tmp__279 = var_name_tmp__281;
  goto var_name_tmp__286;

var_name_tmp__285:
  var_name_tmp__282 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field5));
  var_name_tmp__279 = var_name_tmp__282;
  goto var_name_tmp__286;

var_name_tmp__286:
  var_name_tmp__283 = var_name_tmp__279;
  return var_name_tmp__283;
}


void FSMC_PCCARDDeInit(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0)) = 24;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field2)) = -50529028;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field3)) = -50529028;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field4)) = -50529028;
}


void FSMC_PCCARDInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__287) {
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__288;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__289;
  uint32_t var_name_tmp__290;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__291;
  uint32_t var_name_tmp__292;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__293;
  uint32_t var_name_tmp__294;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__295;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__296;
  uint32_t var_name_tmp__297;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__298;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__299;
  uint32_t var_name_tmp__300;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__301;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__302;
  uint32_t var_name_tmp__303;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__304;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__305;
  uint32_t var_name_tmp__306;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__307;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__308;
  uint32_t var_name_tmp__309;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__310;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__311;
  uint32_t var_name_tmp__312;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__313;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__314;
  uint32_t var_name_tmp__315;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__316;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__317;
  uint32_t var_name_tmp__318;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__319;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__320;
  uint32_t var_name_tmp__321;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__322;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__323;
  uint32_t var_name_tmp__324;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__325;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__326;
  uint32_t var_name_tmp__327;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__328;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__329;
  uint32_t var_name_tmp__330;

  var_name_tmp__288 = var_name_tmp__287;
  var_name_tmp__289 = var_name_tmp__288;
  var_name_tmp__290 = *((&var_name_tmp__289->field0));
  var_name_tmp__291 = var_name_tmp__288;
  var_name_tmp__292 = *((&var_name_tmp__291->field1));
  var_name_tmp__293 = var_name_tmp__288;
  var_name_tmp__294 = *((&var_name_tmp__293->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0)) = (((var_name_tmp__290 | 16) | (var_name_tmp__292 << 9)) | (var_name_tmp__294 << 13));
  var_name_tmp__295 = var_name_tmp__288;
  var_name_tmp__296 = *((&var_name_tmp__295->field3));
  var_name_tmp__297 = *((&var_name_tmp__296->field0));
  var_name_tmp__298 = var_name_tmp__288;
  var_name_tmp__299 = *((&var_name_tmp__298->field3));
  var_name_tmp__300 = *((&var_name_tmp__299->field1));
  var_name_tmp__301 = var_name_tmp__288;
  var_name_tmp__302 = *((&var_name_tmp__301->field3));
  var_name_tmp__303 = *((&var_name_tmp__302->field2));
  var_name_tmp__304 = var_name_tmp__288;
  var_name_tmp__305 = *((&var_name_tmp__304->field3));
  var_name_tmp__306 = *((&var_name_tmp__305->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field2)) = (((var_name_tmp__297 | (var_name_tmp__300 << 8)) | (var_name_tmp__303 << 16)) | (var_name_tmp__306 << 24));
  var_name_tmp__307 = var_name_tmp__288;
  var_name_tmp__308 = *((&var_name_tmp__307->field4));
  var_name_tmp__309 = *((&var_name_tmp__308->field0));
  var_name_tmp__310 = var_name_tmp__288;
  var_name_tmp__311 = *((&var_name_tmp__310->field4));
  var_name_tmp__312 = *((&var_name_tmp__311->field1));
  var_name_tmp__313 = var_name_tmp__288;
  var_name_tmp__314 = *((&var_name_tmp__313->field4));
  var_name_tmp__315 = *((&var_name_tmp__314->field2));
  var_name_tmp__316 = var_name_tmp__288;
  var_name_tmp__317 = *((&var_name_tmp__316->field4));
  var_name_tmp__318 = *((&var_name_tmp__317->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field3)) = (((var_name_tmp__309 | (var_name_tmp__312 << 8)) | (var_name_tmp__315 << 16)) | (var_name_tmp__318 << 24));
  var_name_tmp__319 = var_name_tmp__288;
  var_name_tmp__320 = *((&var_name_tmp__319->field5));
  var_name_tmp__321 = *((&var_name_tmp__320->field0));
  var_name_tmp__322 = var_name_tmp__288;
  var_name_tmp__323 = *((&var_name_tmp__322->field5));
  var_name_tmp__324 = *((&var_name_tmp__323->field1));
  var_name_tmp__325 = var_name_tmp__288;
  var_name_tmp__326 = *((&var_name_tmp__325->field5));
  var_name_tmp__327 = *((&var_name_tmp__326->field2));
  var_name_tmp__328 = var_name_tmp__288;
  var_name_tmp__329 = *((&var_name_tmp__328->field5));
  var_name_tmp__330 = *((&var_name_tmp__329->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field4)) = (((var_name_tmp__321 | (var_name_tmp__324 << 8)) | (var_name_tmp__327 << 16)) | (var_name_tmp__330 << 24));
}


void FSMC_PCCARDStructInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__331) {
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__332;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__333;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__334;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__335;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__336;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__337;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__338;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__339;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__340;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__341;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__342;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__343;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__344;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__345;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__346;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__347;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__348;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__349;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__350;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__351;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__352;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__353;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__354;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__355;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__356;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__357;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__358;
  struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef* var_name_tmp__359;

  var_name_tmp__332 = var_name_tmp__331;
  var_name_tmp__333 = var_name_tmp__332;
  *((&var_name_tmp__333->field0)) = 0;
  var_name_tmp__334 = var_name_tmp__332;
  *((&var_name_tmp__334->field1)) = 0;
  var_name_tmp__335 = var_name_tmp__332;
  *((&var_name_tmp__335->field2)) = 0;
  var_name_tmp__336 = var_name_tmp__332;
  var_name_tmp__337 = *((&var_name_tmp__336->field3));
  *((&var_name_tmp__337->field0)) = 252;
  var_name_tmp__338 = var_name_tmp__332;
  var_name_tmp__339 = *((&var_name_tmp__338->field3));
  *((&var_name_tmp__339->field1)) = 252;
  var_name_tmp__340 = var_name_tmp__332;
  var_name_tmp__341 = *((&var_name_tmp__340->field3));
  *((&var_name_tmp__341->field2)) = 252;
  var_name_tmp__342 = var_name_tmp__332;
  var_name_tmp__343 = *((&var_name_tmp__342->field3));
  *((&var_name_tmp__343->field3)) = 252;
  var_name_tmp__344 = var_name_tmp__332;
  var_name_tmp__345 = *((&var_name_tmp__344->field4));
  *((&var_name_tmp__345->field0)) = 252;
  var_name_tmp__346 = var_name_tmp__332;
  var_name_tmp__347 = *((&var_name_tmp__346->field4));
  *((&var_name_tmp__347->field1)) = 252;
  var_name_tmp__348 = var_name_tmp__332;
  var_name_tmp__349 = *((&var_name_tmp__348->field4));
  *((&var_name_tmp__349->field2)) = 252;
  var_name_tmp__350 = var_name_tmp__332;
  var_name_tmp__351 = *((&var_name_tmp__350->field4));
  *((&var_name_tmp__351->field3)) = 252;
  var_name_tmp__352 = var_name_tmp__332;
  var_name_tmp__353 = *((&var_name_tmp__352->field5));
  *((&var_name_tmp__353->field0)) = 252;
  var_name_tmp__354 = var_name_tmp__332;
  var_name_tmp__355 = *((&var_name_tmp__354->field5));
  *((&var_name_tmp__355->field1)) = 252;
  var_name_tmp__356 = var_name_tmp__332;
  var_name_tmp__357 = *((&var_name_tmp__356->field5));
  *((&var_name_tmp__357->field2)) = 252;
  var_name_tmp__358 = var_name_tmp__332;
  var_name_tmp__359 = *((&var_name_tmp__358->field5));
  *((&var_name_tmp__359->field3)) = 252;
}


void FSMC_PCCARDCmd(uint32_t var_name_tmp__360) {
  uint32_t var_name_tmp__361;    /* Address-exposed local */
  uint32_t var_name_tmp__362;
  uint32_t var_name_tmp__363;
  uint32_t var_name_tmp__364;

  var_name_tmp__361 = var_name_tmp__360;
  var_name_tmp__362 = var_name_tmp__361;
  if ((((var_name_tmp__362 != 0u)&1))) {
    goto var_name_tmp__365;
  } else {
    goto var_name_tmp__366;
  }

var_name_tmp__365:
  var_name_tmp__363 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0)) = (var_name_tmp__363 | 4);
  goto var_name_tmp__367;

var_name_tmp__366:
  var_name_tmp__364 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field0)) = (var_name_tmp__364 & 1048571);
  goto var_name_tmp__367;

var_name_tmp__367:
  return;
}


void FSMC_ITConfig(uint32_t var_name_tmp__368, uint32_t var_name_tmp__369, uint32_t var_name_tmp__370) {
  uint32_t var_name_tmp__371;    /* Address-exposed local */
  uint32_t var_name_tmp__372;    /* Address-exposed local */
  uint32_t var_name_tmp__373;    /* Address-exposed local */
  uint32_t var_name_tmp__374;
  uint32_t var_name_tmp__375;
  uint32_t var_name_tmp__376;
  uint32_t var_name_tmp__377;
  uint32_t var_name_tmp__378;
  uint32_t var_name_tmp__379;
  uint32_t var_name_tmp__380;
  uint32_t var_name_tmp__381;
  uint32_t var_name_tmp__382;
  uint32_t var_name_tmp__383;
  uint32_t var_name_tmp__384;
  uint32_t var_name_tmp__385;
  uint32_t var_name_tmp__386;
  uint32_t var_name_tmp__387;
  uint32_t var_name_tmp__388;
  uint32_t var_name_tmp__389;
  uint32_t var_name_tmp__390;

  var_name_tmp__371 = var_name_tmp__368;
  var_name_tmp__372 = var_name_tmp__369;
  var_name_tmp__373 = var_name_tmp__370;
  var_name_tmp__374 = var_name_tmp__373;
  if ((((var_name_tmp__374 != 0u)&1))) {
    goto var_name_tmp__391;
  } else {
    goto var_name_tmp__392;
  }

var_name_tmp__391:
  var_name_tmp__375 = var_name_tmp__371;
  if ((((var_name_tmp__375 == 16u)&1))) {
    goto var_name_tmp__393;
  } else {
    goto var_name_tmp__394;
  }

var_name_tmp__393:
  var_name_tmp__376 = var_name_tmp__372;
  var_name_tmp__377 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1)) = (var_name_tmp__377 | var_name_tmp__376);
  goto var_name_tmp__395;

var_name_tmp__394:
  var_name_tmp__378 = var_name_tmp__371;
  if ((((var_name_tmp__378 == 256u)&1))) {
    goto var_name_tmp__396;
  } else {
    goto var_name_tmp__397;
  }

var_name_tmp__396:
  var_name_tmp__379 = var_name_tmp__372;
  var_name_tmp__380 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1)) = (var_name_tmp__380 | var_name_tmp__379);
  goto var_name_tmp__398;

var_name_tmp__397:
  var_name_tmp__381 = var_name_tmp__372;
  var_name_tmp__382 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1)) = (var_name_tmp__382 | var_name_tmp__381);
  goto var_name_tmp__398;

var_name_tmp__398:
  goto var_name_tmp__395;

var_name_tmp__395:
  goto var_name_tmp__399;

var_name_tmp__392:
  var_name_tmp__383 = var_name_tmp__371;
  if ((((var_name_tmp__383 == 16u)&1))) {
    goto var_name_tmp__400;
  } else {
    goto var_name_tmp__401;
  }

var_name_tmp__400:
  var_name_tmp__384 = var_name_tmp__372;
  var_name_tmp__385 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1)) = (var_name_tmp__385 & (~(var_name_tmp__384)));
  goto var_name_tmp__402;

var_name_tmp__401:
  var_name_tmp__386 = var_name_tmp__371;
  if ((((var_name_tmp__386 == 256u)&1))) {
    goto var_name_tmp__403;
  } else {
    goto var_name_tmp__404;
  }

var_name_tmp__403:
  var_name_tmp__387 = var_name_tmp__372;
  var_name_tmp__388 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1)) = (var_name_tmp__388 & (~(var_name_tmp__387)));
  goto var_name_tmp__405;

var_name_tmp__404:
  var_name_tmp__389 = var_name_tmp__372;
  var_name_tmp__390 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1)) = (var_name_tmp__390 & (~(var_name_tmp__389)));
  goto var_name_tmp__405;

var_name_tmp__405:
  goto var_name_tmp__402;

var_name_tmp__402:
  goto var_name_tmp__399;

var_name_tmp__399:
  return;
}


uint32_t FSMC_GetFlagStatus(uint32_t var_name_tmp__406, uint32_t var_name_tmp__407) {
  uint32_t var_name_tmp__408;    /* Address-exposed local */
  uint32_t var_name_tmp__409;    /* Address-exposed local */
  uint32_t var_name_tmp__410;    /* Address-exposed local */
  uint32_t var_name_tmp__411;    /* Address-exposed local */
  uint32_t var_name_tmp__412;
  uint32_t var_name_tmp__413;
  uint32_t var_name_tmp__414;
  uint32_t var_name_tmp__415;
  uint32_t var_name_tmp__416;
  uint32_t var_name_tmp__417;
  uint32_t var_name_tmp__418;
  uint32_t var_name_tmp__419;

  var_name_tmp__408 = var_name_tmp__406;
  var_name_tmp__409 = var_name_tmp__407;
  var_name_tmp__410 = 0;
  var_name_tmp__411 = 0;
  var_name_tmp__412 = var_name_tmp__408;
  if ((((var_name_tmp__412 == 16u)&1))) {
    goto var_name_tmp__420;
  } else {
    goto var_name_tmp__421;
  }

var_name_tmp__420:
  var_name_tmp__413 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  var_name_tmp__411 = var_name_tmp__413;
  goto var_name_tmp__422;

var_name_tmp__421:
  var_name_tmp__414 = var_name_tmp__408;
  if ((((var_name_tmp__414 == 256u)&1))) {
    goto var_name_tmp__423;
  } else {
    goto var_name_tmp__424;
  }

var_name_tmp__423:
  var_name_tmp__415 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  var_name_tmp__411 = var_name_tmp__415;
  goto var_name_tmp__425;

var_name_tmp__424:
  var_name_tmp__416 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  var_name_tmp__411 = var_name_tmp__416;
  goto var_name_tmp__425;

var_name_tmp__425:
  goto var_name_tmp__422;

var_name_tmp__422:
  var_name_tmp__417 = var_name_tmp__411;
  var_name_tmp__418 = var_name_tmp__409;
  if (((((var_name_tmp__417 & var_name_tmp__418) != 0u)&1))) {
    goto var_name_tmp__426;
  } else {
    goto var_name_tmp__427;
  }

var_name_tmp__426:
  var_name_tmp__410 = 1;
  goto var_name_tmp__428;

var_name_tmp__427:
  var_name_tmp__410 = 0;
  goto var_name_tmp__428;

var_name_tmp__428:
  var_name_tmp__419 = var_name_tmp__410;
  return var_name_tmp__419;
}


void FSMC_ClearFlag(uint32_t var_name_tmp__429, uint32_t var_name_tmp__430) {
  uint32_t var_name_tmp__431;    /* Address-exposed local */
  uint32_t var_name_tmp__432;    /* Address-exposed local */
  uint32_t var_name_tmp__433;
  uint32_t var_name_tmp__434;
  uint32_t var_name_tmp__435;
  uint32_t var_name_tmp__436;
  uint32_t var_name_tmp__437;
  uint32_t var_name_tmp__438;
  uint32_t var_name_tmp__439;
  uint32_t var_name_tmp__440;

  var_name_tmp__431 = var_name_tmp__429;
  var_name_tmp__432 = var_name_tmp__430;
  var_name_tmp__433 = var_name_tmp__431;
  if ((((var_name_tmp__433 == 16u)&1))) {
    goto var_name_tmp__441;
  } else {
    goto var_name_tmp__442;
  }

var_name_tmp__441:
  var_name_tmp__434 = var_name_tmp__432;
  var_name_tmp__435 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1)) = (var_name_tmp__435 & (~(var_name_tmp__434)));
  goto var_name_tmp__443;

var_name_tmp__442:
  var_name_tmp__436 = var_name_tmp__431;
  if ((((var_name_tmp__436 == 256u)&1))) {
    goto var_name_tmp__444;
  } else {
    goto var_name_tmp__445;
  }

var_name_tmp__444:
  var_name_tmp__437 = var_name_tmp__432;
  var_name_tmp__438 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1)) = (var_name_tmp__438 & (~(var_name_tmp__437)));
  goto var_name_tmp__446;

var_name_tmp__445:
  var_name_tmp__439 = var_name_tmp__432;
  var_name_tmp__440 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1)) = (var_name_tmp__440 & (~(var_name_tmp__439)));
  goto var_name_tmp__446;

var_name_tmp__446:
  goto var_name_tmp__443;

var_name_tmp__443:
  return;
}


uint32_t FSMC_GetITStatus(uint32_t var_name_tmp__447, uint32_t var_name_tmp__448) {
  uint32_t var_name_tmp__449;    /* Address-exposed local */
  uint32_t var_name_tmp__450;    /* Address-exposed local */
  uint32_t var_name_tmp__451;    /* Address-exposed local */
  uint32_t var_name_tmp__452;    /* Address-exposed local */
  uint32_t var_name_tmp__453;    /* Address-exposed local */
  uint32_t var_name_tmp__454;    /* Address-exposed local */
  uint32_t var_name_tmp__455;
  uint32_t var_name_tmp__456;
  uint32_t var_name_tmp__457;
  uint32_t var_name_tmp__458;
  uint32_t var_name_tmp__459;
  uint32_t var_name_tmp__460;
  uint32_t var_name_tmp__461;
  uint32_t var_name_tmp__462;
  uint32_t var_name_tmp__463;
  uint32_t var_name_tmp__464;
  uint32_t var_name_tmp__465;
  uint32_t var_name_tmp__466;

  var_name_tmp__449 = var_name_tmp__447;
  var_name_tmp__450 = var_name_tmp__448;
  var_name_tmp__451 = 0;
  var_name_tmp__452 = 0;
  var_name_tmp__453 = 0;
  var_name_tmp__454 = 0;
  var_name_tmp__455 = var_name_tmp__449;
  if ((((var_name_tmp__455 == 16u)&1))) {
    goto var_name_tmp__467;
  } else {
    goto var_name_tmp__468;
  }

var_name_tmp__467:
  var_name_tmp__456 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  var_name_tmp__452 = var_name_tmp__456;
  goto var_name_tmp__469;

var_name_tmp__468:
  var_name_tmp__457 = var_name_tmp__449;
  if ((((var_name_tmp__457 == 256u)&1))) {
    goto var_name_tmp__470;
  } else {
    goto var_name_tmp__471;
  }

var_name_tmp__470:
  var_name_tmp__458 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  var_name_tmp__452 = var_name_tmp__458;
  goto var_name_tmp__472;

var_name_tmp__471:
  var_name_tmp__459 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  var_name_tmp__452 = var_name_tmp__459;
  goto var_name_tmp__472;

var_name_tmp__472:
  goto var_name_tmp__469;

var_name_tmp__469:
  var_name_tmp__460 = var_name_tmp__452;
  var_name_tmp__461 = var_name_tmp__450;
  var_name_tmp__453 = (var_name_tmp__460 & var_name_tmp__461);
  var_name_tmp__462 = var_name_tmp__452;
  var_name_tmp__463 = var_name_tmp__450;
  var_name_tmp__454 = (var_name_tmp__462 & (llvm_lshr_u32(var_name_tmp__463, 3)));
  var_name_tmp__464 = var_name_tmp__453;
  if ((((var_name_tmp__464 != 0u)&1))) {
    goto var_name_tmp__473;
  } else {
    goto var_name_tmp__474;
  }

var_name_tmp__473:
  var_name_tmp__465 = var_name_tmp__454;
  if ((((var_name_tmp__465 != 0u)&1))) {
    goto var_name_tmp__475;
  } else {
    goto var_name_tmp__474;
  }

var_name_tmp__475:
  var_name_tmp__451 = 1;
  goto var_name_tmp__476;

var_name_tmp__474:
  var_name_tmp__451 = 0;
  goto var_name_tmp__476;

var_name_tmp__476:
  var_name_tmp__466 = var_name_tmp__451;
  return var_name_tmp__466;
}


void FSMC_ClearITPendingBit(uint32_t var_name_tmp__477, uint32_t var_name_tmp__478) {
  uint32_t var_name_tmp__479;    /* Address-exposed local */
  uint32_t var_name_tmp__480;    /* Address-exposed local */
  uint32_t var_name_tmp__481;
  uint32_t var_name_tmp__482;
  uint32_t var_name_tmp__483;
  uint32_t var_name_tmp__484;
  uint32_t var_name_tmp__485;
  uint32_t var_name_tmp__486;
  uint32_t var_name_tmp__487;
  uint32_t var_name_tmp__488;

  var_name_tmp__479 = var_name_tmp__477;
  var_name_tmp__480 = var_name_tmp__478;
  var_name_tmp__481 = var_name_tmp__479;
  if ((((var_name_tmp__481 == 16u)&1))) {
    goto var_name_tmp__489;
  } else {
    goto var_name_tmp__490;
  }

var_name_tmp__489:
  var_name_tmp__482 = var_name_tmp__480;
  var_name_tmp__483 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1)) = (var_name_tmp__483 & (~((llvm_lshr_u32(var_name_tmp__482, 3)))));
  goto var_name_tmp__491;

var_name_tmp__490:
  var_name_tmp__484 = var_name_tmp__479;
  if ((((var_name_tmp__484 == 256u)&1))) {
    goto var_name_tmp__492;
  } else {
    goto var_name_tmp__493;
  }

var_name_tmp__492:
  var_name_tmp__485 = var_name_tmp__480;
  var_name_tmp__486 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1)) = (var_name_tmp__486 & (~((llvm_lshr_u32(var_name_tmp__485, 3)))));
  goto var_name_tmp__494;

var_name_tmp__493:
  var_name_tmp__487 = var_name_tmp__480;
  var_name_tmp__488 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1)) = (var_name_tmp__488 & (~((llvm_lshr_u32(var_name_tmp__487, 3)))));
  goto var_name_tmp__494;

var_name_tmp__494:
  goto var_name_tmp__491;

var_name_tmp__491:
  return;
}

