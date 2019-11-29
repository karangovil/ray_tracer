#ifndef MATRIX4x4_H
#define MATRIX4x4_H

#include <array>
#include <stdexcept>
#include <iostream>
#include <iostream>
#include <algorithm>

#include "tuple.h"
#include "constants.h"
#include "utils/equality.h"

namespace RT
{

struct matrix4x4
{
public:
    matrix4x4()
    {
        num_t zero = static_cast<num_t>(0.0);
        num_t one = static_cast<num_t>(1.0);
        for (auto& el : m_data)
            el = zero;
        m_data[0] = one;
        m_data[5] = one;
        m_data[10] = one;
        m_data[15] = one;
    }

    matrix4x4(std::array<num_t, 16> input)
        : m_data {input} {}

    num_t& operator()(size_t i, size_t j)
    { return m_data[i * 4 + j]; }

    num_t operator()(size_t i, size_t j) const
    { return m_data[i * 4 + j]; }
    
    num_t& at(size_t i, size_t j)
    {
        bound_check(i, j);
        return m_data[i * 4 + j];
    }

    num_t at(size_t i, size_t j) const
    {
        bound_check(i, j);
        return m_data[i * 4 + j];
    }

    std::array<num_t, 16> data() const
    { return m_data; }
    
    std::array<num_t, 16>& data()
    { return m_data; }
private:
    std::array<num_t, 16> m_data;

    void bound_check(size_t i, size_t j)
    {
        if (i > 3 || j > 3)
            throw std::out_of_range("matrix4x4 : index is out of range");
    }
    
    void bound_check(size_t i, size_t j) const
    {
        if (i > 3 || j > 3)
            throw std::out_of_range("matrix4x4 : index is out of range");
    }
};

// equality of 4x4 matrices
inline
bool operator==(matrix4x4 const& m1, matrix4x4 const& m2)
{
    bool res = true;
    for (int i = 0; i < 16; ++i)
    {
        res = res && AlmostEquals(m1.data()[i], m2.data()[i]);
        if (res == false)
            return res;
    }
    return res;
}

// 4x4 matrix multiplication
inline
auto operator*(matrix4x4 const& m1, matrix4x4 const& m2)
{
    matrix4x4 res;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            num_t sum = 0;
            for (int k = 0; k < 4; ++k)
                sum += m1(i, k) * m2(k, j);
            res(i, j) = sum;
        }
    }
    return res;
}

// 4x4 matrix vector multiplication
inline
auto operator*(matrix4x4 const& m, tuple const& t)
{
    tuple res;

    res.x = m(0,0) * t.x + m(0,1) * t.y + m(0,2) * t.z + m(0,3) * t.w;
    res.y = m(1,0) * t.x + m(1,1) * t.y + m(1,2) * t.z + m(1,3) * t.w;
    res.z = m(2,0) * t.x + m(2,1) * t.y + m(2,2) * t.z + m(2,3) * t.w;
    res.w = m(3,0) * t.x + m(3,1) * t.y + m(3,2) * t.z + m(3,3) * t.w;

    return res;
}


// 4x4 matrix scalar multiplication
inline
auto operator*(matrix4x4 const& m, num_t const& s)
{
    matrix4x4 res {m};

    for (auto& el : res.data())
        el = el * s;
    return res;
}

inline
auto operator*(num_t const& s, matrix4x4 const& m)
{ return m * s; }

// Transpose function
inline
auto transpose(matrix4x4 const& m)
{
    matrix4x4 res {m};
    for (int i = 0; i < 4; ++i){
        for (int j = i+1; j < 4; ++j)
            std::swap(res(i,j),  res(j,i));
    }
    return res;
}

// overload print operator
inline
std::ostream& operator<<(std::ostream& os, matrix4x4 const& m)
{
    for (int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
            os << m(i,j) << ", ";
        os << std::endl;
    }
    return os;
}

// inverse of matrix4x4
inline
auto determinant(matrix4x4 m)
{
    auto A2323 = m(2,2) * m(3,3) - m(2,3) * m(3,2);
    auto A1323 = m(2,1) * m(3,3) - m(2,3) * m(3,1);
    auto A1223 = m(2,1) * m(3,2) - m(2,2) * m(3,1);
    auto A0323 = m(2,0) * m(3,3) - m(2,3) * m(3,0);
    auto A0223 = m(2,0) * m(3,2) - m(2,2) * m(3,0);
    auto A0123 = m(2,0) * m(3,1) - m(2,1) * m(3,0);

    auto det = m(0,0) * (m(1,1) * A2323 - m(1,2) * A1323 + m(1,3) * A1223)
               - m(0,1) * (m(1,0) * A2323 - m(1,2) * A0323 + m(1,3) * A0223)
               + m(0,2) * (m(1,0) * A1323 - m(1,1) * A0323 + m(1,3) * A0123)
               - m(0,3) * (m(1,0) * A1223 - m(1,1) * A0223 + m(1,2) * A0123);
    return det;
}

