#include "CondFormats/PhysicsToolsObjects/interface/PerformancePayloadFromBinnedTFormula.h"

int PerformancePayloadFromBinnedTFormula::InvalidPos=-1;

#include <iostream>
using namespace std;


PerformancePayloadFromBinnedTFormula::PerformancePayloadFromBinnedTFormula()
    : compiledFormulas_(nullptr) {
}
PerformancePayloadFromBinnedTFormula::~PerformancePayloadFromBinnedTFormula(){
    delete compiledFormulas_;
    compiledFormulas_ = nullptr;
}
// copy ctor
PerformancePayloadFromBinnedTFormula::PerformancePayloadFromBinnedTFormula(const PerformancePayloadFromBinnedTFormula& src) {
    compiledFormulas_.store(src.compiledFormulas_);

}
// move ctor
PerformancePayloadFromBinnedTFormula::PerformancePayloadFromBinnedTFormula(PerformancePayloadFromBinnedTFormula&& rhs)
    : PerformancePayloadFromBinnedTFormula() {
    rhs.swap(*this);
}
// operator=
const PerformancePayloadFromBinnedTFormula&
PerformancePayloadFromBinnedTFormula::operator=(const PerformancePayloadFromBinnedTFormula& rhs) {
    PerformancePayloadFromBinnedTFormula temp(rhs);
    temp.swap(*this);
    return *this;
}
// public swap
void PerformancePayloadFromBinnedTFormula::swap(PerformancePayloadFromBinnedTFormula& rhs) {
    compiledFormulas_.store(rhs.compiledFormulas_);
}

TFormula * PerformancePayloadFromBinnedTFormula::getFormula(PerformanceResult::ResultType r ,BinningPointByMap p ) const {
  //
  // chooses the correct rectangular region
  //
  if (! isInPayload(r,p)) return NULL;
  unsigned int region;
  bool ok =  isOk(p,region);
  if (ok == false) return NULL;

  return (*compiledFormulas_)[region][resultPos(r)];

}

float PerformancePayloadFromBinnedTFormula::getResult(PerformanceResult::ResultType r ,BinningPointByMap p) const {
  check();
  //
  // which formula to use?
  //
  if (! isInPayload(r,p)) return PerformancePayload::InvalidResult;

  // nice, what to do here???
  //  TFormula * formula = compiledFormulas_[resultPos(r)];
  //

  TFormula * formula = getFormula(r,p);

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

bool PerformancePayloadFromBinnedTFormula::isOk(BinningPointByMap p,unsigned int& whichone) const {
  
  //
  // change: look on whether a single rectangularr region matches
  //
  for (unsigned int ti=0; ti< pls.size(); ++ti){
    bool result = true;
    std::vector<BinningVariables::BinningVariablesType>  t = myBinning();
    for (std::vector<BinningVariables::BinningVariablesType>::const_iterator it = t.begin(); it != t.end();++it){
      //
      // now looking into a single payload
      //
      if (!   p.isKeyAvailable(*it)) return false;
      float v = p.value(*it);
      int pos = limitPos(*it);
      std::pair<float, float> limits = (pls[ti].limits())[pos];
      if (v<limits.first || v>limits.second) result= false;
    }
    if (result == true)  {
      whichone = ti;
      return true;
    }
  }
  whichone = 9999;
  return false;
}

bool PerformancePayloadFromBinnedTFormula::isInPayload(PerformanceResult::ResultType res,BinningPointByMap point) const {
  check();
  // first, let's see if it is available at all
  if (resultPos(res) == PerformancePayloadFromBinnedTFormula::InvalidPos) return false;
  unsigned int whocares;
  if ( ! isOk(point,whocares)) return false;
  return true;
}


void PerformancePayloadFromBinnedTFormula::check() const {
  if(!compiledFormulas_) {
      auto ptr = new std::vector<std::vector<TFormula *> >;
      for (unsigned int t=0; t < pls.size(); ++t){
          std::vector <TFormula *> temp;
          for (unsigned int i=0; i < (pls[t].formulas()).size(); ++i){
              PhysicsTFormulaPayload  tmp = pls[t];
              // NOTE: neither TFormula or t->Compile() is thread-safe, should be fixed in ROOT
              TFormula* tt = new TFormula("rr",((tmp.formulas())[i]).c_str()); //FIXME: "rr" should be unique!
              tt->Compile();
              temp.push_back(tt);
          }
          ptr->push_back(temp);
      }

      std::vector<std::vector<TFormula *> >* expect = nullptr;
      bool exchanged = compiledFormulas_.compare_exchange_strong(expect, ptr);
      if(!exchanged) {
          delete ptr;
      }
  }
}




void PerformancePayloadFromBinnedTFormula::printFormula(PerformanceResult::ResultType res,BinningPointByMap point) const {
  check();
  //
  // which formula to use?
  //
  if (resultPos(res) == PerformancePayloadFromBinnedTFormula::InvalidPos)  {
    cout << "Warning: result not available!" << endl;
  }
  
  // nice, what to do here???
  TFormula * formula = getFormula(res, point);
  unsigned int whichone;
  isOk(point,whichone);
  cout << "-- Formula: " << formula->GetExpFormula("p") << endl;
  // prepare the vector to pass, order counts!!!
  //
  std::vector<BinningVariables::BinningVariablesType> t = myBinning();
  
  for (std::vector<BinningVariables::BinningVariablesType>::const_iterator it = t.begin(); it != t.end();++it){
    int pos = limitPos(*it);
    std::pair<float, float> limits = (pls[whichone].limits())[pos];
    cout << "      Variable: " << *it << " with limits: " << "from: " << limits.first  << " to: " << limits.second << endl;
  }

}

#include "FWCore/Utilities/interface/typelookup.h"
TYPELOOKUP_DATA_REG(PerformancePayloadFromBinnedTFormula);
