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
struct l_struct_struct_OC_CAN_TxMailBox_TypeDef;
struct l_struct_struct_OC_CAN_FIFOMailBox_TypeDef;
struct l_struct_struct_OC_CAN_FilterRegister_TypeDef;
struct l_struct_struct_OC_CAN_TypeDef;
struct l_struct_struct_OC_CAN_InitTypeDef;
struct l_struct_struct_OC_CAN_FilterInitTypeDef;
struct l_struct_struct_OC_CanTxMsg;
struct l_struct_struct_OC_CanRxMsg;

/* Function definitions */

/* Types Definitions */
struct l_array_88_uint32_t {
  uint32_t array[88];
};
struct l_struct_struct_OC_CAN_TxMailBox_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_array_3_struct_AC_l_struct_struct_OC_CAN_TxMailBox_TypeDef {
  struct l_struct_struct_OC_CAN_TxMailBox_TypeDef array[3];
};
struct l_struct_struct_OC_CAN_FIFOMailBox_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
};
struct l_array_2_struct_AC_l_struct_struct_OC_CAN_FIFOMailBox_TypeDef {
  struct l_struct_struct_OC_CAN_FIFOMailBox_TypeDef array[2];
};
struct l_array_12_uint32_t {
  uint32_t array[12];
};
struct l_array_8_uint32_t {
  uint32_t array[8];
};
struct l_struct_struct_OC_CAN_FilterRegister_TypeDef {
  uint32_t field0;
  uint32_t field1;
};
struct l_array_28_struct_AC_l_struct_struct_OC_CAN_FilterRegister_TypeDef {
  struct l_struct_struct_OC_CAN_FilterRegister_TypeDef array[28];
};
struct l_struct_struct_OC_CAN_TypeDef {
  uint32_t field0;
  uint32_t field1;
  uint32_t field2;
  uint32_t field3;
  uint32_t field4;
  uint32_t field5;
  uint32_t field6;
  uint32_t field7;
  struct l_array_88_uint32_t field8;
  struct l_array_3_struct_AC_l_struct_struct_OC_CAN_TxMailBox_TypeDef field9;
  struct l_array_2_struct_AC_l_struct_struct_OC_CAN_FIFOMailBox_TypeDef field10;
  struct l_array_12_uint32_t field11;
  uint32_t field12;
  uint32_t field13;
  uint32_t field14;
  uint32_t field15;
  uint32_t field16;
  uint32_t field17;
  uint32_t field18;
  uint32_t field19;
  struct l_array_8_uint32_t field20;
  struct l_array_28_struct_AC_l_struct_struct_OC_CAN_FilterRegister_TypeDef field21;
};
struct l_struct_struct_OC_CAN_InitTypeDef {
  uint16_t field0;
  uint8_t field1;
  uint8_t field2;
  uint8_t field3;
  uint8_t field4;
  uint32_t field5;
  uint32_t field6;
  uint32_t field7;
  uint32_t field8;
  uint32_t field9;
  uint32_t field10;
};
struct l_struct_struct_OC_CAN_FilterInitTypeDef {
  uint16_t field0;
  uint16_t field1;
  uint16_t field2;
  uint16_t field3;
  uint16_t field4;
  uint8_t field5;
  uint8_t field6;
  uint8_t field7;
  uint32_t field8;
};
struct l_array_8_uint8_t {
  uint8_t array[8];
};
struct l_struct_struct_OC_CanTxMsg {
  uint32_t field0;
  uint32_t field1;
  uint8_t field2;
  uint8_t field3;
  uint8_t field4;
  struct l_array_8_uint8_t field5;
};
struct l_struct_struct_OC_CanRxMsg {
  uint32_t field0;
  uint32_t field1;
  uint8_t field2;
  uint8_t field3;
  uint8_t field4;
  struct l_array_8_uint8_t field5;
  uint8_t field6;
};

/* Function Declarations */
void CAN_DeInit(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void RCC_APB1PeriphResetCmd(uint32_t, uint32_t);
uint8_t CAN_Init(struct l_struct_struct_OC_CAN_TypeDef*, struct l_struct_struct_OC_CAN_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_FilterInit(struct l_struct_struct_OC_CAN_FilterInitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_StructInit(struct l_struct_struct_OC_CAN_InitTypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_SlaveStartBank(uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_DBGFreeze(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_TTComModeCmd(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_Transmit(struct l_struct_struct_OC_CAN_TypeDef*, struct l_struct_struct_OC_CanTxMsg*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_TransmitStatus(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_CancelTransmit(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_Receive(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t, struct l_struct_struct_OC_CanRxMsg*) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_FIFORelease(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_MessagePending(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_OperatingModeRequest(struct l_struct_struct_OC_CAN_TypeDef*, uint8_t) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_Sleep(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_WakeUp(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_GetLastErrorCode(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_GetReceiveErrorCounter(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
uint8_t CAN_GetLSBTransmitErrorCounter(struct l_struct_struct_OC_CAN_TypeDef*) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_ITConfig(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CAN_GetFlagStatus(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_ClearFlag(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
uint32_t CAN_GetITStatus(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
static uint32_t CheckITStatus(uint32_t, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void CAN_ClearITPendingBit(struct l_struct_struct_OC_CAN_TypeDef*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow));
void __adin_store_(uint8_t*, uint64_t, uint32_t, uint32_t);
uint64_t __adin_load_(uint8_t*, uint32_t, uint32_t);
void __adin_memcpy_(uint8_t*, uint8_t*, uint32_t);
void __adin_memset_(uint8_t*, uint8_t, uint32_t);


/* REMCU Intrinsic Builtin Function Bodies */
static __forceinline uint32_t llvm_add_u32(uint32_t a, uint32_t b) {
  uint32_t r = a + b;
  return r;
}
static __forceinline uint32_t llvm_sub_u32(uint32_t a, uint32_t b) {
  uint32_t r = a - b;
  return r;
}
static __forceinline uint32_t llvm_lshr_u32(uint32_t a, uint32_t b) {
  uint32_t r = a >> b;
  return r;
}


/* Function Bodies */

void CAN_DeInit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__1) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__2;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__3;

  var_name_tmp__2 = var_name_tmp__1;
  var_name_tmp__3 = var_name_tmp__2;
  if ((((var_name_tmp__3 == ((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424)))&1))) {
    goto var_name_tmp__4;
  } else {
    goto var_name_tmp__5;
  }

var_name_tmp__4:
  RCC_APB1PeriphResetCmd(33554432, 1);
  RCC_APB1PeriphResetCmd(33554432, 0);
  goto var_name_tmp__6;

var_name_tmp__5:
  RCC_APB1PeriphResetCmd(67108864, 1);
  RCC_APB1PeriphResetCmd(67108864, 0);
  goto var_name_tmp__6;

var_name_tmp__6:
  return;
}


uint8_t CAN_Init(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__7, struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__8) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__9;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__10;    /* Address-exposed local */
  uint8_t var_name_tmp__11;    /* Address-exposed local */
  uint32_t var_name_tmp__12;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__13;
  uint32_t* var_name_tmp__14;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__15;
  uint32_t* var_name_tmp__16;
  uint64_t var_name_load_i32_3;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__17;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__18;
  bool var_name_tmp__19;
  bool var_name_tmp__19__PHI_TEMPORARY;
  uint32_t var_name_tmp__20;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__21;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__22;
  uint64_t var_name_load_i32_14;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__23;
  uint32_t* var_name_tmp__24;
  uint64_t var_name_load_i32_17;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__25;
  uint32_t* var_name_tmp__26;
  uint64_t var_name_load_i32_22;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__27;
  uint64_t var_name_load_i32_27;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__28;
  uint32_t* var_name_tmp__29;
  uint64_t var_name_load_i32_30;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__30;
  uint32_t* var_name_tmp__31;
  uint64_t var_name_load_i32_35;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__32;
  uint64_t var_name_load_i32_40;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__33;
  uint32_t* var_name_tmp__34;
  uint64_t var_name_load_i32_43;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__35;
  uint32_t* var_name_tmp__36;
  uint64_t var_name_load_i32_48;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__37;
  uint64_t var_name_load_i32_53;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__38;
  uint32_t* var_name_tmp__39;
  uint64_t var_name_load_i32_56;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__40;
  uint32_t* var_name_tmp__41;
  uint64_t var_name_load_i32_61;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__42;
  uint64_t var_name_load_i32_66;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__43;
  uint32_t* var_name_tmp__44;
  uint64_t var_name_load_i32_69;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__45;
  uint32_t* var_name_tmp__46;
  uint64_t var_name_load_i32_74;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__47;
  uint64_t var_name_load_i32_79;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__48;
  uint32_t* var_name_tmp__49;
  uint64_t var_name_load_i32_82;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__50;
  uint32_t* var_name_tmp__51;
  uint64_t var_name_load_i32_87;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__52;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__53;
  uint64_t var_name_load_i8_91;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__54;
  uint64_t var_name_load_i8_93;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__55;
  uint64_t var_name_load_i8_95;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__56;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__57;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__58;
  uint32_t* var_name_tmp__59;
  uint64_t var_name_load_i32_100;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__60;
  uint64_t var_name_load_i32_105;
  uint32_t var_name_tmp__61;
  bool var_name_tmp__62;
  bool var_name_tmp__62__PHI_TEMPORARY;
  uint32_t var_name_tmp__63;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__64;
  uint64_t var_name_load_i32_108;
  uint8_t var_name_tmp__65;

  var_name_tmp__9 = var_name_tmp__7;
  var_name_tmp__10 = var_name_tmp__8;
  var_name_tmp__11 = 0;
  var_name_tmp__12 = 0;
  var_name_tmp__13 = var_name_tmp__9;
  var_name_tmp__14 = (&var_name_tmp__13->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__14)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__14)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -3))), 32, 4);
  var_name_tmp__15 = var_name_tmp__9;
  var_name_tmp__16 = (&var_name_tmp__15->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__16)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__16)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | 1))), 32, 4);
  goto var_name_tmp__66;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__66:
  var_name_tmp__17 = var_name_tmp__9;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__17->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_8)) & 1) != 1u)&1))) {
    goto var_name_tmp__67;
  } else {
    var_name_tmp__19__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__68;
  }

var_name_tmp__67:
  var_name_tmp__18 = var_name_tmp__12;
  var_name_tmp__19__PHI_TEMPORARY = (((var_name_tmp__18 != 15u)&1));   /* for PHI node */
  goto var_name_tmp__68;

var_name_tmp__68:
  var_name_tmp__19 = ((var_name_tmp__19__PHI_TEMPORARY)&1);
  if (var_name_tmp__19) {
    goto var_name_tmp__69;
  } else {
    goto var_name_tmp__70;
  }

var_name_tmp__69:
  var_name_tmp__20 = var_name_tmp__12;
  var_name_tmp__12 = (llvm_add_u32(var_name_tmp__20, 1));
  goto var_name_tmp__66;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__70:
  var_name_tmp__21 = var_name_tmp__9;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__21->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_11)) & 1) != 1u)&1))) {
    goto var_name_tmp__71;
  } else {
    goto var_name_tmp__72;
  }

var_name_tmp__71:
  var_name_tmp__11 = 0;
  goto var_name_tmp__73;

var_name_tmp__72:
  var_name_tmp__22 = var_name_tmp__10;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__22->field5)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_14)) == 1u)&1))) {
    goto var_name_tmp__74;
  } else {
    goto var_name_tmp__75;
  }

var_name_tmp__74:
  var_name_tmp__23 = var_name_tmp__9;
  var_name_tmp__24 = (&var_name_tmp__23->field0);
  var_name_load_i32_17 = __adin_load_((((uint8_t*)var_name_tmp__24)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__24)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_17)) | 128))), 32, 4);
  goto var_name_tmp__76;

var_name_tmp__75:
  var_name_tmp__25 = var_name_tmp__9;
  var_name_tmp__26 = (&var_name_tmp__25->field0);
  var_name_load_i32_22 = __adin_load_((((uint8_t*)var_name_tmp__26)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__26)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_22)) & -129))), 32, 4);
  goto var_name_tmp__76;

var_name_tmp__76:
  var_name_tmp__27 = var_name_tmp__10;
  var_name_load_i32_27 = __adin_load_((((uint8_t*)((&var_name_tmp__27->field6)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_27)) == 1u)&1))) {
    goto var_name_tmp__77;
  } else {
    goto var_name_tmp__78;
  }

var_name_tmp__77:
  var_name_tmp__28 = var_name_tmp__9;
  var_name_tmp__29 = (&var_name_tmp__28->field0);
  var_name_load_i32_30 = __adin_load_((((uint8_t*)var_name_tmp__29)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__29)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_30)) | 64))), 32, 4);
  goto var_name_tmp__79;

