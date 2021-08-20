#ifndef WDOG_MANAGER_H_
#define WDOG_MANAGER_H_

#include <stdbool.h>
#include <stdint.h>

#include "em_gpio.h"
#include "em_device.h"
#include "em_wdog.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_rmu.h"
#include "em_chip.h"
#include "em_system.h"
#include "bspconfig.h"

class WatchdogManager {
public:
    void InitWDOG();
    void KickWDOG();
    unsigned long getResetCause();

private:
    friend WatchdogManager & WatchdogMgr(void);
    unsigned long resetCause;
    static WatchdogManager sWatchdog;
};

inline WatchdogManager & WatchdogMgr(void)
{
    return WatchdogManager::sWatchdog;
}

#endif