#pragma once
#include "IEntity.h"
#include "Vector2.h"
#include <memory>
#include <string>
class IEntityFactory {
public:
	virtual std::unique_ptr<IEntity> create(const std::string& type, const Vector2& position) = 0;
	virtual ~IEntityFactory() = default;
};