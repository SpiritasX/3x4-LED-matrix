# 3x4-LED-matrix

This project is intended to show how extern interrupts work. Three rows of LEDs light up at the specific order with constant speed.
Every row has a button that makes that one row specifically show random blinking at different speed. That speed can be changed with buttons 4 and 5.
You can't press more then one of the first 3 buttons and you can't press 4th nor 5th button if none of the three are pressed.

# Code

Loop function has one for loop that goes infinitely from 0 to 16 and back every multiple of 2.
Binary function that that number - 1 and generates the 12 digit number that gets outputed on the shift registers. If any of the three buttons are pressed, this function generates 4 of those 12 bits randomly by taking a random number between 0 and 15.
Isr function gets called every time a button is pressed and it checks what button exactly was pressed.

# Links

https://www.onsemi.com/pub/Collateral/MC74HC595-D.PDF
http://www.ti.com/lit/ds/symlink/sn74hc165.pdf
https://www.arduino.cc/en/Tutorial/ShiftIn
https://www.arduino.cc/en/Tutorial/ShiftOut
https://www.arduino.cc/reference/en/

If you have any questions you can contact me on:

Instagram: dejan_bogovac

Facebook: Dejan Bogovac

Gmail: deja.bogovac@gmail.com
