// Copyright (c) [2013-2014] Western Digital Technologies, Inc. All rights reserved.
// source: Settings.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION




#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
#include <string>
#include <algorithm>
#include <utility>
#include "Settings.pb.hpp"
// @@protoc_insertion_point(includes)

namespace kaos {

namespace {

const ::google::protobuf::Descriptor* Settings_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Settings_reflection_ = NULL;
const ::google::protobuf::Descriptor* Settings_ACL_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Settings_ACL_reflection_ = NULL;
const ::google::protobuf::Descriptor* Settings_ACL_Scope_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Settings_ACL_Scope_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Settings_ACL_HmacAlgorithm_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Settings_ACL_Operation_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_Settings_2eproto() {
    protobuf_AddDesc_Settings_2eproto();
    const ::google::protobuf::FileDescriptor* file =
        ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
            "Settings.proto");
    GOOGLE_CHECK(file != NULL);
    Settings_descriptor_ = file->message_type(0);
    static const int Settings_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, clusterversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, lockpin_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, erasepin_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, acl_),
    };
    Settings_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Settings_descriptor_,
        Settings::default_instance_,
        Settings_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Settings));
    Settings_ACL_descriptor_ = Settings_descriptor_->nested_type(0);
    static const int Settings_ACL_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, identity_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, hmackey_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, hmacalgorithm_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, scope_),
    };
    Settings_ACL_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Settings_ACL_descriptor_,
        Settings_ACL::default_instance_,
        Settings_ACL_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Settings_ACL));
    Settings_ACL_Scope_descriptor_ = Settings_ACL_descriptor_->nested_type(0);
    static const int Settings_ACL_Scope_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, tlsrequired_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, keysubstring_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, keysubstringoffset_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, operation_),
    };
    Settings_ACL_Scope_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Settings_ACL_Scope_descriptor_,
        Settings_ACL_Scope::default_instance_,
        Settings_ACL_Scope_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Settings_ACL_Scope, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Settings_ACL_Scope));
    Settings_ACL_HmacAlgorithm_descriptor_ = Settings_ACL_descriptor_->enum_type(0);
    Settings_ACL_Operation_descriptor_ = Settings_ACL_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
    ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                                       &protobuf_AssignDesc_Settings_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Settings_descriptor_, &Settings::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Settings_ACL_descriptor_, &Settings_ACL::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Settings_ACL_Scope_descriptor_, &Settings_ACL_Scope::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Settings_2eproto() {
    delete Settings::default_instance_;
    delete Settings_reflection_;
    delete Settings_ACL::default_instance_;
    delete Settings_ACL_reflection_;
    delete Settings_ACL_Scope::default_instance_;
    delete Settings_ACL_Scope_reflection_;
}

