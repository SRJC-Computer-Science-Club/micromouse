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




	void Path::addStep( Vector::Dir step )
	{
		path.push( step );
	}



	Vector::Dir Path::popStep()
	{
		assert( !path.empty() );

		Vector::Dir step = path.top();
		path.pop();

		return step;
	}



	Vector::Dir Path::peekStep()
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
