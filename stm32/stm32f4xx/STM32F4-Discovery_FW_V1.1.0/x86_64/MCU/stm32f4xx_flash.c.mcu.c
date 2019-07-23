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
struct l_struct_struct_OC_FLASH_TypeDef;

/* Function definitions */

/* Types Definitions */
struct l_struct_struct_OC_FLASH_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
};

/* Function Declarations */
void FLASH_SetLatency(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_PrefetchBufferCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_InstructionCacheCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_DataCacheCmd(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_InstructionCacheReset(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_DataCacheReset(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_Unlock(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_Lock(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_EraseSector(uint32_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_WaitForLastOperation(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_EraseAllSectors(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_ProgramDoubleWord(uint32_t, uint64_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_ProgramWord(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_ProgramHalfWord(uint32_t, uint16_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_ProgramByte(uint32_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_Unlock(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_Lock(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_WRPConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_RDPConfig(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_UserConfig(uint8_t, uint8_t, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_OB_BORConfig(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_OB_Launch(void) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t FLASH_OB_GetUser(void) __ATTRIBUTELIST__((noinline, nothrow));
uint16_t FLASH_OB_GetWRP(void) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_OB_GetRDP(void) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t FLASH_OB_GetBOR(void) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_ITConfig(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_GetFlagStatus(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void FLASH_ClearFlag(uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t FLASH_GetStatus(void) __ATTRIBUTELIST__((noinline, nothrow));


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void FLASH_SetLatency(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888256)) = (((uint8_t)var_name_tmp__3));
}


void FLASH_PrefetchBufferCmd(uint32_t var_name_tmp__4) {
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint32_t var_name_tmp__6;
  uint32_t var_name_tmp__7;
  uint32_t var_name_tmp__8;

  var_name_tmp__5 = var_name_tmp__4;
  var_name_tmp__6 = var_name_tmp__5;
  if ((((var_name_tmp__6 != 0u)&1))) {
    goto var_name_tmp__9;
  } else {
    goto var_name_tmp__10;
  }

var_name_tmp__9:
  var_name_tmp__7 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__7 | 256);
  goto var_name_tmp__11;

var_name_tmp__10:
  var_name_tmp__8 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__8 & -257);
  goto var_name_tmp__11;

var_name_tmp__11:
  return;
}


void FLASH_InstructionCacheCmd(uint32_t var_name_tmp__12) {
  uint32_t var_name_tmp__13;    /* Address-exposed local */
  uint32_t var_name_tmp__14;
  uint32_t var_name_tmp__15;
  uint32_t var_name_tmp__16;

  var_name_tmp__13 = var_name_tmp__12;
  var_name_tmp__14 = var_name_tmp__13;
  if ((((var_name_tmp__14 != 0u)&1))) {
    goto var_name_tmp__17;
  } else {
    goto var_name_tmp__18;
  }

var_name_tmp__17:
  var_name_tmp__15 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__15 | 512);
  goto var_name_tmp__19;

var_name_tmp__18:
  var_name_tmp__16 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__16 & -513);
  goto var_name_tmp__19;

var_name_tmp__19:
  return;
}


void FLASH_DataCacheCmd(uint32_t var_name_tmp__20) {
  uint32_t var_name_tmp__21;    /* Address-exposed local */
  uint32_t var_name_tmp__22;
  uint32_t var_name_tmp__23;
  uint32_t var_name_tmp__24;

  var_name_tmp__21 = var_name_tmp__20;
  var_name_tmp__22 = var_name_tmp__21;
  if ((((var_name_tmp__22 != 0u)&1))) {
    goto var_name_tmp__25;
  } else {
    goto var_name_tmp__26;
  }

var_name_tmp__25:
  var_name_tmp__23 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__23 | 1024);
  goto var_name_tmp__27;

var_name_tmp__26:
  var_name_tmp__24 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__24 & -1025);
  goto var_name_tmp__27;

var_name_tmp__27:
  return;
}


void FLASH_InstructionCacheReset(void) {
  uint32_t var_name_tmp__28;

  var_name_tmp__28 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__28 | 2048);
}


void FLASH_DataCacheReset(void) {
  uint32_t var_name_tmp__29;

  var_name_tmp__29 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field0)) = (var_name_tmp__29 | 4096);
}


void FLASH_Unlock(void) {
  uint32_t var_name_tmp__30;

  var_name_tmp__30 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  if (((((var_name_tmp__30 & 2147483648u) != 0u)&1))) {
    goto var_name_tmp__31;
  } else {
    goto var_name_tmp__32;
  }

var_name_tmp__31:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field1)) = 1164378403u;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field1)) = -839939669;
  goto var_name_tmp__32;

var_name_tmp__32:
  return;
}


void FLASH_Lock(void) {
  uint32_t var_name_tmp__33;

  var_name_tmp__33 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__33 | 2147483648u);
}


uint32_t FLASH_EraseSector(uint32_t var_name_tmp__34, uint8_t var_name_tmp__35) {
  uint32_t var_name_tmp__36;    /* Address-exposed local */
  uint8_t var_name_tmp__37;    /* Address-exposed local */
  uint32_t var_name_tmp__38;    /* Address-exposed local */
  uint32_t var_name_tmp__39;    /* Address-exposed local */
  uint8_t var_name_tmp__40;
  uint8_t var_name_tmp__41;
  uint8_t var_name_tmp__42;
  uint32_t var_name_tmp__43;
  uint32_t var_name_tmp__44;
  uint32_t var_name_tmp__45;
  uint32_t var_name_tmp__46;
  uint32_t var_name_tmp__47;
  uint32_t var_name_tmp__48;
  uint32_t var_name_tmp__49;
  uint32_t var_name_tmp__50;
  uint32_t var_name_tmp__51;
  uint32_t var_name_tmp__52;
  uint32_t var_name_tmp__53;
  uint32_t var_name_tmp__54;
  uint32_t var_name_tmp__55;

  var_name_tmp__36 = var_name_tmp__34;
  var_name_tmp__37 = var_name_tmp__35;
  var_name_tmp__38 = 0;
  var_name_tmp__39 = 8;
  var_name_tmp__40 = var_name_tmp__37;
  if (((((((uint32_t)(uint8_t)var_name_tmp__40)) == 0u)&1))) {
    goto var_name_tmp__56;
  } else {
    goto var_name_tmp__57;
  }

var_name_tmp__56:
  var_name_tmp__38 = 0;
  goto var_name_tmp__58;

var_name_tmp__57:
  var_name_tmp__41 = var_name_tmp__37;
  if (((((((uint32_t)(uint8_t)var_name_tmp__41)) == 1u)&1))) {
    goto var_name_tmp__59;
  } else {
    goto var_name_tmp__60;
  }

var_name_tmp__59:
  var_name_tmp__38 = 256;
  goto var_name_tmp__61;

var_name_tmp__60:
  var_name_tmp__42 = var_name_tmp__37;
  if (((((((uint32_t)(uint8_t)var_name_tmp__42)) == 2u)&1))) {
    goto var_name_tmp__62;
  } else {
    goto var_name_tmp__63;
  }

var_name_tmp__62:
  var_name_tmp__38 = 512;
  goto var_name_tmp__64;

var_name_tmp__63:
  var_name_tmp__38 = 768;
  goto var_name_tmp__64;

var_name_tmp__64:
  goto var_name_tmp__61;

var_name_tmp__61:
  goto var_name_tmp__58;

var_name_tmp__58:
  var_name_tmp__43 = FLASH_WaitForLastOperation();
  var_name_tmp__39 = var_name_tmp__43;
  var_name_tmp__44 = var_name_tmp__39;
  if ((((var_name_tmp__44 == 8u)&1))) {
    goto var_name_tmp__65;
  } else {
    goto var_name_tmp__66;
  }

var_name_tmp__65:
  var_name_tmp__45 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__45 & -769);
  var_name_tmp__46 = var_name_tmp__38;
  var_name_tmp__47 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__47 | var_name_tmp__46);
  var_name_tmp__48 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__48 & -249);
  var_name_tmp__49 = var_name_tmp__36;
  var_name_tmp__50 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__50 | (2 | var_name_tmp__49));
  var_name_tmp__51 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__51 | 65536);
  var_name_tmp__52 = FLASH_WaitForLastOperation();
  var_name_tmp__39 = var_name_tmp__52;
  var_name_tmp__53 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__53 & -3);
  var_name_tmp__54 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__54 & -249);
  goto var_name_tmp__66;

