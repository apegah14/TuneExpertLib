/*
 * Copyright 2018 by Keysight Technologies
 *
 * File Name: N1231B_reg.h
 *
 * Header file providing register map for the 
 * Keysight Technologies N1231B PCI Three-Axis Board
 * designed for use with an Keysight Technologies
 * laser interferometry position measurement system.
 *
 * Last revision of this file: 
 *   26 Aug 2004
 *   08 Nov 2014
 *   30 Mar 2018
 */ 
#ifndef N1231B_REG_H
#define N1231B_REG_H

/*
 *******************************************************************************
 *******************************************************************************
 *
 * REGISTER MAP OF N1231B
 *
 *******************************************************************************
 *	Used for direct register access. 
 *	These constants represent the offset from PCI BAR 2.
 *
 *	If using the N1231B API library, these constants are used with functions:
 *		N1231BReadRegisterLong()
 *		N1231BWriteRegisterLong()
 *		N1231BReadRegisterWord()
 *		N1231BWriteRegisterWord()
 *
 *      Constant Name					Addr	 BitMap Size ReadOrWrite	
 */
#define N1231B_OFST_POS1_SWS			0x0100	/*		long read			*/
#define N1231B_OFST_POS1_AXS			0x0104	/*		long read			*/
#define N1231B_OFST_POS1_SYS			0x0108	/*		long read			*/

#define N1231B_OFST_POS2_SWS			0x0110	/*		long read			*/
#define N1231B_OFST_POS2_AXS			0x0114	/*		long read			*/
#define N1231B_OFST_POS2_SYS			0x0118	/*		long read			*/

#define N1231B_OFST_POS3_SWS			0x0000	/*		long read			*/
#define N1231B_OFST_POS3_AXS			0x0004	/*		long read			*/
#define N1231B_OFST_POS3_SYS			0x0008	/*		long read			*/

#define N1231B_OFST_POS12_SWS_HI		0x010c  /* bmL2 word read*			*/
#define N1231B_OFST_POS12_AXS_HI		0x010e  /* bmM2 word read			*/
#define N1231B_OFST_POS12_SYS_HI		0x011c	/* bmN2 word read			*/
#define N1231B_OFST_POS3_SWS_HI			0x000c  /* bmL1 word read*			*/
#define N1231B_OFST_POS3_AXS_HI			0x000e  /* bmM1 word read			*/
#define N1231B_OFST_POS3_SYS_HI			0x001c	/* bmN1 word read			*/

#define N1231B_OFST_VEL1_SWS			0x0138	/*		long read			*/
#define N1231B_OFST_VEL1_AXS			0x013c	/*		long read			*/
#define N1231B_OFST_VEL1_SYS			0x0140	/*		long read			*/

#define N1231B_OFST_VEL2_SWS			0x0144	/*		long read			*/
#define N1231B_OFST_VEL2_AXS			0x0148	/*		long read			*/
#define N1231B_OFST_VEL2_SYS			0x014c	/*		long read			*/

#define N1231B_OFST_VEL3_SWS			0x0038	/*		long read			*/
#define N1231B_OFST_VEL3_AXS			0x003c	/*		long read			*/
#define N1231B_OFST_VEL3_SYS			0x0040	/*		long read			*/

#define N1231B_OFST_PRESET1				0x0150	/*		long read/write		*/
#define N1231B_OFST_PRESET2				0x0160	/*		long read/write		*/
#define N1231B_OFST_PRESET3A			0x0070	/*		long read/write		*/
#define N1231B_OFST_PRESET3B			0x0170	/*		long read/write		*/

#define N1231B_OFST_GE_TH1				0x0154	/*		long read/write		*/
#define N1231B_OFST_GE_TH2				0x0164	/*		long read/write		*/
#define N1231B_OFST_GE_TH3A				0x0074	/*		long read/write		*/
#define N1231B_OFST_GE_TH3B				0x0174	/*		long read/write		*/

