/*
 * Copyright 2018 by Keysight Technologies
 *
 * File Name: N1231B.h
 *
 * Header file for the API library for the
 * Keysight Technologies N1231B PCI Three-Axis Board
 * designed for use with an Keysight Technologies
 * laser interferometry position measurement systems.
 *
 * See also file N1231B_reg.h
 *
 * Last revision of this file:
 *   26 Aug 2004
 *	  4 Mar 2011 - v2.4 - add support Win7 and 64-bit OS.
 *   30 Oct 2014 - v2.5 - add *HdwIoSetup() routines and 64-bit DLL
 *   03 Apr 2018 - v2.5.1 - adjust comments for use of new bits, add N1231BSyncPDClks()
 *   22 Apr 2018 - v2.6.0 - fold high data rate data types and routines into API DLL
 * 	 20 Jul 2021 - v2.6.1 - edited for use with MinGW (gcc) and minor modifications for Linux compilation
 */

 /*
  * Changes for version 2.4:
  *		Added N1231BPciInterruptDetach() and N1231BPciInterruptWait() routines.
  *		Changed operation of N1231BPciInterruptAttach() routine.
  *		Added N1231B_WAIT_TIMEOUT and N1231B_WAIT_CANCEL return values.
  *
  * Changes for version 2.5:
  *		Added N1231BSetHdwIoSetup() and N1231BGetHdwIoSetup() routines.
  *		Added support for newly defined bits in Data Clock Control and Filter Settings registers.
  *		Added 64-bit DLL so 64-bit applications can access the N1231B.
  *
  * Changes for version 2.6:
  *		Added new data types:
  *				TS_SMPL_INFO, TU_MULTI_ACCESS,
  *				TS_N1231B_HDR_1POS, TS_N1231B_HDR_1POSVEL,
  *				TS_N1231B_HDR_SYSPOS, TS_N1231B_HDR_SYSPOSVEL.
  *		Added new routines:
  *				N1231BpollRead1AxisPos32(), N1231BpollReadSysPos32(),
  *				N1231BpollRead1AxisPosVel(), N1231BpollRead3AxisPosVel(),
  *				N1231BpollReadSysPosVel(), N1231BpolltsRead1AxisPos32(),
  *				N1231BpolltsReadSysPos32(), N1231BpolltsRead1AxisPosVel(),
  *				N1231BpolltsRead3AxisPosVel(), N1231BpolltsReadSysPosVel()
  */

#ifndef N1231B_H
#define N1231B_H

#include "N1231B_reg.h"


#ifdef _WIN32
    #include <windows.h>
#endif


/*
 ****************************************************************
 * C/C++ Compatibility
 ********************************
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************
 * when building DLL, Import in client applications
 ********************************
 */
/*
#ifdef VXWORKS
	#define EXPORT			// Do nothing
#else
	#ifdef USE_STATIC		// Should not be defined if used with N1231B.dll
		#define EXPORT		// Do nothing
	#else
		#ifdef MAKE_DLL
			#define EXPORT	__declspec(dllexport)
		#else
			#define  __declspec(dllimport)
		#endif
	#endif
#endif
*/
/* 
 ************************************
 ************************************
 * DEFINITIONS OF TERMS :
 *
 *  Raw Interferometer Units:
 *    Position and velocity values used by these 
 *    functions are expressed in Raw Interferometer Units.
 *
 *    For Position Information:
 *      Raw Interferometer Position Unit 
 *          = Lambda / (1024 * FoldFactor)
 *
 *    For Velocity Information:
 *      Raw Interferometer Velocity Unit 
 *          = (Lambda * 20E6 Hz) / (2^22 * FoldFactor)
 *
 *    Where:
 *      Lambda = Wavelength of Light 
 *      FoldFactor = 
 *        2 for a Linear Optics System,
 *        4 for a Plane Mirror Optics System, or
 *        8 for a High Resolution Optics System.
 *
 ************************************
 ************************************
 */

/*
 ************************************
 ************************************
 * TABLE OF CONTENTS
 ************************************
 ************************************
 *
 * ==================================
 * Typedefs, Constants, Enums, Structures
 * ==================================
 *
 * Used for opening device:
 *		N1231B_HANDLE
 *		N1231B_IGNORE_FIELD
 *		N1231B_LOCATION
 *
 * Used for 36 bit data:
 *		N1231B_INT64
 *		TU_MULTI_ACCESS
 *		TS_N1231B_HDR_1POS
 *		TS_N1231B_HDR_1POSVEL
 *		TS_N1231B_HDR_SYSPOS
 *		TS_N1231B_HDR_SYSPOSVEL
 *
 * Used for retrieving results into an array
 *		N1231B_SAMPLES
 *
 * Used for interrupts
 *		N1231B_EVT_HANDLE;
 *
 * Used for error returns:
 *		N1231B_RETURN
 *
 * Used for axis identification
 *		N1231B_AXIS
 *
 * Used to specify type of sampled data to retrieve
 *		N1231B_SAMP_TYPE
 *
 * Used to specify sampling parameters and results:
 *		TS_SMPL_INFO
 *
 * Used for programmable data clock identification
 *		N1231B_PDCLOCK
 *
 * ==================================
 * High Level Functions
 * ==================================
 *
 * N1231BOpen()
 * N1231BDefaultDevice()
 * N1231BClose()
 * N1231BFind()
 * N1231BPresetRaw()
 * N1231BPresetRawAll()
 * N1231BGetRawPosVel()
 * N1231BGetRawPosVelAll()
 * N1231BGetRawXSysSample()
 * N1231BGetRawXSysSampleAll()
 * N1231BGetRawXSysSampleAllArray()
 * N1231BGetRawXAxisSample()
 * N1231BGetRawXAxisSampleAll()
 * N1231BGetRawXAxisSampleAllArray()
 * N1231BGetRawXSampleAll()
 * N1231BGetRawXSampleAllArray()
 * N1231BClearStatusBits()
 * N1231BClearPathErrorAll()
 * N1231BClearStatusAll()
 * N1231BGetStatus()
 * N1231BSetInterruptMask()
 * N1231BGetInterruptMask()
 * N1231BSetConfig()
 * N1231BGetConfig()
 * N1231BSetGeLtDirections()
 * N1231BGetGeLtDirections()
 * N1231BSetGeLtThresholds()
 * N1231BGetGeLtThresholds()
 * N1231BGetGeLtStatus()
 * N1231BSetPDClockControl()
 * N1231BGetPDClockControl()
 * N1231BSetFilter()
 * N1231BGetFilter()
 * N1231BSetHdwIoSetup()	- new rev 2.5
 * N1231BGetHdwIoSetup()	- new rev 2.5
 * N1231BSyncPDClks()       - new rev 2.5.1
 * N1231BGetFPGARevs()
 * N1231BGetFPGAIds()
 * N1231BGetHdwRev( )
 * N1231BGetLibraryRev()
 * N1231BGetErrStr()
 *
 * ==================================
 * Polling Data Collection Functions
 * ==================================
 *
 * N1231BpollRead1AxisPos32()	- fastest 1-axis routine
 * N1231BpollReadSysPos32()		- fastest 3-axis routine
 *
 * N1231BpollRead1AxisPosVel()	- can set some params to NULL
 * N1231BpollRead3AxisPosVel()	- can set some params to NULL
 *
 * N1231BpollReadSysPosVel()
 *
 *
 * ==================================
 * Polling with TimeStamp Data Collection Functions
 * ==================================
 *
 * N1231BpolltsRead1AxisPos32()
 * N1231BpolltsReadSysPos32()
 *
 * N1231BpolltsRead1AxisPosVel()
 * N1231BpolltsRead3AxisPosVel()	- can set some params to NULL
 *
 * N1231BpolltsReadSysPosVel()
 *
 * ==================================
 * Interrupt Related Functions
 * ==================================
 *
 * N1231BSetGlobalInterruptEnable()
 * N1231BGetGlobalInterruptEnable()
 * N1231BPciInterruptEnable()
 * N1231BPciInterruptAttach()	<- Only available under Windows (modified in v2.4)
 * N1231BPciInterruptDetach()	<- Only available under Windows (new in v2.4)
 * N1231BPciInterruptWait()		<- Only available under Windows (new in v2.4)
 * N1231BPciAttachIsr()			<- Not available under Windows.
 *
 * ==================================
 * Lower Level Functions
 * ==================================
 *
 * N1231BSamplePosVel()
 * N1231BReadRawPos()
 * N1231BReadRawVel()
 * N1231BWriteRawPresetRegister()
 * N1231BReadRawPresetRegister()
 *
 * ==================================
 * Register Functions (for test use only)
 * ==================================
 *
 * N1231BWriteRegisterLong()
 * N1231BReadRegisterLong()
 * N1231BWriteRegisterWord()
 * N1231BReadRegisterWord()
 *
 */

/*
 ************************************
 ************************************
 * DECLARATIONS
 ************************************
 ************************************
 */

 /*
 ****************************************************************
 * Typedefs, Constants, Enums, Structures
 ********************************
 */

/*
 * Used for opening device
 */
typedef void *N1231B_HANDLE;

#define N1231B_IGNORE_FIELD	0xffffffff

typedef struct
{
	/*
	 * Set following fields to identify device to open.
	 * Values set to IGNORE_FIELD (see above) will not be used
	 * when searching for a device, but will be filled in
	 * by the search or open function once a device is found.
	 */
	unsigned long	BusNumber;
	unsigned long	SlotNumber;
} N1231B_LOCATION;

/*
 * Used for 36 bit data.
 *   Note: Only the 4 lsb of the msb field are used when setting
 *         values into the card.  However, when reading data back
 *         from the card the msb data is sign-extended to fill 
 *         the field.
 */
typedef struct
{
	unsigned long	lsb;
	long			msb;
}N1231B_INT64;

typedef union TU_MULTI_ACCESS
	{									// see routine comments for use of each word in structure
	N1231B_INT64 n31i64;
	short s[4];
	unsigned long ul[2];
	} MULTI_ACCESS, *pMULTI_ACCESS;

typedef struct TS_N1231B_HDR_1POS
	{
	LARGE_INTEGER ts;					// timestamp value
	MULTI_ACCESS umaPos;
	} N1231B_HDR_1POS, * pN1231B_HDR_1POS;

typedef struct TS_N1231B_HDR_1POSVEL
	{
	LARGE_INTEGER ts;					// timestamp value
	MULTI_ACCESS umaPos;
	long lVel;
	} N1231B_HDR_1POSVEL, * pN1231B_HDR_1POSVEL;

typedef struct TS_N1231B_HDR_SYSPOS
	{
	LARGE_INTEGER ts;					// timestamp value
	unsigned long ulAx1poslsb;			// position LSBs or velocity data
	unsigned long ulAx2poslsb;
	unsigned long ulAx3poslsb;
	short sAx123msbValid;				// bitwise OR of A12*UB and A3*UB registers
	short sSysOverrunErr;				// Status Register 2
	} N1231B_HDR_SYSPOS, * pN1231B_HDR_SYSPOS;

