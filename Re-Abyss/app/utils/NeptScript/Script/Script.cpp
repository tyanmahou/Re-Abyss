#include <abyss/utils/NeptScript/Script/Script.hpp>
#include <abyss/utils/NeptScript/Script/Lexer/Lexer.hpp>
#include <abyss/utils/NeptScript/Script/Parser/Parser.hpp>


namespace abyss::Nept
{
    class Script::Impl
    {
    public:
        Impl(const s3d::FilePath& path):
            m_lexer(path),
            m_parser(m_lexer.getTokens())
        {}
    private:
        Lexer m_lexer;
        Parser m_parser;
    };
    Script::Script(const s3d::FilePath& path) :
        m_pImpl(std::make_shared<Impl>(path))
    {}
}
