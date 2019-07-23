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
struct l_struct_struct_OC_EXTI_TypeDef;
struct l_struct_struct_OC_EXTI_InitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_EXTI_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};
struct l_struct_struct_OC_EXTI_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};

/* Function Declarations */
void EXTI_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void EXTI_Init(struct l_struct_struct_OC_EXTI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void EXTI_StructInit(struct l_struct_struct_OC_EXTI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void EXTI_GenerateSWInterrupt(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t EXTI_GetFlagStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void EXTI_ClearFlag(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t EXTI_GetITStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void EXTI_ClearITPendingBit(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}


/* Function Bodies */

void EXTI_DeInit(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field0)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5)) = 8388607;
}


void EXTI_Init(struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__4;
  uint32_t var_name_tmp__5;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__6;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__9;
  uint32_t var_name_tmp__10;
  uint32_t var_name_tmp__11;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__12;
  uint32_t var_name_tmp__13;
  uint32_t var_name_tmp__14;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__15;
  uint32_t var_name_tmp__16;
  uint32_t var_name_tmp__17;
  uint32_t* var_name_tmp__18;
  uint32_t var_name_tmp__19;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__20;
  uint32_t var_name_tmp__21;
  uint32_t var_name_tmp__22;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__23;
  uint32_t var_name_tmp__24;
  uint32_t var_name_tmp__25;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__26;
  uint32_t var_name_tmp__27;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__28;
  uint32_t var_name_tmp__29;
  uint32_t var_name_tmp__30;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__31;
  uint32_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__34;
  uint32_t var_name_tmp__35;
  uint32_t var_name_tmp__36;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__37;
  uint32_t var_name_tmp__38;
  uint32_t var_name_tmp__39;
  uint32_t* var_name_tmp__40;
  uint32_t var_name_tmp__41;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__42;
  uint32_t var_name_tmp__43;
  uint32_t var_name_tmp__44;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__45;
  uint32_t var_name_tmp__46;
  uint32_t var_name_tmp__47;
  uint32_t* var_name_tmp__48;
  uint32_t var_name_tmp__49;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_tmp__3 = 1073822720u;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = *((&var_name_tmp__4->field3));
  if ((((var_name_tmp__5 != 0u)&1))) {
    goto var_name_tmp__50;
  } else {
    goto var_name_tmp__51;
  }

var_name_tmp__50:
  var_name_tmp__6 = var_name_tmp__2;
  var_name_tmp__7 = *((&var_name_tmp__6->field0));
  var_name_tmp__8 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field0)) = (var_name_tmp__8 & (~(var_name_tmp__7)));
  var_name_tmp__9 = var_name_tmp__2;
  var_name_tmp__10 = *((&var_name_tmp__9->field0));
  var_name_tmp__11 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1)) = (var_name_tmp__11 & (~(var_name_tmp__10)));
  var_name_tmp__12 = var_name_tmp__2;
  var_name_tmp__13 = *((&var_name_tmp__12->field1));
  var_name_tmp__14 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__14, var_name_tmp__13));
  var_name_tmp__15 = var_name_tmp__2;
  var_name_tmp__16 = *((&var_name_tmp__15->field0));
  var_name_tmp__17 = var_name_tmp__3;
  var_name_tmp__18 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__17)));
  var_name_tmp__19 = *(volatile uint32_t*)var_name_tmp__18;
  *(volatile uint32_t*)var_name_tmp__18 = (var_name_tmp__19 | var_name_tmp__16);
  var_name_tmp__20 = var_name_tmp__2;
  var_name_tmp__21 = *((&var_name_tmp__20->field0));
  var_name_tmp__22 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2)) = (var_name_tmp__22 & (~(var_name_tmp__21)));
  var_name_tmp__23 = var_name_tmp__2;
  var_name_tmp__24 = *((&var_name_tmp__23->field0));
  var_name_tmp__25 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3)) = (var_name_tmp__25 & (~(var_name_tmp__24)));
  var_name_tmp__26 = var_name_tmp__2;
  var_name_tmp__27 = *((&var_name_tmp__26->field2));
  if ((((var_name_tmp__27 == 16u)&1))) {
    goto var_name_tmp__52;
  } else {
    goto var_name_tmp__53;
  }

var_name_tmp__52:
  var_name_tmp__28 = var_name_tmp__2;
  var_name_tmp__29 = *((&var_name_tmp__28->field0));
  var_name_tmp__30 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2)) = (var_name_tmp__30 | var_name_tmp__29);
  var_name_tmp__31 = var_name_tmp__2;
  var_name_tmp__32 = *((&var_name_tmp__31->field0));
  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3)) = (var_name_tmp__33 | var_name_tmp__32);
  goto var_name_tmp__54;

var_name_tmp__53:
  var_name_tmp__3 = 1073822720u;
  var_name_tmp__34 = var_name_tmp__2;
  var_name_tmp__35 = *((&var_name_tmp__34->field2));
  var_name_tmp__36 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__36, var_name_tmp__35));
  var_name_tmp__37 = var_name_tmp__2;
  var_name_tmp__38 = *((&var_name_tmp__37->field0));
  var_name_tmp__39 = var_name_tmp__3;
  var_name_tmp__40 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__39)));
  var_name_tmp__41 = *(volatile uint32_t*)var_name_tmp__40;
  *(volatile uint32_t*)var_name_tmp__40 = (var_name_tmp__41 | var_name_tmp__38);
  goto var_name_tmp__54;

