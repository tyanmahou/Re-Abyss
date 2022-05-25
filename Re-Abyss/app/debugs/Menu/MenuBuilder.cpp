#include <abyss/debugs/Menu/MenuBuilder.hpp>
#if ABYSS_DEBUG
#include <abyss/scenes/base/ISceneBase.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

#include <abyss/utils/DebugMenu/Folder.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <Siv3D.hpp>

namespace
{
	using abyss::DebugMenu::Node;
	using namespace abyss;
	using namespace abyss::Debug;

	Node BuildSceneChangeButton(const s3d::String& key, const s3d::String& label, std::function<void(GameData*)> callback = nullptr)
	{
		return Node::Create<DebugMenu::Button>(key, label, [key, callback] {
			auto pScene = Menu::GetBind<AppScene*>(U"Scene");
			if (pScene) {
				if (callback) {
					callback(pScene->get().get());
				}
				pScene->changeScene(key, 1000, CrossFade::No);
			}
			});
	}
	Node BuildSceneChangeButton(const s3d::String& key, std::function<void(GameData*)> callback = nullptr)
	{
		return ::BuildSceneChangeButton(key, key, callback);
	}
	Node BuildMainSceneChangeButtons(Node& folder, const s3d::FilePath& basePath)
	{
		for (auto&& path : s3d::FileSystem::DirectoryContents(basePath, Recursive::No)) {
			if (s3d::FileSystem::IsDirectory(path)) {
				if (s3d::FileSystem::DirectoryContents(path).any([](const s3d::FilePath& p) {
					return s3d::FileSystem::Extension(p) == U"tmx";
					})) {
					auto child = Node::Create<DebugMenu::Folder>(s3d::FileSystem::BaseName(path));
					folder.add(BuildMainSceneChangeButtons(child, path));
				}
				continue;
			}
			if (s3d::FileSystem::Extension(path) != U"tmx") {
				continue;
			}
			MainSceneContext context{
				.mapPath = s3d::FileSystem::RelativePath(path)
			};
			auto name = s3d::FileSystem::RelativePath(path, basePath);
			folder.add(::BuildSceneChangeButton(SceneName::Main, name, [context](GameData* data) {
				data->context = context;
			}));
		}
		return folder;
	}
}
namespace abyss::Debug
{
	Node MenuBuilder::BuildSceneMenu(const s3d::XMLElement& xml)
	{
		auto key = xml.name();
		auto label = xml.attribute(U"label").value_or(key);
		auto folder = Node::Create<DebugMenu::Folder>(key, label);

		folder.add(::BuildSceneChangeButton(SceneName::Splash));
		folder.add(::BuildSceneChangeButton(SceneName::Title));
		folder.add(::BuildSceneChangeButton(SceneName::SaveSelect));
		// マップロード
		{
			auto mainFolder = Node::Create<DebugMenu::Folder>(SceneName::Main);
			::BuildMainSceneChangeButtons(mainFolder, Path::MapPath);
			//child.createSeperator();
			::BuildMainSceneChangeButtons(mainFolder, Path::TestMapPath);

			folder.add(mainFolder);
		}
		return folder;
	}
	void MenuBuilder::ExecClearLog()
	{
		LogUpdater::Clear();
	}
	void MenuBuilder::ExecSoundMute(bool value)
	{
		// マスターボリューム設定
		if (value) {
			GlobalAudio::SetVolume(0.0);
		} else {
			GlobalAudio::SetVolume(1.0);
		}
	}
	void MenuBuilder::ExecFPS(s3d::StringView value)
	{
		FrameRateHz::Set(ParseOpt<double>(value));
	}
}
#endif