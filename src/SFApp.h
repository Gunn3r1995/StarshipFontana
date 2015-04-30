#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

  void    FireProjectile();
private:
  SDL_Surface           * surface;
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>      player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > alien_bosses;//adding alien bosses to the list
  list<shared_ptr<SFAsset> > asteroids; //adding asteroids to list
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > walls; //adding walls to list
  list<shared_ptr<SFAsset> > lives; //adding lifes to list
  list<shared_ptr<SFAsset> > game_overs; // adding game over to list
  list<shared_ptr<SFAsset> > life_game_overs; // adding game over to list
  list<shared_ptr<SFAsset> > wins; // adding game over to list
 // list<shared_ptr<SFAsset> > stars; // adding stars to list


  //handles the lifes for aliens and players.
  int alienLives = 36;
  int playerLives = 5;
  int bossLives =30;
  
  int fire; 
  //counter total for the score. 
  int score = 0; 

  

  SFError OnInit();
};
#endif