var_name_tmp__78:
  var_name_tmp__30 = var_name_tmp__9;
  var_name_tmp__31 = (&var_name_tmp__30->field0);
  var_name_load_i32_35 = __adin_load_((((uint8_t*)var_name_tmp__31)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__31)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_35)) & -65))), 32, 4);
  goto var_name_tmp__79;

var_name_tmp__79:
  var_name_tmp__32 = var_name_tmp__10;
  var_name_load_i32_40 = __adin_load_((((uint8_t*)((&var_name_tmp__32->field7)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_40)) == 1u)&1))) {
    goto var_name_tmp__80;
  } else {
    goto var_name_tmp__81;
  }

var_name_tmp__80:
  var_name_tmp__33 = var_name_tmp__9;
  var_name_tmp__34 = (&var_name_tmp__33->field0);
  var_name_load_i32_43 = __adin_load_((((uint8_t*)var_name_tmp__34)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__34)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_43)) | 32))), 32, 4);
  goto var_name_tmp__82;

var_name_tmp__81:
  var_name_tmp__35 = var_name_tmp__9;
  var_name_tmp__36 = (&var_name_tmp__35->field0);
  var_name_load_i32_48 = __adin_load_((((uint8_t*)var_name_tmp__36)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__36)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_48)) & -33))), 32, 4);
  goto var_name_tmp__82;

var_name_tmp__82:
  var_name_tmp__37 = var_name_tmp__10;
  var_name_load_i32_53 = __adin_load_((((uint8_t*)((&var_name_tmp__37->field8)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_53)) == 1u)&1))) {
    goto var_name_tmp__83;
  } else {
    goto var_name_tmp__84;
  }

var_name_tmp__83:
  var_name_tmp__38 = var_name_tmp__9;
  var_name_tmp__39 = (&var_name_tmp__38->field0);
  var_name_load_i32_56 = __adin_load_((((uint8_t*)var_name_tmp__39)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__39)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_56)) | 16))), 32, 4);
  goto var_name_tmp__85;

var_name_tmp__84:
  var_name_tmp__40 = var_name_tmp__9;
  var_name_tmp__41 = (&var_name_tmp__40->field0);
  var_name_load_i32_61 = __adin_load_((((uint8_t*)var_name_tmp__41)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__41)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_61)) & -17))), 32, 4);
  goto var_name_tmp__85;

var_name_tmp__85:
  var_name_tmp__42 = var_name_tmp__10;
  var_name_load_i32_66 = __adin_load_((((uint8_t*)((&var_name_tmp__42->field9)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_66)) == 1u)&1))) {
    goto var_name_tmp__86;
  } else {
    goto var_name_tmp__87;
  }

var_name_tmp__86:
  var_name_tmp__43 = var_name_tmp__9;
  var_name_tmp__44 = (&var_name_tmp__43->field0);
  var_name_load_i32_69 = __adin_load_((((uint8_t*)var_name_tmp__44)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__44)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_69)) | 8))), 32, 4);
  goto var_name_tmp__88;

var_name_tmp__87:
  var_name_tmp__45 = var_name_tmp__9;
  var_name_tmp__46 = (&var_name_tmp__45->field0);
  var_name_load_i32_74 = __adin_load_((((uint8_t*)var_name_tmp__46)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__46)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_74)) & -9))), 32, 4);
  goto var_name_tmp__88;

var_name_tmp__88:
  var_name_tmp__47 = var_name_tmp__10;
  var_name_load_i32_79 = __adin_load_((((uint8_t*)((&var_name_tmp__47->field10)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_79)) == 1u)&1))) {
    goto var_name_tmp__89;
  } else {
    goto var_name_tmp__90;
  }

var_name_tmp__89:
  var_name_tmp__48 = var_name_tmp__9;
  var_name_tmp__49 = (&var_name_tmp__48->field0);
  var_name_load_i32_82 = __adin_load_((((uint8_t*)var_name_tmp__49)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__49)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_82)) | 4))), 32, 4);
  goto var_name_tmp__91;

var_name_tmp__90:
  var_name_tmp__50 = var_name_tmp__9;
  var_name_tmp__51 = (&var_name_tmp__50->field0);
  var_name_load_i32_87 = __adin_load_((((uint8_t*)var_name_tmp__51)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__51)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_87)) & -5))), 32, 4);
  goto var_name_tmp__91;

var_name_tmp__91:
  var_name_tmp__52 = var_name_tmp__10;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__52->field1)), 8, 2);
  var_name_tmp__53 = var_name_tmp__10;
  var_name_load_i8_91 = __adin_load_(((&var_name_tmp__53->field2)), 8, 1);
  var_name_tmp__54 = var_name_tmp__10;
  var_name_load_i8_93 = __adin_load_(((&var_name_tmp__54->field3)), 8, 4);
  var_name_tmp__55 = var_name_tmp__10;
  var_name_load_i8_95 = __adin_load_(((&var_name_tmp__55->field4)), 8, 1);
  var_name_tmp__56 = var_name_tmp__10;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__56->field0)))), 16, 4);
  var_name_tmp__57 = var_name_tmp__9;
  __adin_store_((((uint8_t*)((&var_name_tmp__57->field7)))), (((uint64_t)(uint32_t)((((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) << 30) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_91)))) << 24)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_93)))) << 16)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_95)))) << 20)) | (llvm_sub_u32((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_)))), 1))))), 32, 4);
  var_name_tmp__58 = var_name_tmp__9;
  var_name_tmp__59 = (&var_name_tmp__58->field0);
  var_name_load_i32_100 = __adin_load_((((uint8_t*)var_name_tmp__59)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__59)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_100)) & -2))), 32, 4);
  var_name_tmp__12 = 0;
  goto var_name_tmp__92;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__92:
  var_name_tmp__60 = var_name_tmp__9;
  var_name_load_i32_105 = __adin_load_((((uint8_t*)((&var_name_tmp__60->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_105)) & 1) == 1u)&1))) {
    goto var_name_tmp__93;
  } else {
    var_name_tmp__62__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__94;
  }

var_name_tmp__93:
  var_name_tmp__61 = var_name_tmp__12;
  var_name_tmp__62__PHI_TEMPORARY = (((var_name_tmp__61 != 15u)&1));   /* for PHI node */
  goto var_name_tmp__94;

var_name_tmp__94:
  var_name_tmp__62 = ((var_name_tmp__62__PHI_TEMPORARY)&1);
  if (var_name_tmp__62) {
    goto var_name_tmp__95;
  } else {
    goto var_name_tmp__96;
  }

var_name_tmp__95:
  var_name_tmp__63 = var_name_tmp__12;
  var_name_tmp__12 = (llvm_add_u32(var_name_tmp__63, 1));
  goto var_name_tmp__92;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__96:
  var_name_tmp__64 = var_name_tmp__9;
  var_name_load_i32_108 = __adin_load_((((uint8_t*)((&var_name_tmp__64->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_108)) & 1) == 1u)&1))) {
    goto var_name_tmp__97;
  } else {
    goto var_name_tmp__98;
  }

var_name_tmp__97:
  var_name_tmp__11 = 0;
  goto var_name_tmp__99;

var_name_tmp__98:
  var_name_tmp__11 = 1;
  goto var_name_tmp__99;

var_name_tmp__99:
  goto var_name_tmp__73;

var_name_tmp__73:
  var_name_tmp__65 = var_name_tmp__11;
  return var_name_tmp__65;
}


void CAN_FilterInit(struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__100) {
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__101;    /* Address-exposed local */
  uint32_t var_name_tmp__102;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__103;
  uint64_t var_name_load_i8_;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__104;
  uint64_t var_name_load_i32_1;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__105;
  uint64_t var_name_load_i8_4;
  uint32_t var_name_tmp__106;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__107;
  uint64_t var_name_load_i16_;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__108;
  uint64_t var_name_load_i16_10;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__109;
  uint64_t var_name_load_i8_12;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__110;
  uint64_t var_name_load_i16_16;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__111;
  uint64_t var_name_load_i16_19;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__112;
  uint64_t var_name_load_i8_21;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__113;
  uint64_t var_name_load_i8_25;
  uint32_t var_name_tmp__114;
  uint64_t var_name_load_i32_27;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__115;
  uint64_t var_name_load_i16_31;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__116;
  uint64_t var_name_load_i16_34;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__117;
  uint64_t var_name_load_i8_36;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__118;
  uint64_t var_name_load_i16_41;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__119;
  uint64_t var_name_load_i16_44;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__120;
  uint64_t var_name_load_i8_46;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__121;
  uint64_t var_name_load_i8_50;
  uint32_t var_name_tmp__122;
  uint64_t var_name_load_i32_52;
  uint32_t var_name_tmp__123;
  uint64_t var_name_load_i32_55;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__124;
  uint64_t var_name_load_i16_59;
  uint32_t var_name_tmp__125;
  uint64_t var_name_load_i32_61;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__126;
  uint64_t var_name_load_i16_65;
  uint32_t var_name_tmp__127;
  uint64_t var_name_load_i32_67;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__128;
  uint64_t var_name_load_i32_71;
  uint32_t var_name_tmp__129;
  uint64_t var_name_load_i32_73;
  uint64_t var_name_load_i32_76;

  var_name_tmp__101 = var_name_tmp__100;
  var_name_tmp__102 = 0;
  var_name_tmp__103 = var_name_tmp__101;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__103->field5)), 8, 2);
  var_name_tmp__102 = (1 << (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))));
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  var_name_tmp__104 = var_name_tmp__102;
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & (~(var_name_tmp__104))))), 32, 4);
  var_name_tmp__105 = var_name_tmp__101;
  var_name_load_i8_4 = __adin_load_(((&var_name_tmp__105->field7)), 8, 4);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_4)))) == 0u)&1))) {
    goto var_name_tmp__130;
  } else {
    goto var_name_tmp__131;
  }

var_name_tmp__130:
  var_name_tmp__106 = var_name_tmp__102;
  var_name_load_i32_6 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_6)) & (~(var_name_tmp__106))))), 32, 4);
  var_name_tmp__107 = var_name_tmp__101;
  var_name_load_i16_ = __adin_load_((((uint8_t*)((&var_name_tmp__107->field3)))), 16, 2);
  var_name_tmp__108 = var_name_tmp__101;
  var_name_load_i16_10 = __adin_load_((((uint8_t*)((&var_name_tmp__108->field1)))), 16, 2);
  var_name_tmp__109 = var_name_tmp__101;
  var_name_load_i8_12 = __adin_load_(((&var_name_tmp__109->field5)), 8, 2);
  __adin_store_((((uint8_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)(((uint8_t)var_name_load_i8_12)))))]))->field0)))), (((uint64_t)(uint32_t)(((65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_))))) << 16) | (65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_10)))))))), 32, 4);
  var_name_tmp__110 = var_name_tmp__101;
  var_name_load_i16_16 = __adin_load_((((uint8_t*)((&var_name_tmp__110->field2)))), 16, 4);
  var_name_tmp__111 = var_name_tmp__101;
  var_name_load_i16_19 = __adin_load_((((uint8_t*)((&var_name_tmp__111->field0)))), 16, 4);
  var_name_tmp__112 = var_name_tmp__101;
  var_name_load_i8_21 = __adin_load_(((&var_name_tmp__112->field5)), 8, 2);
  __adin_store_((((uint8_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)(((uint8_t)var_name_load_i8_21)))))]))->field1)))), (((uint64_t)(uint32_t)(((65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_16))))) << 16) | (65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_19)))))))), 32, 4);
  goto var_name_tmp__131;

var_name_tmp__131:
  var_name_tmp__113 = var_name_tmp__101;
  var_name_load_i8_25 = __adin_load_(((&var_name_tmp__113->field7)), 8, 4);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_25)))) == 1u)&1))) {
    goto var_name_tmp__132;
  } else {
    goto var_name_tmp__133;
  }

var_name_tmp__132:
  var_name_tmp__114 = var_name_tmp__102;
  var_name_load_i32_27 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_27)) | var_name_tmp__114))), 32, 4);
  var_name_tmp__115 = var_name_tmp__101;
  var_name_load_i16_31 = __adin_load_((((uint8_t*)((&var_name_tmp__115->field0)))), 16, 4);
  var_name_tmp__116 = var_name_tmp__101;
  var_name_load_i16_34 = __adin_load_((((uint8_t*)((&var_name_tmp__116->field1)))), 16, 2);
  var_name_tmp__117 = var_name_tmp__101;
  var_name_load_i8_36 = __adin_load_(((&var_name_tmp__117->field5)), 8, 2);
  __adin_store_((((uint8_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)(((uint8_t)var_name_load_i8_36)))))]))->field0)))), (((uint64_t)(uint32_t)(((65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_31))))) << 16) | (65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_34)))))))), 32, 4);
  var_name_tmp__118 = var_name_tmp__101;
  var_name_load_i16_41 = __adin_load_((((uint8_t*)((&var_name_tmp__118->field2)))), 16, 4);
  var_name_tmp__119 = var_name_tmp__101;
  var_name_load_i16_44 = __adin_load_((((uint8_t*)((&var_name_tmp__119->field3)))), 16, 2);
  var_name_tmp__120 = var_name_tmp__101;
  var_name_load_i8_46 = __adin_load_(((&var_name_tmp__120->field5)), 8, 2);
  __adin_store_((((uint8_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)(((uint8_t)var_name_load_i8_46)))))]))->field1)))), (((uint64_t)(uint32_t)(((65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_41))))) << 16) | (65535 & (((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_44)))))))), 32, 4);
  goto var_name_tmp__133;

