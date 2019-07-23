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
struct l_struct_struct_OC_DMA_Stream_TypeDef;
struct l_struct_struct_OC_DMA_TypeDef;
struct l_struct_struct_OC_DMA_InitTypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_DMA_Stream_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};
struct l_struct_struct_OC_DMA_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_struct_struct_OC_DMA_InitTypeDef {
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
};

/* Function Declarations */
void DMA_DeInit(struct l_struct_struct_OC_DMA_Stream_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_Init(struct l_struct_struct_OC_DMA_Stream_TypeDef*, struct l_struct_struct_OC_DMA_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_StructInit(struct l_struct_struct_OC_DMA_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_Cmd(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_PeriphIncOffsetSizeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_FlowControllerConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_SetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t DMA_GetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_DoubleBufferModeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_DoubleBufferModeCmd(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_MemoryTargetConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DMA_GetCurrentMemoryTarget(struct l_struct_struct_OC_DMA_Stream_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DMA_GetCmdStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DMA_GetFIFOStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DMA_GetFlagStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_ClearFlag(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_ITConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t DMA_GetITStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void DMA_ClearITPendingBit(struct l_struct_struct_OC_DMA_Stream_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void DMA_DeInit(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__3;
  uint32_t* var_name_tmp__4;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__5;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__6;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__7;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__8;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__9;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__10;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__11;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__12;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__13;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__14;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__15;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__16;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__17;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__18;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__19;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__20;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__21;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__22;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__23;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__24;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__25;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__26;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  var_name_tmp__4 = (&var_name_tmp__3->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__4)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__4)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -2))), 32, 4);
  var_name_tmp__5 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__5->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__6 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__6->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__7 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__7->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__8 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__8->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__9 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__9->field4)))), UINT64_C(0), 32, 4);
  var_name_tmp__10 = var_name_tmp__2;
  __adin_store_((((uint8_t*)((&var_name_tmp__10->field5)))), UINT64_C(33), 32, 4);
  var_name_tmp__11 = var_name_tmp__2;
  if ((((var_name_tmp__11 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897488)))&1))) {
    goto var_name_tmp__27;
  } else {
    goto var_name_tmp__28;
  }

var_name_tmp__27:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2))), UINT64_C(61), 32, 4);
  goto var_name_tmp__29;

var_name_tmp__28:
  var_name_tmp__12 = var_name_tmp__2;
  if ((((var_name_tmp__12 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897512)))&1))) {
    goto var_name_tmp__30;
  } else {
    goto var_name_tmp__31;
  }

var_name_tmp__30:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2))), UINT64_C(3904), 32, 4);
  goto var_name_tmp__32;

var_name_tmp__31:
  var_name_tmp__13 = var_name_tmp__2;
  if ((((var_name_tmp__13 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897536)))&1))) {
    goto var_name_tmp__33;
  } else {
    goto var_name_tmp__34;
  }

var_name_tmp__33:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2))), UINT64_C(3997696), 32, 4);
  goto var_name_tmp__35;

var_name_tmp__34:
  var_name_tmp__14 = var_name_tmp__2;
  if ((((var_name_tmp__14 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897560)))&1))) {
    goto var_name_tmp__36;
  } else {
    goto var_name_tmp__37;
  }

var_name_tmp__36:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2))), UINT64_C(255852544), 32, 4);
  goto var_name_tmp__38;

var_name_tmp__37:
  var_name_tmp__15 = var_name_tmp__2;
  if ((((var_name_tmp__15 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897584)))&1))) {
    goto var_name_tmp__39;
  } else {
    goto var_name_tmp__40;
  }

var_name_tmp__39:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3))), UINT64_C(536870973), 32, 4);
  goto var_name_tmp__41;

var_name_tmp__40:
  var_name_tmp__16 = var_name_tmp__2;
  if ((((var_name_tmp__16 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897608)))&1))) {
    goto var_name_tmp__42;
  } else {
    goto var_name_tmp__43;
  }

var_name_tmp__42:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3))), UINT64_C(536874816), 32, 4);
  goto var_name_tmp__44;

var_name_tmp__43:
  var_name_tmp__17 = var_name_tmp__2;
  if ((((var_name_tmp__17 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897632)))&1))) {
    goto var_name_tmp__45;
  } else {
    goto var_name_tmp__46;
  }

var_name_tmp__45:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3))), UINT64_C(540868608), 32, 4);
  goto var_name_tmp__47;

var_name_tmp__46:
  var_name_tmp__18 = var_name_tmp__2;
  if ((((var_name_tmp__18 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897656)))&1))) {
    goto var_name_tmp__48;
  } else {
    goto var_name_tmp__49;
  }

var_name_tmp__48:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3))), UINT64_C(792723456), 32, 4);
  goto var_name_tmp__50;

var_name_tmp__49:
  var_name_tmp__19 = var_name_tmp__2;
  if ((((var_name_tmp__19 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512)))&1))) {
    goto var_name_tmp__51;
  } else {
    goto var_name_tmp__52;
  }

var_name_tmp__51:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2))), UINT64_C(61), 32, 4);
  goto var_name_tmp__53;

