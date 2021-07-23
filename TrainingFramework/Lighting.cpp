#include "stdafx.h"
#include "Lighting.h"

void Lighting::Print() {
	Object::Print();
	printf("\nambient_weight: %d, spce_power: %d", ambient_weight, spec_power);
}
void Lighting::Draw() {

}

Lighting::Lighting(){}
Lighting::~Lighting(){}