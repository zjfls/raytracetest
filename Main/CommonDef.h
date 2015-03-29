#pragma once
#define MAX_FILENAME_LENGTH 128
#define MAX_FILEPATH_LENGTH 256
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p != nullptr) { (p)->Release(); (p)=nullptr; } }
#endif