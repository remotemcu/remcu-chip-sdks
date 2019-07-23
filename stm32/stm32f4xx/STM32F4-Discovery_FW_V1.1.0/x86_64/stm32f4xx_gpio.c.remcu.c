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
struct l_struct_struct_OC_GPIO_TypeDef;
struct l_struct_struct_OC_GPIO_InitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_array_2_uint32_t {
  uint32_t array[2];
};
struct l_struct_struct_OC_GPIO_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint16_t field6;
  uint16_t field7;
  uint32_t field8;
  struct l_array_2_uint32_t field9;
};
struct l_struct_struct_OC_GPIO_InitTypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
};

/* Function Declarations */
void GPIO_DeInit(struct l_struct_struct_OC_GPIO_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_AHB1PeriphResetCmd(uint32_t, uint32_t);
void GPIO_Init(struct l_struct_struct_OC_GPIO_TypeDef*, struct l_struct_struct_OC_GPIO_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_StructInit(struct l_struct_struct_OC_GPIO_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_PinLockConfig(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t GPIO_ReadInputDataBit(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t GPIO_ReadInputData(struct l_struct_struct_OC_GPIO_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t GPIO_ReadOutputDataBit(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t GPIO_ReadOutputData(struct l_struct_struct_OC_GPIO_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_SetBits(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_ResetBits(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_WriteBit(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_Write(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_ToggleBits(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
void GPIO_PinAFConfig(struct l_struct_struct_OC_GPIO_TypeDef*, uint16_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_mul_u32(uint32_t a, uint32_t b) {
  uint32_t r = a * b;
  return r;
}
static __forceinline uint32_t llvm_ashr_u32(int32_t a, int32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void GPIO_DeInit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__3;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__4;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__5;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__6;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__7;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__8;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__9;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__10;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__11;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073872896)))&1))) {
    goto var_name_tmp__12;
  } else {
    goto var_name_tmp__13;
  }

var_name_tmp__12:
  RCC_AHB1PeriphResetCmd(1, 1);
  RCC_AHB1PeriphResetCmd(1, 0);
  goto var_name_tmp__14;

var_name_tmp__13:
  var_name_tmp__4 = var_name_tmp__2;
  if ((((var_name_tmp__4 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073873920)))&1))) {
    goto var_name_tmp__15;
  } else {
    goto var_name_tmp__16;
  }

var_name_tmp__15:
  RCC_AHB1PeriphResetCmd(2, 1);
  RCC_AHB1PeriphResetCmd(2, 0);
  goto var_name_tmp__17;

var_name_tmp__16:
  var_name_tmp__5 = var_name_tmp__2;
  if ((((var_name_tmp__5 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073874944)))&1))) {
    goto var_name_tmp__18;
  } else {
    goto var_name_tmp__19;
  }

var_name_tmp__18:
  RCC_AHB1PeriphResetCmd(4, 1);
  RCC_AHB1PeriphResetCmd(4, 0);
  goto var_name_tmp__20;

var_name_tmp__19:
  var_name_tmp__6 = var_name_tmp__2;
  if ((((var_name_tmp__6 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073875968)))&1))) {
    goto var_name_tmp__21;
  } else {
    goto var_name_tmp__22;
  }

var_name_tmp__21:
  RCC_AHB1PeriphResetCmd(8, 1);
  RCC_AHB1PeriphResetCmd(8, 0);
  goto var_name_tmp__23;

var_name_tmp__22:
  var_name_tmp__7 = var_name_tmp__2;
  if ((((var_name_tmp__7 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073876992)))&1))) {
    goto var_name_tmp__24;
  } else {
    goto var_name_tmp__25;
  }

var_name_tmp__24:
  RCC_AHB1PeriphResetCmd(16, 1);
  RCC_AHB1PeriphResetCmd(16, 0);
  goto var_name_tmp__26;

var_name_tmp__25:
  var_name_tmp__8 = var_name_tmp__2;
  if ((((var_name_tmp__8 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073878016)))&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__28;
  }

var_name_tmp__27:
  RCC_AHB1PeriphResetCmd(32, 1);
  RCC_AHB1PeriphResetCmd(32, 0);
  goto var_name_tmp__29;

var_name_tmp__28:
  var_name_tmp__9 = var_name_tmp__2;
  if ((((var_name_tmp__9 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073879040)))&1))) {
    goto var_name_tmp__30;
  } else {
    goto var_name_tmp__31;
  }

