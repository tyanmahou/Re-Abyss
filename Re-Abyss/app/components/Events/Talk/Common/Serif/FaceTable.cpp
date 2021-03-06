#include "FaceTable.hpp"
#include <Siv3D.hpp>
#include <abyss/models/Event/Talk/FaceTableModel.hpp>

namespace abyss::Event::Talk
{

    FaceTable::FaceTable(std::shared_ptr<FaceTableModel> faceTable):
        m_faceTable(faceTable)
    {}
    bool FaceTable::isContain(const s3d::String& actor, const s3d::String& kind) const
    {
        return m_faceTable->isContain(actor, kind);
    }
    s3d::Texture FaceTable::getFace(const s3d::String& actor, const s3d::String& kind) const
    {
        return m_faceTable->getFace(actor, kind);
    }
}
