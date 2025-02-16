import math
import numpy as np
from Basilisk.architecture import messaging


def create_rw_lists():
    """
        Create RW lists containing Gs (spinning axis) data and Js (inertia) data
    """
    RWAGsMatrix = []
    RWAJsList = []
    wheelJs = 50.0 / (6000.0 / 60.0 * math.pi * 2.0) #check what this
    rwElAngle = 60 * math.pi / 180.0 #Eman: changed

    rwClockAngle = 225.0 * math.pi / 180.0 #rw1 in MBZ def (it was 45 for BSK)
    RWAJsList.extend([wheelJs])
    RWAGsMatrix.extend([
        math.sin(rwElAngle) * math.sin(rwClockAngle),
        math.sin(rwElAngle) * math.cos(rwClockAngle),
        -math.cos(rwElAngle)
    ])

    rwClockAngle -= 90.0 * math.pi / 180.0 #rw2 in MBZ def (it was +=90 for BSK)
    RWAJsList.extend([wheelJs])
    RWAGsMatrix.extend([math.sin(rwElAngle) * math.sin(rwClockAngle),
                        -math.sin(rwElAngle) * math.cos(rwClockAngle), math.cos(rwElAngle)])

    rwClockAngle -= 180.0 * math.pi / 180.0 #rw3 in MBZ def (it was +=180 for BSK)
    RWAJsList.extend([wheelJs])
    RWAGsMatrix.extend([math.sin(rwElAngle) * math.sin(rwClockAngle),
                        math.sin(rwElAngle) * math.cos(rwClockAngle), -math.cos(rwElAngle)])

    rwClockAngle += 90.0 * math.pi / 180.0 #rw1 in MBZ def (it was -=90 for BSK)
    RWAJsList.extend([wheelJs])
    RWAGsMatrix.extend([math.sin(rwElAngle) * math.sin(rwClockAngle),
                        -math.sin(rwElAngle) * math.cos(rwClockAngle), math.cos(rwElAngle)])
    return RWAGsMatrix, RWAJsList


def CreateRWAClass():
    """
        Create Dynamics RW class and initialize it
    """
    RWAGsMatrix, RWAJsList = create_rw_lists()
    rwClass = messaging.RWConstellationMsgPayload()
    rwPointerList = list()
    rwClass.numRW = 4
    i = 0
    while i < 4:
        rwPointer = messaging.RWConfigElementMsgPayload()
        rwPointer.gsHat_B = RWAGsMatrix[i * 3:i * 3 + 3]
        rwPointer.Js = RWAJsList[i]
        rwPointer.uMax = 0.2
        rwPointerList.append(rwPointer)
        i += 1
    rwClass.reactionWheels = rwPointerList
    return rwClass


def CreateRWAClassDyn():
    """
        Create FSW RW Config class and initialize it
    """
    RWAGsMatrix, RWAJsList = create_rw_lists()
    rwConfigData = messaging.RWArrayConfigMsgPayload()
    gsList = np.zeros(3 * messaging.MAX_EFF_CNT)
    gsList[0:3 * 3 + 3] = RWAGsMatrix[0:3 * 3 + 3]
    rwConfigData.GsMatrix_B = gsList
    jsList = np.zeros(messaging.MAX_EFF_CNT)
    jsList[0:4] = RWAJsList[0:4]
    rwConfigData.JsList = jsList
    rwConfigData.numRW = 4
    torqueMax = np.zeros(messaging.MAX_EFF_CNT)
    torqueMax[0:4] = [0.2] * 4
    rwConfigData.uMax = torqueMax
    return rwConfigData