var_name_tmp__52:
  var_name_tmp__20 = var_name_tmp__2;
  if ((((var_name_tmp__20 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898536)))&1))) {
    goto var_name_tmp__54;
  } else {
    goto var_name_tmp__55;
  }

var_name_tmp__54:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2))), UINT64_C(3904), 32, 4);
  goto var_name_tmp__56;

var_name_tmp__55:
  var_name_tmp__21 = var_name_tmp__2;
  if ((((var_name_tmp__21 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898560)))&1))) {
    goto var_name_tmp__57;
  } else {
    goto var_name_tmp__58;
  }

var_name_tmp__57:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2))), UINT64_C(3997696), 32, 4);
  goto var_name_tmp__59;

var_name_tmp__58:
  var_name_tmp__22 = var_name_tmp__2;
  if ((((var_name_tmp__22 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898584)))&1))) {
    goto var_name_tmp__60;
  } else {
    goto var_name_tmp__61;
  }

var_name_tmp__60:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2))), UINT64_C(255852544), 32, 4);
  goto var_name_tmp__62;

var_name_tmp__61:
  var_name_tmp__23 = var_name_tmp__2;
  if ((((var_name_tmp__23 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898608)))&1))) {
    goto var_name_tmp__63;
  } else {
    goto var_name_tmp__64;
  }

var_name_tmp__63:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3))), UINT64_C(536870973), 32, 4);
  goto var_name_tmp__65;

var_name_tmp__64:
  var_name_tmp__24 = var_name_tmp__2;
  if ((((var_name_tmp__24 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898632)))&1))) {
    goto var_name_tmp__66;
  } else {
    goto var_name_tmp__67;
  }

var_name_tmp__66:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3))), UINT64_C(536874816), 32, 4);
  goto var_name_tmp__68;

var_name_tmp__67:
  var_name_tmp__25 = var_name_tmp__2;
  if ((((var_name_tmp__25 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898656)))&1))) {
    goto var_name_tmp__69;
  } else {
    goto var_name_tmp__70;
  }

var_name_tmp__69:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3))), UINT64_C(540868608), 32, 4);
  goto var_name_tmp__71;

var_name_tmp__70:
  var_name_tmp__26 = var_name_tmp__2;
  if ((((var_name_tmp__26 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898680)))&1))) {
    goto var_name_tmp__72;
  } else {
    goto var_name_tmp__73;
  }

var_name_tmp__72:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3))), UINT64_C(792723456), 32, 4);
  goto var_name_tmp__73;

var_name_tmp__73:
  goto var_name_tmp__71;

var_name_tmp__71:
  goto var_name_tmp__68;

var_name_tmp__68:
  goto var_name_tmp__65;

var_name_tmp__65:
  goto var_name_tmp__62;

var_name_tmp__62:
  goto var_name_tmp__59;

var_name_tmp__59:
  goto var_name_tmp__56;

var_name_tmp__56:
  goto var_name_tmp__53;

var_name_tmp__53:
  goto var_name_tmp__50;

var_name_tmp__50:
  goto var_name_tmp__47;

var_name_tmp__47:
  goto var_name_tmp__44;

var_name_tmp__44:
  goto var_name_tmp__41;

var_name_tmp__41:
  goto var_name_tmp__38;

var_name_tmp__38:
  goto var_name_tmp__35;

var_name_tmp__35:
  goto var_name_tmp__32;

var_name_tmp__32:
  goto var_name_tmp__29;

var_name_tmp__29:
  return;
}