#define N1231B_OFST_LT_TH1				0x0158	/*		long read/write		*/
#define N1231B_OFST_LT_TH2				0x0168	/*		long read/write		*/
#define N1231B_OFST_LT_TH3A				0x0078	/*		long read/write		*/
#define N1231B_OFST_LT_TH3B 			0x0178	/*		long read/write		*/

#define N1231B_OFST_PRESET1_HI			0x015c	/* bmO1 word read/write*	*/
#define N1231B_OFST_THRESH1_HI			0x015e	/* bmP1 word read/write		*/

#define N1231B_OFST_PRESET2_HI			0x016c	/* bmO2 word read/write*	*/
#define N1231B_OFST_THRESH2_HI			0x016e	/* bmP2 word read/write		*/

#define N1231B_OFST_PRESET3A_HI			0x007c	/* bmO3 word read/write*	*/
#define N1231B_OFST_THRESH3A_HI			0x007e	/* bmP3 word read/write		*/

#define N1231B_OFST_PRESET3B_HI			0x017c	/* bmO3 word read/write*	*/
#define N1231B_OFST_THRESH3B_HI			0x017e	/* bmP3 word read/write		*/

#define N1231B_OFST_CONFIG_3A			0x0020	/* bmD1 word read/write		*/
#define N1231B_OFST_CONFIG_123B			0x0120	/* bmD2 word read/write		*/

#define N1231B_OFST_CONFIG_CMP_3A		0x0028	/* bmG1 word read/write		*/
#define N1231B_OFST_CONFIG_CMP_123B		0x0128	/* bmG2 word read/write		*/

#define N1231B_OFST_STATE_CMP_3A		0x002A	/* bmI1 word read			*/
#define N1231B_OFST_STATE_CMP_123B		0x012A	/* bmI2 word read			*/

#define N1231B_OFST_VALID3				0x0022	/* bmH1 word read			*/
#define N1231B_OFST_VALID12				0x0122	/* bmH2 word read			*/

#define N1231B_OFST_CHN_STATUS			0x0026	/* bmF1 word read/write		*/
#define N1231B_OFST_CMP_STATUS			0x0126	/* bmF2 word read/write		*/

#define N1231B_OFST_CHN_INTRMASK		0x0024	/* bmE1 word read/write		*/
#define N1231B_OFST_CMP_INTRMASK		0x0124	/* bmE2 word read/write		*/

#define N1231B_OFST_FILTER				0x0014	/* bmC  word read/write		*/
#define N1231B_OFST_HWIOSU              0x0016  /* bmQ  word read/write new */
#define N1231B_OFST_SAMPLE_PRESET		0x0010	/* bmA  word write			*/
#define N1231B_OFST_GLOBAL_INTR_ENB		0X0012	/* bmB  word read/write		*/

#define N1231B_OFST_FPGA1_REV			0x002c	/*		long read			*/
#define N1231B_OFST_FPGA2_REV			0x012c	/*		long read			*/
#define N1231B_OFST_FPGA1_ID			0x0030	/*		long read			*/
#define N1231B_OFST_FPGA2_ID			0x0130	/*		long read			*/

#define N1231B_OFST_CLK1_DIV			0x0034	/* bmK1	word read/write*	*/
#define N1231B_OFST_CLK1_MODE			0x0036	/* bmJ1	word read/write		*/
#define N1231B_OFST_CLK1_PHSOFST		0x0018	/*      word read/write new */
#define N1231B_OFST_CLK2_DIV			0x0134	/* bmK2	word read/write*	*/
#define N1231B_OFST_CLK2_MODE			0x0136	/* bmJ2	word read/write		*/

/*
 * NOTES to above address map:
 *   read*        = Can read from this and the following address as one 32-bit operation 
 *   read/write*  = Can read or write to this and following address as one 32-bit operation 
 */

/*
 *******************************************************************************
 *******************************************************************************
 *
 * BIT MAPS
 *
 *******************************************************************************
 *******************************************************************************
 */

/*
 * Sample & Preset (Bitmap A)
 *	For use with:
 *		N1231B_OFST_SAMPLE_PRESET  (word write)
 */
