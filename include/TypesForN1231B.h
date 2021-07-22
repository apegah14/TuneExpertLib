#ifndef _TYPESFORN1231B_H
#define _TYPESFORN1231B_H

    typedef signed char                  S8;
    typedef unsigned char                  U8;
    typedef signed short                 S16;
    typedef unsigned short                 U16;
    typedef signed int                 S32;
    typedef unsigned int                 U32;
    typedef signed long long                 S64;
    typedef unsigned long long                 U64;
    typedef signed long           PLX_INT_PTR;        // For 32/64-bit code compatability
    typedef unsigned long         PLX_UINT_PTR;
    typedef int                   HANDLE;
    typedef int                   PLX_DRIVER_HANDLE;  // Linux-specific driver handle

    #define INVALID_HANDLE_VALUE  (HANDLE)-1

#endif	//_TYPESFORN1231B_H
