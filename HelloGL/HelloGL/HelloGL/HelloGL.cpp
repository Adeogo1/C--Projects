#include "HelloGL.h"
using namespace GLUTCallbacks;





HelloGL::HelloGL(int argc, char* argv[]) {

	srand(time(0));
	infile.open("Scores.txt");
	if (!infile.is_open()) {
		cout << "File failed to Open" << endl;
	}

	InitGL(argc, argv);
	InitObjects();
	InitObjLoaders();
	InitObjectsLightObject();
	while (infile >> fileHighScore)
	{
		highestScore = fileHighScore;
	}
	infile.close();



	rotation = 0.0f;
	glutMainLoop();
}


void HelloGL::InitObjects() {

	distance = framecount = 0;

	//Cube::Load((char*)"cube.txt");
	old_t = glutGet(GLUT_ELAPSED_TIME);
	camera = new Camera();

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 10.0f;
	//cout << "Camera eye" << endl;
	//cout << "X = " << camera->eye.x << " Y = " << camera->eye.y << " Z = " << camera->eye.z << endl;

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;
	//cout << "Camera centre" << endl;
	//cout << "X = " << camera->center.x << " Y = " << camera->center.y << " Z = " << camera->center.z << endl;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	//cout << "Camera up" << endl;
	//cout << "X = " << camera->up.x << " Y = " << camera->up.y << " Z = " << camera->up.z << endl;

	
}

void HelloGL::InitGL(int argc, char* argv[]) {
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);



	//glDepthFunc(GL_ALWAYS);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Project");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16);

	//controls
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	Menu();

	glutMouseFunc(GLUTCallbacks::Mouse);
	glutMotionFunc(GLUTCallbacks::Motion);
	glutPassiveMotionFunc(GLUTCallbacks::PassiveMotion);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0.1, 1000);//you can leave yours at 0 i changed mine to 0.1
	glMatrixMode(GL_MODELVIEW);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


}


void HelloGL::InitObjLoaders() {
	//Mesh* cubeMesh = MeshLoader::Load((char*)"cube.obj");
	////Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");
	//Texture2D* texture = new Texture2D();
	//texture->LoadRAW((char*)"Penguins.raw", 512, 512);
	//for (int i = 0; i < 0; i++)
	//{
	//	float r = static_cast <float> (rand() % 10) / static_cast <float> (10);
	//	objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	//}
	//SkyBox
	Obj* SkyBox = ObjLoader::Load((char*)"Skybox.obj");
	Texture2D* SkyboxTexture = new Texture2D();
	SkyboxTexture->LoadRAW((char*)"SKYBOX.raw", 1500, 1150);
	m_SkyBox = new ObjCube(SkyBox, SkyboxTexture, 0, 0, 0);

	
	//Platforms
	Obj* Platform = ObjLoader::Load((char*)"Platform.obj");
	Texture2D* PlatformTexture = new Texture2D();
	PlatformTexture->LoadRAW((char*)"block.raw", 2048, 2048);
	
	startPos.x = 17.7;
	startPos.y = -24.3;
	startPos.z = -95.8;

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			m_Platform[i] = new ObjCube(Platform, PlatformTexture, startPos.x,startPos.y,startPos.z);
			cout << startPos.z << endl;
			m_Platform[i]->SetDistanceTravelled(497.8);
			m_Platform[i]->SetResetPos(startPos.z);

		}
		else
		{
		startPos.z = -593.6;
		m_Platform[i] = new ObjCube(Platform, PlatformTexture, startPos.x ,startPos.y,startPos.z);
		cout << startPos.z << endl;
		m_Platform[i]->SetDistanceTravelled(497.8);
		m_Platform[i]->SetResetPos(startPos.z);

		}
		//objObjects[i]->BoxCollider->Origin = startPos;
		//objObjects[i]->BoxCollider->Width = 59.8;
		//objObjects[i]->BoxCollider->Depth = 2.1;
		//objObjects[i]->BoxCollider->Height = 497.8;
		
	}

	//Barrels
	boxRadius = 0.87 * 9;
	Obj* Barrels = ObjLoader::Load((char*)"cube.obj");
	Texture2D* barrelTexture = new Texture2D();
	barrelTexture->LoadRAW((char*)"wood.raw", 2048, 2048);
	//radius is 0.87

	for (int i = 0; i < 8; i++)
	{
		m_ObjPositions.x = (rand()%200) + (-30);
		m_ObjPositions.y = -18.3;
		m_ObjPositions.z = (rand() % 1000) + (-250);

		m_objects[i] = new ObjBarrels(Barrels, barrelTexture, m_ObjPositions.x, m_ObjPositions.y, m_ObjPositions.z);
		m_objects[i]->SetDistanceTravelled(40);
		m_objects[i]->SetResetPos(rand() % 100 + (-250));
	}

	//Player
	m_Alive = true;
	playerRadius = 4.2582;
	Obj* Object = ObjLoader::Load((char*)"soccer_ball.obj");
	Texture2D* newTexture = new Texture2D();
	newTexture->LoadRAW((char*)"football_ball_Base.raw", 2048, 2048);
	position.x = ((rand() % 400) / 10.0f) - 20.0f;
	position.y =  -19.4;
	position.z = -95.8 + 38;

	m_Player = new Character(Object, newTexture, position.x, position.y, position.z);

}



