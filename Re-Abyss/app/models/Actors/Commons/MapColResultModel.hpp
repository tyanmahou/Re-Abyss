#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPrePhysicsModel.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/ColDirection.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class TerrainModel;

    class MapColResultModel : 
        public IComponent,
        public IPrePhysicsModel
    {
    private:
        s3d::Array<Ref<TerrainModel>> m_results;
        ColDirection m_col;
        IActor* m_pActor;
    public:
        MapColResultModel(IActor* pActor);

        void add(ColDirection col);

        void add(const Ref<TerrainModel>& terrain, ColDirection col);
        void onPrePhysics() final;

        bool isHitGround() const;

        bool isHitWall() const;

        bool isHitWall(Forward forward) const;

        bool isHitAny() const;

        const s3d::Array<Ref<TerrainModel>>& getResults() const
        {
            return m_results;
        }

        s3d::Array<IActor*> getHitActors()const;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<MapColResultModel>
    {
        using Base = IPrePhysicsModel;
    };
}
