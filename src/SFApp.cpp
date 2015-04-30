#include "SFApp.h"

SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
 

/* could not load star since the error, "Could not load asset of type 12" came up
  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  auto stars  = make_shared<SFAsset>(SFASSET_STAR, sf_window);
  auto star_pos = Point2(canvas_w, canvas_h);
  stars->SetPosition(star_pos);
*/

//set the player in the middle of the game board
  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w / 2.0f, 88.0f);
  player->SetPosition(player_pos);
  


  const int number_of_aliens = 9;
  for(int i=0; i<number_of_aliens; i++) {

    // place aliens
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens)+60 * i, 270.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

  for(int i=0; i<number_of_aliens; i++) {

    // place aliens
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens)+60 * i, 320.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

   for(int i=0; i<number_of_aliens; i++) {

    // place aliens
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens)+60 * i, 370.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }
  
     for(int i=0; i<number_of_aliens; i++) {

    // place aliens
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens)+60 * i, 420.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

   //placing walls
  const int number_of_walls = 15;
  for(int i=0; i<number_of_walls; i++) {
    // place an wall at width/number_of_walls * i
    auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
    auto pos   = Point2(625.0f,(canvas_h/number_of_walls+16)+32.0f * i);
    wall->SetPosition(pos);
    walls.push_back(wall);
  }

  const int number_of_walls2 = 15;
  for(int i=0; i<number_of_walls2; i++) {
    // place an wall at width/number_of_walls * i
    auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
    auto pos   = Point2(15.0f ,(canvas_h/number_of_walls2+16)+32.0f * i);
    wall->SetPosition(pos);
    walls.push_back(wall);
  }

  //spawn the coins randomly
  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2(rand() % 600, rand() % 400 + 600);
  coin->SetPosition(pos);
  coins.push_back(coin);

   // place life sprite
  const int number_of_lives = 5;
  for(int i=0; i<number_of_lives; i++) {
 
    auto life = make_shared<SFAsset>(SFASSET_LIFE, sf_window);
    auto pos   = Point2((canvas_w/number_of_lives/4) * i +(canvas_w/number_of_lives)*2,465);
    life->SetPosition(pos);
    lives.push_back(life);
  }

   const int number_of_asteroids = 3;
   for(int i = 0; i <= number_of_asteroids; i++){

     auto asteroid = make_shared<SFAsset>(SFASSET_ASTEROID, sf_window);
     auto pos  = Point2(rand() % 600, rand() % 400 + 600);
     asteroid->SetPosition(pos);
     asteroids.push_back(asteroid);
  }  

   cout << "**********************************************************************" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                             Starting Game                          *" << endl;
   cout << "*                             Lives Left = "<< playerLives <<"                         *" << endl;
   cout << "*                               Score = " << score <<  "                      *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*--------------------------------------------------------------------*" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                   The Universe's Fate is up to You                 *" << endl;
   cout << "*                It's Your Job to Destroy all the Aliens             *" << endl;
   cout << "*                         Before it's too Late!                      *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*--------------------------------------------------------------------*" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                  Battle Aliens with the Lastest Weapon             *" << endl;
   cout << "*                            The Laser Cannon                        *" << endl;
   cout << "*                  But be Careful as space is filled with            *" << endl;
   cout << "*              Thousands of Asteroids which will Destroy your        *" << endl;
   cout << "*                               Spaceship!                           *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*--------------------------------------------------------------------*" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                               Controls                             *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*               Up                                Up                 *" << endl;
   cout << "*             _____                              _____               *" << endl;
   cout << "*            |     |                            |     |              *" << endl;
   cout << "*            |  w  |                            |  ^  |              *" << endl;
   cout << "*            |_____|                            |_____|              *" << endl;
   cout << "*      _____  _____  _____                _____  _____  _____        *" << endl;
   cout << "*     |     ||     ||     |              |     ||     ||     |       *" << endl;
   cout << "* Left|  a  ||  s  ||  d  | Right   Left |  <  ||  v  ||  >  | Right *" << endl;
   cout << "*     |_____||_____||_____|              |_____||_____||_____|       *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*             Down                                Down               *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                             Fire Laser                             *" << endl;
   cout << "*           ______________________________________________           *" << endl;
   cout << "*          |                                              |          *" << endl;
   cout << "*          |                     Space                    |          *" << endl;
   cout << "*          |______________________________________________|          *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                              Quit Game                             *" << endl;
   cout << "*                                _____                               *" << endl;
   cout << "*                               |     |                              *" << endl;
   cout << "*                               |  q  |                              *" << endl;
   cout << "*                               |_____|                              *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "*                                                                    *" << endl;
   cout << "**********************************************************************" << endl;
   cout << "" << endl;

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;

     cout << "**********************************************************************" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*                               Game Over!                           *" << endl;
     cout << "*                              Lives Left = "<< playerLives <<"                        *" << endl;
     cout << "*                                Score = " << score <<  "                         *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "**********************************************************************" << endl;
     cout << "" << endl;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
      player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_PLAYER_UP:
    player->GoNorth();
    break;
  case SFEVENT_PLAYER_DOWN:
    player->GoSouth();
    break;
  case SFEVENT_FIRE:
    FireProjectile();
    break;
    
    }
  }

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}


