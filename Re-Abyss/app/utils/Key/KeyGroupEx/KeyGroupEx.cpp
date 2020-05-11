#include "KeyGroupEx.hpp"

namespace abyss
{
    bool KeyGroupEx::down() const
    {
        return m_keys.any([](const std::shared_ptr<IKey>& k) { return k->down(); });
    }
    bool KeyGroupEx::pressed() const
    {
        return m_keys.any([](const std::shared_ptr<IKey>& k) { return k->pressed(); });
    }
    bool KeyGroupEx::up() const
    {
        return m_keys.any([](const std::shared_ptr<IKey>& k) { return k->up(); });
    }
    s3d::int32 KeyGroupEx::num_pressed() const
    {
        s3d::int32 num = 0;

        for (const auto& key : m_keys) {
            num += key->pressed();
        }
        return num;
    }
    s3d::Duration KeyGroupEx::pressedDuration() const
    {
        s3d::Duration duration(0);

        for (const auto& key : m_keys) {
            duration = std::max(key->pressedDuration(), duration);
        }

        return duration;
    }
    s3d::String KeyGroupEx::name() const
    {
        s3d::String s;

        bool isFirst = true;

        for (const auto& key : m_keys) {
            if (isFirst) {
                isFirst = false;
            } else {
                s.append(U"|");
            }

            s.append(key->name());
        }
        return s;
    }
}

void s3d::Formatter(FormatData& formatData, const abyss::KeyGroupEx& group)
{
    formatData.string.append(group.name());
}
