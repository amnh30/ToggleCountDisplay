#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL // Define CPU frequency for delay

void displaySevenSegment(uint8_t number);

int main(void) {
    DDRA = 0xFF;  // Set PORTA as output for 7-segment display
    DDRC = 0xFF;  // Set PORTC as output for LED
    DDRB &= ~(1 << PB0);  // Set PB0 as input for DIP switch

    uint8_t count = 0;
    uint8_t prevSwitchState = 0;

    while(1) {
        uint8_t switchState = PINB & (1 << PB0); // Read DIP switch state

        if (switchState && !prevSwitchState) { // Detect rising edge (switch toggled)
            if (count < 9) {
                count++;
            }
        }

        displaySevenSegment(count);

        if (count == 9) {
            PORTC |= (1 << PC0); // Turn on LED (sending a HIGH signal)
        } else {
            PORTC &= ~(1 << PC0); // Turn off LED (sending a LOW signal)
        }


        prevSwitchState = switchState;
        _delay_ms(50); // Debounce delay
    }
}

void displaySevenSegment(uint8_t number) {
    // Array for common anode 7-segment representation of digits 0-9
    uint8_t segmentDigits[10] = {
        0xC0, // 0 (0x3F inverted)
        0xF9, // 1 (0x06 inverted)
        0xA4, // 2 (0x5B inverted)
        0xB0, // 3 (0x4F inverted)
        0x99, // 4 (0x66 inverted)
        0x92, // 5 (0x6D inverted)
        0x82, // 6 (0x7D inverted)
        0xF8, // 7 (0x07 inverted)
        0x80, // 8 (0x7F inverted)
        0x90  // 9 (0x6F inverted)
    };

    PORTA = segmentDigits[number]; // Display the corresponding digit on the 7-segment
}
