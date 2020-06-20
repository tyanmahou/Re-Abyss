#pragma once
#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/models/Event/Talk/SerifModel.hpp>

namespace abyss::Event::Talk
{
    class FaceManager;

    class Serif : public IEvent
    {
        SerifModel m_serif;
 
        std::shared_ptr<FaceManager> m_faceManager;
    public:
        Serif();
        ~Serif();
        void setModel(SerifModel&& model);
        void setFaceManager(const std::shared_ptr<FaceManager>& faceManager);
        bool update(double dt) override;
    };
}