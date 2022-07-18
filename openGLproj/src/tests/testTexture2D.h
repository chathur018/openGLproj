#pragma once

#include "test.h"

#include "renderer.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	class testTexture2D : public test
	{
	private:
		vertexArray* m_vao;
		vertexBuffer* m_vbo;
		indexBuffer* m_ibo;
		shader m_shader;
		texture m_texture;
		
		glm::mat4 m_proj, m_view;
		
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		float m_rotationA;
		float m_rotationB;
	
	public:
		testTexture2D();
		~testTexture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}