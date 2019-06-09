#ifndef __SYSTEM_CONF__
#define __SYSTEM_CONF__

#define STM32_UUID ((uint32_t *)0x1FF80050)
/***** OPTIONS**********/

//#define debug
//#define NODE


/* MPU settings */
#define USE_ACK				true
#define DEV_ADDR			0x1A2B
#define HEAD_SIZE			7
#define CONFIG_ADDR         0xFFFF
#define SLEEP_TIME          2000               //millisecond
#define SLEEP_FACTOR        20                                     
#define RX_TIMEOUT_VALUE    1000            //millisecond
#define RX_TIMEOUT_FACTOR   10
#define MAX_POWER           25

#define JOIN_RETRY          1000

/****** CONFIGURATION ***************/

#define RF_FREQUENCY		                        868000000	    //Europe band
#define TX_OUTPUT_POWER_DF		                    14				//dBm

/*Lora settings */

#define LORA_BANDWIDTH_DF                           0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR_DF                    7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]

#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#define MAX_PAYLOAD                                 256

#endif