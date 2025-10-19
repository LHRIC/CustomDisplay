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
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

int counter = 0;
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
    Screen1ViewBase::handleTickEvent();     // Call superclass eventhandler
//    //tickCounter += 1;
//    if (tickCounter == 60)
//    {
//       //Screen1View::updateText();
//       tickCounter = 0;
//    }
}

void Screen1View::updateCanValue(uint16_t value, uint8_t assigner)
{
    // Update text area or gauge
	switch(assigner){
	case 0://rpm progress bar
		imageProgress1.setValue(value);
		imageProgress1.invalidate();
		break;
	case 1:
		Unicode::snprintfFloat(ThrottleValueBuffer, THROTTLEVALUE_SIZE, "%4.1f", value / 10.0);
		//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
		ThrottleValue.invalidate();
		break;
	case 2:
	    Unicode::snprintf(CoolantValueBuffer, COOLANTVALUE_SIZE, "%u", value);
	    //CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
	    CoolantValue.invalidate();
		break;
	case 3:
		Unicode::snprintfFloat(BatteryValueBuffer, BATTERYVALUE_SIZE, "%4.1f", value / 10.0);
		//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
		BatteryValue.invalidate();
		break;
	case 4:
		if(value > 10){//must be negative (-1) because our int8_t got casted due to poor design :(
			Unicode::snprintf(GearValueBuffer, GEARVALUE_SIZE, "%s", "-");
			//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
			GearValue.invalidate();
		}
		else{//positive
			Unicode::snprintf(GearValueBuffer, GEARVALUE_SIZE, "%d", value);
			//CoolantValue.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
			GearValue.invalidate();
		}
		break;
//	default://test values
//		Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", value);
//		//textArea1.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
//		textArea1.invalidate();
//		break;
	}

}