var_name_tmp__66:
  var_name_tmp__55 = var_name_tmp__39;
  return var_name_tmp__55;
}


uint32_t FLASH_WaitForLastOperation(void) {
  uint32_t var_name_tmp__67;    /* Address-exposed local */
  uint32_t var_name_tmp__68;
  uint32_t var_name_tmp__69;
  uint32_t var_name_tmp__70;
  uint32_t var_name_tmp__71;

  *(volatile uint32_t*)(&var_name_tmp__67) = 8;
  var_name_tmp__68 = FLASH_GetStatus();
  *(volatile uint32_t*)(&var_name_tmp__67) = var_name_tmp__68;
  goto var_name_tmp__72;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__72:
  var_name_tmp__69 = *(volatile uint32_t*)(&var_name_tmp__67);
  if ((((var_name_tmp__69 == 1u)&1))) {
    goto var_name_tmp__73;
  } else {
    goto var_name_tmp__74;
  }

var_name_tmp__73:
  var_name_tmp__70 = FLASH_GetStatus();
  *(volatile uint32_t*)(&var_name_tmp__67) = var_name_tmp__70;
  goto var_name_tmp__72;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__74:
  var_name_tmp__71 = *(volatile uint32_t*)(&var_name_tmp__67);
  return var_name_tmp__71;
}