void DMA_Init(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__74, struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__75) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__76;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__79;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__80;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__81;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__82;
  uint64_t var_name_load_i32_5;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__83;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__84;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__85;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__86;
  uint64_t var_name_load_i32_17;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__87;
  uint64_t var_name_load_i32_20;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__88;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__89;
  uint64_t var_name_load_i32_26;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__90;
  uint64_t var_name_load_i32_29;
  uint32_t var_name_tmp__91;
  uint32_t var_name_tmp__92;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__93;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__94;
  uint64_t var_name_load_i32_33;
  uint32_t var_name_tmp__95;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__96;
  uint64_t var_name_load_i32_36;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__97;
  uint64_t var_name_load_i32_39;
  uint32_t var_name_tmp__98;
  uint32_t var_name_tmp__99;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__100;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__101;
  uint64_t var_name_load_i32_44;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__102;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__103;
  uint64_t var_name_load_i32_49;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__104;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__105;
  uint64_t var_name_load_i32_54;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__106;

  var_name_tmp__76 = var_name_tmp__74;
  var_name_tmp__77 = var_name_tmp__75;
  var_name_tmp__78 = 0;
  var_name_tmp__79 = var_name_tmp__76;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__79->field0)))), 32, 4);
  var_name_tmp__78 = (((uint32_t)var_name_load_i32_));
  var_name_tmp__80 = var_name_tmp__78;
  var_name_tmp__78 = (var_name_tmp__80 & -266567617);
  var_name_tmp__81 = var_name_tmp__77;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__81->field0)))), 32, 4);
  var_name_tmp__82 = var_name_tmp__77;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__82->field3)))), 32, 4);
  var_name_tmp__83 = var_name_tmp__77;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__83->field5)))), 32, 4);
  var_name_tmp__84 = var_name_tmp__77;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__84->field6)))), 32, 4);
  var_name_tmp__85 = var_name_tmp__77;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__85->field7)))), 32, 4);
  var_name_tmp__86 = var_name_tmp__77;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__86->field8)))), 32, 4);
  var_name_tmp__87 = var_name_tmp__77;
  var_name_load_i32_20 = __adin_load_((((uint8_t*)((&var_name_tmp__87->field9)))), 32, 4);
  var_name_tmp__88 = var_name_tmp__77;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&var_name_tmp__88->field10)))), 32, 4);
  var_name_tmp__89 = var_name_tmp__77;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__89->field13)))), 32, 4);
  var_name_tmp__90 = var_name_tmp__77;
  var_name_load_i32_29 = __adin_load_((((uint8_t*)((&var_name_tmp__90->field14)))), 32, 4);
  var_name_tmp__91 = var_name_tmp__78;
  var_name_tmp__78 = (var_name_tmp__91 | ((((((((((((uint32_t)var_name_load_i32_2)) | (((uint32_t)var_name_load_i32_5))) | (((uint32_t)var_name_load_i32_8))) | (((uint32_t)var_name_load_i32_11))) | (((uint32_t)var_name_load_i32_14))) | (((uint32_t)var_name_load_i32_17))) | (((uint32_t)var_name_load_i32_20))) | (((uint32_t)var_name_load_i32_23))) | (((uint32_t)var_name_load_i32_26))) | (((uint32_t)var_name_load_i32_29))));
  var_name_tmp__92 = var_name_tmp__78;
  var_name_tmp__93 = var_name_tmp__76;
  __adin_store_((((uint8_t*)((&var_name_tmp__93->field0)))), (((uint64_t)(uint32_t)var_name_tmp__92)), 32, 4);
  var_name_tmp__94 = var_name_tmp__76;
  var_name_load_i32_33 = __adin_load_((((uint8_t*)((&var_name_tmp__94->field5)))), 32, 4);
  var_name_tmp__78 = (((uint32_t)var_name_load_i32_33));
  var_name_tmp__95 = var_name_tmp__78;
  var_name_tmp__78 = (var_name_tmp__95 & -8);
  var_name_tmp__96 = var_name_tmp__77;
  var_name_load_i32_36 = __adin_load_((((uint8_t*)((&var_name_tmp__96->field11)))), 32, 4);
  var_name_tmp__97 = var_name_tmp__77;
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&var_name_tmp__97->field12)))), 32, 4);
  var_name_tmp__98 = var_name_tmp__78;
  var_name_tmp__78 = (var_name_tmp__98 | ((((uint32_t)var_name_load_i32_36)) | (((uint32_t)var_name_load_i32_39))));
  var_name_tmp__99 = var_name_tmp__78;
  var_name_tmp__100 = var_name_tmp__76;
  __adin_store_((((uint8_t*)((&var_name_tmp__100->field5)))), (((uint64_t)(uint32_t)var_name_tmp__99)), 32, 4);
  var_name_tmp__101 = var_name_tmp__77;
  var_name_load_i32_44 = __adin_load_((((uint8_t*)((&var_name_tmp__101->field4)))), 32, 4);
  var_name_tmp__102 = var_name_tmp__76;
  __adin_store_((((uint8_t*)((&var_name_tmp__102->field1)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_44)))), 32, 4);
  var_name_tmp__103 = var_name_tmp__77;
  var_name_load_i32_49 = __adin_load_((((uint8_t*)((&var_name_tmp__103->field1)))), 32, 4);
  var_name_tmp__104 = var_name_tmp__76;
  __adin_store_((((uint8_t*)((&var_name_tmp__104->field2)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_49)))), 32, 4);
  var_name_tmp__105 = var_name_tmp__77;
  var_name_load_i32_54 = __adin_load_((((uint8_t*)((&var_name_tmp__105->field2)))), 32, 4);
  var_name_tmp__106 = var_name_tmp__76;
  __adin_store_((((uint8_t*)((&var_name_tmp__106->field3)))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_54)))), 32, 4);
}


void DMA_StructInit(struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__107) {
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__108;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__109;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__110;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__111;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__112;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__113;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__114;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__115;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__116;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__117;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__118;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__119;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__120;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__121;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__122;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__123;

  var_name_tmp__108 = var_name_tmp__107;
  var_name_tmp__109 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__109->field0)))), UINT64_C(0), 32, 4);
  var_name_tmp__110 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__110->field1)))), UINT64_C(0), 32, 4);
  var_name_tmp__111 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__111->field2)))), UINT64_C(0), 32, 4);
  var_name_tmp__112 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__112->field3)))), UINT64_C(0), 32, 4);
  var_name_tmp__113 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__113->field4)))), UINT64_C(0), 32, 4);
  var_name_tmp__114 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__114->field5)))), UINT64_C(0), 32, 4);
  var_name_tmp__115 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__115->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__116 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__116->field7)))), UINT64_C(0), 32, 4);
  var_name_tmp__117 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__117->field8)))), UINT64_C(0), 32, 4);
  var_name_tmp__118 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__118->field9)))), UINT64_C(0), 32, 4);
  var_name_tmp__119 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__119->field10)))), UINT64_C(0), 32, 4);
  var_name_tmp__120 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__120->field11)))), UINT64_C(0), 32, 4);
  var_name_tmp__121 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__121->field12)))), UINT64_C(0), 32, 4);
  var_name_tmp__122 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__122->field13)))), UINT64_C(0), 32, 4);
  var_name_tmp__123 = var_name_tmp__108;
  __adin_store_((((uint8_t*)((&var_name_tmp__123->field14)))), UINT64_C(0), 32, 4);
}


