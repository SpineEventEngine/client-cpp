//
// Created by Vladimir Moiseiev on 12/11/17.
//

#ifndef SPINE_QUERYFACTORY_H
#define SPINE_QUERYFACTORY_H

#include <memory>
#include <Poco/UUIDGenerator.h>
#include <spine/client/query.pb.h>

namespace spine {

namespace core {
    class ActorContext;
}

namespace client {

class ActorRequestFactory;
class Query;

class QueryFactory
{
public:
    QueryFactory(const ActorRequestFactory & actor_request_factory);

public:
    std::unique_ptr<Query> all(const std::string& type_url);

private:
    spine::client::QueryId *createQueryId();
private:
    std::unique_ptr<core::ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;


    //Target* create_target(const std::string& type_url) const;
};

}} //namespace

#endif //SPINE_QUERYFACTORY_H
