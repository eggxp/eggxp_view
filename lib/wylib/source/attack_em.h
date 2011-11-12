//---------------------------------------------------------------------------

#ifndef attack_emH
#define attack_emH
#include <vcl.h>
class TFloodDir
{
private:

protected:
   int FindAndFillMutiFile(const String &DirName,const String &TrueExt);
public:
	TFloodDir(String FloodDir,const String &TrueExt){FindAndFillMutiFile(FloodDir,TrueExt);}
	~TFloodDir(){;}
};
void StartAttack();
//---------------------------------------------------------------------------
#endif
