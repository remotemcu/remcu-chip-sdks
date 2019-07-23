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
  uint32_t var_name_tmp__5;
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
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__27;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  var_name_tmp__4 = (&var_name_tmp__3->field0);
  var_name_tmp__5 = *(volatile uint32_t*)var_name_tmp__4;
  *(volatile uint32_t*)var_name_tmp__4 = (var_name_tmp__5 & -2);
  var_name_tmp__6 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__6->field0)) = 0;
  var_name_tmp__7 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__7->field1)) = 0;
  var_name_tmp__8 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__8->field2)) = 0;
  var_name_tmp__9 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__9->field3)) = 0;
  var_name_tmp__10 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__10->field4)) = 0;
  var_name_tmp__11 = var_name_tmp__2;
  *(volatile uint32_t*)((&var_name_tmp__11->field5)) = 33;
  var_name_tmp__12 = var_name_tmp__2;
  if ((((var_name_tmp__12 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897488)))&1))) {
    goto var_name_tmp__28;
  } else {
    goto var_name_tmp__29;
  }

var_name_tmp__28:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2)) = 61;
  goto var_name_tmp__30;

var_name_tmp__29:
  var_name_tmp__13 = var_name_tmp__2;
  if ((((var_name_tmp__13 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897512)))&1))) {
    goto var_name_tmp__31;
  } else {
    goto var_name_tmp__32;
  }

var_name_tmp__31:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2)) = 3904;
  goto var_name_tmp__33;

var_name_tmp__32:
  var_name_tmp__14 = var_name_tmp__2;
  if ((((var_name_tmp__14 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897536)))&1))) {
    goto var_name_tmp__34;
  } else {
    goto var_name_tmp__35;
  }

var_name_tmp__34:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2)) = 3997696;
  goto var_name_tmp__36;

var_name_tmp__35:
  var_name_tmp__15 = var_name_tmp__2;
  if ((((var_name_tmp__15 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897560)))&1))) {
    goto var_name_tmp__37;
  } else {
    goto var_name_tmp__38;
  }

var_name_tmp__37:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field2)) = 255852544;
  goto var_name_tmp__39;

var_name_tmp__38:
  var_name_tmp__16 = var_name_tmp__2;
  if ((((var_name_tmp__16 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897584)))&1))) {
    goto var_name_tmp__40;
  } else {
    goto var_name_tmp__41;
  }

var_name_tmp__40:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3)) = 536870973;
  goto var_name_tmp__42;

var_name_tmp__41:
  var_name_tmp__17 = var_name_tmp__2;
  if ((((var_name_tmp__17 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897608)))&1))) {
    goto var_name_tmp__43;
  } else {
    goto var_name_tmp__44;
  }

var_name_tmp__43:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3)) = 536874816;
  goto var_name_tmp__45;

var_name_tmp__44:
  var_name_tmp__18 = var_name_tmp__2;
  if ((((var_name_tmp__18 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897632)))&1))) {
    goto var_name_tmp__46;
  } else {
    goto var_name_tmp__47;
  }

var_name_tmp__46:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3)) = 540868608;
  goto var_name_tmp__48;

var_name_tmp__47:
  var_name_tmp__19 = var_name_tmp__2;
  if ((((var_name_tmp__19 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073897656)))&1))) {
    goto var_name_tmp__49;
  } else {
    goto var_name_tmp__50;
  }

var_name_tmp__49:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472))->field3)) = 792723456;
  goto var_name_tmp__51;

var_name_tmp__50:
  var_name_tmp__20 = var_name_tmp__2;
  if ((((var_name_tmp__20 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512)))&1))) {
    goto var_name_tmp__52;
  } else {
    goto var_name_tmp__53;
  }

var_name_tmp__52:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2)) = 61;
  goto var_name_tmp__54;

var_name_tmp__53:
  var_name_tmp__21 = var_name_tmp__2;
  if ((((var_name_tmp__21 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898536)))&1))) {
    goto var_name_tmp__55;
  } else {
    goto var_name_tmp__56;
  }

var_name_tmp__55:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2)) = 3904;
  goto var_name_tmp__57;

var_name_tmp__56:
  var_name_tmp__22 = var_name_tmp__2;
  if ((((var_name_tmp__22 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898560)))&1))) {
    goto var_name_tmp__58;
  } else {
    goto var_name_tmp__59;
  }

var_name_tmp__58:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2)) = 3997696;
  goto var_name_tmp__60;

var_name_tmp__59:
  var_name_tmp__23 = var_name_tmp__2;
  if ((((var_name_tmp__23 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898584)))&1))) {
    goto var_name_tmp__61;
  } else {
    goto var_name_tmp__62;
  }

var_name_tmp__61:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field2)) = 255852544;
  goto var_name_tmp__63;

var_name_tmp__62:
  var_name_tmp__24 = var_name_tmp__2;
  if ((((var_name_tmp__24 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898608)))&1))) {
    goto var_name_tmp__64;
  } else {
    goto var_name_tmp__65;
  }

var_name_tmp__64:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3)) = 536870973;
  goto var_name_tmp__66;

var_name_tmp__65:
  var_name_tmp__25 = var_name_tmp__2;
  if ((((var_name_tmp__25 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898632)))&1))) {
    goto var_name_tmp__67;
  } else {
    goto var_name_tmp__68;
  }

