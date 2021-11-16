#include <grrlib.h>
#include <stdlib.h>
#include <stdio.h>

#include <wiiuse/wpad.h>
#include "all_gfx.h"

typedef struct{
    float x;
    float y;
    float vy;
} varimario;
varimario vamario;
//int main
int main() {
    int n = 0;
    GRRLIB_Init();
    WPAD_Init();

    GRRLIB_Settings.antialias = false;
    GRRLIB_texImg *tex_grr = GRRLIB_LoadTexture(logo);
    GRRLIB_texImg *tex_mario = GRRLIB_LoadTexture(mario);
    GRRLIB_texImg *tex_bg = GRRLIB_LoadTexture(Bg);

    for(n = 0; n < 502; n ++){
        GRRLIB_DrawImg(0, 0, tex_grr, 0, 1, 1, GRRLIB_WHITE); // Draw a bitmap
        GRRLIB_Render();
    }
    GRRLIB_FreeTexture(tex_grr);

    while(1){
        vamario.y += vamario.vy;
        vamario.vy += 0.123;

        int wpadheld = WPAD_ButtonsHeld(0);
        int wpadown = WPAD_ButtonsDown(0);
        WPAD_ScanPads();

        if(wpadheld & WPAD_BUTTON_UP) vamario.x -= 2;
        if(wpadheld & WPAD_BUTTON_DOWN) vamario.x += 2;

        if(vamario.y > 440){
            vamario.y = 440;
            if(wpadown & WPAD_BUTTON_2) vamario.vy = -4.6;
        }

        GRRLIB_FillScreen(GRRLIB_BLACK);    // Clear the screen
        GRRLIB_DrawImg(0, 0, tex_bg, 0, 4, 4, GRRLIB_WHITE);
        GRRLIB_DrawImg(vamario.x, vamario.y , tex_mario, 0, 2, 2, GRRLIB_WHITE);
        GRRLIB_Render();
    }
    GRRLIB_FreeTexture(tex_mario);
    GRRLIB_FreeTexture(tex_bg); 
    
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    return 0;
}
