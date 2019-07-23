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

void FLASH_SetLatency(uint32_t var_name_tmp__1) {
  uint32_t var_name_tmp__2;    /* Address-exposed local */
  uint32_t var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint8_t)(((uint8_t)var_name_tmp__3)))), 8, 1);
}


void FLASH_PrefetchBufferCmd(uint32_t var_name_tmp__4) {
  uint32_t var_name_tmp__5;    /* Address-exposed local */
  uint32_t var_name_tmp__6;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__5 = var_name_tmp__4;
  var_name_tmp__6 = var_name_tmp__5;
  if ((((var_name_tmp__6 != 0u)&1))) {
    goto var_name_tmp__7;
  } else {
    goto var_name_tmp__8;
  }

var_name_tmp__7:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 256))), 32, 4);
  goto var_name_tmp__9;

var_name_tmp__8:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -257))), 32, 4);
  goto var_name_tmp__9;

var_name_tmp__9:
  return;
}


void FLASH_InstructionCacheCmd(uint32_t var_name_tmp__10) {
  uint32_t var_name_tmp__11;    /* Address-exposed local */
  uint32_t var_name_tmp__12;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__11 = var_name_tmp__10;
  var_name_tmp__12 = var_name_tmp__11;
  if ((((var_name_tmp__12 != 0u)&1))) {
    goto var_name_tmp__13;
  } else {
    goto var_name_tmp__14;
  }

var_name_tmp__13:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 512))), 32, 4);
  goto var_name_tmp__15;

var_name_tmp__14:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -513))), 32, 4);
  goto var_name_tmp__15;

var_name_tmp__15:
  return;
}


void FLASH_DataCacheCmd(uint32_t var_name_tmp__16) {
  uint32_t var_name_tmp__17;    /* Address-exposed local */
  uint32_t var_name_tmp__18;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;

  var_name_tmp__17 = var_name_tmp__16;
  var_name_tmp__18 = var_name_tmp__17;
  if ((((var_name_tmp__18 != 0u)&1))) {
    goto var_name_tmp__19;
  } else {
    goto var_name_tmp__20;
  }

var_name_tmp__19:
  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1024))), 32, 4);
  goto var_name_tmp__21;

var_name_tmp__20:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -1025))), 32, 4);
  goto var_name_tmp__21;

var_name_tmp__21:
  return;
}


void FLASH_InstructionCacheReset(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 2048))), 32, 4);
}


void FLASH_DataCacheReset(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), 32, 4);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888256)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 4096))), 32, 4);
}


void FLASH_Unlock(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 2147483648u) != 0u)&1))) {
    goto var_name_tmp__22;
  } else {
    goto var_name_tmp__23;
  }

var_name_tmp__22:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field1))), UINT64_C(1164378403), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field1))), UINT64_C(3455027627), 32, 4);
  goto var_name_tmp__23;

var_name_tmp__23:
  return;
}


void FLASH_Lock(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 2147483648u))), 32, 4);
}


