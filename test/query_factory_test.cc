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


#include <gtest/gtest.h>

#include <boost/algorithm/string.hpp>

#include "spine/query_factory.h"
#include "spine/actor_request_factory.h"

#include "common_factory_test.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

class QueryFactoryShould : public CommonFactoryTest
{
};

TEST_F(QueryFactoryShould, Create)
{
    QueryPtr query = query_factory_->all<ZoneId>();

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), ZoneId::descriptor()->full_name());


}