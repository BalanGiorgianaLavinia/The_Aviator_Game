#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include <ctime>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

float doubleRand2(float LO, float HI) {
	float r3 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	return r3;
}

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new TemaCamera::Camera();


	camera->Set(glm::vec3(0, 1.45, 3.5f), glm::vec3(0, 2.1, 0), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);


	/////////////////////////////////shadere////////////////////////////
	//shader mare
	{
		Shader *shader = new Shader("Shader_Mare");
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/VertexShader_Apa.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/FragmentShader_Apa.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//shader avion
	{
		Shader *shader = new Shader("Shader_Avion");
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/VertexShader_Avion.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/FragmentShader_Avion.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//shader obstacole
	{
		Shader *shader = new Shader("Shader_Obstacole");
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/VertexShader_Obstacole.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/FragmentShader_Obstacole.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//shader combustibili
	{
		Shader *shader = new Shader("Shader_Combustibili");
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/VertexShader_Combustibili.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2EGC/Shaders/FragmentShader_Combustibili.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}



	/////////////////////////////////meshe//////////////////////////////
	// corpul avionului
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-2, 0.8,  0.5),	glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(2, 0,  0),		glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(2, 2, 0),		glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(-2, 1.5, 0.5),	glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-2, 1.5, 1.5),	glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(-2, 0.8, 1.5),	glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(2, 0, 2),		glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(2, 2, 2),		glm::vec3(0.5, 0.6, 0.6), glm::vec3(0.1, 0.5, 0.8))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 2, 3,
			0, 5, 4,		0, 4, 3,
			5, 6, 7,		5, 7, 4,
			6, 1, 2,		2, 7, 6,
			7, 2, 4,		4, 2, 3,
			6, 1, 5,		5, 1, 0
		};
		Mesh* cub_corp = new Mesh("cube_body");
		cub_corp = CreateMesh("cube_body", vertices, indices);
		meshes[cub_corp->GetMeshID()] = cub_corp;
	}


	// botul avionului
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(2, 0,	0),	glm::vec3(0), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(2.5, 0,	0),	glm::vec3(0), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(2.5, 2,	0),	glm::vec3(0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(2, 2,	0),	glm::vec3(0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(2, 2,	2),	glm::vec3(0), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(2.5, 2,	2),	glm::vec3(0), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(2.5, 0,	2),	glm::vec3(0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(2, 0,	2),	glm::vec3(0), glm::vec3(0.1, 0.5, 0.8))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* cub_fata = new Mesh("cube_face");
		cub_fata = CreateMesh("cube_face", vertices, indices);
		meshes[cub_fata->GetMeshID()] = cub_fata;
	}
	// aripile avionului
	{
		vector<VertexFormat> vertices
		{
		
			VertexFormat(glm::vec3(-0.1,	1,		-1.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1.5,		1,		-1.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(1.5,		1.2,	-1.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(-0.1,	1.2,	-1.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-0.1,	1.2,	 3.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1.5,		1.2,	 3.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(1.5,		1,		 3.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(-0.1,	1,		 3.5),		glm::vec3(0.5, 0.3, 0.1), glm::vec3(0.1, 0.5, 0.8))

		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0,
		};

		Mesh* cub_aripi = new Mesh("cube_wing");
		cub_aripi = CreateMesh("cube_wings", vertices, indices);
		meshes[cub_aripi->GetMeshID()] = cub_aripi;
	}
	//suport elice
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(2.5, 0.8, 0.8),	glm::vec3(0.6, 0, 0), glm::vec3(0.2, 0.8, 0.2)),//0
			VertexFormat(glm::vec3(2.8, 0.8, 0.8),	glm::vec3(0.6, 0, 0), glm::vec3(0.9, 0.4, 0.2)),//1
			VertexFormat(glm::vec3(2.8, 1.2, 0.8),	glm::vec3(0.6, 0, 0), glm::vec3(0.7, 0.7, 0.1)),//2
			VertexFormat(glm::vec3(2.5, 1.2, 0.8),	glm::vec3(0.6, 0, 0), glm::vec3(0.7, 0.3, 0.7)),//3
			VertexFormat(glm::vec3(2.5, 1.2, 1.2),	glm::vec3(0.6, 0, 0), glm::vec3(0.3, 0.5, 0.4)),//4
			VertexFormat(glm::vec3(2.8, 1.2, 1.2),	glm::vec3(0.6, 0, 0), glm::vec3(0.5, 0.2, 0.9)),//5
			VertexFormat(glm::vec3(2.8, 0.8, 1.2),	glm::vec3(0.6, 0, 0), glm::vec3(0.7, 0.0, 0.7)),//6
			VertexFormat(glm::vec3(2.5, 0.8, 1.2),	glm::vec3(0.6, 0, 0), glm::vec3(0.1, 0.5, 0.8))//7
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* cub_suport = new Mesh("cube_elice_suport");
		cub_suport = CreateMesh("cube_elice_suport", vertices, indices);
		meshes[cub_suport->GetMeshID()] = cub_suport;
	}
	//elice
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(2.8,			0 - 0.5,	0 + 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.2, 0.8, 0.2)),//0
			VertexFormat(glm::vec3(2.8 + 0.3,	0 - 0.5,	0 + 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.9, 0.4, 0.2)),//1
			VertexFormat(glm::vec3(2.8 + 0.3,	2 + 0.5,	0 + 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.7, 0.1)),//2
			VertexFormat(glm::vec3(2.8,			2 + 0.5,	0 + 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.3, 0.7)),//3
			VertexFormat(glm::vec3(2.8,			2 + 0.5,	2 - 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.3, 0.5, 0.4)),//4
			VertexFormat(glm::vec3(2.8 + 0.3,	2 + 0.5,	2 - 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.5, 0.2, 0.9)),//5
			VertexFormat(glm::vec3(2.8 + 0.3,	0 - 0.5,	2 - 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.0, 0.7)),//6
			VertexFormat(glm::vec3(2.8,			0 - 0.5,	2 - 0.8),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.1, 0.5, 0.8)),//7
																					  
			VertexFormat(glm::vec3(2.8,			0 + 0.8,	0 - 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(2.8 + 0.3,	0 + 0.8,	0 - 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(2.8 + 0.3,	2 - 0.8,	0 - 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(2.8,			2 - 0.8,	0 - 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(2.8,			2 - 0.8,	2 + 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(2.8 + 0.3,	2 - 0.8,	2 + 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(2.8 + 0.3,	0 + 0.8,	2 + 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(2.8,			0 + 0.8,	2 + 0.5),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.1, 0.5, 0.8))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0,

			8, 9, 10,		8, 10, 11,
			15, 12, 8,		8, 12, 11,
			14, 13, 15,		15, 13, 12,
			9, 10, 14,		14, 10, 13,
			13, 10, 12,		12, 10, 11,
			14, 9, 15,		15, 9, 8
		};
		Mesh* cub_elice = new Mesh("cube_elice");
		cub_elice = CreateMesh("cube_elice", vertices, indices);
		meshes[cub_elice->GetMeshID()] = cub_elice;
	}
	// coada avionului
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-2 -0.4, 1, 0.95),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.2, 0.8, 0.2)),//0
			VertexFormat(glm::vec3(-2, 1, 0.95),			glm::vec3(0.4, 0.3, 0), glm::vec3(0.9, 0.4, 0.2)),//1
			VertexFormat(glm::vec3(-2, 2.5, 0.95),			glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.7, 0.1)),//2
			VertexFormat(glm::vec3(-2 -0.4, 2.5, 0.95),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.3, 0.7)),//3
			VertexFormat(glm::vec3(-2 -0.4, 2.5, 1.05),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.3, 0.5, 0.4)),//4
			VertexFormat(glm::vec3(-2, 2.5, 1.05),			glm::vec3(0.4, 0.3, 0), glm::vec3(0.5, 0.2, 0.9)),//5
			VertexFormat(glm::vec3(-2, 1, 1.05),			glm::vec3(0.4, 0.3, 0), glm::vec3(0.7, 0.0, 0.7)),//6
			VertexFormat(glm::vec3(-2 -0.4, 1, 1.05),		glm::vec3(0.4, 0.3, 0), glm::vec3(0.1, 0.5, 0.8))//7
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* cub_coada = new Mesh("cube_tail");
		cub_coada = CreateMesh("cube_tail", vertices, indices);
		meshes[cub_coada->GetMeshID()] = cub_coada;
	}


	//////////////////////pilot
	// head1
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, 1,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(1, 1,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(1, 2,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 2,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 2,	1.5),	glm::vec3(0)),
			VertexFormat(glm::vec3(1, 2,	1.5),	glm::vec3(0)),
			VertexFormat(glm::vec3(1, 1,	1.5),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 1,	1.5),	glm::vec3(0))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* head = new Mesh("head1");
		head = CreateMesh("head1", vertices, indices);
		meshes[head->GetMeshID()] = head;
	}

	// head2
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.8, 2.1,	0.4),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(0.8, 2.1,	0.4),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(0.8, 2.9,	0.4),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(-0.8, 2.9,	0.4),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(-0.8, 2.9,	1.6),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(0.8, 2.9,	1.6),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(0.8, 2.1,	1.6),	glm::vec3(0.9, 0.7, 0.6)),
			VertexFormat(glm::vec3(-0.8, 2.1,	1.6),	glm::vec3(0.9, 0.7, 0.6))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* head = new Mesh("head2");
		head = CreateMesh("head2", vertices, indices);
		meshes[head->GetMeshID()] = head;
	}

	// head3
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-0.8, 2.9,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.9,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 3.1,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-0.8, 3.1,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-0.8, 3.1,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 3.1,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.9,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(-0.8, 2.9,	1.6),	glm::vec3(0))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* head = new Mesh("head3");
		head = CreateMesh("head3", vertices, indices);
		meshes[head->GetMeshID()] = head;
	}

	// head4
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, 3,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 3,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 3.3,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 3.3,	0.4),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 3.3,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 3.3,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 3,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(-1, 3,	1.6),	glm::vec3(0))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* head = new Mesh("head4");
		head = CreateMesh("head4", vertices, indices);
		meshes[head->GetMeshID()] = head;
	}

	// head5
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 2.6,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.6,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.7,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 2.7,	1.6),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 2.7,		1.7),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.7,	1.7),	glm::vec3(0)),
			VertexFormat(glm::vec3(0.8, 2.6,	1.7),	glm::vec3(0)),
			VertexFormat(glm::vec3(0, 2.6,		1.7),	glm::vec3(0))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3,
			7, 4, 0,		0, 4, 3,
			6, 5, 7,		7, 5, 4,
			1, 2, 6,		6, 2, 5,
			5, 2, 4,		4, 2, 3,
			6, 1, 7,		7, 1, 0
		};
		Mesh* head = new Mesh("head5");
		head = CreateMesh("head5", vertices, indices);
		meshes[head->GetMeshID()] = head;
	}



	// marea
	{
		vector<VertexFormat> vertices;
		vector<unsigned short> indices;

		int numberOfCircles = 10;
		float z;
		

		for (int i = 0; i < numberOfCircles; i++) {
			z = i * 0.05;
			for (int j = 0; j < 3600; j++) {
				float x = (rand() % 200 - 100) * 0.01;
				float y = (rand() % 200 - 100) * 0.01;
				glm::vec3 random_val = glm::vec3(x, y, 0);
				vertices.push_back(VertexFormat(glm::vec3(cos(j), sin(j), z), glm::vec3(0), random_val));
			}
		}

		for (int i = 0; i < numberOfCircles - 1; i++) {
			for (int j = 0; j < 3600; j++) {
				indices.push_back(i * 3600 + j);
				indices.push_back(i * 3600 + j + 1);
				indices.push_back((i+1) * 3600 + j + 1);

				indices.push_back(i * 3600);
				indices.push_back((i + 1) * 3600 + j + 1);
				indices.push_back((i + 1) * 3600 + j);
			}
		}

		Mesh* mesh = new Mesh("sea");
		mesh = CreateMesh("sea", vertices, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}


	//norii
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0,  0),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(2, 0,  0),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(2, 2, 0),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(0, 2, 0),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(0, 2, 2),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(0, 0, 2),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(2, 0, 2),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(2, 2, 2),	glm::vec3(0.9, 0.9, 0.8), glm::vec3(0.1, 0.5, 0.8))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 2, 3,
			0, 5, 4,		0, 4, 3,
			5, 6, 7,		5, 7, 4,
			6, 1, 2,		2, 7, 6,
			7, 2, 4,		4, 2, 3,
			6, 1, 5,		5, 1, 0
		};
		Mesh* cub_nor = new Mesh("cube_cloud");
		cub_nor = CreateMesh("cube_cloud", vertices, indices);
		meshes[cub_nor->GetMeshID()] = cub_nor;

		for (int i = 0; i < numberOfClouds; i++) {
			float x = 1 + (rand() % 100) * 0.4f ;
			float y = 2.2f + (rand() % 100) * 0.03f;
			float z = (rand() % 100) * 0.01 - 1.5;
			cloudPositions[i] = glm::vec3(x, y, z);

			float speed = doubleRand2(0.5, 1);
			cloudSpeed[i] = speed;
		}
		
	}
	
	//obstacolele
	{
		Mesh* mesh = new Mesh("obstacle");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		for (int i = 0; i < numberOfObstacles; i++) {
			float x = doubleRand2(6.0, 20.0);
			float y = 1.6 + (rand() % 2800) * 0.001; // 1.6;
			obstaclePositions[i] = glm::vec3(x, y, 0);
			obstacleSpeed[i] = doubleRand2(1.2, 1.8);		//0.8
			Sleep(10);
		}
	}


	//combustibilii
	{
		Mesh* mesh = new Mesh("combustibil");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;

		for (int sir = 0; sir < numberOfFuels; sir++) {
			float x = doubleRand2(6.0, 20.0);
			float y = 1.6 + (rand() % 2800) * 0.001;
			float speed = doubleRand2(1, 1.2);
			combustibilSpeed[sir] = speed;

			Sleep(10);

			for (int teapot = 0; teapot < teapots; teapot++) {
				float ceva = teapot % 2 != 0 ? 0 : 0.05;
				fuel[sir][teapot] = glm::vec3(x + teapot * 0.15, y - ceva, 0);
			}
		}

	}


	//bara combustibil
	//bara combustibil - spate
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, -0.1),	glm::vec3(0), glm::vec3(1)),
			VertexFormat(glm::vec3(2, 0, -0.1),	glm::vec3(0), glm::vec3(1)),
			VertexFormat(glm::vec3(2, 1, -0.1),	glm::vec3(0), glm::vec3(1)),
			VertexFormat(glm::vec3(0, 1, -0.1),	glm::vec3(0), glm::vec3(1))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3
		};
		Mesh* bara_spate = new Mesh("bara_spate");
		bara_spate = CreateMesh("bara_spate", vertices, indices);
		meshes[bara_spate->GetMeshID()] = bara_spate;
	}
	//bara combustibil - fata
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0),	glm::vec3(0.3, 1, 0.6), glm::vec3(0)),
			VertexFormat(glm::vec3(2, 0, 0),	glm::vec3(0.3, 1, 0.6), glm::vec3(0)),
			VertexFormat(glm::vec3(2, 1, 0),	glm::vec3(0.3, 1, 0.6), glm::vec3(0)),
			VertexFormat(glm::vec3(0, 1, 0),	glm::vec3(0.3, 1, 0.6), glm::vec3(0))
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,		0, 2, 3
		};
		Mesh* bara_fata = new Mesh("bara_fata");
		bara_fata = CreateMesh("bara_fata", vertices, indices);
		meshes[bara_fata->GetMeshID()] = bara_fata;
	}

	//vieti
	{
		Mesh* mesh = new Mesh("hearth");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "hearth.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	//sfera care aduce o viata in plus
	{
		float x = doubleRand2(6.0, 10.0);
		float y = 1.6 + (rand() % 2800) * 0.001;

		bonusPos = glm::vec3(x, y, 0);
	}

}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}
void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1, 1, 0.7, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
	if (cameraFT == false)
		camera->Set(glm::vec3(0, 1.45, 3.5f), glm::vec3(0, 2.1, 0), glm::vec3(0, 1, 0));
	else
		camera->Set(glm::vec3(0.07, translateAvionY + 0.2, 0), glm::vec3(translateAvionY, translateAvionY, 0), glm::vec3(0, translateAvionY, 0));

	//randez avion
	{
		//conditii terminare joc
		//terminare vieti sau terminare combustibil
		if (vieti <= 0 || translateX_bara_fata <= 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, translateAvionY, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleXPlane, scaleYPlane, scaleZPlane));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_avionZ), glm::vec3(0, 0, 1));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_avionX), glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -1.0f, -1.0f));

			RenderSimpleMesh(meshes["head1"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head2"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head3"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head4"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head5"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_body"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_face"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_elice_suport"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_tail"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_wings"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_elice"], shaders["Shader_Avion"], modelMatrix);

			translateAvionY -= deltaTimeSeconds;
			angle_avionX += 300 * deltaTimeSeconds;
			angle_avionZ -= 100 * deltaTimeSeconds;

			if (angle_avionZ <= -70) { angle_avionZ = -70; }
		}
		else {

			score += 1;					//maresc scorul jucatorului


			rightPlanePos = 3.1f;
			leftPlanePos = -2.0f;
			upPlanePos = 2;
			downPlanePos = 0;

			//	rotirea avionului pe Ox
			if (direction == false)	angle_avionX += 40 * deltaTimeSeconds;
			else                    angle_avionX -= 40 * deltaTimeSeconds;

			if (angle_avionX < -45) {
				angle_avionX = -45;
				direction = false;	//adica sa o ia spre dreapta
			}
			if (angle_avionX > 45) {
				angle_avionX = 45;
				direction = true;	//adica sa o ia spre stanga
			}

			//rotirea avionului pe Oz
			angle_avionZ += mouseOy;
			if (angle_avionZ > 1) {
				angle_avionZ -= 5 * deltaTimeSeconds;
			}
			else if (angle_avionZ < -1) {
				angle_avionZ += 5 * deltaTimeSeconds;
			}
			else {
				angle_avionZ = 0;
			}

			if (angle_avionZ >= 30)		angle_avionZ = 30;
			if (angle_avionZ <= -30) 	angle_avionZ = -30;


			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, translateAvionY, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleXPlane, scaleYPlane, scaleZPlane));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_avionZ), glm::vec3(0, 0, 1));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_avionX), glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -1.0f, -1.0f));

			RenderSimpleMesh(meshes["head1"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head2"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head3"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head4"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["head5"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_body"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_face"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_elice_suport"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_tail"], shaders["Shader_Avion"], modelMatrix);
			RenderSimpleMesh(meshes["cube_wings"], shaders["Shader_Avion"], modelMatrix);


			//randez elicea
			angle_elice += 800 * deltaTimeSeconds;
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.0f, 1.0f));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_elice), glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.0f, -1.0f));
			RenderSimpleMesh(meshes["cube_elice"], shaders["Shader_Avion"], modelMatrix);

			//actualizez limitele de incadrare ale avionului

			rightPlanePos -= 0.5f;
			rightPlanePos *= scaleXPlane;

			leftPlanePos -= 0.5f;
			leftPlanePos *= scaleXPlane;

			upPlanePos -= 1.0f;
			upPlanePos *= scaleYPlane;
			upPlanePos += translateAvionY;

			downPlanePos -= 1.0f;
			downPlanePos *= scaleYPlane;
			downPlanePos += translateAvionY;
		}


		//iesire joc cand avionul ajunge sub apa
		//ori i s-au terminat vietile, ori s-a terminat combustibilul, ori s-a dus el in apa
		if (translateAvionY < 1.4) {
			cout << "Game Over! :(" << endl;
			cout << "Scorul tau este " << score / 10 << endl;
			exit(0);
		}

	}

	//randez norii
	{
		for (int i = 0; i < numberOfClouds; i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, cloudPositions[i]);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(30 + 60), glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.15f, 0.06f));
			RenderSimpleMesh(meshes["cube_cloud"], shaders["Shader_Avion"], modelMatrix);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5, 0.5, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.8f, 0.8f));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_cloud_component), glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1));
			RenderSimpleMesh(meshes["cube_cloud"], shaders["Shader_Avion"], modelMatrix);

			modelMatrix = glm::rotate(modelMatrix, RADIANS(20), glm::vec3(0, 1, 1));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5, 0, 0));
			RenderSimpleMesh(meshes["cube_cloud"], shaders["Shader_Avion"], modelMatrix);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_cloud_component), glm::vec3(1, 1, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1));
			RenderSimpleMesh(meshes["cube_cloud"], shaders["Shader_Avion"], modelMatrix);

			cloudPositions[i].x -= deltaTimeSeconds * cloudSpeed[i];
			if (cloudPositions[i].x < -7) {
				cloudPositions[i].x = 5 + (rand() % 100) * 0.4f;

				float speed = doubleRand2(0.5, 1);
				cloudSpeed[i] = speed;
			}
		}

		angle_cloud_component += 40 * deltaTimeSeconds;
	}


	//randez marea
	{
		float additionalScale = cameraFT ? 1.2 : 0;

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_Mare), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3 + additionalScale, 1.3 + additionalScale, 20));

		RenderSimpleMesh(meshes["sea"], shaders["Shader_Mare"], modelMatrix, glm::vec3(1, 0.5, 0.5));

		angle_Mare += 10 * deltaTimeSeconds;
	}


	//randez obstacole
	{
		for (int i = 0; i < numberOfObstacles; i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, obstaclePositions[i]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_obstacle), glm::vec3(1, 1, 1));
			RenderSimpleMesh(meshes["obstacle"], shaders["Shader_Obstacole"], modelMatrix, glm::vec3(0.7, 0, 0));	

			obstaclePositions[i].x -= deltaTimeSeconds * obstacleSpeed[i];
			if (obstaclePositions[i].x < -4) {
				float x = doubleRand2(6.0, 20.0);
				float y = 1.6 + (rand() % 2800) * 0.001;
				obstaclePositions[i] = glm::vec3(x, y, 0);

				obstacleSpeed[i] = doubleRand2(1.3, 1.8);		//0.8

				if (cameraFT)	obstacleSpeed[i] = doubleRand2(0.3, 1.0);		//vreau sa micsorez viteza obstacolelor in first person
				

				if (score >= 200)	obstacleSpeed[i] *= 1.5;		//factor pentru marirea vitezei atunci cand avansez in scor
			}

			//verific coliziune
			if (obstaclePositions[i].x - 0.1 <= rightPlanePos && obstaclePositions[i].x + 0.1 >= leftPlanePos &&
				obstaclePositions[i].y - 0.1 <= upPlanePos && obstaclePositions[i].y + 0.1 >= downPlanePos) {
					float x = doubleRand2(6.0, 20.0);
					obstaclePositions[i].x = x;

					vieti -= 1;
			}
					
		}
		
		angle_obstacle += 60 * deltaTimeSeconds;
	}


	//randez sfera care aduce o viata in plus
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, bonusPos);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));
		RenderSimpleMesh(meshes["obstacle"], shaders["Shader_Obstacole"], modelMatrix, glm::vec3(0.5, 0.2, 1));

		bonusPos.x -= deltaTimeSeconds * doubleRand2(1.3, 1.8);

		if (bonusPos.x < -10) {
			float x = doubleRand2(10.0, 16.0);
			float y = 1.6 + (rand() % 2800) * 0.001;

			bonusPos = glm::vec3(x, y, 0);
		}

		//coliziune
		if (bonusPos.x - 0.1 <= rightPlanePos && bonusPos.x + 0.1 >= leftPlanePos &&
			bonusPos.y - 0.1 <= upPlanePos && bonusPos.y + 0.1 >= downPlanePos) {
				float x = doubleRand2(10.0, 16.0);
				float y = 1.6 + (rand() % 2800) * 0.001;

				bonusPos = glm::vec3(x, y, 0);

				if (vieti < 3)	vieti += 1;
			
		}
	}


	//randez combustibilii
	{
		angle_teapot += 100 * deltaTimeSeconds;
		teapot_color = glm::vec3(0.4, 0.6, 0.9);

		for (int sir = 0; sir < numberOfFuels; sir++) {
			for (int teapot = 0; teapot < teapots; teapot++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, fuel[sir][teapot]);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(scale_teapot));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(angle_teapot), glm::vec3(1, 1, 1));
				RenderSimpleMesh(meshes["combustibil"], shaders["Shader_Combustibili"], modelMatrix, teapot_color);

				float factor = score >= 200 ? 1.5 : 1;			//factor pentru marirea vitezei atunci cand avansez in scor

				fuel[sir][teapot].x -= factor * combustibilSpeed[sir] * deltaTimeSeconds;

				if (fuel[sir][teapot].x < -4) {
					if (teapot == 0) {
						float x = doubleRand2(6.0, 20.0);
						float y = 1.6 + (rand() % 2800) * 0.001;
						fuel[sir][teapot] = glm::vec3(x, y, 0);
					}
					else {
						float ceva = teapot % 2 != 0 ? 0 : 0.05;
						fuel[sir][teapot] = fuel[sir][0] + glm::vec3(teapot * 0.15, -ceva, 0);
					}
				}

				
				if (fuel[sir][teapot].x - 0.1 <= rightPlanePos && fuel[sir][teapot].x + 0.1 >= leftPlanePos &&
					fuel[sir][teapot].y - 0.1 <= upPlanePos && fuel[sir][teapot].y + 0.1 >= downPlanePos) {

						translateX_bara_fata += 0.02;		//cresc combustibilul cand acumuleaza teapot-uri
						if (translateX_bara_fata >= 0.6) { translateX_bara_fata = 0.6; }

					if (teapot == 0) {
						float x = doubleRand2(6.0, 20.0);
						float y = 1.6 + (rand() % 2800) * 0.001;
						fuel[sir][teapot] = glm::vec3(x, y, 0);
					}
					else {
						float ceva = teapot % 2 != 0 ? 0 : 0.05;
						fuel[sir][teapot] = fuel[sir][0] + glm::vec3(teapot * 0.15, -ceva, 0);
					}

				}
			}
		}
	}



	//randez vietile jucatorului
	{
		if (vieti > 0) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX_life, translateY_life, translateZ_life));
			modelMatrix = glm::scale(modelMatrix, scale_vieti);
			RenderSimpleMesh(meshes["hearth"], shaders["Shader_Combustibili"], modelMatrix, glm::vec3(1, 0, 0));

			if (vieti > 1) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX_life + 0.3, translateY_life, translateZ_life));
				modelMatrix = glm::scale(modelMatrix, scale_vieti);
				RenderSimpleMesh(meshes["hearth"], shaders["Shader_Combustibili"], modelMatrix, glm::vec3(1, 0, 0));

				if (vieti > 2) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX_life + 0.6, translateY_life, translateZ_life));
					modelMatrix = glm::scale(modelMatrix, scale_vieti);
					RenderSimpleMesh(meshes["hearth"], shaders["Shader_Combustibili"], modelMatrix, glm::vec3(1, 0, 0));
				}
			}
		}
	}


	//randez bara de combustibil
	{ 
		//randez bara fata
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX_life - 0.15, 3.7, translateZ_life));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(translateX_bara_fata, 0.2, 0));
			RenderSimpleMesh(meshes["bara_fata"], shaders["Shader_Combustibili"], modelMatrix, color_bara_fata);
		}


		if(cameraFT) { translateX_bara_fata -= 0.01 * deltaTimeSeconds; }	//daca sunt in first person scad mai greu combustibilul
		else			translateX_bara_fata -= 0.05 * deltaTimeSeconds;	//fac sa scada combustibilul in timp


		if (translateX_bara_fata <= 0.15) 	color_bara_fata = glm::vec3(1, 0, 0);
		else								color_bara_fata = glm::vec3(0.3, 1, 0.6);
	
		if (translateX_bara_fata <= 0) {
			translateX_bara_fata = 0;
		}

		//randez bara spate
		{
			glm::mat4 modelmatrix = glm::mat4(1);
			modelmatrix = glm::translate(modelmatrix, glm::vec3(translateX_life - 0.15, 3.7, translateZ_life));
			modelmatrix = glm::scale(modelmatrix, glm::vec3(0.6, 0.2, 0));
			RenderSimpleMesh(meshes["bara_spate"], shaders["Shader_Combustibili"], modelmatrix, glm::vec3(0));
		}
		
	}


	//randez apa peste tot
	{
		glm::mat4 modelmatrix = glm::mat4(1);
		modelmatrix = glm::scale(modelmatrix, glm::vec3(100, 0.1, 40));
		modelmatrix = glm::translate(modelmatrix, glm::vec3(-2.25, -2, -1));
		RenderSimpleMesh(meshes["cube_face"], shaders["Shader_Combustibili"], modelmatrix, glm::vec3(0.6, 1, 1));
	}


}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	GLint loc_obj_color = glGetUniformLocation(shader->program, "color");
	glUniform3f(loc_obj_color, color.x, color.y, color.z);

	double time = Engine::GetElapsedTime();
	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, time);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed * deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-cameraSpeed * deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-cameraSpeed * deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(cameraSpeed * deltaTime);

		}


		if (window->KeyHold(GLFW_KEY_1)) {
			left += 10.0f * deltaTime;
			right -= 10.0f * deltaTime;
		}
		if (window->KeyHold(GLFW_KEY_2)) {
			left -= 10.0f * deltaTime;
			right += 10.0f * deltaTime;
		}
		if (window->KeyHold(GLFW_KEY_3)) {
			top -= 10.0f * deltaTime;
			bottom += 10.0f * deltaTime;
		}
		if (window->KeyHold(GLFW_KEY_4)) {
			top += 10.0f * deltaTime;
			bottom -= 10.0f * deltaTime;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_C) {
		cameraFT = !cameraFT;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float sensivityOX = 0.001f;
	float sensivityOY = 0.0065f;
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			camera->RotateFirstPerson_OX(-sensivityOY * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOX * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			camera->RotateThirdPerson_OX(sensivityOY * deltaY);
			camera->RotateThirdPerson_OY(sensivityOX * deltaX);
		}
	}

	mouseOy = -deltaY;

	if(vieti > 0) translateAvionY -= sensivityOY * deltaY;
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
