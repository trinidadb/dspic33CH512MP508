-PWM modules works. But when I tried outputting a signal with 20ms (50Hz) of period I wasn't able.
Based on my test the minimum frequency y was able to obtain was 122Hz.
Additional changes need to be made to obtain the required frequency/period.
I tried different things but nothing work.
Additionally I tried using the Auxiliary PLL to reduce the PLL output frequency but when I tried to set FPLLO to a lower value than FPLLI the PWM output generated variables pulses