#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <string>

namespace test
{
	class test
	{
	public:
		test(){}
		virtual ~test(){}

		virtual void onUpdate(float deltaTime){}
		virtual void onRender(){}
		virtual void onImGuiRender(){}
	};

	class testMenu : public test
	{
	public:
		testMenu(test*& currentTestPointer);

		void onImGuiRender() override;

		template<typename T>
		void registerTest(const std::string name)
		{
			std::cout << "registering test" << name << std::endl;

			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<test*()>>> m_tests;
	};
}