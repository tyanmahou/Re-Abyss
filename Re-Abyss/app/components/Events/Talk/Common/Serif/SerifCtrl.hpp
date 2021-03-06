#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/Talk/base/ITalker.hpp>
#include <abyss/models/Event/Talk/SerifModel.hpp>

namespace abyss::Event::Talk
{
    class SerifCtrl : 
        public IComponent,
        public ITalker
    {
    public:
        SerifCtrl(TalkObj* pTalk, const SerifModel& serif);

        void onStart() override;
        void onEnd() override;

        Coro::Task<> onTalk() override;


        const s3d::Optional<s3d::String>& getActorName()const;

        SerifModel::Side getSide() const;

        const s3d::Array<SerifModel::Message>& getMessages()const;

        const s3d::String& getMessage(size_t index)const;

        s3d::int32 getStrIndex()const;

        bool isAll()const;
        bool isLeft()const;
        bool isRight()const;

        s3d::String getPrev() const;
        const s3d::String& getCurrent() const;
        const s3d::String& getCurrentKind()const;

        bool isEnd() const;
    private:
        TalkObj* m_pTalk;
        SerifModel m_serif;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Talk::SerifCtrl>
    {
        using Base = MultiComponents<
            Event::Talk::ITalker
        >;
    };
}