#include "Memory.h"
#include <assert.h>

namespace Micromouse {

	int Memory::read(int address)
	{
		assert(address >= 0 && address < 2048);

#ifdef __MK20DX256__ // Teensy Compile
		int load;
		EEPROM.get(address, load);
		return load;
#else // PC compile
		return 0;
#endif
	}



	void Memory::write(int address, int val)
	{
		assert(address >= 0 && address < 2048);

#ifdef __MK20DX256__ // Teensy Compile
		EEPROM.put(address, val);
#endif
	}
}