typedef struct TS_N1231B_HDR_SYSPOSVEL
	{
	LARGE_INTEGER ts;					// timestamp value
	unsigned long ulAx1poslsb;			// position LSBs
	unsigned long ulAx2poslsb;
	unsigned long ulAx3poslsb;
	short sAx123msbValid;				// bitwise OR of A12*UB and A3*UB registers
	short sSysOverrunErr;				// Status Register 2
	long lAx1vel;						// velocity data
	long lAx2vel;
	long lAx3vel;
	} N1231B_HDR_SYSPOSVEL, * pN1231B_HDR_SYSPOSVEL;


/*
 * Used for retrieving results into an array
 */
typedef struct
{
	unsigned long	index;
	unsigned short	*pPosMsb;
	long			*pPosLsb1;
	long			*pVel1;
	long			*pPosLsb2;
	long			*pVel2;
	long			*pPosLsb3;
	long			*pVel3;
} N1231B_SAMPLES;
 
/*
 * Used for interrupts
 */
typedef void *N1231B_EVT_HANDLE;

/*
 * Used for error returns
 */
typedef short N1231B_RETURN;
enum E_N1231B_RETURN
{
	N1231B_SUCCESS		= 0,
	N1231B_ERR_HANDLE	= 16, /* Leave a space for bitmap-type errors */
	N1231B_ERR_PARAM,
	N1231B_ERR_DEVICE,
	N1231B_ERR_DRIVER,
	N1231B_ERR_MEMORY,		/* Insufficient mem for device */
	N1231B_ERR_REG,			/* Invalid register address */
	N1231B_ERR_HEAP,		/* No space on heap */
	N1231B_ERR_HEAP_LOCKED,	/* Should never occur */
	N1231B_ERR_BAD_AXIS,	/* Axis does not exist */
	N1231B_ERR_AXIS,		/* Axis or reference has status error or invalid data */
	N1231B_ERR_UNKNOWN1,	/* Should never occur */
	N1231B_ERR_UNKNOWN2,	/* Should never occur */
	N1231B_ERR_UNKNOWN3,	/* Should never occur */
	N1231B_ERR_UNKNOWN4,	/* Should never occur */
	N1231B_ERR_UNKNOWN5,	/* Should never occur */
	N1231B_ERR_UNKNOWN6,	/* Should never occur */
	N1231B_ERR_UNKNOWN7,	/* Should never occur */
	N1231B_ERR_MAX_EVENTS,
	N1231B_WAIT_TIMEOUT,	/* wait for intr function timed out */
	N1231B_WAIT_CANCEL		/* wait for intr was cancelled */
};

/*
 * Used for axis identification
 */
typedef short N1231B_AXIS;
enum E_N1231B_AXIS
{
	AXIS_1,
	AXIS_2,
	AXIS_3,
	AXIS_3A,	// Used when working with comparators 
	AXIS_3B		// Used when working with comparators 
};

/*
 * Used to specify type and quantity of sampled data to retrieve
 */
typedef short N1231B_SAMP_TYPE;
enum E_N1231B_SAMP_TYPE
{
	SAMP_TYPE_SWS,
	SAMP_TYPE_AXS,
	SAMP_TYPE_SYS
};

typedef struct TS_SMPL_INFO
	{
	unsigned long ulRequested;			// samples to get
	unsigned long ulObtained;			// samples actually obtained
	unsigned long ulTimeoutLoopCount;	// # of iterations (ms for *isr* ruotines) before timeout error
	} SMPL_INFO, *pSMPL_INFO;

/*
 * Used for programmable data clock identification
 */
typedef short N1231B_PDCLOCK;
enum E_N1231B_PDCLOCK
{
	PDCLK_1,
	PDCLK_2,
	PDCLK_BOTH	
};

 /*
 *********************************************
 *********************************************
 * FUNCTION DECLARATIONS
 *********************************************
 *********************************************
 */

/*
 * ==================================
 * High Level Functions
 * ==================================
 */

/************************************************************************/
N1231B_RETURN 
N1231BOpen(N1231B_LOCATION	*pDevice,
		   N1231B_HANDLE	*pN1231BHandle,
		   unsigned long	*pProductId);
/*
 *	Opens N1231B-type device specified by structure *pDevice.
 *
 *	If pDevice points to NULL, then this function will open the
 *	first N1231B-type device that is found.  
 *
 *	If pDevice points to a structure of type N1231B_LOCATION 
 *  then this function will open the first N1231B-type device 
 *	matching the information in pDevice.  Upon successful 
 *	completion of this function any incomplete fields in 
 *	*pDevice will have been filled in (to show the bus and  
 *	slot of the device opened).  
 *
 *	An N1231B-type device is any PCI device with the Keysight
 *	Vendor ID (0x15bc) and Device ID = 0x0a00.  Other Keysight
 *	axis cards (for example, the N1231A) may use these same IDs, 
 *  but can be istinguished by the ProductId (see below). 
 *
 *	Parameter *pN1231BHandle returns a handle required by other 
 *	functions to reference the opened device.  
 *
 *	If pProductId is not NULL, then *pProductId will be set
 *	to the ID code of FPGA1. For an N1231B card this value should 
 *	be 0x0001231B.  If other axis cards are present, this code can be 
 *	used to verify that the correct card model was opened.
 *	NOTE THAT *pProductId is used only to return a value -- its 
 *	value upon entry to this function is ignored.
 *
 *	Before exiting from the application which called this function,
 *	a call should be made to N1231BClose() to release the handle and 
 *	its associated memory block.
 *
 *  The function N1231BDefaultDevice() can be called to initialize 
 *  pDevice to find the first N1231B (or N1231B-type device).  
 *  Calling N1231BOpen() using this default pDevice is the same as 
 *  calling it with a pointer to NULL, except that supplying a pointer 
 *  to the N1231B_LOCATION structure allows return of information on 
 *  the device found.
 *
 *	The return code specifies the success or failure of this function,
 *	as follows:
 *		N1231B_SUCCESS:		The function returned successfully.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_DEVICE:	No device found.
 *		N1231B_ERR_DRIVER:	No device driver installed.
 *		N1231B_ERR_MEMORY:	Insufficient memory.
 *		N1231B_ERR_HEAP:	No space on heap.
 */

/************************************************************************/
void
N1231BDefaultDevice(N1231B_LOCATION	*pDevice);
/*
 *	Fills structure *pDevice with default values. 
 *	Using these default values with N1231BOpen() will cause the 
 *	first N1231B-type device in the system to be opened.  If there is 
 *  only one such device in the system, this provides a simple method
 *	for opening the device.  If there are multiple N1231B-type cards
 *	then after calling this function it will be necessary to 
 *	modify one or more fields to specify the particular card 
 *	to be opened.
 * 
 * EXAMPLE:
 *  pDevice->BusNumber	= IGNORE_FIELD;
 *  pDevice->SlotNumber	= IGNORE_FIELD;
 */

/************************************************************************/
N1231B_RETURN
N1231BClose(N1231B_HANDLE	*pN1231BHandle);
/*
 *	Closes the N1231B card specified by *pN1231BHandle.
 *  If successful, *pN1231BHandle is set to NULL.
 *
 *	The return code specifies the success of failure of this function,
 *	as follows:
 *		N1231B_SUCCESS:		The function returned successfully
 *      N1231B_PARAM:		A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid
 *		N1231B_ERR_DEVICE:	Device not closed properly.
 *		N1231B_ERR_HEAP:	Error accessing heap.
 */

/************************************************************************/
N1231B_RETURN 
N1231BFind(const N1231B_LOCATION	*pDevice,
		   unsigned int				*pNumFound,
		   N1231B_LOCATION			*pDeviceArray,
		   unsigned int				numMax);
/*
 *	Determines the number of N1231B-type devices in the system 
 *	and (optionally) builds an array of information on 
 *	these devices.
 *
 *	If numMax is zero and pDeviceArray is NULL, then reports
 *	total number of N1231B-type devices matching the pDevice 
 *	description.
 *
 *	Otherwise, builds an array (at pDeviceArray) of the first numMax
 *	devices found.
 *
 *  PARAMETERS:
 *		*pDevice:
 *			Pointer to structure of type N1231B_LOCATION.
 *			If NULL, search will find all N1231B-type devices.
 *			If non-NULL, search will be limited to devices
 *				matching the specified criteria.
 *		*pNumFound
 *			Returns number of devices found.
 *			If numMax is zero and pDeviceArray is NULL then
 *				this will be the total number of devices matching
 *				the description.
 *			Otherwise, this number will not exceed numMax.
 *		*pDeviceArray
 *			Pointer to array of structures of type N1231B_LOCATION
 *			used to return information on found devices.  If NULL, 
 *			then numMax must be zero.
 *		*numMax
 *			Maximum number of devices to be reported.  The array 
 *			at pDeviceArray must be at least this large. 
 *			If pDeviceArray is NULL, then numMax must be zero.
 *
 *	ERROR CODES:
 *	  The return code specifies the success of failure of this function,
 *	  as follows:
 *		N1231B_SUCCESS:		The function returned successfully.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_DEVICE:	No device found.
 *		N1231B_ERR_DRIVER:	No device driver installed.
 *		N1231B_ERR_MEMORY:	Insufficient memory.
 *	  In case of error, *pNumFound will be set to zero.
 */

/************************************************************************/
N1231B_RETURN
N1231BPresetRaw(N1231B_HANDLE	N1231BHandle,
			    N1231B_AXIS		axis,
			    N1231B_INT64	preset,
			    unsigned long	*pStatus);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis, attempts to perform the following:
 *
 *	a) Load the Preset Position register with preset,
 *	b) Reset all errors on the specified axis and the ref axis.
 *	c) Transfer the Preset Position value to the Position register
 *     (i.e., perform a Position Preset operation).
 *	d) If pStatus is non-NULL, set *pStatus to show contents of the status 
 *     registers.
 *
 *	The preset value is in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS:	 The axis still shows a status error.
 */

/************************************************************************/
N1231B_RETURN
N1231BPresetRawAll(N1231B_HANDLE	N1231BHandle,
			       N1231B_INT64		preset1,
			       N1231B_INT64		preset2,
			       N1231B_INT64		preset3,
			       unsigned long	*pStatus);
