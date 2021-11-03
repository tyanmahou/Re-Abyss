#include "TalkBuilder.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/components/Novel/Common/Command/CharaSetter.hpp>
#include <abyss/components/Novel/Common/Command/ClearMessage.hpp>
#include <abyss/components/Novel/Common/Command/ColorTag.hpp>
#include <abyss/components/Novel/Common/Command/MessageStream.hpp>
#include <abyss/components/Novel/Common/Command/NameSetter.hpp>
#include <abyss/components/Novel/Common/Command/ShakeTag.hpp>
#include <abyss/components/Novel/Common/Command/WaitInput.hpp>
#include <abyss/components/Novel/Common/Command/WaitTime.hpp>

#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/utils/Mns/Script.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Novel;
    using namespace Mns;
    using namespace Mns::Ast;
    class EvalImpl final : public IEvalImpl
    {
    public:
        EvalImpl(TalkObj* pTalk):
            m_pTalk(pTalk),
            m_pEngine(pTalk->engine().get())
        {}
        ~EvalImpl()
        {
            this->buildTrigger(U"Teardown");
        }
    public:
        void eval(const TagStatement& statement) override
        {
            const auto& tag = statement.tag.first;
            const auto& tagValue = statement.tag.second;
            if (tag == U"cm") {
                m_pEngine->addCommand<ClearMessage>();
            } else if (tag == U"l") {
                m_pEngine->addCommand<WaitInput>();
            } else if (tag == U"r") {
                m_pEngine->addCommand<MessageStream>(U"\n");
            } else if (tag == U"color" && tagValue) {
                m_pEngine->addCommand<ColorTag>(Color(*tagValue));
            } else if (tag == U"/color") {
                m_pEngine->addCommand<ColorTag>(s3d::none);
            } else if (tag == U"shake") {
                m_pEngine->addCommand<ShakeTag>(true);
            } else if (tag == U"/shake") {
                m_pEngine->addCommand<ShakeTag>(false);
            } else if (tag == U"wait") {
                Duration time{};
                for (const auto& [key, value] : statement.childs) {
                    if (key == U"time" && value) {
                        time = Duration(s3d::Parse<double>(*value));
                    }
                }
                m_pEngine->addCommand<WaitTime>(time);
            } else if (tag == U"chara") {
                s3d::Optional<CharaKind> kind;
                if (tagValue) {
                    kind = Enum::Parse<CharaKind>(*tagValue);
                }
                s3d::Optional<Side> side;
                s3d::Optional<Face> face;
                for (const auto& [key, value] : statement.childs) {
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
                m_pEngine->addCommand<CharaSetter>(kind, side, face);
            } else if (tag == U"build" && tagValue) {
                this->buildTrigger(U"Teardown");
                m_build = tagValue;
                this->buildTrigger(U"Setup");
            } else if (tag == U"trigger") {
                for (const auto& [key, value] : statement.childs) {
                    if (key == U"event" && value) {
                        this->buildTrigger(*value);
                        break;
                    }
                }
            }
        }
        void eval(const Ast::NameStatement& statement) override
        {
            m_pEngine->addCommand<NameSetter>(statement.name);
        }
        void eval(const Ast::TextStatement& statement) override
        {
            m_pEngine->addCommand<MessageStream>(statement.text);
        }
    private:
        void buildTrigger(s3d::StringView eventName)
        {
            if (!m_build) {
                return;
            }
            if (auto buildFunc = Reflect<>::find<void(*)(TalkObj*)>(
                U"abyss::Novel::{}::Builder::{}"_fmt(*m_build, eventName)
                )) {
                (*buildFunc)(m_pTalk);
            }
        }
    private:
        TalkObj* m_pTalk;
        Engine* m_pEngine;

        s3d::Optional<s3d::String> m_build;
    };
}
namespace abyss::Novel
{
    void TalkBuilder::Build(TalkObj* pTalk, const s3d::String& path)
    {
        // スクリプトからロード
        {
            Mns::Script script(path);
            EvalImpl eval(pTalk);
            script.eval(&eval);
        }

        pTalk->attach<MessageBox>(pTalk);
    }
}
