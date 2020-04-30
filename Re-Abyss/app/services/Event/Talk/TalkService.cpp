#include "TalkService.hpp"
#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>
#include <abyss/controllers/Event/Talk/base/TriggerManager.hpp>
#include <abyss/controllers/Event/Talk/base/Serif.hpp>
#include <abyss/controllers/Event/Talk/base/TriggerEvent.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::Talk
{
    std::shared_ptr<TalkEvent> TalkService::load(const s3d::String& path)
    {
        auto talk = std::make_shared<TalkEvent>();

        JSONReader json(path);
        if (!json) {
            return talk;
        }
        auto faceManager = std::make_shared<FaceManager>();
        for (const auto& elm : json[U"actors"].arrayView()) {
            faceManager->add(
                elm[U"name"].getString(),
                elm[U"path"].getString()
            );
        }
        auto triggerManager = std::make_shared<TriggerManager>();
        for (const auto& elm : json[U"serifs"].arrayView()) {
            if (const auto& trigger = elm[U"trigger"].getOpt<String>(); trigger) {
                // トリガーイベント
                auto event = std::make_shared<TriggerEvent>();
                event->setName(*trigger);
                event->setTriggerManager(triggerManager);

                talk->addEvent(event);
            } else {
                SerifModel model;
                elm[U"actor"].getOpt<String>().then([&model](const String& actor) {
                    model.setActorName(actor);
                });
                elm[U"kind"].getOpt<String>().then([&model](const String& kind) {
                    model.setKind(kind);
                });
                String side = elm[U"side"].getOr<String>(U"left");
                model.setSide(side == U"left" ? SerifModel::Side::Left : SerifModel::Side::Right);

                for (const auto& message : elm[U"messages"].arrayView()) {
                    model.addMessage(message.get<String>());
                }

                auto serif = std::make_shared<Serif>();
                serif->setModel(std::move(model));
                serif->setFaceManager(faceManager);

                talk->addEvent(serif);
            }
        }
        return talk;
    }
}

