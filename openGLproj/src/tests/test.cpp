#include "test.h"
#include "imgui/imgui.h"

namespace test
{
	testMenu::testMenu(test*& currentTestPointer)
		: m_currentTest(currentTestPointer)
	{

	}

	void testMenu::onImGuiRender()
	{
		for (auto& test : m_tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_currentTest = test.second();
		}
	}
}