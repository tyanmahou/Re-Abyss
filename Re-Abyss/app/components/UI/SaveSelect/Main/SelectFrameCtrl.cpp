#include <abyss/components/UI/SaveSelect/Main/SelectFrameCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::SaveSelect::Main
{
    SelectFrameCtrl::SelectFrameCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<SelectFrame::SelectFrameVM>())
    {}

    void SelectFrameCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<UserSelector>();
    }

    void SelectFrameCtrl::onStart()
    {
        m_selector = m_pUi->find<UserSelector>();
    }

    void SelectFrameCtrl::onDraw() const
    {
        m_view
            ->setSelectUserId(m_selector->getSelectId())
            .draw();
    }
}
