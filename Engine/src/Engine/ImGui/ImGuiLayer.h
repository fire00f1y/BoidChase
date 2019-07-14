#pragma once

#include "Engine/Layer.h"

namespace Engine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& e);

	private:

	};

}