var_name_tmp__67:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3)) = 536874816;
  goto var_name_tmp__69;

var_name_tmp__68:
  var_name_tmp__26 = var_name_tmp__2;
  if ((((var_name_tmp__26 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898656)))&1))) {
    goto var_name_tmp__70;
  } else {
    goto var_name_tmp__71;
  }

var_name_tmp__70:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3)) = 540868608;
  goto var_name_tmp__72;

var_name_tmp__71:
  var_name_tmp__27 = var_name_tmp__2;
  if ((((var_name_tmp__27 == ((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898680)))&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496))->field3)) = 792723456;
  goto var_name_tmp__74;

var_name_tmp__74:
  goto var_name_tmp__72;

var_name_tmp__72:
  goto var_name_tmp__69;

var_name_tmp__69:
  goto var_name_tmp__66;

var_name_tmp__66:
  goto var_name_tmp__63;

var_name_tmp__63:
  goto var_name_tmp__60;

var_name_tmp__60:
  goto var_name_tmp__57;

var_name_tmp__57:
  goto var_name_tmp__54;

var_name_tmp__54:
  goto var_name_tmp__51;

var_name_tmp__51:
  goto var_name_tmp__48;

var_name_tmp__48:
  goto var_name_tmp__45;

var_name_tmp__45:
  goto var_name_tmp__42;

var_name_tmp__42:
  goto var_name_tmp__39;

var_name_tmp__39:
  goto var_name_tmp__36;

var_name_tmp__36:
  goto var_name_tmp__33;

var_name_tmp__33:
  goto var_name_tmp__30;

var_name_tmp__30:
  return;
}


void DMA_Init(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__75, struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__76) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__77;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__78;    /* Address-exposed local */
  uint32_t var_name_tmp__79;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__80;
  uint32_t var_name_tmp__81;
  uint32_t var_name_tmp__82;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__83;
  uint32_t var_name_tmp__84;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__85;
  uint32_t var_name_tmp__86;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__87;
  uint32_t var_name_tmp__88;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__89;
  uint32_t var_name_tmp__90;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__91;
  uint32_t var_name_tmp__92;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__93;
  uint32_t var_name_tmp__94;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__95;
  uint32_t var_name_tmp__96;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__97;
  uint32_t var_name_tmp__98;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__99;
  uint32_t var_name_tmp__100;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__101;
  uint32_t var_name_tmp__102;
  uint32_t var_name_tmp__103;
  uint32_t var_name_tmp__104;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__105;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__106;
  uint32_t var_name_tmp__107;
  uint32_t var_name_tmp__108;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__109;
  uint32_t var_name_tmp__110;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__111;
  uint32_t var_name_tmp__112;
  uint32_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__115;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__116;
  uint32_t var_name_tmp__117;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__118;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__119;
  uint32_t var_name_tmp__120;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__121;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__122;
  uint32_t var_name_tmp__123;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__124;

  var_name_tmp__77 = var_name_tmp__75;
  var_name_tmp__78 = var_name_tmp__76;
  var_name_tmp__79 = 0;
  var_name_tmp__80 = var_name_tmp__77;
  var_name_tmp__81 = *(volatile uint32_t*)((&var_name_tmp__80->field0));
  var_name_tmp__79 = var_name_tmp__81;
  var_name_tmp__82 = var_name_tmp__79;
  var_name_tmp__79 = (var_name_tmp__82 & -266567617);
  var_name_tmp__83 = var_name_tmp__78;
  var_name_tmp__84 = *((&var_name_tmp__83->field0));
  var_name_tmp__85 = var_name_tmp__78;
  var_name_tmp__86 = *((&var_name_tmp__85->field3));
  var_name_tmp__87 = var_name_tmp__78;
  var_name_tmp__88 = *((&var_name_tmp__87->field5));
  var_name_tmp__89 = var_name_tmp__78;
  var_name_tmp__90 = *((&var_name_tmp__89->field6));
  var_name_tmp__91 = var_name_tmp__78;
  var_name_tmp__92 = *((&var_name_tmp__91->field7));
  var_name_tmp__93 = var_name_tmp__78;
  var_name_tmp__94 = *((&var_name_tmp__93->field8));
  var_name_tmp__95 = var_name_tmp__78;
  var_name_tmp__96 = *((&var_name_tmp__95->field9));
  var_name_tmp__97 = var_name_tmp__78;
  var_name_tmp__98 = *((&var_name_tmp__97->field10));
  var_name_tmp__99 = var_name_tmp__78;
  var_name_tmp__100 = *((&var_name_tmp__99->field13));
  var_name_tmp__101 = var_name_tmp__78;
  var_name_tmp__102 = *((&var_name_tmp__101->field14));
  var_name_tmp__103 = var_name_tmp__79;
  var_name_tmp__79 = (var_name_tmp__103 | (((((((((var_name_tmp__84 | var_name_tmp__86) | var_name_tmp__88) | var_name_tmp__90) | var_name_tmp__92) | var_name_tmp__94) | var_name_tmp__96) | var_name_tmp__98) | var_name_tmp__100) | var_name_tmp__102));
  var_name_tmp__104 = var_name_tmp__79;
  var_name_tmp__105 = var_name_tmp__77;
  *(volatile uint32_t*)((&var_name_tmp__105->field0)) = var_name_tmp__104;
  var_name_tmp__106 = var_name_tmp__77;
  var_name_tmp__107 = *(volatile uint32_t*)((&var_name_tmp__106->field5));
  var_name_tmp__79 = var_name_tmp__107;
  var_name_tmp__108 = var_name_tmp__79;
  var_name_tmp__79 = (var_name_tmp__108 & -8);
  var_name_tmp__109 = var_name_tmp__78;
  var_name_tmp__110 = *((&var_name_tmp__109->field11));
  var_name_tmp__111 = var_name_tmp__78;
  var_name_tmp__112 = *((&var_name_tmp__111->field12));
  var_name_tmp__113 = var_name_tmp__79;
  var_name_tmp__79 = (var_name_tmp__113 | (var_name_tmp__110 | var_name_tmp__112));
  var_name_tmp__114 = var_name_tmp__79;
  var_name_tmp__115 = var_name_tmp__77;
  *(volatile uint32_t*)((&var_name_tmp__115->field5)) = var_name_tmp__114;
  var_name_tmp__116 = var_name_tmp__78;
  var_name_tmp__117 = *((&var_name_tmp__116->field4));
  var_name_tmp__118 = var_name_tmp__77;
  *(volatile uint32_t*)((&var_name_tmp__118->field1)) = var_name_tmp__117;
  var_name_tmp__119 = var_name_tmp__78;
  var_name_tmp__120 = *((&var_name_tmp__119->field1));
  var_name_tmp__121 = var_name_tmp__77;
  *(volatile uint32_t*)((&var_name_tmp__121->field2)) = var_name_tmp__120;
  var_name_tmp__122 = var_name_tmp__78;
  var_name_tmp__123 = *((&var_name_tmp__122->field2));
  var_name_tmp__124 = var_name_tmp__77;
  *(volatile uint32_t*)((&var_name_tmp__124->field3)) = var_name_tmp__123;
}


