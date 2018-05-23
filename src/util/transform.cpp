//
// Created by lxs on 17-3-27.
//

#include "util/transform.h"

namespace pbre {
  Transform Transform::operator*(const Transform &t2) {
    Matrix4_4 new_matrix = this->matrix * (t2.matrix), new_inver = t2.inverse * (this->inverse);
    return Transform(new_matrix, new_inver);
  }

  Point3D Transform::operator()(const Point3D &p) {
    float p_array[4] = {p.x, p.y, p.z, 1.f}, p_trans_array[4];
    this->matrix.trans(p_array, p_trans_array);
    if (std::fabs(p_trans_array[3] - 1.f) < 1e-3)
      return Point3D(p_trans_array[0], p_trans_array[1], p_trans_array[2]);
    else
      return Point3D(p_trans_array[0], p_trans_array[1], p_trans_array[2]) / p_trans_array[3];
  }

  Vector3D Transform::operator()(const Vector3D &v) {
    float v_array[4] = {v.x, v.y, v.z, 0.f}, v_trans_array[4];
    this->matrix.trans(v_array, v_trans_array);
    return Vector3D(v_trans_array[0], v_trans_array[1], v_trans_array[2]);
  }

  Normal Transform::operator()(const Normal &n) {
    return Normal(inverse.m[0][0] * n.x + inverse.m[1][0] * n.y + inverse.m[2][0] * n.y,
                  inverse.m[0][1] * n.x + inverse.m[1][1] * n.y + inverse.m[2][1] * n.y,
                  inverse.m[0][2] * n.x + inverse.m[1][2] * n.y + inverse.m[2][2] * n.y);
  }

  Ray Transform::operator()(const Ray &ray) {
    return Ray((*this)(ray.o), (*this)(ray.d));
  }

