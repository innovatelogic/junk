#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>

#include <gtest/gtest.h>

using namespace clang;

class StatementVisitor : public clang::RecursiveASTVisitor<StatementVisitor> {
public:
    explicit StatementVisitor(clang::ASTContext &context) 
        : context(context), sourceManager(context.getSourceManager()), inMainFunction(false) {}

    bool VisitFunctionDecl(clang::FunctionDecl *f) {
        // Check if the function name is "main"
        if (f->isThisDeclarationADefinition() && f->getNameInfo().getName().getAsString() == "main") {
            inMainFunction = true;
            TraverseStmt(f->getBody());  // Traverse only the body of main
            inMainFunction = false;
            return false;  // Skip other declarations once "main" is found and visited
        }
        return true;
    }

    bool VisitStmt(clang::Stmt *s) {
        if (inMainFunction) {
            clang::SourceRange range = s->getSourceRange();
            if (range.isValid()) {
                clang::StringRef stmtText = clang::Lexer::getSourceText(
                    clang::CharSourceRange::getTokenRange(range),
                    sourceManager, context.getLangOpts()
                );
                llvm::outs() << stmtText << "\n";
            }
        }
        return true;
    }

private:
    clang::ASTContext &context;
    clang::SourceManager &sourceManager;
    bool inMainFunction;
};

class StatementASTConsumer : public clang::ASTConsumer {
public:
    void HandleTranslationUnit(clang::ASTContext &context) override {
        StatementVisitor visitor(context);
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};

class StatementFrontendAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &, llvm::StringRef) override {
        return std::make_unique<StatementASTConsumer>();
    }
};


TEST(StatementVisitor, AST_Parse)
{
    const char *code = R"(
    #include <iostream>
    int main()
    {
        int a = 1;
        int b = 2;
        int c = a + b;
        std::cout << "Hello, World!" << c << std::endl;
        return 0;
    }
    )";

    if (!clang::tooling::runToolOnCodeWithArgs(std::make_unique<StatementFrontendAction>(),
                                        code,
                                        {"-x", "c++", "-std=c++20"}))
    {
        std::cerr << "Error: Tool did not run correctly.\n";
    }


}