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
  uint32_t var_name_tmp__15;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__16;
  uint32_t* var_name_tmp__17;
  uint32_t var_name_tmp__18;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__19;
  uint32_t var_name_tmp__20;
  uint32_t var_name_tmp__21;
  bool var_name_tmp__22;
  bool var_name_tmp__22__PHI_TEMPORARY;
  uint32_t var_name_tmp__23;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__24;
  uint32_t var_name_tmp__25;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__26;
  uint32_t var_name_tmp__27;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__28;
  uint32_t* var_name_tmp__29;
  uint32_t var_name_tmp__30;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__31;
  uint32_t* var_name_tmp__32;
  uint32_t var_name_tmp__33;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__34;
  uint32_t var_name_tmp__35;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__36;
  uint32_t* var_name_tmp__37;
  uint32_t var_name_tmp__38;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__39;
  uint32_t* var_name_tmp__40;
  uint32_t var_name_tmp__41;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__42;
  uint32_t var_name_tmp__43;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__44;
  uint32_t* var_name_tmp__45;
  uint32_t var_name_tmp__46;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__47;
  uint32_t* var_name_tmp__48;
  uint32_t var_name_tmp__49;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__50;
  uint32_t var_name_tmp__51;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__52;
  uint32_t* var_name_tmp__53;
  uint32_t var_name_tmp__54;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__55;
  uint32_t* var_name_tmp__56;
  uint32_t var_name_tmp__57;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__58;
  uint32_t var_name_tmp__59;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__60;
  uint32_t* var_name_tmp__61;
  uint32_t var_name_tmp__62;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__63;
  uint32_t* var_name_tmp__64;
  uint32_t var_name_tmp__65;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__66;
  uint32_t var_name_tmp__67;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__68;
  uint32_t* var_name_tmp__69;
  uint32_t var_name_tmp__70;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__71;
  uint32_t* var_name_tmp__72;
  uint32_t var_name_tmp__73;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__74;
  uint8_t var_name_tmp__75;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__76;
  uint8_t var_name_tmp__77;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__78;
  uint8_t var_name_tmp__79;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__80;
  uint8_t var_name_tmp__81;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__82;
  uint16_t var_name_tmp__83;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__84;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__85;
  uint32_t* var_name_tmp__86;
  uint32_t var_name_tmp__87;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__88;
  uint32_t var_name_tmp__89;
  uint32_t var_name_tmp__90;
  bool var_name_tmp__91;
  bool var_name_tmp__91__PHI_TEMPORARY;
  uint32_t var_name_tmp__92;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__93;
  uint32_t var_name_tmp__94;
  uint8_t var_name_tmp__95;

  var_name_tmp__9 = var_name_tmp__7;
  var_name_tmp__10 = var_name_tmp__8;
  var_name_tmp__11 = 0;
  var_name_tmp__12 = 0;
  var_name_tmp__13 = var_name_tmp__9;
  var_name_tmp__14 = (&var_name_tmp__13->field0);
  var_name_tmp__15 = *(volatile uint32_t*)var_name_tmp__14;
  *(volatile uint32_t*)var_name_tmp__14 = (var_name_tmp__15 & -3);
  var_name_tmp__16 = var_name_tmp__9;
  var_name_tmp__17 = (&var_name_tmp__16->field0);
  var_name_tmp__18 = *(volatile uint32_t*)var_name_tmp__17;
  *(volatile uint32_t*)var_name_tmp__17 = (var_name_tmp__18 | 1);
  goto var_name_tmp__96;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__96:
  var_name_tmp__19 = var_name_tmp__9;
  var_name_tmp__20 = *(volatile uint32_t*)((&var_name_tmp__19->field1));
  if (((((var_name_tmp__20 & 1) != 1u)&1))) {
    goto var_name_tmp__97;
  } else {
    var_name_tmp__22__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__98;
  }

var_name_tmp__97:
  var_name_tmp__21 = var_name_tmp__12;
  var_name_tmp__22__PHI_TEMPORARY = (((var_name_tmp__21 != 15u)&1));   /* for PHI node */
  goto var_name_tmp__98;

var_name_tmp__98:
  var_name_tmp__22 = ((var_name_tmp__22__PHI_TEMPORARY)&1);
  if (var_name_tmp__22) {
    goto var_name_tmp__99;
  } else {
    goto var_name_tmp__100;
  }

var_name_tmp__99:
  var_name_tmp__23 = var_name_tmp__12;
  var_name_tmp__12 = (llvm_add_u32(var_name_tmp__23, 1));
  goto var_name_tmp__96;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__100:
  var_name_tmp__24 = var_name_tmp__9;
  var_name_tmp__25 = *(volatile uint32_t*)((&var_name_tmp__24->field1));
  if (((((var_name_tmp__25 & 1) != 1u)&1))) {
    goto var_name_tmp__101;
  } else {
    goto var_name_tmp__102;
  }

var_name_tmp__101:
  var_name_tmp__11 = 0;
  goto var_name_tmp__103;

var_name_tmp__102:
  var_name_tmp__26 = var_name_tmp__10;
  var_name_tmp__27 = *((&var_name_tmp__26->field5));
  if ((((var_name_tmp__27 == 1u)&1))) {
    goto var_name_tmp__104;
  } else {
    goto var_name_tmp__105;
  }

var_name_tmp__104:
  var_name_tmp__28 = var_name_tmp__9;
  var_name_tmp__29 = (&var_name_tmp__28->field0);
  var_name_tmp__30 = *(volatile uint32_t*)var_name_tmp__29;
  *(volatile uint32_t*)var_name_tmp__29 = (var_name_tmp__30 | 128);
  goto var_name_tmp__106;

var_name_tmp__105:
  var_name_tmp__31 = var_name_tmp__9;
  var_name_tmp__32 = (&var_name_tmp__31->field0);
  var_name_tmp__33 = *(volatile uint32_t*)var_name_tmp__32;
  *(volatile uint32_t*)var_name_tmp__32 = (var_name_tmp__33 & -129);
  goto var_name_tmp__106;

var_name_tmp__106:
  var_name_tmp__34 = var_name_tmp__10;
  var_name_tmp__35 = *((&var_name_tmp__34->field6));
  if ((((var_name_tmp__35 == 1u)&1))) {
    goto var_name_tmp__107;
  } else {
    goto var_name_tmp__108;
  }

var_name_tmp__107:
  var_name_tmp__36 = var_name_tmp__9;
  var_name_tmp__37 = (&var_name_tmp__36->field0);
  var_name_tmp__38 = *(volatile uint32_t*)var_name_tmp__37;
  *(volatile uint32_t*)var_name_tmp__37 = (var_name_tmp__38 | 64);
  goto var_name_tmp__109;

var_name_tmp__108:
  var_name_tmp__39 = var_name_tmp__9;
  var_name_tmp__40 = (&var_name_tmp__39->field0);
  var_name_tmp__41 = *(volatile uint32_t*)var_name_tmp__40;
  *(volatile uint32_t*)var_name_tmp__40 = (var_name_tmp__41 & -65);
  goto var_name_tmp__109;

var_name_tmp__109:
  var_name_tmp__42 = var_name_tmp__10;
  var_name_tmp__43 = *((&var_name_tmp__42->field7));
  if ((((var_name_tmp__43 == 1u)&1))) {
    goto var_name_tmp__110;
  } else {
    goto var_name_tmp__111;
  }

var_name_tmp__110:
  var_name_tmp__44 = var_name_tmp__9;
  var_name_tmp__45 = (&var_name_tmp__44->field0);
  var_name_tmp__46 = *(volatile uint32_t*)var_name_tmp__45;
  *(volatile uint32_t*)var_name_tmp__45 = (var_name_tmp__46 | 32);
  goto var_name_tmp__112;

var_name_tmp__111:
  var_name_tmp__47 = var_name_tmp__9;
  var_name_tmp__48 = (&var_name_tmp__47->field0);
  var_name_tmp__49 = *(volatile uint32_t*)var_name_tmp__48;
  *(volatile uint32_t*)var_name_tmp__48 = (var_name_tmp__49 & -33);
  goto var_name_tmp__112;

var_name_tmp__112:
  var_name_tmp__50 = var_name_tmp__10;
  var_name_tmp__51 = *((&var_name_tmp__50->field8));
  if ((((var_name_tmp__51 == 1u)&1))) {
    goto var_name_tmp__113;
  } else {
    goto var_name_tmp__114;
  }

var_name_tmp__113:
  var_name_tmp__52 = var_name_tmp__9;
  var_name_tmp__53 = (&var_name_tmp__52->field0);
  var_name_tmp__54 = *(volatile uint32_t*)var_name_tmp__53;
  *(volatile uint32_t*)var_name_tmp__53 = (var_name_tmp__54 | 16);
  goto var_name_tmp__115;

var_name_tmp__114:
  var_name_tmp__55 = var_name_tmp__9;
  var_name_tmp__56 = (&var_name_tmp__55->field0);
  var_name_tmp__57 = *(volatile uint32_t*)var_name_tmp__56;
  *(volatile uint32_t*)var_name_tmp__56 = (var_name_tmp__57 & -17);
  goto var_name_tmp__115;

var_name_tmp__115:
  var_name_tmp__58 = var_name_tmp__10;
  var_name_tmp__59 = *((&var_name_tmp__58->field9));
  if ((((var_name_tmp__59 == 1u)&1))) {
    goto var_name_tmp__116;
  } else {
    goto var_name_tmp__117;
  }

var_name_tmp__116:
  var_name_tmp__60 = var_name_tmp__9;
  var_name_tmp__61 = (&var_name_tmp__60->field0);
  var_name_tmp__62 = *(volatile uint32_t*)var_name_tmp__61;
  *(volatile uint32_t*)var_name_tmp__61 = (var_name_tmp__62 | 8);
  goto var_name_tmp__118;

var_name_tmp__117:
  var_name_tmp__63 = var_name_tmp__9;
  var_name_tmp__64 = (&var_name_tmp__63->field0);
  var_name_tmp__65 = *(volatile uint32_t*)var_name_tmp__64;
  *(volatile uint32_t*)var_name_tmp__64 = (var_name_tmp__65 & -9);
  goto var_name_tmp__118;

var_name_tmp__118:
  var_name_tmp__66 = var_name_tmp__10;
  var_name_tmp__67 = *((&var_name_tmp__66->field10));
  if ((((var_name_tmp__67 == 1u)&1))) {
    goto var_name_tmp__119;
  } else {
    goto var_name_tmp__120;
  }

var_name_tmp__119:
  var_name_tmp__68 = var_name_tmp__9;
  var_name_tmp__69 = (&var_name_tmp__68->field0);
  var_name_tmp__70 = *(volatile uint32_t*)var_name_tmp__69;
  *(volatile uint32_t*)var_name_tmp__69 = (var_name_tmp__70 | 4);
  goto var_name_tmp__121;

var_name_tmp__120:
  var_name_tmp__71 = var_name_tmp__9;
  var_name_tmp__72 = (&var_name_tmp__71->field0);
  var_name_tmp__73 = *(volatile uint32_t*)var_name_tmp__72;
  *(volatile uint32_t*)var_name_tmp__72 = (var_name_tmp__73 & -5);
  goto var_name_tmp__121;

var_name_tmp__121:
  var_name_tmp__74 = var_name_tmp__10;
  var_name_tmp__75 = *((&var_name_tmp__74->field1));
  var_name_tmp__76 = var_name_tmp__10;
  var_name_tmp__77 = *((&var_name_tmp__76->field2));
  var_name_tmp__78 = var_name_tmp__10;
  var_name_tmp__79 = *((&var_name_tmp__78->field3));
  var_name_tmp__80 = var_name_tmp__10;
  var_name_tmp__81 = *((&var_name_tmp__80->field4));
  var_name_tmp__82 = var_name_tmp__10;
  var_name_tmp__83 = *((&var_name_tmp__82->field0));
  var_name_tmp__84 = var_name_tmp__9;
  *(volatile uint32_t*)((&var_name_tmp__84->field7)) = ((((((((uint32_t)(uint8_t)var_name_tmp__75)) << 30) | ((((uint32_t)(uint8_t)var_name_tmp__77)) << 24)) | ((((uint32_t)(uint8_t)var_name_tmp__79)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__81)) << 20)) | (llvm_sub_u32((((uint32_t)(uint16_t)var_name_tmp__83)), 1)));
  var_name_tmp__85 = var_name_tmp__9;
  var_name_tmp__86 = (&var_name_tmp__85->field0);
  var_name_tmp__87 = *(volatile uint32_t*)var_name_tmp__86;
  *(volatile uint32_t*)var_name_tmp__86 = (var_name_tmp__87 & -2);
  var_name_tmp__12 = 0;
  goto var_name_tmp__122;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__122:
  var_name_tmp__88 = var_name_tmp__9;
  var_name_tmp__89 = *(volatile uint32_t*)((&var_name_tmp__88->field1));
  if (((((var_name_tmp__89 & 1) == 1u)&1))) {
    goto var_name_tmp__123;
  } else {
    var_name_tmp__91__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__124;
  }