void SFApp::OnUpdateWorld() {

   int w, h;
   SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h); 


      for(auto a : aliens){
      for(auto c : coins){
      for(auto asteroid : asteroids){
        if(playerLives <= 0){
          a->SetNotAlive();
          c->SetNotAlive();
          asteroid->SetNotAlive();
        }

        if(alienLives <= 0){
          a->SetNotAlive();
          c->SetNotAlive();
          asteroid->SetNotAlive();
        }
      }
    }
  }
   
     
// Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }
// Update Coin Positions
  for(auto c: coins) {
    c->GoSouth();
  }
//Update Asteroid Positions
  for(auto asteroid : asteroids) {
     asteroid->GoSouth();
  }

 //Update Position 
 // Detect Collision between Player and Aliens and Asteroids
  for(auto a : aliens) {
    for(auto l : lives){
      for(auto c : coins){
         for(auto asteroid : asteroids) {
  if(player->CollidesWith(a)){
    a->HandleCollision();
    l->HandleCollision();
    player->HandleCollision();
      playerLives--;
      score = score -100;

     cout << "**********************************************************************" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*                         You Crashed into Alien!                    *" << endl;
     cout << "*                                Game Over!                          *" << endl;
     cout << "*                         Lives Left = "<< playerLives <<"                             *" << endl;
     cout << "*                         Score = " << score <<  "                               *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "**********************************************************************" << endl;
     cout << "" << endl;
  
   if(playerLives == 0){

     cout << "**********************************************************************" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*              Aliens Destroyed You, The Universe is in Danger!      *" << endl;
     cout << "*                          Click 'q' to Retry                        *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*                       Asteroid Destroyed into You!                 *" << endl;
     cout << "*                                Game Over!                          *" << endl;
     cout << "*                         Lives Left = "<< playerLives <<"                             *" << endl;
     cout << "*                         Score = " << score <<  "                               *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "**********************************************************************" << endl;
     cout << "" << endl;

     
       int canvas_w, canvas_h;
       SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);   
    
          auto game_over = make_shared<SFAsset>(SFASSET_GAME_OVER, sf_window);
          auto pos   = Point2(canvas_w/2, canvas_h);
          game_over->SetPosition(pos);
          game_overs.push_back(game_over);
 
          auto life_game_over = make_shared<SFAsset>(SFASSET_LIFE_GAME_OVER, sf_window);
          auto pos_life_game_over   = Point2(canvas_w/2, canvas_h/2);
          life_game_over->SetPosition(pos_life_game_over);
          life_game_overs.push_back(life_game_over);
    }
  }
  
        
   
   if(player->CollidesWith(asteroid)){
    l->HandleCollision();
    player->HandleCollision();
    asteroid->HandleCollision();
      playerLives--;
      score = score -100;

     cout << "**********************************************************************" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*                       Asteroid Smashed into You!                   *" << endl;
     cout << "*                          Click 'q' to Retry                        *" << endl;
     cout << "*                         Lives Left = "<< playerLives <<"                             *" << endl;
     cout << "*                         Score - 100 = " << score <<  "                         *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "**********************************************************************" << endl;
     cout << "" << endl;

         
   if(playerLives == 0){

     cout << "**********************************************************************" << endl;
     cout << "*                                                                    *" << endl;
     cout << "*                       Asteroid Destroyed into You!                 *" << endl;
     cout << "*                                Game Over!                          *" << endl;
     cout << "*                         Lives Left = "<< playerLives <<"                             *" << endl;
     cout << "*                         Score = " << score <<  "                               *" << endl;
     cout << "*                                                                    *" << endl;
     cout << "**********************************************************************" << endl;
     cout << "" << endl;

       int canvas_w, canvas_h;
       SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);   

          auto game_over = make_shared<SFAsset>(SFASSET_GAME_OVER, sf_window);
          auto pos   = Point2(canvas_w/2, canvas_h);
          game_over->SetPosition(pos);
          game_overs.push_back(game_over);
 
          auto life_game_over = make_shared<SFAsset>(SFASSET_LIFE_GAME_OVER, sf_window);
          auto pos_life_game_over   = Point2(canvas_w/2, canvas_h/2);
          life_game_over->SetPosition(pos_life_game_over);
          life_game_overs.push_back(life_game_over);

              }
            }
          } 
        }
      }
    }
  
 // Detect collisions between Player and Walls
 for(auto w : walls) {
   if(player->CollidesWith(w)) {
    w->HandleCollision();
    player->HandleCollision();
    score = score -50;

         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                       You Crashed into a Wall!                     *" << endl;
         cout << "*                         Score - 50 = " << score <<  "                          *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;
     }
  }

 //detect collisions between Player and Coins
 for(auto c : coins) {
   if(player->CollidesWith(c)) {
    c->HandleCollision();
    score = score + 100;

         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                       You Collected an Coin!                           *" << endl;
         cout << "*                         Score + 100 = " << score <<  "                         *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;
    }  
  }

  // Detect collisions between Projectiles and Aliens
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        p->HandleCollision();
        a->HandleCollision();
        score = score +50;
        alienLives = alienLives - 1;

         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                       You Shot an Alien!                           *" << endl;
         cout << "*                         Score + 50 = " << score <<  "                          *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;

       if(alienLives == 0){



         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                      You Destroyed all the Aliens                  *" << endl;
         cout << "*                       You Saved the Universe                       *" << endl;
         cout << "*                         Score = " << score <<  "                             *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;
         
       int canvas_w, canvas_h;
       SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);   

          auto win = make_shared<SFAsset>(SFASSET_WIN, sf_window);
          auto pos   = Point2(canvas_w/2, canvas_h);
          win->SetPosition(pos);
          wins.push_back(win);


        }  
      }
    }
  }
  // Detect collisions between Projectiles and Asteroids
  for(auto p : projectiles) {
    for(auto asteroid : asteroids) {
        if(p->CollidesWith(asteroid)) {
        p->HandleCollision();
        asteroid->HandleCollision();
        score = score +50;

         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                       You Destroyed an Asteroid!                   *" << endl;
         cout << "*                         Score + 50 = " << score <<  "                          *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;

      }
    }
  }
 
  //detect collisions between Projectiles and Coins
   for(auto p : projectiles) {
     for(auto c : coins) {
       if(p->CollidesWith(c)) {
          c->HandleCollision();
          p->HandleCollision();
          score = score +150;

         cout << "**********************************************************************" << endl;
         cout << "*                                                                    *" << endl;
         cout << "*                       You Shot an Coin!                            *" << endl;
         cout << "*                         Score + 150 = " << score <<  "                          *" << endl;
         cout << "*                                                                    *" << endl;
         cout << "**********************************************************************" << endl;
         cout << "" << endl;
      }
    } 
  }
 
  // Detect collisions between Projectiles and Walls
  for(auto p : projectiles) {
    for(auto w : walls) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
        w->HandleCollision();
      }
    }
  }

 //detect collisions between Coins and Walls
  for(auto c : coins) {
  for(auto w : walls) {
    if(c->CollidesWith(w)) {
     c->HandleCollision();
      }
    }
  }


 //detect collisions between Asteroids and Walls
 for(auto asteroid : asteroids) {
 for(auto w : walls) {
   if(asteroid->CollidesWith(w)) {
    asteroid->HandleCollision();
      }
    }
  }

  for(auto a : aliens) {
    // do something here
  }

  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> alienTmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      alienTmp.push_back(a);
    }
  }
  aliens.clear(); 
  aliens = list<shared_ptr<SFAsset>>(alienTmp);


 //remove dead coins

 list<shared_ptr<SFAsset>>coinTmp;
  for(auto c: coins) {
    if(c->IsAlive()) {
     coinTmp.push_back(c);
     }
   }
   coins.clear();
   coins = list<shared_ptr<SFAsset>>(coinTmp);

 

 //remove dead lives
  list<shared_ptr<SFAsset>> lifeTmp;
  for(auto l : lives) {
    if(l->IsAlive()) {
      lifeTmp.push_back(l);
    }
  }
  lives.clear(); 
  lives = list<shared_ptr<SFAsset>>(lifeTmp);
 

 //remove dead Projectiles

 list<shared_ptr<SFAsset>>projectileTmp;
  for(auto p: projectiles) {
    if(p->IsAlive()) {
     projectileTmp.push_back(p);
     }
   }
   projectiles.clear();
   projectiles = list<shared_ptr<SFAsset>>(projectileTmp);


  //remove dead Asteroids

 list<shared_ptr<SFAsset>>asteroidTmp;
  for(auto asteroid: asteroids) {
    if(asteroid->IsAlive()) {
     asteroidTmp.push_back(asteroid);
     }
   }
   asteroids.clear();
   asteroids = list<shared_ptr<SFAsset>>(asteroidTmp);


}
void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the Player
  player->OnRender();

  // draw the Projectiles
  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  //Draw the Aliens
  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  //Draw the lives
  for(auto l: lives) {
    if(l->IsAlive())l->OnRender();
  }

  //Draw the Walls
  for(auto w: walls) {
    w->OnRender();
  }

  //Draw the Coins
  for(auto c: coins) {
    c->OnRender();
  }
  //Draw the Asteroids
  for(auto asteroid: asteroids) {
    if(asteroid->IsAlive()) {asteroid->OnRender();}
  }
  //Draw the Game Over
  for(auto game_over: game_overs) {
    game_over->OnRender();
  }
  //Draw the Life Game Over
  for(auto life_game_over: life_game_overs) {
    life_game_over->OnRender();
  }
  // Draw Win
  for(auto win : wins){
	  if(win->IsAlive()){ win->OnRender();}
  }

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}
 

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
  }




