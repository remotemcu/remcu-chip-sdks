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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


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
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__4)))])))), UINT64_C(12507), 32, 4);
  goto var_name_tmp__10;

var_name_tmp__9:
  var_name_tmp__5 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__5)))])))), UINT64_C(12498), 32, 4);
  goto var_name_tmp__10;

var_name_tmp__10:
  var_name_tmp__6 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(llvm_add_u32(var_name_tmp__6, 1)))))])))), UINT64_C(268435455), 32, 4);
  var_name_tmp__7 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__7)))])))), UINT64_C(268435455), 32, 4);
}


void FSMC_NORSRAMInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__11) {
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__12;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__13;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__14;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__15;
  uint64_t var_name_load_i32_5;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__16;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__17;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__18;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__19;
  uint64_t var_name_load_i32_17;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__20;
  uint64_t var_name_load_i32_20;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__21;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__22;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__23;
  uint64_t var_name_load_i32_29;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__24;
  uint64_t var_name_load_i32_32;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__25;
  uint64_t var_name_load_i32_35;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__26;
  uint64_t var_name_load_i32_39;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__27;
  uint64_t var_name_load_i32_42;
  uint32_t* var_name_tmp__28;
  uint64_t var_name_load_i32_45;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__29;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_;
  uint64_t var_name_load_i32_50;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__30;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_53;
  uint64_t var_name_load_i32_56;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__31;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59;
  uint64_t var_name_load_i32_62;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__32;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_65;
  uint64_t var_name_load_i32_68;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__33;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_71;
  uint64_t var_name_load_i32_74;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__34;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_77;
  uint64_t var_name_load_i32_80;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__35;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_83;
  uint64_t var_name_load_i32_86;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__36;
  uint64_t var_name_load_i32_89;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__37;
  uint64_t var_name_load_i32_94;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__38;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_97;
  uint64_t var_name_load_i32_100;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__39;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_103;
  uint64_t var_name_load_i32_106;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__40;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_109;
  uint64_t var_name_load_i32_112;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__41;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_115;
  uint64_t var_name_load_i32_118;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__42;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_121;
  uint64_t var_name_load_i32_124;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__43;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_127;
  uint64_t var_name_load_i32_130;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__44;
  uint64_t var_name_load_i32_133;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__45;
  uint64_t var_name_load_i32_138;

  var_name_tmp__12 = var_name_tmp__11;
  var_name_tmp__13 = var_name_tmp__12;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__13->field1)))), 32, 4);
  var_name_tmp__14 = var_name_tmp__12;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__14->field2)))), 32, 8);
  var_name_tmp__15 = var_name_tmp__12;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__15->field3)))), 32, 4);
  var_name_tmp__16 = var_name_tmp__12;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__16->field4)))), 32, 8);
  var_name_tmp__17 = var_name_tmp__12;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__17->field5)))), 32, 4);
  var_name_tmp__18 = var_name_tmp__12;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__18->field6)))), 32, 8);
  var_name_tmp__19 = var_name_tmp__12;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__19->field7)))), 32, 4);
  var_name_tmp__20 = var_name_tmp__12;
  var_name_load_i32_20 = __adin_load_((((uint8_t*)((&var_name_tmp__20->field8)))), 32, 8);
  var_name_tmp__21 = var_name_tmp__12;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&var_name_tmp__21->field9)))), 32, 4);
  var_name_tmp__22 = var_name_tmp__12;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__22->field10)))), 32, 8);
  var_name_tmp__23 = var_name_tmp__12;
  var_name_load_i32_29 = __adin_load_((((uint8_t*)((&var_name_tmp__23->field11)))), 32, 4);
  var_name_tmp__24 = var_name_tmp__12;
  var_name_load_i32_32 = __adin_load_((((uint8_t*)((&var_name_tmp__24->field12)))), 32, 8);
  var_name_tmp__25 = var_name_tmp__12;
  var_name_load_i32_35 = __adin_load_((((uint8_t*)((&var_name_tmp__25->field0)))), 32, 8);
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_35)))))])))), (((uint64_t)(uint32_t)((((((((((((((uint32_t)var_name_load_i32_)) | (((uint32_t)var_name_load_i32_2))) | (((uint32_t)var_name_load_i32_5))) | (((uint32_t)var_name_load_i32_8))) | (((uint32_t)var_name_load_i32_11))) | (((uint32_t)var_name_load_i32_14))) | (((uint32_t)var_name_load_i32_17))) | (((uint32_t)var_name_load_i32_20))) | (((uint32_t)var_name_load_i32_23))) | (((uint32_t)var_name_load_i32_26))) | (((uint32_t)var_name_load_i32_29))) | (((uint32_t)var_name_load_i32_32))))), 32, 4);
  var_name_tmp__26 = var_name_tmp__12;
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&var_name_tmp__26->field2)))), 32, 8);
  if (((((((uint32_t)var_name_load_i32_39)) == 8u)&1))) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__47;
  }

var_name_tmp__46:
  var_name_tmp__27 = var_name_tmp__12;
  var_name_load_i32_42 = __adin_load_((((uint8_t*)((&var_name_tmp__27->field0)))), 32, 8);
  var_name_tmp__28 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_42)))))]);
  var_name_load_i32_45 = __adin_load_((((uint8_t*)var_name_tmp__28)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__28)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_45)) | 64))), 32, 4);
  goto var_name_tmp__47;