var_name_tmp__123:
  var_name_tmp__90 = var_name_tmp__12;
  var_name_tmp__91__PHI_TEMPORARY = (((var_name_tmp__90 != 15u)&1));   /* for PHI node */
  goto var_name_tmp__124;

var_name_tmp__124:
  var_name_tmp__91 = ((var_name_tmp__91__PHI_TEMPORARY)&1);
  if (var_name_tmp__91) {
    goto var_name_tmp__125;
  } else {
    goto var_name_tmp__126;
  }

var_name_tmp__125:
  var_name_tmp__92 = var_name_tmp__12;
  var_name_tmp__12 = (llvm_add_u32(var_name_tmp__92, 1));
  goto var_name_tmp__122;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__126:
  var_name_tmp__93 = var_name_tmp__9;
  var_name_tmp__94 = *(volatile uint32_t*)((&var_name_tmp__93->field1));
  if (((((var_name_tmp__94 & 1) == 1u)&1))) {
    goto var_name_tmp__127;
  } else {
    goto var_name_tmp__128;
  }

var_name_tmp__127:
  var_name_tmp__11 = 0;
  goto var_name_tmp__129;

var_name_tmp__128:
  var_name_tmp__11 = 1;
  goto var_name_tmp__129;

var_name_tmp__129:
  goto var_name_tmp__103;

var_name_tmp__103:
  var_name_tmp__95 = var_name_tmp__11;
  return var_name_tmp__95;
}


void CAN_FilterInit(struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__130) {
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__131;    /* Address-exposed local */
  uint32_t var_name_tmp__132;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__133;
  uint8_t var_name_tmp__134;
  uint32_t var_name_tmp__135;
  uint32_t var_name_tmp__136;
  uint32_t var_name_tmp__137;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__138;
  uint8_t var_name_tmp__139;
  uint32_t var_name_tmp__140;
  uint32_t var_name_tmp__141;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__142;
  uint16_t var_name_tmp__143;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__144;
  uint16_t var_name_tmp__145;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__146;
  uint8_t var_name_tmp__147;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__148;
  uint16_t var_name_tmp__149;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__150;
  uint16_t var_name_tmp__151;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__152;
  uint8_t var_name_tmp__153;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__154;
  uint8_t var_name_tmp__155;
  uint32_t var_name_tmp__156;
  uint32_t var_name_tmp__157;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__158;
  uint16_t var_name_tmp__159;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__160;
  uint16_t var_name_tmp__161;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__162;
  uint8_t var_name_tmp__163;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__164;
  uint16_t var_name_tmp__165;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__166;
  uint16_t var_name_tmp__167;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__168;
  uint8_t var_name_tmp__169;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__170;
  uint8_t var_name_tmp__171;
  uint32_t var_name_tmp__172;
  uint32_t var_name_tmp__173;
  uint32_t var_name_tmp__174;
  uint32_t var_name_tmp__175;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__176;
  uint16_t var_name_tmp__177;
  uint32_t var_name_tmp__178;
  uint32_t var_name_tmp__179;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__180;
  uint16_t var_name_tmp__181;
  uint32_t var_name_tmp__182;
  uint32_t var_name_tmp__183;
  struct l_struct_struct_OC_CAN_FilterInitTypeDef* var_name_tmp__184;
  uint32_t var_name_tmp__185;
  uint32_t var_name_tmp__186;
  uint32_t var_name_tmp__187;
  uint32_t var_name_tmp__188;

  var_name_tmp__131 = var_name_tmp__130;
  var_name_tmp__132 = 0;
  var_name_tmp__133 = var_name_tmp__131;
  var_name_tmp__134 = *((&var_name_tmp__133->field5));
  var_name_tmp__132 = (1 << (((uint32_t)(uint8_t)var_name_tmp__134)));
  var_name_tmp__135 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__135 | 1);
  var_name_tmp__136 = var_name_tmp__132;
  var_name_tmp__137 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19)) = (var_name_tmp__137 & (~(var_name_tmp__136)));
  var_name_tmp__138 = var_name_tmp__131;
  var_name_tmp__139 = *((&var_name_tmp__138->field7));
  if (((((((uint32_t)(uint8_t)var_name_tmp__139)) == 0u)&1))) {
    goto var_name_tmp__189;
  } else {
    goto var_name_tmp__190;
  }

var_name_tmp__189:
  var_name_tmp__140 = var_name_tmp__132;
  var_name_tmp__141 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15)) = (var_name_tmp__141 & (~(var_name_tmp__140)));
  var_name_tmp__142 = var_name_tmp__131;
  var_name_tmp__143 = *((&var_name_tmp__142->field3));
  var_name_tmp__144 = var_name_tmp__131;
  var_name_tmp__145 = *((&var_name_tmp__144->field1));
  var_name_tmp__146 = var_name_tmp__131;
  var_name_tmp__147 = *((&var_name_tmp__146->field5));
  *(volatile uint32_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__147)))]))->field0)) = (((65535 & (((uint32_t)(uint16_t)var_name_tmp__143))) << 16) | (65535 & (((uint32_t)(uint16_t)var_name_tmp__145))));
  var_name_tmp__148 = var_name_tmp__131;
  var_name_tmp__149 = *((&var_name_tmp__148->field2));
  var_name_tmp__150 = var_name_tmp__131;
  var_name_tmp__151 = *((&var_name_tmp__150->field0));
  var_name_tmp__152 = var_name_tmp__131;
  var_name_tmp__153 = *((&var_name_tmp__152->field5));
  *(volatile uint32_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__153)))]))->field1)) = (((65535 & (((uint32_t)(uint16_t)var_name_tmp__149))) << 16) | (65535 & (((uint32_t)(uint16_t)var_name_tmp__151))));
  goto var_name_tmp__190;

var_name_tmp__190:
  var_name_tmp__154 = var_name_tmp__131;
  var_name_tmp__155 = *((&var_name_tmp__154->field7));
  if (((((((uint32_t)(uint8_t)var_name_tmp__155)) == 1u)&1))) {
    goto var_name_tmp__191;
  } else {
    goto var_name_tmp__192;
  }

var_name_tmp__191:
  var_name_tmp__156 = var_name_tmp__132;
  var_name_tmp__157 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field15)) = (var_name_tmp__157 | var_name_tmp__156);
  var_name_tmp__158 = var_name_tmp__131;
  var_name_tmp__159 = *((&var_name_tmp__158->field0));
  var_name_tmp__160 = var_name_tmp__131;
  var_name_tmp__161 = *((&var_name_tmp__160->field1));
  var_name_tmp__162 = var_name_tmp__131;
  var_name_tmp__163 = *((&var_name_tmp__162->field5));
  *(volatile uint32_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__163)))]))->field0)) = (((65535 & (((uint32_t)(uint16_t)var_name_tmp__159))) << 16) | (65535 & (((uint32_t)(uint16_t)var_name_tmp__161))));
  var_name_tmp__164 = var_name_tmp__131;
  var_name_tmp__165 = *((&var_name_tmp__164->field2));
  var_name_tmp__166 = var_name_tmp__131;
  var_name_tmp__167 = *((&var_name_tmp__166->field3));
  var_name_tmp__168 = var_name_tmp__131;
  var_name_tmp__169 = *((&var_name_tmp__168->field5));
  *(volatile uint32_t*)((&((&(*((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field21))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__169)))]))->field1)) = (((65535 & (((uint32_t)(uint16_t)var_name_tmp__165))) << 16) | (65535 & (((uint32_t)(uint16_t)var_name_tmp__167))));
  goto var_name_tmp__192;

var_name_tmp__192:
  var_name_tmp__170 = var_name_tmp__131;
  var_name_tmp__171 = *((&var_name_tmp__170->field6));
  if (((((((uint32_t)(uint8_t)var_name_tmp__171)) == 0u)&1))) {
    goto var_name_tmp__193;
  } else {
    goto var_name_tmp__194;
  }

var_name_tmp__193:
  var_name_tmp__172 = var_name_tmp__132;
  var_name_tmp__173 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13)) = (var_name_tmp__173 & (~(var_name_tmp__172)));
  goto var_name_tmp__195;

var_name_tmp__194:
  var_name_tmp__174 = var_name_tmp__132;
  var_name_tmp__175 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field13)) = (var_name_tmp__175 | var_name_tmp__174);
  goto var_name_tmp__195;

var_name_tmp__195:
  var_name_tmp__176 = var_name_tmp__131;
  var_name_tmp__177 = *((&var_name_tmp__176->field4));
  if (((((((uint32_t)(uint16_t)var_name_tmp__177)) == 0u)&1))) {
    goto var_name_tmp__196;
  } else {
    goto var_name_tmp__197;
  }

var_name_tmp__196:
  var_name_tmp__178 = var_name_tmp__132;
  var_name_tmp__179 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17)) = (var_name_tmp__179 & (~(var_name_tmp__178)));
  goto var_name_tmp__197;

var_name_tmp__197:
  var_name_tmp__180 = var_name_tmp__131;
  var_name_tmp__181 = *((&var_name_tmp__180->field4));
  if (((((((uint32_t)(uint16_t)var_name_tmp__181)) == 1u)&1))) {
    goto var_name_tmp__198;
  } else {
    goto var_name_tmp__199;
  }

var_name_tmp__198:
  var_name_tmp__182 = var_name_tmp__132;
  var_name_tmp__183 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field17)) = (var_name_tmp__183 | var_name_tmp__182);
  goto var_name_tmp__199;

var_name_tmp__199:
  var_name_tmp__184 = var_name_tmp__131;
  var_name_tmp__185 = *((&var_name_tmp__184->field8));
  if ((((var_name_tmp__185 == 1u)&1))) {
    goto var_name_tmp__200;
  } else {
    goto var_name_tmp__201;
  }

var_name_tmp__200:
  var_name_tmp__186 = var_name_tmp__132;
  var_name_tmp__187 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field19)) = (var_name_tmp__187 | var_name_tmp__186);
  goto var_name_tmp__201;

var_name_tmp__201:
  var_name_tmp__188 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__188 & -2);
}


void CAN_StructInit(struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__202) {
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__203;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__204;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__205;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__206;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__207;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__208;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__209;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__210;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__211;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__212;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__213;
  struct l_struct_struct_OC_CAN_InitTypeDef* var_name_tmp__214;

  var_name_tmp__203 = var_name_tmp__202;
  var_name_tmp__204 = var_name_tmp__203;
  *((&var_name_tmp__204->field5)) = 0;
  var_name_tmp__205 = var_name_tmp__203;
  *((&var_name_tmp__205->field6)) = 0;
  var_name_tmp__206 = var_name_tmp__203;
  *((&var_name_tmp__206->field7)) = 0;
  var_name_tmp__207 = var_name_tmp__203;
  *((&var_name_tmp__207->field8)) = 0;
  var_name_tmp__208 = var_name_tmp__203;
  *((&var_name_tmp__208->field9)) = 0;
  var_name_tmp__209 = var_name_tmp__203;
  *((&var_name_tmp__209->field10)) = 0;
  var_name_tmp__210 = var_name_tmp__203;
  *((&var_name_tmp__210->field1)) = 0;
  var_name_tmp__211 = var_name_tmp__203;
  *((&var_name_tmp__211->field2)) = 0;
  var_name_tmp__212 = var_name_tmp__203;
  *((&var_name_tmp__212->field3)) = 3;
  var_name_tmp__213 = var_name_tmp__203;
  *((&var_name_tmp__213->field4)) = 2;
  var_name_tmp__214 = var_name_tmp__203;
  *((&var_name_tmp__214->field0)) = 1;
}


