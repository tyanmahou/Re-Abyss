#include <abyss/utils/NeptScript/Script/Script.hpp>

namespace abyss::Nept
{
    class Script::Impl
    {
    public:
        Impl(const s3d::FilePath& path)
        {}
    private:
    };
    Script::Script(const s3d::FilePath& path) :
        m_pImpl(std::make_shared<Impl>(path))
    {}
}
