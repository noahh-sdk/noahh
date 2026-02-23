#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN
/**
 @js NA
 @lua NA
 */
class CC_DLL CCDevice
{
    NOAHH_FRIEND_MODIFY
private:


    CCDevice();
public:
    NOAHH_CUSTOM_CONSTRUCTOR_BEGIN(CCDevice)
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    static int getDPI();
};


NS_CC_END

#endif /* __CCDEVICE_H__ */

