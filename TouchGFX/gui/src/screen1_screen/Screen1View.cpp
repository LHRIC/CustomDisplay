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

void Screen1View::updateCanValue(uint16_t value)
{
    // Update text area or gauge
	counter = value;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", counter);
    textArea1.resizeToCurrentText(); // optional, will resize the box to fit the text if it is too small
    textArea1.invalidate();
}
