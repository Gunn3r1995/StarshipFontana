#include "SFAsset.h"

int SFAsset::SFASSETID=0;

SFAsset::SFAsset(SFASSETTYPE type, std::shared_ptr<SFWindow> window): type(type), sf_window(window) {
  this->id   = ++SFASSETID;

  switch (type) {
  case SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player.png");
    break;
  case SFASSET_PROJECTILE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile.png");
    break;
  case SFASSET_ALIEN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien.png");
    break;
  case SFASSET_COIN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/coin.png");
    break;
//Alien Boss
  case SFASSET_ALIEN_BOSS:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien.png");
    break;
//Wall texture
  case SFASSET_WALL:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/wall.png");
    break;
//Life Texture
  case SFASSET_LIFE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/life.png");
    break; 
//Asteroid Texture 
  case SFASSET_ASTEROID:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/asteroid.png");
    break; 
//Game Over Texture
  case SFASSET_GAME_OVER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/gameover.png");
    break;
//Life Game Over Texture
  case SFASSET_LIFE_GAME_OVER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/lifegameover.png");
    break;
//Life Win
  case SFASSET_WIN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/win.png");
    break;
/*
//Stars assets
  case SFASSET_STAR:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/star.png");
    break;
*/
}
  if(!sprite) {
    cerr << "Could not load asset of type " << type << endl;
    throw SF_ERROR_LOAD_ASSET;
  }


  // Get texture width & height
  int w, h;
  SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

  // Initialise bounding box
  bbox = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), w, h));
}

 


SFAsset::SFAsset(const SFAsset& a) {
  sprite = a.sprite;
  sf_window = a.sf_window;
  bbox   = a.bbox;
  type   = a.type;
  }

SFAsset::~SFAsset() {
  bbox.reset();
  if(sprite) {
    SDL_DestroyTexture(sprite);
    sprite = nullptr;
  }
}




/**
 * The logical coordinates in the game assume that the screen
 * is indexed from 0,0 in the bottom left corner.  The blittable
 * coordinates of the screen map 0,0 to the top left corner. We
 * need to convert between the two coordinate spaces.  We assume
 * that there is a 1-to-1 quantisation.
 */
Vector2 GameSpaceToScreenSpace(SDL_Renderer* renderer, Vector2 &r) {
  int w, h;
  SDL_GetRendererOutputSize(renderer, &w, &h);

  return Vector2 (
                  r.getX(),
                  (h - r.getY())
                  );
  
  }




void SFAsset::SetPosition(Point2 & point) {
  Vector2 v(point.getX(), point.getY());
  bbox->SetCentre(v);
}

Point2 SFAsset::GetPosition() {
  return Point2(bbox->centre->getX(), bbox->centre->getY());
}

SFAssetId SFAsset::GetId() {
  return id;
 }


void SFAsset::OnRender() {
  // 1. Get the SDL_Rect from SFBoundingBox
  SDL_Rect rect;

  Vector2 gs = (*(bbox->centre) + (*(bbox->extent_x) * -1)) + (*(bbox->extent_y) * -1);
  Vector2 ss = GameSpaceToScreenSpace(sf_window->getRenderer(), gs);
  rect.x = ss.getX();
  rect.y = ss.getY();
  rect.w = bbox->extent_x->getX() * 2;
  rect.h = bbox->extent_y->getY() * 2;

  // 2. Blit the sprite onto the level
  SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
  Vector2 c = *(bbox->centre) + Vector2(-7.0f, 0.0f);
  if(!(c.getX()-30.0f < 0)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoEast() {
  int w, h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);

  Vector2 c = *(bbox->centre) + Vector2(7.0f, 0.0f);
  if(!(c.getX()+30.0f > w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoNorth() {
    int w, h;
//Movement for player north
  if(SFASSET_PLAYER == type){
    SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
    Vector2 c = *(bbox->centre) + Vector2(0.0f, 7.0f);

  if(!(c.getY()-18.0f > h)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

 // Movement for Projectile
  if(SFASSET_PROJECTILE == type){
    SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);
  
    Vector2 c = *(bbox->centre) + Vector2(0.0f, 5.0f);

  if(!(c.getY()> h + 30.0f)) {
      bbox->centre.reset();
      bbox->centre = make_shared<Vector2>(c);
     }
  else {
     this->SetNotAlive();
    }
  }
}


void SFAsset::GoSouth() {
//Movement for Player South

  if(SFASSET_PLAYER == type){
    Vector2 c = *(bbox->centre) + Vector2(0.0f, -7.0f);

  if(!(c.getY() < 64.0f)) {
      bbox->centre.reset();
      bbox->centre = make_shared<Vector2>(c);
    }
  }
//Movement for Coin South

  if(SFASSET_COIN == type){
   Vector2 c = *(bbox->centre) + Vector2(0.0f, -2.5f); 

  if(!(c.getY() < 0.0f)) {
     bbox->centre.reset();
     bbox->centre = make_shared<Vector2>(c);
   }

  else{
    auto pos = Point2(rand() % 600+34, rand() % 400 + 600); 
    this->SetPosition(pos);
    }
  }

//Movement for Asteroid South

    if(SFASSET_ASTEROID == type){
   Vector2 c = *(bbox->centre) + Vector2(0.0f, -4.0f); 

  if(!(c.getY() < 0.0f)) {
     bbox->centre.reset();
     bbox->centre = make_shared<Vector2>(c);
   }

  else{
    auto pos = Point2(rand() % 600+34, rand() % 400 + 600); 
    this->SetPosition(pos);
    }
  }
}
  
bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
  return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
  return bbox;
}

void SFAsset::SetNotAlive() {
  type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
  return (SFASSET_DEAD != type);
}


void SFAsset::HandleCollision() {
  if(SFASSET_PROJECTILE == type || SFASSET_ALIEN == type) {
    SetNotAlive();
  }
    if(SFASSET_COIN == type) {
                 int canvas_w, canvas_h;
                 SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
                 auto pos = Point2(rand() % 600, rand() % 400 + 600);
    this->SetPosition(pos);
  }
    if (SFASSET_LIFE == type ){
                 SetNotAlive();
   }

    if(SFASSET_PLAYER == type) {
                 int canvas_w, canvas_h;
                 SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
                 auto player_pos = Point2(canvas_w / 2.0f, 88.0f);
    this->SetPosition(player_pos);
  }
    if(SFASSET_ASTEROID == type) {
                 int canvas_w, canvas_h;
                 SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);
                 auto pos = Point2(rand() % 600, rand() % 400 + 600);
    this->SetPosition(pos);
  }
 }
  