var_name_tmp__54:
  goto var_name_tmp__55;

var_name_tmp__51:
  var_name_tmp__42 = var_name_tmp__2;
  var_name_tmp__43 = *((&var_name_tmp__42->field1));
  var_name_tmp__44 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__44, var_name_tmp__43));
  var_name_tmp__45 = var_name_tmp__2;
  var_name_tmp__46 = *((&var_name_tmp__45->field0));
  var_name_tmp__47 = var_name_tmp__3;
  var_name_tmp__48 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__47)));
  var_name_tmp__49 = *(volatile uint32_t*)var_name_tmp__48;
  *(volatile uint32_t*)var_name_tmp__48 = (var_name_tmp__49 & (~(var_name_tmp__46)));
  goto var_name_tmp__55;

var_name_tmp__55:
  return;
}


void EXTI_StructInit(struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__56) {
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__57;    /* Address-exposed local */
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__58;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__59;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__60;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__61;

  var_name_tmp__57 = var_name_tmp__56;
  var_name_tmp__58 = var_name_tmp__57;
  *((&var_name_tmp__58->field0)) = 0;
  var_name_tmp__59 = var_name_tmp__57;
  *((&var_name_tmp__59->field1)) = 0;
  var_name_tmp__60 = var_name_tmp__57;
  *((&var_name_tmp__60->field2)) = 12;
  var_name_tmp__61 = var_name_tmp__57;
  *((&var_name_tmp__61->field3)) = 0;
}


void EXTI_GenerateSWInterrupt(uint32_t var_name_tmp__62) {
  uint32_t var_name_tmp__63;    /* Address-exposed local */
  uint32_t var_name_tmp__64;
  uint32_t var_name_tmp__65;

  var_name_tmp__63 = var_name_tmp__62;
  var_name_tmp__64 = var_name_tmp__63;
  var_name_tmp__65 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field4)) = (var_name_tmp__65 | var_name_tmp__64);
}


uint32_t EXTI_GetFlagStatus(uint32_t var_name_tmp__66) {
  uint32_t var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;    /* Address-exposed local */
  uint32_t var_name_tmp__69;
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;

  var_name_tmp__67 = var_name_tmp__66;
  var_name_tmp__68 = 0;
  var_name_tmp__69 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5));
  var_name_tmp__70 = var_name_tmp__67;
  if (((((var_name_tmp__69 & var_name_tmp__70) != 0u)&1))) {
    goto var_name_tmp__72;
  } else {
    goto var_name_tmp__73;
  }

var_name_tmp__72:
  var_name_tmp__68 = 1;
  goto var_name_tmp__74;

var_name_tmp__73:
  var_name_tmp__68 = 0;
  goto var_name_tmp__74;

var_name_tmp__74:
  var_name_tmp__71 = var_name_tmp__68;
  return var_name_tmp__71;
}


void EXTI_ClearFlag(uint32_t var_name_tmp__75) {
  uint32_t var_name_tmp__76;    /* Address-exposed local */
  uint32_t var_name_tmp__77;

  var_name_tmp__76 = var_name_tmp__75;
  var_name_tmp__77 = var_name_tmp__76;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5)) = var_name_tmp__77;
}


uint32_t EXTI_GetITStatus(uint32_t var_name_tmp__78) {
  uint32_t var_name_tmp__79;    /* Address-exposed local */
  uint32_t var_name_tmp__80;    /* Address-exposed local */
  uint32_t var_name_tmp__81;    /* Address-exposed local */
  uint32_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint32_t var_name_tmp__86;
  uint32_t var_name_tmp__87;

  var_name_tmp__79 = var_name_tmp__78;
  var_name_tmp__80 = 0;
  var_name_tmp__81 = 0;
  var_name_tmp__82 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field0));
  var_name_tmp__83 = var_name_tmp__79;
  var_name_tmp__81 = (var_name_tmp__82 & var_name_tmp__83);
  var_name_tmp__84 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5));
  var_name_tmp__85 = var_name_tmp__79;
  if (((((var_name_tmp__84 & var_name_tmp__85) != 0u)&1))) {
    goto var_name_tmp__88;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__88:
  var_name_tmp__86 = var_name_tmp__81;
  if ((((var_name_tmp__86 != 0u)&1))) {
    goto var_name_tmp__90;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__90:
  var_name_tmp__80 = 1;
  goto var_name_tmp__91;

var_name_tmp__89:
  var_name_tmp__80 = 0;
  goto var_name_tmp__91;

var_name_tmp__91:
  var_name_tmp__87 = var_name_tmp__80;
  return var_name_tmp__87;
}


void EXTI_ClearITPendingBit(uint32_t var_name_tmp__92) {
  uint32_t var_name_tmp__93;    /* Address-exposed local */
  uint32_t var_name_tmp__94;

  var_name_tmp__93 = var_name_tmp__92;
  var_name_tmp__94 = var_name_tmp__93;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5)) = var_name_tmp__94;
}

