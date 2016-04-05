#include "Memory.h"
#include <assert.h>

namespace Micromouse {

	int Memory::read(int address)
	{
		assert(address >= 0 && address < 2048);

#ifdef __MK20DX256__ // Teensy compile
		return EEPROM.read(address);
#endif
		return 0;
	}

	void Memory::write(int address, int val)
	{
		assert(address >= 0 && address < 2048);

#ifdef __MK20DX256__ // Teensy compile
		EEPROM.update(address, val);
#endif
	}
}