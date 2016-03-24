#include "RobotIO.h"

namespace Micromouse
{
	/**** CONSTRUCTORS ****/

	RobotIO::RobotIO()
	{
		initSensors();
	}

	RobotIO::~RobotIO()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}
	}





	/**** SENSORS ****/

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearForward()
	{
		return false;
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearRight()
	{
		return false;
	}

	// ## NOT YET IMPLEMENTED ## 
	bool RobotIO::isClearLeft()
	{
		return false;
	}





	/**** MOTORS ****/

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::moveForward()
	{

	}

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::rotateLeft()
	{

	}

	// ## NOT YET IMPLEMENTED ## 
	void RobotIO::rotateRight()
	{

	}





	/**** INITIALIZATIONS ****/

	void RobotIO::initSensors()
	{
		for (int i = 0; i < 4; i++)
		{
			delete IRSensors[i];
		}

		IRSensors[LEFT] = new IRSenor(IR_LEFT_PIN, 40, 300);
		IRSensors[RIGHT] = new IRSenor(IR_RIGHT_PIN, 40, 300);
		IRSensors[FRONT_LEFT] = new IRSenor(IR_FRONT_LEFT_PIN, 40, 300);
		IRSensors[FRONT_RIGHT] = new IRSenor(IR_FRONT_RIGHT_PIN, 40, 300);
	}
}