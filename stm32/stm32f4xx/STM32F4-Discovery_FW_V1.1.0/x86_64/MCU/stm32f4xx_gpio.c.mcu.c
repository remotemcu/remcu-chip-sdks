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
  uint32_t var_name_tmp__48;
  uint32_t var_name_tmp__49;
  uint32_t var_name_tmp__50;
  uint32_t var_name_tmp__51;
  uint32_t var_name_tmp__52;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__53;
  uint32_t* var_name_tmp__54;
  uint32_t var_name_tmp__55;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__56;
  uint32_t var_name_tmp__57;
  uint32_t var_name_tmp__58;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__59;
  uint32_t* var_name_tmp__60;
  uint32_t var_name_tmp__61;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__62;
  uint32_t var_name_tmp__63;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__64;
  uint32_t var_name_tmp__65;
  uint32_t var_name_tmp__66;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__67;
  uint32_t* var_name_tmp__68;
  uint32_t var_name_tmp__69;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__70;
  uint32_t var_name_tmp__71;
  uint32_t var_name_tmp__72;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__73;
  uint32_t* var_name_tmp__74;
  uint32_t var_name_tmp__75;
  uint32_t var_name_tmp__76;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__77;
  uint32_t* var_name_tmp__78;
  uint32_t var_name_tmp__79;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__80;
  uint32_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__83;
  uint32_t* var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint32_t var_name_tmp__86;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__87;
  uint32_t* var_name_tmp__88;
  uint32_t var_name_tmp__89;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__90;
  uint32_t var_name_tmp__91;
  uint32_t var_name_tmp__92;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__93;
  uint32_t* var_name_tmp__94;
  uint32_t var_name_tmp__95;
  uint32_t var_name_tmp__96;

  var_name_tmp__40 = var_name_tmp__38;
  var_name_tmp__41 = var_name_tmp__39;
  var_name_tmp__42 = 0;
  var_name_tmp__43 = 0;
  var_name_tmp__44 = 0;
  var_name_tmp__42 = 0;
  goto var_name_tmp__97;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__97:
  var_name_tmp__45 = var_name_tmp__42;
  if ((((((uint32_t)var_name_tmp__45) < ((uint32_t)16u))&1))) {
    goto var_name_tmp__98;
  } else {
    goto var_name_tmp__99;
  }

var_name_tmp__98:
  var_name_tmp__46 = var_name_tmp__42;
  var_name_tmp__43 = (1 << var_name_tmp__46);
  var_name_tmp__47 = var_name_tmp__41;
  var_name_tmp__48 = *((&var_name_tmp__47->field0));
  var_name_tmp__49 = var_name_tmp__43;
  var_name_tmp__44 = (var_name_tmp__48 & var_name_tmp__49);
  var_name_tmp__50 = var_name_tmp__44;
  var_name_tmp__51 = var_name_tmp__43;
  if ((((var_name_tmp__50 == var_name_tmp__51)&1))) {
    goto var_name_tmp__100;
  } else {
    goto var_name_tmp__101;
  }

var_name_tmp__100:
  var_name_tmp__52 = var_name_tmp__42;
  var_name_tmp__53 = var_name_tmp__40;
  var_name_tmp__54 = (&var_name_tmp__53->field0);
  var_name_tmp__55 = *(volatile uint32_t*)var_name_tmp__54;
  *(volatile uint32_t*)var_name_tmp__54 = (var_name_tmp__55 & (~((3 << (llvm_mul_u32(var_name_tmp__52, 2))))));
  var_name_tmp__56 = var_name_tmp__41;
  var_name_tmp__57 = *((&var_name_tmp__56->field1));
  var_name_tmp__58 = var_name_tmp__42;
  var_name_tmp__59 = var_name_tmp__40;
  var_name_tmp__60 = (&var_name_tmp__59->field0);
  var_name_tmp__61 = *(volatile uint32_t*)var_name_tmp__60;
  *(volatile uint32_t*)var_name_tmp__60 = (var_name_tmp__61 | (var_name_tmp__57 << (llvm_mul_u32(var_name_tmp__58, 2))));
  var_name_tmp__62 = var_name_tmp__41;
  var_name_tmp__63 = *((&var_name_tmp__62->field1));
  if ((((var_name_tmp__63 == 1u)&1))) {
    goto var_name_tmp__102;
  } else {
    goto var_name_tmp__103;
  }

