//---------------------------------------------------------------------------
//构造任意类型的2维数组模板类  by bluely 2003.05
//用法举例:
//typedef Array2D<int> IntArray;
//IntArray ia(640,480);  创建一个640,480的int二维数组
//注意,此类内部进行了基于内存的memcpy动作，所以不支持复杂类作为T,只能支持支持memcpy操作的数据类型和struct

#ifndef array_2dH
#define array_2dH
template <class T>
class Array2D
{
  private:
   T **  m_lppBufMap;           //存放实际数据的数组指针
   int m_Width;               //数组的宽度(列数)
   int m_Height;              //数组的高度(行数)
   int m_Size;                  //数组的大小
  public:
   __fastcall Array2D();
   __fastcall ~Array2D();
   __fastcall Array2D(int Width,int Heigth);
   __fastcall Array2D(int Width,int Heigth,void *Data);
   void Create(int Width,int Height);            //根据宽和高创建空数据数据
   void Create(int Width,int Height,void *Data); //根据数据缓冲区创建二维数组
   void Free();                                 //清空并且释放内存
   __inline int  Width(){return m_Width;}
   __inline int  Height(){return m_Height;}
   __inline int  Size(){return m_Size;}
   __inline int  BufferSize(){return   m_Size * sizeof(T);}   //缓冲区中的数据实际占用内存大小
   void *        Data(); //获取数组实际缓冲区,配合BufferSize()函数使用,可以得到缓冲区和缓冲区长度,直接对缓冲区进行操作
   T * operator[](int i) {return m_lppBufMap[i];}
};
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D()
{
   m_lppBufMap = NULL;
   m_Width  = 0;
   m_Height = 0;
   m_Size = 0;
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D(int Width,int Heigth)
{
  m_lppBufMap = NULL;
  Create(Width,Heigth);
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::Array2D(int Width,int Heigth,void *Data)
{
  m_lppBufMap = NULL;
  Create(Width,Heigth,Data);
}
//---------------------------------------------------------------------------
template <class T>
__fastcall Array2D<T>::~Array2D()
{
  Free();
}
//---------------------------------------------------------------------------
template <class T>
void Array2D<T>::Create(int Width,int Height)
{
    Free();
    m_Width  = Width;
    m_Height = Height;
    m_Size   = m_Width * m_Height;
    m_lppBufMap = new T *[m_Width];    //分配第一维
    m_lppBufMap[0] = new T[m_Size];  //分配第二维
    ZeroMemory(m_lppBufMap[0], m_Size * sizeof(T));
    for(int i = 1; i < m_Width; i++)
    {
        m_lppBufMap[i] = m_lppBufMap[i - 1] + m_Height;
    }
}
//---------------------------------------------------------------------------
template <class T>
void Array2D<T>::Create(int Width,int Height,void *Data)
{
    Create(Width,Height);
    memcpy(m_lppBufMap[0],Data,m_Size * sizeof(T));
}


//---------------------------------------------------------------------------
template <class T>
void  Array2D<T>::Free()
{
   if (m_lppBufMap)
   {
     if (m_lppBufMap[0] != NULL)
     {
       delete [] m_lppBufMap[0];
     }
     delete []m_lppBufMap;
     m_lppBufMap = NULL;
   }
   m_Width  = 0;
   m_Height = 0;
   m_Size = 0;
}
//---------------------------------------------------------------------------
template <class T>
void *  Array2D<T>:: Data()
{
    if (m_Size <= 0)
    {
      return NULL;
    }
    return m_lppBufMap[0];
}
//---------------------------------------------------------------------------
#endif
