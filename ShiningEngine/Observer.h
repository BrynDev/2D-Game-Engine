#pragma once
namespace Shining
{
	class GameObject;
	class Observer
	{
	public:
		Observer(GameObject* pObjectToModify);
		virtual ~Observer() = default;

		virtual void Notify(GameObject* const pSubject, const int eventID, void* const pData) noexcept = 0;
		bool DecreaseSubjectCount() noexcept; //returns true if subject count is zero
		void IncreaseSubjectCount() noexcept;
		void SetTargetObject(GameObject* pObjectToModify) noexcept;
	protected:
		GameObject* m_pObjectToModify;
		int m_SubjectCount;
		
	};
}


