#ifndef LLVM_MCAD_BROKERS_ASMFILEBROKER_H
#define LLVM_MCAD_BROKERS_ASMFILEBROKER_H
#include "llvm/Support/SourceMgr.h"
#include "AsmUtils/CodeRegion.h"
#include "AsmUtils/CodeRegionGenerator.h"
#include "Broker.h"
#include "MCAWorker.h"

namespace llvm {
namespace mcad {
// A broker that simply reads from local assembly file.
// Useful for testing.
class AsmFileBroker : public Broker {
  llvm::SourceMgr SrcMgr;
  mca::AsmCodeRegionGenerator CRG;

  const mca::CodeRegions *Regions;
  mca::CodeRegions::const_iterator IterRegion, IterRegionEnd;
  size_t CurInstIdx;

  bool IsInvalid;

  bool parseIfNeeded();

public:
  AsmFileBroker(const Target &T, MCContext &C,
                const MCAsmInfo &A, const MCSubtargetInfo &S,
                const MCInstrInfo &I);

  static void Register(BrokerFacade BF);

  const MCInst *fetch() override;

  int fetch(MutableArrayRef<const MCInst*> MCIS, int Size = -1) override;
};
} // end namespace mcad
} // end namespace llvm
#endif
