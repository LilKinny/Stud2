#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "LoadOBJ.h"

Mesh* MeshBuilder::GenerateRec(const std::string& meshName, Color color, float x, float y)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * x, 0.5f * y, 0.f);	v.color = color;	v.normal.Set(0, 0, -1); v.texCoord.Set(1.f, 1.f);	vertex_buffer_data.push_back(v);       //v0   
	v.pos.Set(-0.5f * x, 0.5f * y, 0.f);	v.color = color;	v.normal.Set(0, 0, -1);	v.texCoord.Set(0.f, 1.f); 	vertex_buffer_data.push_back(v);     //v1   
	v.pos.Set(-0.5f * x, -0.5f * y, 0.f);	v.color = color;	v.normal.Set(0, 0, -1);	v.texCoord.Set(0.f, 0.f);	vertex_buffer_data.push_back(v);     //v2	
	v.pos.Set(0.5f * x, -0.5f * y, 0.f);	v.color = color;	v.normal.Set(0, 0, -1);	v.texCoord.Set(1.f, 0.f);	vertex_buffer_data.push_back(v);

	//tri1
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);
	//tri2
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//x-axis
	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//y-axis
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	//z-axis
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v); //v0
	v.pos.Set(-0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v); //v1
	v.pos.Set(-0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1); v.texCoord.Set(1,1); vertex_buffer_data.push_back(v); //v2
	v.pos.Set(0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0, 0, 1);	v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v); //v3

	//tri1
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	//tri2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string& meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	// left side
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(-1, 0, 0); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);

	// Back Side
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(0, 0);  vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(1,1); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 0, -1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);

	// Bottom side
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);

	// Front side
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 0, 1);vertex_buffer_data.push_back(v);
	
	// Right Side
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(1, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(1, 0, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(1, 0, 0);vertex_buffer_data.push_back(v);

	// Top Side
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color; v.normal.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color; v.normal.Set(0, 1, 0);vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color; v.normal.Set(0, 1, 0);vertex_buffer_data.push_back(v);

	
	for (unsigned i = 0; i < 36; ++i)
	{

		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color,   float Radius, int numSegments)

{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = 0; i <= numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		v.pos.Set(Radius * cosf(theta), 0.f, Radius * sinf(theta)); v.color = color;
		vertex_buffer_data.push_back(v);
		v.pos.Set(0.f, 0.f, 0.f); v.color = color;
		vertex_buffer_data.push_back(v);

	}
	for (unsigned int i = 0; i < vertex_buffer_data.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float PI = 3.1415926f;
	int totalStacks = 18;
	int totalSlices = 36;

	for (unsigned int stackNumber = 0; stackNumber <= totalStacks; ++stackNumber)
	{
		for (unsigned int sliceNumber = 0; sliceNumber < totalSlices; ++sliceNumber)
		{
			float theta = stackNumber * PI / totalStacks;
			float phi = sliceNumber * 2 * PI / totalSlices;

			float x = radius * cos(phi) * sin(theta);
			float y = radius * sin(phi) * sin(theta);
			float z = radius * cos(theta);

			v.pos.Set(x, y, z); v.color = color; v.normal.Set(x,y,z);  vertex_buffer_data.push_back(v);
		}
	}

	//Calculate index positions
	for (unsigned int stackNumber = 0; stackNumber < totalStacks; ++stackNumber)
	{
		for (unsigned int sliceNumber = 0; sliceNumber <= totalSlices; ++sliceNumber)
		{
			index_buffer_data.push_back((stackNumber * totalSlices) + (sliceNumber % totalSlices));
			index_buffer_data.push_back(((stackNumber + 1) * totalSlices) + (sliceNumber % totalSlices));
		}
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path)
{
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData//Use triangle list and remember to set index size}
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
}

Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path)
{
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(), vertices, uvs, normals, materials);
	if (!success) return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials) mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}
//Read vertices, texcoords & normals from OBJ

Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	unsigned offset = 0;
	for (unsigned row = 0; row < numRow; ++row)
	{
		for (unsigned col = 0; col < numCol; ++col)
		{
			v.pos.Set(0.5f, 0.5f, 0.f);	v.texCoord.Set((col + 1) * width, (numRow - row ) * height); vertex_buffer_data.push_back(v); //v0
			v.pos.Set(-0.5f, 0.5f, 0.f); v.texCoord.Set(col*width, (numRow - row ) * height); vertex_buffer_data.push_back(v); //v1
			v.pos.Set(-0.5f, -0.5f, 0.f); v.texCoord.Set(col * width, (numRow - row - 1) * height); vertex_buffer_data.push_back(v); //v2
			v.pos.Set(0.5f, -0.5f, 0.f); v.texCoord.Set((col + 1) * width, (numRow - row - 1) * height); vertex_buffer_data.push_back(v); //v3


			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);

			offset += 4;

			
			//Task: Add 6 indices into index_buffer_data
		}
		
	}
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}