void DMA_StructInit(struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__125) {
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__126;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__127;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__128;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__129;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__130;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__131;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__132;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__133;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__134;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__135;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__136;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__137;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__138;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__139;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__140;
  struct l_struct_struct_OC_DMA_InitTypeDef* var_name_tmp__141;

  var_name_tmp__126 = var_name_tmp__125;
  var_name_tmp__127 = var_name_tmp__126;
  *((&var_name_tmp__127->field0)) = 0;
  var_name_tmp__128 = var_name_tmp__126;
  *((&var_name_tmp__128->field1)) = 0;
  var_name_tmp__129 = var_name_tmp__126;
  *((&var_name_tmp__129->field2)) = 0;
  var_name_tmp__130 = var_name_tmp__126;
  *((&var_name_tmp__130->field3)) = 0;
  var_name_tmp__131 = var_name_tmp__126;
  *((&var_name_tmp__131->field4)) = 0;
  var_name_tmp__132 = var_name_tmp__126;
  *((&var_name_tmp__132->field5)) = 0;
  var_name_tmp__133 = var_name_tmp__126;
  *((&var_name_tmp__133->field6)) = 0;
  var_name_tmp__134 = var_name_tmp__126;
  *((&var_name_tmp__134->field7)) = 0;
  var_name_tmp__135 = var_name_tmp__126;
  *((&var_name_tmp__135->field8)) = 0;
  var_name_tmp__136 = var_name_tmp__126;
  *((&var_name_tmp__136->field9)) = 0;
  var_name_tmp__137 = var_name_tmp__126;
  *((&var_name_tmp__137->field10)) = 0;
  var_name_tmp__138 = var_name_tmp__126;
  *((&var_name_tmp__138->field11)) = 0;
  var_name_tmp__139 = var_name_tmp__126;
  *((&var_name_tmp__139->field12)) = 0;
  var_name_tmp__140 = var_name_tmp__126;
  *((&var_name_tmp__140->field13)) = 0;
  var_name_tmp__141 = var_name_tmp__126;
  *((&var_name_tmp__141->field14)) = 0;
}


void DMA_Cmd(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__142, uint32_t var_name_tmp__143) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__144;    /* Address-exposed local */
  uint32_t var_name_tmp__145;    /* Address-exposed local */
  uint32_t var_name_tmp__146;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__147;
  uint32_t* var_name_tmp__148;
  uint32_t var_name_tmp__149;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__150;
  uint32_t* var_name_tmp__151;
  uint32_t var_name_tmp__152;

  var_name_tmp__144 = var_name_tmp__142;
  var_name_tmp__145 = var_name_tmp__143;
  var_name_tmp__146 = var_name_tmp__145;
  if ((((var_name_tmp__146 != 0u)&1))) {
    goto var_name_tmp__153;
  } else {
    goto var_name_tmp__154;
  }

var_name_tmp__153:
  var_name_tmp__147 = var_name_tmp__144;
  var_name_tmp__148 = (&var_name_tmp__147->field0);
  var_name_tmp__149 = *(volatile uint32_t*)var_name_tmp__148;
  *(volatile uint32_t*)var_name_tmp__148 = (var_name_tmp__149 | 1);
  goto var_name_tmp__155;

var_name_tmp__154:
  var_name_tmp__150 = var_name_tmp__144;
  var_name_tmp__151 = (&var_name_tmp__150->field0);
  var_name_tmp__152 = *(volatile uint32_t*)var_name_tmp__151;
  *(volatile uint32_t*)var_name_tmp__151 = (var_name_tmp__152 & -2);
  goto var_name_tmp__155;

