// Copyright (c) [2013-2014] Western Digital Technologies, Inc. All rights reserved.
// source: Entry.proto

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
#include "Entry.pb.hpp"
// @@protoc_insertion_point(includes)

namespace kaos {

namespace {

const ::google::protobuf::Descriptor* Entry_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Entry_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Entry_2eproto() {
  protobuf_AddDesc_Entry_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Entry.proto");
  GOOGLE_CHECK(file != NULL);
  Entry_descriptor_ = file->message_type(0);
  static const int Entry_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, value_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, version_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, tag_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, algorithm_),
  };
  Entry_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Entry_descriptor_,
      Entry::default_instance_,
      Entry_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Entry, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Entry));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Entry_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Entry_descriptor_, &Entry::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Entry_2eproto() {
  delete Entry::default_instance_;
  delete Entry_reflection_;
}

void protobuf_AddDesc_Entry_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::com::seagate::kinetic::proto::protobuf_AddDesc_Kinetic_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013Entry.proto\022\004kaos\032\rKinetic.proto\"\202\001\n\005E"
    "ntry\022\013\n\003key\030\001 \002(\014\022\r\n\005value\030\002 \002(\014\022\017\n\007vers"
    "ion\030\003 \002(\014\022\013\n\003tag\030\004 \002(\014\022\?\n\talgorithm\030\005 \001("
    "\0162,.com.seagate.kinetic.proto.Command.Al"
    "gorithm", 167);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Entry.proto", &protobuf_RegisterTypes);
  Entry::default_instance_ = new Entry();
  Entry::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Entry_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Entry_2eproto {
  StaticDescriptorInitializer_Entry_2eproto() {
    protobuf_AddDesc_Entry_2eproto();
  }
} static_descriptor_initializer_Entry_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Entry::kKeyFieldNumber;
const int Entry::kValueFieldNumber;
const int Entry::kVersionFieldNumber;
const int Entry::kTagFieldNumber;
const int Entry::kAlgorithmFieldNumber;
#endif  // !_MSC_VER

Entry::Entry()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:kaos.Entry)
}

void Entry::InitAsDefaultInstance() {
}

Entry::Entry(const Entry& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:kaos.Entry)
}

void Entry::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  value_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  version_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  tag_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  algorithm_ = -1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Entry::~Entry() {
  // @@protoc_insertion_point(destructor:kaos.Entry)
  SharedDtor();
}

void Entry::SharedDtor() {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete key_;
  }
  if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete value_;
  }
  if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete version_;
  }
  if (tag_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete tag_;
  }
  if (this != default_instance_) {
  }
}

void Entry::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Entry::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Entry_descriptor_;
}

const Entry& Entry::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Entry_2eproto();
  return *default_instance_;
}

Entry* Entry::default_instance_ = NULL;

Entry* Entry::New() const {
  return new Entry;
}

void Entry::Clear() {
  if (_has_bits_[0 / 32] & 31) {
    if (has_key()) {
      if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        key_->clear();
      }
    }
    if (has_value()) {
      if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        value_->clear();
      }
    }
    if (has_version()) {
      if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        version_->clear();
      }
    }
    if (has_tag()) {
      if (tag_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        tag_->clear();
      }
    }
    algorithm_ = -1;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Entry::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:kaos.Entry)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bytes key = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_key()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_value;
        break;
      }

      // required bytes value = 2;
      case 2: {
        if (tag == 18) {
         parse_value:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_value()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_version;
        break;
      }

      // required bytes version = 3;
      case 3: {
        if (tag == 26) {
         parse_version:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_version()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_tag;
        break;
      }

      // required bytes tag = 4;
      case 4: {
        if (tag == 34) {
         parse_tag:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_tag()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_algorithm;
        break;
      }

      // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 5;
      case 5: {
        if (tag == 40) {
         parse_algorithm:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::com::seagate::kinetic::proto::Command_Algorithm_IsValid(value)) {
            set_algorithm(static_cast< ::com::seagate::kinetic::proto::Command_Algorithm >(value));
          } else {
            mutable_unknown_fields()->AddVarint(5, value);
          }
        } else {
          goto handle_unusual;
        }
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
  // @@protoc_insertion_point(parse_success:kaos.Entry)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:kaos.Entry)
  return false;
#undef DO_
}

void Entry::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:kaos.Entry)
  // required bytes key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      1, this->key(), output);
  }

  // required bytes value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->value(), output);
  }

  // required bytes version = 3;
  if (has_version()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->version(), output);
  }

  // required bytes tag = 4;
  if (has_tag()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      4, this->tag(), output);
  }

  // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 5;
  if (has_algorithm()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      5, this->algorithm(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:kaos.Entry)
}

::google::protobuf::uint8* Entry::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:kaos.Entry)
  // required bytes key = 1;
  if (has_key()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->key(), target);
  }

  // required bytes value = 2;
  if (has_value()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->value(), target);
  }

  // required bytes version = 3;
  if (has_version()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->version(), target);
  }

  // required bytes tag = 4;
  if (has_tag()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        4, this->tag(), target);
  }

  // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 5;
  if (has_algorithm()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      5, this->algorithm(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:kaos.Entry)
  return target;
}

int Entry::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bytes key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->key());
    }

    // required bytes value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->value());
    }

    // required bytes version = 3;
    if (has_version()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->version());
    }

    // required bytes tag = 4;
    if (has_tag()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->tag());
    }

    // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 5;
    if (has_algorithm()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->algorithm());
    }

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

void Entry::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Entry* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Entry*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Entry::MergeFrom(const Entry& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
    if (from.has_version()) {
      set_version(from.version());
    }
    if (from.has_tag()) {
      set_tag(from.tag());
    }
    if (from.has_algorithm()) {
      set_algorithm(from.algorithm());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Entry::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Entry::CopyFrom(const Entry& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Entry::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void Entry::Swap(Entry* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(value_, other->value_);
    std::swap(version_, other->version_);
    std::swap(tag_, other->tag_);
    std::swap(algorithm_, other->algorithm_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Entry::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Entry_descriptor_;
  metadata.reflection = Entry_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace kaos

// @@protoc_insertion_point(global_scope)
