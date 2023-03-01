#include <abyss/utils/NeptScript/Evaluator/Evaluator.hpp>
#include <abyss/utils/NeptScript/Evaluator/IEvaluator.hpp>
#include <abyss/utils/NeptScript/Ast/Root.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/BlockStatement.hpp>
#include <abyss/utils/NeptScript/Ast/Statement/SectionStatement.hpp>

namespace
{
    using namespace abyss::Nept;
    using namespace abyss::Nept::Ast;

    // Fwd
    void eval(IEvaluator* pImpl, const BlockStatement& statement);

    void eval(IEvaluator* pImpl, const CharaStatement& statement)
    {
        pImpl->eval(statement);
    }
    void eval(IEvaluator* pImpl, const CommandStatement& statement)
    {
        pImpl->eval(statement);
    }
    void eval(IEvaluator* pImpl, const TextStatement& statement)
    {
        pImpl->eval(statement);
    }
    void eval(IEvaluator* pImpl, const SectionStatement& statement)
    {
        pImpl->evalOnSectionStart(statement.section);
        eval(pImpl, *statement.block);
        pImpl->evalOnSectionEnd(statement.section);
    }
    void eval(IEvaluator* pImpl, s3d::Array<std::shared_ptr<IStatement>> statements)
    {
        for (auto&& pStatement : statements) {
            if (auto chara = std::dynamic_pointer_cast<CharaStatement>(pStatement)) {
                eval(pImpl, *chara);
            } else if (auto command = std::dynamic_pointer_cast<CommandStatement>(pStatement)) {
                eval(pImpl, *command);
            } else if (auto text = std::dynamic_pointer_cast<TextStatement>(pStatement)) {
                eval(pImpl, *text);
            } else if (auto block = std::dynamic_pointer_cast<BlockStatement>(pStatement)) {
                eval(pImpl, *block);
            } else if (auto section = std::dynamic_pointer_cast<SectionStatement>(pStatement)) {
                eval(pImpl, *section);
            }
        }
    }
    void eval(IEvaluator* pImpl, const BlockStatement& statement)
    {
        eval(pImpl, statement.statements);
    }
    void eval(IEvaluator* pImpl, const Root& root)
    {
        eval(pImpl, root.statements);
    }
}
namespace abyss::Nept
{
    using namespace Ast;

    Evaluator::Evaluator(IEvaluator* pImpl) :
        m_pImpl(pImpl)
    {}
    void Evaluator::eval(Ast::Root* root)
    {
        if (!root) {
            return;
        }
        if (!m_pImpl) {
            return;
        }
        ::eval(m_pImpl, *root);
    }
}
