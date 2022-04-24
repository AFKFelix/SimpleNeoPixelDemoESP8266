# SimpleNeoPixelDemoESP8266
This is a version of the [SimpleNeoPixelDemo](https://github.com/bigjosh/SimpleNeoPixelDemo/tree/master) but for the ESP8266.

The code sends bits/bytes to the LED. It uses asm "nop" to get the delay needed to controll the NeoPixels.
If you want to get deeper into how the WS2812/WS2812b protocol works, have a look at [this](https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/).

*Note:  The code is just a little demonstration and not really optimized*
