#pragma once
#include <stack>
#include "Vector.h"


namespace Micromouse
{
	// This class represents the path the mouse should follow to reach the destination
	// It consists of a stack of direction vectors that when executed in order will
	// guide the mouse to the finish destination

	class Path
	{
	public:
		Path();
		~Path();

		// adds step to 'path'
		// steps need to be added in reverse order
		void addStep( Vector::Dir step );

		// returns the next step in the path and removes it from the path
		// calling on an empty path will result in an error
		Vector::Dir nextStep();

		// returns the next step in the path without removing it
		// calling on an empty path will result in an error
		Vector::Dir peekStep();

		//returns the number of steps in the path
		int size();

		// returns true when the path is empty, false otherwise;
		bool empty();

	private:
		// a first in - last out (FILO) list of steps for motion control to follow
		// it is a FILO list because the path is created in reverse
		// each step consist of a direction and magnitude to travel before continuing on to the next step
		std::stack<Vector::Dir> path;
	};
}

