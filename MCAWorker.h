#ifndef MCAD_MCAWORKER_H
#define MCAD_MCAWORKER_H
#include "llvm/MCA/SourceMgr.h"
#include "llvm/Support/Timer.h"
#include <functional>
#include <utility>
#include <list>
#include <unordered_map>
#include <set>

namespace llvm {
class ToolOutputFile;
class MCSubtargetInfo;
class MCInst;
class MCInstPrinter;
namespace mca {
class Context;
class InstrBuilder;
class Pipeline;
class PipelineOptions;
class PipelinePrinter;
class InstrDesc;
class Instruction;
} // end namespace mca

namespace mcad {
class MCAWorker {
  const MCSubtargetInfo &STI;
  mca::InstrBuilder &MCAIB;
  const MCInstPrinter &MIP;
  std::unique_ptr<mca::Pipeline> MCAPipeline;
  std::unique_ptr<mca::PipelinePrinter> MCAPipelinePrinter;

  std::list<const MCInst*> TraceMIs;
  // MCAWorker is the owner of this callback. Note that
  // SummaryView will only take reference of it.
  std::function<size_t(void)> GetTraceMISize;

  mca::IncrementalSourceMgr SrcMgr;

  std::unordered_map<const mca::InstrDesc*,
                     std::set<mca::Instruction*>> RecycledInsts;
  std::function<mca::Instruction*(const mca::InstrDesc&)>
    GetRecycledInst;
  std::function<void(mca::Instruction*)> AddRecycledInst;

  TimerGroup Timers;

  // The thread worker
  void addTraceInstsImpl() {}

  void runPipeline() {}

public:
  MCAWorker() = delete;

  MCAWorker(const MCSubtargetInfo &STI,
            mca::Context &MCA,
            const mca::PipelineOptions &PO,
            mca::InstrBuilder &IB,
            const MCInstPrinter &IP);

  void printMCA(ToolOutputFile &OF) {}
};
} // end namespace mcad
} // end namespace llvm
#endif
