#pragma once
#include <Siv3D/Array.hpp>

namespace abyss
{
    namespace detail
    {
        template<class Type>
        Type HermiteCurve(const Type& p0, const Type& p1, const Type& v0, const Type& v1, double t)
        {
            auto c0 = 2.0 * p0 + -2.0 * p1 + v0 + v1;
            auto c1 = -3.0 * p0 + 3.0 * p1 + -2.0 * v0 - v1;
            auto c2 = v0;
            auto c3 = p0;

            auto t2 = t * t;
            auto t3 = t2 * t;
            return c0 * t3 + c1 * t2 + c2 * t + c3;
        }
    }

    /// <summary>
    /// Catmull-Rom スプライン曲線
    /// </summary>
    template<class Type>
    class CatmullRomSpline
    {
        struct Section
        {
            double aboutLength = 0.0f;
            double ratio = 0.0f;
        };
    public:
        CatmullRomSpline() = default;
        CatmullRomSpline(const s3d::Array<Type>& list):
            m_points(list.begin(), list.end())
        {
            restruct();
        }
        CatmullRomSpline(const std::initializer_list<Type>& list):
            m_points(list.begin(), list.end())
        {
            restruct();
        }

        void addPos(const Type& value)
        {
            m_points.push_back(value);
            restruct();
        }

        /// <summary>
        /// 座標を取得
        /// </summary>
        /// <param name="t">0～1</param>
        /// <returns></returns>
        Type pos(double t) const
        {
            auto size = m_points.size();
            auto progress = (size - 1) * t;
            auto i = static_cast<s3d::uint32>(progress);
            auto weight = progress - i;

            // 末端
            if (i >= size - 1) {
                i = size - 2;
                weight = 1.0;
            }

            auto p0 =  m_points[i];
            auto p1 =  m_points[i + 1];

            Type v0;
            if (i > 0) {
                v0 = 0.5 * (m_points[i + 1] - m_points[i - 1]);
            } else {
                v0 = m_points[i + 1] - m_points[i];
            }

            Type v1;
            if (i < size - 2) {
                v1 = 0.5 * (m_points[i + 2] - m_points[i]);
            } else {
                v1 = m_points[i + 1] - m_points[i];
            }
            return detail::HermiteCurve(p0, p1, v0, v1, weight);
        }

        Type posUniform(double t) const
        {
            auto sectionSize = m_sections.size();
            if (sectionSize == 0) {
                return pos(1.0);
            }

            auto tSum = 0.0;
            auto tPerSection = 1.0 / static_cast<double>(sectionSize);
            size_t index = 0;
            for (const auto& section : m_sections) {
                if (t < tSum + section.ratio) {
                    return pos((index + (t - tSum) / section.ratio) * tPerSection);
                }
                tSum += section.ratio;

                ++index;
            }
            return pos(1.0);
        }
        Type posUniformDist(double dist) const
        {
            if (m_aboutLength <= 0) {
                return pos(1.0);
            }
            return posUniform(dist / m_aboutLength);
        }

    private:
        s3d::Array<Type> m_points;
        s3d::Array<Section> m_sections;

        double m_aboutLength = 0.0;

        void restruct()
        {
            m_sections.clear();

            auto lengthSum = 0.0;
            auto sectionSize = m_points.size() - 1;
            for (size_t index = 0; index < sectionSize; ++index) {
                auto length = (m_points[index + 1] - m_points[index]).length();
                lengthSum += length;
                m_sections.push_back(Section{
                    .aboutLength = length
                });
            }
            m_aboutLength = lengthSum;

            for (auto& section : m_sections) {
                section.ratio = section.aboutLength / m_aboutLength;
            }
        }
    };

}