  Matrix4_4 Matrix4_4::Inverse() {
    Matrix4_4 inver = Matrix4_4();
    float norm_1 = 1 / this->Norm();
    inver.m[0][0] = norm_1 * (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[2][1] * m[3][2] * m[1][3]
                              - m[3][1] * m[2][2] * m[1][3] - m[2][3] * m[3][2] * m[1][1] -
                              m[3][3] * m[1][2] * m[2][1]);
    inver.m[1][0] = norm_1 * (m[3][0] * m[2][2] * m[1][3] + m[2][3] * m[3][2] * m[1][0] + m[2][0] * m[1][2] * m[3][3]
                              - m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] -
                              m[2][0] * m[3][2] * m[1][3]);
    inver.m[2][0] = norm_1 * (m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[2][0] * m[3][1] * m[1][3]
                              - m[3][0] * m[2][1] * m[1][3] - m[3][1] * m[2][3] * m[1][0] -
                              m[3][3] * m[2][0] * m[1][1]);
    inver.m[3][0] = norm_1 * (m[3][0] * m[2][1] * m[1][2] + m[3][1] * m[2][2] * m[1][0] + m[1][1] * m[2][0] * m[3][2]
                              - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] -
                              m[2][0] * m[3][1] * m[1][2]);

    inver.m[0][1] = -norm_1 * (m[0][1] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][1] + m[2][1] * m[3][2] * m[0][3]
                               - m[3][1] * m[2][2] * m[0][3] - m[2][3] * m[3][2] * m[0][1] -
                               m[3][3] * m[0][2] * m[2][1]);
    inver.m[1][1] = -norm_1 * (m[3][0] * m[2][2] * m[0][3] + m[2][3] * m[3][2] * m[0][0] + m[2][0] * m[0][2] * m[3][3]
                               - m[0][0] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][0] -
                               m[2][0] * m[3][2] * m[0][3]);
    inver.m[2][1] = -norm_1 * (m[0][0] * m[2][1] * m[3][3] + m[0][1] * m[2][3] * m[3][0] + m[2][0] * m[3][1] * m[0][3]
                               - m[3][0] * m[2][1] * m[0][3] - m[3][1] * m[2][3] * m[0][0] -
                               m[3][3] * m[2][0] * m[0][1]);
    inver.m[3][1] = -norm_1 * (m[3][0] * m[2][1] * m[0][2] + m[3][1] * m[2][2] * m[0][0] + m[0][1] * m[2][0] * m[3][2]
                               - m[0][0] * m[2][1] * m[3][2] - m[0][1] * m[2][2] * m[3][0] -
                               m[2][0] * m[3][1] * m[0][2]);

    inver.m[0][2] = norm_1 * (m[0][1] * m[1][2] * m[3][3] + m[0][2] * m[1][3] * m[3][1] + m[1][1] * m[3][2] * m[0][3]
                              - m[3][1] * m[1][2] * m[0][3] - m[1][3] * m[3][2] * m[0][1] -
                              m[3][3] * m[0][2] * m[1][1]);
    inver.m[1][2] = norm_1 * (m[3][0] * m[1][2] * m[0][3] + m[1][3] * m[3][2] * m[0][0] + m[1][0] * m[0][2] * m[3][3]
                              - m[0][0] * m[1][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0] -
                              m[1][0] * m[3][2] * m[0][3]);
    inver.m[2][2] = norm_1 * (m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] + m[1][0] * m[3][1] * m[0][3]
                              - m[3][0] * m[1][1] * m[0][3] - m[3][1] * m[1][3] * m[0][0] -
                              m[3][3] * m[1][0] * m[0][1]);
    inver.m[3][2] = norm_1 * (m[3][0] * m[1][1] * m[0][2] + m[3][1] * m[1][2] * m[0][0] + m[0][1] * m[1][0] * m[3][2]
                              - m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] -
                              m[1][0] * m[3][1] * m[0][2]);

    inver.m[0][3] = -norm_1 * (m[0][1] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][1] + m[1][1] * m[2][2] * m[0][3]
                               - m[2][1] * m[1][2] * m[0][3] - m[1][3] * m[2][2] * m[0][1] -
                               m[2][3] * m[0][2] * m[1][1]);
    inver.m[1][3] = -norm_1 * (m[2][0] * m[1][2] * m[0][3] + m[1][3] * m[2][2] * m[0][0] + m[1][0] * m[0][2] * m[2][3]
                               - m[0][0] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][0] -
                               m[1][0] * m[2][2] * m[0][3]);
    inver.m[2][3] = -norm_1 * (m[0][0] * m[1][1] * m[2][3] + m[0][1] * m[1][3] * m[2][0] + m[1][0] * m[2][1] * m[0][3]
                               - m[2][0] * m[1][1] * m[0][3] - m[2][1] * m[1][3] * m[0][0] -
                               m[2][3] * m[1][0] * m[0][1]);
    inver.m[3][3] = -norm_1 * (m[2][0] * m[1][1] * m[0][2] + m[2][1] * m[1][2] * m[0][0] + m[0][1] * m[1][0] * m[2][2]
                               - m[0][0] * m[1][1] * m[2][2] - m[0][1] * m[1][2] * m[2][0] -
                               m[1][0] * m[2][1] * m[0][2]);
    return inver;
  }

  float Matrix4_4::Norm() {
    return (m[0][0] * (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[2][1] * m[3][2] * m[1][3]
                       - m[3][1] * m[2][2] * m[1][3] - m[2][3] * m[3][2] * m[1][1] - m[3][3] * m[1][2] * m[2][1])
            + m[0][1] * (m[3][0] * m[2][2] * m[1][3] + m[2][3] * m[3][2] * m[1][0] + m[2][0] * m[1][2] * m[3][3]
                         - m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] - m[2][0] * m[3][2] * m[1][3])
            + m[0][2] * (m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[2][0] * m[3][1] * m[1][3]
                         - m[3][0] * m[2][1] * m[1][3] - m[3][1] * m[2][3] * m[1][0] - m[3][3] * m[2][0] * m[1][1])
            + m[0][3] * (m[3][0] * m[2][1] * m[1][2] + m[3][1] * m[2][2] * m[1][0] + m[1][1] * m[2][0] * m[3][2]
                         - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[2][0] * m[3][1] * m[1][2]));
  }

  Transform Translate(const Vector3D &v) {
    Matrix4_4 m(1, 0, 0, v.x,
                0, 1, 0, v.y,
                0, 0, 1, v.z,
                0, 0, 0, 1);
    Matrix4_4 m_inver(1, 0, 0, -v.x,
                      0, 1, 0, -v.y,
                      0, 0, 1, -v.z,
                      0, 0, 0, 1);
    return Transform(m, m_inver);
  }

  Transform Scale(float x_scale, float y_scale, float z_scale) {
    Matrix4_4 m(x_scale, 0, 0, 0,
                0, y_scale, 0, 0,
                0, 0, z_scale, 0,
                0, 0, 0, 1);
    Matrix4_4 m_inver(1.f / x_scale, 0, 0, 0,
                      0, 1.f / y_scale, 0, 0,
                      0, 0, 1.f / z_scale, 0,
                      0, 0, 0, 1);
    return Transform(m, m_inver);
  }