// inverse of matrix4x4
inline
auto inverse(matrix4x4 m)
{
    auto A2323 = m(2,2) * m(3,3) - m(2,3) * m(3,2);
    auto A1323 = m(2,1) * m(3,3) - m(2,3) * m(3,1);
    auto A1223 = m(2,1) * m(3,2) - m(2,2) * m(3,1);
    auto A0323 = m(2,0) * m(3,3) - m(2,3) * m(3,0);
    auto A0223 = m(2,0) * m(3,2) - m(2,2) * m(3,0);
    auto A0123 = m(2,0) * m(3,1) - m(2,1) * m(3,0);

    num_t det = m(0,0) * (m(1,1) * A2323 - m(1,2) * A1323 + m(1,3) * A1223)
               - m(0,1) * (m(1,0) * A2323 - m(1,2) * A0323 + m(1,3) * A0223)
               + m(0,2) * (m(1,0) * A1323 - m(1,1) * A0323 + m(1,3) * A0123)
               - m(0,3) * (m(1,0) * A1223 - m(1,1) * A0223 + m(1,2) * A0123);
    if (det == static_cast<num_t>(0.0))
        throw std::domain_error("Zero determinant");
    det = 1 / det;

    matrix4x4 res;

    auto A2313 = m(1,2) * m(3,3) - m(1,3) * m(3,2);
    auto A1313 = m(1,1) * m(3,3) - m(1,3) * m(3,1);
    auto A1213 = m(1,1) * m(3,2) - m(1,2) * m(3,1);
    auto A2312 = m(1,2) * m(2,3) - m(1,3) * m(2,2);
    auto A1312 = m(1,1) * m(2,3) - m(1,3) * m(2,1);
    auto A1212 = m(1,1) * m(2,2) - m(1,2) * m(2,1);
    auto A0313 = m(1,0) * m(3,3) - m(1,3) * m(3,0);
    auto A0213 = m(1,0) * m(3,2) - m(1,2) * m(3,0);
    auto A0312 = m(1,0) * m(2,3) - m(1,3) * m(2,0);
    auto A0212 = m(1,0) * m(2,2) - m(1,2) * m(2,0);
    auto A0113 = m(1,0) * m(3,1) - m(1,1) * m(3,0);
    auto A0112 = m(1,0) * m(2,1) - m(1,1) * m(2,0);
    
    res(0,0) = det *   (m(1,1) * A2323 - m(1,2) * A1323 + m(1,3) * A1223);
    res(0,1) = det * - (m(0,1) * A2323 - m(0,2) * A1323 + m(0,3) * A1223);
    res(0,2) = det *   (m(0,1) * A2313 - m(0,2) * A1313 + m(0,3) * A1213);
    res(0,3) = det * - (m(0,1) * A2312 - m(0,2) * A1312 + m(0,3) * A1212);
    res(1,0) = det * - (m(1,0) * A2323 - m(1,2) * A0323 + m(1,3) * A0223);
    res(1,1) = det *   (m(0,0) * A2323 - m(0,2) * A0323 + m(0,3) * A0223);
    res(1,2) = det * - (m(0,0) * A2313 - m(0,2) * A0313 + m(0,3) * A0213);
    res(1,3) = det *   (m(0,0) * A2312 - m(0,2) * A0312 + m(0,3) * A0212);
    res(2,0) = det *   (m(1,0) * A1323 - m(1,1) * A0323 + m(1,3) * A0123);
    res(2,1) = det * - (m(0,0) * A1323 - m(0,1) * A0323 + m(0,3) * A0123);
    res(2,2) = det *   (m(0,0) * A1313 - m(0,1) * A0313 + m(0,3) * A0113);
    res(2,3) = det * - (m(0,0) * A1312 - m(0,1) * A0312 + m(0,3) * A0112);
    res(3,0) = det * - (m(1,0) * A1223 - m(1,1) * A0223 + m(1,2) * A0123);
    res(3,1) = det *   (m(0,0) * A1223 - m(0,1) * A0223 + m(0,2) * A0123);
    res(3,2) = det * - (m(0,0) * A1213 - m(0,1) * A0213 + m(0,2) * A0113);
    res(3,3) = det *   (m(0,0) * A1212 - m(0,1) * A0212 + m(0,2) * A0112);

    return res;
}

} // end namespace RT
#endif