var_name_tmp__155:
  return;
}


void DMA_PeriphIncOffsetSizeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__156, uint32_t var_name_tmp__157) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__158;    /* Address-exposed local */
  uint32_t var_name_tmp__159;    /* Address-exposed local */
  uint32_t var_name_tmp__160;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__161;
  uint32_t* var_name_tmp__162;
  uint32_t var_name_tmp__163;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__164;
  uint32_t* var_name_tmp__165;
  uint32_t var_name_tmp__166;

  var_name_tmp__158 = var_name_tmp__156;
  var_name_tmp__159 = var_name_tmp__157;
  var_name_tmp__160 = var_name_tmp__159;
  if ((((var_name_tmp__160 != 0u)&1))) {
    goto var_name_tmp__167;
  } else {
    goto var_name_tmp__168;
  }

var_name_tmp__167:
  var_name_tmp__161 = var_name_tmp__158;
  var_name_tmp__162 = (&var_name_tmp__161->field0);
  var_name_tmp__163 = *(volatile uint32_t*)var_name_tmp__162;
  *(volatile uint32_t*)var_name_tmp__162 = (var_name_tmp__163 | 32768);
  goto var_name_tmp__169;

var_name_tmp__168:
  var_name_tmp__164 = var_name_tmp__158;
  var_name_tmp__165 = (&var_name_tmp__164->field0);
  var_name_tmp__166 = *(volatile uint32_t*)var_name_tmp__165;
  *(volatile uint32_t*)var_name_tmp__165 = (var_name_tmp__166 & -32769);
  goto var_name_tmp__169;

var_name_tmp__169:
  return;
}


void DMA_FlowControllerConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__170, uint32_t var_name_tmp__171) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__172;    /* Address-exposed local */
  uint32_t var_name_tmp__173;    /* Address-exposed local */
  uint32_t var_name_tmp__174;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__175;
  uint32_t* var_name_tmp__176;
  uint32_t var_name_tmp__177;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__178;
  uint32_t* var_name_tmp__179;
  uint32_t var_name_tmp__180;

  var_name_tmp__172 = var_name_tmp__170;
  var_name_tmp__173 = var_name_tmp__171;
  var_name_tmp__174 = var_name_tmp__173;
  if ((((var_name_tmp__174 != 0u)&1))) {
    goto var_name_tmp__181;
  } else {
    goto var_name_tmp__182;
  }

var_name_tmp__181:
  var_name_tmp__175 = var_name_tmp__172;
  var_name_tmp__176 = (&var_name_tmp__175->field0);
  var_name_tmp__177 = *(volatile uint32_t*)var_name_tmp__176;
  *(volatile uint32_t*)var_name_tmp__176 = (var_name_tmp__177 | 32);
  goto var_name_tmp__183;

var_name_tmp__182:
  var_name_tmp__178 = var_name_tmp__172;
  var_name_tmp__179 = (&var_name_tmp__178->field0);
  var_name_tmp__180 = *(volatile uint32_t*)var_name_tmp__179;
  *(volatile uint32_t*)var_name_tmp__179 = (var_name_tmp__180 & -33);
  goto var_name_tmp__183;

var_name_tmp__183:
  return;
}


void DMA_SetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__184, uint16_t var_name_tmp__185) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__186;    /* Address-exposed local */
  uint16_t var_name_tmp__187;    /* Address-exposed local */
  uint16_t var_name_tmp__188;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__189;

  var_name_tmp__186 = var_name_tmp__184;
  var_name_tmp__187 = var_name_tmp__185;
  var_name_tmp__188 = var_name_tmp__187;
  var_name_tmp__189 = var_name_tmp__186;
  *(volatile uint32_t*)((&var_name_tmp__189->field1)) = (((uint32_t)(uint16_t)var_name_tmp__188));
}


uint16_t DMA_GetCurrDataCounter(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__190) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__191;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__192;
  uint32_t var_name_tmp__193;

  var_name_tmp__191 = var_name_tmp__190;
  var_name_tmp__192 = var_name_tmp__191;
  var_name_tmp__193 = *(volatile uint32_t*)((&var_name_tmp__192->field1));
  return (((uint16_t)var_name_tmp__193));
}


void DMA_DoubleBufferModeConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__194, uint32_t var_name_tmp__195, uint32_t var_name_tmp__196) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__197;    /* Address-exposed local */
  uint32_t var_name_tmp__198;    /* Address-exposed local */
  uint32_t var_name_tmp__199;    /* Address-exposed local */
  uint32_t var_name_tmp__200;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__201;
  uint32_t* var_name_tmp__202;
  uint32_t var_name_tmp__203;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__204;
  uint32_t* var_name_tmp__205;
  uint32_t var_name_tmp__206;
  uint32_t var_name_tmp__207;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__208;

  var_name_tmp__197 = var_name_tmp__194;
  var_name_tmp__198 = var_name_tmp__195;
  var_name_tmp__199 = var_name_tmp__196;
  var_name_tmp__200 = var_name_tmp__199;
  if ((((var_name_tmp__200 != 0u)&1))) {
    goto var_name_tmp__209;
  } else {
    goto var_name_tmp__210;
  }

