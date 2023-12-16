#pragma once
#include "texture.h"
#include "GameObject.h"

class Button : public GameObject
{
private:
	Texture* myTexture;
	SDL_Rect screenPos;
public:
	Button(Texture*, int, int);
	~Button();
	void Update() override;
	void Render() const;
	void save(std::ostream&) const override;
};