void protobuf_AddDesc_Settings_2eproto() {
    static bool already_here = false;
    if (already_here) return;
    already_here = true;
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
        "\n\016Settings.proto\022\004kaos\"\230\004\n\010Settings\022\026\n\016c"
        "lusterVersion\030\001 \001(\003\022\017\n\007lockPin\030\002 \001(\014\022\020\n\010"
        "erasePin\030\003 \001(\014\022\037\n\003acl\030\004 \003(\0132\022.kaos.Setti"
        "ngs.ACL\032\257\003\n\003ACL\022\020\n\010identity\030\001 \001(\003\022\017\n\007hma"
        "cKey\030\002 \001(\014\0227\n\rhmacAlgorithm\030\003 \001(\0162 .kaos"
        ".Settings.ACL.HmacAlgorithm\022\'\n\005scope\030\004 \003"
        "(\0132\030.kaos.Settings.ACL.Scope\032\177\n\005Scope\022\023\n"
        "\013tlsRequired\030\001 \001(\010\022\024\n\014keySubstring\030\002 \001(\014"
        "\022\032\n\022keySubstringOffset\030\003 \001(\003\022/\n\toperatio"
        "n\030\004 \003(\0162\034.kaos.Settings.ACL.Operation\"9\n"
        "\rHmacAlgorithm\022\031\n\014HMAC_INVALID\020\377\377\377\377\377\377\377\377\377"
        "\001\022\r\n\tHMAC_SHA1\020\001\"g\n\tOperation\022\010\n\004READ\020\000\022"
        "\t\n\005WRITE\020\001\022\n\n\006DELETE\020\002\022\t\n\005RANGE\020\003\022\t\n\005SET"
        "UP\020\004\022\t\n\005P2POP\020\005\022\n\n\006GETLOG\020\007\022\014\n\010SECURITY\020"
        "\010", 561);
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
        "Settings.proto", &protobuf_RegisterTypes);
    Settings::default_instance_ = new Settings();
    Settings_ACL::default_instance_ = new Settings_ACL();
    Settings_ACL_Scope::default_instance_ = new Settings_ACL_Scope();
    Settings::default_instance_->InitAsDefaultInstance();
    Settings_ACL::default_instance_->InitAsDefaultInstance();
    Settings_ACL_Scope::default_instance_->InitAsDefaultInstance();
    ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Settings_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Settings_2eproto {
    StaticDescriptorInitializer_Settings_2eproto() {
        protobuf_AddDesc_Settings_2eproto();
    }
} static_descriptor_initializer_Settings_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* Settings_ACL_HmacAlgorithm_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Settings_ACL_HmacAlgorithm_descriptor_;
}
bool Settings_ACL_HmacAlgorithm_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Settings_ACL_HmacAlgorithm Settings_ACL::HMAC_INVALID;
const Settings_ACL_HmacAlgorithm Settings_ACL::HMAC_SHA1;
const Settings_ACL_HmacAlgorithm Settings_ACL::HmacAlgorithm_MIN;
const Settings_ACL_HmacAlgorithm Settings_ACL::HmacAlgorithm_MAX;
const int Settings_ACL::HmacAlgorithm_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Settings_ACL_Operation_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Settings_ACL_Operation_descriptor_;
}
bool Settings_ACL_Operation_IsValid(int value) {
    switch (value) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 7:
        case 8:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Settings_ACL_Operation Settings_ACL::READ;
const Settings_ACL_Operation Settings_ACL::WRITE;
const Settings_ACL_Operation Settings_ACL::DELETE;
const Settings_ACL_Operation Settings_ACL::RANGE;
const Settings_ACL_Operation Settings_ACL::SETUP;
const Settings_ACL_Operation Settings_ACL::P2POP;
const Settings_ACL_Operation Settings_ACL::GETLOG;
const Settings_ACL_Operation Settings_ACL::SECURITY;
const Settings_ACL_Operation Settings_ACL::Operation_MIN;
const Settings_ACL_Operation Settings_ACL::Operation_MAX;
const int Settings_ACL::Operation_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Settings_ACL_Scope::kTlsRequiredFieldNumber;
const int Settings_ACL_Scope::kKeySubstringFieldNumber;
const int Settings_ACL_Scope::kKeySubstringOffsetFieldNumber;
const int Settings_ACL_Scope::kOperationFieldNumber;
#endif  // !_MSC_VER

Settings_ACL_Scope::Settings_ACL_Scope()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:kaos.Settings.ACL.Scope)
}

void Settings_ACL_Scope::InitAsDefaultInstance() {
}

Settings_ACL_Scope::Settings_ACL_Scope(const Settings_ACL_Scope& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:kaos.Settings.ACL.Scope)
}

void Settings_ACL_Scope::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    tlsrequired_ = false;
    keysubstring_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    keysubstringoffset_ = GOOGLE_LONGLONG(0);
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Settings_ACL_Scope::~Settings_ACL_Scope() {
    // @@protoc_insertion_point(destructor:kaos.Settings.ACL.Scope)
    SharedDtor();
}

void Settings_ACL_Scope::SharedDtor() {
    if (keysubstring_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete keysubstring_;
    }
    if (this != default_instance_) {
    }
}

void Settings_ACL_Scope::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Settings_ACL_Scope::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Settings_ACL_Scope_descriptor_;
}

const Settings_ACL_Scope& Settings_ACL_Scope::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Settings_2eproto();
    return *default_instance_;
}

Settings_ACL_Scope* Settings_ACL_Scope::default_instance_ = NULL;

