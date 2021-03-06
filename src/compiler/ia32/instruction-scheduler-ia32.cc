// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/compiler/instruction-scheduler.h"

namespace v8 {
namespace internal {
namespace compiler {

bool InstructionScheduler::SchedulerSupported() { return true; }


int InstructionScheduler::GetTargetInstructionFlags(
    const Instruction* instr) const {
  switch (instr->arch_opcode()) {
    case kIA32Add:
    case kIA32And:
    case kIA32Cmp:
    case kIA32Cmp16:
    case kIA32Cmp8:
    case kIA32Test:
    case kIA32Test16:
    case kIA32Test8:
    case kIA32Or:
    case kIA32Xor:
    case kIA32Sub:
    case kIA32Imul:
    case kIA32ImulHigh:
    case kIA32UmulHigh:
    case kIA32Not:
    case kIA32Neg:
    case kIA32Shl:
    case kIA32Shr:
    case kIA32Sar:
    case kIA32AddPair:
    case kIA32SubPair:
    case kIA32MulPair:
    case kIA32ShlPair:
    case kIA32ShrPair:
    case kIA32SarPair:
    case kIA32Ror:
    case kIA32Lzcnt:
    case kIA32Tzcnt:
    case kIA32Popcnt:
    case kIA32Lea:
    case kSSEFloat32Cmp:
    case kSSEFloat32Add:
    case kSSEFloat32Sub:
    case kSSEFloat32Mul:
    case kSSEFloat32Div:
    case kSSEFloat32Abs:
    case kSSEFloat32Neg:
    case kSSEFloat32Sqrt:
    case kSSEFloat32Round:
    case kSSEFloat64Cmp:
    case kSSEFloat64Add:
    case kSSEFloat64Sub:
    case kSSEFloat64Mul:
    case kSSEFloat64Div:
    case kSSEFloat64Mod:
    case kSSEFloat32Max:
    case kSSEFloat64Max:
    case kSSEFloat32Min:
    case kSSEFloat64Min:
    case kSSEFloat64Abs:
    case kSSEFloat64Neg:
    case kSSEFloat64Sqrt:
    case kSSEFloat64Round:
    case kSSEFloat32ToFloat64:
    case kSSEFloat64ToFloat32:
    case kSSEFloat32ToInt32:
    case kSSEFloat32ToUint32:
    case kSSEFloat64ToInt32:
    case kSSEFloat64ToUint32:
    case kSSEInt32ToFloat32:
    case kSSEUint32ToFloat32:
    case kSSEInt32ToFloat64:
    case kSSEUint32ToFloat64:
    case kSSEFloat64ExtractLowWord32:
    case kSSEFloat64ExtractHighWord32:
    case kSSEFloat64InsertLowWord32:
    case kSSEFloat64InsertHighWord32:
    case kSSEFloat64LoadLowWord32:
    case kSSEFloat64SilenceNaN:
    case kAVXFloat32Add:
    case kAVXFloat32Sub:
    case kAVXFloat32Mul:
    case kAVXFloat32Div:
    case kAVXFloat64Add:
    case kAVXFloat64Sub:
    case kAVXFloat64Mul:
    case kAVXFloat64Div:
    case kAVXFloat64Abs:
    case kAVXFloat64Neg:
    case kAVXFloat32Abs:
    case kAVXFloat32Neg:
    case kIA32BitcastFI:
    case kIA32BitcastIF:
    case kIA32I32x4Splat:
    case kIA32I32x4ExtractLane:
    case kSSEI32x4ReplaceLane:
    case kAVXI32x4ReplaceLane:
    case kIA32I32x4Neg:
    case kSSEI32x4Shl:
    case kAVXI32x4Shl:
    case kSSEI32x4ShrS:
    case kAVXI32x4ShrS:
    case kSSEI32x4Add:
    case kAVXI32x4Add:
    case kSSEI32x4Sub:
    case kAVXI32x4Sub:
    case kSSEI32x4Mul:
    case kAVXI32x4Mul:
    case kSSEI32x4MinS:
    case kAVXI32x4MinS:
    case kSSEI32x4MaxS:
    case kAVXI32x4MaxS:
    case kSSEI32x4Eq:
    case kAVXI32x4Eq:
    case kSSEI32x4Ne:
    case kAVXI32x4Ne:
    case kSSEI32x4GtS:
    case kAVXI32x4GtS:
    case kSSEI32x4GeS:
    case kAVXI32x4GeS:
    case kSSEI32x4ShrU:
    case kAVXI32x4ShrU:
    case kSSEI32x4MinU:
    case kAVXI32x4MinU:
    case kSSEI32x4MaxU:
    case kAVXI32x4MaxU:
    case kSSEI32x4GtU:
    case kAVXI32x4GtU:
    case kSSEI32x4GeU:
    case kAVXI32x4GeU:
    case kIA32I16x8Splat:
    case kIA32I16x8ExtractLane:
    case kSSEI16x8ReplaceLane:
    case kAVXI16x8ReplaceLane:
    case kSSEI16x8Shl:
    case kAVXI16x8Shl:
    case kSSEI16x8ShrS:
    case kAVXI16x8ShrS:
    case kSSEI16x8Add:
    case kAVXI16x8Add:
    case kSSEI16x8AddSaturateS:
    case kAVXI16x8AddSaturateS:
    case kSSEI16x8Sub:
    case kAVXI16x8Sub:
    case kSSEI16x8SubSaturateS:
    case kAVXI16x8SubSaturateS:
    case kSSEI16x8ShrU:
    case kAVXI16x8ShrU:
    case kIA32I8x16Splat:
    case kIA32I8x16ExtractLane:
    case kSSEI8x16ReplaceLane:
    case kAVXI8x16ReplaceLane:
      return (instr->addressing_mode() == kMode_None)
          ? kNoOpcodeFlags
          : kIsLoadOperation | kHasSideEffect;

    case kIA32Idiv:
    case kIA32Udiv:
      return (instr->addressing_mode() == kMode_None)
                 ? kMayNeedDeoptOrTrapCheck
                 : kMayNeedDeoptOrTrapCheck | kIsLoadOperation | kHasSideEffect;

    case kIA32Movsxbl:
    case kIA32Movzxbl:
    case kIA32Movb:
    case kIA32Movsxwl:
    case kIA32Movzxwl:
    case kIA32Movw:
    case kIA32Movl:
    case kIA32Movss:
    case kIA32Movsd:
      // Moves are used for memory load/store operations.
      return instr->HasOutput() ? kIsLoadOperation : kHasSideEffect;

    case kIA32StackCheck:
      return kIsLoadOperation;

    case kIA32Push:
    case kIA32PushFloat32:
    case kIA32PushFloat64:
    case kIA32Poke:
      return kHasSideEffect;

#define CASE(Name) case k##Name:
    COMMON_ARCH_OPCODE_LIST(CASE)
#undef CASE
      // Already covered in architecture independent code.
      UNREACHABLE();
  }

  UNREACHABLE();
}


int InstructionScheduler::GetInstructionLatency(const Instruction* instr) {
  // Basic latency modeling for ia32 instructions. They have been determined
  // in an empirical way.
  switch (instr->arch_opcode()) {
    case kCheckedLoadInt8:
    case kCheckedLoadUint8:
    case kCheckedLoadInt16:
    case kCheckedLoadUint16:
    case kCheckedLoadWord32:
    case kCheckedLoadFloat32:
    case kCheckedLoadFloat64:
    case kCheckedStoreWord8:
    case kCheckedStoreWord16:
    case kCheckedStoreWord32:
    case kCheckedStoreFloat32:
    case kCheckedStoreFloat64:
    case kSSEFloat64Mul:
      return 5;
    case kIA32Imul:
    case kIA32ImulHigh:
      return 5;
    case kSSEFloat32Cmp:
    case kSSEFloat64Cmp:
      return 9;
    case kSSEFloat32Add:
    case kSSEFloat32Sub:
    case kSSEFloat32Abs:
    case kSSEFloat32Neg:
    case kSSEFloat64Add:
    case kSSEFloat64Sub:
    case kSSEFloat64Max:
    case kSSEFloat64Min:
    case kSSEFloat64Abs:
    case kSSEFloat64Neg:
      return 5;
    case kSSEFloat32Mul:
      return 4;
    case kSSEFloat32ToFloat64:
    case kSSEFloat64ToFloat32:
      return 6;
    case kSSEFloat32Round:
    case kSSEFloat64Round:
    case kSSEFloat32ToInt32:
    case kSSEFloat64ToInt32:
      return 8;
    case kSSEFloat32ToUint32:
      return 21;
    case kSSEFloat64ToUint32:
      return 15;
    case kIA32Idiv:
      return 33;
    case kIA32Udiv:
      return 26;
    case kSSEFloat32Div:
      return 35;
    case kSSEFloat64Div:
      return 63;
    case kSSEFloat32Sqrt:
    case kSSEFloat64Sqrt:
      return 25;
    case kSSEFloat64Mod:
      return 50;
    case kArchTruncateDoubleToI:
      return 9;
    default:
      return 1;
  }
}

}  // namespace compiler
}  // namespace internal
}  // namespace v8