#define N1231B_PRESET_1		0x0001
#define N1231B_SAMPLE_1		0x0002
#define N1231B_PRESET_2		0x0010
#define N1231B_SAMPLE_2		0x0020
#define N1231B_PRESET_3		0x0100
#define N1231B_SAMPLE_3		0x0200
#define N1231B_CLK_SYNC		0x8000

/*
 * Global Interrupt Enable (Bitmap B)
 *	For use with:
 *		N1231B_OFST_GLOBAL_INTR_ENB  (word read/write)
 */
#define N1231B_IRQ_ENB		0x1000
#define N1231B_IRQ_DISABLE	0x0000

/*
 * Filter Settings (Bitmap C)
 *	For use with:
 *		N1231B_OFST_FILTER  (word read/write)
 *
 *	new *XCLD_A* bits exclude specified axis errors from system error hardware output
 */
#define N1231B_FILTER_ENB	0X0010

#define N1231B_KP0			0x0000
#define N1231B_KP1			0x0001
#define	N1231B_KP2			0x0002
#define N1231B_KP3			0x0003

#define N1231B_KV0			0x0000
#define N1231B_KV1			0x0004
#define N1231B_KV2			0x0008
#define N1231B_KV3			0x000C

#define N1231B_XCLD_A1		0x1000		/* new in FPGA rev '0003 */
#define N1231B_XCLD_A2		0x2000		/* new in FPGA rev '0003 */
#define N1231B_XCLD_A3		0x4000		/* new in FPGA rev '0003 */

/*
 * Control/Setup (Bitmap D)
 *	For use with:
 *	The 16 msb are for use with
 *		N1231B_OFST_CONFIG_3A    (word read/write)
 *	The 16 lsb are for use with
 *		N1231B_OFST_CONFIG_123B  (word read/write) 
 */
#define	N1231B_DIRECTION_MINUS_1	0x00000008 
#define	N1231B_DIRECTION_MINUS_2	0x00000080 
#define	N1231B_DIRECTION_MINUS_3	0x00000800 

#define N1231B_LT_OUT_POS_TRUE_1	0x00000001 
#define N1231B_LT_OUT_POS_TRUE_2	0x00000010 
#define N1231B_LT_OUT_POS_TRUE_3A	0x01000000
#define N1231B_LT_OUT_POS_TRUE_3B	0x00000100 

#define N1231B_GE_OUT_POS_TRUE_1	0x00000002 
#define N1231B_GE_OUT_POS_TRUE_2	0x00000020 
#define N1231B_GE_OUT_POS_TRUE_3A	0x02000000
#define N1231B_GE_OUT_POS_TRUE_3B	0x00000200

#define	N1231B_THRESH_OUT_LVTTL_1	0x00000004 
#define	N1231B_THRESH_OUT_LVTTL_2	0x00000040 
#define	N1231B_THRESH_OUT_LVTTL_3A	0x04000000
#define	N1231B_THRESH_OUT_LVTTL_3B	0x00000400 

#define N1231B_BASE_ADDR_0			0x00000000
#define N1231B_BASE_ADDR_1			0x00001000
#define N1231B_BASE_ADDR_2			0x00002000
#define N1231B_BASE_ADDR_3			0x00003000

#define N1231B_BUS_MODE_DIRECT		0x00004000
#define N1231B_A3_TIME_ADJUST       0x80000000

/*
 * Interrupt Mask  (Bitmap E)
 * Status Register (Bitmap F)
 *	The 16 msb are for use with
 *		N1231B_OFST_CHN_INTRMASK  (word read/write)
 *		N1231B_OFST_CHN_STATUS	  (word read/write)
 *  The 16 lsb are for use with
 *		N1231B_OFST_CMP_INTRMASK  (word read/write)
 *		N1231B_OFST_CMP_STATUS    (word read/write)
 */
#define N1231B_NO_SIG_1					0x00010000
#define N1231B_GLITCH_1					0x00020000
#define N1231B_AXIS_SAMPLE_DATA_RDY_1	0x00000004  /* Read Only */
#define N1231B_AXIS_SAMPLE_OVERRUN_1	0x00000008
#define N1231B_LT_ALERT_1				0x00000001
#define N1231B_GE_ALERT_1				0x00000002

