#include "Serif.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>

namespace abyss::Event::Talk
{
    Serif::Serif()
    {}
    Serif::~Serif()
    {}
    void Serif::setModel(SerifModel && model)
    {
        m_serif = std::move(model);
    }
    void Serif::setFaceManager(const std::shared_ptr<FaceManager>& faceManager)
    {
        m_faceManager = faceManager;
    }
    bool Serif::update([[maybe_unused]] double dt)
    {
        return m_serif.update();
    }
}
