#pragma once
#include "texture.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>
#include <list>

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
private:
	Texture* myTexture;
	SDL_Rect screenPos;
	std::list<Callback> myCallbacks;
public:
	Button(GameState*, Texture*, int, int);
	~Button();
	void Connect(Callback);
	void Update() override;
	void Render() const;
	void save(std::ostream&) const override;
	void handleEvent(const SDL_Event&) override;
};

