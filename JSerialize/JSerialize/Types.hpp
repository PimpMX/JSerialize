#pragma once

namespace JSerialize
{
	template<class>
	class CSerializeable;
}

namespace Example
{
	struct Struct;
}

/*
*		Use "SINGLE_ARG" when using template classes as parameters for CSerializeable's. This is needed because the preprocessor strictly divides arguments by
*		the ',' character. With this define we can bypass this unwanted behaviour.
*/

#define SINGLE_ARG(...) __VA_ARGS__

//		The "POSSIBLE_TYPES" macro defines all the possible datatypes that our std::variant could store.

#define POSSIBLE_TYPES SINGLE_ARG(bool, unsigned char, char, unsigned short, short, unsigned int, int, unsigned long, long, float, double)