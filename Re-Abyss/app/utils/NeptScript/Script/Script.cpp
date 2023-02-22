#include <abyss/utils/NeptScript/Script/Script.hpp>
#include <abyss/utils/NeptScript/Script/Lexer/Lexer.hpp>
namespace abyss::Nept
{
    class Script::Impl
    {
    public:
        Impl(const s3d::FilePath& path):
            m_lexer(path)
        {}
    private:
        Lexer m_lexer;
    };
    Script::Script(const s3d::FilePath& path) :
        m_pImpl(std::make_shared<Impl>(path))
    {}
}
