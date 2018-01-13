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

#ifndef MESSAGE_UTILS_HPP_
#define MESSAGE_UTILS_HPP_

#include <memory>
#include <google/protobuf/message.h>

namespace spine
{

template<class Derived> constexpr bool is_protobuf_message
        = std::is_base_of<google::protobuf::Message, Derived>::value;

template<typename Msg>
typename std::enable_if
        <
                std::is_base_of<google::protobuf::Message, Msg>::value,
                Msg
        >::type*
clone(const Msg& msg)
{
    auto new_msg = msg.New();
    new_msg->CopyFrom(msg);
    return new_msg;
}

template<typename T>
typename std::enable_if
        <
                std::is_base_of<google::protobuf::Message, typename std::unique_ptr<T>::element_type>::value,
                typename std::unique_ptr<T>::element_type
        >::type*
clone(const std::unique_ptr<T>& p)
{
    return clone<T>(*p);
}

}
#endif //MESSAGE_UTILS_HPP_
