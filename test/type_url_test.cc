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

#include "type_url.h"

using namespace spine::type;

const std::string TYPE1 = "Type1";
const std::string PREFIX1 = "Prefix1";
const std::string URL1 = std::string(PREFIX1) + "/" + std::string(TYPE1);

TEST(TypeUrlShould, Create)
{
    type_url_t type_url = TypeUrl::create(PREFIX1, TYPE1);
    ASSERT_TRUE(type_url);
    ASSERT_EQ(type_url->prefix(), PREFIX1);
    ASSERT_EQ(type_url->type(), TYPE1);
    ASSERT_EQ(type_url->value(), URL1);
}

TEST(TypeUrlShould, ParseUrl)
{
    type_url_t type_url = TypeUrl::parse(URL1);
    ASSERT_TRUE(type_url);
    ASSERT_EQ(type_url->prefix(), PREFIX1);
    ASSERT_EQ(type_url->type(), TYPE1);
    ASSERT_EQ(type_url->value(), URL1);
}

TEST(TypeUrlShould, ThrowAtCreateWithInvalidParams)
{
    ASSERT_FALSE(TypeUrl::create(PREFIX1, ""));
    ASSERT_FALSE(TypeUrl::create("", TYPE1));
    ASSERT_FALSE(TypeUrl::create("", ""));
}

TEST(TypeUrlShould, ThrowAtParseWithInvalidParams)
{
    ASSERT_FALSE(TypeUrl::parse(""));
    ASSERT_FALSE(TypeUrl::parse("Type"));
    ASSERT_FALSE(TypeUrl::parse("Type/"));
    ASSERT_FALSE(TypeUrl::parse("/"));
    ASSERT_FALSE(TypeUrl::parse("/sadfsad"));
}

//TEST(TypeUrlShould, ThrowAtCreateWithInvalidParams)
//{
//    ASSERT_THROW(TypeUrl::create(PREFIX1, ""), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::create("", TYPE1), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::create("", ""), std::invalid_argument);
//}
//
//TEST(TypeUrlShould, ThrowAtParseWithInvalidParams)
//{
//    ASSERT_THROW(TypeUrl::parse(""), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::parse("Type"), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::parse("Type/"), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::parse("/"), std::invalid_argument);
//    ASSERT_THROW(TypeUrl::parse("/sadfsad"), std::invalid_argument);
//}