var_name_tmp__133:
  var_name_tmp__121 = var_name_tmp__101;
  var_name_load_i8_50 = __adin_load_(((&var_name_tmp__121->field6)), 8, 1);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_50)))) == 0u)&1))) {
    goto var_name_tmp__134;
  } else {
    goto var_name_tmp__135;
  }

var_name_tmp__134:
  var_name_tmp__122 = var_name_tmp__102;
  var_name_load_i32_52 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_52)) & (~(var_name_tmp__122))))), 32, 4);
  goto var_name_tmp__136;

var_name_tmp__135:
  var_name_tmp__123 = var_name_tmp__102;
  var_name_load_i32_55 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_55)) | var_name_tmp__123))), 32, 4);
  goto var_name_tmp__136;

var_name_tmp__136:
  var_name_tmp__124 = var_name_tmp__101;
  var_name_load_i16_59 = __adin_load_((((uint8_t*)((&var_name_tmp__124->field4)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_59)))) == 0u)&1))) {
    goto var_name_tmp__137;
  } else {
    goto var_name_tmp__138;
  }

var_name_tmp__137:
  var_name_tmp__125 = var_name_tmp__102;
  var_name_load_i32_61 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_61)) & (~(var_name_tmp__125))))), 32, 4);
  goto var_name_tmp__138;

var_name_tmp__138:
  var_name_tmp__126 = var_name_tmp__101;
  var_name_load_i16_65 = __adin_load_((((uint8_t*)((&var_name_tmp__126->field4)))), 16, 4);
  if (((((((uint32_t)(uint16_t)(((uint16_t)var_name_load_i16_65)))) == 1u)&1))) {
    goto var_name_tmp__139;
  } else {
    goto var_name_tmp__140;
  }

var_name_tmp__139:
  var_name_tmp__127 = var_name_tmp__102;
  var_name_load_i32_67 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_67)) | var_name_tmp__127))), 32, 4);
  goto var_name_tmp__140;

var_name_tmp__140:
  var_name_tmp__128 = var_name_tmp__101;
  var_name_load_i32_71 = __adin_load_((((uint8_t*)((&var_name_tmp__128->field8)))), 32, 4);
  if (((((((uint32_t)var_name_load_i32_71)) == 1u)&1))) {
    goto var_name_tmp__141;
  } else {
    goto var_name_tmp__142;
  }

var_name_tmp__141:
  var_name_tmp__129 = var_name_tmp__102;
  var_name_load_i32_73 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_73)) | var_name_tmp__129))), 32, 4);
  goto var_name_tmp__142;

var_name_tmp__142:
  var_name_load_i32_76 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_76)) & -2))), 32, 4);
}


void CAN_StructInit(struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__143) {
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__144;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__145;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__146;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__147;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__148;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__149;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__150;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__151;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__152;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__153;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__154;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__155;

  var_name_tmp__144 = var_name_tmp__143;
  var_name_tmp__145 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__145->field5)))), UINT64_C(0), 32, 4);
  var_name_tmp__146 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__146->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__147 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__147->field7)))), UINT64_C(0), 32, 4);
  var_name_tmp__148 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__148->field8)))), UINT64_C(0), 32, 4);
  var_name_tmp__149 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__149->field9)))), UINT64_C(0), 32, 4);
  var_name_tmp__150 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__150->field10)))), UINT64_C(0), 32, 4);
  var_name_tmp__151 = var_name_tmp__144;
  __adin_store_(((&var_name_tmp__151->field1)), UINT64_C(0), 8, 2);
  var_name_tmp__152 = var_name_tmp__144;
  __adin_store_(((&var_name_tmp__152->field2)), UINT64_C(0), 8, 1);
  var_name_tmp__153 = var_name_tmp__144;
  __adin_store_(((&var_name_tmp__153->field3)), UINT64_C(3), 8, 4);
  var_name_tmp__154 = var_name_tmp__144;
  __adin_store_(((&var_name_tmp__154->field4)), UINT64_C(2), 8, 1);
  var_name_tmp__155 = var_name_tmp__144;
  __adin_store_((((uint8_t*)((&var_name_tmp__155->field0)))), UINT64_C(1), 16, 4);
}


void CAN_SlaveStartBank(uint8_t var_name_tmp__156) {
  uint8_t var_name_tmp__157;    /* Address-exposed local */
  uint64_t var_name_load_i32_;
  uint64_t var_name_load_i32_1;
  uint8_t var_name_tmp__158;
  uint64_t var_name_load_i32_4;
  uint64_t var_name_load_i32_7;

  var_name_tmp__157 = var_name_tmp__156;
  var_name_load_i32_ = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 1))), 32, 4);
  var_name_load_i32_1 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_1)) & -16143))), 32, 4);
  var_name_tmp__158 = var_name_tmp__157;
  var_name_load_i32_4 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_4)) | ((((uint32_t)(uint8_t)var_name_tmp__158)) << 8)))), 32, 4);
  var_name_load_i32_7 = __adin_load_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), 32, 4);
  __adin_store_(((uint8_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12))), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_7)) & -2))), 32, 4);
}


void CAN_DBGFreeze(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__159, uint32_t var_name_tmp__160) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__161;    /* Address-exposed local */
  uint32_t var_name_tmp__162;    /* Address-exposed local */
  uint32_t var_name_tmp__163;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__164;
  uint32_t* var_name_tmp__165;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__166;
  uint32_t* var_name_tmp__167;
  uint64_t var_name_load_i32_3;

  var_name_tmp__161 = var_name_tmp__159;
  var_name_tmp__162 = var_name_tmp__160;
  var_name_tmp__163 = var_name_tmp__162;
  if ((((var_name_tmp__163 != 0u)&1))) {
    goto var_name_tmp__168;
  } else {
    goto var_name_tmp__169;
  }

var_name_tmp__168:
  var_name_tmp__164 = var_name_tmp__161;
  var_name_tmp__165 = (&var_name_tmp__164->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__165)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__165)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 65536))), 32, 4);
  goto var_name_tmp__170;

var_name_tmp__169:
  var_name_tmp__166 = var_name_tmp__161;
  var_name_tmp__167 = (&var_name_tmp__166->field0);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__167)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__167)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & -65537))), 32, 4);
  goto var_name_tmp__170;

var_name_tmp__170:
  return;
}


void CAN_TTComModeCmd(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__171, uint32_t var_name_tmp__172) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__173;    /* Address-exposed local */
  uint32_t var_name_tmp__174;    /* Address-exposed local */
  uint32_t var_name_tmp__175;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__176;
  uint32_t* var_name_tmp__177;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__178;
  uint32_t* var_name_tmp__179;
  uint64_t var_name_load_i32_3;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__180;
  uint32_t* var_name_tmp__181;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__182;
  uint32_t* var_name_tmp__183;
  uint64_t var_name_load_i32_13;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__184;
  uint32_t* var_name_tmp__185;
  uint64_t var_name_load_i32_18;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__186;
  uint32_t* var_name_tmp__187;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__188;
  uint32_t* var_name_tmp__189;
  uint64_t var_name_load_i32_28;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__190;
  uint32_t* var_name_tmp__191;
  uint64_t var_name_load_i32_33;

  var_name_tmp__173 = var_name_tmp__171;
  var_name_tmp__174 = var_name_tmp__172;
  var_name_tmp__175 = var_name_tmp__174;
  if ((((var_name_tmp__175 != 0u)&1))) {
    goto var_name_tmp__192;
  } else {
    goto var_name_tmp__193;
  }

var_name_tmp__192:
  var_name_tmp__176 = var_name_tmp__173;
  var_name_tmp__177 = (&var_name_tmp__176->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__177)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__177)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 128))), 32, 4);
  var_name_tmp__178 = var_name_tmp__173;
  var_name_tmp__179 = (&((&(*((&var_name_tmp__178->field9))).array[((int64_t)UINT64_C(0))]))->field1);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__179)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__179)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | 256))), 32, 4);
  var_name_tmp__180 = var_name_tmp__173;
  var_name_tmp__181 = (&((&(*((&var_name_tmp__180->field9))).array[((int64_t)UINT64_C(1))]))->field1);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)var_name_tmp__181)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__181)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_8)) | 256))), 32, 4);
  var_name_tmp__182 = var_name_tmp__173;
  var_name_tmp__183 = (&((&(*((&var_name_tmp__182->field9))).array[((int64_t)UINT64_C(2))]))->field1);
  var_name_load_i32_13 = __adin_load_((((uint8_t*)var_name_tmp__183)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__183)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_13)) | 256))), 32, 4);
  goto var_name_tmp__194;

var_name_tmp__193:
  var_name_tmp__184 = var_name_tmp__173;
  var_name_tmp__185 = (&var_name_tmp__184->field0);
  var_name_load_i32_18 = __adin_load_((((uint8_t*)var_name_tmp__185)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__185)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_18)) & -129))), 32, 4);
  var_name_tmp__186 = var_name_tmp__173;
  var_name_tmp__187 = (&((&(*((&var_name_tmp__186->field9))).array[((int64_t)UINT64_C(0))]))->field1);
  var_name_load_i32_23 = __adin_load_((((uint8_t*)var_name_tmp__187)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__187)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_23)) & -257))), 32, 4);
  var_name_tmp__188 = var_name_tmp__173;
  var_name_tmp__189 = (&((&(*((&var_name_tmp__188->field9))).array[((int64_t)UINT64_C(1))]))->field1);
  var_name_load_i32_28 = __adin_load_((((uint8_t*)var_name_tmp__189)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__189)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_28)) & -257))), 32, 4);
  var_name_tmp__190 = var_name_tmp__173;
  var_name_tmp__191 = (&((&(*((&var_name_tmp__190->field9))).array[((int64_t)UINT64_C(2))]))->field1);
  var_name_load_i32_33 = __adin_load_((((uint8_t*)var_name_tmp__191)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__191)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_33)) & -257))), 32, 4);
  goto var_name_tmp__194;

var_name_tmp__194:
  return;
}


uint8_t CAN_Transmit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__195, struct l_struct_struct_OC_CanTxMsg* var_name_tmp__196) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__197;    /* Address-exposed local */
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__198;    /* Address-exposed local */
  uint8_t var_name_tmp__199;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__200;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__201;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__202;
  uint64_t var_name_load_i32_5;
  uint8_t var_name_tmp__203;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__204;
  uint8_t var_name_tmp__205;
  uint32_t* var_name_tmp__206;
  uint64_t var_name_load_i32_8;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__207;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__208;
  uint64_t var_name_load_i32_12;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__209;
  uint64_t var_name_load_i8_14;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__210;
  uint8_t var_name_tmp__211;
  uint32_t* var_name_tmp__212;
  uint64_t var_name_load_i32_17;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__213;
  uint64_t var_name_load_i32_22;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__214;
  uint64_t var_name_load_i8_24;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__215;
  uint64_t var_name_load_i8_26;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__216;
  uint8_t var_name_tmp__217;
  uint32_t* var_name_tmp__218;
  uint64_t var_name_load_i32_29;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__219;
  uint8_t* var_name_tmp__220;
  uint64_t var_name_load_i8_33;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__221;
  uint8_t var_name_tmp__222;
  uint32_t* var_name_tmp__223;
  uint64_t var_name_load_i32_36;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__224;
  uint64_t var_name_load_i8_40;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__225;
  uint8_t var_name_tmp__226;
  uint32_t* var_name_tmp__227;
  uint64_t var_name_load_i32_43;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__228;
  uint64_t var_name_load_i8_47;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__229;
  uint64_t var_name_load_i8_49;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__230;
  uint64_t var_name_load_i8_51;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__231;
  uint64_t var_name_load_i8_53;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__232;
  uint8_t var_name_tmp__233;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__234;
  uint64_t var_name_load_i8_57;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__235;
  uint64_t var_name_load_i8_59;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__236;
  uint64_t var_name_load_i8_61;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__237;
  uint64_t var_name_load_i8_63;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__238;
  uint8_t var_name_tmp__239;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__240;
  uint8_t var_name_tmp__241;
  uint32_t* var_name_tmp__242;
  uint64_t var_name_load_i32_68;
  uint8_t var_name_tmp__243;

  var_name_tmp__197 = var_name_tmp__195;
  var_name_tmp__198 = var_name_tmp__196;
  var_name_tmp__199 = 0;
  var_name_tmp__200 = var_name_tmp__197;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__200->field2)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_)) & 67108864) == 67108864u)&1))) {
    goto var_name_tmp__244;
  } else {
    goto var_name_tmp__245;
  }

