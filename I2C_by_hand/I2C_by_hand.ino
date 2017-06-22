/*
 * ***************************************************************************
 * 
 *         ***         ######   #####    #####
 *         ***           ##    ### ###  ### ###
 *         ***           ##    ##   ##  ##   ##
 *         ***           ##        ##   ##
 *         ***           ##       ##    ##
 *       *******         ##      ##     ##
 *        *****          ##     ##      ##   ##
 *         ***           ##    ###      ### ###
 *          *          ######  #######   #####     B Y   H A N D
 *          
 * *************************************************************************** 
 * SIMPLE I2C BITBANG SKETCH. It is much more smaller than the Wire.Lib
 *  ---------------------------------------------------------------------------
 *                                +-----+
 *                         - TX1 -|  A  |- VIN
 *                         - RX0 -|  R  |- GND
 *                           RST -|  D  |- RST
 *                           GND -|  U  |- 5V  -  
 *                         -  D2 -|  I  |- A7  -   
 *                         -  D3 -|  N  |- A6  -  
 *                         -  D4 -|  O  |- A5  - SCL  - Any I2C Device 
 *                         -  D5 -|     |- A4  - SDA  - Any I2C Device
 *                         -  D6 -|  N  |- A3  -  
 *                         -  D7 -|  A  |- A2  -  
 *                         -  D8 -|  N  |- A1  -  
 *                         -  D9 -|  O  |- A0  -  
 *                         - D10 -|     |- REF
 *                         - D11 -|  V  |- 3V3 -  
 *                         - D12 -|  3  |- D13 -  
 *                                +-usb-+
 * ---------------------------------------------------------------------------
 */


volatile uint8_t *i2c_port;                      // Adresse des Port-Registers

#define I2C_SDA A4                                                  // SDA-Pin
#define I2C_SCL A5                                                  // SCL-Pin

#define I2C_PORT_REG 3                            // digitalPinToPort(SDA-Pin)
#define I2C_SDA_HIGH 16                        // digitalPinToBitMask(SDA-Pin)
#define I2C_SDA_LOW  239                                      // ~I2C_SDA_HIGH
#define I2C_SCL_HIGH 32                        // digitalPinToBitMask(SCL-Pin)
#define I2C_SCL_LOW  223                                      // ~I2C_SCL_HIGH
#define I2C_DEL 5                                // I2C-Delay in Mikrosekunden

// ---------------------------------------------------------------------------

/* Adresses of I2C Devices:
 *  You have to choose the adress given in the datasheet and then  
 *  you have to shift it left for 1 bit. e.g
 *  DS1307 has given the adress 0x68 in the datasheet. 0x68 << 1 = 0xD0  !!
 */

#define ADR_RTC  0xD0                        // Adr. lt. Datenblatt: 0x68 << 1
#define ADR_BMP  0xEE                        // Adr. lt. Datenblatt: 0x77 << 1
#define ADR_HMC  0x3C                        // Adr. lt. Datenblatt: 0x1E << 1 
#define ADR_MPU  0xD0                        // Adr. lt. Datenblatt: 0x68 << 1

// ---------------------------------------------------------------------------

void setup() {
  // Set I2C Pins and Port
  i2c_port = portOutputRegister(I2C_PORT_REG);
  pinMode(I2C_SCL, OUTPUT);                            // SDA, SCL sind Output
  pinMode(I2C_SDA, OUTPUT);

}

/*
 * ***************************************************************************
 * 
 *         ***         ##        #####    #####   ######
 *         ***         ##       ### ###  ### ###  ##  ###
 *         ***         ##       ##   ##  ##   ##  ##   ##
 *         ***         ##       ##   ##  ##   ##  ##  ###
 *         ***         ##       ##   ##  ##   ##  ######
 *       *******       ##       ##   ##  ##   ##  ##
 *        *****        ##       ##   ##  ##   ##  ##
 *         ***         ##   ##  ### ###  ### ###  ##
 *          *          #######   #####    #####   ##
 *          
 * ***************************************************************************         
 */
 