Settings_ACL_Scope* Settings_ACL_Scope::New() const {
    return new Settings_ACL_Scope;
}

void Settings_ACL_Scope::Clear() {
    if (_has_bits_[0 / 32] & 7) {
        tlsrequired_ = false;
        if (has_keysubstring()) {
            if (keysubstring_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                keysubstring_->clear();
            }
        }
        keysubstringoffset_ = GOOGLE_LONGLONG(0);
    }
    operation_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Settings_ACL_Scope::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:kaos.Settings.ACL.Scope)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bool tlsRequired = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &tlsrequired_)));
                    set_has_tlsrequired();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_keySubstring;
                break;
            }

            // optional bytes keySubstring = 2;
            case 2: {
                if (tag == 18) {
parse_keySubstring:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_keysubstring()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_keySubstringOffset;
                break;
            }

            // optional int64 keySubstringOffset = 3;
            case 3: {
                if (tag == 24) {
parse_keySubstringOffset:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &keysubstringoffset_)));
                    set_has_keysubstringoffset();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_operation;
                break;
            }

            // repeated .kaos.Settings.ACL.Operation operation = 4;
            case 4: {
                if (tag == 32) {
parse_operation:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::kaos::Settings_ACL_Operation_IsValid(value)) {
                        add_operation(static_cast<::kaos::Settings_ACL_Operation>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(4, value);
                    }
                }
                else if (tag == 34) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPackedEnumNoInline(
                             input,
                             &::kaos::Settings_ACL_Operation_IsValid,
                             this->mutable_operation())));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_operation;
                if (input->ExpectAtEnd()) goto success;
                break;
            }

            default: {
handle_unusual:
                if (tag == 0 ||
                        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
                        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
                    goto success;
                }
                DO_(::google::protobuf::internal::WireFormat::SkipField(
                        input, tag, mutable_unknown_fields()));
                break;
            }
        }
    }
success:
    // @@protoc_insertion_point(parse_success:kaos.Settings.ACL.Scope)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:kaos.Settings.ACL.Scope)
    return false;
#undef DO_
}

void Settings_ACL_Scope::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:kaos.Settings.ACL.Scope)
    // optional bool tlsRequired = 1;
    if (has_tlsrequired()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->tlsrequired(), output);
    }

    // optional bytes keySubstring = 2;
    if (has_keysubstring()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->keysubstring(), output);
    }

    // optional int64 keySubstringOffset = 3;
    if (has_keysubstringoffset()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->keysubstringoffset(), output);
    }

    // repeated .kaos.Settings.ACL.Operation operation = 4;
    for (int i = 0; i < this->operation_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            4, this->operation(i), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:kaos.Settings.ACL.Scope)
}

::google::protobuf::uint8* Settings_ACL_Scope::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:kaos.Settings.ACL.Scope)
    // optional bool tlsRequired = 1;
    if (has_tlsrequired()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->tlsrequired(), target);
    }

    // optional bytes keySubstring = 2;
    if (has_keysubstring()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->keysubstring(), target);
    }

    // optional int64 keySubstringOffset = 3;
    if (has_keysubstringoffset()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->keysubstringoffset(), target);
    }

    // repeated .kaos.Settings.ACL.Operation operation = 4;
    for (int i = 0; i < this->operation_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     4, this->operation(i), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:kaos.Settings.ACL.Scope)
    return target;
}

int Settings_ACL_Scope::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bool tlsRequired = 1;
        if (has_tlsrequired()) {
            total_size += 1 + 1;
        }

        // optional bytes keySubstring = 2;
        if (has_keysubstring()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->keysubstring());
        }

        // optional int64 keySubstringOffset = 3;
        if (has_keysubstringoffset()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->keysubstringoffset());
        }

    }
    // repeated .kaos.Settings.ACL.Operation operation = 4;
    {
        int data_size = 0;
        for (int i = 0; i < this->operation_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
                             this->operation(i));
        }
        total_size += 1 * this->operation_size() + data_size;
    }

    if (!unknown_fields().empty()) {
        total_size +=
            ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
                unknown_fields());
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = total_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    return total_size;
}

