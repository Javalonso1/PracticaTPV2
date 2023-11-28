#pragma once
#include "checkML.h"
#include <stdexcept>
#include <string>

class InvadersError : public std::logic_error {
public:
	InvadersError(const std::string& e) : logic_error(e) {};
};