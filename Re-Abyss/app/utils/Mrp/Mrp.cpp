#include <abyss/utils/Mrp/Mrp.hpp>
#include <abyss/utils/Mrp/Lexer/Lexer.hpp>
#include <abyss/utils/Mrp/Parser/Parser.hpp>
namespace Mrp
{
    class Mrp::Impl
    {
    private:
        using Data = std::unique_ptr<s3d::HashTable<s3d::String, MrpGroup>>;
    public:
        Impl(s3d::FilePathView path) :
            m_lexer(path),
            m_parser(m_lexer.getTokens())
        {
            m_data = m_parser.group();
        }

        const Data& getData()
        {
            return m_data;
        }
    private:
        Lexer m_lexer;
        Parser m_parser;
        Data m_data;
    };

    Mrp::Mrp(s3d::FilePathView path):
        m_pImpl(std::make_shared<Impl>(path))
    {}
    Mrp::operator bool() const
    {
        if (!m_pImpl) {
            return false;
        }
        if (!m_pImpl->getData()) {
            return false;
        }
        return true;
    }
    Mrp::const_iterator Mrp::begin() const
    {
        return m_pImpl->getData()->begin();
    }
    Mrp::const_iterator Mrp::end() const
    {
        return m_pImpl->getData()->end();
    }
}
