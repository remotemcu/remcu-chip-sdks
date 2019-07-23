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
struct l_struct_struct_OC_DCMI_TypeDef;
struct l_struct_struct_OC_DCMI_InitTypeDef;
struct l_struct_struct_OC_DCMI_CROPInitTypeDef;
struct l_struct_struct_OC_DCMI_CodesInitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_DCMI_TypeDef {
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
};
struct l_struct_struct_OC_DCMI_InitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint16_t field5;
  uint16_t field6;
};
struct l_struct_struct_OC_DCMI_CROPInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
};
struct l_struct_struct_OC_DCMI_CodesInitTypeDef {
  uint8_t field0;
  uint8_t field1;
  uint8_t field2;
  uint8_t field3;
};

/* Function Declarations */
void DCMI_DeInit(void) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_Init(struct l_struct_struct_OC_DCMI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_StructInit(struct l_struct_struct_OC_DCMI_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_CROPConfig(struct l_struct_struct_OC_DCMI_CROPInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_CROPCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_SetEmbeddedSynchroCodes(struct l_struct_struct_OC_DCMI_CodesInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_JPEGCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_Cmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_CaptureCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DCMI_ReadData(void) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_ITConfig(uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DCMI_GetFlagStatus(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_ClearFlag(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DCMI_GetITStatus(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void DCMI_ClearITPendingBit(uint16_t) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void DCMI_DeInit(void) {
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5)) = 31;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field6)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field7)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field8)) = 0;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field9)) = 0;
}


void DCMI_Init(struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint32_t var_name_tmp__4;
  uint32_t var_name_tmp__5;
  uint32_t var_name_tmp__6;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__7;
  uint16_t var_name_tmp__8;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__9;
  uint16_t var_name_tmp__10;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__11;
  uint16_t var_name_tmp__12;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__13;
  uint16_t var_name_tmp__14;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__15;
  uint16_t var_name_tmp__16;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__17;
  uint16_t var_name_tmp__18;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__19;
  uint16_t var_name_tmp__20;
  uint32_t var_name_tmp__21;
  uint32_t var_name_tmp__22;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_tmp__4 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__4 & -16386);
  var_name_tmp__5 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  var_name_tmp__3 = var_name_tmp__5;
  var_name_tmp__6 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__6 & -4083);
  var_name_tmp__7 = var_name_tmp__2;
  var_name_tmp__8 = *((&var_name_tmp__7->field0));
  var_name_tmp__9 = var_name_tmp__2;
  var_name_tmp__10 = *((&var_name_tmp__9->field1));
  var_name_tmp__11 = var_name_tmp__2;
  var_name_tmp__12 = *((&var_name_tmp__11->field2));
  var_name_tmp__13 = var_name_tmp__2;
  var_name_tmp__14 = *((&var_name_tmp__13->field3));
  var_name_tmp__15 = var_name_tmp__2;
  var_name_tmp__16 = *((&var_name_tmp__15->field4));
  var_name_tmp__17 = var_name_tmp__2;
  var_name_tmp__18 = *((&var_name_tmp__17->field5));
  var_name_tmp__19 = var_name_tmp__2;
  var_name_tmp__20 = *((&var_name_tmp__19->field6));
  var_name_tmp__21 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__21 | (((((((((uint32_t)(uint16_t)var_name_tmp__8)) | (((uint32_t)(uint16_t)var_name_tmp__10))) | (((uint32_t)(uint16_t)var_name_tmp__12))) | (((uint32_t)(uint16_t)var_name_tmp__14))) | (((uint32_t)(uint16_t)var_name_tmp__16))) | (((uint32_t)(uint16_t)var_name_tmp__18))) | (((uint32_t)(uint16_t)var_name_tmp__20))));
  var_name_tmp__22 = var_name_tmp__3;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = var_name_tmp__22;
}


