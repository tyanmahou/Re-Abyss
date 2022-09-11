#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    ColorCtrl::ColorCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {
        m_colorMul.resize(1);
        m_colorAdd.resize(1);
    }
    const s3d::ColorF& ColorCtrl::colorMul(size_t index) const
    {
        return m_colorMul[index];
    }

    const s3d::ColorF& ColorCtrl::colorAdd(size_t index) const
    {
        return m_colorAdd[index];
    }

    void ColorCtrl::resizeBuffer(size_t sizeMul, size_t sizeAdd)
    {
        m_colorMul.resize(sizeMul);
        m_colorAdd.resize(sizeAdd);
    }
    void ColorCtrl::resizeBuffer(size_t size)
    {
        this->resizeBuffer(size, size);
    }
    void ColorCtrl::setup(Executer executer)
    {
        executer.onStart().addAfter<ColorAnim::IColorMul>();
        executer.onStart().addAfter<ColorAnim::IColorAdd>();

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
        for (size_t index = 0; index < m_colorMul.size(); ++index) {
            m_colorMul[index] = s3d::Palette::White;
            for (auto&& mulAnim : m_colorMulAnims) {
                if (mulAnim && ((static_cast<size_t>(1) << index) & mulAnim->indexMaskMul()) != 0) {
                    m_colorMul[index] *= mulAnim->colorMul();
                }
            }
        }
        for (size_t index = 0; index < m_colorAdd.size(); ++index) {
            m_colorAdd[index] = ColorF(0, 0);
            for (auto&& addAnim : m_colorAddAnims) {
                if (addAnim && ((static_cast<size_t>(1) << index) & addAnim->indexMaskAdd()) != 0) {
                    m_colorAdd[index] += addAnim->colorAdd();
                }
            }
        }
    }
}
