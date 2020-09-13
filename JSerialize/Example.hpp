#pragma once

#include "JSerialize/JSerialize.hpp"

namespace Example
{
	struct Struct
	{
		SERIALIZEABLE(int, m_Integer, 0, true);
		SERIALIZEABLE(float, m_Float, 0.0f, true);
		SERIALIZEABLE(double, m_Double, 0.0f, true);
		SERIALIZEABLE(void*, m_pVoid, 0, true);
	};
}