void Settings_ACL_Scope::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Settings_ACL_Scope* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Settings_ACL_Scope*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Settings_ACL_Scope::MergeFrom(const Settings_ACL_Scope& from) {
    GOOGLE_CHECK_NE(&from, this);
    operation_.MergeFrom(from.operation_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_tlsrequired()) {
            set_tlsrequired(from.tlsrequired());
        }
        if (from.has_keysubstring()) {
            set_keysubstring(from.keysubstring());
        }
        if (from.has_keysubstringoffset()) {
            set_keysubstringoffset(from.keysubstringoffset());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Settings_ACL_Scope::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Settings_ACL_Scope::CopyFrom(const Settings_ACL_Scope& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Settings_ACL_Scope::IsInitialized() const {

    return true;
}

void Settings_ACL_Scope::Swap(Settings_ACL_Scope* other) {
    if (other != this) {
        std::swap(tlsrequired_, other->tlsrequired_);
        std::swap(keysubstring_, other->keysubstring_);
        std::swap(keysubstringoffset_, other->keysubstringoffset_);
        operation_.Swap(&other->operation_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Settings_ACL_Scope::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Settings_ACL_Scope_descriptor_;
    metadata.reflection = Settings_ACL_Scope_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Settings_ACL::kIdentityFieldNumber;
const int Settings_ACL::kHmacKeyFieldNumber;
const int Settings_ACL::kHmacAlgorithmFieldNumber;
const int Settings_ACL::kScopeFieldNumber;
#endif  // !_MSC_VER

Settings_ACL::Settings_ACL()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:kaos.Settings.ACL)
}

void Settings_ACL::InitAsDefaultInstance() {
}

Settings_ACL::Settings_ACL(const Settings_ACL& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:kaos.Settings.ACL)
}

void Settings_ACL::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    identity_ = GOOGLE_LONGLONG(0);
    hmackey_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    hmacalgorithm_ = -1;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Settings_ACL::~Settings_ACL() {
    // @@protoc_insertion_point(destructor:kaos.Settings.ACL)
    SharedDtor();
}

void Settings_ACL::SharedDtor() {
    if (hmackey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete hmackey_;
    }
    if (this != default_instance_) {
    }
}

void Settings_ACL::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Settings_ACL::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Settings_ACL_descriptor_;
}

const Settings_ACL& Settings_ACL::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Settings_2eproto();
    return *default_instance_;
}

Settings_ACL* Settings_ACL::default_instance_ = NULL;

Settings_ACL* Settings_ACL::New() const {
    return new Settings_ACL;
}

void Settings_ACL::Clear() {
    if (_has_bits_[0 / 32] & 7) {
        identity_ = GOOGLE_LONGLONG(0);
        if (has_hmackey()) {
            if (hmackey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                hmackey_->clear();
            }
        }
        hmacalgorithm_ = -1;
    }
    scope_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Settings_ACL::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:kaos.Settings.ACL)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional int64 identity = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &identity_)));
                    set_has_identity();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_hmacKey;
                break;
            }

            // optional bytes hmacKey = 2;
            case 2: {
                if (tag == 18) {
parse_hmacKey:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_hmackey()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_hmacAlgorithm;
                break;
            }

            // optional .kaos.Settings.ACL.HmacAlgorithm hmacAlgorithm = 3;
            case 3: {
                if (tag == 24) {
parse_hmacAlgorithm:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::kaos::Settings_ACL_HmacAlgorithm_IsValid(value)) {
                        set_hmacalgorithm(static_cast<::kaos::Settings_ACL_HmacAlgorithm>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(3, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_scope;
                break;
            }

            // repeated .kaos.Settings.ACL.Scope scope = 4;
            case 4: {
                if (tag == 34) {
parse_scope:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_scope()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_scope;
                if (input->ExpectAtEnd()) goto success;
                break;
            }

            default: {
handle_unusual:
                if (tag == 0 ||
                        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
                        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
                    goto success;
                }
                DO_(::google::protobuf::internal::WireFormat::SkipField(
                        input, tag, mutable_unknown_fields()));
                break;
            }
        }
    }
success:
    // @@protoc_insertion_point(parse_success:kaos.Settings.ACL)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:kaos.Settings.ACL)
    return false;
#undef DO_
}

void Settings_ACL::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:kaos.Settings.ACL)
    // optional int64 identity = 1;
    if (has_identity()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->identity(), output);
    }

    // optional bytes hmacKey = 2;
    if (has_hmackey()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->hmackey(), output);
    }

    // optional .kaos.Settings.ACL.HmacAlgorithm hmacAlgorithm = 3;
    if (has_hmacalgorithm()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            3, this->hmacalgorithm(), output);
    }

    // repeated .kaos.Settings.ACL.Scope scope = 4;
    for (int i = 0; i < this->scope_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, this->scope(i), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:kaos.Settings.ACL)
}

