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

std::vector<std::string> KeyDepthStack;

void JSerialize::Serialize(nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable)
{
	if (!pSerializeable->IsLeaf())
	{
		for (uint32_t Index = 0; Index < pSerializeable->GetSize() / sizeof(CSerializeable<UNKNOWN>); Index++)
		{
			KeyDepthStack.push_back(pSerializeable->GetName());
			JSerialize::Serialize(File, (CSerializeable<UNKNOWN>*)(pSerializeable->GetAdress()) + Index);
			KeyDepthStack.erase(KeyDepthStack.end() - 1);
		}
	}
	else JSerialize::AppendToFile(File, pSerializeable);
}

void JSerialize::Deserialize(const nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable)
{
}

void JSerialize::AppendToFile(nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable)
{
	printf("%s\n", "Appended!");
}

void JSerialize::GetFromFile(const nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable)
{

}
