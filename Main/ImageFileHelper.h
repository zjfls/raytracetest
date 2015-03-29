#pragma once


class MAIN_API ppmImage
{
public:
	ppmImage(const char* strPath,int width,int height) :stream(strPath, std::ios::out | std::ios::binary)
	{
		stream << "P6\n" << width << " " << height << "\n255\n";
	}
	virtual ~ppmImage(){};

	void Save(){ stream.close(); };
	ofstream stream;
};
class ImageFileHelper:public Singleton<ImageFileHelper>
{
public:
	ImageFileHelper();
	virtual ~ImageFileHelper();


};

