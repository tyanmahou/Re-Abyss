#pragma once
#include <memory>
#include <abyss/services/Decor/base/IDecorService.hpp>

#include <Emaject.hpp>

namespace abyss::decor
{
    class IDecorDataStore;

    class DecorService : public IDecorService
    {
        s3d::Array<std::shared_ptr<DecorEntity>> m_front;
        s3d::Array<std::shared_ptr<DecorEntity>> m_back;
        s3d::Array<std::shared_ptr<DecorEntity>> m_custom;
    public:
        INJECT_CTOR(DecorService(
            std::shared_ptr<IDecorDataStore> decor,
            std::shared_ptr<IGimmickDataStore> gimmick,
            std::shared_ptr<IMapDataStore> map
        ));
        const s3d::Array<std::shared_ptr<DecorEntity>>& getFront() const override
        {
            return m_front;
        }
        const s3d::Array<std::shared_ptr<DecorEntity>>& getBack() const override
        {
            return m_back;
        }
        const s3d::Array<std::shared_ptr<DecorEntity>>& getCustom() const override
        {
            return m_custom;
        }
    };
}