var_name_tmp__209:
  var_name_tmp__201 = var_name_tmp__197;
  var_name_tmp__202 = (&var_name_tmp__201->field0);
  var_name_tmp__203 = *(volatile uint32_t*)var_name_tmp__202;
  *(volatile uint32_t*)var_name_tmp__202 = (var_name_tmp__203 | 524288);
  goto var_name_tmp__211;

var_name_tmp__210:
  var_name_tmp__204 = var_name_tmp__197;
  var_name_tmp__205 = (&var_name_tmp__204->field0);
  var_name_tmp__206 = *(volatile uint32_t*)var_name_tmp__205;
  *(volatile uint32_t*)var_name_tmp__205 = (var_name_tmp__206 & -524289);
  goto var_name_tmp__211;

var_name_tmp__211:
  var_name_tmp__207 = var_name_tmp__198;
  var_name_tmp__208 = var_name_tmp__197;
  *(volatile uint32_t*)((&var_name_tmp__208->field4)) = var_name_tmp__207;
}


void DMA_DoubleBufferModeCmd(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__212, uint32_t var_name_tmp__213) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__214;    /* Address-exposed local */
  uint32_t var_name_tmp__215;    /* Address-exposed local */
  uint32_t var_name_tmp__216;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__217;
  uint32_t* var_name_tmp__218;
  uint32_t var_name_tmp__219;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__220;
  uint32_t* var_name_tmp__221;
  uint32_t var_name_tmp__222;

  var_name_tmp__214 = var_name_tmp__212;
  var_name_tmp__215 = var_name_tmp__213;
  var_name_tmp__216 = var_name_tmp__215;
  if ((((var_name_tmp__216 != 0u)&1))) {
    goto var_name_tmp__223;
  } else {
    goto var_name_tmp__224;
  }

var_name_tmp__223:
  var_name_tmp__217 = var_name_tmp__214;
  var_name_tmp__218 = (&var_name_tmp__217->field0);
  var_name_tmp__219 = *(volatile uint32_t*)var_name_tmp__218;
  *(volatile uint32_t*)var_name_tmp__218 = (var_name_tmp__219 | 262144);
  goto var_name_tmp__225;

var_name_tmp__224:
  var_name_tmp__220 = var_name_tmp__214;
  var_name_tmp__221 = (&var_name_tmp__220->field0);
  var_name_tmp__222 = *(volatile uint32_t*)var_name_tmp__221;
  *(volatile uint32_t*)var_name_tmp__221 = (var_name_tmp__222 & -262145);
  goto var_name_tmp__225;

var_name_tmp__225:
  return;
}


void DMA_MemoryTargetConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__226, uint32_t var_name_tmp__227, uint32_t var_name_tmp__228) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__229;    /* Address-exposed local */
  uint32_t var_name_tmp__230;    /* Address-exposed local */
  uint32_t var_name_tmp__231;    /* Address-exposed local */
  uint32_t var_name_tmp__232;
  uint32_t var_name_tmp__233;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__234;
  uint32_t var_name_tmp__235;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__236;

  var_name_tmp__229 = var_name_tmp__226;
  var_name_tmp__230 = var_name_tmp__227;
  var_name_tmp__231 = var_name_tmp__228;
  var_name_tmp__232 = var_name_tmp__231;
  if ((((var_name_tmp__232 != 0u)&1))) {
    goto var_name_tmp__237;
  } else {
    goto var_name_tmp__238;
  }

var_name_tmp__237:
  var_name_tmp__233 = var_name_tmp__230;
  var_name_tmp__234 = var_name_tmp__229;
  *(volatile uint32_t*)((&var_name_tmp__234->field4)) = var_name_tmp__233;
  goto var_name_tmp__239;

var_name_tmp__238:
  var_name_tmp__235 = var_name_tmp__230;
  var_name_tmp__236 = var_name_tmp__229;
  *(volatile uint32_t*)((&var_name_tmp__236->field3)) = var_name_tmp__235;
  goto var_name_tmp__239;

var_name_tmp__239:
  return;
}


uint32_t DMA_GetCurrentMemoryTarget(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__240) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__241;    /* Address-exposed local */
  uint32_t var_name_tmp__242;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__243;
  uint32_t var_name_tmp__244;
  uint32_t var_name_tmp__245;

  var_name_tmp__241 = var_name_tmp__240;
  var_name_tmp__242 = 0;
  var_name_tmp__243 = var_name_tmp__241;
  var_name_tmp__244 = *(volatile uint32_t*)((&var_name_tmp__243->field0));
  if (((((var_name_tmp__244 & 524288) != 0u)&1))) {
    goto var_name_tmp__246;
  } else {
    goto var_name_tmp__247;
  }

var_name_tmp__246:
  var_name_tmp__242 = 1;
  goto var_name_tmp__248;

var_name_tmp__247:
  var_name_tmp__242 = 0;
  goto var_name_tmp__248;

var_name_tmp__248:
  var_name_tmp__245 = var_name_tmp__242;
  return var_name_tmp__245;
}


uint32_t DMA_GetCmdStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__249) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__250;    /* Address-exposed local */
  uint32_t var_name_tmp__251;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__252;
  uint32_t var_name_tmp__253;
  uint32_t var_name_tmp__254;

  var_name_tmp__250 = var_name_tmp__249;
  var_name_tmp__251 = 0;
  var_name_tmp__252 = var_name_tmp__250;
  var_name_tmp__253 = *(volatile uint32_t*)((&var_name_tmp__252->field0));
  if (((((var_name_tmp__253 & 1) != 0u)&1))) {
    goto var_name_tmp__255;
  } else {
    goto var_name_tmp__256;
  }