var_name_tmp__30:
  RCC_AHB1PeriphResetCmd(64, 1);
  RCC_AHB1PeriphResetCmd(64, 0);
  goto var_name_tmp__32;

var_name_tmp__31:
  var_name_tmp__10 = var_name_tmp__2;
  if ((((var_name_tmp__10 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073880064)))&1))) {
    goto var_name_tmp__33;
  } else {
    goto var_name_tmp__34;
  }

var_name_tmp__33:
  RCC_AHB1PeriphResetCmd(128, 1);
  RCC_AHB1PeriphResetCmd(128, 0);
  goto var_name_tmp__35;

var_name_tmp__34:
  var_name_tmp__11 = var_name_tmp__2;
  if ((((var_name_tmp__11 == ((struct l_struct_struct_OC_GPIO_TypeDef*)(uintptr_t)UINT64_C(1073881088)))&1))) {
    goto var_name_tmp__36;
  } else {
    goto var_name_tmp__37;
  }

var_name_tmp__36:
  RCC_AHB1PeriphResetCmd(256, 1);
  RCC_AHB1PeriphResetCmd(256, 0);
  goto var_name_tmp__37;

var_name_tmp__37:
  goto var_name_tmp__35;

var_name_tmp__35:
  goto var_name_tmp__32;

var_name_tmp__32:
  goto var_name_tmp__29;

var_name_tmp__29:
  goto var_name_tmp__26;

var_name_tmp__26:
  goto var_name_tmp__23;

var_name_tmp__23:
  goto var_name_tmp__20;

var_name_tmp__20:
  goto var_name_tmp__17;

var_name_tmp__17:
  goto var_name_tmp__14;

var_name_tmp__14:
  return;
}


void GPIO_Init(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__38, struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__39) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__40;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__41;    /* Address-exposed local */
  uint32_t var_name_tmp__42;    /* Address-exposed local */
  uint32_t var_name_tmp__43;    /* Address-exposed local */
  uint32_t var_name_tmp__44;    /* Address-exposed local */
  uint32_t var_name_tmp__45;
  uint32_t var_name_tmp__46;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__47;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__48;
  uint32_t var_name_tmp__49;
  uint32_t var_name_tmp__50;
  uint32_t var_name_tmp__51;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__52;
  uint32_t* var_name_tmp__53;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__54;
  uint64_t var_name_load_i32_6;
  uint32_t var_name_tmp__55;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__56;
  uint32_t* var_name_tmp__57;
  uint64_t var_name_load_i32_9;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__58;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__59;
  uint64_t var_name_load_i32_17;
  uint32_t var_name_tmp__60;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__61;
  uint32_t* var_name_tmp__62;
  uint64_t var_name_load_i32_20;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__63;
  uint64_t var_name_load_i32_25;
  uint32_t var_name_tmp__64;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__65;
  uint32_t* var_name_tmp__66;
  uint64_t var_name_load_i32_28;
  uint32_t var_name_tmp__67;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__68;
  uint32_t* var_name_tmp__69;
  uint64_t var_name_load_i32_33;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__70;
  uint64_t var_name_load_i32_38;
  uint32_t var_name_tmp__71;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__72;
  uint32_t* var_name_tmp__73;
  uint64_t var_name_load_i32_41;
  uint32_t var_name_tmp__74;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__75;
  uint32_t* var_name_tmp__76;
  uint64_t var_name_load_i32_46;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__77;
  uint64_t var_name_load_i32_51;
  uint32_t var_name_tmp__78;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__79;
  uint32_t* var_name_tmp__80;
  uint64_t var_name_load_i32_54;
  uint32_t var_name_tmp__81;

  var_name_tmp__40 = var_name_tmp__38;
  var_name_tmp__41 = var_name_tmp__39;
  var_name_tmp__42 = 0;
  var_name_tmp__43 = 0;
  var_name_tmp__44 = 0;
  var_name_tmp__42 = 0;
  goto var_name_tmp__82;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__82:
  var_name_tmp__45 = var_name_tmp__42;
  if ((((((uint32_t)var_name_tmp__45) < ((uint32_t)16u))&1))) {
    goto var_name_tmp__83;
  } else {
    goto var_name_tmp__84;
  }