uint32_t FLASH_EraseSector(uint32_t var_name_tmp__24, uint8_t var_name_tmp__25) {
  uint32_t var_name_tmp__26;    /* Address-exposed local */
  uint8_t var_name_tmp__27;    /* Address-exposed local */
  uint32_t var_name_tmp__28;    /* Address-exposed local */
  uint32_t var_name_tmp__29;    /* Address-exposed local */
  uint8_t var_name_tmp__30;
  uint8_t var_name_tmp__31;
  uint8_t var_name_tmp__32;
  uint32_t var_name_tmp__33;
  uint32_t var_name_tmp__34;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__35;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__36;
  uint64_t var_name_load_i32_7;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__37;
  uint64_t var_name_load_i32_13;
  uint64_t var_name_load_i32_16;
  uint32_t var_name_tmp__38;

  var_name_tmp__26 = var_name_tmp__24;
  var_name_tmp__27 = var_name_tmp__25;
  var_name_tmp__28 = 0;
  var_name_tmp__29 = 8;
  var_name_tmp__30 = var_name_tmp__27;
  if (((((((uint32_t)(uint8_t)var_name_tmp__30)) == 0u)&1))) {
    goto var_name_tmp__39;
  } else {
    goto var_name_tmp__40;
  }

var_name_tmp__39:
  var_name_tmp__28 = 0;
  goto var_name_tmp__41;

var_name_tmp__40:
  var_name_tmp__31 = var_name_tmp__27;
  if (((((((uint32_t)(uint8_t)var_name_tmp__31)) == 1u)&1))) {
    goto var_name_tmp__42;
  } else {
    goto var_name_tmp__43;
  }

var_name_tmp__42:
  var_name_tmp__28 = 256;
  goto var_name_tmp__44;

var_name_tmp__43:
  var_name_tmp__32 = var_name_tmp__27;
  if (((((((uint32_t)(uint8_t)var_name_tmp__32)) == 2u)&1))) {
    goto var_name_tmp__45;
  } else {
    goto var_name_tmp__46;
  }

var_name_tmp__45:
  var_name_tmp__28 = 512;
  goto var_name_tmp__47;

var_name_tmp__46:
  var_name_tmp__28 = 768;
  goto var_name_tmp__47;

var_name_tmp__47:
  goto var_name_tmp__44;

var_name_tmp__44:
  goto var_name_tmp__41;

var_name_tmp__41:
  var_name_tmp__33 = FLASH_WaitForLastOperation();
  var_name_tmp__29 = var_name_tmp__33;
  var_name_tmp__34 = var_name_tmp__29;
  if ((((var_name_tmp__34 == 8u)&1))) {
    goto var_name_tmp__48;
  } else {
    goto var_name_tmp__49;
  }

var_name_tmp__48:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_tmp__35 = var_name_tmp__28;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__35))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) & -249))), 32, 4);
  var_name_tmp__36 = var_name_tmp__26;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) | (2 | var_name_tmp__36)))), 32, 4);
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_10)) | 65536))), 32, 4);
  var_name_tmp__37 = FLASH_WaitForLastOperation();
  var_name_tmp__29 = var_name_tmp__37;
  var_name_load_i32_13 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) & -3))), 32, 4);
  var_name_load_i32_16 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_16)) & -249))), 32, 4);
  goto var_name_tmp__49;

var_name_tmp__49:
  var_name_tmp__38 = var_name_tmp__29;
  return var_name_tmp__38;
}


uint32_t FLASH_WaitForLastOperation(void) {
  uint32_t var_name_tmp__50;    /* Address-exposed local */
  uint32_t var_name_tmp__51;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__52;
  uint64_t var_name_load_i32_6;

  __adin_store_((((uint8_t*)(&var_name_tmp__50))), UINT64_C(8), 32, 4);
  var_name_tmp__51 = FLASH_GetStatus();
  __adin_store_((((uint8_t*)(&var_name_tmp__50))), (((uint64_t)(uint32_t)var_name_tmp__51)), 32, 4);
  goto var_name_tmp__53;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__53:
  var_name_load_i32_ = __adin_load_((((uint8_t*)(&var_name_tmp__50))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_)) == 1u)&1))) {
    goto var_name_tmp__54;
  } else {
    goto var_name_tmp__55;
  }

var_name_tmp__54:
  var_name_tmp__52 = FLASH_GetStatus();
  __adin_store_((((uint8_t*)(&var_name_tmp__50))), (((uint64_t)(uint32_t)var_name_tmp__52)), 32, 4);
  goto var_name_tmp__53;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__55:
  var_name_load_i32_6 = __adin_load_((((uint8_t*)(&var_name_tmp__50))), 32, 4);
  return (((uint32_t)var_name_load_i32_6));
}


