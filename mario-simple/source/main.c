//la cosa esta diseñada para ser jugada con el wiimote alado.A
#include <grrlib.h>//include GRRLIB
#include <stdlib.h>//include C
#include <stdio.h>//include C

#include <wiiuse/wpad.h>//include wiimotes
#include "all_gfx.h" //include graphics

typedef struct{     //variables 
    float x;        //posicion X
    float y;        //posicion Y
    float vy;       //gravedad
} varimario;
varimario vamario;

//int main
int main() {
    int n = 0;      //variables
    GRRLIB_Init();  //iniciar GRRLIB
    WPAD_Init();    //iniciar wiimotes

    GRRLIB_Settings.antialias = false; //desactivar antialias
    GRRLIB_texImg *tex_grr = GRRLIB_LoadTexture(logo);//cargar textura de logo
    GRRLIB_texImg *tex_mario = GRRLIB_LoadTexture(mario);//cargar textura de mario
    GRRLIB_texImg *tex_bg = GRRLIB_LoadTexture(Bg);//cargar fondo de pantalla

       //splash de grrlib
    for(n = 0; n < 502; n ++){
        GRRLIB_DrawImg(0, 0, tex_grr, 0, 1, 1, GRRLIB_WHITE); // dibujar textura
        GRRLIB_Render();//renderizar
    }
    GRRLIB_FreeTexture(tex_grr);//librerar textura

    //bucle para siempre
    while(1){
        vamario.y += vamario.vy; //sumarle a la posicion y la gravedad
        vamario.vy += 0.123;     //sumarle a la gravedad 0.123

        int wpadheld = WPAD_ButtonsHeld(0);//variable de control
        int wpadown = WPAD_ButtonsDown(0);//Variable de control
        WPAD_ScanPads();    //escanear los controles

        if(wpadheld & WPAD_BUTTON_UP) vamario.x -= 2;   //si tecla arriba esta presionado ir a isquierda
        if(wpadheld & WPAD_BUTTON_DOWN) vamario.x += 2; //si tecla abajo esta presionado ir a derecha

        if(vamario.y > 440){ //si la posicion Y es mayor que 440
            vamario.y = 440;//y = 440
            if(wpadown & WPAD_BUTTON_2) vamario.vy = -4.6;//si el boton 2 fue presionado, saltar
        }

        GRRLIB_FillScreen(GRRLIB_BLACK);    // llenar la pantalla de negro
        GRRLIB_DrawImg(0, 0, tex_bg, 0, 4, 4, GRRLIB_WHITE);//dibujar fondo de pantalla
        GRRLIB_DrawImg(vamario.x, vamario.y , tex_mario, 0, 2, 2, GRRLIB_WHITE);
        GRRLIB_Render();//renderizar
    }
    GRRLIB_FreeTexture(tex_mario);              //liberar textura
    GRRLIB_FreeTexture(tex_bg);                 //liberar fondo de pantalla
    
    GRRLIB_Exit(); // desiniciar grrlib
    return 0;//apagar
}
