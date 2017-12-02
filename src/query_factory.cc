//
// Created by Vladimir Moiseiev on 12/11/17.
//

#include "query_factory.h"

#include <sstream>



#include "actor_request_factory.h"

namespace spine {
namespace client {

const std::string QUERY_ID_TEMPLATE = "query-";

QueryFactory::QueryFactory(const ActorRequestFactory &actor_request_factory)
{
    actor_context_ = actor_request_factory.actor_context();
}

std::unique_ptr<Query> QueryFactory::all(const std::string& type_url) {
    Target *target = Target::default_instance().New();
    target->set_type(type_url);

    std::unique_ptr<Query> query { Query::default_instance().New() };

    query->set_allocated_id(createQueryId());

    query->set_allocated_context(new ::spine::core::ActorContext(*actor_context_));
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
