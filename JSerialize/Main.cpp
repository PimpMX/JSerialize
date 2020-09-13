#include "Example.hpp"

/*
*		NOTE: This main is only used as a testing execution point for executing the functions of the JSerialize
*		namespace for the purpose of testing and running examples.
*/

#include <iostream>

int main()
{
	nlohmann::json MyFile;
	SERIALIZEABLE(Example::Struct, MyStr, Example::Struct(), false);

	JSerialize::Serialize(MyFile, (JSerialize::CSerializeable<UNKNOWN>*)(&MyStr));
}