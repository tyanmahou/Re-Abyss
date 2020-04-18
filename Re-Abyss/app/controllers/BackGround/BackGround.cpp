#include "BackGround.hpp"
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>

namespace abyss
{
    BackGround::BackGround(const std::shared_ptr<IBackGroundService>& service)
    {
        BackGroundTranslator translator;
        for (const auto& entity : service->getBgs()) {
            m_view.addBackGround(translator.toVM(entity));
        }
    }
    void BackGround::draw(const CameraView& camera) const
    {
        m_view.draw(camera);
    }
}