/*
 *	For the card specified by N1231BHandle, attempts to  
 *	perform the following:
 *
 *	a) Reset all errors on axis 1, 2, and 3 and the Ref axes.
 *	b) Load the Preset Position registers for each axis 
 *     with preset1, preset2, and preset3.
 *	c) Transfer these Preset Position values to the Position registers
 *     (i.e., perform a Postion Preset operation).
 *	d) If pStatus is non-NULL, set *pStatus to show contents of the status 
 *     registers.
 *
 *	The preset values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_AXIS:	An axis still shows a status error.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawPosVel(N1231B_HANDLE	N1231BHandle,
				   N1231B_AXIS		axis,
			   	   N1231B_INT64		*pPosition,
				   long				*pVelocity);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis, attempts to perform the following:
 *
 *	a) Generates a software sample on the specified axis.
 *	b) Reads position and velocity values on the specified axis
 *     into the corresponding parameters (provided parameter is non-NULL).
 *
 *	If data is not valid on the specified axis, the position and 
 *	velocity parameters will be left unchanged.
 *
 *	The position and velocity values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS:	 Data invalid on specified axis.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawPosVelAll(N1231B_HANDLE		N1231BHandle,
			   	      N1231B_INT64		*pPosition1,
				      long				*pVelocity1,
			   	      N1231B_INT64		*pPosition2,
				      long				*pVelocity2,
				      N1231B_INT64		*pPosition3,
				      long				*pVelocity3,
					  unsigned short	*pValid);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Generates a software sample on axes 1, 2, and 3.
 *	b) Reads position and velocity software sample values on 
 *     axis 1, 2, and 3 into the corresponding parameters, if
 *     these parameters are non-NULL.  If a passed parameter is
 *     NULL the value is not written. 
 *
 *  If a position or velocity pointer is NULL, then the corresponding
 *  value is not read from the card.  However, the software sample 
 *  command is still generated.
 *
 *	If data is not valid on an axis, the position and 
 *	velocity parameters for that axis will be left unchanged.
 *
 *	The sample valid bits are returned in *pValid (provided pValid is 
 *  non-NULL).  Therefore, if N1231B_ERR_AXIS is returned, the 
 *  *pValid parameter can be used to determine which axes were invalid.
 *	The constants (for Bitmap L):
 *		N1231B_VALID_1
 *		N1231B_VALID_2
 *		N1231B_VALID_3
 *	can be used to assist in analyzing *pValid.
 *
 *	The position and velocity values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_AXIS:	Data was not valid on at least one axis.
 *                            NOTE: If both the pPosition & pVelocity
 *                            parameters are NULL for an axis, then 
 *                            errors on that axis will not cause 
 *                            N1231B_ERR_AXIS to be reported, but 
 *                            *pValid will still report the error.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXSysSample(N1231B_HANDLE	N1231BHandle,
				       N1231B_AXIS		axis,
					   N1231B_INT64		*pPosition,
			   	       long				*pVelocity);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Reads position and velocity values from the system sample 
 *     register.  If pPosition or pVelocity is NULL, that value is 
 *     not read.
 *
 *  IMPORTANT NOTE: This function reads the value that was taken on the 
 *  last external "system sample" signal.  Therefore, repeated calls to 
 *  this function will return the same value unless a new external 
 *  "system sample" signal is received.  
 *
 *	If data is not valid on the axis, *pPosition and *pVelocity
 *	will be left unchanged.
 *
 *	The values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXSysSampleAll(N1231B_HANDLE		N1231BHandle,
					      N1231B_INT64		*pPosition1,
			   	          long				*pVelocity1,
					      N1231B_INT64		*pPosition2,
			   	          long				*pVelocity2,
					      N1231B_INT64		*pPosition3,
			   	          long				*pVelocity3,
						  unsigned short	*pValid);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads position and velocity values from the system sample 
 *     registers for all axes.  If any of the pPosition or pVelocity 
 *     parameters are NULL, that value is not read.
 *
 *  IMPORTANT NOTE: This function reads the values that were taken on 
 *  the last external "system sample" signal.  Therefore, repeated calls 
 *  to this function will return the same values unless a new external 
 *  "system sample" signal is received.  
 *
 *	If data is not valid on an axis, *pPosition and *pVelocity
 *	for that axis will be left unchanged.
 *
 *  Even if some of the position or velocity parameters are NULL, this
 *  function forces a read of the msb of the axis 1 and 3 registers to 
 *  prevent sample overrun errors.  Therefore, this function should not
 *  be used if it is intended to make other reads of individual axis, as
 *  unreported sample overrun conditions could occur.
 *
 *	The values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXSysSampleAllArray(N1231B_HANDLE	N1231BHandle,
							   N1231B_SAMPLES	*pSamples);
/*
 *	For the card specified by N1231BHandle:
 *
 *  This function provides a means of reading and storing data with 
 *  a minimum of processing overhead.  It is intended that the calling 
 *  function will later perform validity checking on the data.
 *
 *  Parameter *pSamples (of type N1231B_SAMPLES) is a structure of 
 *  pointers to arrays for storing position and velocity data.  The first 
 *  element of this structure is an index indicating the position in each 
 *  of these arrays for storing the current data.  It is the 
 *  responsibility of the calling program to increment the index and 
 *  assure that it is in range.
 *
 *  If any of the position or velocity array pointers in struct *pSamples 
 *  are NULL, then that data is not stored.
 *
 *  Even if some of the position or velocity array pointers are NULL, 
 *  this function forces a read of the msb of the axis 1 and 3 registers 
 *  to prevent sample overrun errors.  Therefore, this function should 
 *  not be used if it is intended to make other reads of individual axis, 
 *  as unreported sample overrun conditions could occur.

 *  The *pPosMsb array holds the most significant 4 bits of each 36-bit 
 *  position value, packed into a single 16-bit word.  The high order 
 *  4 bits of this word hold the data valid bits for the words.
 *
 *  The data valid bits are not checked by this function.  Data is read
 *  and stored regardless of whether it is valid.  It is the 
 *  responsibility of the calling routine to verify validity.
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXAxisSample(N1231B_HANDLE	N1231BHandle,
				        N1231B_AXIS		axis,
					    N1231B_INT64	*pPosition,
			   	        long			*pVelocity);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Reads position and velocity values from the axis sample 
 *     register.  If pPosition or pVelocity is NULL, that value is 
 *     not read.
 *
 *  IMPORTANT NOTE: This function reads the value that was taken on the 
 *  last external "axis sample" signal.  Therefore, repeated calls to 
 *  this function will return the same value unless a new external 
 *  "axis sample" signal is received.  
 *
 *	If data is not valid on the axis, *pPosition and *pVelocity
 *	will be left unchanged.
 *
 *	The values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXAxisSampleAll(N1231B_HANDLE	N1231BHandle,
					       N1231B_INT64		*pPosition1,
			   	           long				*pVelocity1,
					       N1231B_INT64		*pPosition2,
			   	           long				*pVelocity2,
					       N1231B_INT64		*pPosition3,
			   	           long				*pVelocity3,
						   unsigned short	*pValid);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads position and velocity values from the axis sample 
 *     registers for all axes.  If any of the pPosition or pVelocity 
 *     parameters are NULL, that value is not read.
 *
 *  IMPORTANT NOTE: This function reads the values that were taken on 
 *  the last external "axis sample" signal.  Therefore, repeated calls 
 *  to this function will return the same values unless a new external 
 *  "axis sample" signal is received.  
 *
 *	If data is not valid on an axis, *pPosition and *pVelocity
 *	for that axis will be left unchanged.
 *
 *	The values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXAxisSampleAllArray(N1231B_HANDLE	N1231BHandle,
								N1231B_SAMPLES	*pSamples);
/*
 *	For the card specified by N1231BHandle:
 *
 *  This function provides a means of reading and storing data with 
 *  a minimum of processing overhead.  It is intended that the calling 
 *  function will later perform validity checking on the data.
 *
 *  Parameter *pSamples (of type N1231B_SAMPLES) is a structure of 
 *  pointers to arrays for storing position and velocity data.  The first 
 *  element of this structure is an index indicating the position in each 
 *  of these arrays for storing the current data.  It is the
 *  responsibility of the calling program to increment the index and 
 *  assure that it is in range.
 *
 *  If any of the position or velocity array pointers in struct *pSamples 
 *  are NULL, then that data is not stored.
 *
 *  The *pPosMsb array holds the most significant 4 bits of each 36-bit 
 *  position value, packed into a single 16-bit word.  The high order 
 *  4 bits of this word hold the data valid bits for the words.
 *
 *  The data valid bits are not checked by this function.  Data is read
 *  and stored regardless of whether it is valid.  It is the 
 *  responsibility of the calling routine to verify validity.
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXSampleAll(N1231B_HANDLE	N1231BHandle,
					   N1231B_INT64		*pAxsPosition1,
			   	       long				*pAxsVelocity1,
					   N1231B_INT64		*pAxsPosition2,
			   	       long				*pAxsVelocity2,
					   N1231B_INT64		*pAxsPosition3,
			   	       long				*pAxsVelocity3,
					   N1231B_INT64		*pSysPosition1,
			   	       long				*pSysVelocity1,
					   N1231B_INT64		*pSysPosition2,
			   	       long				*pSysVelocity2,
					   N1231B_INT64		*pSysPosition3,
			   	       long				*pSysVelocity3,
					   unsigned short	*pAxsValid,
					   unsigned short	*pSysValid);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads position and velocity values from the system sample and 
 *     axis sample registers for all axes.  If any of the position 
 *     or velocity parameters are NULL, that value is not read.
 *
 *  IMPORTANT NOTE: This function reads the values that were taken on 
 *  the last external "system sample" and "axis sample" signals.  
 *  Therefore, repeated calls to this function will return the same 
 *  values unless new sample signals are received.  
 *
 *	If data is not valid on an axis, the *position and *velocity 
 *  parameters for that axis will be left unchanged.
 *
 *  Even if some of the position or velocity parameters are NULL, this
 *  function forces a read of the msb of the axis 1 and 3 system sample
 *  registers to prevent system sample overrun errors.  Therefore, this 
 *  function should not be used if it is intended to make other reads of 
 *  the system sample registers for individual axis, as unreported 
 *  system sample overrun conditions could occur.
 *
 *	The values are in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetRawXSampleAllArray(N1231B_HANDLE	N1231BHandle,
							N1231B_SAMPLES	*pSysSamples,
							N1231B_SAMPLES  *pAxsSamples);
/*
 *	For the card specified by N1231BHandle:
 *
 *  This function provides a means of reading and storing data with 
 *  a minimum of processing overhead.  It is intended that the calling 
 *  function will later perform validity checking on the data.
 *
 *  Parameter *pSysSamples and *pAxsSamples (of type N1231B_SAMPLES) are 
 *  structures of pointers to arrays for storing position and velocity data.  
 *  The first element of each structure is an index indicating the position 
 *  in each of these arrays for storing the current data.  Parameter
 *  *pSysSamples is used for "system sample" data, and *pAxsSamples is for 
 *  "axis sample" data.  It is the responsibility of the calling program 
 *  to increment the index and assure that it is in range.
 *
 *  If any of the position or velocity array pointers in struct 
 *  *pSysSamples or *pAxsSamples is NULL, then that data is not stored.
 *
 *  Even if some of the position or velocity array pointers in 
 *  *pSysSamples are NULL, this function forces a read of the msb of the 
 *  axis 1 and 3 registers to prevent sample overrun errors.  Therefore, 
 *  this function should not be used if it is intended to make other reads 
 *  of individual axis, as unreported sample overrun conditions could occur.
 *
 *  The *pPosMsb arrays holds the most significant 4 bits of each 36-bit 
 *  position value, packed into a single 16-bit word.  The high order 
 *  4 bits of these words hold the data valid bits for the words.
 *
 *  The data valid bits are not checked by this function.  Data is read
 *  and stored regardless of whether it is valid.  It is the 
 *  responsibility of the calling routine to verify validity.
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BClearStatusBits(N1231B_HANDLE		N1231BHandle,
				      unsigned long		resetBits,
					  unsigned long		*pStatus);
/*
 *	For the card specified by N1231BHandle:
 *   
 *	a) Attempts to clear specific bits (resetBits) in status registers
 *  b) Sets *pStatus to the new values of the status registers (unless
 *     pStatus is NULL).
 *
 *	NOTE: Although two separate hardware registers are used for status,
 *	      this function concatenates them into a single *pStatus register.
 *
 *	The following constants can be used to clear and 
 *  interpret the bits in *pStatus:
 *
 *		N1231B_NO_SIG_1	
 *		N1231B_GLITCH_1	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_1 (see note below)
 *		N1231B_AXIS_SAMPLE_OVERRUN_1  (see note below)
 *		N1231B_LT_ALERT_1
 *		N1231B_GE_ALERT_1
 *
 *		N1231B_NO_SIG_2	
 *		N1231B_GLITCH_2	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_2 (see note below)
 *		N1231B_AXIS_SAMPLE_OVERRUN_2  (see note below)
 *		N1231B_LT_ALERT_2
 *		N1231B_GE_ALERT_2
 *
 *		N1231B_NO_SIG_3	
 *		N1231B_GLITCH_3	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_3 (see note below)
 *		N1231B_AXIS_SAMPLE_OVERRUN_3  (see note below)
 *		N1231B_LT_ALERT_3A
 *		N1231B_GE_ALERT_3A
 *		N1231B_LT_ALERT_3B
 *		N1231B_GE_ALERT_3B
 *
 *		N1231B_NO_SIG_REF
 *		N1231B_GLITCH_REF
 *
 *		N1231B_SYS_SAMPLE_DATA_RDY (see note below)
 *		N1231B_SYS_SAMPLE_OVERRUN  (see note below)
 *
 *  Note: The SAMPLE_DATA_RDY bits are cleared by writing to the .
 *        corresponding SAMPLE_OVERRUN bits.  SAMPLE_DATA_RDY bits 
 *        are not cleared by writng to them directly.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BClearPathErrorAll(N1231B_HANDLE		N1231BHandle,
					    unsigned long		*pStatus);
/*
 *	For the card specified by N1231BHandle:
 *   
 *	a) Attempts to clear the "path error" bits in the status registers.
 *  b) Sets *pStatus to the new values of the status registers (unless
 *     pStatus is NULL).
 *
 *  NOTE: The "path error" bits are the logical OR of the following:
 *			N1231B_NO_SIG_1
 *			N1231B_GLITCH_1
 *			N1231B_NO_SIG_2
 *			N1231B_GLITCH_2
 *			N1231B_NO_SIG_3
 *			N1231B_GLITCH_3
 *			N1231B_NO_SIG_REF
 *			N1231B_GLITCH_REF
 *
 *	NOTE: Although two separate hardware registers are used for status,
 *	      this function concatenates them into a single *pStatus parameter.
 *
 *  See N1231BClearStatusBits(), above, for constants that can be used
 *      to interpret the value returned in *pStatus.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BClearStatusAll(N1231B_HANDLE	N1231BHandle,
					 unsigned long	*pStatus);
/*
 *	For the card specified by N1231BHandle:
 *   
 *	a) Attempts to clear the status registers
 *  b) Sets *pStatus to the show the new values of the status registers
 *     (unless pStatus is NULL).
 *
 *	NOTE: Although two separate hardware registers are used for status,
 *	      this function concatenates them into a single *pStatus register.
 *
 *	The following constants can be used to interpret the 
 *	bits in *pStatus:
 *
 *		N1231B_NO_SIG_1	
 *		N1231B_GLITCH_1	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_1
 *		N1231B_AXIS_SAMPLE_OVERRUN_1
 *		N1231B_LT_ALERT_1
 *		N1231B_GE_ALERT_1
 *
 *		N1231B_NO_SIG_2	
 *		N1231B_GLITCH_2	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_2
 *		N1231B_AXIS_SAMPLE_OVERRUN_2
 *		N1231B_LT_ALERT_2
 *		N1231B_GE_ALERT_2
 *
 *		N1231B_NO_SIG_3	
 *		N1231B_GLITCH_3	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_3
 *		N1231B_AXIS_SAMPLE_OVERRUN_3
 *		N1231B_LT_ALERT_3A
 *		N1231B_GE_ALERT_3A
 *		N1231B_LT_ALERT_3B
 *		N1231B_GE_ALERT_3B
 *
 *		N1231B_NO_SIG_REF
 *		N1231B_GLITCH_REF
 *
 *		N1231B_SYS_SAMPLE_DATA_RDY
 *		N1231B_SYS_SAMPLE_OVERRUN
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetStatus(N1231B_HANDLE	N1231BHandle,
				unsigned long	*pStatus,
				unsigned short	*pDataValid);
/* 
 *	For the card specified by N1231BHandle:
 *   
 *	a) Sets *pStatus to show the contents of the status registers
 *	   (unless pStatus is NULL).
 *  b) Sets *pDataValid to show the contents of the Data Valid register
 *     (unless pDataValid is NULL).
 *
 *	NOTE: Although two separate hardware registers are used for status,
 *	      this function concatenates them into a single *pStatus parameter.
 * 
 *        Also, the two separate registers that are read for data valid are
 *        ORed into a single *pDataValid parameter.
 *
 *	The following constants can be used to interpret the 
 *	bits in *pStatus:
 *
 *		N1231B_NO_SIG_1	
 *		N1231B_GLITCH_1	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_1
 *		N1231B_AXIS_SAMPLE_OVERRUN_1
 *		N1231B_LT_ALERT_1
 *		N1231B_GE_ALERT_1
 *
 *		N1231B_NO_SIG_2	
 *		N1231B_GLITCH_2	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_2
 *		N1231B_AXIS_SAMPLE_OVERRUN_2
 *		N1231B_LT_ALERT_2
 *		N1231B_GE_ALERT_2
 *
 *		N1231B_NO_SIG_3	
 *		N1231B_GLITCH_3	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_3
 *		N1231B_AXIS_SAMPLE_OVERRUN_3
 *		N1231B_LT_ALERT_3A
 *		N1231B_GE_ALERT_3A
 *		N1231B_LT_ALERT_3B
 *		N1231B_GE_ALERT_3B
 *
 *		N1231B_NO_SIG_REF
 *		N1231B_GLITCH_REF
 *
 *		N1231B_SYS_SAMPLE_DATA_RDY
 *		N1231B_SYS_SAMPLE_OVERRUN
 *
 *	The following constants can be used to interpret the 
 *	bits in *pDataValid:
 *
 *		N1231B_ERR_1				
 *		N1231B_SW_SAMPLE_VALID_1	
 *		N1231B_AXIS_SAMPLE_VALID_1	
 *		N1231B_SYS_SAMPLE_VALID_1
 *
 *		N1231B_ERR_2				
 *		N1231B_SW_SAMPLE_VALID_2	
 *		N1231B_AXIS_SAMPLE_VALID_2	
 *		N1231B_SYS_SAMPLE_VALID_2
 *
 *		N1231B_ERR_3				
 *		N1231B_SW_SAMPLE_VALID_3	
 *		N1231B_AXIS_SAMPLE_VALID_3	
 *		N1231B_SYS_SAMPLE_VALID_3	
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetInterruptMask(N1231B_HANDLE	N1231BHandle,
					   unsigned long	intrMask);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets the interrupt mask registers.
 *
 *	NOTE: Although two separate hardware registers are used for the 
 *        interrupt mask, this function concatenates them into a 
 *        single *intrMask parameter.
 *
 *  The following constants can be used for IntrMask:
 *		N1231B_NO_SIG_1	
 *		N1231B_GLITCH_1	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_1
 *		N1231B_AXIS_SAMPLE_OVERRUN_1
 *		N1231B_LT_ALERT_1
 *		N1231B_GE_ALERT_1
 *
 *		N1231B_NO_SIG_2	
 *		N1231B_GLITCH_2	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_2
 *		N1231B_AXIS_SAMPLE_OVERRUN_2
 *		N1231B_LT_ALERT_2
 *		N1231B_GE_ALERT_2
 *
 *		N1231B_NO_SIG_3	
 *		N1231B_GLITCH_3	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_3
 *		N1231B_AXIS_SAMPLE_OVERRUN_3
 *		N1231B_LT_ALERT_3A
 *		N1231B_GE_ALERT_3A
 *		N1231B_LT_ALERT_3B
 *		N1231B_GE_ALERT_3B
 *
 *		N1231B_NO_SIG_REF
 *		N1231B_GLITCH_REF
 *
 *		N1231B_SYS_SAMPLE_DATA_RDY
 *		N1231B_SYS_SAMPLE_OVERRUN
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetInterruptMask(N1231B_HANDLE	N1231BHandle,
					   unsigned long	*pIntrMask);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets *pIntrMask to show contents of the 
 *     interrupt mask registers.
 *
 *	NOTE: Although two separate hardware registers are used for the 
 *        interrupt mask, this function concatenates them into a 
 *        single *intrMask parameter.
 *
 *	The following constants cam be used to interpret bits in *pIntrMask:
 *		N1231B_NO_SIG_1	
 *		N1231B_GLITCH_1	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_1
 *		N1231B_AXIS_SAMPLE_OVERRUN_1
 *		N1231B_LT_ALERT_1
 *		N1231B_GE_ALERT_1
 *
 *		N1231B_NO_SIG_2	
 *		N1231B_GLITCH_2	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_2
 *		N1231B_AXIS_SAMPLE_OVERRUN_2
 *		N1231B_LT_ALERT_2
 *		N1231B_GE_ALERT_2
 *
 *		N1231B_NO_SIG_3	
 *		N1231B_GLITCH_3	
 *		N1231B_AXIS_SAMPLE_DATA_RDY_3
 *		N1231B_AXIS_SAMPLE_OVERRUN_3
 *		N1231B_LT_ALERT_3A
 *		N1231B_GE_ALERT_3A
 *		N1231B_LT_ALERT_3B
 *		N1231B_GE_ALERT_3B
 *
 *		N1231B_NO_SIG_REF
 *		N1231B_GLITCH_REF
 *
 *		N1231B_SYS_SAMPLE_DATA_RDY
 *		N1231B_SYS_SAMPLE_OVERRUN
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetConfig(N1231B_HANDLE	N1231BHandle,
				unsigned long	config);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets the configuration registers.
 *
 *	NOTE: Although two separate hardware registers are used for config,
 *	      this function concatenates them into a single config register.
 *
 *	The following constants can be used for config: 
 *		N1231B_DIRECTION_MINUS_1
 *		N1231B_DIRECTION_MINUS_2
 *		N1231B_DIRECTION_MINUS_3
 *
 *		N1231B_LT_OUT_POS_TRUE_1
 *		N1231B_LT_OUT_POS_TRUE_2
 *		N1231B_LT_OUT_POS_TRUE_3A
 *		N1231B_LT_OUT_POS_TRUE_3B
 *
 *		N1231B_GE_OUT_POS_TRUE_1
 *		N1231B_GE_OUT_POS_TRUE_2
 *		N1231B_GE_OUT_POS_TRUE_3A
 *		N1231B_GE_OUT_POS_TRUE_3B
 *
 *		N1231B_THRESH_OUT_LVTTL_1
 *		N1231B_THRESH_OUT_LVTTL_2
 *		N1231B_THRESH_OUT_LVTTL_3A
 *		N1231B_THRESH_OUT_LVTTL_3B
 *
 *		N1231B_BASE_ADDR_0
 *		N1231B_BASE_ADDR_1
 *		N1231B_BASE_ADDR_2
 *		N1231B_BASE_ADDR_3
 *
 *		N1231B_BUS_MODE_DIRECT
 *      N1231B_A3_TIME_ADJUST
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetConfig(N1231B_HANDLE	N1231BHandle,
				unsigned long	*pConfig);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets *pConfig to show contents of the 
 *     configuration registers.
 *
 *	NOTE: Although two separate hardware registers are used for config,
 *	      this function concatenates them into a single *pConfig register.
 *
 *	The same constants shown under N1231BSetConfig()
 *	can be used to interpret the bits in *pConfig.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetGeLtDirections(N1231B_HANDLE	N1231BHandle,
				        unsigned long	alertDirections);
/* 
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets the Alert Direction registers.
 *
 *	NOTE: Although two separate hardware registers are used for Alert
 *        Direction, this function concatenates them into a single 
 *        alertDirections register.
 *
 *	The following constants can be used for alertDirections: 
 *      N1231B_LT_ALERT_WHEN_GOES_FALSE_1
 *      N1231B_GE_ALERT_WHEN_GOES_FALSE_1
 *
 *      N1231B_LT_ALERT_WHEN_GOES_FALSE_2
 *      N1231B_GE_ALERT_WHEN_GOES_FALSE_2
 *
 *      N1231B_LT_ALERT_WHEN_GOES_FALSE_3A
 *      N1231B_GE_ALERT_WHEN_GOES_FALSE_3A
 *      N1231B_LT_ALERT_WHEN_GOES_FALSE_3B
 *      N1231B_GE_ALERT_WHEN_GOES_FALSE_3B
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetGeLtDirections(N1231B_HANDLE	N1231BHandle,
				        unsigned long	*pAlertDirections);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets *pAlertDirections to show contents of the 
 *     Alert Direction registers.
 *
 *	NOTE: Although two separate hardware registers are used for Alert
 *        Direction, this function concatenates them into a single 
 *        *pAlertDirections register.
 *
 *	The same constants shown under N1231BSetGeLtDirections()
 *	can be used to interpret the bits in *pAlertDirections.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetGeLtThresholds(N1231B_HANDLE	N1231BHandle,
					    N1231B_AXIS		axis,
						N1231B_INT64	geValue,
						N1231B_INT64	ltValue);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis, attempts to perform the following:
 *
 *	a) Load the Greater Than or Equal Threshold Register with geValue.
 *  b) Load the Less Than Threshold register with ltValue,
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 */

