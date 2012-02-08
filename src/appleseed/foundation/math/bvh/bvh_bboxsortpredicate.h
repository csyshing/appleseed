
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_FOUNDATION_MATH_BVH_BVH_BBOXSORTPREDICATE_H
#define APPLESEED_FOUNDATION_MATH_BVH_BVH_BBOXSORTPREDICATE_H

// Standard headers.
#include <cstddef>
#include <vector>

namespace foundation {
namespace bvh {

//
// A predicate to sort items according to the centroid of their bounding box
// along a given dimension.
//

template <typename AABBType>
class BboxSortPredicate
{
  public:
    BboxSortPredicate(
        const std::vector<AABBType>&    bboxes,
        const size_t                    dim);

    bool operator()(const size_t lhs, const size_t rhs) const;

  private:
    const std::vector<AABBType>&        m_bboxes;
    const size_t                        m_dim;
};


//
// BboxSortPredicate class implementation.
//

template <typename AABBType>
inline BboxSortPredicate<AABBType>::BboxSortPredicate(
    const std::vector<AABBType>&        bboxes,
    const size_t                        dim)
  : m_bboxes(bboxes)
  , m_dim(dim)
{
}

template <typename AABBType>
inline bool BboxSortPredicate<AABBType>::operator()(
    const size_t                        lhs,
    const size_t                        rhs) const
{
    typedef typename AABBType::VectorType VectorType;

    const VectorType lhs_center = m_bboxes[lhs].center();
    const VectorType rhs_center = m_bboxes[rhs].center();

    for (size_t i = 0; i < AABBType::Dimension; ++i)
    {
        const size_t d = (m_dim + i) % AABBType::Dimension;

        if (lhs_center[d] < rhs_center[d])
            return true;

        if (lhs_center[d] > rhs_center[d])
            return false;
    }

    return false;
}

}       // namespace bvh
}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_MATH_BVH_BVH_BBOXSORTPREDICATE_H
