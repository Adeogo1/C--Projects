#include "ObjBarrels.h"







ObjBarrels::ObjBarrels(Obj* obj, Texture2D* textrures, float x, float y, float z) : Objshapes(obj, textrures, x, y, z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	startPos = _position.z;
}

void ObjBarrels::Draw() {

	glBindTexture(GL_TEXTURE_2D, _textrures->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_obj->vertex);
	glNormalPointer(GL_FLOAT, 0, &_obj->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, &_obj->TexCoord);



	//glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	//glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	//glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
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

void ObjBarrels::Update() {
	_position.z += 1.0f;
	if (_position.z > m_distanceTravelled)
	{
		_position.z = m_resetPos;
	}
}

ObjBarrels::~ObjBarrels()
{
}
