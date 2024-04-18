#include "admin.hpp"

struct TextureManager{
  static SDL_Texture* LoadTexture(Admin MyGame, string filePath);
  static void Draw(Admin MyGame, SDL_Texture* tex, SDL_Rect dst);
  static void Draw(Admin MyGame, SDL_Texture* tex, const Vector2D &pos, const Vector2D &size);
  static void DrawS(Admin MyGame, SDL_Texture* tex, const Vector2D &pos, const Vector2D &size, SDL_Rect src);
  static void DrawEx(Admin MyGame, SDL_Texture* tex, const Vector2D &pos, const Vector2D &size, const int &angle, SDL_RendererFlip flip);
  static void SetPos(SDL_Rect& dst, const Vector2D &pos, const Vector2D &size);
};
