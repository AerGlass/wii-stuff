#include <grrlib.h> //incluir grrlib (IMPORTANTE)
#include <stdlib.h>
#include <stdio.h> //incluir C (IMPORTANTE)

#include <wiiuse/wpad.h>//para los controles
#include "all_gfx.h" //los graficos

//int main
int main() {
    int n = 0;
    GRRLIB_Init();      //Iniciar GRRLIB
    WPAD_Init();        //Iniciar control de wii
    
    GRRLIB_Settings.antialias = false;  //deshabilitar antialias
    GRRLIB_ttfFont *arial = GRRLIB_LoadTTF(arial_ttf, arial_ttf_size); //cargar fuente
    GRRLIB_ttfFont *myFont = GRRLIB_LoadTTF(font_ttf, font_ttf_size); //cargar fuente
    while(1){
        GRRLIB_FillScreen(GRRLIB_BLACK);    // Clear the screen
        GRRLIB_PrintfTTF(0, 0, arial, "Esto es arial!!!!!!", 32, COLOR_TEXT); //dibujar texto
        GRRLIB_PrintfTTF(32, 32, myFont, "Hecho con grrlib", 20, COLOR_TEXT); //dibujar texto
        GRRLIB_Render();
    }
    GRRLIB_FreeTTF(myFont);             //liberar fuente
    GRRLIB_FreeTTF(arial);              //liberar fuente

    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    return 0; //apagar
}
