#include <abyss/utils/Mns/Evaluator/Evaluator.hpp>

namespace Mns
{
    Evaluator::Evaluator(IEvalImpl* pImpl):
        m_pImpl(pImpl)
    {}
    void Evaluator::eval(Ast::Root * root)
    {
        if (!root) {
            return;
        }
        if (!m_pImpl) {
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
