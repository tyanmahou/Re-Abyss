#pragma once

namespace abyss
{
	///<summary>
	///�V���O���g���e���v���[�g
	///</summary>
	template<class _Tp>
	class Singleton
	{
	public:
		///<summary>
		///<para>�T�v�F�C���X�^���X��Ԃ�</para>
		///<para>�Ԃ�l�F�V���O���g����class�̃|�C���^�^</para>
		///</summary>
		static _Tp* Instance()
		{
			static _Tp instance;
			return &instance;
		}
	protected:
		Singleton() {}
		virtual ~Singleton() {}
	private:
		Singleton(const Singleton& other);
		Singleton& operator=(const Singleton& other);
	};

}