#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>
#include <joystick.h>
#include <_suzy.h>
#include <_mikey.h>

extern char lynxtgi[];
extern char lynxjoy[];

extern unsigned char spaceship[]; //sprite
extern unsigned char star[]; //sprite
// extern unsigned char *musicptr; //song


//Base palette for gameplay
static int mypalette[] =  {
    
  0x0000, 0x0471, 0x0692, 0x0e46, 0x0004, 0x0818,
  0x0666, 0x0888, 0x0616, 0x0b7f, 0x066e, 0x0b3b, 
  0x0513, 0x0b55, 0x0818, 0x0eee
  
};

//Function for filling the registers that represent the color palette
void set_palette(const int* palette){
    
    char index;
    
    for(index = 0; index < 0x10; index++){
        
        POKE(0xFDA0 + index, palette[index]>>8);
     
        POKE(0xFDB0 + index, palette[index] & 0xFF);
        
    }
    
};

//need this struct to point to the seperate channels of music
typedef struct {
    unsigned char *music0;
    unsigned char *music1;
    unsigned char *music2;
    unsigned char *music3;
} song_t;

extern song_t musicptr; //pull in our externally referenced music data.

//Install drivers and initial colors for text
void initialize(){
    
	tgi_install(&lynxtgi);
        
	tgi_init();
        
	joy_install(&lynxjoy);
        
        lynx_snd_init();
        
	CLI();

	tgi_setbgcolor(COLOR_BLUE); //txt line bg color
        
	tgi_setpalette(tgi_getdefpalette());
	
	tgi_setcolor(COLOR_WHITE);
        
	tgi_clear();
        
        lynx_snd_pause();
        
        //play each channel of our song
        lynx_snd_play ( 0 , musicptr.music0);
        
        lynx_snd_play ( 1 , musicptr.music1);
        
        lynx_snd_play ( 2 , musicptr.music2);
        
        lynx_snd_play ( 3 , musicptr.music3);
        
        lynx_snd_continue();
/*	
	while (tgi_busy()){
            
            
	};*/
}

//---------------------Sprites

//stars
SCB_REHV_PAL  starsprite_01 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV,
 0x01,
 0x0000,
 star, //sprite data
 80,3, //position x,y
 0x0300, 0x1f00, //scale x,y
 { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,} //palette
    
};

SCB_REHV  starsprite_02 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV | REUSEPAL,
 0x01,
 0x0000,
 star, //sprite data
 80,3, //position x,y
 0x0300, 0x1f00, //scale x,y
    
};

SCB_REHV  starsprite_03 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV | REUSEPAL,
 0x01,
 0x0000,
 star, //sprite data
 86,3, //position x,y
 0x0200, 0x0a00, //scale x,y
    
};

SCB_REHV  starsprite_04 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV | REUSEPAL,
 0x01,
 0x0000,
 star, //sprite data
 92,3, //position x,y
 0x0100, 0x0300, //scale x,y
    
};

SCB_REHV  starsprite_05 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV | REUSEPAL,
 0x01,
 0x0000,
 star, //sprite data
 98,3, //position x,y
 0x0100, 0x0300, //scale x,y
    
};

SCB_REHV  starsprite_06 = {
    
 BPP_4 | TYPE_NONCOLL,
 REHV | REUSEPAL,
 0x01,
 0x0000,
 star, //sprite data
 104,3, //position x,y
 0x0200, 0x0a00, //scale x,y
    
};

//Spaceship
SCB_REHV  spaceshipsprite = {
    
 BPP_4 | TYPE_NORMAL,
 REHV | REUSEPAL, //need to reset values for this sprite before reading them THEN tell it to use the same palette as well.
 0x01,
 0x0000,
 spaceship, //sprite data
 80,42, //position x,y
 0x0200, 0x0200, //scale x,y
    
};

int random_number;

int fade_delay = 0;

int btn_delay = 0;

int scale_direction = 1;  //1-get bigger, 0-get smaller

int fade_direction = 0;

//Star vars

int star_delay = 0;

int start_wall = -30;

int end_wall = 105;

//warning lights vars

int warning_delay = 0;

int warning_direction = 1;

int warning_lights = 0;

long joy;