uint32_t FLASH_EraseAllSectors(uint8_t var_name_tmp__75) {
  uint8_t var_name_tmp__76;    /* Address-exposed local */
  uint32_t var_name_tmp__77;    /* Address-exposed local */
  uint32_t var_name_tmp__78;    /* Address-exposed local */
  uint32_t var_name_tmp__79;
  uint8_t var_name_tmp__80;
  uint8_t var_name_tmp__81;
  uint8_t var_name_tmp__82;
  uint32_t var_name_tmp__83;
  uint32_t var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint32_t var_name_tmp__86;
  uint32_t var_name_tmp__87;
  uint32_t var_name_tmp__88;
  uint32_t var_name_tmp__89;
  uint32_t var_name_tmp__90;
  uint32_t var_name_tmp__91;

  var_name_tmp__76 = var_name_tmp__75;
  var_name_tmp__77 = 0;
  var_name_tmp__78 = 8;
  var_name_tmp__79 = FLASH_WaitForLastOperation();
  var_name_tmp__78 = var_name_tmp__79;
  var_name_tmp__80 = var_name_tmp__76;
  if (((((((uint32_t)(uint8_t)var_name_tmp__80)) == 0u)&1))) {
    goto var_name_tmp__92;
  } else {
    goto var_name_tmp__93;
  }

var_name_tmp__92:
  var_name_tmp__77 = 0;
  goto var_name_tmp__94;

var_name_tmp__93:
  var_name_tmp__81 = var_name_tmp__76;
  if (((((((uint32_t)(uint8_t)var_name_tmp__81)) == 1u)&1))) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__96;
  }

var_name_tmp__95:
  var_name_tmp__77 = 256;
  goto var_name_tmp__97;

var_name_tmp__96:
  var_name_tmp__82 = var_name_tmp__76;
  if (((((((uint32_t)(uint8_t)var_name_tmp__82)) == 2u)&1))) {
    goto var_name_tmp__98;
  } else {
    goto var_name_tmp__99;
  }

var_name_tmp__98:
  var_name_tmp__77 = 512;
  goto var_name_tmp__100;

var_name_tmp__99:
  var_name_tmp__77 = 768;
  goto var_name_tmp__100;

var_name_tmp__100:
  goto var_name_tmp__97;

var_name_tmp__97:
  goto var_name_tmp__94;

var_name_tmp__94:
  var_name_tmp__83 = var_name_tmp__78;
  if ((((var_name_tmp__83 == 8u)&1))) {
    goto var_name_tmp__101;
  } else {
    goto var_name_tmp__102;
  }

var_name_tmp__101:
  var_name_tmp__84 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__84 & -769);
  var_name_tmp__85 = var_name_tmp__77;
  var_name_tmp__86 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__86 | var_name_tmp__85);
  var_name_tmp__87 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__87 | 4);
  var_name_tmp__88 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__88 | 65536);
  var_name_tmp__89 = FLASH_WaitForLastOperation();
  var_name_tmp__78 = var_name_tmp__89;
  var_name_tmp__90 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__90 & -5);
  goto var_name_tmp__102;

