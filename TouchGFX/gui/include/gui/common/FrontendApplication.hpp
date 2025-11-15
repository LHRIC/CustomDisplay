#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include "gpio_flags.hpp"

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }
    virtual void handleTickEvent()
    {
        static bool onScreen1 = true;

        if (uartRequestScreenChange)
        {
            if (onScreen1)
                gotoDiagnosticsScreenNoTransition();
            else
                gotoScreen1ScreenNoTransition();

            onScreen1 = !onScreen1;
            uartRequestScreenChange = false;
        }
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
private:
};

#endif // FRONTENDAPPLICATION_HPP