/************************************************************************/
N1231B_RETURN
N1231BGetGeLtThresholds(N1231B_HANDLE	N1231BHandle,
					    N1231B_AXIS		axis,
					    N1231B_INT64	*pGeValue,
						N1231B_INT64	*pLtValue);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Sets *pGeValue to the contents of the Greater Than or Equal 
 *     Threshold Register.
 *	a) Sets *pLtValue to the contents of the Less Than Threshold Register.
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 */

/************************************************************************/
N1231B_RETURN
N1231BGetGeLtStatus(N1231B_HANDLE	N1231BHandle,
				    unsigned long	*pGeLtStatus);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets *pGeLtStatus to show contents of the 
 *     Comparator Status registers (which shows the "real-time" state
 *     of the comparators).
 *
 *	NOTE: Although two separate hardware registers are used for 
 *        Comparator Status, this function concatenates them into a 
 *        single *pGeLtStatus register.
 *
 *	The following constants can be used to interpret the bits 
 *  in *pGeLtStatus: 
 *		N1231B_LT_TRUE_1
 *		N1231B_GE_TRUE_1
 *
 *		N1231B_LT_TRUE_2
 *		N1231B_GE_TRUE_2
 *
 *		N1231B_LT_TRUE_3A
 *		N1231B_GE_TRUE_3A
 *		N1231B_LT_TRUE_3B
 *		N1231B_GE_TRUE_3B
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetPDClockControl(N1231B_HANDLE	N1231BHandle,
						N1231B_PDCLOCK	pdClock,
						unsigned short	clkControl,
						unsigned short	clkDivider);
