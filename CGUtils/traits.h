#ifndef TRAITS_H
#define TRAITS_H

#include "cg-utils_global.h"
#include "matrix.h"

#include <type_traits>

CGUTILS_NAMESPACE_BEGIN

template<typename>
struct is_vector : std::false_type {};

template<size_t N>
struct is_vector<Vector<N>> : std::true_type {};

template<typename T, typename = void>
struct is_iterable : std::false_type {};

template<typename T>
struct is_iterable<
        T,
        std::void_t<decltype(
                (void)(std::begin(std::declval<T&>()) != std::end(std::declval<T&>())),
                (void)++std::declval<decltype(std::begin(std::declval<T&>()))&>(),
                *std::begin(std::declval<T&>())
            )>
        > : std::true_type {};

template<typename Container>
struct contained_type {
    typedef typename std::iterator_traits<decltype(std::begin(std::declval<Container&>()))>::value_type type;
};

template<typename Container, typename T, typename = void>
struct is_container_of : std::false_type {};

template<typename Container, typename T>
struct is_container_of<
            Container,
            T,
            typename std::enable_if<
                is_iterable<Container>::value &&
                std::is_same<typename contained_type<Container>::type, T>::value
            >::type
        > : std::true_type {};

template<typename T, typename = void>
struct is_container_of_vectors : std::false_type {};

template<typename T>
struct is_container_of_vectors<
            T,
            typename std::enable_if<
                is_iterable<T>::value &&
                is_vector<typename contained_type<T>::type>::value
            >::type
        > : std::true_type {};

CGUTILS_NAMESPACE_END

#endif // TRAITS_H
