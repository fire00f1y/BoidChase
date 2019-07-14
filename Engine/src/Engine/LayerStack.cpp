#include "precompiled.h"

#include "LayerStack.h"

namespace Engine {

	// TODO: Decouple the lifespan of a layer from the application life

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) 
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* layer) 
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		if (removeLayer(layer))
		{
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		removeLayer(layer);
	}

	bool LayerStack::removeLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			return true;
		}
		return false;
	}

}