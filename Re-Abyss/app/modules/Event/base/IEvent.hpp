#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Event
{
    class StreamHandler;

    class IEvent final : public GameObject
    {
    private:
        Ref<StreamHandler> m_stream;
        bool m_isWorldStop = true;
    public:
        IEvent();

        /// <summary>
        /// イベントの更新
        /// </summary>
        /// <returns></returns>
        bool update();

        void setIsWorldStop(bool isWorldStop)
        {
            m_isWorldStop = isWorldStop;
        }

        bool isWorldStop() const
        {
            return m_isWorldStop;
        }
    };
}