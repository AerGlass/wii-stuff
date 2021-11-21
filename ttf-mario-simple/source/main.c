#include <grrlib.h>
#include <stdlib.h>
#include <stdio.h>

#include <wiiuse/wpad.h>
#include "all_gfx.h"

typedef struct{ //variables para mario
    float x; //posicion X
    float hflip; //scaleX
    float vflip;  //scaleY
    float y; //Posicion Y
    float vy; //gravedad
} varimario;
varimario vamario;

//int main
int main() {
    vamario.hflip = 2;
    vamario.vflip = 2;
    int n = 0;
    float bg_x = 0;
    GRRLIB_Init();      //Iniciar GRRLIB
    WPAD_Init();        //Iniciar control de wii
    
    GRRLIB_Settings.antialias = false;
    GRRLIB_texImg *tex_grr = GRRLIB_LoadTexture(logo); //cargar logo de grrlib
    GRRLIB_texImg *tex_mario = GRRLIB_LoadTexture(mario); //Cargar textura de mario
    GRRLIB_texImg *tex_bg = GRRLIB_LoadTexture(Bg); //cargar fondo de pantalla
    GRRLIB_ttfFont *myFont = GRRLIB_LoadTTF(font_ttf, font_ttf_size); //cargar fuente

    for(n = 0; n < 502; n ++){
        int wpadown = WPAD_ButtonsDown(0); //variable para control
        WPAD_ScanPads(); // escanear control
        if(wpadown & WPAD_BUTTON_A) break;
        if(wpadown & WPAD_BUTTON_B) break;
        if(wpadown & WPAD_BUTTON_1) break;
        if(wpadown & WPAD_BUTTON_2) break;
        if(wpadown & WPAD_BUTTON_UP) break;
        if(wpadown & WPAD_BUTTON_DOWN) break;
        if(wpadown & WPAD_BUTTON_LEFT) break;
        if(wpadown & WPAD_BUTTON_RIGHT) break;
        
        GRRLIB_DrawImg(0, 0, tex_grr, 0, 1, 1, GRRLIB_WHITE); // Dibujar imagen
        GRRLIB_Render(); //renderizar
    }
    GRRLIB_FreeTexture(tex_grr); //liberar textura de grrlib

    for(n = 0; n < 302; n++){
        GRRLIB_PrintfTTF (0,0, myFont,"Please hold wii remote sideways",32,0xe7d8c9FF);//poner texto en la pantalla
        GRRLIB_Render();
    }
    while(1){
        vamario.y += vamario.vy; //sumarle a la posicion Y la gravedad
        vamario.vy += 0.123; //sumarle a la gravedad 0.123

        int wpadheld = WPAD_ButtonsHeld(0); //variables para el control
        int wpadown = WPAD_ButtonsDown(0); //variables para el control
        WPAD_ScanPads(); //escanear control

        if(wpadheld & WPAD_BUTTON_UP) {vamario.x -= 2; //si el boton arriba fue presionado ir a la isquierda
        vamario.hflip = -2; //hacer flip horinzotal al personaje
        }
        if(wpadheld & WPAD_BUTTON_DOWN) {vamario.x += 2; //si el boton abajo fue presionado ir a derecha
        vamario.hflip = 2; //quitar flip horizontal
        }
        if(wpadown & WPAD_BUTTON_1) vamario.vflip = 7; // si el boton 1 fue presionado
        if(vamario.y > 440){
            vamario.y = 440; // colision
            if(wpadown & WPAD_BUTTON_2) vamario.vy = -4.6; // si el boton 2 fue presionado, saltar
        }
        if(vamario.x < 0) vamario.x = 0; // colisiones
        if(vamario.x > 720) vamario.x = 720; // colisiones

        GRRLIB_FillScreen(GRRLIB_BLACK);    // Clear the screen
        GRRLIB_DrawImg(bg_x, 0, tex_bg, 0, 4, 4, GRRLIB_WHITE); //dibujar fondo de pantalla
        GRRLIB_DrawImg(vamario.x, vamario.y , tex_mario, 0, vamario.hflip, vamario.vflip, GRRLIB_WHITE); //dibujar imagen
        GRRLIB_PrintfTTF (0,0, myFont,"Press 1 to scale the sprite",32,0xe7d8c9FF);//poner texto en la pantalla
        GRRLIB_Render();
    }
    GRRLIB_FreeTTF(myFont);
    GRRLIB_FreeTexture(tex_mario);
    GRRLIB_FreeTexture(tex_bg); 
    
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    return 0;
}