/*
 *	For the card specified by N1231BHandle and the Programmable Data Clock
 *  specified by pdClock, attempts to perform the following:
 *
 *	a) Sets the clock control to clkControl.
 *  b) Sets the clock divider to clkDivider.
 *
 *  The low-order bite of clkControl, bits 7:0, specifies the width of the 
 *  clock pulse.  The following constants can be ORed into this word to 
 *  specify the clock behavior.
 *		N1231B_PDCLK_ON
 *		N1231B_PDCLK_20MHZ
 *		N1231B_PDCLK_POLARITY_HIGH
 *      N1231B_PDCLK_SEL20KHZCLK    (valid only for PDCLK_1)
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetPDClockControl(N1231B_HANDLE	N1231BHandle,
					    N1231B_PDCLOCK	pdClock,
						unsigned short	*pClkControl,
						unsigned short	*pClkDivider);
/*
 *	For the card specified by N1231BHandle and the Programmable Data Clock
 *  specified by pdClock, retrieves the following information:
 *
 *	a) *pClkControl is set to the value in the clock control register.
 *  b) *pClkDivider is set to the value in the clock divider register.
 *
 *  See the description of N1231BSetPDClockControl() for constants that 
 *  can be used to interpret *pClkControl.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetFilter(N1231B_HANDLE	N1231BHandle,
				unsigned short	filter);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets the filter register.
 *
 *	The following constants can be used for filter:
 *
 *		N1231B_FILTER_ENB
 *
 *		N1231B_KP0
 *		N1231B_KP1
 *		N1231B_KP2
 *		N1231B_KP3
 *
 *		N1231B_KV0
 *		N1231B_KV1
 *		N1231B_KV2
 *		N1231B_KV3
 *
 *      N1231B_XCLD_A1	- new in FPGA rev '0003
 *      N1231B_XCLD_A2	- new in FPGA rev '0003
 *      N1231B_XCLD_A3	- new in FPGA rev '0003
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetFilter(N1231B_HANDLE	N1231BHandle,
				unsigned short	*pFilter);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets *pFilter to show contents of the filter register.
 *
 *	The same constants shown under N1231BSetFilter()
 *	can be used to interpret the bits in the word.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSetHdwIoSetup(N1231B_HANDLE	N1231BHandle,
				unsigned short	HdwIoSetup);
/*
 *		NEW in FPGA rev '0003
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets the Hardware IO Setup register.
 *
 *	The following constants can be used for HdwIoSetup:
 *
 *      N1231B_HWIO_DISA1H
 *      N1231B_HWIO_DISA2H
 *      N1231B_HWIO_DISA3H
 *      N1231B_HWIO_DISSYSH
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetHdwIoSetup(N1231B_HANDLE	N1231BHandle,
				unsigned short	*pHdwIoSetup);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets *pHdwIoSetup to show contents of the Hardware IO Setup register.
 *
 *	The same constants shown under N1231BGetHdwIoSetup()
 *	can be used to interpret the bits in the word.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BSyncPDClks(N1231B_HANDLE	N1231BHandle);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets N1231B_CLK_SYNC bit in the command (N1231B_OFST_SAMPLE_PRESET) register.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *      N1231B_ERR_PARAM:   A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetFPGARevs(N1231B_HANDLE	N1231BHandle,
				  unsigned long	*pFPGA1Rev,
				  unsigned long	*pFPGA2Rev);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Sets *pFPGA1Rev and *pFPGA2Rev to show the
 *	   revision codes of the two FPGAs.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetFPGAIds(N1231B_HANDLE	N1231BHandle,
				 unsigned long	*pFPGA1Id,
				 unsigned long	*pFPGA2Id);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Sets *pFPGA1Id and *pFPGA2Id to show the 
 *	   ID codes of the two FPGAs.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetHdwRev(N1231B_HANDLE	N1231BHandle,
				unsigned short	*pHdwRev);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads the Hardware Revision code.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
unsigned int
N1231BGetLibraryRev(void);
/*
 *  Returns the library revision number.
 */

/************************************************************************/
char*
N1231BGetErrStr(N1231B_RETURN	err);
/*
 *	Returns a string describing the error conditions 
 *	related to error parameter "err".
 */

/************************************************************************/
/*
 * =============================================================================
 * Polling Data Collection Functions
 * =============================================================================
 *
 *	All of these routines limit themselves to run only on the specified
 *	processor. They should only be run on a multi-processor system! For the
 *	highest data rates, the user should prevent all other running tasks from
 *	running on the specified core (this can be done manually from the Processes
 *	Tab in Windows Task Manager - see "Set Affinity..." in the right click
 *	context manu).
 *
 */

