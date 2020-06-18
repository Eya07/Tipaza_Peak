/**
* @file main.c
* @autor eya dhamna
* @date  Mai ,2020
*
*testing program for velocity 
*
*/

#include "perso.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"



personnage initperso (personnage c)
{char scoree[100];

	TTF_Init();

	//chargement du spritesheet 
	c.sprite= IMG_Load("sprite.png");  
	

	//Définition des différentes positions du personnage par rapport au background 
	c.position_perso.x = 50;
  	c.position_perso.y = 400;
	c.position_perso.w=hero_sprite_W;
	c.position_perso.h=hero_sprite_H;

	c.direction=1;    //1 à droite et 0 à gauche 

	//chargement des images de la structure vie en les stockant dans un tableau 
	c.vie_perso.vie[1]=IMG_Load("image_de_vie1.jpg");
	c.vie_perso.vie[2]=IMG_Load("image_de_vie2.jpg");
	c.vie_perso.vie[3]=IMG_Load("image_de_vie3.jpg");
	c.vie_perso.vie[0]=IMG_Load("image_de_vie0.jpg");

	//Définition de la position de ces images par rapport au background
	c.vie_perso.position_de_vie.x=20 ; 
	c.vie_perso.position_de_vie.y=10 ; 
	
	//initialisation de nbre de vie 
	c.vie_perso.nbredevie=3;

	//initialisation du score 
	c.score_perso.score_atteint=0;
	
	//Définition de la position de frame
	c.position_sprite.x=0;
	c.position_sprite.y=300;
	c.position_sprite.w=hero_sprite_W;
	c.position_sprite.h=hero_sprite_H;

		
	//initialisation des compteurs	
	c.numr=-1;
	c.numl=-1;
	
	//Définition de la couleur noire 	
	SDL_Color policeNoire={0,0,0};

	//ouverture de la police 
	c.score_perso.police_score= TTF_OpenFont("angelina.TTF" , 40);

	//j'ai effectué l'écriture de texte selon le format que j'en aurais besoin 
	sprintf(scoree,"Score: %d",c.score_perso.score_atteint);

	//écriture dans le champ sdl surface* le score 
        c.score_perso.score_texte= TTF_RenderText_Blended(c.score_perso.police_score,scoree,policeNoire);	

	//Définition de la position du texte du score 
	c.score_perso.position_score.x=50 ;
	c.score_perso.position_score.y=70 ;

	c.velocity=1;

	c.speed=0;

	
  return c;
}
///******************************************************************************************************************************************



void affichageperso(personnage c, SDL_Surface * screen)

{
	SDL_BlitSurface(c.vie_perso.vie[c.vie_perso.nbredevie], NULL, screen, &c.vie_perso.position_de_vie);
	SDL_BlitSurface(c.score_perso.score_texte, NULL, screen, &c.score_perso.position_score);
	SDL_BlitSurface(c.sprite,&c.position_sprite, screen, &c.position_perso);	
}





///********************************************************************************************************************************


void freesurfaceperso(personnage *c)
{
int i ;
SDL_FreeSurface(c->sprite);

for(i=0;i<4;i++)
{
SDL_FreeSurface(c->vie_perso.vie[i]);
}

TTF_CloseFont(c->score_perso.police_score); 

TTF_Quit();
}




//******************************************************************************************************************************************

void animperso (personnage *c)
{
		if (c->direction ==1)
                {	c->numr++; //le compteur de droite augmente 

			if(c->numr==6)//si on arrive à la fin du spritesheet on reprend  
				{
				c->numr=0;
				c->position_sprite.x=0;
				}
			else 		//si non on avance vers la frame suivante on multipliant la largeur de frame par le compteur  
				{
				c->position_sprite.x=c->numr*hero_sprite_W;
				}
				c->position_sprite.y=300;
                }
                else if (c->direction ==0)   
		{	c->numl++;
			if(c->numl==6)
			{
				c->numl=0;
				c->position_sprite.x=0;
		   	}
			else 
			{
				c->position_sprite.x=c->numl*hero_sprite_W;
			}
				c->position_sprite.y=0;
                 }		
					
}


