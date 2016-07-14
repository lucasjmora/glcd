/* Copyright 2014, ACSE & CADIEEL
 *    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *    CADIEEL: http://www.cadieel.org.ar
 * All rights reserved.
 *
 *    or
 *
 * Copyright 2014, Your Name <youremail@domain.com>
 * All rights reserved.
 *
 *    or
 *
 * Copyright 2014, ACSE & CADIEEL & Your Name <youremail@domain.com
 *    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *    CADIEEL: http://www.cadieel.org.ar
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Short description of this file
 **
 ** Long description of this file
 **
 **/

/*==================[inclusions]=============================================*/
#include "os.h"
#include "ciaaPOSIX_stdio.h"
#include "glcd_ctrl_internal.h"

/*==================[macros and definitions]=================================*/
/* adapted from lpc1114 code base: check licence */
#define NT7532_CMD_DISP_OFF               0xAE
#define NT7532_CMD_DISP_ON                0xAF
#define NT7532_CMD_SET_DISP_START_LINE    0x60
#define NT7532_CMD_SET_PAGE               0xB0
#define NT7532_CMD_SET_COLUMN_UPPER       0x10
#define NT7532_CMD_SET_COLUMN_LOWER       0x00
#define NT7532_CMD_SET_ADC_NORMAL         0xA0
#define NT7532_CMD_SET_ADC_REVERSE        0xA1
#define NT7532_CMD_SET_DISP_NORMAL        0xA6
#define NT7532_CMD_SET_DISP_REVERSE       0xA7
#define NT7532_CMD_SET_ALLPTS_NORMAL      0xA4
#define NT7532_CMD_SET_ALLPTS_ON          0xA5
#define NT7532_CMD_SET_BIAS_9             0xA2 
#define NT7532_CMD_SET_BIAS_7             0xA3
#define NT7532_CMD_RMW                    0xE0
#define NT7532_CMD_RMW_CLEAR              0xEE
#define NT7532_CMD_INTERNAL_RST           0xE2
#define NT7532_CMD_SET_COM_NORMAL         0xC0
#define NT7532_CMD_SET_COM_REVERSE        0xC8
#define NT7532_CMD_SET_POWER_CTRL         0x28
#define NT7532_CMD_SET_RESISTOR_RATIO     0x20
#define NT7532_CMD_SET_VOLUME_FIRST       0x81
#define NT7532_CMD_SET_VOLUME_SECOND      0x20
#define NT7532_CMD_SET_STATIC_OFF         0xAC
#define NT7532_CMD_SET_STATIC_ON          0xAD
#define NT7532_CMD_SET_STATIC_REG         0x00
#define NT7532_CMD_NOP                    0xE3
#define NT7532_CMD_TEST                   0xF0
#define NT7532_CMD_TEST_RST               0xF0

#define GLCD_DISPLAY_WIDTH  128
#define GLCD_DISPLAY_HEIGHT 64
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void glcd_NT7532_init();
static void glcd_NT7532_cmdWrite(uint8_t cmd);
static void glcd_NT7532_dataWrite(uint8_t data);
static void glcd_NT7532_setPage(uint8_t data);
static void glcd_NT7532_setColumn(uint8_t data);

/*==================[internal data definition]===============================*/
static uint32_t wr_buffer;

glcdModuleType glcd_NT7532 = {
   glcd_NT7532_init,
   glcd_NT7532_cmdWrite,
   glcd_NT7532_dataWrite,
   glcd_NT7532_setPage,
   glcd_NT7532_setColumn,
   GLCD_DISPLAY_WIDTH,
   GLCD_DISPLAY_HEIGHT
};

/*==================[external data definition]===============================*/
extern int32_t ciaaLcd_fd;

/*==================[internal functions definition]==========================*/
static void glcd_NT7532_cmdWrite(uint8_t cmd)                          
{
   wr_buffer = (0x0900 | cmd) << 8;               
   ciaaPOSIX_write(ciaaLcd_fd, &wr_buffer , 3);     

   //SetRelAlarm(SetEvTon, 1, 0);
   //WaitEvent(evTon);
   //ClearEvent(evTon);

   wr_buffer &= 0x0007FFFF;            
   ciaaPOSIX_write(ciaaLcd_fd, &wr_buffer , 3);
} 

