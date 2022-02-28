//-----------------------------------------------------------------------------
// touchkbd.h
//-----------------------------------------------------------------------------
// Copyright 2022 Picosapiens
//
// This file is part of Ranocchio
//
//  Ranocchio is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Ranocchio is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Girino.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#ifndef TOUCHKBD
#define TOUCHKBD

#include "ranocchio.h"

#define SCREENWIDTH 320
#define KEYBOARDY 110
#define KEYSIZE 32

extern char keyboardkeys[4][10];

void touchkeyinput(char* s, int numchars, char* instructions);

#endif //TOUCHKBD