::google::protobuf::uint8* Settings_ACL::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:kaos.Settings.ACL)
    // optional int64 identity = 1;
    if (has_identity()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->identity(), target);
    }

    // optional bytes hmacKey = 2;
    if (has_hmackey()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->hmackey(), target);
    }

    // optional .kaos.Settings.ACL.HmacAlgorithm hmacAlgorithm = 3;
    if (has_hmacalgorithm()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     3, this->hmacalgorithm(), target);
    }

    // repeated .kaos.Settings.ACL.Scope scope = 4;
    for (int i = 0; i < this->scope_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     4, this->scope(i), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:kaos.Settings.ACL)
    return target;
}

int Settings_ACL::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 identity = 1;
        if (has_identity()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->identity());
        }

        // optional bytes hmacKey = 2;
        if (has_hmackey()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->hmackey());
        }

        // optional .kaos.Settings.ACL.HmacAlgorithm hmacAlgorithm = 3;
        if (has_hmacalgorithm()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->hmacalgorithm());
        }

    }
    // repeated .kaos.Settings.ACL.Scope scope = 4;
    total_size += 1 * this->scope_size();
    for (int i = 0; i < this->scope_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->scope(i));
    }

    if (!unknown_fields().empty()) {
        total_size +=
            ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
                unknown_fields());
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = total_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    return total_size;
}

void Settings_ACL::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Settings_ACL* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Settings_ACL*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Settings_ACL::MergeFrom(const Settings_ACL& from) {
    GOOGLE_CHECK_NE(&from, this);
    scope_.MergeFrom(from.scope_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_identity()) {
            set_identity(from.identity());
        }
        if (from.has_hmackey()) {
            set_hmackey(from.hmackey());
        }
        if (from.has_hmacalgorithm()) {
            set_hmacalgorithm(from.hmacalgorithm());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Settings_ACL::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Settings_ACL::CopyFrom(const Settings_ACL& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Settings_ACL::IsInitialized() const {

    return true;
}

void Settings_ACL::Swap(Settings_ACL* other) {
    if (other != this) {
        std::swap(identity_, other->identity_);
        std::swap(hmackey_, other->hmackey_);
        std::swap(hmacalgorithm_, other->hmacalgorithm_);
        scope_.Swap(&other->scope_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Settings_ACL::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Settings_ACL_descriptor_;
    metadata.reflection = Settings_ACL_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Settings::kClusterVersionFieldNumber;
const int Settings::kLockPinFieldNumber;
const int Settings::kErasePinFieldNumber;
const int Settings::kAclFieldNumber;
#endif  // !_MSC_VER

Settings::Settings()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:kaos.Settings)
}

void Settings::InitAsDefaultInstance() {
}

Settings::Settings(const Settings& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:kaos.Settings)
}

void Settings::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    clusterversion_ = GOOGLE_LONGLONG(0);
    lockpin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    erasepin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Settings::~Settings() {
    // @@protoc_insertion_point(destructor:kaos.Settings)
    SharedDtor();
}

void Settings::SharedDtor() {
    if (lockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete lockpin_;
    }
    if (erasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete erasepin_;
    }
    if (this != default_instance_) {
    }
}

void Settings::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Settings::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Settings_descriptor_;
}

const Settings& Settings::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Settings_2eproto();
    return *default_instance_;
}

Settings* Settings::default_instance_ = NULL;

Settings* Settings::New() const {
    return new Settings;
}

void Settings::Clear() {
    if (_has_bits_[0 / 32] & 7) {
        clusterversion_ = GOOGLE_LONGLONG(0);
        if (has_lockpin()) {
            if (lockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                lockpin_->clear();
            }
        }
        if (has_erasepin()) {
            if (erasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                erasepin_->clear();
            }
        }
    }
    acl_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Settings::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:kaos.Settings)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional int64 clusterVersion = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &clusterversion_)));
                    set_has_clusterversion();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_lockPin;
                break;
            }

            // optional bytes lockPin = 2;
            case 2: {
                if (tag == 18) {
parse_lockPin:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_lockpin()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_erasePin;
                break;
            }

            // optional bytes erasePin = 3;
            case 3: {
                if (tag == 26) {
parse_erasePin:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_erasepin()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_acl;
                break;
            }

            // repeated .kaos.Settings.ACL acl = 4;
            case 4: {
                if (tag == 34) {
parse_acl:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_acl()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_acl;
                if (input->ExpectAtEnd()) goto success;
                break;
            }

            default: {
handle_unusual:
                if (tag == 0 ||
                        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
                        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
                    goto success;
                }
                DO_(::google::protobuf::internal::WireFormat::SkipField(
                        input, tag, mutable_unknown_fields()));
                break;
            }
        }
    }
success:
    // @@protoc_insertion_point(parse_success:kaos.Settings)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:kaos.Settings)
    return false;
#undef DO_
}

