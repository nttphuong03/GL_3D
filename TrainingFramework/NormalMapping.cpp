#include "stdafx.h"
#include "NormalMapping.h"

void Mapping::Print() {
	Object::Print();
	printf("\nambient_weight: %d, spce_power: %d", ambient_weight, spec_power);
}

void Mapping::Draw() {

}
Mapping::Mapping(){}
Mapping::~Mapping(){}