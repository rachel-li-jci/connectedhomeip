#include <WatchdogManager.h>

WatchdogManager WatchdogManager::sWatchdog;

void WatchdogManager::InitWDOG()
{
    CMU_ClockEnable(cmuClock_HFLE, true);

    WDOG_Init_TypeDef wdogInit = WDOG_INIT_DEFAULT;
    wdogInit.debugRun = true;
    wdogInit.em3Run = true;
    wdogInit.clkSel = wdogClkSelULFRCO;
    wdogInit.perSel = wdogPeriod_2k;
    WDOG_Init(&wdogInit);
}

void WatchdogManager::KickWDOG()
{
    WDOG_Feed();
}

unsigned long WatchdogManager::getResetCause()
{
    resetCause = RMU_ResetCauseGet();
    RMU_ResetCauseClear();
    return resetCause;
}

// End of File