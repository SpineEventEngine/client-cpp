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

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.pb.h>

#include <spine/options.pb.h>

#include "spine/validator.h"

using namespace ::google::protobuf;

namespace spine {
namespace client {

//bool validate(const FieldDescriptor& field)

bool Validator::Validate(const ::google::protobuf::Message &message)
{
    //message.GetDescriptor()->file()->options().
    const Descriptor *desc       = message.GetDescriptor();
    const Reflection *refl       = message.GetReflection();
    int fieldCount = desc->field_count();

    fprintf(stderr, "Message name:  %s \n",message.GetTypeName().c_str());

    for(int i=0;i<fieldCount;i++)
    {
        const FieldDescriptor *field = desc->field(i);
        if(FieldDescriptor::Type::TYPE_MESSAGE == field->type())
        {
            const Message& field_message = refl->GetMessage(message, field);
            Validate(field_message);
        }
        if(field->options().GetExtension(required))
        {
            const Message& field_message = refl->GetMessage(message, field);
            field_message
            return false;
        }
        fprintf(stderr, "The name of the %i th element is %s and the type is  %s \n",i,field->name().c_str(),field->type_name());

    }
    return true;
}

}
}