void HelloGL::Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// THIS CLEARS THE SCENE
	if (m_Alive)
	{
		glRotatef(rotation, 1.0f, 1.0f, 1.0f);
		//glTranslatef(position.x, position.y, position.z);
		Vector3 v = { -3.78f, 4.3f, -1.0f };
		Color c = { 0.4f, 1.0f, 0.0f };

		string d = to_string(distance);
		DrawString(("Distance: " + d).c_str(), &v, &c);

		Vector3 bestv = { -1.0f, 4.3f, -1.0f };
		Color  bestc= { 0.4f, 1.0f, 0.0f };

		string f = to_string(fileHighScore);
		DrawString(("Best Distance: " + f).c_str(), &bestv, &bestc);
		DrawObjs();
	}
	else
	{
		glClearColor(1, 0.6,0.2, 1);
		//glRotatef(rotation, 1.0f, 1.0f, 1.0f);
		//glTranslatef(position.x, position.y, position.z);
		Vector3 v = { -1.4f, 0.7f, -0.2f };
		Color c = { 0.4f, 1.0f, 0.0f };

		string d = to_string(distance);
		DrawString("GAME OVER", &v, &c);

	}


	
	


	glFlush();
	glutSwapBuffers();
}


void HelloGL::DrawString(const char* text, Vector3* position, Color* color) {
	glDisable(GL_LIGHTING);
	glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	glColor3f(color->r, color->g, color->b);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	
	glPopMatrix();
	glEnable(GL_LIGHTING);

}


void HelloGL::Update() {
	if (distance > highestScore) {
		outfile.open("Scores.txt");
		if (!outfile.is_open()) {
			cout << "File failed to Open" << endl;
		}
		highestScore = distance;
		fileHighScore = highestScore;
		outfile << fileHighScore << endl;
		outfile.close();
	}
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->center.x, camera->center.y, camera->center.z,
		camera->up.x, camera->up.y, camera->up.z);

	UpdateObjs();

	framecount++;
	if (framecount == 40)
	{
		distance++;
		framecount = 0;
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glutPostRedisplay();
}


void HelloGL::UpdateObjs() {

	for (int i = 0; i < 2; i++) {
		m_Platform[i]->Update();
	}
	//m_Player->AddGravity(startPos.y, 0);
	m_Player->Update();
	for (int i = 0; i < 8; i++)
	{
		m_objects[i]->Update();
		if (m_objects[i]->GetPos().z > 5)
		{
			m_objects[i]->SetResetPos(rand() % 100 + (-150));

		}
		float sqDistance = pow((playerRadius + boxRadius), 2);
		if (calculateDistanceSquared(m_objects[i]->GetPos(), m_Player->GetPos()) <= sqDistance)
		{
			m_Alive = false;
		}
	}

}
void HelloGL::DrawObjs() {
	m_SkyBox->Draw();
	for (int i = 0; i < 2; i++)
	{
		m_Platform[i]->Draw();
	}
	for (int i = 0; i < 8; i++)
	{
		m_objects[i]->Draw();
	}

	m_Player->Draw();
}



