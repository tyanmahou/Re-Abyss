#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Cron
{
    class RoomMoveCallbackCtrl :
        public IComponent
    {
        class Impl;
    public:
        RoomMoveCallbackCtrl(Batch* batch);

        void setup(Executer executer) override;
        void onStart() override;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}