#pragma once
#include "Vec3.h"
#include "drand48.h"

class perlin
{
public:
	float noise(const vec3& p) const;

private:
	static float*	_ranFloat;
	static int*		_permX;
	static int*		_permY;
	static int*		_permZ;

};





static float* perlinGenerate();

// �ı����к���
void	permute(int* p, int n);

static int* perlinGeneratePerm();


