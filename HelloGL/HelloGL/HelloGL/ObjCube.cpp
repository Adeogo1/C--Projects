#include "ObjCube.h"



ObjCube::ObjCube(Obj* obj, Texture2D* textrures, float x, float y, float z) : Objshapes(obj, textrures, x, y, z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	startPos = m_position.z;
}


void ObjCube::Draw() {

	glBindTexture(GL_TEXTURE_2D, _textrures->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_obj->vertex);
	glNormalPointer(GL_FLOAT, 0, &_obj->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, &_obj->TexCoord);


	//initobjectsmaterials();
	//glmaterialfv(gl_front, gl_ambient, &(_material->ambient.x));
	//glmaterialfv(gl_front, gl_diffuse, &(_material->diffuse.x));
	//glmaterialfv(gl_front, gl_specular, &(_material->specular.x));
	//glmaterialf(gl_front, gl_shininess, _material->shininess);
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	//glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
	//glRotatef(_rotation, 0.0f, 1.0f, 0.0f);

	//glDrawElements(GL_TRIANGLES, _obj->Indicies, GL_UNSIGNED_SHORT, _mesh->Indices);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _obj->Indicies; i++)
	{
		//cout << _obj->TexCoord[_obj->TexCoordsindices[i]].x << endl;
		glTexCoord2fv(&_obj->TexCoord[_obj->TexCoordsindices[i]].x);
		glNormal3fv(&_obj->Normals[_obj->Normalindicies[i]].x);
		glVertex3fv(&_obj->vertex[_obj->Vertices[i]].x);
	}
	glEnd();
	glPopMatrix();


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void ObjCube::Update() {
	m_position.z += 1.0f;
	if (m_position.z > m_distanceTravelled)
	{
		m_position.z = m_resetPos;
	}
	//cout << "X = " << m_position.x << "Y = " << m_position.y << "Z = " << m_position.z << endl;
}

void ObjCube::InitObjectsMaterials() {
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0;
}


void ObjCube::Keyboard(unsigned char key, int x, int y) {
	if (key == 'd')
	{
		m_position.x += 0.2;
	}
	else if (key == 'a')
	{
		m_position.x -= 0.2;

	}
	if (key == 'u')
	{
		m_position.y += 0.7;
	}
	else if (key == 'l')
	{
		m_position.y -= 0.7;
	}
	if (key == 'w')
	{
		m_position.z += 0.7;
	}
	else if (key == 's')
	{
		m_position.z -= 0.7;
	}
}



ObjCube::~ObjCube()
{
}
