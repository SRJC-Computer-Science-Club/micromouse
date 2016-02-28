#pragma once
#include <stack>
#include "Vector.h"



namespace Micromouse
{
	class Path
	{
	public:
		Path();
		~Path();


	private:
		std::stack<Vector::Dir> path;
	};
}
