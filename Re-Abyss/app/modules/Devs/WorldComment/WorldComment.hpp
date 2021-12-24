#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/ColorF.hpp>

#include <Siv3D/Array.hpp>
#include <abyss/utils/IdGenerator/IdGen.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Devs
{
	/// <summary>
	/// ワールドコメント
	/// </summary>
	class WorldComment
	{
	public:
		/// <summary>
		/// リクエスター
		/// </summary>
		class Requestor
		{
			friend class WorldComment;
		public:
			struct Handle;
		public:
			void comment(
				const s3d::String& text,
				const s3d::Vec2& pos,
				const s3d::ColorF& color = s3d::ColorF(0.8)
			) const;
		private:
			Requestor(WorldComment* pWorldComment);
		private:
			std::shared_ptr<Handle> m_pHandle;
		};
	private:
		struct Record
		{
			Ref<Requestor::Handle> handle;
			s3d::String text;
			s3d::Vec2 pos;
			s3d::ColorF color;
		};
	public:
		/// <summary>
		/// リクエスターを取得
		/// </summary>
		std::unique_ptr<Requestor> getRequestor();

		/// <summary>
		/// フラッシュ
		/// </summary>
		/// <returns></returns>
		void flush();

		/// <summary>
		/// 描画
		/// </summary>
		void draw();

		s3d::uint64 selectId() const
		{
			return m_selectId;
		}
	private:
		void request(Record&& record);
	private:
		s3d::uint64 m_selectId = 0;
		IdGenU64 m_idCounter;

		s3d::Array<Record> m_records;
	};
}