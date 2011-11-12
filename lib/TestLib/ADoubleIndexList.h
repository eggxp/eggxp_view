//---------------------------------------------------------------------------

#ifndef ADoubleIndexListH
#define ADoubleIndexListH
//---------------------------------------------------------------------------
#include	"AMap.h"
#include	"AList.h"

template <class T>  class	ADoubleIndexList
{
private:
	AIndexList<T>			m_Key1;
	AIndexList<T>			m_Key2;
public:
	ADoubleIndexList(bool	isAutoFree = true);
	~ADoubleIndexList();

	bool			Add(DWORD	key1, DWORD		key2, T * lpData);
	void			DeleteByKey1(DWORD	key1);
	void			DeleteByKey2(DWORD	key2);
	int				Count();
	T		*		At(int index);
	T 		* 		FindByKey1(DWORD	key1);
	T 		* 		FindByKey2(DWORD	key2);
};


template <class T>    ADoubleIndexList<T>::ADoubleIndexList(bool	isAutoFree) :
								m_Key1(false), m_Key2(isAutoFree)
{

}

template <class T>    ADoubleIndexList<T>::~ADoubleIndexList()
{

}

template <class T>    bool		ADoubleIndexList<T>::Add(DWORD	key1, DWORD		key2, T * lpData)
{
	if(m_Key1.AddEx(key1, lpData) && m_Key2.AddEx(key2, lpData))
		return true;

	return false;
}

template <class T>    void		ADoubleIndexList<T>::DeleteByKey1(DWORD	key1)
{
	T * lpData = FindByKey1(key1);
	m_Key2.Delete((size_t)lpData->Key2);
    m_Key1.Delete((size_t)key1);
}

template <class T>    void		ADoubleIndexList<T>::DeleteByKey2(DWORD	key2)
{
	T * lpData = FindByKey2(key2);
	m_Key1.Delete((size_t)lpData->Key1);
	m_Key2.Delete((size_t)key2);
}

template <class T>    int		ADoubleIndexList<T>::Count()
{
	return	m_Key2.Count();
}

template <class T>    T		*	ADoubleIndexList<T>::At(int index)
{
	return	m_Key2.At(index);
}

template <class T>    T 	* 	ADoubleIndexList<T>::FindByKey1(DWORD	key1)
{
	return 	m_Key1.Find(key1);
}

template <class T>    T 	* 	ADoubleIndexList<T>::FindByKey2(DWORD	key2)
{
	return	m_Key2.Find(key2);
}

#endif
