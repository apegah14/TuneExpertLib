/*
 * Copyright 2018 by Keysight Technologies
 *
 * File Name: N1231B_DL.h
 *
 * Header file for Dynamically Loading the N1231B API library DLL
 * for the Keysight Technologies N1231B PCI Three-Axis Board
 * designed for use with an Keysight Technologies
 * laser interferometry position measurement systems.
 *
 * ======================= IMPORTANT USAGE NOTE ========================
 *	If more than one file within a project needs to include this
 *	header file, then those files MUST #define N1231B_DECLARATIONS_ONLY
 *	before including the file. The one project file that includes this
 *	header without this #define will get a warning about not using
 *	compiled headers due to code in the header file.
 * =====================================================================
 *
 * See the N1231B.h file for function parameter information
 *
 * Last revision of this file:
 *	  13 Apr 2011 - initial release
 *    10 Apr 2018 - Added 'GetHdwIoSetup() to TFP_N1231BPUS, 'SetHdwIoSetup() to TFP_N1231BUS, and 'SyncPDClks() to TFP_N1231BIDT function types
 *     1 May 2018 - Added support for all 'poll* data collection routines
 */

#ifndef N1231B_DL_H
#define N1231B_DL_H

/*
 ****************************************************************
 * C/C++ Compatibility
 ********************************
 */
#ifdef __cplusplus
extern "C" {
#endif

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
 * Used for programmable data clock identification
 *		N1231B_PDCLOCK
 *
 * Used for dynamic loading of DLL routines
 *		TFP_N1231BOPN
 *		TFP_N1231BDEF
 *		TFP_N1231BCLS
 *		TFP_N1231BFND
 *		TFP_N1231BPRE
 *		TFP_N1231BPREALL
 *		TFP_N1231BGPV
 *		TFP_N1231BGPVALL
 *		TFP_N1231BGPVARY
 *		TFP_N1231BGXSALL
 *		TFP_N1231BGXSALLARY
 *		TFP_N1231BCSB
 *		TFP_N1231BPUL
 *		TFP_N1231BGS
 *		TFP_N1231BUL
 *		TFP_N1231BSLT
 *		TFP_N1231BGLT
 *		TFP_N1231BSKC
 *		TFP_N1231BGKC
 *		TFP_N1231BUS
 *		TFP_N1231BPUS
 *		TFP_N1231B2PUL
 *		TFP_N1231BGLR
 *		TFP_N1231BGES
 *		TFP_N1231BIEN
 *		TFP_N1231BIAT
 *		TFP_N1231BIDT
 *		TFP_N1231BSPV
 *		TFP_N1231BAXPI64
 *		TFP_N1231BRV
 *		TFP_N1231BWPRE
 *		TFP_N1231BWL
 *		TFP_N1231BRL
 *		TFP_N1231BWS
 *		TFP_N1231BRS
 *
 * ==================================
 * High Level Functions
 * ==================================
 *
 * N1231B_LoadAPI()
 * N1231B_FreeAPI()
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
 * N1231BpollRead1AxisPosVel()	- can set some params to NULL
 * N1231BpollRead3AxisPosVel()	- can set some params to NULL
 * N1231BpollReadSysPosVel()
 *
 * ==================================
 * Polling with TimeStamp Data Collection Functions
 * ==================================
 *
 * N1231BpolltsRead1AxisPos32()
 * N1231BpolltsReadSysPos32()
 * N1231BpolltsRead1AxisPosVel()
 * N1231BpolltsRead3AxisPosVel()	- can set some params to NULL
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
 ******************************************
 * Typedefs, Constants, Enums, Structures *
 ******************************************
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
 * Used for polled data collection functions
 */
typedef struct TS_SMPL_INFO
	{
	unsigned long ulRequested;			// samples to get
	unsigned long ulObtained;			// samples actually obtained
	unsigned long ulTimeoutLoopCount;	// # of iterations (ms for *isr* ruotines) before timeout error
	} SMPL_INFO, *pSMPL_INFO;

typedef union TU_MULTI_ACCESS			// see routine comments for use of each word in structure
	{
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
 * Used to specify type of sampled data to retrieve
 */
typedef short N1231B_SAMP_TYPE;
enum E_N1231B_SAMP_TYPE
{
	SAMP_TYPE_SWS,
	SAMP_TYPE_AXS,
	SAMP_TYPE_SYS
};

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
 * Used for delay loading API DLL routines
 */
/* for 'Open	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BOPN) (
	N1231B_LOCATION*,
	N1231B_HANDLE*,
	unsigned long*
	);

/* for 'DefaultDevice	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BDEF) (
	N1231B_LOCATION*
	);

/* for 'Close	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BCLS) (
	N1231B_HANDLE*
	);

/* for 'Find	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BFND) (
	N1231B_LOCATION*,
	unsigned int*,
	N1231B_LOCATION*,
	unsigned int
	);

/* for 'PresetRaw	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BPRE) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64,
	unsigned short*
	);

/* for 'PresetRawAll	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BPREALL) (
	N1231B_HANDLE,
	N1231B_INT64,
	N1231B_INT64,
	N1231B_INT64,
	unsigned long*
	);

/* for 'GetRawPosVel, 'GetRawXSysSample, 'GetRawXAxisSample	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BGPV) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64*,
	long*
	);

/* for 'GetRawPosVelAll, 'GetRawXSysSampleAll, 'GetRawXAxisSampleAll	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BGPVALL) (
	N1231B_HANDLE,
	N1231B_INT64*,
	long*,
	N1231B_INT64*,
	long*,
	N1231B_INT64*,
	long*,
	unsigned short*
	);

/* for 'GetRawXSysSampleAllArray, 'GetRawXAxisSampleAllArray */
typedef N1231B_RETURN (__cdecl * TFP_N1231BGPVARY) (
	N1231B_HANDLE,
	N1231B_SAMPLES*
	);

/* for 'GetRawXSampleAll */
typedef N1231B_RETURN (__cdecl * TFP_N1231BGXSALL) (
	N1231B_HANDLE,
	N1231B_INT64*,		long*,
	N1231B_INT64*,		long*,
	N1231B_INT64*,		long*,
	N1231B_INT64*,		long*,
	N1231B_INT64*,		long*,
	N1231B_INT64*,		long*,
	unsigned short*,	unsigned short*
	);

/* for 'GetRawXSampleAllArray */
typedef N1231B_RETURN (__cdecl * TFP_N1231BGXSALLARY) (
	N1231B_HANDLE,
	N1231B_SAMPLES*,
	N1231B_SAMPLES*
	);

/* for 'ClearStatusBits	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BCSB) (
	N1231B_HANDLE,
	unsigned long,
	unsigned long*
	);

/* for 'ClearPathErrorAll, 'ClearStatusAll, 'GetInterruptMask, 'GetConfig, 'GetGeLtDirections, 'GetGeLtStatus	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BPUL) (
	N1231B_HANDLE,
	unsigned long*
	);

/* for 'GetStatus	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BGS) (
	N1231B_HANDLE,
	unsigned long*,
	unsigned short*
	);

/* for 'SetIinterruptMask, 'SetConfig, 'SetGeLtDirections, PciInterruptWait	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BUL) (
	N1231B_HANDLE,
	unsigned long
	);

/* for 'SetGeLtThresholds */
typedef N1231B_RETURN (__cdecl * TFP_N1231BSLT) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64,
	N1231B_INT64
	);

/* for 'GetGeLtThresholds */
typedef N1231B_RETURN (__cdecl * TFP_N1231BGLT) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64*,
	N1231B_INT64*
	);