void Settings::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:kaos.Settings)
    // optional int64 clusterVersion = 1;
    if (has_clusterversion()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->clusterversion(), output);
    }

    // optional bytes lockPin = 2;
    if (has_lockpin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->lockpin(), output);
    }

    // optional bytes erasePin = 3;
    if (has_erasepin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->erasepin(), output);
    }

    // repeated .kaos.Settings.ACL acl = 4;
    for (int i = 0; i < this->acl_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, this->acl(i), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:kaos.Settings)
}

::google::protobuf::uint8* Settings::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:kaos.Settings)
    // optional int64 clusterVersion = 1;
    if (has_clusterversion()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->clusterversion(), target);
    }

    // optional bytes lockPin = 2;
    if (has_lockpin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->lockpin(), target);
    }

    // optional bytes erasePin = 3;
    if (has_erasepin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->erasepin(), target);
    }

    // repeated .kaos.Settings.ACL acl = 4;
    for (int i = 0; i < this->acl_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     4, this->acl(i), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:kaos.Settings)
    return target;
}

int Settings::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 clusterVersion = 1;
        if (has_clusterversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->clusterversion());
        }

        // optional bytes lockPin = 2;
        if (has_lockpin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->lockpin());
        }

        // optional bytes erasePin = 3;
        if (has_erasepin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->erasepin());
        }

    }
    // repeated .kaos.Settings.ACL acl = 4;
    total_size += 1 * this->acl_size();
    for (int i = 0; i < this->acl_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->acl(i));
    }

    if (!unknown_fields().empty()) {
        total_size +=
            ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
                unknown_fields());
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = total_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    return total_size;
}

void Settings::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Settings* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Settings*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Settings::MergeFrom(const Settings& from) {
    GOOGLE_CHECK_NE(&from, this);
    acl_.MergeFrom(from.acl_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_clusterversion()) {
            set_clusterversion(from.clusterversion());
        }
        if (from.has_lockpin()) {
            set_lockpin(from.lockpin());
        }
        if (from.has_erasepin()) {
            set_erasepin(from.erasepin());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Settings::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Settings::CopyFrom(const Settings& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Settings::IsInitialized() const {

    return true;
}

void Settings::Swap(Settings* other) {
    if (other != this) {
        std::swap(clusterversion_, other->clusterversion_);
        std::swap(lockpin_, other->lockpin_);
        std::swap(erasepin_, other->erasepin_);
        acl_.Swap(&other->acl_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Settings::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Settings_descriptor_;
    metadata.reflection = Settings_reflection_;
    return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace kaos

// @@protoc_insertion_point(global_scope)
