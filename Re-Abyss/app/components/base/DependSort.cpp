#include "DependSort.hpp"

namespace
{
    using namespace abyss;

    struct Node
    {
        Ref<IComponent> component;
        Depends depends;
        bool isOpen = false;
        bool isTemp = false;
    };

    void Visit(s3d::Array<Ref<IComponent>>& result, s3d::Array<Node>& nodes, Node& n)
    {
        if (n.isTemp) {
            return;
        }
        n.isTemp = true;

        s3d::Array<Node*> out;
        for (auto& node : nodes) {
            if (n.depends.isAfter(node.component.get())) {
                out.push_back(&node);
            } else if (node.depends.isBefore(n.component.get())) {
                out.push_back(&node);
            }
        }
        for (auto* o : out) {
            Visit(result, nodes, *o);
        }
        n.isOpen = true;
        result.push_back(n.component);
    };
}
namespace abyss
{
    void DependsSort::regist(IComponent* component, Depends depends)
    {
        m_depends[component] = depends;
    }
    s3d::Array<Ref<IComponent>> DependsSort::sort(const s3d::Array<Ref<IComponent>>& origin)
    {
        s3d::Array<Node> nodes;
        for (auto& com : origin) {
            nodes.push_back({ com, m_depends[com.get()] });
        }
        s3d::Array<Ref<IComponent>> result;
        for (auto& node : nodes) {
            if (!node.isOpen) {
                Visit(result, nodes, node);
            }
        }
        return result;
    }
}