void CAN_SlaveStartBank(uint8_t var_name_tmp__215) {
  uint8_t var_name_tmp__216;    /* Address-exposed local */
  uint32_t var_name_tmp__217;
  uint32_t var_name_tmp__218;
  uint8_t var_name_tmp__219;
  uint32_t var_name_tmp__220;
  uint32_t var_name_tmp__221;

  var_name_tmp__216 = var_name_tmp__215;
  var_name_tmp__217 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__217 | 1);
  var_name_tmp__218 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__218 & -16143);
  var_name_tmp__219 = var_name_tmp__216;
  var_name_tmp__220 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__220 | ((((uint32_t)(uint8_t)var_name_tmp__219)) << 8));
  var_name_tmp__221 = *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12));
  *(volatile uint32_t*)((&((struct l_struct_struct_OC_CAN_TypeDef*)(uintptr_t)UINT64_C(1073767424))->field12)) = (var_name_tmp__221 & -2);
}


void CAN_DBGFreeze(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__222, uint32_t var_name_tmp__223) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__224;    /* Address-exposed local */
  uint32_t var_name_tmp__225;    /* Address-exposed local */
  uint32_t var_name_tmp__226;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__227;
  uint32_t* var_name_tmp__228;
  uint32_t var_name_tmp__229;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__230;
  uint32_t* var_name_tmp__231;
  uint32_t var_name_tmp__232;

  var_name_tmp__224 = var_name_tmp__222;
  var_name_tmp__225 = var_name_tmp__223;
  var_name_tmp__226 = var_name_tmp__225;
  if ((((var_name_tmp__226 != 0u)&1))) {
    goto var_name_tmp__233;
  } else {
    goto var_name_tmp__234;
  }

var_name_tmp__233:
  var_name_tmp__227 = var_name_tmp__224;
  var_name_tmp__228 = (&var_name_tmp__227->field0);
  var_name_tmp__229 = *(volatile uint32_t*)var_name_tmp__228;
  *(volatile uint32_t*)var_name_tmp__228 = (var_name_tmp__229 | 65536);
  goto var_name_tmp__235;

var_name_tmp__234:
  var_name_tmp__230 = var_name_tmp__224;
  var_name_tmp__231 = (&var_name_tmp__230->field0);
  var_name_tmp__232 = *(volatile uint32_t*)var_name_tmp__231;
  *(volatile uint32_t*)var_name_tmp__231 = (var_name_tmp__232 & -65537);
  goto var_name_tmp__235;

var_name_tmp__235:
  return;
}


void CAN_TTComModeCmd(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__236, uint32_t var_name_tmp__237) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__238;    /* Address-exposed local */
  uint32_t var_name_tmp__239;    /* Address-exposed local */
  uint32_t var_name_tmp__240;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__241;
  uint32_t* var_name_tmp__242;
  uint32_t var_name_tmp__243;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__244;
  uint32_t* var_name_tmp__245;
  uint32_t var_name_tmp__246;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__247;
  uint32_t* var_name_tmp__248;
  uint32_t var_name_tmp__249;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__250;
  uint32_t* var_name_tmp__251;
  uint32_t var_name_tmp__252;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__253;
  uint32_t* var_name_tmp__254;
  uint32_t var_name_tmp__255;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__256;
  uint32_t* var_name_tmp__257;
  uint32_t var_name_tmp__258;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__259;
  uint32_t* var_name_tmp__260;
  uint32_t var_name_tmp__261;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__262;
  uint32_t* var_name_tmp__263;
  uint32_t var_name_tmp__264;

  var_name_tmp__238 = var_name_tmp__236;
  var_name_tmp__239 = var_name_tmp__237;
  var_name_tmp__240 = var_name_tmp__239;
  if ((((var_name_tmp__240 != 0u)&1))) {
    goto var_name_tmp__265;
  } else {
    goto var_name_tmp__266;
  }

var_name_tmp__265:
  var_name_tmp__241 = var_name_tmp__238;
  var_name_tmp__242 = (&var_name_tmp__241->field0);
  var_name_tmp__243 = *(volatile uint32_t*)var_name_tmp__242;
  *(volatile uint32_t*)var_name_tmp__242 = (var_name_tmp__243 | 128);
  var_name_tmp__244 = var_name_tmp__238;
  var_name_tmp__245 = (&((&(*((&var_name_tmp__244->field9))).array[((int64_t)UINT64_C(0))]))->field1);
  var_name_tmp__246 = *(volatile uint32_t*)var_name_tmp__245;
  *(volatile uint32_t*)var_name_tmp__245 = (var_name_tmp__246 | 256);
  var_name_tmp__247 = var_name_tmp__238;
  var_name_tmp__248 = (&((&(*((&var_name_tmp__247->field9))).array[((int64_t)UINT64_C(1))]))->field1);
  var_name_tmp__249 = *(volatile uint32_t*)var_name_tmp__248;
  *(volatile uint32_t*)var_name_tmp__248 = (var_name_tmp__249 | 256);
  var_name_tmp__250 = var_name_tmp__238;
  var_name_tmp__251 = (&((&(*((&var_name_tmp__250->field9))).array[((int64_t)UINT64_C(2))]))->field1);
  var_name_tmp__252 = *(volatile uint32_t*)var_name_tmp__251;
  *(volatile uint32_t*)var_name_tmp__251 = (var_name_tmp__252 | 256);
  goto var_name_tmp__267;

var_name_tmp__266:
  var_name_tmp__253 = var_name_tmp__238;
  var_name_tmp__254 = (&var_name_tmp__253->field0);
  var_name_tmp__255 = *(volatile uint32_t*)var_name_tmp__254;
  *(volatile uint32_t*)var_name_tmp__254 = (var_name_tmp__255 & -129);
  var_name_tmp__256 = var_name_tmp__238;
  var_name_tmp__257 = (&((&(*((&var_name_tmp__256->field9))).array[((int64_t)UINT64_C(0))]))->field1);
  var_name_tmp__258 = *(volatile uint32_t*)var_name_tmp__257;
  *(volatile uint32_t*)var_name_tmp__257 = (var_name_tmp__258 & -257);
  var_name_tmp__259 = var_name_tmp__238;
  var_name_tmp__260 = (&((&(*((&var_name_tmp__259->field9))).array[((int64_t)UINT64_C(1))]))->field1);
  var_name_tmp__261 = *(volatile uint32_t*)var_name_tmp__260;
  *(volatile uint32_t*)var_name_tmp__260 = (var_name_tmp__261 & -257);
  var_name_tmp__262 = var_name_tmp__238;
  var_name_tmp__263 = (&((&(*((&var_name_tmp__262->field9))).array[((int64_t)UINT64_C(2))]))->field1);
  var_name_tmp__264 = *(volatile uint32_t*)var_name_tmp__263;
  *(volatile uint32_t*)var_name_tmp__263 = (var_name_tmp__264 & -257);
  goto var_name_tmp__267;

var_name_tmp__267:
  return;
}


uint8_t CAN_Transmit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__268, struct l_struct_struct_OC_CanTxMsg* var_name_tmp__269) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__270;    /* Address-exposed local */
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__271;    /* Address-exposed local */
  uint8_t var_name_tmp__272;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__273;
  uint32_t var_name_tmp__274;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__275;
  uint32_t var_name_tmp__276;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__277;
  uint32_t var_name_tmp__278;
  uint8_t var_name_tmp__279;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__280;
  uint8_t var_name_tmp__281;
  uint32_t* var_name_tmp__282;
  uint32_t var_name_tmp__283;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__284;
  uint8_t var_name_tmp__285;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__286;
  uint32_t var_name_tmp__287;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__288;
  uint8_t var_name_tmp__289;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__290;
  uint8_t var_name_tmp__291;
  uint32_t* var_name_tmp__292;
  uint32_t var_name_tmp__293;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__294;
  uint32_t var_name_tmp__295;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__296;
  uint8_t var_name_tmp__297;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__298;
  uint8_t var_name_tmp__299;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__300;
  uint8_t var_name_tmp__301;
  uint32_t* var_name_tmp__302;
  uint32_t var_name_tmp__303;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__304;
  uint8_t* var_name_tmp__305;
  uint8_t var_name_tmp__306;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__307;
  uint8_t var_name_tmp__308;
  uint32_t* var_name_tmp__309;
  uint32_t var_name_tmp__310;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__311;
  uint8_t var_name_tmp__312;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__313;
  uint8_t var_name_tmp__314;
  uint32_t* var_name_tmp__315;
  uint32_t var_name_tmp__316;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__317;
  uint8_t var_name_tmp__318;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__319;
  uint8_t var_name_tmp__320;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__321;
  uint8_t var_name_tmp__322;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__323;
  uint8_t var_name_tmp__324;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__325;
  uint8_t var_name_tmp__326;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__327;
  uint8_t var_name_tmp__328;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__329;
  uint8_t var_name_tmp__330;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__331;
  uint8_t var_name_tmp__332;
  struct l_struct_struct_OC_CanTxMsg* var_name_tmp__333;
  uint8_t var_name_tmp__334;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__335;
  uint8_t var_name_tmp__336;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__337;
  uint8_t var_name_tmp__338;
  uint32_t* var_name_tmp__339;
  uint32_t var_name_tmp__340;
  uint8_t var_name_tmp__341;

  var_name_tmp__270 = var_name_tmp__268;
  var_name_tmp__271 = var_name_tmp__269;
  var_name_tmp__272 = 0;
  var_name_tmp__273 = var_name_tmp__270;
  var_name_tmp__274 = *(volatile uint32_t*)((&var_name_tmp__273->field2));
  if (((((var_name_tmp__274 & 67108864) == 67108864u)&1))) {
    goto var_name_tmp__342;
  } else {
    goto var_name_tmp__343;
  }

var_name_tmp__342:
  var_name_tmp__272 = 0;
  goto var_name_tmp__344;

var_name_tmp__343:
  var_name_tmp__275 = var_name_tmp__270;
  var_name_tmp__276 = *(volatile uint32_t*)((&var_name_tmp__275->field2));
  if (((((var_name_tmp__276 & 134217728) == 134217728u)&1))) {
    goto var_name_tmp__345;
  } else {
    goto var_name_tmp__346;
  }

var_name_tmp__345:
  var_name_tmp__272 = 1;
  goto var_name_tmp__347;

var_name_tmp__346:
  var_name_tmp__277 = var_name_tmp__270;
  var_name_tmp__278 = *(volatile uint32_t*)((&var_name_tmp__277->field2));
  if (((((var_name_tmp__278 & 268435456) == 268435456u)&1))) {
    goto var_name_tmp__348;
  } else {
    goto var_name_tmp__349;
  }

var_name_tmp__348:
  var_name_tmp__272 = 2;
  goto var_name_tmp__350;

var_name_tmp__349:
  var_name_tmp__272 = 4;
  goto var_name_tmp__350;

var_name_tmp__350:
  goto var_name_tmp__347;

var_name_tmp__347:
  goto var_name_tmp__344;

var_name_tmp__344:
  var_name_tmp__279 = var_name_tmp__272;
  if (((((((uint32_t)(uint8_t)var_name_tmp__279)) != 4u)&1))) {
    goto var_name_tmp__351;
  } else {
    goto var_name_tmp__352;
  }

var_name_tmp__351:
  var_name_tmp__280 = var_name_tmp__270;
  var_name_tmp__281 = var_name_tmp__272;
  var_name_tmp__282 = (&((&(*((&var_name_tmp__280->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__281)))]))->field0);
  var_name_tmp__283 = *(volatile uint32_t*)var_name_tmp__282;
  *(volatile uint32_t*)var_name_tmp__282 = (var_name_tmp__283 & 1);
  var_name_tmp__284 = var_name_tmp__271;
  var_name_tmp__285 = *((&var_name_tmp__284->field2));
  if (((((((uint32_t)(uint8_t)var_name_tmp__285)) == 0u)&1))) {
    goto var_name_tmp__353;
  } else {
    goto var_name_tmp__354;
  }

var_name_tmp__353:
  var_name_tmp__286 = var_name_tmp__271;
  var_name_tmp__287 = *((&var_name_tmp__286->field0));
  var_name_tmp__288 = var_name_tmp__271;
  var_name_tmp__289 = *((&var_name_tmp__288->field3));
  var_name_tmp__290 = var_name_tmp__270;
  var_name_tmp__291 = var_name_tmp__272;
  var_name_tmp__292 = (&((&(*((&var_name_tmp__290->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__291)))]))->field0);
  var_name_tmp__293 = *(volatile uint32_t*)var_name_tmp__292;
  *(volatile uint32_t*)var_name_tmp__292 = (var_name_tmp__293 | ((var_name_tmp__287 << 21) | (((uint32_t)(uint8_t)var_name_tmp__289))));
  goto var_name_tmp__355;

