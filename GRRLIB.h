/********************************************************************************************
   _____       _____       _     _____                _                    
  / ____|     |  __ \     | |   |  __ \              | |                   
 | |  ____  __| |__) |__ _| |__ | |__) |___ _ __   __| | ___ _ __ ___ _ __ 
 | | |_ \ \/ /|  _  // _` | '_ \|  _  // _ \ '_ \ / _` |/ _ \ '__/ _ \ '__|
 | |__| |>  < | | \ \ (_| | |_) | | \ \  __/ | | | (_| |  __/ | |  __/ |   
  \_____/_/\_\|_|  \_\__, |_.__/|_|  \_\___|_| |_|\__,_|\___|_|  \___|_|   
                      __/ |                                                
                     |___/           
GRRLIB Version : 1.6

Coder : NoNameNo
	uschghost
                                    
info : http://wiibrew.org/index.php?title=Homebrew_apps/GRRLIB
********************************************************************************************/
#ifndef __GXHDR__
#define __GXHDR__

typedef unsigned short u16;
typedef unsigned int u32;

extern "C"
{

u16 *GRRLIB_MakeBuffer(int w, int h);

void GRRLIB_FillScreen(u16 color);
void GRRLIB_Line(short int x1, short int y1, short int x2, short int y2, u16 color);
u16 GRRLIB_Conv888_565(u32 colorin);
void GRRLIB_DrawImg(int xpos, int ypos, int width, int high, const u16 data[], float rad_ang, float rapport );
void GRRLIB_DrawRectangle(int x, int y, int hight, int widht, u16 color, int filled);
void GRRLIB_Print(int x, int y, int xsize, int ysize,char* text,const u16 tdata[], int fg, int bg);

void GRRLIB_InitVideo ();
void GRRLIB_Start();
void GRRLIB_Render();

}
#endif