var_name_tmp__102:
  var_name_tmp__91 = var_name_tmp__78;
  return var_name_tmp__91;
}


uint32_t FLASH_ProgramDoubleWord(uint32_t var_name_tmp__103, uint64_t var_name_tmp__104) {
  uint32_t var_name_tmp__105;    /* Address-exposed local */
  uint64_t var_name_tmp__106;    /* Address-exposed local */
  uint32_t var_name_tmp__107;    /* Address-exposed local */
  uint32_t var_name_tmp__108;
  uint32_t var_name_tmp__109;
  uint32_t var_name_tmp__110;
  uint32_t var_name_tmp__111;
  uint32_t var_name_tmp__112;
  uint64_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  uint32_t var_name_tmp__115;
  uint32_t var_name_tmp__116;
  uint32_t var_name_tmp__117;

  var_name_tmp__105 = var_name_tmp__103;
  var_name_tmp__106 = var_name_tmp__104;
  var_name_tmp__107 = 8;
  var_name_tmp__108 = FLASH_WaitForLastOperation();
  var_name_tmp__107 = var_name_tmp__108;
  var_name_tmp__109 = var_name_tmp__107;
  if ((((var_name_tmp__109 == 8u)&1))) {
    goto var_name_tmp__118;
  } else {
    goto var_name_tmp__119;
  }

var_name_tmp__118:
  var_name_tmp__110 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__110 & -769);
  var_name_tmp__111 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__111 | 768);
  var_name_tmp__112 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__112 | 1);
  var_name_tmp__113 = var_name_tmp__106;
  var_name_tmp__114 = var_name_tmp__105;
  *(volatile uint64_t*)(((uint64_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__114)))) = var_name_tmp__113;
  var_name_tmp__115 = FLASH_WaitForLastOperation();
  var_name_tmp__107 = var_name_tmp__115;
  var_name_tmp__116 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__116 & -2);
  goto var_name_tmp__119;

var_name_tmp__119:
  var_name_tmp__117 = var_name_tmp__107;
  return var_name_tmp__117;
}


uint32_t FLASH_ProgramWord(uint32_t var_name_tmp__120, uint32_t var_name_tmp__121) {
  uint32_t var_name_tmp__122;    /* Address-exposed local */
  uint32_t var_name_tmp__123;    /* Address-exposed local */
  uint32_t var_name_tmp__124;    /* Address-exposed local */
  uint32_t var_name_tmp__125;
  uint32_t var_name_tmp__126;
  uint32_t var_name_tmp__127;
  uint32_t var_name_tmp__128;
  uint32_t var_name_tmp__129;
  uint32_t var_name_tmp__130;
  uint32_t var_name_tmp__131;
  uint32_t var_name_tmp__132;
  uint32_t var_name_tmp__133;
  uint32_t var_name_tmp__134;

  var_name_tmp__122 = var_name_tmp__120;
  var_name_tmp__123 = var_name_tmp__121;
  var_name_tmp__124 = 8;
  var_name_tmp__125 = FLASH_WaitForLastOperation();
  var_name_tmp__124 = var_name_tmp__125;
  var_name_tmp__126 = var_name_tmp__124;
  if ((((var_name_tmp__126 == 8u)&1))) {
    goto var_name_tmp__135;
  } else {
    goto var_name_tmp__136;
  }

var_name_tmp__135:
  var_name_tmp__127 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__127 & -769);
  var_name_tmp__128 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__128 | 512);
  var_name_tmp__129 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__129 | 1);
  var_name_tmp__130 = var_name_tmp__123;
  var_name_tmp__131 = var_name_tmp__122;
  *(volatile uint32_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__131)))) = var_name_tmp__130;
  var_name_tmp__132 = FLASH_WaitForLastOperation();
  var_name_tmp__124 = var_name_tmp__132;
  var_name_tmp__133 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__133 & -2);
  goto var_name_tmp__136;

var_name_tmp__136:
  var_name_tmp__134 = var_name_tmp__124;
  return var_name_tmp__134;
}