var_name_tmp__103:
  var_name_tmp__64 = var_name_tmp__41;
  var_name_tmp__65 = *((&var_name_tmp__64->field1));
  if ((((var_name_tmp__65 == 2u)&1))) {
    goto var_name_tmp__102;
  } else {
    goto var_name_tmp__104;
  }

var_name_tmp__102:
  var_name_tmp__66 = var_name_tmp__42;
  var_name_tmp__67 = var_name_tmp__40;
  var_name_tmp__68 = (&var_name_tmp__67->field2);
  var_name_tmp__69 = *(volatile uint32_t*)var_name_tmp__68;
  *(volatile uint32_t*)var_name_tmp__68 = (var_name_tmp__69 & (~((3 << (llvm_mul_u32(var_name_tmp__66, 2))))));
  var_name_tmp__70 = var_name_tmp__41;
  var_name_tmp__71 = *((&var_name_tmp__70->field2));
  var_name_tmp__72 = var_name_tmp__42;
  var_name_tmp__73 = var_name_tmp__40;
  var_name_tmp__74 = (&var_name_tmp__73->field2);
  var_name_tmp__75 = *(volatile uint32_t*)var_name_tmp__74;
  *(volatile uint32_t*)var_name_tmp__74 = (var_name_tmp__75 | (var_name_tmp__71 << (llvm_mul_u32(var_name_tmp__72, 2))));
  var_name_tmp__76 = var_name_tmp__42;
  var_name_tmp__77 = var_name_tmp__40;
  var_name_tmp__78 = (&var_name_tmp__77->field1);
  var_name_tmp__79 = *(volatile uint32_t*)var_name_tmp__78;
  *(volatile uint32_t*)var_name_tmp__78 = (var_name_tmp__79 & (~((1 << (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__76))))))));
  var_name_tmp__80 = var_name_tmp__41;
  var_name_tmp__81 = *((&var_name_tmp__80->field3));
  var_name_tmp__82 = var_name_tmp__42;
  var_name_tmp__83 = var_name_tmp__40;
  var_name_tmp__84 = (&var_name_tmp__83->field1);
  var_name_tmp__85 = *(volatile uint32_t*)var_name_tmp__84;
  *(volatile uint32_t*)var_name_tmp__84 = (var_name_tmp__85 | (((uint32_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__81)))) << (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__82))))))))));
  goto var_name_tmp__104;

var_name_tmp__104:
  var_name_tmp__86 = var_name_tmp__42;
  var_name_tmp__87 = var_name_tmp__40;
  var_name_tmp__88 = (&var_name_tmp__87->field3);
  var_name_tmp__89 = *(volatile uint32_t*)var_name_tmp__88;
  *(volatile uint32_t*)var_name_tmp__88 = (var_name_tmp__89 & (~((3 << (llvm_mul_u32((((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__86)))), 2))))));
  var_name_tmp__90 = var_name_tmp__41;
  var_name_tmp__91 = *((&var_name_tmp__90->field4));
  var_name_tmp__92 = var_name_tmp__42;
  var_name_tmp__93 = var_name_tmp__40;
  var_name_tmp__94 = (&var_name_tmp__93->field3);
  var_name_tmp__95 = *(volatile uint32_t*)var_name_tmp__94;
  *(volatile uint32_t*)var_name_tmp__94 = (var_name_tmp__95 | (var_name_tmp__91 << (llvm_mul_u32(var_name_tmp__92, 2))));
  goto var_name_tmp__101;

var_name_tmp__101:
  goto var_name_tmp__105;

var_name_tmp__105:
  var_name_tmp__96 = var_name_tmp__42;
  var_name_tmp__42 = (llvm_add_u32(var_name_tmp__96, 1));
  goto var_name_tmp__97;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__99:
  return;
}


void GPIO_StructInit(struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__106) {
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__107;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__108;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__109;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_GPIO_InitTypeDef* var_name_tmp__112;

  var_name_tmp__107 = var_name_tmp__106;
  var_name_tmp__108 = var_name_tmp__107;
  *((&var_name_tmp__108->field0)) = 65535;
  var_name_tmp__109 = var_name_tmp__107;
  *((&var_name_tmp__109->field1)) = 0;
  var_name_tmp__110 = var_name_tmp__107;
  *((&var_name_tmp__110->field2)) = 0;
  var_name_tmp__111 = var_name_tmp__107;
  *((&var_name_tmp__111->field3)) = 0;
  var_name_tmp__112 = var_name_tmp__107;
  *((&var_name_tmp__112->field4)) = 0;
}


