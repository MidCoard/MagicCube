#include "RenderLayer.h"


STATE cubeState = STOP;//记录旋转信息

ROTATE_FLAG rotateFlag = NO_ROTATE;//标记要旋转的层数

namespace Render {

	bool startGameLoop = false;
	bool pause = false;
	bool help = false;
	bool developer = false;
	bool backToTitle = false;
	bool openFileSuccess = false;
	bool ignoreKeyboardInput = false;
	bool firstMouse = true;
	bool initialize = false;

	GLWindow *mainWindow;

	Shader *cubeShader;

	Camera *camera;

	unsigned int locationValue = 0;

	mat4 projection = mat4(1.0f);
	mat4 view = mat4(1.0f);

	mat4 currentModel = mat4(1.0f);
	vector<mat4> allCubesState(NUM_CUBES, mat4(1.0f));
	const mat4 identityMatrix = mat4(1.0f);//单位矩阵

	const float rotateVelocity = 4.0f;
	float angle = 0.0;
	float targetAngle = 90.0;
	vec3 rotationVector;
	mutex cubeMutex;

	GLuint magicCubeVAO, magicCubeVBO;
	GLuint ColorVBO;
	
	float lastX,lastY;
	
/*绘制光源使用，本程序不需要绘制出光源，故保留不用*/
	Shader *lightShader;
	GLuint lightVAO, lightVBO;
	GLuint normalVBO;
	vec3 lightPosition = CAMERA_POSITION;
	mat4 lightModel = mat4(1.0f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);



	bool isStartGameLoop() {
		return startGameLoop;
	}

	bool isPause() {
		return pause;
	}

	bool isHelp() {
		return help;
	}

	bool isDeveloper() {
		return developer;
	}

	bool isBackToTitle() {
		return backToTitle;
	}

	bool isOpenFileSuccess() {
		return openFileSuccess;
	}

	void setBackToTitle(bool flag) {
		backToTitle = flag;
	}

	void setPause(bool flag) {
		pause = flag;
	}

	void setDeveloper(bool flag) {
		developer = flag;
	}

	void setHelp(bool flag) {
		help = flag;
	}

	void setStartGameLoop(bool flag) {
		startGameLoop = flag;
	}
	
	bool isInitialize() {
		return initialize;
	}
	
	Camera *getCamera() {
		return camera;
	}

	void setCamera(Camera *c) {
		camera = c;
	}

	void setCurrentModel(mat4 m) {
		currentModel = m;
	}

	mat4 *getCubeState(int x, int y, int z) {
		return &allCubesState[x * 9 + y * 3 + z];
	}

	void resetStates() {
		for (int i = 0; i < NUM_CUBES; i++)
			Render::allCubesState[i] = mat4(1.0f);
	}

	bool isIgnoreKeyboardInput() {
		return ignoreKeyboardInput;
	}

	void initRenderLayer(char *state) {
		if (initialize)
			return;

		mainWindow = new GLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, (char *) WINDOW_TITLE);
		cubeShader = new Shader("shaders/MagicCube.vs", "shaders/MagicCube.fs");
		lightShader = new Shader("shaders/Light.vs", "shaders/Light.fs");
		camera = new Camera(CAMERA_POSITION);

		projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		view = camera->getViewMatrix();

		defaultVertices();
		setColors(logicColors[0], logicColors[1], logicColors[2], logicColors[3], logicColors[4], logicColors[5]);

		glfwSetFramebufferSizeCallback(mainWindow->getWindow(), frameBufferSizeCallback);
		glfwSetCursorPosCallback(mainWindow->getWindow(), mouseCallback);
		glfwSetScrollCallback(mainWindow->getWindow(), scrollCallback);

