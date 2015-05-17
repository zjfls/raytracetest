#pragma once
class MAIN_API IOInterface
{
public:
	IOInterface();
	virtual ~IOInterface();

	virtual bool IsLBDown() = 0;
	virtual bool IsRBDown() = 0;
	virtual bool IsKeyDown(char c) = 0;
};
