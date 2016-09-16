#pragma once

#include <glm/fwd.hpp>
#include <memory>
#include <ServiceManager.h>

class DisplayObject;
class TextObject;

namespace Aeonphyxius {
	class Updater;
	class Engine : public Core::Service {
	public:
		enum Texture {
			TEXTURE_BACKGROUND,
			TEXTURE_BLUE,
			TEXTURE_GREEN,
			TEXTURE_PURPLE,
			TEXTURE_RED,
			TEXTURE_YELLOW,
			TEXTURE_MUSIC_ON,
			TEXTURE_MUSIC_OFF,
			TEXTURE_SFX_ON,
			TEXTURE_SFX_OFF,
			TEXTURE_EXIT,
			TEXTURE_SCORE_PANEL,
			TEXTURE_SELECTED_GEM,
			NONE,
			TEXTURE_MAX
		};

		Engine();
		~Engine();

		float GetLastFrameSeconds() const;
		float GetMouseX() const;
		float GetMouseY() const;
		bool GetMouseButtonDown() const;
		
		void Start(Updater& updater);
		void Quit();

		int GetTextureHeight(Texture texture) const;
		int GetTextureWidth(Texture texture) const;
		void Render(Texture texture, const glm::mat4& transform);
		void Render(Texture texture, float x, float y, float rotation = 0.0f);
		void Render(DisplayObject *par_object);

		float CalculateStringWidth(const char* text) const;
		
		void Write(const char* text, const glm::mat4& transform);
		void Write(const char* text, float x, float y, glm::vec3 scale, float rotation = 0.0f);		
		void Write(const TextObject *par_textobj);

		int GetWidth() const;
		int GetHeight() const;

	private:
		struct EngineImplementation;
		std::unique_ptr<EngineImplementation> mPimpl;
	};
}