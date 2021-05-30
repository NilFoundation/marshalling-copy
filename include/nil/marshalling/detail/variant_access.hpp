//---------------------------------------------------------------------------//
// Copyright (c) 2017-2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
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

#ifndef MARSHALLING_VARIANT_ACCESS_HPP
#define MARSHALLING_VARIANT_ACCESS_HPP

#include <tuple>
#include <type_traits>

#include <nil/marshalling/detail/macro_common.hpp>
#include <nil/marshalling/detail/gen_enum.hpp>
#include <nil/marshalling/detail/base_detection.hpp>

#ifdef MARSHALLING_MUST_DEFINE_BASE
#define MARSHALLING_AS_VARIANT_FUNC Base& as_variant()
#define MARSHALLING_AS_VARIANT_CONST_FUNC const Base& as_variant() const
#define MARSHALLING_VARIANT_INIT_FIELD_FUNC(v_, n_)                                                         \
    typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), typename Base::members_type>::type& \
        MARSHALLING_CONCATENATE(initField_, n_)(TArgs && ... args)
#define MARSHALLING_VARIANT_ACCESS_FIELD_FUNC(v_, n_)                                                       \
    typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), typename Base::members_type>::type& \
        MARSHALLING_CONCATENATE(accessField_, n_)()
#define MARSHALLING_VARIANT_ACCESS_FIELD_CONST_FUNC(v_, n_)                                                       \
    const typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), typename Base::members_type>::type& \
        MARSHALLING_CONCATENATE(accessField_, n_)() const

#else    // #ifdef MARSHALLING_MUST_DEFINE_BASE
#define MARSHALLING_AS_VARIANT_FUNC \
    FUNC_AUTO_REF_RETURN(as_variant, decltype(nil::marshalling::types::to_field_base(*this)))
#define MARSHALLING_AS_VARIANT_CONST_FUNC \
    FUNC_AUTO_REF_RETURN_CONST(as_variant, decltype(nil::marshalling::types::to_field_base(*this)))
#define MARSHALLING_VARIANT_INIT_FIELD_FUNC(v_, n_)               \
    FUNC_ARGS_AUTO_REF_RETURN(                                    \
        MARSHALLING_CONCATENATE(initField_, n_), TArgs&&... args, \
        decltype(v_.template init_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>(std::forward<TArgs>(args)...)))
#define MARSHALLING_VARIANT_ACCESS_FIELD_FUNC(v_, n_)               \
    FUNC_AUTO_REF_RETURN(MARSHALLING_CONCATENATE(accessField_, n_), \
                         decltype(v_.template access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>()))
#define MARSHALLING_VARIANT_ACCESS_FIELD_CONST_FUNC(v_, n_)               \
    FUNC_AUTO_REF_RETURN_CONST(MARSHALLING_CONCATENATE(accessField_, n_), \
                               decltype(v_.template access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>()))
#endif    // #ifdef MARSHALLING_MUST_DEFINE_BASE

#define MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)                                                             \
    template<typename... TArgs>                                                                              \
    MARSHALLING_VARIANT_INIT_FIELD_FUNC(v_, n_) {                                                            \
        return v_.template init_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>(std::forward<TArgs>(args)...); \
    }                                                                                                        \
    MARSHALLING_VARIANT_ACCESS_FIELD_FUNC(v_, n_) {                                                          \
        return v_.template access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>();                           \
    }                                                                                                        \
    MARSHALLING_VARIANT_ACCESS_FIELD_CONST_FUNC(v_, n_) {                                                    \
        return v_.template access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>();                           \
    }

#define MARSHALLING_VARIANT_MEM_ACC_FUNC_1(v_, n_) MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_2(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_1(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_3(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_2(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_4(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_3(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_5(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_4(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_6(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_5(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_7(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_6(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_8(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_7(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_9(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_8(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_10(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_9(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_11(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_10(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_12(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_11(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_13(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_12(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_14(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_13(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_15(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_14(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_16(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_15(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_17(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_16(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_18(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_17(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_19(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_18(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_20(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_19(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_21(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_20(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_22(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_21(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_23(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_22(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_24(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_23(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_25(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_24(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_26(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_25(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_27(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_26(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_28(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_27(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_29(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_28(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_30(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_29(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_31(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_30(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_32(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_31(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_33(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_32(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_34(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_33(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_35(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_34(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_36(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_35(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_37(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_36(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_38(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_37(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_39(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_38(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_40(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_39(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_41(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_40(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_42(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_41(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_43(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_42(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_44(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_43(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_45(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_44(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_46(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_45(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_47(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_46(v_, __VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_48(v_, n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC(v_, n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_47(v_, __VA_ARGS__))

#define MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_(N, v_, ...) \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_##N(v_, __VA_ARGS__))
#define MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC(N, v_, ...) \
    MARSHALLING_EXPAND(MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_(N, v_, __VA_ARGS__))
#define MARSHALLING_DO_VARIANT_MEM_ACC_FUNC(v_, ...) \
    MARSHALLING_EXPAND(MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC(MARSHALLING_NUM_ARGS(__VA_ARGS__), v_, __VA_ARGS__))

// --------------------------------------------

#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)                                                               \
    template<typename... TArgs>                                                                                       \
    typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), members_type>::type& MARSHALLING_CONCATENATE( \
        initField_, n_)(TArgs && ... args) {                                                                          \
        return init_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>(std::forward<TArgs>(args)...);                      \
    }                                                                                                                 \
    typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), members_type>::type& MARSHALLING_CONCATENATE( \
        accessField_, n_)() {                                                                                         \
        return access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>();                                                \
    }                                                                                                                 \
    const typename std::tuple_element<MARSHALLING_CONCATENATE(FieldIdx_, n_), members_type>::type&                    \
        MARSHALLING_CONCATENATE(accessField_, n_)() const {                                                           \
        return access_field<MARSHALLING_CONCATENATE(FieldIdx_, n_)>();                                                \
    }

#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_1(n_) MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_2(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_1(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_3(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_2(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_4(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_3(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_5(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_4(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_6(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_5(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_7(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_6(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_8(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_7(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_9(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)            \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_8(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_10(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_9(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_11(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_10(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_12(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_11(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_13(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_12(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_14(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_13(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_15(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_14(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_16(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_15(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_17(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_16(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_18(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_17(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_19(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_18(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_20(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_19(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_21(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_20(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_22(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_21(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_23(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_22(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_24(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_23(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_25(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_24(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_26(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_25(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_27(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_26(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_28(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_27(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_29(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_28(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_30(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_29(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_31(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_30(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_32(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_31(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_33(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_32(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_34(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_33(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_35(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_34(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_36(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_35(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_37(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_36(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_38(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_37(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_39(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_38(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_40(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_39(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_41(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_40(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_42(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_41(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_43(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_42(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_44(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_43(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_45(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_44(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_46(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_45(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_47(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_46(__VA_ARGS__))
#define MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_48(n_, ...) \
    MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(n_)             \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_47(__VA_ARGS__))

#define MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_(N, ...) \
    MARSHALLING_EXPAND(MARSHALLING_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_##N(__VA_ARGS__))
#define MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(N, ...) \
    MARSHALLING_EXPAND(MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_NOTEMPLATE_(N, __VA_ARGS__))
#define MARSHALLING_DO_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(...) \
    MARSHALLING_EXPAND(                                     \
        MARSHALLING_CHOOSE_VARIANT_MEM_ACC_FUNC_NOTEMPLATE(MARSHALLING_NUM_ARGS(__VA_ARGS__), __VA_ARGS__))
#endif    // MARSHALLING_VARIANT_ACCESS_HPP