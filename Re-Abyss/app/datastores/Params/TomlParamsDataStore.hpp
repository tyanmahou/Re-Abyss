#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/TOMLReader.hpp>
#include <abyss/datastores/Params/base/IParamsDataStore.hpp>
#include <abyss/utils/TomlBind/TomlBind.hpp>
namespace abyss
{
    template<class Entity>
    class TomlParamsDataStore : public IParamsDataStore<Entity>
    {
        s3d::FilePath m_tomlPath;
    public:
        TomlParamsDataStore(const s3d::FilePath& toml):
            m_tomlPath(toml)
        {}

        virtual Entity select() const
        {
            return TomlBind<Entity>{}(s3d::TOMLReader(m_tomlPath));
        }
    };
}