var_name_tmp__47:
  var_name_tmp__29 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__29->field13)))), 64, 8);
  var_name_load_i32_50 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_))->field0)))), 32, 4);
  var_name_tmp__30 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_53 = __adin_load_((((uint8_t*)((&var_name_tmp__30->field13)))), 64, 8);
  var_name_load_i32_56 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_53))->field1)))), 32, 4);
  var_name_tmp__31 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59 = __adin_load_((((uint8_t*)((&var_name_tmp__31->field13)))), 64, 8);
  var_name_load_i32_62 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59))->field2)))), 32, 4);
  var_name_tmp__32 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_65 = __adin_load_((((uint8_t*)((&var_name_tmp__32->field13)))), 64, 8);
  var_name_load_i32_68 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_65))->field3)))), 32, 4);
  var_name_tmp__33 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_71 = __adin_load_((((uint8_t*)((&var_name_tmp__33->field13)))), 64, 8);
  var_name_load_i32_74 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_71))->field4)))), 32, 4);
  var_name_tmp__34 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_77 = __adin_load_((((uint8_t*)((&var_name_tmp__34->field13)))), 64, 8);
  var_name_load_i32_80 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_77))->field5)))), 32, 4);
  var_name_tmp__35 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_83 = __adin_load_((((uint8_t*)((&var_name_tmp__35->field13)))), 64, 8);
  var_name_load_i32_86 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_83))->field6)))), 32, 4);
  var_name_tmp__36 = var_name_tmp__12;
  var_name_load_i32_89 = __adin_load_((((uint8_t*)((&var_name_tmp__36->field0)))), 32, 8);
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_89)), 1)))))])))), (((uint64_t)(uint32_t)(((((((((uint32_t)var_name_load_i32_50)) | ((((uint32_t)var_name_load_i32_56)) << 4)) | ((((uint32_t)var_name_load_i32_62)) << 8)) | ((((uint32_t)var_name_load_i32_68)) << 16)) | ((((uint32_t)var_name_load_i32_74)) << 20)) | ((((uint32_t)var_name_load_i32_80)) << 24)) | (((uint32_t)var_name_load_i32_86))))), 32, 4);
  var_name_tmp__37 = var_name_tmp__12;
  var_name_load_i32_94 = __adin_load_((((uint8_t*)((&var_name_tmp__37->field11)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_94)) == 16384u)&1))) {
    goto var_name_tmp__48;
  } else {
    goto var_name_tmp__49;
  }

var_name_tmp__48:
  var_name_tmp__38 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_97 = __adin_load_((((uint8_t*)((&var_name_tmp__38->field14)))), 64, 8);
  var_name_load_i32_100 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_97))->field0)))), 32, 4);
  var_name_tmp__39 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_103 = __adin_load_((((uint8_t*)((&var_name_tmp__39->field14)))), 64, 8);
  var_name_load_i32_106 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_103))->field1)))), 32, 4);
  var_name_tmp__40 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_109 = __adin_load_((((uint8_t*)((&var_name_tmp__40->field14)))), 64, 8);
  var_name_load_i32_112 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_109))->field2)))), 32, 4);
  var_name_tmp__41 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_115 = __adin_load_((((uint8_t*)((&var_name_tmp__41->field14)))), 64, 8);
  var_name_load_i32_118 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_115))->field4)))), 32, 4);
  var_name_tmp__42 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_121 = __adin_load_((((uint8_t*)((&var_name_tmp__42->field14)))), 64, 8);
  var_name_load_i32_124 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_121))->field5)))), 32, 4);
  var_name_tmp__43 = var_name_tmp__12;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_127 = __adin_load_((((uint8_t*)((&var_name_tmp__43->field14)))), 64, 8);
  var_name_load_i32_130 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_127))->field6)))), 32, 4);
  var_name_tmp__44 = var_name_tmp__12;
  var_name_load_i32_133 = __adin_load_((((uint8_t*)((&var_name_tmp__44->field0)))), 32, 8);
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_133)))))])))), (((uint64_t)(uint32_t)((((((((uint32_t)var_name_load_i32_100)) | ((((uint32_t)var_name_load_i32_106)) << 4)) | ((((uint32_t)var_name_load_i32_112)) << 8)) | ((((uint32_t)var_name_load_i32_118)) << 20)) | ((((uint32_t)var_name_load_i32_124)) << 24)) | (((uint32_t)var_name_load_i32_130))))), 32, 4);
  goto var_name_tmp__50;

var_name_tmp__49:
  var_name_tmp__45 = var_name_tmp__12;
  var_name_load_i32_138 = __adin_load_((((uint8_t*)((&var_name_tmp__45->field0)))), 32, 8);
  __adin_store_((((uint8_t*)((&(*((&((struct l_struct_struct_OC_FSMC_Bank1E_TypeDef*)(uintptr_t)UINT64_C(2684354820))->field0))).array[((int64_t)(((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_138)))))])))), UINT64_C(268435455), 32, 4);
  goto var_name_tmp__50;

var_name_tmp__50:
  return;
}


void FSMC_NORSRAMStructInit(struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__51) {
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__52;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__53;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__54;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__55;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__56;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__57;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__58;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__59;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__60;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__61;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__62;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__63;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__64;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__65;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__66;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__67;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_15;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__68;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_19;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__69;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_23;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__70;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_27;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__71;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_31;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__72;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_35;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__73;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_39;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__74;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_43;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__75;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_47;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__76;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_51;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__77;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_55;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__78;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59;
  struct l_struct_struct_OC_FSMC_NORSRAMInitTypeDef* var_name_tmp__79;
  uint64_t var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_63;

  var_name_tmp__52 = var_name_tmp__51;
  var_name_tmp__53 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__53->field0)))), UINT64_C(0), 32, 8);
  var_name_tmp__54 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__54->field1)))), UINT64_C(2), 32, 4);
  var_name_tmp__55 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__55->field2)))), UINT64_C(0), 32, 8);
  var_name_tmp__56 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__56->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__57 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__57->field4)))), UINT64_C(0), 32, 8);
  var_name_tmp__58 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__58->field5)))), UINT64_C(0), 32, 4);
  var_name_tmp__59 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__59->field6)))), UINT64_C(0), 32, 8);
  var_name_tmp__60 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__60->field7)))), UINT64_C(0), 32, 4);
  var_name_tmp__61 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__61->field8)))), UINT64_C(0), 32, 8);
  var_name_tmp__62 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__62->field9)))), UINT64_C(4096), 32, 4);
  var_name_tmp__63 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__63->field10)))), UINT64_C(8192), 32, 8);
  var_name_tmp__64 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__64->field11)))), UINT64_C(0), 32, 4);
  var_name_tmp__65 = var_name_tmp__52;
  __adin_store_((((uint8_t*)((&var_name_tmp__65->field12)))), UINT64_C(0), 32, 8);
  var_name_tmp__66 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__66->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_))->field0)))), UINT64_C(15), 32, 4);
  var_name_tmp__67 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_15 = __adin_load_((((uint8_t*)((&var_name_tmp__67->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_15))->field1)))), UINT64_C(15), 32, 4);
  var_name_tmp__68 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_19 = __adin_load_((((uint8_t*)((&var_name_tmp__68->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_19))->field2)))), UINT64_C(255), 32, 4);
  var_name_tmp__69 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_23 = __adin_load_((((uint8_t*)((&var_name_tmp__69->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_23))->field3)))), UINT64_C(15), 32, 4);
  var_name_tmp__70 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_27 = __adin_load_((((uint8_t*)((&var_name_tmp__70->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_27))->field4)))), UINT64_C(15), 32, 4);
  var_name_tmp__71 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_31 = __adin_load_((((uint8_t*)((&var_name_tmp__71->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_31))->field5)))), UINT64_C(15), 32, 4);
  var_name_tmp__72 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_35 = __adin_load_((((uint8_t*)((&var_name_tmp__72->field13)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_35))->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__73 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_39 = __adin_load_((((uint8_t*)((&var_name_tmp__73->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_39))->field0)))), UINT64_C(15), 32, 4);
  var_name_tmp__74 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_43 = __adin_load_((((uint8_t*)((&var_name_tmp__74->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_43))->field1)))), UINT64_C(15), 32, 4);
  var_name_tmp__75 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_47 = __adin_load_((((uint8_t*)((&var_name_tmp__75->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_47))->field2)))), UINT64_C(255), 32, 4);
  var_name_tmp__76 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_51 = __adin_load_((((uint8_t*)((&var_name_tmp__76->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_51))->field3)))), UINT64_C(15), 32, 4);
  var_name_tmp__77 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_55 = __adin_load_((((uint8_t*)((&var_name_tmp__77->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_55))->field4)))), UINT64_C(15), 32, 4);
  var_name_tmp__78 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59 = __adin_load_((((uint8_t*)((&var_name_tmp__78->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_59))->field5)))), UINT64_C(15), 32, 4);
  var_name_tmp__79 = var_name_tmp__52;
  var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_63 = __adin_load_((((uint8_t*)((&var_name_tmp__79->field14)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NORSRAMTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NORSRAMTimingInitTypeDef_p_63))->field6)))), UINT64_C(0), 32, 4);
}


