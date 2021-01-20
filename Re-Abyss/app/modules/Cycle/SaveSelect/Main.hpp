#pragma once
#include <memory>

#include <abyss/models/User/UserModel.hpp>
#include <abyss/utils/Hierarchy/Hierarchy.hpp>

#include <Siv3D/Fwd.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Cycle::SaveSelect
{
    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;

        virtual void onNewGame() = 0;
        virtual void onLoadGame() = 0;
        virtual void onBack() = 0;
    };
    class Main
    {
    private:
        HierarchyManager m_hierarcy;

    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;

        void finally();
    };
}