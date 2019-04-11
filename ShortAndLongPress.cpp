#include <Arduino.h>
#include "ShortAndLongPress.h"

ShortAndLongPress::ShortAndLongPress( int pin, uint32_t long_click_ms, uint8_t active )
{
  _state = ShortAndLongPress::QUIESCENT;
  _long_click_ms = long_click_ms;
  _pin = pin;
  _active=active;
  _OnButtonDown = null;
  _OnShortPress = null;
  _OnLongPress = null;
}

void
ShortAndLongPress::tick( uint32_t now_time )
{
  bool pushed = digitalRead( _pin ) ^ _active; 
  
  switch ( _state )
  {
    case ShortAndLongPress::QUIESCENT:
      if ( pushed ) {
        _press_time = now_time;
        _state = ShortAndLongPress::DOWN;
        if ( null != _OnButtonDown ) (*_OnButtonDown)();
      }
      break;
    case ShortAndLongPress::DOWN:
      if ( ( now_time - _press_time ) > _long_click_ms )  {
        if ( null != _OnLongPress ) {
          (*_OnLongPress)();
        }
        _state = ShortAndLongPress::DONE;
      }
      else if ( ! pushed )
      {
        if ( null != _OnShortPress ) {
          (*_OnShortPress)();
        }
        _state = ShortAndLongPress::QUIESCENT;        
      }
      break;
    case ShortAndLongPress::DONE:
      if ( ! pushed ) {
        _state = ShortAndLongPress::QUIESCENT;
      }
  }

}

void ShortAndLongPress::setOnButtonDown( void (*f)() ) {
  _OnButtonDown = f;
}

void ShortAndLongPress::setOnLongPress( void (*f)() ) {
  _OnLongPress = f;
}

void ShortAndLongPress::setOnShortPress( void (*f)() ) {
  _OnShortPress = f;
}
