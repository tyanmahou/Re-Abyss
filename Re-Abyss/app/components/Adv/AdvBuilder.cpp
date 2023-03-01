#include <abyss/components/Adv/AdvBuilder.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

#include <abyss/components/Adv/Common/Command/Bgm.hpp>
#include <abyss/components/Adv/Common/Command/CharaSetter.hpp>
#include <abyss/components/Adv/Common/Command/ClearMessage.hpp>
#include <abyss/components/Adv/Common/Command/ColorTag.hpp>
#include <abyss/components/Adv/Common/Command/MessageStream.hpp>
#include <abyss/components/Adv/Common/Command/NameSetter.hpp>
#include <abyss/components/Adv/Common/Command/PauseDisabled.hpp>
#include <abyss/components/Adv/Common/Command/ShakeTag.hpp>
#include <abyss/components/Adv/Common/Command/ShowHideMessage.hpp>
#include <abyss/components/Adv/Common/Command/SignalSend.hpp>
#include <abyss/components/Adv/Common/Command/SignalReceive.hpp>
#include <abyss/components/Adv/Common/Command/SkipEnabled.hpp>
#include <abyss/components/Adv/Common/Command/WaitInput.hpp>
#include <abyss/components/Adv/Common/Command/WaitTime.hpp>

#include <abyss/components/Adv/Common/MessageBox.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

