#include <iostream>
#include "Controller.h"

using namespace std;

namespace Micromouse
{

	ostream& operator<<(ostream &out, const Vector::Pos &pos)
	{
		int x = pos.x();
		return out << "(" << pos.x() << ", " << pos.y() << ")";
	}

	Controller::Controller()
	{
		MouseBot mb = MouseBot();
		cout << mb.getPos() << endl;

		mb.moveForward();
		cout << mb.getPos() << endl;

		mb.turnRight();
		cout << mb.getPos() << endl;

		mb.moveForward();
		cout << mb.getPos() << endl;

		mb.rotateLeft();
		mb.rotateLeft();
		cout << mb.getPos() << endl;

		mb.moveForward();
		cout << mb.getPos() << endl;

		system("pause");
	}






	Controller::~Controller()
	{
	}


}