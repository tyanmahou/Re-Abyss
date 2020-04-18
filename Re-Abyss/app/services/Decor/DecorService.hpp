#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/Decor/base/IDecorService.hpp>

namespace abyss
{
    class DecorService : public IDecorService
    {
        s3d::Array<std::shared_ptr<IDecorModel>> m_front;
        s3d::Array<std::shared_ptr<IDecorModel>> m_back;
        s3d::Array<std::shared_ptr<IDecorModel>> m_custom;
    public:
        DecorService(
            std::shared_ptr<IDecorDataStore> decor,
            std::shared_ptr<IGimmickDataStore> gimmick,
            std::shared_ptr<IMapDataStore> map
        );
        const s3d::Array<std::shared_ptr<IDecorModel>>& getFront() const override
        {
            return m_front;
        }
        const s3d::Array<std::shared_ptr<IDecorModel>>& getBack() const override
        {
            return m_back;
        }
        const s3d::Array<std::shared_ptr<IDecorModel>>& getCustom() const override
        {
            return m_custom;
        }

    };
}