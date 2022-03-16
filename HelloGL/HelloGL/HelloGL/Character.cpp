#include "Character.h"







Character::Character(Obj* obj, Texture2D* textrures, float x, float y, float z) : Objshapes(obj, textrures, x,y,z)
{
	old_t = glutGet(GLUT_ELAPSED_TIME);
	dt = 0;
	m_position.x = x;//16.1f;
	m_position.y = y;//-19.4f;
	m_position.z = z;//-59.3f;
	m_Rotation = 0;
	m_Vrotation.x = 0;
	m_Vrotation.y = 0;
	m_Vrotation.z = 0;

}

void Character::Draw() {
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
	//glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(m_Rotation, m_Vrotation.x, m_Vrotation.y, m_Vrotation.z);
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

void Character::Update() {
	int t;

	t = glutGet(GLUT_ELAPSED_TIME);
	dt = (t - old_t) / 1000.0;
	old_t = t;
	//m_position.y -= 9.8 * dt;
	if (m_position.x <= -23.5)
	{
		m_position.x = -23.5;
	}
	if (m_position.x >= 24)
	{
		m_position.x = 24;
	}
	m_Vrotation.x = -1.0f;
	m_Rotation += 3;
	//cout << "X = " << m_position.x << "Y = " << m_position.y << "Z = " << m_position.z << endl;

	if (!m_buttonPressed)
	{
		ResetBallPosition();
	}
	glutPostRedisplay();
	cout << "X = " << m_position.x << "Y = " << m_position.y << "Z = " << m_position.z << endl;
}

void Character::AddGravity(float yPos, float depth) {

	if (m_position.y != yPos)
	{
		m_position.y = yPos + depth;
	}
}

void Character::ResetBallPosition() {
	if (m_Vrotation.z > 0)
	{
		m_Vrotation.z -= dt*2;
		if (m_Vrotation.z == 0)
		{
			m_Vrotation.z = 0;
		}
	}
	if (m_Vrotation.z < 0)
	{
		m_Vrotation.z += dt*2;
		if (m_Vrotation.z == 0)
		{
			m_Vrotation.z = 0;
		}
	}
}

void Character::Keyboard(unsigned char key, int x, int y) {
	if (key == 'd' || key == 'D')
	{
		m_buttonPressed = true;
		m_position.x += 0.6;
		m_Vrotation.z -= 0.02f;
		if (m_Vrotation.z == -0.1f)
		{
			m_Vrotation.z = -0.1f;
		}
	}
	else if (key == 'a' || key == 'A')
	{
		m_buttonPressed = true;
		m_position.x -= 0.6;
		m_Vrotation.z += 0.02f;
		if (m_Vrotation.z == 0.1f)
		{
			m_Vrotation.z = 0.1f;
		}	
	}
}

void Character::KeyboardUp(unsigned char key, int x, int y) {
	if (key == 'd')
	{
		m_buttonPressed = false;
		//m_Vrotation.z = 0;
		//m_Rotation -= m_Rotation;
	}
	else if (key == 'a')
	{
		m_buttonPressed = false;
		ResetBallPosition();
		//m_Vrotation.z = 0;
		//m_Rotation -= m_Rotation;
	}
}



Character::~Character()
{
}