/* for 'SetPDClockControl */
typedef N1231B_RETURN (__cdecl * TFP_N1231BSKC) (
	N1231B_HANDLE,
	N1231B_PDCLOCK,
	unsigned short,
	unsigned short
	);

/* for 'GetPDClockControl */
typedef N1231B_RETURN (__cdecl * TFP_N1231BGKC) (
	N1231B_HANDLE,
	N1231B_PDCLOCK,
	unsigned short*,
	unsigned short*
	);

/* for 'SetFilter, 'SetGlobalInterruptEnable, SetHdwIoSetup	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BUS) (
	N1231B_HANDLE,
	unsigned short
	);

/* for 'GetFilter, 'GetGlobalInterruptEnable, GetHdwIoSetup, 'GetHdwRev */
typedef N1231B_RETURN (__cdecl * TFP_N1231BPUS) (
	N1231B_HANDLE,
	unsigned short*
	);

/* for 'GetFPGARevs, 'GetFPGAIds	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231B2PUL) (
	N1231B_HANDLE,
	unsigned long*,
	unsigned long*
	);

/* for 'GetLibraryRev	*/
typedef unsigned int (__cdecl * TFP_N1231BGLR) (
	void
	);

/* for 'GetErrStr	*/
typedef char* (__cdecl * TFP_N1231BGES) (
	N1231B_RETURN
	);

/* for 'pollReadSysPos32, 'pollReadSysPosVel */
typedef N1231B_RETURN (__cdecl * TFP_N1231BUSPSIPV) (
	N1231B_HANDLE,
	unsigned short,
	SMPL_INFO *,
	void *
	);

/* for 'pollRead1AxisPos32 */
typedef N1231B_RETURN (__cdecl * TFP_N1231BP132) (
	N1231B_HANDLE,
	N1231B_AXIS,
	unsigned short,
	SMPL_INFO *,
	MULTI_ACCESS *
	);

/* for 'polltsReadSysPos32, 'polltsReadSysPosVel */
typedef N1231B_RETURN (__cdecl * TFP_N1231BUSPSIPVPLI) (
	N1231B_HANDLE,
	unsigned short,
	SMPL_INFO *,
	void *,
	LARGE_INTEGER *
	);

/* for 'pollRead1AxisPosVel, 'polltsRead1AxisPos3, 'polltsRead1AxisPosVel */
typedef N1231B_RETURN (__cdecl * TFP_N1231BAUSPSIPVPV) (
	N1231B_HANDLE,
	N1231B_AXIS,
	unsigned short,
	SMPL_INFO *,
	void *,
	void *
	);

