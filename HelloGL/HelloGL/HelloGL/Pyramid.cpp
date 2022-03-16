#include "Pyramid.h"




Vertex* Pyramid::indexedVertices = nullptr;


Color* Pyramid::indexedColors = nullptr;


GLushort* Pyramid::indices = nullptr;


int Pyramid::numVertices = 0;
int Pyramid::numColors = 0;
int Pyramid::numIndicies = 0;



Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}

Pyramid::~Pyramid() {

}

void Pyramid::Draw() {
	if (_mesh->Vertices != nullptr  && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);


		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f); // not rotating
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f); // not rotating

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisable(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	}

}

void Pyramid::Update() {
	//_rotation += 0.5f;//not rotating
}