/*
 * Copyright 2018, TeamDev Ltd. All rights reserved.
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

#ifndef SPINE_ANY_UTILS_H
#define SPINE_ANY_UTILS_H

/**
 * @file any_utils.h
 *
 * Utility functions to operate with \b protobuf::Any and \b protobuf::Message.
 *
 * @author Vladimir Moiseiev
 */

#include <memory>

#include "spine/util/message_utils.hpp"

#include <google/protobuf/any.pb.h>
#include <google/protobuf/message.h>

namespace spine {
namespace client {

/**
 * Converts \b protobuf::Message to \b protobuf::Any.
 *
 * Any will be packed using certain Type URL prefix. If `.proto file` contains a custom
 * prefix — it will be used, otherwise, it will be set to default
 * Google's prefix `type.googleapis.com`.
 *
 * @param message Protobuf message.
 * @return Protobuf Any packed from a message.
 */
std::unique_ptr<::google::protobuf::Any> to_any(const ::google::protobuf::Message &message);

/**
 * Converts \b protobuf::Any to \b protobuf::Message.
 *
 * @tparam T A Protobuf Message type expected.
 * @param any Protobuf Any that contains \b Message.
 * @return unique_ptr of the supplied Protobuf Message. May return empty unique_ptr, if unpack fail.
 */
template <typename T, typename = enable_param_if_protobuf_message<T>>
std::unique_ptr<T> from_any(const ::google::protobuf::Any& any)
{
    std::unique_ptr<T> result { T::default_instance().New() };
    if ( any.UnpackTo(result.get()) )
    {
        return result;
    }
    return std::unique_ptr<T>{};
};

}} // namespace
#endif //SPINE_ANY_UTILS_H
