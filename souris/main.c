/**
* @file main.c
* @autor eya dhamna
* @date  Mai ,2020
*
*testing program for velocity 
*
*/



#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "perso.h"


int main()
{

	SDL_Surface *screen = NULL ;
	SDL_Event event;
	personnage c ;
	background b ;

int running=1 ;



 screen= SDL_SetVideoMode(1360, 700, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

  
  initialiser (&b ) ;
  setup (screen,&b) ;
  c=initperso(c);


  affichageperso(c,screen);
  SDL_Flip(screen);


  SDL_EnableKeyRepeat(10, 10);
  while(running)
	{
   
   	SDL_PollEvent(&event);
    switch(event.type)
            {
	case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            	{	
		case SDLK_RIGHT: 
		
			c.direction=1;
			
		break;
		case SDLK_LEFT: 
			
			c.direction=0;
			
			
		break;
		case SDLK_ESCAPE:
			running = 0;
		break;	

		
		}
	break ;
	case SDL_KEYUP:
	
                switch(event.key.keysym.sym)
            	{	
		case SDLK_LCTRL:
	     
		 c.speed+=1;

		if(c.speed>=2)
		    {
		     c.speed=0;
		     c.velocity=1;
		    }	

                 if(c.speed==0)
		    {
			b.pos.x+=10;
			c.velocity=1;
		    }
		
		break ;
                  }  //switch2
        break;
 		
		
                 }
	
	evenement (screen ,&b,c.direction,&c ) ;
	
	SDL_BlitSurface(b.img,&(b.pos),screen, NULL);
	SDL_Flip(b.img);
	
	
	mouvement (&c);
	animperso(&c);
	affichageperso(c,screen);

	
	c.direction=-1;
	
	SDL_Flip(b.img);
	SDL_Flip(screen);
	

     }

    

    return EXIT_SUCCESS;
}


