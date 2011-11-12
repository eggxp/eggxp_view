//---------------------------------------------------------------------------

#ifndef singprocH
#define singprocH
#include <vcl.h>
//单进程限定类
//---------------------------------------------------------------------------
class WYSingleProc
{
private:
   String Name;
protected:
	virtual bool MutexCheck(bool &IsExists);
	virtual bool FileCheck(bool &IsExists);
	virtual bool EventCheck(bool &IsExists);
public:
	WYSingleProc(String ObjName);
	~WYSingleProc();
	virtual bool Check(bool &IsExists);   //返回真表示已经有实例存在,
};
#endif
