#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
#include <iostream>

namespace RT
{

template<typename T>
struct matrix
{
    public:
        matrix(size_t rows, size_t cols)
           : m_rows(rows),
             m_cols(cols),
             m_data(rows * cols) {}

        //matrix(const matrix& rhs)
        
        T& operator()(size_t i, size_t j)
        {
            bound_check(i, j);
            return m_data[i * m_cols + j];
            //catch (const std::exception& e)
            //{
            //    std::cout << e.what();
            //}
        }

        T operator()(size_t i, size_t j) const
        {
            bound_check(i, j);
            return m_data[i * m_cols + j];
        }
    private:
        size_t m_rows, m_cols;
        std::vector<T> m_data;

        void bound_check(size_t i, size_t j)
        {
            if (i > (m_rows - 1) || j > (m_cols - 1))
                throw std::out_of_range("matrix<T> : index is out of range");
        }
};

} // end namespace RT
#endif
