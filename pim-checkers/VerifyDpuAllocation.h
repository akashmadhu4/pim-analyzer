#ifndef VERIFY_ALLOCATIONS_CHECKER_H
#define VERIFY_ALLOCATIONS_CHECKER_H

#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"


namespace pim {

class VerifyDpuAllocationChecker 
    : public clang::ento::Checker<clang::ento::check::PreCall> {
  mutable std::unique_ptr<clang::ento::BugType> BT;

public:
  void checkPreCall(const clang::ento::CallEvent &Call, 
                   clang::ento::CheckerContext &C) const;
};

} 

#endif