void GPIO_PinLockConfig(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__113, uint16_t var_name_tmp__114) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__115;    /* Address-exposed local */
  uint16_t var_name_tmp__116;    /* Address-exposed local */
  uint32_t var_name_tmp__117;    /* Address-exposed local */
  uint16_t var_name_tmp__118;
  uint32_t var_name_tmp__119;
  uint32_t var_name_tmp__120;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__121;
  uint16_t var_name_tmp__122;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__123;
  uint32_t var_name_tmp__124;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__125;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__126;
  uint32_t var_name_tmp__127;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__128;
  uint32_t var_name_tmp__129;

  var_name_tmp__115 = var_name_tmp__113;
  var_name_tmp__116 = var_name_tmp__114;
  *(volatile uint32_t*)(&var_name_tmp__117) = 65536;
  var_name_tmp__118 = var_name_tmp__116;
  var_name_tmp__119 = *(volatile uint32_t*)(&var_name_tmp__117);
  *(volatile uint32_t*)(&var_name_tmp__117) = (var_name_tmp__119 | (((uint32_t)(uint16_t)var_name_tmp__118)));
  var_name_tmp__120 = *(volatile uint32_t*)(&var_name_tmp__117);
  var_name_tmp__121 = var_name_tmp__115;
  *(volatile uint32_t*)((&var_name_tmp__121->field8)) = var_name_tmp__120;
  var_name_tmp__122 = var_name_tmp__116;
  var_name_tmp__123 = var_name_tmp__115;
  *(volatile uint32_t*)((&var_name_tmp__123->field8)) = (((uint32_t)(uint16_t)var_name_tmp__122));
  var_name_tmp__124 = *(volatile uint32_t*)(&var_name_tmp__117);
  var_name_tmp__125 = var_name_tmp__115;
  *(volatile uint32_t*)((&var_name_tmp__125->field8)) = var_name_tmp__124;
  var_name_tmp__126 = var_name_tmp__115;
  var_name_tmp__127 = *(volatile uint32_t*)((&var_name_tmp__126->field8));
  *(volatile uint32_t*)(&var_name_tmp__117) = var_name_tmp__127;
  var_name_tmp__128 = var_name_tmp__115;
  var_name_tmp__129 = *(volatile uint32_t*)((&var_name_tmp__128->field8));
  *(volatile uint32_t*)(&var_name_tmp__117) = var_name_tmp__129;
}


uint8_t GPIO_ReadInputDataBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__130, uint16_t var_name_tmp__131) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__132;    /* Address-exposed local */
  uint16_t var_name_tmp__133;    /* Address-exposed local */
  uint8_t var_name_tmp__134;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__135;
  uint32_t var_name_tmp__136;
  uint16_t var_name_tmp__137;
  uint8_t var_name_tmp__138;

  var_name_tmp__132 = var_name_tmp__130;
  var_name_tmp__133 = var_name_tmp__131;
  var_name_tmp__134 = 0;
  var_name_tmp__135 = var_name_tmp__132;
  var_name_tmp__136 = *(volatile uint32_t*)((&var_name_tmp__135->field4));
  var_name_tmp__137 = var_name_tmp__133;
  if (((((var_name_tmp__136 & (((uint32_t)(uint16_t)var_name_tmp__137))) != 0u)&1))) {
    goto var_name_tmp__139;
  } else {
    goto var_name_tmp__140;
  }

var_name_tmp__139:
  var_name_tmp__134 = 1;
  goto var_name_tmp__141;

var_name_tmp__140:
  var_name_tmp__134 = 0;
  goto var_name_tmp__141;

var_name_tmp__141:
  var_name_tmp__138 = var_name_tmp__134;
  return var_name_tmp__138;
}


uint16_t GPIO_ReadInputData(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__142) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__143;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__144;
  uint32_t var_name_tmp__145;

  var_name_tmp__143 = var_name_tmp__142;
  var_name_tmp__144 = var_name_tmp__143;
  var_name_tmp__145 = *(volatile uint32_t*)((&var_name_tmp__144->field4));
  return (((uint16_t)var_name_tmp__145));
}


