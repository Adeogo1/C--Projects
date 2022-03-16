#include "Cube.h"





Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{

	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
	startPos = _position.z;
}

Cube::~Cube() {

}

void Cube::Draw() {
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);		
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoord);
		

		InitObjectsMaterials();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f); 
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f); 

		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();


		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update() {

	_rotation += randRot;
	
	_position.z += 0.4;
	if (_position.z > 10)
	{
		_position.z = startPos;
	}

}


void Cube::InitObjectsMaterials() {
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0;
}


/*
#include "Cube.h"

Vertex Cube::m_IndexedVertices[] =
{
	1,1,1,		-1,1,1,
	-1,-1,1,	1,-1,1,
	1,-1,-1,	1,1,-1,
	-1,1,-1,	-1,-1,-1
};

Color Cube::m_IndexedColors[] =
{
	1,1,1,	1,1,0,
	1,0,0,	1,0,1,
	0,0,1,	0,1,1,
	0,1,0,	0,0,0
};

GLushort Cube::m_Indices[] =
{
	0,1,2,	2,3,0,
	0,3,4,	4,5,0,
	0,5,6,	6,1,0,
	1,6,7,	7,2,1,
	7,4,3,	3,2,7,
	4,7,6,	6,5,4
};

Cube::Cube(float x, float y, float z)
{
	m_Rotation = 0.0f;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	//glBegin(GL_TRIANGLES);
//for (int i = 0; i < 36; ++i)
//{
//	glColor3fv(&m_IndexedColors[m_Indices[i]].r);
//	glVertex3fv(&m_IndexedVertices[m_Indices[i]].x);
//}
//glEnd();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(m_Rotation, 1.0f, 0.0f, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_IndexedVertices);
	glColorPointer(3, GL_FLOAT, 0, m_IndexedColors);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, m_Indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}

void Cube::Update()
{
	m_Rotation += 0.1f;
}
*/