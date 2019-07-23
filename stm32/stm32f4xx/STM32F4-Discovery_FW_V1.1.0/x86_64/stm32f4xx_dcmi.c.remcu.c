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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void DCMI_DeInit(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5))), UINT64_C(31), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field6))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field7))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field8))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field9))), UINT64_C(0), 32, 4);
}


void DCMI_Init(struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__4;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__5;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__6;
  uint64_t var_name_load_i16_4;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__7;
  uint64_t var_name_load_i16_7;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__8;
  uint64_t var_name_load_i16_10;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__9;
  uint64_t var_name_load_i16_13;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__10;
  uint64_t var_name_load_i16_16;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__11;
  uint64_t var_name_load_i16_19;
  uint32_t var_name_tmp__12;
  uint32_t var_name_tmp__13;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -16386))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  var_name_tmp__3 = (((uint32_t)var_name_load_i32_1));
  var_name_tmp__4 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__4 & -4083);
  var_name_tmp__5 = var_name_tmp__2;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__5->field0)))), 16, 2);
  var_name_tmp__6 = var_name_tmp__2;
  var_name_load_i16_4 = __adin_load_((((uint8_t*)((&var_name_tmp__6->field1)))), 16, 2);
  var_name_tmp__7 = var_name_tmp__2;
  var_name_load_i16_7 = __adin_load_((((uint8_t*)((&var_name_tmp__7->field2)))), 16, 2);
  var_name_tmp__8 = var_name_tmp__2;
  var_name_load_i16_10 = __adin_load_((((uint8_t*)((&var_name_tmp__8->field3)))), 16, 2);
  var_name_tmp__9 = var_name_tmp__2;
  var_name_load_i16_13 = __adin_load_((((uint8_t*)((&var_name_tmp__9->field4)))), 16, 2);
  var_name_tmp__10 = var_name_tmp__2;
  var_name_load_i16_16 = __adin_load_((((uint8_t*)((&var_name_tmp__10->field5)))), 16, 2);
  var_name_tmp__11 = var_name_tmp__2;
  var_name_load_i16_19 = __adin_load_((((uint8_t*)((&var_name_tmp__11->field6)))), 16, 2);
  var_name_tmp__12 = var_name_tmp__3;
  var_name_tmp__3 = (var_name_tmp__12 | (((((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_4))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_7))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_10))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_13))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_16))))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_19))))));
  var_name_tmp__13 = var_name_tmp__3;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)var_name_tmp__13)), 32, 4);
}


void DCMI_StructInit(struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__14) {
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__15;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__16;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__17;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__18;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__19;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__20;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__21;
  struct l_struct_struct_OC_DCMI_InitTypeDef* var_name_tmp__22;

  var_name_tmp__15 = var_name_tmp__14;
  var_name_tmp__16 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__16->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__17 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__17->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__18 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__18->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__19 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__19->field3)))), UINT64_C(0), 16, 2);
  var_name_tmp__20 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__20->field4)))), UINT64_C(0), 16, 2);
  var_name_tmp__21 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__21->field5)))), UINT64_C(0), 16, 2);
  var_name_tmp__22 = var_name_tmp__15;
  __adin_store_((((uint8_t*)((&var_name_tmp__22->field6)))), UINT64_C(0), 16, 2);
}


void DCMI_CROPConfig(struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__23) {
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__24;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__25;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__26;
  uint64_t var_name_load_i16_2;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__27;
  uint64_t var_name_load_i16_5;
  struct l_struct_struct_OC_DCMI_CROPInitTypeDef* var_name_tmp__28;
  uint64_t var_name_load_i16_8;

  var_name_tmp__24 = var_name_tmp__23;
  var_name_tmp__25 = var_name_tmp__24;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__25->field1)))), 16, 2);
  var_name_tmp__26 = var_name_tmp__24;
  var_name_load_i16_2 = __adin_load_((((uint8_t*)((&var_name_tmp__26->field0)))), 16, 2);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field8))), (((uint64_t)(uint32_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) | ((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_2)))) << 16)))), 32, 4);
  var_name_tmp__27 = var_name_tmp__24;
  var_name_load_i16_5 = __adin_load_((((uint8_t*)((&var_name_tmp__27->field3)))), 16, 2);
  var_name_tmp__28 = var_name_tmp__24;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__28->field2)))), 16, 2);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field9))), (((uint64_t)(uint32_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_5)))) | ((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8)))) << 16)))), 32, 4);
}


