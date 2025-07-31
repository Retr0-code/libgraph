/*
    Copyright (C) 2023 Nikita Retr0-code Korneev

    libgraph is free software: you can redistribute, modify it
    under the terms of the MIT License.

    You should have received a copy of MIT License along with jsast.js.
    If not, see <https://opensource.org/license/MIT.
*/

#pragma once
#include "GraphBase.hpp"

/**
 * @brief Standard accumulator that adds up given values.
 * 
 * @tparam T - type of value to add.
 */
template <class T>
class AccumulatorSum : IAccumulator<T> {
public:    
    AccumulatorSum(const T& init) : _sum(init) {}
    
    AccumulatorSum(const T&& init) : _sum(init) {}

    virtual const T& operator()(const T& accumulated, const T& value) final {
        this->_sum = accumulated + value;
        return this->_sum;
    }
    
    virtual T operator()(T accumulated, T value) final {
        this->_sum = accumulated + value;
        return this->_sum;
    }

    virtual const T& Get(void) const final {
        return this->_sum;
    }

private:
    T _sum;
};

/**
 * @brief Standard accumulator that multiplies given values.
 * 
 * @tparam T - type of value to multiply.
 */
template <class T>
class AccumulatorMul : IAccumulator<T> {
public:
    AccumulatorMul(const T& init) : _product(init) {}
    
    AccumulatorMul(const T&& init) : _product(init) {}

    virtual const T& operator()(const T& accumulated, const T& value) final {
        this->_product = accumulated * value;
        return this->_product;
    }
    
    virtual T operator()(T accumulated, T value) final {
        this->_product = accumulated * value;
        return this->_product;
    }

    virtual const T& Get(void) const final {
        return this->_product;
    }

private:
    T _product;
};
