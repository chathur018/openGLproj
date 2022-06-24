#include "testClearColor.h"

#include "renderer.h"
#include "imgui/imgui.h"

namespace test
{
	testClearColor::testClearColor()
		: m_clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	testClearColor::~testClearColor()
	{
	}

	void testClearColor::onUpdate(float deltaTime)
	{

	}

	void testClearColor::onRender()
	{
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void testClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_clearColor);
	}
}