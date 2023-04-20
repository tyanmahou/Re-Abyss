#include <abyss/scenes/Fade/SceneFader.hpp>

namespace abyss::Fade
{
    class SceneFader::Impl
    {
    public:
        Impl()
        {

        }
    };

    SceneFader::SceneFader()
        :m_pImpl(std::make_unique<Impl>())
    {}
    SceneFader::~SceneFader()
    {}
    void SceneFader::update()
    {

    }
    void SceneFader::draw() const
    {

    }
}
