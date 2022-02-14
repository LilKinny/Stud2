#include "GL\glew.h"

#include "shader.hpp"
#include "Scene2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera.h"
#include "Vertex.h"
#include "MeshBuilder.h"
#include "Mesh.h"


Camera camera;


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}


void Scene2::Init()
{
    glEnable(GL_CULL_FACE);
    rotateAngle = 1.0f;
    translateX = 1.0f;
    scaleAll = 1.0f;
    m_programID = LoadShaders(
        "Shader//TransformVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader");

    m_parameters[U_MVP] = glGetUniformLocation(m_programID,
        "MVP");
    camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1,
        0));
    glUseProgram(m_programID);
    // Init VBO here
    // Set background color to dark blue
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //glUseProgram(m_programID);

    //// Enable depth test
    //glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);

    //glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[0]); //generate


    //static const GLuint index_buffer_data[] = {
    //0, 1, 2,

    //0, 2, 3,

    //};
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer[GEO_TRIANGLE_1]); //bind index buffer
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //    sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);



    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 2, 0), 1);
    meshList[GEO_AXES] = MeshBuilder::GenerateQuad("axes", Color(1, 2, 0), 1);
    //meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1,);


}

void Scene2::Update(double dt)
{
    rotateAngle += (float)(10 * dt);
    translateX += (float)(10 * dt);
    scaleAll += (float)(2 * dt);

    if (Application::IsKeyPressed('1')) {
        glEnable(GL_CULL_FACE);

    }

    if (Application::IsKeyPressed('2'))
        glDisable(GL_CULL_FACE);

    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode

    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode






}

void Scene2::Render()
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
    //view.SetToIdentity();
    view.SetToLookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
    );

    /*projection.SetToOrtho(-10, 10, -5, +5, -5, +5);*/
    projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);

    scale.SetToScale(2, 2, 2);
    rotate.SetToRotation(rotateAngle, 0, 0, 1);
    translate.SetToTranslation(-0.5, 1, 0.5);

    model = translate * rotate * scale;
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_QUAD]->Render();
    meshList[GEO_AXES]->Render();


}
void Scene2::Exit()
{
    // Cleanup VBO here
    //glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    //glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);


    /*glDeleteVertexArrays(1, &m_vertexArrayID);*/
    delete meshList[GEO_QUAD];




    glDeleteProgram(m_programID);

}