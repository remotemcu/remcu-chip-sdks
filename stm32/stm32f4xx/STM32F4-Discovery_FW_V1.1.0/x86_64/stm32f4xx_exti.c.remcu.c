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

void EXTI_DeInit(void) {
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073822720)), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3))), UINT64_C(0), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5))), UINT64_C(8388607), 32, 4);
}


void EXTI_Init(struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;    /* Address-exposed local */
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__4;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__5;
  uint64_t var_name_load_i32_2;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__6;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_9;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__7;
  uint64_t var_name_load_i32_13;
  uint32_t var_name_tmp__8;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__9;
  uint64_t var_name_load_i32_16;
  uint32_t var_name_tmp__10;
  uint32_t* var_name_tmp__11;
  uint64_t var_name_load_i32_19;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__12;
  uint64_t var_name_load_i32_24;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__13;
  uint64_t var_name_load_i32_30;
  uint64_t var_name_load_i32_32;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__14;
  uint64_t var_name_load_i32_36;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__15;
  uint64_t var_name_load_i32_39;
  uint64_t var_name_load_i32_41;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__16;
  uint64_t var_name_load_i32_45;
  uint64_t var_name_load_i32_47;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__17;
  uint64_t var_name_load_i32_51;
  uint32_t var_name_tmp__18;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__19;
  uint64_t var_name_load_i32_54;
  uint32_t var_name_tmp__20;
  uint32_t* var_name_tmp__21;
  uint64_t var_name_load_i32_57;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__22;
  uint64_t var_name_load_i32_62;
  uint32_t var_name_tmp__23;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__24;
  uint64_t var_name_load_i32_65;
  uint32_t var_name_tmp__25;
  uint32_t* var_name_tmp__26;
  uint64_t var_name_load_i32_68;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = 0;
  var_name_tmp__3 = 1073822720u;
  var_name_tmp__4 = var_name_tmp__2;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__4->field3)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) != 0u)&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__28;
  }

var_name_tmp__27:
  var_name_tmp__5 = var_name_tmp__2;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__5->field0)))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073822720)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073822720)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & (~((((uint32_t)var_name_load_i32_2))))))), 32, 4);
  var_name_tmp__6 = var_name_tmp__2;
  var_name_load_i32_7 = __adin_load_((((uint8_t*)((&var_name_tmp__6->field0)))), 32, 4);
  var_name_load_i32_9 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field1))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_9)) & (~((((uint32_t)var_name_load_i32_7))))))), 32, 4);
  var_name_tmp__7 = var_name_tmp__2;
  var_name_load_i32_13 = __adin_load_((((uint8_t*)((&var_name_tmp__7->field1)))), 32, 4);
  var_name_tmp__8 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__8, (((uint32_t)var_name_load_i32_13))));
  var_name_tmp__9 = var_name_tmp__2;
  var_name_load_i32_16 = __adin_load_((((uint8_t*)((&var_name_tmp__9->field0)))), 32, 4);
  var_name_tmp__10 = var_name_tmp__3;
  var_name_tmp__11 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__10)));
  var_name_load_i32_19 = __adin_load_((((uint8_t*)var_name_tmp__11)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__11)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_19)) | (((uint32_t)var_name_load_i32_16))))), 32, 4);
  var_name_tmp__12 = var_name_tmp__2;
  var_name_load_i32_24 = __adin_load_((((uint8_t*)((&var_name_tmp__12->field0)))), 32, 4);
  var_name_load_i32_26 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_26)) & (~((((uint32_t)var_name_load_i32_24))))))), 32, 4);
  var_name_tmp__13 = var_name_tmp__2;
  var_name_load_i32_30 = __adin_load_((((uint8_t*)((&var_name_tmp__13->field0)))), 32, 4);
  var_name_load_i32_32 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_32)) & (~((((uint32_t)var_name_load_i32_30))))))), 32, 4);
  var_name_tmp__14 = var_name_tmp__2;
  var_name_load_i32_36 = __adin_load_((((uint8_t*)((&var_name_tmp__14->field2)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_36)) == 16u)&1))) {
    goto var_name_tmp__29;
  } else {
    goto var_name_tmp__30;
  }

var_name_tmp__29:
  var_name_tmp__15 = var_name_tmp__2;
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&var_name_tmp__15->field0)))), 32, 4);
  var_name_load_i32_41 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field2))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_41)) | (((uint32_t)var_name_load_i32_39))))), 32, 4);
  var_name_tmp__16 = var_name_tmp__2;
  var_name_load_i32_45 = __adin_load_((((uint8_t*)((&var_name_tmp__16->field0)))), 32, 4);
  var_name_load_i32_47 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field3))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_47)) | (((uint32_t)var_name_load_i32_45))))), 32, 4);
  goto var_name_tmp__31;

var_name_tmp__30:
  var_name_tmp__3 = 1073822720u;
  var_name_tmp__17 = var_name_tmp__2;
  var_name_load_i32_51 = __adin_load_((((uint8_t*)((&var_name_tmp__17->field2)))), 32, 4);
  var_name_tmp__18 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__18, (((uint32_t)var_name_load_i32_51))));
  var_name_tmp__19 = var_name_tmp__2;
  var_name_load_i32_54 = __adin_load_((((uint8_t*)((&var_name_tmp__19->field0)))), 32, 4);
  var_name_tmp__20 = var_name_tmp__3;
  var_name_tmp__21 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__20)));
  var_name_load_i32_57 = __adin_load_((((uint8_t*)var_name_tmp__21)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__21)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_57)) | (((uint32_t)var_name_load_i32_54))))), 32, 4);
  goto var_name_tmp__31;

var_name_tmp__31:
  goto var_name_tmp__32;

