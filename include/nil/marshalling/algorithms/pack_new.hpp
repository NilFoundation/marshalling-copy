//---------------------------------------------------------------------------//
// Copyright (c) 2020-2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020-2021 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2021 Aleksei Moskvin <alalmoskvin@gmail.com>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#ifndef MARSHALLING_MARSHALL_NEW_HPP
#define MARSHALLING_MARSHALL_NEW_HPP

#include <type_traits>

#include <boost/spirit/home/support/container.hpp>

#include <nil/marshalling/type_traits.hpp>
#include <nil/marshalling/inference.hpp>
#include <nil/marshalling/algorithms/pack_value.hpp>
#include <nil/detail/type_traits.hpp>

namespace nil {
    namespace marshalling {
        template<typename TEndian, typename SinglePassRange>
        range_pack_impl<TEndian, typename SinglePassRange::const_iterator> pack(const SinglePassRange &r, status_type &status) {

            return range_pack_impl<TEndian, typename SinglePassRange::const_iterator>(r, status);
        }

        template<typename TEndian, typename InputIterator>
        range_pack_impl<TEndian, InputIterator> pack(InputIterator first, InputIterator last, status_type &status) {

            return range_pack_impl<TEndian, InputIterator>(first, last, status);
        }

        template<typename TEndian, typename SinglePassRange, typename OutputIterator>
        itr_pack_impl<TEndian, typename SinglePassRange::iterator, OutputIterator> pack(SinglePassRange r, OutputIterator out, status_type &status) {

            return itr_pack_impl<TEndian, typename SinglePassRange::iterator, OutputIterator>(r, out, status);
        }

        template<typename TEndian, typename InputIterator, typename OutputIterator>
        itr_pack_impl<TEndian, typename InputIterator::iterator, OutputIterator> pack(InputIterator first, InputIterator last, OutputIterator out, status_type &status) {

            return itr_pack_impl<TEndian, typename InputIterator::iterator, OutputIterator>(first, last, out, status);
        }

    }    // namespace marshalling
}    // namespace nil

#endif    // MARSHALLING_MARSHALL_NEW_HPP