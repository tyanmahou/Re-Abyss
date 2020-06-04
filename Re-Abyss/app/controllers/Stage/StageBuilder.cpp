#include "StageBuilder.hpp"

#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>

namespace abyss
{
    void StageLoader::initBackGround(BackGround& backGround)
    {
        BackGroundTranslator translator;
        for (const auto& entity : m_backGroundService->getBgs()) {
            backGround.add(translator.toVM(entity));
        }
    }
}