uint32_t FLASH_EraseAllSectors(uint8_t var_name_tmp__56) {
  uint8_t var_name_tmp__57;    /* Address-exposed local */
  uint32_t var_name_tmp__58;    /* Address-exposed local */
  uint32_t var_name_tmp__59;    /* Address-exposed local */
  uint32_t var_name_tmp__60;
  uint8_t var_name_tmp__61;
  uint8_t var_name_tmp__62;
  uint8_t var_name_tmp__63;
  uint32_t var_name_tmp__64;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__65;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__66;
  uint64_t var_name_load_i32_10;
  uint32_t var_name_tmp__67;

  var_name_tmp__57 = var_name_tmp__56;
  var_name_tmp__58 = 0;
  var_name_tmp__59 = 8;
  var_name_tmp__60 = FLASH_WaitForLastOperation();
  var_name_tmp__59 = var_name_tmp__60;
  var_name_tmp__61 = var_name_tmp__57;
  if (((((((uint32_t)(uint8_t)var_name_tmp__61)) == 0u)&1))) {
    goto var_name_tmp__68;
  } else {
    goto var_name_tmp__69;
  }

var_name_tmp__68:
  var_name_tmp__58 = 0;
  goto var_name_tmp__70;

var_name_tmp__69:
  var_name_tmp__62 = var_name_tmp__57;
  if (((((((uint32_t)(uint8_t)var_name_tmp__62)) == 1u)&1))) {
    goto var_name_tmp__71;
  } else {
    goto var_name_tmp__72;
  }

var_name_tmp__71:
  var_name_tmp__58 = 256;
  goto var_name_tmp__73;

var_name_tmp__72:
  var_name_tmp__63 = var_name_tmp__57;
  if (((((((uint32_t)(uint8_t)var_name_tmp__63)) == 2u)&1))) {
    goto var_name_tmp__74;
  } else {
    goto var_name_tmp__75;
  }

var_name_tmp__74:
  var_name_tmp__58 = 512;
  goto var_name_tmp__76;

var_name_tmp__75:
  var_name_tmp__58 = 768;
  goto var_name_tmp__76;

var_name_tmp__76:
  goto var_name_tmp__73;

var_name_tmp__73:
  goto var_name_tmp__70;

var_name_tmp__70:
  var_name_tmp__64 = var_name_tmp__59;
  if ((((var_name_tmp__64 == 8u)&1))) {
    goto var_name_tmp__77;
  } else {
    goto var_name_tmp__78;
  }

var_name_tmp__77:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_tmp__65 = var_name_tmp__58;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | var_name_tmp__65))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | 4))), 32, 4);
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) | 65536))), 32, 4);
  var_name_tmp__66 = FLASH_WaitForLastOperation();
  var_name_tmp__59 = var_name_tmp__66;
  var_name_load_i32_10 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_10)) & -5))), 32, 4);
  goto var_name_tmp__78;

var_name_tmp__78:
  var_name_tmp__67 = var_name_tmp__59;
  return var_name_tmp__67;
}


uint32_t FLASH_ProgramDoubleWord(uint32_t var_name_tmp__79, uint64_t var_name_tmp__80) {
  uint32_t var_name_tmp__81;    /* Address-exposed local */
  uint64_t var_name_tmp__82;    /* Address-exposed local */
  uint32_t var_name_tmp__83;    /* Address-exposed local */
  uint32_t var_name_tmp__84;
  uint32_t var_name_tmp__85;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_tmp__86;
  uint32_t var_name_tmp__87;
  uint32_t var_name_tmp__88;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__89;

  var_name_tmp__81 = var_name_tmp__79;
  var_name_tmp__82 = var_name_tmp__80;
  var_name_tmp__83 = 8;
  var_name_tmp__84 = FLASH_WaitForLastOperation();
  var_name_tmp__83 = var_name_tmp__84;
  var_name_tmp__85 = var_name_tmp__83;
  if ((((var_name_tmp__85 == 8u)&1))) {
    goto var_name_tmp__90;
  } else {
    goto var_name_tmp__91;
  }

var_name_tmp__90:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 768))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | 1))), 32, 4);
  var_name_tmp__86 = var_name_tmp__82;
  var_name_tmp__87 = var_name_tmp__81;
  __adin_store_((((uint8_t*)(((uint64_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__87)))))), var_name_tmp__86, 64, 8);
  var_name_tmp__88 = FLASH_WaitForLastOperation();
  var_name_tmp__83 = var_name_tmp__88;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & -2))), 32, 4);
  goto var_name_tmp__91;

var_name_tmp__91:
  var_name_tmp__89 = var_name_tmp__83;
  return var_name_tmp__89;
}


