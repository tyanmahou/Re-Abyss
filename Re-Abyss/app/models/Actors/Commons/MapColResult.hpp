#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPrePhysicsModel.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/ColDirection.hpp>
#include <abyss/utils/Ref/Ref.hpp>

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

        void add(const Ref<TerrainModel>& terrain, ColDirection col);
        void onPrePhysics() final;
    };
}