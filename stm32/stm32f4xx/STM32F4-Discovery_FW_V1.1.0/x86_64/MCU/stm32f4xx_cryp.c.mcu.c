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
struct l_struct_struct_OC_CRYP_InitTypeDef;
struct l_struct_struct_OC_CRYP_TypeDef;
struct l_struct_struct_OC_CRYP_KeyInitTypeDef;
struct l_struct_struct_OC_CRYP_IVInitTypeDef;
struct l_struct_struct_OC_CRYP_Context;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_CRYP_InitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
};
struct l_struct_struct_OC_CRYP_TypeDef {
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
  uint32_t field13;
  uint32_t field14;
  uint32_t field15;
  uint32_t field16;
  uint32_t field17;
  uint32_t field18;
  uint32_t field19;
};
struct l_struct_struct_OC_CRYP_KeyInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint32_t field6;
  uint32_t field7;
};
struct l_struct_struct_OC_CRYP_IVInitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_CRYP_Context {
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
};

/* Function Declarations */
void CRYP_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB2PeriphResetCmd(uint32_t, uint32_t);
void CRYP_Init(struct l_struct_struct_OC_CRYP_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_StructInit(struct l_struct_struct_OC_CRYP_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_KeyInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_KeyStructInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_IVInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_IVStructInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_FIFOFlush(void) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_Cmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_DataIn(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRYP_DataOut(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRYP_SaveContext(struct l_struct_struct_OC_CRYP_Context*, struct l_struct_struct_OC_CRYP_KeyInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_RestoreContext(struct l_struct_struct_OC_CRYP_Context*) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_DMACmd(uint8_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void CRYP_ITConfig(uint8_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRYP_GetITStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CRYP_GetFlagStatus(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}


/* Function Bodies */

void CRYP_DeInit(void) {
  RCC_AHB2PeriphResetCmd(16, 1);
  RCC_AHB2PeriphResetCmd(16, 0);
}


void CRYP_Init(struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__4;
  uint16_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__8;
  uint16_t var_name_tmp__9;
  uint32_t var_name_tmp__10;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__11;
  uint16_t var_name_tmp__12;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__13;
  uint16_t var_name_tmp__14;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__15;
  uint16_t var_name_tmp__16;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__17;
  uint16_t var_name_tmp__18;
  uint32_t var_name_tmp__19;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__20;
  uint16_t var_name_tmp__21;
  uint32_t var_name_tmp__22;
  uint32_t var_name_tmp__23;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__24;
  uint16_t var_name_tmp__25;
  uint32_t var_name_tmp__26;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__3 & -57);
  var_name_tmp__4 = var_name_tmp__2;
  var_name_tmp__5 = *((&var_name_tmp__4->field1));
  var_name_tmp__6 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__6 | (((uint32_t)(uint16_t)var_name_tmp__5)));
  var_name_tmp__7 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__7 & -193);
  var_name_tmp__8 = var_name_tmp__2;
  var_name_tmp__9 = *((&var_name_tmp__8->field2));
  var_name_tmp__10 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__10 | (((uint32_t)(uint16_t)var_name_tmp__9)));
  var_name_tmp__11 = var_name_tmp__2;
  var_name_tmp__12 = *((&var_name_tmp__11->field1));
  if (((((((uint32_t)(uint16_t)var_name_tmp__12)) == 32u)&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__28;
  }

var_name_tmp__28:
  var_name_tmp__13 = var_name_tmp__2;
  var_name_tmp__14 = *((&var_name_tmp__13->field1));
  if (((((((uint32_t)(uint16_t)var_name_tmp__14)) == 40u)&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__29;
  }

var_name_tmp__29:
  var_name_tmp__15 = var_name_tmp__2;
  var_name_tmp__16 = *((&var_name_tmp__15->field1));
  if (((((((uint32_t)(uint16_t)var_name_tmp__16)) == 48u)&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__30;
  }

var_name_tmp__30:
  var_name_tmp__17 = var_name_tmp__2;
  var_name_tmp__18 = *((&var_name_tmp__17->field1));
  if (((((((uint32_t)(uint16_t)var_name_tmp__18)) == 56u)&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__31;
  }

var_name_tmp__27:
  var_name_tmp__19 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__19 & -769);
  var_name_tmp__20 = var_name_tmp__2;
  var_name_tmp__21 = *((&var_name_tmp__20->field3));
  var_name_tmp__22 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__22 | (((uint32_t)(uint16_t)var_name_tmp__21)));
  goto var_name_tmp__31;

var_name_tmp__31:
  var_name_tmp__23 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__23 & -5);
  var_name_tmp__24 = var_name_tmp__2;
  var_name_tmp__25 = *((&var_name_tmp__24->field0));
  var_name_tmp__26 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__26 | (((uint32_t)(uint16_t)var_name_tmp__25)));
}


void CRYP_StructInit(struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__32) {
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__33;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__34;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__35;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__36;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__37;

  var_name_tmp__33 = var_name_tmp__32;
  var_name_tmp__34 = var_name_tmp__33;
  *((&var_name_tmp__34->field0)) = 0;
  var_name_tmp__35 = var_name_tmp__33;
  *((&var_name_tmp__35->field1)) = 0;
  var_name_tmp__36 = var_name_tmp__33;
  *((&var_name_tmp__36->field2)) = 0;
  var_name_tmp__37 = var_name_tmp__33;
  *((&var_name_tmp__37->field3)) = 0;
}


void CRYP_KeyInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__38) {
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__39;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__40;
  uint32_t var_name_tmp__41;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__42;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__44;
  uint32_t var_name_tmp__45;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__46;
  uint32_t var_name_tmp__47;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__48;
  uint32_t var_name_tmp__49;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__50;
  uint32_t var_name_tmp__51;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__52;
  uint32_t var_name_tmp__53;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__54;
  uint32_t var_name_tmp__55;

  var_name_tmp__39 = var_name_tmp__38;
  var_name_tmp__40 = var_name_tmp__39;
  var_name_tmp__41 = *((&var_name_tmp__40->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field8)) = var_name_tmp__41;
  var_name_tmp__42 = var_name_tmp__39;
  var_name_tmp__43 = *((&var_name_tmp__42->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field9)) = var_name_tmp__43;
  var_name_tmp__44 = var_name_tmp__39;
  var_name_tmp__45 = *((&var_name_tmp__44->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field10)) = var_name_tmp__45;
  var_name_tmp__46 = var_name_tmp__39;
  var_name_tmp__47 = *((&var_name_tmp__46->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field11)) = var_name_tmp__47;
  var_name_tmp__48 = var_name_tmp__39;
  var_name_tmp__49 = *((&var_name_tmp__48->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field12)) = var_name_tmp__49;
  var_name_tmp__50 = var_name_tmp__39;
  var_name_tmp__51 = *((&var_name_tmp__50->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field13)) = var_name_tmp__51;
  var_name_tmp__52 = var_name_tmp__39;
  var_name_tmp__53 = *((&var_name_tmp__52->field6));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field14)) = var_name_tmp__53;
  var_name_tmp__54 = var_name_tmp__39;
  var_name_tmp__55 = *((&var_name_tmp__54->field7));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field15)) = var_name_tmp__55;
}


void CRYP_KeyStructInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__56) {
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__57;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__58;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__59;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__60;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__61;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__62;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__63;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__64;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__65;

  var_name_tmp__57 = var_name_tmp__56;
  var_name_tmp__58 = var_name_tmp__57;
  *((&var_name_tmp__58->field0)) = 0;
  var_name_tmp__59 = var_name_tmp__57;
  *((&var_name_tmp__59->field1)) = 0;
  var_name_tmp__60 = var_name_tmp__57;
  *((&var_name_tmp__60->field2)) = 0;
  var_name_tmp__61 = var_name_tmp__57;
  *((&var_name_tmp__61->field3)) = 0;
  var_name_tmp__62 = var_name_tmp__57;
  *((&var_name_tmp__62->field4)) = 0;
  var_name_tmp__63 = var_name_tmp__57;
  *((&var_name_tmp__63->field5)) = 0;
  var_name_tmp__64 = var_name_tmp__57;
  *((&var_name_tmp__64->field6)) = 0;
  var_name_tmp__65 = var_name_tmp__57;
  *((&var_name_tmp__65->field7)) = 0;
}


void CRYP_IVInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__66) {
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__67;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__68;
  uint32_t var_name_tmp__69;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__70;
  uint32_t var_name_tmp__71;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__72;
  uint32_t var_name_tmp__73;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__74;
  uint32_t var_name_tmp__75;

  var_name_tmp__67 = var_name_tmp__66;
  var_name_tmp__68 = var_name_tmp__67;
  var_name_tmp__69 = *((&var_name_tmp__68->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16)) = var_name_tmp__69;
  var_name_tmp__70 = var_name_tmp__67;
  var_name_tmp__71 = *((&var_name_tmp__70->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17)) = var_name_tmp__71;
  var_name_tmp__72 = var_name_tmp__67;
  var_name_tmp__73 = *((&var_name_tmp__72->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18)) = var_name_tmp__73;
  var_name_tmp__74 = var_name_tmp__67;
  var_name_tmp__75 = *((&var_name_tmp__74->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19)) = var_name_tmp__75;
}


