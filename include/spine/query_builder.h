

#ifndef SPINE_QUERY_BUILDER_H
#define SPINE_QUERY_BUILDER_H

#include "spine/util/message_utils.hpp"
#include "spine/types.h"

#include <spine/client/query.pb.h>

namespace spine{
namespace client
{

template <typename T, typename = enable_param_if_protobuf_message<T>>
class QueryBuilder
{
public:
    QueryBuilder& select();
    template <typename I, typename = enable_param_if_protobuf_message<I>>
    QueryBuilder& byId(const std::vector<std::unique_ptr<I>>& ids);

    template <typename I, typename = enable_param_if_protobuf_message<I>>
    QueryBuilder& withMasks(const std::vector<std::string>& masks);

    QueryBuilder& orderBy(const std::string& column, OrderBy::Direction direction);

    QueryBuilder& limit(std::uint32_t count);

    QueryPtr build()
    {

    }
};

}
}
#endif //SPINE_QUERY_BUILDER_H
