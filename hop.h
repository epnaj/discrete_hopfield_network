#ifndef hop_h
#define hop_h

#include <iostream>
#include "out.h"

#define ull unsigned long long

#define ZERO_DIAGONAL 0

template <typename T>
struct Neuron{
    // bias is equal to 0
    T value;
    void applySignum(){ value = value < 0 ? -1 : (value > 0); }
    void applySignumTwoState(){ value = value > 0 ? 1 : -1; }
};

template <typename T>
struct Matrix{
    T *elements;
    const ull m_rows, m_cols;
    const ull m_size;
    Matrix(const ull &rows, const ull &cols) : m_size(rows*cols), m_rows(rows), m_cols(cols){ elements = new T [m_size]; }
    ~Matrix(){ delete [] elements; }
};

template <typename T>
struct Network{
    const ull n_size;
    Matrix <Neuron <T>> *m;
    Matrix <T> *synapses;
    Network(const ull &img_rows, const ull &img_cols) : n_size(img_cols*img_rows) {
        m = new Matrix <Neuron <T>> (img_rows, img_cols);
        synapses = new Matrix <T> (n_size, n_size);
        for(ull i=0; i<synapses->m_size; ++i){
            // null all of the weights at the beggining
            synapses->elements[i] = 0;
        }
    }

    void push(const T *data, const ull &data_size){
        if(data_size < n_size){
            std::cout << "Wrong data size!\n";
            return;
        }
        for(ull i=0; i<n_size; ++i){
            m->elements[i].value = data[i];
        }
    }

    void applyHebbRule(){   
        for(ull i=0; i<synapses->m_rows; ++i){
            for(ull j=0; j<synapses->m_cols; ++j){
                synapses->elements[i*synapses->m_rows + j] += m->elements[i].value * m->elements[j].value / m->m_size;
            }
        }
        // depending on purpose you can set network not to take self state
        #if ZERO_DIAGONAL == 1
        for(ull i=0; i<synapses->m_rows; ++i)
            synapses->elements[i*synapses->m_rows + i] = 0;
        #endif
    }

    void pushForward(const T *pattern, const ull &p_size){
        for(ull i=0; i<m->m_size; ++i)
            m->elements[i].value = 0;
        T temp;
        for(ull i=0; i<synapses->m_rows; ++i){
            temp = 0;
            for(ull j=0; j<synapses->m_cols; ++j){
                temp += pattern[j] * synapses->elements[i*synapses->m_rows + j];
            }
            m->elements[i].value += temp;
            m->elements[i].applySignum();
        }
        std::cout << "Image recovered using network :\n";
        for(ull i=0; i<m->m_rows; ++i){
            for(ull j=0; j<m->m_cols; ++j){
                std::cout << (m->elements[i*m->m_rows + j].value == 1 ? "x" : " ");
            }
            std::cout << std::endl;
        }
    }
    
    ~Network(){
        delete [] m;
        delete [] synapses;
    }
};

#endif
