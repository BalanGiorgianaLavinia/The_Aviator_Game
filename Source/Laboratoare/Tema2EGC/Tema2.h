#pragma once
#include <Component/SimpleScene.h>
#include "TemaCamera.h"
#include <Core/GPU/Mesh.h>
#include <time.h>

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		TemaCamera::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;

		bool perspectiveCamera = false;
		float fov = 60.0f;
		float left = -3.0f, right = 3.0f, bottom = -3.0f, top = 3.0f;

		float angle_Mare = 0;


		//pentru avion
		bool direction = false;		//directia de rotatie a avionului in jurul lui Ox
		float angle_avionX = 0;
		float angle_avionZ = 0;
		float angle_elice = 0;
		float translateAvionY = 2;
		bool directionZ = false;
		float mouseOy = 0;

		float scaleXPlane = 0.09f;
		float scaleYPlane = 0.1f;
		float scaleZPlane = 0.1f;

		float rightPlanePos = 3.1f;	//limita dtreapta de la elice
		float leftPlanePos = -2.0f;	//limita stanga a corpului avionului
		float upPlanePos = 2;		//limita sus a corpului avionului
		float downPlanePos = 0;		//limita jos a corpului avionului



		//pentru nori
		static const int numberOfClouds = 28;
		float angle_cloud = 0;
		float angle_cloud_component = 0;
		glm::vec3 cloudPositions[numberOfClouds];
		float cloudSpeed[numberOfClouds];


		//pentru obstacole
		static const int numberOfObstacles = 20;	//16	//12
		float translateX_obstacol = 1;
		float translateY_obstacol = 2;
		float angle_obstacle = 0;
		glm::vec3 obstaclePositions[numberOfObstacles];
		float obstacleSpeed[numberOfObstacles];


		//pentru sfera care aduce o viata in plus
		glm::vec3 bonusPos;

		

		//pentru combustibili
		glm::vec3 teapot_color;
		glm::vec3 scale_teapot = glm::vec3(0.15, 0.15, 0.15);
		float angle_teapot = 0;
		static const int numberOfFuels = 8;		//7
		static const int teapots = 6;


		glm::vec3 fuel[numberOfFuels][teapots];
		float combustibilSpeed[numberOfFuels];

		//pentru vieti
		glm::vec3 scale_vieti = glm::vec3(0.003);
		float translateX_life = -3.6f;
		float translateY_life = 4.0f;
		float translateZ_life = 0.2;
		int vieti = 3;


		//pentru bara combustibil
		float translateX_bara_fata = 0.6f;
		glm::vec3 color_bara_fata = glm::vec3(0.3, 1, 0.6);


		//pentru camera
		bool cameraFT = false;


		int score = 0;

		
};
