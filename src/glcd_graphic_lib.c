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
#include "glcd_ctrl_internal.h"
#include "glcd_graphic_lib.h"
#include "font.c"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal data definition]===============================*/
glcdModuleType * glcd;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void glcd_init(void)
{
   glcd = glcd_addDriver();   
   glcd->init();
   ciaaPOSIX_printf("glcd_init()\n");
}

void glcd_putPixel(uint8_t x, uint8_t y, glcd_color_t color)
{
   /* TODO: x and y range control and color parameter implementation*/ 
   uint8_t page;
   uint8_t row_in_page;
   
   page = 7 - y / 8;
   row_in_page = 0x01 << (7 - y % 8);
   *(glcd->glcd_framebuffer + (x + 129 * page)) |= row_in_page;

//   glcd->setPage(page);
//   glcd->setColumn(x);
//   glcd->dataWrite(row_in_page);
}

/* Bresenham’s algorithm */
void glcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, glcd_color_t colour)
{
    signed int dx = 0x0000;
    signed int dy = 0x0000;
    signed int stepx = 0x0000;
    signed int stepy = 0x0000;
    signed int fraction = 0x0000;

    dy = (y2 - y1);
    dx = (x2 - x1);

    if(dy < 0)
    {
        dy = -dy;
        stepy = -1;
    }
    else
    {
        stepy = 1;
    }

    if(dx < 0)
    {
        dx = -dx;
        stepx = -1;
    }
    else
    {
        stepx = 1;
    }

    dx <<= 0x01;
    dy <<= 0x01;

    glcd_putPixel(x1, y1, colour);

    if(dx > dy)
    {
        fraction = (dy - (dx >> 1));
        while(x1 != x2)
        {
            if(fraction >= 0)
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            glcd_putPixel(x1, y1, colour);
        }
    }
    else
    {
        fraction = (dx - (dy >> 1));

        while(y1 != y2)
        {
            if (fraction >= 0)
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            glcd_putPixel(x1, y1, colour);
        }
    }
}

void glcd_circle(uint8_t x0, uint8_t y0, uint8_t r, glcd_color_t color)
{
}

void glcd_rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, glcd_color_t color)
{
   glcd_line(x0,y0,x1,y0,GLCD_COLOR_BLACK);
   glcd_line(x1,y0,x1,y1,GLCD_COLOR_BLACK);
   glcd_line(x0,y1,x1,y1,GLCD_COLOR_BLACK);
   glcd_line(x0,y0,x0,y1,GLCD_COLOR_BLACK);
}

void glcd_fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, glcd_color_t color)
{

}

void glcd_clearScreen(glcd_color_t color)
{
   uint16_t i;
   uint16_t fb_size = glcd->glcd_display_width * glcd->glcd_display_height;
   uint8_t color_fill = ~(color * 0xff);

   for (i=0; i < fb_size; i++)
   {
      *(glcd->glcd_framebuffer + i) = color_fill;
   }
}

void glcd_putString(uint8_t x, uint8_t y, uint8_t *string)
{
     do
     {
         glcd_putChar(x, y, *string++);
         x += 0x06;
     }while((*string >= 0x20) && (*string <= 0x7F));
}

uint8_t glcd_putChar(uint8_t x, uint8_t y, char ch)
{
   uint8_t i,j,value;
     for(i = 0x00; i < 0x05; i++)
     {
         for(j = 0x00; j < 0x08; j++)
         {
             value = 0x0000;
             value = ((font[((uint8_t)ch) - 0x20][i]));

             if(((value >> j) & 0x01) != 0x00)
             {
                 glcd_putPixel(x, y, 0);
             }
   //          else
   //          {
   //              glcd_putPixel(x, y, GLCD_COLOR_WHITE);
   //          }

             y -= 1;
          }
          y += 8;
          x++;
      }
}

/*==================[end of file]============================================*/