void CRYP_IVStructInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__76) {
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__77;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__78;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__79;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__80;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__81;

  var_name_tmp__77 = var_name_tmp__76;
  var_name_tmp__78 = var_name_tmp__77;
  *((&var_name_tmp__78->field0)) = 0;
  var_name_tmp__79 = var_name_tmp__77;
  *((&var_name_tmp__79->field1)) = 0;
  var_name_tmp__80 = var_name_tmp__77;
  *((&var_name_tmp__80->field2)) = 0;
  var_name_tmp__81 = var_name_tmp__77;
  *((&var_name_tmp__81->field3)) = 0;
}


void CRYP_FIFOFlush(void) {
  uint32_t var_name_tmp__82;

  var_name_tmp__82 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__82 | 16384);
}


void CRYP_Cmd(uint32_t var_name_tmp__83) {
  uint32_t var_name_tmp__84;    /* Address-exposed local */
  uint32_t var_name_tmp__85;
  uint32_t var_name_tmp__86;
  uint32_t var_name_tmp__87;

  var_name_tmp__84 = var_name_tmp__83;
  var_name_tmp__85 = var_name_tmp__84;
  if ((((var_name_tmp__85 != 0u)&1))) {
    goto var_name_tmp__88;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__88:
  var_name_tmp__86 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__86 | 32768);
  goto var_name_tmp__90;

var_name_tmp__89:
  var_name_tmp__87 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__87 & -32769);
  goto var_name_tmp__90;

