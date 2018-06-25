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

#include <sstream>

#include "spine/query_factory.h"

using namespace spine::core;
using namespace google::protobuf;

namespace spine {
namespace client {

const std::string QUERY_ID_TEMPLATE = "query-"; // The format of all QueryId query identifiers.

QueryFactory::QueryFactory(std::unique_ptr<core::ActorContext>&& actor_context)
{
    actor_context_ = std::move(actor_context);
}

QueryPtr QueryFactory::for_query(std::unique_ptr<Target>&& target)
{
    std::unique_ptr<Query> query { Query::default_instance().New() };

    query->set_allocated_id(create_query_id());
    query->set_allocated_context(clone(actor_context_));
    query->set_allocated_target(target.release());
    query->set_allocated_field_mask(clone(FieldMask::default_instance()));

    return query;
}

QueryPtr QueryFactory::for_query(std::unique_ptr<Target>&& target, std::unique_ptr<FieldMask> && field_mask)
{
    std::unique_ptr<Query> query = for_query(std::move(target));
    query->set_allocated_field_mask(field_mask.release());

    return query;
}

QueryPtr QueryFactory::make_query(const std::string& prefix, const std::string& type)
{
    std::unique_ptr<Target> target = compose_target(prefix, type);
    return for_query(std::move(target));
}

QueryPtr QueryFactory::make_query(const std::string& prefix, const std::string& type,
                                  const std::vector<std::string>& masks)
{
    std::unique_ptr<Target> target = compose_target(prefix, type);
    return for_query(std::move(target), std::move(make_field_mask(masks)));
}

std::unique_ptr<FieldMask> QueryFactory::make_field_mask(const std::vector<std::string>& masks)
{
    std::unique_ptr<FieldMask> field_mask {FieldMask::default_instance().New() };

    RepeatedPtrField< string> paths (masks.begin(), masks.end());
    field_mask->mutable_paths()->Swap(&paths);

    return field_mask;
}

QueryId *QueryFactory::create_query_id()
{
    QueryId *query_id = QueryId::default_instance().New();
    std::stringstream query_id_stream;
    query_id_stream << QUERY_ID_TEMPLATE << uuid_generator_.createRandom().toString();
    query_id->set_value(query_id_stream.str());

    return query_id;
}

}}
