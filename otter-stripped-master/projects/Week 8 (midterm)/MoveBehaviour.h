#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class MoveBehaviour : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<MoveBehaviour> Sptr;

	MoveBehaviour();
	virtual ~MoveBehaviour();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(MoveBehaviour);
	virtual nlohmann::json ToJson() const override;
	static MoveBehaviour::Sptr FromJson(const nlohmann::json& blob);

protected:
	//float _impulse;
	float _force;

	bool _isPressed = false;
	Gameplay::Physics::RigidBody::Sptr _body;
};