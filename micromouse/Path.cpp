#include "Path.h"
#include <assert.h>




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
		assert( !path.empty() );

		DirectionVector step = path.top();
		path.pop();

		return step;
	}



	DirectionVector Path::peekStep()
	{
		assert( !path.empty() );

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
