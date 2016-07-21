/*
Copyright (c) 2016, Autonomous Vehicle Systems Lab, Univeristy of Colorado at Boulder

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#ifndef _MRP_PD_CONTROL_H_
#define _MRP_PD_CONTROL_H_

#include "messaging/static_messaging.h"
#include "../_GeneralModuleFiles/vehControlOut.h"
#include "effectorInterfaces/errorConversion/vehEffectorOut.h"
#include <stdint.h>

/*! \addtogroup ADCSAlgGroup
 * @{
 */

/*! @brief Top level structure for the MRP Steering attitude control routine. */
typedef struct {
    /* declare module private variables */
    double K;                           /*!< [rad/sec] Proportional gain applied to MRP errors */
    double P;                           /*!< [N*m*s]   Rate error feedback gain applied  */
    double GsMatrix[3*MAX_EFF_CNT];     /*!< []        The spin axis matrix used for RWAs*/
    double JsList[3*MAX_EFF_CNT];       /*!< [kgm2]    The spin axis inertia for RWAs*/
    uint32_t numRWAs;                   /*!< []        The number of reaction wheels available on vehicle */

    /* declare module IO interfaces */
    char outputDataName[MAX_STAT_MSG_LENGTH];               /*!< The name of the output message*/
    int32_t outputMsgID;                                    /*!< [] ID for the outgoing body accel requests*/
    char inputGuidName[MAX_STAT_MSG_LENGTH];                /*!< The name of the Input message*/
    int32_t inputGuidID;                                    /*!< [] ID for the incoming guidance errors*/
    char inputVehicleConfigDataName[MAX_STAT_MSG_LENGTH];   /*!< The name of the Input message*/
    int32_t inputVehicleConfigDataID;                       /*!< [] ID for the incoming static vehicle data */
    char inputRWSpeedsName[MAX_STAT_MSG_LENGTH];/*!< [] The name for the reaction wheel speeds message */
    int32_t inputRWSpeedsID;                    /*!< [] The ID for the reaction wheel speeds message*/
    char inputRWConfigData[MAX_STAT_MSG_LENGTH]; /*!< [-] The name of the RWA configuration message*/
    int32_t inputRWConfID;      /*!< [-] ID for the incoming RWA configuration data*/
    
    vehControlOut controlOut;                               /*!< [] Control output requests */
}MRP_PDConfig;

#ifdef __cplusplus
extern "C" {
#endif
    
    void SelfInit_MRP_PD(MRP_PDConfig *ConfigData, uint64_t moduleID);
    void CrossInit_MRP_PD(MRP_PDConfig *ConfigData, uint64_t moduleID);
    void Update_MRP_PD(MRP_PDConfig *ConfigData, uint64_t callTime, uint64_t moduleID);
    void Reset_MRP_PD(MRP_PDConfig *ConfigData, uint64_t callTime, uint64_t moduleID);
    
#ifdef __cplusplus
}
#endif

/*! @} */

#endif