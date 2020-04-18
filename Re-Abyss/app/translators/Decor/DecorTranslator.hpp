#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class DecorTranslator
    {
        DecorGraphicsManager* m_manager = nullptr;
    public:
        DecorTranslator() = default;
        DecorTranslator(DecorGraphicsManager* manager);

        std::shared_ptr<IDecorModel> toModel(const DecorEntity& entity) const;
        std::shared_ptr<IDecorModel> toModel(const DoorEntity& entity)const;
        std::shared_ptr<IDecorModel> toModel(const MapEntity& entity)const;

        std::shared_ptr<IDecorVM> toVM(const IDecorModel& model)const;
    };
}