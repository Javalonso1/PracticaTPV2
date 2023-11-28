#pragma once
#include "checkML.h"
#include <stdexcept>
#include <string>
#include "InvadersError.h"

class SDLError : public InvadersError {
public:
	SDLError(const std::string& e) : InvadersError("SDL Error : " + e) {};

};