uint32_t FLASH_ProgramHalfWord(uint32_t var_name_tmp__137, uint16_t var_name_tmp__138) {
  uint32_t var_name_tmp__139;    /* Address-exposed local */
  uint16_t var_name_tmp__140;    /* Address-exposed local */
  uint32_t var_name_tmp__141;    /* Address-exposed local */
  uint32_t var_name_tmp__142;
  uint32_t var_name_tmp__143;
  uint32_t var_name_tmp__144;
  uint32_t var_name_tmp__145;
  uint32_t var_name_tmp__146;
  uint16_t var_name_tmp__147;
  uint32_t var_name_tmp__148;
  uint32_t var_name_tmp__149;
  uint32_t var_name_tmp__150;
  uint32_t var_name_tmp__151;

  var_name_tmp__139 = var_name_tmp__137;
  var_name_tmp__140 = var_name_tmp__138;
  var_name_tmp__141 = 8;
  var_name_tmp__142 = FLASH_WaitForLastOperation();
  var_name_tmp__141 = var_name_tmp__142;
  var_name_tmp__143 = var_name_tmp__141;
  if ((((var_name_tmp__143 == 8u)&1))) {
    goto var_name_tmp__152;
  } else {
    goto var_name_tmp__153;
  }

var_name_tmp__152:
  var_name_tmp__144 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__144 & -769);
  var_name_tmp__145 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__145 | 256);
  var_name_tmp__146 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__146 | 1);
  var_name_tmp__147 = var_name_tmp__140;
  var_name_tmp__148 = var_name_tmp__139;
  *(volatile uint16_t*)(((uint16_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__148)))) = var_name_tmp__147;
  var_name_tmp__149 = FLASH_WaitForLastOperation();
  var_name_tmp__141 = var_name_tmp__149;
  var_name_tmp__150 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__150 & -2);
  goto var_name_tmp__153;

var_name_tmp__153:
  var_name_tmp__151 = var_name_tmp__141;
  return var_name_tmp__151;
}


uint32_t FLASH_ProgramByte(uint32_t var_name_tmp__154, uint8_t var_name_tmp__155) {
  uint32_t var_name_tmp__156;    /* Address-exposed local */
  uint8_t var_name_tmp__157;    /* Address-exposed local */
  uint32_t var_name_tmp__158;    /* Address-exposed local */
  uint32_t var_name_tmp__159;
  uint32_t var_name_tmp__160;
  uint32_t var_name_tmp__161;
  uint32_t var_name_tmp__162;
  uint32_t var_name_tmp__163;
  uint8_t var_name_tmp__164;
  uint32_t var_name_tmp__165;
  uint32_t var_name_tmp__166;
  uint32_t var_name_tmp__167;
  uint32_t var_name_tmp__168;

  var_name_tmp__156 = var_name_tmp__154;
  var_name_tmp__157 = var_name_tmp__155;
  var_name_tmp__158 = 8;
  var_name_tmp__159 = FLASH_WaitForLastOperation();
  var_name_tmp__158 = var_name_tmp__159;
  var_name_tmp__160 = var_name_tmp__158;
  if ((((var_name_tmp__160 == 8u)&1))) {
    goto var_name_tmp__169;
  } else {
    goto var_name_tmp__170;
  }

var_name_tmp__169:
  var_name_tmp__161 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__161 & -769);
  var_name_tmp__162 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = var_name_tmp__162;
  var_name_tmp__163 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__163 | 1);
  var_name_tmp__164 = var_name_tmp__157;
  var_name_tmp__165 = var_name_tmp__156;
  *(volatile uint8_t*)(((uint8_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__165)))) = var_name_tmp__164;
  var_name_tmp__166 = FLASH_WaitForLastOperation();
  var_name_tmp__158 = var_name_tmp__166;
  var_name_tmp__167 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__167 & -2);
  goto var_name_tmp__170;

var_name_tmp__170:
  var_name_tmp__168 = var_name_tmp__158;
  return var_name_tmp__168;
}


void FLASH_OB_Unlock(void) {
  uint32_t var_name_tmp__171;

  var_name_tmp__171 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5));
  if (((((var_name_tmp__171 & 1) != 0u)&1))) {
    goto var_name_tmp__172;
  } else {
    goto var_name_tmp__173;
  }

var_name_tmp__172:
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field2)) = 135866939;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field2)) = 1281191551u;
  goto var_name_tmp__173;

var_name_tmp__173:
  return;
}


void FLASH_OB_Lock(void) {
  uint32_t var_name_tmp__174;

  var_name_tmp__174 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5)) = (var_name_tmp__174 | 1);
}


