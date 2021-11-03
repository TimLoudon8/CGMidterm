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
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json MoveBehaviour::ToJson() const {
	return {
		{ "impulse", _impulse }
	};
}

MoveBehaviour::MoveBehaviour() :
	IComponent(),
	_impulse(10.0f)
{ }

MoveBehaviour::~MoveBehaviour() = default;

MoveBehaviour::Sptr MoveBehaviour::FromJson(const nlohmann::json & blob) {
	MoveBehaviour::Sptr result = std::make_shared<MoveBehaviour>();
	result->_impulse = blob["impulse"];
	return result;
}

void MoveBehaviour::Update(float deltaTime) {
	bool pressed = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_SPACE);
	if (pressed) {
		if (_isPressed == false) {
			_body->ApplyImpulse(glm::vec3(0.0f, 0.0f, _impulse));
		}
		_isPressed = pressed;
	}
	else {
		_isPressed = false;
	}
}

