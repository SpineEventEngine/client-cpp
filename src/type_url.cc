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

#include "type_url.h"

#include <boost/algorithm/string.hpp>

using namespace spine::type;

static const char SEPARATOR = '/';

TypeUrl::TypeUrl(const std::string& prefix, const std::string& type)
{
    prefix_ = prefix;
    type_ = type;
}

std::string TypeUrl::prefix() const
{
    return prefix_;
}

std::string TypeUrl::type() const
{
    return type_;
}

type_url_t TypeUrl::create(const std::string& prefix, const std::string& type)
{
    if (prefix.empty() || type.empty())
    {
        return type_url_t();
    }
    return type_url_t(new TypeUrl(prefix, type));
}

type_url_t TypeUrl::parse(const std::string& from)
{
    if (from.empty())
    {
        return type_url_t();
    }

    std::vector<std::string> split_values;
    boost::split(split_values, from, [](char val) { return SEPARATOR == val;});
    if (2 == split_values.size() && !split_values[0].empty() && !split_values[1].empty())
    {
        return type_url_t(new TypeUrl(split_values[0], split_values[1]));
    }
    return type_url_t();
}

std::string TypeUrl::value() const
{
    return prefix_ + SEPARATOR + type_;
}
