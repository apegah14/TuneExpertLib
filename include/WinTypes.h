#ifndef _WINTYPES_H
#define _WINTYPES_H

typedef S32	LONG;
typedef U32	DWORD;
typedef long LONGLONG;		// assumes 64-bit linux
typedef void * LPVOID;
typedef void * HGLOBAL;
typedef unsigned int UINT;
typedef unsigned long ULONG_PTR;	// assumes 64-bit linux
typedef ULONG_PTR SIZE_T;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;

#endif	//_WINTYPES_H