var_name_tmp__244:
  var_name_tmp__199 = 0;
  goto var_name_tmp__246;

var_name_tmp__245:
  var_name_tmp__201 = var_name_tmp__197;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__201->field2)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_2)) & 134217728) == 134217728u)&1))) {
    goto var_name_tmp__247;
  } else {
    goto var_name_tmp__248;
  }

var_name_tmp__247:
  var_name_tmp__199 = 1;
  goto var_name_tmp__249;

var_name_tmp__248:
  var_name_tmp__202 = var_name_tmp__197;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__202->field2)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_5)) & 268435456) == 268435456u)&1))) {
    goto var_name_tmp__250;
  } else {
    goto var_name_tmp__251;
  }

var_name_tmp__250:
  var_name_tmp__199 = 2;
  goto var_name_tmp__252;

var_name_tmp__251:
  var_name_tmp__199 = 4;
  goto var_name_tmp__252;

var_name_tmp__252:
  goto var_name_tmp__249;

var_name_tmp__249:
  goto var_name_tmp__246;

var_name_tmp__246:
  var_name_tmp__203 = var_name_tmp__199;
  if (((((((uint32_t)(uint8_t)var_name_tmp__203)) != 4u)&1))) {
    goto var_name_tmp__253;
  } else {
    goto var_name_tmp__254;
  }

var_name_tmp__253:
  var_name_tmp__204 = var_name_tmp__197;
  var_name_tmp__205 = var_name_tmp__199;
  var_name_tmp__206 = (&((&(*((&var_name_tmp__204->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__205)))]))->field0);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)var_name_tmp__206)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__206)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_8)) & 1))), 32, 4);
  var_name_tmp__207 = var_name_tmp__198;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__207->field2)), 8, 4);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) == 0u)&1))) {
    goto var_name_tmp__255;
  } else {
    goto var_name_tmp__256;
  }

var_name_tmp__255:
  var_name_tmp__208 = var_name_tmp__198;
  var_name_load_i32_12 = __adin_load_((((uint8_t*)((&var_name_tmp__208->field0)))), 32, 4);
  var_name_tmp__209 = var_name_tmp__198;
  var_name_load_i8_14 = __adin_load_(((&var_name_tmp__209->field3)), 8, 1);
  var_name_tmp__210 = var_name_tmp__197;
  var_name_tmp__211 = var_name_tmp__199;
  var_name_tmp__212 = (&((&(*((&var_name_tmp__210->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__211)))]))->field0);
  var_name_load_i32_17 = __adin_load_((((uint8_t*)var_name_tmp__212)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__212)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_17)) | (((((uint32_t)var_name_load_i32_12)) << 21) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_14)))))))), 32, 4);
  goto var_name_tmp__257;

var_name_tmp__256:
  var_name_tmp__213 = var_name_tmp__198;
  var_name_load_i32_22 = __adin_load_((((uint8_t*)((&var_name_tmp__213->field1)))), 32, 4);
  var_name_tmp__214 = var_name_tmp__198;
  var_name_load_i8_24 = __adin_load_(((&var_name_tmp__214->field2)), 8, 4);
  var_name_tmp__215 = var_name_tmp__198;
  var_name_load_i8_26 = __adin_load_(((&var_name_tmp__215->field3)), 8, 1);
  var_name_tmp__216 = var_name_tmp__197;
  var_name_tmp__217 = var_name_tmp__199;
  var_name_tmp__218 = (&((&(*((&var_name_tmp__216->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__217)))]))->field0);
  var_name_load_i32_29 = __adin_load_((((uint8_t*)var_name_tmp__218)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__218)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_29)) | ((((((uint32_t)var_name_load_i32_22)) << 3) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_24))))) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_26)))))))), 32, 4);
  goto var_name_tmp__257;

var_name_tmp__257:
  var_name_tmp__219 = var_name_tmp__198;
  var_name_tmp__220 = (&var_name_tmp__219->field4);
  var_name_load_i8_33 = __adin_load_(var_name_tmp__220, 8, 2);
  __adin_store_(var_name_tmp__220, (((uint64_t)(uint8_t)(((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_33)))) & 15))))), 8, 2);
  var_name_tmp__221 = var_name_tmp__197;
  var_name_tmp__222 = var_name_tmp__199;
  var_name_tmp__223 = (&((&(*((&var_name_tmp__221->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__222)))]))->field1);
  var_name_load_i32_36 = __adin_load_((((uint8_t*)var_name_tmp__223)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__223)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_36)) & -16))), 32, 4);
  var_name_tmp__224 = var_name_tmp__198;
  var_name_load_i8_40 = __adin_load_(((&var_name_tmp__224->field4)), 8, 2);
  var_name_tmp__225 = var_name_tmp__197;
  var_name_tmp__226 = var_name_tmp__199;
  var_name_tmp__227 = (&((&(*((&var_name_tmp__225->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__226)))]))->field1);
  var_name_load_i32_43 = __adin_load_((((uint8_t*)var_name_tmp__227)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__227)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_43)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_40))))))), 32, 4);
  var_name_tmp__228 = var_name_tmp__198;
  var_name_load_i8_47 = __adin_load_(((&(*((&var_name_tmp__228->field5))).array[((int64_t)UINT64_C(3))])), 8, 1);
  var_name_tmp__229 = var_name_tmp__198;
  var_name_load_i8_49 = __adin_load_(((&(*((&var_name_tmp__229->field5))).array[((int64_t)UINT64_C(2))])), 8, 1);
  var_name_tmp__230 = var_name_tmp__198;
  var_name_load_i8_51 = __adin_load_(((&(*((&var_name_tmp__230->field5))).array[((int64_t)UINT64_C(1))])), 8, 1);
  var_name_tmp__231 = var_name_tmp__198;
  var_name_load_i8_53 = __adin_load_(((&(*((&var_name_tmp__231->field5))).array[((int64_t)UINT64_C(0))])), 8, 1);
  var_name_tmp__232 = var_name_tmp__197;
  var_name_tmp__233 = var_name_tmp__199;
  __adin_store_((((uint8_t*)((&((&(*((&var_name_tmp__232->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__233)))]))->field2)))), (((uint64_t)(uint32_t)(((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_47)))) << 24) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_49)))) << 16)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_51)))) << 8)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_53))))))), 32, 4);
  var_name_tmp__234 = var_name_tmp__198;
  var_name_load_i8_57 = __adin_load_(((&(*((&var_name_tmp__234->field5))).array[((int64_t)UINT64_C(7))])), 8, 1);
  var_name_tmp__235 = var_name_tmp__198;
  var_name_load_i8_59 = __adin_load_(((&(*((&var_name_tmp__235->field5))).array[((int64_t)UINT64_C(6))])), 8, 1);
  var_name_tmp__236 = var_name_tmp__198;
  var_name_load_i8_61 = __adin_load_(((&(*((&var_name_tmp__236->field5))).array[((int64_t)UINT64_C(5))])), 8, 1);
  var_name_tmp__237 = var_name_tmp__198;
  var_name_load_i8_63 = __adin_load_(((&(*((&var_name_tmp__237->field5))).array[((int64_t)UINT64_C(4))])), 8, 1);
  var_name_tmp__238 = var_name_tmp__197;
  var_name_tmp__239 = var_name_tmp__199;
  __adin_store_((((uint8_t*)((&((&(*((&var_name_tmp__238->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__239)))]))->field3)))), (((uint64_t)(uint32_t)(((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_57)))) << 24) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_59)))) << 16)) | ((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_61)))) << 8)) | (((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_63))))))), 32, 4);
  var_name_tmp__240 = var_name_tmp__197;
  var_name_tmp__241 = var_name_tmp__199;
  var_name_tmp__242 = (&((&(*((&var_name_tmp__240->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__241)))]))->field0);
  var_name_load_i32_68 = __adin_load_((((uint8_t*)var_name_tmp__242)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__242)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_68)) | 1))), 32, 4);
  goto var_name_tmp__254;

var_name_tmp__254:
  var_name_tmp__243 = var_name_tmp__199;
  return var_name_tmp__243;
}


uint8_t CAN_TransmitStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__258, uint8_t var_name_tmp__259) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__260;    /* Address-exposed local */
  uint8_t var_name_tmp__261;    /* Address-exposed local */
  uint32_t var_name_tmp__262;    /* Address-exposed local */
  uint8_t var_name_tmp__263;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__264;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__265;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__266;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__267;
  uint32_t var_name_tmp__268;

  var_name_tmp__260 = var_name_tmp__258;
  var_name_tmp__261 = var_name_tmp__259;
  var_name_tmp__262 = 0;
  var_name_tmp__263 = var_name_tmp__261;
  switch ((((uint32_t)(uint8_t)var_name_tmp__263))) {
  default:
    goto var_name_tmp__269;
  case 0u:
    goto var_name_tmp__270;
  case 1u:
    goto var_name_tmp__271;
  case 2u:
    goto var_name_tmp__272;
  }

var_name_tmp__270:
  var_name_tmp__264 = var_name_tmp__260;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__264->field2)))), 32, 4);
  var_name_tmp__262 = ((((uint32_t)var_name_load_i32_)) & 67108867);
  goto var_name_tmp__273;

var_name_tmp__271:
  var_name_tmp__265 = var_name_tmp__260;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__265->field2)))), 32, 4);
  var_name_tmp__262 = ((((uint32_t)var_name_load_i32_2)) & 134218496);
  goto var_name_tmp__273;

var_name_tmp__272:
  var_name_tmp__266 = var_name_tmp__260;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__266->field2)))), 32, 4);
  var_name_tmp__262 = ((((uint32_t)var_name_load_i32_5)) & 268632064);
  goto var_name_tmp__273;

var_name_tmp__269:
  var_name_tmp__262 = 0;
  goto var_name_tmp__273;

var_name_tmp__273:
  var_name_tmp__267 = var_name_tmp__262;
  switch (var_name_tmp__267) {
  default:
    goto var_name_tmp__274;
  case 0u:
    goto var_name_tmp__275;
  case 67108865u:
    goto var_name_tmp__276;
  case 134217984u:
    goto var_name_tmp__277;
  case 268500992u:
    goto var_name_tmp__278;
  case 67108867u:
    goto var_name_tmp__279;
  case 134218496u:
    goto var_name_tmp__280;
  case 268632064u:
    goto var_name_tmp__281;
  }

var_name_tmp__275:
  var_name_tmp__262 = 2;
  goto var_name_tmp__282;

var_name_tmp__276:
  var_name_tmp__262 = 0;
  goto var_name_tmp__282;

var_name_tmp__277:
  var_name_tmp__262 = 0;
  goto var_name_tmp__282;

var_name_tmp__278:
  var_name_tmp__262 = 0;
  goto var_name_tmp__282;

var_name_tmp__279:
  var_name_tmp__262 = 1;
  goto var_name_tmp__282;

var_name_tmp__280:
  var_name_tmp__262 = 1;
  goto var_name_tmp__282;

var_name_tmp__281:
  var_name_tmp__262 = 1;
  goto var_name_tmp__282;

var_name_tmp__274:
  var_name_tmp__262 = 0;
  goto var_name_tmp__282;

var_name_tmp__282:
  var_name_tmp__268 = var_name_tmp__262;
  return (((uint8_t)var_name_tmp__268));
}


void CAN_CancelTransmit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__283, uint8_t var_name_tmp__284) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__285;    /* Address-exposed local */
  uint8_t var_name_tmp__286;    /* Address-exposed local */
  uint8_t var_name_tmp__287;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__288;
  uint32_t* var_name_tmp__289;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__290;
  uint32_t* var_name_tmp__291;
  uint64_t var_name_load_i32_3;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__292;
  uint32_t* var_name_tmp__293;
  uint64_t var_name_load_i32_8;

  var_name_tmp__285 = var_name_tmp__283;
  var_name_tmp__286 = var_name_tmp__284;
  var_name_tmp__287 = var_name_tmp__286;
  switch ((((uint32_t)(uint8_t)var_name_tmp__287))) {
  default:
    goto var_name_tmp__294;
  case 0u:
    goto var_name_tmp__295;
  case 1u:
    goto var_name_tmp__296;
  case 2u:
    goto var_name_tmp__297;
  }

