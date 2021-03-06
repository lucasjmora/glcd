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

#ifndef GLCD_GRAPHIC_LIB_H
#define GLCD_GRAPHIC_LIB_H
/** \brief Short description of this file
 **
 ** Long description of this file
 **
 **/

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
//typedef void (*glcd_controllerInit)(void);
//typedef void (*glcd_cmdWrite)(uint8_t);
//typedef void (*glcd_dataWrite)(uint8_t);
//
//typedef struct {
//   glcd_controllerInit init;
//   glcd_cmdWrite cmdWrite;
//   glcd_dataWrite dataWrite;   
//   uint8_t glcd_display_width;
//   uint8_t glcd_display_height;
//}glcdModuleType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
typedef enum
{
   GLCD_COLOR_BLACK,
   GLCD_COLOR_WHITE
}glcd_color_t;


void glcd_init (void);
void glcd_putPixel(uint8_t x, uint8_t y, glcd_color_t color);
void glcd_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, glcd_color_t color);
void glcd_circle(uint8_t x0, uint8_t y0, uint8_t r, glcd_color_t color);
void glcd_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, glcd_color_t color);
void glcd_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, glcd_color_t color);
void glcd_clearScreen(glcd_color_t color);
void glcd_putString(uint8_t x, uint8_t y, uint8_t *string);
uint8_t glcd_putChar(uint8_t x, uint8_t y, char ch);
//uint8_t glcd_putChar(uint8_t x, uint8_t y, uint8_t ch, glcd_color_t fb, glcd_color_t bg);
/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef GLCD_GRAPHIC_LIB_H */

