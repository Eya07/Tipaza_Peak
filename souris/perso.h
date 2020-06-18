/**
* @file perso.h
* @autor eya dhamna
* @date  Mai ,2020
*
*testing program for main character animation   
*
*/

#ifndef PERSO_H_
#define PERSO_H_
#include <stdio.h>

#include <stdlib.h>

#include "SDL/SDL.h"

#include "SDL/SDL_image.h"

#include "SDL/SDL_mixer.h"

#include "SDL/SDL_ttf.h"

#define mapw 6838 
#define maph 613

#define hero_sprite_W 200 
#define hero_sprite_H 300

/**
* @struct background
* @brief struct for background
*
*/

typedef struct 
{
  SDL_Surface *img ;
  SDL_Rect pos ; 

}background;

/**
* @struct vie
* @brief struct for life of hero
*
*/


typedef struct vie 
{
	int nbredevie ;/*!< entier */
	SDL_Surface *vie[4];/*!< surface */
	SDL_Rect position_de_vie ; /*!< rectangle */
	
}vie  ;

/**
* @struct score
* @brief struct for score of hero
*
*/


typedef struct score
{
	int score_atteint;/*!< entier */
	SDL_Rect position_score ; /*!< rectangle */
	TTF_Font *police_score; /*!< font */
	SDL_Surface *score_texte;/*!< surface */
	
}score  ;

/**
* @struct personnage
* @brief struct for hero
*
*/


typedef struct personnage
    {
	SDL_Surface *sprite;/*!< surface */
	SDL_Rect position_perso;/*!< rectangle */
	SDL_Rect position_sprite;/*!< rectangle */
	int direction;/*!< entier */
	int numr , numl ;/*!< entier */
	vie vie_perso ;/*!<vie */
	score score_perso ; /*!< score */
	int velocity ;/*!< entier */
	int speed ; /*!< entier */
     } personnage;

/**
* @brief to initialize hero 
* @param c=personnage 
* @return personnage 
*/
personnage initperso (personnage c);
/**
* @brief to display hero 
* @param c=personnage 
* @param screen the screen 
* @return nothing
*/
void affichageperso(personnage c, SDL_Surface * screen);
/**
* @brief to animate hero 
* @param c=personnage 
* @return nothing
*/
void animperso (personnage *c);
/**
* @brief to free memory from hero 
* @param c=personnage 
* @return nothing
*/
void freesurfaceperso(personnage *c);

void mouvement (personnage *c);

void initialiser (background *b) ;

void scrolling_gauche (SDL_Surface*screen , background *b,personnage *c);

void evenement (SDL_Surface *screen ,background *b,int direction, personnage *c  );

void scrolling_droit (SDL_Surface *screen , background *b, personnage *c);
void moveCharByMouse(SDL_Surface *screen,SDL_Rect * persoPos, SDL_Event event, char whichDirection);
char animCharMouse (charac c, SDL_Surface *screen, SDL_Event event);
void setup (SDL_Surface *screen, background *b);



#endif
