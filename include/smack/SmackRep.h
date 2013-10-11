//
// Copyright (c) 2013 Zvonimir Rakamaric (zvonimir@cs.utah.edu),
//                    Michael Emmi (michael.emmi@gmail.com)
// This file is distributed under the MIT License. See LICENSE for details.
//
#ifndef SMACKREP_H
#define SMACKREP_H

#include "smack/BoogieAst.h"
#include "smack/SmackOptions.h"
#include "llvm/InstVisitor.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/GetElementPtrTypeIterator.h"
#include "llvm/Support/GraphWriter.h"
#include "llvm/Support/Regex.h"
#include <sstream>

namespace smack {

using llvm::Regex;
using llvm::SmallVector;
using llvm::StringRef;
using namespace std;
  
class SmackRep {
public:
  static const string CURRADDR; // TODO: push this into SmackRepFlatMem
  static const string ALLOC;
  static const string BLOCK_LBL;
  static const string RET_VAR;
  static const string BOOL_VAR;
  static const string FLOAT_VAR;
  static const string PTR_VAR;
  static const string BOOL_TYPE;
  static const string FLOAT_TYPE;
  static const string NULL_VAL;

  static const string ALLOCA;
  static const string MALLOC;
  static const string FREE;
  static const string MEMCPY;

  static const string PTR;
  static const string STATIC;
  static const string OBJ;
  static const string OFF;
  static const string PA;
  
  static const string FP;

  static const string B2P;
  static const string I2P;
  static const string P2I;
  static const string I2B;
  static const string B2I;

  static const string FP2SI;
  static const string FP2UI;
  static const string SI2FP;
  static const string UI2FP;

  static const string ADD;
  static const string SUB;
  static const string MUL;
  static const string SDIV;
  static const string UDIV;
  static const string SREM;
  static const string UREM;
  static const string AND;
  static const string OR;
  static const string XOR;
  static const string LSHR;
  static const string ASHR;
  static const string SHL;

  static const string FADD;
  static const string FSUB;
  static const string FMUL;
  static const string FDIV;
  static const string FREM;

  static const string SGE;
  static const string UGE;
  static const string SLE;
  static const string ULE;
  static const string SLT;
  static const string ULT;
  static const string SGT;
  static const string UGT;
  
  static const string NAND;
  static const string MAX;
  static const string MIN;
  static const string UMAX;
  static const string UMIN;
  
  static const string FFALSE;
  static const string FOEQ;
  static const string FOGE;
  static const string FOGT;
  static const string FOLE;
  static const string FOLT;
  static const string FONE;
  static const string FORD;
  static const string FTRUE;
  static const string FUEQ;
  static const string FUGE;
  static const string FUGT;
  static const string FULE;
  static const string FULT;
  static const string FUNE;
  static const string FUNO;
  
  static const string MEM_OP;
  static const string REC_MEM_OP;
  static const string MEM_READ;
  static const string MEM_WRITE;

  static const Expr* NUL;

  static const string BOOGIE_REC_PTR;
  static const string BOOGIE_REC_OBJ;
  static const string BOOGIE_REC_INT;
  
  static const string STATIC_INIT;

  // TODO Make this width a parameter to generate bitvector-based code.
  static const int width;

protected:
  static const string ARITHMETIC;
  static const string AUX_PROCS;
  static const string MEMORY_DEBUG_SYMBOLS;
  llvm::AliasAnalysis* aliasAnalysis;
  vector<const void*> memoryRegions;
  const llvm::DataLayout* targetData;
  
  vector<const Stmt*> staticInits;
  vector<const Decl*> extraDecls;
  
  unsigned uniqueFpNum;
  unsigned uniqueUndefNum;

protected:
  SmackRep(llvm::AliasAnalysis* aa)
    : aliasAnalysis(aa), targetData(aa->getDataLayout()) {
    uniqueFpNum = 0;
    uniqueUndefNum = 0;
  }  
public:
  static SmackRep* createRep(llvm::AliasAnalysis* aa);
  
  bool isSmackName(string n);
  bool isProcIgnore(string n);
  bool isSmackAssert(llvm::Function* f);
  bool isSmackAssume(llvm::Function* f);
  bool isSmackRecObj(llvm::Function* f);
  bool isSmackRecInt(llvm::Function* f);
  bool isSmackRecPtr(llvm::Function* f);
  bool isInt(const llvm::Type* t);
  bool isInt(const llvm::Value* v);
  bool isBool(llvm::Type* t);
  bool isBool(llvm::Value* v);
  bool isFloat(llvm::Type* t);
  bool isFloat(llvm::Value* v);
  string type(llvm::Type* t);
  string type(llvm::Value* v);

  unsigned storageSize(llvm::Type* t);
  unsigned fieldOffset(llvm::StructType* t, unsigned fieldNo);
  
  unsigned getRegion(const llvm::Value* v);
  string memReg(unsigned i);

  const Expr* mem(const llvm::Value* v);
  // const Expr* ptr(const Expr* obj, const Expr* off);
  // const Expr* obj(const Expr* e);
  // const Expr* off(const Expr* e);
  const Expr* i2p(const Expr* e);
  const Expr* p2i(const Expr* e);
  const Expr* b2p(const Expr* e);
  const Expr* i2b(const Expr* e);
  const Expr* b2i(const Expr* e);

  const Expr* fp2si(const Expr* e);
  const Expr* fp2ui(const Expr* e);
  const Expr* si2fp(const Expr* e);
  const Expr* ui2fp(const Expr* e);

  const Expr* pa(const Expr* e, int x, int y);
  const Expr* pa(const Expr* e, const Expr* x, int y);
  const Expr* pa(const Expr* e, const Expr* x, const Expr* y);

  string id(const llvm::Value* v);
  const Expr* undef();
  const Expr* lit(const llvm::Value* v);
  const Expr* lit(unsigned v);
  const Expr* ptrArith(llvm::Value* p, vector<llvm::Value*> ps,
                       vector<llvm::Type*> ts);
  const Expr* expr(const llvm::Value* v);
  const Expr* op(llvm::BinaryOperator& o);
  const Expr* pred(llvm::CmpInst& ci);
  
  virtual const Expr* ptr2val(const Expr* e) = 0;
  virtual const Expr* val2ptr(const Expr* e) = 0;
  virtual const Expr* ref2ptr(const Expr* e) = 0;
  
  virtual vector<const Decl*> globalDecl(const llvm::Value* g) = 0;
  virtual vector<string> getModifies();
  void addStaticInit(const llvm::Value* g);
  bool hasStaticInits();
  Procedure* getStaticInit();
  vector<const Decl*> getExtraDecls();
  virtual string getPtrType() = 0;
  virtual string getPrelude();
  
  virtual string memoryModel() = 0;
  virtual string mallocProc() = 0;
  virtual string freeProc() = 0;
  virtual string allocaProc() = 0;
  virtual string memcpyCall(int dstReg, int srcReg);
  virtual string memcpyProc(int dstReg, int srcReg) = 0;
  
};
}

#endif // SMACKREP_H