void DCMI_CROPCmd(uint32_t var_name_tmp__29) {
  uint32_t var_name_tmp__30;    /* Address-exposed local */
  uint32_t var_name_tmp__31;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__30 = var_name_tmp__29;
  var_name_tmp__31 = var_name_tmp__30;
  if ((((var_name_tmp__31 != 0u)&1))) {
    goto var_name_tmp__32;
  } else {
    goto var_name_tmp__33;
  }

var_name_tmp__32:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 4))), 32, 4);
  goto var_name_tmp__34;

var_name_tmp__33:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -5))), 32, 4);
  goto var_name_tmp__34;

var_name_tmp__34:
  return;
}


void DCMI_SetEmbeddedSynchroCodes(struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__35) {
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__36;    /* Address-exposed local */
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__37;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__38;
  uint64_t var_name_load_i8_1;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__39;
  uint64_t var_name_load_i8_3;
  struct l_struct_struct_OC_DCMI_CodesInitTypeDef* var_name_tmp__40;
  uint64_t var_name_load_i8_5;

  var_name_tmp__36 = var_name_tmp__35;
  var_name_tmp__37 = var_name_tmp__36;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__37->field0)), 8, 1);
  var_name_tmp__38 = var_name_tmp__36;
  var_name_load_i8_1 = __adin_load_(((&var_name_tmp__38->field1)), 8, 1);
  var_name_tmp__39 = var_name_tmp__36;
  var_name_load_i8_3 = __adin_load_(((&var_name_tmp__39->field2)), 8, 1);
  var_name_tmp__40 = var_name_tmp__36;
  var_name_load_i8_5 = __adin_load_(((&var_name_tmp__40->field3)), 8, 1);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field6))), (((uint64_t)(uint32_t)((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_1)))) << 8)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_3)))) << 16)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_5)))) << 24)))), 32, 4);
}


void DCMI_JPEGCmd(uint32_t var_name_tmp__41) {
  uint32_t var_name_tmp__42;    /* Address-exposed local */
  uint32_t var_name_tmp__43;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__42 = var_name_tmp__41;
  var_name_tmp__43 = var_name_tmp__42;
  if ((((var_name_tmp__43 != 0u)&1))) {
    goto var_name_tmp__44;
  } else {
    goto var_name_tmp__45;
  }

var_name_tmp__44:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 8))), 32, 4);
  goto var_name_tmp__46;

var_name_tmp__45:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -9))), 32, 4);
  goto var_name_tmp__46;

var_name_tmp__46:
  return;
}


void DCMI_Cmd(uint32_t var_name_tmp__47) {
  uint32_t var_name_tmp__48;    /* Address-exposed local */
  uint32_t var_name_tmp__49;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__48 = var_name_tmp__47;
  var_name_tmp__49 = var_name_tmp__48;
  if ((((var_name_tmp__49 != 0u)&1))) {
    goto var_name_tmp__50;
  } else {
    goto var_name_tmp__51;
  }

var_name_tmp__50:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 16384))), 32, 4);
  goto var_name_tmp__52;

var_name_tmp__51:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -16385))), 32, 4);
  goto var_name_tmp__52;

var_name_tmp__52:
  return;
}


void DCMI_CaptureCmd(uint32_t var_name_tmp__53) {
  uint32_t var_name_tmp__54;    /* Address-exposed local */
  uint32_t var_name_tmp__55;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__54 = var_name_tmp__53;
  var_name_tmp__55 = var_name_tmp__54;
  if ((((var_name_tmp__55 != 0u)&1))) {
    goto var_name_tmp__56;
  } else {
    goto var_name_tmp__57;
  }

var_name_tmp__56:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  goto var_name_tmp__58;

var_name_tmp__57:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342504960)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -2))), 32, 4);
  goto var_name_tmp__58;

var_name_tmp__58:
  return;
}


uint32_t DCMI_ReadData(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field10))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


void DCMI_ITConfig(uint16_t var_name_tmp__59, uint32_t var_name_tmp__60) {
  uint16_t var_name_tmp__61;    /* Address-exposed local */
  uint32_t var_name_tmp__62;    /* Address-exposed local */
  uint32_t var_name_tmp__63;
  uint16_t var_name_tmp__64;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__65;
  uint64_t var_name_load_i32_1;

  var_name_tmp__61 = var_name_tmp__59;
  var_name_tmp__62 = var_name_tmp__60;
  var_name_tmp__63 = var_name_tmp__62;
  if ((((var_name_tmp__63 != 0u)&1))) {
    goto var_name_tmp__66;
  } else {
    goto var_name_tmp__67;
  }

var_name_tmp__66:
  var_name_tmp__64 = var_name_tmp__61;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (((uint32_t)(uint16_t)var_name_tmp__64))))), 32, 4);
  goto var_name_tmp__68;

