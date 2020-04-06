#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/repositories/Params/base/IParamsRepository.hpp>
namespace abyss
{
    class Params
    {
    private:
        template<class Entity>
        inline static std::unique_ptr<IParamsRepository<Entity>> s_repository = nullptr;
    public:

        template<class Entity>
        static void Bind(std::unique_ptr<IParamsRepository<Entity>>&& repository)
        {
            s_repository<Entity> = std::move(repository);
        }
        template<class Entity>
        static const Entity* Get()
        {
            if (!s_repository<Entity>) {
                return nullptr;
            }
            return &(s_repository<Entity>->select());
        }
    };
}