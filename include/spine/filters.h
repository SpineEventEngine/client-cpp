//
// Created by vladimir.moiseiev on 2019-04-09.
//

#ifndef SPINE_FILTERS_H
#define SPINE_FILTERS_H

#include <memory>
#include <boost/algorithm/string.hpp>

#include <spine/client/filters.pb.h>
#include <spine/base/field_path.pb.h>

#include "util/any_utils.hpp"

namespace spine {
namespace client {

static std::unique_ptr<base::FieldPath> make_field_path(const std::vector<std::string>& elements)
{
    std::unique_ptr<base::FieldPath> field_path {base::FieldPath::default_instance().New()};
    for(auto& path : elements)
    {
        field_path->add_field_name(path);
    }

    return field_path;
}


template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> make_filter(const std::string& field_path, T value)
{
    std::vector<std::string> elems;
    typedef boost::split_iterator<std::string::const_iterator> spliterator;
    std::string sdelim(1, '.');
    for (spliterator it = boost::make_split_iterator(field_path,
                                                     boost::first_finder(sdelim, boost::is_equal()));
         it != spliterator(); ++it) {
        elems.push_back(boost::copy_range<std::string>(*it));
    }

    std::unique_ptr<base::FieldPath> path = make_field_path(elems);

    std::unique_ptr<Filter> filter {Filter::default_instance().New()};
    filter->set_allocated_field_path(path.release());
    filter->set_allocated_value(to_any(value).release());
    return filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> eq(const std::string& field_path, T value)
{
    std::unique_ptr<Filter> filter = make_filter(field_path, value);
    filter->set_operator_(Filter::EQUAL);
    return filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> gt(const std::string& field_path, T value)
{
    std::unique_ptr<Filter> filter = make_filter(field_path, value);
    filter->set_operator_(Filter::GREATER_THAN);
    return filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> lt(const std::string& field_path, T value)
{
    std::unique_ptr<Filter> filter = make_filter(field_path, value);
    filter->set_operator_(Filter::LESS_THAN);
    return filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> ge(const std::string& field_path, T value)
{
    std::unique_ptr<Filter> filter = make_filter(field_path, value);
    filter->set_operator_(Filter::GREATER_OR_EQUAL);
    return filter;
}

template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<Filter> le(const std::string& field_path, T value)
{
    std::unique_ptr<Filter> filter = make_filter(field_path, value);
    filter->set_operator_(Filter::LESS_OR_EQUAL);
    return filter;
}


static std::unique_ptr<CompositeFilter> make_composite_filter(std::unique_ptr<Filter>& filter)
{
    std::unique_ptr<CompositeFilter> composite_filter {CompositeFilter::default_instance().New()};
    composite_filter->mutable_filter()->AddAllocated(filter.release());
    composite_filter->set_operator_(CompositeFilter::ALL);

    return composite_filter;
}

static std::unique_ptr<CompositeFilter> make_composite_filter(std::vector<std::unique_ptr<Filter>>& filters)
{
    std::unique_ptr<CompositeFilter> composite_filter {CompositeFilter::default_instance().New()};
    for(std::unique_ptr<Filter>& filter : filters)
    {
        composite_filter->mutable_filter()->AddAllocated(filter.release());
    }

    return composite_filter;
}

static std::unique_ptr<CompositeFilter> either(std::vector<std::unique_ptr<Filter>>& filters)
{
    std::unique_ptr<CompositeFilter> composite_filter = make_composite_filter(filters);
    composite_filter->set_operator_(CompositeFilter::EITHER);
    return composite_filter;
}

static std::unique_ptr<CompositeFilter> all(std::vector<std::unique_ptr<Filter>>& filters)
{
    std::unique_ptr<CompositeFilter> composite_filter = make_composite_filter(filters);
    composite_filter->set_operator_(CompositeFilter::ALL);
    return composite_filter;
}



}
}

#endif //SPINE_FILTERS_H
