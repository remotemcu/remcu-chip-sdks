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
struct l_struct_struct_OC_HASH_InitTypeDef;
struct l_struct_struct_OC_HASH_TypeDef;
struct l_struct_struct_OC_HASH_MsgDigest;
struct l_struct_struct_OC_HASH_Context;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_HASH_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_array_5_uint32_t {
  uint32_t array[5];
};
struct l_array_52_uint32_t {
  uint32_t array[52];
};
struct l_array_51_uint32_t {
  uint32_t array[51];
};
struct l_struct_struct_OC_HASH_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  struct l_array_5_uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  struct l_array_52_uint32_t field6;
  struct l_array_51_uint32_t field7;
};
struct l_struct_struct_OC_HASH_MsgDigest {
  struct l_array_5_uint32_t field0;
};
struct l_struct_struct_OC_HASH_Context {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  struct l_array_51_uint32_t field3;
};

/* Function Declarations */
void HASH_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphResetCmd(uint32_t, uint32_t);
void HASH_Init(struct l_struct_struct_OC_HASH_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_StructInit(struct l_struct_struct_OC_HASH_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_Reset(void) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_SetLastWordValidBitsNbr(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_DataIn(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t HASH_GetInFIFOWordsNbr(void) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_GetDigest(struct l_struct_struct_OC_HASH_MsgDigest*) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_StartDigest(void) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_SaveContext(struct l_struct_struct_OC_HASH_Context*) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_RestoreContext(struct l_struct_struct_OC_HASH_Context*) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_DMACmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_ITConfig(uint8_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t HASH_GetFlagStatus(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_ClearFlag(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t HASH_GetITStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void HASH_ClearITPendingBit(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint8_t llvm_add_u8(uint8_t a, uint8_t b) {
  uint8_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void HASH_DeInit(void) {
  RCC_AHB2PeriphResetCmd(32, 1);
  RCC_AHB2PeriphResetCmd(32, 0);
}


void HASH_Init(struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__4;
  uint32_t var_name_tmp__5;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__6;
  uint32_t var_name_tmp__7;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__8;
  uint32_t var_name_tmp__9;
  uint32_t var_name_tmp__10;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__11;
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__14;
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;
  uint32_t var_name_tmp__17;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__3 & -241);
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = *((&var_name_tmp__4->field0));
  var_name_tmp__6 = var_name_tmp__2;
  var_name_tmp__7 = *((&var_name_tmp__6->field2));
  var_name_tmp__8 = var_name_tmp__2;
  var_name_tmp__9 = *((&var_name_tmp__8->field1));
  var_name_tmp__10 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__10 | ((var_name_tmp__5 | var_name_tmp__7) | var_name_tmp__9));
  var_name_tmp__11 = var_name_tmp__2;
  var_name_tmp__12 = *((&var_name_tmp__11->field1));
  if ((((var_name_tmp__12 == 64u)&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  var_name_tmp__13 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__13 & -65537);
  var_name_tmp__14 = var_name_tmp__2;
  var_name_tmp__15 = *((&var_name_tmp__14->field3));
  var_name_tmp__16 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__16 | var_name_tmp__15);
  goto var_name_tmp__19;

var_name_tmp__19:
  var_name_tmp__17 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__17 | 4);
}


void HASH_StructInit(struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__20) {
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__21;    /* Address-exposed local */
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__22;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__23;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__24;
  struct l_struct_struct_OC_HASH_InitTypeDef* var_name_tmp__25;

  var_name_tmp__21 = var_name_tmp__20;
  var_name_tmp__22 = var_name_tmp__21;
  *((&var_name_tmp__22->field0)) = 0;
  var_name_tmp__23 = var_name_tmp__21;
  *((&var_name_tmp__23->field1)) = 0;
  var_name_tmp__24 = var_name_tmp__21;
  *((&var_name_tmp__24->field2)) = 0;
  var_name_tmp__25 = var_name_tmp__21;
  *((&var_name_tmp__25->field3)) = 0;
}


void HASH_Reset(void) {
  uint32_t var_name_tmp__26;

  var_name_tmp__26 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__26 | 4);
}


void HASH_SetLastWordValidBitsNbr(uint16_t var_name_tmp__27) {
  uint16_t var_name_tmp__28;    /* Address-exposed local */
  uint32_t var_name_tmp__29;
  uint16_t var_name_tmp__30;
  uint32_t var_name_tmp__31;

  var_name_tmp__28 = var_name_tmp__27;
  var_name_tmp__29 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2)) = (var_name_tmp__29 & -32);
  var_name_tmp__30 = var_name_tmp__28;
  var_name_tmp__31 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2)) = (var_name_tmp__31 | (((uint32_t)(uint16_t)var_name_tmp__30)));
}


void HASH_DataIn(uint32_t var_name_tmp__32) {
  uint32_t var_name_tmp__33;    /* Address-exposed local */
  uint32_t var_name_tmp__34;

  var_name_tmp__33 = var_name_tmp__32;
  var_name_tmp__34 = var_name_tmp__33;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field1)) = var_name_tmp__34;
}


