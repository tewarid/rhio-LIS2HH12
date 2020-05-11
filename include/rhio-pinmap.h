/**
 * Rhomb.io Duino Pinmap
 *
 * Copyright (c) Tecnofingers S.L
 * All rights reserved.
 *
 * @author Guillermo Alonso
 * @version 1.0.2
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RHIO_PINMAP
#define RHIO_PINMAP

//*** S100_DUINO_UNO_v1_0 *********************************//
#ifdef S100_DUINO_UNO_v1_0
  #define NMI    2
  #define INT0   3

  #define IO0    4
  #define IO1    5
  #define IO2    6
  #define IO3    7
  #define IO4    8
  #define IO5    A0
  #define IO6    A1
  #define IO7    A2

  #define LED    9
  #define PWM0   9

  #define RXD    0
  #define TXD    1
  #define SDA    A4
  #define SCL    A5
  #define MOSI   11
  #define MISO   12
  #define SCK    13
  #define CS0    10
  #define _1WIRE A3  // SJ4 must be closed & SJ1 must be open

  #define AD0    A6
  #define CAPT0  A7

  #define RSTOUT A3  // SJ1 must be closed & SJ4 must be open
#endif
//**** end of S100_DUINO_UNO_v1_0 ***********************//


//*** S100_DUINO_LEONARDO_v1_0 **************************//
#ifdef S100_DUINO_LEONARDO_v1_0
  #define NMI      HWB  // HWB on original Leonardo; MCU pin: PE2
  #define INT0      SS  // RXLED on original Leonardo; MCU pin: PB0

  #define IO0    4
  #define IO1    5
  #define IO2    6
  #define IO3    7
  #define IO4    8
  #define IO5    A0
  #define IO6    A1
  #define IO7    A2

  #define LED    9
  #define PWM    9

  #define RXD    0
  #define TXD    1
  #define SDA    A4
  #define SCL    A5
  #define MOSI   11
  #define MISO   12
  #define SCK    13
  #define CS0    10
  #define _1WIRE TXLED // RXLED on original Leonardo; MCU pin: PD5

  #define AD0    A6
  #define AD1    A7

  #define RSTOUT A1
#endif
//**** end of S100_DUINO_LEONARDO_v1_0 ***********************//


//*** S200_DUINO_UNO_PRO_v1_0 ********************************//
#ifdef S200_DUINO_UNO_PRO_v1_0
  #include "clsPCA9555.h"  // library for IO-EXPANDER required

  #define IOEX0   ED0
  #define IOEX1   ED1
  #define IOEX2   ED2
  #define IOEX3   ED3
  #define IOEX4   ED4
  #define IOEX5   ED5
  #define IOEX6   ED6
  #define IOEX7   ED7
  #define IOEX8   ED8
  #define IOEX9   ED9
  #define IOEX10  ED10
  #define IOEX11  ED11
  #define IOEX12  ED12
  #define IOEX13  ED13
  #define IOEX14  ED14
  #define IOEX15  ED15

  #define AND_OUT  2
  #define IOEX_INT A2  // MUX_SW=LOW required
  #define NMI      A0  // MUX_SW=LOW required
  #define INT0     A1  // MUX_SW=LOW required
  #define INT1     IOEX2

  #define MUX_SW   7
  #define UART_SW  IOEX0

  #define IO0      4
  #define IO1      3
  #define IO2      5
  #define IO3      IOEX3
  #define IO4      IOEX4
  #define IO5      IOEX5
  #define IO6      IOEX6
  #define IO7      IOEX7
  #define IO8      IOEX8
  #define IO9      IOEX9
  #define IO10     IOEX10
  #define IO11     IOEX11
  #define IO12     IOEX12
  #define IO13     IOEX13
  #define IO14     IOEX14
  #define IO15     IOEX15

  #define LED      9
  #define PWM0     9
  #define PWM1     6

  #define RXD      0  // UART_SW=LOW required
  #define TXD      1  // UART_SW=LOW required
  #define RXD1     0  // UART_SW=HIGH required
  #define TXD1     1  // UART_SW=HIGH required
  #define SDA      A4
  #define SCL      A5
  #define MOSI     11
  #define MISO     12
  #define SCK      13
  #define CS0      10
  #define CS1      IOEX1
  #define _1WIRE   A3  // MUX_SW=LOW required

  #define AD0      A6
  #define AD1      A7
  #define AD2      A0  // MUX_SW=HIGH required
  #define AD3      A1   // MUX_SW=HIGH required
  #define AD4      A2  // MUX_SW=HIGH required
  #define AD5      A3  // MUX_SW=HIGH required

  #define RSTOUT   8