var_name_tmp__295:
  var_name_tmp__288 = var_name_tmp__285;
  var_name_tmp__289 = (&var_name_tmp__288->field2);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__289)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__289)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 128))), 32, 4);
  goto var_name_tmp__298;

var_name_tmp__296:
  var_name_tmp__290 = var_name_tmp__285;
  var_name_tmp__291 = (&var_name_tmp__290->field2);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__291)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__291)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | 32768))), 32, 4);
  goto var_name_tmp__298;

var_name_tmp__297:
  var_name_tmp__292 = var_name_tmp__285;
  var_name_tmp__293 = (&var_name_tmp__292->field2);
  var_name_load_i32_8 = __adin_load_((((uint8_t*)var_name_tmp__293)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__293)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_8)) | 8388608))), 32, 4);
  goto var_name_tmp__298;

var_name_tmp__294:
  goto var_name_tmp__298;

var_name_tmp__298:
  return;
}


void CAN_Receive(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__299, uint8_t var_name_tmp__300, struct l_struct_struct_OC_CanRxMsg* var_name_tmp__301) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__302;    /* Address-exposed local */
  uint8_t var_name_tmp__303;    /* Address-exposed local */
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__304;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__305;
  uint8_t var_name_tmp__306;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__307;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__308;
  uint64_t var_name_load_i8_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__309;
  uint8_t var_name_tmp__310;
  uint64_t var_name_load_i32_2;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__311;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__312;
  uint8_t var_name_tmp__313;
  uint64_t var_name_load_i32_6;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__314;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__315;
  uint8_t var_name_tmp__316;
  uint64_t var_name_load_i32_11;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__317;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__318;
  uint8_t var_name_tmp__319;
  uint64_t var_name_load_i32_15;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__320;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__321;
  uint8_t var_name_tmp__322;
  uint64_t var_name_load_i32_19;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__323;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__324;
  uint8_t var_name_tmp__325;
  uint64_t var_name_load_i32_23;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__326;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__327;
  uint8_t var_name_tmp__328;
  uint64_t var_name_load_i32_27;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__329;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__330;
  uint8_t var_name_tmp__331;
  uint64_t var_name_load_i32_31;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__332;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__333;
  uint8_t var_name_tmp__334;
  uint64_t var_name_load_i32_35;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__335;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__336;
  uint8_t var_name_tmp__337;
  uint64_t var_name_load_i32_39;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__338;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__339;
  uint8_t var_name_tmp__340;
  uint64_t var_name_load_i32_43;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__341;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__342;
  uint8_t var_name_tmp__343;
  uint64_t var_name_load_i32_47;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__344;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__345;
  uint8_t var_name_tmp__346;
  uint64_t var_name_load_i32_51;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__347;
  uint8_t var_name_tmp__348;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__349;
  uint32_t* var_name_tmp__350;
  uint64_t var_name_load_i32_55;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__351;
  uint32_t* var_name_tmp__352;
  uint64_t var_name_load_i32_60;

  var_name_tmp__302 = var_name_tmp__299;
  var_name_tmp__303 = var_name_tmp__300;
  var_name_tmp__304 = var_name_tmp__301;
  var_name_tmp__305 = var_name_tmp__302;
  var_name_tmp__306 = var_name_tmp__303;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__305->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__306)))]))->field0)))), 32, 4);
  var_name_tmp__307 = var_name_tmp__304;
  __adin_store_(((&var_name_tmp__307->field2)), (((uint64_t)(uint8_t)(((uint8_t)(4 & (((uint32_t)var_name_load_i32_))))))), 8, 4);
  var_name_tmp__308 = var_name_tmp__304;
  var_name_load_i8_ = __adin_load_(((&var_name_tmp__308->field2)), 8, 4);
  if (((((((uint32_t)(uint8_t)(((uint8_t)var_name_load_i8_)))) == 0u)&1))) {
    goto var_name_tmp__353;
  } else {
    goto var_name_tmp__354;
  }

var_name_tmp__353:
  var_name_tmp__309 = var_name_tmp__302;
  var_name_tmp__310 = var_name_tmp__303;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__309->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__310)))]))->field0)))), 32, 4);
  var_name_tmp__311 = var_name_tmp__304;
  __adin_store_((((uint8_t*)((&var_name_tmp__311->field0)))), (((uint64_t)(uint32_t)(2047 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_2)), 21))))), 32, 4);
  goto var_name_tmp__355;

var_name_tmp__354:
  var_name_tmp__312 = var_name_tmp__302;
  var_name_tmp__313 = var_name_tmp__303;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__312->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__313)))]))->field0)))), 32, 4);
  var_name_tmp__314 = var_name_tmp__304;
  __adin_store_((((uint8_t*)((&var_name_tmp__314->field1)))), (((uint64_t)(uint32_t)(536870911 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_6)), 3))))), 32, 4);
  goto var_name_tmp__355;

var_name_tmp__355:
  var_name_tmp__315 = var_name_tmp__302;
  var_name_tmp__316 = var_name_tmp__303;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__315->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__316)))]))->field0)))), 32, 4);
  var_name_tmp__317 = var_name_tmp__304;
  __adin_store_(((&var_name_tmp__317->field3)), (((uint64_t)(uint8_t)(((uint8_t)(2 & (((uint32_t)var_name_load_i32_11))))))), 8, 1);
  var_name_tmp__318 = var_name_tmp__302;
  var_name_tmp__319 = var_name_tmp__303;
  var_name_load_i32_15 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__318->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__319)))]))->field1)))), 32, 4);
  var_name_tmp__320 = var_name_tmp__304;
  __adin_store_(((&var_name_tmp__320->field4)), (((uint64_t)(uint8_t)(((uint8_t)(15 & (((uint32_t)var_name_load_i32_15))))))), 8, 2);
  var_name_tmp__321 = var_name_tmp__302;
  var_name_tmp__322 = var_name_tmp__303;
  var_name_load_i32_19 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__321->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__322)))]))->field1)))), 32, 4);
  var_name_tmp__323 = var_name_tmp__304;
  __adin_store_(((&var_name_tmp__323->field6)), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_19)), 8))))))), 8, 1);
  var_name_tmp__324 = var_name_tmp__302;
  var_name_tmp__325 = var_name_tmp__303;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__324->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__325)))]))->field2)))), 32, 4);
  var_name_tmp__326 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__326->field5))).array[((int64_t)UINT64_C(0))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (((uint32_t)var_name_load_i32_23))))))), 8, 1);
  var_name_tmp__327 = var_name_tmp__302;
  var_name_tmp__328 = var_name_tmp__303;
  var_name_load_i32_27 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__327->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__328)))]))->field2)))), 32, 4);
  var_name_tmp__329 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__329->field5))).array[((int64_t)UINT64_C(1))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_27)), 8))))))), 8, 1);
  var_name_tmp__330 = var_name_tmp__302;
  var_name_tmp__331 = var_name_tmp__303;
  var_name_load_i32_31 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__330->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__331)))]))->field2)))), 32, 4);
  var_name_tmp__332 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__332->field5))).array[((int64_t)UINT64_C(2))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_31)), 16))))))), 8, 1);
  var_name_tmp__333 = var_name_tmp__302;
  var_name_tmp__334 = var_name_tmp__303;
  var_name_load_i32_35 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__333->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__334)))]))->field2)))), 32, 4);
  var_name_tmp__335 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__335->field5))).array[((int64_t)UINT64_C(3))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_35)), 24))))))), 8, 1);
  var_name_tmp__336 = var_name_tmp__302;
  var_name_tmp__337 = var_name_tmp__303;
  var_name_load_i32_39 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__336->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__337)))]))->field3)))), 32, 4);
  var_name_tmp__338 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__338->field5))).array[((int64_t)UINT64_C(4))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (((uint32_t)var_name_load_i32_39))))))), 8, 1);
  var_name_tmp__339 = var_name_tmp__302;
  var_name_tmp__340 = var_name_tmp__303;
  var_name_load_i32_43 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__339->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__340)))]))->field3)))), 32, 4);
  var_name_tmp__341 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__341->field5))).array[((int64_t)UINT64_C(5))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_43)), 8))))))), 8, 1);
  var_name_tmp__342 = var_name_tmp__302;
  var_name_tmp__343 = var_name_tmp__303;
  var_name_load_i32_47 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__342->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__343)))]))->field3)))), 32, 4);
  var_name_tmp__344 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__344->field5))).array[((int64_t)UINT64_C(6))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_47)), 16))))))), 8, 1);
  var_name_tmp__345 = var_name_tmp__302;
  var_name_tmp__346 = var_name_tmp__303;
  var_name_load_i32_51 = __adin_load_((((uint8_t*)((&((&(*((&var_name_tmp__345->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__346)))]))->field3)))), 32, 4);
  var_name_tmp__347 = var_name_tmp__304;
  __adin_store_(((&(*((&var_name_tmp__347->field5))).array[((int64_t)UINT64_C(7))])), (((uint64_t)(uint8_t)(((uint8_t)(255 & (llvm_lshr_u32((((uint32_t)var_name_load_i32_51)), 24))))))), 8, 1);
  var_name_tmp__348 = var_name_tmp__303;
  if (((((((uint32_t)(uint8_t)var_name_tmp__348)) == 0u)&1))) {
    goto var_name_tmp__356;
  } else {
    goto var_name_tmp__357;
  }

var_name_tmp__356:
  var_name_tmp__349 = var_name_tmp__302;
  var_name_tmp__350 = (&var_name_tmp__349->field3);
  var_name_load_i32_55 = __adin_load_((((uint8_t*)var_name_tmp__350)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__350)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_55)) | 32))), 32, 4);
  goto var_name_tmp__358;

var_name_tmp__357:
  var_name_tmp__351 = var_name_tmp__302;
  var_name_tmp__352 = (&var_name_tmp__351->field4);
  var_name_load_i32_60 = __adin_load_((((uint8_t*)var_name_tmp__352)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__352)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_60)) | 32))), 32, 4);
  goto var_name_tmp__358;

var_name_tmp__358:
  return;
}


void CAN_FIFORelease(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__359, uint8_t var_name_tmp__360) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__361;    /* Address-exposed local */
  uint8_t var_name_tmp__362;    /* Address-exposed local */
  uint8_t var_name_tmp__363;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__364;
  uint32_t* var_name_tmp__365;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__366;
  uint32_t* var_name_tmp__367;
  uint64_t var_name_load_i32_3;

  var_name_tmp__361 = var_name_tmp__359;
  var_name_tmp__362 = var_name_tmp__360;
  var_name_tmp__363 = var_name_tmp__362;
  if (((((((uint32_t)(uint8_t)var_name_tmp__363)) == 0u)&1))) {
    goto var_name_tmp__368;
  } else {
    goto var_name_tmp__369;
  }

var_name_tmp__368:
  var_name_tmp__364 = var_name_tmp__361;
  var_name_tmp__365 = (&var_name_tmp__364->field3);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__365)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__365)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | 32))), 32, 4);
  goto var_name_tmp__370;

var_name_tmp__369:
  var_name_tmp__366 = var_name_tmp__361;
  var_name_tmp__367 = (&var_name_tmp__366->field4);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__367)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__367)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) | 32))), 32, 4);
  goto var_name_tmp__370;

var_name_tmp__370:
  return;
}


uint8_t CAN_MessagePending(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__371, uint8_t var_name_tmp__372) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__373;    /* Address-exposed local */
  uint8_t var_name_tmp__374;    /* Address-exposed local */
  uint8_t var_name_tmp__375;    /* Address-exposed local */
  uint8_t var_name_tmp__376;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__377;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__378;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__379;
  uint64_t var_name_load_i32_2;
  uint8_t var_name_tmp__380;

  var_name_tmp__373 = var_name_tmp__371;
  var_name_tmp__374 = var_name_tmp__372;
  var_name_tmp__375 = 0;
  var_name_tmp__376 = var_name_tmp__374;
  if (((((((uint32_t)(uint8_t)var_name_tmp__376)) == 0u)&1))) {
    goto var_name_tmp__381;
  } else {
    goto var_name_tmp__382;
  }

var_name_tmp__381:
  var_name_tmp__377 = var_name_tmp__373;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__377->field3)))), 32, 4);
  var_name_tmp__375 = (((uint8_t)((((uint32_t)var_name_load_i32_)) & 3)));
  goto var_name_tmp__383;

var_name_tmp__382:
  var_name_tmp__378 = var_name_tmp__374;
  if (((((((uint32_t)(uint8_t)var_name_tmp__378)) == 1u)&1))) {
    goto var_name_tmp__384;
  } else {
    goto var_name_tmp__385;
  }

var_name_tmp__384:
  var_name_tmp__379 = var_name_tmp__373;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__379->field4)))), 32, 4);
  var_name_tmp__375 = (((uint8_t)((((uint32_t)var_name_load_i32_2)) & 3)));
  goto var_name_tmp__386;

