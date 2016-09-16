#include "Engine.h"

#include <stdexcept>
#include <algorithm>
#include <vector>

#define GLM_FORCE_RADIANS 
#include <glm/gtc/matrix_transform.hpp>
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <sdl/Sdl.h>

#include "Font.h"
#include "GlContext.h"
#include "Sdl.h"
#include "SdlWindow.h"
#include "SdlSurface.h"
#include "Updater.h"
#include "DisplayObject.h"
#include "TextObject.h"

namespace Aeonphyxius 
{
	static const int WindowWidth = 755;
	static const int WindowHeight = 600;
	static const float MaxFrameTicks = 300.0f;
	static const float TextScale = 0.5f;

	struct Engine::EngineImplementation 
	{
		Sdl mSdl;
		SdlWindow mSdlWindow;
		GlContext mGlContext;
		std::unique_ptr<SdlSurface> mSdlSurfaceContainer[Engine::TEXTURE_MAX];
		std::unique_ptr<SdlSurface> mFontSdlSurface;
		float mElapsedTicks;
		float mLastFrameSeconds;
		Updater* mUpdater;
		bool mQuit;

		float mMouseX;
		float mMouseY;
		bool mMouseButtonDown;
		
		EngineImplementation()
			: mSdl(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE)
			, mSdlWindow(WindowWidth, WindowHeight)
			, mGlContext(mSdlWindow)
			, mLastFrameSeconds(1.0f / 60.0f)
			, mMouseX(WindowWidth * 0.5f)
			, mMouseY(WindowHeight * 0.5f)
			, mMouseButtonDown(false)
			, mQuit(false)
			, mUpdater(nullptr)
			, mElapsedTicks(static_cast<float>(SDL_GetTicks()))
		{
		}

		void Start();
		void ParseEvents();
	};