/**********************************************************
 * N1231BpollRead1AxisPos32()
 *
 *	This routine implements a tight polling loop that tests the Axis Sample
 *	Ready bit for the specified axis, and reads and saves the 32 LSBs of each
 *	position value along with the overrun status into the passed array. However,
 *	the last saved value contains the full 36-bit position word and final valid
 *	status so one can re-create the full position value for all samples provided
 *	the stage speed is less than 2^31 * Resolution / Sample Period. Resolution
 *	will be Lambda/1024/Fold, with Fold = {2 (linear optics), 4 (plane mirror
 *	optics), 8 (high resolution optics)}. Note that generally this condition
 *	will be true for sample rates over ~6 Hz when using plane mirror optics.
 *	The user must post process the data to determine if (and when) any data
 *	overrun errors occured during data collection.
 *
 *	The routine saves the raw position and status data in pPosSamples array.
 *	The ->n31i64.lsb values hold the 32 LSBs of each position sample. Most of
 *	the ->s[2] values are unchanged, only the final value holds the word
 *	containing the final MSBs and valid status for the specified axis.
 *	The ->s[3] values hold the status word containing the overrun error
 *	status for the specified axis. The user must post process the LSB data to
 *	detect wrap-around and re-create the desired number of upper bits. Note that
 *	any overrun errors will indicate a gap in the data between the current
 *	sample and the next sample, and although there is no information about how
 *	long the gap is, it is reasonable to assume that the stage did not move far
 *	enough to cause the 32-bit value to wrap around, so it still should be
 *	possible to fully re-create the upper bits when there are overrrun errors.
 *
 *	Note that this routine ignores the pSmplInfo->ulTimeoutLoopCount value and
 *	does NOT do any timeout testing.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Axis                    Either AXIS_1, or AXIS_2, or AXIS_3
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosSamples             Pointer to array of MULTI_ACCESS structures to hold the sample data
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpollRead1AxisPos32(N1231B_HANDLE		N1231BHandle,
					 N1231B_AXIS		Axis,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 MULTI_ACCESS *		pPosSamples);

/**********************************************************
 * N1231BpollReadSysPos32()
 *
 *	This routine implements a tight polling loop that tests the System Sample
 *	Ready bit, and reads and saves the position (32 LSBs only) for each axis
 *	along with the overrun status into the passed array. However, the last
 *	saved values contain the full 36-bit position words and final valid
 *	status so one can re-create the full position value for all samples provided
 *	the stage speed is less than 2^31 * Resolution / Sample Period. Resolution
 *	will be Lambda/1024/Fold, with Fold = {2 (linear optics), 4 (plane mirror
 *	optics), 8 (high resolution optics)}. Note that generally this condition
 *	will be true for sample rates over ~6 Hz when using plane mirror optics.
 *	The user must post process the data to determine if (and when) any data
 *	overrun errors occured during data collection.
 *
 *	The routine saves the raw position and status data in pPosSamples array.
 *	The ->*lsb values hold the 32 LSBs of each position sample. Most of the
 *	->sAx123msbValid values are unchanged, only the final value holds the word
 *	containing the final MSBs and valid status for all axes. The .ts values are
 *	not changed. The .sSysOverrunErr values hold the status word containing the
 *	overrun error status. The user must post process the LSB data to detect
 *	wrap-around and re-create the desired number of upper bits for each axis.
 *	Note that any overrun errors will indicate a gap in the data between the
 *	current sample and the next sample, and although there is no information
 *	about how long the gap is, it is reasonable to assume that the stage did not
 *	move far enough to cause the 32-bit value to wrap around, so it still should
 *	be possible to fully re-create the upper bits when there are overrrun errors.
 *
 *	Note that this routine ignores the pSmplInfo->ulTimeoutLoopCount value and
 *	does NOT do any timeout testing.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Axis                    Either AXIS_1, or AXIS_2, or AXIS_3
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosSamples             Pointer to array of N1231B_HDR_SYSPOS structures to hold the sample data
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpollReadSysPos32(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_SYSPOS *	pPosSamples);

/**********************************************************
 * N1231BpollRead1AxisPosVel()
 *
 *	This routine implements a tight polling loop that tests the Axis Sample
 *	Ready bit for the specified axis, and reads and saves both position and
 *	velocity data along with the status value to the passed array. The user
 *	must post process the data to determine if the data is valid, and if any
 *	data overrun errors occured during the data collection process.
 *
 *	The routine saves the raw position and status data in pPosSamples array.
 *	The ->s[3] values hold the status words containing the overrun error
 *	status for the specified axis. The ->s[2] values hold the words containing
 *	the MSBs for the specified axis. The user must decode these values during
 *	post processing to determine the validity of the position information and
 *	if any data samples were missed. Note that when the status bits indicate
 *	an overrun error occurred, then the gap in the data is between the current
 *	sample and the next sample.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Axis                    Either AXIS_1, or AXIS_2, or AXIS_3
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosSamples             Pointer to array of MULTI_ACCESS structures to hold the position sample data
 *      pVelSamples             Pointer to array of long values to hold the velocity sample data (may be NULL)
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpollRead1AxisPosVel(N1231B_HANDLE		N1231BHandle,
					 N1231B_AXIS		Axis,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 MULTI_ACCESS *		pPosSamples,
					 long *				pVelSamples);

/**********************************************************
 * N1231BpollRead3AxisPosVel()
 *
 *	This routine implements a tight polling loop that tests all of the Axis
 *	Sample Ready bits, and reads and saves both position and velocity data
 *	along with the status value to the passed arrays. The user must post
 *	process the data to determine if the data is valid, and if any data
 *	overrun errors occured during the data collection process.
 *
 *	The routine saves the raw position and status data in pAx*PosSamples arrays.
 *	The ->s[3] values hold the status words containing the overrun error
 *	status for the corresponding axis. The ->s[2] values hold the words
 *	containing the MSBs for the axis. The user must decode these values during
 *	post processing to determine the validity of the position information and
 *	if any data samples were missed. Note that when the status bits indicate
 *	an overrun error occurred, then the gap in the data is between the current
 *	sample and the next sample.
 *
 *	Notes
 *		1) any of the pAx*Info pointers (but not all) can be NULL to not collect
 *			any data for that axis, in which case the corresponding pAx*Samples
 *			pointers will be ignored and can also be NULL.
 *		2) each axis can have a different data rate and number of samples.
 *		3) any of the pAx*VelSamples pointers can be set to NULL to not collect
 *			Vel data for that axis.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pAx1Info				Pointer to SMPL_INFO structure for Axis1 - see note 1
 *      pAx2Info				Pointer to SMPL_INFO structure for Axis2 - see note 1
 *      pAx3Info				Pointer to SMPL_INFO structure for Axis3 - see note 1
 *      pAx1PosSamples          Pointer to array of MULTI_ACCESS structures to hold the Axis1 position sample data
 *      pAx2PosSamples          Pointer to array of MULTI_ACCESS structures to hold the Axis2 position sample data
 *      pAx3PosSamples          Pointer to array of MULTI_ACCESS structures to hold the Axis3 position sample data
 *      pAx1VelSamples          Pointer to array of long values to hold the Axis1 velocity sample data - can be NULL
 *      pAx2VelSamples          Pointer to array of long values to hold the Axis2 velocity sample data - can be NULL
 *      pAx3VelSamples          Pointer to array of long values to hold the Axis3 velocity sample data - can be NULL
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL, or AxisB == AxisA.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpollRead3AxisPosVel(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pAx1Info,
					 SMPL_INFO *		pAx2Info,
					 SMPL_INFO *		pAx3Info,
					 MULTI_ACCESS *		pAx1PosSamples,
					 MULTI_ACCESS *		pAx2PosSamples,
					 MULTI_ACCESS *		pAx3PosSamples,
					 long *				pAx1VelSamples,
					 long *				pAx2VelSamples,
					 long *				pAx3VelSamples);

/**********************************************************
 * N1231BpollReadSysPosVel()
 *
 *	This routine implements a tight polling loop that tests the System Sample
 *	Ready bit, and reads and saves both the position and velocity values along
 *	with the status values for all axes to the passed array. The user must post
 *	process the data to determine if the data is valid, and if any data
 *	overrun errors occured during the data collection process.
 *
 *	The routine saves the raw position, velocity, and status data in the
 *	pPosVelSamples array. The ->ts values are not changed. The user must decode
 *	the ->sAx123msbValid and ->sSysOverrunErr values during post processing to
 *	determine the validity of the position information and if any data samples
 *	were missed. Note that when the status bits indicate an overrun error
 *	occurred, then the gap in the data is between the current sample and
 *	the next sample.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pInfo					Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosVelSamples          Pointer to array of N1231B_HDR_SYSPOSVEL structures to hold the sample data
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL, or AxisB == AxisA.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpollReadSysPosVel(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_SYSPOSVEL *	pPosVelSamples);

/************************************************************************/

/*
 * =============================================================================
 * Polling with TimeStamp Data Collection Functions
 * =============================================================================
 *
 *	All of these routines limit themselves to run only on the specified
 *	processor. They should only be run on a multi-processor system! For the
 *	highest data rates, the user should prevent all other running tasks from
 *	running on the specified core (this can be done manually from the Processes
 *	Tab in Windows Task Manager - see "Set Affinity..." in the right click
 *	context manu).
 *
 */

/************************************************************************/