#endif
//**** end of S200_DUINO_UNO_PRO_v1_0 ***********************//


//*** S200_DUINO_ZERO_v1_0 **********************************//
#ifdef S200_DUINO_ZERO_v1_0
  #define NMI    4
  #define INT0   3
  #define INT1   23
  // #define CAPT0   ??   // PA28, pin not includded on Arduino IDE for original Zero

  #define IO0    2
  #define IO1    5
  #define IO2    6
  #define IO3    7
  #define IO4    8
  // #define IO5    ??   // PA27, pin not includded on Arduino IDE for original Zero
  #define IO6    24
  #define IO7    22

  #define LED    9
  #define PWM0   9
  // #define PWM1   ??  // PB03, pin not includded on Arduino IDE for original Zero

  #define RXD    0
  #define TXD    1
  // #define RTS    ??  // PA31, pin not includded on Arduino IDE for original Zero
  // #define CTS    ??  // PA30, pin not includded on Arduino IDE for original Zero
  #define RXD1   31
  #define TXD1   30

  #define SDA    20
  #define SCL    21
  #define MOSI   35
  #define MISO   34
  #define SCK    37
  #define CS0    10
  #define CS1    A5  // MUX_SW=LOW required
  #define MEM_CS A4  // MUX_SW=LOW required
  #define uSD_CS A2  // MUX_SW=LOW required
  // #define USB_P      ??  // PA25, pin not includded on Arduino IDE for original Zero
  // #define USB_N     ??  // PA24, pin not includded on Arduino IDE for original Zero
  #define _1WIRE A3  // MUX_SW=LOW required

  #define AD0    A1
  #define AD1    A4  // MUX_SW=HIGH required
  #define AD2    A2  // MUX_SW=HIGH required
  #define AD3    A5  // MUX_SW=HIGH required
  #define DAC0   A0

  #define MUX_SW 38  // ANALOG (MULTIPLEXOR) SWITCH
  #define RSTOUT A3  // MUX_SW=HIGH required
#endif
//**** end of S200_DUINO_ZERO_v1_0 ***************************//