#define N1231B_NO_SIG_2					0x00100000
#define N1231B_GLITCH_2					0x00200000
#define N1231B_AXIS_SAMPLE_DATA_RDY_2	0x00000040  /* Read Only */
#define N1231B_AXIS_SAMPLE_OVERRUN_2	0x00000080
#define N1231B_LT_ALERT_2				0x00000010
#define N1231B_GE_ALERT_2				0x00000020

#define N1231B_NO_SIG_3					0x01000000
#define N1231B_GLITCH_3					0x02000000
#define N1231B_AXIS_SAMPLE_DATA_RDY_3	0x04000000	/* Read Only */
#define N1231B_AXIS_SAMPLE_OVERRUN_3	0x08000000
#define N1231B_LT_ALERT_3A				0x40000000
#define N1231B_GE_ALERT_3A				0x80000000
#define N1231B_LT_ALERT_3B				0x00000100
#define N1231B_GE_ALERT_3B				0x00000200

#define N1231B_NO_SIG_REF				0x10000000
#define N1231B_GLITCH_REF				0x20000000

#define N1231B_SYS_SAMPLE_DATA_RDY		0x00004000	/* Read Only */
#define N1231B_SYS_SAMPLE_OVERRUN		0x00008000

#define N1231B_PATH_ERRORS  ( N1231B_NO_SIG_1   \
							| N1231B_GLITCH_1   \
							| N1231B_NO_SIG_2   \
							| N1231B_GLITCH_2   \
							| N1231B_NO_SIG_3   \
							| N1231B_GLITCH_3   \
							| N1231B_NO_SIG_REF \
							| N1231B_GLITCH_REF )

#define N1231B_PATH_ERROR_1 ( N1231B_NO_SIG_1   \
							| N1231B_GLITCH_1   \
							| N1231B_NO_SIG_REF \
							| N1231B_GLITCH_REF )

#define N1231B_PATH_ERROR_2 ( N1231B_NO_SIG_2   \
							| N1231B_GLITCH_2   \
							| N1231B_NO_SIG_REF \
							| N1231B_GLITCH_REF )

#define N1231B_PATH_ERROR_3 ( N1231B_NO_SIG_3   \
							| N1231B_GLITCH_3   \
							| N1231B_NO_SIG_REF \
							| N1231B_GLITCH_REF )

/*
 * GE/LT Alert Direction Select (Bitmap G)
 *	The 16 msb are for use with
 *		N1231B_OFST_CONFIG_CMP_3A    (word read/write)
 *	The 16 lsb are for use with
 *		N1231B_OFST_CONFIG_CMP_123B	 (word read/write) 
 */
#define N1231B_LT_ALERT_WHEN_GOES_FALSE_1	0x00000001 
#define N1231B_GE_ALERT_WHEN_GOES_FALSE_1	0x00000002

#define N1231B_LT_ALERT_WHEN_GOES_FALSE_2	0x00000010
#define N1231B_GE_ALERT_WHEN_GOES_FALSE_2	0x00000020

#define N1231B_LT_ALERT_WHEN_GOES_FALSE_3A	0x40000000 
#define N1231B_GE_ALERT_WHEN_GOES_FALSE_3A	0x80000000 
#define N1231B_LT_ALERT_WHEN_GOES_FALSE_3B	0x00000100
#define N1231B_GE_ALERT_WHEN_GOES_FALSE_3B	0x00000200

/*
 * Sample Valid (Bitmap H)
 *	Used with:
 *		N1231B_OFST_VALID3  (word read)
 *		N1231B_OFST_VALID12 (word read)
 */
#define N1231B_ERR_1				0x0001
#define N1231B_SW_SAMPLE_VALID_1	0x0002
#define N1231B_AXIS_SAMPLE_VALID_1	0x0004
#define N1231B_SYS_SAMPLE_VALID_1	0x0008

