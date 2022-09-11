#include <abyss/components/Cron/Common/RoomMoveCallbackCtrl.hpp>

#include <abyss/modules/Cron/base/Batch.hpp>
#include <abyss/modules/Room/IRoomMoveCallback.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Cron
{
    class RoomMoveCallbackCtrl::Impl : 
        public Room::IRoomMoveCallback
    {
    public:
        Impl(Batch* batch):
            m_batch(batch)
        {
        }
        void setup(Executer executer)
        {
            executer.onStart().addAfter<Room::IRoomMoveCallback>();
        }
        void onStart()
        {
            m_callbacks = m_batch->finds<Room::IRoomMoveCallback>();
        }
        void onCheckOut()
        {
            for (auto&& c : m_callbacks) {
                if (c) {
                    c->onCheckOut();
                }
            }
        }
        void onCheckIn()
        {
            for (auto&& c : m_callbacks) {
                if (c) {
                    c->onCheckIn();
                }
            }
        }
        RoomManager* roomManager()
        {
            return m_batch->getModule<RoomManager>();
        }
    private:
        Batch* m_batch;
        s3d::Array<Ref<Room::IRoomMoveCallback>> m_callbacks;
    };
    RoomMoveCallbackCtrl::RoomMoveCallbackCtrl(Batch* batch):
        m_pImpl(std::make_shared<Impl>(batch))
    {}

    void RoomMoveCallbackCtrl::setup(Executer executer)
    {
        m_pImpl->setup(executer);
    }

    void RoomMoveCallbackCtrl::onStart()
    {
        m_pImpl->onStart();
        if (auto roomManager = m_pImpl->roomManager()) {
            roomManager->addCallback(m_pImpl);
        }
    }
}
