#pragma once

namespace Micromouse
{

	/* defines directions 0-8, with 4 being NONE
	it is done this way to make converting from direction to Vectorinates easier
	here are the 8 directions
	NW  N  NE

	W  NONE E

	SW  s  SE
	*/
	// TODO: move into own namespace maybe?
	enum direction { NW , N , NE , W , NONE , E , SW , S , SE };
	
	direction& operator++( direction& dir );

	namespace Vector
	{
		class Pos
		{
		public:
			Pos( int x , int y );
			~Pos();

			int x();
			int y();
			void x( int x );
			void y( int y );


			//static const Vector::Pos& UNDEFINED;//a Vector that represents an undefined Vector

		private:
			void validateSelf();

			int _x , _y;
		};



		class Dir
		{
		public:
			Dir( direction dir , int mag );
			~Dir();

			direction dir();
			int mag();
			void dir( direction dir );
			void mag( int mag );

		private:
			void validateSelf();

			direction _dir;
			int _mag;
		};
	}
}


