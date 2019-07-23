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
struct l_struct_struct_OC_CRYP_KeyInitTypeDef;
struct l_struct_struct_OC_CRYP_TypeDef;
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
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


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
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__3;
  uint64_t var_name_load_i16_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__4;
  uint64_t var_name_load_i16_8;
  uint64_t var_name_load_i32_10;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__5;
  uint64_t var_name_load_i16_14;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__6;
  uint64_t var_name_load_i16_17;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__7;
  uint64_t var_name_load_i16_20;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__8;
  uint64_t var_name_load_i16_23;
  uint64_t var_name_load_i32_25;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__9;
  uint64_t var_name_load_i16_29;
  uint64_t var_name_load_i32_31;
  uint64_t var_name_load_i32_34;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__10;
  uint64_t var_name_load_i16_38;
  uint64_t var_name_load_i32_40;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -57))), 32, 4);
  var_name_tmp__3 = var_name_tmp__2;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__3->field1)))), 16, 2);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_))))))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & -193))), 32, 4);
  var_name_tmp__4 = var_name_tmp__2;
  var_name_load_i16_8 = __adin_load_((((uint8_t*)((&var_name_tmp__4->field2)))), 16, 2);
  var_name_load_i32_10 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_10)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_8))))))), 32, 4);
  var_name_tmp__5 = var_name_tmp__2;
  var_name_load_i16_14 = __adin_load_((((uint8_t*)((&var_name_tmp__5->field1)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_14)))) == 32u)&1))) {
    goto var_name_tmp__11;
  } else {
    goto var_name_tmp__12;
  }

var_name_tmp__12:
  var_name_tmp__6 = var_name_tmp__2;
  var_name_load_i16_17 = __adin_load_((((uint8_t*)((&var_name_tmp__6->field1)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_17)))) == 40u)&1))) {
    goto var_name_tmp__11;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__13:
  var_name_tmp__7 = var_name_tmp__2;
  var_name_load_i16_20 = __adin_load_((((uint8_t*)((&var_name_tmp__7->field1)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_20)))) == 48u)&1))) {
    goto var_name_tmp__11;
  } else {
    goto var_name_tmp__14;
  }

var_name_tmp__14:
  var_name_tmp__8 = var_name_tmp__2;
  var_name_load_i16_23 = __adin_load_((((uint8_t*)((&var_name_tmp__8->field1)))), 16, 2);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_23)))) == 56u)&1))) {
    goto var_name_tmp__11;
  } else {
    goto var_name_tmp__15;
  }

var_name_tmp__11:
  var_name_load_i32_25 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_25)) & -769))), 32, 4);
  var_name_tmp__9 = var_name_tmp__2;
  var_name_load_i16_29 = __adin_load_((((uint8_t*)((&var_name_tmp__9->field3)))), 16, 2);
  var_name_load_i32_31 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_31)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_29))))))), 32, 4);
  goto var_name_tmp__15;

var_name_tmp__15:
  var_name_load_i32_34 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_34)) & -5))), 32, 4);
  var_name_tmp__10 = var_name_tmp__2;
  var_name_load_i16_38 = __adin_load_((((uint8_t*)((&var_name_tmp__10->field0)))), 16, 2);
  var_name_load_i32_40 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_40)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_38))))))), 32, 4);
}


void CRYP_StructInit(struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__16) {
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__17;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__18;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__19;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__20;
  struct l_struct_struct_OC_CRYP_InitTypeDef* var_name_tmp__21;

  var_name_tmp__17 = var_name_tmp__16;
  var_name_tmp__18 = var_name_tmp__17;
  __adin_store_((((uint8_t*)((&var_name_tmp__18->field0)))), UINT64_C(0), 16, 2);
  var_name_tmp__19 = var_name_tmp__17;
  __adin_store_((((uint8_t*)((&var_name_tmp__19->field1)))), UINT64_C(0), 16, 2);
  var_name_tmp__20 = var_name_tmp__17;
  __adin_store_((((uint8_t*)((&var_name_tmp__20->field2)))), UINT64_C(0), 16, 2);
  var_name_tmp__21 = var_name_tmp__17;
  __adin_store_((((uint8_t*)((&var_name_tmp__21->field3)))), UINT64_C(0), 16, 2);
}