var_name_tmp__67:
  var_name_tmp__65 = var_name_tmp__61;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (((uint32_t)(uint16_t)(((uint16_t)(~((((uint32_t)(uint16_t)var_name_tmp__65))))))))))), 32, 4);
  goto var_name_tmp__68;

var_name_tmp__68:
  return;
}


uint32_t DCMI_GetFlagStatus(uint16_t var_name_tmp__69) {
  uint16_t var_name_tmp__70;    /* Address-exposed local */
  uint32_t var_name_tmp__71;    /* Address-exposed local */
  uint32_t var_name_tmp__72;    /* Address-exposed local */
  uint32_t var_name_tmp__73;    /* Address-exposed local */
  uint16_t var_name_tmp__74;
  uint32_t var_name_tmp__75;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__76;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__77;
  uint16_t var_name_tmp__78;
  uint32_t var_name_tmp__79;

  var_name_tmp__70 = var_name_tmp__69;
  var_name_tmp__71 = 0;
  var_name_tmp__73 = 0;
  var_name_tmp__74 = var_name_tmp__70;
  var_name_tmp__72 = (llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__74)), 12));
  var_name_tmp__75 = var_name_tmp__72;
  if ((((var_name_tmp__75 == 1u)&1))) {
    goto var_name_tmp__80;
  } else {
    goto var_name_tmp__81;
  }

var_name_tmp__80:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field2))), 32, 4);
  var_name_tmp__73 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__82;

var_name_tmp__81:
  var_name_tmp__76 = var_name_tmp__72;
  if ((((var_name_tmp__76 == 2u)&1))) {
    goto var_name_tmp__83;
  } else {
    goto var_name_tmp__84;
  }

var_name_tmp__83:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field1))), 32, 4);
  var_name_tmp__73 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__85;

var_name_tmp__84:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field4))), 32, 4);
  var_name_tmp__73 = (((uint32_t)var_name_load_i32_3));
  goto var_name_tmp__85;

var_name_tmp__85:
  goto var_name_tmp__82;

var_name_tmp__82:
  var_name_tmp__77 = var_name_tmp__73;
  var_name_tmp__78 = var_name_tmp__70;
  if (((((var_name_tmp__77 & (((uint32_t)(uint16_t)var_name_tmp__78))) != 0u)&1))) {
    goto var_name_tmp__86;
  } else {
    goto var_name_tmp__87;
  }

var_name_tmp__86:
  var_name_tmp__71 = 1;
  goto var_name_tmp__88;

var_name_tmp__87:
  var_name_tmp__71 = 0;
  goto var_name_tmp__88;

var_name_tmp__88:
  var_name_tmp__79 = var_name_tmp__71;
  return var_name_tmp__79;
}


void DCMI_ClearFlag(uint16_t var_name_tmp__89) {
  uint16_t var_name_tmp__90;    /* Address-exposed local */
  uint16_t var_name_tmp__91;

  var_name_tmp__90 = var_name_tmp__89;
  var_name_tmp__91 = var_name_tmp__90;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__91)))), 32, 4);
}


uint32_t DCMI_GetITStatus(uint16_t var_name_tmp__92) {
  uint16_t var_name_tmp__93;    /* Address-exposed local */
  uint32_t var_name_tmp__94;    /* Address-exposed local */
  uint32_t var_name_tmp__95;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__96;
  uint32_t var_name_tmp__97;
  uint32_t var_name_tmp__98;

  var_name_tmp__93 = var_name_tmp__92;
  var_name_tmp__94 = 0;
  var_name_tmp__95 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field4))), 32, 4);
  var_name_tmp__96 = var_name_tmp__93;
  var_name_tmp__95 = ((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint16_t)var_name_tmp__96)));
  var_name_tmp__97 = var_name_tmp__95;
  if ((((var_name_tmp__97 != 0u)&1))) {
    goto var_name_tmp__99;
  } else {
    goto var_name_tmp__100;
  }

var_name_tmp__99:
  var_name_tmp__94 = 1;
  goto var_name_tmp__101;

var_name_tmp__100:
  var_name_tmp__94 = 0;
  goto var_name_tmp__101;

var_name_tmp__101:
  var_name_tmp__98 = var_name_tmp__94;
  return var_name_tmp__98;
}


void DCMI_ClearITPendingBit(uint16_t var_name_tmp__102) {
  uint16_t var_name_tmp__103;    /* Address-exposed local */
  uint16_t var_name_tmp__104;

  var_name_tmp__103 = var_name_tmp__102;
  var_name_tmp__104 = var_name_tmp__103;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DCMI_TypeDef*)(uintptr_t)UINT64_C(1342504960))->field5))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__104)))), 32, 4);
}

