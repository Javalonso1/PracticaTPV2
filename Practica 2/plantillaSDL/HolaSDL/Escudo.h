#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "Reward.h"
class PlayState;

class Escudo : public Reward
{
private:
public:
	Escudo(Point2D<int>&, Texture*, PlayState* gayme);
	void Act() override;
	void save(std::ostream&) const override;
};
