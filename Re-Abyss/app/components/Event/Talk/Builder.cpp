#include "Builder.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>

#include <abyss/components/Event/Talk/TalkCtrl.hpp>
#include <abyss/components/Event/Talk/Common/Serif/SerifCtrl.hpp>
#include <abyss/components/Event/Talk/Common/Serif/FaceTable.hpp>
#include <abyss/components/Event/Talk/TriggerFactory.hpp>

#include <abyss/components/Event/Talk/BossTalk0_0/Build.hpp>

#include <abyss/models/Event/Talk/SerifModel.hpp>
#include <abyss/models/Event/Talk/FaceTableModel.hpp>

#include <Siv3D.hpp>
//todo消す
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Event::Talk
{
    void Builder::Build(IEvent* pEvent, const s3d::String& path)
    {
        // 世界停止はしない
        pEvent->setIsWorldStop(false);

        // todo リソースロード経由にする
        auto fixPath = FileUtil::FixRelativePath(path);
        JSONReader json(fixPath);
        if (!json) {
            return;
        }

        // 顔グラフィック
        auto faceTableModel = std::make_shared<FaceTableModel>();
        {
            for (const auto& elm : json[U"actors"].arrayView()) {
                faceTableModel->add(
                    elm[U"name"].getString(),
                    elm[U"path"].getString()
                );
            }
        }
        // トリガー
        TriggerFactory triggerFactory;
        {
            json[U"build_id"].getOpt<String>().then([&](const String& name) {
                // イベントビルド
                if (name == U"BossTalk0-0") {
                    return BossTalk0_0::Build(triggerFactory);
                }
            });
        }

        // 会話制御
        auto talkCtrl = pEvent->attach<TalkCtrl>(pEvent);

        for (const auto& event : json[U"events"].arrayView()) {
            if (const auto& trigger = event[U"trigger"].getOpt<String>(); trigger) {
                // トリガーイベント
                auto talkObj = talkCtrl->create();
                if (auto&& builder = triggerFactory[*trigger]) {
                    builder(talkObj.get());
                } else {
#if ABYSS_DEBUG
                    Debug::Log::PrintCache << U"Not found trigger:{}"_fmt(*trigger);
#endif
                }
            } else if (const auto& serif = event[U"serif"]; serif.isObject()) {
                // セリフ
                SerifModel model;
                serif[U"actor"].getOpt<String>().then([&model](const String& actor) {
                    model.setActorName(actor);
                });
                String side = serif[U"side"].getOr<String>(U"left");
                model.setSide(side == U"left" ? SerifModel::Side::Left : SerifModel::Side::Right);

                for (const auto& message : serif[U"messages"].arrayView()) {
                    for (const auto& [kind, m] : message.objectView()) {
                        model.addMessage(SerifModel::Message{ kind,  m.get<String>() });
                    }
                }
                auto talkObj = talkCtrl->create();
                talkObj->attach<SerifCtrl>(talkObj.get(), model);
                talkObj->attach<FaceTable>(faceTableModel);
            }
        }
    }
}