	Engine::Engine()
		: mPimpl(new EngineImplementation) {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetSwapInterval(1);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::string assets("./assets");
		std::string background = assets; background += "/BackGround.jpg";
		std::string blue = assets; blue += "/Blue.png";
		std::string green = assets; green += "/Green.png";
		std::string purple = assets; purple += "/Purple.png";
		std::string red = assets; red += "/Red.png";
		std::string yellow = assets; yellow += "/Yellow.png";
		std::string font = assets; font += "/berlin_sans_demi_72_0.png";
		std::string sfx_icon_on = assets; sfx_icon_on += "/sfx_on.png";
		std::string sfx_icon_off = assets; sfx_icon_off += "/sfx_off.png";
		std::string music_icon_on = assets; music_icon_on += "/music_on.png";
		std::string music_icon_off = assets; music_icon_off += "/music_off.png";
		std::string exit_icon = assets; exit_icon += "/exit.png";
		std::string socre_panel = assets; socre_panel += "/panel.png";
		std::string selected_gem = assets; selected_gem += "/selected.png";

		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_BACKGROUND].reset(new SdlSurface(background.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_BLUE].reset(new SdlSurface(blue.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_GREEN].reset(new SdlSurface(green.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_PURPLE].reset(new SdlSurface(purple.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_RED].reset(new SdlSurface(red.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_YELLOW].reset(new SdlSurface(yellow.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_SFX_ON].reset(new SdlSurface(sfx_icon_on.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_SFX_OFF].reset(new SdlSurface(sfx_icon_off.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_MUSIC_ON].reset(new SdlSurface(music_icon_on.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_MUSIC_OFF].reset(new SdlSurface(music_icon_off.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_EXIT].reset(new SdlSurface(exit_icon.c_str()));		
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_SCORE_PANEL].reset(new SdlSurface(socre_panel.c_str()));
		mPimpl->mSdlSurfaceContainer[Engine::TEXTURE_SELECTED_GEM].reset(new SdlSurface(selected_gem.c_str()));
		mPimpl->mFontSdlSurface.reset(new SdlSurface(font.c_str()));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, WindowWidth, WindowHeight, 0.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	Engine::~Engine() {
	}

	float Engine::GetLastFrameSeconds() const {
		return mPimpl->mLastFrameSeconds;
	}

	float Engine::GetMouseX() const {
		return mPimpl->mMouseX;
	}

	float Engine::GetMouseY() const {
		return mPimpl->mMouseY;
	}

	bool Engine::GetMouseButtonDown() const {
		return mPimpl->mMouseButtonDown;
	}
	
	void Engine::Quit() {
		mPimpl->mQuit = true;
	}

	void Engine::Start(Updater& updater) {
		mPimpl->mUpdater = &updater;
		mPimpl->mSdlWindow.Show();
		mPimpl->Start();
	}

	int Engine::GetTextureHeight(Texture texture) const {
		return mPimpl->mSdlSurfaceContainer[texture]->Height();
	}

	int Engine::GetTextureWidth(Texture texture) const {
		return mPimpl->mSdlSurfaceContainer[texture]->Width();
	}

	void Engine::Render(Engine::Texture texture, const glm::mat4& transform) {
		glLoadMatrixf(reinterpret_cast<const float*>(&transform));

		SdlSurface& surface = *mPimpl->mSdlSurfaceContainer[texture];

		surface.Bind();

		glBegin(GL_QUADS);
		glTexCoord2i(0, 1); glVertex2i(0, surface.Height());
		glTexCoord2i(1, 1); glVertex2i(surface.Width(), surface.Height());
		glTexCoord2i(1, 0); glVertex2i(surface.Width(), 0);
		glTexCoord2i(0, 0); glVertex2i(0, 0);
		glEnd();
	}

	void Engine::Render(Texture texture, float x, float y, float rotation) {
		glm::mat4 transformation;
		transformation = glm::translate(transformation, glm::vec3(x, y, 0.0f));
		if (rotation) {
			transformation = glm::rotate(transformation, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		Render(texture, transformation);
	}

	void Engine::Render(DisplayObject *par_display_obj)
	{
		// Only render if this object is visible
		if (par_display_obj->isVisible() && par_display_obj->getTexture()!= NONE){
			glm::mat4 transformation;
			transformation = glm::translate(transformation, par_display_obj->getPosition());

			if (par_display_obj->getRotation() != 0.0) {
				transformation = glm::rotate(transformation, par_display_obj->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
			}

			if (par_display_obj->getScale() != glm::vec3(1, 1, 1)){
				transformation = glm::scale(transformation, par_display_obj->getScale());
			}

			Render(par_display_obj->getTexture(), transformation);
		}
		
	}


	Glyph& FindGlyph(char c) {
		auto found = std::lower_bound(std::begin(Font), std::end(Font), c);
		if (found == std::end(Font) || c < *found) {
			found = std::lower_bound(std::begin(Font), std::end(Font), static_cast<int>('_'));
		}
		return *found;
	}

	float Engine::CalculateStringWidth(const char* text) const {
		int advance = 0;
		for (; *text; ++text) {
			Glyph& g = FindGlyph(*text);
			advance += g.advance;
		}
		return advance*TextScale;
	}

	void Engine::Write(const char* text, const glm::mat4& transform) {
		glLoadMatrixf(reinterpret_cast<const float*>(&transform));
		int advance = 0;
		for (; *text;++text) {
			Glyph& g = FindGlyph(*text);

			float fontTexWidth  = static_cast<float>(mPimpl->mFontSdlSurface->Width());
			float fontTexHeight = static_cast<float>(mPimpl->mFontSdlSurface->Height());

			float uvLeft = static_cast<float>(g.x) / fontTexWidth;
			float uvRight = static_cast<float>(g.x + g.width) / fontTexWidth;
			float uvBottom = static_cast<float>(g.y) / fontTexHeight;
			float uvTop = static_cast<float>(g.y + g.height) / fontTexHeight;

			float worldLeft = static_cast<float>(g.xoffset + advance);
			float worldRight = static_cast<float>(g.xoffset + g.width + advance);
			float worldBottom = static_cast<float>(g.yoffset);
			float worldTop = static_cast<float>(g.yoffset + g.height);

			mPimpl->mFontSdlSurface->Bind();

			glBegin(GL_QUADS);
			glTexCoord2f(uvLeft / 2.0f, uvTop / 2.0f); glVertex2f(worldLeft * TextScale, worldTop * TextScale);
			glTexCoord2f(uvRight / 2.0f, uvTop / 2.0f); glVertex2f(worldRight * TextScale, worldTop * TextScale);
			glTexCoord2f(uvRight / 2.0f, uvBottom / 2.0f); glVertex2f(worldRight * TextScale, worldBottom * TextScale);
			glTexCoord2f(uvLeft / 2.0f, uvBottom / 2.0f); glVertex2f(worldLeft * TextScale, worldBottom * TextScale);
			glEnd();
			advance += g.advance;
		}
	}

	void Engine::Write(const char* text, float x, float y, glm::vec3 scale, float rotation ) {
		glm::mat4 transformation;
		transformation = glm::translate(transformation, glm::vec3(x, y, 0.0f));
		if (rotation) {
			transformation = glm::rotate(transformation, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			transformation = glm::translate(transformation, glm::vec3(-CalculateStringWidth(text)/2.0f, -20.0f, 0.0f));			
		}
		transformation = glm::scale(transformation, scale);
		Write(text, transformation);
	}
	void Engine::Write(const TextObject *par_textobj){
		if (par_textobj->isVisible()){
			Write(par_textobj->getText(), par_textobj->getPosition().x, par_textobj->getPosition().y, par_textobj->getScale(), par_textobj->getRotation());
		}
		
	}


	int Engine::GetWidth() const {
		return WindowWidth;
	}

	int Engine::GetHeight() const {
		return WindowHeight;
	}

	void Engine::EngineImplementation::Start() {
		while (!mQuit) {
			SDL_GL_SwapWindow(mSdlWindow);
			glClear(GL_COLOR_BUFFER_BIT);

			//ParseEvents();
			
			float currentTicks = static_cast<float>(SDL_GetTicks());
			float lastFrameTicks = currentTicks - mElapsedTicks;
			mElapsedTicks = currentTicks;

			lastFrameTicks = std::min(lastFrameTicks, MaxFrameTicks);
			mLastFrameSeconds = lastFrameTicks * 0.001f;

			if (mUpdater) {
				mUpdater->Update();
			}
		}
	}

	void Engine::EngineImplementation::ParseEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				mQuit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mMouseButtonDown = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mMouseButtonDown = false;
				break;
			case SDL_MOUSEMOTION:
				mMouseX = static_cast<float>(event.motion.x);
				mMouseY = static_cast<float>(event.motion.y);
				break;
			default:
				break;
			}
		}
	}
}
