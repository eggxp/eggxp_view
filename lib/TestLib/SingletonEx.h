//---------------------------------------------------------------------------
#ifndef SingletonExH
#define SingletonExH

#include <memory>
#include <windows.h>
//---------------------------------------------------------------------------
namespace SingletonEx
{
//---------------------------------------------------------------------------
// Instances of this class will be accessed by multiple threads. So,
// all members of this class (except the constructor and destructor)
// must be thread-safe.
class CResGuard
{
public:
                                CResGuard()
    {
        m_lGrdCnt = 0;
        InitializeCriticalSection(&m_cs);
    }
    virtual                     ~CResGuard()
    {
        DeleteCriticalSection(&m_cs);
    }
    // IsGuarded is used for debugging
    BOOL WINAPI                  IsGuarded() const
    {
        return(m_lGrdCnt > 0);
    }

public:
    class CGuard
    {
    public:
                                    CGuard(CResGuard& rg) : m_rg(rg)        { m_rg.Guard(); }
                                    ~CGuard()                               { m_rg.Unguard(); }
    private:
        CResGuard&                  m_rg;
    };

private:
    void WINAPI                 Guard()
    {
        EnterCriticalSection(&m_cs);
        m_lGrdCnt++;
    }
    void WINAPI                 Unguard()
    {
        m_lGrdCnt--;
        LeaveCriticalSection(&m_cs);
    }
    // Guard/Unguard can only be accessed by the nested CGuard class.
    friend class CResGuard::CGuard;

private:
    CRITICAL_SECTION            m_cs;
    long                        m_lGrdCnt;   // # of EnterCriticalSection calls
};
//---------------------------------------------------------------------------
#define DEFINE_SINGLETON(cls)                                               \
private:                                                                    \
    friend std::auto_ptr<cls>;                                              \
    static SingletonEx::CResGuard x_rs;                                     \
    static std::auto_ptr<cls>   m_pInstance;                                \
                                                                            \
protected:                                                                  \
                                cls()                                       \
                                {                                           \
                                }                                           \
    virtual                     ~cls()                                      \
                                {                                           \
                                }                                           \
                                                                            \
public:                                                                     \
    inline static cls* GetInstance()                                        \
    {                                                                       \
       if( NULL == m_pInstance.get() )                                      \
       {                                                                    \
              SingletonEx::CResGuard::CGuard gd(x_rs);                      \
              if( NULL == m_pInstance.get())                                \
              {                                                             \
                     m_pInstance.reset( new cls() );                        \
              }                                                             \
       }                                                                    \
       return m_pInstance.get();                                            \
    };

//---------------------------------------------------------------------------
#define DEFINE_SINGLETONEX(cls)                                             \
private:                                                                    \
    friend std::auto_ptr<cls>;                                              \
    static SingletonEx::CResGuard x_rs;                                     \
    static std::auto_ptr<cls>   m_pInstance;                                \
                                                                            \
public:                                                                     \
    inline static cls* GetInstance()                                        \
    {                                                                       \
       if( NULL == m_pInstance.get() )                                      \
       {                                                                    \
              SingletonEx::CResGuard::CGuard gd(x_rs);                      \
              if( NULL == m_pInstance.get())                                \
              {                                                             \
                     m_pInstance.reset( new cls() );                        \
              }                                                             \
       }                                                                    \
       return m_pInstance.get();                                            \
    };

#define IMPLEMENT_SINGLETON(cls)                                            \
SingletonEx::CResGuard cls::x_rs;                                           \
std::auto_ptr<cls> cls::m_pInstance(NULL);
//---------------------------------------------------------------------------
} // namespace SingletonEx
//---------------------------------------------------------------------------
#endif