uint8_t GPIO_ReadOutputDataBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__146, uint16_t var_name_tmp__147) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__148;    /* Address-exposed local */
  uint16_t var_name_tmp__149;    /* Address-exposed local */
  uint8_t var_name_tmp__150;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__151;
  uint32_t var_name_tmp__152;
  uint16_t var_name_tmp__153;
  uint8_t var_name_tmp__154;

  var_name_tmp__148 = var_name_tmp__146;
  var_name_tmp__149 = var_name_tmp__147;
  var_name_tmp__150 = 0;
  var_name_tmp__151 = var_name_tmp__148;
  var_name_tmp__152 = *(volatile uint32_t*)((&var_name_tmp__151->field5));
  var_name_tmp__153 = var_name_tmp__149;
  if (((((var_name_tmp__152 & (((uint32_t)(uint16_t)var_name_tmp__153))) != 0u)&1))) {
    goto var_name_tmp__155;
  } else {
    goto var_name_tmp__156;
  }

var_name_tmp__155:
  var_name_tmp__150 = 1;
  goto var_name_tmp__157;

var_name_tmp__156:
  var_name_tmp__150 = 0;
  goto var_name_tmp__157;

var_name_tmp__157:
  var_name_tmp__154 = var_name_tmp__150;
  return var_name_tmp__154;
}


uint16_t GPIO_ReadOutputData(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__158) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__159;    /* Address-exposed local */
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__160;
  uint32_t var_name_tmp__161;

  var_name_tmp__159 = var_name_tmp__158;
  var_name_tmp__160 = var_name_tmp__159;
  var_name_tmp__161 = *(volatile uint32_t*)((&var_name_tmp__160->field5));
  return (((uint16_t)var_name_tmp__161));
}


void GPIO_SetBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__162, uint16_t var_name_tmp__163) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__164;    /* Address-exposed local */
  uint16_t var_name_tmp__165;    /* Address-exposed local */
  uint16_t var_name_tmp__166;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__167;

  var_name_tmp__164 = var_name_tmp__162;
  var_name_tmp__165 = var_name_tmp__163;
  var_name_tmp__166 = var_name_tmp__165;
  var_name_tmp__167 = var_name_tmp__164;
  *(volatile uint16_t*)((&var_name_tmp__167->field6)) = var_name_tmp__166;
}


void GPIO_ResetBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__168, uint16_t var_name_tmp__169) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__170;    /* Address-exposed local */
  uint16_t var_name_tmp__171;    /* Address-exposed local */
  uint16_t var_name_tmp__172;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__173;

  var_name_tmp__170 = var_name_tmp__168;
  var_name_tmp__171 = var_name_tmp__169;
  var_name_tmp__172 = var_name_tmp__171;
  var_name_tmp__173 = var_name_tmp__170;
  *(volatile uint16_t*)((&var_name_tmp__173->field7)) = var_name_tmp__172;
}


void GPIO_WriteBit(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__174, uint16_t var_name_tmp__175, uint32_t var_name_tmp__176) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__177;    /* Address-exposed local */
  uint16_t var_name_tmp__178;    /* Address-exposed local */
  uint32_t var_name_tmp__179;    /* Address-exposed local */
  uint32_t var_name_tmp__180;
  uint16_t var_name_tmp__181;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__182;
  uint16_t var_name_tmp__183;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__184;

  var_name_tmp__177 = var_name_tmp__174;
  var_name_tmp__178 = var_name_tmp__175;
  var_name_tmp__179 = var_name_tmp__176;
  var_name_tmp__180 = var_name_tmp__179;
  if ((((var_name_tmp__180 != 0u)&1))) {
    goto var_name_tmp__185;
  } else {
    goto var_name_tmp__186;
  }

var_name_tmp__185:
  var_name_tmp__181 = var_name_tmp__178;
  var_name_tmp__182 = var_name_tmp__177;
  *(volatile uint16_t*)((&var_name_tmp__182->field6)) = var_name_tmp__181;
  goto var_name_tmp__187;

var_name_tmp__186:
  var_name_tmp__183 = var_name_tmp__178;
  var_name_tmp__184 = var_name_tmp__177;
  *(volatile uint16_t*)((&var_name_tmp__184->field7)) = var_name_tmp__183;
  goto var_name_tmp__187;

var_name_tmp__187:
  return;
}


