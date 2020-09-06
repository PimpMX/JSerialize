#include "JSerialize.hpp"

void JSerialize::CPrimitiveVisitor::operator()(bool& Bool)
{
	(*m_pFile)[m_KeyName] = Bool;
}

void JSerialize::CPrimitiveVisitor::operator()(unsigned char& UCharacter)
{
	(*m_pFile)[m_KeyName] = UCharacter;
}

void JSerialize::CPrimitiveVisitor::operator()(char& Character)
{
	(*m_pFile)[m_KeyName] = Character;
}

void JSerialize::CPrimitiveVisitor::operator()(unsigned short& UShort)
{
	(*m_pFile)[m_KeyName] = UShort;
}

void JSerialize::CPrimitiveVisitor::operator()(short& Short)
{
	(*m_pFile)[m_KeyName] = Short;
}

void JSerialize::CPrimitiveVisitor::operator()(unsigned int& UInteger)
{
	(*m_pFile)[m_KeyName] = UInteger;
}

void JSerialize::CPrimitiveVisitor::operator()(int& Integer)
{
	(*m_pFile)[m_KeyName] = Integer;
}

void JSerialize::CPrimitiveVisitor::operator()(unsigned long& ULong)
{
	(*m_pFile)[m_KeyName] = ULong;
}

void JSerialize::CPrimitiveVisitor::operator()(long& Long)
{
	(*m_pFile)[m_KeyName] = Long;
}

void JSerialize::CPrimitiveVisitor::operator()(float& Float)
{
	(*m_pFile)[m_KeyName] = Float;
}

void JSerialize::CPrimitiveVisitor::operator()(double& Double)
{
	(*m_pFile)[m_KeyName] = Double;
}

