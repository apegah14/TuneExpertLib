// TuneExpertDataLib.h : Include file for standard system include files,
// or project specific include files.

#pragma once


#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef linux
	#include "TypesForN1231B.h"
	#include "WinTypes.h"
#endif

#include "N1231B.h"

#include <stdbool.h>

#define N1231B_CLOCK 20.0e6
#define LAMBDA_NM 632.99137
#define COMP_NUM 0.9997287
#define START_MM 50
#define MAX_MM 55
#define MIN_MM 45
#define FOLD 2

typedef struct {
    double dPCnvrt2um, dVCnvrt2umps;
    union { N1231B_INT64 s; long i64; } uAx1Pos, uAx2Pos, uAx3Pos;
    long iAx1Vel, iAx2Vel, iAx3Vel;
    unsigned int uiGeLtStatus;
    N1231B_RETURN rc1, rc2;
    unsigned short wValid;
} LASER_DATA;

typedef struct {
    double p1, p2, p3;
    double v1, v2, v3;
} PosVelSample;

void begin_read();
double read_ax1();
double read_ax2();
double read_ax3();
PosVelSample read_data_struct();
void read_data_pointer(double* pvs);

long test();
void open_device();
N1231B_RETURN check(N1231B_RETURN rc, bool bFatal, char* pMessag);
void setup_device(void);
void clear_pos_errors(void);
void reset_laser(void);
void PaintScreen(void);
void UpdateScreen(LASER_DATA* pLsrDta);