void FSMC_NORSRAMCmd(uint32_t var_name_tmp__80, uint32_t var_name_tmp__81) {
  uint32_t var_name_tmp__82;    /* Address-exposed local */
  uint32_t var_name_tmp__83;    /* Address-exposed local */
  uint32_t var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint32_t* var_name_tmp__86;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__87;
  uint32_t* var_name_tmp__88;
  uint64_t var_name_load_i32_3;

  var_name_tmp__82 = var_name_tmp__80;
  var_name_tmp__83 = var_name_tmp__81;
  var_name_tmp__84 = var_name_tmp__83;
  if ((((var_name_tmp__84 != 0u)&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__90;
  }

var_name_tmp__89:
  var_name_tmp__85 = var_name_tmp__82;
  var_name_tmp__86 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__85)))]);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__86)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__86)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  goto var_name_tmp__91;

var_name_tmp__90:
  var_name_tmp__87 = var_name_tmp__82;
  var_name_tmp__88 = (&(*((&((struct l_struct_struct_OC_FSMC_Bank1_TypeDef*)(uintptr_t)UINT64_C(2684354560))->field0))).array[((int64_t)(((uint64_t)(uint32_t)var_name_tmp__87)))]);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__88)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__88)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & 1048574))), 32, 4);
  goto var_name_tmp__91;

var_name_tmp__91:
  return;
}


void FSMC_NANDDeInit(uint32_t var_name_tmp__92) {
  uint32_t var_name_tmp__93;    /* Address-exposed local */
  uint32_t var_name_tmp__94;

  var_name_tmp__93 = var_name_tmp__92;
  var_name_tmp__94 = var_name_tmp__93;
  if ((((var_name_tmp__94 == 16u)&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__96;
  }

var_name_tmp__95:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), UINT64_C(24), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), UINT64_C(64), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field2))), UINT64_C(4244438268), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field3))), UINT64_C(4244438268), 32, 4);
  goto var_name_tmp__97;

var_name_tmp__96:
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), UINT64_C(24), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), UINT64_C(64), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field2))), UINT64_C(4244438268), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field3))), UINT64_C(4244438268), 32, 4);
  goto var_name_tmp__97;

var_name_tmp__97:
  return;
}