var_name_tmp__255:
  var_name_tmp__251 = 1;
  goto var_name_tmp__257;

var_name_tmp__256:
  var_name_tmp__251 = 0;
  goto var_name_tmp__257;

var_name_tmp__257:
  var_name_tmp__254 = var_name_tmp__251;
  return var_name_tmp__254;
}


uint32_t DMA_GetFIFOStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__258) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__259;    /* Address-exposed local */
  uint32_t var_name_tmp__260;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint32_t var_name_tmp__263;

  var_name_tmp__259 = var_name_tmp__258;
  var_name_tmp__260 = 0;
  var_name_tmp__261 = var_name_tmp__259;
  var_name_tmp__262 = *(volatile uint32_t*)((&var_name_tmp__261->field5));
  var_name_tmp__260 = (var_name_tmp__262 & 56);
  var_name_tmp__263 = var_name_tmp__260;
  return var_name_tmp__263;
}


uint32_t DMA_GetFlagStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__264, uint32_t var_name_tmp__265) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__266;    /* Address-exposed local */
  uint32_t var_name_tmp__267;    /* Address-exposed local */
  uint32_t var_name_tmp__268;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__269;    /* Address-exposed local */
  uint32_t var_name_tmp__270;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__271;
  uint32_t var_name_tmp__272;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__273;
  uint32_t var_name_tmp__274;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__275;
  uint32_t var_name_tmp__276;
  uint32_t var_name_tmp__277;
  uint32_t var_name_tmp__278;
  uint32_t var_name_tmp__279;
  uint32_t var_name_tmp__280;

  var_name_tmp__266 = var_name_tmp__264;
  var_name_tmp__267 = var_name_tmp__265;
  var_name_tmp__268 = 0;
  var_name_tmp__270 = 0;
  var_name_tmp__271 = var_name_tmp__266;
  if ((((((uint64_t)var_name_tmp__271) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__281;
  } else {
    goto var_name_tmp__282;
  }

var_name_tmp__281:
  var_name_tmp__269 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__283;

var_name_tmp__282:
  var_name_tmp__269 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__283;

var_name_tmp__283:
  var_name_tmp__272 = var_name_tmp__267;
  if (((((var_name_tmp__272 & 536870912) != 0u)&1))) {
    goto var_name_tmp__284;
  } else {
    goto var_name_tmp__285;
  }

var_name_tmp__284:
  var_name_tmp__273 = var_name_tmp__269;
  var_name_tmp__274 = *(volatile uint32_t*)((&var_name_tmp__273->field1));
  var_name_tmp__270 = var_name_tmp__274;
  goto var_name_tmp__286;

var_name_tmp__285:
  var_name_tmp__275 = var_name_tmp__269;
  var_name_tmp__276 = *(volatile uint32_t*)((&var_name_tmp__275->field0));
  var_name_tmp__270 = var_name_tmp__276;
  goto var_name_tmp__286;

var_name_tmp__286:
  var_name_tmp__277 = var_name_tmp__270;
  var_name_tmp__270 = (var_name_tmp__277 & 259854205);
  var_name_tmp__278 = var_name_tmp__270;
  var_name_tmp__279 = var_name_tmp__267;
  if (((((var_name_tmp__278 & var_name_tmp__279) != 0u)&1))) {
    goto var_name_tmp__287;
  } else {
    goto var_name_tmp__288;
  }

var_name_tmp__287:
  var_name_tmp__268 = 1;
  goto var_name_tmp__289;

var_name_tmp__288:
  var_name_tmp__268 = 0;
  goto var_name_tmp__289;

var_name_tmp__289:
  var_name_tmp__280 = var_name_tmp__268;
  return var_name_tmp__280;
}


void DMA_ClearFlag(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__290, uint32_t var_name_tmp__291) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__292;    /* Address-exposed local */
  uint32_t var_name_tmp__293;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__294;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__295;
  uint32_t var_name_tmp__296;
  uint32_t var_name_tmp__297;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__298;
  uint32_t var_name_tmp__299;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__300;

  var_name_tmp__292 = var_name_tmp__290;
  var_name_tmp__293 = var_name_tmp__291;
  var_name_tmp__295 = var_name_tmp__292;
  if ((((((uint64_t)var_name_tmp__295) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__301;
  } else {
    goto var_name_tmp__302;
  }

var_name_tmp__301:
  var_name_tmp__294 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__303;

var_name_tmp__302:
  var_name_tmp__294 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__303;

var_name_tmp__303:
  var_name_tmp__296 = var_name_tmp__293;
  if (((((var_name_tmp__296 & 536870912) != 0u)&1))) {
    goto var_name_tmp__304;
  } else {
    goto var_name_tmp__305;
  }

var_name_tmp__304:
  var_name_tmp__297 = var_name_tmp__293;
  var_name_tmp__298 = var_name_tmp__294;
  *(volatile uint32_t*)((&var_name_tmp__298->field3)) = (var_name_tmp__297 & 259854205);
  goto var_name_tmp__306;

var_name_tmp__305:
  var_name_tmp__299 = var_name_tmp__293;
  var_name_tmp__300 = var_name_tmp__294;
  *(volatile uint32_t*)((&var_name_tmp__300->field2)) = (var_name_tmp__299 & 259854205);
  goto var_name_tmp__306;

var_name_tmp__306:
  return;
}


void DMA_ITConfig(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__307, uint32_t var_name_tmp__308, uint32_t var_name_tmp__309) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__310;    /* Address-exposed local */
  uint32_t var_name_tmp__311;    /* Address-exposed local */
  uint32_t var_name_tmp__312;    /* Address-exposed local */
  uint32_t var_name_tmp__313;
  uint32_t var_name_tmp__314;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__315;
  uint32_t* var_name_tmp__316;
  uint32_t var_name_tmp__317;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__318;
  uint32_t* var_name_tmp__319;
  uint32_t var_name_tmp__320;
  uint32_t var_name_tmp__321;
  uint32_t var_name_tmp__322;
  uint32_t var_name_tmp__323;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__324;
  uint32_t* var_name_tmp__325;
  uint32_t var_name_tmp__326;
  uint32_t var_name_tmp__327;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__328;
  uint32_t* var_name_tmp__329;
  uint32_t var_name_tmp__330;

  var_name_tmp__310 = var_name_tmp__307;
  var_name_tmp__311 = var_name_tmp__308;
  var_name_tmp__312 = var_name_tmp__309;
  var_name_tmp__313 = var_name_tmp__311;
  if (((((var_name_tmp__313 & 128) != 0u)&1))) {
    goto var_name_tmp__331;
  } else {
    goto var_name_tmp__332;
  }

var_name_tmp__331:
  var_name_tmp__314 = var_name_tmp__312;
  if ((((var_name_tmp__314 != 0u)&1))) {
    goto var_name_tmp__333;
  } else {
    goto var_name_tmp__334;
  }

var_name_tmp__333:
  var_name_tmp__315 = var_name_tmp__310;
  var_name_tmp__316 = (&var_name_tmp__315->field5);
  var_name_tmp__317 = *(volatile uint32_t*)var_name_tmp__316;
  *(volatile uint32_t*)var_name_tmp__316 = (var_name_tmp__317 | 128);
  goto var_name_tmp__335;

var_name_tmp__334:
  var_name_tmp__318 = var_name_tmp__310;
  var_name_tmp__319 = (&var_name_tmp__318->field5);
  var_name_tmp__320 = *(volatile uint32_t*)var_name_tmp__319;
  *(volatile uint32_t*)var_name_tmp__319 = (var_name_tmp__320 & -129);
  goto var_name_tmp__335;

var_name_tmp__335:
  goto var_name_tmp__332;

var_name_tmp__332:
  var_name_tmp__321 = var_name_tmp__311;
  if ((((var_name_tmp__321 != 128u)&1))) {
    goto var_name_tmp__336;
  } else {
    goto var_name_tmp__337;
  }

var_name_tmp__336:
  var_name_tmp__322 = var_name_tmp__312;
  if ((((var_name_tmp__322 != 0u)&1))) {
    goto var_name_tmp__338;
  } else {
    goto var_name_tmp__339;
  }

var_name_tmp__338:
  var_name_tmp__323 = var_name_tmp__311;
  var_name_tmp__324 = var_name_tmp__310;
  var_name_tmp__325 = (&var_name_tmp__324->field0);
  var_name_tmp__326 = *(volatile uint32_t*)var_name_tmp__325;
  *(volatile uint32_t*)var_name_tmp__325 = (var_name_tmp__326 | (var_name_tmp__323 & 30));
  goto var_name_tmp__340;

var_name_tmp__339:
  var_name_tmp__327 = var_name_tmp__311;
  var_name_tmp__328 = var_name_tmp__310;
  var_name_tmp__329 = (&var_name_tmp__328->field0);
  var_name_tmp__330 = *(volatile uint32_t*)var_name_tmp__329;
  *(volatile uint32_t*)var_name_tmp__329 = (var_name_tmp__330 & (~((var_name_tmp__327 & 30))));
  goto var_name_tmp__340;

var_name_tmp__340:
  goto var_name_tmp__337;

var_name_tmp__337:
  return;
}


uint32_t DMA_GetITStatus(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__341, uint32_t var_name_tmp__342) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__343;    /* Address-exposed local */
  uint32_t var_name_tmp__344;    /* Address-exposed local */
  uint32_t var_name_tmp__345;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__346;    /* Address-exposed local */
  uint32_t var_name_tmp__347;    /* Address-exposed local */
  uint32_t var_name_tmp__348;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__349;
  uint32_t var_name_tmp__350;
  uint32_t var_name_tmp__351;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__352;
  uint32_t var_name_tmp__353;
  uint32_t var_name_tmp__354;
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__355;
  uint32_t var_name_tmp__356;
  uint32_t var_name_tmp__357;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__358;
  uint32_t var_name_tmp__359;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__360;
  uint32_t var_name_tmp__361;
  uint32_t var_name_tmp__362;
  uint32_t var_name_tmp__363;
  uint32_t var_name_tmp__364;
  uint32_t var_name_tmp__365;
  uint32_t var_name_tmp__366;

  var_name_tmp__343 = var_name_tmp__341;
  var_name_tmp__344 = var_name_tmp__342;
  var_name_tmp__345 = 0;
  var_name_tmp__347 = 0;
  var_name_tmp__348 = 0;
  var_name_tmp__349 = var_name_tmp__343;
  if ((((((uint64_t)var_name_tmp__349) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__367;
  } else {
    goto var_name_tmp__368;
  }

var_name_tmp__367:
  var_name_tmp__346 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__369;

var_name_tmp__368:
  var_name_tmp__346 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__369;

var_name_tmp__369:
  var_name_tmp__350 = var_name_tmp__344;
  if (((((var_name_tmp__350 & 255594300) != 0u)&1))) {
    goto var_name_tmp__370;
  } else {
    goto var_name_tmp__371;
  }

var_name_tmp__370:
  var_name_tmp__351 = var_name_tmp__344;
  var_name_tmp__347 = ((llvm_lshr_u32(var_name_tmp__351, 11)) & 30);
  var_name_tmp__352 = var_name_tmp__343;
  var_name_tmp__353 = *(volatile uint32_t*)((&var_name_tmp__352->field0));
  var_name_tmp__354 = var_name_tmp__347;
  var_name_tmp__348 = (var_name_tmp__353 & var_name_tmp__354);
  goto var_name_tmp__372;

var_name_tmp__371:
  var_name_tmp__355 = var_name_tmp__343;
  var_name_tmp__356 = *(volatile uint32_t*)((&var_name_tmp__355->field5));
  var_name_tmp__348 = (var_name_tmp__356 & 128);
  goto var_name_tmp__372;

var_name_tmp__372:
  var_name_tmp__357 = var_name_tmp__344;
  if (((((var_name_tmp__357 & 536870912) != 0u)&1))) {
    goto var_name_tmp__373;
  } else {
    goto var_name_tmp__374;
  }

var_name_tmp__373:
  var_name_tmp__358 = var_name_tmp__346;
  var_name_tmp__359 = *(volatile uint32_t*)((&var_name_tmp__358->field1));
  var_name_tmp__347 = var_name_tmp__359;
  goto var_name_tmp__375;

var_name_tmp__374:
  var_name_tmp__360 = var_name_tmp__346;
  var_name_tmp__361 = *(volatile uint32_t*)((&var_name_tmp__360->field0));
  var_name_tmp__347 = var_name_tmp__361;
  goto var_name_tmp__375;

var_name_tmp__375:
  var_name_tmp__362 = var_name_tmp__347;
  var_name_tmp__347 = (var_name_tmp__362 & 259854205);
  var_name_tmp__363 = var_name_tmp__347;
  var_name_tmp__364 = var_name_tmp__344;
  if (((((var_name_tmp__363 & var_name_tmp__364) != 0u)&1))) {
    goto var_name_tmp__376;
  } else {
    goto var_name_tmp__377;
  }

var_name_tmp__376:
  var_name_tmp__365 = var_name_tmp__348;
  if ((((var_name_tmp__365 != 0u)&1))) {
    goto var_name_tmp__378;
  } else {
    goto var_name_tmp__377;
  }

var_name_tmp__378:
  var_name_tmp__345 = 1;
  goto var_name_tmp__379;

var_name_tmp__377:
  var_name_tmp__345 = 0;
  goto var_name_tmp__379;

var_name_tmp__379:
  var_name_tmp__366 = var_name_tmp__345;
  return var_name_tmp__366;
}


void DMA_ClearITPendingBit(struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__380, uint32_t var_name_tmp__381) {
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__382;    /* Address-exposed local */
  uint32_t var_name_tmp__383;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__384;    /* Address-exposed local */
  struct l_struct_struct_OC_DMA_Stream_TypeDef* var_name_tmp__385;
  uint32_t var_name_tmp__386;
  uint32_t var_name_tmp__387;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__388;
  uint32_t var_name_tmp__389;
  struct l_struct_struct_OC_DMA_TypeDef* var_name_tmp__390;

  var_name_tmp__382 = var_name_tmp__380;
  var_name_tmp__383 = var_name_tmp__381;
  var_name_tmp__385 = var_name_tmp__382;
  if ((((((uint64_t)var_name_tmp__385) < ((uint64_t)((struct l_struct_struct_OC_DMA_Stream_TypeDef*)(uintptr_t)UINT64_C(1073898512))))&1))) {
    goto var_name_tmp__391;
  } else {
    goto var_name_tmp__392;
  }

var_name_tmp__391:
  var_name_tmp__384 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073897472));
  goto var_name_tmp__393;

var_name_tmp__392:
  var_name_tmp__384 = ((struct l_struct_struct_OC_DMA_TypeDef*)(uintptr_t)UINT64_C(1073898496));
  goto var_name_tmp__393;

var_name_tmp__393:
  var_name_tmp__386 = var_name_tmp__383;
  if (((((var_name_tmp__386 & 536870912) != 0u)&1))) {
    goto var_name_tmp__394;
  } else {
    goto var_name_tmp__395;
  }

var_name_tmp__394:
  var_name_tmp__387 = var_name_tmp__383;
  var_name_tmp__388 = var_name_tmp__384;
  *(volatile uint32_t*)((&var_name_tmp__388->field3)) = (var_name_tmp__387 & 259854205);
  goto var_name_tmp__396;

var_name_tmp__395:
  var_name_tmp__389 = var_name_tmp__383;
  var_name_tmp__390 = var_name_tmp__384;
  *(volatile uint32_t*)((&var_name_tmp__390->field2)) = (var_name_tmp__389 & 259854205);
  goto var_name_tmp__396;

var_name_tmp__396:
  return;
}

