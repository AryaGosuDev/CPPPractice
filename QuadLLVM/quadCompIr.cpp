#include "llvm-c/Core.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm-c/BitReader.h"
#include "llvm-c/BitWriter.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include <iostream>

using namespace llvm;
//using namespace llvm::orc;

//typical cmd line compilate : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g main.cpp -o run
//g++ --std=c++14 -O0 -gline-tables-only -emit-llvm -o quad.bc -c quadCompIr.cpp
//g++ --std=c++11 -I /usr/local/llvm/include/ -L -O0 -Wall quadCompIr.cpp -o run

namespace {

	struct BasicLoops : public LoopPass {
		static char ID;
		BasicLoops () : LoopPass(ID){}
		void getAnalysisUsage ( AnalysisUsage & AU) const {
			//AU.setPreservesCFG();
	  		AU.addRequired<LoopInfoWrapperPass>();
		}
		virtual bool runOnLoop (Loop * l, LPPassManager & LPM) override {
			LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
			return true  ;
		}
	};
}

char BasicLoops::ID = 0;
static RegisterPass<BasicLoops> X("loop", "Quad Loop Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

	static llvm::RegisterStandardPasses Y(
    llvm::PassManagerBuilder::EP_EarlyAsPossible,
    [](const llvm::PassManagerBuilder &Builder,
       llvm::legacy::PassManagerBase &PM) { PM.add(new BasicLoops()); });