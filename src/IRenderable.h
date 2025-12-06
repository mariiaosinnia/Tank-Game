#pragma once
#include "RenderData.h"
class IRenderable {
public:
	virtual RenderData getRenderData() const = 0;
	virtual ~IRenderable() = default;
};