var_name_tmp__28:
  var_name_tmp__22 = var_name_tmp__2;
  var_name_load_i32_62 = __adin_load_((((uint8_t*)((&var_name_tmp__22->field1)))), 32, 4);
  var_name_tmp__23 = var_name_tmp__3;
  var_name_tmp__3 = (llvm_add_u32(var_name_tmp__23, (((uint32_t)var_name_load_i32_62))));
  var_name_tmp__24 = var_name_tmp__2;
  var_name_load_i32_65 = __adin_load_((((uint8_t*)((&var_name_tmp__24->field0)))), 32, 4);
  var_name_tmp__25 = var_name_tmp__3;
  var_name_tmp__26 = ((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__25)));
  var_name_load_i32_68 = __adin_load_((((uint8_t*)var_name_tmp__26)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__26)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_68)) & (~((((uint32_t)var_name_load_i32_65))))))), 32, 4);
  goto var_name_tmp__32;

var_name_tmp__32:
  return;
}


void EXTI_StructInit(struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__33) {
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__34;    /* Address-exposed local */
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__35;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__36;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__37;
  struct l_struct_struct_OC_EXTI_InitTypeDef* var_name_tmp__38;

  var_name_tmp__34 = var_name_tmp__33;
  var_name_tmp__35 = var_name_tmp__34;
  __adin_store_((((uint8_t*)((&var_name_tmp__35->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__36 = var_name_tmp__34;
  __adin_store_((((uint8_t*)((&var_name_tmp__36->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__37 = var_name_tmp__34;
  __adin_store_((((uint8_t*)((&var_name_tmp__37->field2)))), UINT64_C(12), 32, 4);
  var_name_tmp__38 = var_name_tmp__34;
  __adin_store_((((uint8_t*)((&var_name_tmp__38->field3)))), UINT64_C(0), 32, 4);
}


void EXTI_GenerateSWInterrupt(uint32_t var_name_tmp__39) {
  uint32_t var_name_tmp__40;    /* Address-exposed local */
  uint32_t var_name_tmp__41;
  uint64_t var_name_load_i32_;

  var_name_tmp__40 = var_name_tmp__39;
  var_name_tmp__41 = var_name_tmp__40;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__41))), 32, 4);
}


uint32_t EXTI_GetFlagStatus(uint32_t var_name_tmp__42) {
  uint32_t var_name_tmp__43;    /* Address-exposed local */
  uint32_t var_name_tmp__44;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__45;
  uint32_t var_name_tmp__46;

  var_name_tmp__43 = var_name_tmp__42;
  var_name_tmp__44 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5))), 32, 4);
  var_name_tmp__45 = var_name_tmp__43;
  if ((((((((uint32_t)var_name_load_i32_)) & var_name_tmp__45) != 0u)&1))) {
    goto var_name_tmp__47;
  } else {
    goto var_name_tmp__48;
  }

var_name_tmp__47:
  var_name_tmp__44 = 1;
  goto var_name_tmp__49;

var_name_tmp__48:
  var_name_tmp__44 = 0;
  goto var_name_tmp__49;

var_name_tmp__49:
  var_name_tmp__46 = var_name_tmp__44;
  return var_name_tmp__46;
}


void EXTI_ClearFlag(uint32_t var_name_tmp__50) {
  uint32_t var_name_tmp__51;    /* Address-exposed local */
  uint32_t var_name_tmp__52;

  var_name_tmp__51 = var_name_tmp__50;
  var_name_tmp__52 = var_name_tmp__51;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5))), (((uint64_t)(uint32_t)var_name_tmp__52)), 32, 4);
}


uint32_t EXTI_GetITStatus(uint32_t var_name_tmp__53) {
  uint32_t var_name_tmp__54;    /* Address-exposed local */
  uint32_t var_name_tmp__55;    /* Address-exposed local */
  uint32_t var_name_tmp__56;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__57;
  uint64_t var_name_load_i32_1;
  uint32_t var_name_tmp__58;
  uint32_t var_name_tmp__59;
  uint32_t var_name_tmp__60;

  var_name_tmp__54 = var_name_tmp__53;
  var_name_tmp__55 = 0;
  var_name_tmp__56 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073822720)), 32, 4);
  var_name_tmp__57 = var_name_tmp__54;
  var_name_tmp__56 = ((((uint32_t)var_name_load_i32_)) & var_name_tmp__57);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5))), 32, 4);
  var_name_tmp__58 = var_name_tmp__54;
  if ((((((((uint32_t)var_name_load_i32_1)) & var_name_tmp__58) != 0u)&1))) {
    goto var_name_tmp__61;
  } else {
    goto var_name_tmp__62;
  }

var_name_tmp__61:
  var_name_tmp__59 = var_name_tmp__56;
  if ((((var_name_tmp__59 != 0u)&1))) {
    goto var_name_tmp__63;
  } else {
    goto var_name_tmp__62;
  }

var_name_tmp__63:
  var_name_tmp__55 = 1;
  goto var_name_tmp__64;

var_name_tmp__62:
  var_name_tmp__55 = 0;
  goto var_name_tmp__64;

var_name_tmp__64:
  var_name_tmp__60 = var_name_tmp__55;
  return var_name_tmp__60;
}


void EXTI_ClearITPendingBit(uint32_t var_name_tmp__65) {
  uint32_t var_name_tmp__66;    /* Address-exposed local */
  uint32_t var_name_tmp__67;

  var_name_tmp__66 = var_name_tmp__65;
  var_name_tmp__67 = var_name_tmp__66;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_EXTI_TypeDef*)(uintptr_t)UINT64_C(1073822720))->field5))), (((uint64_t)(uint32_t)var_name_tmp__67)), 32, 4);
}

