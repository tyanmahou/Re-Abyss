#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ColorCtrl::ColorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    const s3d::ColorF& ColorCtrl::colorMul() const
    {
        return m_colorMul;
    }

    const s3d::ColorF& ColorCtrl::colorAdd() const
    {
        return m_colorAdd;
    }

    void ColorCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<ColorAnim::IColorMul>();
        executer.on<IComponent>().addAfter<ColorAnim::IColorAdd>();

        executer.on<IPreDraw>().addAfter<ColorAnim::IColorMul>();
        executer.on<IPreDraw>().addAfter<ColorAnim::IColorAdd>();
    }

    void ColorCtrl::onStart()
    {
        m_colorMulAnims = m_pActor->finds<ColorAnim::IColorMul>();
        m_colorAddAnims = m_pActor->finds<ColorAnim::IColorAdd>();
    }

    void ColorCtrl::onPreDraw()
    {
        m_colorMul = s3d::Palette::White;
        m_colorAdd = ColorF(0, 0);

        for (auto&& mulAnim : m_colorMulAnims) {
            if (mulAnim) {
                m_colorMul *= mulAnim->colorMul();
            }
        }
        for (auto&& addAnim : m_colorAddAnims) {
            if (addAnim) {
                m_colorAdd += addAnim->colorAdd();
            }
        }
    }
}
