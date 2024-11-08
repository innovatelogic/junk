#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>

#include <gtest/gtest.h>

using namespace clang;

class StatementVisitor : public RecursiveASTVisitor<StatementVisitor> {
public:
    explicit StatementVisitor(ASTContext &context) 
        : context(context), sourceManager(context.getSourceManager()) {}

    bool VisitStmt(Stmt *s) {

        //s->dump();
        // Get the source range of the statement
        SourceRange range = s->getSourceRange();
        
        // Print the exact source code for the statement
        if (range.isValid()) {
            StringRef stmtText = Lexer::getSourceText(CharSourceRange::getTokenRange(range),
                                                      sourceManager, 
                                                      context.getLangOpts());
            llvm::outs() << stmtText << "\n";
        }
        return true;
    }

private:
    ASTContext &context;
    SourceManager &sourceManager;
};

class StatementASTConsumer : public ASTConsumer {
public:
    void HandleTranslationUnit(ASTContext &context) override {
        StatementVisitor visitor(context);
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};

class StatementFrontendAction : public ASTFrontendAction {
public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &, llvm::StringRef) override {
        return std::make_unique<StatementASTConsumer>();
    }
};

TEST(StatementVisitor, basic_test)
{
    const char *code = R"(
    #include <vector>
    #include <unordered_set>
    #include <iostream>
    int longest_streak_fixed(const std::vector<int> &nums)
    {
        if (nums.empty()){
        return 0;
    }

    int max_len = 1;

    std::unordered_set<int> num_set(nums.begin(), nums.end());
    std::unordered_map<int, int> dyn_precalc_seq;

    for (auto &n : num_set)
    {
        if (num_set.count(n - 1) == 0)
        {
            int len = 1;
            int curr_n = n + 1;

            while (num_set.count(curr_n) > 0)
            {
                auto iter_find = dyn_precalc_seq.find(curr_n);
                if (iter_find != std::end(dyn_precalc_seq)) {
                    len += iter_find->second;
                    break;
                }

                ++len;
                ++curr_n;
            }

            max_len = std::max(max_len, len);

            dyn_precalc_seq[n] = len;
        }
    }

    return max_len;
    }
    void main()
    {
        std::vector<int> nums = {1, 0, -1};
        longest_streak_fixed(nums);
    }
    )";

    if (!clang::tooling::runToolOnCode(std::make_unique<StatementFrontendAction>(), code, {"-std=c++17"})) {
        std::cerr << "Error: Tool did not run correctly.\n";
    }


}