var_name_tmp__90:
  return;
}


void CRYP_DataIn(uint32_t var_name_tmp__91) {
  uint32_t var_name_tmp__92;    /* Address-exposed local */
  uint32_t var_name_tmp__93;

  var_name_tmp__92 = var_name_tmp__91;
  var_name_tmp__93 = var_name_tmp__92;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field2)) = var_name_tmp__93;
}


uint32_t CRYP_DataOut(void) {
  uint32_t var_name_tmp__94;

  var_name_tmp__94 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field3));
  return var_name_tmp__94;
}


uint32_t CRYP_SaveContext(struct l_struct_struct_OC_CRYP_Context* var_name_tmp__95, struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__96) {
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__97;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  uint32_t var_name_tmp__103;
  uint32_t var_name_tmp__104;
  uint32_t var_name_tmp__105;
  uint32_t var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  uint32_t var_name_tmp__109;
  bool var_name_tmp__110;
  bool var_name_tmp__110__PHI_TEMPORARY;
  uint32_t var_name_tmp__111;
  uint32_t var_name_tmp__112;
  uint32_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  uint32_t var_name_tmp__115;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__116;
  uint32_t var_name_tmp__117;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__118;
  uint32_t var_name_tmp__119;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__120;
  uint32_t var_name_tmp__121;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__122;
  uint32_t var_name_tmp__123;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__124;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__125;
  uint32_t var_name_tmp__126;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__127;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__128;
  uint32_t var_name_tmp__129;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__130;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__131;
  uint32_t var_name_tmp__132;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__133;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__134;
  uint32_t var_name_tmp__135;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__136;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__137;
  uint32_t var_name_tmp__138;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__139;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__140;
  uint32_t var_name_tmp__141;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__142;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__143;
  uint32_t var_name_tmp__144;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__145;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__146;
  uint32_t var_name_tmp__147;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__148;
  uint32_t var_name_tmp__149;

  var_name_tmp__97 = var_name_tmp__95;
  var_name_tmp__98 = var_name_tmp__96;
  *(volatile uint32_t*)(&var_name_tmp__99) = 0;
  var_name_tmp__100 = 0;
  var_name_tmp__102 = 0;
  var_name_tmp__103 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4)) = (var_name_tmp__103 & -2);
  var_name_tmp__104 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  if (((((var_name_tmp__104 & 8) != 0u)&1))) {
    goto var_name_tmp__150;
  } else {
    goto var_name_tmp__151;
  }

