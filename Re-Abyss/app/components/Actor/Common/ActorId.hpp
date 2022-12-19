#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    class ActorId :
        public IComponent
    {
    public:
        ActorId(s3d::uint32 id);

        s3d::uint32 id() const
        {
            return m_id;
        }
    private:
        s3d::uint32 m_id;
    };
}
