#include "StageData.hpp"

#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>

namespace abyss
{
    StageData::StageData(std::shared_ptr<IBackGroundService>, std::shared_ptr<IDecorService>, std::shared_ptr<IDecorGraphicsService>, std::shared_ptr<IStageService>)
    {}
    //void StageData::initBackGround(BackGround& backGround)
    //{
    //    BackGroundTranslator translator;
    //    for (const auto& entity : m_backGroundService->getBgs()) {
    //        backGround.add(translator.toVM(entity));
    //    }
    //}
}