uint32_t FLASH_ProgramWord(uint32_t var_name_tmp__92, uint32_t var_name_tmp__93) {
  uint32_t var_name_tmp__94;    /* Address-exposed local */
  uint32_t var_name_tmp__95;    /* Address-exposed local */
  uint32_t var_name_tmp__96;    /* Address-exposed local */
  uint32_t var_name_tmp__97;
  uint32_t var_name_tmp__98;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint32_t var_name_tmp__99;
  uint32_t var_name_tmp__100;
  uint32_t var_name_tmp__101;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__102;

  var_name_tmp__94 = var_name_tmp__92;
  var_name_tmp__95 = var_name_tmp__93;
  var_name_tmp__96 = 8;
  var_name_tmp__97 = FLASH_WaitForLastOperation();
  var_name_tmp__96 = var_name_tmp__97;
  var_name_tmp__98 = var_name_tmp__96;
  if ((((var_name_tmp__98 == 8u)&1))) {
    goto var_name_tmp__103;
  } else {
    goto var_name_tmp__104;
  }

var_name_tmp__103:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 512))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | 1))), 32, 4);
  var_name_tmp__99 = var_name_tmp__95;
  var_name_tmp__100 = var_name_tmp__94;
  __adin_store_((((uint8_t*)(((uint32_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__100)))))), (((uint64_t)(uint32_t)var_name_tmp__99)), 32, 4);
  var_name_tmp__101 = FLASH_WaitForLastOperation();
  var_name_tmp__96 = var_name_tmp__101;
  var_name_load_i32_8 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_8)) & -2))), 32, 4);
  goto var_name_tmp__104;

var_name_tmp__104:
  var_name_tmp__102 = var_name_tmp__96;
  return var_name_tmp__102;
}


uint32_t FLASH_ProgramHalfWord(uint32_t var_name_tmp__105, uint16_t var_name_tmp__106) {
  uint32_t var_name_tmp__107;    /* Address-exposed local */
  uint16_t var_name_tmp__108;    /* Address-exposed local */
  uint32_t var_name_tmp__109;    /* Address-exposed local */
  uint32_t var_name_tmp__110;
  uint32_t var_name_tmp__111;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint16_t var_name_tmp__112;
  uint32_t var_name_tmp__113;
  uint32_t var_name_tmp__114;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__115;

  var_name_tmp__107 = var_name_tmp__105;
  var_name_tmp__108 = var_name_tmp__106;
  var_name_tmp__109 = 8;
  var_name_tmp__110 = FLASH_WaitForLastOperation();
  var_name_tmp__109 = var_name_tmp__110;
  var_name_tmp__111 = var_name_tmp__109;
  if ((((var_name_tmp__111 == 8u)&1))) {
    goto var_name_tmp__116;
  } else {
    goto var_name_tmp__117;
  }

var_name_tmp__116:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) | 256))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | 1))), 32, 4);
  var_name_tmp__112 = var_name_tmp__108;
  var_name_tmp__113 = var_name_tmp__107;
  __adin_store_((((uint8_t*)(((uint16_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__113)))))), (((uint64_t)(uint16_t)var_name_tmp__112)), 16, 2);
  var_name_tmp__114 = FLASH_WaitForLastOperation();
  var_name_tmp__109 = var_name_tmp__114;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & -2))), 32, 4);
  goto var_name_tmp__117;

var_name_tmp__117:
  var_name_tmp__115 = var_name_tmp__109;
  return var_name_tmp__115;
}


uint32_t FLASH_ProgramByte(uint32_t var_name_tmp__118, uint8_t var_name_tmp__119) {
  uint32_t var_name_tmp__120;    /* Address-exposed local */
  uint8_t var_name_tmp__121;    /* Address-exposed local */
  uint32_t var_name_tmp__122;    /* Address-exposed local */
  uint32_t var_name_tmp__123;
  uint32_t var_name_tmp__124;
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_4;
  uint8_t var_name_tmp__125;
  uint32_t var_name_tmp__126;
  uint32_t var_name_tmp__127;
  uint64_t var_name_load_i32_7;
  uint32_t var_name_tmp__128;

  var_name_tmp__120 = var_name_tmp__118;
  var_name_tmp__121 = var_name_tmp__119;
  var_name_tmp__122 = 8;
  var_name_tmp__123 = FLASH_WaitForLastOperation();
  var_name_tmp__122 = var_name_tmp__123;
  var_name_tmp__124 = var_name_tmp__122;
  if ((((var_name_tmp__124 == 8u)&1))) {
    goto var_name_tmp__129;
  } else {
    goto var_name_tmp__130;
  }

var_name_tmp__129:
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -769))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)(((uint32_t)var_name_load_i32_1)))), 32, 4);
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | 1))), 32, 4);
  var_name_tmp__125 = var_name_tmp__121;
  var_name_tmp__126 = var_name_tmp__120;
  __adin_store_((((uint8_t*)(uintptr_t)(((uint64_t)(uint32_t)var_name_tmp__126)))), (((uint64_t)(uint8_t)var_name_tmp__125)), 8, 1);
  var_name_tmp__127 = FLASH_WaitForLastOperation();
  var_name_tmp__122 = var_name_tmp__127;
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & -2))), 32, 4);
  goto var_name_tmp__130;

