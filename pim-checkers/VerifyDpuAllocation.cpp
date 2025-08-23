#include "VerifyDpuAllocation.h"
#include <iostream>



void pim::VerifyDpuAllocationChecker::checkPreCall(const clang::ento::CallEvent &Call,
    clang::ento::CheckerContext &C) const {
            std::cout<<"Inside the PreCall function of VerifyDpuAllocationChecker"<<std::endl;
            return;
    }