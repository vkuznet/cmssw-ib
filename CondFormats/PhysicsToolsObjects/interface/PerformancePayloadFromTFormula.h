#ifndef PerformancePayloadFromTFormula_h
#define PerformancePayloadFromTFormula_h

#include "CondFormats/PhysicsToolsObjects/interface/PhysicsTFormulaPayload.h"
#include "CondFormats/PhysicsToolsObjects/interface/PerformancePayload.h"

#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
#include <atomic>
#endif
#include <algorithm>
#include <string>
#include <vector>
#include "TFormula.h"

#include "CondFormats/PhysicsToolsObjects/interface/BinningPointByMap.h"

class PerformancePayloadFromTFormula : public PerformancePayload {
//  class PerformancePayloadFromTFormula : public PerformancePayload, public PhysicsPerformancePayload {
 public:

  static int InvalidPos;

  PerformancePayloadFromTFormula(std::vector<PerformanceResult::ResultType> r, std::vector<BinningVariables::BinningVariablesType> b  ,  PhysicsTFormulaPayload& in) : pl(in), results_(r), variables_(b) {}

  PerformancePayloadFromTFormula();
  virtual ~PerformancePayloadFromTFormula();
  // copy ctor
  PerformancePayloadFromTFormula(const PerformancePayloadFromTFormula& src);
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  PerformancePayloadFromTFormula(PerformancePayloadFromTFormula&& src);
#endif
  // operator=
  const PerformancePayloadFromTFormula& operator=(const PerformancePayloadFromTFormula& rhs);
  void swap(PerformancePayloadFromTFormula& rhs);

  float getResult(PerformanceResult::ResultType,BinningPointByMap) const ; // gets from the full payload
  
  virtual bool isParametrizedInVariable(const BinningVariables::BinningVariablesType p)  const {
    return (limitPos(p) != PerformancePayloadFromTFormula::InvalidPos);
  }
  
  virtual bool isInPayload(PerformanceResult::ResultType,BinningPointByMap) const ;
  
  const PhysicsTFormulaPayload & formulaPayload() const {return pl;}
  
  void printFormula(PerformanceResult::ResultType res) const;
  

 protected:
  
  virtual std::vector<BinningVariables::BinningVariablesType> myBinning() const {return variables_;}

  virtual int limitPos(const BinningVariables::BinningVariablesType b) const {
    std::vector<BinningVariables::BinningVariablesType>::const_iterator p;
    p = find(variables_.begin(), variables_.end(), b);
    if (p == variables_.end()) return PerformancePayloadFromTFormula::InvalidPos;
    return ((p-variables_.begin()));
    
  }

  virtual int resultPos(PerformanceResult::ResultType r) const {
    std::vector<PerformanceResult::ResultType>::const_iterator p;
    p = find (results_.begin(), results_.end(), r);
    if ( p == results_.end()) return PerformancePayloadFromTFormula::InvalidPos;
      return ((p-results_.begin()));
  }


  bool isOk(BinningPointByMap p) const; 

  void check() const;

  PhysicsTFormulaPayload pl;
  //
  // the variable mapping
  //
  std::vector<PerformanceResult::ResultType> results_;
  std::vector<BinningVariables::BinningVariablesType> variables_;
  //
  // the transient part
  //
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  mutable   std::atomic<std::vector<TFormula*>*> compiledFormulas_;
#else
  mutable   std::vector<TFormula *> compiledFormulas_;
#endif
};

#endif
