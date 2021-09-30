#include "Builder.hpp"
#include <abyss/types/Forward.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/components/Actor/Common/CustomDraw.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Demo/DemoCtrl.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Head/HeadVM.hpp>
#include <abyss/views/util/MaskUtil/MaskUtil.hpp>

namespace
{
    class Drawer;
}
namespace abyss::Actor::Enemy::CodeZero::Demo
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos)
    {
        // デモ制御
        {
            pActor->attach<DemoCtrl>(pActor)
                ->setPos(pos + s3d::Vec2{ 0, 400 })
                .setTargetPos(pos);
        }
        // 描画制御
        {
            pActor->attach<CustomDraw>()
                ->setDrawer<Drawer>(pActor);
        }
    }
}

namespace
{
    using namespace abyss;
    using abyss::Actor::ActorObj;
    using abyss::Actor::CustomDraw;
    using namespace abyss::Actor::Enemy::CodeZero;
    using namespace abyss::Actor::Enemy::CodeZero::Demo;

    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(ActorObj* pActor):
            m_pActor(pActor),
            m_bodyVM(std::make_unique<Body::BodyVM>()),
            m_headVM(std::make_unique<Head::HeadVM>()),
            m_leftHandVM(std::make_unique<Hand::HandVM>(Forward::Left)),
            m_rightHandVM(std::make_unique<Hand::HandVM>(Forward::Right))
        {}
        void onStart()override
        {
            m_demoCtrl = m_pActor->find<DemoCtrl>();
        }

        void onDraw() const override
        {
            const auto& pos = m_demoCtrl->getPos();
            const auto& targetPos = m_demoCtrl->getTargetPos();
            const s3d::RectF maskArea(targetPos.x - Constants::GameScreenSize.x / 2.0f, targetPos.y + 140, Constants::GameScreenSize.x, 120);

            {
                auto mask = MaskUtil::Instance().notEqual([maskArea] {
                    maskArea.draw(s3d::Palette::Black);
                });

                m_bodyVM->setPos(pos).draw();
                double time = m_pActor->getTimeSec();
                m_headVM->setTime(time).setPos(pos + Param::Head::Offset).draw();
                m_leftHandVM->setTime(time).setPos(pos + s3d::Vec2{ 110, 90 }).draw();
                m_rightHandVM->setTime(time).setPos(pos + s3d::Vec2{ -110, 90 }).draw();
            }
        }
    private:
        ActorObj* m_pActor;
        std::unique_ptr<Body::BodyVM> m_bodyVM;
        std::unique_ptr<Head::HeadVM> m_headVM;
        std::unique_ptr<Hand::HandVM> m_leftHandVM;
        std::unique_ptr<Hand::HandVM> m_rightHandVM;

        Ref<DemoCtrl> m_demoCtrl;
    };
}