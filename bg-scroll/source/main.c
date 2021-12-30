// he descubierto que soy la persona mas tonta del mindp
//la cosa esta diseñada para ser jugada con el wiimote alado.A
#include <grrlib.h>//include GRRLIB
#include <stdlib.h>//include C
#include <stdio.h>//include C

#include <wiiuse/wpad.h>//include wiimotes
#include "all_gfx.h" //include graphics
typedef struct {
    float x;
    float y;
}type;
typedef struct{
    float x;
    float y;
}tybg;
type pe;
tybg bg;
//int main
int main() {
    int n = 0;
    GRRLIB_Init();  //iniciar GRRLIB
    WPAD_Init();    //iniciar wiimotes

    GRRLIB_Settings.antialias = false; //desactivar antialias
    GRRLIB_texImg *tex_grr = GRRLIB_LoadTexture(logo);//cargar textura de logo
    GRRLIB_texImg *tex_a = GRRLIB_LoadTexture(a);//cargar textura de mario
    GRRLIB_texImg *tex_e = GRRLIB_LoadTexture(e);//cargar fondo de pantalla

       //splash de grrlib
    for(n = 0; n < 502; n ++){
        GRRLIB_DrawImg(0, 0, tex_grr, 0, 1, 1, GRRLIB_WHITE); // dibujar textura
        GRRLIB_Render();//renderizar
    }
    GRRLIB_FreeTexture(tex_grr);//librerar textura

    while(1){
        WPAD_ScanPads(); // lo que se me olvido

        int wpad = WPAD_ButtonsHeld(0);

        if(wpad & WPAD_BUTTON_UP) pe.y --;
        if(wpad & WPAD_BUTTON_DOWN) pe.y ++;
        if(wpad & WPAD_BUTTON_RIGHT) pe.x ++;
        if(wpad & WPAD_BUTTON_LEFT) pe.x --;
        if(pe.x < 0) pe.x = 0;
        else if(pe.y < 0) pe.y = 0;

        bg.y = -pe.y;
        bg.x = -pe.x;

        if(bg.y > 720) bg.y = 720;
        else if(bg.x > 1280) bg.x = 1280;

        GRRLIB_FillScreen(GRRLIB_BLACK);    // llenar la pantalla de negro
        GRRLIB_DrawImg(bg.x, bg.y, tex_e, 0, 2, 2, GRRLIB_WHITE);//dibujar fondo de pantalla
        GRRLIB_DrawImg(pe.x, pe.y, tex_a, 0, 2, 2, GRRLIB_WHITE);
        GRRLIB_Render();
    }
    GRRLIB_Exit(); // desiniciar grrlib
    return 0;//apagar
}
