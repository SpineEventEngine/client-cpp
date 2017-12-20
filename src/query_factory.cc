/*
 * Copyright 2017, TeamDev Ltd. All rights reserved.
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

#include "query_factory.h"

#include <sstream>



#include "actor_request_factory.h"
#include "common.h"

namespace spine {
namespace client {

const std::string QUERY_ID_TEMPLATE = "query-";

QueryFactory::QueryFactory(const ActorRequestFactory &actor_request_factory)
{
    actor_context_ = actor_request_factory.actor_context();
}

std::unique_ptr<Query> QueryFactory::all(const std::string& type_url) {
    Target* target = create_target(type_url);

    std::unique_ptr<Query> query { Query::default_instance().New() };

    query->set_allocated_id(createQueryId());
    query->set_allocated_context(copy_actor_context(*actor_context_));
    query->set_allocated_target(target);

    return query;
}

    QueryId *QueryFactory::createQueryId() {
    QueryId *query_id = new QueryId();
    std::__1::stringstream query_id_stream;
    query_id_stream << QUERY_ID_TEMPLATE << uuid_generator_.createRandom().toString();
    query_id->set_value(query_id_stream.str());
    return query_id;
}


}} // namespace
