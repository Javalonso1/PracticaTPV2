#pragma once
#include "checkML.h"
#include <stdexcept>
#include <string>
#include "InvadersError.h"

class FileNotFoundError : public InvadersError {
public:
	FileNotFoundError(const std::string& e) : InvadersError("File " + e + " not found") {};
};