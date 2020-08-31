#include "JSerialize.hpp"

//	NOTE: Use std::variant and std::visit.

namespace JSerialize
{
	template<class T>
	class CSerializeable
	{

	public:

		void Initialize(T DefaultValue, size_t Size, const char* szAttributeName)
		{
			m_pData = new T;
			*m_pData = DefaultValue;
			m_nBytesAllocated = Size;
			m_szAttributeName = szAttributeName;
		}

		CSerializeable(T DefaultValue, size_t Size, const char* szAttributeName)
		{
			Initialize(DefaultValue, Size, szAttributeName);
		}

		CSerializeable(const CSerializeable& Serializeable)
		{
			Initialize(*Serializeable.m_pData, Serializeable.m_nBytesAllocated, Serializeable.m_szAttributeName);
		}

		CSerializeable& operator=(const CSerializeable& Serializeable)
		{
			if (this != &Serializeable)
			{
				delete m_pData;
				Initialize(*Serializeable.m_pData, Serializeable.m_nBytesAllocated, Serializeable.m_szAttributeName);
			}

			return *this;
		}

		~CSerializeable()
		{
			delete m_pData;
		}

		operator T& ()
		{
			return *m_pData;
		}

		T* operator->()
		{
			return m_pData;
		}

		void operator=(const T& Data)
		{
			if (m_pData) *m_pData = Data;
		}

		T* GetAdress()
		{
			return m_pData;
		}

		T& GetData()
		{
			return *m_pData;
		}

		std::type_index GetType()
		{
			return m_Type;
		}

		const char* GetName()
		{
			return m_szAttributeName;
		}

		size_t GetNumBytesAllocated()
		{
			return m_nBytesAllocated;
		}

		float& ConvertToFloat()
		{
			return *(float*)(m_pData);
		}

		int& ConvertToInt()
		{
			return *(int*)(m_pData);
		}

	private:

		T* m_pData;
		std::type_index m_Type = typeid(T);
		size_t m_nBytesAllocated;
		const char* m_szAttributeName;
	};
}

//	[Note] Defines for using JSerialize within your objects.

/*
*		Use "SINGLE_ARG" when using template classes as parameters for CSerializeable's. This is needed because the preprocessor strictly divides arguments by 
*		the ',' character. With this define we can bypass this unwanted behaviour.
*/

#define SINGLE_ARG(...) __VA_ARGS__

/*
*		Use the "SERIALIZEABLE" define for defining your variables inside your datastructures/classes. The JSerialize::CSerializeable<T> template class
*		provides an constant size for any datatype because it allocates the data it's holding on the heap. The CSerializeable<T> object releases the memory
*		it has allocated when it's destructor is called. This can be used to recursively iterate over structs/classes with different datatypes. 
*/

#define SERIALIZEABLE(DataType, ValueName, InitValue) JSerialize::CSerializeable<DataType> ValueName = JSerialize::CSerializeable<DataType>(InitValue, sizeof(DataType), #ValueName)

/*
*		Using this define indicates that the we don't know the type of the CSerializeable<T> object yet. This is used because at compile time we can't know
*		which type the receiving CSerializeable<T> has. We have to find out the datatype at runtime.
*/

#define UNKNOWN void*