var_name_tmp__150:
  var_name_tmp__100 = 17;
  goto var_name_tmp__152;

var_name_tmp__151:
  var_name_tmp__100 = 21;
  goto var_name_tmp__152;

var_name_tmp__152:
  goto var_name_tmp__153;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__153:
  var_name_tmp__105 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1));
  var_name_tmp__106 = var_name_tmp__100;
  var_name_tmp__101 = (var_name_tmp__105 & var_name_tmp__106);
  var_name_tmp__107 = *(volatile uint32_t*)(&var_name_tmp__99);
  *(volatile uint32_t*)(&var_name_tmp__99) = (llvm_add_u32(var_name_tmp__107, 1));
  goto var_name_tmp__154;

var_name_tmp__154:
  var_name_tmp__108 = *(volatile uint32_t*)(&var_name_tmp__99);
  if ((((var_name_tmp__108 != 65535u)&1))) {
    goto var_name_tmp__155;
  } else {
    var_name_tmp__110__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__156;
  }

var_name_tmp__155:
  var_name_tmp__109 = var_name_tmp__101;
  var_name_tmp__110__PHI_TEMPORARY = (((var_name_tmp__109 != 1u)&1));   /* for PHI node */
  goto var_name_tmp__156;

var_name_tmp__156:
  var_name_tmp__110 = ((var_name_tmp__110__PHI_TEMPORARY)&1);
  if (var_name_tmp__110) {
    goto var_name_tmp__153;
  } else {
    goto var_name_tmp__157;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__157:
  var_name_tmp__111 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1));
  var_name_tmp__112 = var_name_tmp__100;
  if (((((var_name_tmp__111 & var_name_tmp__112) != 1u)&1))) {
    goto var_name_tmp__158;
  } else {
    goto var_name_tmp__159;
  }

var_name_tmp__158:
  var_name_tmp__102 = 0;
  goto var_name_tmp__160;

