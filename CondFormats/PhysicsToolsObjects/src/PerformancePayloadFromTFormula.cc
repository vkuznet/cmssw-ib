#include "CondFormats/PhysicsToolsObjects/interface/PerformancePayloadFromTFormula.h"

int PerformancePayloadFromTFormula::InvalidPos=-1;

#include <iostream>
using namespace std;

PerformancePayloadFromTFormula::PerformancePayloadFromTFormula()
    : compiledFormulas_(nullptr) {}

PerformancePayloadFromTFormula::~PerformancePayloadFromTFormula() {
    for (unsigned int i=0; i < (*compiledFormulas_).size(); ++i){
        auto ptr = (*compiledFormulas_)[i];
        if (ptr) delete ptr;
    }
    delete compiledFormulas_;
    compiledFormulas_ = nullptr;
}
// copy ctor
PerformancePayloadFromTFormula::PerformancePayloadFromTFormula(const PerformancePayloadFromTFormula& src) {
    compiledFormulas_.store(src.compiledFormulas_);

}
// move ctor
PerformancePayloadFromTFormula::PerformancePayloadFromTFormula(PerformancePayloadFromTFormula&& rhs)
    : PerformancePayloadFromTFormula() {
    rhs.swap(*this);
}
// operator=
const PerformancePayloadFromTFormula&
PerformancePayloadFromTFormula::operator=(const PerformancePayloadFromTFormula& rhs) {
    PerformancePayloadFromTFormula temp(rhs);
    temp.swap(*this);
    return *this;
}
// public swap
void PerformancePayloadFromTFormula::swap(PerformancePayloadFromTFormula& rhs) {
    compiledFormulas_.store(rhs.compiledFormulas_);
}

float PerformancePayloadFromTFormula::getResult(PerformanceResult::ResultType r ,BinningPointByMap p) const {
  check();
  //
  // which formula to use?
  //
  if (! isInPayload(r,p)) return PerformancePayload::InvalidResult;

  // nice, what to do here???
  TFormula * formula = (*compiledFormulas_)[resultPos(r)];
  //
  // prepare the vector to pass, order counts!!!
  //
  std::vector<BinningVariables::BinningVariablesType> t = myBinning();
  
  // sorry, TFormulas just work up to dimension==4
  Double_t values[4];
  int i=0;
  for (std::vector<BinningVariables::BinningVariablesType>::const_iterator it = t.begin(); it != t.end();++it, ++i){
    values[i] = p.value(*it);    
  }
  //
  // i need a non const version #$%^
  return formula->EvalPar(values);
}

bool PerformancePayloadFromTFormula::isOk(BinningPointByMap p) const {
  
  std::vector<BinningVariables::BinningVariablesType> t = myBinning();
  
  for (std::vector<BinningVariables::BinningVariablesType>::const_iterator it = t.begin(); it != t.end();++it){
    if (!   p.isKeyAvailable(*it)) return false;
    float v = p.value(*it);
    int pos = limitPos(*it);
    std::pair<float, float> limits = (pl.limits())[pos];
    if (v<limits.first || v>limits.second) return false;
  }
  return true;
}

bool PerformancePayloadFromTFormula::isInPayload(PerformanceResult::ResultType res,BinningPointByMap point) const {
  check();
  // first, let's see if it is available at all
  if (resultPos(res) == PerformancePayloadFromTFormula::InvalidPos) return false;
  
  if ( ! isOk(point)) return false;
  return true;
}


void PerformancePayloadFromTFormula::check() const {
  if(!compiledFormulas_) {

      auto ptr = new std::vector<TFormula *>;
      for (unsigned int i=0; i < pl.formulas().size(); ++i){
        // NOTE: neither TFormula or t->Compile() is thread-safe, should be fixed in ROOT
        TFormula* t = new TFormula("rr",(pl.formulas()[i]).c_str()); //FIXME: "rr" should be unique!
        t->Compile();
        ptr->push_back(t);
      }

      std::vector<TFormula *>* expect = nullptr;
      bool exchanged = compiledFormulas_.compare_exchange_strong(expect, ptr);
      if(!exchanged) {
          delete ptr;
      }
  }
}

void PerformancePayloadFromTFormula::printFormula(PerformanceResult::ResultType res) const {
  check();
  //
  // which formula to use?
  //
  if (resultPos(res) == PerformancePayloadFromTFormula::InvalidPos)  {
    cout << "Warning: result not available!" << endl;
  }
  
  // nice, what to do here???
  TFormula * formula = (*compiledFormulas_)[resultPos(res)];
  cout << "-- Formula: " << formula->GetExpFormula("p") << endl;
  // prepare the vector to pass, order counts!!!
  //
  std::vector<BinningVariables::BinningVariablesType> t = myBinning();
  
  for (std::vector<BinningVariables::BinningVariablesType>::const_iterator it = t.begin(); it != t.end();++it){
    int pos = limitPos(*it);
    std::pair<float, float> limits = (pl.limits())[pos];
    cout << "      Variable: " << *it << " with limits: " << "from: " << limits.first  << " to: " << limits.second << endl;
  }

}

#include "FWCore/Utilities/interface/typelookup.h"
TYPELOOKUP_DATA_REG(PerformancePayloadFromTFormula);
