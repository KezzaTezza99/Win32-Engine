#ifndef  __UTILS_
#define __UTILS_

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

inline int ClampValues(int _min, int _val, int _max)
{
	if (_val < _min) return _min;
	if (_val > _max) return _max;
	return _val;
}
#endif // ! __UTILS_