void mouvement (personnage *c)
{
if(c->direction ==1)
{

c->position_perso.x+=5;

if(c->position_perso.x +c->position_sprite.w >1280)
c->position_perso.x=1280-c->position_sprite.w ;
/*if(c->speed==1)
  {
    
	c->position_perso.x+= 10 + c->velocity ;
 	
  }*/
}
else if (c->direction ==0)
{

c->position_perso.x-=5;

if(c->position_perso.x +c->position_sprite.w <0)
c->position_perso.x=10;
  /*if(c->speed==1)
  {

	c->position_perso.x-= (10 + c->velocity) ;
   
  }*/
}
}

///******************************************************************************************************************************************

//scrolling 


void initialiser (background *b) 
{
  
  b->img=IMG_Load("background.png") ;
  b->pos.x=0 ;
  b->pos.y=0 ;
  
}

void setup (SDL_Surface *screen, background *b)
{
  SDL_BlitSurface(b->img,NULL,screen, &(b->pos));
  SDL_Flip(screen) ;
}

///******************************************************************************************************************************************

void scrolling_droit (SDL_Surface *screen , background *b, personnage *c)
{
 if (b->pos.x<=mapw)
   b->pos.x+=10 ;

          
if(c->speed==1)
  {
    if(c->velocity<100)
    {
        c->velocity+=1 ;
	b->pos.x+=10 + c->velocity ; 
	SDL_Delay(50);
    }
		
  }

}

///******************************************************************************************************************************************

void scrolling_gauche (SDL_Surface*screen , background *b,personnage *c)
{
 if (b->pos.x>=0)
   b->pos.x-=10 ;

  if(c->speed==1)
  {
    if(c->velocity<100)
    {
        c->velocity+=1 ; 
	b->pos.x-= (10 + c->velocity) ;
	SDL_Delay(50);
    }
	 
  }
}

///******************************************************************************************************************************************

void evenement (SDL_Surface *screen ,background *b,int direction, personnage *c  )
{

                    if(direction==1) // Flèche droite
            	
                          scrolling_droit (screen ,b,c) ;
                          

                   

                     if(direction==0) // Flèche gauche
                          scrolling_gauche (screen ,b,c) ;
                        

}



///******************************************************************************************************************************************
void moveChar (SDL_Event event, SDL_Rect *posobj, int inWhichDir){
switch (event.key.keysym.sym){
  case SDLK_SPACE:
  if(inWhichDir != 1){
    posobj->y -=10;
  }
  break;
  case SDLK_RIGHT:
    if(inWhichDir != 2){
      posobj->x +=10;
    }
  break;
  case SDLK_LEFT:
    if(inWhichDir != 3){
        posobj->x -= 10;
      }
   break;
   case SDLK_DOWN:
     if(inWhichDir != 4){
         posobj->y += 10;
       }
    break;
  }

}
void moveCharByMouse(SDL_Surface *screen,SDL_Rect * persoPos, SDL_Event event, char whichDirection){
  switch(event.type){
         case SDL_MOUSEBUTTONDOWN:
             if(event.button.button == SDL_BUTTON_LEFT){
              persoPos->x += 10;
           }
         break;
   }
}
char animCharMouse (charac c, SDL_Surface *screen, SDL_Event event){
  char dir;
  static int i,j;
  if (event.button.x >= 480) {
     j = 13;
    if (i > 12){
       i = 0;
     SDL_BlitSurface(c.spriteright[i], NULL, screen, &c.positionChar);
     dir = 'r';
     return dir;
    }else{
      i++;
      SDL_BlitSurface(c.spriteright[i], NULL, screen, &c.positionChar);
      dir = 'r';
      return dir;
}
  }else{
    j = 13;
    if (j > 12){
       j = 0;
     SDL_BlitSurface(c.spriteleft[j], NULL, screen, &c.positionChar);
     dir = 'l';
     return dir;
    }else{
    j++;
  SDL_BlitSurface(c.spriteleft[j], NULL, screen, &c.positionChar);
  dir = 'l';
  return dir;
}
  }
  return 'n';

}



+
