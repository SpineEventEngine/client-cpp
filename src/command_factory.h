//
// Created by Vladimir Moiseiev on 12/11/17.
//

#ifndef SPINE_COMMANDFACTORY_H
#define SPINE_COMMANDFACTORY_H

#include <memory>
#include <google/protobuf/message.h>
#include <google/protobuf/timestamp.pb.h>
#include <spine/time/zone.pb.h>
#include <Poco/UUIDGenerator.h>
#include <spine/core/command.pb.h>

namespace spine
{
namespace core
{
    class Command;
    class CommandContext;
    class UserId;
    class ActorContext;
}
namespace client
{

    class ActorRequestFactory;

class CommandFactory
{
public:
    CommandFactory(const ActorRequestFactory & actor_request_factory);
public:
    std::unique_ptr<core::Command> create(const ::google::protobuf::Message& message);
    std::unique_ptr<core::Command> create(const ::google::protobuf::Message& message, int target_version);

private:
    std::unique_ptr<core::ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;

};

}} //namespace


#endif //SPINE_COMMANDFACTORY_H
