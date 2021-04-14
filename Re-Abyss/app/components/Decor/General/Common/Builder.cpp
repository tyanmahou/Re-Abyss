#include "Builder.hpp"
#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/components/Decor/Commons/CommonBuilder.hpp>
#include <abyss/components/Decor/Commons/DecorInfo.hpp>
#include <abyss/components/Decor/Commons/CustomDraw.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Decor/Decor.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace
{
    class Drawer;
}
namespace abyss::decor::General::Common
{
    void Builder::Build(DecorObj* pObj, const CommonEntity& entity)
    {
        CommonBuilder::Build(pObj, BuildOption{}
            .setInitInfo(entity)
        );

        // 描画制御
        {
            pObj->attach<CustomDraw>()
                ->setDrawer<Drawer>(pObj);
        }
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::decor;

    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(DecorObj* pObj) :
            m_pObj(pObj)
        {}
        void onStart()override
        {
           m_info = m_pObj->find<DecorInfo>();
        }

        void onDraw() const override
        {
            auto quad = m_info->toQuad();
            auto camera = m_pObj->getModule<Camera>();
            if (!quad.intersects(camera->screenRegion())) {
                return;
            }
            auto decor = m_pObj->getModule<Decor>();
            auto time = m_pObj->getModule<GlobalTime>()->time();
            auto tex = decor
                ->getTexture(m_info->getGId(), time)
                .mirrored(m_info->isMirrored())
                .flipped(m_info->isFlipped());
            quad(tex).draw();
        }
    private:
        DecorObj* m_pObj;
        Ref<DecorInfo> m_info;
    };
}