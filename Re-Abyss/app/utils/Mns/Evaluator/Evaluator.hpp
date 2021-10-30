#pragma once
#include <abyss/utils/Mns/Evaluator/IEvalImpl.hpp>
#include <abyss/utils/Mns/Ast/Root.hpp>

namespace Mns
{
    class Evaluator
    {
    public:
        Evaluator(IEvalImpl* pImpl);

        void eval(Ast::Root* root);
    private:
        IEvalImpl* m_pImpl;
    };
}