void DMA_Cmd(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__124, uint32_t var_name_tmp__125) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__126;    /* Address-exposed local */
  uint32_t var_name_tmp__127;    /* Address-exposed local */
  uint32_t var_name_tmp__128;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__129;
  uint32_t* var_name_tmp__130;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__131;
  uint32_t* var_name_tmp__132;
  uint64_t var_name_load_i32_3;

  var_name_tmp__126 = var_name_tmp__124;
  var_name_tmp__127 = var_name_tmp__125;
  var_name_tmp__128 = var_name_tmp__127;
  if ((((var_name_tmp__128 != 0u)&1))) {
    goto var_name_tmp__133;
  } else {
    goto var_name_tmp__134;
  }

var_name_tmp__133:
  var_name_tmp__129 = var_name_tmp__126;
  var_name_tmp__130 = (&var_name_tmp__129->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__130)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__130)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  goto var_name_tmp__135;

var_name_tmp__134:
  var_name_tmp__131 = var_name_tmp__126;
  var_name_tmp__132 = (&var_name_tmp__131->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__132)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__132)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -2))), 32, 4);
  goto var_name_tmp__135;

var_name_tmp__135:
  return;
}


void DMA_PeriphIncOffsetSizeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__136, uint32_t var_name_tmp__137) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__138;    /* Address-exposed local */
  uint32_t var_name_tmp__139;    /* Address-exposed local */
  uint32_t var_name_tmp__140;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__141;
  uint32_t* var_name_tmp__142;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__143;
  uint32_t* var_name_tmp__144;
  uint64_t var_name_load_i32_3;

  var_name_tmp__138 = var_name_tmp__136;
  var_name_tmp__139 = var_name_tmp__137;
  var_name_tmp__140 = var_name_tmp__139;
  if ((((var_name_tmp__140 != 0u)&1))) {
    goto var_name_tmp__145;
  } else {
    goto var_name_tmp__146;
  }

var_name_tmp__145:
  var_name_tmp__141 = var_name_tmp__138;
  var_name_tmp__142 = (&var_name_tmp__141->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__142)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__142)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 32768))), 32, 4);
  goto var_name_tmp__147;

var_name_tmp__146:
  var_name_tmp__143 = var_name_tmp__138;
  var_name_tmp__144 = (&var_name_tmp__143->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__144)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__144)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -32769))), 32, 4);
  goto var_name_tmp__147;

var_name_tmp__147:
  return;
}


void DMA_FlowControllerConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__148, uint32_t var_name_tmp__149) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__150;    /* Address-exposed local */
  uint32_t var_name_tmp__151;    /* Address-exposed local */
  uint32_t var_name_tmp__152;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__153;
  uint32_t* var_name_tmp__154;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__155;
  uint32_t* var_name_tmp__156;
  uint64_t var_name_load_i32_3;

  var_name_tmp__150 = var_name_tmp__148;
  var_name_tmp__151 = var_name_tmp__149;
  var_name_tmp__152 = var_name_tmp__151;
  if ((((var_name_tmp__152 != 0u)&1))) {
    goto var_name_tmp__157;
  } else {
    goto var_name_tmp__158;
  }

var_name_tmp__157:
  var_name_tmp__153 = var_name_tmp__150;
  var_name_tmp__154 = (&var_name_tmp__153->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__154)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__154)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 32))), 32, 4);
  goto var_name_tmp__159;

var_name_tmp__158:
  var_name_tmp__155 = var_name_tmp__150;
  var_name_tmp__156 = (&var_name_tmp__155->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__156)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__156)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -33))), 32, 4);
  goto var_name_tmp__159;

var_name_tmp__159:
  return;
}


void DMA_SetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__160, uint16_t var_name_tmp__161) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__162;    /* Address-exposed local */
  uint16_t var_name_tmp__163;    /* Address-exposed local */
  uint16_t var_name_tmp__164;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__165;

  var_name_tmp__162 = var_name_tmp__160;
  var_name_tmp__163 = var_name_tmp__161;
  var_name_tmp__164 = var_name_tmp__163;
  var_name_tmp__165 = var_name_tmp__162;
  __adin_store_((((uint8_t*)((&var_name_tmp__165->field1)))), (((uint64_t)(uint32_t)(((uint32_t)(uint16_t)var_name_tmp__164)))), 32, 4);
}


