//
// Created by lxs on 17-3-27.
//

#ifndef UTIL_TRANSFORM_H
#define UTIL_TRANSFORM_H

#include "geometry.h"
#include "ray.h"

class Matrix4_4 {
public:
    // method
    Matrix4_4() {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                m[i][j] = 0.f;
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }
    Matrix4_4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33)
    {
        m[0][0] = m00, m[0][1] = m01, m[0][2] = m02, m[0][3] =m03;
        m[1][0] = m10, m[1][1] = m11, m[1][2] = m12, m[1][3] =m13;
        m[2][0] = m20, m[2][1] = m21, m[2][2] = m22, m[2][3] =m23;
        m[3][0] = m30, m[3][1] = m31, m[3][2] = m32, m[3][3] =m33;
    }
    Matrix4_4(float f[4][4]) {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                m[i][j] = f[i][j];
    }
    Matrix4_4(const Matrix4_4 &matrix) {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                m[i][j] = matrix.m[i][j];
    }
    Matrix4_4 operator+(const Matrix4_4 &matrix) {
        Matrix4_4 new_matrix;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                new_matrix.m[i][j] = m[i][j] + matrix.m[i][j];
        return new_matrix;
    }
    Matrix4_4 operator-(const Matrix4_4 &matrix) {
        Matrix4_4 new_matrix;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                new_matrix.m[i][j] = m[i][j] - matrix.m[i][j];
        return new_matrix;
    }
    Matrix4_4 operator*(const Matrix4_4 &matrix) const {
        Matrix4_4 mul;
        float s;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
            {
                s = 0.f;
                for(int k = 0; k < 4; k++)
                    s += m[i][k] * matrix.m[k][j];
                mul.m[i][j] = s;
            }
        return mul;
    }
    Matrix4_4 operator*(const float f) {
        Matrix4_4 new_matrix;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                new_matrix.m[i][j] = m[i][j]*f;
        return new_matrix;
    }
    Matrix4_4 operator/(const float f) {
        Matrix4_4 new_matrix;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                new_matrix.m[i][j] = m[i][j]/f;
        return new_matrix;
    }
    Matrix4_4 Inverse();
    float Norm();
    void trans(float f[4], float f_result[4]) {
        // f代表一个列向量
        f_result[0] = m[0][0]*f[0] + m[0][1]*f[1] + m[0][2]*f[2] + m[0][3]*f[3];
        f_result[1] = m[1][0]*f[0] + m[1][1]*f[1] + m[1][2]*f[2] + m[1][3]*f[3];
        f_result[2] = m[2][0]*f[0] + m[2][1]*f[1] + m[2][2]*f[2] + m[2][3]*f[3];
        f_result[3] = m[3][0]*f[0] + m[3][1]*f[1] + m[3][2]*f[2] + m[3][3]*f[3];
    }

    // value
    float m[4][4];

};


class Transform {
public:
    // method
    Transform():matrix(), inverse() {}
    Transform(const Transform &trans):matrix(trans.matrix), inverse(trans.inverse) {}
    Transform(const Matrix4_4 &m, const Matrix4_4 &m_inverse):matrix(m), inverse(m_inverse) {}
    Transform Inverse() const {
        return Transform(inverse, matrix);
    }
    Transform operator*(const Transform &t2);
    Point3D operator()(const Point3D &p);
    Vector3D operator()(const Vector3D &v);
    Normal operator()(const Normal &n);
    Ray operator()(const Ray &ray);

private:
    // value
    Matrix4_4 matrix, inverse;  //变换矩阵和逆变换矩阵
};


// Some special transform
Transform Translate(const Vector3D &v);
Transform Scale(float x_scale, float y_scale, float z_scale);
Transform RotateX(float radians);
Transform RotateY(float radians);
Transform RotateZ(float radians);
Transform Rotate(const Vector3D &v, float radians);
Transform LookAt(const Point3D &pos, const Point3D &look, const Vector3D &up);

#endif //UTIL_TRANSFORM_H