void FLASH_OB_WRPConfig(uint32_t var_name_tmp__175, uint32_t var_name_tmp__176) {
  uint32_t var_name_tmp__177;    /* Address-exposed local */
  uint32_t var_name_tmp__178;    /* Address-exposed local */
  uint32_t var_name_tmp__179;    /* Address-exposed local */
  uint32_t var_name_tmp__180;
  uint32_t var_name_tmp__181;
  uint32_t var_name_tmp__182;
  uint32_t var_name_tmp__183;
  uint16_t var_name_tmp__184;
  uint32_t var_name_tmp__185;
  uint16_t var_name_tmp__186;

  var_name_tmp__177 = var_name_tmp__175;
  var_name_tmp__178 = var_name_tmp__176;
  var_name_tmp__179 = 8;
  var_name_tmp__180 = FLASH_WaitForLastOperation();
  var_name_tmp__179 = var_name_tmp__180;
  var_name_tmp__181 = var_name_tmp__179;
  if ((((var_name_tmp__181 == 8u)&1))) {
    goto var_name_tmp__187;
  } else {
    goto var_name_tmp__188;
  }

var_name_tmp__187:
  var_name_tmp__182 = var_name_tmp__178;
  if ((((var_name_tmp__182 != 0u)&1))) {
    goto var_name_tmp__189;
  } else {
    goto var_name_tmp__190;
  }

var_name_tmp__189:
  var_name_tmp__183 = var_name_tmp__177;
  var_name_tmp__184 = *(volatile uint16_t*)((uint16_t*)(uintptr_t)UINT64_C(1073888278));
  *(volatile uint16_t*)((uint16_t*)(uintptr_t)UINT64_C(1073888278)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__184)) & (~(var_name_tmp__183)))));
  goto var_name_tmp__191;

var_name_tmp__190:
  var_name_tmp__185 = var_name_tmp__177;
  var_name_tmp__186 = *(volatile uint16_t*)((uint16_t*)(uintptr_t)UINT64_C(1073888278));
  *(volatile uint16_t*)((uint16_t*)(uintptr_t)UINT64_C(1073888278)) = (((uint16_t)((((uint32_t)(uint16_t)var_name_tmp__186)) | (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__185)))))));
  goto var_name_tmp__191;

var_name_tmp__191:
  goto var_name_tmp__188;

var_name_tmp__188:
  return;
}


void FLASH_OB_RDPConfig(uint8_t var_name_tmp__192) {
  uint8_t var_name_tmp__193;    /* Address-exposed local */
  uint32_t var_name_tmp__194;    /* Address-exposed local */
  uint32_t var_name_tmp__195;
  uint32_t var_name_tmp__196;
  uint8_t var_name_tmp__197;

  var_name_tmp__193 = var_name_tmp__192;
  var_name_tmp__194 = 8;
  var_name_tmp__195 = FLASH_WaitForLastOperation();
  var_name_tmp__194 = var_name_tmp__195;
  var_name_tmp__196 = var_name_tmp__194;
  if ((((var_name_tmp__196 == 8u)&1))) {
    goto var_name_tmp__198;
  } else {
    goto var_name_tmp__199;
  }

var_name_tmp__198:
  var_name_tmp__197 = var_name_tmp__193;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888277)) = var_name_tmp__197;
  goto var_name_tmp__199;

var_name_tmp__199:
  return;
}