var_name_tmp__354:
  var_name_tmp__294 = var_name_tmp__271;
  var_name_tmp__295 = *((&var_name_tmp__294->field1));
  var_name_tmp__296 = var_name_tmp__271;
  var_name_tmp__297 = *((&var_name_tmp__296->field2));
  var_name_tmp__298 = var_name_tmp__271;
  var_name_tmp__299 = *((&var_name_tmp__298->field3));
  var_name_tmp__300 = var_name_tmp__270;
  var_name_tmp__301 = var_name_tmp__272;
  var_name_tmp__302 = (&((&(*((&var_name_tmp__300->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__301)))]))->field0);
  var_name_tmp__303 = *(volatile uint32_t*)var_name_tmp__302;
  *(volatile uint32_t*)var_name_tmp__302 = (var_name_tmp__303 | (((var_name_tmp__295 << 3) | (((uint32_t)(uint8_t)var_name_tmp__297))) | (((uint32_t)(uint8_t)var_name_tmp__299))));
  goto var_name_tmp__355;

var_name_tmp__355:
  var_name_tmp__304 = var_name_tmp__271;
  var_name_tmp__305 = (&var_name_tmp__304->field4);
  var_name_tmp__306 = *var_name_tmp__305;
  *var_name_tmp__305 = (((uint8_t)((((uint32_t)(uint8_t)var_name_tmp__306)) & 15)));
  var_name_tmp__307 = var_name_tmp__270;
  var_name_tmp__308 = var_name_tmp__272;
  var_name_tmp__309 = (&((&(*((&var_name_tmp__307->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__308)))]))->field1);
  var_name_tmp__310 = *(volatile uint32_t*)var_name_tmp__309;
  *(volatile uint32_t*)var_name_tmp__309 = (var_name_tmp__310 & -16);
  var_name_tmp__311 = var_name_tmp__271;
  var_name_tmp__312 = *((&var_name_tmp__311->field4));
  var_name_tmp__313 = var_name_tmp__270;
  var_name_tmp__314 = var_name_tmp__272;
  var_name_tmp__315 = (&((&(*((&var_name_tmp__313->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__314)))]))->field1);
  var_name_tmp__316 = *(volatile uint32_t*)var_name_tmp__315;
  *(volatile uint32_t*)var_name_tmp__315 = (var_name_tmp__316 | (((uint32_t)(uint8_t)var_name_tmp__312)));
  var_name_tmp__317 = var_name_tmp__271;
  var_name_tmp__318 = *((&(*((&var_name_tmp__317->field5))).array[((int64_t)UINT64_C(3))]));
  var_name_tmp__319 = var_name_tmp__271;
  var_name_tmp__320 = *((&(*((&var_name_tmp__319->field5))).array[((int64_t)UINT64_C(2))]));
  var_name_tmp__321 = var_name_tmp__271;
  var_name_tmp__322 = *((&(*((&var_name_tmp__321->field5))).array[((int64_t)UINT64_C(1))]));
  var_name_tmp__323 = var_name_tmp__271;
  var_name_tmp__324 = *((&(*((&var_name_tmp__323->field5))).array[((int64_t)UINT64_C(0))]));
  var_name_tmp__325 = var_name_tmp__270;
  var_name_tmp__326 = var_name_tmp__272;
  *(volatile uint32_t*)((&((&(*((&var_name_tmp__325->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__326)))]))->field2)) = (((((((uint32_t)(uint8_t)var_name_tmp__318)) << 24) | ((((uint32_t)(uint8_t)var_name_tmp__320)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__322)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__324)));
  var_name_tmp__327 = var_name_tmp__271;
  var_name_tmp__328 = *((&(*((&var_name_tmp__327->field5))).array[((int64_t)UINT64_C(7))]));
  var_name_tmp__329 = var_name_tmp__271;
  var_name_tmp__330 = *((&(*((&var_name_tmp__329->field5))).array[((int64_t)UINT64_C(6))]));
  var_name_tmp__331 = var_name_tmp__271;
  var_name_tmp__332 = *((&(*((&var_name_tmp__331->field5))).array[((int64_t)UINT64_C(5))]));
  var_name_tmp__333 = var_name_tmp__271;
  var_name_tmp__334 = *((&(*((&var_name_tmp__333->field5))).array[((int64_t)UINT64_C(4))]));
  var_name_tmp__335 = var_name_tmp__270;
  var_name_tmp__336 = var_name_tmp__272;
  *(volatile uint32_t*)((&((&(*((&var_name_tmp__335->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__336)))]))->field3)) = (((((((uint32_t)(uint8_t)var_name_tmp__328)) << 24) | ((((uint32_t)(uint8_t)var_name_tmp__330)) << 16)) | ((((uint32_t)(uint8_t)var_name_tmp__332)) << 8)) | (((uint32_t)(uint8_t)var_name_tmp__334)));
  var_name_tmp__337 = var_name_tmp__270;
  var_name_tmp__338 = var_name_tmp__272;
  var_name_tmp__339 = (&((&(*((&var_name_tmp__337->field9))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__338)))]))->field0);
  var_name_tmp__340 = *(volatile uint32_t*)var_name_tmp__339;
  *(volatile uint32_t*)var_name_tmp__339 = (var_name_tmp__340 | 1);
  goto var_name_tmp__352;

var_name_tmp__352:
  var_name_tmp__341 = var_name_tmp__272;
  return var_name_tmp__341;
}


uint8_t CAN_TransmitStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__356, uint8_t var_name_tmp__357) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__358;    /* Address-exposed local */
  uint8_t var_name_tmp__359;    /* Address-exposed local */
  uint32_t var_name_tmp__360;    /* Address-exposed local */
  uint8_t var_name_tmp__361;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__362;
  uint32_t var_name_tmp__363;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__364;
  uint32_t var_name_tmp__365;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__366;
  uint32_t var_name_tmp__367;
  uint32_t var_name_tmp__368;
  uint32_t var_name_tmp__369;

  var_name_tmp__358 = var_name_tmp__356;
  var_name_tmp__359 = var_name_tmp__357;
  var_name_tmp__360 = 0;
  var_name_tmp__361 = var_name_tmp__359;
  switch ((((uint32_t)(uint8_t)var_name_tmp__361))) {
  default:
    goto var_name_tmp__370;
  case 0u:
    goto var_name_tmp__371;
  case 1u:
    goto var_name_tmp__372;
  case 2u:
    goto var_name_tmp__373;
  }

var_name_tmp__371:
  var_name_tmp__362 = var_name_tmp__358;
  var_name_tmp__363 = *(volatile uint32_t*)((&var_name_tmp__362->field2));
  var_name_tmp__360 = (var_name_tmp__363 & 67108867);
  goto var_name_tmp__374;

var_name_tmp__372:
  var_name_tmp__364 = var_name_tmp__358;
  var_name_tmp__365 = *(volatile uint32_t*)((&var_name_tmp__364->field2));
  var_name_tmp__360 = (var_name_tmp__365 & 134218496);
  goto var_name_tmp__374;

var_name_tmp__373:
  var_name_tmp__366 = var_name_tmp__358;
  var_name_tmp__367 = *(volatile uint32_t*)((&var_name_tmp__366->field2));
  var_name_tmp__360 = (var_name_tmp__367 & 268632064);
  goto var_name_tmp__374;

var_name_tmp__370:
  var_name_tmp__360 = 0;
  goto var_name_tmp__374;

var_name_tmp__374:
  var_name_tmp__368 = var_name_tmp__360;
  switch (var_name_tmp__368) {
  default:
    goto var_name_tmp__375;
  case 0u:
    goto var_name_tmp__376;
  case 67108865u:
    goto var_name_tmp__377;
  case 134217984u:
    goto var_name_tmp__378;
  case 268500992u:
    goto var_name_tmp__379;
  case 67108867u:
    goto var_name_tmp__380;
  case 134218496u:
    goto var_name_tmp__381;
  case 268632064u:
    goto var_name_tmp__382;
  }

var_name_tmp__376:
  var_name_tmp__360 = 2;
  goto var_name_tmp__383;

var_name_tmp__377:
  var_name_tmp__360 = 0;
  goto var_name_tmp__383;

var_name_tmp__378:
  var_name_tmp__360 = 0;
  goto var_name_tmp__383;

var_name_tmp__379:
  var_name_tmp__360 = 0;
  goto var_name_tmp__383;

var_name_tmp__380:
  var_name_tmp__360 = 1;
  goto var_name_tmp__383;

var_name_tmp__381:
  var_name_tmp__360 = 1;
  goto var_name_tmp__383;

var_name_tmp__382:
  var_name_tmp__360 = 1;
  goto var_name_tmp__383;

var_name_tmp__375:
  var_name_tmp__360 = 0;
  goto var_name_tmp__383;

var_name_tmp__383:
  var_name_tmp__369 = var_name_tmp__360;
  return (((uint8_t)var_name_tmp__369));
}


void CAN_CancelTransmit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__384, uint8_t var_name_tmp__385) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__386;    /* Address-exposed local */
  uint8_t var_name_tmp__387;    /* Address-exposed local */
  uint8_t var_name_tmp__388;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__389;
  uint32_t* var_name_tmp__390;
  uint32_t var_name_tmp__391;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__392;
  uint32_t* var_name_tmp__393;
  uint32_t var_name_tmp__394;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__395;
  uint32_t* var_name_tmp__396;
  uint32_t var_name_tmp__397;

  var_name_tmp__386 = var_name_tmp__384;
  var_name_tmp__387 = var_name_tmp__385;
  var_name_tmp__388 = var_name_tmp__387;
  switch ((((uint32_t)(uint8_t)var_name_tmp__388))) {
  default:
    goto var_name_tmp__398;
  case 0u:
    goto var_name_tmp__399;
  case 1u:
    goto var_name_tmp__400;
  case 2u:
    goto var_name_tmp__401;
  }

var_name_tmp__399:
  var_name_tmp__389 = var_name_tmp__386;
  var_name_tmp__390 = (&var_name_tmp__389->field2);
  var_name_tmp__391 = *(volatile uint32_t*)var_name_tmp__390;
  *(volatile uint32_t*)var_name_tmp__390 = (var_name_tmp__391 | 128);
  goto var_name_tmp__402;

var_name_tmp__400:
  var_name_tmp__392 = var_name_tmp__386;
  var_name_tmp__393 = (&var_name_tmp__392->field2);
  var_name_tmp__394 = *(volatile uint32_t*)var_name_tmp__393;
  *(volatile uint32_t*)var_name_tmp__393 = (var_name_tmp__394 | 32768);
  goto var_name_tmp__402;

var_name_tmp__401:
  var_name_tmp__395 = var_name_tmp__386;
  var_name_tmp__396 = (&var_name_tmp__395->field2);
  var_name_tmp__397 = *(volatile uint32_t*)var_name_tmp__396;
  *(volatile uint32_t*)var_name_tmp__396 = (var_name_tmp__397 | 8388608);
  goto var_name_tmp__402;

var_name_tmp__398:
  goto var_name_tmp__402;

var_name_tmp__402:
  return;
}


void CAN_Receive(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__403, uint8_t var_name_tmp__404, struct l_struct_struct_OC_CanRxMsg* var_name_tmp__405) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__406;    /* Address-exposed local */
  uint8_t var_name_tmp__407;    /* Address-exposed local */
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__408;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__409;
  uint8_t var_name_tmp__410;
  uint32_t var_name_tmp__411;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__412;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__413;
  uint8_t var_name_tmp__414;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__415;
  uint8_t var_name_tmp__416;
  uint32_t var_name_tmp__417;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__418;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__419;
  uint8_t var_name_tmp__420;
  uint32_t var_name_tmp__421;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__422;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__423;
  uint8_t var_name_tmp__424;
  uint32_t var_name_tmp__425;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__426;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__427;
  uint8_t var_name_tmp__428;
  uint32_t var_name_tmp__429;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__430;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__431;
  uint8_t var_name_tmp__432;
  uint32_t var_name_tmp__433;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__434;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__435;
  uint8_t var_name_tmp__436;
  uint32_t var_name_tmp__437;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__438;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__439;
  uint8_t var_name_tmp__440;
  uint32_t var_name_tmp__441;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__442;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__443;
  uint8_t var_name_tmp__444;
  uint32_t var_name_tmp__445;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__446;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__447;
  uint8_t var_name_tmp__448;
  uint32_t var_name_tmp__449;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__450;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__451;
  uint8_t var_name_tmp__452;
  uint32_t var_name_tmp__453;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__454;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__455;
  uint8_t var_name_tmp__456;
  uint32_t var_name_tmp__457;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__458;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__459;
  uint8_t var_name_tmp__460;
  uint32_t var_name_tmp__461;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__462;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__463;
  uint8_t var_name_tmp__464;
  uint32_t var_name_tmp__465;
  struct l_struct_struct_OC_CanRxMsg* var_name_tmp__466;
  uint8_t var_name_tmp__467;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__468;
  uint32_t* var_name_tmp__469;
  uint32_t var_name_tmp__470;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__471;
  uint32_t* var_name_tmp__472;
  uint32_t var_name_tmp__473;

  var_name_tmp__406 = var_name_tmp__403;
  var_name_tmp__407 = var_name_tmp__404;
  var_name_tmp__408 = var_name_tmp__405;
  var_name_tmp__409 = var_name_tmp__406;
  var_name_tmp__410 = var_name_tmp__407;
  var_name_tmp__411 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__409->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__410)))]))->field0));
  var_name_tmp__412 = var_name_tmp__408;
  *((&var_name_tmp__412->field2)) = (((uint8_t)(4 & var_name_tmp__411)));
  var_name_tmp__413 = var_name_tmp__408;
  var_name_tmp__414 = *((&var_name_tmp__413->field2));
  if (((((((uint32_t)(uint8_t)var_name_tmp__414)) == 0u)&1))) {
    goto var_name_tmp__474;
  } else {
    goto var_name_tmp__475;
  }