void FSMC_NANDInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__98) {
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__103;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__104;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__105;
  uint64_t var_name_load_i32_5;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__106;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__107;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__108;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__109;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_;
  uint64_t var_name_load_i32_17;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__110;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_20;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__111;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_26;
  uint64_t var_name_load_i32_29;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__112;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_32;
  uint64_t var_name_load_i32_35;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__113;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_38;
  uint64_t var_name_load_i32_41;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__114;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_44;
  uint64_t var_name_load_i32_47;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__115;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_50;
  uint64_t var_name_load_i32_53;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__116;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_56;
  uint64_t var_name_load_i32_59;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__117;
  uint64_t var_name_load_i32_62;
  uint32_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint32_t var_name_tmp__120;
  uint32_t var_name_tmp__121;
  uint32_t var_name_tmp__122;
  uint32_t var_name_tmp__123;

  var_name_tmp__99 = var_name_tmp__98;
  var_name_tmp__100 = 0;
  var_name_tmp__101 = 0;
  var_name_tmp__102 = 0;
  var_name_tmp__103 = var_name_tmp__99;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__103->field1)))), 32, 4);
  var_name_tmp__104 = var_name_tmp__99;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__104->field2)))), 32, 8);
  var_name_tmp__105 = var_name_tmp__99;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__105->field3)))), 32, 4);
  var_name_tmp__106 = var_name_tmp__99;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__106->field4)))), 32, 8);
  var_name_tmp__107 = var_name_tmp__99;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__107->field5)))), 32, 4);
  var_name_tmp__108 = var_name_tmp__99;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__108->field6)))), 32, 8);
  var_name_tmp__100 = (((((((((uint32_t)var_name_load_i32_)) | 8) | (((uint32_t)var_name_load_i32_2))) | (((uint32_t)var_name_load_i32_5))) | (((uint32_t)var_name_load_i32_8))) | ((((uint32_t)var_name_load_i32_11)) << 9)) | ((((uint32_t)var_name_load_i32_14)) << 13));
  var_name_tmp__109 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__109->field7)))), 64, 8);
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_))->field0)))), 32, 4);
  var_name_tmp__110 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_20 = __adin_load_((((uint8_t*)((&var_name_tmp__110->field7)))), 64, 8);
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_20))->field1)))), 32, 4);
  var_name_tmp__111 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_26 = __adin_load_((((uint8_t*)((&var_name_tmp__111->field7)))), 64, 8);
  var_name_load_i32_29 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_26))->field2)))), 32, 4);
  var_name_tmp__112 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_32 = __adin_load_((((uint8_t*)((&var_name_tmp__112->field7)))), 64, 8);
  var_name_load_i32_35 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_32))->field3)))), 32, 4);
  var_name_tmp__101 = ((((((uint32_t)var_name_load_i32_17)) | ((((uint32_t)var_name_load_i32_23)) << 8)) | ((((uint32_t)var_name_load_i32_29)) << 16)) | ((((uint32_t)var_name_load_i32_35)) << 24));
  var_name_tmp__113 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_38 = __adin_load_((((uint8_t*)((&var_name_tmp__113->field8)))), 64, 8);
  var_name_load_i32_41 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_38))->field0)))), 32, 4);
  var_name_tmp__114 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_44 = __adin_load_((((uint8_t*)((&var_name_tmp__114->field8)))), 64, 8);
  var_name_load_i32_47 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_44))->field1)))), 32, 4);
  var_name_tmp__115 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_50 = __adin_load_((((uint8_t*)((&var_name_tmp__115->field8)))), 64, 8);
  var_name_load_i32_53 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_50))->field2)))), 32, 4);
  var_name_tmp__116 = var_name_tmp__99;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_56 = __adin_load_((((uint8_t*)((&var_name_tmp__116->field8)))), 64, 8);
  var_name_load_i32_59 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_56))->field3)))), 32, 4);
  var_name_tmp__102 = ((((((uint32_t)var_name_load_i32_41)) | ((((uint32_t)var_name_load_i32_47)) << 8)) | ((((uint32_t)var_name_load_i32_53)) << 16)) | ((((uint32_t)var_name_load_i32_59)) << 24));
  var_name_tmp__117 = var_name_tmp__99;
  var_name_load_i32_62 = __adin_load_((((uint8_t*)((&var_name_tmp__117->field0)))), 32, 8);
  if (((((((uint32_t)var_name_load_i32_62)) == 16u)&1))) {
    goto var_name_tmp__124;
  } else {
    goto var_name_tmp__125;
  }

var_name_tmp__124:
  var_name_tmp__118 = var_name_tmp__100;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), (((uint64_t)(uint32_t)var_name_tmp__118)), 32, 4);
  var_name_tmp__119 = var_name_tmp__101;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field2))), (((uint64_t)(uint32_t)var_name_tmp__119)), 32, 4);
  var_name_tmp__120 = var_name_tmp__102;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field3))), (((uint64_t)(uint32_t)var_name_tmp__120)), 32, 4);
  goto var_name_tmp__126;

var_name_tmp__125:
  var_name_tmp__121 = var_name_tmp__100;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), (((uint64_t)(uint32_t)var_name_tmp__121)), 32, 4);
  var_name_tmp__122 = var_name_tmp__101;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field2))), (((uint64_t)(uint32_t)var_name_tmp__122)), 32, 4);
  var_name_tmp__123 = var_name_tmp__102;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field3))), (((uint64_t)(uint32_t)var_name_tmp__123)), 32, 4);
  goto var_name_tmp__126;

var_name_tmp__126:
  return;
}


void FSMC_NANDStructInit(struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__127) {
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__128;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__129;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__130;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__131;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__132;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__133;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__134;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__135;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__136;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__137;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__138;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__139;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__140;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__141;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__142;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29;
  struct l_struct_struct_OC_FSMC_NANDInitTypeDef* var_name_tmp__143;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33;

  var_name_tmp__128 = var_name_tmp__127;
  var_name_tmp__129 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__129->field0)))), UINT64_C(16), 32, 8);
  var_name_tmp__130 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__130->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__131 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__131->field2)))), UINT64_C(0), 32, 8);
  var_name_tmp__132 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__132->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__133 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__133->field4)))), UINT64_C(0), 32, 8);
  var_name_tmp__134 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__134->field5)))), UINT64_C(0), 32, 4);
  var_name_tmp__135 = var_name_tmp__128;
  __adin_store_((((uint8_t*)((&var_name_tmp__135->field6)))), UINT64_C(0), 32, 8);
  var_name_tmp__136 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__136->field7)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_))->field0)))), UINT64_C(252), 32, 4);
  var_name_tmp__137 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9 = __adin_load_((((uint8_t*)((&var_name_tmp__137->field7)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9))->field1)))), UINT64_C(252), 32, 4);
  var_name_tmp__138 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13 = __adin_load_((((uint8_t*)((&var_name_tmp__138->field7)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13))->field2)))), UINT64_C(252), 32, 4);
  var_name_tmp__139 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17 = __adin_load_((((uint8_t*)((&var_name_tmp__139->field7)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17))->field3)))), UINT64_C(252), 32, 4);
  var_name_tmp__140 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21 = __adin_load_((((uint8_t*)((&var_name_tmp__140->field8)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21))->field0)))), UINT64_C(252), 32, 4);
  var_name_tmp__141 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25 = __adin_load_((((uint8_t*)((&var_name_tmp__141->field8)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25))->field1)))), UINT64_C(252), 32, 4);
  var_name_tmp__142 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29 = __adin_load_((((uint8_t*)((&var_name_tmp__142->field8)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29))->field2)))), UINT64_C(252), 32, 4);
  var_name_tmp__143 = var_name_tmp__128;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33 = __adin_load_((((uint8_t*)((&var_name_tmp__143->field8)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33))->field3)))), UINT64_C(252), 32, 4);
}