var_name_tmp__159:
  var_name_tmp__113 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4)) = (var_name_tmp__113 & -3);
  var_name_tmp__114 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__114 & -32769);
  var_name_tmp__115 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  var_name_tmp__116 = var_name_tmp__97;
  *((&var_name_tmp__116->field0)) = (var_name_tmp__115 & 1020);
  var_name_tmp__117 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16));
  var_name_tmp__118 = var_name_tmp__97;
  *((&var_name_tmp__118->field1)) = var_name_tmp__117;
  var_name_tmp__119 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17));
  var_name_tmp__120 = var_name_tmp__97;
  *((&var_name_tmp__120->field2)) = var_name_tmp__119;
  var_name_tmp__121 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18));
  var_name_tmp__122 = var_name_tmp__97;
  *((&var_name_tmp__122->field3)) = var_name_tmp__121;
  var_name_tmp__123 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19));
  var_name_tmp__124 = var_name_tmp__97;
  *((&var_name_tmp__124->field4)) = var_name_tmp__123;
  var_name_tmp__125 = var_name_tmp__98;
  var_name_tmp__126 = *((&var_name_tmp__125->field0));
  var_name_tmp__127 = var_name_tmp__97;
  *((&var_name_tmp__127->field5)) = var_name_tmp__126;
  var_name_tmp__128 = var_name_tmp__98;
  var_name_tmp__129 = *((&var_name_tmp__128->field1));
  var_name_tmp__130 = var_name_tmp__97;
  *((&var_name_tmp__130->field6)) = var_name_tmp__129;
  var_name_tmp__131 = var_name_tmp__98;
  var_name_tmp__132 = *((&var_name_tmp__131->field2));
  var_name_tmp__133 = var_name_tmp__97;
  *((&var_name_tmp__133->field7)) = var_name_tmp__132;
  var_name_tmp__134 = var_name_tmp__98;
  var_name_tmp__135 = *((&var_name_tmp__134->field3));
  var_name_tmp__136 = var_name_tmp__97;
  *((&var_name_tmp__136->field8)) = var_name_tmp__135;
  var_name_tmp__137 = var_name_tmp__98;
  var_name_tmp__138 = *((&var_name_tmp__137->field4));
  var_name_tmp__139 = var_name_tmp__97;
  *((&var_name_tmp__139->field9)) = var_name_tmp__138;
  var_name_tmp__140 = var_name_tmp__98;
  var_name_tmp__141 = *((&var_name_tmp__140->field5));
  var_name_tmp__142 = var_name_tmp__97;
  *((&var_name_tmp__142->field10)) = var_name_tmp__141;
  var_name_tmp__143 = var_name_tmp__98;
  var_name_tmp__144 = *((&var_name_tmp__143->field6));
  var_name_tmp__145 = var_name_tmp__97;
  *((&var_name_tmp__145->field11)) = var_name_tmp__144;
  var_name_tmp__146 = var_name_tmp__98;
  var_name_tmp__147 = *((&var_name_tmp__146->field7));
  var_name_tmp__148 = var_name_tmp__97;
  *((&var_name_tmp__148->field12)) = var_name_tmp__147;
  var_name_tmp__102 = 1;
  goto var_name_tmp__160;

var_name_tmp__160:
  var_name_tmp__149 = var_name_tmp__102;
  return var_name_tmp__149;
}


