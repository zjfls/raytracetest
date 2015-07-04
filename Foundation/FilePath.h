#pragma once
namespace ZG
{
	FOUNDATION_API std::string getFileSuffix(std::string fullFilePath);
	FOUNDATION_API std::string getFileName(std::string fullFilePath);
	FOUNDATION_API std::string getFileNameWithoutSuffix(std::string fullFilePath);
	FOUNDATION_API std::string removeSuffix(std::string fileName);
	FOUNDATION_API std::string getFileDirectory(std::string fullFilePath);
}