var_name_tmp__83:
  var_name_tmp__46 = var_name_tmp__42;
  var_name_tmp__43 = (1 << var_name_tmp__46);
  var_name_tmp__47 = var_name_tmp__41;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__47->field0)))), 32, 4);
  var_name_tmp__48 = var_name_tmp__43;
  var_name_tmp__44 = ((((uint32_t)var_name_load_i32_)) & var_name_tmp__48);
  var_name_tmp__49 = var_name_tmp__44;
  var_name_tmp__50 = var_name_tmp__43;
  if ((((var_name_tmp__49 == var_name_tmp__50)&1))) {
    goto var_name_tmp__85;
  } else {
    goto var_name_tmp__86;
  }

var_name_tmp__85:
  var_name_tmp__51 = var_name_tmp__42;
  var_name_tmp__52 = var_name_tmp__40;
  var_name_tmp__53 = (&var_name_tmp__52->field0);
  var_name_load_i32_2 = __adin_load_((((uint8_t*)var_name_tmp__53)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__53)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_2)) & (~((3 << (llvm_mul_u32(var_name_tmp__51, 2)))))))), 32, 4);
  var_name_tmp__54 = var_name_tmp__41;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__54->field1)))), 32, 4);
  var_name_tmp__55 = var_name_tmp__42;
  var_name_tmp__56 = var_name_tmp__40;
  var_name_tmp__57 = (&var_name_tmp__56->field0);
  var_name_load_i32_9 = __adin_load_((((uint8_t*)var_name_tmp__57)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__57)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_9)) | ((((uint32_t)var_name_load_i32_6)) << (llvm_mul_u32(var_name_tmp__55, 2)))))), 32, 4);
  var_name_tmp__58 = var_name_tmp__41;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__58->field1)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_14)) == 1u)&1))) {
    goto var_name_tmp__87;
  } else {
    goto var_name_tmp__88;
  }

var_name_tmp__88:
  var_name_tmp__59 = var_name_tmp__41;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__59->field1)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_17)) == 2u)&1))) {
    goto var_name_tmp__87;
  } else {
    goto var_name_tmp__89;
  }