#include <abyss/utils/NeptScript/Script/Script.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Adv;
    using namespace abyss::Nept;
    using namespace abyss::Nept::Ast;

    class Evaluator final : public IEvaluator
    {
    public:
        Evaluator(AdvObj* pObj) :
            m_pObj(pObj),
            m_pEngine(pObj->engine().get())
        {}
        ~Evaluator()
        {
            this->showHideMessage(false);
            this->buildTrigger(U"Teardown");
        }
    public:
        void eval(const CharaStatement& statement) override
        {
            // キャラ
            {
                s3d::Optional<CharaKind> kind = Enum::Parse<CharaKind>(statement.actor);

                s3d::Optional<Side> side;
                if (statement.look == LookType::Left) {
                    side = Side::Left;
                } else {
                    side = Side::Right;
                }
                s3d::Optional<Face> face;
                if (statement.emote) {
                    face = Face(*statement.emote);
                }
                this->buildChara(std::move(kind), std::move(side), std::move(face));
            }

            // 表示名
            if (statement.displayName) {
                m_pEngine->addCommand<NameSetter>(*statement.displayName);
            }
        }
        void eval(const CommandStatement& statement) override
        {
            const auto& command = statement.command;
            const auto& param = statement.rootParam;
            if (command == U"cm") {
                m_pEngine->addCommand<ClearMessage>();
            } else if (command == U"l") {
                m_pEngine->addCommand<WaitInput>();
            } else if (command == U"r") {
                m_pEngine->addCommand<MessageStream>(U"\n");
            } else if (command == U"color" && param) {
                m_pEngine->addCommand<ColorTag>(Color(*param));
            } else if (command == U"/color") {
                m_pEngine->addCommand<ColorTag>(s3d::none);
            } else if (command == U"shake") {
                m_pEngine->addCommand<ShakeTag>(true);
            } else if (command == U"/shake") {
                m_pEngine->addCommand<ShakeTag>(false);
            } else if (command == U"wait") {
                Duration time{};
                for (const auto& [key, value] : statement.params) {
                    if (key == U"time" && value) {
                        time = Duration(s3d::Parse<double>(*value));
                    }
                }
                m_pEngine->addCommand<WaitTime>(time);
            } else if (command == U"chara") {
                s3d::Optional<CharaKind> kind;
                if (param) {
                    kind = Enum::Parse<CharaKind>(*param);
                }
                s3d::Optional<Side> side;
                s3d::Optional<Face> face;
                for (const auto& [key, value] : statement.params) {
                    if (key == U"side" && value) {
                        if (*value == U"l") {
                            side = Side::Left;
                        } else if (*value == U"r") {
                            side = Side::Right;
                        }
                    } else if (key == U"face" && value) {
                        face = Face(*value);
                    }
                }
                this->buildChara(std::move(kind), std::move(side), std::move(face));
            } else if (command == U"build" && param) {
                this->buildTrigger(U"Teardown");
                m_build = param;
                this->buildTrigger(U"Setup");
            } else if (command == U"command" && param) {
                this->buildNativeCommand(*param);
            } else if (command == U"showmessage") {
                this->showHideMessage(true);
            } else if (command == U"hidemessage") {
                this->showHideMessage(false);
            } else if (command == U"send" && param) {
                auto func = this->findFunc<void(AdvObj*)>(*param);
                m_pEngine->addCommand<SignalSend>(func);
            } else if (command == U"receive" && param) {
                auto func = this->findFunc<bool(AdvObj*)>(*param);
                m_pEngine->addCommand<SignalReceive>(func);
            } else if (command == U"skippable") {
                m_pEngine->addCommand<SkipEnabled>(true);
            } else if (command == U"/skippable") {
                m_pEngine->addCommand<SkipEnabled>(false);
            } else if (command == U"pause-disabled") {
                m_pEngine->addCommand<PauseDisabled>(true);
            } else if (command == U"/pause-disabled") {
                m_pEngine->addCommand<PauseDisabled>(false);
            } else if (command == U"bgm") {
                Duration fade{ 2s };
                Bgm::Kind kind{};
                String path = U"";
                for (const auto& [key, value] : statement.params) {
                    if (key == U"play" && value) {
                        kind = Bgm::Kind::Play;
                        path = *value;
                    }if (key == U"stop") {
                        kind = Bgm::Kind::Stop;
                    } else if (key == U"stash") {
                        kind = Bgm::Kind::Stash;
                    } else if (key == U"stash-pop") {
                        kind = Bgm::Kind::StashPop;
                    } else if (key == U"fade" && value) {
                        fade = Duration(s3d::Parse<double>(*value));
                    }
                }
                m_pEngine->addCommand<Bgm>(kind, path, fade);
            }
        }
        void eval(const TextStatement& statement) override
        {
            this->showHideMessage(true);
            m_pEngine->addCommand<MessageStream>(statement.text);
        }

        void evalOnSectionStart(const s3d::String& section) override
        {
            m_blocks.push(section);
            if (auto blockFunc = this->findBlockFunc(section, U"Start")) {
                (*blockFunc)(m_pObj);
            }
        }
        void evalOnSectionEnd([[maybe_unused]]const s3d::String& section) override
        {
            if (m_blocks.empty()) {
                return;
            }
            if (auto blockFunc = this->findBlockFunc(m_blocks.top(), U"End")) {
                (*blockFunc)(m_pObj);
            }
            m_blocks.pop();
        }

        void error([[maybe_unused]]const s3d::Array<Nept::Error>& errors) override
        {
#if ABYSS_DEBUG
            for (const auto& error : errors) {
                Debug::Log::Error(error.message);
            }
#endif
        }
    private:
        void buildChara(s3d::Optional<CharaKind> kind, s3d::Optional<Side> side, s3d::Optional<Face> face)
        {
            // キャラか位置が変わったら切り替え
            const bool isChangeChara = kind && kind != m_charaKind;
            const bool isChangeSide = side && side != m_charaSide;
            bool isHide = isChangeChara || isChangeSide;
            if (isHide) {
                this->showHideMessage(false);
            }
            if (isChangeChara && !side) {
                side = Side::Left;
            }
            if (isChangeChara && !face) {
                face = Face{};
            }

            m_pEngine->addCommand<CharaSetter>(kind, side, face);
            m_charaKind = std::move(kind);
            m_charaSide = std::move(side);
        }
        void showHideMessage(bool isShow)
        {
            if (m_isVisibleMessage == isShow) {
                return;
            }
            m_isVisibleMessage = isShow;
            m_pEngine->addCommand<ShowHideMessage>(isShow);
        }
        bool buildNativeCommand(s3d::StringView name)
        {
            if (this->buildTrigger(name)) {
                return true;
            }
            if (auto func = this->findFunc<void(AdvObj*)>(name)) {
                (*func)(m_pObj);
                return true;
            }
            return false;
        }
        bool buildTrigger(s3d::StringView eventName)
        {
            if (!m_build) {
                return false;
            }
            if (auto buildFunc = findBuildFunc(eventName)) {
                (*buildFunc)(m_pObj);
                return true;
            }
            return false;
        }
        template<class T>
        auto findFunc(s3d::StringView name)
            -> decltype(Reflect<>::find<T>(U""))
        {
            if (auto func = Reflect<>::find<T>(
                U"abyss::Adv::{}::{}"_fmt(*m_build, name)
            )) {
                return func;
            }
            return Reflect<>::find<T>(
                U"abyss::Adv::{}"_fmt(name)
            );
        }
        auto findBuildFunc(s3d::StringView name)
            -> decltype(Reflect<>::find<void(AdvObj*)>(U""))
        {
            return Reflect<>::find<void(AdvObj*)>(
                U"abyss::Adv::{}::Builder::{}"_fmt(*m_build, name)
            );
        }
        auto findBlockFunc(s3d::StringView blockName, s3d::StringView name)
            -> decltype(Reflect<>::find<void(AdvObj*)>(U""))
        {
            return Reflect<>::find<void(AdvObj*)>(
                U"abyss::Adv::{}::Builder::{}::{}"_fmt(*m_build, blockName, name)
            );
        }
    private:
        AdvObj* m_pObj;
        Engine* m_pEngine;

        bool m_isVisibleMessage = false;
        s3d::Optional<CharaKind> m_charaKind;
        s3d::Optional<Side> m_charaSide;
        s3d::Optional<s3d::String> m_build;

        std::stack<s3d::String> m_blocks;
    };
}
namespace
{
    //using namespace abyss;
    //using namespace abyss::Adv;
    //using namespace Mns;
    //using namespace Mns::Ast;
    //class EvalImpl final : public IEvalImpl
    //{
    //public:
    //    EvalImpl(AdvObj* pObj):
    //        m_pObj(pObj),
    //        m_pEngine(pObj->engine().get())
    //    {}
    //    ~EvalImpl()
    //    {
    //        this->showHideMessage(false);
    //        this->buildTrigger(U"Teardown");
    //    }
    //public:
    //    void eval(const TagStatement& statement) override
    //    {
    //        const auto& tag = statement.tag.first;
    //        const auto& tagValue = statement.tag.second;
    //        if (tag == U"cm") {
    //            m_pEngine->addCommand<ClearMessage>();
    //        } else if (tag == U"l") {
    //            m_pEngine->addCommand<WaitInput>();
    //        } else if (tag == U"r") {
    //            m_pEngine->addCommand<MessageStream>(U"\n");
    //        } else if (tag == U"color" && tagValue) {
    //            m_pEngine->addCommand<ColorTag>(Color(*tagValue));
    //        } else if (tag == U"/color") {
    //            m_pEngine->addCommand<ColorTag>(s3d::none);
    //        } else if (tag == U"shake") {
    //            m_pEngine->addCommand<ShakeTag>(true);
    //        } else if (tag == U"/shake") {
    //            m_pEngine->addCommand<ShakeTag>(false);
    //        } else if (tag == U"wait") {
    //            Duration time{};
    //            for (const auto& [key, value] : statement.childs) {
    //                if (key == U"time" && value) {
    //                    time = Duration(s3d::Parse<double>(*value));
    //                }
    //            }
    //            m_pEngine->addCommand<WaitTime>(time);
    //        } else if (tag == U"chara") {
    //            s3d::Optional<CharaKind> kind;
    //            if (tagValue) {
    //                kind = Enum::Parse<CharaKind>(*tagValue);
    //            }
    //            s3d::Optional<Side> side;
    //            s3d::Optional<Face> face;
    //            for (const auto& [key, value] : statement.childs) {
    //                if (key == U"side" && value) {
    //                    if (*value == U"l") {
    //                        side = Side::Left;
    //                    } else if (*value == U"r") {
    //                        side = Side::Right;
    //                    }
    //                } else if (key == U"face" && value) {
    //                    face = Face(*value);
    //                }
    //            }
    //            // キャラか位置が変わったら切り替え
    //            const bool isChangeChara = kind && kind != m_charaKind;
    //            const bool isChangeSide = side && side != m_charaSide;
    //            bool isHide = isChangeChara || isChangeSide;
    //            if (isHide) {
    //                this->showHideMessage(false);
    //            }
    //            if (isChangeChara && !side) {
    //                side = Side::Left;
    //            }
    //            if (isChangeChara && !face) {
    //                face = Face{};
    //            }
    //            m_pEngine->addCommand<CharaSetter>(kind, side, face);
    //            m_charaKind = std::move(kind);
    //            m_charaSide = std::move(side);
    //        } else if (tag == U"build" && tagValue) {
    //            this->buildTrigger(U"Teardown");
    //            m_build = tagValue;
    //            this->buildTrigger(U"Setup");
    //        } else if (tag == U"command" && tagValue) {
    //            this->buildNativeCommand(*tagValue);
    //        } else if (tag == U"showmessage") {
    //            this->showHideMessage(true);
    //        } else if (tag == U"hidemessage") {
    //            this->showHideMessage(false);
    //        } else if (tag == U"signal") {
    //            for (const auto& [key, value] : statement.childs) {
    //                if (key == U"send" && value) {
    //                    auto func = this->findFunc<void(AdvObj*)>(*value);
    //                    m_pEngine->addCommand<SignalSend>(func);
    //                    break;
    //                } else if (key == U"receive" && value) {
    //                    auto func = this->findFunc<bool(AdvObj*)>(*value);
    //                    m_pEngine->addCommand<SignalReceive>(func);
    //                    break;
    //                }
    //            }
    //        } else if (tag == U"skippable") {
    //            m_pEngine->addCommand<SkipEnabled>(true);
    //        } else if (tag == U"/skippable") {
    //            m_pEngine->addCommand<SkipEnabled>(false);
    //        } else if (tag == U"start" && tagValue) {
    //            m_blocks.push(*tagValue);
    //            if (auto blockFunc = this->findBlockFunc(*tagValue, U"Start")) {
    //                (*blockFunc)(m_pObj);
    //            }
    //        } else if (tag == U"end") {
    //            if (!m_blocks.empty()) {
    //                if (auto blockFunc = this->findBlockFunc(m_blocks.top(), U"End")) {
    //                    (*blockFunc)(m_pObj);
    //                }
    //                m_blocks.pop();
    //            }
    //        } else if (tag == U"pause-disabled") {
    //            m_pEngine->addCommand<PauseDisabled>(true);
    //        } else if (tag == U"/pause-disabled") {
    //            m_pEngine->addCommand<PauseDisabled>(false);
    //        } else if (tag == U"bgm") {
    //            Duration fade{2s};
    //            Bgm::Kind kind{};
    //            String path = U"";
    //            for (const auto& [key, value] : statement.childs) {
    //                if (key == U"play" && value) {
    //                    kind = Bgm::Kind::Play;
    //                    path = *value;
    //                }if (key == U"stop") {
    //                    kind = Bgm::Kind::Stop;
    //                } else if (key == U"stash") {
    //                    kind = Bgm::Kind::Stash;
    //                } else if (key == U"stash-pop") {
    //                    kind = Bgm::Kind::StashPop;
    //                } else if (key == U"fade" && value) {
    //                    fade = Duration(s3d::Parse<double>(*value));
    //                }
    //            }
    //            m_pEngine->addCommand<Bgm>(kind, path, fade);
    //        }
    //    }
    //    void eval(const Ast::NameStatement& statement) override
    //    {
    //        m_pEngine->addCommand<NameSetter>(statement.name);
    //    }
    //    void eval(const Ast::TextStatement& statement) override
    //    {
    //        this->showHideMessage(true);
    //        m_pEngine->addCommand<MessageStream>(statement.text);
    //    }
    //private:
    //    void showHideMessage(bool isShow)
    //    {
    //        if (m_isVisibleMessage == isShow) {
    //            return;
    //        }
    //        m_isVisibleMessage = isShow;
    //        m_pEngine->addCommand<ShowHideMessage>(isShow);
    //    }
    //    bool buildNativeCommand(s3d::StringView name)
    //    {
    //        if (this->buildTrigger(name)) {
    //            return true;
    //        }
    //        if (auto func = this->findFunc<void(AdvObj*)>(name)) {
    //            (*func)(m_pObj);
    //            return true;
    //        }
    //        return false;
    //    }
    //    bool buildTrigger(s3d::StringView eventName)
    //    {
    //        if (!m_build) {
    //            return false;
    //        }
    //        if (auto buildFunc = findBuildFunc(eventName)) {
    //            (*buildFunc)(m_pObj);
    //            return true;
    //        }
    //        return false;
    //    }
    //    template<class T>
    //    auto findFunc(s3d::StringView name)
    //        ->decltype(Reflect<>::find<T>(U""))
    //    {
    //        if (auto func = Reflect<>::find<T>(
    //            U"abyss::Adv::{}::{}"_fmt(*m_build, name)
    //            )) {
    //            return func;
    //        }
    //        return Reflect<>::find<T>(
    //            U"abyss::Adv::{}"_fmt(name)
    //            );
    //    }
    //    auto findBuildFunc(s3d::StringView name)
    //        ->decltype(Reflect<>::find<void(AdvObj*)>(U""))
    //    {
    //        return Reflect<>::find<void(AdvObj*)>(
    //            U"abyss::Adv::{}::Builder::{}"_fmt(*m_build, name)
    //            );
    //    }
    //    auto findBlockFunc(s3d::StringView blockName, s3d::StringView name)
    //        ->decltype(Reflect<>::find<void(AdvObj*)>(U""))
    //    {
    //        return Reflect<>::find<void(AdvObj*)>(
    //            U"abyss::Adv::{}::Builder::{}::{}"_fmt(*m_build, blockName, name)
    //            );
    //    }
    //private:
    //    AdvObj* m_pObj;
    //    Engine* m_pEngine;

    //    bool m_isVisibleMessage = false;
    //    s3d::Optional<CharaKind> m_charaKind;
    //    s3d::Optional<Side> m_charaSide;
    //    s3d::Optional<s3d::String> m_build;

    //    std::stack<s3d::String> m_blocks;
    //};
}
namespace abyss::Adv
{
    void AdvBuilder::Build(AdvObj* pObj, const s3d::String& path)
    {
        // スクリプトからロード
        {
            Nept::Script script(path);
            Evaluator eval(pObj);
            script.eval(&eval);
        }
        pObj->attach<SkipCtrl>(pObj);
        pObj->attach<MessageBox>(pObj);
        pObj->attach<TalkCtrl>(pObj);
    }
}