var_name_tmp__474:
  var_name_tmp__415 = var_name_tmp__406;
  var_name_tmp__416 = var_name_tmp__407;
  var_name_tmp__417 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__415->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__416)))]))->field0));
  var_name_tmp__418 = var_name_tmp__408;
  *((&var_name_tmp__418->field0)) = (2047 & (llvm_lshr_u32(var_name_tmp__417, 21)));
  goto var_name_tmp__476;

var_name_tmp__475:
  var_name_tmp__419 = var_name_tmp__406;
  var_name_tmp__420 = var_name_tmp__407;
  var_name_tmp__421 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__419->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__420)))]))->field0));
  var_name_tmp__422 = var_name_tmp__408;
  *((&var_name_tmp__422->field1)) = (536870911 & (llvm_lshr_u32(var_name_tmp__421, 3)));
  goto var_name_tmp__476;

var_name_tmp__476:
  var_name_tmp__423 = var_name_tmp__406;
  var_name_tmp__424 = var_name_tmp__407;
  var_name_tmp__425 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__423->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__424)))]))->field0));
  var_name_tmp__426 = var_name_tmp__408;
  *((&var_name_tmp__426->field3)) = (((uint8_t)(2 & var_name_tmp__425)));
  var_name_tmp__427 = var_name_tmp__406;
  var_name_tmp__428 = var_name_tmp__407;
  var_name_tmp__429 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__427->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__428)))]))->field1));
  var_name_tmp__430 = var_name_tmp__408;
  *((&var_name_tmp__430->field4)) = (((uint8_t)(15 & var_name_tmp__429)));
  var_name_tmp__431 = var_name_tmp__406;
  var_name_tmp__432 = var_name_tmp__407;
  var_name_tmp__433 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__431->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__432)))]))->field1));
  var_name_tmp__434 = var_name_tmp__408;
  *((&var_name_tmp__434->field6)) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__433, 8)))));
  var_name_tmp__435 = var_name_tmp__406;
  var_name_tmp__436 = var_name_tmp__407;
  var_name_tmp__437 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__435->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__436)))]))->field2));
  var_name_tmp__438 = var_name_tmp__408;
  *((&(*((&var_name_tmp__438->field5))).array[((int64_t)UINT64_C(0))])) = (((uint8_t)(255 & var_name_tmp__437)));
  var_name_tmp__439 = var_name_tmp__406;
  var_name_tmp__440 = var_name_tmp__407;
  var_name_tmp__441 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__439->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__440)))]))->field2));
  var_name_tmp__442 = var_name_tmp__408;
  *((&(*((&var_name_tmp__442->field5))).array[((int64_t)UINT64_C(1))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__441, 8)))));
  var_name_tmp__443 = var_name_tmp__406;
  var_name_tmp__444 = var_name_tmp__407;
  var_name_tmp__445 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__443->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__444)))]))->field2));
  var_name_tmp__446 = var_name_tmp__408;
  *((&(*((&var_name_tmp__446->field5))).array[((int64_t)UINT64_C(2))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__445, 16)))));
  var_name_tmp__447 = var_name_tmp__406;
  var_name_tmp__448 = var_name_tmp__407;
  var_name_tmp__449 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__447->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__448)))]))->field2));
  var_name_tmp__450 = var_name_tmp__408;
  *((&(*((&var_name_tmp__450->field5))).array[((int64_t)UINT64_C(3))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__449, 24)))));
  var_name_tmp__451 = var_name_tmp__406;
  var_name_tmp__452 = var_name_tmp__407;
  var_name_tmp__453 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__451->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__452)))]))->field3));
  var_name_tmp__454 = var_name_tmp__408;
  *((&(*((&var_name_tmp__454->field5))).array[((int64_t)UINT64_C(4))])) = (((uint8_t)(255 & var_name_tmp__453)));
  var_name_tmp__455 = var_name_tmp__406;
  var_name_tmp__456 = var_name_tmp__407;
  var_name_tmp__457 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__455->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__456)))]))->field3));
  var_name_tmp__458 = var_name_tmp__408;
  *((&(*((&var_name_tmp__458->field5))).array[((int64_t)UINT64_C(5))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__457, 8)))));
  var_name_tmp__459 = var_name_tmp__406;
  var_name_tmp__460 = var_name_tmp__407;
  var_name_tmp__461 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__459->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__460)))]))->field3));
  var_name_tmp__462 = var_name_tmp__408;
  *((&(*((&var_name_tmp__462->field5))).array[((int64_t)UINT64_C(6))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__461, 16)))));
  var_name_tmp__463 = var_name_tmp__406;
  var_name_tmp__464 = var_name_tmp__407;
  var_name_tmp__465 = *(volatile uint32_t*)((&((&(*((&var_name_tmp__463->field10))).array[((int64_t)(((uint64_t)(uint8_t)var_name_tmp__464)))]))->field3));
  var_name_tmp__466 = var_name_tmp__408;
  *((&(*((&var_name_tmp__466->field5))).array[((int64_t)UINT64_C(7))])) = (((uint8_t)(255 & (llvm_lshr_u32(var_name_tmp__465, 24)))));
  var_name_tmp__467 = var_name_tmp__407;
  if (((((((uint32_t)(uint8_t)var_name_tmp__467)) == 0u)&1))) {
    goto var_name_tmp__477;
  } else {
    goto var_name_tmp__478;
  }

var_name_tmp__477:
  var_name_tmp__468 = var_name_tmp__406;
  var_name_tmp__469 = (&var_name_tmp__468->field3);
  var_name_tmp__470 = *(volatile uint32_t*)var_name_tmp__469;
  *(volatile uint32_t*)var_name_tmp__469 = (var_name_tmp__470 | 32);
  goto var_name_tmp__479;

var_name_tmp__478:
  var_name_tmp__471 = var_name_tmp__406;
  var_name_tmp__472 = (&var_name_tmp__471->field4);
  var_name_tmp__473 = *(volatile uint32_t*)var_name_tmp__472;
  *(volatile uint32_t*)var_name_tmp__472 = (var_name_tmp__473 | 32);
  goto var_name_tmp__479;

var_name_tmp__479:
  return;
}


void CAN_FIFORelease(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__480, uint8_t var_name_tmp__481) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__482;    /* Address-exposed local */
  uint8_t var_name_tmp__483;    /* Address-exposed local */
  uint8_t var_name_tmp__484;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__485;
  uint32_t* var_name_tmp__486;
  uint32_t var_name_tmp__487;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__488;
  uint32_t* var_name_tmp__489;
  uint32_t var_name_tmp__490;

  var_name_tmp__482 = var_name_tmp__480;
  var_name_tmp__483 = var_name_tmp__481;
  var_name_tmp__484 = var_name_tmp__483;
  if (((((((uint32_t)(uint8_t)var_name_tmp__484)) == 0u)&1))) {
    goto var_name_tmp__491;
  } else {
    goto var_name_tmp__492;
  }

var_name_tmp__491:
  var_name_tmp__485 = var_name_tmp__482;
  var_name_tmp__486 = (&var_name_tmp__485->field3);
  var_name_tmp__487 = *(volatile uint32_t*)var_name_tmp__486;
  *(volatile uint32_t*)var_name_tmp__486 = (var_name_tmp__487 | 32);
  goto var_name_tmp__493;

var_name_tmp__492:
  var_name_tmp__488 = var_name_tmp__482;
  var_name_tmp__489 = (&var_name_tmp__488->field4);
  var_name_tmp__490 = *(volatile uint32_t*)var_name_tmp__489;
  *(volatile uint32_t*)var_name_tmp__489 = (var_name_tmp__490 | 32);
  goto var_name_tmp__493;

var_name_tmp__493:
  return;
}


uint8_t CAN_MessagePending(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__494, uint8_t var_name_tmp__495) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__496;    /* Address-exposed local */
  uint8_t var_name_tmp__497;    /* Address-exposed local */
  uint8_t var_name_tmp__498;    /* Address-exposed local */
  uint8_t var_name_tmp__499;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__500;
  uint32_t var_name_tmp__501;
  uint8_t var_name_tmp__502;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__503;
  uint32_t var_name_tmp__504;
  uint8_t var_name_tmp__505;

  var_name_tmp__496 = var_name_tmp__494;
  var_name_tmp__497 = var_name_tmp__495;
  var_name_tmp__498 = 0;
  var_name_tmp__499 = var_name_tmp__497;
  if (((((((uint32_t)(uint8_t)var_name_tmp__499)) == 0u)&1))) {
    goto var_name_tmp__506;
  } else {
    goto var_name_tmp__507;
  }

var_name_tmp__506:
  var_name_tmp__500 = var_name_tmp__496;
  var_name_tmp__501 = *(volatile uint32_t*)((&var_name_tmp__500->field3));
  var_name_tmp__498 = (((uint8_t)(var_name_tmp__501 & 3)));
  goto var_name_tmp__508;

var_name_tmp__507:
  var_name_tmp__502 = var_name_tmp__497;
  if (((((((uint32_t)(uint8_t)var_name_tmp__502)) == 1u)&1))) {
    goto var_name_tmp__509;
  } else {
    goto var_name_tmp__510;
  }

var_name_tmp__509:
  var_name_tmp__503 = var_name_tmp__496;
  var_name_tmp__504 = *(volatile uint32_t*)((&var_name_tmp__503->field4));
  var_name_tmp__498 = (((uint8_t)(var_name_tmp__504 & 3)));
  goto var_name_tmp__511;

var_name_tmp__510:
  var_name_tmp__498 = 0;
  goto var_name_tmp__511;

var_name_tmp__511:
  goto var_name_tmp__508;

var_name_tmp__508:
  var_name_tmp__505 = var_name_tmp__498;
  return var_name_tmp__505;
}


uint8_t CAN_OperatingModeRequest(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__512, uint8_t var_name_tmp__513) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__514;    /* Address-exposed local */
  uint8_t var_name_tmp__515;    /* Address-exposed local */
  uint8_t var_name_tmp__516;    /* Address-exposed local */
  uint32_t var_name_tmp__517;    /* Address-exposed local */
  uint8_t var_name_tmp__518;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__519;
  uint32_t var_name_tmp__520;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__521;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__522;
  uint32_t var_name_tmp__523;
  uint32_t var_name_tmp__524;
  bool var_name_tmp__525;
  bool var_name_tmp__525__PHI_TEMPORARY;
  uint32_t var_name_tmp__526;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__527;
  uint32_t var_name_tmp__528;
  uint8_t var_name_tmp__529;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__530;
  uint32_t* var_name_tmp__531;
  uint32_t var_name_tmp__532;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__533;
  uint32_t var_name_tmp__534;
  uint32_t var_name_tmp__535;
  bool var_name_tmp__536;
  bool var_name_tmp__536__PHI_TEMPORARY;
  uint32_t var_name_tmp__537;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__538;
  uint32_t var_name_tmp__539;
  uint8_t var_name_tmp__540;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__541;
  uint32_t var_name_tmp__542;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__543;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__544;
  uint32_t var_name_tmp__545;
  uint32_t var_name_tmp__546;
  bool var_name_tmp__547;
  bool var_name_tmp__547__PHI_TEMPORARY;
  uint32_t var_name_tmp__548;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__549;
  uint32_t var_name_tmp__550;
  uint8_t var_name_tmp__551;

  var_name_tmp__514 = var_name_tmp__512;
  var_name_tmp__515 = var_name_tmp__513;
  var_name_tmp__516 = 0;
  var_name_tmp__517 = 15;
  var_name_tmp__518 = var_name_tmp__515;
  if (((((((uint32_t)(uint8_t)var_name_tmp__518)) == 0u)&1))) {
    goto var_name_tmp__552;
  } else {
    goto var_name_tmp__553;
  }

