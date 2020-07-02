#pragma once
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::Event::Talk
{
    class SerifModel;
    class FaceManager;

    class Serif : public IEvent
    {
        std::shared_ptr<SerifModel> m_serif;
 
        std::shared_ptr<FaceManager> m_faceManager;
    public:
        Serif();

        void setModel(const std::shared_ptr<SerifModel>& model);
        void setFaceManager(const std::shared_ptr<FaceManager>& faceManager);
        void onStart() override;

        bool update(double dt) override;

        void onEnd() override;

    };
}