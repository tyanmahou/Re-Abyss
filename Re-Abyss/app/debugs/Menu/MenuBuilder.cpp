#include <abyss/debugs/Menu/MenuBuilder.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Path.hpp>
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/scenes/Sequence/Game/GameSequence.hpp>
#include <abyss/scenes/Sequence/SceneDebug/SceneDebugSequence.hpp>
#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>

#include <abyss/debugs/System/System.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/MenuUtil.hpp>
#include <abyss/utils/DebugMenu/Folder.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <Siv3D.hpp>

namespace
{
	using abyss::DebugMenu::Node;
	using namespace abyss;
	using namespace abyss::Debug;

    template<class SeqType, class... Args>
    Node BuildSeqChangeButton(const s3d::String& label, Args&&... args)
    {
        return Node::Create<DebugMenu::Button>(label, label, [args...] {
            if (auto* pSequence = Debug::System::Context().pSequence) {
                if constexpr (std::is_constructible_v<SeqType, SequenceManager*, Args...>) {
                    pSequence->changeSequence<SeqType>(pSequence, args...);
                } else {
                    pSequence->changeSequence<SeqType>(args...);
                }
                // メニューを閉じる
                MenuUtil::RequestClose();
            }
        });
    }
	Node BuildSceneChangeButton(SceneKind key, const s3d::String& label, std::function<void(SequecneData*)> callback = nullptr)
	{
		return Node::Create<DebugMenu::Button>(label, [key, callback] {
			if (auto* pSequence = Debug::System::Context().pSequence) {
				if (callback) {
					callback(pSequence->data());
				}
				pSequence->changeSequence<SceneDebugSequence>(pSequence, key);

				// メニューを閉じる
				MenuUtil::RequestClose();
			}
		});
	}
	Node BuildSceneChangeButton(SceneKind key, std::function<void(SequecneData*)> callback = nullptr)
	{
		return ::BuildSceneChangeButton(key, Enum::ToStr(key), callback);
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
            if (s3d::FileSystem::FileName(path).starts_with(U".")) {
                continue;
            }
			abyss::StageSeqContext context{
				.mapPath = s3d::FileSystem::RelativePath(path)
			};
			auto name = s3d::FileSystem::RelativePath(path, basePath);
			folder.add(::BuildSeqChangeButton<StageSequence>(name, context));
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

		folder.add(::BuildSeqChangeButton<GameSequence>(U"Splash", SceneKind::Splash));
		folder.add(::BuildSeqChangeButton<GameSequence>(U"Title", SceneKind::Title));
		folder.add(::BuildSeqChangeButton<GameSequence>(U"SaveSelect", SceneKind::SaveSelect));
		// マップロード
		{
			auto mainFolder = Node::Create<DebugMenu::Folder>(U"Stage");
			::BuildMainSceneChangeButtons(mainFolder, Path::MapPath);
			//child.createSeperator();
			::BuildMainSceneChangeButtons(mainFolder, Path::TestMapPath);

			folder.add(mainFolder);
		}
		return folder;
	}
	void MenuBuilder::ExecClearLog()
	{
		Log::Clear();
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
