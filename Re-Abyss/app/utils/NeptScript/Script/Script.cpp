#include <abyss/utils/NeptScript/Script/Script.hpp>
#include <abyss/utils/NeptScript/Script/Lexer/Lexer.hpp>
#include <abyss/utils/NeptScript/Script/Parser/Parser.hpp>
#include <abyss/utils/NeptScript/Script/Evaluator/Evaluator.hpp>

namespace abyss::Nept
{
    class Script::Impl
    {
    public:
        Impl(const s3d::FilePath& path):
            m_lexer(path),
            m_parser(m_lexer.getTokens())
        {}

        void eval(IEvaluator* evalImpl)
        {
            Evaluator evaluator(evalImpl);
            return evaluator.eval(m_parser.root().get());
        }
    private:
        Lexer m_lexer;
        Parser m_parser;
    };
    Script::Script(const s3d::FilePath& path) :
        m_pImpl(std::make_shared<Impl>(path))
    {}
    void Script::eval(IEvaluator* evaluator)
    {
        if (!m_pImpl) {
            return;
        }
        m_pImpl->eval(evaluator);
    }
}