void CRYP_KeyInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__22) {
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__23;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__24;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__25;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__26;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__27;
  uint64_t var_name_load_i32_10;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__28;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__29;
  uint64_t var_name_load_i32_18;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__30;
  uint64_t var_name_load_i32_22;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__31;
  uint64_t var_name_load_i32_26;

  var_name_tmp__23 = var_name_tmp__22;
  var_name_tmp__24 = var_name_tmp__23;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__24->field0)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field8))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__25 = var_name_tmp__23;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__25->field1)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field9))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_2)))), 32, 4);
  var_name_tmp__26 = var_name_tmp__23;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__26->field2)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field10))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_6)))), 32, 4);
  var_name_tmp__27 = var_name_tmp__23;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__27->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field11))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_10)))), 32, 4);
  var_name_tmp__28 = var_name_tmp__23;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__28->field4)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field12))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_14)))), 32, 4);
  var_name_tmp__29 = var_name_tmp__23;
  var_name_load_i32_18 = __adin_load_((((uint8_t*)((&var_name_tmp__29->field5)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field13))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_18)))), 32, 4);
  var_name_tmp__30 = var_name_tmp__23;
  var_name_load_i32_22 = __adin_load_((((uint8_t*)((&var_name_tmp__30->field6)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field14))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_22)))), 32, 4);
  var_name_tmp__31 = var_name_tmp__23;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__31->field7)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field15))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_26)))), 32, 4);
}


void CRYP_KeyStructInit(struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__32) {
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__33;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__34;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__35;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__36;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__37;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__38;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__39;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__40;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__41;

  var_name_tmp__33 = var_name_tmp__32;
  var_name_tmp__34 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__34->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__35 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__35->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__36 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__36->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__37 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__37->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__38 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__38->field4)))), UINT64_C(0), 32, 4);
  var_name_tmp__39 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__39->field5)))), UINT64_C(0), 32, 4);
  var_name_tmp__40 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__40->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__41 = var_name_tmp__33;
  __adin_store_((((uint8_t*)((&var_name_tmp__41->field7)))), UINT64_C(0), 32, 4);
}


void CRYP_IVInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__42) {
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__43;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__44;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__45;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__46;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__47;
  uint64_t var_name_load_i32_10;

  var_name_tmp__43 = var_name_tmp__42;
  var_name_tmp__44 = var_name_tmp__43;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__44->field0)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__45 = var_name_tmp__43;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__45->field1)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_2)))), 32, 4);
  var_name_tmp__46 = var_name_tmp__43;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__46->field2)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_6)))), 32, 4);
  var_name_tmp__47 = var_name_tmp__43;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__47->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_10)))), 32, 4);
}


void CRYP_IVStructInit(struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__48) {
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__49;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__50;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__51;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__52;
  struct l_struct_struct_OC_CRYP_IVInitTypeDef* var_name_tmp__53;

  var_name_tmp__49 = var_name_tmp__48;
  var_name_tmp__50 = var_name_tmp__49;
  __adin_store_((((uint8_t*)((&var_name_tmp__50->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__51 = var_name_tmp__49;
  __adin_store_((((uint8_t*)((&var_name_tmp__51->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__52 = var_name_tmp__49;
  __adin_store_((((uint8_t*)((&var_name_tmp__52->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__53 = var_name_tmp__49;
  __adin_store_((((uint8_t*)((&var_name_tmp__53->field3)))), UINT64_C(0), 32, 4);
}


void CRYP_FIFOFlush(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 16384))), 32, 4);
}


void CRYP_Cmd(uint32_t var_name_tmp__54) {
  uint32_t var_name_tmp__55;    /* Address-exposed local */
  uint32_t var_name_tmp__56;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__55 = var_name_tmp__54;
  var_name_tmp__56 = var_name_tmp__55;
  if ((((var_name_tmp__56 != 0u)&1))) {
    goto var_name_tmp__57;
  } else {
    goto var_name_tmp__58;
  }

var_name_tmp__57:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 32768))), 32, 4);
  goto var_name_tmp__59;

var_name_tmp__58:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -32769))), 32, 4);
  goto var_name_tmp__59;

var_name_tmp__59:
  return;
}


void CRYP_DataIn(uint32_t var_name_tmp__60) {
  uint32_t var_name_tmp__61;    /* Address-exposed local */
  uint32_t var_name_tmp__62;

  var_name_tmp__61 = var_name_tmp__60;
  var_name_tmp__62 = var_name_tmp__61;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field2))), (((uint64_t)(uint32_t)var_name_tmp__62)), 32, 4);
}


