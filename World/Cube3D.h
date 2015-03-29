#pragma once

class WORLD_API Cube3D :public IRenderable
{
public:
	Cube3D();
	virtual ~Cube3D();

	virtual void Update();
};

