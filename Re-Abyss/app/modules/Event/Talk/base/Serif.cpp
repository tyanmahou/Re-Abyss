#include "Serif.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Event/Talk/base/FaceManager.hpp>
#include <abyss/models/Event/Talk/SerifModel.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/modules/UI/Serif/Serif.hpp>

namespace abyss::Event::Talk
{
    Serif::Serif():
        m_serif(std::make_shared<SerifModel>())
    {}
    void Serif::setModel(const std::shared_ptr<SerifModel>& model)
    {
        m_serif = model;
    }
    void Serif::setFaceManager(const std::shared_ptr<FaceManager>& faceManager)
    {
        m_faceManager = faceManager;
    }
    void Serif::onStart()
    {
        m_pManager->getModule<UI>()->create<ui::Serif>(m_serif, m_faceManager);
    }
    bool Serif::update([[maybe_unused]] double dt)
    {
        return m_serif->update();
    }
    void Serif::onEnd()
    {}
}
