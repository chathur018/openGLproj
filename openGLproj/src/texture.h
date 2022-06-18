#pragma once

#include "renderer.h"

class texture
{
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;

public:
	texture(const std::string& filepath);
	~texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;
};