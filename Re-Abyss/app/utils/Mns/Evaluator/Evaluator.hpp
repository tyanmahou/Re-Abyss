#pragma once
#include <abyss/utils/Mns/Evaluator/IEvalImpl.hpp>
#include <abyss/utils/Mns/Ast/Root.hpp>

namespace Mns
{
    class Evaluator
    {
    public:
        Evaluator(std::unique_ptr<IEvalImpl>&& pImpl);

        void eval(Ast::Root* root);
    private:
        std::unique_ptr<IEvalImpl> m_pImpl;
    };
}
