#include "Gameplay/Components/MoveBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"

void MoveBehaviour::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void MoveBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Force", &_force, 1.0f);
}

nlohmann::json MoveBehaviour::ToJson() const {
	return {
		{ "impulse", _force }
	};
}

MoveBehaviour::MoveBehaviour() :
	IComponent(),
	_force(5.0f)
{ }

MoveBehaviour::~MoveBehaviour() = default;

MoveBehaviour::Sptr MoveBehaviour::FromJson(const nlohmann::json & blob) {
	MoveBehaviour::Sptr result = std::make_shared<MoveBehaviour>();
	result->_force = blob["force"];
	return result;
}

void MoveBehaviour::Update(float deltaTime) {
	bool pressedLeft = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_LEFT);
	bool pressedRight = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_RIGHT);
	bool pressedUp = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_UP);
	bool pressedDown = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_DOWN);

	if (pressedLeft) {
		if (_isPressedLeft == false) {
			_force = -1 * _force; //make negative for left
			_body->ApplyImpulse(glm::vec3(_force, 0.0f, 0.0f));
		}
		_isPressedLeft = pressedLeft;
	}
	else if (pressedRight) {
		if (_isPressedRight == false) {
			
			_body->ApplyImpulse(glm::vec3(_force, 0.0f, 0.0f));
		}
		_isPressedRight = pressedRight;
	}
	else if (pressedUp) {
		if (_isPressedUp == false) {

			_body->ApplyImpulse(glm::vec3(0.0f, _force, 0.0f));
		}
		_isPressedUp = pressedUp;
	}
	else if (pressedDown) {
		if (_isPressedDown == false) {
			_force = -1 * _force;
			_body->ApplyImpulse(glm::vec3(0.0f, _force, 0.0f));
		}
		_isPressedDown = pressedDown;
	}
}

