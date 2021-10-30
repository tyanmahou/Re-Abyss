#include "Evaluator.hpp"

namespace Mns
{
    Evaluator::Evaluator(std::unique_ptr<IEvalImpl>&& pImpl):
        m_pImpl(std::move(pImpl))
    {}
    void Evaluator::eval(Ast::Root * root)
    {
        if (!root) {
            return;
        }
        for (auto&& pStatement : root->statements) {
            if (auto tag = std::dynamic_pointer_cast<Ast::TagStatement>(pStatement)) {
                m_pImpl->eval(*tag);
            } else if (auto name = std::dynamic_pointer_cast<Ast::NameStatement>(pStatement)) {
                m_pImpl->eval(*name);
            } else if (auto text = std::dynamic_pointer_cast<Ast::TextStatement>(pStatement)) {
                m_pImpl->eval(*text);
            }
        }
    }
}
