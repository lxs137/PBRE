#include "geometry.h"

inline Vector3D Vector3D::operator+ (const Vector3D &v){
    return Vector3D(x + v.x, y + v.y, z + v.z);
}
inline Vector3D Vector3D::operator- (const Vector3D &v);
inline Vector3D Vector3D::operator* (const Vector3D &v);
inline Vector3D &Vector3D::operator+= (const Vector3D &v);
inline Vector3D &Vector3D::operator-= (const Vector3D &v);
