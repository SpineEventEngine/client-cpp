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


#include <gtest/gtest.h>

#include "common_factory_test.h"
#include "unit_tests.pb.h"
#include "unit_tests_no_prefix.pb.h"
#include <spine/client/query.pb.h>

#include "spine/query_builder.h"
#include "spine/filters.h"

#include <google/protobuf/wrappers.pb.h>

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class QueryBuilderShould : public CommonFactoryTest
{

};

TEST_F(QueryBuilderShould, CreateWithBuilder)
{

    Int32Value pValue1;   pValue1.set_value(15);
    Int32Value pValue2;   pValue2.set_value(42);
    Int32Value pValue3;   pValue3.set_value(17);

    std::vector<std::unique_ptr<Int32Value>> ids;
    ids.emplace_back(std::make_unique<Int32Value>());
    ids.emplace_back(std::make_unique<Int32Value>());
    ids.emplace_back(std::make_unique<Int32Value>());

    std::vector<std::string> masks {"mask1", "mask2"};

    std::unique_ptr<CompositeFilter> all_filter = all(eq("field1", pValue1), ge("field4", pValue2), gt("field16", pValue3));
    std::unique_ptr<CompositeFilter> either_filter = either(eq("dsfdsf", pValue2), ge("field4", pValue3), gt("dfgdf", pValue1));

    QueryBuilder<TestMessage> builder;

    QueryPtr query = builder
                        .byId(ids)
                        .withMasks(masks)
                        .limit(15)
                        .orderBy("column", OrderBy::ASCENDING)
                        .where(
                            all(
                                eq("field1", pValue1),
                                ge("field4", pValue2),
                                gt("field16", pValue3)
                            )
                        )
                        .build();




    int x = 1;

}