void loop() {
  /*
   * Here you can use the following commands:
   * 
   * I2C_StartCondition();
   * There is no need to call this function, because it will be called by 
   * the I2C_SendByte(mByte,mStart,mLast) function if mStart is true
   * 
   * I2C_StartCondition();
   * Ther is no need to call this function, because it will be called by
   * the I2C_SendByte(mByte,mStart,mLast) or I2C_ReadByte(mLast) or
   * I2C_Read2Byte(mLast) functions if mLast if true;
   * 
   * I2C_BitMapper(mI2CAdr, mRegister, mAndMask, mOrMask);
   * With this function you can set some or any bit in a Register of a
   * I2C-Device. 
   * mI2CAdr -    Adress of the Device (see Notes to adresses on top of this)
   * mRegister -  any Register of the Device you want to change
   * mAndMask -   Binary Mask of the bits in the register: 
   *              1: don't change  0: change
   * mOrMask -    Binary Mask of the bits in the register:
   *              1: set 1         0: set 0
   * e.g. I2C_BitMapper(ADR_RTC, 0x00, 0b01111111, 0b10000000) sets the 7th
   * bit of Register 0x00 on DS1307-RTC and stopps the clock running.
   * 
   * I2C_SendByte(mByte,mStart,mLast);
   * Sends a byte to a I2C Device
   * mByte -      Data
   * mStart -     Includes StartCondition (true or false)
   * mLast -      Includes StopCondition (true or false)
   * 
   * I2C_ReadByte(boolean mLast);
   * Reads a byte from a I2C Device
   * mLast -      Includes StopCondition (true or false)
   * 
   * I2C_Read2Byte(boolean mLast);
   * Reads a word of 2 bytes from a I2C Device
   * mLast -      Includes StopCondition (true or false)
   * 
   */


  // Example: find out if DS1307-RTC is running (7th bit of register 0x00
  // has to be unset)

  // if you want to send a write-command to the I2C Device clear the
  // first bit of the ADR-Byte   (ADR_RTC | 0x00)
  I2C_SendByte((ADR_RTC | 0x00), true, false);     // Send StartCondition and
                                           // adress of the device to I2C Bus
  I2C_SendByte(0x00,false,true);       // Send the adress of the register you
                               // want to start from and send a StopCondition

  // if you want to send a read-command to the I2C Device set the
  // first bit of the ADR-Byte   (ADR_RTC | 0x01)
  I2C_SendByte(ADR_RTC | 0x01, true,false);        // Send StartCondition and
                                           // adress of the device to I2C Bus
  int mResult = I2C_ReadByte(true);        // Read one Byte and StopCondition

  if (mResult & 0x80) {                            // Check if 7th bit is set
     // The clock is not running
  } else {
     // The clock is running
  }

  do {
    
  } while (true);
   
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void I2C_StartCondition(void) {
  I2C_SDA_H();                              // Startverfahren nach NXP-Vorgabe
  I2C_SCL_H();             // während eines Clock-Pulses wechselt SDA von High
  I2C_SDA_L();                                                 // zu Low-State
  I2C_SCL_L();
}

// ---------------------------------------------------------------------------

void I2C_StopCondition(void) {
  I2C_SDA_L();                               // Stopverfahren nach NXP-Vorgabe
  I2C_SCL_H();              // Während eines Clock-Pulses wechselt SDA von Low
  I2C_SDA_H();                                                // zu High-State
}

// ---------------------------------------------------------------------------

int I2C_ReadBit(void) {
  int mBit;                                  // Zum Lesen eines einzelnen Bits 
  I2C_SDA_H();                        // von der Datenleitung muss diese zuvor 
  pinMode(I2C_SDA, INPUT);          // von Output zu Input umgeschalten werden 
  delayMicroseconds(I2C_DEL);
  I2C_SCL_H();                             // Nachdem der Master den Clockpuls 
                                             //auf "High" gezogen hat kann das 
  mBit = digitalRead(I2C_SDA);       // Bit von der SDA-Leitung gelesen werden
  I2C_SCL_L(); 
  pinMode(I2C_SDA, OUTPUT);             // Anschließend wird SDA wieder Output
  return mBit;
}

// ---------------------------------------------------------------------------

void I2C_BitMapper(uint8_t mI2CAdr, uint8_t mRegister, 
                   uint8_t mAndMask, uint8_t mOrMask) {
  I2C_SendByte((mI2CAdr | 0x00), true, false);                // Adresse rufen
  I2C_SendByte(mRegister,false,true);                       // Registeradresse
  I2C_SendByte(mI2CAdr | 0x01, true,false); 
  byte mRegValue = I2C_ReadByte(true) ;                        // Inhalt lesen
  mRegValue &= mAndMask;                          // Verknüpfung mit And-Maske
  mRegValue |= mOrMask;                            // Verknüpfung mit Or-Maske
  I2C_SendByte((mI2CAdr | 0x00), true, false);
  I2C_SendByte(mRegister,false,false);
  I2C_SendByte(mRegValue,false,true);                      // Zurück schreiben                    
}

// ---------------------------------------------------------------------------

boolean I2C_SendByte(byte mByte, boolean mStart, boolean mLast) {
  if (mStart)    I2C_StartCondition();
  for(uint8_t mBit = 0x80; mBit; mBit >>=1) {     // Sendet 8 Bits, MSB zuerst
    if (mByte & mBit) { I2C_SDA_H(); }
    else              { I2C_SDA_L(); }
    I2C_SCL_H();                                                  // Clockpuls
    I2C_SCL_L();
  }
  boolean mAck = I2C_ReadBit();     // nach jedem Byte wird das Acknoledge-Bit
                                                                    // gelesen
  if (mLast)     I2C_StopCondition();  // Wenn letztes Byte, dann Übermittlung                       
                                                                    // beenden
  if (mAck)      return false;
  return true;
}

// ---------------------------------------------------------------------------

byte I2C_ReadByte(boolean mLast) {                 // Liest 8 Bit vom Slave
  byte mByte = 0;
  for(uint8_t mBit = 0; mBit < 8; mBit++) {
    mByte <<= 1;
    mByte |= I2C_ReadBit(); 
  }
  // Ack
  if (mLast)           { I2C_SDA_H(); }          // Ggf. Acknoledge Bit senden
  else                 { I2C_SDA_L(); } // Beim letzen Byte einer Trans. nicht
  I2C_SCL_H();
  I2C_SCL_L();

  // Stopp
  if (mLast)     I2C_StopCondition();                   // Ggf. Trans. beenden
  return mByte;
}

// ---------------------------------------------------------------------------

uint16_t I2C_Read2Byte(boolean mLast) {         // Liest zwei Byte als int16_t
  uint16_t mResult;
  mResult = (I2C_ReadByte(false) << 8);
  mResult |= I2C_ReadByte(mLast);
  return mResult;
}

// ---------------------------------------------------------------------------
void I2C_SDA_H(void) {                               // SDA-Leitung auf "High"
  *i2c_port |= I2C_SDA_HIGH;
}

// ---------------------------------------------------------------------------

void I2C_SDA_L(void) {                                // SDA-Leitung auf "Low"
  *i2c_port &= I2C_SDA_LOW;
}

// ---------------------------------------------------------------------------

void I2C_SCL_H(void) {                               // SCL-Leitung auf "High"
  *i2c_port |= I2C_SCL_HIGH;                         // mit kurzer Verzögerung
  delayMicroseconds(I2C_DEL);
}

// ---------------------------------------------------------------------------

void I2C_SCL_L(void) {                                // SCL-Leitung auf "Low"
  *i2c_port &= I2C_SCL_LOW;
}