/**********************************************************
 * N1231BpolltsRead1AxisPos32()
 *
 *	This routine implements a tight polling loop that tests the Axis Sample
 *	Ready bit for the specified axis, and reads and saves the position's 32 LSBs
 *	and a status value, along with a time stamp value, into the passed array.
 *	The user must post process the data to determine if the data is valid, and
 *	if any data overrun errors occured during the data collection process.
 *
 *	The routine saves the raw time stamp, 32 LSBs of position, and status
 *	data in the pPosSamples array. The ->umaPos.s[3] values hold the status
 *	words containing the overrun error status for the specified axis. The
 *	->umaPos.n31i64.lsb values hold the 32 LSBs of each position sample. The
 *	->umaPos.s[2] values are mostly unchanged except the final one which
 *	holds the final MSBs for the specified axis. The user must post process
 *	the LSB data to re-create the MSB data from the final value, which also
 *	conatains a sample valid status bit. The ->umaPos.s[3] and ->ts values
 *	can be used to determine if any and how many data points were missed. Note
 *	that when the status bits and time stamp values indicate an overrun error
 *	occurred, the actual gap in the data is between the current sample and
 *	the next sample, not between the last sample and the current sample.
 *
 *	Note that this routine ignores the pSmplInfo->ulTimeoutLoopCount value and
 *	does NOT do any timeout testing.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Axis                    Either AXIS_1, or AXIS_2, or AXIS_3
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosSamples             Pointer to array of N1231B_HDR_1POS structures to hold the sample data
 *		pTimeStampFreq			Pointer to variable to receive the frequency for the Time Stamp counter
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpolltsRead1AxisPos32(N1231B_HANDLE		N1231BHandle,
					 N1231B_AXIS		Axis,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_1POS *	pPosSamples,
					 LARGE_INTEGER *	pTimeStampFreq);

/**********************************************************
 * N1231BpolltsReadSysPos32()
 *
 *	This routine implements a tight polling loop that tests the System Sample
 *	Ready bit, and reads and saves the position (32 LSBs only), status, and
 *	timestamp values to the passed array. The user must post process the data
 *	to determine if the data is valid, and if any data overrun errors occured
 *	during the data collection process.
 *
 *	The routine saves the raw time stamp, position, and status data in
 *	pPosSamples array. The ->*lsb values hold the 32 LSBs of each position
 *	sample. Most of the ->sAx123msbValid values are unchanged, only the final
 *	value holds the word containing the final MSBs and valid status for all
 *	axes. The .sSysOverrunErr values hold the status word containing the
 *	overrun error status. The user must post process the LSB data to detect
 *	wrap-around and re-create the desired number of upper bits for each axis.
 *	Note that any overrun errors will indicate a gap in the data between the
 *	current sample and the next sample, and although the ->ts values can be used
 *	to calculate how long the gap is, it is reasonable to assume that the stage
 *	did not move far enough to cause the 32-bit value to wrap around, so it
 *	still should be possible to fully re-create the upper bits when there are
 *	overrrun errors.
 *
 *	Note that this routine ignores the pSmplInfo->ulTimeoutLoopCount value and
 *	does NOT do any timeout testing.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosSamples             Pointer to array of N1231B_HDR_SYSPOS structures to hold all sample data
 *		pTimeStampFreq			Pointer to variable to receive the frequency for the Time Stamp counter
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpolltsReadSysPos32(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_SYSPOS *	pPosSamples,
					 LARGE_INTEGER *	pTimeStampFreq);

/**********************************************************
 * N1231BpolltsRead1AxisPosVel()
 *
 *	This routine implements a tight polling loop that tests the Axis Sample
 *	Ready bit for the specified axis, and reads and saves both position and
 *	velocity data along with the status value and a time stamp value, to the
 *	passed array. The user must post process the data to determine if the data
 *	is valid, and if any data overrun errors occured during the data collection
 *	process.
 *
 *	The routine saves the raw time stamp, position, velocity, and status data
 *	in the pPosVelSamples array. The ->umaPos.s[3] value holds the status
 *	word containing the overrun error status for the specified axis. The
 *	->umaPos.s[2] values hold the words containing the MSBs for the specified
 *	axis. The user must decode these values during post processing to determine
 *	the validity of the position information and if any data samples were
 *	missed. The ->ts values can be used to determine how many data points
 *	were missed. Note that when the status bits and time stamp values indicate
 *	an overrun error occurred, the actual gap in the data is between the
 *	current sample and the next sample, not between the last sample and the
 *	current sample.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Axis                    Either AXIS_1, or AXIS_2, or AXIS_3
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosVelSamples          Pointer to array of N1231B_HDR_1POSVEL structures to hold the Pos & Vel sample data
 *		pTimeStampFreq			Pointer to variable to receive the frequency for the Time Stamp counter
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpolltsRead1AxisPosVel(N1231B_HANDLE		N1231BHandle,
					 N1231B_AXIS		Axis,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_1POSVEL *	pPosVelSamples,
					 LARGE_INTEGER *	pTimeStampFreq);

/**********************************************************
 * N1231BpolltsRead3AxisPosVel()
 *
 *	This routine implements a tight polling loop that tests all of the Axis
 *	Sample Ready bits, and reads and saves both position and velocity data
 *	along with status and timestamp values to the passed arrays. The user must
 *	psot process the data to determine if the data is valid, and if any data
 *	overrun errors occured during the data collection process.
 *
 *	The routine saves the raw time stamp, position, velocity, and status data
 *	in the pPosVelSamples arrays. The ->umaPos.s[3] values hold the status
 *	words containing the overrun error status for the corresponding axis. The
 *	->umaPos.s[2] values hold the words containing the MSBs. The user must
 *	decode these values during post processing to determine the validity of
 *	the position information and if any data samples were missed. The ->ts
 *	values can be used to determine how many data points were missed. Note that
 *	when the status bits and time stamp values indicate an overrun error
 *	occurred, the actual gap in the data is between the current sample and the
 *	next sample, not between the last sample and the current sample.
 *
 *	Notes
 *		1) any of the pAx*Info pointers (but not all) can be NULL to not collect
 *			any data for that axis, in which case the corresponding pAx*PosVelSamples
 *			pointer will be ignored and can also be NULL.
 *		2) each axis can have a different data rate and number of samples.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pAx1Info				Pointer to SMPL_INFO structure for Axis1 - see note 1
 *      pAx2Info				Pointer to SMPL_INFO structure for Axis2 - see note 1
 *      pAx3Info				Pointer to SMPL_INFO structure for Axis3 - see note 1
 *      pAx1PosVelSamples       Pointer to array of N1231B_HDR_1POSVEL structures to hold the Axis1 sample data
 *      pAx2PosVelSamples       Pointer to array of N1231B_HDR_1POSVEL structures to hold the Axis2 sample data
 *      pAx3PosVelSamples       Pointer to array of N1231B_HDR_1POSVEL structures to hold the Axis3 sample data
 *		pTimeStampFreq			Pointer to variable to receive the frequency for the Time Stamp counter
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL, or AxisB == AxisA.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpolltsRead3AxisPosVel(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pAx1Info,
					 SMPL_INFO *		pAx2Info,
					 SMPL_INFO *		pAx3Info,
					 N1231B_HDR_1POSVEL *	pAx1PosVelSamples,
					 N1231B_HDR_1POSVEL *	pAx2PosVelSamples,
					 N1231B_HDR_1POSVEL *	pAx3PosVelSamples,
					 LARGE_INTEGER *	pTimeStampFreq);

/**********************************************************
 * N1231BpolltsReadSysPosVel()
 *
 *	This routine implements a tight polling loop that tests the System Sample
 *	Ready bit, and reads and saves both the position and velocity values along
 *	with the status and timestamp values for all axes to the passed array. The
 *	user must post process the data to determine if the data is valid, and if
 *	any data overrun errors occured during the data collection process.
 *
 *	The routine saves the raw time stamp, position, velocity, and status data in
 *	the pPosVelSamples array. The sSysOverrunErr values hold the status words
 *	containing the overrun error status. The sAx123msbValid values hold the
 *	words containing the MSBs. The user must decode these values during post
 *	processing to determine the validity of the position information and if
 *	any data samples were missed. The .ts values can be used to determine how
 *	many data points were missed. Note that when the status bits and time stamp
 *	values indicate an overrun error occurred, the actual gap in the data is
 *	between the current sample and the next sample, not between the last
 *	sample and the current sample.
 *
 *	Parameters:
 *		N1231BHandle			Handle obtained from N1231BOpen()
 *      Processor               Number from 0 to N-1, to specify which core to use
 *      pSmplInfo				Pointer to SMPL_INFO with Requested and Actual # samples and timeout info
 *      pPosVelSamples          Pointer to array of N1231B_HDR_SYSPOSVEL structures to hold the Pos & Vel sample data
 *		pTimeStampFreq			Pointer to variable to receive the frequency for the Time Stamp counter
 *
 *	Return value:
 *		N1231B_SUCCESS:		 	Success.
 *  	N1231B_ERR_HANDLE		Invalid handle passed.
 *  	N1231B_ERR_PARAM		At least one of the parameters is NULL.
 *  	N1231B_WAIT_TIMEOUT		The wait loop executed the maximum # of times.
 *		N1231B_ERR_UNKNOWN2		Invalid Processor Specified.
 *  	N1231B_ERR_UNKNOWN6		an unexpected error occured.
 *
 */
N1231B_RETURN
N1231BpolltsReadSysPosVel(N1231B_HANDLE		N1231BHandle,
					 unsigned short		Processor,
					 SMPL_INFO *		pSmplInfo,
					 N1231B_HDR_SYSPOSVEL *	pPosVelSamples,
					 LARGE_INTEGER *	pTimeStampFreq);

/************************************************************************/

/*
 * ==================================
 * Interrupt Related Functions
 * ==================================
 */

/************************************************************************/
N1231B_RETURN
N1231BSetGlobalInterruptEnable(N1231B_HANDLE	N1231BHandle,
						       unsigned short   enable);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Turns on the Global Interrupt Enable if enable is set to:
 *       N1231B_IRQ_ENB
 *  b) Turns off the Global Interrupt Enable if enable is set to:
 *       N1231B_IRQ_DISABLE
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BGetGlobalInterruptEnable(N1231B_HANDLE	N1231BHandle,
						       unsigned short   *pEnable);
/*
 *	For the card specified by N1231BHandle:
 * 
 *	a) Retrives the Global Interrupt Enable bit into *pEnable.
 *
 *  If the Global Interrupt Enable bit is set, then *pEnable will
 *  be set to N1231B_IRQ_ENB. Otherwise, it will be set to 
 *  N1231B_IRQ_DISABLE (which is 0).
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 */

/************************************************************************/
N1231B_RETURN
N1231BPciInterruptEnable(N1231B_HANDLE	N1231BHandle,
						 int			enable);
/*
 *	For the card specified by N1231BHandle:
 *	
 *	Enables interrupts if parameter enable is non-zero.
 *	Disables interrupts if parameter enable is zero.
 *
 *	NOTE: See also N1231BSetGlobalInterruptEnable()
 *		  and the Interrupt Mask bits.
 *
 *		  The Interrupt Mask bits determine whether 
 *		  individual status bits can generate interrupts.
 *
 *		  The Global Interrupt Enable bit, set or cleared by
 *        N1231BSetGlobalInterruptEnable(), controls whether interrupt 
 *		  conditions can be passed to the PCI interface.  It can be 
 *        used to temporarily inhibit generation of interrupts.
 *
 *		  This function (N1231BPciInterruptEnable) is used 
 *		  to turn on (or off) PCI interrupt handling   
 *		  so that it can respond to the card conditions.
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *      N1231B_ERR_DEVICE:  An internal structure is invalid
 */

/************************************************************************/
/* Following function defined ONLY when running under Microsoft Windows */
/************************************************************************/
N1231B_RETURN
N1231BPciInterruptAttach(N1231B_HANDLE		N1231BHandle,
						 N1231B_EVT_HANDLE	*eventHandle);
/*
 *	For the card specified by N1231BHandle:
 *
 *	Allocates internal resources that signal the
 *	N1231BPciInterruptWait() function when the N1231B card
 *	generates an interrupt. The 'Wait function operates similar
 *	to the Windows' WaitForSingleObject() routine. Note that
 *	the 'Attach function only needs to be called once, and
 *	that a corresponding 'Detach function should be called
 *	prior to closing the board (however, for compatability with
 *	code written for API version 1.2, if the function is called
 *	more than once, it detects that resources are already
 *	allocated and does not allocate more).
 *
 *  Also see the N1231BPciInterruptEnable() function, which
 *	must be called multiple times (each time an interrupt occurs,
 *	the interrupt is disabled).
 *
 *	The *eventHandle parameter helps maintain some backwards
 *	compatability with code written for API version 1.2, and will
 *	be set to the event object used within the API to notify the
 *	N1231BPciInterruptWait() function. However, the API's wait
 *	function should be used instead of a Windows Wait Function.
 *
 *	Return value:
 *		N1231B_SUCCESS:		  Success.
 *		N1231B_ERR_PARAM:	  A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	  N1231BHandle invalid.
 *      N1231B_ERR_DEVICE:    An internal structure is invalid
 *		N1231B_ERR_MAX_EVENTS Maximum number of events exceeded.
 */

/************************************************************************/
/* Following function defined ONLY when running under Microsoft Windows */
/* And only available in API version 2.4 or greater                     */
/************************************************************************/
N1231B_RETURN
N1231BPciInterruptDetach(N1231B_HANDLE		N1231BHandle);
/*
 *	For the card specified by N1231BHandle:
 *
 *	De-allocates the internal recources that were setup
 *	by a prior call to N1231B_PciInterruptAttach().
 *
 *	Return value:
 *		N1231B_SUCCESS:		  Success.
 *		N1231B_ERR_HANDLE:	  N1231BHandle invalid.
 *		N1231B_ERR_PARAM:	  A passed parameter is NULL.
 *      N1231B_ERR_DEVICE:    An internal structure is invalid
 *		N1231B_ERR_MAX_EVENTS Insufficient resources for operation.
 */

/************************************************************************/
/* Following function defined ONLY when running under Microsoft Windows */
/* And only available in API version 2.4 or greater                     */
/************************************************************************/
N1231B_RETURN
N1231BPciInterruptWait(N1231B_HANDLE		N1231BHandle,
					   unsigned long		Timeout_ms);
/*
 *	For the card specified by N1231BHandle:
 *
 *	Waits the specified timeout limit for a previously setup
 *	interrupt to occur (see N1231BPciInterruptAttache() and
 *	N1231BPciInterruptEnable()). This function should be called
 *	(instead of a Windows Wait function) to wait for, or check
 *	the status of any pending interrupts from the board.
 *
 *	Return value:
 *		N1231B_SUCCESS:		  Success.
 *		N1231B_ERR_HANDLE:	  N1231BHandle invalid.
 *		N1231B_ERR_PARAM:	  A passed parameter is NULL.
 *      N1231B_ERR_DEVICE:    An internal structure is invalid
 *      N1231B_ERR_DRIVER:    Low-level driver failure
 *      N1231B_WAIT_TIMEOUT:  Timeout reached
 *      N1231B_WAIT_CANCEL:   Wait cancelled
 */

/************************************************************************/
/* Following function not provided for use under Windows.               */
/* Used internally by Keysight for factory testing.                      */
/************************************************************************/
N1231B_RETURN
N1231BPciAttachIsr(N1231B_HANDLE  N1231BHandle,
				   void           (*isrFunc)(N1231B_HANDLE N1231BHandle));