uint16_t DMA_GetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__166) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__167;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__168;
  uint64_t var_name_load_i32_;

  var_name_tmp__167 = var_name_tmp__166;
  var_name_tmp__168 = var_name_tmp__167;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__168->field1)))), 32, 4);
  return (((uint16_t)(((uint32_t)var_name_load_i32_))));
}


void DMA_DoubleBufferModeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__169, uint32_t var_name_tmp__170, uint32_t var_name_tmp__171) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__172;    /* Address-exposed local */
  uint32_t var_name_tmp__173;    /* Address-exposed local */
  uint32_t var_name_tmp__174;    /* Address-exposed local */
  uint32_t var_name_tmp__175;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__176;
  uint32_t* var_name_tmp__177;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__178;
  uint32_t* var_name_tmp__179;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__180;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__181;

  var_name_tmp__172 = var_name_tmp__169;
  var_name_tmp__173 = var_name_tmp__170;
  var_name_tmp__174 = var_name_tmp__171;
  var_name_tmp__175 = var_name_tmp__174;
  if ((((var_name_tmp__175 != 0u)&1))) {
    goto var_name_tmp__182;
  } else {
    goto var_name_tmp__183;
  }

var_name_tmp__182:
  var_name_tmp__176 = var_name_tmp__172;
  var_name_tmp__177 = (&var_name_tmp__176->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__177)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__177)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 524288))), 32, 4);
  goto var_name_tmp__184;

var_name_tmp__183:
  var_name_tmp__178 = var_name_tmp__172;
  var_name_tmp__179 = (&var_name_tmp__178->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__179)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__179)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -524289))), 32, 4);
  goto var_name_tmp__184;

var_name_tmp__184:
  var_name_tmp__180 = var_name_tmp__173;
  var_name_tmp__181 = var_name_tmp__172;
  __adin_store_((((uint8_t*)((&var_name_tmp__181->field4)))), (((uint64_t)(uint32_t)var_name_tmp__180)), 32, 4);
}


void DMA_DoubleBufferModeCmd(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__185, uint32_t var_name_tmp__186) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__187;    /* Address-exposed local */
  uint32_t var_name_tmp__188;    /* Address-exposed local */
  uint32_t var_name_tmp__189;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__190;
  uint32_t* var_name_tmp__191;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__192;
  uint32_t* var_name_tmp__193;
  uint64_t var_name_load_i32_3;

  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__186;
  var_name_tmp__189 = var_name_tmp__188;
  if ((((var_name_tmp__189 != 0u)&1))) {
    goto var_name_tmp__194;
  } else {
    goto var_name_tmp__195;
  }

var_name_tmp__194:
  var_name_tmp__190 = var_name_tmp__187;
  var_name_tmp__191 = (&var_name_tmp__190->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__191)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__191)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 262144))), 32, 4);
  goto var_name_tmp__196;

var_name_tmp__195:
  var_name_tmp__192 = var_name_tmp__187;
  var_name_tmp__193 = (&var_name_tmp__192->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__193)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__193)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -262145))), 32, 4);
  goto var_name_tmp__196;

var_name_tmp__196:
  return;
}


void DMA_MemoryTargetConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__197, uint32_t var_name_tmp__198, uint32_t var_name_tmp__199) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__200;    /* Address-exposed local */
  uint32_t var_name_tmp__201;    /* Address-exposed local */
  uint32_t var_name_tmp__202;    /* Address-exposed local */
  uint32_t var_name_tmp__203;
  uint32_t var_name_tmp__204;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__205;
  uint32_t var_name_tmp__206;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__207;

  var_name_tmp__200 = var_name_tmp__197;
  var_name_tmp__201 = var_name_tmp__198;
  var_name_tmp__202 = var_name_tmp__199;
  var_name_tmp__203 = var_name_tmp__202;
  if ((((var_name_tmp__203 != 0u)&1))) {
    goto var_name_tmp__208;
  } else {
    goto var_name_tmp__209;
  }

var_name_tmp__208:
  var_name_tmp__204 = var_name_tmp__201;
  var_name_tmp__205 = var_name_tmp__200;
  __adin_store_((((uint8_t*)((&var_name_tmp__205->field4)))), (((uint64_t)(uint32_t)var_name_tmp__204)), 32, 4);
  goto var_name_tmp__210;

var_name_tmp__209:
  var_name_tmp__206 = var_name_tmp__201;
  var_name_tmp__207 = var_name_tmp__200;
  __adin_store_((((uint8_t*)((&var_name_tmp__207->field3)))), (((uint64_t)(uint32_t)var_name_tmp__206)), 32, 4);
  goto var_name_tmp__210;

var_name_tmp__210:
  return;
}


uint32_t DMA_GetCurrentMemoryTarget(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__211) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__212;    /* Address-exposed local */
  uint32_t var_name_tmp__213;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__214;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__215;

  var_name_tmp__212 = var_name_tmp__211;
  var_name_tmp__213 = 0;
  var_name_tmp__214 = var_name_tmp__212;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__214->field0)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 524288) != 0u)&1))) {
    goto var_name_tmp__216;
  } else {
    goto var_name_tmp__217;
  }

