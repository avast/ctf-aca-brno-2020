#include "obfuscate.h"


uint32_t _xorshift128(uint32_t * state)
{
	/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
	uint32_t s, t = state[3];
	t ^= t << 11;
	t ^= t >> 8;
	state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
	t ^= s;
	t ^= s >> 19;
	state[0] = t;
	return t;
}

void _crypt(char* flag, uint32_t* state)
{
	if (flag[0]) {
		int sz = flag[1];
		for (int i = 0; i<sz; ++i) {
			flag[i+2] ^= _xorshift128(state) & 0xffu;
		}
		flag[0]=0;
	}
}