/*
 *	For the card specified by N1231BHandle:
 *
 *  Attaches the routine specified by isrFunc to the interrupt.
 *  If an interrupt occurs, this function will be called and 
 *  passed the N1231BHandle as its only argument.
 *
 *  Function isrFunc must not return a value.
 *
 *	Return value:
 *		N1231B_SUCCESS:		  Success.
 *		N1231B_ERR_PARAM:	  A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	  N1231BHandle invalid.
 */

/************************************************************************/

/*
 * ==================================
 * Lower Level Functions
 * ==================================
 */

/************************************************************************/
N1231B_RETURN
N1231BSamplePosVel(N1231B_HANDLE	N1231BHandle,
				   N1231B_AXIS		axis);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Executes a Software Sample of position and velocity.
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 */

/************************************************************************/
N1231B_RETURN
N1231BReadRawPos(N1231B_HANDLE	N1231BHandle,
				 N1231B_AXIS	axis,
			   	 N1231B_INT64	*pPosition);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Reads position value from the software sample register.
 *
 *  IMPORTANT NOTE: This function reads the value that was taken 
 *  on the last "sample" command.  It does not cause a new sample 
 *  to be latched.  Therefore, repeated calls to this function will
 *  return the same value unless a new sample command is issued.
 *  See also: N1231BSamplePosVel() and N1231BGetRawPosVel().
 *
 *	If an error has occurred on the axis, *pPosition 
 *	will be left unchanged.
 *
 *	The position value is in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS		 Error on the axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BReadRawVel(N1231B_HANDLE	N1231BHandle,
				 N1231B_AXIS	axis,
			   	 long			*pVelocity);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Reads velocity value from the software sample register.
 *
 *  IMPORTANT NOTE: This function reads the value that was taken 
 *  on the last "sample" command.  It does not cause a new sample 
 *  to be latched.  Therefore, repeated calls to this function will
 *  return the same value unless a new sample command is issued.
 *  See also: N1231BSamplePosVel() and N1231BGetRawPosVel().
 *
 *	If an error has occurred on the axis, *pVelocity 
 *	will be left unchanged.
 *
 *	The velocity value is in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 *		N1231B_ERR_AXIS:	 Error on axis or reference.
 */

/************************************************************************/
N1231B_RETURN
N1231BWriteRawPresetRegister(N1231B_HANDLE	N1231BHandle,
							 N1231B_AXIS	axis,
							 N1231B_INT64	presetValue);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Writes presetValue to the preset position register for the axis.
 *     
 *  IMPORTANT NOTE: 
 *    Does not transfer this value into the position register.
 *    See also: N1231BPresetRaw().
 *
 *	The preset value is in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:	  	 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 */

/************************************************************************/
N1231B_RETURN
N1231BReadRawPresetRegister(N1231B_HANDLE	N1231BHandle,
						    N1231B_AXIS		axis,
						    N1231B_INT64	*pPresetValue);
/*
 *	For the card specified by N1231BHandle and the axis specified
 *  by axis:
 *
 *	a) Sets *pPresetValue to the contents of the 
 *	   preset position register for the axis.
 *
 *	The preset value is in raw interferometer 
 *	units (see Definitions of Terms near top of this file).
 *
 *	Return value:
 *		N1231B_SUCCESS:		 Success.
 *		N1231B_ERR_PARAM:	 A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	 N1231BHandle invalid.
 *		N1231B_ERR_BAD_AXIS: Axis does not exist 
 */


/************************************************************************/
/*
 * ==================================
 * Register Functions (for test use only)
 * ==================================
 */

/************************************************************************/
N1231B_RETURN
N1231BWriteRegisterLong(N1231B_HANDLE	N1231BHandle,
						unsigned int	N1231BRegister,
						long			value);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Writes 32-bit value to the specified register.
 *
 *	The following constants can be used for the parameter 
 *  N1231BRegister:  However, be sure to also write the high order 
 *  4 bits of the 36-bit value to the corresponding "high" register.
 *
 *		N1231B_OFST_PRESET1
 *		N1231B_OFST_PRESET2
 *		N1231B_OFST_PRESET3A
 *		N1231B_OFST_PRESET3B
 *
 *		N1231B_OFST_GE_TH1
 *		N1231B_OFST_GE_TH2
 *		N1231B_OFST_GE_TH3A
 *		N1231B_OFST_GE_TH3B
 *
 *		N1231B_OFST_LT_TH1
 *		N1231B_OFST_LT_TH2
 *		N1231B_OFST_LT_TH3A
 *		N1231B_OFST_LT_TH3B
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_REG:		Invalid register for long write.
 */

/************************************************************************/
N1231B_RETURN
N1231BReadRegisterLong(N1231B_HANDLE	N1231BHandle,
					   unsigned int		N1231BRegister,
					   long				*value);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads 32-bit value from the specified register.
 *
 *	The following constants can be used for the parameter 
 *  N1231BRegister:  However, be sure to also read the high order 
 *  4 bits of any 36-bit values from the corresponding "high" register.
 *
 *		N1231B_OFST_POS1_SWS
 *		N1231B_OFST_POS1_AXS
 *		N1231B_OFST_POS1_SYS
 *
 *		N1231B_OFST_POS2_SWS
 *		N1231B_OFST_POS2_AXS
 *		N1231B_OFST_POS2_SYS
 *
 *		N1231B_OFST_POS3_SWS
 *		N1231B_OFST_POS3_AXS
 *		N1231B_OFST_POS3_SYS
 *
 *		N1231B_OFST_VEL1_SWS
 *		N1231B_OFST_VEL1_AXS
 *		N1231B_OFST_VEL1_SYS
 *
 *		N1231B_OFST_VEL2_SWS
 *		N1231B_OFST_VEL2_AXS
 *		N1231B_OFST_VEL2_SYS
 *
 *		N1231B_OFST_VEL3_SWS
 *		N1231B_OFST_VEL3_AXS
 *		N1231B_OFST_VEL3_SYS
 *
 *		N1231B_OFST_PRESET1
 *		N1231B_OFST_PRESET2
 *		N1231B_OFST_PRESET3A
 *		N1231B_OFST_PRESET3B
 *
 *		N1231B_OFST_GE_TH1
 *		N1231B_OFST_GE_TH2
 *		N1231B_OFST_GE_TH3A
 *		N1231B_OFST_GE_TH3B
 *
 *		N1231B_OFST_LT_TH1
 *		N1231B_OFST_LT_TH2
 *		N1231B_OFST_LT_TH3A
 *		N1231B_OFST_LT_TH3B
 *
 *		N1231B_OFST_FPGA1_REV
 *		N1231B_OFST_FPGA2_REV
 *		N1231B_OFST_FPGA1_ID
 *		N1231B_OFST_FPGA2_ID
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_REG:		Invalid register for long read.
 */

/************************************************************************/
N1231B_RETURN
N1231BWriteRegisterWord(N1231B_HANDLE	N1231BHandle,
						unsigned int	N1231BRegister,
						short			value);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Writes 16-bit value to the specified register.
 *
 *	The following constants can be used 
 *	for the parameter N1231BRegister:
 *
 *		N1231B_OFST_PRESET1_HI
 *		N1231B_OFST_THRESH1_HI
 *
 *		N1231B_OFST_PRESET2_HI
 *		N1231B_OFST_THRESH2_HI
 *
 *		N1231B_OFST_PRESET3A_HI
 *		N1231B_OFST_THRESH3A_HI
 *
 *		N1231B_OFST_PRESET3B_HI
 *		N1231B_OFST_THRESH3B_HI
 *
 *		N1231B_OFST_CONFIG_3A
 *		N1231B_OFST_CONFIG_123B
 *
 *		N1231B_OFST_CONFIG_CMP_3A
 *		N1231B_OFST_CONFIG_CMP_123B
 *
 *		N1231B_OFST_CHN_STATUS
 *		N1231B_OFST_CMP_STATUS
 *
 *		N1231B_OFST_CHN_INTRMASK
 *		N1231B_OFST_CMP_INTRMASK
 *
 *		N1231B_OFST_FILTER
 *		N1231B_OFST_HWIOSU
 *		N1231B_OFST_SAMPLE_PRESET
 *		N1231B_OFST_GLOBAL_INTR_ENB
 *
 *		N1231B_OFST_CLK1_DIV
 *		N1231B_OFST_CLK1_MODE
 *      N1231B_OFST_CLK1_PHSOFST
 *		N1231B_OFST_CLK2_DIV
 *		N1231B_OFST_CLK2_MODE
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_REG:		Invalid register for word write.
 */

/************************************************************************/
N1231B_RETURN
N1231BReadRegisterWord(N1231B_HANDLE	N1231BHandle,
					   unsigned int		N1231BRegister,
					   short			*value);
/*
 *	For the card specified by N1231BHandle:
 *
 *	a) Reads 16-bit value from the specified register.
 *
 *	The following constants can be used 
 *	for the parameter N1231BRegister:
 *
 *		N1231B_OFST_POS12_SWS_HI
 *		N1231B_OFST_POS12_AXS_HI
 *		N1231B_OFST_POS12_SYS_HI
 *		N1231B_OFST_POS3_SWS_HI
 *		N1231B_OFST_POS3_AXS_HI
 *		N1231B_OFST_POS3_SYS_HI
 *
 *		N1231B_OFST_PRESET1_HI
 *		N1231B_OFST_THRESH1_HI
 *
 *		N1231B_OFST_PRESET2_HI
 *		N1231B_OFST_THRESH2_HI
 *
 *		N1231B_OFST_PRESET3A_HI
 *		N1231B_OFST_THRESH3A_HI
 *
 *		N1231B_OFST_PRESET3B_HI
 *		N1231B_OFST_THRESH3B_HI
 *
 *		N1231B_OFST_CONFIG_3A
 *		N1231B_OFST_CONFIG_123B
 *
 *		N1231B_OFST_CONFIG_CMP_3A
 *		N1231B_OFST_CONFIG_CMP_123B
 *
 *		N1231B_OFST_STATE_CMP_3A
 *		N1231B_OFST_STATE_CMP_123B
 *
 *		N1231B_OFST_VALID3
 *		N1231B_OFST_VALID12
 *
 *		N1231B_OFST_CHN_STATUS
 *		N1231B_OFST_CMP_STATUS
 *
 *		N1231B_OFST_CHN_INTRMASK
 *		N1231B_OFST_CMP_INTRMASK
 *
 *		N1231B_OFST_FILTER
 *		N1231B_OFST_HWIOSU
 *		N1231B_OFST_GLOBAL_INTR_ENB
 *
 *		N1231B_OFST_CLK1_DIV
 *		N1231B_OFST_CLK1_MODE
 *      N1231B_OFST_CLK1_PHSOFST
 *		N1231B_OFST_CLK2_DIV
 *		N1231B_OFST_CLK2_MODE
 *
 *
 *	Return value:
 *		N1231B_SUCCESS:		Success.
 *		N1231B_ERR_PARAM:	A passed parameter is NULL.
 *		N1231B_ERR_HANDLE:	N1231BHandle invalid.
 *		N1231B_ERR_REG:		Invalid register for word read.
 */

#ifdef __cplusplus
}
#endif

#endif /* IFNDEF N1231B_H */
