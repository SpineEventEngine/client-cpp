

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
    QueryBuilder(QueryFactory& query_factory) : query_factory_(query_factory)
    {

    }

    template <typename I, typename = enable_param_if_protobuf_message<I>>
    QueryBuilder& byId(const std::vector<std::unique_ptr<I>>& ids)
    {
        for(auto& id : ids)
        {
            ids_.emplace_back(to_any(*id));
        }
        return *this;
    }

    QueryBuilder& withMasks(const std::vector<std::string>& masks)
    {
        std::copy(masks.begin(), masks.end(), std::back_inserter(field_masks_));
        return *this;
    }

    QueryBuilder& orderBy(const std::string& column, OrderBy::Direction direction)
    {
        ordering_column_ = column;
        direction_ = direction;

        return *this;
    }

    QueryBuilder& limit(std::uint32_t count)
    {
        limit_ = count;
        return *this;
    }

    template <typename ...Filters, typename = std::unique_ptr<CompositeFilter>>
    QueryBuilder& where(Filters&&... args)
    {
        add_to_vector(composite_filters_, std::forward<Filters>(args)...);
        return *this;
    }

    QueryPtr build()
    {
        QueryPtr query = query_factory_.all<ZoneId>();
        if( !field_masks_.empty() )
        {

        }

        if( !composite_filters_.empty() )
        {

        }
        return QueryPtr();
    }

private:

private:
    QueryFactory& query_factory_;
    std::vector<std::unique_ptr<google::protobuf::Any>> ids_;
    std::vector<std::string> field_masks_;
    std::vector<std::unique_ptr<CompositeFilter>> composite_filters_;
    std::string ordering_column_;
    OrderBy::Direction direction_;
    std::uint32_t limit_;
};

}
}
#endif //SPINE_QUERY_BUILDER_H
