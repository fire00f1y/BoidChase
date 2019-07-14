#pragma once

#include "Core.h"
#include "Layer.h"

namespace Engine {
	typedef std::vector<Layer*> Layers;

	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		Layers::iterator begin() { return m_Layers.begin(); }
		Layers::iterator end() { return m_Layers.end(); }
	private:
		Layers m_Layers;
		Layers::iterator m_LayerInsert;

		bool removeLayer(Layer* layer);
	};

}