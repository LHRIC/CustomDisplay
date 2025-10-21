#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/utils.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/Types.hpp>
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
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateText(){

    // Get the Unicode text from the TextArea
//    const Unicode::UnicodeChar* text = textArea1.getTypedText().getText();
//
//    // Create a buffer for the UTF-8 (ASCII) version
//    uint8_t asciiBuffer[50];  // must be uint8_t, NOT char
//    memset(asciiBuffer, 0, sizeof(asciiBuffer));
//
//    // Convert Unicode to UTF-8
//    Unicode::toUTF8(text, asciiBuffer, sizeof(asciiBuffer));
//
//    // Print as a string (cast to char* for printf)
//    touchgfx_printf("Text content: %s\n", (char*)asciiBuffer);
	//char textArea1Buffer[10];
	//touchgfx_printf("%d", Unicode::strncpy(textArea1Buffer, "zoom", TEXTAREA1_SIZE));
//	counter++;
//	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", counter);
//	textArea1.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//	textArea1.invalidate();
}

void Screen1View::handleTickEvent()
{
    //Screen1ViewBase::handleTickEvent();     // Call superclass eventhandler
//    //tickCounter += 1;
//    if (tickCounter == 60)
//    {
//       //Screen1View::updateText();
//       tickCounter = 0;
//    }
}

void Screen1View::updateCanValue(CAN_value_t CAN_val)
{
    //Update text area or progress bar (make a case for anything with special functionality, default is for text)
	switch(CAN_val.valueIdentifier){
	case RPM://rpm progress bar
		imageProgress1.setValue(CAN_val.value.u16);
		imageProgress1.invalidate();
		break;
//	case THROTTLE:
//		Unicode::snprintfFloat(ThrottleValueBuffer, THROTTLEVALUE_SIZE, "%4.1f", CAN_val.value.f);
//		//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//		ThrottleValue.invalidate();
//		break;
//	case COOLANT:
//	    Unicode::snprintf(CoolantValueBuffer, COOLANTVALUE_SIZE, "%u", CAN_val.value.u16);
//	    //CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//	    CoolantValue.invalidate();
//		break;
//	case BATTERY:
//		Unicode::snprintfFloat(BatteryValueBuffer, BATTERYVALUE_SIZE, "%4.1f", CAN_val.value.f);
//		//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//		BatteryValue.invalidate();
//		break;
//	case GEAR://can be -1
//			Unicode::snprintf(GearValueBuffer, GEARVALUE_SIZE, "%d", CAN_val.value.i8);
//			//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//			GearValue.invalidate();
	default://text update
		//fill the buffer based on
		switch(CAN_val.type){
		case CAN_TYPE_FLOAT16:
			Unicode::snprintfFloat(CAN_val.bufferPtr, CAN_val.bufferSize, "%4.1f", CAN_val.value.f);
			break;
		case CAN_TYPE_INT8:
			Unicode::snprintf(CAN_val.bufferPtr, CAN_val.bufferSize, "%d", CAN_val.value.i8);
			break;
		case CAN_TYPE_UINT16:
			Unicode::snprintf(CAN_val.bufferPtr, CAN_val.bufferSize, "%u", CAN_val.value.u16);
			break;
		}
		CAN_val.textAreaPtr->invalidate();
		break;
	}

}
