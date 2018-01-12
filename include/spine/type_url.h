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

#ifndef SPINE_TYPEURL_H
#define SPINE_TYPEURL_H

#include <string>
#include "types.h"

namespace spine
{
namespace type
{

/**
 * A URL of a Protobuf type.
 *
 * Consists of the two parts separated with a slash.
 * The first part is the type URL prefix (for example, `type.googleapis.com`).
 * The second part is a [fully-qualified Protobuf type name](@code google::protobuf::Descriptors::Descriptor::full_name).
 *
 * @author Alexander Yevsyukov
 * @see google::protobuf::Any::type_url
 */
class TypeUrl final
{
public:
    /**
     * Create new [TypeUrl](@ref TypeUrl).
     *
     * @param prefix The prefix of the type URL.
     * @param type The name of the Protobuf type.
     *
    */
    static TypeUrlPtr create(const std::string& prefix, const std::string& type);
    /**
    * Creates a new instance from the passed type URL.
    *
    * @param from the type URL of the Protobuf message type
    */
    static TypeUrlPtr parse(const std::string& from);

    /**
     *
     * @return a string representation of [TypeUrl](@ref TypeUrl).
     */
    std::string value() const;

    std::string prefix() const;     /**< @return The prefix of the type URL. */
    std::string type() const;       /**< @return The name of the Protobuf type. */

public:
    TypeUrl(const TypeUrl&) = default;
    TypeUrl(TypeUrl&&) = default;
    TypeUrl& operator=(const TypeUrl&) = default;
    TypeUrl& operator=(TypeUrl&&) = default;

    ~TypeUrl() = default;

private:
    TypeUrl(const std::string& prefix, const std::string& type);

private:
    std::string prefix_;      /**< The prefix of the type URL. */
    std::string type_;        /**< The name of the Protobuf type. */
};

}} //namespace

#endif //SPINE_TYPEURL_H
