#ifndef RETAIN_LOOP_INFO_H
#define RETAIN_LOOP_INFO_H
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <stdint.h>
#include <llvm/Pass.h>
#include <fstream>
#include <llvm/PassAnalysisSupport.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/PassRegistry.h>
#include <llvm/Support/Registry.h>
class RetainLoopInfo : public llvm::FunctionPass {
private:
  bool runOnFunction(llvm::Function &F);
  struct CModule_t* module;
  
public:
  
  static char ID; // Pass identification, replacement for typeid
  RetainLoopInfo();
  void getAnalysisUsage(llvm::AnalysisUsage &) const;
  virtual const char *getPassName() const {
    return "RetainLoopInfo";
  }
  struct CLoop_t** getLoops();
  int getNumLoops();
  void setModule(struct CModule_t* m);
};
/*namespace llvm{
INITIALIZE_PASS(RetainLoopInfo, "retain loopinfo", "Retains loopinfo information", false, false)
INITIALIZE_PASS_BEGIN(RetainLoopInfo, "retain loopinfo", "Retains loopinfo information", false, false)
INITIALIZE_PASS_DEPENDENCY(LoopInfo)
INITIALIZE_PASS_END(RetainLoopInfo, "retain loopinfo", "Retains loopinfo information", false, false)
}*/
#endif