void FSMC_NANDCmd(uint32_t var_name_tmp__144, uint32_t var_name_tmp__145) {
  uint32_t var_name_tmp__146;    /* Address-exposed local */
  uint32_t var_name_tmp__147;    /* Address-exposed local */
  uint32_t var_name_tmp__148;
  uint32_t var_name_tmp__149;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__150;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;

  var_name_tmp__146 = var_name_tmp__144;
  var_name_tmp__147 = var_name_tmp__145;
  var_name_tmp__148 = var_name_tmp__147;
  if ((((var_name_tmp__148 != 0u)&1))) {
    goto var_name_tmp__151;
  } else {
    goto var_name_tmp__152;
  }

var_name_tmp__151:
  var_name_tmp__149 = var_name_tmp__146;
  if ((((var_name_tmp__149 == 16u)&1))) {
    goto var_name_tmp__153;
  } else {
    goto var_name_tmp__154;
  }

var_name_tmp__153:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 4))), 32, 4);
  goto var_name_tmp__155;

var_name_tmp__154:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 4))), 32, 4);
  goto var_name_tmp__155;

var_name_tmp__155:
  goto var_name_tmp__156;

var_name_tmp__152:
  var_name_tmp__150 = var_name_tmp__146;
  if ((((var_name_tmp__150 == 16u)&1))) {
    goto var_name_tmp__157;
  } else {
    goto var_name_tmp__158;
  }

var_name_tmp__157:
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & 1048571))), 32, 4);
  goto var_name_tmp__159;

var_name_tmp__158:
  var_name_load_i32_7 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & 1048571))), 32, 4);
  goto var_name_tmp__159;

var_name_tmp__159:
  goto var_name_tmp__156;

var_name_tmp__156:
  return;
}


void FSMC_NANDECCCmd(uint32_t var_name_tmp__160, uint32_t var_name_tmp__161) {
  uint32_t var_name_tmp__162;    /* Address-exposed local */
  uint32_t var_name_tmp__163;    /* Address-exposed local */
  uint32_t var_name_tmp__164;
  uint32_t var_name_tmp__165;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__166;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;

  var_name_tmp__162 = var_name_tmp__160;
  var_name_tmp__163 = var_name_tmp__161;
  var_name_tmp__164 = var_name_tmp__163;
  if ((((var_name_tmp__164 != 0u)&1))) {
    goto var_name_tmp__167;
  } else {
    goto var_name_tmp__168;
  }

var_name_tmp__167:
  var_name_tmp__165 = var_name_tmp__162;
  if ((((var_name_tmp__165 == 16u)&1))) {
    goto var_name_tmp__169;
  } else {
    goto var_name_tmp__170;
  }

var_name_tmp__169:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 64))), 32, 4);
  goto var_name_tmp__171;

var_name_tmp__170:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 64))), 32, 4);
  goto var_name_tmp__171;

var_name_tmp__171:
  goto var_name_tmp__172;

var_name_tmp__168:
  var_name_tmp__166 = var_name_tmp__162;
  if ((((var_name_tmp__166 == 16u)&1))) {
    goto var_name_tmp__173;
  } else {
    goto var_name_tmp__174;
  }

var_name_tmp__173:
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354656)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & 1048511))), 32, 4);
  goto var_name_tmp__175;

var_name_tmp__174:
  var_name_load_i32_7 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354688)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & 1048511))), 32, 4);
  goto var_name_tmp__175;

var_name_tmp__175:
  goto var_name_tmp__172;

var_name_tmp__172:
  return;
}


uint32_t FSMC_GetECC(uint32_t var_name_tmp__176) {
  uint32_t var_name_tmp__177;    /* Address-exposed local */
  uint32_t var_name_tmp__178;    /* Address-exposed local */
  uint32_t var_name_tmp__179;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__180;

  var_name_tmp__177 = var_name_tmp__176;
  var_name_tmp__178 = 0;
  var_name_tmp__179 = var_name_tmp__177;
  if ((((var_name_tmp__179 == 16u)&1))) {
    goto var_name_tmp__181;
  } else {
    goto var_name_tmp__182;
  }

var_name_tmp__181:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field5))), 32, 4);
  var_name_tmp__178 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__183;

var_name_tmp__182:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field5))), 32, 4);
  var_name_tmp__178 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__183;

var_name_tmp__183:
  var_name_tmp__180 = var_name_tmp__178;
  return var_name_tmp__180;
}


void FSMC_PCCARDDeInit(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), UINT64_C(24), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field2))), UINT64_C(4244438268), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field3))), UINT64_C(4244438268), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field4))), UINT64_C(4244438268), 32, 4);
}


