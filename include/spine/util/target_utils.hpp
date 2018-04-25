/*
 * Copyright 2018, TeamDev Ltd. All rights reserved.
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

#include "spine/util/message_utils.hpp"
#include "spine/util/any_utils.hpp"

namespace spine {
namespace client {


template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<EntityFilters> make_entity_filters(const std::vector<std::unique_ptr<T>>& ids)
{
    std::unique_ptr<EntityIdFilter> entity_id_filter { EntityIdFilter::default_instance().New() };
    for (auto &message : ids)
    {
        std::unique_ptr<google::protobuf::Any> any = to_any(*message);
        std::unique_ptr<EntityId> entity_id { EntityId::default_instance().New() };
        entity_id->set_allocated_id(any.release());
        entity_id_filter->mutable_ids()->AddAllocated(entity_id.release());
    }
    std::unique_ptr<EntityFilters> entity_filters { EntityFilters::default_instance().New() };
    entity_filters->set_allocated_id_filter(entity_id_filter.release());

    return entity_filters;
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
    target->set_allocated_filters(clone(EntityFilters::default_instance()));

    return target;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Target> compose_target(const std::string& prefix, const std::string& type,
                                       const std::vector<std::unique_ptr<T>>& ids)
{
    std::unique_ptr<Target> target = std::move(compose_target(prefix, type));
    if( !ids.empty() )
    {
        target->set_include_all(false);
        target->set_allocated_filters(make_entity_filters(ids).release());
    }
    return target;
}

}
}

#endif //SPINE_TARGET_UTILS_H
