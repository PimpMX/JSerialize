#pragma once

#include <typeinfo>
#include <variant>
#include <string>

//	nlohmanns json is responsible for parsing/saving json data.

#include "Dependencies/json.hpp"

//	Define all possible types in Types.hpp

#include "Types.hpp"

/*
*		Using this define indicates that the we don't know the type of the CSerializeable<T> object yet. This is used because at compile time we can't know
*		which type the receiving CSerializeable<T> has. We have to find out the datatype at runtime.
*/

#define UNKNOWN void*

namespace JSerialize
{
	/*
	*		The purpose of the CSerializeable class is to bind data of any datatype to an attribute name
	*		for serialization. This is used to loop through CSerializeable objects in config datastructures
	*		and fetch the name of the current attribute for serializing the CSerializeable object under the correct name.
	*/

	template<class T>
	class CSerializeable
	{

	public:

		void Initialize(bool IsLeaf, T DefaultValue, size_t Size, std::string VarName)
		{
			m_bLeaf = IsLeaf;
			m_nSize = Size;
			m_VarName = VarName;
			m_pData = new std::variant<POSSIBLE_TYPES>();
			*m_pData = DefaultValue;
		}
		
		CSerializeable()
		{
			m_bLeaf = true;
			m_nSize = 0;
			m_VarName = "undefined";
			m_pData = nullptr;
		}

		CSerializeable(bool IsLeaf, T DefaultValue, size_t Size, std::string VarName)
		{
			Initialize(IsLeaf, DefaultValue, Size, VarName);
		}

		CSerializeable(const CSerializeable& Serializeable)
		{
			Initialize(Serializeable.m_bLeaf, std::get<T>(*Serializeable.m_pData), Serializeable.m_nSize, Serializeable.m_VarName);
		}

		CSerializeable& operator=(const CSerializeable& Serializeable)
		{
			if(this != &Serializeable)
			{
				m_bLeaf = Serializeable.m_bLeaf;
				m_nSize = Serializeable.m_nSize;
				m_VarName = Serializeable.m_VarName;
				*m_pData = *Serializeable.m_pData;
			}

			return *this;
		}

		~CSerializeable()
		{
			delete m_pData;
		}

		//	Assignment.

		void operator=(const T& Data)
		{
			*m_pData = Data;
		}

		//	Implicit access.

		operator T&()
		{
			return std::get<T>(*m_pData);
		}

		T* operator->()
		{
			return &std::get<T>(*m_pData);
		}

		//	Explicit access.

		T* GetAdress()
		{
			return &std::get<T>(*m_pData);
		}

		T& GetData()
		{
			return std::get<T>(*m_pData);
		}

		//	Object attribute access.

		bool IsLeaf()
		{
			/*
			*	m_bLeaf == false indicates that the underlying type of the CSerializeable<T> consists of one or more CSerializeable<T> objects
			*	which means the current object can't be serialized by our visitor. m_bLeaf == true means that the underlying type doesn't consist
			*	of any more CSerializeable<T> objects and can be serialized.
			*/

			return m_bLeaf;
		}

		size_t GetSize()
		{
			return m_nSize;
		}
		
		std::string GetName()
		{
			return m_VarName;
		}

		std::variant<POSSIBLE_TYPES>& GetVariant()
		{
			return *m_pData;
		}

	private:

		bool m_bLeaf;
		size_t m_nSize;
		std::string m_VarName;
		std::variant<POSSIBLE_TYPES>* m_pData;
	};

	/*
	*		The CPrimitveVisitor class provides operators for all the primitve types for serialization. It is used when 'visiting' the
	*		std::variant. If you're using more types or your own objects you need to create a new visitor class which derives from 
	*		this class and implement operators for your datatypes.
	*/

	class CPrimitiveVisitor
	{

	public:

		CPrimitiveVisitor(std::string KeyName, nlohmann::json* pFile)
		{
			m_KeyName = KeyName;
			m_pFile = pFile;
		}

		void SetKeyName(std::string KeyName)
		{
			m_KeyName = KeyName;
		}

		void operator()(bool& Bool);
		void operator()(unsigned char& UCharacter);
		void operator()(char& Character);
		void operator()(unsigned short& UShort);
		void operator()(short& Short);
		void operator()(unsigned int& UInteger);
		void operator()(int& Integer);
		void operator()(unsigned long& ULong);
		void operator()(long& Long);
		void operator()(float& Float);
		void operator()(double& Double);

	private:

		std::string m_KeyName;
		nlohmann::json* m_pFile;
	};

	void Serialize(nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable);
	void Deserialize(const nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable);

	void AppendToFile(nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable);
	void GetFromFile(const nlohmann::json& File, CSerializeable<UNKNOWN>* pSerializeable);
}

/*
*		Use the "SERIALIZEABLE" define for defining your variables inside your datastructures/classes. The JSerialize::CSerializeable<T> template class
*		provides an constant size for any datatype because it allocates the data it's holding on the heap. The CSerializeable<T> object releases the memory
*		it has allocated when it's destructor is called.
*/

#define SERIALIZEABLE(DataType, ValueName, InitValue, IsLeaf) JSerialize::CSerializeable<DataType> ValueName = JSerialize::CSerializeable<DataType>(IsLeaf, InitValue, sizeof(DataType), #ValueName)

