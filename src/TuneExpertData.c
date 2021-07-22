// TuneExpertData.c: Functions to output data from N1231B Laser Interferometer Board + some helpers
//

#include "TuneExpertData.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <memory.h>

N1231B_HANDLE hBrd = (N1231B_HANDLE)0;

LASER_DATA LsrData;

long test()
{
    return 9;
}

void open_device()
{
    N1231B_LOCATION sDevice;
    N1231BDefaultDevice(&sDevice);
    check(N1231BOpen(&sDevice, &hBrd, NULL), true, (char*)"Open Default Board");
    LsrData.dPCnvrt2um = LAMBDA_NM * COMP_NUM / (FOLD * 1024 * 1000);
    LsrData.dVCnvrt2umps = LsrData.dPCnvrt2um * N1231B_CLOCK / (4194304 / 1024);
    setup_device();
}

PosVelSample read_data_struct()
{
    PosVelSample pvs;

    LsrData.rc1 = N1231BGetRawPosVelAll(hBrd, &LsrData.uAx1Pos.s, &LsrData.iAx1Vel, &LsrData.uAx2Pos.s, &LsrData.iAx2Vel, &LsrData.uAx3Pos.s, &LsrData.iAx3Vel, &LsrData.wValid);

    pvs.p1 = LsrData.dPCnvrt2um * LsrData.uAx1Pos.i64 - START_MM * 1000;
    pvs.p2 = LsrData.dPCnvrt2um * LsrData.uAx2Pos.i64 - START_MM * 1000;
    pvs.p3 = LsrData.dPCnvrt2um * LsrData.uAx3Pos.i64 - START_MM * 1000;
    pvs.v1 = LsrData.dVCnvrt2umps * LsrData.iAx1Vel;
    pvs.v2 = LsrData.dVCnvrt2umps * LsrData.iAx2Vel;
    pvs.v3 = LsrData.dVCnvrt2umps * LsrData.iAx3Vel;
    return pvs;
}

void read_data_pointer(double* pvs)
{
    LsrData.rc1 = N1231BGetRawPosVelAll(hBrd, &LsrData.uAx1Pos.s, &LsrData.iAx1Vel, &LsrData.uAx2Pos.s, &LsrData.iAx2Vel, &LsrData.uAx3Pos.s, &LsrData.iAx3Vel, &LsrData.wValid);

    pvs[0] = LsrData.dPCnvrt2um * LsrData.uAx1Pos.i64 - START_MM * 1000;
    pvs[1] = LsrData.dPCnvrt2um * LsrData.uAx2Pos.i64 - START_MM * 1000;
    pvs[2] = LsrData.dPCnvrt2um * LsrData.uAx3Pos.i64 - START_MM * 1000;
}

void begin_read() {
    double sample = 0;
    LsrData.rc1 = N1231BGetRawPosVelAll(hBrd, &LsrData.uAx1Pos.s, &LsrData.iAx1Vel, &LsrData.uAx2Pos.s, &LsrData.iAx2Vel, &LsrData.uAx3Pos.s, &LsrData.iAx3Vel, &LsrData.wValid);
    LsrData.rc2 = N1231BGetGeLtStatus(hBrd, (unsigned long*)&LsrData.uiGeLtStatus);
}

double read_ax1()
{
    return LsrData.dPCnvrt2um * LsrData.uAx1Pos.i64 - START_MM * 1000;
}

double read_ax2()
{
    return LsrData.dPCnvrt2um * LsrData.uAx2Pos.i64 - START_MM * 1000;
}

double read_ax3()
{
    return LsrData.dPCnvrt2um * LsrData.uAx3Pos.i64 - START_MM * 1000;
}

void setup_device(void)
{
    union { N1231B_INT64 s; long i64; } uStart, uMax, uMin;

    uStart.i64 = START_MM * 1000000 / (LAMBDA_NM * COMP_NUM / (FOLD * 1024));
    uMax.i64 = MAX_MM * 1000000 / (LAMBDA_NM * COMP_NUM / (FOLD * 1024));
    uMin.i64 = MIN_MM * 1000000 / (LAMBDA_NM * COMP_NUM / (FOLD * 1024));

    check(N1231BPresetRawAll(hBrd, uStart.s, uStart.s, uStart.s, NULL), false, (char*)"Presetting Position Values");
    check(N1231BSetGeLtThresholds(hBrd, AXIS_1, uMax.s, uMin.s), false, (char*)"Setting Axis 1 Compare Thresholds");
    check(N1231BSetGeLtThresholds(hBrd, AXIS_2, uMax.s, uMin.s), false, (char*)"Setting Axis 2 Compare Thresholds");
    check(N1231BSetGeLtThresholds(hBrd, AXIS_3, uMax.s, uMin.s), false, (char*)"Setting Axis 3 Compare Thresholds");
    check(N1231BSetGeLtDirections(hBrd, 0), false, (char*)"Setting Compare Directions");
    check(N1231BSetConfig(hBrd, N1231B_BUS_MODE_DIRECT), false, (char*)"Setting Configuration");
    check(N1231BSetFilter(hBrd, N1231B_FILTER_ENB | N1231B_KP2 | N1231B_KV1), false, (char*)"Setting Filter");
    check(N1231BSetHdwIoSetup(hBrd, N1231B_HWIO_DISA1H | N1231B_HWIO_DISA2H | N1231B_HWIO_DISA3H), false, (char*)"Setting Hw IO Config");
}
void clear_pos_errors(void)
{
    check(N1231BClearPathErrorAll(hBrd, NULL), false, (char*)"Clearing Path Errors");
}

void reset_laser(void)
{
    union { N1231B_INT64 s; long i64; } uStart;
    uStart.i64 = START_MM * 1000000 / (LAMBDA_NM * COMP_NUM / (FOLD * 1024));

    check(N1231BPresetRawAll(hBrd, uStart.s, uStart.s, uStart.s, NULL), false, (char*)"Presetting Position Values");
}

void PaintScreen(void)
{
    printf("\033[3J\033[1;1H\033[0J");	// Clear Screen
    printf("\n\n\tn31bTest2 - Keysight N1231B Example Position Display Program - 3 May 2021\n\n");
    printf("   Axis 1:   Pos:                 um   Vel:            um/s   Cmpr:\n");
    printf("   Axis 2:   Pos:                 um   Vel:            um/s   Cmpr:\n");
    printf("   Axis 3:   Pos:                 um   Vel:            um/s   Cmpr:\n");
    printf("\n\n\n\n");
}

void UpdateScreen(LASER_DATA* pLsrDta)
{
    printf("\033[3J\033[1;1H\033[0J");
    long double pos1 = pLsrDta->dPCnvrt2um * pLsrDta->uAx1Pos.i64 - START_MM * 1000;
    printf("%Le\n", pos1);
}

N1231B_RETURN check(N1231B_RETURN rc, bool bFatal, char* pMessage)
{
    if (rc == N1231B_SUCCESS) return (0);

    printf("\033[12;1H\033[K");
    printf("%sError '%s' when %s%s\n",
        (bFatal ? "Fatal " : ""),
        N1231BGetErrStr(rc), pMessage,
        (bFatal ? "\n\tTerminating Program" : "")
    );

    if (bFatal)
    {
        if (hBrd) N1231BClose(&hBrd);
        exit(rc);
    }

    return (rc);
}