var_name_tmp__130:
  var_name_tmp__128 = var_name_tmp__122;
  return var_name_tmp__128;
}


void FLASH_OB_Unlock(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 1) != 0u)&1))) {
    goto var_name_tmp__131;
  } else {
    goto var_name_tmp__132;
  }

var_name_tmp__131:
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field2))), UINT64_C(135866939), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field2))), UINT64_C(1281191551), 32, 4);
  goto var_name_tmp__132;

var_name_tmp__132:
  return;
}


void FLASH_OB_Lock(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
}


void FLASH_OB_WRPConfig(uint32_t var_name_tmp__133, uint32_t var_name_tmp__134) {
  uint32_t var_name_tmp__135;    /* Address-exposed local */
  uint32_t var_name_tmp__136;    /* Address-exposed local */
  uint32_t var_name_tmp__137;    /* Address-exposed local */
  uint32_t var_name_tmp__138;
  uint32_t var_name_tmp__139;
  uint32_t var_name_tmp__140;
  uint32_t var_name_tmp__141;
  uint64_t var_name_load_i16_;
  uint32_t var_name_tmp__142;
  uint64_t var_name_load_i16_1;

  var_name_tmp__135 = var_name_tmp__133;
  var_name_tmp__136 = var_name_tmp__134;
  var_name_tmp__137 = 8;
  var_name_tmp__138 = FLASH_WaitForLastOperation();
  var_name_tmp__137 = var_name_tmp__138;
  var_name_tmp__139 = var_name_tmp__137;
  if ((((var_name_tmp__139 == 8u)&1))) {
    goto var_name_tmp__143;
  } else {
    goto var_name_tmp__144;
  }

var_name_tmp__143:
  var_name_tmp__140 = var_name_tmp__136;
  if ((((var_name_tmp__140 != 0u)&1))) {
    goto var_name_tmp__145;
  } else {
    goto var_name_tmp__146;
  }

var_name_tmp__145:
  var_name_tmp__141 = var_name_tmp__135;
  var_name_load_i16_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888278)), 16, 2);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888278)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))) & (~(var_name_tmp__141))))))), 16, 2);
  goto var_name_tmp__147;

var_name_tmp__146:
  var_name_tmp__142 = var_name_tmp__135;
  var_name_load_i16_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888278)), 16, 2);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888278)), (((uint64_t)(uint16_t)(((uint16_t)((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_1)))) | (((uint32_t)(uint16_t)(((uint16_t)var_name_tmp__142))))))))), 16, 2);
  goto var_name_tmp__147;

var_name_tmp__147:
  goto var_name_tmp__144;

var_name_tmp__144:
  return;
}


void FLASH_OB_RDPConfig(uint8_t var_name_tmp__148) {
  uint8_t var_name_tmp__149;    /* Address-exposed local */
  uint32_t var_name_tmp__150;    /* Address-exposed local */
  uint32_t var_name_tmp__151;
  uint32_t var_name_tmp__152;
  uint8_t var_name_tmp__153;

  var_name_tmp__149 = var_name_tmp__148;
  var_name_tmp__150 = 8;
  var_name_tmp__151 = FLASH_WaitForLastOperation();
  var_name_tmp__150 = var_name_tmp__151;
  var_name_tmp__152 = var_name_tmp__150;
  if ((((var_name_tmp__152 == 8u)&1))) {
    goto var_name_tmp__154;
  } else {
    goto var_name_tmp__155;
  }

var_name_tmp__154:
  var_name_tmp__153 = var_name_tmp__149;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888277)), (((uint64_t)(uint8_t)var_name_tmp__153)), 8, 1);
  goto var_name_tmp__155;

var_name_tmp__155:
  return;
}