var_name_tmp__87:
  var_name_tmp__60 = var_name_tmp__42;
  var_name_tmp__61 = var_name_tmp__40;
  var_name_tmp__62 = (&var_name_tmp__61->field2);
  var_name_load_i32_20 = __adin_load_((((uint8_t*)var_name_tmp__62)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__62)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_20)) & (~((3 << (llvm_mul_u32(var_name_tmp__60, 2)))))))), 32, 4);
  var_name_tmp__63 = var_name_tmp__41;
  var_name_load_i32_25 = __adin_load_((((uint8_t*)((&var_name_tmp__63->field2)))), 32, 4);
  var_name_tmp__64 = var_name_tmp__42;
  var_name_tmp__65 = var_name_tmp__40;
  var_name_tmp__66 = (&var_name_tmp__65->field2);
  var_name_load_i32_28 = __adin_load_((((uint8_t*)var_name_tmp__66)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__66)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_28)) | ((((uint32_t)var_name_load_i32_25)) << (llvm_mul_u32(var_name_tmp__64, 2)))))), 32, 4);
  var_name_tmp__67 = var_name_tmp__42;
  var_name_tmp__68 = var_name_tmp__40;
  var_name_tmp__69 = (&var_name_tmp__68->field1);
  var_name_load_i32_33 = __adin_load_((((uint8_t*)var_name_tmp__69)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__69)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_33)) & (~((1 << (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__67)))))))))), 32, 4);
  var_name_tmp__70 = var_name_tmp__41;
  var_name_load_i32_38 = __adin_load_((((uint8_t*)((&var_name_tmp__70->field3)))), 32, 4);
  var_name_tmp__71 = var_name_tmp__42;
  var_name_tmp__72 = var_name_tmp__40;
  var_name_tmp__73 = (&var_name_tmp__72->field1);
  var_name_load_i32_41 = __adin_load_((((uint8_t*)var_name_tmp__73)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__73)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_41)) | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)(((uint32_t)var_name_load_i32_38)))))) << (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__71)))))))))))), 32, 4);
  goto var_name_tmp__89;

var_name_tmp__89:
  var_name_tmp__74 = var_name_tmp__42;
  var_name_tmp__75 = var_name_tmp__40;
  var_name_tmp__76 = (&var_name_tmp__75->field3);
  var_name_load_i32_46 = __adin_load_((((uint8_t*)var_name_tmp__76)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__76)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_46)) & (~((3 << (llvm_mul_u32((((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__74)))), 2)))))))), 32, 4);
  var_name_tmp__77 = var_name_tmp__41;
  var_name_load_i32_51 = __adin_load_((((uint8_t*)((&var_name_tmp__77->field4)))), 32, 4);
  var_name_tmp__78 = var_name_tmp__42;
  var_name_tmp__79 = var_name_tmp__40;
  var_name_tmp__80 = (&var_name_tmp__79->field3);
  var_name_load_i32_54 = __adin_load_((((uint8_t*)var_name_tmp__80)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__80)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_54)) | ((((uint32_t)var_name_load_i32_51)) << (llvm_mul_u32(var_name_tmp__78, 2)))))), 32, 4);
  goto var_name_tmp__86;

var_name_tmp__86:
  goto var_name_tmp__90;

var_name_tmp__90:
  var_name_tmp__81 = var_name_tmp__42;
  var_name_tmp__42 = (llvm_add_u32(var_name_tmp__81, 1));
  goto var_name_tmp__82;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__84:
  return;
}


