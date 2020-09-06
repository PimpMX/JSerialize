#include "Example.hpp"

/*
*		NOTE: This main is only used as a testing execution point for executing the functions of the JSerialize
*		namespace for the purpose of testing and running examples.
*/

#include <iostream>

int main()
{
	Example::Struct MyStruct;
	nlohmann::json MyFile;
	JSerialize::CPrimitiveVisitor MyVisitor(MyStruct.m_Float.GetName(), &MyFile);

	std::visit(MyVisitor, MyStruct.m_Float.GetVariant());
	std::cout << MyFile.dump(2) << std::endl;
}