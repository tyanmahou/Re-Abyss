#pragma once

namespace abyss::Nept
{
    class IEvaluator;
    namespace Ast
    {
        class Root;
    }

    class Evaluator
    {
    public:
        Evaluator(IEvaluator* pImpl);

        void eval(Ast::Root* root);
    private:
        IEvaluator* m_pImpl;
    };
}
