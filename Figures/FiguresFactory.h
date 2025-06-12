//
// Created by Marat on 13.06.25.
//

#pragma once

#include "Figures.h"
#include <sstream>
#include <memory>

std::unique_ptr<Figures> createFigures(std::istringstream& is);


