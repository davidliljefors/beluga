class Quaternion {
public:
    float x, y, z, w;

    // Constructors
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    
    // Static constructors
    static Quaternion identity();
    static Quaternion from_euler(float pitch, float yaw, float roll);
    static Quaternion from_axis_angle(float x, float y, float z, float angle_radians);

    // Operations
    Quaternion conjugate() const;
    float magnitude() const;
    Quaternion normalize() const;
    void normalize_self();

    // Operators
    Quaternion operator*(const Quaternion& other) const;
    Quaternion& operator*=(const Quaternion& other);
    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    // Utility
    void to_axis_angle(float& x, float& y, float& z, float& angle_radians) const;
    void to_euler(float& pitch, float& yaw, float& roll) const;
}; 