uint8_t HASH_GetInFIFOWordsNbr(void) {
  uint32_t var_name_tmp__35;

  var_name_tmp__35 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  return (((uint8_t)(llvm_lshr_u32((var_name_tmp__35 & 3840), 8))));
}


void HASH_GetDigest(struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__36) {
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__37;    /* Address-exposed local */
  uint32_t var_name_tmp__38;
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__39;
  uint32_t var_name_tmp__40;
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__41;
  uint32_t var_name_tmp__42;
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__43;
  uint32_t var_name_tmp__44;
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__45;
  uint32_t var_name_tmp__46;
  struct l_struct_struct_OC_HASH_MsgDigest* var_name_tmp__47;

  var_name_tmp__37 = var_name_tmp__36;
  var_name_tmp__38 = *(volatile uint32_t*)((
    &((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field3[((int64_t)UINT64_C(0))]
    ));
  var_name_tmp__39 = var_name_tmp__37;
  *((&(*((&var_name_tmp__39->field0))).array[((int64_t)UINT64_C(0))])) = var_name_tmp__38;
  var_name_tmp__40 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field3[((int64_t)UINT64_C(1))]));
  var_name_tmp__41 = var_name_tmp__37;
  *((&(*((&var_name_tmp__41->field0))).array[((int64_t)UINT64_C(1))])) = var_name_tmp__40;
  var_name_tmp__42 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field3[((int64_t)UINT64_C(2))]));
  var_name_tmp__43 = var_name_tmp__37;
  *((&(*((&var_name_tmp__43->field0))).array[((int64_t)UINT64_C(2))])) = var_name_tmp__42;
  var_name_tmp__44 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field3[((int64_t)UINT64_C(3))]));
  var_name_tmp__45 = var_name_tmp__37;
  *((&(*((&var_name_tmp__45->field0))).array[((int64_t)UINT64_C(3))])) = var_name_tmp__44;
  var_name_tmp__46 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field3[((int64_t)UINT64_C(4))]));
  var_name_tmp__47 = var_name_tmp__37;
  *((&(*((&var_name_tmp__47->field0))).array[((int64_t)UINT64_C(4))])) = var_name_tmp__46;
}


void HASH_StartDigest(void) {
  uint32_t var_name_tmp__48;

  var_name_tmp__48 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2)) = (var_name_tmp__48 | 256);
}


void HASH_SaveContext(struct l_struct_struct_OC_HASH_Context* var_name_tmp__49) {
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__50;    /* Address-exposed local */
  uint8_t var_name_tmp__51;    /* Address-exposed local */
  uint32_t var_name_tmp__52;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__53;
  uint32_t var_name_tmp__54;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__55;
  uint32_t var_name_tmp__56;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__57;
  uint8_t var_name_tmp__58;
  uint8_t var_name_tmp__59;
  uint32_t var_name_tmp__60;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__61;
  uint8_t var_name_tmp__62;
  uint8_t var_name_tmp__63;

  var_name_tmp__50 = var_name_tmp__49;
  var_name_tmp__51 = 0;
  var_name_tmp__52 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4));
  var_name_tmp__53 = var_name_tmp__50;
  *((&var_name_tmp__53->field0)) = var_name_tmp__52;
  var_name_tmp__54 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2));
  var_name_tmp__55 = var_name_tmp__50;
  *((&var_name_tmp__55->field1)) = var_name_tmp__54;
  var_name_tmp__56 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  var_name_tmp__57 = var_name_tmp__50;
  *((&var_name_tmp__57->field2)) = var_name_tmp__56;
  var_name_tmp__51 = 0;
  goto var_name_tmp__64;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__64:
  var_name_tmp__58 = var_name_tmp__51;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__58))) <= ((int32_t)50u))&1))) {
    goto var_name_tmp__65;
  } else {
    goto var_name_tmp__66;
  }

