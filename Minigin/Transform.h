#pragma once
namespace dae
{
	class Transform final
	{
	public:
		TRSMatrix GetTRSMatrix() const { return m_TRS; }
		void CalculateTRS();

		const Vector GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
		void SetPosition(const Vector& p);

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float angle, bool isDegree = true);

		const Vector GetScale() const { return m_Scale; }
		void SetScale(float x, float y);
		void SetScale(const Vector& s);

	private:
		TRSMatrix m_TRS{};
		Vector m_Position{};
		float m_Rotation{};
		Vector m_Scale{ 1,1 };
	};
}
