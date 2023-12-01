#pragma once

#include <vector>

#include <Model.h>
#include <WorldTransform.h>

class BaseCharacter {

public:

	virtual void Initialize(const std::vector<Model*>& model);

	virtual void Update();

	virtual void Draw(const ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

protected:

	std::vector<Model*> models_;

	WorldTransform worldTransform_;

};
