#include <avr/io.h>
#include <util/delay.h>

// Function to display numbers on the 7-segment display (common anode)
void display_7segment(uint8_t number)
{
    // Array to store the active-low values for 0-9 on the 7-segment display
    uint8_t segment_codes[10] = {
        0b11000000, // 0
        0b11111001, // 1
        0b10100100, // 2
        0b10110000, // 3
        0b10011001, // 4
        0b10010010, // 5
        0b10000010, // 6
        0b11111000, // 7
        0b10000000, // 8
        0b10010000  // 9
    };

    PORTA = segment_codes[number];
}

int main(void)
{
    uint8_t counter = 0;
    uint8_t last_state = 0;

    // Configure Port A as output for 7-segment display
    DDRA = 0xFF;
    // Configure Port B as input for the toggle switch
    DDRB &= ~(1 << PINB0);
    PORTB = 0xff;
    // Configure Port C as output for LED
    DDRC = (1 << PINC0);

    // Initialize the 7-segment display to show 0
    display_7segment(counter);
    while (1)
    {
        if (PINB == 0b11111110 && last_state == 0)
        {
            counter++;
            display_7segment(counter);
            PORTC = 1;
            last_state = 1;

        }
        else if(PINB == 0b11111111){
            last_state = 0;
            PORTC = 0;
        }
        if(9 == counter)

        	while(1){PORTC = 1;}
    }

    return 0;
}