void GPIO_StructInit(struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__91) {
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__92;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__93;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__94;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__95;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__96;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__97;

  var_name_tmp__92 = var_name_tmp__91;
  var_name_tmp__93 = var_name_tmp__92;
  __adin_store_((((uint8_t*)((&var_name_tmp__93->field0)))), UINT64_C(65535), 32, 4);
  var_name_tmp__94 = var_name_tmp__92;
  __adin_store_((((uint8_t*)((&var_name_tmp__94->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__95 = var_name_tmp__92;
  __adin_store_((((uint8_t*)((&var_name_tmp__95->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__96 = var_name_tmp__92;
  __adin_store_((((uint8_t*)((&var_name_tmp__96->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__97 = var_name_tmp__92;
  __adin_store_((((uint8_t*)((&var_name_tmp__97->field4)))), UINT64_C(0), 32, 4);
}


void GPIO_PinLockConfig(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__98, uint16_t var_name_tmp__99) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__100;    /* Address-exposed local */
  uint16_t var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  uint16_t var_name_tmp__103;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_4;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__104;
  uint16_t var_name_tmp__105;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__106;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__107;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__108;
  uint64_t var_name_load_i32_16;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__109;
  uint64_t var_name_load_i32_21;

  var_name_tmp__100 = var_name_tmp__98;
  var_name_tmp__101 = var_name_tmp__99;
  __adin_store_((((uint8_t*)(&var_name_tmp__102))), UINT64_C(65536), 32, 4);
  var_name_tmp__103 = var_name_tmp__101;
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__102))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__102))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | (((uint32_t)(uint16_t)var_name_tmp__103))))), 32, 4);
  var_name_load_i32_4 = __adin_load_((((uint8_t*)(&var_name_tmp__102))), 32, 4);
  var_name_tmp__104 = var_name_tmp__100;
  __adin_store_((((uint8_t*)((&var_name_tmp__104->field8)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_4)))), 32, 4);
  var_name_tmp__105 = var_name_tmp__101;
  var_name_tmp__106 = var_name_tmp__100;
  __adin_store_((((uint8_t*)((&var_name_tmp__106->field8)))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__105)))), 32, 4);
  var_name_load_i32_11 = __adin_load_((((uint8_t*)(&var_name_tmp__102))), 32, 4);
  var_name_tmp__107 = var_name_tmp__100;
  __adin_store_((((uint8_t*)((&var_name_tmp__107->field8)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_11)))), 32, 4);
  var_name_tmp__108 = var_name_tmp__100;
  var_name_load_i32_16 = __adin_load_((((uint8_t*)((&var_name_tmp__108->field8)))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__102))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_16)))), 32, 4);
  var_name_tmp__109 = var_name_tmp__100;
  var_name_load_i32_21 = __adin_load_((((uint8_t*)((&var_name_tmp__109->field8)))), 32, 4);
  __adin_store_((((uint8_t*)(&var_name_tmp__102))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_21)))), 32, 4);
}


uint8_t GPIO_ReadInputDataBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__110, uint16_t var_name_tmp__111) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__112;    /* Address-exposed local */
  uint16_t var_name_tmp__113;    /* Address-exposed local */
  uint8_t var_name_tmp__114;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__115;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__116;
  uint8_t var_name_tmp__117;

  var_name_tmp__112 = var_name_tmp__110;
  var_name_tmp__113 = var_name_tmp__111;
  var_name_tmp__114 = 0;
  var_name_tmp__115 = var_name_tmp__112;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__115->field4)))), 32, 4);
  var_name_tmp__116 = var_name_tmp__113;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint16_t)var_name_tmp__116))) != 0u)&1))) {
    goto var_name_tmp__118;
  } else {
    goto var_name_tmp__119;
  }

var_name_tmp__118:
  var_name_tmp__114 = 1;
  goto var_name_tmp__120;

var_name_tmp__119:
  var_name_tmp__114 = 0;
  goto var_name_tmp__120;

var_name_tmp__120:
  var_name_tmp__117 = var_name_tmp__114;
  return var_name_tmp__117;
}


uint16_t GPIO_ReadInputData(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__121) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__122;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__123;
  uint64_t var_name_load_i32_;

  var_name_tmp__122 = var_name_tmp__121;
  var_name_tmp__123 = var_name_tmp__122;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__123->field4)))), 32, 4);
  return (((uint16_t)(((uint32_t)var_name_load_i32_))));
}


uint8_t GPIO_ReadOutputDataBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__124, uint16_t var_name_tmp__125) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__126;    /* Address-exposed local */
  uint16_t var_name_tmp__127;    /* Address-exposed local */
  uint8_t var_name_tmp__128;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__129;
  uint64_t var_name_load_i32_;
  uint16_t var_name_tmp__130;
  uint8_t var_name_tmp__131;

  var_name_tmp__126 = var_name_tmp__124;
  var_name_tmp__127 = var_name_tmp__125;
  var_name_tmp__128 = 0;
  var_name_tmp__129 = var_name_tmp__126;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__129->field5)))), 32, 4);
  var_name_tmp__130 = var_name_tmp__127;
  if ((((((((uint32_t)var_name_load_i32_)) & (((uint32_t)(uint16_t)var_name_tmp__130))) != 0u)&1))) {
    goto var_name_tmp__132;
  } else {
    goto var_name_tmp__133;
  }

