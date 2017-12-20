
set(spine_proto_files
        spine/ui/color.proto
        spine/ui/language.proto
        spine/validate/constraint_violation.proto
        spine/validate/validation_error.proto
        spine/change/change.proto
        spine/change/value_mismatch.proto
        spine/net/email_address.proto
        spine/net/url.proto
        spine/net/internet_domain.proto
        spine/core/response.proto
        spine/core/tenant_id.proto
        spine/core/user_id.proto
        spine/core/actor_context.proto
        spine/core/bounded_context.proto
        spine/core/ack.proto
        spine/core/event.proto
        spine/core/version.proto
        spine/core/command.proto
        spine/core/enrichment.proto
        spine/core/rejection.proto
        spine/time/zone.proto
        spine/time/time.proto
        spine/options.proto
        spine/people/person_name.proto
        spine/client/subscription.proto
        spine/client/query_service.proto
        spine/client/query.proto
        spine/client/entities.proto
        spine/client/subscription_service.proto
        spine/client/command_service.proto
        spine/base/field_path.proto
        spine/base/field_filter.proto
        spine/base/error.proto
        google/protobuf/timestamp.proto
        google/protobuf/field_mask.proto
        google/protobuf/api.proto
        google/protobuf/duration.proto
        google/protobuf/struct.proto
        google/protobuf/wrappers.proto
        google/protobuf/source_context.proto
        google/protobuf/any.proto
        google/protobuf/type.proto
        google/protobuf/empty.proto
        google/protobuf/compiler/plugin.proto
        google/protobuf/descriptor.proto
        )

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(PROTO_DIR ${CMAKE_HOME_DIRECTORY}/dependencies/spine)

set(PROTOC_EXE ${GRPC_INSTALL_DIR}/bin/protoc)
macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)
    add_custom_command(
            OUTPUT ${GENERATED_DIR}/${dirname}/${basename}.pb.cc
            DEPENDS ${PROTOC_EXE} ${PROTO_DIR}/${dirname}/${basename}.proto
            COMMAND ${PROTOC_EXE} ${PROTO_DIR}/${dirname}/${basename}.proto
            --proto_path=${GENERATED_DIR}
            --cpp_out=${GENERATED_DIR}
            --grpc_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${GRPC_INSTALL_DIR}/bin/grpc_cpp_plugin
            -I ${PROTO_DIR}
            VERBATIM
    )
endmacro(compile_proto_file)

set(spine_generated_files)
foreach(proto_file ${spine_proto_files})
    compile_proto_file(${proto_file})
    string(REPLACE .proto .pb.cc pb_file ${proto_file})
    set(spine_generated_files ${spine_generated_files}
            ${GENERATED_DIR}/${pb_file})
endforeach(proto_file)
