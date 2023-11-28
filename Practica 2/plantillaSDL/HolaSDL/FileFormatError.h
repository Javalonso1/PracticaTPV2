#pragma once
#include "checkML.h"
#include <stdexcept>
#include <string>
#include "InvadersError.h"

class FileFormatError : public InvadersError {
private:
	std::string nombre;
	int linea;
public:
	FileFormatError(const std::string& e, int lin, std::string nombe) : InvadersError("File format error in line " + std::to_string(lin) + " of " + nombe + ": " + e),
					nombre(nombe), linea(lin){};

};