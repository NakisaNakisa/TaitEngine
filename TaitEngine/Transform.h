#pragma once
namespace tait
{
	class Transform final
	{
	public:
		void Translate(const Vector& delta);

		const Vector& GetPosition() const { return m_Position; }
		const Vector& GetCenter() const { return m_Center; }
		const Vector& GetSize() const { return m_Size; }
		const Vector& GetHalfSize() const { return m_HalfSize; }
		const Rect& GetRect() const { return m_Rect; }

		void SetPosition(float x, float y);
		void SetPosition(const Vector& p);
		void SetCenterPosition(float x, float y);
		void SetCenterPosition(const Vector& p);
		void SetSize(float w, float h);
		void SetSize(const Vector& s);
		void SetHalfSize(float w, float h);
		void SetHalfSize(const Vector& s);

	private:
		Rect m_Rect{};
		Vector m_Position{};
		Vector m_Center{};
		Vector m_Size{};
		Vector m_HalfSize{};
	};
}