void FSMC_PCCARDInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__184) {
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__185;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__186;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__187;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__188;
  uint64_t var_name_load_i32_5;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__189;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__190;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_11;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__191;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17;
  uint64_t var_name_load_i32_20;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__192;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_23;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__193;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_30;
  uint64_t var_name_load_i32_33;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__194;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_36;
  uint64_t var_name_load_i32_39;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__195;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_42;
  uint64_t var_name_load_i32_45;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__196;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_48;
  uint64_t var_name_load_i32_51;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__197;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_55;
  uint64_t var_name_load_i32_58;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__198;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_61;
  uint64_t var_name_load_i32_64;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__199;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_67;
  uint64_t var_name_load_i32_70;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__200;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_73;
  uint64_t var_name_load_i32_76;

  var_name_tmp__185 = var_name_tmp__184;
  var_name_tmp__186 = var_name_tmp__185;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__186->field0)))), 32, 8);
  var_name_tmp__187 = var_name_tmp__185;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__187->field1)))), 32, 4);
  var_name_tmp__188 = var_name_tmp__185;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__188->field2)))), 32, 8);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), (((uint64_t)(uint32_t)((((((uint32_t)var_name_load_i32_)) | 16) | ((((uint32_t)var_name_load_i32_2)) << 9)) | ((((uint32_t)var_name_load_i32_5)) << 13)))), 32, 4);
  var_name_tmp__189 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__189->field3)))), 64, 8);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_))->field0)))), 32, 4);
  var_name_tmp__190 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_11 = __adin_load_((((uint8_t*)((&var_name_tmp__190->field3)))), 64, 8);
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_11))->field1)))), 32, 4);
  var_name_tmp__191 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17 = __adin_load_((((uint8_t*)((&var_name_tmp__191->field3)))), 64, 8);
  var_name_load_i32_20 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17))->field2)))), 32, 4);
  var_name_tmp__192 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_23 = __adin_load_((((uint8_t*)((&var_name_tmp__192->field3)))), 64, 8);
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_23))->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field2))), (((uint64_t)(uint32_t)((((((uint32_t)var_name_load_i32_8)) | ((((uint32_t)var_name_load_i32_14)) << 8)) | ((((uint32_t)var_name_load_i32_20)) << 16)) | ((((uint32_t)var_name_load_i32_26)) << 24)))), 32, 4);
  var_name_tmp__193 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_30 = __adin_load_((((uint8_t*)((&var_name_tmp__193->field4)))), 64, 8);
  var_name_load_i32_33 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_30))->field0)))), 32, 4);
  var_name_tmp__194 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_36 = __adin_load_((((uint8_t*)((&var_name_tmp__194->field4)))), 64, 8);
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_36))->field1)))), 32, 4);
  var_name_tmp__195 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_42 = __adin_load_((((uint8_t*)((&var_name_tmp__195->field4)))), 64, 8);
  var_name_load_i32_45 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_42))->field2)))), 32, 4);
  var_name_tmp__196 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_48 = __adin_load_((((uint8_t*)((&var_name_tmp__196->field4)))), 64, 8);
  var_name_load_i32_51 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_48))->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field3))), (((uint64_t)(uint32_t)((((((uint32_t)var_name_load_i32_33)) | ((((uint32_t)var_name_load_i32_39)) << 8)) | ((((uint32_t)var_name_load_i32_45)) << 16)) | ((((uint32_t)var_name_load_i32_51)) << 24)))), 32, 4);
  var_name_tmp__197 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_55 = __adin_load_((((uint8_t*)((&var_name_tmp__197->field5)))), 64, 8);
  var_name_load_i32_58 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_55))->field0)))), 32, 4);
  var_name_tmp__198 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_61 = __adin_load_((((uint8_t*)((&var_name_tmp__198->field5)))), 64, 8);
  var_name_load_i32_64 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_61))->field1)))), 32, 4);
  var_name_tmp__199 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_67 = __adin_load_((((uint8_t*)((&var_name_tmp__199->field5)))), 64, 8);
  var_name_load_i32_70 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_67))->field2)))), 32, 4);
  var_name_tmp__200 = var_name_tmp__185;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_73 = __adin_load_((((uint8_t*)((&var_name_tmp__200->field5)))), 64, 8);
  var_name_load_i32_76 = __adin_load_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_73))->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field4))), (((uint64_t)(uint32_t)((((((uint32_t)var_name_load_i32_58)) | ((((uint32_t)var_name_load_i32_64)) << 8)) | ((((uint32_t)var_name_load_i32_70)) << 16)) | ((((uint32_t)var_name_load_i32_76)) << 24)))), 32, 4);
}


void FSMC_PCCARDStructInit(struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__201) {
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__202;    /* Address-exposed local */
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__203;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__204;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__205;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__206;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__207;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_5;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__208;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__209;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__210;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__211;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__212;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__213;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__214;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__215;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_37;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__216;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_41;
  struct l_struct_struct_OC_FSMC_PCCARDInitTypeDef* var_name_tmp__217;
  uint64_t var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_45;

  var_name_tmp__202 = var_name_tmp__201;
  var_name_tmp__203 = var_name_tmp__202;
  __adin_store_((((uint8_t*)((&var_name_tmp__203->field0)))), UINT64_C(0), 32, 8);
  var_name_tmp__204 = var_name_tmp__202;
  __adin_store_((((uint8_t*)((&var_name_tmp__204->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__205 = var_name_tmp__202;
  __adin_store_((((uint8_t*)((&var_name_tmp__205->field2)))), UINT64_C(0), 32, 8);
  var_name_tmp__206 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_ = __adin_load_((((uint8_t*)((&var_name_tmp__206->field3)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_))->field0)))), UINT64_C(252), 32, 4);
  var_name_tmp__207 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_5 = __adin_load_((((uint8_t*)((&var_name_tmp__207->field3)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_5))->field1)))), UINT64_C(252), 32, 4);
  var_name_tmp__208 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9 = __adin_load_((((uint8_t*)((&var_name_tmp__208->field3)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_9))->field2)))), UINT64_C(252), 32, 4);
  var_name_tmp__209 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13 = __adin_load_((((uint8_t*)((&var_name_tmp__209->field3)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_13))->field3)))), UINT64_C(252), 32, 4);
  var_name_tmp__210 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17 = __adin_load_((((uint8_t*)((&var_name_tmp__210->field4)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_17))->field0)))), UINT64_C(252), 32, 4);
  var_name_tmp__211 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21 = __adin_load_((((uint8_t*)((&var_name_tmp__211->field4)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_21))->field1)))), UINT64_C(252), 32, 4);
  var_name_tmp__212 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25 = __adin_load_((((uint8_t*)((&var_name_tmp__212->field4)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_25))->field2)))), UINT64_C(252), 32, 4);
  var_name_tmp__213 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29 = __adin_load_((((uint8_t*)((&var_name_tmp__213->field4)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_29))->field3)))), UINT64_C(252), 32, 4);
  var_name_tmp__214 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33 = __adin_load_((((uint8_t*)((&var_name_tmp__214->field5)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_33))->field0)))), UINT64_C(252), 32, 4);
  var_name_tmp__215 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_37 = __adin_load_((((uint8_t*)((&var_name_tmp__215->field5)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_37))->field1)))), UINT64_C(252), 32, 4);
  var_name_tmp__216 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_41 = __adin_load_((((uint8_t*)((&var_name_tmp__216->field5)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_41))->field2)))), UINT64_C(252), 32, 4);
  var_name_tmp__217 = var_name_tmp__202;
  var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_45 = __adin_load_((((uint8_t*)((&var_name_tmp__217->field5)))), 64, 8);
  __adin_store_((((uint8_t*)((&(((struct l_struct_struct_OC_FSMC_NAND_PCCARDTimingInitTypeDef*)(uintptr_t)var_name_load__struct_2e_FSMC_NAND_PCCARDTimingInitTypeDef_p_45))->field3)))), UINT64_C(252), 32, 4);
}


void FSMC_PCCARDCmd(uint32_t var_name_tmp__218) {
  uint32_t var_name_tmp__219;    /* Address-exposed local */
  uint32_t var_name_tmp__220;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__219 = var_name_tmp__218;
  var_name_tmp__220 = var_name_tmp__219;
  if ((((var_name_tmp__220 != 0u)&1))) {
    goto var_name_tmp__221;
  } else {
    goto var_name_tmp__222;
  }

var_name_tmp__221:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 4))), 32, 4);
  goto var_name_tmp__223;