static void glcd_NT7532_dataWrite(uint8_t data)                        
{
   wr_buffer = (0x0b00 | data) << 8;              
   ciaaPOSIX_write(ciaaLcd_fd, &wr_buffer , 3);

   //SetRelAlarm(SetEvTon, 1, 0);
   //WaitEvent(evTon);
   //ClearEvent(evTon);

   wr_buffer &= 0x0007FFFF;              
   ciaaPOSIX_write(ciaaLcd_fd, &wr_buffer , 3);
} 

static void glcd_NT7532_init()
{
   wr_buffer = 0;              
   
   /* all pins low waiting stabilizing the power */
   /*reset pin ????*/
   ciaaPOSIX_write(ciaaLcd_fd, &wr_buffer , 3);     

   SetRelAlarm(SetEvTon, 10, 0);
   WaitEvent(evTon);
   ClearEvent(evTon);

   glcd_NT7532_cmdWrite(NT7532_CMD_INTERNAL_RST);
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_BIAS_9);                         // LCD Bias Select
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_ADC_NORMAL);                     // ADC Select
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_COM_REVERSE);                     // SHL Select
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_POWER_CTRL | 0x07);           // Turn on voltage converter (VC=1, VR=0, VF=0)
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_VOLUME_FIRST);
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_VOLUME_SECOND | 0x11);           // Turn on voltage follower
   //glcd_NT7532_cmdWrite(NT7532_CMD_SET_VOLUME_SECOND | 0x3f);           // allow set brightness (value 0..63)
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_RESISTOR_RATIO | 0x6);           // Set LCD operating voltage
   // Turn display on
   glcd_NT7532_cmdWrite(NT7532_CMD_DISP_ON);
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_DISP_START_LINE);                // Initial Display Line

	SetRelAlarm(SetEvTon, 10, 0);
	WaitEvent(evTon);
	ClearEvent(evTon);
//   CMD(NT7532_CMD_SET_ALLPTS_NORMAL);
//   st7565SetBrightness(0x18);
}

static void glcd_NT7532_setPage(uint8_t page)
{
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_PAGE | page);
}

static void glcd_NT7532_setColumn(uint8_t column)
{
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_COLUMN_LOWER | ( column & 0x0f));
   glcd_NT7532_cmdWrite(NT7532_CMD_SET_COLUMN_UPPER | ((column & 0xf0) >> 4));
}

/*==================[external functions definition]==========================*/

extern glcdModuleType * glcd_addDriver(void)
{
   ciaaPOSIX_printf("glcd_addDriver()\n");
   return &glcd_NT7532; 
}
//extern void glcd_addDriver(glcdModuleType * glcd_device)
//{
//   glcd_device = &glcd_NT7532; 
//   ciaaPOSIX_printf("glcd_addDriver()\n");
//}






extern void ciaaLcd_NT7532_refresh()//, uint8_t * framebuffer)
{
  uint8_t c, p;
  //int pagemap[] = { 3, 2, 1, 0, 7, 6, 5, 4 };

  for(p = 0; p < 8; p++) 
  {
    glcd_NT7532_cmdWrite(NT7532_CMD_SET_PAGE | p);
    //glcd_NT7532_cmdWrite(NT7532_CMD_SET_PAGE | pagemap[p]);
    glcd_NT7532_cmdWrite(NT7532_CMD_SET_COLUMN_LOWER | (0x0 & 0xf));
    glcd_NT7532_cmdWrite(NT7532_CMD_SET_COLUMN_UPPER | ((0x0 >> 4) & 0xf));
   // glcd_NT7532_cmdWrite(NT7532_CMD_RMW);
   // glcd_NT7532_dataWrite(0xf0);
    
    for(c = 0; c < 129; c++) 
    {
      //DATA(buffer[(128*p)+c]);
      glcd_NT7532_dataWrite(0x00);
    }
  }

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
