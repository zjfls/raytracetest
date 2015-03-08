#pragma once

class IWorld;
class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();


	bool Init(int argc, char** argv);
	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	virtual void PreUpdate();
	virtual void OnUpdate();
	virtual void Run();


protected:
	int m_argc;
	char** m_argv;
	IWorld* m_pWorld;
};