void FLASH_OB_UserConfig(uint8_t var_name_tmp__200, uint8_t var_name_tmp__201, uint8_t var_name_tmp__202) {
  uint8_t var_name_tmp__203;    /* Address-exposed local */
  uint8_t var_name_tmp__204;    /* Address-exposed local */
  uint8_t var_name_tmp__205;    /* Address-exposed local */
  uint8_t var_name_tmp__206;    /* Address-exposed local */
  uint32_t var_name_tmp__207;    /* Address-exposed local */
  uint32_t var_name_tmp__208;
  uint32_t var_name_tmp__209;
  uint8_t var_name_tmp__210;
  uint8_t var_name_tmp__211;
  uint8_t var_name_tmp__212;
  uint8_t var_name_tmp__213;
  uint8_t var_name_tmp__214;

  var_name_tmp__203 = var_name_tmp__200;
  var_name_tmp__204 = var_name_tmp__201;
  var_name_tmp__205 = var_name_tmp__202;
  var_name_tmp__206 = -1;
  var_name_tmp__207 = 8;
  var_name_tmp__208 = FLASH_WaitForLastOperation();
  var_name_tmp__207 = var_name_tmp__208;
  var_name_tmp__209 = var_name_tmp__207;
  if ((((var_name_tmp__209 == 8u)&1))) {
    goto var_name_tmp__215;
  } else {
    goto var_name_tmp__216;
  }

var_name_tmp__215:
  var_name_tmp__210 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276));
  var_name_tmp__206 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__210)) & 15)));
  var_name_tmp__211 = var_name_tmp__203;
  var_name_tmp__212 = var_name_tmp__205;
  var_name_tmp__213 = var_name_tmp__204;
  var_name_tmp__214 = var_name_tmp__206;
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__211)) | (((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__212)) | (((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__213)) | (((uint32_t)(uint8_t)var_name_tmp__214)))))))))))))));
  goto var_name_tmp__216;

var_name_tmp__216:
  return;
}


void FLASH_OB_BORConfig(uint8_t var_name_tmp__217) {
  uint8_t var_name_tmp__218;    /* Address-exposed local */
  uint8_t var_name_tmp__219;
  uint8_t var_name_tmp__220;
  uint8_t var_name_tmp__221;

  var_name_tmp__218 = var_name_tmp__217;
  var_name_tmp__219 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276));
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__219)) & -13)));
  var_name_tmp__220 = var_name_tmp__218;
  var_name_tmp__221 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276));
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__221)) | (((uint32_t)(uint8_t)var_name_tmp__220)))));
}


uint32_t FLASH_OB_Launch(void) {
  uint32_t var_name_tmp__222;    /* Address-exposed local */
  uint8_t var_name_tmp__223;
  uint32_t var_name_tmp__224;
  uint32_t var_name_tmp__225;

  var_name_tmp__222 = 8;
  var_name_tmp__223 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276));
  *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276)) = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__223)) | 2)));
  var_name_tmp__224 = FLASH_WaitForLastOperation();
  var_name_tmp__222 = var_name_tmp__224;
  var_name_tmp__225 = var_name_tmp__222;
  return var_name_tmp__225;
}


uint8_t FLASH_OB_GetUser(void) {
  uint32_t var_name_tmp__226;

  var_name_tmp__226 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5));
  return (((uint8_t)(llvm_lshr_u32(var_name_tmp__226, 5))));
}


uint16_t FLASH_OB_GetWRP(void) {
  uint16_t var_name_tmp__227;

  var_name_tmp__227 = *(volatile uint16_t*)((uint16_t*)(uintptr_t)UINT64_C(1073888278));
  return var_name_tmp__227;
}


uint32_t FLASH_OB_GetRDP(void) {
  uint32_t var_name_tmp__228;    /* Address-exposed local */
  uint8_t var_name_tmp__229;
  uint32_t var_name_tmp__230;

  var_name_tmp__228 = 0;
  var_name_tmp__229 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888277));
  if (((((((uint32_t)(uint8_t)var_name_tmp__229)) != 170u)&1))) {
    goto var_name_tmp__231;
  } else {
    goto var_name_tmp__232;
  }

var_name_tmp__231:
  var_name_tmp__228 = 1;
  goto var_name_tmp__233;

var_name_tmp__232:
  var_name_tmp__228 = 0;
  goto var_name_tmp__233;

var_name_tmp__233:
  var_name_tmp__230 = var_name_tmp__228;
  return var_name_tmp__230;
}


uint8_t FLASH_OB_GetBOR(void) {
  uint8_t var_name_tmp__234;

  var_name_tmp__234 = *(volatile uint8_t*)((uint8_t*)(uintptr_t)UINT64_C(1073888276));
  return (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__234)) & 12)));
}