void FLASH_OB_UserConfig(uint8_t var_name_tmp__156, uint8_t var_name_tmp__157, uint8_t var_name_tmp__158) {
  uint8_t var_name_tmp__159;    /* Address-exposed local */
  uint8_t var_name_tmp__160;    /* Address-exposed local */
  uint8_t var_name_tmp__161;    /* Address-exposed local */
  uint8_t var_name_tmp__162;    /* Address-exposed local */
  uint32_t var_name_tmp__163;    /* Address-exposed local */
  uint32_t var_name_tmp__164;
  uint32_t var_name_tmp__165;
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__166;
  uint8_t var_name_tmp__167;
  uint8_t var_name_tmp__168;
  uint8_t var_name_tmp__169;

  var_name_tmp__159 = var_name_tmp__156;
  var_name_tmp__160 = var_name_tmp__157;
  var_name_tmp__161 = var_name_tmp__158;
  var_name_tmp__162 = -1;
  var_name_tmp__163 = 8;
  var_name_tmp__164 = FLASH_WaitForLastOperation();
  var_name_tmp__163 = var_name_tmp__164;
  var_name_tmp__165 = var_name_tmp__163;
  if ((((var_name_tmp__165 == 8u)&1))) {
    goto var_name_tmp__170;
  } else {
    goto var_name_tmp__171;
  }

var_name_tmp__170:
  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), 8, 1);
  var_name_tmp__162 = (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) & 15)));
  var_name_tmp__166 = var_name_tmp__159;
  var_name_tmp__167 = var_name_tmp__161;
  var_name_tmp__168 = var_name_tmp__160;
  var_name_tmp__169 = var_name_tmp__162;
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__166)) | (((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__167)) | (((uint32_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__168)) | (((uint32_t)(uint8_t)var_name_tmp__169))))))))))))))))), 8, 1);
  goto var_name_tmp__171;

var_name_tmp__171:
  return;
}


void FLASH_OB_BORConfig(uint8_t var_name_tmp__172) {
  uint8_t var_name_tmp__173;    /* Address-exposed local */
  uint64_t var_name_load_i8_;
  uint8_t var_name_tmp__174;
  uint64_t var_name_load_i8_1;

  var_name_tmp__173 = var_name_tmp__172;
  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) & -13))))), 8, 1);
  var_name_tmp__174 = var_name_tmp__173;
  var_name_load_i8_1 = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_1)))) | (((uint32_t)(uint8_t)var_name_tmp__174))))))), 8, 1);
}


uint32_t FLASH_OB_Launch(void) {
  uint32_t var_name_tmp__175;    /* Address-exposed local */
  uint64_t var_name_load_i8_;
  uint32_t var_name_tmp__176;
  uint32_t var_name_tmp__177;

  var_name_tmp__175 = 8;
  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), 8, 1);
  __adin_store_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) | 2))))), 8, 1);
  var_name_tmp__176 = FLASH_WaitForLastOperation();
  var_name_tmp__175 = var_name_tmp__176;
  var_name_tmp__177 = var_name_tmp__175;
  return var_name_tmp__177;
}


uint8_t FLASH_OB_GetUser(void) {
  uint64_t var_name_load_i32_;

  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field5))), 32, 4);
  return (((uint8_t)(llvm_lshr_u32((((uint32_t)var_name_load_i32_)), 5))));
}


uint16_t FLASH_OB_GetWRP(void) {
  uint64_t var_name_load_i16_;

  var_name_load_i16_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888278)), 16, 2);
  return (((uint16_t)var_name_load_i16_));
}


uint32_t FLASH_OB_GetRDP(void) {
  uint32_t var_name_tmp__178;    /* Address-exposed local */
  uint64_t var_name_load_i8_;
  uint32_t var_name_tmp__179;

  var_name_tmp__178 = 0;
  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888277)), 8, 1);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) != 170u)&1))) {
    goto var_name_tmp__180;
  } else {
    goto var_name_tmp__181;
  }

var_name_tmp__180:
  var_name_tmp__178 = 1;
  goto var_name_tmp__182;

var_name_tmp__181:
  var_name_tmp__178 = 0;
  goto var_name_tmp__182;

var_name_tmp__182:
  var_name_tmp__179 = var_name_tmp__178;
  return var_name_tmp__179;
}


uint8_t FLASH_OB_GetBOR(void) {
  uint64_t var_name_load_i8_;

  var_name_load_i8_ = __adin_load_(((uint8_t*)(uintptr_t)UINT64_C(1073888276)), 8, 1);
  return (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) & 12)));
}