void DCMI_StructInit(struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__23) {
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__24;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__25;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__26;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__27;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__28;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__29;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__30;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__31;

  var_name_tmp__24 = var_name_tmp__23;
  var_name_tmp__25 = var_name_tmp__24;
  *((&var_name_tmp__25->field0)) = 0;
  var_name_tmp__26 = var_name_tmp__24;
  *((&var_name_tmp__26->field1)) = 0;
  var_name_tmp__27 = var_name_tmp__24;
  *((&var_name_tmp__27->field2)) = 0;
  var_name_tmp__28 = var_name_tmp__24;
  *((&var_name_tmp__28->field3)) = 0;
  var_name_tmp__29 = var_name_tmp__24;
  *((&var_name_tmp__29->field4)) = 0;
  var_name_tmp__30 = var_name_tmp__24;
  *((&var_name_tmp__30->field5)) = 0;
  var_name_tmp__31 = var_name_tmp__24;
  *((&var_name_tmp__31->field6)) = 0;
}


void DCMI_CROPConfig(struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__32) {
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__33;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__34;
  uint16_t var_name_tmp__35;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__36;
  uint16_t var_name_tmp__37;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__38;
  uint16_t var_name_tmp__39;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__40;
  uint16_t var_name_tmp__41;

  var_name_tmp__33 = var_name_tmp__32;
  var_name_tmp__34 = var_name_tmp__33;
  var_name_tmp__35 = *((&var_name_tmp__34->field1));
  var_name_tmp__36 = var_name_tmp__33;
  var_name_tmp__37 = *((&var_name_tmp__36->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field8)) = ((((uint32_t)(uint16_t)var_name_tmp__35)) | ((((uint32_t)(uint16_t)var_name_tmp__37)) << 16));
  var_name_tmp__38 = var_name_tmp__33;
  var_name_tmp__39 = *((&var_name_tmp__38->field3));
  var_name_tmp__40 = var_name_tmp__33;
  var_name_tmp__41 = *((&var_name_tmp__40->field2));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field9)) = ((((uint32_t)(uint16_t)var_name_tmp__39)) | ((((uint32_t)(uint16_t)var_name_tmp__41)) << 16));
}


void DCMI_CROPCmd(uint32_t var_name_tmp__42) {
  uint32_t var_name_tmp__43;    /* Address-exposed local */
  uint32_t var_name_tmp__44;
  uint32_t var_name_tmp__45;
  uint32_t var_name_tmp__46;

  var_name_tmp__43 = var_name_tmp__42;
  var_name_tmp__44 = var_name_tmp__43;
  if ((((var_name_tmp__44 != 0u)&1))) {
    goto var_name_tmp__47;
  } else {
    goto var_name_tmp__48;
  }

var_name_tmp__47:
  var_name_tmp__45 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__45 | 4);
  goto var_name_tmp__49;

var_name_tmp__48:
  var_name_tmp__46 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__46 & -5);
  goto var_name_tmp__49;

var_name_tmp__49:
  return;
}


void DCMI_SetEmbeddedSynchroCodes(struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__50) {
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__51;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__52;
  uint8_t var_name_tmp__53;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__54;
  uint8_t var_name_tmp__55;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__56;
  uint8_t var_name_tmp__57;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__58;
  uint8_t var_name_tmp__59;

  var_name_tmp__51 = var_name_tmp__50;
  var_name_tmp__52 = var_name_tmp__51;
  var_name_tmp__53 = *((&var_name_tmp__52->field0));
  var_name_tmp__54 = var_name_tmp__51;
  var_name_tmp__55 = *((&var_name_tmp__54->field1));
  var_name_tmp__56 = var_name_tmp__51;
  var_name_tmp__57 = *((&var_name_tmp__56->field2));
  var_name_tmp__58 = var_name_tmp__51;
  var_name_tmp__59 = *((&var_name_tmp__58->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field6)) = ((((((uint32_t)(uint8_t)var_name_tmp__53)) | ((((uint32_t)(uint8_t)var_name_tmp__55)) << 8)) | ((((uint32_t)(uint8_t)var_name_tmp__57)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__59)) << 24));
}


