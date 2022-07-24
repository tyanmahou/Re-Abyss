#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Types.hpp>

namespace abyss::Pause
{
    /// <summary>
    /// ポーズ管理
    /// </summary>
    class PauseManager
    {
    public:
        enum class DisableKind
        {
            Demo,
        };
    public:
        PauseManager();

        void setManager(Manager* pManager)
        {
            m_pManager = pManager;
        }
        void setPausable(bool isPausable, DisableKind kind);
        bool isPausable() const;

        void update();

    private:
        Manager* m_pManager = nullptr;
        Ref<Event::EventObj> m_obj;
        s3d::int32 m_pausaDisableBit{};
    };
}
