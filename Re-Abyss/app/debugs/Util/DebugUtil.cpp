#include <abyss/debugs/Util/DebugUtil.hpp>
#if ABYSS_DEBUG

#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/ITerrain.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Overloaded.hpp>

#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

#include <Siv3D.hpp>
#include <Siv3D/Windows/Windows.hpp>

namespace abyss::Debug
{
    void DebugUtil::DrawDebug(const World& world)
    {
        if (!Menu::IsDebug(Debug::DebugFlag::ActorCollider)) {
            return;
        }
        auto coms = world.finds<Actor::Collider>();

        constexpr ColorF color = ColorF(1, 0, 0, 0.4);
        size_t size{};
        for (auto&& com : coms) {
            for (const auto& c : *com) {
                DrawShape(c->getCollider(), color);
                ++size;
            }
        }
        Debug::Log.Update << U"Colliders: " << size;
    }
    void DebugUtil::DrawDebug(const PhysicsManager& physics)
    {
        if (!Menu::IsDebug(Debug::DebugFlag::ActorMapCollider)) {
            return;
        }

        constexpr ColorF color = ColorF(0, 0, 1, 0.4);
        {
            const auto& colliders = physics.getContacters();
            Debug::Log.Update << U"Map Colliders: " << colliders.size();

            for (auto&& col : colliders) {
                if (!col->isActive()) {
                    continue;
                }
                DrawShape(col->getShape(), color);
            }
        }
        {
            const auto& terrains = physics.getTerrains();
            Debug::Log.Update << U"Map Terrain: " << terrains.size();

            for (auto&& terrain : terrains) {
                if (!terrain->isActive()) {
                    continue;
                }
                const auto& data = terrain->getData();
                const auto& region = data.region;
                const auto& col = data.col;

                const Vec2 qSize = {
                    Min(10.0, region.size.x / 4.0),
                    Min(10.0, region.size.y / 4.0)
                };
                if (col.isUp()) {
                    RectF(region.x, region.y, region.w, qSize.y).draw(color);
                }
                if (col.isDown()) {
                    RectF(region.x, region.y + region.h, region.w, -qSize.y).draw(color);
                }
                if (col.isLeft()) {
                    RectF(region.x, region.y, qSize.x, region.h).draw(color);
                }
                if (col.isRight()) {
                    RectF(region.x + region.w, region.y, -qSize.x, region.h).draw(color);
                }
            }
        }
    }
    void DebugUtil::DrawShape(const CShape& shape, const s3d::ColorF& color)
    {
        std::visit(overloaded{
            [&color](const auto& c) {
                c.draw(color);
            },
            [&color](const s3d::Vec2& c) {
                s3d::Shape2D::Cross(5, 2, c).draw(color);
            },
            [&color](const s3d::Array<CShape>& c) {
                for (const auto& shape : c) {
                    DrawShape(shape, color);
                }
            },
            []([[maybe_unused]] const s3d::None_t&) {}
        }, shape);
    }
    void DebugUtil::AlertDecorCount(const Decors& decor)
    {
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertDecorCount)) {
            return;
        }
        Debug::Log.Update << U"---LogDecorCount---";
        Debug::Log.Update << U"Decor: " << decor.size();
    }
    void DebugUtil::AlertEffectCount(const Effects& effects)
    {
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertEffectCount)) {
            return;
        }
        Debug::Log.Update << U"---LogEffectCount---";
        Debug::Log.Update << U"Effect: " << effects.size();
    }
    void DebugUtil::AlertDrawerCount(const DrawManager* drawManager)
    {
        if (!drawManager) {
            return;
        }
        if (!Debug::Menu::IsDebug(Debug::DebugFlag::AlertDrawerCount)) {
            return;
        }
        Debug::Log.Update << U"---LogDrawerCount---";
        for (DrawLayer layer = DrawLayer::BackGround; layer < DrawLayer::Size; ++layer) {
            Debug::Log.Update << U"{}: {}"_fmt(Enum::ToStrView(layer), drawManager->size(layer));
        }
    }
    bool DebugUtil::FileEdit(const s3d::FilePath& path)
    {
        return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", s3d::FileSystem::FullPath(path).toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
    }
}

#endif
