//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once


namespace Kodiak
{

struct BaseObject
{
	std::variant<uint64_t, void*> value;

	BaseObject(uint64_t i)
		: value(i)
	{}

	BaseObject(void* p)
		: value(p)
	{}

	template<typename T> operator T* () const { return static_cast<T*>(std::get<void*>(value)); }
};


class IObject : NonCopyable, NonMovable
{
protected:
	IObject() = default;
	virtual ~IObject() = default;

public:
	virtual HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj) = 0;
	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
};


template <class T>
class TRefCount : public T
{
private:
	std::atomic<unsigned long> m_refCount = 1;
public:
	HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj) final
	{
		if (!ppvObj)
		{
			return E_INVALIDARG;
		}

		*ppvObj = nullptr;
		
		if (riid == IID_IUnknown || riid == T::IID)
		{
			*ppvObj = (LPVOID)this;
			AddRef();
			return NOERROR;
		}

		return E_NOINTERFACE;
	}

	ULONG AddRef() final
	{
		++m_refCount;
		return m_refCount;
	}

	ULONG Release() final
	{
		ULONG ulRefCount = --m_refCount;
		if (0 == m_refCount)
		{
			delete this;
		}
		return ulRefCount;
	}
};

} // namespace Kodiak