/* for 'polltsRead3AxisPosVel */
typedef N1231B_RETURN (__cdecl * TFP_N1231BPT3PV) (
	N1231B_HANDLE,
	unsigned short,
	SMPL_INFO *,
	SMPL_INFO *,
	SMPL_INFO *,
	N1231B_HDR_1POSVEL *,
	N1231B_HDR_1POSVEL *,
	N1231B_HDR_1POSVEL *,
	LARGE_INTEGER *
	);

/* for 'pollRead3AxisPosVel */
typedef N1231B_RETURN (__cdecl * TFP_N1231BP3PV) (
	N1231B_HANDLE,
	unsigned short,
	SMPL_INFO *,
	SMPL_INFO *,
	SMPL_INFO *,
	MULTI_ACCESS *,
	MULTI_ACCESS *,
	MULTI_ACCESS *,
	long *,
	long *,
	long *
	);

/* for 'InterruptEnable	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BIEN) (
	N1231B_HANDLE,
	int
	);

/* for 'InterruptAttach	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BIAT) (
	N1231B_HANDLE,
	N1231B_EVT_HANDLE*
	);

/* for 'InterruptDetach, N1231BSyncPDClks	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BIDT) (
	N1231B_HANDLE
	);

/* for 'SamplePosVel	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BSPV) (
	N1231B_HANDLE,
	N1231B_AXIS
	);

/* for 'ReadRawPos, 'ReadRawPresetRegister	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BAXPI64) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64*
	);

/* for 'ReadRawVel	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BRV) (
	N1231B_HANDLE,
	N1231B_AXIS,
	long*
	);

/* for 'WriteRawPresetRegister	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BWPRE) (
	N1231B_HANDLE,
	N1231B_AXIS,
	N1231B_INT64
	);

/* for 'WriteRegisterLong	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BWL) (
	N1231B_HANDLE,
	unsigned int,
	long
	);

/* for 'ReadRegisterLong	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BRL) (
	N1231B_HANDLE,
	unsigned int,
	long*
	);

/* for 'WriteRegisterWord	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BWS) (
	N1231B_HANDLE,
	unsigned int,
	short
	);

/* for 'ReadRegisterWord	*/
typedef N1231B_RETURN (__cdecl * TFP_N1231BRS) (
	N1231B_HANDLE,
	unsigned int,
	short*
	);

/*
 *********************************************
 *********************************************
 * FUNCTION POINTER VARIABLES
 *
 *	note - comment out any un-used functions
 *
 *********************************************
 *********************************************
 */

#ifdef N1231B_DECLARATIONS_ONLY

/*
 * used with 2nd, 3rd, ... source files in projects that need these declarations
 *
 * comment out any un-used functions if desired
 */
extern TFP_N1231BOPN		N1231BOpen;
extern TFP_N1231BDEF		N1231BDefaultDevice;
extern TFP_N1231BCLS		N1231BClose;
extern TFP_N1231BFND		N1231BFind;
extern TFP_N1231BPRE		N1231BPresetRaw;
extern TFP_N1231BPREALL		N1231BPresetRawAll;
extern TFP_N1231BGPV		N1231BGetRawPosVel;
extern TFP_N1231BGPVALL		N1231BGetRawPosVelAll;
extern TFP_N1231BGPV		N1231BGetRawXSysSample;
extern TFP_N1231BGPVALL		N1231BGetRawXSysSampleAll;
extern TFP_N1231BGPVARY		N1231BGetRawXSysSampleAllArray;
extern TFP_N1231BGPV		N1231BGetRawXAxisSample;
extern TFP_N1231BGPVALL		N1231BGetRawXAxisSampleAll;
extern TFP_N1231BGPVARY		N1231BGetRawXAxisSampleAllArray;
extern TFP_N1231BGXSALL		N1231BGetRawXSampleAll;
extern TFP_N1231BGXSALLARY	N1231BGetRawXSampleAllArray;
extern TFP_N1231BCSB		N1231BClearStatusBits;
extern TFP_N1231BPUL		N1231BClearPathErrorAll;
extern TFP_N1231BPUL		N1231BClearStatusAll;
extern TFP_N1231BGS			N1231BGetStatus;
extern TFP_N1231BUL			N1231BSetInterruptMask;
extern TFP_N1231BPUL		N1231BGetInterruptMask;
extern TFP_N1231BUL			N1231BSetConfig;
extern TFP_N1231BPUL		N1231BGetConfig;
extern TFP_N1231BUL			N1231BSetGeLtDirections;
extern TFP_N1231BPUL		N1231BGetGeLtDirections;
extern TFP_N1231BSLT		N1231BSetGeLtThresholds;
extern TFP_N1231BGLT		N1231BGetGeLtThresholds;
extern TFP_N1231BPUL		N1231BGetGeLtStatus;
extern TFP_N1231BSKC		N1231BSetPDClockControl;
extern TFP_N1231BGKC		N1231BGetPDClockControl;
extern TFP_N1231BUS			N1231BSetFilter;
extern TFP_N1231BPUS		N1231BGetFilter;
extern TFP_N1231BUS			N1231BSetHdwIoSetup;
extern TFP_N1231BPUS		N1231BGetHdwIoSetup;
extern TFP_N1231BIDT		N1231BSyncPDClks;
extern TFP_N1231B2PUL		N1231BGetFPGARevs;
extern TFP_N1231B2PUL		N1231BGetFPGAIds;
extern TFP_N1231BPUS		N1231BGetHdwRev;
extern TFP_N1231BGLR		N1231BGetLibraryRev;
extern TFP_N1231BGES		N1231BGetErrStr;
extern TFP_N1231BUSPSIPV	N1231BpollReadSysPos32;
extern TFP_N1231BUSPSIPV	N1231BpollReadSysPosVel;
extern TFP_N1231BP132		N1231BpollRead1AxisPos32;
extern TFP_N1231BUSPSIPVPLI	N1231BpolltsReadSysPos32;
extern TFP_N1231BUSPSIPVPLI	N1231BpolltsReadSysPosVel;
extern TFP_N1231BAUSPSIPVPV	N1231BpollRead1AxisPosVel;
extern TFP_N1231BAUSPSIPVPV	N1231BpolltsRead1AxisPos3;
extern TFP_N1231BAUSPSIPVPV	N1231BpolltsRead1AxisPosVel;
extern TFP_N1231BPT3PV		N1231BpolltsRead3AxisPosVel;
extern TFP_N1231BP3PV		N1231BpollRead3AxisPosVel;
extern TFP_N1231BUS			N1231BSetGlobalInterruptEnable;
extern TFP_N1231BPUS		N1231BGetGlobalInterruptEnable;
extern TFP_N1231BIEN		N1231BPciInterruptEnable;
extern TFP_N1231BIAT		N1231BPciInterruptAttach;
extern TFP_N1231BIDT		N1231BPciInterruptDetach;
extern TFP_N1231BUL			N1231BPciInterruptWait;
extern TFP_N1231BSPV		N1231BSamplePosVel;
extern TFP_N1231BAXPI64		N1231BReadRawPos;
extern TFP_N1231BRV			N1231BReadRawVel;
extern TFP_N1231BWPRE		N1231BWriteRawPresetRegister;
extern TFP_N1231BAXPI64		N1231BReadRawPresetRegister;
extern TFP_N1231BWL			N1231BWriteRegisterLong;
extern TFP_N1231BRL			N1231BReadRegisterLong;
extern TFP_N1231BWS			N1231BWriteRegisterWord;
extern TFP_N1231BRS			N1231BReadRegisterWord;

