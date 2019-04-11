#ifndef SHORTANDLONGPRESS_H
#define SHORTANDLONGPRESS_H

#define null 0

class ShortAndLongPress
{
  private:
    static const uint8_t QUIESCENT=0; // Button is released, waiting for push
    static const uint8_t DOWN=1; // Button is down, waiting for timeout or release
    static const uint8_t DONE=2; // Timeout has occured, button still down

    uint8_t _state;
    uint32_t _press_time;
    uint32_t _long_click_ms;
    int _pin;
    uint8_t _active;
    uint8_t  active; // low or high
    void (*_OnButtonDown)();
    void (*_OnShortPress)();
    void (*_OnLongPress)();

  public:
    static const uint8_t ACTIVE_HIGH=0;
    static const uint8_t ACTIVE_LOW=1;
    ShortAndLongPress( int pin, uint32_t long_click_ms, uint8_t active );
  
    void tick( uint32_t now_time );
    
    void setOnButtonDown( void (*f)() );
    void setOnLongPress( void (*f)() );
    void setOnShortPress( void (*f)() );
    
};

#endif /* SHORTANDLONGPRESS_H */
