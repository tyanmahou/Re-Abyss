#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/utils/Ref/Ref.hpp>


namespace abyss::Event
{
    class GamePause : public IEvent
    {
    private:
        bool m_waitFlag = true;
    public:
        GamePause();

        void onStart() override;
        bool update(double dt) override;
        void onEnd() override;
    };
}