var_name_tmp__385:
  var_name_tmp__375 = 0;
  goto var_name_tmp__386;

var_name_tmp__386:
  goto var_name_tmp__383;

var_name_tmp__383:
  var_name_tmp__380 = var_name_tmp__375;
  return var_name_tmp__380;
}


uint8_t CAN_OperatingModeRequest(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__387, uint8_t var_name_tmp__388) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__389;    /* Address-exposed local */
  uint8_t var_name_tmp__390;    /* Address-exposed local */
  uint8_t var_name_tmp__391;    /* Address-exposed local */
  uint32_t var_name_tmp__392;    /* Address-exposed local */
  uint8_t var_name_tmp__393;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__394;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__395;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__396;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__397;
  bool var_name_tmp__398;
  bool var_name_tmp__398__PHI_TEMPORARY;
  uint32_t var_name_tmp__399;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__400;
  uint64_t var_name_load_i32_6;
  uint8_t var_name_tmp__401;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__402;
  uint32_t* var_name_tmp__403;
  uint64_t var_name_load_i32_9;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__404;
  uint64_t var_name_load_i32_14;
  uint32_t var_name_tmp__405;
  bool var_name_tmp__406;
  bool var_name_tmp__406__PHI_TEMPORARY;
  uint32_t var_name_tmp__407;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__408;
  uint64_t var_name_load_i32_17;
  uint8_t var_name_tmp__409;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__410;
  uint64_t var_name_load_i32_20;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__411;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__412;
  uint64_t var_name_load_i32_25;
  uint32_t var_name_tmp__413;
  bool var_name_tmp__414;
  bool var_name_tmp__414__PHI_TEMPORARY;
  uint32_t var_name_tmp__415;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__416;
  uint64_t var_name_load_i32_28;
  uint8_t var_name_tmp__417;

  var_name_tmp__389 = var_name_tmp__387;
  var_name_tmp__390 = var_name_tmp__388;
  var_name_tmp__391 = 0;
  var_name_tmp__392 = 15;
  var_name_tmp__393 = var_name_tmp__390;
  if (((((((uint32_t)(uint8_t)var_name_tmp__393)) == 0u)&1))) {
    goto var_name_tmp__418;
  } else {
    goto var_name_tmp__419;
  }

var_name_tmp__418:
  var_name_tmp__394 = var_name_tmp__389;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__394->field0)))), 32, 4);
  var_name_tmp__395 = var_name_tmp__389;
  __adin_store_((((uint8_t*)((&var_name_tmp__395->field0)))), (((uint64_t)(uint32_t)(((((uint32_t)var_name_load_i32_)) & -3) | 1))), 32, 4);
  goto var_name_tmp__420;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__420:
  var_name_tmp__396 = var_name_tmp__389;
  var_name_load_i32_3 = __adin_load_((((uint8_t*)((&var_name_tmp__396->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 3) != 1u)&1))) {
    goto var_name_tmp__421;
  } else {
    var_name_tmp__398__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__422;
  }

var_name_tmp__421:
  var_name_tmp__397 = var_name_tmp__392;
  var_name_tmp__398__PHI_TEMPORARY = (((var_name_tmp__397 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__422;

var_name_tmp__422:
  var_name_tmp__398 = ((var_name_tmp__398__PHI_TEMPORARY)&1);
  if (var_name_tmp__398) {
    goto var_name_tmp__423;
  } else {
    goto var_name_tmp__424;
  }

var_name_tmp__423:
  var_name_tmp__399 = var_name_tmp__392;
  var_name_tmp__392 = (llvm_add_u32(var_name_tmp__399, -1));
  goto var_name_tmp__420;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__424:
  var_name_tmp__400 = var_name_tmp__389;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__400->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_6)) & 3) != 1u)&1))) {
    goto var_name_tmp__425;
  } else {
    goto var_name_tmp__426;
  }

var_name_tmp__425:
  var_name_tmp__391 = 0;
  goto var_name_tmp__427;

var_name_tmp__426:
  var_name_tmp__391 = 1;
  goto var_name_tmp__427;

var_name_tmp__427:
  goto var_name_tmp__428;

var_name_tmp__419:
  var_name_tmp__401 = var_name_tmp__390;
  if (((((((uint32_t)(uint8_t)var_name_tmp__401)) == 1u)&1))) {
    goto var_name_tmp__429;
  } else {
    goto var_name_tmp__430;
  }

var_name_tmp__429:
  var_name_tmp__402 = var_name_tmp__389;
  var_name_tmp__403 = (&var_name_tmp__402->field0);
  var_name_load_i32_9 = __adin_load_((((uint8_t*)var_name_tmp__403)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__403)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_9)) & -4))), 32, 4);
  goto var_name_tmp__431;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__431:
  var_name_tmp__404 = var_name_tmp__389;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__404->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_14)) & 3) != 0u)&1))) {
    goto var_name_tmp__432;
  } else {
    var_name_tmp__406__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__433;
  }

var_name_tmp__432:
  var_name_tmp__405 = var_name_tmp__392;
  var_name_tmp__406__PHI_TEMPORARY = (((var_name_tmp__405 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__433;

var_name_tmp__433:
  var_name_tmp__406 = ((var_name_tmp__406__PHI_TEMPORARY)&1);
  if (var_name_tmp__406) {
    goto var_name_tmp__434;
  } else {
    goto var_name_tmp__435;
  }

var_name_tmp__434:
  var_name_tmp__407 = var_name_tmp__392;
  var_name_tmp__392 = (llvm_add_u32(var_name_tmp__407, -1));
  goto var_name_tmp__431;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__435:
  var_name_tmp__408 = var_name_tmp__389;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__408->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_17)) & 3) != 0u)&1))) {
    goto var_name_tmp__436;
  } else {
    goto var_name_tmp__437;
  }

var_name_tmp__436:
  var_name_tmp__391 = 0;
  goto var_name_tmp__438;

var_name_tmp__437:
  var_name_tmp__391 = 1;
  goto var_name_tmp__438;

var_name_tmp__438:
  goto var_name_tmp__439;

var_name_tmp__430:
  var_name_tmp__409 = var_name_tmp__390;
  if (((((((uint32_t)(uint8_t)var_name_tmp__409)) == 2u)&1))) {
    goto var_name_tmp__440;
  } else {
    goto var_name_tmp__441;
  }

var_name_tmp__440:
  var_name_tmp__410 = var_name_tmp__389;
  var_name_load_i32_20 = __adin_load_((((uint8_t*)((&var_name_tmp__410->field0)))), 32, 4);
  var_name_tmp__411 = var_name_tmp__389;
  __adin_store_((((uint8_t*)((&var_name_tmp__411->field0)))), (((uint64_t)(uint32_t)(((((uint32_t)var_name_load_i32_20)) & -2) | 2))), 32, 4);
  goto var_name_tmp__442;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__442:
  var_name_tmp__412 = var_name_tmp__389;
  var_name_load_i32_25 = __adin_load_((((uint8_t*)((&var_name_tmp__412->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_25)) & 3) != 2u)&1))) {
    goto var_name_tmp__443;
  } else {
    var_name_tmp__414__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__444;
  }

var_name_tmp__443:
  var_name_tmp__413 = var_name_tmp__392;
  var_name_tmp__414__PHI_TEMPORARY = (((var_name_tmp__413 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__444;

var_name_tmp__444:
  var_name_tmp__414 = ((var_name_tmp__414__PHI_TEMPORARY)&1);
  if (var_name_tmp__414) {
    goto var_name_tmp__445;
  } else {
    goto var_name_tmp__446;
  }

var_name_tmp__445:
  var_name_tmp__415 = var_name_tmp__392;
  var_name_tmp__392 = (llvm_add_u32(var_name_tmp__415, -1));
  goto var_name_tmp__442;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__446:
  var_name_tmp__416 = var_name_tmp__389;
  var_name_load_i32_28 = __adin_load_((((uint8_t*)((&var_name_tmp__416->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_28)) & 3) != 2u)&1))) {
    goto var_name_tmp__447;
  } else {
    goto var_name_tmp__448;
  }

var_name_tmp__447:
  var_name_tmp__391 = 0;
  goto var_name_tmp__449;

var_name_tmp__448:
  var_name_tmp__391 = 1;
  goto var_name_tmp__449;

var_name_tmp__449:
  goto var_name_tmp__450;

var_name_tmp__441:
  var_name_tmp__391 = 0;
  goto var_name_tmp__450;

var_name_tmp__450:
  goto var_name_tmp__439;

var_name_tmp__439:
  goto var_name_tmp__428;

var_name_tmp__428:
  var_name_tmp__417 = var_name_tmp__391;
  return var_name_tmp__417;
}


uint8_t CAN_Sleep(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__451) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__452;    /* Address-exposed local */
  uint8_t var_name_tmp__453;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__454;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__455;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__456;
  uint64_t var_name_load_i32_3;
  uint8_t var_name_tmp__457;

  var_name_tmp__452 = var_name_tmp__451;
  var_name_tmp__453 = 0;
  var_name_tmp__454 = var_name_tmp__452;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__454->field0)))), 32, 4);
  var_name_tmp__455 = var_name_tmp__452;
  __adin_store_((((uint8_t*)((&var_name_tmp__455->field0)))), (((uint64_t)(uint32_t)(((((uint32_t)var_name_load_i32_)) & -2) | 2))), 32, 4);
  var_name_tmp__456 = var_name_tmp__452;
  var_name_load_i32_3 = __adin_load_((((uint8_t*)((&var_name_tmp__456->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 3) == 2u)&1))) {
    goto var_name_tmp__458;
  } else {
    goto var_name_tmp__459;
  }

var_name_tmp__458:
  var_name_tmp__453 = 1;
  goto var_name_tmp__459;

var_name_tmp__459:
  var_name_tmp__457 = var_name_tmp__453;
  return var_name_tmp__457;
}


uint8_t CAN_WakeUp(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__460) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__461;    /* Address-exposed local */
  uint32_t var_name_tmp__462;    /* Address-exposed local */
  uint8_t var_name_tmp__463;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__464;
  uint32_t* var_name_tmp__465;
  uint64_t var_name_load_i32_;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__466;
  uint64_t var_name_load_i32_3;
  uint32_t var_name_tmp__467;
  bool var_name_tmp__468;
  bool var_name_tmp__468__PHI_TEMPORARY;
  uint32_t var_name_tmp__469;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__470;
  uint64_t var_name_load_i32_6;
  uint8_t var_name_tmp__471;

  var_name_tmp__461 = var_name_tmp__460;
  var_name_tmp__462 = 65535;
  var_name_tmp__463 = 0;
  var_name_tmp__464 = var_name_tmp__461;
  var_name_tmp__465 = (&var_name_tmp__464->field0);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__465)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__465)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) & -3))), 32, 4);
  goto var_name_tmp__472;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__472:
  var_name_tmp__466 = var_name_tmp__461;
  var_name_load_i32_3 = __adin_load_((((uint8_t*)((&var_name_tmp__466->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_3)) & 2) == 2u)&1))) {
    goto var_name_tmp__473;
  } else {
    var_name_tmp__468__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__474;
  }

var_name_tmp__473:
  var_name_tmp__467 = var_name_tmp__462;
  var_name_tmp__468__PHI_TEMPORARY = (((var_name_tmp__467 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__474;

var_name_tmp__474:
  var_name_tmp__468 = ((var_name_tmp__468__PHI_TEMPORARY)&1);
  if (var_name_tmp__468) {
    goto var_name_tmp__475;
  } else {
    goto var_name_tmp__476;
  }

var_name_tmp__475:
  var_name_tmp__469 = var_name_tmp__462;
  var_name_tmp__462 = (llvm_add_u32(var_name_tmp__469, -1));
  goto var_name_tmp__472;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__476:
  var_name_tmp__470 = var_name_tmp__461;
  var_name_load_i32_6 = __adin_load_((((uint8_t*)((&var_name_tmp__470->field1)))), 32, 4);
  if ((((((((uint32_t)var_name_load_i32_6)) & 2) != 2u)&1))) {
    goto var_name_tmp__477;
  } else {
    goto var_name_tmp__478;
  }

var_name_tmp__477:
  var_name_tmp__463 = 1;
  goto var_name_tmp__478;

var_name_tmp__478:
  var_name_tmp__471 = var_name_tmp__463;
  return var_name_tmp__471;
}


uint8_t CAN_GetLastErrorCode(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__479) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__480;    /* Address-exposed local */
  uint8_t var_name_tmp__481;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__482;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__483;

  var_name_tmp__480 = var_name_tmp__479;
  var_name_tmp__481 = 0;
  var_name_tmp__482 = var_name_tmp__480;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__482->field6)))), 32, 4);
  var_name_tmp__481 = (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)(((uint32_t)var_name_load_i32_)))))) & 112)));
  var_name_tmp__483 = var_name_tmp__481;
  return var_name_tmp__483;
}


