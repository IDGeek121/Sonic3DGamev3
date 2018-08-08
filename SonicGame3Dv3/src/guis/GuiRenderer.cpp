#include "guirenderer.h"
#include "guishader.h"
#include "guitexture.h"

#include <glad/glad.h>
#include "../engineTester/main.h"
#include "../renderEngine/renderEngine.h"
#include "../models/models.h"
#include "../toolbox/maths.h"
#include "../toolbox/matrix.h"

#include <vector>

RawModel GuiRenderer::quadModel;
GuiShader* GuiRenderer::shader = nullptr;

void GuiRenderer::init()
{
	std::vector<float> positions;
	positions.push_back(-1);
	positions.push_back(1);
	positions.push_back(-1);
	positions.push_back(-1);
	positions.push_back(1);
	positions.push_back(1);
	positions.push_back(1);
	positions.push_back(-1);
	GuiRenderer::quadModel = Loader_loadToVAO(&positions, 2);
	GuiRenderer::shader = new GuiShader("res/Shaders/guis/guiVertexShader.txt", "res/Shaders/guis/guiFragmentShader.txt"); INCR_NEW
}

void GuiRenderer::render(std::list<GuiTexture*>* guis)
{
	GuiRenderer::shader->start();
	glBindVertexArray(GuiRenderer::quadModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture* gui: (*guis))
	{
		if (gui->getVisible())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gui->getTexture());
			Matrix4f matrix;
			createTransformationMatrix(&matrix, gui->getPosition(), gui->getRotation(), gui->getSizeScaled());
			GuiRenderer::shader->loadTransformation(&matrix);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, GuiRenderer::quadModel.getVertexCount());
		}
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	GuiRenderer::shader->stop();
}
	
void GuiRenderer::cleanUp()
{
	GuiRenderer::shader->cleanUp();
	delete GuiRenderer::shader; INCR_DEL
	GuiRenderer::shader = nullptr;
}