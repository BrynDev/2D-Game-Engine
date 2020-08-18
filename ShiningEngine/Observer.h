#pragma once
namespace Shining
{
	class GameObject;
	class Observer
	{
	public:
		Observer();
		virtual ~Observer() = default;

		virtual void Notify(GameObject* const pSubject, const int eventID, void* const pData) noexcept = 0;
		bool DecreaseSubjectCount() noexcept; //returns true if subject count is zero
		void IncreaseSubjectCount() noexcept;
	protected:
		int m_SubjectCount;
		
	};
}