var_name_tmp__552:
  var_name_tmp__519 = var_name_tmp__514;
  var_name_tmp__520 = *(volatile uint32_t*)((&var_name_tmp__519->field0));
  var_name_tmp__521 = var_name_tmp__514;
  *(volatile uint32_t*)((&var_name_tmp__521->field0)) = ((var_name_tmp__520 & -3) | 1);
  goto var_name_tmp__554;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__554:
  var_name_tmp__522 = var_name_tmp__514;
  var_name_tmp__523 = *(volatile uint32_t*)((&var_name_tmp__522->field1));
  if (((((var_name_tmp__523 & 3) != 1u)&1))) {
    goto var_name_tmp__555;
  } else {
    var_name_tmp__525__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__556;
  }

var_name_tmp__555:
  var_name_tmp__524 = var_name_tmp__517;
  var_name_tmp__525__PHI_TEMPORARY = (((var_name_tmp__524 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__556;

var_name_tmp__556:
  var_name_tmp__525 = ((var_name_tmp__525__PHI_TEMPORARY)&1);
  if (var_name_tmp__525) {
    goto var_name_tmp__557;
  } else {
    goto var_name_tmp__558;
  }

var_name_tmp__557:
  var_name_tmp__526 = var_name_tmp__517;
  var_name_tmp__517 = (llvm_add_u32(var_name_tmp__526, -1));
  goto var_name_tmp__554;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__558:
  var_name_tmp__527 = var_name_tmp__514;
  var_name_tmp__528 = *(volatile uint32_t*)((&var_name_tmp__527->field1));
  if (((((var_name_tmp__528 & 3) != 1u)&1))) {
    goto var_name_tmp__559;
  } else {
    goto var_name_tmp__560;
  }

var_name_tmp__559:
  var_name_tmp__516 = 0;
  goto var_name_tmp__561;

var_name_tmp__560:
  var_name_tmp__516 = 1;
  goto var_name_tmp__561;

var_name_tmp__561:
  goto var_name_tmp__562;

var_name_tmp__553:
  var_name_tmp__529 = var_name_tmp__515;
  if (((((((uint32_t)(uint8_t)var_name_tmp__529)) == 1u)&1))) {
    goto var_name_tmp__563;
  } else {
    goto var_name_tmp__564;
  }

var_name_tmp__563:
  var_name_tmp__530 = var_name_tmp__514;
  var_name_tmp__531 = (&var_name_tmp__530->field0);
  var_name_tmp__532 = *(volatile uint32_t*)var_name_tmp__531;
  *(volatile uint32_t*)var_name_tmp__531 = (var_name_tmp__532 & -4);
  goto var_name_tmp__565;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__565:
  var_name_tmp__533 = var_name_tmp__514;
  var_name_tmp__534 = *(volatile uint32_t*)((&var_name_tmp__533->field1));
  if (((((var_name_tmp__534 & 3) != 0u)&1))) {
    goto var_name_tmp__566;
  } else {
    var_name_tmp__536__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__567;
  }

var_name_tmp__566:
  var_name_tmp__535 = var_name_tmp__517;
  var_name_tmp__536__PHI_TEMPORARY = (((var_name_tmp__535 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__567;

var_name_tmp__567:
  var_name_tmp__536 = ((var_name_tmp__536__PHI_TEMPORARY)&1);
  if (var_name_tmp__536) {
    goto var_name_tmp__568;
  } else {
    goto var_name_tmp__569;
  }

var_name_tmp__568:
  var_name_tmp__537 = var_name_tmp__517;
  var_name_tmp__517 = (llvm_add_u32(var_name_tmp__537, -1));
  goto var_name_tmp__565;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__569:
  var_name_tmp__538 = var_name_tmp__514;
  var_name_tmp__539 = *(volatile uint32_t*)((&var_name_tmp__538->field1));
  if (((((var_name_tmp__539 & 3) != 0u)&1))) {
    goto var_name_tmp__570;
  } else {
    goto var_name_tmp__571;
  }

var_name_tmp__570:
  var_name_tmp__516 = 0;
  goto var_name_tmp__572;

var_name_tmp__571:
  var_name_tmp__516 = 1;
  goto var_name_tmp__572;

var_name_tmp__572:
  goto var_name_tmp__573;

var_name_tmp__564:
  var_name_tmp__540 = var_name_tmp__515;
  if (((((((uint32_t)(uint8_t)var_name_tmp__540)) == 2u)&1))) {
    goto var_name_tmp__574;
  } else {
    goto var_name_tmp__575;
  }

var_name_tmp__574:
  var_name_tmp__541 = var_name_tmp__514;
  var_name_tmp__542 = *(volatile uint32_t*)((&var_name_tmp__541->field0));
  var_name_tmp__543 = var_name_tmp__514;
  *(volatile uint32_t*)((&var_name_tmp__543->field0)) = ((var_name_tmp__542 & -2) | 2);
  goto var_name_tmp__576;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__576:
  var_name_tmp__544 = var_name_tmp__514;
  var_name_tmp__545 = *(volatile uint32_t*)((&var_name_tmp__544->field1));
  if (((((var_name_tmp__545 & 3) != 2u)&1))) {
    goto var_name_tmp__577;
  } else {
    var_name_tmp__547__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__578;
  }

var_name_tmp__577:
  var_name_tmp__546 = var_name_tmp__517;
  var_name_tmp__547__PHI_TEMPORARY = (((var_name_tmp__546 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__578;

var_name_tmp__578:
  var_name_tmp__547 = ((var_name_tmp__547__PHI_TEMPORARY)&1);
  if (var_name_tmp__547) {
    goto var_name_tmp__579;
  } else {
    goto var_name_tmp__580;
  }

var_name_tmp__579:
  var_name_tmp__548 = var_name_tmp__517;
  var_name_tmp__517 = (llvm_add_u32(var_name_tmp__548, -1));
  goto var_name_tmp__576;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__580:
  var_name_tmp__549 = var_name_tmp__514;
  var_name_tmp__550 = *(volatile uint32_t*)((&var_name_tmp__549->field1));
  if (((((var_name_tmp__550 & 3) != 2u)&1))) {
    goto var_name_tmp__581;
  } else {
    goto var_name_tmp__582;
  }

var_name_tmp__581:
  var_name_tmp__516 = 0;
  goto var_name_tmp__583;

var_name_tmp__582:
  var_name_tmp__516 = 1;
  goto var_name_tmp__583;

var_name_tmp__583:
  goto var_name_tmp__584;

var_name_tmp__575:
  var_name_tmp__516 = 0;
  goto var_name_tmp__584;

var_name_tmp__584:
  goto var_name_tmp__573;

var_name_tmp__573:
  goto var_name_tmp__562;

var_name_tmp__562:
  var_name_tmp__551 = var_name_tmp__516;
  return var_name_tmp__551;
}


uint8_t CAN_Sleep(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__585) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__586;    /* Address-exposed local */
  uint8_t var_name_tmp__587;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__588;
  uint32_t var_name_tmp__589;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__590;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__591;
  uint32_t var_name_tmp__592;
  uint8_t var_name_tmp__593;

  var_name_tmp__586 = var_name_tmp__585;
  var_name_tmp__587 = 0;
  var_name_tmp__588 = var_name_tmp__586;
  var_name_tmp__589 = *(volatile uint32_t*)((&var_name_tmp__588->field0));
  var_name_tmp__590 = var_name_tmp__586;
  *(volatile uint32_t*)((&var_name_tmp__590->field0)) = ((var_name_tmp__589 & -2) | 2);
  var_name_tmp__591 = var_name_tmp__586;
  var_name_tmp__592 = *(volatile uint32_t*)((&var_name_tmp__591->field1));
  if (((((var_name_tmp__592 & 3) == 2u)&1))) {
    goto var_name_tmp__594;
  } else {
    goto var_name_tmp__595;
  }

var_name_tmp__594:
  var_name_tmp__587 = 1;
  goto var_name_tmp__595;

var_name_tmp__595:
  var_name_tmp__593 = var_name_tmp__587;
  return var_name_tmp__593;
}


uint8_t CAN_WakeUp(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__596) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__597;    /* Address-exposed local */
  uint32_t var_name_tmp__598;    /* Address-exposed local */
  uint8_t var_name_tmp__599;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__600;
  uint32_t* var_name_tmp__601;
  uint32_t var_name_tmp__602;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__603;
  uint32_t var_name_tmp__604;
  uint32_t var_name_tmp__605;
  bool var_name_tmp__606;
  bool var_name_tmp__606__PHI_TEMPORARY;
  uint32_t var_name_tmp__607;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__608;
  uint32_t var_name_tmp__609;
  uint8_t var_name_tmp__610;

  var_name_tmp__597 = var_name_tmp__596;
  var_name_tmp__598 = 65535;
  var_name_tmp__599 = 0;
  var_name_tmp__600 = var_name_tmp__597;
  var_name_tmp__601 = (&var_name_tmp__600->field0);
  var_name_tmp__602 = *(volatile uint32_t*)var_name_tmp__601;
  *(volatile uint32_t*)var_name_tmp__601 = (var_name_tmp__602 & -3);
  goto var_name_tmp__611;

  do {     /* Syntactic loop '' to make GCC happy */
var_name_tmp__611:
  var_name_tmp__603 = var_name_tmp__597;
  var_name_tmp__604 = *(volatile uint32_t*)((&var_name_tmp__603->field1));
  if (((((var_name_tmp__604 & 2) == 2u)&1))) {
    goto var_name_tmp__612;
  } else {
    var_name_tmp__606__PHI_TEMPORARY = 0;   /* for PHI node */
    goto var_name_tmp__613;
  }

var_name_tmp__612:
  var_name_tmp__605 = var_name_tmp__598;
  var_name_tmp__606__PHI_TEMPORARY = (((var_name_tmp__605 != 0u)&1));   /* for PHI node */
  goto var_name_tmp__613;

var_name_tmp__613:
  var_name_tmp__606 = ((var_name_tmp__606__PHI_TEMPORARY)&1);
  if (var_name_tmp__606) {
    goto var_name_tmp__614;
  } else {
    goto var_name_tmp__615;
  }

var_name_tmp__614:
  var_name_tmp__607 = var_name_tmp__598;
  var_name_tmp__598 = (llvm_add_u32(var_name_tmp__607, -1));
  goto var_name_tmp__611;

  } while (1); /* end of syntactic loop '' */
var_name_tmp__615:
  var_name_tmp__608 = var_name_tmp__597;
  var_name_tmp__609 = *(volatile uint32_t*)((&var_name_tmp__608->field1));
  if (((((var_name_tmp__609 & 2) != 2u)&1))) {
    goto var_name_tmp__616;
  } else {
    goto var_name_tmp__617;
  }

var_name_tmp__616:
  var_name_tmp__599 = 1;
  goto var_name_tmp__617;

var_name_tmp__617:
  var_name_tmp__610 = var_name_tmp__599;
  return var_name_tmp__610;
}


uint8_t CAN_GetLastErrorCode(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__618) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__619;    /* Address-exposed local */
  uint8_t var_name_tmp__620;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__621;
  uint32_t var_name_tmp__622;
  uint8_t var_name_tmp__623;

  var_name_tmp__619 = var_name_tmp__618;
  var_name_tmp__620 = 0;
  var_name_tmp__621 = var_name_tmp__619;
  var_name_tmp__622 = *(volatile uint32_t*)((&var_name_tmp__621->field6));
  var_name_tmp__620 = (((uint8_t)((((uint32_t)(uint8_t)(((uint8_t)var_name_tmp__622)))) & 112)));
  var_name_tmp__623 = var_name_tmp__620;
  return var_name_tmp__623;
}


uint8_t CAN_GetReceiveErrorCounter(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__624) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__625;    /* Address-exposed local */
  uint8_t var_name_tmp__626;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__627;
  uint32_t var_name_tmp__628;
  uint8_t var_name_tmp__629;

  var_name_tmp__625 = var_name_tmp__624;
  var_name_tmp__626 = 0;
  var_name_tmp__627 = var_name_tmp__625;
  var_name_tmp__628 = *(volatile uint32_t*)((&var_name_tmp__627->field6));
  var_name_tmp__626 = (((uint8_t)(llvm_lshr_u32((var_name_tmp__628 & -16777216), 24))));
  var_name_tmp__629 = var_name_tmp__626;
  return var_name_tmp__629;
}


uint8_t CAN_GetLSBTransmitErrorCounter(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__630) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__631;    /* Address-exposed local */
  uint8_t var_name_tmp__632;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__633;
  uint32_t var_name_tmp__634;
  uint8_t var_name_tmp__635;

  var_name_tmp__631 = var_name_tmp__630;
  var_name_tmp__632 = 0;
  var_name_tmp__633 = var_name_tmp__631;
  var_name_tmp__634 = *(volatile uint32_t*)((&var_name_tmp__633->field6));
  var_name_tmp__632 = (((uint8_t)(llvm_lshr_u32((var_name_tmp__634 & 16711680), 16))));
  var_name_tmp__635 = var_name_tmp__632;
  return var_name_tmp__635;
}


void CAN_ITConfig(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__636, uint32_t var_name_tmp__637, uint32_t var_name_tmp__638) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__639;    /* Address-exposed local */
  uint32_t var_name_tmp__640;    /* Address-exposed local */
  uint32_t var_name_tmp__641;    /* Address-exposed local */
  uint32_t var_name_tmp__642;
  uint32_t var_name_tmp__643;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__644;
  uint32_t* var_name_tmp__645;
  uint32_t var_name_tmp__646;
  uint32_t var_name_tmp__647;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__648;
  uint32_t* var_name_tmp__649;
  uint32_t var_name_tmp__650;

  var_name_tmp__639 = var_name_tmp__636;
  var_name_tmp__640 = var_name_tmp__637;
  var_name_tmp__641 = var_name_tmp__638;
  var_name_tmp__642 = var_name_tmp__641;
  if ((((var_name_tmp__642 != 0u)&1))) {
    goto var_name_tmp__651;
  } else {
    goto var_name_tmp__652;
  }

var_name_tmp__651:
  var_name_tmp__643 = var_name_tmp__640;
  var_name_tmp__644 = var_name_tmp__639;
  var_name_tmp__645 = (&var_name_tmp__644->field5);
  var_name_tmp__646 = *(volatile uint32_t*)var_name_tmp__645;
  *(volatile uint32_t*)var_name_tmp__645 = (var_name_tmp__646 | var_name_tmp__643);
  goto var_name_tmp__653;

var_name_tmp__652:
  var_name_tmp__647 = var_name_tmp__640;
  var_name_tmp__648 = var_name_tmp__639;
  var_name_tmp__649 = (&var_name_tmp__648->field5);
  var_name_tmp__650 = *(volatile uint32_t*)var_name_tmp__649;
  *(volatile uint32_t*)var_name_tmp__649 = (var_name_tmp__650 & (~(var_name_tmp__647)));
  goto var_name_tmp__653;

var_name_tmp__653:
  return;
}


uint32_t CAN_GetFlagStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__654, uint32_t var_name_tmp__655) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__656;    /* Address-exposed local */
  uint32_t var_name_tmp__657;    /* Address-exposed local */
  uint32_t var_name_tmp__658;    /* Address-exposed local */
  uint32_t var_name_tmp__659;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__660;
  uint32_t var_name_tmp__661;
  uint32_t var_name_tmp__662;
  uint32_t var_name_tmp__663;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__664;
  uint32_t var_name_tmp__665;
  uint32_t var_name_tmp__666;
  uint32_t var_name_tmp__667;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__668;
  uint32_t var_name_tmp__669;
  uint32_t var_name_tmp__670;
  uint32_t var_name_tmp__671;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__672;
  uint32_t var_name_tmp__673;
  uint32_t var_name_tmp__674;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__675;
  uint32_t var_name_tmp__676;
  uint32_t var_name_tmp__677;
  uint32_t var_name_tmp__678;

  var_name_tmp__656 = var_name_tmp__654;
  var_name_tmp__657 = var_name_tmp__655;
  var_name_tmp__658 = 0;
  var_name_tmp__659 = var_name_tmp__657;
  if (((((var_name_tmp__659 & 15728640) != 0u)&1))) {
    goto var_name_tmp__679;
  } else {
    goto var_name_tmp__680;
  }

var_name_tmp__679:
  var_name_tmp__660 = var_name_tmp__656;
  var_name_tmp__661 = *(volatile uint32_t*)((&var_name_tmp__660->field6));
  var_name_tmp__662 = var_name_tmp__657;
  if (((((var_name_tmp__661 & (var_name_tmp__662 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__681;
  } else {
    goto var_name_tmp__682;
  }

var_name_tmp__681:
  var_name_tmp__658 = 1;
  goto var_name_tmp__683;

var_name_tmp__682:
  var_name_tmp__658 = 0;
  goto var_name_tmp__683;

var_name_tmp__683:
  goto var_name_tmp__684;

var_name_tmp__680:
  var_name_tmp__663 = var_name_tmp__657;
  if (((((var_name_tmp__663 & 16777216) != 0u)&1))) {
    goto var_name_tmp__685;
  } else {
    goto var_name_tmp__686;
  }

var_name_tmp__685:
  var_name_tmp__664 = var_name_tmp__656;
  var_name_tmp__665 = *(volatile uint32_t*)((&var_name_tmp__664->field1));
  var_name_tmp__666 = var_name_tmp__657;
  if (((((var_name_tmp__665 & (var_name_tmp__666 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__687;
  } else {
    goto var_name_tmp__688;
  }

var_name_tmp__687:
  var_name_tmp__658 = 1;
  goto var_name_tmp__689;

var_name_tmp__688:
  var_name_tmp__658 = 0;
  goto var_name_tmp__689;

var_name_tmp__689:
  goto var_name_tmp__690;

var_name_tmp__686:
  var_name_tmp__667 = var_name_tmp__657;
  if (((((var_name_tmp__667 & 134217728) != 0u)&1))) {
    goto var_name_tmp__691;
  } else {
    goto var_name_tmp__692;
  }

var_name_tmp__691:
  var_name_tmp__668 = var_name_tmp__656;
  var_name_tmp__669 = *(volatile uint32_t*)((&var_name_tmp__668->field2));
  var_name_tmp__670 = var_name_tmp__657;
  if (((((var_name_tmp__669 & (var_name_tmp__670 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__693;
  } else {
    goto var_name_tmp__694;
  }

var_name_tmp__693:
  var_name_tmp__658 = 1;
  goto var_name_tmp__695;

var_name_tmp__694:
  var_name_tmp__658 = 0;
  goto var_name_tmp__695;

var_name_tmp__695:
  goto var_name_tmp__696;

var_name_tmp__692:
  var_name_tmp__671 = var_name_tmp__657;
  if (((((var_name_tmp__671 & 33554432) != 0u)&1))) {
    goto var_name_tmp__697;
  } else {
    goto var_name_tmp__698;
  }

var_name_tmp__697:
  var_name_tmp__672 = var_name_tmp__656;
  var_name_tmp__673 = *(volatile uint32_t*)((&var_name_tmp__672->field3));
  var_name_tmp__674 = var_name_tmp__657;
  if (((((var_name_tmp__673 & (var_name_tmp__674 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__699;
  } else {
    goto var_name_tmp__700;
  }

var_name_tmp__699:
  var_name_tmp__658 = 1;
  goto var_name_tmp__701;

var_name_tmp__700:
  var_name_tmp__658 = 0;
  goto var_name_tmp__701;

var_name_tmp__701:
  goto var_name_tmp__702;

var_name_tmp__698:
  var_name_tmp__675 = var_name_tmp__656;
  var_name_tmp__676 = *(volatile uint32_t*)((&var_name_tmp__675->field4));
  var_name_tmp__677 = var_name_tmp__657;
  if (((((var_name_tmp__676 & (var_name_tmp__677 & 1048575)) != 0u)&1))) {
    goto var_name_tmp__703;
  } else {
    goto var_name_tmp__704;
  }

var_name_tmp__703:
  var_name_tmp__658 = 1;
  goto var_name_tmp__705;

var_name_tmp__704:
  var_name_tmp__658 = 0;
  goto var_name_tmp__705;

var_name_tmp__705:
  goto var_name_tmp__702;

var_name_tmp__702:
  goto var_name_tmp__696;

var_name_tmp__696:
  goto var_name_tmp__690;

var_name_tmp__690:
  goto var_name_tmp__684;

var_name_tmp__684:
  var_name_tmp__678 = var_name_tmp__658;
  return var_name_tmp__678;
}


void CAN_ClearFlag(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__706, uint32_t var_name_tmp__707) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__708;    /* Address-exposed local */
  uint32_t var_name_tmp__709;    /* Address-exposed local */
  uint32_t var_name_tmp__710;    /* Address-exposed local */
  uint32_t var_name_tmp__711;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__712;
  uint32_t var_name_tmp__713;
  uint32_t var_name_tmp__714;
  uint32_t var_name_tmp__715;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__716;
  uint32_t var_name_tmp__717;
  uint32_t var_name_tmp__718;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__719;
  uint32_t var_name_tmp__720;
  uint32_t var_name_tmp__721;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__722;
  uint32_t var_name_tmp__723;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__724;

  var_name_tmp__708 = var_name_tmp__706;
  var_name_tmp__709 = var_name_tmp__707;
  var_name_tmp__710 = 0;
  var_name_tmp__711 = var_name_tmp__709;
  if ((((var_name_tmp__711 == 821035120u)&1))) {
    goto var_name_tmp__725;
  } else {
    goto var_name_tmp__726;
  }

var_name_tmp__725:
  var_name_tmp__712 = var_name_tmp__708;
  *(volatile uint32_t*)((&var_name_tmp__712->field6)) = 0;
  goto var_name_tmp__727;

var_name_tmp__726:
  var_name_tmp__713 = var_name_tmp__709;
  var_name_tmp__710 = (var_name_tmp__713 & 1048575);
  var_name_tmp__714 = var_name_tmp__709;
  if (((((var_name_tmp__714 & 33554432) != 0u)&1))) {
    goto var_name_tmp__728;
  } else {
    goto var_name_tmp__729;
  }

var_name_tmp__728:
  var_name_tmp__715 = var_name_tmp__710;
  var_name_tmp__716 = var_name_tmp__708;
  *(volatile uint32_t*)((&var_name_tmp__716->field3)) = var_name_tmp__715;
  goto var_name_tmp__730;

var_name_tmp__729:
  var_name_tmp__717 = var_name_tmp__709;
  if (((((var_name_tmp__717 & 67108864) != 0u)&1))) {
    goto var_name_tmp__731;
  } else {
    goto var_name_tmp__732;
  }

var_name_tmp__731:
  var_name_tmp__718 = var_name_tmp__710;
  var_name_tmp__719 = var_name_tmp__708;
  *(volatile uint32_t*)((&var_name_tmp__719->field4)) = var_name_tmp__718;
  goto var_name_tmp__733;

var_name_tmp__732:
  var_name_tmp__720 = var_name_tmp__709;
  if (((((var_name_tmp__720 & 134217728) != 0u)&1))) {
    goto var_name_tmp__734;
  } else {
    goto var_name_tmp__735;
  }

var_name_tmp__734:
  var_name_tmp__721 = var_name_tmp__710;
  var_name_tmp__722 = var_name_tmp__708;
  *(volatile uint32_t*)((&var_name_tmp__722->field2)) = var_name_tmp__721;
  goto var_name_tmp__736;

var_name_tmp__735:
  var_name_tmp__723 = var_name_tmp__710;
  var_name_tmp__724 = var_name_tmp__708;
  *(volatile uint32_t*)((&var_name_tmp__724->field1)) = var_name_tmp__723;
  goto var_name_tmp__736;

var_name_tmp__736:
  goto var_name_tmp__733;

var_name_tmp__733:
  goto var_name_tmp__730;

var_name_tmp__730:
  goto var_name_tmp__727;

var_name_tmp__727:
  return;
}


uint32_t CAN_GetITStatus(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__737, uint32_t var_name_tmp__738) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__739;    /* Address-exposed local */
  uint32_t var_name_tmp__740;    /* Address-exposed local */
  uint32_t var_name_tmp__741;    /* Address-exposed local */
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__742;
  uint32_t var_name_tmp__743;
  uint32_t var_name_tmp__744;
  uint32_t var_name_tmp__745;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__746;
  uint32_t var_name_tmp__747;
  uint32_t var_name_tmp__748;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__749;
  uint32_t var_name_tmp__750;
  uint32_t var_name_tmp__751;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__752;
  uint32_t var_name_tmp__753;
  uint32_t var_name_tmp__754;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__755;
  uint32_t var_name_tmp__756;
  uint32_t var_name_tmp__757;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__758;
  uint32_t var_name_tmp__759;
  uint32_t var_name_tmp__760;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__761;
  uint32_t var_name_tmp__762;
  uint32_t var_name_tmp__763;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__764;
  uint32_t var_name_tmp__765;
  uint32_t var_name_tmp__766;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__767;
  uint32_t var_name_tmp__768;
  uint32_t var_name_tmp__769;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__770;
  uint32_t var_name_tmp__771;
  uint32_t var_name_tmp__772;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__773;
  uint32_t var_name_tmp__774;
  uint32_t var_name_tmp__775;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__776;
  uint32_t var_name_tmp__777;
  uint32_t var_name_tmp__778;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__779;
  uint32_t var_name_tmp__780;
  uint32_t var_name_tmp__781;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__782;
  uint32_t var_name_tmp__783;
  uint32_t var_name_tmp__784;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__785;
  uint32_t var_name_tmp__786;
  uint32_t var_name_tmp__787;
  uint32_t var_name_tmp__788;

  var_name_tmp__739 = var_name_tmp__737;
  var_name_tmp__740 = var_name_tmp__738;
  var_name_tmp__741 = 0;
  var_name_tmp__742 = var_name_tmp__739;
  var_name_tmp__743 = *(volatile uint32_t*)((&var_name_tmp__742->field5));
  var_name_tmp__744 = var_name_tmp__740;
  if (((((var_name_tmp__743 & var_name_tmp__744) != 0u)&1))) {
    goto var_name_tmp__789;
  } else {
    goto var_name_tmp__790;
  }

var_name_tmp__789:
  var_name_tmp__745 = var_name_tmp__740;
  switch (var_name_tmp__745) {
  default:
    goto var_name_tmp__791;
  case 1u:
    goto var_name_tmp__792;
  case 2u:
    goto var_name_tmp__793;
  case 4u:
    goto var_name_tmp__794;
  case 8u:
    goto var_name_tmp__795;
  case 16u:
    goto var_name_tmp__796;
  case 32u:
    goto var_name_tmp__797;
  case 64u:
    goto var_name_tmp__798;
  case 65536u:
    goto var_name_tmp__799;
  case 131072u:
    goto var_name_tmp__800;
  case 256u:
    goto var_name_tmp__801;
  case 512u:
    goto var_name_tmp__802;
  case 1024u:
    goto var_name_tmp__803;
  case 2048u:
    goto var_name_tmp__804;
  case 32768u:
    goto var_name_tmp__805;
  }

var_name_tmp__792:
  var_name_tmp__746 = var_name_tmp__739;
  var_name_tmp__747 = *(volatile uint32_t*)((&var_name_tmp__746->field2));
  var_name_tmp__748 = CheckITStatus(var_name_tmp__747, 65793);
  var_name_tmp__741 = var_name_tmp__748;
  goto var_name_tmp__806;

var_name_tmp__793:
  var_name_tmp__749 = var_name_tmp__739;
  var_name_tmp__750 = *(volatile uint32_t*)((&var_name_tmp__749->field3));
  var_name_tmp__751 = CheckITStatus(var_name_tmp__750, 3);
  var_name_tmp__741 = var_name_tmp__751;
  goto var_name_tmp__806;

var_name_tmp__794:
  var_name_tmp__752 = var_name_tmp__739;
  var_name_tmp__753 = *(volatile uint32_t*)((&var_name_tmp__752->field3));
  var_name_tmp__754 = CheckITStatus(var_name_tmp__753, 8);
  var_name_tmp__741 = var_name_tmp__754;
  goto var_name_tmp__806;

var_name_tmp__795:
  var_name_tmp__755 = var_name_tmp__739;
  var_name_tmp__756 = *(volatile uint32_t*)((&var_name_tmp__755->field3));
  var_name_tmp__757 = CheckITStatus(var_name_tmp__756, 16);
  var_name_tmp__741 = var_name_tmp__757;
  goto var_name_tmp__806;

var_name_tmp__796:
  var_name_tmp__758 = var_name_tmp__739;
  var_name_tmp__759 = *(volatile uint32_t*)((&var_name_tmp__758->field4));
  var_name_tmp__760 = CheckITStatus(var_name_tmp__759, 3);
  var_name_tmp__741 = var_name_tmp__760;
  goto var_name_tmp__806;

var_name_tmp__797:
  var_name_tmp__761 = var_name_tmp__739;
  var_name_tmp__762 = *(volatile uint32_t*)((&var_name_tmp__761->field4));
  var_name_tmp__763 = CheckITStatus(var_name_tmp__762, 8);
  var_name_tmp__741 = var_name_tmp__763;
  goto var_name_tmp__806;

var_name_tmp__798:
  var_name_tmp__764 = var_name_tmp__739;
  var_name_tmp__765 = *(volatile uint32_t*)((&var_name_tmp__764->field4));
  var_name_tmp__766 = CheckITStatus(var_name_tmp__765, 16);
  var_name_tmp__741 = var_name_tmp__766;
  goto var_name_tmp__806;

var_name_tmp__799:
  var_name_tmp__767 = var_name_tmp__739;
  var_name_tmp__768 = *(volatile uint32_t*)((&var_name_tmp__767->field1));
  var_name_tmp__769 = CheckITStatus(var_name_tmp__768, 8);
  var_name_tmp__741 = var_name_tmp__769;
  goto var_name_tmp__806;

var_name_tmp__800:
  var_name_tmp__770 = var_name_tmp__739;
  var_name_tmp__771 = *(volatile uint32_t*)((&var_name_tmp__770->field1));
  var_name_tmp__772 = CheckITStatus(var_name_tmp__771, 16);
  var_name_tmp__741 = var_name_tmp__772;
  goto var_name_tmp__806;

var_name_tmp__801:
  var_name_tmp__773 = var_name_tmp__739;
  var_name_tmp__774 = *(volatile uint32_t*)((&var_name_tmp__773->field6));
  var_name_tmp__775 = CheckITStatus(var_name_tmp__774, 1);
  var_name_tmp__741 = var_name_tmp__775;
  goto var_name_tmp__806;

var_name_tmp__802:
  var_name_tmp__776 = var_name_tmp__739;
  var_name_tmp__777 = *(volatile uint32_t*)((&var_name_tmp__776->field6));
  var_name_tmp__778 = CheckITStatus(var_name_tmp__777, 2);
  var_name_tmp__741 = var_name_tmp__778;
  goto var_name_tmp__806;

var_name_tmp__803:
  var_name_tmp__779 = var_name_tmp__739;
  var_name_tmp__780 = *(volatile uint32_t*)((&var_name_tmp__779->field6));
  var_name_tmp__781 = CheckITStatus(var_name_tmp__780, 4);
  var_name_tmp__741 = var_name_tmp__781;
  goto var_name_tmp__806;

var_name_tmp__804:
  var_name_tmp__782 = var_name_tmp__739;
  var_name_tmp__783 = *(volatile uint32_t*)((&var_name_tmp__782->field6));
  var_name_tmp__784 = CheckITStatus(var_name_tmp__783, 112);
  var_name_tmp__741 = var_name_tmp__784;
  goto var_name_tmp__806;

var_name_tmp__805:
  var_name_tmp__785 = var_name_tmp__739;
  var_name_tmp__786 = *(volatile uint32_t*)((&var_name_tmp__785->field1));
  var_name_tmp__787 = CheckITStatus(var_name_tmp__786, 4);
  var_name_tmp__741 = var_name_tmp__787;
  goto var_name_tmp__806;

var_name_tmp__791:
  var_name_tmp__741 = 0;
  goto var_name_tmp__806;

var_name_tmp__806:
  goto var_name_tmp__807;

var_name_tmp__790:
  var_name_tmp__741 = 0;
  goto var_name_tmp__807;

var_name_tmp__807:
  var_name_tmp__788 = var_name_tmp__741;
  return var_name_tmp__788;
}


static uint32_t CheckITStatus(uint32_t var_name_tmp__808, uint32_t var_name_tmp__809) {
  uint32_t var_name_tmp__810;    /* Address-exposed local */
  uint32_t var_name_tmp__811;    /* Address-exposed local */
  uint32_t var_name_tmp__812;    /* Address-exposed local */
  uint32_t var_name_tmp__813;
  uint32_t var_name_tmp__814;
  uint32_t var_name_tmp__815;

  var_name_tmp__810 = var_name_tmp__808;
  var_name_tmp__811 = var_name_tmp__809;
  var_name_tmp__812 = 0;
  var_name_tmp__813 = var_name_tmp__810;
  var_name_tmp__814 = var_name_tmp__811;
  if (((((var_name_tmp__813 & var_name_tmp__814) != 0u)&1))) {
    goto var_name_tmp__816;
  } else {
    goto var_name_tmp__817;
  }

var_name_tmp__816:
  var_name_tmp__812 = 1;
  goto var_name_tmp__818;

var_name_tmp__817:
  var_name_tmp__812 = 0;
  goto var_name_tmp__818;

var_name_tmp__818:
  var_name_tmp__815 = var_name_tmp__812;
  return var_name_tmp__815;
}


void CAN_ClearITPendingBit(struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__819, uint32_t var_name_tmp__820) {
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__821;    /* Address-exposed local */
  uint32_t var_name_tmp__822;    /* Address-exposed local */
  uint32_t var_name_tmp__823;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__824;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__825;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__826;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__827;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__828;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__829;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__830;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__831;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__832;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__833;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__834;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__835;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__836;
  struct l_struct_struct_OC_CAN_TypeDef* var_name_tmp__837;

  var_name_tmp__821 = var_name_tmp__819;
  var_name_tmp__822 = var_name_tmp__820;
  var_name_tmp__823 = var_name_tmp__822;
  switch (var_name_tmp__823) {
  default:
    goto var_name_tmp__838;
  case 1u:
    goto var_name_tmp__839;
  case 4u:
    goto var_name_tmp__840;
  case 8u:
    goto var_name_tmp__841;
  case 32u:
    goto var_name_tmp__842;
  case 64u:
    goto var_name_tmp__843;
  case 65536u:
    goto var_name_tmp__844;
  case 131072u:
    goto var_name_tmp__845;
  case 256u:
    goto var_name_tmp__846;
  case 512u:
    goto var_name_tmp__847;
  case 1024u:
    goto var_name_tmp__848;
  case 2048u:
    goto var_name_tmp__849;
  case 32768u:
    goto var_name_tmp__850;
  }

var_name_tmp__839:
  var_name_tmp__824 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__824->field2)) = 65793;
  goto var_name_tmp__851;

var_name_tmp__840:
  var_name_tmp__825 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__825->field3)) = 8;
  goto var_name_tmp__851;

var_name_tmp__841:
  var_name_tmp__826 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__826->field3)) = 16;
  goto var_name_tmp__851;

var_name_tmp__842:
  var_name_tmp__827 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__827->field4)) = 8;
  goto var_name_tmp__851;

var_name_tmp__843:
  var_name_tmp__828 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__828->field4)) = 16;
  goto var_name_tmp__851;

var_name_tmp__844:
  var_name_tmp__829 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__829->field1)) = 8;
  goto var_name_tmp__851;

var_name_tmp__845:
  var_name_tmp__830 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__830->field1)) = 16;
  goto var_name_tmp__851;

var_name_tmp__846:
  var_name_tmp__831 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__831->field1)) = 4;
  goto var_name_tmp__851;

var_name_tmp__847:
  var_name_tmp__832 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__832->field1)) = 4;
  goto var_name_tmp__851;

var_name_tmp__848:
  var_name_tmp__833 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__833->field1)) = 4;
  goto var_name_tmp__851;

var_name_tmp__849:
  var_name_tmp__834 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__834->field6)) = 0;
  var_name_tmp__835 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__835->field1)) = 4;
  goto var_name_tmp__851;

var_name_tmp__850:
  var_name_tmp__836 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__836->field6)) = 0;
  var_name_tmp__837 = var_name_tmp__821;
  *(volatile uint32_t*)((&var_name_tmp__837->field1)) = 4;
  goto var_name_tmp__851;

var_name_tmp__838:
  goto var_name_tmp__851;

var_name_tmp__851:
  return;
}

