#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Effect
{
    class Drawer final: public IComponent
    {
    public:
        Drawer(EffectObj* pObj);

        void onStart() override;
        void draw() const;
    private:
        EffectObj* m_pObj;
        s3d::Array<Coro::Task<>> m_drawTasks;
    };
}