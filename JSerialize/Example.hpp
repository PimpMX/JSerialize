#pragma once

#include "JSerialize/JSerialize.hpp"

namespace Example
{
	struct Struct
	{
		SERIALIZEABLE(int, m_Integer, 0);
		SERIALIZEABLE(float, m_Float, 0.0f);
		SERIALIZEABLE(double, m_Double, 0.0f);
		SERIALIZEABLE(void*, m_pVoid, 0);
		SERIALIZEABLE(float, m_Float2, 1.0f);
	};
}



