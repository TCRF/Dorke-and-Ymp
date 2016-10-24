#include "resource.h"

//#define EMBED_ROM
#define PAL_VIEW
#define CONFIG_NAME	"game.cfg"

static const char* RomTitleNames[] =
{
	"Dorke and Imp"
};

#ifndef EMBED_ROM
static const char* RomFileNames[] =
{
	"dorke"
};
#endif

#include "../piko.cpp"