void CRYP_RestoreContext(struct l_struct_struct_OC_CRYP_Context* var_name_tmp__161) {
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__162;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__163;
  uint32_t var_name_tmp__164;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__165;
  uint32_t var_name_tmp__166;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__167;
  uint32_t var_name_tmp__168;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__169;
  uint32_t var_name_tmp__170;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__171;
  uint32_t var_name_tmp__172;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__173;
  uint32_t var_name_tmp__174;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__175;
  uint32_t var_name_tmp__176;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__177;
  uint32_t var_name_tmp__178;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__179;
  uint32_t var_name_tmp__180;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__181;
  uint32_t var_name_tmp__182;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__183;
  uint32_t var_name_tmp__184;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__185;
  uint32_t var_name_tmp__186;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__187;
  uint32_t var_name_tmp__188;
  uint32_t var_name_tmp__189;

  var_name_tmp__162 = var_name_tmp__161;
  var_name_tmp__163 = var_name_tmp__162;
  var_name_tmp__164 = *((&var_name_tmp__163->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = var_name_tmp__164;
  var_name_tmp__165 = var_name_tmp__162;
  var_name_tmp__166 = *((&var_name_tmp__165->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field8)) = var_name_tmp__166;
  var_name_tmp__167 = var_name_tmp__162;
  var_name_tmp__168 = *((&var_name_tmp__167->field6));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field9)) = var_name_tmp__168;
  var_name_tmp__169 = var_name_tmp__162;
  var_name_tmp__170 = *((&var_name_tmp__169->field7));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field10)) = var_name_tmp__170;
  var_name_tmp__171 = var_name_tmp__162;
  var_name_tmp__172 = *((&var_name_tmp__171->field8));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field11)) = var_name_tmp__172;
  var_name_tmp__173 = var_name_tmp__162;
  var_name_tmp__174 = *((&var_name_tmp__173->field9));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field12)) = var_name_tmp__174;
  var_name_tmp__175 = var_name_tmp__162;
  var_name_tmp__176 = *((&var_name_tmp__175->field10));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field13)) = var_name_tmp__176;
  var_name_tmp__177 = var_name_tmp__162;
  var_name_tmp__178 = *((&var_name_tmp__177->field11));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field14)) = var_name_tmp__178;
  var_name_tmp__179 = var_name_tmp__162;
  var_name_tmp__180 = *((&var_name_tmp__179->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field15)) = var_name_tmp__180;
  var_name_tmp__181 = var_name_tmp__162;
  var_name_tmp__182 = *((&var_name_tmp__181->field1));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16)) = var_name_tmp__182;
  var_name_tmp__183 = var_name_tmp__162;
  var_name_tmp__184 = *((&var_name_tmp__183->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17)) = var_name_tmp__184;
  var_name_tmp__185 = var_name_tmp__162;
  var_name_tmp__186 = *((&var_name_tmp__185->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18)) = var_name_tmp__186;
  var_name_tmp__187 = var_name_tmp__162;
  var_name_tmp__188 = *((&var_name_tmp__187->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19)) = var_name_tmp__188;
  var_name_tmp__189 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field0)) = (var_name_tmp__189 | 32768);
}


void CRYP_DMACmd(uint8_t var_name_tmp__190, uint32_t var_name_tmp__191) {
  uint8_t var_name_tmp__192;    /* Address-exposed local */
  uint32_t var_name_tmp__193;    /* Address-exposed local */
  uint32_t var_name_tmp__194;
  uint8_t var_name_tmp__195;
  uint32_t var_name_tmp__196;
  uint8_t var_name_tmp__197;
  uint32_t var_name_tmp__198;

  var_name_tmp__192 = var_name_tmp__190;
  var_name_tmp__193 = var_name_tmp__191;
  var_name_tmp__194 = var_name_tmp__193;
  if ((((var_name_tmp__194 != 0u)&1))) {
    goto var_name_tmp__199;
  } else {
    goto var_name_tmp__200;
  }

var_name_tmp__199:
  var_name_tmp__195 = var_name_tmp__192;
  var_name_tmp__196 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4)) = (var_name_tmp__196 | (((uint32_t)(uint8_t)var_name_tmp__195)));
  goto var_name_tmp__201;

var_name_tmp__200:
  var_name_tmp__197 = var_name_tmp__192;
  var_name_tmp__198 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4)) = (var_name_tmp__198 & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__197)))))))));
  goto var_name_tmp__201;

var_name_tmp__201:
  return;
}


