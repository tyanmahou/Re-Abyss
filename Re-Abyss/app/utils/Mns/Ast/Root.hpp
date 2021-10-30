#pragma once
#include <abyss/utils/Mns/Ast/IStatement.hpp>
#include <Siv3D/Array.hpp>
#include <memory>

namespace Mns::Ast
{
	struct Root : INode
	{
		s3d::Array<std::shared_ptr<IStatement>> statements;
	};
}