// 旋转的角度默认为弧度制
  Transform RotateX(float radians) {
    float sin_x = std::sin(radians);
    float cos_x = std::cos(radians);
    Matrix4_4 m(1, 0, 0, 0,
                0, cos_x, -sin_x, 0,
                0, sin_x, cos_x, 0,
                0, 0, 0, 1);
    Matrix4_4 m_inver(1, 0, 0, 0,
                      0, cos_x, sin_x, 0,
                      0, -sin_x, cos_x, 0,
                      0, 0, 0, 1);
    return Transform(m, m_inver);
  }

  Transform RotateY(float radians) {
    float sin_y = std::sin(radians);
    float cos_y = std::cos(radians);
    Matrix4_4 m(cos_y, 0, sin_y, 0,
                0, 1, 0, 0,
                -sin_y, 0, cos_y, 0,
                0, 0, 0, 1);
    Matrix4_4 m_inver(cos_y, 0, -sin_y, 0,
                      0, 1, 0, 0,
                      sin_y, 0, cos_y, 0,
                      0, 0, 0, 1);
    return Transform(m, m_inver);
  }

  Transform RotateZ(float radians) {
    float sin_z = std::sin(radians);
    float cos_z = std::cos(radians);
    Matrix4_4 m(cos_z, -sin_z, 0, 0,
                sin_z, cos_z, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
    Matrix4_4 m_inver(cos_z, sin_z, 0, 0,
                      -sin_z, cos_z, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
    return Transform(m, m_inver);
  }

  Transform Rotate(const Vector3D &v, float radians) {
    float x = v.x, y = v.y, z = v.z;
    float sin_r = std::sin(radians);
    float cos_r = std::cos(radians);
    float m[4][4], m_inver[4][4];

    m[0][0] = cos_r + x * x * (1 - cos_r);
    m[0][1] = x * y * (1 - cos_r) - z * sin_r;
    m[0][2] = x * z * (1 - cos_r) + y * sin_r;
    m[0][3] = 0;

    m[1][0] = y * x * (1 - cos_r) + z * sin_r;
    m[1][1] = cos_r + y * y * (1 - cos_r);
    m[1][2] = y * z * (1 - cos_r) - x * sin_r;
    m[1][3] = 0;

    m[2][0] = z * x * (1 - cos_r) - y * sin_r;
    m[2][1] = z * y * (1 - cos_r) + x * sin_r;
    m[2][2] = cos_r + z * z * (1 - cos_r);
    m[2][3] = 0;

    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;

    m_inver[0][0] = m[0][0];
    m_inver[0][1] = m[1][0];
    m_inver[0][2] = m[2][0];
    m_inver[0][3] = 0;

    m_inver[1][0] = m[0][1];
    m_inver[1][1] = m[1][1];
    m_inver[1][2] = m[2][1];
    m_inver[1][3] = 0;

    m_inver[2][0] = m[0][2];
    m_inver[2][1] = m[1][2];
    m_inver[2][2] = m[2][2];
    m_inver[2][3] = 0;

    m_inver[3][0] = 0;
    m_inver[3][1] = 0;
    m_inver[3][2] = 0;
    m_inver[3][3] = 1;

    return Transform(Matrix4_4(m), Matrix4_4(m_inver));
  }

  Transform LookAt(const Point3D &pos, const Point3D &look, const Vector3D &up) {
    Vector3D dir = Normalize(look - pos), right = Cross(dir, Normalize(up)),
        newup = Cross(right, dir);
    Matrix4_4 cam2world(right.x, newup.x, dir.x, pos.x,
                        right.y, newup.y, dir.y, pos.y,
                        right.z, newup.z, dir.z, pos.z,
                        0, 0, 0, 1);
    return Transform(cam2world.Inverse(), cam2world);
  }
}