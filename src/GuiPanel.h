#pragma once


class GuiPanel
{
public:
	virtual ~GuiPanel() = 0;
	virtual void on_gui() = 0;
};
