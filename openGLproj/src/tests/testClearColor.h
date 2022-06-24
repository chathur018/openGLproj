#pragma once

#include "test.h"

namespace test
{
	class testClearColor : public test
	{
	private:
		float m_clearColor[4];
	
	public:
		testClearColor();
		~testClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}