var_name_tmp__222:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(2684354720)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & 1048571))), 32, 4);
  goto var_name_tmp__223;

var_name_tmp__223:
  return;
}


void FSMC_ITConfig(uint32_t var_name_tmp__224, uint32_t var_name_tmp__225, uint32_t var_name_tmp__226) {
  uint32_t var_name_tmp__227;    /* Address-exposed local */
  uint32_t var_name_tmp__228;    /* Address-exposed local */
  uint32_t var_name_tmp__229;    /* Address-exposed local */
  uint32_t var_name_tmp__230;
  uint32_t var_name_tmp__231;
  uint32_t var_name_tmp__232;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__233;
  uint32_t var_name_tmp__234;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__235;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__236;
  uint32_t var_name_tmp__237;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__238;
  uint32_t var_name_tmp__239;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__240;
  uint64_t var_name_load_i32_13;

  var_name_tmp__227 = var_name_tmp__224;
  var_name_tmp__228 = var_name_tmp__225;
  var_name_tmp__229 = var_name_tmp__226;
  var_name_tmp__230 = var_name_tmp__229;
  if ((((var_name_tmp__230 != 0u)&1))) {
    goto var_name_tmp__241;
  } else {
    goto var_name_tmp__242;
  }

var_name_tmp__241:
  var_name_tmp__231 = var_name_tmp__227;
  if ((((var_name_tmp__231 == 16u)&1))) {
    goto var_name_tmp__243;
  } else {
    goto var_name_tmp__244;
  }

var_name_tmp__243:
  var_name_tmp__232 = var_name_tmp__228;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__232))), 32, 4);
  goto var_name_tmp__245;

var_name_tmp__244:
  var_name_tmp__233 = var_name_tmp__227;
  if ((((var_name_tmp__233 == 256u)&1))) {
    goto var_name_tmp__246;
  } else {
    goto var_name_tmp__247;
  }

var_name_tmp__246:
  var_name_tmp__234 = var_name_tmp__228;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__234))), 32, 4);
  goto var_name_tmp__248;

var_name_tmp__247:
  var_name_tmp__235 = var_name_tmp__228;
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | var_name_tmp__235))), 32, 4);
  goto var_name_tmp__248;

var_name_tmp__248:
  goto var_name_tmp__245;

var_name_tmp__245:
  goto var_name_tmp__249;

var_name_tmp__242:
  var_name_tmp__236 = var_name_tmp__227;
  if ((((var_name_tmp__236 == 16u)&1))) {
    goto var_name_tmp__250;
  } else {
    goto var_name_tmp__251;
  }

var_name_tmp__250:
  var_name_tmp__237 = var_name_tmp__228;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & (~(var_name_tmp__237))))), 32, 4);
  goto var_name_tmp__252;

var_name_tmp__251:
  var_name_tmp__238 = var_name_tmp__227;
  if ((((var_name_tmp__238 == 256u)&1))) {
    goto var_name_tmp__253;
  } else {
    goto var_name_tmp__254;
  }

var_name_tmp__253:
  var_name_tmp__239 = var_name_tmp__228;
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_10)) & (~(var_name_tmp__239))))), 32, 4);
  goto var_name_tmp__255;

var_name_tmp__254:
  var_name_tmp__240 = var_name_tmp__228;
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) & (~(var_name_tmp__240))))), 32, 4);
  goto var_name_tmp__255;

var_name_tmp__255:
  goto var_name_tmp__252;

var_name_tmp__252:
  goto var_name_tmp__249;

var_name_tmp__249:
  return;
}


uint32_t FSMC_GetFlagStatus(uint32_t var_name_tmp__256, uint32_t var_name_tmp__257) {
  uint32_t var_name_tmp__258;    /* Address-exposed local */
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  uint32_t var_name_tmp__260;    /* Address-exposed local */
  uint32_t var_name_tmp__261;    /* Address-exposed local */
  uint32_t var_name_tmp__262;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__263;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__264;
  uint32_t var_name_tmp__265;
  uint32_t var_name_tmp__266;

  var_name_tmp__258 = var_name_tmp__256;
  var_name_tmp__259 = var_name_tmp__257;
  var_name_tmp__260 = 0;
  var_name_tmp__261 = 0;
  var_name_tmp__262 = var_name_tmp__258;
  if ((((var_name_tmp__262 == 16u)&1))) {
    goto var_name_tmp__267;
  } else {
    goto var_name_tmp__268;
  }

var_name_tmp__267:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  var_name_tmp__261 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__269;

var_name_tmp__268:
  var_name_tmp__263 = var_name_tmp__258;
  if ((((var_name_tmp__263 == 256u)&1))) {
    goto var_name_tmp__270;
  } else {
    goto var_name_tmp__271;
  }

var_name_tmp__270:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  var_name_tmp__261 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__272;

var_name_tmp__271:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  var_name_tmp__261 = (((uint32_t)var_name_load_i32_3));
  goto var_name_tmp__272;

var_name_tmp__272:
  goto var_name_tmp__269;

var_name_tmp__269:
  var_name_tmp__264 = var_name_tmp__261;
  var_name_tmp__265 = var_name_tmp__259;
  if (((((var_name_tmp__264 & var_name_tmp__265) != 0u)&1))) {
    goto var_name_tmp__273;
  } else {
    goto var_name_tmp__274;
  }

var_name_tmp__273:
  var_name_tmp__260 = 1;
  goto var_name_tmp__275;

var_name_tmp__274:
  var_name_tmp__260 = 0;
  goto var_name_tmp__275;

var_name_tmp__275:
  var_name_tmp__266 = var_name_tmp__260;
  return var_name_tmp__266;
}


void FSMC_ClearFlag(uint32_t var_name_tmp__276, uint32_t var_name_tmp__277) {
  uint32_t var_name_tmp__278;    /* Address-exposed local */
  uint32_t var_name_tmp__279;    /* Address-exposed local */
  uint32_t var_name_tmp__280;
  uint32_t var_name_tmp__281;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__282;
  uint32_t var_name_tmp__283;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__284;
  uint64_t var_name_load_i32_4;

  var_name_tmp__278 = var_name_tmp__276;
  var_name_tmp__279 = var_name_tmp__277;
  var_name_tmp__280 = var_name_tmp__278;
  if ((((var_name_tmp__280 == 16u)&1))) {
    goto var_name_tmp__285;
  } else {
    goto var_name_tmp__286;
  }

var_name_tmp__285:
  var_name_tmp__281 = var_name_tmp__279;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & (~(var_name_tmp__281))))), 32, 4);
  goto var_name_tmp__287;

