#include "TextManager.hpp"

SDL_Texture* TextureManager::LoadTexture(Admin MyGame, string filePath) {
	SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(MyGame.renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::Draw(Admin MyGame, SDL_Texture* tex, SDL_Rect dst) {
	SDL_RenderCopy(MyGame.renderer, tex, NULL, &dst);
}

void TextureManager::Draw(Admin MyGame, SDL_Texture* tex, const Vector2D &pos, const Vector2D &size) {
	SDL_Rect dst;
	SetPos(dst, pos, size);
	SDL_RenderCopy(MyGame.renderer, tex, NULL, &dst);
}

void TextureManager::DrawS(Admin MyGame, SDL_Texture* tex, const Vector2D &pos,
							const Vector2D &size, SDL_Rect src) {
	SDL_Rect dst;
	SetPos(dst, pos, size);
	SDL_RenderCopy(MyGame.renderer, tex, &src, &dst);
}

void TextureManager::DrawEx(Admin MyGame, SDL_Texture* tex, const Vector2D &pos, const Vector2D &size,
					const int &angle, SDL_RendererFlip flip) {
	SDL_Rect dst;
	SetPos(dst, pos, size);
	SDL_RenderCopyEx(MyGame.renderer, tex, NULL, &dst, angle, nullptr, flip);
}

void TextureManager::SetPos(SDL_Rect& dst, const Vector2D &pos, const Vector2D &size) {
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = size.x;
	dst.h = size.y;
}
