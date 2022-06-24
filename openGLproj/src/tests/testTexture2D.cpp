#include "testTexture2D.h"

#include "imgui/imgui.h"

#include "vertexBufferLayout.h"

namespace test
{
	testTexture2D::testTexture2D()
        : m_translationA(200, 200, 0), m_translationB(400, 400, 0),
        m_shader("res/shaders/basic.shader"), m_texture("res/textures/logo.png")
	{
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
             50.0f, -50.0f, 1.0f, 0.0f,
             50.0f,  50.0f, 1.0f, 1.0f,
            -50.0f,  50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_vao = new vertexArray();
        m_vbo = new vertexBuffer(positions, 4 * 4 * sizeof(float));
        vertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_vao->addBuffer(*m_vbo, layout);
		m_ibo = new indexBuffer(indices, 6);

        m_shader.bind();
        //m_shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        m_shader.setUniform1i("u_Texture", 0);

        m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	}

	testTexture2D::~testTexture2D()
	{
        delete m_vao;
        delete m_vbo;
        delete m_ibo;
	}

	void testTexture2D::onUpdate(float deltaTime)
	{

	}

	void testTexture2D::onRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        

        renderer renderer;

        m_texture.bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_vao, *m_ibo, m_shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_vao, *m_ibo, m_shader);
        }
	}

	void testTexture2D::onImGuiRender()
	{
        ImGui::SliderFloat3("translation A", &m_translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("translation B", &m_translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}