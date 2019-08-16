/*
 * Copyright 2018, TeamDev. All rights reserved.
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

#ifndef SPINE_TARGET_UTILS_H
#define SPINE_TARGET_UTILS_H

/**
 * @file target_utils.hpp
 *
 * Utility functions to operate with spine::client::Target.
 * For internal use.
 *
 * @author Vladimir Moiseiev
 */


#include <memory>
#include <vector>

#include <spine/client/entities.pb.h>
#include <spine/client/subscription.pb.h>
#include <spine/client/filters.pb.h>

#include "spine/util/message_utils.hpp"
#include "spine/util/any_utils.hpp"
#include "spine/query_utils.h"
#include "spine/filters.h"

namespace spine {
namespace client {

template <typename T, typename = enable_param_if_protobuf_message<T>>
static std::unique_ptr<IdFilter> make_id_filter(const std::vector<std::unique_ptr<T>>& ids)
{
    std::unique_ptr<IdFilter> id_filter{IdFilter::default_instance().New()};
    for (auto& message : ids)
    {
        std::unique_ptr<google::protobuf::Any> any = to_any(*message);
        id_filter->mutable_ids()->AddAllocated(any.release());
    }

    return id_filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
static std::unique_ptr<TargetFilters> make_ids_and_target_filters(const std::vector<std::unique_ptr<T>>& ids,
                                                                  std::vector<std::unique_ptr<CompositeFilter>>& composite_filters)
{
    std::unique_ptr<TargetFilters> target_filters { TargetFilters::default_instance().New() };
    if( !ids.empty())
    {
        target_filters->set_allocated_id_filter(make_id_filter(ids).release());
    }

    if( !composite_filters.empty() )
    {
        for (std::unique_ptr<CompositeFilter>& composite_filter : composite_filters)
        {
            target_filters->mutable_filter()->AddAllocated(composite_filter.release());
        }
    }
    return target_filters;
}

inline std::unique_ptr<Target> compose_target(const std::string& prefix, const std::string& type)
{
    std::unique_ptr<Target> target { Target::default_instance().New() };

    std::string type_url = type;
    if( !prefix.empty() )
    {
        type_url.insert(0, prefix + "/");
    }
    target->set_type(type_url);
    target->set_include_all(true);

    return target;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Target> compose_target(const std::string& prefix, const std::string& type,
                                       const std::vector<std::unique_ptr<T>>& ids,
                                       std::vector<std::unique_ptr<CompositeFilter>>& composite_filters
                                       )
{
    std::unique_ptr<Target> target = std::move(compose_target(prefix, type));
    if( !ids.empty() || !composite_filters.empty())
    {
        target->set_allocated_filters(make_ids_and_target_filters(ids, composite_filters).release());
    }
    return target;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Target> compose_target(const std::string& prefix, const std::string& type,
                                       const std::vector<std::unique_ptr<T>>& ids)
{
    std::vector<std::unique_ptr<CompositeFilter>> empty;
    return compose_target(prefix, type, ids, empty);
}

}

}

#endif //SPINE_TARGET_UTILS_H
