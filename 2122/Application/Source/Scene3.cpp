#include "GL\glew.h"

#include "shader.hpp"
#include "Scene3.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"



Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}


void Scene3::Init()
{
	rotateAngle = 1.0f;
	translateX = 1.0f;
	scaleAll = 1.0f;
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	glUseProgram(m_programID);
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.f, 0.1f, 0.1f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	// An array of 3 vectors which represents 3 vertices
	// shape 1
	static const GLfloat vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f

	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_1]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3vertices
	static const GLfloat color_buffer_data[] = {

		0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);

	//Load vertex and fragment shaders




	// shape 2
	static const GLfloat vertex_buffer_data_2[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
	};
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ROOF]);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2),
		vertex_buffer_data_2, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3vertices
	static const GLfloat color_buffer_data_2[] = {
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,
	0.3f, 0.3f, 0.3f,


	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_ROOF]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2),
		color_buffer_data_2, GL_STATIC_DRAW);



		///


		static const GLfloat vertex_buffer_data_3[] = {
	-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
		};
		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_FLOOR]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_3),
			vertex_buffer_data_3, GL_STATIC_DRAW);

		// An array of 3 vectors which represents the colors of the 3vertices
		static const GLfloat color_buffer_data_3[] = {
		0.3f, 0.4f, 0.4f,
		0.0f, 0.3f, 0.3,
		0.3f, 0.4f, 0.4f,
		0.3f, 0.4f, 0.4f,
		0.3f, 0.4f, 0.4f,
		0.3f, 0.4f, 0.4f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_FLOOR]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_3),
			color_buffer_data_3, GL_STATIC_DRAW);
		glUseProgram(m_programID);


		//
		
		static const GLfloat vertex_buffer_data_4[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
		};
		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_2]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_4),
			vertex_buffer_data_4, GL_STATIC_DRAW);

		// An array of 3 vectors which represents the colors of the 3vertices
		static const GLfloat color_buffer_data_4[] = {
		0.9f, 0.7f, 0.3f,
		0.9f, 0.7f, 0.3f,
		0.9f, 0.7f, 0.3f,
		0.9f, 0.7f, 0.3f,
		0.9f, 0.7f, 0.3f,
		0.9f, 0.7f, 0.3f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_4),
			color_buffer_data_4, GL_STATIC_DRAW);


		//

		static const GLfloat vertex_buffer_data_5[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
		};
		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TREE_BODY]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_5),
			vertex_buffer_data_5, GL_STATIC_DRAW);

		// An array of 3 vectors which represents the colors of the 3vertices
		static const GLfloat color_buffer_data_5[] = {
		0.6f, 0.4f, 0.3f,
		0.6f, 0.4f, 0.3f,
		0.6f, 0.4f, 0.3f,
		0.6f, 0.4f, 0.3f,
		0.6f, 0.4f, 0.3f,
		0.6f, 0.4f, 0.3f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TREE_BODY]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_5),
			color_buffer_data_5, GL_STATIC_DRAW);
		glUseProgram(m_programID);

		//
		
		static const GLfloat vertex_buffer_data_6[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
		};
		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE_HEAD]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_6),
			vertex_buffer_data_6, GL_STATIC_DRAW);

		// An array of 3 vectors which represents the colors of the 3vertices
		static const GLfloat color_buffer_data_6[] = {
		0.1f, 0.7f, 0.3f,
		0.1f, 0.7f, 0.3f,
		0.1f, 0.7f, 0.3f,
		0.1f, 0.7f, 0.3f,
		0.1f, 0.7f, 0.3f,
		0.1f, 0.7f, 0.3f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_HEAD]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_6),
			color_buffer_data_6, GL_STATIC_DRAW);
		glUseProgram(m_programID);


		static const GLfloat vertex_buffer_data_7[] = {
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
		};
		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE_HEAD_DARK]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_7),
			vertex_buffer_data_7, GL_STATIC_DRAW);

		// An array of 3 vectors which represents the colors of the 3vertices
		static const GLfloat color_buffer_data_7[] = {
		0.1f, 0.6f, 0.3f,
		0.1f, 0.6f, 0.3f,
		0.1f, 0.6f, 0.3f,
		0.1f, 0.6f, 0.3f,
		0.1f, 0.6f, 0.3f,
		0.1f, 0.6f, 0.3f,

		};
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_HEAD_DARK]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_7),
			color_buffer_data_7, GL_STATIC_DRAW);
		glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene3::Update(double dt)
{
	rotateAngle += (float)(10 * dt);
	translateX += (float)(-1.5* dt);
	scaleAll += (float)(-0.75 * dt);

}

void Scene3::Render()
{
	// Render VBO here
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-10, 10, -5, +5, -5, +5);
	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-7, 4, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
	&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	//
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-10, 10, -5, +5, -5, +5);
	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-5, 2, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-10, 10, -5, +5, -5, +5);
	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-7, 0, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_1]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-5, 4, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	//
	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-7, 2, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	//

	scale.SetToScale(.9, .9, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-5, 0, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 1st attribute buffer : vertices

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_HOUSELIGHT_2]);
	glVertexAttribPointer(
		1, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);



	scale.SetToScale(9.5, 4.5, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(-6, 0, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ROOF]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_ROOF]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	//


	//


	scale.SetToScale(1.5, .9, 1.5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(6.5, 1.5, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE_HEAD_DARK]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_HEAD_DARK]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle



	scale.SetToScale(3.0, 2.75, 1.5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(7.0, 1.5, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE_HEAD]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_HEAD]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle

	// TODO
	//PARTICLE
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, translateX, -translateX);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TREE_HEAD_DARK]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TREE_HEAD_DARK]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle




	scale.SetToScale(2, 1, 1.5);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(7, 0, -1.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TREE_BODY]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TREE_BODY]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle
	//

	scale.SetToScale(24, 4, 4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, -3, 0.5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]); //update the shader with new MVP
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_FLOOR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_FLOOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices = 1 triangle



	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);





	//...
	//glClear(GL_COLOR_BUFFER_BIT);

	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(
	//	0, // attribute 0. Must match the layout in the shader.Usually 0 is for vertex
	//	3, // size
	//	GL_FLOAT, // type
	//	GL_FALSE, // normalized?
	//	0, // stride
	//	0 // array buffer offset
	//);

	//glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//// Draw the triangle
	//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	//
	//
	//
	//glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);




	glDeleteProgram(m_programID);

}