uint32_t CRYP_DataOut(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field3))), 32, 4);
  return (((uint32_t)var_name_load_i32_));
}


uint32_t CRYP_SaveContext(struct l_struct_struct_OC_CRYP_Context* var_name_tmp__63, struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__64) {
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__65;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__66;    /* Address-exposed local */
  uint32_t var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;    /* Address-exposed local */
  uint32_t var_name_tmp__69;    /* Address-exposed local */
  uint32_t var_name_tmp__70;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__71;
  uint64_t var_name_load_i32_6;
  uint64_t var_name_load_i32_11;
  uint32_t var_name_tmp__72;
  bool var_name_tmp__73;
  bool var_name_tmp__73__PHI_TEMPORARY;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__74;
  uint64_t var_name_load_i32_15;
  uint64_t var_name_load_i32_18;
  uint64_t var_name_load_i32_21;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__75;
  uint64_t var_name_load_i32_25;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__76;
  uint64_t var_name_load_i32_29;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__77;
  uint64_t var_name_load_i32_33;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__78;
  uint64_t var_name_load_i32_37;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__79;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__80;
  uint64_t var_name_load_i32_42;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__81;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__82;
  uint64_t var_name_load_i32_47;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__83;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__84;
  uint64_t var_name_load_i32_52;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__85;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__86;
  uint64_t var_name_load_i32_57;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__87;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__88;
  uint64_t var_name_load_i32_62;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__89;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__90;
  uint64_t var_name_load_i32_67;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__91;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__92;
  uint64_t var_name_load_i32_72;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__93;
  struct l_struct_struct_OC_CRYP_KeyInitTypeDef* var_name_tmp__94;
  uint64_t var_name_load_i32_77;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__95;
  uint32_t var_name_tmp__96;

  var_name_tmp__65 = var_name_tmp__63;
  var_name_tmp__66 = var_name_tmp__64;
  __adin_store_((((uint8_t*)(&var_name_tmp__67))), UINT64_C(0), 32, 4);
  var_name_tmp__68 = 0;
  var_name_tmp__70 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -2))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_1)) & 8) != 0u)&1))) {
    goto var_name_tmp__97;
  } else {
    goto var_name_tmp__98;
  }

var_name_tmp__97:
  var_name_tmp__68 = 17;
  goto var_name_tmp__99;

var_name_tmp__98:
  var_name_tmp__68 = 21;
  goto var_name_tmp__99;

var_name_tmp__99:
  goto var_name_tmp__100;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__100:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1))), 32, 4);
  var_name_tmp__71 = var_name_tmp__68;
  var_name_tmp__69 = ((((uint32_t)var_name_load_i32_3)) & var_name_tmp__71);
  var_name_load_i32_6 = __adin_load_((((uint8_t*)(&var_name_tmp__67))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__67))), (((uint64_t)(uint32_t)(llvm_add_u32((((uint32_t)var_name_load_i32_6)), 1)))), 32, 4);
  goto var_name_tmp__101;

var_name_tmp__101:
  var_name_load_i32_11 = __adin_load_((((uint8_t*)(&var_name_tmp__67))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_11)) != 65535u)&1))) {
    goto var_name_tmp__102;
  } else {
    var_name_tmp__73__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__103;
  }

var_name_tmp__102:
  var_name_tmp__72 = var_name_tmp__69;
  var_name_tmp__73__PHI_TEMPORARY = (((var_name_tmp__72 != 1u)&1));   /* for PHI node */
  goto var_name_tmp__103;

