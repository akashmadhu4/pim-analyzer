#include <stdio.h>
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/ADT/StringRef.h"
#include <iostream>

static llvm::cl::OptionCategory PIMAnalyzerCategory("PIM Analyzer Options");

static llvm::cl::opt<bool> VerifyAllocations(
    "verify-alloc",
    llvm::cl::desc("Enable DPU allocation verification"),
    llvm::cl::cat(PIMAnalyzerCategory));

static llvm::cl::opt<bool> CheckMRAMTransfers(
    "check-mram",
    llvm::cl::desc("Enable MRAM transfer rules checking"),
    llvm::cl::init(true),  
    llvm::cl::cat(PIMAnalyzerCategory));



 std::vector<std::string> getAllSourceFiles(const std::string &Path) {
    std::vector<std::string> Sources;
    std::error_code EC;
    
    if (llvm::sys::fs::is_directory(Path)) {
        for (llvm::sys::fs::recursive_directory_iterator It(Path, EC), End;
             It != End; It.increment(EC)) {
            if (EC) {
                llvm::errs() << "Error in Accessing " << It->path() << ": " 
                            << EC.message() << "\n";
                continue;
            }
            
            llvm::StringRef Extension = llvm::sys::path::extension(It->path());
            if (Extension == ".c" || Extension == ".cpp" || 
                Extension == ".cc" || Extension == ".cxx") {
                Sources.push_back(It->path());
            }
        }
    } else if (llvm::sys::fs::exists(Path)) {
        Sources.push_back(Path);
    }
    
    return Sources;
}   


int main(int argc,const char** argv){

    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(
        argc, argv, PIMAnalyzerCategory);

    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError(); 
        return 1;
    }


    clang::tooling::CommonOptionsParser &OptionsParser = *ExpectedParser;

    auto Sources = getAllSourceFiles(OptionsParser.getSourcePathList()[0]);

    if (Sources.empty()) {
        llvm::errs() << "Error: No source files found\n";
        return 1;
    }

     //printing all the source files for analaying
    std::for_each(Sources.begin(),Sources.end(),[](const std::string &source){ 
        std::cout << source << "\n";
    });

    





    return 0;
}