var_name_tmp__286:
  var_name_tmp__282 = var_name_tmp__278;
  if ((((var_name_tmp__282 == 256u)&1))) {
    goto var_name_tmp__288;
  } else {
    goto var_name_tmp__289;
  }

var_name_tmp__288:
  var_name_tmp__283 = var_name_tmp__279;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__283))))), 32, 4);
  goto var_name_tmp__290;

var_name_tmp__289:
  var_name_tmp__284 = var_name_tmp__279;
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & (~(var_name_tmp__284))))), 32, 4);
  goto var_name_tmp__290;

var_name_tmp__290:
  goto var_name_tmp__287;

var_name_tmp__287:
  return;
}


uint32_t FSMC_GetITStatus(uint32_t var_name_tmp__291, uint32_t var_name_tmp__292) {
  uint32_t var_name_tmp__293;    /* Address-exposed local */
  uint32_t var_name_tmp__294;    /* Address-exposed local */
  uint32_t var_name_tmp__295;    /* Address-exposed local */
  uint32_t var_name_tmp__296;    /* Address-exposed local */
  uint32_t var_name_tmp__297;    /* Address-exposed local */
  uint32_t var_name_tmp__298;    /* Address-exposed local */
  uint32_t var_name_tmp__299;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__300;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__301;
  uint32_t var_name_tmp__302;
  uint32_t var_name_tmp__303;
  uint32_t var_name_tmp__304;
  uint32_t var_name_tmp__305;
  uint32_t var_name_tmp__306;
  uint32_t var_name_tmp__307;

  var_name_tmp__293 = var_name_tmp__291;
  var_name_tmp__294 = var_name_tmp__292;
  var_name_tmp__295 = 0;
  var_name_tmp__296 = 0;
  var_name_tmp__297 = 0;
  var_name_tmp__298 = 0;
  var_name_tmp__299 = var_name_tmp__293;
  if ((((var_name_tmp__299 == 16u)&1))) {
    goto var_name_tmp__308;
  } else {
    goto var_name_tmp__309;
  }

var_name_tmp__308:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  var_name_tmp__296 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__310;

var_name_tmp__309:
  var_name_tmp__300 = var_name_tmp__293;
  if ((((var_name_tmp__300 == 256u)&1))) {
    goto var_name_tmp__311;
  } else {
    goto var_name_tmp__312;
  }

var_name_tmp__311:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  var_name_tmp__296 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__313;

var_name_tmp__312:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  var_name_tmp__296 = (((uint32_t)var_name_load_i32_3));
  goto var_name_tmp__313;

var_name_tmp__313:
  goto var_name_tmp__310;

var_name_tmp__310:
  var_name_tmp__301 = var_name_tmp__296;
  var_name_tmp__302 = var_name_tmp__294;
  var_name_tmp__297 = (var_name_tmp__301 & var_name_tmp__302);
  var_name_tmp__303 = var_name_tmp__296;
  var_name_tmp__304 = var_name_tmp__294;
  var_name_tmp__298 = (var_name_tmp__303 & (llvm_lshr_u32(var_name_tmp__304, 3)));
  var_name_tmp__305 = var_name_tmp__297;
  if ((((var_name_tmp__305 != 0u)&1))) {
    goto var_name_tmp__314;
  } else {
    goto var_name_tmp__315;
  }

var_name_tmp__314:
  var_name_tmp__306 = var_name_tmp__298;
  if ((((var_name_tmp__306 != 0u)&1))) {
    goto var_name_tmp__316;
  } else {
    goto var_name_tmp__315;
  }

var_name_tmp__316:
  var_name_tmp__295 = 1;
  goto var_name_tmp__317;

var_name_tmp__315:
  var_name_tmp__295 = 0;
  goto var_name_tmp__317;

var_name_tmp__317:
  var_name_tmp__307 = var_name_tmp__295;
  return var_name_tmp__307;
}


void FSMC_ClearITPendingBit(uint32_t var_name_tmp__318, uint32_t var_name_tmp__319) {
  uint32_t var_name_tmp__320;    /* Address-exposed local */
  uint32_t var_name_tmp__321;    /* Address-exposed local */
  uint32_t var_name_tmp__322;
  uint32_t var_name_tmp__323;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__324;
  uint32_t var_name_tmp__325;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__326;
  uint64_t var_name_load_i32_4;

  var_name_tmp__320 = var_name_tmp__318;
  var_name_tmp__321 = var_name_tmp__319;
  var_name_tmp__322 = var_name_tmp__320;
  if ((((var_name_tmp__322 == 16u)&1))) {
    goto var_name_tmp__327;
  } else {
    goto var_name_tmp__328;
  }

var_name_tmp__327:
  var_name_tmp__323 = var_name_tmp__321;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank2_TypeDef*)(uintptr_t)UINT64_C(2684354656))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & (~((llvm_lshr_u32(var_name_tmp__323, 3))))))), 32, 4);
  goto var_name_tmp__329;

var_name_tmp__328:
  var_name_tmp__324 = var_name_tmp__320;
  if ((((var_name_tmp__324 == 256u)&1))) {
    goto var_name_tmp__330;
  } else {
    goto var_name_tmp__331;
  }

var_name_tmp__330:
  var_name_tmp__325 = var_name_tmp__321;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank3_TypeDef*)(uintptr_t)UINT64_C(2684354688))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~((llvm_lshr_u32(var_name_tmp__325, 3))))))), 32, 4);
  goto var_name_tmp__332;

var_name_tmp__331:
  var_name_tmp__326 = var_name_tmp__321;
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FSMC_Bank4_TypeDef*)(uintptr_t)UINT64_C(2684354720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & (~((llvm_lshr_u32(var_name_tmp__326, 3))))))), 32, 4);
  goto var_name_tmp__332;

var_name_tmp__332:
  goto var_name_tmp__329;

var_name_tmp__329:
  return;
}

