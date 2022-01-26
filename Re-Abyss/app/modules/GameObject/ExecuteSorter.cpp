#include <abyss/modules/GameObject/ExecuteSorter.hpp>

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
namespace abyss::detail
{
    void ExecuteSorter::regist(IComponent* component, Executer executer)
    {
        m_executer[component] = executer;
    }
    s3d::Array<Ref<IComponent>> ExecuteSorter::sort(const std::type_index& process, const s3d::Array<Ref<IComponent>>& origin)
    {
        s3d::Array<Node> nodes;
        for (auto& com : origin) {
            nodes.push_back({ com });
        }
        // 出力ノードをまとめる
        for (auto& node1 : nodes) {
            s3d::Array<Node*> outs;
            auto& executer1 = m_executer[node1.component.get()];
            for (auto& node2 : nodes) {
                if (&node1 == &node2) {
                    continue;
                }
                auto& executer2 = m_executer[node2.component.get()];
                if (executer1.on(process).isBefore(node2.component.get())) {
                    outs.push_back(&node2);
                } else if (executer2.on(process).isAfter(node1.component.get())) {
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