int N1231B_LoadAPI(void);
void N1231B_FreeAPI(void);

#else

/*
 * used only for 1st source file in projects that need these declarations
 *
 * comment out any un-used functions if desired
 */

/*
 * ==================================
 * High Level Functions
 * ==================================
 */
TFP_N1231BOPN N1231BOpen = NULL;
TFP_N1231BDEF N1231BDefaultDevice = NULL;
TFP_N1231BCLS N1231BClose = NULL;
TFP_N1231BFND N1231BFind = NULL;
TFP_N1231BPRE N1231BPresetRaw = NULL;
TFP_N1231BPREALL N1231BPresetRawAll = NULL;
TFP_N1231BGPV N1231BGetRawPosVel = NULL;
TFP_N1231BGPVALL N1231BGetRawPosVelAll = NULL;
TFP_N1231BGPV N1231BGetRawXSysSample = NULL;
TFP_N1231BGPVALL N1231BGetRawXSysSampleAll = NULL;
TFP_N1231BGPVARY N1231BGetRawXSysSampleAllArray = NULL;
TFP_N1231BGPV N1231BGetRawXAxisSample = NULL;
TFP_N1231BGPVALL N1231BGetRawXAxisSampleAll = NULL;
TFP_N1231BGPVARY N1231BGetRawXAxisSampleAllArray = NULL;
TFP_N1231BGXSALL N1231BGetRawXSampleAll = NULL;
TFP_N1231BGXSALLARY N1231BGetRawXSampleAllArray = NULL;
TFP_N1231BCSB N1231BClearStatusBits = NULL;
TFP_N1231BPUL N1231BClearPathErrorAll = NULL;
TFP_N1231BPUL N1231BClearStatusAll = NULL;
TFP_N1231BGS N1231BGetStatus = NULL;
TFP_N1231BUL N1231BSetInterruptMask = NULL;
TFP_N1231BPUL N1231BGetInterruptMask = NULL;
TFP_N1231BUL N1231BSetConfig = NULL;
TFP_N1231BPUL N1231BGetConfig = NULL;
TFP_N1231BUL N1231BSetGeLtDirections = NULL;
TFP_N1231BPUL N1231BGetGeLtDirections = NULL;
TFP_N1231BSLT N1231BSetGeLtThresholds = NULL;
TFP_N1231BGLT N1231BGetGeLtThresholds = NULL;
TFP_N1231BPUL N1231BGetGeLtStatus = NULL;
TFP_N1231BSKC N1231BSetPDClockControl = NULL;
TFP_N1231BGKC N1231BGetPDClockControl = NULL;
TFP_N1231BUS N1231BSetFilter = NULL;
TFP_N1231BPUS N1231BGetFilter = NULL;
TFP_N1231BUS N1231BSetHdwIoSetup = NULL;      // new rev 2.5
TFP_N1231BPUS N1231BGetHdwIoSetup = NULL;     // new rev 2.5
TFP_N1231BIDT N1231BSyncPDClks = NULL;        // new rev 2.5.1
TFP_N1231B2PUL N1231BGetFPGARevs = NULL;
TFP_N1231B2PUL N1231BGetFPGAIds = NULL;
TFP_N1231BPUS N1231BGetHdwRev = NULL;
TFP_N1231BGLR N1231BGetLibraryRev = NULL;
TFP_N1231BGES N1231BGetErrStr = NULL;
/*
 * ==================================
 * Poll Functions
 * ==================================
 */
