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
    bool _Up = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_UP);
    bool _Down = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_DOWN);
    bool _Left = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_LEFT);
    bool _Right = glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_RIGHT);

    glm::vec3 current = GetGameObject()->GetPosition();


    if (_Up) {       
            GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(0.0f, -0.1f, 0.0f));   
    }
    if (_Down) {  
            GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(0.0f, 0.1f, 0.0f));   
    }
    if (_Left) {     
            GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(0.1f, 0.0f, 0.0f)); 
    }
    if (_Right) {   
            GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(-0.1f, 0.0f, 0.0f));
    }

    if (GetGameObject()->GetPosition().x >= 9.4) {
        GetGameObject()->SetPostion(glm::vec3(-9.4, current.y, current.z));
    }
    if (GetGameObject()->GetPosition().x <= -9.4) {
        GetGameObject()->SetPostion(glm::vec3(9.4, current.y, current.z));
    }
    if (GetGameObject()->GetPosition().y >= 9.4) {
        GetGameObject()->SetPostion(glm::vec3(current.x, -9.4, current.z));
    }
    if (GetGameObject()->GetPosition().y <= -9.4) {
        GetGameObject()->SetPostion(glm::vec3(current.x, 9.4, current.z));
    }
}

