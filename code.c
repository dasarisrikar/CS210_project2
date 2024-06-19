//after adding game over
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*******************************************************************************
 * This file provides address values that exist in the DE1-SoC Computer
 ******************************************************************************/

#ifndef SYSTEM_INFO
#define SYSTEM_INFO

#define BOARD				"DE1-SoC"


#define SW_BASE				0xFF200040


#endif
void write_pixel(int x, int y, short colour);
void clear_screen();
void draw_line(int x1, int y1, int y2, int x2, short color);
int ran1();
int ran2();
void dino2();//no neck dino
void write_char(int x, int y, char c);
void draw_game_over();

#define VGA_WIDTH 320
#define VGA_HEIGHT 240
#define white 0xffff
#define black 0x0000
#define RED 0xff00
volatile int pixel_buffer_start; 
int main() {
    // Clear the screen
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;//location of pixxel buffer controller
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    draw_line(0, 200, 210, 320, white);
	 draw_line(40,180,200,60,white);
     draw_line(45,170,180,55,white);
    int dx = 1;
    int dy = 1;
    srand(time(NULL));  // Seed the random number generator
    int ab=0;
	int a1=ran1();
    int a2=ran2();
    int b1;
    int b2;
    int dx1 = 2;
    int dx2=2;
    int c1;
	int d1=0;
	int d2=0;
    int bang=0;
    volatile int *SW_switch_ptr = (int *)SW_BASE;
    while (1) {
         int SW_value = *(SW_switch_ptr); 
        //for dino
        if ((SW_value & 0x1) && d1==0 && !(SW_value & 0x2)) {
			b1=0;
			b2=0;
			d1++;
            bang=1;
		}
		else if(!(SW_value & 0x1)){
			d1=0;
		}
           if(b1==0 && b2==0){
			draw_line(40,180,200,60,black);
            draw_line(45,170,180,55,black);
            draw_line(40,200-dx1,202-dx1,60,black);
            draw_line(40,180-dx1,200-dx1,60,white);
            draw_line(45,170-dx1,180-dx1,55,white);
            dx1+=2;
            if(dx1==80){
                b1++;
                dx1=2;
            }
           }
           else if(b1!=0 && b2==0){
            draw_line(40,88+dx1,100+dx1,60,black);
            draw_line(40,100+dx1,120+dx1,60,white);
            draw_line(45,90+dx1,100+dx1,55,white);
            dx1+=2;
            if(dx1==80){
              b2++;
              dx1=2;
              b1=0;
            }
           }
           else if(b1==0 && b2!=0){
            bang==0;
            draw_line(40,180,200,60,white);
            draw_line(45,170,180,55,white);
           }
        
        //for dino3
        if ((SW_value & 0x2) && d2==0 && !(SW_value & 0x1)) {
			c1=0;
			d2++;
            bang=2;
		}
		else if(!(SW_value & 0x2)){
			d2=0;
		}
            if(c1!=0 && bang==2){
               draw_line(40,180,200,60,white);
               draw_line(45,170,180,55,white);
               dx2=4;
               bang=0;
            }
            else if(c1==0 && bang==2){
                dino2();
                dx2+=2;
                if(dx2>=160){
                    c1++;
                }
            }
       if(bang!=1 && bang!=2){
		    draw_line(40,180,200,60,white);
            draw_line(45,170,180,55,white);
        }
		
        
     
        //for blocks
        draw_line(320 - dx, 180, 200, 322 - dx, black);
        draw_line(300 - dx, 180, 200, 320 - dx, white);
        dx += 1;
		
        if(300-dx<120 ){
			                 if(((300-dx<=45)&&(300-dx>40))||((300-dx>60)&&(300-dx<70))){
						 		 if(SW_value & 0x1){
						 			//printf("%d",SW_value);
									goto C;
						 		 }
				
						 	}
			                if(300-dx==60){
								if(bang!=1){
									goto C;
								}
							}
			                if(bang==2){
								goto C;
							}
						 }
        if (300 - dx <= a1) {
           ab++;
        }
		if(ab>0){
            if(a2==0){
                    // Clear the previous position of the block
                    draw_line(320 - dy, 180, 200, 322 - dy, black);
                    draw_line(300 - dy, 180, 200, 320 - dy, white);
                    dy += 1;
                    if (300 - dy == 0) {
                        dy = 1;
                        ab=0;
                        a2=ran2();
                        draw_line(0,180,200,25,black);
                        
						 if(300-dy<120 ){
			                 if(((300-dy<=45)&&(300-dy>40))||((300-dy>60)&&(300-dy<70))){
						 		 if(SW_value & 0x1){
						 			//printf("%d",SW_value);
									goto C;
						 		 }
				
						 	}
							 if(300-dy==60){
								if(bang!=1){
									goto C;
								}
							}
			                if(bang==2){
								goto C;
							}
						 }
		       }
            }
            else{
                 // Clear the previous position of the block
                    draw_line(320 - dy, 0, 170, 321 - dy, black);
                    draw_line(300 - dy, 0, 170, 320 - dy, white);
                    dy += 1;
                    if (300 - dy == 0) {
                        dy = 1;
                        ab=0;
                        a2=ran2();
                        draw_line(0,0,170,25,black);
						
        if(300-dy<120 ){
			                 if(((300-dy<=45)&&(300-dy>40))||((300-dy>60)&&(300-dy<70))){
						 		 if(SW_value & 0x2){
						 			//printf("%d",SW_value);
									goto C;
						 		 }
				
						 	}
			if(300-dy==60){
								if(bang!=2){
									goto C;
								}
							}
			                if(bang==1){
								goto C;
							}
						 }

                    }
            }
		}
        if (300 - dx == 0) {
            dx = 1;
            a1=ran1();
			draw_line(0,180,200,25,black);
        }
        
        // Short delay loop
        for (int i = 0; i < 100000; i++) {
			
            // Adjust the loop count for desired delay
			
        }
    }

   C: // Game over message
    clear_screen();
    draw_game_over();
    
}
void draw_box(int x, int y, int width, int height, short int colour) {
    int x_increment,y_increment;
	for ( x_increment = 0 ; x_increment < width; x_increment++) {
		for ( y_increment = 0 ; y_increment < height; y_increment++) {
			plot_pixel(x + x_increment, y + y_increment, colour);
		}
	}
}
void plot_pixel(int x, int y, short int line_colour) {
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_colour;
}
void draw_game_over() {
    // "G"
    draw_box(20, 50, 20, 5, RED);  // Top horizontal line
    draw_box(15, 50, 5, 30, RED);   // Left vertical line
    draw_box(20, 75, 20, 5, RED);   // Bottom horizontal line
    draw_box(35, 65, 5, 15, RED);   // Right vertical line on bottom
    draw_box(25, 65, 10, 5, RED);   // Middle horizontal line

    // "A"
    draw_box(45, 50, 5, 30, RED);   // Left vertical line
    draw_box(50, 50, 15, 5, RED);   // Top horizontal line
    draw_box(65, 50, 5, 30, RED);   // Right vertical line
    draw_box(50, 65, 15, 5, RED);   // Middle horizontal line

    // "M"
    draw_box(75, 50, 5, 30, RED);   // First vertical line
    draw_box(80, 50, 5, 15, RED);   // First slanting line
    draw_box(85, 50, 5, 30, RED);   // Middle vertical line
    draw_box(90, 50, 5, 15, RED);   // Second slanting line
    draw_box(95, 50, 5, 30, RED);   // Last vertical line

    // "E"
    draw_box(105, 50, 5, 30, RED);  // Left vertical line
    draw_box(105, 50, 20, 5, RED);  // Top horizontal line
    draw_box(105, 65, 15, 5, RED);  // Middle horizontal line
    draw_box(105, 75, 20, 5, RED);  // Bottom horizontal line

    // "O"
    draw_box(155, 50, 5, 30, RED);  // Left vertical line
    draw_box(160, 50, 15, 5, RED);  // Top horizontal line
    draw_box(175, 50, 5, 30, RED);  // Right vertical line
    draw_box(160, 75, 15, 5, RED);  // Bottom horizontal line
    
	// "U"
	draw_box(185, 50, 5, 25, RED);  // Left vertical line
	draw_box(195, 50, 5, 25, RED);  // Right vertical line
	draw_box(190, 75, 5, 5, RED);   // Bottom middle horizontal segment, slightly lower to simulate a curve

	// "E"
    draw_box(205, 50, 5, 30, RED);  // Left vertical line
    draw_box(205, 50, 20, 5, RED);  // Top horizontal line
    draw_box(205, 65, 15, 5, RED);  // Middle horizontal line
    draw_box(205, 75, 20, 5, RED);  // Bottom horizontal line

    // "R"
    draw_box(230, 50,  5, 30, RED);   // Left vertical line
    draw_box(235, 50, 15,  5, RED);   // Top horizontal line
    draw_box(250, 50,  5, 30, RED);   // Right vertical line top (approximate the upper curve)
    draw_box(245, 65,  5,  5, RED);    // Middle horizontal line (corner)
    draw_box(235, 65, 10,  5, RED);   // Middle horizontal line (extension to left)

    char* s = "ON SWITCH 1 TO RESTART THE GAME";
    int  m = 20; // Center the message horizontally
    while (*s) {
        write_char(m, 40, *s);
        m++; // Move to the next character position
        s++;
    }

}
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char *character_buffer = (volatile char *)(0x09000000 + (y<<7) + x);
  *character_buffer=c;
}
void dino2(){
    draw_line(40,180,200,60,black);
     draw_line(45,170,180,55,black);
    draw_line(40,180,200,60,white);
    draw_line(45,165,180,55,black);
}
int ran2(){
    int r=rand()%2;
    return r;
}
int ran1() {
    int min = 120;
    int max = 200;
    int random_number = rand() % (max - min + 1) + min;
    return random_number;
}

void write_pixel(int x, int y, short colour) {
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

void clear_screen() {
    for (int x = 0; x < VGA_WIDTH; x++) {
        for (int y = 0; y < VGA_HEIGHT; y++) {
            write_pixel(x, y, 0); // Set pixel to black
        }
    }
}

void draw_line(int x1, int y1, int y2, int x2, short color) {
    for (int i = 0; i <= y2 - y1; i++) {
        for (int x = x1; x <= x2; x++) {
            write_pixel(x, y1 + i, color);
        }
    }
}