#include "Decor.hpp"
#include <abyss/models/Decor/base/IDecorModel.hpp>
#include <abyss/services/Decor/DecorService.hpp>
#include <abyss/translators/Decor/DecorTranslator.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss
{
    Decor::Decor(const std::shared_ptr<IDecorService>& service, const std::shared_ptr<DecorGraphicsManager>& manager):
        m_decorService(service),
        m_manager(manager)
    {}
    void Decor::init(const Camera& camera)
    {
        m_view.clear();

        DecorTranslator m_translator{ m_manager.get() };

        auto add = [&](s3d::int32 order, const s3d::Array<std::shared_ptr<IDecorModel>>& decors) {
            for (const auto& model : decors) {
                if (!model) {
                    continue;
                }
                bool isInScreen = model->isInScreen(camera.getCurrentRoom().getRegion());
                if (const auto& nextRoom = camera.nextRoom(); nextRoom) {
                    isInScreen |= model->isInScreen(nextRoom->getRegion());
                }
                if (!isInScreen) {
                    continue;
                }
                if (auto vm = m_translator.toVM(*model)) {
                    m_view.add(order, vm);
                }
            }
        };
        add(DecorOrder::Front, m_decorService->getFront());
        add(DecorOrder::Back, m_decorService->getBack());
        add(DecorOrder::Middle, m_decorService->getCustom());
    }
    void Decor::draw(s3d::int32 order, const s3d::RectF& screen) const
    {
        m_view.draw(order, screen);
    }
}