TFP_N1231BUSPSIPV N1231BpollReadSysPos32 = NULL;
TFP_N1231BUSPSIPV N1231BpollReadSysPosVel = NULL;
TFP_N1231BP132 N1231BpollRead1AxisPos32 = NULL;
TFP_N1231BUSPSIPVPLI N1231BpolltsReadSysPos32 = NULL;
TFP_N1231BUSPSIPVPLI N1231BpolltsReadSysPosVel = NULL;
TFP_N1231BAUSPSIPVPV N1231BpollRead1AxisPosVel = NULL;
TFP_N1231BAUSPSIPVPV N1231BpolltsRead1AxisPos3 = NULL;
TFP_N1231BAUSPSIPVPV N1231BpolltsRead1AxisPosVel = NULL;
TFP_N1231BPT3PV N1231BpolltsRead3AxisPosVel = NULL;
TFP_N1231BP3PV N1231BpollRead3AxisPosVel = NULL;
/*
 * ==================================
 * Interrupt Related Functions
 * ==================================
 */
TFP_N1231BUS N1231BSetGlobalInterruptEnable = NULL;
TFP_N1231BPUS N1231BGetGlobalInterruptEnable = NULL;
TFP_N1231BIEN N1231BPciInterruptEnable = NULL;
TFP_N1231BIAT N1231BPciInterruptAttach = NULL;
TFP_N1231BIDT N1231BPciInterruptDetach = NULL;
TFP_N1231BUL N1231BPciInterruptWait = NULL;
/*
 * ==================================
 * Lower Level Functions
 * ==================================
 */
TFP_N1231BSPV N1231BSamplePosVel = NULL;
TFP_N1231BAXPI64 N1231BReadRawPos = NULL;
TFP_N1231BRV N1231BReadRawVel = NULL;
TFP_N1231BWPRE N1231BWriteRawPresetRegister = NULL;
TFP_N1231BAXPI64 N1231BReadRawPresetRegister = NULL;
/*
 * ==================================
 * Register Functions (for test use only)
 * ==================================
 */
TFP_N1231BWL N1231BWriteRegisterLong = NULL;
TFP_N1231BRL N1231BReadRegisterLong = NULL;
TFP_N1231BWS N1231BWriteRegisterWord = NULL;
TFP_N1231BRS N1231BReadRegisterWord = NULL;

HMODULE hN1231B_API = NULL;

/*
 *********************************************
 *********************************************
 * LOAD (and FREE) LIBRARY CODE
 *********************************************
 *********************************************
 */

/*
 * Return values:
 *		-1 : DLL could not be loaded
 *		 0 : Success
 *		>0 : Number of routines that could not be found in loaded DLL
 */