#define N1231B_ERR_2				0x0010
#define N1231B_SW_SAMPLE_VALID_2	0x0020
#define N1231B_AXIS_SAMPLE_VALID_2	0x0040
#define N1231B_SYS_SAMPLE_VALID_2	0x0080

#define N1231B_ERR_3				0x0100
#define N1231B_SW_SAMPLE_VALID_3	0x0200
#define N1231B_AXIS_SAMPLE_VALID_3	0x0400
#define N1231B_SYS_SAMPLE_VALID_3	0x0800

/*
 * GE/LT Current State (Bitmap I)
 *	The 16 msb are for use with
 *		N1231B_OFST_STATE_CMP_3A   (word read)
 *	The 16 lsb are for use with
 *		N1231B_OFST_STATE_CMP_123B (word read)
 */
#define N1231B_LT_TRUE_1		0x00000001
#define N1231B_GE_TRUE_1		0x00000002

#define N1231B_LT_TRUE_2		0x00000010
#define N1231B_GE_TRUE_2		0x00000020

#define N1231B_LT_TRUE_3A		0x40000000
#define N1231B_GE_TRUE_3A		0x80000000
#define N1231B_LT_TRUE_3B		0x00000100
#define N1231B_GE_TRUE_3B		0x00000200

/*
 * Data Clock Control (Bitmap J)
 *	For use with:
 *		N1231B_OFST_CLK1_MODE  (word read/write)
 *		N1231B_OFST_CLK2_MODE  (word read/write)
 *	NOTE: Width goes in bits 0:7.
 *
 *	New bit (CLK1 only) selects a 20 KHz clock to generate PD Clock instead
 *		of the 20 MHz clock, allowing clock frequencies down to
 *		0.305 Hz and pulse widths up to 12.75 ms
 */
#define N1231B_PDCLK_ON					0x0100
#define N1231B_PDCLK_20MHZ				0x0200
#define N1231B_PDCLK_POLARITY_HIGH		0x0400
#define N1231B_PDCLK_SEL20KHZCLK		0x1000	/* new in FPGA1 rev '0003 */

/*
 * Status Bits with HI Position Data
 * Upper Bits -- Software Sample (Bitmap L)
 * Upper Bits -- Axis Sample     (Bitmap M)
 * Upper Bits -- System Sample   (Bitmap N)
 *
 *	For use with the "Valid" word returned by some 
 *    data read functions.
 *  In addition, the Axis 1 and 2 constants can be used with:
 *		N1231B_OFST_POS12_SWS_HI  (word read)
 *		N1231B_OFST_POS12_AXS_HI  (word read)
 *		N1231B_OFST_POS12_SYS_HI  (word read)
 *  and the Axis 3 and SYSERR constants can be used with:
 *		N1231B_OFST_POS3_SWS_HI  (word read)
 *		N1231B_OFST_POS3_AXS_HI  (word read)
 *		N1231B_OFST_POS3_SYS_HI	 (word read)
 */
#define N1231B_VALID_1					0x1000
#define N1231B_VALID_2					0x2000
#define N1231B_VALID_3					0x4000
#define N1231B_SYSERR					0x8000
#define N1231B_UPPER_1					0x000f
#define N1231B_UPPER_2					0x00f0
#define N1231B_UPPER_3					0x0f00

/*
 * Hardware Setup (Bitmap Q) - new in FPGA rev '0003
 *
 * For use with:
 *		N1231B_OFST_HWIOSU		(word read/write)
 *
 * New HW IO operation controlled by register
 *	DIS*	- Disables HOLD input signals so HW Pos output operates with no connection to hold line
 */

#define N1231B_HWIO_DISA1H			0x0010	/* new in FPGA rev '0003 */
#define N1231B_HWIO_DISA2H			0x0020	/* new in FPGA rev '0003 */
#define N1231B_HWIO_DISA3H			0x0040	/* new in FPGA rev '0003 */
#define N1231B_HWIO_DISSYSH			0x0080	/* new in FPGA rev '0003 */

#endif /* ifndef N1231B_REG_H */
