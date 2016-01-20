
#include "attGuidance/attRefGen/attRefGen.h"
#include "SimCode/utilities/linearAlgebra.h"
#include "SimCode/utilities/rigidBodyKinematics.h"
#include "sensorInterfaces/IMUSensorData/imuComm.h"
#include <string.h>
#include <math.h>

/*! This method initializes the ConfigData for the nominal attitude maneuver guidance.
 It checks to ensure that the inputs are sane and then creates the
 output message
 @return void
 @param ConfigData The configuration data associated with the attitude maneuver guidance
 */
void SelfInit_attRefGen(attRefGenConfig *ConfigData, uint64_t moduleID)
{
    
    /*! Begin method steps */
    /*! - Create output message for module */
    ConfigData->outputMsgID = CreateNewMessage(ConfigData->outputDataName,
        sizeof(attGuidOut), "attGuidOut", moduleID);
    return;
    
}

/*! This method performs the second stage of initialization for the attitude maneuver
 interface.  It's primary function is to link the input messages that were
 created elsewhere.
 @return void
 @param ConfigData The configuration data associated with the attitude maneuver guidance
 */
void CrossInit_attRefGen(attRefGenConfig *ConfigData, uint64_t moduleID)
{
    /*! - Find the input IDs for each input message*/
    ConfigData->inputNavID = subscribeToMessage(ConfigData->inputNavStateName,
        sizeof(NavStateOut), moduleID);
    ConfigData->inputCmdID = subscribeToMessage(ConfigData->inputAttCmdName,
        sizeof(attCmdOut), moduleID);
    return;
    
}

/*! This method resets the reference generation algorithm back to a pristine 
    state so that the algorithm is primed to begin computing a new reference 
	for the vehicle to follow
	@return void
	@param ConfigData The configuration data associated with the attitude maneuver guidance
	@param moduleID The module ID associated with this instance of the algorithm
*/
void Reset_attRefGen(attRefGenConfig *ConfigData, uint64_t moduleID)
{
	ConfigData->mnvrActive = 0;
}

/*! This method takes the estimated state and commanded attitude and computes the
 current attitude/attitude rate errors to pass on to control.
 @return void
 @param ConfigData The configuration data associated with the attitude maneuver guidance
 @param callTime The clock time at which the function was called (nanoseconds)
 */
void Update_attRefGen(attRefGenConfig *ConfigData, uint64_t callTime,
    uint64_t moduleID)
{
    attCmdOut localCmd;
    NavStateOut localState;
    uint64_t clockTime;
    uint32_t readSize;
	double prvUse_BcBf[3];
    double MRP_BcBf[3];
	double propDT;

    
    memset(&localCmd, 0x0, sizeof(attCmdOut));
    memset(&localState, 0x0, sizeof(NavStateOut));
	memset(&(ConfigData->attOut), 0x0, sizeof(attGuidOut));
    
    ReadMessage(ConfigData->inputNavID, &clockTime, &readSize,
                sizeof(NavStateOut), (void*) &(localState));
    ReadMessage(ConfigData->inputCmdID, &clockTime, &readSize,
                sizeof(attCmdOut), (void*) &(localCmd));
    
    if(ConfigData->mnvrActive != 1)
    {
		ConfigData->startClockRead = callTime;
		ConfigData->mnvrActive = 1;
    }
    ConfigData->mnvrComplete = 0;

	ConfigData->currMnvrTime = (callTime*1.0E-9 -
		ConfigData->startClockRead*1.0E-9);
    propDT = ConfigData->propagateReference == 0 ? 0.0 :
        ConfigData->currMnvrTime - ConfigData->totalMnvrTime;

	v3Scale(propDT, ConfigData->mnvrScanRate, prvUse_BcBf);
	PRV2MRP(prvUse_BcBf, MRP_BcBf);

	addMRP(localCmd.sigma_BR, MRP_BcBf, ConfigData->sigmaCmd_BR);
	v3Scale(-1.0, ConfigData->sigmaCmd_BR, ConfigData->sigmaCmd_BR);
	addMRP(ConfigData->sigmaCmd_BR, localState.sigma_BN,
		ConfigData->attOut.sigma_BR);
	MRPswitch(ConfigData->attOut.sigma_BR, 1.0, ConfigData->attOut.sigma_BR);
	if (ConfigData->currMnvrTime >= ConfigData->totalMnvrTime)
	{
		ConfigData->mnvrComplete = 1;
	}
	v3Add(localCmd.omega_BR, ConfigData->mnvrScanRate,
        ConfigData->omegaCmd_BR_B);
	v3Subtract(localState.omega_BN_B, ConfigData->omegaCmd_BR_B,
		ConfigData->attOut.omega_BR_B);
    
    WriteMessage(ConfigData->outputMsgID, callTime, sizeof(attGuidOut),
        (void*)&(ConfigData->attOut), moduleID);
    
    return;
}
