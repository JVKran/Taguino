//commando's
#define R_REGISTER           0x00        //Leest commando en status registers, 5 bit register map address
#define W_REGISTER           0x20        //Schrijft commando en status registers, 5 bit register map address. Uitvoerbaar in power down
#define R_RX_PAYLOAD         0x61        //Leest de RX-payload: 1 - 32 bytes
#define W_TX_PAYLOAD         0xA0        //Schrijft TX-payload 1 - 32 bytes
#define FLUSH_TX             0xE1        //Flush TX FIFO, in TX mode
#define FLUSH_RX             0xE2        //Flush RX FIFO, in RX mode

//addresses
#define CONFIG               0x00        //Configuration register
#define EN_RXADDR            0x02        //Enabled RX Addresses
#define SETUP_AW             0x03        //Setup of address widths
#define SETUP_RETR           0x04        //Setup of automatic retransmission
#define RF_CH                0x05        //RF channel (sets the frequency channel where nRF is operation on)
#define RF_SETUP             0x06        //RF setup register
#define STATUS               0x07        //Status register
#define RX_ADDR_P0           0x0A        //Receive address data pipe 0, maximum 5 bytes length
#define RX_ADDR_P1           0x0B        //Receive address data pipe 1, maximum 5 bytes length
#define RX_ADDR_P2           0x0C        //Receive address data pipe 2, maximum 5 bytes length
#define RX_ADDR_P3           0x0D        //Receive address data pipe 3, maximum 5 bytes length
#define RX_ADDR_P4           0x0E        //Receive address data pipe 4, maximum 5 bytes length
#define RX_ADDR_P5           0x0F        //Receive address data pipe 5, maximum 5 bytes length
#define TX_ADDR              0x10        //Transmit address. Used for a PTX device only 
#define RX_PW_P0             0x11        
#define RX_PW_P1             0x12           
#define RX_PW_P2             0x13
#define RX_PW_P3             0x14
#define RX_PW_P4             0x15
#define RX_PW_P5             0x16
#define FIFO_STATUS          0x17        //FIFO status register
#define DYNPD                0x1C        //Enable dynamic payload length
#define FEATURE              0x1D        //Feature register

//mnemonic
#define PWR_UP               1        //1: POWER UP, 0: POWER DOWN
#define PRIM_RX              0        //1: PRX, 0: PTX
#define ERX_P5               5        //Enable data pipe 5
#define ERX_P4               4        //Enable data pipe 4
#define ERX_P3               3        //Enable data pipe 3
#define ERX_P2               2        //Enable data pipe 2
#define ERX_P1               1        //Enable data pipe 1
#define ERX_P0               0        //Enable data pipe 0
#define ARD                  4        //Auto Retransmit Delay
#define ARC                  0        //Auto Retransmit Count
#define RF_DR_LOW            5        //Set RF data rate to 250kps
#define RF_DR_HIGH           3        //Select between the high speed data rates
#define RF_PWR_LOW           1        //Set RF output power low 
#define RF_PWR_HIGH          2        //Set RF output power high
#define RX_DR                6        //Data ready RX FIFO interrupt     
#define TX_DS                5        //Data sent TX FIFO interrupt
#define MAX_RT               4        //Maximum number of TX retransmits interrupt 
#define RX_EMPTY             0        //RX FIFO empty flag, 1: RX FIFO empty, 0: Data in RX FIFO