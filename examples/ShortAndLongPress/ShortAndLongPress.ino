#include "ShortAndLongPress.h"

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 2
#define LONG_PRESS_MS 350

#if BUTTON_PIN == LED_PIN
#error lol, no
#endif

ShortAndLongPress button( BUTTON_PIN, LONG_PRESS_MS, ShortAndLongPress::ACTIVE_LOW );

void shortPressHandler(  ) {
  // On short press, flash twice quick
  digitalWrite( LED_PIN, HIGH );
  delay(250);
  digitalWrite( LED_PIN, LOW );
  delay(250);
  digitalWrite( LED_PIN, HIGH );
  delay(250);
  digitalWrite( LED_PIN, LOW );
  delay(250);  
}
void longPressHandler(  ) {
  // On long press, flash once slow
  digitalWrite( LED_PIN, HIGH );
  delay(500);
  digitalWrite( LED_PIN, LOW );
  delay(500);
}

void setup() {

  pinMode( BUTTON_PIN, INPUT_PULLUP );

  button.setOnShortPress( shortPressHandler );
  button.setOnLongPress( longPressHandler );
  
  pinMode( LED_PIN, OUTPUT );
}

void loop() {
  button.tick( millis() ); // Must tick quite frequently or you may miss presses.
  delay(1);
}