var_name_tmp__132:
  var_name_tmp__128 = 1;
  goto var_name_tmp__134;

var_name_tmp__133:
  var_name_tmp__128 = 0;
  goto var_name_tmp__134;

var_name_tmp__134:
  var_name_tmp__131 = var_name_tmp__128;
  return var_name_tmp__131;
}


uint16_t GPIO_ReadOutputData(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__135) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__136;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__137;
  uint64_t var_name_load_i32_;

  var_name_tmp__136 = var_name_tmp__135;
  var_name_tmp__137 = var_name_tmp__136;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__137->field5)))), 32, 4);
  return (((uint16_t)(((uint32_t)var_name_load_i32_))));
}


void GPIO_SetBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__138, uint16_t var_name_tmp__139) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__140;    /* Address-exposed local */
  uint16_t var_name_tmp__141;    /* Address-exposed local */
  uint16_t var_name_tmp__142;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__143;

  var_name_tmp__140 = var_name_tmp__138;
  var_name_tmp__141 = var_name_tmp__139;
  var_name_tmp__142 = var_name_tmp__141;
  var_name_tmp__143 = var_name_tmp__140;
  __adin_store_((((uint8_t*)((&var_name_tmp__143->field6)))), (((uint64_t)(uint16_t)var_name_tmp__142)), 16, 4);
}


void GPIO_ResetBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__144, uint16_t var_name_tmp__145) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__146;    /* Address-exposed local */
  uint16_t var_name_tmp__147;    /* Address-exposed local */
  uint16_t var_name_tmp__148;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__149;

  var_name_tmp__146 = var_name_tmp__144;
  var_name_tmp__147 = var_name_tmp__145;
  var_name_tmp__148 = var_name_tmp__147;
  var_name_tmp__149 = var_name_tmp__146;
  __adin_store_((((uint8_t*)((&var_name_tmp__149->field7)))), (((uint64_t)(uint16_t)var_name_tmp__148)), 16, 2);
}


void GPIO_WriteBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__150, uint16_t var_name_tmp__151, uint32_t var_name_tmp__152) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__153;    /* Address-exposed local */
  uint16_t var_name_tmp__154;    /* Address-exposed local */
  uint32_t var_name_tmp__155;    /* Address-exposed local */
  uint32_t var_name_tmp__156;
  uint16_t var_name_tmp__157;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__158;
  uint16_t var_name_tmp__159;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__160;

  var_name_tmp__153 = var_name_tmp__150;
  var_name_tmp__154 = var_name_tmp__151;
  var_name_tmp__155 = var_name_tmp__152;
  var_name_tmp__156 = var_name_tmp__155;
  if ((((var_name_tmp__156 != 0u)&1))) {
    goto var_name_tmp__161;
  } else {
    goto var_name_tmp__162;
  }

var_name_tmp__161:
  var_name_tmp__157 = var_name_tmp__154;
  var_name_tmp__158 = var_name_tmp__153;
  __adin_store_((((uint8_t*)((&var_name_tmp__158->field6)))), (((uint64_t)(uint16_t)var_name_tmp__157)), 16, 4);
  goto var_name_tmp__163;

var_name_tmp__162:
  var_name_tmp__159 = var_name_tmp__154;
  var_name_tmp__160 = var_name_tmp__153;
  __adin_store_((((uint8_t*)((&var_name_tmp__160->field7)))), (((uint64_t)(uint16_t)var_name_tmp__159)), 16, 2);
  goto var_name_tmp__163;

var_name_tmp__163:
  return;
}