void FLASH_ITConfig(uint32_t var_name_tmp__235, uint32_t var_name_tmp__236) {
  uint32_t var_name_tmp__237;    /* Address-exposed local */
  uint32_t var_name_tmp__238;    /* Address-exposed local */
  uint32_t var_name_tmp__239;
  uint32_t var_name_tmp__240;
  uint32_t var_name_tmp__241;
  uint32_t var_name_tmp__242;
  uint32_t var_name_tmp__243;

  var_name_tmp__237 = var_name_tmp__235;
  var_name_tmp__238 = var_name_tmp__236;
  var_name_tmp__239 = var_name_tmp__238;
  if ((((var_name_tmp__239 != 0u)&1))) {
    goto var_name_tmp__244;
  } else {
    goto var_name_tmp__245;
  }

var_name_tmp__244:
  var_name_tmp__240 = var_name_tmp__237;
  var_name_tmp__241 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__241 | var_name_tmp__240);
  goto var_name_tmp__246;

var_name_tmp__245:
  var_name_tmp__242 = var_name_tmp__237;
  var_name_tmp__243 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4)) = (var_name_tmp__243 & (~(var_name_tmp__242)));
  goto var_name_tmp__246;

var_name_tmp__246:
  return;
}


uint32_t FLASH_GetFlagStatus(uint32_t var_name_tmp__247) {
  uint32_t var_name_tmp__248;    /* Address-exposed local */
  uint32_t var_name_tmp__249;    /* Address-exposed local */
  uint32_t var_name_tmp__250;
  uint32_t var_name_tmp__251;
  uint32_t var_name_tmp__252;

  var_name_tmp__248 = var_name_tmp__247;
  var_name_tmp__249 = 0;
  var_name_tmp__250 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3));
  var_name_tmp__251 = var_name_tmp__248;
  if (((((var_name_tmp__250 & var_name_tmp__251) != 0u)&1))) {
    goto var_name_tmp__253;
  } else {
    goto var_name_tmp__254;
  }

var_name_tmp__253:
  var_name_tmp__249 = 1;
  goto var_name_tmp__255;

var_name_tmp__254:
  var_name_tmp__249 = 0;
  goto var_name_tmp__255;

var_name_tmp__255:
  var_name_tmp__252 = var_name_tmp__249;
  return var_name_tmp__252;
}


void FLASH_ClearFlag(uint32_t var_name_tmp__256) {
  uint32_t var_name_tmp__257;    /* Address-exposed local */
  uint32_t var_name_tmp__258;

  var_name_tmp__257 = var_name_tmp__256;
  var_name_tmp__258 = var_name_tmp__257;
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3)) = var_name_tmp__258;
}


uint32_t FLASH_GetStatus(void) {
  uint32_t var_name_tmp__259;    /* Address-exposed local */
  uint32_t var_name_tmp__260;
  uint32_t var_name_tmp__261;
  uint32_t var_name_tmp__262;
  uint32_t var_name_tmp__263;
  uint32_t var_name_tmp__264;

  var_name_tmp__259 = 8;
  var_name_tmp__260 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3));
  if (((((var_name_tmp__260 & 65536) == 65536u)&1))) {
    goto var_name_tmp__265;
  } else {
    goto var_name_tmp__266;
  }

var_name_tmp__265:
  var_name_tmp__259 = 1;
  goto var_name_tmp__267;

var_name_tmp__266:
  var_name_tmp__261 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3));
  if (((((var_name_tmp__261 & 16) != 0u)&1))) {
    goto var_name_tmp__268;
  } else {
    goto var_name_tmp__269;
  }

var_name_tmp__268:
  var_name_tmp__259 = 5;
  goto var_name_tmp__270;

var_name_tmp__269:
  var_name_tmp__262 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3));
  if (((((var_name_tmp__262 & 239) != 0u)&1))) {
    goto var_name_tmp__271;
  } else {
    goto var_name_tmp__272;
  }

var_name_tmp__271:
  var_name_tmp__259 = 6;
  goto var_name_tmp__273;

var_name_tmp__272:
  var_name_tmp__263 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3));
  if (((((var_name_tmp__263 & 2) != 0u)&1))) {
    goto var_name_tmp__274;
  } else {
    goto var_name_tmp__275;
  }

var_name_tmp__274:
  var_name_tmp__259 = 7;
  goto var_name_tmp__276;

var_name_tmp__275:
  var_name_tmp__259 = 8;
  goto var_name_tmp__276;

var_name_tmp__276:
  goto var_name_tmp__273;

var_name_tmp__273:
  goto var_name_tmp__270;

var_name_tmp__270:
  goto var_name_tmp__267;

var_name_tmp__267:
  var_name_tmp__264 = var_name_tmp__259;
  return var_name_tmp__264;
}

