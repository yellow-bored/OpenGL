#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

// �趨�����Ǻ��ӽǵķ�Χ
const float fov_max = 45.0f;
const float fov_min = 1.0f;
const float pitch_max = 89.9f;
const float pitch_min = -89.9f;

enum CamMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera{
public:
	glm::vec3 m_CamPos;  // �����λ��
	glm::vec3 m_CamFront;  //
	glm::vec3 m_CamUp;  // ��������������������������x��
	glm::vec3 m_Right;



	float m_yaw;  //0�Ⱦ������ҿ���  ��ƫ��
	float m_pitch;   //������
	float m_fov;   //�ӽ�

	float m_sensitivity;  // ����������
	float m_MoveSpeed;


	Camera(glm::vec3 CamPos = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 CamUp = glm::vec3(0.0f,1.0f,0.0f), float fov = 45.0f, float sensitivity = 0.1f, float MoveSpeed = 2.5f) : m_CamFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_yaw(-90.0f), m_pitch(0.0f) {
		m_CamPos = CamPos;
		m_CamUp = CamUp;
		m_fov = fov;
		m_sensitivity = sensitivity; 
		m_MoveSpeed = MoveSpeed;
		m_Right = glm::normalize(glm::cross(m_CamFront, m_CamUp));
	}
	void MouseMovement(float xoffset, float yoffset) {
		xoffset *= m_sensitivity;
		yoffset *= m_sensitivity;

		m_yaw += xoffset;
		m_pitch += yoffset;
		// ���Ƕ�����
		if (m_pitch > pitch_max) m_pitch = pitch_max;
		if (m_pitch < pitch_min) m_pitch = pitch_min;

		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		m_CamFront = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_CamFront, m_CamUp));
	}
	void MouseScroll(float yoffset) {
		m_fov -= yoffset;
		// �趨�ӽǵķ�Χ
		if (m_fov < fov_min) m_fov = fov_min;
		if (m_fov > fov_max) m_fov = fov_max;
	}
	void Key_MouseMovement(float deltaTime, CamMovement movement) {
		float CamSpeed = m_MoveSpeed * deltaTime;

		if (movement == FORWARD) m_CamPos += CamSpeed * m_CamFront;
		if (movement == BACKWARD) m_CamPos -= CamSpeed * m_CamFront;
		if (movement == LEFT) m_CamPos -= CamSpeed * m_Right;
		if (movement == RIGHT) m_CamPos += CamSpeed * m_Right;
	}

	glm::mat4 CreateView_M() {
		return glm::lookAt(m_CamPos, m_CamPos + m_CamFront, m_CamUp);
	}
};