var_name_tmp__65:
  var_name_tmp__59 = var_name_tmp__51;
  var_name_tmp__60 = *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field7))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__59)))]));
  var_name_tmp__61 = var_name_tmp__50;
  var_name_tmp__62 = var_name_tmp__51;
  *((&(*((&var_name_tmp__61->field3))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__62)))])) = var_name_tmp__60;
  goto var_name_tmp__67;

var_name_tmp__67:
  var_name_tmp__63 = var_name_tmp__51;
  var_name_tmp__51 = (llvm_add_u8(var_name_tmp__63, 1));
  goto var_name_tmp__64;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__66:
  return;
}


void HASH_RestoreContext(struct l_struct_struct_OC_HASH_Context* var_name_tmp__68) {
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__69;    /* Address-exposed local */
  uint8_t var_name_tmp__70;    /* Address-exposed local */
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__71;
  uint32_t var_name_tmp__72;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__73;
  uint32_t var_name_tmp__74;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__75;
  uint32_t var_name_tmp__76;
  uint32_t var_name_tmp__77;
  uint8_t var_name_tmp__78;
  struct l_struct_struct_OC_HASH_Context* var_name_tmp__79;
  uint8_t var_name_tmp__80;
  uint32_t var_name_tmp__81;
  uint8_t var_name_tmp__82;
  uint8_t var_name_tmp__83;

  var_name_tmp__69 = var_name_tmp__68;
  var_name_tmp__70 = 0;
  var_name_tmp__71 = var_name_tmp__69;
  var_name_tmp__72 = *((&var_name_tmp__71->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4)) = var_name_tmp__72;
  var_name_tmp__73 = var_name_tmp__69;
  var_name_tmp__74 = *((&var_name_tmp__73->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field2)) = var_name_tmp__74;
  var_name_tmp__75 = var_name_tmp__69;
  var_name_tmp__76 = *((&var_name_tmp__75->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = var_name_tmp__76;
  var_name_tmp__77 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__77 | 4);
  var_name_tmp__70 = 0;
  goto var_name_tmp__84;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__84:
  var_name_tmp__78 = var_name_tmp__70;
  if ((((((int32_t)(((uint32_t)(uint8_t)var_name_tmp__78))) <= ((int32_t)50u))&1))) {
    goto var_name_tmp__85;
  } else {
    goto var_name_tmp__86;
  }

var_name_tmp__85:
  var_name_tmp__79 = var_name_tmp__69;
  var_name_tmp__80 = var_name_tmp__70;
  var_name_tmp__81 = *((&(*((&var_name_tmp__79->field3))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__80)))]));
  var_name_tmp__82 = var_name_tmp__70;
  *(volatile uint32_t*)((&(*((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field7))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__82)))])) = var_name_tmp__81;
  goto var_name_tmp__87;

var_name_tmp__87:
  var_name_tmp__83 = var_name_tmp__70;
  var_name_tmp__70 = (llvm_add_u8(var_name_tmp__83, 1));
  goto var_name_tmp__84;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__86:
  return;
}


void HASH_DMACmd(uint32_t var_name_tmp__88) {
  uint32_t var_name_tmp__89;    /* Address-exposed local */
  uint32_t var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint32_t var_name_tmp__92;

  var_name_tmp__89 = var_name_tmp__88;
  var_name_tmp__90 = var_name_tmp__89;
  if ((((var_name_tmp__90 != 0u)&1))) {
    goto var_name_tmp__93;
  } else {
    goto var_name_tmp__94;
  }

var_name_tmp__93:
  var_name_tmp__91 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__91 | 8);
  goto var_name_tmp__95;

var_name_tmp__94:
  var_name_tmp__92 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0)) = (var_name_tmp__92 & -9);
  goto var_name_tmp__95;

var_name_tmp__95:
  return;
}


void HASH_ITConfig(uint8_t var_name_tmp__96, uint32_t var_name_tmp__97) {
  uint8_t var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;
  uint8_t var_name_tmp__101;
  uint32_t var_name_tmp__102;
  uint8_t var_name_tmp__103;
  uint32_t var_name_tmp__104;

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
  var_name_tmp__102 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4)) = (var_name_tmp__102 | (((uint32_t)(uint8_t)var_name_tmp__101)));
  goto var_name_tmp__107;

