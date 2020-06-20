#include "TalkService.hpp"
#include <Siv3D.hpp>

#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>
#include <abyss/controllers/Event/Talk/base/TriggerManager.hpp>
#include <abyss/controllers/Event/Talk/base/Serif.hpp>
#include <abyss/controllers/Event/Talk/base/TriggerEvent.hpp>

#include <abyss/controllers/Event/Talk/BossTalk0_0/Build.hpp>

#include <abyss/models/Event/Talk/SerifModel.hpp>

//todo消す
#include <abyss/utils/FileUtil/FileUtil.hpp>

namespace abyss::Event::Talk
{
    std::shared_ptr<TalkEvent> TalkService::load(const s3d::String& path)
    {
        auto talk = std::make_shared<TalkEvent>();
        // todo リソースロード経由にする
        auto fixPath = FileUtil::FixRelativePath(path);
        JSONReader json(fixPath);
        if (!json) {
            return talk;
        }
        // 顔グラフィック
        auto faceManager = std::make_shared<FaceManager>();
        for (const auto& elm : json[U"actors"].arrayView()) {
            faceManager->add(
                elm[U"name"].getString(),
                elm[U"path"].getString()
            );
        }
        auto triggerManager = std::make_shared<TriggerManager>();
        for (const auto& event : json[U"events"].arrayView()) {
            if (const auto& trigger = event[U"trigger"].getOpt<String>(); trigger) {
                // トリガーイベント
                auto triggerEvent = std::make_shared<TriggerEvent>();
                triggerEvent->setName(*trigger);
                triggerEvent->setTriggerManager(triggerManager);

                talk->addEvent(triggerEvent);
            } else if(const auto& serif = event[U"serif"]; serif.isObject()){
                auto model = std::make_shared<SerifModel>();
                serif[U"actor"].getOpt<String>().then([&model](const String& actor) {
                    model->setActorName(actor);
                });
                String side = serif[U"side"].getOr<String>(U"left");
                model->setSide(side == U"left" ? SerifModel::Side::Left : SerifModel::Side::Right);

                for (const auto& message : serif[U"messages"].arrayView()) {
                    for (const auto& [kind, m] : message.objectView()) {
                        model->addMessage(SerifModel::Message{ kind,  m.get<String>() });
                    }
                }

                auto serifEvent = std::make_shared<Serif>();
                serifEvent->setModel(model);
                serifEvent->setFaceManager(faceManager);

                talk->addEvent(serifEvent);
            }
        }
        json[U"build_id"].getOpt<String>().then([&manager = *triggerManager](const String& name) {
            // イベントビルド
            if (name == U"BossTalk0-0") {
                return BossTalk0_0::Build(manager);
            }
        });
        return talk;
    }
}

