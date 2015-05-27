Scheduler blink example.

This example project use EFM32 CMSIS, the emlib peripheral library and
the libttdcore utility library to demonstrate the use of the LED andthe
software-scheduled timers on the TDxxxx EVB.

Unlike the simple blink example, this demonstration relies on the software-
scheduled timer feature of the libtdcore library to toggle the LED connected to
the TDxxxx RF module TIM2 pin on the TDxxxx EVB every 0.5 s.
