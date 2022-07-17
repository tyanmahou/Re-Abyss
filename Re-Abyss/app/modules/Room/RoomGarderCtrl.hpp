#pragma once

namespace abyss::Room
{
    class RoomGarderCtrl
    {
    public:
        RoomGarderCtrl() = default;

        bool isLock() const
        {
            return m_isLock;
        }
        void lock()
        {
            this->setIslock(true);
        }
        void unlock()
        {
            this->setIslock(false);
        }
        void setIslock(bool isLock)
        {
            m_isLock = isLock;
        }
    private:
        bool m_isLock = false;
    };
}