int N1231B_LoadAPI(void)
	{
	int NoFunctionCount = 0;

	if (hN1231B_API) return (0);

	if ((hN1231B_API = LoadLibrary(L"N1231B")) == NULL)
		return (-1);

	/* comment out any un-used functions if desired	*/
	if ((N1231BOpen						= (TFP_N1231BOPN	)	GetProcAddress(hN1231B_API,"N1231BOpen")					) == NULL) NoFunctionCount++;
	if ((N1231BDefaultDevice			= (TFP_N1231BDEF	)	GetProcAddress(hN1231B_API,"N1231BDefaultDevice")			) == NULL) NoFunctionCount++;
	if ((N1231BClose					= (TFP_N1231BCLS	)	GetProcAddress(hN1231B_API,"N1231BClose")					) == NULL) NoFunctionCount++;
	if ((N1231BFind						= (TFP_N1231BFND	)	GetProcAddress(hN1231B_API,"N1231BFind")					) == NULL) NoFunctionCount++;
	if ((N1231BPresetRaw				= (TFP_N1231BPRE	)	GetProcAddress(hN1231B_API,"N1231BPresetRaw")				) == NULL) NoFunctionCount++;
	if ((N1231BPresetRawAll				= (TFP_N1231BPREALL	)	GetProcAddress(hN1231B_API,"N1231BPresetRawAll")			) == NULL) NoFunctionCount++;
	if ((N1231BGetRawPosVel				= (TFP_N1231BGPV	)	GetProcAddress(hN1231B_API,"N1231BGetRawPosVel")			) == NULL) NoFunctionCount++;
	if ((N1231BGetRawPosVelAll			= (TFP_N1231BGPVALL	)	GetProcAddress(hN1231B_API,"N1231BGetRawPosVelAll")			) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXSysSample			= (TFP_N1231BGPV	)	GetProcAddress(hN1231B_API,"N1231BGetRawXSysSample")		) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXSysSampleAll		= (TFP_N1231BGPVALL	)	GetProcAddress(hN1231B_API,"N1231BGetRawXSysSampleAll")		) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXSysSampleAllArray	= (TFP_N1231BGPVARY	)	GetProcAddress(hN1231B_API,"N1231BGetRawXSysSampleAllArray")) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXAxisSample		= (TFP_N1231BGPV	)	GetProcAddress(hN1231B_API,"N1231BGetRawXAxisSample")		) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXAxisSampleAll		= (TFP_N1231BGPVALL	)	GetProcAddress(hN1231B_API,"N1231BGetRawXAxisSampleAll")	) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXAxisSampleAllArray= (TFP_N1231BGPVARY	)	GetProcAddress(hN1231B_API,"N1231BGetRawXAxisSampleAllArray")) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXSampleAll			= (TFP_N1231BGXSALL	)	GetProcAddress(hN1231B_API,"N1231BGetRawXSampleAll")		) == NULL) NoFunctionCount++;
	if ((N1231BGetRawXSampleAllArray	= (TFP_N1231BGXSALLARY)	GetProcAddress(hN1231B_API,"N1231BGetRawXSampleAllArray")	) == NULL) NoFunctionCount++;
	if ((N1231BClearStatusBits			= (TFP_N1231BCSB	)	GetProcAddress(hN1231B_API,"N1231BClearStatusBits")			) == NULL) NoFunctionCount++;
	if ((N1231BClearPathErrorAll		= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BClearPathErrorAll")		) == NULL) NoFunctionCount++;
	if ((N1231BClearStatusAll			= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BClearStatusAll")			) == NULL) NoFunctionCount++;
	if ((N1231BGetStatus				= (TFP_N1231BGS		)	GetProcAddress(hN1231B_API,"N1231BGetStatus")				) == NULL) NoFunctionCount++;
	if ((N1231BSetInterruptMask			= (TFP_N1231BUL		)	GetProcAddress(hN1231B_API,"N1231BSetInterruptMask")		) == NULL) NoFunctionCount++;
	if ((N1231BGetInterruptMask			= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BGetInterruptMask")		) == NULL) NoFunctionCount++;
	if ((N1231BSetConfig				= (TFP_N1231BUL		)	GetProcAddress(hN1231B_API,"N1231BSetConfig")				) == NULL) NoFunctionCount++;
	if ((N1231BGetConfig				= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BGetConfig")				) == NULL) NoFunctionCount++;
	if ((N1231BSetGeLtDirections		= (TFP_N1231BUL		)	GetProcAddress(hN1231B_API,"N1231BSetGeLtDirections")		) == NULL) NoFunctionCount++;
	if ((N1231BGetGeLtDirections		= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BGetGeLtDirections")		) == NULL) NoFunctionCount++;
	if ((N1231BSetGeLtThresholds		= (TFP_N1231BSLT	)	GetProcAddress(hN1231B_API,"N1231BSetGeLtThresholds")		) == NULL) NoFunctionCount++;
	if ((N1231BGetGeLtThresholds		= (TFP_N1231BGLT	)	GetProcAddress(hN1231B_API,"N1231BGetGeLtThresholds")		) == NULL) NoFunctionCount++;
	if ((N1231BGetGeLtStatus			= (TFP_N1231BPUL	)	GetProcAddress(hN1231B_API,"N1231BGetGeLtStatus")			) == NULL) NoFunctionCount++;
	if ((N1231BSetPDClockControl		= (TFP_N1231BSKC	)	GetProcAddress(hN1231B_API,"N1231BSetPDClockControl")		) == NULL) NoFunctionCount++;
	if ((N1231BGetPDClockControl		= (TFP_N1231BGKC	)	GetProcAddress(hN1231B_API,"N1231BGetPDClockControl")		) == NULL) NoFunctionCount++;
	if ((N1231BSetFilter				= (TFP_N1231BUS		)	GetProcAddress(hN1231B_API,"N1231BSetFilter")				) == NULL) NoFunctionCount++;
	if ((N1231BGetFilter				= (TFP_N1231BPUS	)	GetProcAddress(hN1231B_API,"N1231BGetFilter")				) == NULL) NoFunctionCount++;
	if ((N1231BSetHdwIoSetup			= (TFP_N1231BUS		)	GetProcAddress(hN1231B_API,"N1231BSetHdwIoSetup")			) == NULL) NoFunctionCount++;     // new rev 2.5
	if ((N1231BGetHdwIoSetup			= (TFP_N1231BPUS	)	GetProcAddress(hN1231B_API,"N1231BGetHdwIoSetup")			) == NULL) NoFunctionCount++;     // new rev 2.5
	if ((N1231BSyncPDClks				= (TFP_N1231BIDT	)	GetProcAddress(hN1231B_API,"N1231BSyncPDClks")				) == NULL) NoFunctionCount++;     // new rev 2.5.1
	if ((N1231BGetFPGARevs				= (TFP_N1231B2PUL	)	GetProcAddress(hN1231B_API,"N1231BGetFPGARevs")				) == NULL) NoFunctionCount++;
	if ((N1231BGetFPGAIds				= (TFP_N1231B2PUL	)	GetProcAddress(hN1231B_API,"N1231BGetFPGAIds")				) == NULL) NoFunctionCount++;
	if ((N1231BGetHdwRev				= (TFP_N1231BPUS	)	GetProcAddress(hN1231B_API,"N1231BGetHdwRev")				) == NULL) NoFunctionCount++;
	if ((N1231BGetLibraryRev			= (TFP_N1231BGLR	)	GetProcAddress(hN1231B_API,"N1231BGetLibraryRev")			) == NULL) NoFunctionCount++;
	if ((N1231BGetErrStr				= (TFP_N1231BGES	)	GetProcAddress(hN1231B_API,"N1231BGetErrStr")				) == NULL) NoFunctionCount++;
	if ((N1231BpollReadSysPos32;		= (TFP_N1231BUSPSIPV	)	GetProcAddress(hN1231B_API,"N1231BpollReadSysPos32")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpollReadSysPosVel;		= (TFP_N1231BUSPSIPV	)	GetProcAddress(hN1231B_API,"N1231BpollReadSysPosVel")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpollRead1AxisPos32;		= (TFP_N1231BP132		)	GetProcAddress(hN1231B_API,"N1231BpollRead1AxisPos32")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpolltsReadSysPos32;		= (TFP_N1231BUSPSIPVPLI	)	GetProcAddress(hN1231B_API,"N1231BpolltsReadSysPos32")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpolltsReadSysPosVel;		= (TFP_N1231BUSPSIPVPLI	)	GetProcAddress(hN1231B_API,"N1231BpolltsReadSysPosVel")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpollRead1AxisPosVel;		= (TFP_N1231BAUSPSIPVPV	)	GetProcAddress(hN1231B_API,"N1231BpollRead1AxisPosVel")	) == NULL) NoFunctionCount++;     // new rev 2.6
	if ((N1231BpolltsRead1AxisPos3;		= (TFP_N1231BAUSPSIPVPV	)	GetProcAddress(hN1231B_API,"N1231BpolltsRead1AxisPos3")		) == NULL) NoFunctionCount++; // new rev 2.6
	if ((N1231BpolltsRead1AxisPosVel	= (TFP_N1231BAUSPSIPVPV	)	GetProcAddress(hN1231B_API,"N1231BpolltsRead1AxisPosVel")	) == NULL) NoFunctionCount++; // new rev 2.6
	if ((N1231BpolltsRead3AxisPosVel	= (TFP_N1231BPT3PV		)	GetProcAddress(hN1231B_API,"N1231BpolltsRead3AxisPosVel")	) == NULL) NoFunctionCount++; // new rev 2.6
	if ((N1231BpollRead3AxisPosVel;		= (TFP_N1231BP3PV		)	GetProcAddress(hN1231B_API,"N1231BpollRead3AxisPosVel")		) == NULL) NoFunctionCount++; // new rev 2.6
	if ((N1231BSetGlobalInterruptEnable	= (TFP_N1231BUS		)	GetProcAddress(hN1231B_API,"N1231BSetGlobalInterruptEnable")) == NULL) NoFunctionCount++;
	if ((N1231BGetGlobalInterruptEnable	= (TFP_N1231BPUS	)	GetProcAddress(hN1231B_API,"N1231BGetGlobalInterruptEnable")) == NULL) NoFunctionCount++;
	if ((N1231BPciInterruptEnable		= (TFP_N1231BIEN	)	GetProcAddress(hN1231B_API,"N1231BPciInterruptEnable")		) == NULL) NoFunctionCount++;
	if ((N1231BPciInterruptAttach		= (TFP_N1231BIAT	)	GetProcAddress(hN1231B_API,"N1231BPciInterruptAttach")		) == NULL) NoFunctionCount++;
	if ((N1231BPciInterruptDetach		= (TFP_N1231BIDT	)	GetProcAddress(hN1231B_API,"N1231BPciInterruptDetach")		) == NULL) NoFunctionCount++;
	if ((N1231BPciInterruptWait			= (TFP_N1231BUL		)	GetProcAddress(hN1231B_API,"N1231BPciInterruptWait")		) == NULL) NoFunctionCount++;
	if ((N1231BSamplePosVel				= (TFP_N1231BSPV	)	GetProcAddress(hN1231B_API,"N1231BSamplePosVel")			) == NULL) NoFunctionCount++;
	if ((N1231BReadRawPos				= (TFP_N1231BAXPI64	)	GetProcAddress(hN1231B_API,"N1231BReadRawPos")				) == NULL) NoFunctionCount++;
	if ((N1231BReadRawVel				= (TFP_N1231BRV		)	GetProcAddress(hN1231B_API,"N1231BReadRawVel")				) == NULL) NoFunctionCount++;
	if ((N1231BWriteRawPresetRegister	= (TFP_N1231BWPRE	)	GetProcAddress(hN1231B_API,"N1231BWriteRawPresetRegister")	) == NULL) NoFunctionCount++;
	if ((N1231BReadRawPresetRegister	= (TFP_N1231BAXPI64	)	GetProcAddress(hN1231B_API,"N1231BReadRawPresetRegister")	) == NULL) NoFunctionCount++;
	if ((N1231BWriteRegisterLong		= (TFP_N1231BWL		)	GetProcAddress(hN1231B_API,"N1231BWriteRegisterLong")		) == NULL) NoFunctionCount++;
	if ((N1231BReadRegisterLong			= (TFP_N1231BRL		)	GetProcAddress(hN1231B_API,"N1231BReadRegisterLong")		) == NULL) NoFunctionCount++;
	if ((N1231BWriteRegisterWord		= (TFP_N1231BWS		)	GetProcAddress(hN1231B_API,"N1231BWriteRegisterWord")		) == NULL) NoFunctionCount++;
	if ((N1231BReadRegisterWord			= (TFP_N1231BRS		)	GetProcAddress(hN1231B_API,"N1231BReadRegisterWord")		) == NULL) NoFunctionCount++;

	return (NoFunctionCount);
	}

void N1231B_FreeAPI(void)
	{
	if (hN1231B_API)
		{
		/* comment out any un-used functions if desired	*/
		N1231BOpen						= NULL;
		N1231BDefaultDevice				= NULL;
		N1231BClose						= NULL;
		N1231BFind						= NULL;
		N1231BPresetRaw					= NULL;
		N1231BPresetRawAll				= NULL;
		N1231BGetRawPosVel				= NULL;
		N1231BGetRawPosVelAll			= NULL;
		N1231BGetRawXSysSample			= NULL;
		N1231BGetRawXSysSampleAll		= NULL;
		N1231BGetRawXSysSampleAllArray	= NULL;
		N1231BGetRawXAxisSample			= NULL;
		N1231BGetRawXAxisSampleAll		= NULL;
		N1231BGetRawXAxisSampleAllArray	= NULL;
		N1231BGetRawXSampleAll			= NULL;
		N1231BGetRawXSampleAllArray		= NULL;
		N1231BClearStatusBits			= NULL;
		N1231BClearPathErrorAll			= NULL;
		N1231BClearStatusAll			= NULL;
		N1231BGetStatus					= NULL;
		N1231BSetInterruptMask			= NULL;
		N1231BGetInterruptMask			= NULL;
		N1231BSetConfig					= NULL;
		N1231BGetConfig					= NULL;
		N1231BSetGeLtDirections			= NULL;
		N1231BGetGeLtDirections			= NULL;
		N1231BSetGeLtThresholds			= NULL;
		N1231BGetGeLtThresholds			= NULL;
		N1231BGetGeLtStatus				= NULL;
		N1231BSetPDClockControl			= NULL;
		N1231BGetPDClockControl			= NULL;
		N1231BSetFilter					= NULL;
		N1231BGetFilter					= NULL;
		N1231BSetHdwIoSetup				= NULL;     // new rev 2.5
		N1231BGetHdwIoSetup				= NULL;     // new rev 2.5
		N1231BSyncPDClks				= NULL;     // new rev 2.5.1
		N1231BGetFPGARevs				= NULL;
		N1231BGetFPGAIds				= NULL;
		N1231BGetHdwRev					= NULL;
		N1231BGetLibraryRev				= NULL;
		N1231BGetErrStr					= NULL;
		N1231BpollReadSysPos32;			= NULL;     // new rev 2.6
		N1231BpollReadSysPosVel;		= NULL;     // new rev 2.6
		N1231BpollRead1AxisPos32;		= NULL;     // new rev 2.6
		N1231BpolltsReadSysPos32;		= NULL;     // new rev 2.6
		N1231BpolltsReadSysPosVel;		= NULL;     // new rev 2.6
		N1231BpollRead1AxisPosVel;		= NULL;     // new rev 2.6
		N1231BpolltsRead1AxisPos3;		= NULL;     // new rev 2.6
		N1231BpolltsRead1AxisPosVel		= NULL;     // new rev 2.6
		N1231BpolltsRead3AxisPosVel		= NULL;     // new rev 2.6
		N1231BpollRead3AxisPosVel;		= NULL;     // new rev 2.6
		N1231BSetGlobalInterruptEnable	= NULL;
		N1231BGetGlobalInterruptEnable	= NULL;
		N1231BPciInterruptEnable		= NULL;
		N1231BPciInterruptAttach		= NULL;
		N1231BPciInterruptDetach		= NULL;
		N1231BPciInterruptWait			= NULL;
		N1231BSamplePosVel				= NULL;
		N1231BReadRawPos				= NULL;
		N1231BReadRawVel				= NULL;
		N1231BWriteRawPresetRegister	= NULL;
		N1231BReadRawPresetRegister		= NULL;
		N1231BWriteRegisterLong			= NULL;
		N1231BReadRegisterLong			= NULL;
		N1231BWriteRegisterWord			= NULL;
		N1231BReadRegisterWord			= NULL;

		FreeLibrary(hN1231B_API);
		hN1231B_API = NULL;
		}
	}
#endif

#ifdef __cplusplus
}
#endif

#endif /* IFNDEF N1231B_DL_H */
