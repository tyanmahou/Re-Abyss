#include "LogoCtrl.hpp"
#include <abyss/params/UI/Title/LogoParam.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title::Logo
{
    LogoCtrl::LogoCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_timer(LogoParam::Step::TimeSec)
    {
    }
    void LogoCtrl::onUpdate()
    {
        if (this->isEnd()) {
            return;
        } else if (m_phase == Phase::Start) {
            m_phase = Phase::Step1;
            m_timer.start();
        }

        if (m_timer.reachedZero()) {
            m_phase = static_cast<Phase>(static_cast<int32>(m_phase) + 1);
            m_timer.restart();
        }
    }
    double LogoCtrl::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool LogoCtrl::isEnd() const
    {
        return m_phase == Phase::End;
    }
    std::pair<s3d::Optional<LogoCtrl::ViewParam>, s3d::Optional<LogoCtrl::ViewParam>>
        LogoCtrl::getViewParams() const
    {
        const auto& basePos = LogoParam::Step::BasePos;
        const auto& endPos = LogoParam::End::Pos;
        const auto& moveOffset = LogoParam::Step::MoveOffset;
        const auto& moveDiff = LogoParam::Step::MoveDiff;

        const auto moveOffset2 = Vec2{ -moveOffset.x, moveOffset.y };
        const auto moveDiff2 = Vec2{ -moveDiff.x,  moveDiff.y };

        double time0_1 = this->time0_1();

        switch (m_phase) {
        case Phase::Step1:
        {
            const auto offset = moveOffset - time0_1 * moveDiff;
            return {
                ViewParam{
                    .pos = basePos + offset,
                    .alpha = 0.5,
                },
                s3d::none,
            };
        }
        break;
        case Phase::Step2:
        {
            const auto offset = -moveOffset + time0_1 * moveDiff;
            return {
                ViewParam{
                    .pos = basePos + offset,
                    .alpha = 0.5,
                },
                s3d::none,
            };
        }
        break;
        case Phase::Step3:
        {
            const auto offset = moveOffset2 - time0_1 * moveDiff2;
            return {
                ViewParam{
                    .pos = basePos + offset,
                    .alpha = 0.5,
                },
                s3d::none,
            };
        }
        break;
        case Phase::Step4:
        {
            const auto offset = -moveOffset2 + time0_1 * moveDiff2;
            return {
                ViewParam{
                    .pos = basePos + offset,
                    .alpha = 0.5,
                },
                s3d::none,
            };
        }
        break;
        case Phase::Step5:
        {
            auto offset1 = -moveOffset + time0_1 * moveDiff;
            offset1.y = 0;
            auto offset2 = moveOffset - time0_1 * moveDiff;
            offset2.y = 0;

            return {
                ViewParam{
                    .pos = endPos + offset1,
                    .alpha = 0.5,
                },
                ViewParam{
                    .pos = endPos + offset2,
                    .alpha = 0.5,
                },
            };
        }
        break;
        case Phase::End:
        {
            return {
                ViewParam{
                    .pos = endPos,
                    .alpha = 1.0
                },
                s3d::none
            };
        }
        break;
        default:
            return { s3d::none, s3d::none };
        }
    }
}