var_name_tmp__103:
  var_name_tmp__73 = ((var_name_tmp__73__PHI_TEMPORARY)&1);
  if (var_name_tmp__73) {
    goto var_name_tmp__100;
  } else {
    goto var_name_tmp__104;
  }

  } while (1); /* end of syntactic loop '' */
var_name_tmp__104:
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1))), 32, 4);
  var_name_tmp__74 = var_name_tmp__68;
  if ((((((((uint32_t)var_name_load_i32_13)) & var_name_tmp__74) != 1u)&1))) {
    goto var_name_tmp__105;
  } else {
    goto var_name_tmp__106;
  }

var_name_tmp__105:
  var_name_tmp__70 = 0;
  goto var_name_tmp__107;

var_name_tmp__106:
  var_name_load_i32_15 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_15)) & -3))), 32, 4);
  var_name_load_i32_18 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_18)) & -32769))), 32, 4);
  var_name_load_i32_21 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  var_name_tmp__75 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__75->field0)))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_21)) & 1020))), 32, 4);
  var_name_load_i32_25 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16))), 32, 4);
  var_name_tmp__76 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__76->field1)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_25)))), 32, 4);
  var_name_load_i32_29 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17))), 32, 4);
  var_name_tmp__77 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__77->field2)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_29)))), 32, 4);
  var_name_load_i32_33 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18))), 32, 4);
  var_name_tmp__78 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__78->field3)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_33)))), 32, 4);
  var_name_load_i32_37 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19))), 32, 4);
  var_name_tmp__79 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__79->field4)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_37)))), 32, 4);
  var_name_tmp__80 = var_name_tmp__66;
  var_name_load_i32_42 = __adin_load_((((uint8_t*)((&var_name_tmp__80->field0)))), 32, 4);
  var_name_tmp__81 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__81->field5)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_42)))), 32, 4);
  var_name_tmp__82 = var_name_tmp__66;
  var_name_load_i32_47 = __adin_load_((((uint8_t*)((&var_name_tmp__82->field1)))), 32, 4);
  var_name_tmp__83 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__83->field6)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_47)))), 32, 4);
  var_name_tmp__84 = var_name_tmp__66;
  var_name_load_i32_52 = __adin_load_((((uint8_t*)((&var_name_tmp__84->field2)))), 32, 4);
  var_name_tmp__85 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__85->field7)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_52)))), 32, 4);
  var_name_tmp__86 = var_name_tmp__66;
  var_name_load_i32_57 = __adin_load_((((uint8_t*)((&var_name_tmp__86->field3)))), 32, 4);
  var_name_tmp__87 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__87->field8)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_57)))), 32, 4);
  var_name_tmp__88 = var_name_tmp__66;
  var_name_load_i32_62 = __adin_load_((((uint8_t*)((&var_name_tmp__88->field4)))), 32, 4);
  var_name_tmp__89 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__89->field9)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_62)))), 32, 4);
  var_name_tmp__90 = var_name_tmp__66;
  var_name_load_i32_67 = __adin_load_((((uint8_t*)((&var_name_tmp__90->field5)))), 32, 4);
  var_name_tmp__91 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__91->field10)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_67)))), 32, 4);
  var_name_tmp__92 = var_name_tmp__66;
  var_name_load_i32_72 = __adin_load_((((uint8_t*)((&var_name_tmp__92->field6)))), 32, 4);
  var_name_tmp__93 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__93->field11)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_72)))), 32, 4);
  var_name_tmp__94 = var_name_tmp__66;
  var_name_load_i32_77 = __adin_load_((((uint8_t*)((&var_name_tmp__94->field7)))), 32, 4);
  var_name_tmp__95 = var_name_tmp__65;
  __adin_store_((((uint8_t*)((&var_name_tmp__95->field12)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_77)))), 32, 4);
  var_name_tmp__70 = 1;
  goto var_name_tmp__107;

var_name_tmp__107:
  var_name_tmp__96 = var_name_tmp__70;
  return var_name_tmp__96;
}