var_name_tmp__216:
  var_name_tmp__213 = 1;
  goto var_name_tmp__218;

var_name_tmp__217:
  var_name_tmp__213 = 0;
  goto var_name_tmp__218;

var_name_tmp__218:
  var_name_tmp__215 = var_name_tmp__213;
  return var_name_tmp__215;
}


uint32_t DMA_GetCmdStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__219) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__220;    /* Address-exposed local */
  uint32_t var_name_tmp__221;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__222;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__223;

  var_name_tmp__220 = var_name_tmp__219;
  var_name_tmp__221 = 0;
  var_name_tmp__222 = var_name_tmp__220;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__222->field0)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 1) != 0u)&1))) {
    goto var_name_tmp__224;
  } else {
    goto var_name_tmp__225;
  }

var_name_tmp__224:
  var_name_tmp__221 = 1;
  goto var_name_tmp__226;

var_name_tmp__225:
  var_name_tmp__221 = 0;
  goto var_name_tmp__226;

var_name_tmp__226:
  var_name_tmp__223 = var_name_tmp__221;
  return var_name_tmp__223;
}


uint32_t DMA_GetFIFOStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__227) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__228;    /* Address-exposed local */
  uint32_t var_name_tmp__229;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__230;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__231;

  var_name_tmp__228 = var_name_tmp__227;
  var_name_tmp__229 = 0;
  var_name_tmp__230 = var_name_tmp__228;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__230->field5)))), 32, 4);
  var_name_tmp__229 = ((((uint32_t)var_name_load_i32_)) & 56);
  var_name_tmp__231 = var_name_tmp__229;
  return var_name_tmp__231;
}


uint32_t DMA_GetFlagStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__232, uint32_t var_name_tmp__233) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__234;    /* Address-exposed local */
  uint32_t var_name_tmp__235;    /* Address-exposed local */
  uint32_t var_name_tmp__236;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__237;    /* Address-exposed local */
  uint32_t var_name_tmp__238;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__239;
  uint32_t var_name_tmp__240;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__241;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__242;
  uint64_t var_name_load_i32_2;
  uint32_t var_name_tmp__243;
  uint32_t var_name_tmp__244;
  uint32_t var_name_tmp__245;
  uint32_t var_name_tmp__246;

  var_name_tmp__234 = var_name_tmp__232;
  var_name_tmp__235 = var_name_tmp__233;
  var_name_tmp__236 = 0;
  var_name_tmp__238 = 0;
  var_name_tmp__239 = var_name_tmp__234;
  if ((((((uint64_t)var_name_tmp__239) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__247;
  } else {
    goto var_name_tmp__248;
  }

var_name_tmp__247:
  var_name_tmp__237 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__249;

var_name_tmp__248:
  var_name_tmp__237 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__249;

var_name_tmp__249:
  var_name_tmp__240 = var_name_tmp__235;
  if (((((var_name_tmp__240 & 536870912) != 0u)&1))) {
    goto var_name_tmp__250;
  } else {
    goto var_name_tmp__251;
  }

var_name_tmp__250:
  var_name_tmp__241 = var_name_tmp__237;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__241->field1)))), 32, 4);
  var_name_tmp__238 = (((uint32_t)var_name_load_i32_));
  goto var_name_tmp__252;

var_name_tmp__251:
  var_name_tmp__242 = var_name_tmp__237;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__242->field0)))), 32, 4);
  var_name_tmp__238 = (((uint32_t)var_name_load_i32_2));
  goto var_name_tmp__252;

var_name_tmp__252:
  var_name_tmp__243 = var_name_tmp__238;
  var_name_tmp__238 = (var_name_tmp__243 & 259854205);
  var_name_tmp__244 = var_name_tmp__238;
  var_name_tmp__245 = var_name_tmp__235;
  if (((((var_name_tmp__244 & var_name_tmp__245) != 0u)&1))) {
    goto var_name_tmp__253;
  } else {
    goto var_name_tmp__254;
  }

var_name_tmp__253:
  var_name_tmp__236 = 1;
  goto var_name_tmp__255;

var_name_tmp__254:
  var_name_tmp__236 = 0;
  goto var_name_tmp__255;

var_name_tmp__255:
  var_name_tmp__246 = var_name_tmp__236;
  return var_name_tmp__246;
}


