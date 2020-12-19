#include "DependSort.hpp"

namespace
{
    using namespace abyss;

    struct Node
    {
        Ref<IComponent> component;
        s3d::Array<Node*> outs;
        bool isOpen = false;
        bool isTemp = false;
    };

    void Visit(s3d::Array<Ref<IComponent>>& result, s3d::Array<Node>& nodes, Node& n)
    {
        if (n.isTemp) {
            return;
        }
        n.isTemp = true;
        for (auto* o : n.outs) {
            Visit(result, nodes, *o);
        }
        n.isOpen = true;
        result.push_front(n.component);
    };
}
namespace abyss
{
    void DependsSort::regist(IComponent* component, Depends depends)
    {
        m_depends[component] = depends;
    }
    s3d::Array<Ref<IComponent>> DependsSort::sort(const std::type_index& process, const s3d::Array<Ref<IComponent>>& origin)
    {
        s3d::Array<Node> nodes;
        for (auto& com : origin) {
            nodes.push_back({ com });
        }
        // 出力ノードをまとめる
        for (auto& node1 : nodes) {
            s3d::Array<Node*> outs;
            auto& depends1 = m_depends[node1.component.get()];
            for (auto& node2 : nodes) {
                if (&node1 == &node2) {
                    continue;
                }
                auto& depends2 = m_depends[node2.component.get()];
                if (depends1.on(process).isBefore(node2.component.get())) {
                    outs.push_back(&node2);
                } else if (depends2.on(process).isAfter(node1.component.get())) {
                    outs.push_back(&node2);
                }
            }
            node1.outs = std::move(outs);
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