//*** S100_DUINO_MEGA_v2_0 *********************************//
#ifdef S100_DUINO_MEGA_v2_0

  #define NMI      2
  #define INT0     3
  #define INT1     12
  #define INT2     11
  // #define INT3      ??  // PJ6 pin not includded on Arduino IDE for original Mega
  // #define INT4      ??  // PE6 pin not includded on Arduino IDE for original Mega
  // #define INT5      ??  // PE7 pin not includded on Arduino IDE for original Mega
  // #define INT6      ??  // PJ2 pin not includded on Arduino IDE for original Mega

  #define IO0      36
  #define IO1      33
  #define IO2      44
  #define IO3      37
  #define IO4      34
  #define IO5      43
  #define IO6      46
  #define IO7      48

  #define IO8      47
  #define IO9      42
  #define IO10     45
  #define IO11     4
  #define IO12     32
  #define IO13     26
  #define IO14     31
  #define IO15     27

  #define IO16     39
  #define IO17     25
  #define IO18     24
  #define IO19     30
  #define IO20     28
  #define IO21     23
  #define IO22     29
  #define IO23     22

  #define IO24     35  // second function (main function is CS1)
  #define IO25     40  // second function (main function is CS2)
  #define IO26     41
  #define IO27     38
  #define IO28     28
  #define IO29     9  // second function (main function is PWM3)
  #define IO30     8  // second function (main function is PWM2)
  #define IO31     7  // second function (main function is PWM1)

  // #define IO32     ??  // PD6 pin not includded on Arduino IDE for original Mega
  // #define IO34     ??  // PJ5 pin not includded on Arduino IDE for original Mega
  // #define IO35     ??  // PJ7 pin not includded on Arduino IDE for original Mega

  #define LED      13
  #define PWM0     13
  #define PWM1     7
  #define PWM2     8
  #define PWM3     9
  #define PWM4     10

  #define RXD      0
  #define TXD      1
  #define RXD1     19
  #define TXD1     18
  #define RXD2     17
  #define TXD2     16
  #define RXD3     15
  #define TXD3     14

  #define SDA      20
  #define SCL      21
  #define MOSI     51
  #define MISO     50
  #define SCK      52
  #define CS0      53
  #define CS1      35
  #define CS2      40
  #define MEM_CS   A15
  // #define uSD_CS      ??  // SPI Mode only; PD5 pin not includded on Arduino IDE for original Mega
  #define QSPI_CS0 A14  // SPI Mode only;

  // #define _1WIRE   ??  // PH7 pin not includded on Arduino IDE for original Mega

  #define AD0      A0
  #define AD1      A1
  #define AD2      A2
  #define AD3      A3
  #define AD4      A4
  #define AD5      A5
  #define AD6      A6

  #define AD9      A12
  #define AD10     A11
  #define AD11     A9
  #define AD12     A8
  #define AD13     A13
  #define AD14     A10
  #define AD15     A4

  // #define COMP_P     ??  // PE2 pin not includded on Arduino IDE for original Mega
  #define COMP_N   5

  #define TS_YU    A12
  #define TS_XL    A11
  #define TS_YD    A9
  #define TS_XR    A8

  // #define CAPT0     ??  // PD4 pin not includded on Arduino IDE for original Mega
  #define CAPT1    49
  // #define RSTOUT   ??  // PJ3 pin not includded on Arduino IDE for original Mega
#endif
//**** end of S100_DUINO_MEGA_v2_0 ***********************//


//*** S100_ESP32_WROOM_32_v1_0 *********************************//
#ifdef S100_ESP32_WROOM_32_v1_0
  #define NMI       0
  #define INT0      34

  #define IO0       2
  #define IO1       4
  #define IO2       25
  #define IO3       26
  #define IO4       27
  #define IO5       13
  #define IO6       33  // R16 must be populated
  #define IO7       15  // R14 must be populated

  #define LED       12
  #define PWM0      12

  #define RXD       RXD0
  #define TXD       TXD0
  #define RTS       22  // R12 must be populated
  #define CTS       19  // R13 must be populated
  #define RXD1      16
  #define TXD1      17
  #define SDA       21
  #define SCL       22
  #define MOSI      23
  #define MISO      19
  #define SCK       18
  #define CS0       5
  #define QSPI_CS0  32
  #define MEM_CS    15  // R15 must be populated
  #define _1WIRE     33  // R22 must be populated

  #define SDIO_DATAO SD0
  #define SDIO_DATA1 SD1
  #define SDIO_DATA2 SD2
  #define SDIO_DATA3 SD3
  #define SDIO_CLK  CMD
  #define SDIO_CMD  CLK

  #define AD0      35

  #define DIFF_P  SENSOR_VP
  #define DIFF_N  SENSOR_VN

  #define RSTOUT   14
#endif
//**** end of S100_ESP32_WROOM_32_v1_0 ***********************//


//*** S100_ESP_WROOM_02_v1_0 *********************************//
#ifdef S100_ESP_WROOM_02_v1_0
  // coming soon
#endif
//**** end of S100_ESP_WROOM_02_v1_0 ***********************//


//*** S200_STM32L476_v2_0 *********************************//
#ifdef S200_STM32L476_v2_0
  // coming soon
#endif
//**** end of S200_STM32L476_v2_0 ***********************//

#endif // RHIO_PINMAP