void DMA_ClearFlag(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__256, uint32_t var_name_tmp__257) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__258;    /* Address-exposed local */
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__260;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint32_t var_name_tmp__263;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__264;
  uint32_t var_name_tmp__265;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__266;

  var_name_tmp__258 = var_name_tmp__256;
  var_name_tmp__259 = var_name_tmp__257;
  var_name_tmp__261 = var_name_tmp__258;
  if ((((((uint64_t)var_name_tmp__261) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__267;
  } else {
    goto var_name_tmp__268;
  }

var_name_tmp__267:
  var_name_tmp__260 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__269;

var_name_tmp__268:
  var_name_tmp__260 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__269;

var_name_tmp__269:
  var_name_tmp__262 = var_name_tmp__259;
  if (((((var_name_tmp__262 & 536870912) != 0u)&1))) {
    goto var_name_tmp__270;
  } else {
    goto var_name_tmp__271;
  }

var_name_tmp__270:
  var_name_tmp__263 = var_name_tmp__259;
  var_name_tmp__264 = var_name_tmp__260;
  __adin_store_((((uint8_t*)((&var_name_tmp__264->field3)))), (((uint64_t)(uint32_t)(var_name_tmp__263 & 259854205))), 32, 4);
  goto var_name_tmp__272;

var_name_tmp__271:
  var_name_tmp__265 = var_name_tmp__259;
  var_name_tmp__266 = var_name_tmp__260;
  __adin_store_((((uint8_t*)((&var_name_tmp__266->field2)))), (((uint64_t)(uint32_t)(var_name_tmp__265 & 259854205))), 32, 4);
  goto var_name_tmp__272;

var_name_tmp__272:
  return;
}


void DMA_ITConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__273, uint32_t var_name_tmp__274, uint32_t var_name_tmp__275) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__276;    /* Address-exposed local */
  uint32_t var_name_tmp__277;    /* Address-exposed local */
  uint32_t var_name_tmp__278;    /* Address-exposed local */
  uint32_t var_name_tmp__279;
  uint32_t var_name_tmp__280;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__281;
  uint32_t* var_name_tmp__282;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__283;
  uint32_t* var_name_tmp__284;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__285;
  uint32_t var_name_tmp__286;
  uint32_t var_name_tmp__287;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__288;
  uint32_t* var_name_tmp__289;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__290;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__291;
  uint32_t* var_name_tmp__292;
  uint64_t var_name_load_i32_13;

  var_name_tmp__276 = var_name_tmp__273;
  var_name_tmp__277 = var_name_tmp__274;
  var_name_tmp__278 = var_name_tmp__275;
  var_name_tmp__279 = var_name_tmp__277;
  if (((((var_name_tmp__279 & 128) != 0u)&1))) {
    goto var_name_tmp__293;
  } else {
    goto var_name_tmp__294;
  }

var_name_tmp__293:
  var_name_tmp__280 = var_name_tmp__278;
  if ((((var_name_tmp__280 != 0u)&1))) {
    goto var_name_tmp__295;
  } else {
    goto var_name_tmp__296;
  }

var_name_tmp__295:
  var_name_tmp__281 = var_name_tmp__276;
  var_name_tmp__282 = (&var_name_tmp__281->field5);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__282)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__282)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 128))), 32, 4);
  goto var_name_tmp__297;

var_name_tmp__296:
  var_name_tmp__283 = var_name_tmp__276;
  var_name_tmp__284 = (&var_name_tmp__283->field5);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__284)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__284)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -129))), 32, 4);
  goto var_name_tmp__297;

var_name_tmp__297:
  goto var_name_tmp__294;

var_name_tmp__294:
  var_name_tmp__285 = var_name_tmp__277;
  if ((((var_name_tmp__285 != 128u)&1))) {
    goto var_name_tmp__298;
  } else {
    goto var_name_tmp__299;
  }

var_name_tmp__298:
  var_name_tmp__286 = var_name_tmp__278;
  if ((((var_name_tmp__286 != 0u)&1))) {
    goto var_name_tmp__300;
  } else {
    goto var_name_tmp__301;
  }

var_name_tmp__300:
  var_name_tmp__287 = var_name_tmp__277;
  var_name_tmp__288 = var_name_tmp__276;
  var_name_tmp__289 = (&var_name_tmp__288->field0);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)var_name_tmp__289)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__289)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_8)) | (var_name_tmp__287 & 30)))), 32, 4);
  goto var_name_tmp__302;

var_name_tmp__301:
  var_name_tmp__290 = var_name_tmp__277;
  var_name_tmp__291 = var_name_tmp__276;
  var_name_tmp__292 = (&var_name_tmp__291->field0);
  var_name_load_i32_13 = __adin_load_((((uint8_t*)var_name_tmp__292)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__292)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) & (~((var_name_tmp__290 & 30)))))), 32, 4);
  goto var_name_tmp__302;

var_name_tmp__302:
  goto var_name_tmp__299;

var_name_tmp__299:
  return;
}