void CRYP_RestoreContext(struct l_struct_struct_OC_CRYP_Context* var_name_tmp__108) {
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__109;    /* Address-exposed local */
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__110;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__111;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__112;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__113;
  uint64_t var_name_load_i32_10;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__114;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__115;
  uint64_t var_name_load_i32_18;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__116;
  uint64_t var_name_load_i32_22;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__117;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__118;
  uint64_t var_name_load_i32_30;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__119;
  uint64_t var_name_load_i32_34;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__120;
  uint64_t var_name_load_i32_38;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__121;
  uint64_t var_name_load_i32_42;
  struct l_struct_struct_OC_CRYP_Context* var_name_tmp__122;
  uint64_t var_name_load_i32_46;
  uint64_t var_name_load_i32_49;

  var_name_tmp__109 = var_name_tmp__108;
  var_name_tmp__110 = var_name_tmp__109;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__110->field0)))), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_)))), 32, 4);
  var_name_tmp__111 = var_name_tmp__109;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__111->field5)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field8))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_2)))), 32, 4);
  var_name_tmp__112 = var_name_tmp__109;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__112->field6)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field9))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_6)))), 32, 4);
  var_name_tmp__113 = var_name_tmp__109;
  var_name_load_i32_10 = __adin_load_((((uint8_t*)((&var_name_tmp__113->field7)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field10))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_10)))), 32, 4);
  var_name_tmp__114 = var_name_tmp__109;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__114->field8)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field11))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_14)))), 32, 4);
  var_name_tmp__115 = var_name_tmp__109;
  var_name_load_i32_18 = __adin_load_((((uint8_t*)((&var_name_tmp__115->field9)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field12))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_18)))), 32, 4);
  var_name_tmp__116 = var_name_tmp__109;
  var_name_load_i32_22 = __adin_load_((((uint8_t*)((&var_name_tmp__116->field10)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field13))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_22)))), 32, 4);
  var_name_tmp__117 = var_name_tmp__109;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__117->field11)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field14))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_26)))), 32, 4);
  var_name_tmp__118 = var_name_tmp__109;
  var_name_load_i32_30 = __adin_load_((((uint8_t*)((&var_name_tmp__118->field12)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field15))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_30)))), 32, 4);
  var_name_tmp__119 = var_name_tmp__109;
  var_name_load_i32_34 = __adin_load_((((uint8_t*)((&var_name_tmp__119->field1)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field16))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_34)))), 32, 4);
  var_name_tmp__120 = var_name_tmp__109;
  var_name_load_i32_38 = __adin_load_((((uint8_t*)((&var_name_tmp__120->field2)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field17))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_38)))), 32, 4);
  var_name_tmp__121 = var_name_tmp__109;
  var_name_load_i32_42 = __adin_load_((((uint8_t*)((&var_name_tmp__121->field3)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field18))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_42)))), 32, 4);
  var_name_tmp__122 = var_name_tmp__109;
  var_name_load_i32_46 = __adin_load_((((uint8_t*)((&var_name_tmp__122->field4)))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field19))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_46)))), 32, 4);
  var_name_load_i32_49 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1342570496)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_49)) | 32768))), 32, 4);
}


void CRYP_DMACmd(uint8_t var_name_tmp__123, uint32_t var_name_tmp__124) {
  uint8_t var_name_tmp__125;    /* Address-exposed local */
  uint32_t var_name_tmp__126;    /* Address-exposed local */
  uint32_t var_name_tmp__127;
  uint8_t var_name_tmp__128;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__129;
  uint64_t var_name_load_i32_1;

  var_name_tmp__125 = var_name_tmp__123;
  var_name_tmp__126 = var_name_tmp__124;
  var_name_tmp__127 = var_name_tmp__126;
  if ((((var_name_tmp__127 != 0u)&1))) {
    goto var_name_tmp__130;
  } else {
    goto var_name_tmp__131;
  }

var_name_tmp__130:
  var_name_tmp__128 = var_name_tmp__125;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (((uint32_t)(uint8_t)var_name_tmp__128))))), 32, 4);
  goto var_name_tmp__132;

