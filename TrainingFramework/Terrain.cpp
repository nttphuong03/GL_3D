#include "stdafx.h"
#include "Terrain.h"

void Terrain::Print() {
	Object::Print();
	printf("\ntiling: %d", tiling);
	printf("\nfog_start: %d, fog_length: %d, log_color: %f %f %f", fog_start, fog_length, fog_color.x, fog_color.y, fog_color.z);
}

Terrain::~Terrain() {

}

void Terrain::Draw(){}
Terrain::Terrain(){}