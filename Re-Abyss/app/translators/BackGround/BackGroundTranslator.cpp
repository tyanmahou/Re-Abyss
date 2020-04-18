#include "BackGroundTranslator.hpp"
#include <abyss/entities/BackGround/BackGroundEntity.hpp>
#include <abyss/views/BackGround/BackGroundVM.hpp>

namespace abyss
{
    BackGroundVM abyss::BackGroundTranslator::toVM(const BackGroundEntity& entity) const
    {
        return BackGroundVM(
            entity.filePath, 
            entity.offset, 
            entity.loop,
            entity.rate
        );
    }
}