void FLASH_ITConfig(uint32_t var_name_tmp__183, uint32_t var_name_tmp__184) {
  uint32_t var_name_tmp__185;    /* Address-exposed local */
  uint32_t var_name_tmp__186;    /* Address-exposed local */
  uint32_t var_name_tmp__187;
  uint32_t var_name_tmp__188;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__189;
  uint64_t var_name_load_i32_1;

  var_name_tmp__185 = var_name_tmp__183;
  var_name_tmp__186 = var_name_tmp__184;
  var_name_tmp__187 = var_name_tmp__186;
  if ((((var_name_tmp__187 != 0u)&1))) {
    goto var_name_tmp__190;
  } else {
    goto var_name_tmp__191;
  }

var_name_tmp__190:
  var_name_tmp__188 = var_name_tmp__185;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__188))), 32, 4);
  goto var_name_tmp__192;

var_name_tmp__191:
  var_name_tmp__189 = var_name_tmp__185;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field4))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__189))))), 32, 4);
  goto var_name_tmp__192;

var_name_tmp__192:
  return;
}


uint32_t FLASH_GetFlagStatus(uint32_t var_name_tmp__193) {
  uint32_t var_name_tmp__194;    /* Address-exposed local */
  uint32_t var_name_tmp__195;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__196;
  uint32_t var_name_tmp__197;

  var_name_tmp__194 = var_name_tmp__193;
  var_name_tmp__195 = 0;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), 32, 4);
  var_name_tmp__196 = var_name_tmp__194;
  if ((((((((uint32_t)var_name_load_i32_)) & var_name_tmp__196) != 0u)&1))) {
    goto var_name_tmp__198;
  } else {
    goto var_name_tmp__199;
  }

var_name_tmp__198:
  var_name_tmp__195 = 1;
  goto var_name_tmp__200;

var_name_tmp__199:
  var_name_tmp__195 = 0;
  goto var_name_tmp__200;

var_name_tmp__200:
  var_name_tmp__197 = var_name_tmp__195;
  return var_name_tmp__197;
}


void FLASH_ClearFlag(uint32_t var_name_tmp__201) {
  uint32_t var_name_tmp__202;    /* Address-exposed local */
  uint32_t var_name_tmp__203;

  var_name_tmp__202 = var_name_tmp__201;
  var_name_tmp__203 = var_name_tmp__202;
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), (((uint64_t)(uint32_t)var_name_tmp__203)), 32, 4);
}


uint32_t FLASH_GetStatus(void) {
  uint32_t var_name_tmp__204;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint64_t var_name_load_i32_3;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__205;

  var_name_tmp__204 = 8;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 65536) == 65536u)&1))) {
    goto var_name_tmp__206;
  } else {
    goto var_name_tmp__207;
  }

var_name_tmp__206:
  var_name_tmp__204 = 1;
  goto var_name_tmp__208;

var_name_tmp__207:
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_1)) & 16) != 0u)&1))) {
    goto var_name_tmp__209;
  } else {
    goto var_name_tmp__210;
  }

var_name_tmp__209:
  var_name_tmp__204 = 5;
  goto var_name_tmp__211;

var_name_tmp__210:
  var_name_load_i32_3 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 239) != 0u)&1))) {
    goto var_name_tmp__212;
  } else {
    goto var_name_tmp__213;
  }

var_name_tmp__212:
  var_name_tmp__204 = 6;
  goto var_name_tmp__214;

var_name_tmp__213:
  var_name_load_i32_5 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_FLASH_TypeDef*)(uintptr_t)UINT64_C(1073888256))->field3))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_5)) & 2) != 0u)&1))) {
    goto var_name_tmp__215;
  } else {
    goto var_name_tmp__216;
  }

var_name_tmp__215:
  var_name_tmp__204 = 7;
  goto var_name_tmp__217;

var_name_tmp__216:
  var_name_tmp__204 = 8;
  goto var_name_tmp__217;

var_name_tmp__217:
  goto var_name_tmp__214;

var_name_tmp__214:
  goto var_name_tmp__211;

var_name_tmp__211:
  goto var_name_tmp__208;

var_name_tmp__208:
  var_name_tmp__205 = var_name_tmp__204;
  return var_name_tmp__205;
}

