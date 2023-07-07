#include <abyss/utils/NeptScript/Script.hpp>
#include <abyss/utils/NeptScript/Lexer/Lexer.hpp>
#include <abyss/utils/NeptScript/Parser/Parser.hpp>
#include <abyss/utils/NeptScript/Evaluator/Evaluator.hpp>

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
            evaluator.eval(m_parser.root().get());
            if (evalImpl) {
                evalImpl->error(m_parser.errors());
            }
        }

        bool isValid() const
        {
            return !m_lexer.getTokens().isEmpty();
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
    Script::operator bool() const noexcept
    {
        if (!m_pImpl) {
            return false;
        }
        return m_pImpl->isValid();
    }
}
