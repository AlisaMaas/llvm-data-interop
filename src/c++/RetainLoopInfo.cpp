#include "RetainLoopInfo.h"
#include "marshal.cpp"
#include <llvm/Analysis/LoopInfo.h>

using namespace llvm;
using namespace std;
// Register call coverage as a pass
char RetainLoopInfo::ID = 0;
static RegisterPass<RetainLoopInfo> X("RetainLoopInfo",
                "Keep the loop info stuff around for later.",
                false, false);

struct CModule_t* module = 0;
struct CLoop_t** cloops = NULL;
int numLoops = 0;
RetainLoopInfo::RetainLoopInfo() : FunctionPass(ID) {
}
void RetainLoopInfo::getAnalysisUsage(AnalysisUsage &usage) const
{
  // read-only pass never changes anything
  	usage.setPreservesAll();
	usage.addRequired<LoopInfo>();
}

// ***
// runOnFunction: Entry point of the function
// ***
bool RetainLoopInfo::runOnFunction(Function& F) {
  printf_d("RetainLoopInfo::Top of runOnFunction\n");
  LoopInfo &LI = getAnalysis<LoopInfo>();
  printf_d("RetainLoopInfo::Got LoopInfo!\n");
  cloops = (struct CLoop_t**)calloc(LI.end()-LI.begin(), sizeof(struct CLoop_t*));
  printf_d("RetainLoopInfo::Making some cloops\n");
  numLoops = 0;

  for (LoopInfo::iterator i = LI.begin(), e = LI.end(); i != e; ++i) {
  	printf_d("RetainLoopInfo::About to translate a loop\n");
	struct CLoop_t* loop = translateLoop(module, *i, NULL); 
	printf_d("RetainLoopInfo::Finished translating a loop\n");
	cloops[numLoops++] = loop; 
	printf_d("RetainLoopInfo::Added a loop to the cloops\n");
   }
   printf_d("RetainLoopInfo::Done with runOnFunction!!!\n");
  return false; // we didn't change the function
}

struct CLoop_t** RetainLoopInfo::getLoops(){
  return cloops;
}

int RetainLoopInfo::getNumLoops(){
	return numLoops;
}
void RetainLoopInfo::setModule(struct CModule_t* m){
	module = m;
}