var_name_tmp__106:
  var_name_tmp__103 = var_name_tmp__98;
  var_name_tmp__104 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4)) = (var_name_tmp__104 & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__103)))))))));
  goto var_name_tmp__107;

var_name_tmp__107:
  return;
}


uint32_t HASH_GetFlagStatus(uint16_t var_name_tmp__108) {
  uint16_t var_name_tmp__109;    /* Address-exposed local */
  uint32_t var_name_tmp__110;    /* Address-exposed local */
  uint32_t var_name_tmp__111;    /* Address-exposed local */
  uint16_t var_name_tmp__112;
  uint32_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  uint32_t var_name_tmp__115;
  uint16_t var_name_tmp__116;
  uint32_t var_name_tmp__117;

  var_name_tmp__109 = var_name_tmp__108;
  var_name_tmp__110 = 0;
  var_name_tmp__111 = 0;
  var_name_tmp__112 = var_name_tmp__109;
  if ((((((((uint32_t)(uint16_t)var_name_tmp__112)) & 4096) != 0u)&1))) {
    goto var_name_tmp__118;
  } else {
    goto var_name_tmp__119;
  }

var_name_tmp__118:
  var_name_tmp__113 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field0));
  var_name_tmp__111 = var_name_tmp__113;
  goto var_name_tmp__120;

var_name_tmp__119:
  var_name_tmp__114 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field5));
  var_name_tmp__111 = var_name_tmp__114;
  goto var_name_tmp__120;

var_name_tmp__120:
  var_name_tmp__115 = var_name_tmp__111;
  var_name_tmp__116 = var_name_tmp__109;
  if (((((var_name_tmp__115 & (((uint32_t)(uint16_t)var_name_tmp__116))) != 0u)&1))) {
    goto var_name_tmp__121;
  } else {
    goto var_name_tmp__122;
  }

var_name_tmp__121:
  var_name_tmp__110 = 1;
  goto var_name_tmp__123;

var_name_tmp__122:
  var_name_tmp__110 = 0;
  goto var_name_tmp__123;

var_name_tmp__123:
  var_name_tmp__117 = var_name_tmp__110;
  return var_name_tmp__117;
}


void HASH_ClearFlag(uint16_t var_name_tmp__124) {
  uint16_t var_name_tmp__125;    /* Address-exposed local */
  uint16_t var_name_tmp__126;

  var_name_tmp__125 = var_name_tmp__124;
  var_name_tmp__126 = var_name_tmp__125;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field5)) = (~((((uint32_t)(uint16_t)var_name_tmp__126))));
}


uint32_t HASH_GetITStatus(uint8_t var_name_tmp__127) {
  uint8_t var_name_tmp__128;    /* Address-exposed local */
  uint32_t var_name_tmp__129;    /* Address-exposed local */
  uint32_t var_name_tmp__130;    /* Address-exposed local */
  uint32_t var_name_tmp__131;
  uint32_t var_name_tmp__132;
  uint32_t var_name_tmp__133;
  uint8_t var_name_tmp__134;
  uint32_t var_name_tmp__135;

  var_name_tmp__128 = var_name_tmp__127;
  var_name_tmp__129 = 0;
  var_name_tmp__130 = 0;
  var_name_tmp__131 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field5));
  var_name_tmp__130 = var_name_tmp__131;
  var_name_tmp__132 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field4));
  var_name_tmp__133 = var_name_tmp__130;
  var_name_tmp__134 = var_name_tmp__128;
  if ((((((var_name_tmp__132 & var_name_tmp__133) & (((uint32_t)(uint8_t)var_name_tmp__134))) != 0u)&1))) {
    goto var_name_tmp__136;
  } else {
    goto var_name_tmp__137;
  }

var_name_tmp__136:
  var_name_tmp__129 = 1;
  goto var_name_tmp__138;

var_name_tmp__137:
  var_name_tmp__129 = 0;
  goto var_name_tmp__138;

var_name_tmp__138:
  var_name_tmp__135 = var_name_tmp__129;
  return var_name_tmp__135;
}


void HASH_ClearITPendingBit(uint8_t var_name_tmp__139) {
  uint8_t var_name_tmp__140;    /* Address-exposed local */
  uint8_t var_name_tmp__141;

  var_name_tmp__140 = var_name_tmp__139;
  var_name_tmp__141 = var_name_tmp__140;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_HASH_TypeDef*)(uintptr_t)UINT64_C(1342571520))->field5)) = (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__141))))))));
}

