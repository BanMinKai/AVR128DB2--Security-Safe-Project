// in this file, i simply want to pack all the functions used for scanning into 
// 1 function only... this goes against the guideline: 1 function 1 job
// this scan for key is like an encapsulating function :>

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "mfrc522.h"
#include "usart0.h"
#include <util/delay.h>


#define KEY_FOUND 1
#define KEY_NOT_FOUND 0
uint8_t tag_id[8] = {0x14,0x63,0x97,0x6A,0x8A,0x00,0x00,0x00};



uint8_t mfrc522_api_scan_for_key(uint8_t* buffer)
{
    uint8_t byte = mfrc522_request(PICC_REQALL,buffer);
    uint8_t id_is_match = 1;
		// 
    if(byte == CARD_FOUND)
    {
        byte = mfrc522_get_card_serial(buffer);
        if(byte == CARD_FOUND)
        {   
            ;
            for(byte=0;byte<8;byte++)
            {
                if (buffer[byte] != tag_id[byte])
                {
                    id_is_match = 0;
                }

                usart_transmitByte(buffer[byte]);

            }
            if (id_is_match)
            {
                return KEY_FOUND;
            } 
            else
            {
                return KEY_NOT_FOUND;
            }
            
        }
        else
        {
            usart_printf("Error\r\n");
            return KEY_NOT_FOUND;
        }
    }
}