void DCMI_JPEGCmd(uint32_t var_name_tmp__60) {
  uint32_t var_name_tmp__61;    /* Address-exposed local */
  uint32_t var_name_tmp__62;
  uint32_t var_name_tmp__63;
  uint32_t var_name_tmp__64;

  var_name_tmp__61 = var_name_tmp__60;
  var_name_tmp__62 = var_name_tmp__61;
  if ((((var_name_tmp__62 != 0u)&1))) {
    goto var_name_tmp__65;
  } else {
    goto var_name_tmp__66;
  }

var_name_tmp__65:
  var_name_tmp__63 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__63 | 8);
  goto var_name_tmp__67;

var_name_tmp__66:
  var_name_tmp__64 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__64 & -9);
  goto var_name_tmp__67;

var_name_tmp__67:
  return;
}


void DCMI_Cmd(uint32_t var_name_tmp__68) {
  uint32_t var_name_tmp__69;    /* Address-exposed local */
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;
  uint32_t var_name_tmp__72;

  var_name_tmp__69 = var_name_tmp__68;
  var_name_tmp__70 = var_name_tmp__69;
  if ((((var_name_tmp__70 != 0u)&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  var_name_tmp__71 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__71 | 16384);
  goto var_name_tmp__75;

var_name_tmp__74:
  var_name_tmp__72 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__72 & -16385);
  goto var_name_tmp__75;

var_name_tmp__75:
  return;
}


void DCMI_CaptureCmd(uint32_t var_name_tmp__76) {
  uint32_t var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;
  uint32_t var_name_tmp__79;
  uint32_t var_name_tmp__80;

  var_name_tmp__77 = var_name_tmp__76;
  var_name_tmp__78 = var_name_tmp__77;
  if ((((var_name_tmp__78 != 0u)&1))) {
    goto var_name_tmp__81;
  } else {
    goto var_name_tmp__82;
  }

var_name_tmp__81:
  var_name_tmp__79 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__79 | 1);
  goto var_name_tmp__83;

var_name_tmp__82:
  var_name_tmp__80 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field0)) = (var_name_tmp__80 & -2);
  goto var_name_tmp__83;

var_name_tmp__83:
  return;
}


uint32_t DCMI_ReadData(void) {
  uint32_t var_name_tmp__84;

  var_name_tmp__84 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field10));
  return var_name_tmp__84;
}


void DCMI_ITConfig(uint16_t var_name_tmp__85, uint32_t var_name_tmp__86) {
  uint16_t var_name_tmp__87;    /* Address-exposed local */
  uint32_t var_name_tmp__88;    /* Address-exposed local */
  uint32_t var_name_tmp__89;
  uint16_t var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint16_t var_name_tmp__92;
  uint32_t var_name_tmp__93;

  var_name_tmp__87 = var_name_tmp__85;
  var_name_tmp__88 = var_name_tmp__86;
  var_name_tmp__89 = var_name_tmp__88;
  if ((((var_name_tmp__89 != 0u)&1))) {
    goto var_name_tmp__94;
  } else {
    goto var_name_tmp__95;
  }

var_name_tmp__94:
  var_name_tmp__90 = var_name_tmp__87;
  var_name_tmp__91 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3)) = (var_name_tmp__91 | (((uint32_t)(uint16_t)var_name_tmp__90)));
  goto var_name_tmp__96;

var_name_tmp__95:
  var_name_tmp__92 = var_name_tmp__87;
  var_name_tmp__93 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3)) = (var_name_tmp__93 & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__92)))))))));
  goto var_name_tmp__96;

var_name_tmp__96:
  return;
}


uint32_t DCMI_GetFlagStatus(uint16_t var_name_tmp__97) {
  uint16_t var_name_tmp__98;    /* Address-exposed local */
  uint32_t var_name_tmp__99;    /* Address-exposed local */
  uint32_t var_name_tmp__100;    /* Address-exposed local */
  uint32_t var_name_tmp__101;    /* Address-exposed local */
  uint16_t var_name_tmp__102;
  uint32_t var_name_tmp__103;
  uint32_t var_name_tmp__104;
  uint32_t var_name_tmp__105;
  uint32_t var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  uint16_t var_name_tmp__109;
  uint32_t var_name_tmp__110;

  var_name_tmp__98 = var_name_tmp__97;
  var_name_tmp__99 = 0;
  var_name_tmp__101 = 0;
  var_name_tmp__102 = var_name_tmp__98;
  var_name_tmp__100 = (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__102)), 12));
  var_name_tmp__103 = var_name_tmp__100;
  if ((((var_name_tmp__103 == 1u)&1))) {
    goto var_name_tmp__111;
  } else {
    goto var_name_tmp__112;
  }

