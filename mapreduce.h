// Copyright (C) 2018 Anders Dalle Henning Dalvander
//
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#if !defined(ADHD_MAPREDUCE_H)
#define ADHD_MAPREDUCE_H

#include <numeric>
#include <utility>
#include <vector>

namespace adhd {
   template <typename TMap>
   struct map_t {
      TMap map;
   };

   template <typename TMap>
   map_t<TMap> map(TMap map) {
      return { std::move(map) };
   }

   template <typename T, typename TMap>
   auto operator>>(const std::vector<T>& lhs, const map_t<TMap>& rhs) {
      using TMapped = decltype(rhs.map(std::declval<T>()));
      std::vector<TMapped> m;
      m.reserve(lhs.size());
      for (const auto& e : lhs) {
         m.emplace_back(rhs.map(e));
      }
      return std::move(m);
   }

   template <typename TFilter>
   struct filter_t {
      TFilter filter;
   };

   template <typename TFilter>
   filter_t<TFilter> filter(TFilter filter) {
      return { std::move(filter) };
   }

   template <typename T, typename TFilter>
   auto operator>>(const std::vector<T>& lhs, const filter_t<TFilter>& rhs) {
      std::vector<T> m;
      for (const auto& e : lhs) {
         if (rhs.filter(e)) {
            m.emplace_back(e);
         }
      }
      return std::move(m);
   }

   template <typename TReduce, typename TInit>
   struct reduce_t {
      TReduce reduce;
      TInit init;
   };

   template <typename TReduce, typename TInit>
   reduce_t<TReduce, TInit> reduce(TReduce reduce, TInit init) {
      return { std::move(reduce), std::move(init) };
   }

   template <typename T, typename TReduce, typename TInit>
   auto operator>>(const std::vector<T>& lhs, const reduce_t<TReduce, TInit>& rhs) {
      return std::reduce(std::begin(lhs), std::end(lhs), rhs.init, rhs.reduce);
   }
}

#endif
