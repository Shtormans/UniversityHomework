#pragma once

#include "Graphic.h"
#include "MonoBehaviour.h"

class Retracter;

class SelectableObject : public MonoBehaviour
{
private:
	const float selectedThickness = 2;
	const float deselectedThickness = 0;

	Graphic* graphic_;
	Retracter* retracter_;
	bool selected;

	void awake() override;

public:
	bool can_select();
	void select();
	void deselect();

	void highlight() const;
	void unhighlight() const;

	bool is_selected() const;
};