void main(void){
	
	initialize();
        
        //set random positions of stars
        
        starsprite_01.hpos = rand()%150;
        
        starsprite_02.hpos = rand()%150;
        
        starsprite_03.hpos = rand()%150;
        
        starsprite_04.hpos = rand()%150;
        
        starsprite_05.hpos = rand()%150;
        
        starsprite_06.hpos = rand()%150;
            

	while (1)
	{
            
            tgi_clear();
            
            
            //counters
            
            star_delay ++;
            
            fade_delay ++;
            
            btn_delay += 1;
            
            random_number = rand()%150;
            
            
            joy = joy_read(JOY_1);
            
            set_palette(mypalette);
            
            
            //Clear the screen to avoid smearing
            
            tgi_setcolor(COLOR_WHITE);
            
            tgi_setbgcolor(COLOR_BLACK);
            
        //Background Star Movement and Checks
            
            if(star_delay <= 9){
                
                starsprite_01.vpos += 3;
                
                starsprite_02.vpos += 3;
                
                starsprite_03.vpos += 2;
                
                starsprite_04.vpos += 1;
                
                starsprite_05.vpos += 1;
                
                starsprite_06.vpos += 2;
                
                if(starsprite_01.vpos >= end_wall){
                    
                 starsprite_01.vpos = start_wall - rand()%50;   
        
                 starsprite_01.hpos = rand()%150;
                    
                }
                
                if(starsprite_02.vpos >= end_wall){
                    
                 starsprite_02.vpos = start_wall - rand()%80;  
        
                 starsprite_02.hpos = rand()%150; 
                    
                }
                
                if(starsprite_03.vpos >= end_wall){
                    
                 starsprite_03.vpos = start_wall - rand()%13;   
        
                 starsprite_03.hpos = rand()%150;
                    
                }
                
                if(starsprite_04.vpos >= end_wall){
                    
                 starsprite_04.vpos = start_wall - rand()%20;   
        
                 starsprite_04.hpos = rand()%150;
                    
                }
                
                if(starsprite_05.vpos >= end_wall){
                    
                 starsprite_05.vpos = start_wall - rand()%5;  
        
                 starsprite_05.hpos = rand()%150; 
                    
                }
                
                if(starsprite_06.vpos >= end_wall){
                    
                 starsprite_06.vpos = start_wall - rand()%18; 
        
                 starsprite_06.hpos = rand()%150;  
                    
                }
                
                star_delay = 0;
                
            }
            
        //update our palettes for fades and other color changes
            
            //spaceship lights fade down
            if(fade_direction == 0 && fade_delay >= 5){
                
                mypalette[3] -= 0x0100;
                
                mypalette[3] -= 0x0010;
                
                mypalette[3] -= 0x0001;
                
                fade_delay = 0;
                
                if(mypalette[3] <= 0x0a00){
                    
                 fade_direction = 1;   
                    
                }
                
            }
            
            //spaceship lights fade up
            if(fade_direction == 1 && fade_delay >= 5){
                
                mypalette[3] += 0x0100;
                
                mypalette[3] += 0x0010;
                
                mypalette[3] += 0x0001;
                
                fade_delay = 0;
                
                if(mypalette[3] >= 0x0f57){
                    
                 fade_direction = 0;   
                    
                }
                
            }
            
        //warning lights
        
            if(warning_lights == 1){
                
                warning_delay += 1;
        
            //fade up
            if(warning_direction == 1 && warning_delay >= 6){
                
                mypalette[0] += 0x0004;
                
                warning_delay = 0;
                
                if(mypalette[0] >= 0x000b){
                    
                    mypalette[0] = 0x000f;
                    
                    warning_direction = 0;
                    
                }
                
            }
        
            //fade down
            if(warning_direction == 0 && warning_delay >= 6){
                
                mypalette[0] -= 0x0001;
                
                warning_delay = 0;
                
                if(mypalette[0] <= 0x0000){
                    
                    mypalette[0] = 0x0004;
                    
                    warning_direction = 1;
                    
                }
                
            }
                
                
            }
            
            
        //Draw our text for the screen
            
        //draw our sprites for this VBL
            
            tgi_sprite(&starsprite_01);
            
            tgi_sprite(&starsprite_02);
            
            tgi_sprite(&starsprite_03);
            
            tgi_sprite(&starsprite_04);
            
            tgi_sprite(&starsprite_05);
            
            tgi_sprite(&starsprite_06);
            
            tgi_sprite(&spaceshipsprite);
            
            tgi_outtextxy(28,80, "---WARNING---");
            
        //vsync and update everything
            
            tgi_updatedisplay(); 
            
            while(tgi_busy());
            
            
//Spaceship Joypad Actions------------------------------------------
            
            //move up
            if(joy & JOYPAD_UP){
                
             spaceshipsprite.vpos -= 1;
                
            }
            
            //move left
            if(joy & JOYPAD_LEFT){
                
             spaceshipsprite.hpos -= 1;
                
            }
            
            //move down
            if(joy & JOYPAD_DOWN){
                
             spaceshipsprite.vpos += 1;
             
            }
            
            //move right
            if(joy & JOYPAD_RIGHT){
                
             spaceshipsprite.hpos += 1;
                
            }
            
            if(joy & BUTTON_INNER && btn_delay >= 20){
                
                //Warning lights
                if(warning_lights == 0){
                    
                    warning_lights = 1;
                    
                    mypalette[0] = 0x0000;
                    
                }
                
                //Warning lights
                else if(warning_lights == 1){
                    
                    warning_lights = 0;
                    
                    mypalette[0] = 0x0000;
                    
                }
                
             btn_delay = 0;
             
             warning_delay = 0;
             
            }
     
		
	};//While loop end
}