uint8_t CAN_GetReceiveErrorCounter(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__484) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__485;    /* Address-exposed local */
  uint8_t var_name_tmp__486;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__487;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__488;

  var_name_tmp__485 = var_name_tmp__484;
  var_name_tmp__486 = 0;
  var_name_tmp__487 = var_name_tmp__485;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__487->field6)))), 32, 4);
  var_name_tmp__486 = (((uint8_t)(llvm_lshr_u32(((((uint32_t)var_name_load_i32_)) & -16777216), 24))));
  var_name_tmp__488 = var_name_tmp__486;
  return var_name_tmp__488;
}


uint8_t CAN_GetLSBTransmitErrorCounter(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__489) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__490;    /* Address-exposed local */
  uint8_t var_name_tmp__491;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__492;
  uint64_t var_name_load_i32_;
  uint8_t var_name_tmp__493;

  var_name_tmp__490 = var_name_tmp__489;
  var_name_tmp__491 = 0;
  var_name_tmp__492 = var_name_tmp__490;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__492->field6)))), 32, 4);
  var_name_tmp__491 = (((uint8_t)(llvm_lshr_u32(((((uint32_t)var_name_load_i32_)) & 16711680), 16))));
  var_name_tmp__493 = var_name_tmp__491;
  return var_name_tmp__493;
}


void CAN_ITConfig(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__494, uint32_t var_name_tmp__495, uint32_t var_name_tmp__496) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__497;    /* Address-exposed local */
  uint32_t var_name_tmp__498;    /* Address-exposed local */
  uint32_t var_name_tmp__499;    /* Address-exposed local */
  uint32_t var_name_tmp__500;
  uint32_t var_name_tmp__501;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__502;
  uint32_t* var_name_tmp__503;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__504;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__505;
  uint32_t* var_name_tmp__506;
  uint64_t var_name_load_i32_3;

  var_name_tmp__497 = var_name_tmp__494;
  var_name_tmp__498 = var_name_tmp__495;
  var_name_tmp__499 = var_name_tmp__496;
  var_name_tmp__500 = var_name_tmp__499;
  if ((((var_name_tmp__500 != 0u)&1))) {
    goto var_name_tmp__507;
  } else {
    goto var_name_tmp__508;
  }

var_name_tmp__507:
  var_name_tmp__501 = var_name_tmp__498;
  var_name_tmp__502 = var_name_tmp__497;
  var_name_tmp__503 = (&var_name_tmp__502->field5);
  var_name_load_i32_ = __adin_load_((((uint8_t*)var_name_tmp__503)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__503)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_)) | var_name_tmp__501))), 32, 4);
  goto var_name_tmp__509;

var_name_tmp__508:
  var_name_tmp__504 = var_name_tmp__498;
  var_name_tmp__505 = var_name_tmp__497;
  var_name_tmp__506 = (&var_name_tmp__505->field5);
  var_name_load_i32_3 = __adin_load_((((uint8_t*)var_name_tmp__506)), 32, 4);
  __adin_store_((((uint8_t*)var_name_tmp__506)), (((uint64_t)(uint32_t)((((uint32_t)var_name_load_i32_3)) & (~(var_name_tmp__504))))), 32, 4);
  goto var_name_tmp__509;

var_name_tmp__509:
  return;
}


uint32_t CAN_GetFlagStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__510, uint32_t var_name_tmp__511) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__512;    /* Address-exposed local */
  uint32_t var_name_tmp__513;    /* Address-exposed local */
  uint32_t var_name_tmp__514;    /* Address-exposed local */
  uint32_t var_name_tmp__515;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__516;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__517;
  uint32_t var_name_tmp__518;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__519;
  uint64_t var_name_load_i32_2;
  uint32_t var_name_tmp__520;
  uint32_t var_name_tmp__521;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__522;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__523;
  uint32_t var_name_tmp__524;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__525;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__526;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__527;
  uint64_t var_name_load_i32_11;
  uint32_t var_name_tmp__528;
  uint32_t var_name_tmp__529;

  var_name_tmp__512 = var_name_tmp__510;
  var_name_tmp__513 = var_name_tmp__511;
  var_name_tmp__514 = 0;
  var_name_tmp__515 = var_name_tmp__513;
  if (((((var_name_tmp__515 & 15728640) != 0u)&1))) {
    goto var_name_tmp__530;
  } else {
    goto var_name_tmp__531;
  }

