#ifndef VECTOR_H
#define VECTOR_H

// Note: virtual function overloads appear in the virtual table
// in reverse order of appearance.

class Vector2 {
protected:
	inline virtual void AddImpl(const float* p_value);
	inline virtual void AddImpl(float p_value);
	inline virtual void SubImpl(const float* p_value);
	inline virtual void MulImpl(const float* p_value);
	inline virtual void MulImpl(const float& p_value);
	inline virtual void DivImpl(const float& p_value);
	inline virtual float DotImpl(const float* p_a, const float* p_b) const;
	inline virtual void SetData(float* p_data);
	inline virtual void EqualsImpl(const float* p_data);

	float* m_data;

public:
	Vector2(float* p_data) { SetData(p_data); }

	Vector2(const float* p_data) : m_data((float*) p_data) {}

	inline virtual float* GetData();
	inline virtual const float* GetData() const;
	inline virtual void Clear();
	inline virtual float Dot(const float* p_a, const float* p_b) const;
	inline virtual float Dot(const Vector2& p_a, const Vector2& p_b) const;
	inline virtual float Dot(const float* p_a, const Vector2& p_b) const;
	inline virtual float Dot(const Vector2& p_a, const float* p_b) const;
	inline virtual float LenSquared() const;
	inline virtual int Unitize();
	inline virtual void operator+=(float p_value);
	inline virtual void operator+=(const float* p_other);
	inline virtual void operator+=(const Vector2& p_other);
	inline virtual void operator-=(const float* p_other);
	inline virtual void operator-=(const Vector2& p_other);
	inline virtual void operator*=(const float* p_other);
	inline virtual void operator*=(const Vector2& p_other);
	inline virtual void operator*=(const float& p_value);
	inline virtual void operator/=(const float& p_value);
	inline virtual void operator=(const float* p_other);
	inline virtual void operator=(const Vector2& p_other);

	// Vector3::operator=

	// Vector4::operator=

	float& operator[](int idx) { return m_data[idx]; }

	const float& operator[](int idx) const { return m_data[idx]; }
};

class Vector3 : public Vector2 {
protected:
	inline void AddImpl(const float* p_value) override;
	inline void AddImpl(float p_value) override;
	inline void SubImpl(const float* p_value) override;
	inline void MulImpl(const float* p_value) override;
	inline void MulImpl(const float& p_value) override;
	inline void DivImpl(const float& p_value) override;
	inline float DotImpl(const float* p_a, const float* p_b) const override;
	inline void EqualsImpl(const float* p_data) override;
	inline virtual void EqualsCrossImpl(const float* p_a, const float* p_b);

public:
	Vector3(float* p_data) : Vector2(p_data) {}

	// Hack: Some code initializes a Vector3 from a (most likely) const float*
	// source. Example: LegoCameraController::GetWorldUp Vector3 however is a
	// class that can mutate its underlying source, making initialization with a
	// const source fundamentally incompatible.

	Vector3(const float* p_data) : Vector2(p_data) {}

	inline void Clear() override;
	inline float LenSquared() const override;
	inline virtual void EqualsCross(const Vector3& p_a, const Vector3& p_b);
	inline virtual void EqualsCross(const Vector3& p_a, const float* p_b);
	inline virtual void EqualsCross(const float* p_a, const Vector3& p_b);
	inline virtual void Fill(const float& p_value);

	friend class Mx3DPointFloat;
};

class Vector4 : public Vector3 {
protected:
	inline void AddImpl(const float* p_value) override;
	inline void AddImpl(float p_value) override;
	inline void SubImpl(const float* p_value) override;
	inline void MulImpl(const float* p_value) override;
	inline void MulImpl(const float& p_value) override;
	inline void DivImpl(const float& p_value) override;
	inline float DotImpl(const float* p_a, const float* p_b) const override;
	inline void EqualsImpl(const float* p_data) override;

public:
	Vector4(float* p_data) : Vector3(p_data) {}

	// Some code initializes a Vector4 from a `const float*` source.
	// Example: `LegoCarBuild::VTable0x6c`
	// Vector4 however is a class that can mutate its underlying source, making
	// initialization with a const source fundamentally incompatible.
	// BETA10 appears to have two separate constructors for Vector4 as well,
	// supporting the theory that this decompilation is correct.

	Vector4(const float* p_data) : Vector3(p_data) {}

	inline void Clear() override;
	inline float LenSquared() const override;
	inline void Fill(const float& p_value) override;
	inline virtual void
	SetMatrixProduct(const float* p_vec, const float* p_mat);
	inline virtual void SetMatrixProduct(const Vector4& p_a, const float* p_b);
	inline virtual int NormalizeQuaternion();
	inline virtual int
	EqualsHamiltonProduct(const Vector4& p_a, const Vector4& p_b);

	float& operator[](int idx) { return m_data[idx]; }

	const float& operator[](int idx) const { return m_data[idx]; }

	friend class Mx4DPointFloat;
};

#endif // VECTOR_H
