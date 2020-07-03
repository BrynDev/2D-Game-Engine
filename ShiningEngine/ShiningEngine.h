#pragma once
struct SDL_Window;
#include <vector>
namespace Shining
{
	class ShiningEngine
	{
	public:
		ShiningEngine() = default;
		void Initialize();
		void LoadDemoScene() const;
		void Cleanup();
		void Run();
		void SetDataPath(const std::string& pathToDataFolder) noexcept;

		static const int GetMsPerFrame()
		{
			return MsPerFrame;
		}

		ShiningEngine(const ShiningEngine& other) = delete;
		ShiningEngine& operator=(const ShiningEngine& rhs) = delete;
		ShiningEngine(ShiningEngine&& other) = delete;
		ShiningEngine& operator=(ShiningEngine&& rhs) = delete;
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}