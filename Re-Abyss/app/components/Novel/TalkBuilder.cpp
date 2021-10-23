#include "TalkBuilder.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/components/Novel/Common/ColorTag.hpp>
#include <abyss/components/Novel/Common/MessageStream.hpp>
#include <abyss/components/Novel/Common/WaitInput.hpp>
#include <abyss/components/Novel/Common/WaitTime.hpp>
#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <Siv3D.hpp>

//namespace abyss::Event::Talk
//{
//    void TalkBuilder::Build(EventObj* pEvent, const s3d::String& path)
//    {
//        // TODO リソースロード経由にする
//        auto fixPath = FileUtil::FixRelativePath(path);
//        JSON json = JSON::Load(fixPath);
//        if (!json) {
//            return;
//        }
//
//        // 顔グラフィック
//        auto faceTableModel = std::make_shared<FaceTableModel>();
//        {
//            for (const auto& elm : json[U"actors"].arrayView()) {
//                faceTableModel->add(
//                    elm[U"name"].getString(),
//                    elm[U"path"].getString()
//                );
//            }
//        }
//        // トリガー
//        TriggerFactory triggerFactory;
//        {
//            json[U"build_id"].getOpt<String>().then([&](const String& name) {
//                // イベントビルド
//                if (name == U"BossTalk0-0") {
//                    return BossTalk0_0::Build(triggerFactory);
//                }
//            });
//        }
//
//        // 会話制御
//        auto talkCtrl = pEvent->attach<TalkCtrl>(pEvent);
//
//        for (auto&& event : json[U"events"].arrayView()) {
//            if (auto&& trigger = event[U"trigger"].getOpt<String>(); trigger) {
//                // トリガーイベント
//                auto talkObj = talkCtrl->create();
//                if (auto&& builder = triggerFactory[*trigger]) {
//                    builder(talkObj.get());
//                } else {
//#if ABYSS_DEBUG
//                    Debug::LogWarn << U"Not found trigger:{}"_fmt(*trigger);
//#endif
//                }
//            } else if (auto&& serif = event[U"serif"]; serif.isObject()) {
//                // セリフ
//                OldSerifModel model;
//                serif[U"actor"].getOpt<String>().then([&model](const String& actor) {
//                    model.setActorName(actor);
//                });
//                String side = serif[U"side"].getOr<String>(U"left");
//                model.setSide(side == U"left" ? OldSerifModel::Side::Left : OldSerifModel::Side::Right);
//
//                for (auto&& message : serif[U"messages"].arrayView()) {
//                    for (auto&& [kind, m] : message) {
//                        model.addMessage(OldSerifModel::Message{ kind,  m.get<String>() });
//                    }
//                }
//                auto talkObj = talkCtrl->create();
//                talkObj->attach<OldSerifCtrl>(talkObj.get(), model);
//                talkObj->attach<FaceTable>(faceTableModel);
//            }
//        }
//    }
//}

namespace abyss::Novel
{
    void TalkBuilder::Build(TalkObj* pTalk, const s3d::String& path)
    {
        const auto& engine = pTalk->engine();

        engine->addCommand<MessageStream>(U"ああああああ");
        engine->addCommand<WaitTime>(1.0s);
        engine->addCommand<MessageStream>(U".");
        engine->addCommand<WaitTime>(1.0s);
        engine->addCommand<MessageStream>(U".");
        engine->addCommand<WaitTime>(1.0s);
        engine->addCommand<MessageStream>(U".");
        engine->addCommand<WaitTime>(1.0s);
        engine->addCommand<ColorTag>(s3d::Palette::Red);
        engine->addCommand<MessageStream>(U"いいいうふぃふぃふぃｙふぃふぃふぃ\n");
        engine->addCommand<WaitInput>();
        engine->addCommand<ColorTag>(s3d::none);
        engine->addCommand<MessageStream>(U"うううううううううううう\nああああ");
        engine->addCommand<WaitInput>();

        pTalk->attach<MessageBox>(pTalk);
    }
}