void GPIO_Write(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__164, uint16_t var_name_tmp__165) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__166;    /* Address-exposed local */
  uint16_t var_name_tmp__167;    /* Address-exposed local */
  uint16_t var_name_tmp__168;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__169;

  var_name_tmp__166 = var_name_tmp__164;
  var_name_tmp__167 = var_name_tmp__165;
  var_name_tmp__168 = var_name_tmp__167;
  var_name_tmp__169 = var_name_tmp__166;
  __adin_store_((((uint8_t*)((&var_name_tmp__169->field5)))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__168)))), 32, 4);
}


void GPIO_ToggleBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__170, uint16_t var_name_tmp__171) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__172;    /* Address-exposed local */
  uint16_t var_name_tmp__173;    /* Address-exposed local */
  uint16_t var_name_tmp__174;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__175;
  uint32_t* var_name_tmp__176;
  uint64_t var_name_load_i32_;

  var_name_tmp__172 = var_name_tmp__170;
  var_name_tmp__173 = var_name_tmp__171;
  var_name_tmp__174 = var_name_tmp__173;
  var_name_tmp__175 = var_name_tmp__172;
  var_name_tmp__176 = (&var_name_tmp__175->field5);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__176)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__176)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) ^ (((uint32_t)(uint16_t)var_name_tmp__174))))), 32, 4);
}


void GPIO_PinAFConfig(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__177, uint16_t var_name_tmp__178, uint8_t var_name_tmp__179) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__180;    /* Address-exposed local */
  uint16_t var_name_tmp__181;    /* Address-exposed local */
  uint8_t var_name_tmp__182;    /* Address-exposed local */
  uint32_t var_name_tmp__183;    /* Address-exposed local */
  uint32_t var_name_tmp__184;    /* Address-exposed local */
  uint8_t var_name_tmp__185;
  uint16_t var_name_tmp__186;
  uint16_t var_name_tmp__187;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__188;
  uint16_t var_name_tmp__189;
  uint32_t* var_name_tmp__190;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__191;
  uint16_t var_name_tmp__192;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__193;
  uint32_t var_name_tmp__194;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__195;
  uint16_t var_name_tmp__196;

  var_name_tmp__180 = var_name_tmp__177;
  var_name_tmp__181 = var_name_tmp__178;
  var_name_tmp__182 = var_name_tmp__179;
  var_name_tmp__183 = 0;
  var_name_tmp__184 = 0;
  var_name_tmp__185 = var_name_tmp__182;
  var_name_tmp__186 = var_name_tmp__181;
  var_name_tmp__183 = ((((uint32_t)(uint8_t)var_name_tmp__185)) << (llvm_mul_u32(((((uint32_t)(uint16_t)var_name_tmp__186)) & 7), 4)));
  var_name_tmp__187 = var_name_tmp__181;
  var_name_tmp__188 = var_name_tmp__180;
  var_name_tmp__189 = var_name_tmp__181;
  var_name_tmp__190 = (&(*((&var_name_tmp__188->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__189)), 3)))))]);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__190)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__190)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & (~((15 << (llvm_mul_u32(((((uint32_t)(uint16_t)var_name_tmp__187)) & 7), 4)))))))), 32, 4);
  var_name_tmp__191 = var_name_tmp__180;
  var_name_tmp__192 = var_name_tmp__181;
  var_name_load_i32_3 = __adin_load_((((uint8_t*)((&(*((&var_name_tmp__191->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__192)), 3)))))])))), 32, 4);
  var_name_tmp__193 = var_name_tmp__183;
  var_name_tmp__184 = ((((uint32_t)var_name_load_i32_3)) | var_name_tmp__193);
  var_name_tmp__194 = var_name_tmp__184;
  var_name_tmp__195 = var_name_tmp__180;
  var_name_tmp__196 = var_name_tmp__181;
  __adin_store_((((uint8_t*)((&(*((&var_name_tmp__195->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__196)), 3)))))])))), (((uint64_t)(uint32_t)var_name_tmp__194)), 32, 4);
}

