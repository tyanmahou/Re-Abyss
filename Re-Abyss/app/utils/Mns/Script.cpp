#include "Script.hpp"
#include <abyss/utils/Mns/Lexer/Lexer.hpp>
#include <abyss/utils/Mns/Parser/Parser.hpp>
#include <abyss/utils/Mns/Evaluator/Evaluator.hpp>

namespace Mns
{
    class Script::Impl
    {
    public:
        Impl(const s3d::FilePath& path):
            m_lexer(path),
            m_parser(m_lexer.getTokens())
        {}

        void eval(IEvalImpl* evalImpl)
        {
            Evaluator evaluator(evalImpl);
            return evaluator.eval(m_parser.root().get());
        }
    private:
        Lexer m_lexer;
        Parser m_parser;
    };
    Script::Script(const s3d::FilePath& path):
        m_pImpl(std::make_shared<Impl>(path))
    {}
    void Script::eval(IEvalImpl * evaluator)
    {
        if (!m_pImpl) {
            return;
        }
        m_pImpl->eval(evaluator);
    }
}