		setMagicCubeMatrix();
		initImage();

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &magicCubeVAO);

		glGenVertexArrays(1, &lightVAO);
		glGenBuffers(1, &lightVBO);

		attribPointer();

		lightModel = translate(lightModel, lightPosition);
		lightModel = scale(lightModel, vec3(0.2f));
		string check(state);
		if (!check.empty()) {
			FILE *file = fopen(state, "rb");
			if (file == nullptr) {
				cout << "Cannot open " << state << endl;
				cout << "Use default states" << endl;
			} else {
				openFileSuccess = true;
				cout << "Find valid states" << endl;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						for (int k = 0; k < 3; k++)
							fread(Render::getCubeState(i, j, k), sizeof(mat4), 1, file);
				fclose(file);
			}
		}
		initialize = true;
	}

	void startMenu() {
		projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		view = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0, 0, 0), camera->getWorldUp());
		glClearColor(WINDOW_COLOR.getR(), WINDOW_COLOR.getG(), WINDOW_COLOR.getB(), WINDOW_COLOR.getA());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float alpha = abs(sin(glfwGetTime()));
		renderImage(vec3(0, 2, 0), vec3(3.3f, 1.1f, 1.0f), 1.0f, view, projection, (char *) "images/Title.png");
		renderImage(vec3(0, 0.2, 0), vec3(2.79f, 0.93f, 1.0f), alpha, view, projection,
		            (char *) "images/Start.png");
		renderImage(vec3(0, -2, 0), vec3(1.8f, 0.6f,1.0f), 1.0f, view, projection, (char *) "images/help.png");
		renderImage(vec3(0, -3, 0), vec3(1.8f, 0.6f, 1.0f), 1.0f, view, projection, (char *) "images/Developer.png");
		if (openFileSuccess)
			renderImage(vec3(-3, -3.8, 0), vec3(1.8f, 0.6f, 1.0f), 1.0f, view, projection, (char *) "images/SaveSucceed.png");
		if (!openFileSuccess)
			renderImage(vec3(-3, -3.8, 0), vec3(1.8f, 0.6f, 1.0f), 1.0f, view, projection, (char *) "images/SaveFail.png");
		glfwSwapBuffers(mainWindow->getWindow());
		glfwPollEvents();
	};

	void pauseMenu() {
		projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		view = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0, 0, 0), camera->getWorldUp());
		glClearColor(WINDOW_COLOR.getR(), WINDOW_COLOR.getG(), WINDOW_COLOR.getB(), WINDOW_COLOR.getA());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderImage(vec3(0, 1, 0), vec3(4.5f, 1.5f, 1.0f), 1.0f, view, projection,
		            (char *) "images/pause.png");
		renderImage(vec3(0, -1, 0), vec3(2.4f, 0.8f, 1.0f), 1.0f, view, projection, (char *) "images/help.png");
		renderImage(vec3(0, -2, 0), vec3(2.1f, 0.7f, 1.0f), 1.0f, view, projection, (char *) "images/BackToTitle.png");
		glfwSwapBuffers(mainWindow->getWindow());
		glfwPollEvents();
	}

	void helpMenu() {
		projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		view = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0, 0, 0), camera->getWorldUp());
		glClearColor(WINDOW_COLOR.getR(), WINDOW_COLOR.getG(), WINDOW_COLOR.getB(), WINDOW_COLOR.getA());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (help)
			renderImage(vec3(0, 0, 0), vec3(4.2f, 4.2f, 1.0f), 1.0f, view, projection,
			            (char *) "images/HelpContent.png");
		else if (developer)
			renderImage(vec3(0, 0, 0), vec3(4.2f, 4.2f, 1.0f), 1.0f, view, projection,
			            (char *) "images/DeveloperInfo.png");
		glfwSwapBuffers(mainWindow->getWindow());
		glfwPollEvents();
	}

	void attribPointer() {
		glBindVertexArray(magicCubeVAO);

		glGenBuffers(1, &magicCubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, magicCubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(localCubeVertices), localCubeVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(locationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
		glEnableVertexAttribArray(locationValue++);//链接顶点

		glGenBuffers(1, &normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normalVector), normalVector, GL_STATIC_DRAW);
		glVertexAttribPointer(locationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
		glEnableVertexAttribArray(locationValue++);//链接法向量

		glGenBuffers(1, &ColorVBO);
		glBindBuffer(GL_ARRAY_BUFFER, ColorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(locationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
		glEnableVertexAttribArray(locationValue++);//链接颜色

		locationValue = 0;

		glBindVertexArray(lightVAO);

		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(localCubeVertices), localCubeVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(locationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
		glEnableVertexAttribArray(locationValue++);//链接光源顶点
	}

	void setMagicCubeMatrix() {
		view = camera->getViewMatrix();
		projection = perspective(radians(camera->getZoom()), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f,
		                         100.0f);
		cubeShader->setMat4("transform", transformMatrix);
		cubeShader->setMat4("view", view);
		cubeShader->setMat4("projection", projection);
		cubeShader->setVec3("lightColor", lightColor);
		cubeShader->setVec3("lightPos", lightPosition);
		cubeShader->setVec3("viewPos", camera->getPosition());
	}

	void gameLoop(double elapsed) {
		lightPosition = camera->getPosition();
		projection = perspective(radians(camera->getZoom()), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f,
		                         100.0f);
		view = camera->getViewMatrix();

		glClearColor(WINDOW_COLOR.getR(), WINDOW_COLOR.getG(), WINDOW_COLOR.getB(), WINDOW_COLOR.getA());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Logic::isInShuffling())
			for (int i = 0; i < Logic::getNowStep() + 1; i++)
				renderImage(vec3(-1.8 + (3.6 / Logic::getSteps()) * i, -2, 2.5), vec3(0.05f, 0.1f, 1.0f), 1.0f, view, projection,
				            (char *) "images/ProcessBar.png");
		if (Logic::isInSolving())
			for (int i = Logic::getStates() - Logic::getNowState() + 2; i > 0; i--)
				renderImage(vec3(-1.8 + (3.6 / Logic::getStates()) * i, -2, 2.5), vec3(0.025f, 0.1f, 1.0f), 1.0f, view, projection,
				            (char *) "images/ProcessBar.png");

		//进度条

		cubeShader->use();
		setMagicCubeMatrix();
		glBindVertexArray(magicCubeVAO);
		mat4 model = mat4(1.0f);
		switch (cubeState) {
			case STOP: {
				for (int i = 0; i < NUM_CUBES; i++) {
					mat4 templeCurrentModel = currentModel;
					templeCurrentModel *= allCubesState[i];
					model = translate(templeCurrentModel, cubePositions[i]);
					cubeShader->setMat4("model", model);
					setMagicCubeMatrix();
					glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
				}
				if (rotateFlag == ROTATE_X_1 || rotateFlag == ROTATE_X_2 || rotateFlag == ROTATE_X_3) {
					cubeState = ROTATE_X;
					angle = 0.0;
					rotationVector = STANDARD_X_AXIS;
				} else if (rotateFlag == ROTATE_Y_1 || rotateFlag == ROTATE_Y_2 || rotateFlag == ROTATE_Y_3) {
					cubeState = ROTATE_Y;
					angle = 0.0;
					rotationVector = STANDARD_Y_AXIS;
				} else if (rotateFlag == ROTATE_Z_1 || rotateFlag == ROTATE_Z_2 || rotateFlag == ROTATE_Z_3) {
					cubeState = ROTATE_Z;
					angle = 0.0;
					rotationVector = STANDARD_Z_AXIS;
				}
				break;
			}
			case ROTATE_X: {
				angle += rotateVelocity * elapsed * targetAngle;
				for (int i = 0; i < NUM_CUBES; i++) {
					mat3 allMatsM3 = allCubesState[i];
					vec3 newCube = allMatsM3 * cubePositions[i];
					float &x = newCube.x;
					if (rotateFlag == ROTATE_X_1) {
						if (X_1) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_X_2) {
						if (X_2) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_X_3) {
						if (X_3) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					}
					cubeShader->setMat4("model", model);
					glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);

				}
				if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle))
					cubeState = UPDATE;
				else
					ignoreKeyboardInput = true;
				break;
			}
			case ROTATE_Y: {
				angle += rotateVelocity * elapsed * targetAngle;
				for (int i = 0; i < NUM_CUBES; i++) {
					mat3 allMatsM3 = allCubesState[i];
					vec3 newCube = allMatsM3 * cubePositions[i];
					float &y = newCube.y;
					if (rotateFlag == ROTATE_Y_1) {
						if (Y_1) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_Y_2) {
						if (Y_2) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_Y_3) {
						if (Y_3) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					}
					cubeShader->setMat4("model", model);
					glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
				}
				if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle))
					cubeState = UPDATE;
				 else
					ignoreKeyboardInput = true;
				break;
			}
			case ROTATE_Z: {
				angle += rotateVelocity * elapsed * targetAngle;
				for (int i = 0; i < NUM_CUBES; i++) {
					mat3 allMatsM3 = allCubesState[i];
					vec3 newCube = allMatsM3 * cubePositions[i];
					float &z = newCube.z;
					if (rotateFlag == ROTATE_Z_1) {
						if (Z_1) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_Z_2) {
						if (Z_2) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					} else if (rotateFlag == ROTATE_Z_3) {
						if (Z_3) {
							mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						} else {
							mat4 templeCurrentModel = currentModel;
							templeCurrentModel *= allCubesState[i];
							model = translate(templeCurrentModel, cubePositions[i]);
						}
					}
					cubeShader->setMat4("model", model);
					glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
				}
				if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle))
					cubeState = UPDATE;
				else
					ignoreKeyboardInput = true;
				break;
			}
			case UPDATE: {
				unique_lock<mutex> lock(cubeMutex);
				ignoreKeyboardInput = false;
				for (int i = 0; i < NUM_CUBES; i++) {
					mat3 allMatsM3 = allCubesState[i];
					vec3 newCube = allMatsM3 * cubePositions[i];
					float &x = newCube.x;
					float &y = newCube.y;
					float &z = newCube.z;
					if (rotateFlag == ROTATE_X_1) {
						if (X_1) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_X_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_X_2) {
						if (X_2) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_X_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_X_3) {
						if (X_3) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_X_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Y_1) {
						if (Y_1) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Y_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Y_2) {
						if (Y_2) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Y_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Y_3) {
						if (Y_3) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Y_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Z_1) {
						if (Z_1) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Z_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Z_2) {
						if (Z_2) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Z_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					} else if (rotateFlag == ROTATE_Z_3) {
						if (Z_3) {
							mat4 thisTime = rotate(identityMatrix, radians(targetAngle), STANDARD_Z_AXIS);
							allCubesState[i] = thisTime * allCubesState[i];
						}
					}
				}
				lock.unlock();
				for (int i = 0; i < NUM_CUBES; i++) {
					mat4 templeCurrentModel = currentModel;
					templeCurrentModel *= allCubesState[i];
					model = translate(templeCurrentModel, cubePositions[i]);
					cubeShader->setMat4("model", model);
					glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
				}
				cubeState = STOP;
				targetAngle = 0;
				rotateFlag = NO_ROTATE;
				if (Logic::isSolved() && !Logic::isInShuffling()) 
					cout << "Solved it!" << endl;
				break;
			}
		}
		glfwSwapBuffers(mainWindow->getWindow());
		glfwPollEvents();
	}

	void clear() {
		glDeleteVertexArrays(1, &magicCubeVAO);
		glDeleteBuffers(1, &magicCubeVBO);
		glDeleteBuffers(1, &ColorVBO);
		glDeleteVertexArrays(1, &lightVAO);
		glDeleteBuffers(1, &lightVBO);
		glDeleteVertexArrays(1, &imageVAO);
		glDeleteBuffers(1, &imageVBO);
		glfwTerminate();
	}

	void mouseCallback(GLFWwindow *window, double xCoordinate, double yCoordinate) {
		if (firstMouse) {
			lastX = xCoordinate;
			lastY = yCoordinate;
			firstMouse = false;
		}
		float xOffset = xCoordinate - lastX;
		float yOffset = lastY - yCoordinate;
		lastX = xCoordinate;
		lastY = yCoordinate;
		if (!(pause || help || !startGameLoop))
			camera->processMouseMovement(xOffset, yOffset);
		else
			camera->processMouseMovement(0, 0);
	}

	void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
		camera->processMouseScroll(yOffset);
	}

	GLWindow *getGLWindow() {
		return mainWindow;
	}

	void setFirstMouse(bool flag) {
		firstMouse = flag;
	}

	void rotate_X_1(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_X_1;
		targetAngle = degrees;
	}

	void rotate_X_2(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_X_2;
		targetAngle = degrees;
	}

	void rotate_X_3(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_X_3;
		targetAngle = degrees;
	}

	void rotate_Y_1(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Y_1;
		targetAngle = degrees;
	}

	void rotate_Y_2(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Y_2;
		targetAngle = degrees;
	}

	void rotate_Y_3(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Y_3;
		targetAngle = degrees;
	}

	void rotate_Z_1(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Z_1;
		targetAngle = degrees;
	}

	void rotate_Z_2(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Z_2;
		targetAngle = degrees;
	}

	void rotate_Z_3(float degrees) {
		if (degrees != 0)
			ignoreKeyboardInput = true;
		lock_guard<mutex> l(cubeMutex);
		rotateFlag = ROTATE_Z_3;
		targetAngle = degrees;
	}
}