var_name_tmp__111:
  var_name_tmp__104 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field2));
  var_name_tmp__101 = var_name_tmp__104;
  goto var_name_tmp__113;

var_name_tmp__112:
  var_name_tmp__105 = var_name_tmp__100;
  if ((((var_name_tmp__105 == 2u)&1))) {
    goto var_name_tmp__114;
  } else {
    goto var_name_tmp__115;
  }

var_name_tmp__114:
  var_name_tmp__106 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field1));
  var_name_tmp__101 = var_name_tmp__106;
  goto var_name_tmp__116;

var_name_tmp__115:
  var_name_tmp__107 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field4));
  var_name_tmp__101 = var_name_tmp__107;
  goto var_name_tmp__116;

var_name_tmp__116:
  goto var_name_tmp__113;

var_name_tmp__113:
  var_name_tmp__108 = var_name_tmp__101;
  var_name_tmp__109 = var_name_tmp__98;
  if (((((var_name_tmp__108 & (((uint32_t)(uint16_t)var_name_tmp__109))) != 0u)&1))) {
    goto var_name_tmp__117;
  } else {
    goto var_name_tmp__118;
  }

var_name_tmp__117:
  var_name_tmp__99 = 1;
  goto var_name_tmp__119;

var_name_tmp__118:
  var_name_tmp__99 = 0;
  goto var_name_tmp__119;

var_name_tmp__119:
  var_name_tmp__110 = var_name_tmp__99;
  return var_name_tmp__110;
}


void DCMI_ClearFlag(uint16_t var_name_tmp__120) {
  uint16_t var_name_tmp__121;    /* Address-exposed local */
  uint16_t var_name_tmp__122;

  var_name_tmp__121 = var_name_tmp__120;
  var_name_tmp__122 = var_name_tmp__121;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5)) = (((uint32_t)(uint16_t)var_name_tmp__122));
}


uint32_t DCMI_GetITStatus(uint16_t var_name_tmp__123) {
  uint16_t var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;    /* Address-exposed local */
  uint32_t var_name_tmp__126;    /* Address-exposed local */
  uint32_t var_name_tmp__127;
  uint16_t var_name_tmp__128;
  uint32_t var_name_tmp__129;
  uint32_t var_name_tmp__130;

  var_name_tmp__124 = var_name_tmp__123;
  var_name_tmp__125 = 0;
  var_name_tmp__126 = 0;
  var_name_tmp__127 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field4));
  var_name_tmp__128 = var_name_tmp__124;
  var_name_tmp__126 = (var_name_tmp__127 & (((uint32_t)(uint16_t)var_name_tmp__128)));
  var_name_tmp__129 = var_name_tmp__126;
  if ((((var_name_tmp__129 != 0u)&1))) {
    goto var_name_tmp__131;
  } else {
    goto var_name_tmp__132;
  }

var_name_tmp__131:
  var_name_tmp__125 = 1;
  goto var_name_tmp__133;

var_name_tmp__132:
  var_name_tmp__125 = 0;
  goto var_name_tmp__133;

var_name_tmp__133:
  var_name_tmp__130 = var_name_tmp__125;
  return var_name_tmp__130;
}


void DCMI_ClearITPendingBit(uint16_t var_name_tmp__134) {
  uint16_t var_name_tmp__135;    /* Address-exposed local */
  uint16_t var_name_tmp__136;

  var_name_tmp__135 = var_name_tmp__134;
  var_name_tmp__136 = var_name_tmp__135;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5)) = (((uint32_t)(uint16_t)var_name_tmp__136));
}

