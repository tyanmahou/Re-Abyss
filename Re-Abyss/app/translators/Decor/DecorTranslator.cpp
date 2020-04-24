#include "DecorTranslator.hpp"
#include <Siv3D.hpp>

#include <abyss/models/Decor/Common/CommonDecorModel.hpp>
#include <abyss/models/Decor/Door/DoorDecorModel.hpp>
#include <abyss/models/Decor/Map/MapDecorModel.hpp>

#include <abyss/views/Decor/Common/CommonDecorVM.hpp>
#include <abyss/views/Decor/Door/DoorDecorVM.hpp>
#include <abyss/views/Decor/Map/MapDecorVM.hpp>

namespace abyss
{
    DecorTranslator::DecorTranslator(DecorGraphicsManager* manager):
        m_manager(manager)
    {}
    std::shared_ptr<IDecorModel> abyss::DecorTranslator::toModel(const DecorEntity& entity)const
    {
        RectF rect{ entity.pos - entity.size / 2.0, entity.size };
        auto quad = rect.rotatedAt(rect.bl(), s3d::ToRadians(entity.rotation));
        auto model = std::make_shared<CommonDecorModel>(
            entity.gId,
            quad,
            entity.isMirrored,
            entity.isFlipped
        );
        model->setType(DecorType::Common);
        return model;
    }
    std::shared_ptr<IDecorModel> DecorTranslator::toModel(const DoorEntity& entity)const
    {
        auto model = std::make_shared<DoorDecorModel>(entity.pos, entity.size, entity.kind);
        model->setType(DecorType::Door);
        return model;
    }
    std::shared_ptr<IDecorModel> DecorTranslator::toModel(const MapEntity& entity)const
    {
        RectF rect{ entity.pos - entity.size / 2.0, entity.size };
        auto model = std::make_shared<MapDecorModel>(entity.gId, rect);
        model->setType(DecorType::Map);
        return model;
    }
    std::shared_ptr<IDecorVM> DecorTranslator::toVM(const IDecorModel& model) const
    {
        switch (model.getType()) {
        case DecorType::Common:
        {
            return std::make_shared<CommonDecorVM>(m_manager, static_cast<const CommonDecorModel&>(model));
        }break;
        case DecorType::Door:
        {
            return std::make_shared<DoorDecorVM>(static_cast<const DoorDecorModel&>(model));
        }break;
        case DecorType::Map:
        {
            return std::make_shared<MapDecorVM>(m_manager, static_cast<const MapDecorModel&>(model));
        }break;
        default:
            break;
        }
        return nullptr;
    }
}