uint32_t DMA_GetITStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__303, uint32_t var_name_tmp__304) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__305;    /* Address-exposed local */
  uint32_t var_name_tmp__306;    /* Address-exposed local */
  uint32_t var_name_tmp__307;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__308;    /* Address-exposed local */
  uint32_t var_name_tmp__309;    /* Address-exposed local */
  uint32_t var_name_tmp__310;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__311;
  uint32_t var_name_tmp__312;
  uint32_t var_name_tmp__313;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__314;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__315;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__316;
  uint64_t var_name_load_i32_2;
  uint32_t var_name_tmp__317;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__318;
  uint64_t var_name_load_i32_5;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__319;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__320;
  uint32_t var_name_tmp__321;
  uint32_t var_name_tmp__322;
  uint32_t var_name_tmp__323;
  uint32_t var_name_tmp__324;

  var_name_tmp__305 = var_name_tmp__303;
  var_name_tmp__306 = var_name_tmp__304;
  var_name_tmp__307 = 0;
  var_name_tmp__309 = 0;
  var_name_tmp__310 = 0;
  var_name_tmp__311 = var_name_tmp__305;
  if ((((((uint64_t)var_name_tmp__311) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__325;
  } else {
    goto var_name_tmp__326;
  }

var_name_tmp__325:
  var_name_tmp__308 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__327;

var_name_tmp__326:
  var_name_tmp__308 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__327;

var_name_tmp__327:
  var_name_tmp__312 = var_name_tmp__306;
  if (((((var_name_tmp__312 & 255594300) != 0u)&1))) {
    goto var_name_tmp__328;
  } else {
    goto var_name_tmp__329;
  }

var_name_tmp__328:
  var_name_tmp__313 = var_name_tmp__306;
  var_name_tmp__309 = ((llvm_lshr_u32(var_name_tmp__313, 11)) & 30);
  var_name_tmp__314 = var_name_tmp__305;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__314->field0)))), 32, 4);
  var_name_tmp__315 = var_name_tmp__309;
  var_name_tmp__310 = ((((uint32_t)var_name_load_i32_)) & var_name_tmp__315);
  goto var_name_tmp__330;

var_name_tmp__329:
  var_name_tmp__316 = var_name_tmp__305;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__316->field5)))), 32, 4);
  var_name_tmp__310 = ((((uint32_t)var_name_load_i32_2)) & 128);
  goto var_name_tmp__330;

var_name_tmp__330:
  var_name_tmp__317 = var_name_tmp__306;
  if (((((var_name_tmp__317 & 536870912) != 0u)&1))) {
    goto var_name_tmp__331;
  } else {
    goto var_name_tmp__332;
  }

var_name_tmp__331:
  var_name_tmp__318 = var_name_tmp__308;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__318->field1)))), 32, 4);
  var_name_tmp__309 = (((uint32_t)var_name_load_i32_5));
  goto var_name_tmp__333;

var_name_tmp__332:
  var_name_tmp__319 = var_name_tmp__308;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__319->field0)))), 32, 4);
  var_name_tmp__309 = (((uint32_t)var_name_load_i32_8));
  goto var_name_tmp__333;

var_name_tmp__333:
  var_name_tmp__320 = var_name_tmp__309;
  var_name_tmp__309 = (var_name_tmp__320 & 259854205);
  var_name_tmp__321 = var_name_tmp__309;
  var_name_tmp__322 = var_name_tmp__306;
  if (((((var_name_tmp__321 & var_name_tmp__322) != 0u)&1))) {
    goto var_name_tmp__334;
  } else {
    goto var_name_tmp__335;
  }

var_name_tmp__334:
  var_name_tmp__323 = var_name_tmp__310;
  if ((((var_name_tmp__323 != 0u)&1))) {
    goto var_name_tmp__336;
  } else {
    goto var_name_tmp__335;
  }

var_name_tmp__336:
  var_name_tmp__307 = 1;
  goto var_name_tmp__337;

var_name_tmp__335:
  var_name_tmp__307 = 0;
  goto var_name_tmp__337;

var_name_tmp__337:
  var_name_tmp__324 = var_name_tmp__307;
  return var_name_tmp__324;
}


void DMA_ClearITPendingBit(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__338, uint32_t var_name_tmp__339) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__340;    /* Address-exposed local */
  uint32_t var_name_tmp__341;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__342;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__343;
  uint32_t var_name_tmp__344;
  uint32_t var_name_tmp__345;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__346;
  uint32_t var_name_tmp__347;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__348;

  var_name_tmp__340 = var_name_tmp__338;
  var_name_tmp__341 = var_name_tmp__339;
  var_name_tmp__343 = var_name_tmp__340;
  if ((((((uint64_t)var_name_tmp__343) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__349;
  } else {
    goto var_name_tmp__350;
  }

var_name_tmp__349:
  var_name_tmp__342 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__351;

var_name_tmp__350:
  var_name_tmp__342 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__351;

var_name_tmp__351:
  var_name_tmp__344 = var_name_tmp__341;
  if (((((var_name_tmp__344 & 536870912) != 0u)&1))) {
    goto var_name_tmp__352;
  } else {
    goto var_name_tmp__353;
  }

var_name_tmp__352:
  var_name_tmp__345 = var_name_tmp__341;
  var_name_tmp__346 = var_name_tmp__342;
  __adin_store_((((uint8_t*)((&var_name_tmp__346->field3)))), (((uint64_t)(uint32_t)(var_name_tmp__345 & 259854205))), 32, 4);
  goto var_name_tmp__354;

var_name_tmp__353:
  var_name_tmp__347 = var_name_tmp__341;
  var_name_tmp__348 = var_name_tmp__342;
  __adin_store_((((uint8_t*)((&var_name_tmp__348->field2)))), (((uint64_t)(uint32_t)(var_name_tmp__347 & 259854205))), 32, 4);
  goto var_name_tmp__354;

var_name_tmp__354:
  return;
}