void GPIO_Write(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__188, uint16_t var_name_tmp__189) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__190;    /* Address-exposed local */
  uint16_t var_name_tmp__191;    /* Address-exposed local */
  uint16_t var_name_tmp__192;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__193;

  var_name_tmp__190 = var_name_tmp__188;
  var_name_tmp__191 = var_name_tmp__189;
  var_name_tmp__192 = var_name_tmp__191;
  var_name_tmp__193 = var_name_tmp__190;
  *(volatile uint32_t*)((&var_name_tmp__193->field5)) = (((uint32_t)(uint16_t)var_name_tmp__192));
}


void GPIO_ToggleBits(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__194, uint16_t var_name_tmp__195) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__196;    /* Address-exposed local */
  uint16_t var_name_tmp__197;    /* Address-exposed local */
  uint16_t var_name_tmp__198;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__199;
  uint32_t* var_name_tmp__200;
  uint32_t var_name_tmp__201;

  var_name_tmp__196 = var_name_tmp__194;
  var_name_tmp__197 = var_name_tmp__195;
  var_name_tmp__198 = var_name_tmp__197;
  var_name_tmp__199 = var_name_tmp__196;
  var_name_tmp__200 = (&var_name_tmp__199->field5);
  var_name_tmp__201 = *(volatile uint32_t*)var_name_tmp__200;
  *(volatile uint32_t*)var_name_tmp__200 = (var_name_tmp__201 ^ (((uint32_t)(uint16_t)var_name_tmp__198)));
}


void GPIO_PinAFConfig(struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__202, uint16_t var_name_tmp__203, uint8_t var_name_tmp__204) {
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__205;    /* Address-exposed local */
  uint16_t var_name_tmp__206;    /* Address-exposed local */
  uint8_t var_name_tmp__207;    /* Address-exposed local */
  uint32_t var_name_tmp__208;    /* Address-exposed local */
  uint32_t var_name_tmp__209;    /* Address-exposed local */
  uint8_t var_name_tmp__210;
  uint16_t var_name_tmp__211;
  uint16_t var_name_tmp__212;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__213;
  uint16_t var_name_tmp__214;
  uint32_t* var_name_tmp__215;
  uint32_t var_name_tmp__216;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__217;
  uint16_t var_name_tmp__218;
  uint32_t var_name_tmp__219;
  uint32_t var_name_tmp__220;
  uint32_t var_name_tmp__221;
  struct l_struct_struct_OC_GPIO_TypeDef* var_name_tmp__222;
  uint16_t var_name_tmp__223;

  var_name_tmp__205 = var_name_tmp__202;
  var_name_tmp__206 = var_name_tmp__203;
  var_name_tmp__207 = var_name_tmp__204;
  var_name_tmp__208 = 0;
  var_name_tmp__209 = 0;
  var_name_tmp__210 = var_name_tmp__207;
  var_name_tmp__211 = var_name_tmp__206;
  var_name_tmp__208 = ((((uint32_t)(uint8_t)var_name_tmp__210)) << (llvm_mul_u32(((((uint32_t)(uint16_t)var_name_tmp__211)) & 7), 4)));
  var_name_tmp__212 = var_name_tmp__206;
  var_name_tmp__213 = var_name_tmp__205;
  var_name_tmp__214 = var_name_tmp__206;
  var_name_tmp__215 = (&(*((&var_name_tmp__213->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__214)), 3)))))]);
  var_name_tmp__216 = *(volatile uint32_t*)var_name_tmp__215;
  *(volatile uint32_t*)var_name_tmp__215 = (var_name_tmp__216 & (~((15 << (llvm_mul_u32(((((uint32_t)(uint16_t)var_name_tmp__212)) & 7), 4))))));
  var_name_tmp__217 = var_name_tmp__205;
  var_name_tmp__218 = var_name_tmp__206;
  var_name_tmp__219 = *(volatile uint32_t*)((&(*((&var_name_tmp__217->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__218)), 3)))))]));
  var_name_tmp__220 = var_name_tmp__208;
  var_name_tmp__209 = (var_name_tmp__219 | var_name_tmp__220);
  var_name_tmp__221 = var_name_tmp__209;
  var_name_tmp__222 = var_name_tmp__205;
  var_name_tmp__223 = var_name_tmp__206;
  *(volatile uint32_t*)((&(*((&var_name_tmp__222->field9))).array[((int64_t)(((int64_t)(int32_t)(llvm_ashr_u32((((uint32_t)(uint16_t)var_name_tmp__223)), 3)))))])) = var_name_tmp__221;
}

