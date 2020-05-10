#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;

    class ParentCtrlModel : public IComponent
    {
        CodeZeroActor* m_parent;
        Ref<HPModel> m_hp;
    public:
        ParentCtrlModel(CodeZeroActor* parent);

        void setup() override;
        CodeZeroActor* getParent()const
        {
            return m_parent;
        }

        Ref<HPModel> getHp()const;

        const s3d::Vec2& getPos() const;
    };
}