/*
 * Copyright 2019, TeamDev. All rights reserved.
 *
 * Redistribution and use in source and/or binary forms, with or without
 * modification, must retain the above copyright notice and the following
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "spine/query_utils.h"

using namespace google::protobuf;

namespace spine {
namespace client {

std::unique_ptr<FieldMask> make_field_mask(const std::vector<std::string>& masks)
{
    std::unique_ptr<FieldMask> field_mask_ptr {FieldMask::default_instance().New() };

    for(auto& field_mask : masks)
    {
        //ignoring google validation by type descriptor
        //FieldMaskUtil::AddPathToFieldMask<std::string>(StringPiece{field_mask}, field_mask_ptr.get());
        field_mask_ptr->add_paths(field_mask);
    }

    return field_mask_ptr;
}

std::unique_ptr<spine::client::OrderBy> make_order_by(const std::string& order_by_column,
                                                      const OrderBy::Direction& direction)
{
    std::unique_ptr<OrderBy> order_by {OrderBy::default_instance().New()};
    order_by->set_column(order_by_column);
    order_by->set_direction(direction);
    return order_by;
}

std::unique_ptr<Pagination> make_pagination(uint32_t page_size)
{
    std::unique_ptr<Pagination> pagination {Pagination::default_instance().New()};
    pagination->set_page_size(page_size);
    return pagination;
}

}
}
