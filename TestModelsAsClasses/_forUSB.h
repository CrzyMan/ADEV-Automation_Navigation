#ifndef _FORUSBH
#define _FORUSBH

/**
 * DISCLAIMER:
 * This code was not initially writen or majorly editted by the Rose-Hulman 2016-2017 ADEV Automation Navigation team
 * The code is owned by the contributers to the GitHub repository, https://github.com/felis/USB_Host_Sheild_2.0
 */

// Libraries for the USB
#include <cdcacm.h>
#include <usbhub.h>

// Class used by the USB
class ACMAsyncOper : public CDCAsyncOper
{
public:
    uint8_t OnInit(ACM *pacm);
};

// Setting the initializer for the helper class
uint8_t ACMAsyncOper::OnInit(ACM *pacm)
{
    uint8_t rcode;
    // Set DTR = 1 RTS=1
    rcode = pacm->SetControlLineState(3);

    if (rcode)
    {
        ErrorMessage<uint8_t>(PSTR("SetControlLineState"), rcode);
        return rcode;
    }

    LINE_CODING  lc;
    lc.dwDTERate  = 115200;
    lc.bCharFormat  = 0;
    lc.bParityType  = 0;
    lc.bDataBits  = 8;

    rcode = pacm->SetLineCoding(&lc);

    if (rcode)
        ErrorMessage<uint8_t>(PSTR("SetLineCoding"), rcode);

    return rcode;
}

// The USB used to get information for the LIDAR system
USB     Usb;

// Helper class
ACMAsyncOper  AsyncOper;

// ACM is basically the communication protocol for the USB
// It is who we ask to get the information from
ACM           Acm(&Usb, &AsyncOper);

#endif // _FORUSBH
