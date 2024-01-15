#pragma once

inline int ClampValues(int _min, int _val, int _max)
{
	if (_val < _min) return _min;
	if (_val > _max) return _max;
	return _val;
}