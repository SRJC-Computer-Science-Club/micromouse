#include "Path.h"
#include "AssertionHandler.h"



namespace Micromouse
{
	Path::Path()
	{
	}



	Path::~Path()
	{
	}


	void Path::addStep( DirectionVector step )
	{
		path.push( step );
	}



	DirectionVector Path::popStep()
	{
		assertion(!path.empty(), 6);

		DirectionVector step = path.top();
		path.pop();

		return step;
	}



	DirectionVector Path::peekStep()
	{
		assertion(!path.empty(), 7);

		return path.top();
	}



	int Path::size()
	{
		return path.size();
	}



	bool Path::empty()
	{
		return path.empty();
	}
}