var_name_tmp__530:
  var_name_tmp__516 = var_name_tmp__512;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__516->field6)))), 32, 4);
  var_name_tmp__517 = var_name_tmp__513;
  if ((((((((uint32_t)var_name_load_i32_)) & (var_name_tmp__517 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__532;
  } else {
    goto var_name_tmp__533;
  }

var_name_tmp__532:
  var_name_tmp__514 = 1;
  goto var_name_tmp__534;

var_name_tmp__533:
  var_name_tmp__514 = 0;
  goto var_name_tmp__534;

var_name_tmp__534:
  goto var_name_tmp__535;

var_name_tmp__531:
  var_name_tmp__518 = var_name_tmp__513;
  if (((((var_name_tmp__518 & 16777216) != 0u)&1))) {
    goto var_name_tmp__536;
  } else {
    goto var_name_tmp__537;
  }

var_name_tmp__536:
  var_name_tmp__519 = var_name_tmp__512;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__519->field1)))), 32, 4);
  var_name_tmp__520 = var_name_tmp__513;
  if ((((((((uint32_t)var_name_load_i32_2)) & (var_name_tmp__520 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__538;
  } else {
    goto var_name_tmp__539;
  }

var_name_tmp__538:
  var_name_tmp__514 = 1;
  goto var_name_tmp__540;

var_name_tmp__539:
  var_name_tmp__514 = 0;
  goto var_name_tmp__540;

var_name_tmp__540:
  goto var_name_tmp__541;

var_name_tmp__537:
  var_name_tmp__521 = var_name_tmp__513;
  if (((((var_name_tmp__521 & 134217728) != 0u)&1))) {
    goto var_name_tmp__542;
  } else {
    goto var_name_tmp__543;
  }

var_name_tmp__542:
  var_name_tmp__522 = var_name_tmp__512;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__522->field2)))), 32, 4);
  var_name_tmp__523 = var_name_tmp__513;
  if ((((((((uint32_t)var_name_load_i32_5)) & (var_name_tmp__523 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__544;
  } else {
    goto var_name_tmp__545;
  }

var_name_tmp__544:
  var_name_tmp__514 = 1;
  goto var_name_tmp__546;

var_name_tmp__545:
  var_name_tmp__514 = 0;
  goto var_name_tmp__546;

var_name_tmp__546:
  goto var_name_tmp__547;

var_name_tmp__543:
  var_name_tmp__524 = var_name_tmp__513;
  if (((((var_name_tmp__524 & 33554432) != 0u)&1))) {
    goto var_name_tmp__548;
  } else {
    goto var_name_tmp__549;
  }

var_name_tmp__548:
  var_name_tmp__525 = var_name_tmp__512;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__525->field3)))), 32, 4);
  var_name_tmp__526 = var_name_tmp__513;
  if ((((((((uint32_t)var_name_load_i32_8)) & (var_name_tmp__526 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__550;
  } else {
    goto var_name_tmp__551;
  }

var_name_tmp__550:
  var_name_tmp__514 = 1;
  goto var_name_tmp__552;

var_name_tmp__551:
  var_name_tmp__514 = 0;
  goto var_name_tmp__552;

var_name_tmp__552:
  goto var_name_tmp__553;

var_name_tmp__549:
  var_name_tmp__527 = var_name_tmp__512;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__527->field4)))), 32, 4);
  var_name_tmp__528 = var_name_tmp__513;
  if ((((((((uint32_t)var_name_load_i32_11)) & (var_name_tmp__528 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__554;
  } else {
    goto var_name_tmp__555;
  }

var_name_tmp__554:
  var_name_tmp__514 = 1;
  goto var_name_tmp__556;

var_name_tmp__555:
  var_name_tmp__514 = 0;
  goto var_name_tmp__556;

var_name_tmp__556:
  goto var_name_tmp__553;

var_name_tmp__553:
  goto var_name_tmp__547;

var_name_tmp__547:
  goto var_name_tmp__541;

var_name_tmp__541:
  goto var_name_tmp__535;

var_name_tmp__535:
  var_name_tmp__529 = var_name_tmp__514;
  return var_name_tmp__529;
}


void CAN_ClearFlag(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__557, uint32_t var_name_tmp__558) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__559;    /* Address-exposed local */
  uint32_t var_name_tmp__560;    /* Address-exposed local */
  uint32_t var_name_tmp__561;    /* Address-exposed local */
  uint32_t var_name_tmp__562;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__563;
  uint32_t var_name_tmp__564;
  uint32_t var_name_tmp__565;
  uint32_t var_name_tmp__566;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__567;
  uint32_t var_name_tmp__568;
  uint32_t var_name_tmp__569;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__570;
  uint32_t var_name_tmp__571;
  uint32_t var_name_tmp__572;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__573;
  uint32_t var_name_tmp__574;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__575;

  var_name_tmp__559 = var_name_tmp__557;
  var_name_tmp__560 = var_name_tmp__558;
  var_name_tmp__561 = 0;
  var_name_tmp__562 = var_name_tmp__560;
  if ((((var_name_tmp__562 == 821035120u)&1))) {
    goto var_name_tmp__576;
  } else {
    goto var_name_tmp__577;
  }

var_name_tmp__576:
  var_name_tmp__563 = var_name_tmp__559;
  __adin_store_((((uint8_t*)((&var_name_tmp__563->field6)))), UINT64_C(0), 32, 4);
  goto var_name_tmp__578;

var_name_tmp__577:
  var_name_tmp__564 = var_name_tmp__560;
  var_name_tmp__561 = (var_name_tmp__564 & 1048575);
  var_name_tmp__565 = var_name_tmp__560;
  if (((((var_name_tmp__565 & 33554432) != 0u)&1))) {
    goto var_name_tmp__579;
  } else {
    goto var_name_tmp__580;
  }

var_name_tmp__579:
  var_name_tmp__566 = var_name_tmp__561;
  var_name_tmp__567 = var_name_tmp__559;
  __adin_store_((((uint8_t*)((&var_name_tmp__567->field3)))), (((uint64_t)(uint32_t)var_name_tmp__566)), 32, 4);
  goto var_name_tmp__581;

var_name_tmp__580:
  var_name_tmp__568 = var_name_tmp__560;
  if (((((var_name_tmp__568 & 67108864) != 0u)&1))) {
    goto var_name_tmp__582;
  } else {
    goto var_name_tmp__583;
  }

var_name_tmp__582:
  var_name_tmp__569 = var_name_tmp__561;
  var_name_tmp__570 = var_name_tmp__559;
  __adin_store_((((uint8_t*)((&var_name_tmp__570->field4)))), (((uint64_t)(uint32_t)var_name_tmp__569)), 32, 4);
  goto var_name_tmp__584;

var_name_tmp__583:
  var_name_tmp__571 = var_name_tmp__560;
  if (((((var_name_tmp__571 & 134217728) != 0u)&1))) {
    goto var_name_tmp__585;
  } else {
    goto var_name_tmp__586;
  }

var_name_tmp__585:
  var_name_tmp__572 = var_name_tmp__561;
  var_name_tmp__573 = var_name_tmp__559;
  __adin_store_((((uint8_t*)((&var_name_tmp__573->field2)))), (((uint64_t)(uint32_t)var_name_tmp__572)), 32, 4);
  goto var_name_tmp__587;

var_name_tmp__586:
  var_name_tmp__574 = var_name_tmp__561;
  var_name_tmp__575 = var_name_tmp__559;
  __adin_store_((((uint8_t*)((&var_name_tmp__575->field1)))), (((uint64_t)(uint32_t)var_name_tmp__574)), 32, 4);
  goto var_name_tmp__587;

var_name_tmp__587:
  goto var_name_tmp__584;

var_name_tmp__584:
  goto var_name_tmp__581;

var_name_tmp__581:
  goto var_name_tmp__578;

var_name_tmp__578:
  return;
}


uint32_t CAN_GetITStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__588, uint32_t var_name_tmp__589) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__590;    /* Address-exposed local */
  uint32_t var_name_tmp__591;    /* Address-exposed local */
  uint32_t var_name_tmp__592;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__593;
  uint64_t var_name_load_i32_;
  uint32_t var_name_tmp__594;
  uint32_t var_name_tmp__595;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__596;
  uint64_t var_name_load_i32_2;
  uint32_t var_name_tmp__597;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__598;
  uint64_t var_name_load_i32_5;
  uint32_t var_name_tmp__599;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__600;
  uint64_t var_name_load_i32_8;
  uint32_t var_name_tmp__601;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__602;
  uint64_t var_name_load_i32_11;
  uint32_t var_name_tmp__603;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__604;
  uint64_t var_name_load_i32_14;
  uint32_t var_name_tmp__605;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__606;
  uint64_t var_name_load_i32_17;
  uint32_t var_name_tmp__607;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__608;
  uint64_t var_name_load_i32_20;
  uint32_t var_name_tmp__609;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__610;
  uint64_t var_name_load_i32_23;
  uint32_t var_name_tmp__611;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__612;
  uint64_t var_name_load_i32_26;
  uint32_t var_name_tmp__613;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__614;
  uint64_t var_name_load_i32_29;
  uint32_t var_name_tmp__615;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__616;
  uint64_t var_name_load_i32_32;
  uint32_t var_name_tmp__617;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__618;
  uint64_t var_name_load_i32_35;
  uint32_t var_name_tmp__619;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__620;
  uint64_t var_name_load_i32_38;
  uint32_t var_name_tmp__621;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__622;
  uint64_t var_name_load_i32_41;
  uint32_t var_name_tmp__623;
  uint32_t var_name_tmp__624;

  var_name_tmp__590 = var_name_tmp__588;
  var_name_tmp__591 = var_name_tmp__589;
  var_name_tmp__592 = 0;
  var_name_tmp__593 = var_name_tmp__590;
  var_name_load_i32_ = __adin_load_((((uint8_t*)((&var_name_tmp__593->field5)))), 32, 4);
  var_name_tmp__594 = var_name_tmp__591;
  if ((((((((uint32_t)var_name_load_i32_)) & var_name_tmp__594) != 0u)&1))) {
    goto var_name_tmp__625;
  } else {
    goto var_name_tmp__626;
  }

var_name_tmp__625:
  var_name_tmp__595 = var_name_tmp__591;
  switch (var_name_tmp__595) {
  default:
    goto var_name_tmp__627;
  case 1u:
    goto var_name_tmp__628;
  case 2u:
    goto var_name_tmp__629;
  case 4u:
    goto var_name_tmp__630;
  case 8u:
    goto var_name_tmp__631;
  case 16u:
    goto var_name_tmp__632;
  case 32u:
    goto var_name_tmp__633;
  case 64u:
    goto var_name_tmp__634;
  case 65536u:
    goto var_name_tmp__635;
  case 131072u:
    goto var_name_tmp__636;
  case 256u:
    goto var_name_tmp__637;
  case 512u:
    goto var_name_tmp__638;
  case 1024u:
    goto var_name_tmp__639;
  case 2048u:
    goto var_name_tmp__640;
  case 32768u:
    goto var_name_tmp__641;
  }

var_name_tmp__628:
  var_name_tmp__596 = var_name_tmp__590;
  var_name_load_i32_2 = __adin_load_((((uint8_t*)((&var_name_tmp__596->field2)))), 32, 4);
  var_name_tmp__597 = CheckITStatus((((uint32_t)var_name_load_i32_2)), 65793);
  var_name_tmp__592 = var_name_tmp__597;
  goto var_name_tmp__642;

var_name_tmp__629:
  var_name_tmp__598 = var_name_tmp__590;
  var_name_load_i32_5 = __adin_load_((((uint8_t*)((&var_name_tmp__598->field3)))), 32, 4);
  var_name_tmp__599 = CheckITStatus((((uint32_t)var_name_load_i32_5)), 3);
  var_name_tmp__592 = var_name_tmp__599;
  goto var_name_tmp__642;

var_name_tmp__630:
  var_name_tmp__600 = var_name_tmp__590;
  var_name_load_i32_8 = __adin_load_((((uint8_t*)((&var_name_tmp__600->field3)))), 32, 4);
  var_name_tmp__601 = CheckITStatus((((uint32_t)var_name_load_i32_8)), 8);
  var_name_tmp__592 = var_name_tmp__601;
  goto var_name_tmp__642;

var_name_tmp__631:
  var_name_tmp__602 = var_name_tmp__590;
  var_name_load_i32_11 = __adin_load_((((uint8_t*)((&var_name_tmp__602->field3)))), 32, 4);
  var_name_tmp__603 = CheckITStatus((((uint32_t)var_name_load_i32_11)), 16);
  var_name_tmp__592 = var_name_tmp__603;
  goto var_name_tmp__642;

var_name_tmp__632:
  var_name_tmp__604 = var_name_tmp__590;
  var_name_load_i32_14 = __adin_load_((((uint8_t*)((&var_name_tmp__604->field4)))), 32, 4);
  var_name_tmp__605 = CheckITStatus((((uint32_t)var_name_load_i32_14)), 3);
  var_name_tmp__592 = var_name_tmp__605;
  goto var_name_tmp__642;

var_name_tmp__633:
  var_name_tmp__606 = var_name_tmp__590;
  var_name_load_i32_17 = __adin_load_((((uint8_t*)((&var_name_tmp__606->field4)))), 32, 4);
  var_name_tmp__607 = CheckITStatus((((uint32_t)var_name_load_i32_17)), 8);
  var_name_tmp__592 = var_name_tmp__607;
  goto var_name_tmp__642;

var_name_tmp__634:
  var_name_tmp__608 = var_name_tmp__590;
  var_name_load_i32_20 = __adin_load_((((uint8_t*)((&var_name_tmp__608->field4)))), 32, 4);
  var_name_tmp__609 = CheckITStatus((((uint32_t)var_name_load_i32_20)), 16);
  var_name_tmp__592 = var_name_tmp__609;
  goto var_name_tmp__642;

var_name_tmp__635:
  var_name_tmp__610 = var_name_tmp__590;
  var_name_load_i32_23 = __adin_load_((((uint8_t*)((&var_name_tmp__610->field1)))), 32, 4);
  var_name_tmp__611 = CheckITStatus((((uint32_t)var_name_load_i32_23)), 8);
  var_name_tmp__592 = var_name_tmp__611;
  goto var_name_tmp__642;

var_name_tmp__636:
  var_name_tmp__612 = var_name_tmp__590;
  var_name_load_i32_26 = __adin_load_((((uint8_t*)((&var_name_tmp__612->field1)))), 32, 4);
  var_name_tmp__613 = CheckITStatus((((uint32_t)var_name_load_i32_26)), 16);
  var_name_tmp__592 = var_name_tmp__613;
  goto var_name_tmp__642;

var_name_tmp__637:
  var_name_tmp__614 = var_name_tmp__590;
  var_name_load_i32_29 = __adin_load_((((uint8_t*)((&var_name_tmp__614->field6)))), 32, 4);
  var_name_tmp__615 = CheckITStatus((((uint32_t)var_name_load_i32_29)), 1);
  var_name_tmp__592 = var_name_tmp__615;
  goto var_name_tmp__642;

var_name_tmp__638:
  var_name_tmp__616 = var_name_tmp__590;
  var_name_load_i32_32 = __adin_load_((((uint8_t*)((&var_name_tmp__616->field6)))), 32, 4);
  var_name_tmp__617 = CheckITStatus((((uint32_t)var_name_load_i32_32)), 2);
  var_name_tmp__592 = var_name_tmp__617;
  goto var_name_tmp__642;

var_name_tmp__639:
  var_name_tmp__618 = var_name_tmp__590;
  var_name_load_i32_35 = __adin_load_((((uint8_t*)((&var_name_tmp__618->field6)))), 32, 4);
  var_name_tmp__619 = CheckITStatus((((uint32_t)var_name_load_i32_35)), 4);
  var_name_tmp__592 = var_name_tmp__619;
  goto var_name_tmp__642;

var_name_tmp__640:
  var_name_tmp__620 = var_name_tmp__590;
  var_name_load_i32_38 = __adin_load_((((uint8_t*)((&var_name_tmp__620->field6)))), 32, 4);
  var_name_tmp__621 = CheckITStatus((((uint32_t)var_name_load_i32_38)), 112);
  var_name_tmp__592 = var_name_tmp__621;
  goto var_name_tmp__642;

var_name_tmp__641:
  var_name_tmp__622 = var_name_tmp__590;
  var_name_load_i32_41 = __adin_load_((((uint8_t*)((&var_name_tmp__622->field1)))), 32, 4);
  var_name_tmp__623 = CheckITStatus((((uint32_t)var_name_load_i32_41)), 4);
  var_name_tmp__592 = var_name_tmp__623;
  goto var_name_tmp__642;

var_name_tmp__627:
  var_name_tmp__592 = 0;
  goto var_name_tmp__642;

var_name_tmp__642:
  goto var_name_tmp__643;

var_name_tmp__626:
  var_name_tmp__592 = 0;
  goto var_name_tmp__643;

var_name_tmp__643:
  var_name_tmp__624 = var_name_tmp__592;
  return var_name_tmp__624;
}


static uint32_t CheckITStatus(uint32_t var_name_tmp__644, uint32_t var_name_tmp__645) {
  uint32_t var_name_tmp__646;    /* Address-exposed local */
  uint32_t var_name_tmp__647;    /* Address-exposed local */
  uint32_t var_name_tmp__648;    /* Address-exposed local */
  uint32_t var_name_tmp__649;
  uint32_t var_name_tmp__650;
  uint32_t var_name_tmp__651;

  var_name_tmp__646 = var_name_tmp__644;
  var_name_tmp__647 = var_name_tmp__645;
  var_name_tmp__648 = 0;
  var_name_tmp__649 = var_name_tmp__646;
  var_name_tmp__650 = var_name_tmp__647;
  if (((((var_name_tmp__649 & var_name_tmp__650) != 0u)&1))) {
    goto var_name_tmp__652;
  } else {
    goto var_name_tmp__653;
  }

var_name_tmp__652:
  var_name_tmp__648 = 1;
  goto var_name_tmp__654;

var_name_tmp__653:
  var_name_tmp__648 = 0;
  goto var_name_tmp__654;

var_name_tmp__654:
  var_name_tmp__651 = var_name_tmp__648;
  return var_name_tmp__651;
}


void CAN_ClearITPendingBit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__655, uint32_t var_name_tmp__656) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__657;    /* Address-exposed local */
  uint32_t var_name_tmp__658;    /* Address-exposed local */
  uint32_t var_name_tmp__659;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__660;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__661;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__662;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__663;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__664;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__665;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__666;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__667;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__668;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__669;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__670;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__671;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__672;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__673;

  var_name_tmp__657 = var_name_tmp__655;
  var_name_tmp__658 = var_name_tmp__656;
  var_name_tmp__659 = var_name_tmp__658;
  switch (var_name_tmp__659) {
  default:
    goto var_name_tmp__674;
  case 1u:
    goto var_name_tmp__675;
  case 4u:
    goto var_name_tmp__676;
  case 8u:
    goto var_name_tmp__677;
  case 32u:
    goto var_name_tmp__678;
  case 64u:
    goto var_name_tmp__679;
  case 65536u:
    goto var_name_tmp__680;
  case 131072u:
    goto var_name_tmp__681;
  case 256u:
    goto var_name_tmp__682;
  case 512u:
    goto var_name_tmp__683;
  case 1024u:
    goto var_name_tmp__684;
  case 2048u:
    goto var_name_tmp__685;
  case 32768u:
    goto var_name_tmp__686;
  }

var_name_tmp__675:
  var_name_tmp__660 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__660->field2)))), UINT64_C(65793), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__676:
  var_name_tmp__661 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__661->field3)))), UINT64_C(8), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__677:
  var_name_tmp__662 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__662->field3)))), UINT64_C(16), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__678:
  var_name_tmp__663 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__663->field4)))), UINT64_C(8), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__679:
  var_name_tmp__664 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__664->field4)))), UINT64_C(16), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__680:
  var_name_tmp__665 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__665->field1)))), UINT64_C(8), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__681:
  var_name_tmp__666 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__666->field1)))), UINT64_C(16), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__682:
  var_name_tmp__667 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__667->field1)))), UINT64_C(4), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__683:
  var_name_tmp__668 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__668->field1)))), UINT64_C(4), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__684:
  var_name_tmp__669 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__669->field1)))), UINT64_C(4), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__685:
  var_name_tmp__670 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__670->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__671 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__671->field1)))), UINT64_C(4), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__686:
  var_name_tmp__672 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__672->field6)))), UINT64_C(0), 32, 4);
  var_name_tmp__673 = var_name_tmp__657;
  __adin_store_((((uint8_t*)((&var_name_tmp__673->field1)))), UINT64_C(4), 32, 4);
  goto var_name_tmp__687;

var_name_tmp__674:
  goto var_name_tmp__687;

var_name_tmp__687:
  return;
}