void HelloGL::InitObjectsLightObject() {
	_lightPosition = new Vector4();
	_lightPosition->x = 1.0;
	_lightPosition->y = 5.0;
	_lightPosition->z = -5.0;
	_lightPosition->w = 1.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2 * 5;
	_lightData->Ambient.y = 0.2 * 5;
	_lightData->Ambient.z = 0.2 * 5;
	_lightData->Ambient.w = 1.0 * 5;
	_lightData->Diffuse.x = 1.0 * 5;
	_lightData->Diffuse.y = 1.0 * 5;
	_lightData->Diffuse.z = 1.0 * 5;
	_lightData->Diffuse.w = 1.0 * 5;
	_lightData->Specular.x = 0.2 * 5;
	_lightData->Specular.y = 0.2 * 5;
	_lightData->Specular.z = 0.2 * 5;
	_lightData->Specular.w = 1.0 * 5;


}




void HelloGL::Keyboard(unsigned char key, int x, int y) {
	m_Player->Keyboard(key,x,y);
	//for (int i = 0; i < 2; i++)
	//{
	//	objObjects[i]->Keyboard(key, x, y);
	//}
	if (key == 'd')
	{
		//rotation += 0.6;

	}
	else if (key == 'a')
	{

	}
}

void HelloGL::Menu() {

		int selection = glutCreateMenu(GLUTCallbacks::CreateMenu);

		glutAddMenuEntry("Play Again", 1);
		glutAddMenuEntry("Quit", 0);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	
}

void  HelloGL::CreateMenu(int choice) {
	switch (choice)
	{
	case 1:
		Reset();
		break;
	case 0:
		exit(0);
	default:
		break;
	}
}

void HelloGL::KeyboardUp(unsigned char key, int x, int y) {
	m_Player->KeyboardUp(key, x, y);
	if (key == 'd')
	{
		//rotation -= rotation;
	}
	else if (key == 'a')
	{
		//rotation -= 0.5f;
	}
}


void HelloGL::Reset() {
	distance = 0;
	framecount = 0;
	m_Alive = true;
	for (int i = 0; i < 8; i++)
	{
		m_ObjPositions.x = (rand() % 200) + (-30);
		m_ObjPositions.y = -18.3;
		m_ObjPositions.z = (rand() % 1000) + (-250);
		m_objects[i]->SetPos(m_ObjPositions);
	}
	position.x = ((rand() % 400) / 10.0f) - 20.0f;
	position.y = -19.4;
	//position.z = -95.8 + 16.9;
	m_Player->SetPos(position);
}

void HelloGL::Special(int key, int x, int y) {

}

void HelloGL::SpecialUp(int key, int x, int y) {

}

void HelloGL::Mouse(int button, int state, int x, int y) {

}

void HelloGL::Motion(int x, int y) {

}

void HelloGL::PassiveMotion(int x, int y) {

}

//void HelloGL::DrawPolygon() 
//{
//	glBegin(GL_POLYGON);
//	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
//	glVertex2f(-0.75, 0.5);
//	glVertex2f(0.75, 0.5);
//	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
//	glVertex2f(0.75, -0.5);
//	glVertex2f(-0.75, -0.5);
//	glEnd();
//}

//void HelloGL::DrawPolygon2()
//{
//	glBegin(GL_POLYGON);//STARTS TO DRAW A POLYGON
//		glColor3f(1.0f, 0.5f, 0.0f); // Black
//		glVertex2f(-0.13f, -0.2f);
//		glVertex2f(0.13f, -0.2f);
//		glVertex2f(0.2f, 0.0f);
//		glVertex2f(0.13f, 0.2f);
//		glVertex2f(-0.13f, 0.2f);
//		glVertex2f(-0.2f, 0.0f);
//		glEnd();
//	
//}

//void HelloGL::DrawCube() {
//	glBegin(GL_TRIANGLES);//STARTS TO DRAW A POLYGON
//	//face v0-v1-v2
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, -1);
//	//face v2-v3-v0
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	//face v0-v3-v4
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	//face v4-v5-v0
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);



//	//face v0-v5-v6
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	//face v6-v1-v0
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//
//
//
//	//face v1-v6-v7
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	//face v7-v2-v1
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//
//
//
// 	//face v7-v4-v3
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	//face v3-v2-v7
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//
//
//	//face v4-v7-v6
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	//face v6-v5-v4
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//
//
//	glEnd();
//	
//}