void CRYP_ITConfig(uint8_t var_name_tmp__202, uint32_t var_name_tmp__203) {
  uint8_t var_name_tmp__204;    /* Address-exposed local */
  uint32_t var_name_tmp__205;    /* Address-exposed local */
  uint32_t var_name_tmp__206;
  uint8_t var_name_tmp__207;
  uint32_t var_name_tmp__208;
  uint8_t var_name_tmp__209;
  uint32_t var_name_tmp__210;

  var_name_tmp__204 = var_name_tmp__202;
  var_name_tmp__205 = var_name_tmp__203;
  var_name_tmp__206 = var_name_tmp__205;
  if ((((var_name_tmp__206 != 0u)&1))) {
    goto var_name_tmp__211;
  } else {
    goto var_name_tmp__212;
  }

var_name_tmp__211:
  var_name_tmp__207 = var_name_tmp__204;
  var_name_tmp__208 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5)) = (var_name_tmp__208 | (((uint32_t)(uint8_t)var_name_tmp__207)));
  goto var_name_tmp__213;

var_name_tmp__212:
  var_name_tmp__209 = var_name_tmp__204;
  var_name_tmp__210 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5)) = (var_name_tmp__210 & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__209)))))))));
  goto var_name_tmp__213;

var_name_tmp__213:
  return;
}


uint32_t CRYP_GetITStatus(uint8_t var_name_tmp__214) {
  uint8_t var_name_tmp__215;    /* Address-exposed local */
  uint32_t var_name_tmp__216;    /* Address-exposed local */
  uint32_t var_name_tmp__217;
  uint8_t var_name_tmp__218;
  uint32_t var_name_tmp__219;

  var_name_tmp__215 = var_name_tmp__214;
  var_name_tmp__216 = 0;
  var_name_tmp__217 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field7));
  var_name_tmp__218 = var_name_tmp__215;
  if (((((var_name_tmp__217 & (((uint32_t)(uint8_t)var_name_tmp__218))) != 0u)&1))) {
    goto var_name_tmp__220;
  } else {
    goto var_name_tmp__221;
  }

var_name_tmp__220:
  var_name_tmp__216 = 1;
  goto var_name_tmp__222;

var_name_tmp__221:
  var_name_tmp__216 = 0;
  goto var_name_tmp__222;

var_name_tmp__222:
  var_name_tmp__219 = var_name_tmp__216;
  return var_name_tmp__219;
}


uint32_t CRYP_GetFlagStatus(uint8_t var_name_tmp__223) {
  uint8_t var_name_tmp__224;    /* Address-exposed local */
  uint32_t var_name_tmp__225;    /* Address-exposed local */
  uint32_t var_name_tmp__226;    /* Address-exposed local */
  uint8_t var_name_tmp__227;
  uint32_t var_name_tmp__228;
  uint32_t var_name_tmp__229;
  uint32_t var_name_tmp__230;
  uint8_t var_name_tmp__231;
  uint32_t var_name_tmp__232;

  var_name_tmp__224 = var_name_tmp__223;
  var_name_tmp__225 = 0;
  var_name_tmp__226 = 0;
  var_name_tmp__227 = var_name_tmp__224;
  if ((((((((uint32_t)(uint8_t)var_name_tmp__227)) & 32) != 0u)&1))) {
    goto var_name_tmp__233;
  } else {
    goto var_name_tmp__234;
  }

var_name_tmp__233:
  var_name_tmp__228 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field6));
  var_name_tmp__226 = var_name_tmp__228;
  goto var_name_tmp__235;

var_name_tmp__234:
  var_name_tmp__229 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1));
  var_name_tmp__226 = var_name_tmp__229;
  goto var_name_tmp__235;

var_name_tmp__235:
  var_name_tmp__230 = var_name_tmp__226;
  var_name_tmp__231 = var_name_tmp__224;
  if (((((var_name_tmp__230 & (((uint32_t)(uint8_t)var_name_tmp__231))) != 0u)&1))) {
    goto var_name_tmp__236;
  } else {
    goto var_name_tmp__237;
  }

var_name_tmp__236:
  var_name_tmp__225 = 1;
  goto var_name_tmp__238;

var_name_tmp__237:
  var_name_tmp__225 = 0;
  goto var_name_tmp__238;

var_name_tmp__238:
  var_name_tmp__232 = var_name_tmp__225;
  return var_name_tmp__232;
}

