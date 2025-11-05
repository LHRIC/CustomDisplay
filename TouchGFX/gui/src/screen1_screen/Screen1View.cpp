#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/utils.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/Types.hpp>

extern "C" uint32_t HAL_GetTick(void);

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    //textArea1.setWildcard(textArea1Buffer);

    //initialize CAN value buffer pointers
    coolant.textAreaPtr = &CoolantValue;
    coolant.bufferPtr = CoolantValueBuffer;
    coolant.bufferSize = COOLANTVALUE_SIZE;

    throttle.textAreaPtr = &ThrottleValue;
    throttle.bufferPtr = ThrottleValueBuffer;
    throttle.bufferSize = THROTTLEVALUE_SIZE;

    battery.textAreaPtr = &BatteryValue;
    battery.bufferPtr = BatteryValueBuffer;
    battery.bufferSize = BATTERYVALUE_SIZE;

    gear.textAreaPtr = &GearValue;
    gear.bufferPtr = GearValueBuffer;
    gear.bufferSize = GEARVALUE_SIZE;

    lastMs = HAL_GetTick();
    frameCount = 0;
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent()
{
	Screen1ViewBase::handleTickEvent();

	    // Count how many frames (ticks that rendered) occur
	    frameCount++;

	    uint32_t now = HAL_GetTick();
	    uint32_t elapsed = now - lastMs;

	    // Update once per second
	    if (elapsed > 1000)
	    {
	        // Compute FPS over the last window (in seconds)
	        // Using ms -> seconds via (elapsed / 1000.0f)
	        float fps = (float)frameCount * 1000.0f / (float)elapsed;
	        //uint8_t fpsI = (uint8_t)fps;
	        Unicode::snprintfFloat(FPSCOUNTERBuffer, FPSCOUNTER_SIZE, "%3.1f", fps);
	        FPSCOUNTER.invalidateContent();   // redraw the label

	        // Reset window
	        frameCount = 0;
	        lastMs = now;
	    }
}


void Screen1View::updateDisplayValue(CAN_value_t* CAN_val)
{
    //Update text area or progress bar (make a case for anything with special functionality, default is for text)
	switch(CAN_val->valueIdentifier){
	case RPM://rpm progress bar
		imageProgress1.setValue(CAN_val->value.u16);
		imageProgress1.invalidate();
		break;
	default://text update
		//fill the buffer based on updated value
		CAN_value_updateTextBuffer(CAN_val);
		//invalidate text buffer
		CAN_val->textAreaPtr->invalidateContent();
		break;
	}

}
