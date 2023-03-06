#include <abyss/components/Adv/AdvBuilder.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Process.hpp>

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

#include <abyss/utils/NeptScript/Script.hpp>
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
            m_pProcess(pObj->process().get())
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

                s3d::Optional<Adv::LookType> look;
                if (statement.look == Nept::Ast::LookType::Left) {
                    look = Adv::LookType::Left;
                } else if(statement.look == Nept::Ast::LookType::Right) {
                    look = Adv::LookType::Right;
                } else {
                    look = Adv::LookType::Center;
                }
                s3d::Optional<Emote> emote;
                if (statement.emote) {
                    emote = Emote(*statement.emote);
                }
                this->buildChara(std::move(kind), std::move(look), std::move(emote));
            }

            // 表示名
            if (statement.displayName) {
                m_pProcess->addCommand<NameSetter>(*statement.displayName);
            }
        }
        void eval(const CommandStatement& statement) override
        {
            const auto& command = statement.command;
            const auto& param = statement.rootParam;
            if (command == U"cm") {
                m_pProcess->addCommand<ClearMessage>();
            } else if (command == U"l") {
                m_pProcess->addCommand<WaitInput>();
            } else if (command == U"r") {
                m_pProcess->addCommand<MessageStream>(U"\n");
            } else if (command == U"color" && param) {
                m_pProcess->addCommand<ColorTag>(Color(*param));
            } else if (command == U"/color") {
                m_pProcess->addCommand<ColorTag>(s3d::none);
            } else if (command == U"shake") {
                m_pProcess->addCommand<ShakeTag>(true);
            } else if (command == U"/shake") {
                m_pProcess->addCommand<ShakeTag>(false);
            } else if (command == U"wait") {
                Duration time{};
                for (const auto& [key, value] : statement.params) {
                    if (key == U"time" && value) {
                        time = Duration(s3d::Parse<double>(*value));
                    }
                }
                m_pProcess->addCommand<WaitTime>(time);
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
                m_pProcess->addCommand<SignalSend>(func);
            } else if (command == U"receive" && param) {
                auto func = this->findFunc<bool(AdvObj*)>(*param);
                m_pProcess->addCommand<SignalReceive>(func);
            } else if (command == U"skippable") {
                m_pProcess->addCommand<SkipEnabled>(true);
            } else if (command == U"/skippable") {
                m_pProcess->addCommand<SkipEnabled>(false);
            } else if (command == U"pause-disabled") {
                m_pProcess->addCommand<PauseDisabled>(true);
            } else if (command == U"/pause-disabled") {
                m_pProcess->addCommand<PauseDisabled>(false);
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
                m_pProcess->addCommand<Bgm>(kind, path, fade);
            }
        }
        void eval(const TextStatement& statement) override
        {
            this->showHideMessage(true);
            m_pProcess->addCommand<MessageStream>(statement.text);
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
        void buildChara(s3d::Optional<CharaKind> kind, s3d::Optional<Adv::LookType> look, s3d::Optional<Emote> emote)
        {
            // キャラか位置が変わったら切り替え
            const bool isChangeChara = kind && kind != m_charaKind;
            const bool isChangeSide = look && look != m_charaLook;
            bool isHide = isChangeChara || isChangeSide;
            if (isHide) {
                this->showHideMessage(false);
            }
            if (isChangeChara && !look) {
                look = Adv::LookType::Right;
            }
            if (isChangeChara && !emote) {
                emote = Emote{};
            }

            m_pProcess->addCommand<CharaSetter>(kind, look, emote);
            m_charaKind = std::move(kind);
            m_charaLook = std::move(look);
        }
        void showHideMessage(bool isShow)
        {
            if (m_isVisibleMessage == isShow) {
                return;
            }
            m_isVisibleMessage = isShow;
            m_pProcess->addCommand<ShowHideMessage>(isShow);
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
        Process* m_pProcess;

        bool m_isVisibleMessage = false;
        s3d::Optional<CharaKind> m_charaKind;
        s3d::Optional<Adv::LookType> m_charaLook;
        s3d::Optional<s3d::String> m_build;

        std::stack<s3d::String> m_blocks;
    };
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