var_name_tmp__131:
  var_name_tmp__129 = var_name_tmp__125;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__129))))))))))), 32, 4);
  goto var_name_tmp__132;

var_name_tmp__132:
  return;
}


void CRYP_ITConfig(uint8_t var_name_tmp__133, uint32_t var_name_tmp__134) {
  uint8_t var_name_tmp__135;    /* Address-exposed local */
  uint32_t var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;
  uint8_t var_name_tmp__138;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__139;
  uint64_t var_name_load_i32_1;

  var_name_tmp__135 = var_name_tmp__133;
  var_name_tmp__136 = var_name_tmp__134;
  var_name_tmp__137 = var_name_tmp__136;
  if ((((var_name_tmp__137 != 0u)&1))) {
    goto var_name_tmp__140;
  } else {
    goto var_name_tmp__141;
  }

var_name_tmp__140:
  var_name_tmp__138 = var_name_tmp__135;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (((uint32_t)(uint8_t)var_name_tmp__138))))), 32, 4);
  goto var_name_tmp__142;

var_name_tmp__141:
  var_name_tmp__139 = var_name_tmp__135;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field5))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (((uint32_t)(uint8_t)(((uint8_t)(~((((uint32_t)(uint8_t)var_name_tmp__139))))))))))), 32, 4);
  goto var_name_tmp__142;

var_name_tmp__142:
  return;
}


uint32_t CRYP_GetITStatus(uint8_t var_name_tmp__143) {
  uint8_t var_name_tmp__144;    /* Address-exposed local */
  uint32_t var_name_tmp__145;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__146;
  uint32_t var_name_tmp__147;

  var_name_tmp__144 = var_name_tmp__143;
  var_name_tmp__145 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field7))), 32, 4);
  var_name_tmp__146 = var_name_tmp__144;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint8_t)var_name_tmp__146))) != 0u)&1))) {
    goto var_name_tmp__148;
  } else {
    goto var_name_tmp__149;
  }

var_name_tmp__148:
  var_name_tmp__145 = 1;
  goto var_name_tmp__150;

var_name_tmp__149:
  var_name_tmp__145 = 0;
  goto var_name_tmp__150;

var_name_tmp__150:
  var_name_tmp__147 = var_name_tmp__145;
  return var_name_tmp__147;
}


uint32_t CRYP_GetFlagStatus(uint8_t var_name_tmp__151) {
  uint8_t var_name_tmp__152;    /* Address-exposed local */
  uint32_t var_name_tmp__153;    /* Address-exposed local */
  uint32_t var_name_tmp__154;    /* Address-exposed local */
  uint8_t var_name_tmp__155;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__156;
  uint8_t var_name_tmp__157;
  uint32_t var_name_tmp__158;

  var_name_tmp__152 = var_name_tmp__151;
  var_name_tmp__153 = 0;
  var_name_tmp__154 = 0;
  var_name_tmp__155 = var_name_tmp__152;
  if ((((((((uint32_t)(uint8_t)var_name_tmp__155)) & 32) != 0u)&1))) {
    goto var_name_tmp__159;
  } else {
    goto var_name_tmp__160;
  }

var_name_tmp__159:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field6))), 32, 4);
  var_name_tmp__154 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__161;

var_name_tmp__160:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CRYP_TypeDef*)(uintptr_t)UINT64_C(1342570496))->field1))), 32, 4);
  var_name_tmp__154 = (((uint32_t)var_name_load_i32_1));
  goto var_name_tmp__161;

var_name_tmp__161:
  var_name_tmp__156 = var_name_tmp__154;
  var_name_tmp__157 = var_name_tmp__152;
  if (((((var_name_tmp__156 & (((uint32_t)(uint8_t)var_name_tmp__157))) != 0u)&1))) {
    goto var_name_tmp__162;
  } else {
    goto var_name_tmp__163;
  }

var_name_tmp__162:
  var_name_tmp__153 = 1;
  goto var_name_tmp__164;

var_name_tmp__163:
  var_name_tmp__153 = 0;
  goto var_name_tmp__164;

var_name_tmp__164:
  var_name_tmp__158 = var_name_tmp__153;
  return var_name_tmp__158;
}