//void HelloGL::DrawCubeArray() {
//	glPushMatrix();
//
//	glBegin(GL_TRIANGLES);
//	for (int i = 0; i < 36; i++)
//	{
//		glColor3f(colors[i].r, colors[i].g, colors[i].b);
//		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
//	}
//	glEnd();
//	glPopMatrix();
//}
//
//void HelloGL::DrawIndexedCube() {
//	glPushMatrix();
//	glBegin(GL_TRIANGLES);
//	for (int i = 0; i < 36; i++)
//	{
//		indexedVertices[indices[i]].x;
//		indexedVertices[indices[i]].y;
//		indexedVertices[indices[i]].z;
//
//		indexedColors[indices[i]].r;
//		indexedColors[indices[i]].g;
//		indexedColors[indices[i]].b;
//
//	}
//	glEnd();
//	glPopMatrix();
//}
//
//void HelloGL::DrawCubeArrayAlt() {
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_COLOR_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//	glColorPointer(3, GL_FLOAT, 0, colors);
//
//	glPushMatrix();
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glPopMatrix();
//
//	glDisableClientState(GL_COLOR_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void HelloGL::DrawIndexedCubeArrayAlt() {
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_COLOR_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
//	glColorPointer(3, GL_FLOAT, 0, indexedColors);
//
//	glPushMatrix();
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
//	glPopMatrix();
//
//	glDisableClientState(GL_COLOR_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void HelloGL::DrawPolygon3D() {
//	
//	
//	glBegin(GL_QUADS);
//	//Top face (y = 1.0)
//	//define vertices in counter clockwise (CCW) order with normal pointing 
//	glColor3f(0.0f, 1.0f, 0.0f);     // Green
//	glVertex3f(half, half, -half);
//	glVertex3f(-half, half, -half);
//	glVertex3f(-half, half, half);
//	glVertex3f(half, half, half);
//
//	// Bottom face (y = -1.0f)
//	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
//	glVertex3f(half, -half, half);
//	glVertex3f(-half, -half, half);
//	glVertex3f(-half, -half, -half);
//	glVertex3f(half, -half, -half);
//
//	// Front face  (z = 1.0f)
//	glColor3f(1.0f, 0.0f, 0.0f);     // Red
//	glVertex3f(half, half, half);
//	glVertex3f(-half, half, half);
//	glVertex3f(-half, -half, half);
//	glVertex3f(half, -half, half);
//
//	// Back face (z = -1.0f)
//	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
//	glVertex3f(half, -half, -half);
//	glVertex3f(-half, -half, -half);
//	glVertex3f(-half, half, -half);
//	glVertex3f(half, half, -half);
//
//	// Left face (x = -1.0f)
//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//	glVertex3f(-half, half, half);
//	glVertex3f(-half, half, -half);
//	glVertex3f(-half, -half, -half);
//	glVertex3f(-half, -half, half);
//
//	// Right face (x = 1.0f)
//	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
//	glVertex3f(half, half, -half);
//	glVertex3f(half, half, half);
//	glVertex3f(half, -half, half);
//	glVertex3f(half, -half, -half);
//	glEnd();
//}
//
//
//
//
// void HelloGL::DrawRectangle(float width, float height)
//{
//	const float w = width / 2.0f;
//	const float h = height / 2.0f;
//
//	glBegin(GL_QUADS);
//	glVertex2f(-w, h);   // Top-Left
//	glVertex2f(w, h);   // Top-Right
//	glVertex2f(w, -h);   // Bottom-Right
//	glVertex2f(-w, -h);   // Bottom-Left
//	glEnd();
//
//}

// void HelloGL::DrawCircle(float radius, int numSides /* = 8 */)
//{
//	const float step = M_PI / numSides;
//	glBegin(GL_TRIANGLE_FAN);
//	glVertex2f(0.0f, 0.0f);
//	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step)
//	{
//		glVertex2f(radius * sinf(angle), radius * cosf(angle));
//	}
//	glVertex2f(0.0f, radius); // One more vertex to close the circle
//	glEnd();
//}


float HelloGL::calculateDistanceSquared(Vector3 p1, Vector3 p2) {
	float Distance = ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)) + ((p1.z - p2.z) * (p1.z - p2.z));

	return Distance;
}

HelloGL::~HelloGL(void)
{
	delete camera;
	//delete cube;
}

