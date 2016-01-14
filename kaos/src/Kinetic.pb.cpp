// Copyright (c) [2013-2014] Western Digital Technologies, Inc. All rights reserved.
// source: Kinetic.proto

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
#include "Kinetic.pb.hpp"
// @@protoc_insertion_point(includes)

namespace com {
namespace seagate {
namespace kinetic {
namespace proto {

namespace {

const ::google::protobuf::Descriptor* Local_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Local_reflection_ = NULL;
const ::google::protobuf::Descriptor* Message_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Message_reflection_ = NULL;
const ::google::protobuf::Descriptor* Message_HMACauth_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Message_HMACauth_reflection_ = NULL;
const ::google::protobuf::Descriptor* Message_PINauth_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Message_PINauth_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Message_AuthType_descriptor_ = NULL;
const ::google::protobuf::Descriptor* Command_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Header_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Header_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Body_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Body_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Batch_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Batch_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Status_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Status_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Status_StatusCode_descriptor_ = NULL;
const ::google::protobuf::Descriptor* Command_KeyValue_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_KeyValue_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Range_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Range_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Setup_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Setup_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_P2POperation_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_P2POperation_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_P2POperation_Operation_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_P2POperation_Operation_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_P2POperation_Peer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_P2POperation_Peer_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Utilization_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Utilization_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Temperature_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Temperature_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Capacity_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Capacity_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Configuration_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Configuration_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Configuration_Interface_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Configuration_Interface_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Statistics_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Statistics_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Limits_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Limits_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_GetLog_Device_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_GetLog_Device_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_GetLog_Type_descriptor_ = NULL;
const ::google::protobuf::Descriptor* Command_Security_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Security_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Security_ACL_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Security_ACL_reflection_ = NULL;
const ::google::protobuf::Descriptor* Command_Security_ACL_Scope_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_Security_ACL_Scope_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Security_ACL_HMACAlgorithm_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Security_ACL_Permission_descriptor_ = NULL;
const ::google::protobuf::Descriptor* Command_PinOperation_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
Command_PinOperation_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_PinOperation_PinOpType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Synchronization_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Priority_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_Algorithm_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Command_MessageType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_Kinetic_2eproto() {
    protobuf_AddDesc_Kinetic_2eproto();
    const ::google::protobuf::FileDescriptor* file =
        ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
            "Kinetic.proto");
    GOOGLE_CHECK(file != NULL);
    Local_descriptor_ = file->message_type(0);
    static const int Local_offsets_[1] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Local, protocolversion_),
    };
    Local_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Local_descriptor_,
        Local::default_instance_,
        Local_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Local, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Local, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Local));
    Message_descriptor_ = file->message_type(1);
    static const int Message_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, authtype_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, hmacauth_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, pinauth_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, commandbytes_),
    };
    Message_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Message_descriptor_,
        Message::default_instance_,
        Message_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Message));
    Message_HMACauth_descriptor_ = Message_descriptor_->nested_type(0);
    static const int Message_HMACauth_offsets_[2] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_HMACauth, identity_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_HMACauth, hmac_),
    };
    Message_HMACauth_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Message_HMACauth_descriptor_,
        Message_HMACauth::default_instance_,
        Message_HMACauth_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_HMACauth, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_HMACauth, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Message_HMACauth));
    Message_PINauth_descriptor_ = Message_descriptor_->nested_type(1);
    static const int Message_PINauth_offsets_[1] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_PINauth, pin_),
    };
    Message_PINauth_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Message_PINauth_descriptor_,
        Message_PINauth::default_instance_,
        Message_PINauth_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_PINauth, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message_PINauth, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Message_PINauth));
    Message_AuthType_descriptor_ = Message_descriptor_->enum_type(0);
    Command_descriptor_ = file->message_type(2);
    static const int Command_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, header_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, body_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, status_),
    };
    Command_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_descriptor_,
        Command::default_instance_,
        Command_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command));
    Command_Header_descriptor_ = Command_descriptor_->nested_type(0);
    static const int Command_Header_offsets_[10] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, clusterversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, connectionid_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, sequence_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, acksequence_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, messagetype_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, timeout_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, earlyexit_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, priority_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, timequanta_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, batchid_),
    };
    Command_Header_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Header_descriptor_,
        Command_Header::default_instance_,
        Command_Header_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Header, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Header));
    Command_Body_descriptor_ = Command_descriptor_->nested_type(1);
    static const int Command_Body_offsets_[8] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, keyvalue_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, range_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, setup_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, p2poperation_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, getlog_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, security_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, pinop_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, batch_),
    };
    Command_Body_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Body_descriptor_,
        Command_Body::default_instance_,
        Command_Body_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Body, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Body));
    Command_Batch_descriptor_ = Command_descriptor_->nested_type(2);
    static const int Command_Batch_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Batch, count_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Batch, sequence_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Batch, failedsequence_),
    };
    Command_Batch_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Batch_descriptor_,
        Command_Batch::default_instance_,
        Command_Batch_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Batch, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Batch, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Batch));
    Command_Status_descriptor_ = Command_descriptor_->nested_type(3);
    static const int Command_Status_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Status, code_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Status, statusmessage_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Status, detailedmessage_),
    };
    Command_Status_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Status_descriptor_,
        Command_Status::default_instance_,
        Command_Status_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Status, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Status, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Status));
    Command_Status_StatusCode_descriptor_ = Command_Status_descriptor_->enum_type(0);
    Command_KeyValue_descriptor_ = Command_descriptor_->nested_type(4);
    static const int Command_KeyValue_offsets_[8] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, newversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, force_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, key_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, dbversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, tag_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, algorithm_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, metadataonly_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, synchronization_),
    };
    Command_KeyValue_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_KeyValue_descriptor_,
        Command_KeyValue::default_instance_,
        Command_KeyValue_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_KeyValue, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_KeyValue));
    Command_Range_descriptor_ = Command_descriptor_->nested_type(5);
    static const int Command_Range_offsets_[7] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, startkey_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, endkey_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, startkeyinclusive_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, endkeyinclusive_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, maxreturned_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, reverse_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, keys_),
    };
    Command_Range_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Range_descriptor_,
        Command_Range::default_instance_,
        Command_Range_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Range, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Range));
    Command_Setup_descriptor_ = Command_descriptor_->nested_type(6);
    static const int Command_Setup_offsets_[2] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Setup, newclusterversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Setup, firmwaredownload_),
    };
    Command_Setup_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Setup_descriptor_,
        Command_Setup::default_instance_,
        Command_Setup_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Setup, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Setup, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Setup));
    Command_P2POperation_descriptor_ = Command_descriptor_->nested_type(7);
    static const int Command_P2POperation_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation, peer_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation, operation_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation, allchildoperationssucceeded_),
    };
    Command_P2POperation_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_P2POperation_descriptor_,
        Command_P2POperation::default_instance_,
        Command_P2POperation_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_P2POperation));
    Command_P2POperation_Operation_descriptor_ = Command_P2POperation_descriptor_->nested_type(0);
    static const int Command_P2POperation_Operation_offsets_[6] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, key_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, version_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, newkey_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, force_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, status_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, p2pop_),
    };
    Command_P2POperation_Operation_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_P2POperation_Operation_descriptor_,
        Command_P2POperation_Operation::default_instance_,
        Command_P2POperation_Operation_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Operation, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_P2POperation_Operation));
    Command_P2POperation_Peer_descriptor_ = Command_P2POperation_descriptor_->nested_type(1);
    static const int Command_P2POperation_Peer_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Peer, hostname_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Peer, port_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Peer, tls_),
    };
    Command_P2POperation_Peer_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_P2POperation_Peer_descriptor_,
        Command_P2POperation_Peer::default_instance_,
        Command_P2POperation_Peer_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Peer, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_P2POperation_Peer, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_P2POperation_Peer));
    Command_GetLog_descriptor_ = Command_descriptor_->nested_type(8);
    static const int Command_GetLog_offsets_[9] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, types_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, utilizations_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, temperatures_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, capacity_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, configuration_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, statistics_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, messages_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, limits_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, device_),
    };
    Command_GetLog_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_descriptor_,
        Command_GetLog::default_instance_,
        Command_GetLog_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog));
    Command_GetLog_Utilization_descriptor_ = Command_GetLog_descriptor_->nested_type(0);
    static const int Command_GetLog_Utilization_offsets_[2] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Utilization, name_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Utilization, value_),
    };
    Command_GetLog_Utilization_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Utilization_descriptor_,
        Command_GetLog_Utilization::default_instance_,
        Command_GetLog_Utilization_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Utilization, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Utilization, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Utilization));
    Command_GetLog_Temperature_descriptor_ = Command_GetLog_descriptor_->nested_type(1);
    static const int Command_GetLog_Temperature_offsets_[5] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, name_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, current_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, minimum_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, maximum_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, target_),
    };
    Command_GetLog_Temperature_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Temperature_descriptor_,
        Command_GetLog_Temperature::default_instance_,
        Command_GetLog_Temperature_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Temperature, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Temperature));
    Command_GetLog_Capacity_descriptor_ = Command_GetLog_descriptor_->nested_type(2);
    static const int Command_GetLog_Capacity_offsets_[2] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Capacity, nominalcapacityinbytes_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Capacity, portionfull_),
    };
    Command_GetLog_Capacity_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Capacity_descriptor_,
        Command_GetLog_Capacity::default_instance_,
        Command_GetLog_Capacity_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Capacity, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Capacity, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Capacity));
    Command_GetLog_Configuration_descriptor_ = Command_GetLog_descriptor_->nested_type(3);
    static const int Command_GetLog_Configuration_offsets_[13] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, vendor_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, model_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, serialnumber_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, worldwidename_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, version_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, compilationdate_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, sourcehash_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, protocolversion_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, protocolcompilationdate_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, protocolsourcehash_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, interface_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, port_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, tlsport_),
    };
    Command_GetLog_Configuration_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Configuration_descriptor_,
        Command_GetLog_Configuration::default_instance_,
        Command_GetLog_Configuration_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Configuration));
    Command_GetLog_Configuration_Interface_descriptor_ = Command_GetLog_Configuration_descriptor_->nested_type(0);
    static const int Command_GetLog_Configuration_Interface_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, name_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, mac_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, ipv4address_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, ipv6address_),
    };
    Command_GetLog_Configuration_Interface_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Configuration_Interface_descriptor_,
        Command_GetLog_Configuration_Interface::default_instance_,
        Command_GetLog_Configuration_Interface_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Configuration_Interface, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Configuration_Interface));
    Command_GetLog_Statistics_descriptor_ = Command_GetLog_descriptor_->nested_type(4);
    static const int Command_GetLog_Statistics_offsets_[3] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Statistics, messagetype_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Statistics, count_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Statistics, bytes_),
    };
    Command_GetLog_Statistics_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Statistics_descriptor_,
        Command_GetLog_Statistics::default_instance_,
        Command_GetLog_Statistics_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Statistics, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Statistics, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Statistics));
    Command_GetLog_Limits_descriptor_ = Command_GetLog_descriptor_->nested_type(5);
    static const int Command_GetLog_Limits_offsets_[13] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxkeysize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxvaluesize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxversionsize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxtagsize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxconnections_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxoutstandingreadrequests_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxoutstandingwriterequests_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxmessagesize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxkeyrangecount_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxidentitycount_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxpinsize_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxoperationcountperbatch_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, maxbatchcountperdevice_),
    };
    Command_GetLog_Limits_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Limits_descriptor_,
        Command_GetLog_Limits::default_instance_,
        Command_GetLog_Limits_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Limits, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Limits));
    Command_GetLog_Device_descriptor_ = Command_GetLog_descriptor_->nested_type(6);
    static const int Command_GetLog_Device_offsets_[1] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Device, name_),
    };
    Command_GetLog_Device_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_GetLog_Device_descriptor_,
        Command_GetLog_Device::default_instance_,
        Command_GetLog_Device_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Device, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_GetLog_Device, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_GetLog_Device));
    Command_GetLog_Type_descriptor_ = Command_GetLog_descriptor_->enum_type(0);
    Command_Security_descriptor_ = Command_descriptor_->nested_type(9);
    static const int Command_Security_offsets_[5] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, acl_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, oldlockpin_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, newlockpin_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, olderasepin_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, newerasepin_),
    };
    Command_Security_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Security_descriptor_,
        Command_Security::default_instance_,
        Command_Security_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Security));
    Command_Security_ACL_descriptor_ = Command_Security_descriptor_->nested_type(0);
    static const int Command_Security_ACL_offsets_[5] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, identity_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, key_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, hmacalgorithm_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, scope_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, maxpriority_),
    };
    Command_Security_ACL_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Security_ACL_descriptor_,
        Command_Security_ACL::default_instance_,
        Command_Security_ACL_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Security_ACL));
    Command_Security_ACL_Scope_descriptor_ = Command_Security_ACL_descriptor_->nested_type(0);
    static const int Command_Security_ACL_Scope_offsets_[4] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, offset_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, value_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, permission_),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, tlsrequired_),
    };
    Command_Security_ACL_Scope_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_Security_ACL_Scope_descriptor_,
        Command_Security_ACL_Scope::default_instance_,
        Command_Security_ACL_Scope_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_Security_ACL_Scope, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_Security_ACL_Scope));
    Command_Security_ACL_HMACAlgorithm_descriptor_ = Command_Security_ACL_descriptor_->enum_type(0);
    Command_Security_ACL_Permission_descriptor_ = Command_Security_ACL_descriptor_->enum_type(1);
    Command_PinOperation_descriptor_ = Command_descriptor_->nested_type(10);
    static const int Command_PinOperation_offsets_[1] = {
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_PinOperation, pinoptype_),
    };
    Command_PinOperation_reflection_ =
        new ::google::protobuf::internal::GeneratedMessageReflection(
        Command_PinOperation_descriptor_,
        Command_PinOperation::default_instance_,
        Command_PinOperation_offsets_,
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_PinOperation, _has_bits_[0]),
        GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Command_PinOperation, _unknown_fields_),
        -1,
        ::google::protobuf::DescriptorPool::generated_pool(),
        ::google::protobuf::MessageFactory::generated_factory(),
        sizeof(Command_PinOperation));
    Command_PinOperation_PinOpType_descriptor_ = Command_PinOperation_descriptor_->enum_type(0);
    Command_Synchronization_descriptor_ = Command_descriptor_->enum_type(0);
    Command_Priority_descriptor_ = Command_descriptor_->enum_type(1);
    Command_Algorithm_descriptor_ = Command_descriptor_->enum_type(2);
    Command_MessageType_descriptor_ = Command_descriptor_->enum_type(3);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
    ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                                       &protobuf_AssignDesc_Kinetic_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Local_descriptor_, &Local::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Message_descriptor_, &Message::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Message_HMACauth_descriptor_, &Message_HMACauth::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Message_PINauth_descriptor_, &Message_PINauth::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_descriptor_, &Command::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Header_descriptor_, &Command_Header::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Body_descriptor_, &Command_Body::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Batch_descriptor_, &Command_Batch::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Status_descriptor_, &Command_Status::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_KeyValue_descriptor_, &Command_KeyValue::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Range_descriptor_, &Command_Range::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Setup_descriptor_, &Command_Setup::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_P2POperation_descriptor_, &Command_P2POperation::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_P2POperation_Operation_descriptor_, &Command_P2POperation_Operation::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_P2POperation_Peer_descriptor_, &Command_P2POperation_Peer::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_descriptor_, &Command_GetLog::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Utilization_descriptor_, &Command_GetLog_Utilization::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Temperature_descriptor_, &Command_GetLog_Temperature::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Capacity_descriptor_, &Command_GetLog_Capacity::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Configuration_descriptor_, &Command_GetLog_Configuration::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Configuration_Interface_descriptor_, &Command_GetLog_Configuration_Interface::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Statistics_descriptor_, &Command_GetLog_Statistics::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Limits_descriptor_, &Command_GetLog_Limits::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_GetLog_Device_descriptor_, &Command_GetLog_Device::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Security_descriptor_, &Command_Security::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Security_ACL_descriptor_, &Command_Security_ACL::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_Security_ACL_Scope_descriptor_, &Command_Security_ACL_Scope::default_instance());
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
        Command_PinOperation_descriptor_, &Command_PinOperation::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Kinetic_2eproto() {
    delete Local::default_instance_;
    delete Local_reflection_;
    delete Local::_default_protocolversion_;
    delete Message::default_instance_;
    delete Message_reflection_;
    delete Message_HMACauth::default_instance_;
    delete Message_HMACauth_reflection_;
    delete Message_PINauth::default_instance_;
    delete Message_PINauth_reflection_;
    delete Command::default_instance_;
    delete Command_reflection_;
    delete Command_Header::default_instance_;
    delete Command_Header_reflection_;
    delete Command_Body::default_instance_;
    delete Command_Body_reflection_;
    delete Command_Batch::default_instance_;
    delete Command_Batch_reflection_;
    delete Command_Status::default_instance_;
    delete Command_Status_reflection_;
    delete Command_KeyValue::default_instance_;
    delete Command_KeyValue_reflection_;
    delete Command_Range::default_instance_;
    delete Command_Range_reflection_;
    delete Command_Setup::default_instance_;
    delete Command_Setup_reflection_;
    delete Command_P2POperation::default_instance_;
    delete Command_P2POperation_reflection_;
    delete Command_P2POperation_Operation::default_instance_;
    delete Command_P2POperation_Operation_reflection_;
    delete Command_P2POperation_Peer::default_instance_;
    delete Command_P2POperation_Peer_reflection_;
    delete Command_GetLog::default_instance_;
    delete Command_GetLog_reflection_;
    delete Command_GetLog_Utilization::default_instance_;
    delete Command_GetLog_Utilization_reflection_;
    delete Command_GetLog_Temperature::default_instance_;
    delete Command_GetLog_Temperature_reflection_;
    delete Command_GetLog_Capacity::default_instance_;
    delete Command_GetLog_Capacity_reflection_;
    delete Command_GetLog_Configuration::default_instance_;
    delete Command_GetLog_Configuration_reflection_;
    delete Command_GetLog_Configuration_Interface::default_instance_;
    delete Command_GetLog_Configuration_Interface_reflection_;
    delete Command_GetLog_Statistics::default_instance_;
    delete Command_GetLog_Statistics_reflection_;
    delete Command_GetLog_Limits::default_instance_;
    delete Command_GetLog_Limits_reflection_;
    delete Command_GetLog_Device::default_instance_;
    delete Command_GetLog_Device_reflection_;
    delete Command_Security::default_instance_;
    delete Command_Security_reflection_;
    delete Command_Security_ACL::default_instance_;
    delete Command_Security_ACL_reflection_;
    delete Command_Security_ACL_Scope::default_instance_;
    delete Command_Security_ACL_Scope_reflection_;
    delete Command_PinOperation::default_instance_;
    delete Command_PinOperation_reflection_;
}

void protobuf_AddDesc_Kinetic_2eproto() {
    static bool already_here = false;
    if (already_here) return;
    already_here = true;
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
        "\n\rKinetic.proto\022\031com.seagate.kinetic.pro"
        "to\"\'\n\005Local\022\036\n\017protocolVersion\030\001 \001(\t:\0053."
        "0.6\"\374\002\n\007Message\022=\n\010authType\030\004 \001(\0162+.com."
        "seagate.kinetic.proto.Message.AuthType\022="
        "\n\010hmacAuth\030\005 \001(\0132+.com.seagate.kinetic.p"
        "roto.Message.HMACauth\022;\n\007pinAuth\030\006 \001(\0132*"
        ".com.seagate.kinetic.proto.Message.PINau"
        "th\022\024\n\014commandBytes\030\007 \001(\014\032*\n\010HMACauth\022\020\n\010"
        "identity\030\001 \001(\003\022\014\n\004hmac\030\002 \001(\014\032\026\n\007PINauth\022"
        "\013\n\003pin\030\001 \001(\014\"\\\n\010AuthType\022\036\n\021INVALID_AUTH"
        "_TYPE\020\377\377\377\377\377\377\377\377\377\001\022\014\n\010HMACAUTH\020\001\022\013\n\007PINAUT"
        "H\020\002\022\025\n\021UNSOLICITEDSTATUS\020\003\"\3632\n\007Command\0229"
        "\n\006header\030\001 \001(\0132).com.seagate.kinetic.pro"
        "to.Command.Header\0225\n\004body\030\002 \001(\0132\'.com.se"
        "agate.kinetic.proto.Command.Body\0229\n\006stat"
        "us\030\003 \001(\0132).com.seagate.kinetic.proto.Com"
        "mand.Status\032\252\002\n\006Header\022\026\n\016clusterVersion"
        "\030\001 \001(\003\022\024\n\014connectionID\030\003 \001(\003\022\020\n\010sequence"
        "\030\004 \001(\003\022\023\n\013ackSequence\030\006 \001(\003\022C\n\013messageTy"
        "pe\030\007 \001(\0162..com.seagate.kinetic.proto.Com"
        "mand.MessageType\022\017\n\007timeout\030\t \001(\003\022\021\n\tear"
        "lyExit\030\n \001(\010\022=\n\010priority\030\014 \001(\0162+.com.sea"
        "gate.kinetic.proto.Command.Priority\022\022\n\nT"
        "imeQuanta\030\r \001(\003\022\017\n\007batchID\030\016 \001(\r\032\361\003\n\004Bod"
        "y\022=\n\010keyValue\030\001 \001(\0132+.com.seagate.kineti"
        "c.proto.Command.KeyValue\0227\n\005range\030\002 \001(\0132"
        "(.com.seagate.kinetic.proto.Command.Rang"
        "e\0227\n\005setup\030\003 \001(\0132(.com.seagate.kinetic.p"
        "roto.Command.Setup\022E\n\014p2pOperation\030\004 \001(\013"
        "2/.com.seagate.kinetic.proto.Command.P2P"
        "Operation\0229\n\006getLog\030\006 \001(\0132).com.seagate."
        "kinetic.proto.Command.GetLog\022=\n\010security"
        "\030\007 \001(\0132+.com.seagate.kinetic.proto.Comma"
        "nd.Security\022>\n\005pinOp\030\010 \001(\0132/.com.seagate"
        ".kinetic.proto.Command.PinOperation\0227\n\005b"
        "atch\030\t \001(\0132(.com.seagate.kinetic.proto.C"
        "ommand.Batch\032D\n\005Batch\022\r\n\005count\030\001 \001(\005\022\024\n\010"
        "sequence\030\002 \003(\003B\002\020\001\022\026\n\016failedSequence\030\003 \001"
        "(\003\032\361\004\n\006Status\022B\n\004code\030\001 \001(\01624.com.seagat"
        "e.kinetic.proto.Command.Status.StatusCod"
        "e\022\025\n\rstatusMessage\030\002 \001(\t\022\027\n\017detailedMess"
        "age\030\003 \001(\014\"\362\003\n\nStatusCode\022 \n\023INVALID_STAT"
        "US_CODE\020\377\377\377\377\377\377\377\377\377\001\022\021\n\rNOT_ATTEMPTED\020\000\022\013\n"
        "\007SUCCESS\020\001\022\020\n\014HMAC_FAILURE\020\002\022\022\n\016NOT_AUTH"
        "ORIZED\020\003\022\023\n\017VERSION_FAILURE\020\004\022\022\n\016INTERNA"
        "L_ERROR\020\005\022\023\n\017HEADER_REQUIRED\020\006\022\r\n\tNOT_FO"
        "UND\020\007\022\024\n\020VERSION_MISMATCH\020\010\022\020\n\014SERVICE_B"
        "USY\020\t\022\013\n\007EXPIRED\020\n\022\016\n\nDATA_ERROR\020\013\022\023\n\017PE"
        "RM_DATA_ERROR\020\014\022\033\n\027REMOTE_CONNECTION_ERR"
        "OR\020\r\022\014\n\010NO_SPACE\020\016\022\032\n\026NO_SUCH_HMAC_ALGOR"
        "ITHM\020\017\022\023\n\017INVALID_REQUEST\020\020\022\033\n\027NESTED_OP"
        "ERATION_ERRORS\020\021\022\021\n\rDEVICE_LOCKED\020\022\022\033\n\027D"
        "EVICE_ALREADY_UNLOCKED\020\023\022\031\n\025CONNECTION_T"
        "ERMINATED\020\024\022\021\n\rINVALID_BATCH\020\025\032\376\001\n\010KeyVa"
        "lue\022\022\n\nnewVersion\030\002 \001(\014\022\r\n\005force\030\010 \001(\010\022\013"
        "\n\003key\030\003 \001(\014\022\021\n\tdbVersion\030\004 \001(\014\022\013\n\003tag\030\005 "
        "\001(\014\022\?\n\talgorithm\030\006 \001(\0162,.com.seagate.kin"
        "etic.proto.Command.Algorithm\022\024\n\014metadata"
        "Only\030\007 \001(\010\022K\n\017synchronization\030\t \001(\01622.co"
        "m.seagate.kinetic.proto.Command.Synchron"
        "ization\032\221\001\n\005Range\022\020\n\010startKey\030\001 \001(\014\022\016\n\006e"
        "ndKey\030\002 \001(\014\022\031\n\021startKeyInclusive\030\003 \001(\010\022\027"
        "\n\017endKeyInclusive\030\004 \001(\010\022\023\n\013maxReturned\030\005"
        " \001(\005\022\017\n\007reverse\030\006 \001(\010\022\014\n\004keys\030\010 \003(\014\032<\n\005S"
        "etup\022\031\n\021newClusterVersion\030\001 \001(\003\022\030\n\020firmw"
        "areDownload\030\005 \001(\010\032\300\003\n\014P2POperation\022B\n\004pe"
        "er\030\001 \001(\01324.com.seagate.kinetic.proto.Com"
        "mand.P2POperation.Peer\022L\n\toperation\030\002 \003("
        "\01329.com.seagate.kinetic.proto.Command.P2"
        "POperation.Operation\022#\n\033allChildOperatio"
        "nsSucceeded\030\003 \001(\010\032\303\001\n\tOperation\022\013\n\003key\030\003"
        " \001(\014\022\017\n\007version\030\004 \001(\014\022\016\n\006newKey\030\005 \001(\014\022\r\n"
        "\005force\030\006 \001(\010\0229\n\006status\030\007 \001(\0132).com.seaga"
        "te.kinetic.proto.Command.Status\022>\n\005p2pop"
        "\030\010 \001(\0132/.com.seagate.kinetic.proto.Comma"
        "nd.P2POperation\0323\n\004Peer\022\020\n\010hostname\030\001 \001("
        "\t\022\014\n\004port\030\002 \001(\005\022\013\n\003tls\030\003 \001(\010\032\354\016\n\006GetLog\022"
        "=\n\005types\030\001 \003(\0162..com.seagate.kinetic.pro"
        "to.Command.GetLog.Type\022K\n\014utilizations\030\002"
        " \003(\01325.com.seagate.kinetic.proto.Command"
        ".GetLog.Utilization\022K\n\014temperatures\030\003 \003("
        "\01325.com.seagate.kinetic.proto.Command.Ge"
        "tLog.Temperature\022D\n\010capacity\030\004 \001(\01322.com"
        ".seagate.kinetic.proto.Command.GetLog.Ca"
        "pacity\022N\n\rconfiguration\030\005 \001(\01327.com.seag"
        "ate.kinetic.proto.Command.GetLog.Configu"
        "ration\022H\n\nstatistics\030\006 \003(\01324.com.seagate"
        ".kinetic.proto.Command.GetLog.Statistics"
        "\022\020\n\010messages\030\007 \001(\014\022@\n\006limits\030\010 \001(\01320.com"
        ".seagate.kinetic.proto.Command.GetLog.Li"
        "mits\022@\n\006device\030\t \001(\01320.com.seagate.kinet"
        "ic.proto.Command.GetLog.Device\032*\n\013Utiliz"
        "ation\022\014\n\004name\030\001 \001(\t\022\r\n\005value\030\002 \001(\002\032^\n\013Te"
        "mperature\022\014\n\004name\030\001 \001(\t\022\017\n\007current\030\002 \001(\002"
        "\022\017\n\007minimum\030\003 \001(\002\022\017\n\007maximum\030\004 \001(\002\022\016\n\006ta"
        "rget\030\005 \001(\002\032\?\n\010Capacity\022\036\n\026nominalCapacit"
        "yInBytes\030\004 \001(\004\022\023\n\013portionFull\030\005 \001(\002\032\266\003\n\r"
        "Configuration\022\016\n\006vendor\030\005 \001(\t\022\r\n\005model\030\006"
        " \001(\t\022\024\n\014serialNumber\030\007 \001(\014\022\025\n\rworldWideN"
        "ame\030\016 \001(\014\022\017\n\007version\030\010 \001(\t\022\027\n\017compilatio"
        "nDate\030\014 \001(\t\022\022\n\nsourceHash\030\r \001(\t\022\027\n\017proto"
        "colVersion\030\017 \001(\t\022\037\n\027protocolCompilationD"
        "ate\030\020 \001(\t\022\032\n\022protocolSourceHash\030\021 \001(\t\022T\n"
        "\tinterface\030\t \003(\0132A.com.seagate.kinetic.p"
        "roto.Command.GetLog.Configuration.Interf"
        "ace\022\014\n\004port\030\n \001(\005\022\017\n\007tlsPort\030\013 \001(\005\032P\n\tIn"
        "terface\022\014\n\004name\030\001 \001(\t\022\013\n\003MAC\030\002 \001(\014\022\023\n\013ip"
        "v4Address\030\003 \001(\014\022\023\n\013ipv6Address\030\004 \001(\014\032o\n\n"
        "Statistics\022C\n\013messageType\030\001 \001(\0162..com.se"
        "agate.kinetic.proto.Command.MessageType\022"
        "\r\n\005count\030\004 \001(\004\022\r\n\005bytes\030\005 \001(\004\032\342\002\n\006Limits"
        "\022\022\n\nmaxKeySize\030\001 \001(\r\022\024\n\014maxValueSize\030\002 \001"
        "(\r\022\026\n\016maxVersionSize\030\003 \001(\r\022\022\n\nmaxTagSize"
        "\030\004 \001(\r\022\026\n\016maxConnections\030\005 \001(\r\022\"\n\032maxOut"
        "standingReadRequests\030\006 \001(\r\022#\n\033maxOutstan"
        "dingWriteRequests\030\007 \001(\r\022\026\n\016maxMessageSiz"
        "e\030\010 \001(\r\022\030\n\020maxKeyRangeCount\030\t \001(\r\022\030\n\020max"
        "IdentityCount\030\n \001(\r\022\022\n\nmaxPinSize\030\013 \001(\r\022"
        "!\n\031maxOperationCountPerBatch\030\014 \001(\r\022\036\n\026ma"
        "xBatchCountPerDevice\030\r \001(\r\032\026\n\006Device\022\014\n\004"
        "name\030\001 \001(\014\"\236\001\n\004Type\022\031\n\014INVALID_TYPE\020\377\377\377\377"
        "\377\377\377\377\377\001\022\020\n\014UTILIZATIONS\020\000\022\020\n\014TEMPERATURES"
        "\020\001\022\016\n\nCAPACITIES\020\002\022\021\n\rCONFIGURATION\020\003\022\016\n"
        "\nSTATISTICS\020\004\022\014\n\010MESSAGES\020\005\022\n\n\006LIMITS\020\006\022"
        "\n\n\006DEVICE\020\007\032\375\005\n\010Security\022<\n\003acl\030\002 \003(\0132/."
        "com.seagate.kinetic.proto.Command.Securi"
        "ty.ACL\022\022\n\noldLockPIN\030\003 \001(\014\022\022\n\nnewLockPIN"
        "\030\004 \001(\014\022\023\n\013oldErasePIN\030\005 \001(\014\022\023\n\013newEraseP"
        "IN\030\006 \001(\014\032\340\004\n\003ACL\022\020\n\010identity\030\001 \001(\003\022\013\n\003ke"
        "y\030\002 \001(\014\022T\n\rhmacAlgorithm\030\003 \001(\0162=.com.sea"
        "gate.kinetic.proto.Command.Security.ACL."
        "HMACAlgorithm\022D\n\005scope\030\004 \003(\01325.com.seaga"
        "te.kinetic.proto.Command.Security.ACL.Sc"
        "ope\022@\n\013maxPriority\030\005 \001(\0162+.com.seagate.k"
        "inetic.proto.Command.Priority\032\213\001\n\005Scope\022"
        "\016\n\006offset\030\001 \001(\003\022\r\n\005value\030\002 \001(\014\022N\n\npermis"
        "sion\030\003 \003(\0162:.com.seagate.kinetic.proto.C"
        "ommand.Security.ACL.Permission\022\023\n\013TlsReq"
        "uired\030\004 \001(\010\"B\n\rHMACAlgorithm\022#\n\026INVALID_"
        "HMAC_ALGORITHM\020\377\377\377\377\377\377\377\377\377\001\022\014\n\010HmacSHA1\020\001\""
        "\211\001\n\nPermission\022\037\n\022INVALID_PERMISSION\020\377\377\377"
        "\377\377\377\377\377\377\001\022\010\n\004READ\020\000\022\t\n\005WRITE\020\001\022\n\n\006DELETE\020\002"
        "\022\t\n\005RANGE\020\003\022\t\n\005SETUP\020\004\022\t\n\005P2POP\020\005\022\n\n\006GET"
        "LOG\020\007\022\014\n\010SECURITY\020\010\032\320\001\n\014PinOperation\022L\n\t"
        "pinOpType\030\001 \001(\01629.com.seagate.kinetic.pr"
        "oto.Command.PinOperation.PinOpType\"r\n\tPi"
        "nOpType\022\032\n\rINVALID_PINOP\020\377\377\377\377\377\377\377\377\377\001\022\020\n\014U"
        "NLOCK_PINOP\020\001\022\016\n\nLOCK_PINOP\020\002\022\017\n\013ERASE_P"
        "INOP\020\003\022\026\n\022SECURE_ERASE_PINOP\020\004\"c\n\017Synchr"
        "onization\022$\n\027INVALID_SYNCHRONIZATION\020\377\377\377"
        "\377\377\377\377\377\377\001\022\020\n\014WRITETHROUGH\020\001\022\r\n\tWRITEBACK\020\002"
        "\022\t\n\005FLUSH\020\003\"F\n\010Priority\022\n\n\006NORMAL\020\005\022\n\n\006L"
        "OWEST\020\001\022\t\n\005LOWER\020\003\022\n\n\006HIGHER\020\007\022\013\n\007HIGHES"
        "T\020\t\"_\n\tAlgorithm\022\036\n\021INVALID_ALGORITHM\020\377\377"
        "\377\377\377\377\377\377\377\001\022\010\n\004SHA1\020\001\022\010\n\004SHA2\020\002\022\010\n\004SHA3\020\003\022\t"
        "\n\005CRC32\020\004\022\t\n\005CRC64\020\005\"\371\005\n\013MessageType\022!\n\024"
        "INVALID_MESSAGE_TYPE\020\377\377\377\377\377\377\377\377\377\001\022\007\n\003GET\020\002"
        "\022\020\n\014GET_RESPONSE\020\001\022\007\n\003PUT\020\004\022\020\n\014PUT_RESPO"
        "NSE\020\003\022\n\n\006DELETE\020\006\022\023\n\017DELETE_RESPONSE\020\005\022\013"
        "\n\007GETNEXT\020\010\022\024\n\020GETNEXT_RESPONSE\020\007\022\017\n\013GET"
        "PREVIOUS\020\n\022\030\n\024GETPREVIOUS_RESPONSE\020\t\022\017\n\013"
        "GETKEYRANGE\020\014\022\030\n\024GETKEYRANGE_RESPONSE\020\013\022"
        "\016\n\nGETVERSION\020\020\022\027\n\023GETVERSION_RESPONSE\020\017"
        "\022\t\n\005SETUP\020\026\022\022\n\016SETUP_RESPONSE\020\025\022\n\n\006GETLO"
        "G\020\030\022\023\n\017GETLOG_RESPONSE\020\027\022\014\n\010SECURITY\020\032\022\025"
        "\n\021SECURITY_RESPONSE\020\031\022\021\n\rPEER2PEERPUSH\020\034"
        "\022\032\n\026PEER2PEERPUSH_RESPONSE\020\033\022\010\n\004NOOP\020\036\022\021"
        "\n\rNOOP_RESPONSE\020\035\022\020\n\014FLUSHALLDATA\020 \022\031\n\025F"
        "LUSHALLDATA_RESPONSE\020\037\022\t\n\005PINOP\020$\022\022\n\016PIN"
        "OP_RESPONSE\020#\022\r\n\tMEDIASCAN\020&\022\026\n\022MEDIASCA"
        "N_RESPONSE\020%\022\021\n\rMEDIAOPTIMIZE\020(\022\032\n\026MEDIA"
        "OPTIMIZE_RESPONSE\020\'\022\017\n\013START_BATCH\020*\022\030\n\024"
        "START_BATCH_RESPONSE\020)\022\r\n\tEND_BATCH\020,\022\026\n"
        "\022END_BATCH_RESPONSE\020+\022\017\n\013ABORT_BATCH\020.\022\030"
        "\n\024ABORT_BATCH_RESPONSE\020-B\tB\007Kinetic", 6995);
    ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
        "Kinetic.proto", &protobuf_RegisterTypes);
    Local::_default_protocolversion_ =
        new ::std::string("3.0.6", 5);
    Local::default_instance_ = new Local();
    Message::default_instance_ = new Message();
    Message_HMACauth::default_instance_ = new Message_HMACauth();
    Message_PINauth::default_instance_ = new Message_PINauth();
    Command::default_instance_ = new Command();
    Command_Header::default_instance_ = new Command_Header();
    Command_Body::default_instance_ = new Command_Body();
    Command_Batch::default_instance_ = new Command_Batch();
    Command_Status::default_instance_ = new Command_Status();
    Command_KeyValue::default_instance_ = new Command_KeyValue();
    Command_Range::default_instance_ = new Command_Range();
    Command_Setup::default_instance_ = new Command_Setup();
    Command_P2POperation::default_instance_ = new Command_P2POperation();
    Command_P2POperation_Operation::default_instance_ = new Command_P2POperation_Operation();
    Command_P2POperation_Peer::default_instance_ = new Command_P2POperation_Peer();
    Command_GetLog::default_instance_ = new Command_GetLog();
    Command_GetLog_Utilization::default_instance_ = new Command_GetLog_Utilization();
    Command_GetLog_Temperature::default_instance_ = new Command_GetLog_Temperature();
    Command_GetLog_Capacity::default_instance_ = new Command_GetLog_Capacity();
    Command_GetLog_Configuration::default_instance_ = new Command_GetLog_Configuration();
    Command_GetLog_Configuration_Interface::default_instance_ = new Command_GetLog_Configuration_Interface();
    Command_GetLog_Statistics::default_instance_ = new Command_GetLog_Statistics();
    Command_GetLog_Limits::default_instance_ = new Command_GetLog_Limits();
    Command_GetLog_Device::default_instance_ = new Command_GetLog_Device();
    Command_Security::default_instance_ = new Command_Security();
    Command_Security_ACL::default_instance_ = new Command_Security_ACL();
    Command_Security_ACL_Scope::default_instance_ = new Command_Security_ACL_Scope();
    Command_PinOperation::default_instance_ = new Command_PinOperation();
    Local::default_instance_->InitAsDefaultInstance();
    Message::default_instance_->InitAsDefaultInstance();
    Message_HMACauth::default_instance_->InitAsDefaultInstance();
    Message_PINauth::default_instance_->InitAsDefaultInstance();
    Command::default_instance_->InitAsDefaultInstance();
    Command_Header::default_instance_->InitAsDefaultInstance();
    Command_Body::default_instance_->InitAsDefaultInstance();
    Command_Batch::default_instance_->InitAsDefaultInstance();
    Command_Status::default_instance_->InitAsDefaultInstance();
    Command_KeyValue::default_instance_->InitAsDefaultInstance();
    Command_Range::default_instance_->InitAsDefaultInstance();
    Command_Setup::default_instance_->InitAsDefaultInstance();
    Command_P2POperation::default_instance_->InitAsDefaultInstance();
    Command_P2POperation_Operation::default_instance_->InitAsDefaultInstance();
    Command_P2POperation_Peer::default_instance_->InitAsDefaultInstance();
    Command_GetLog::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Utilization::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Temperature::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Capacity::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Configuration::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Configuration_Interface::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Statistics::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Limits::default_instance_->InitAsDefaultInstance();
    Command_GetLog_Device::default_instance_->InitAsDefaultInstance();
    Command_Security::default_instance_->InitAsDefaultInstance();
    Command_Security_ACL::default_instance_->InitAsDefaultInstance();
    Command_Security_ACL_Scope::default_instance_->InitAsDefaultInstance();
    Command_PinOperation::default_instance_->InitAsDefaultInstance();
    ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Kinetic_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Kinetic_2eproto {
    StaticDescriptorInitializer_Kinetic_2eproto() {
        protobuf_AddDesc_Kinetic_2eproto();
    }
} static_descriptor_initializer_Kinetic_2eproto_;

// ===================================================================

::std::string* Local::_default_protocolversion_ = NULL;
#ifndef _MSC_VER
const int Local::kProtocolVersionFieldNumber;
#endif  // !_MSC_VER

Local::Local()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Local)
}

void Local::InitAsDefaultInstance() {
}

Local::Local(const Local& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Local)
}

void Local::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    protocolversion_ = const_cast<::std::string*>(_default_protocolversion_);
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Local::~Local() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Local)
    SharedDtor();
}

void Local::SharedDtor() {
    if (protocolversion_ != _default_protocolversion_) {
        delete protocolversion_;
    }
    if (this != default_instance_) {
    }
}

void Local::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Local::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Local_descriptor_;
}

const Local& Local::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Local* Local::default_instance_ = NULL;

Local* Local::New() const {
    return new Local;
}

void Local::Clear() {
    if (has_protocolversion()) {
        if (protocolversion_ != _default_protocolversion_) {
            protocolversion_->assign(*_default_protocolversion_);
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Local::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Local)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string protocolVersion = 1 [default = "3.0.6"];
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_protocolversion()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->protocolversion().data(), this->protocolversion().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "protocolversion");
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Local)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Local)
    return false;
#undef DO_
}

void Local::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Local)
    // optional string protocolVersion = 1 [default = "3.0.6"];
    if (has_protocolversion()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolversion().data(), this->protocolversion().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolversion");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->protocolversion(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Local)
}

::google::protobuf::uint8* Local::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Local)
    // optional string protocolVersion = 1 [default = "3.0.6"];
    if (has_protocolversion()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolversion().data(), this->protocolversion().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolversion");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                1, this->protocolversion(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Local)
    return target;
}

int Local::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string protocolVersion = 1 [default = "3.0.6"];
        if (has_protocolversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->protocolversion());
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

void Local::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Local* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Local*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Local::MergeFrom(const Local& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_protocolversion()) {
            set_protocolversion(from.protocolversion());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Local::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Local::CopyFrom(const Local& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Local::IsInitialized() const {

    return true;
}

void Local::Swap(Local* other) {
    if (other != this) {
        std::swap(protocolversion_, other->protocolversion_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Local::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Local_descriptor_;
    metadata.reflection = Local_reflection_;
    return metadata;
}


// ===================================================================

const ::google::protobuf::EnumDescriptor* Message_AuthType_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Message_AuthType_descriptor_;
}
bool Message_AuthType_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
        case 2:
        case 3:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Message_AuthType Message::INVALID_AUTH_TYPE;
const Message_AuthType Message::HMACAUTH;
const Message_AuthType Message::PINAUTH;
const Message_AuthType Message::UNSOLICITEDSTATUS;
const Message_AuthType Message::AuthType_MIN;
const Message_AuthType Message::AuthType_MAX;
const int Message::AuthType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Message_HMACauth::kIdentityFieldNumber;
const int Message_HMACauth::kHmacFieldNumber;
#endif  // !_MSC_VER

Message_HMACauth::Message_HMACauth()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Message.HMACauth)
}

void Message_HMACauth::InitAsDefaultInstance() {
}

Message_HMACauth::Message_HMACauth(const Message_HMACauth& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Message.HMACauth)
}

void Message_HMACauth::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    identity_ = GOOGLE_LONGLONG(0);
    hmac_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Message_HMACauth::~Message_HMACauth() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Message.HMACauth)
    SharedDtor();
}

void Message_HMACauth::SharedDtor() {
    if (hmac_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete hmac_;
    }
    if (this != default_instance_) {
    }
}

void Message_HMACauth::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Message_HMACauth::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Message_HMACauth_descriptor_;
}

const Message_HMACauth& Message_HMACauth::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Message_HMACauth* Message_HMACauth::default_instance_ = NULL;

Message_HMACauth* Message_HMACauth::New() const {
    return new Message_HMACauth;
}

void Message_HMACauth::Clear() {
    if (_has_bits_[0 / 32] & 3) {
        identity_ = GOOGLE_LONGLONG(0);
        if (has_hmac()) {
            if (hmac_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                hmac_->clear();
            }
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Message_HMACauth::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Message.HMACauth)
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
                if (input->ExpectTag(18)) goto parse_hmac;
                break;
            }

            // optional bytes hmac = 2;
            case 2: {
                if (tag == 18) {
parse_hmac:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_hmac()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Message.HMACauth)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Message.HMACauth)
    return false;
#undef DO_
}

void Message_HMACauth::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Message.HMACauth)
    // optional int64 identity = 1;
    if (has_identity()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->identity(), output);
    }

    // optional bytes hmac = 2;
    if (has_hmac()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->hmac(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Message.HMACauth)
}

::google::protobuf::uint8* Message_HMACauth::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Message.HMACauth)
    // optional int64 identity = 1;
    if (has_identity()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->identity(), target);
    }

    // optional bytes hmac = 2;
    if (has_hmac()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->hmac(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Message.HMACauth)
    return target;
}

int Message_HMACauth::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 identity = 1;
        if (has_identity()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->identity());
        }

        // optional bytes hmac = 2;
        if (has_hmac()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->hmac());
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

void Message_HMACauth::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Message_HMACauth* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Message_HMACauth*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Message_HMACauth::MergeFrom(const Message_HMACauth& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_identity()) {
            set_identity(from.identity());
        }
        if (from.has_hmac()) {
            set_hmac(from.hmac());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Message_HMACauth::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Message_HMACauth::CopyFrom(const Message_HMACauth& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Message_HMACauth::IsInitialized() const {

    return true;
}

void Message_HMACauth::Swap(Message_HMACauth* other) {
    if (other != this) {
        std::swap(identity_, other->identity_);
        std::swap(hmac_, other->hmac_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Message_HMACauth::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Message_HMACauth_descriptor_;
    metadata.reflection = Message_HMACauth_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Message_PINauth::kPinFieldNumber;
#endif  // !_MSC_VER

Message_PINauth::Message_PINauth()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Message.PINauth)
}

void Message_PINauth::InitAsDefaultInstance() {
}

Message_PINauth::Message_PINauth(const Message_PINauth& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Message.PINauth)
}

void Message_PINauth::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    pin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Message_PINauth::~Message_PINauth() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Message.PINauth)
    SharedDtor();
}

void Message_PINauth::SharedDtor() {
    if (pin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete pin_;
    }
    if (this != default_instance_) {
    }
}

void Message_PINauth::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Message_PINauth::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Message_PINauth_descriptor_;
}

const Message_PINauth& Message_PINauth::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Message_PINauth* Message_PINauth::default_instance_ = NULL;

Message_PINauth* Message_PINauth::New() const {
    return new Message_PINauth;
}

void Message_PINauth::Clear() {
    if (has_pin()) {
        if (pin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
            pin_->clear();
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Message_PINauth::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Message.PINauth)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bytes pin = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_pin()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Message.PINauth)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Message.PINauth)
    return false;
#undef DO_
}

void Message_PINauth::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Message.PINauth)
    // optional bytes pin = 1;
    if (has_pin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            1, this->pin(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Message.PINauth)
}

::google::protobuf::uint8* Message_PINauth::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Message.PINauth)
    // optional bytes pin = 1;
    if (has_pin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                1, this->pin(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Message.PINauth)
    return target;
}

int Message_PINauth::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bytes pin = 1;
        if (has_pin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->pin());
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

void Message_PINauth::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Message_PINauth* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Message_PINauth*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Message_PINauth::MergeFrom(const Message_PINauth& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_pin()) {
            set_pin(from.pin());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Message_PINauth::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Message_PINauth::CopyFrom(const Message_PINauth& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Message_PINauth::IsInitialized() const {

    return true;
}

void Message_PINauth::Swap(Message_PINauth* other) {
    if (other != this) {
        std::swap(pin_, other->pin_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Message_PINauth::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Message_PINauth_descriptor_;
    metadata.reflection = Message_PINauth_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Message::kAuthTypeFieldNumber;
const int Message::kHmacAuthFieldNumber;
const int Message::kPinAuthFieldNumber;
const int Message::kCommandBytesFieldNumber;
#endif  // !_MSC_VER

Message::Message()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Message)
}

void Message::InitAsDefaultInstance() {
    hmacauth_ = const_cast<::com::seagate::kinetic::proto::Message_HMACauth*>(&::com::seagate::kinetic::proto::Message_HMACauth::default_instance());
    pinauth_ = const_cast<::com::seagate::kinetic::proto::Message_PINauth*>(&::com::seagate::kinetic::proto::Message_PINauth::default_instance());
}

Message::Message(const Message& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Message)
}

void Message::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    authtype_ = -1;
    hmacauth_ = NULL;
    pinauth_ = NULL;
    commandbytes_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Message::~Message() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Message)
    SharedDtor();
}

void Message::SharedDtor() {
    if (commandbytes_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete commandbytes_;
    }
    if (this != default_instance_) {
        delete hmacauth_;
        delete pinauth_;
    }
}

void Message::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Message::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Message_descriptor_;
}

const Message& Message::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Message* Message::default_instance_ = NULL;

Message* Message::New() const {
    return new Message;
}

void Message::Clear() {
    if (_has_bits_[0 / 32] & 15) {
        authtype_ = -1;
        if (has_hmacauth()) {
            if (hmacauth_ != NULL) hmacauth_->::com::seagate::kinetic::proto::Message_HMACauth::Clear();
        }
        if (has_pinauth()) {
            if (pinauth_ != NULL) pinauth_->::com::seagate::kinetic::proto::Message_PINauth::Clear();
        }
        if (has_commandbytes()) {
            if (commandbytes_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                commandbytes_->clear();
            }
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Message::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Message)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Message.AuthType authType = 4;
            case 4: {
                if (tag == 32) {
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Message_AuthType_IsValid(value)) {
                        set_authtype(static_cast<::com::seagate::kinetic::proto::Message_AuthType>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(4, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(42)) goto parse_hmacAuth;
                break;
            }

            // optional .com.seagate.kinetic.proto.Message.HMACauth hmacAuth = 5;
            case 5: {
                if (tag == 42) {
parse_hmacAuth:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_hmacauth()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_pinAuth;
                break;
            }

            // optional .com.seagate.kinetic.proto.Message.PINauth pinAuth = 6;
            case 6: {
                if (tag == 50) {
parse_pinAuth:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_pinauth()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(58)) goto parse_commandBytes;
                break;
            }

            // optional bytes commandBytes = 7;
            case 7: {
                if (tag == 58) {
parse_commandBytes:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_commandbytes()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Message)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Message)
    return false;
#undef DO_
}

void Message::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Message)
    // optional .com.seagate.kinetic.proto.Message.AuthType authType = 4;
    if (has_authtype()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            4, this->authtype(), output);
    }

    // optional .com.seagate.kinetic.proto.Message.HMACauth hmacAuth = 5;
    if (has_hmacauth()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            5, this->hmacauth(), output);
    }

    // optional .com.seagate.kinetic.proto.Message.PINauth pinAuth = 6;
    if (has_pinauth()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            6, this->pinauth(), output);
    }

    // optional bytes commandBytes = 7;
    if (has_commandbytes()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            7, this->commandbytes(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Message)
}

::google::protobuf::uint8* Message::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Message)
    // optional .com.seagate.kinetic.proto.Message.AuthType authType = 4;
    if (has_authtype()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     4, this->authtype(), target);
    }

    // optional .com.seagate.kinetic.proto.Message.HMACauth hmacAuth = 5;
    if (has_hmacauth()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     5, this->hmacauth(), target);
    }

    // optional .com.seagate.kinetic.proto.Message.PINauth pinAuth = 6;
    if (has_pinauth()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     6, this->pinauth(), target);
    }

    // optional bytes commandBytes = 7;
    if (has_commandbytes()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                7, this->commandbytes(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Message)
    return target;
}

int Message::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Message.AuthType authType = 4;
        if (has_authtype()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->authtype());
        }

        // optional .com.seagate.kinetic.proto.Message.HMACauth hmacAuth = 5;
        if (has_hmacauth()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->hmacauth());
        }

        // optional .com.seagate.kinetic.proto.Message.PINauth pinAuth = 6;
        if (has_pinauth()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->pinauth());
        }

        // optional bytes commandBytes = 7;
        if (has_commandbytes()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->commandbytes());
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

void Message::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Message* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Message*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Message::MergeFrom(const Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_authtype()) {
            set_authtype(from.authtype());
        }
        if (from.has_hmacauth()) {
            mutable_hmacauth()->::com::seagate::kinetic::proto::Message_HMACauth::MergeFrom(from.hmacauth());
        }
        if (from.has_pinauth()) {
            mutable_pinauth()->::com::seagate::kinetic::proto::Message_PINauth::MergeFrom(from.pinauth());
        }
        if (from.has_commandbytes()) {
            set_commandbytes(from.commandbytes());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Message::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Message::CopyFrom(const Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Message::IsInitialized() const {

    return true;
}

void Message::Swap(Message* other) {
    if (other != this) {
        std::swap(authtype_, other->authtype_);
        std::swap(hmacauth_, other->hmacauth_);
        std::swap(pinauth_, other->pinauth_);
        std::swap(commandbytes_, other->commandbytes_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Message::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Message_descriptor_;
    metadata.reflection = Message_reflection_;
    return metadata;
}


// ===================================================================

const ::google::protobuf::EnumDescriptor* Command_Synchronization_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Synchronization_descriptor_;
}
bool Command_Synchronization_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
        case 2:
        case 3:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_Synchronization Command::INVALID_SYNCHRONIZATION;
const Command_Synchronization Command::WRITETHROUGH;
const Command_Synchronization Command::WRITEBACK;
const Command_Synchronization Command::FLUSH;
const Command_Synchronization Command::Synchronization_MIN;
const Command_Synchronization Command::Synchronization_MAX;
const int Command::Synchronization_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Command_Priority_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Priority_descriptor_;
}
bool Command_Priority_IsValid(int value) {
    switch (value) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_Priority Command::NORMAL;
const Command_Priority Command::LOWEST;
const Command_Priority Command::LOWER;
const Command_Priority Command::HIGHER;
const Command_Priority Command::HIGHEST;
const Command_Priority Command::Priority_MIN;
const Command_Priority Command::Priority_MAX;
const int Command::Priority_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Command_Algorithm_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Algorithm_descriptor_;
}
bool Command_Algorithm_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_Algorithm Command::INVALID_ALGORITHM;
const Command_Algorithm Command::SHA1;
const Command_Algorithm Command::SHA2;
const Command_Algorithm Command::SHA3;
const Command_Algorithm Command::CRC32;
const Command_Algorithm Command::CRC64;
const Command_Algorithm Command::Algorithm_MIN;
const Command_Algorithm Command::Algorithm_MAX;
const int Command::Algorithm_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Command_MessageType_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_MessageType_descriptor_;
}
bool Command_MessageType_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_MessageType Command::INVALID_MESSAGE_TYPE;
const Command_MessageType Command::GET;
const Command_MessageType Command::GET_RESPONSE;
const Command_MessageType Command::PUT;
const Command_MessageType Command::PUT_RESPONSE;
const Command_MessageType Command::DELETE;
const Command_MessageType Command::DELETE_RESPONSE;
const Command_MessageType Command::GETNEXT;
const Command_MessageType Command::GETNEXT_RESPONSE;
const Command_MessageType Command::GETPREVIOUS;
const Command_MessageType Command::GETPREVIOUS_RESPONSE;
const Command_MessageType Command::GETKEYRANGE;
const Command_MessageType Command::GETKEYRANGE_RESPONSE;
const Command_MessageType Command::GETVERSION;
const Command_MessageType Command::GETVERSION_RESPONSE;
const Command_MessageType Command::SETUP;
const Command_MessageType Command::SETUP_RESPONSE;
const Command_MessageType Command::GETLOG;
const Command_MessageType Command::GETLOG_RESPONSE;
const Command_MessageType Command::SECURITY;
const Command_MessageType Command::SECURITY_RESPONSE;
const Command_MessageType Command::PEER2PEERPUSH;
const Command_MessageType Command::PEER2PEERPUSH_RESPONSE;
const Command_MessageType Command::NOOP;
const Command_MessageType Command::NOOP_RESPONSE;
const Command_MessageType Command::FLUSHALLDATA;
const Command_MessageType Command::FLUSHALLDATA_RESPONSE;
const Command_MessageType Command::PINOP;
const Command_MessageType Command::PINOP_RESPONSE;
const Command_MessageType Command::MEDIASCAN;
const Command_MessageType Command::MEDIASCAN_RESPONSE;
const Command_MessageType Command::MEDIAOPTIMIZE;
const Command_MessageType Command::MEDIAOPTIMIZE_RESPONSE;
const Command_MessageType Command::START_BATCH;
const Command_MessageType Command::START_BATCH_RESPONSE;
const Command_MessageType Command::END_BATCH;
const Command_MessageType Command::END_BATCH_RESPONSE;
const Command_MessageType Command::ABORT_BATCH;
const Command_MessageType Command::ABORT_BATCH_RESPONSE;
const Command_MessageType Command::MessageType_MIN;
const Command_MessageType Command::MessageType_MAX;
const int Command::MessageType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command_Header::kClusterVersionFieldNumber;
const int Command_Header::kConnectionIDFieldNumber;
const int Command_Header::kSequenceFieldNumber;
const int Command_Header::kAckSequenceFieldNumber;
const int Command_Header::kMessageTypeFieldNumber;
const int Command_Header::kTimeoutFieldNumber;
const int Command_Header::kEarlyExitFieldNumber;
const int Command_Header::kPriorityFieldNumber;
const int Command_Header::kTimeQuantaFieldNumber;
const int Command_Header::kBatchIDFieldNumber;
#endif  // !_MSC_VER

Command_Header::Command_Header()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Header)
}

void Command_Header::InitAsDefaultInstance() {
}

Command_Header::Command_Header(const Command_Header& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Header)
}

void Command_Header::SharedCtor() {
    _cached_size_ = 0;
    clusterversion_ = GOOGLE_LONGLONG(0);
    connectionid_ = GOOGLE_LONGLONG(0);
    sequence_ = GOOGLE_LONGLONG(0);
    acksequence_ = GOOGLE_LONGLONG(0);
    messagetype_ = -1;
    timeout_ = GOOGLE_LONGLONG(0);
    earlyexit_ = false;
    priority_ = 5;
    timequanta_ = GOOGLE_LONGLONG(0);
    batchid_ = 0u;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Header::~Command_Header() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Header)
    SharedDtor();
}

void Command_Header::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_Header::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Header::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Header_descriptor_;
}

const Command_Header& Command_Header::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Header* Command_Header::default_instance_ = NULL;

Command_Header* Command_Header::New() const {
    return new Command_Header;
}

void Command_Header::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_Header*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 255) {
        ZR_(clusterversion_, timeout_);
        messagetype_ = -1;
        earlyexit_ = false;
        priority_ = 5;
    }
    if (_has_bits_[8 / 32] & 768) {
        timequanta_ = GOOGLE_LONGLONG(0);
        batchid_ = 0u;
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Header::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Header)
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
                if (input->ExpectTag(24)) goto parse_connectionID;
                break;
            }

            // optional int64 connectionID = 3;
            case 3: {
                if (tag == 24) {
parse_connectionID:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &connectionid_)));
                    set_has_connectionid();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_sequence;
                break;
            }

            // optional int64 sequence = 4;
            case 4: {
                if (tag == 32) {
parse_sequence:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &sequence_)));
                    set_has_sequence();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(48)) goto parse_ackSequence;
                break;
            }

            // optional int64 ackSequence = 6;
            case 6: {
                if (tag == 48) {
parse_ackSequence:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &acksequence_)));
                    set_has_acksequence();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(56)) goto parse_messageType;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 7;
            case 7: {
                if (tag == 56) {
parse_messageType:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_MessageType_IsValid(value)) {
                        set_messagetype(static_cast<::com::seagate::kinetic::proto::Command_MessageType>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(7, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(72)) goto parse_timeout;
                break;
            }

            // optional int64 timeout = 9;
            case 9: {
                if (tag == 72) {
parse_timeout:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &timeout_)));
                    set_has_timeout();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(80)) goto parse_earlyExit;
                break;
            }

            // optional bool earlyExit = 10;
            case 10: {
                if (tag == 80) {
parse_earlyExit:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &earlyexit_)));
                    set_has_earlyexit();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(96)) goto parse_priority;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Priority priority = 12;
            case 12: {
                if (tag == 96) {
parse_priority:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Priority_IsValid(value)) {
                        set_priority(static_cast<::com::seagate::kinetic::proto::Command_Priority>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(12, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(104)) goto parse_TimeQuanta;
                break;
            }

            // optional int64 TimeQuanta = 13;
            case 13: {
                if (tag == 104) {
parse_TimeQuanta:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &timequanta_)));
                    set_has_timequanta();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(112)) goto parse_batchID;
                break;
            }

            // optional uint32 batchID = 14;
            case 14: {
                if (tag == 112) {
parse_batchID:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &batchid_)));
                    set_has_batchid();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Header)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Header)
    return false;
#undef DO_
}

void Command_Header::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Header)
    // optional int64 clusterVersion = 1;
    if (has_clusterversion()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->clusterversion(), output);
    }

    // optional int64 connectionID = 3;
    if (has_connectionid()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->connectionid(), output);
    }

    // optional int64 sequence = 4;
    if (has_sequence()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->sequence(), output);
    }

    // optional int64 ackSequence = 6;
    if (has_acksequence()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(6, this->acksequence(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 7;
    if (has_messagetype()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            7, this->messagetype(), output);
    }

    // optional int64 timeout = 9;
    if (has_timeout()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(9, this->timeout(), output);
    }

    // optional bool earlyExit = 10;
    if (has_earlyexit()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(10, this->earlyexit(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Priority priority = 12;
    if (has_priority()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            12, this->priority(), output);
    }

    // optional int64 TimeQuanta = 13;
    if (has_timequanta()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(13, this->timequanta(), output);
    }

    // optional uint32 batchID = 14;
    if (has_batchid()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(14, this->batchid(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Header)
}

::google::protobuf::uint8* Command_Header::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Header)
    // optional int64 clusterVersion = 1;
    if (has_clusterversion()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->clusterversion(), target);
    }

    // optional int64 connectionID = 3;
    if (has_connectionid()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->connectionid(), target);
    }

    // optional int64 sequence = 4;
    if (has_sequence()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->sequence(), target);
    }

    // optional int64 ackSequence = 6;
    if (has_acksequence()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(6, this->acksequence(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 7;
    if (has_messagetype()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     7, this->messagetype(), target);
    }

    // optional int64 timeout = 9;
    if (has_timeout()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(9, this->timeout(), target);
    }

    // optional bool earlyExit = 10;
    if (has_earlyexit()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(10, this->earlyexit(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Priority priority = 12;
    if (has_priority()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     12, this->priority(), target);
    }

    // optional int64 TimeQuanta = 13;
    if (has_timequanta()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(13, this->timequanta(), target);
    }

    // optional uint32 batchID = 14;
    if (has_batchid()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(14, this->batchid(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Header)
    return target;
}

int Command_Header::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 clusterVersion = 1;
        if (has_clusterversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->clusterversion());
        }

        // optional int64 connectionID = 3;
        if (has_connectionid()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->connectionid());
        }

        // optional int64 sequence = 4;
        if (has_sequence()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->sequence());
        }

        // optional int64 ackSequence = 6;
        if (has_acksequence()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->acksequence());
        }

        // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 7;
        if (has_messagetype()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->messagetype());
        }

        // optional int64 timeout = 9;
        if (has_timeout()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->timeout());
        }

        // optional bool earlyExit = 10;
        if (has_earlyexit()) {
            total_size += 1 + 1;
        }

        // optional .com.seagate.kinetic.proto.Command.Priority priority = 12;
        if (has_priority()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->priority());
        }

    }
    if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        // optional int64 TimeQuanta = 13;
        if (has_timequanta()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->timequanta());
        }

        // optional uint32 batchID = 14;
        if (has_batchid()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->batchid());
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

void Command_Header::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Header* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Header*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Header::MergeFrom(const Command_Header& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_clusterversion()) {
            set_clusterversion(from.clusterversion());
        }
        if (from.has_connectionid()) {
            set_connectionid(from.connectionid());
        }
        if (from.has_sequence()) {
            set_sequence(from.sequence());
        }
        if (from.has_acksequence()) {
            set_acksequence(from.acksequence());
        }
        if (from.has_messagetype()) {
            set_messagetype(from.messagetype());
        }
        if (from.has_timeout()) {
            set_timeout(from.timeout());
        }
        if (from.has_earlyexit()) {
            set_earlyexit(from.earlyexit());
        }
        if (from.has_priority()) {
            set_priority(from.priority());
        }
    }
    if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        if (from.has_timequanta()) {
            set_timequanta(from.timequanta());
        }
        if (from.has_batchid()) {
            set_batchid(from.batchid());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Header::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Header::CopyFrom(const Command_Header& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Header::IsInitialized() const {

    return true;
}

void Command_Header::Swap(Command_Header* other) {
    if (other != this) {
        std::swap(clusterversion_, other->clusterversion_);
        std::swap(connectionid_, other->connectionid_);
        std::swap(sequence_, other->sequence_);
        std::swap(acksequence_, other->acksequence_);
        std::swap(messagetype_, other->messagetype_);
        std::swap(timeout_, other->timeout_);
        std::swap(earlyexit_, other->earlyexit_);
        std::swap(priority_, other->priority_);
        std::swap(timequanta_, other->timequanta_);
        std::swap(batchid_, other->batchid_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Header::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Header_descriptor_;
    metadata.reflection = Command_Header_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Body::kKeyValueFieldNumber;
const int Command_Body::kRangeFieldNumber;
const int Command_Body::kSetupFieldNumber;
const int Command_Body::kP2POperationFieldNumber;
const int Command_Body::kGetLogFieldNumber;
const int Command_Body::kSecurityFieldNumber;
const int Command_Body::kPinOpFieldNumber;
const int Command_Body::kBatchFieldNumber;
#endif  // !_MSC_VER

Command_Body::Command_Body()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Body)
}

void Command_Body::InitAsDefaultInstance() {
    keyvalue_ = const_cast<::com::seagate::kinetic::proto::Command_KeyValue*>(&::com::seagate::kinetic::proto::Command_KeyValue::default_instance());
    range_ = const_cast<::com::seagate::kinetic::proto::Command_Range*>(&::com::seagate::kinetic::proto::Command_Range::default_instance());
    setup_ = const_cast<::com::seagate::kinetic::proto::Command_Setup*>(&::com::seagate::kinetic::proto::Command_Setup::default_instance());
    p2poperation_ = const_cast<::com::seagate::kinetic::proto::Command_P2POperation*>(&::com::seagate::kinetic::proto::Command_P2POperation::default_instance());
    getlog_ = const_cast<::com::seagate::kinetic::proto::Command_GetLog*>(&::com::seagate::kinetic::proto::Command_GetLog::default_instance());
    security_ = const_cast<::com::seagate::kinetic::proto::Command_Security*>(&::com::seagate::kinetic::proto::Command_Security::default_instance());
    pinop_ = const_cast<::com::seagate::kinetic::proto::Command_PinOperation*>(&::com::seagate::kinetic::proto::Command_PinOperation::default_instance());
    batch_ = const_cast<::com::seagate::kinetic::proto::Command_Batch*>(&::com::seagate::kinetic::proto::Command_Batch::default_instance());
}

Command_Body::Command_Body(const Command_Body& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Body)
}

void Command_Body::SharedCtor() {
    _cached_size_ = 0;
    keyvalue_ = NULL;
    range_ = NULL;
    setup_ = NULL;
    p2poperation_ = NULL;
    getlog_ = NULL;
    security_ = NULL;
    pinop_ = NULL;
    batch_ = NULL;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Body::~Command_Body() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Body)
    SharedDtor();
}

void Command_Body::SharedDtor() {
    if (this != default_instance_) {
        delete keyvalue_;
        delete range_;
        delete setup_;
        delete p2poperation_;
        delete getlog_;
        delete security_;
        delete pinop_;
        delete batch_;
    }
}

void Command_Body::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Body::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Body_descriptor_;
}

const Command_Body& Command_Body::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Body* Command_Body::default_instance_ = NULL;

Command_Body* Command_Body::New() const {
    return new Command_Body;
}

void Command_Body::Clear() {
    if (_has_bits_[0 / 32] & 255) {
        if (has_keyvalue()) {
            if (keyvalue_ != NULL) keyvalue_->::com::seagate::kinetic::proto::Command_KeyValue::Clear();
        }
        if (has_range()) {
            if (range_ != NULL) range_->::com::seagate::kinetic::proto::Command_Range::Clear();
        }
        if (has_setup()) {
            if (setup_ != NULL) setup_->::com::seagate::kinetic::proto::Command_Setup::Clear();
        }
        if (has_p2poperation()) {
            if (p2poperation_ != NULL) p2poperation_->::com::seagate::kinetic::proto::Command_P2POperation::Clear();
        }
        if (has_getlog()) {
            if (getlog_ != NULL) getlog_->::com::seagate::kinetic::proto::Command_GetLog::Clear();
        }
        if (has_security()) {
            if (security_ != NULL) security_->::com::seagate::kinetic::proto::Command_Security::Clear();
        }
        if (has_pinop()) {
            if (pinop_ != NULL) pinop_->::com::seagate::kinetic::proto::Command_PinOperation::Clear();
        }
        if (has_batch()) {
            if (batch_ != NULL) batch_->::com::seagate::kinetic::proto::Command_Batch::Clear();
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Body::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Body)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.KeyValue keyValue = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_keyvalue()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_range;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Range range = 2;
            case 2: {
                if (tag == 18) {
parse_range:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_range()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_setup;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Setup setup = 3;
            case 3: {
                if (tag == 26) {
parse_setup:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_setup()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_p2pOperation;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.P2POperation p2pOperation = 4;
            case 4: {
                if (tag == 34) {
parse_p2pOperation:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_p2poperation()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_getLog;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.GetLog getLog = 6;
            case 6: {
                if (tag == 50) {
parse_getLog:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_getlog()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(58)) goto parse_security;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Security security = 7;
            case 7: {
                if (tag == 58) {
parse_security:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_security()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_pinOp;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.PinOperation pinOp = 8;
            case 8: {
                if (tag == 66) {
parse_pinOp:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_pinop()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(74)) goto parse_batch;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Batch batch = 9;
            case 9: {
                if (tag == 74) {
parse_batch:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_batch()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Body)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Body)
    return false;
#undef DO_
}

void Command_Body::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Body)
    // optional .com.seagate.kinetic.proto.Command.KeyValue keyValue = 1;
    if (has_keyvalue()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            1, this->keyvalue(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Range range = 2;
    if (has_range()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            2, this->range(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Setup setup = 3;
    if (has_setup()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            3, this->setup(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.P2POperation p2pOperation = 4;
    if (has_p2poperation()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, this->p2poperation(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog getLog = 6;
    if (has_getlog()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            6, this->getlog(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Security security = 7;
    if (has_security()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            7, this->security(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.PinOperation pinOp = 8;
    if (has_pinop()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            8, this->pinop(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Batch batch = 9;
    if (has_batch()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            9, this->batch(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Body)
}

::google::protobuf::uint8* Command_Body::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Body)
    // optional .com.seagate.kinetic.proto.Command.KeyValue keyValue = 1;
    if (has_keyvalue()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     1, this->keyvalue(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Range range = 2;
    if (has_range()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     2, this->range(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Setup setup = 3;
    if (has_setup()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     3, this->setup(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.P2POperation p2pOperation = 4;
    if (has_p2poperation()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     4, this->p2poperation(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog getLog = 6;
    if (has_getlog()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     6, this->getlog(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Security security = 7;
    if (has_security()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     7, this->security(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.PinOperation pinOp = 8;
    if (has_pinop()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     8, this->pinop(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Batch batch = 9;
    if (has_batch()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     9, this->batch(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Body)
    return target;
}

int Command_Body::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.KeyValue keyValue = 1;
        if (has_keyvalue()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->keyvalue());
        }

        // optional .com.seagate.kinetic.proto.Command.Range range = 2;
        if (has_range()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->range());
        }

        // optional .com.seagate.kinetic.proto.Command.Setup setup = 3;
        if (has_setup()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->setup());
        }

        // optional .com.seagate.kinetic.proto.Command.P2POperation p2pOperation = 4;
        if (has_p2poperation()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->p2poperation());
        }

        // optional .com.seagate.kinetic.proto.Command.GetLog getLog = 6;
        if (has_getlog()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->getlog());
        }

        // optional .com.seagate.kinetic.proto.Command.Security security = 7;
        if (has_security()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->security());
        }

        // optional .com.seagate.kinetic.proto.Command.PinOperation pinOp = 8;
        if (has_pinop()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->pinop());
        }

        // optional .com.seagate.kinetic.proto.Command.Batch batch = 9;
        if (has_batch()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->batch());
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

void Command_Body::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Body* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Body*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Body::MergeFrom(const Command_Body& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_keyvalue()) {
            mutable_keyvalue()->::com::seagate::kinetic::proto::Command_KeyValue::MergeFrom(from.keyvalue());
        }
        if (from.has_range()) {
            mutable_range()->::com::seagate::kinetic::proto::Command_Range::MergeFrom(from.range());
        }
        if (from.has_setup()) {
            mutable_setup()->::com::seagate::kinetic::proto::Command_Setup::MergeFrom(from.setup());
        }
        if (from.has_p2poperation()) {
            mutable_p2poperation()->::com::seagate::kinetic::proto::Command_P2POperation::MergeFrom(from.p2poperation());
        }
        if (from.has_getlog()) {
            mutable_getlog()->::com::seagate::kinetic::proto::Command_GetLog::MergeFrom(from.getlog());
        }
        if (from.has_security()) {
            mutable_security()->::com::seagate::kinetic::proto::Command_Security::MergeFrom(from.security());
        }
        if (from.has_pinop()) {
            mutable_pinop()->::com::seagate::kinetic::proto::Command_PinOperation::MergeFrom(from.pinop());
        }
        if (from.has_batch()) {
            mutable_batch()->::com::seagate::kinetic::proto::Command_Batch::MergeFrom(from.batch());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Body::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Body::CopyFrom(const Command_Body& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Body::IsInitialized() const {

    return true;
}

void Command_Body::Swap(Command_Body* other) {
    if (other != this) {
        std::swap(keyvalue_, other->keyvalue_);
        std::swap(range_, other->range_);
        std::swap(setup_, other->setup_);
        std::swap(p2poperation_, other->p2poperation_);
        std::swap(getlog_, other->getlog_);
        std::swap(security_, other->security_);
        std::swap(pinop_, other->pinop_);
        std::swap(batch_, other->batch_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Body::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Body_descriptor_;
    metadata.reflection = Command_Body_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Batch::kCountFieldNumber;
const int Command_Batch::kSequenceFieldNumber;
const int Command_Batch::kFailedSequenceFieldNumber;
#endif  // !_MSC_VER

Command_Batch::Command_Batch()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Batch)
}

void Command_Batch::InitAsDefaultInstance() {
}

Command_Batch::Command_Batch(const Command_Batch& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Batch)
}

void Command_Batch::SharedCtor() {
    _cached_size_ = 0;
    count_ = 0;
    failedsequence_ = GOOGLE_LONGLONG(0);
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Batch::~Command_Batch() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Batch)
    SharedDtor();
}

void Command_Batch::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_Batch::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Batch::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Batch_descriptor_;
}

const Command_Batch& Command_Batch::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Batch* Command_Batch::default_instance_ = NULL;

Command_Batch* Command_Batch::New() const {
    return new Command_Batch;
}

void Command_Batch::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_Batch*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    ZR_(failedsequence_, count_);

#undef OFFSET_OF_FIELD_
#undef ZR_

    sequence_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Batch::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Batch)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional int32 count = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32 > (
                             input, &count_)));
                    set_has_count();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_sequence;
                break;
            }

            // repeated int64 sequence = 2 [packed = true];
            case 2: {
                if (tag == 18) {
parse_sequence:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, this->mutable_sequence())));
                }
                else if (tag == 16) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             1, 18, input, this->mutable_sequence())));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_failedSequence;
                break;
            }

            // optional int64 failedSequence = 3;
            case 3: {
                if (tag == 24) {
parse_failedSequence:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &failedsequence_)));
                    set_has_failedsequence();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Batch)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Batch)
    return false;
#undef DO_
}

void Command_Batch::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Batch)
    // optional int32 count = 1;
    if (has_count()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->count(), output);
    }

    // repeated int64 sequence = 2 [packed = true];
    if (this->sequence_size() > 0) {
        ::google::protobuf::internal::WireFormatLite::WriteTag(2, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
        output->WriteVarint32(_sequence_cached_byte_size_);
    }
    for (int i = 0; i < this->sequence_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64NoTag(
            this->sequence(i), output);
    }

    // optional int64 failedSequence = 3;
    if (has_failedsequence()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->failedsequence(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Batch)
}

::google::protobuf::uint8* Command_Batch::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Batch)
    // optional int32 count = 1;
    if (has_count()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->count(), target);
    }

    // repeated int64 sequence = 2 [packed = true];
    if (this->sequence_size() > 0) {
        target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
                     2,
                     ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
                     target);
        target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
                     _sequence_cached_byte_size_, target);
    }
    for (int i = 0; i < this->sequence_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteInt64NoTagToArray(this->sequence(i), target);
    }

    // optional int64 failedSequence = 3;
    if (has_failedsequence()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->failedsequence(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Batch)
    return target;
}

int Command_Batch::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int32 count = 1;
        if (has_count()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(
                              this->count());
        }

        // optional int64 failedSequence = 3;
        if (has_failedsequence()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->failedsequence());
        }

    }
    // repeated int64 sequence = 2 [packed = true];
    {
        int data_size = 0;
        for (int i = 0; i < this->sequence_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::
                         Int64Size(this->sequence(i));
        }
        if (data_size > 0) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
        }
        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _sequence_cached_byte_size_ = data_size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
        total_size += data_size;
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

void Command_Batch::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Batch* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Batch*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Batch::MergeFrom(const Command_Batch& from) {
    GOOGLE_CHECK_NE(&from, this);
    sequence_.MergeFrom(from.sequence_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_count()) {
            set_count(from.count());
        }
        if (from.has_failedsequence()) {
            set_failedsequence(from.failedsequence());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Batch::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Batch::CopyFrom(const Command_Batch& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Batch::IsInitialized() const {

    return true;
}

void Command_Batch::Swap(Command_Batch* other) {
    if (other != this) {
        std::swap(count_, other->count_);
        sequence_.Swap(&other->sequence_);
        std::swap(failedsequence_, other->failedsequence_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Batch::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Batch_descriptor_;
    metadata.reflection = Command_Batch_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

const ::google::protobuf::EnumDescriptor* Command_Status_StatusCode_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Status_StatusCode_descriptor_;
}
bool Command_Status_StatusCode_IsValid(int value) {
    switch (value) {
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_Status_StatusCode Command_Status::INVALID_STATUS_CODE;
const Command_Status_StatusCode Command_Status::NOT_ATTEMPTED;
const Command_Status_StatusCode Command_Status::SUCCESS;
const Command_Status_StatusCode Command_Status::HMAC_FAILURE;
const Command_Status_StatusCode Command_Status::NOT_AUTHORIZED;
const Command_Status_StatusCode Command_Status::VERSION_FAILURE;
const Command_Status_StatusCode Command_Status::INTERNAL_ERROR;
const Command_Status_StatusCode Command_Status::HEADER_REQUIRED;
const Command_Status_StatusCode Command_Status::NOT_FOUND;
const Command_Status_StatusCode Command_Status::VERSION_MISMATCH;
const Command_Status_StatusCode Command_Status::SERVICE_BUSY;
const Command_Status_StatusCode Command_Status::EXPIRED;
const Command_Status_StatusCode Command_Status::DATA_ERROR;
const Command_Status_StatusCode Command_Status::PERM_DATA_ERROR;
const Command_Status_StatusCode Command_Status::REMOTE_CONNECTION_ERROR;
const Command_Status_StatusCode Command_Status::NO_SPACE;
const Command_Status_StatusCode Command_Status::NO_SUCH_HMAC_ALGORITHM;
const Command_Status_StatusCode Command_Status::INVALID_REQUEST;
const Command_Status_StatusCode Command_Status::NESTED_OPERATION_ERRORS;
const Command_Status_StatusCode Command_Status::DEVICE_LOCKED;
const Command_Status_StatusCode Command_Status::DEVICE_ALREADY_UNLOCKED;
const Command_Status_StatusCode Command_Status::CONNECTION_TERMINATED;
const Command_Status_StatusCode Command_Status::INVALID_BATCH;
const Command_Status_StatusCode Command_Status::StatusCode_MIN;
const Command_Status_StatusCode Command_Status::StatusCode_MAX;
const int Command_Status::StatusCode_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command_Status::kCodeFieldNumber;
const int Command_Status::kStatusMessageFieldNumber;
const int Command_Status::kDetailedMessageFieldNumber;
#endif  // !_MSC_VER

Command_Status::Command_Status()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Status)
}

void Command_Status::InitAsDefaultInstance() {
}

Command_Status::Command_Status(const Command_Status& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Status)
}

void Command_Status::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    code_ = -1;
    statusmessage_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    detailedmessage_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Status::~Command_Status() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Status)
    SharedDtor();
}

void Command_Status::SharedDtor() {
    if (statusmessage_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete statusmessage_;
    }
    if (detailedmessage_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete detailedmessage_;
    }
    if (this != default_instance_) {
    }
}

void Command_Status::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Status::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Status_descriptor_;
}

const Command_Status& Command_Status::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Status* Command_Status::default_instance_ = NULL;

Command_Status* Command_Status::New() const {
    return new Command_Status;
}

void Command_Status::Clear() {
    if (_has_bits_[0 / 32] & 7) {
        code_ = -1;
        if (has_statusmessage()) {
            if (statusmessage_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                statusmessage_->clear();
            }
        }
        if (has_detailedmessage()) {
            if (detailedmessage_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                detailedmessage_->clear();
            }
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Status::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Status)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.Status.StatusCode code = 1;
            case 1: {
                if (tag == 8) {
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Status_StatusCode_IsValid(value)) {
                        set_code(static_cast<::com::seagate::kinetic::proto::Command_Status_StatusCode>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(1, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_statusMessage;
                break;
            }

            // optional string statusMessage = 2;
            case 2: {
                if (tag == 18) {
parse_statusMessage:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_statusmessage()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->statusmessage().data(), this->statusmessage().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "statusmessage");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_detailedMessage;
                break;
            }

            // optional bytes detailedMessage = 3;
            case 3: {
                if (tag == 26) {
parse_detailedMessage:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_detailedmessage()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Status)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Status)
    return false;
#undef DO_
}

void Command_Status::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Status)
    // optional .com.seagate.kinetic.proto.Command.Status.StatusCode code = 1;
    if (has_code()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            1, this->code(), output);
    }

    // optional string statusMessage = 2;
    if (has_statusmessage()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->statusmessage().data(), this->statusmessage().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "statusmessage");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            2, this->statusmessage(), output);
    }

    // optional bytes detailedMessage = 3;
    if (has_detailedmessage()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->detailedmessage(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Status)
}

::google::protobuf::uint8* Command_Status::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Status)
    // optional .com.seagate.kinetic.proto.Command.Status.StatusCode code = 1;
    if (has_code()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     1, this->code(), target);
    }

    // optional string statusMessage = 2;
    if (has_statusmessage()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->statusmessage().data(), this->statusmessage().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "statusmessage");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                2, this->statusmessage(), target);
    }

    // optional bytes detailedMessage = 3;
    if (has_detailedmessage()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->detailedmessage(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Status)
    return target;
}

int Command_Status::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.Status.StatusCode code = 1;
        if (has_code()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->code());
        }

        // optional string statusMessage = 2;
        if (has_statusmessage()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->statusmessage());
        }

        // optional bytes detailedMessage = 3;
        if (has_detailedmessage()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->detailedmessage());
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

void Command_Status::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Status* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Status*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Status::MergeFrom(const Command_Status& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_code()) {
            set_code(from.code());
        }
        if (from.has_statusmessage()) {
            set_statusmessage(from.statusmessage());
        }
        if (from.has_detailedmessage()) {
            set_detailedmessage(from.detailedmessage());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Status::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Status::CopyFrom(const Command_Status& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Status::IsInitialized() const {

    return true;
}

void Command_Status::Swap(Command_Status* other) {
    if (other != this) {
        std::swap(code_, other->code_);
        std::swap(statusmessage_, other->statusmessage_);
        std::swap(detailedmessage_, other->detailedmessage_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Status::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Status_descriptor_;
    metadata.reflection = Command_Status_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_KeyValue::kNewVersionFieldNumber;
const int Command_KeyValue::kForceFieldNumber;
const int Command_KeyValue::kKeyFieldNumber;
const int Command_KeyValue::kDbVersionFieldNumber;
const int Command_KeyValue::kTagFieldNumber;
const int Command_KeyValue::kAlgorithmFieldNumber;
const int Command_KeyValue::kMetadataOnlyFieldNumber;
const int Command_KeyValue::kSynchronizationFieldNumber;
#endif  // !_MSC_VER

Command_KeyValue::Command_KeyValue()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.KeyValue)
}

void Command_KeyValue::InitAsDefaultInstance() {
}

Command_KeyValue::Command_KeyValue(const Command_KeyValue& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.KeyValue)
}

void Command_KeyValue::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    newversion_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    force_ = false;
    key_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    dbversion_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    tag_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    algorithm_ = -1;
    metadataonly_ = false;
    synchronization_ = -1;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_KeyValue::~Command_KeyValue() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.KeyValue)
    SharedDtor();
}

void Command_KeyValue::SharedDtor() {
    if (newversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete newversion_;
    }
    if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete key_;
    }
    if (dbversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete dbversion_;
    }
    if (tag_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete tag_;
    }
    if (this != default_instance_) {
    }
}

void Command_KeyValue::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_KeyValue::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_KeyValue_descriptor_;
}

const Command_KeyValue& Command_KeyValue::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_KeyValue* Command_KeyValue::default_instance_ = NULL;

Command_KeyValue* Command_KeyValue::New() const {
    return new Command_KeyValue;
}

void Command_KeyValue::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_KeyValue*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 255) {
        ZR_(force_, metadataonly_);
        if (has_newversion()) {
            if (newversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                newversion_->clear();
            }
        }
        if (has_key()) {
            if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                key_->clear();
            }
        }
        if (has_dbversion()) {
            if (dbversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                dbversion_->clear();
            }
        }
        if (has_tag()) {
            if (tag_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                tag_->clear();
            }
        }
        algorithm_ = -1;
        synchronization_ = -1;
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_KeyValue::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.KeyValue)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bytes newVersion = 2;
            case 2: {
                if (tag == 18) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_newversion()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_key;
                break;
            }

            // optional bytes key = 3;
            case 3: {
                if (tag == 26) {
parse_key:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_key()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_dbVersion;
                break;
            }

            // optional bytes dbVersion = 4;
            case 4: {
                if (tag == 34) {
parse_dbVersion:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_dbversion()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(42)) goto parse_tag;
                break;
            }

            // optional bytes tag = 5;
            case 5: {
                if (tag == 42) {
parse_tag:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_tag()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(48)) goto parse_algorithm;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 6;
            case 6: {
                if (tag == 48) {
parse_algorithm:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Algorithm_IsValid(value)) {
                        set_algorithm(static_cast<::com::seagate::kinetic::proto::Command_Algorithm>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(6, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(56)) goto parse_metadataOnly;
                break;
            }

            // optional bool metadataOnly = 7;
            case 7: {
                if (tag == 56) {
parse_metadataOnly:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &metadataonly_)));
                    set_has_metadataonly();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(64)) goto parse_force;
                break;
            }

            // optional bool force = 8;
            case 8: {
                if (tag == 64) {
parse_force:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &force_)));
                    set_has_force();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(72)) goto parse_synchronization;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Synchronization synchronization = 9;
            case 9: {
                if (tag == 72) {
parse_synchronization:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Synchronization_IsValid(value)) {
                        set_synchronization(static_cast<::com::seagate::kinetic::proto::Command_Synchronization>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(9, value);
                    }
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.KeyValue)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.KeyValue)
    return false;
#undef DO_
}

void Command_KeyValue::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.KeyValue)
    // optional bytes newVersion = 2;
    if (has_newversion()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->newversion(), output);
    }

    // optional bytes key = 3;
    if (has_key()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->key(), output);
    }

    // optional bytes dbVersion = 4;
    if (has_dbversion()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            4, this->dbversion(), output);
    }

    // optional bytes tag = 5;
    if (has_tag()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            5, this->tag(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 6;
    if (has_algorithm()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            6, this->algorithm(), output);
    }

    // optional bool metadataOnly = 7;
    if (has_metadataonly()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->metadataonly(), output);
    }

    // optional bool force = 8;
    if (has_force()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->force(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Synchronization synchronization = 9;
    if (has_synchronization()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            9, this->synchronization(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.KeyValue)
}

::google::protobuf::uint8* Command_KeyValue::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.KeyValue)
    // optional bytes newVersion = 2;
    if (has_newversion()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->newversion(), target);
    }

    // optional bytes key = 3;
    if (has_key()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->key(), target);
    }

    // optional bytes dbVersion = 4;
    if (has_dbversion()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                4, this->dbversion(), target);
    }

    // optional bytes tag = 5;
    if (has_tag()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                5, this->tag(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 6;
    if (has_algorithm()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     6, this->algorithm(), target);
    }

    // optional bool metadataOnly = 7;
    if (has_metadataonly()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->metadataonly(), target);
    }

    // optional bool force = 8;
    if (has_force()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->force(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Synchronization synchronization = 9;
    if (has_synchronization()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     9, this->synchronization(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.KeyValue)
    return target;
}

int Command_KeyValue::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bytes newVersion = 2;
        if (has_newversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->newversion());
        }

        // optional bool force = 8;
        if (has_force()) {
            total_size += 1 + 1;
        }

        // optional bytes key = 3;
        if (has_key()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->key());
        }

        // optional bytes dbVersion = 4;
        if (has_dbversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->dbversion());
        }

        // optional bytes tag = 5;
        if (has_tag()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->tag());
        }

        // optional .com.seagate.kinetic.proto.Command.Algorithm algorithm = 6;
        if (has_algorithm()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->algorithm());
        }

        // optional bool metadataOnly = 7;
        if (has_metadataonly()) {
            total_size += 1 + 1;
        }

        // optional .com.seagate.kinetic.proto.Command.Synchronization synchronization = 9;
        if (has_synchronization()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->synchronization());
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

void Command_KeyValue::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_KeyValue* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_KeyValue*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_KeyValue::MergeFrom(const Command_KeyValue& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_newversion()) {
            set_newversion(from.newversion());
        }
        if (from.has_force()) {
            set_force(from.force());
        }
        if (from.has_key()) {
            set_key(from.key());
        }
        if (from.has_dbversion()) {
            set_dbversion(from.dbversion());
        }
        if (from.has_tag()) {
            set_tag(from.tag());
        }
        if (from.has_algorithm()) {
            set_algorithm(from.algorithm());
        }
        if (from.has_metadataonly()) {
            set_metadataonly(from.metadataonly());
        }
        if (from.has_synchronization()) {
            set_synchronization(from.synchronization());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_KeyValue::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_KeyValue::CopyFrom(const Command_KeyValue& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_KeyValue::IsInitialized() const {

    return true;
}

void Command_KeyValue::Swap(Command_KeyValue* other) {
    if (other != this) {
        std::swap(newversion_, other->newversion_);
        std::swap(force_, other->force_);
        std::swap(key_, other->key_);
        std::swap(dbversion_, other->dbversion_);
        std::swap(tag_, other->tag_);
        std::swap(algorithm_, other->algorithm_);
        std::swap(metadataonly_, other->metadataonly_);
        std::swap(synchronization_, other->synchronization_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_KeyValue::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_KeyValue_descriptor_;
    metadata.reflection = Command_KeyValue_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Range::kStartKeyFieldNumber;
const int Command_Range::kEndKeyFieldNumber;
const int Command_Range::kStartKeyInclusiveFieldNumber;
const int Command_Range::kEndKeyInclusiveFieldNumber;
const int Command_Range::kMaxReturnedFieldNumber;
const int Command_Range::kReverseFieldNumber;
const int Command_Range::kKeysFieldNumber;
#endif  // !_MSC_VER

Command_Range::Command_Range()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Range)
}

void Command_Range::InitAsDefaultInstance() {
}

Command_Range::Command_Range(const Command_Range& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Range)
}

void Command_Range::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    startkey_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    endkey_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    startkeyinclusive_ = false;
    endkeyinclusive_ = false;
    maxreturned_ = 0;
    reverse_ = false;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Range::~Command_Range() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Range)
    SharedDtor();
}

void Command_Range::SharedDtor() {
    if (startkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete startkey_;
    }
    if (endkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete endkey_;
    }
    if (this != default_instance_) {
    }
}

void Command_Range::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Range::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Range_descriptor_;
}

const Command_Range& Command_Range::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Range* Command_Range::default_instance_ = NULL;

Command_Range* Command_Range::New() const {
    return new Command_Range;
}

void Command_Range::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_Range*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 63) {
        ZR_(startkeyinclusive_, maxreturned_);
        if (has_startkey()) {
            if (startkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                startkey_->clear();
            }
        }
        if (has_endkey()) {
            if (endkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                endkey_->clear();
            }
        }
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    keys_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Range::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Range)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bytes startKey = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_startkey()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_endKey;
                break;
            }

            // optional bytes endKey = 2;
            case 2: {
                if (tag == 18) {
parse_endKey:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_endkey()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_startKeyInclusive;
                break;
            }

            // optional bool startKeyInclusive = 3;
            case 3: {
                if (tag == 24) {
parse_startKeyInclusive:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &startkeyinclusive_)));
                    set_has_startkeyinclusive();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_endKeyInclusive;
                break;
            }

            // optional bool endKeyInclusive = 4;
            case 4: {
                if (tag == 32) {
parse_endKeyInclusive:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &endkeyinclusive_)));
                    set_has_endkeyinclusive();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(40)) goto parse_maxReturned;
                break;
            }

            // optional int32 maxReturned = 5;
            case 5: {
                if (tag == 40) {
parse_maxReturned:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32 > (
                             input, &maxreturned_)));
                    set_has_maxreturned();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(48)) goto parse_reverse;
                break;
            }

            // optional bool reverse = 6;
            case 6: {
                if (tag == 48) {
parse_reverse:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &reverse_)));
                    set_has_reverse();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_keys;
                break;
            }

            // repeated bytes keys = 8;
            case 8: {
                if (tag == 66) {
parse_keys:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->add_keys()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_keys;
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Range)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Range)
    return false;
#undef DO_
}

void Command_Range::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Range)
    // optional bytes startKey = 1;
    if (has_startkey()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            1, this->startkey(), output);
    }

    // optional bytes endKey = 2;
    if (has_endkey()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->endkey(), output);
    }

    // optional bool startKeyInclusive = 3;
    if (has_startkeyinclusive()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->startkeyinclusive(), output);
    }

    // optional bool endKeyInclusive = 4;
    if (has_endkeyinclusive()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->endkeyinclusive(), output);
    }

    // optional int32 maxReturned = 5;
    if (has_maxreturned()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->maxreturned(), output);
    }

    // optional bool reverse = 6;
    if (has_reverse()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->reverse(), output);
    }

    // repeated bytes keys = 8;
    for (int i = 0; i < this->keys_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteBytes(
            8, this->keys(i), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Range)
}

::google::protobuf::uint8* Command_Range::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Range)
    // optional bytes startKey = 1;
    if (has_startkey()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                1, this->startkey(), target);
    }

    // optional bytes endKey = 2;
    if (has_endkey()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->endkey(), target);
    }

    // optional bool startKeyInclusive = 3;
    if (has_startkeyinclusive()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->startkeyinclusive(), target);
    }

    // optional bool endKeyInclusive = 4;
    if (has_endkeyinclusive()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->endkeyinclusive(), target);
    }

    // optional int32 maxReturned = 5;
    if (has_maxreturned()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->maxreturned(), target);
    }

    // optional bool reverse = 6;
    if (has_reverse()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->reverse(), target);
    }

    // repeated bytes keys = 8;
    for (int i = 0; i < this->keys_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteBytesToArray(8, this->keys(i), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Range)
    return target;
}

int Command_Range::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bytes startKey = 1;
        if (has_startkey()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->startkey());
        }

        // optional bytes endKey = 2;
        if (has_endkey()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->endkey());
        }

        // optional bool startKeyInclusive = 3;
        if (has_startkeyinclusive()) {
            total_size += 1 + 1;
        }

        // optional bool endKeyInclusive = 4;
        if (has_endkeyinclusive()) {
            total_size += 1 + 1;
        }

        // optional int32 maxReturned = 5;
        if (has_maxreturned()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(
                              this->maxreturned());
        }

        // optional bool reverse = 6;
        if (has_reverse()) {
            total_size += 1 + 1;
        }

    }
    // repeated bytes keys = 8;
    total_size += 1 * this->keys_size();
    for (int i = 0; i < this->keys_size(); i++) {
        total_size += ::google::protobuf::internal::WireFormatLite::BytesSize(
                          this->keys(i));
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

void Command_Range::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Range* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Range*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Range::MergeFrom(const Command_Range& from) {
    GOOGLE_CHECK_NE(&from, this);
    keys_.MergeFrom(from.keys_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_startkey()) {
            set_startkey(from.startkey());
        }
        if (from.has_endkey()) {
            set_endkey(from.endkey());
        }
        if (from.has_startkeyinclusive()) {
            set_startkeyinclusive(from.startkeyinclusive());
        }
        if (from.has_endkeyinclusive()) {
            set_endkeyinclusive(from.endkeyinclusive());
        }
        if (from.has_maxreturned()) {
            set_maxreturned(from.maxreturned());
        }
        if (from.has_reverse()) {
            set_reverse(from.reverse());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Range::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Range::CopyFrom(const Command_Range& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Range::IsInitialized() const {

    return true;
}

void Command_Range::Swap(Command_Range* other) {
    if (other != this) {
        std::swap(startkey_, other->startkey_);
        std::swap(endkey_, other->endkey_);
        std::swap(startkeyinclusive_, other->startkeyinclusive_);
        std::swap(endkeyinclusive_, other->endkeyinclusive_);
        std::swap(maxreturned_, other->maxreturned_);
        std::swap(reverse_, other->reverse_);
        keys_.Swap(&other->keys_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Range::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Range_descriptor_;
    metadata.reflection = Command_Range_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Setup::kNewClusterVersionFieldNumber;
const int Command_Setup::kFirmwareDownloadFieldNumber;
#endif  // !_MSC_VER

Command_Setup::Command_Setup()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Setup)
}

void Command_Setup::InitAsDefaultInstance() {
}

Command_Setup::Command_Setup(const Command_Setup& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Setup)
}

void Command_Setup::SharedCtor() {
    _cached_size_ = 0;
    newclusterversion_ = GOOGLE_LONGLONG(0);
    firmwaredownload_ = false;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Setup::~Command_Setup() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Setup)
    SharedDtor();
}

void Command_Setup::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_Setup::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Setup::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Setup_descriptor_;
}

const Command_Setup& Command_Setup::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Setup* Command_Setup::default_instance_ = NULL;

Command_Setup* Command_Setup::New() const {
    return new Command_Setup;
}

void Command_Setup::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_Setup*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    ZR_(newclusterversion_, firmwaredownload_);

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Setup::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Setup)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional int64 newClusterVersion = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &newclusterversion_)));
                    set_has_newclusterversion();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(40)) goto parse_firmwareDownload;
                break;
            }

            // optional bool firmwareDownload = 5;
            case 5: {
                if (tag == 40) {
parse_firmwareDownload:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &firmwaredownload_)));
                    set_has_firmwaredownload();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Setup)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Setup)
    return false;
#undef DO_
}

void Command_Setup::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Setup)
    // optional int64 newClusterVersion = 1;
    if (has_newclusterversion()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->newclusterversion(), output);
    }

    // optional bool firmwareDownload = 5;
    if (has_firmwaredownload()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->firmwaredownload(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Setup)
}

::google::protobuf::uint8* Command_Setup::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Setup)
    // optional int64 newClusterVersion = 1;
    if (has_newclusterversion()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->newclusterversion(), target);
    }

    // optional bool firmwareDownload = 5;
    if (has_firmwaredownload()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->firmwaredownload(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Setup)
    return target;
}

int Command_Setup::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 newClusterVersion = 1;
        if (has_newclusterversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->newclusterversion());
        }

        // optional bool firmwareDownload = 5;
        if (has_firmwaredownload()) {
            total_size += 1 + 1;
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

void Command_Setup::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Setup* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Setup*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Setup::MergeFrom(const Command_Setup& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_newclusterversion()) {
            set_newclusterversion(from.newclusterversion());
        }
        if (from.has_firmwaredownload()) {
            set_firmwaredownload(from.firmwaredownload());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Setup::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Setup::CopyFrom(const Command_Setup& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Setup::IsInitialized() const {

    return true;
}

void Command_Setup::Swap(Command_Setup* other) {
    if (other != this) {
        std::swap(newclusterversion_, other->newclusterversion_);
        std::swap(firmwaredownload_, other->firmwaredownload_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Setup::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Setup_descriptor_;
    metadata.reflection = Command_Setup_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_P2POperation_Operation::kKeyFieldNumber;
const int Command_P2POperation_Operation::kVersionFieldNumber;
const int Command_P2POperation_Operation::kNewKeyFieldNumber;
const int Command_P2POperation_Operation::kForceFieldNumber;
const int Command_P2POperation_Operation::kStatusFieldNumber;
const int Command_P2POperation_Operation::kP2PopFieldNumber;
#endif  // !_MSC_VER

Command_P2POperation_Operation::Command_P2POperation_Operation()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.P2POperation.Operation)
}

void Command_P2POperation_Operation::InitAsDefaultInstance() {
    status_ = const_cast<::com::seagate::kinetic::proto::Command_Status*>(&::com::seagate::kinetic::proto::Command_Status::default_instance());
    p2pop_ = const_cast<::com::seagate::kinetic::proto::Command_P2POperation*>(&::com::seagate::kinetic::proto::Command_P2POperation::default_instance());
}

Command_P2POperation_Operation::Command_P2POperation_Operation(const Command_P2POperation_Operation& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.P2POperation.Operation)
}

void Command_P2POperation_Operation::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    key_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    version_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    newkey_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    force_ = false;
    status_ = NULL;
    p2pop_ = NULL;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_P2POperation_Operation::~Command_P2POperation_Operation() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    SharedDtor();
}

void Command_P2POperation_Operation::SharedDtor() {
    if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete key_;
    }
    if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete version_;
    }
    if (newkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete newkey_;
    }
    if (this != default_instance_) {
        delete status_;
        delete p2pop_;
    }
}

void Command_P2POperation_Operation::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_P2POperation_Operation::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_P2POperation_Operation_descriptor_;
}

const Command_P2POperation_Operation& Command_P2POperation_Operation::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_P2POperation_Operation* Command_P2POperation_Operation::default_instance_ = NULL;

Command_P2POperation_Operation* Command_P2POperation_Operation::New() const {
    return new Command_P2POperation_Operation;
}

void Command_P2POperation_Operation::Clear() {
    if (_has_bits_[0 / 32] & 63) {
        if (has_key()) {
            if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                key_->clear();
            }
        }
        if (has_version()) {
            if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                version_->clear();
            }
        }
        if (has_newkey()) {
            if (newkey_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                newkey_->clear();
            }
        }
        force_ = false;
        if (has_status()) {
            if (status_ != NULL) status_->::com::seagate::kinetic::proto::Command_Status::Clear();
        }
        if (has_p2pop()) {
            if (p2pop_ != NULL) p2pop_->::com::seagate::kinetic::proto::Command_P2POperation::Clear();
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_P2POperation_Operation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bytes key = 3;
            case 3: {
                if (tag == 26) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_key()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_version;
                break;
            }

            // optional bytes version = 4;
            case 4: {
                if (tag == 34) {
parse_version:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_version()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(42)) goto parse_newKey;
                break;
            }

            // optional bytes newKey = 5;
            case 5: {
                if (tag == 42) {
parse_newKey:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_newkey()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(48)) goto parse_force;
                break;
            }

            // optional bool force = 6;
            case 6: {
                if (tag == 48) {
parse_force:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &force_)));
                    set_has_force();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(58)) goto parse_status;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Status status = 7;
            case 7: {
                if (tag == 58) {
parse_status:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_status()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_p2pop;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.P2POperation p2pop = 8;
            case 8: {
                if (tag == 66) {
parse_p2pop:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_p2pop()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    return false;
#undef DO_
}

void Command_P2POperation_Operation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    // optional bytes key = 3;
    if (has_key()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->key(), output);
    }

    // optional bytes version = 4;
    if (has_version()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            4, this->version(), output);
    }

    // optional bytes newKey = 5;
    if (has_newkey()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            5, this->newkey(), output);
    }

    // optional bool force = 6;
    if (has_force()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->force(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Status status = 7;
    if (has_status()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            7, this->status(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.P2POperation p2pop = 8;
    if (has_p2pop()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            8, this->p2pop(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.P2POperation.Operation)
}

::google::protobuf::uint8* Command_P2POperation_Operation::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    // optional bytes key = 3;
    if (has_key()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->key(), target);
    }

    // optional bytes version = 4;
    if (has_version()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                4, this->version(), target);
    }

    // optional bytes newKey = 5;
    if (has_newkey()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                5, this->newkey(), target);
    }

    // optional bool force = 6;
    if (has_force()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->force(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Status status = 7;
    if (has_status()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     7, this->status(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.P2POperation p2pop = 8;
    if (has_p2pop()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     8, this->p2pop(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.P2POperation.Operation)
    return target;
}

int Command_P2POperation_Operation::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bytes key = 3;
        if (has_key()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->key());
        }

        // optional bytes version = 4;
        if (has_version()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->version());
        }

        // optional bytes newKey = 5;
        if (has_newkey()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->newkey());
        }

        // optional bool force = 6;
        if (has_force()) {
            total_size += 1 + 1;
        }

        // optional .com.seagate.kinetic.proto.Command.Status status = 7;
        if (has_status()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->status());
        }

        // optional .com.seagate.kinetic.proto.Command.P2POperation p2pop = 8;
        if (has_p2pop()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->p2pop());
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

void Command_P2POperation_Operation::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_P2POperation_Operation* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_P2POperation_Operation*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_P2POperation_Operation::MergeFrom(const Command_P2POperation_Operation& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_key()) {
            set_key(from.key());
        }
        if (from.has_version()) {
            set_version(from.version());
        }
        if (from.has_newkey()) {
            set_newkey(from.newkey());
        }
        if (from.has_force()) {
            set_force(from.force());
        }
        if (from.has_status()) {
            mutable_status()->::com::seagate::kinetic::proto::Command_Status::MergeFrom(from.status());
        }
        if (from.has_p2pop()) {
            mutable_p2pop()->::com::seagate::kinetic::proto::Command_P2POperation::MergeFrom(from.p2pop());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_P2POperation_Operation::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_P2POperation_Operation::CopyFrom(const Command_P2POperation_Operation& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_P2POperation_Operation::IsInitialized() const {

    return true;
}

void Command_P2POperation_Operation::Swap(Command_P2POperation_Operation* other) {
    if (other != this) {
        std::swap(key_, other->key_);
        std::swap(version_, other->version_);
        std::swap(newkey_, other->newkey_);
        std::swap(force_, other->force_);
        std::swap(status_, other->status_);
        std::swap(p2pop_, other->p2pop_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_P2POperation_Operation::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_P2POperation_Operation_descriptor_;
    metadata.reflection = Command_P2POperation_Operation_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_P2POperation_Peer::kHostnameFieldNumber;
const int Command_P2POperation_Peer::kPortFieldNumber;
const int Command_P2POperation_Peer::kTlsFieldNumber;
#endif  // !_MSC_VER

Command_P2POperation_Peer::Command_P2POperation_Peer()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.P2POperation.Peer)
}

void Command_P2POperation_Peer::InitAsDefaultInstance() {
}

Command_P2POperation_Peer::Command_P2POperation_Peer(const Command_P2POperation_Peer& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.P2POperation.Peer)
}

void Command_P2POperation_Peer::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    hostname_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    port_ = 0;
    tls_ = false;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_P2POperation_Peer::~Command_P2POperation_Peer() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    SharedDtor();
}

void Command_P2POperation_Peer::SharedDtor() {
    if (hostname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete hostname_;
    }
    if (this != default_instance_) {
    }
}

void Command_P2POperation_Peer::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_P2POperation_Peer::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_P2POperation_Peer_descriptor_;
}

const Command_P2POperation_Peer& Command_P2POperation_Peer::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_P2POperation_Peer* Command_P2POperation_Peer::default_instance_ = NULL;

Command_P2POperation_Peer* Command_P2POperation_Peer::New() const {
    return new Command_P2POperation_Peer;
}

void Command_P2POperation_Peer::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_P2POperation_Peer*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 7) {
        ZR_(port_, tls_);
        if (has_hostname()) {
            if (hostname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                hostname_->clear();
            }
        }
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_P2POperation_Peer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string hostname = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_hostname()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->hostname().data(), this->hostname().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "hostname");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(16)) goto parse_port;
                break;
            }

            // optional int32 port = 2;
            case 2: {
                if (tag == 16) {
parse_port:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32 > (
                             input, &port_)));
                    set_has_port();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_tls;
                break;
            }

            // optional bool tls = 3;
            case 3: {
                if (tag == 24) {
parse_tls:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &tls_)));
                    set_has_tls();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    return false;
#undef DO_
}

void Command_P2POperation_Peer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    // optional string hostname = 1;
    if (has_hostname()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->hostname().data(), this->hostname().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "hostname");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->hostname(), output);
    }

    // optional int32 port = 2;
    if (has_port()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->port(), output);
    }

    // optional bool tls = 3;
    if (has_tls()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->tls(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.P2POperation.Peer)
}

::google::protobuf::uint8* Command_P2POperation_Peer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    // optional string hostname = 1;
    if (has_hostname()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->hostname().data(), this->hostname().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "hostname");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                1, this->hostname(), target);
    }

    // optional int32 port = 2;
    if (has_port()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->port(), target);
    }

    // optional bool tls = 3;
    if (has_tls()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->tls(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.P2POperation.Peer)
    return target;
}

int Command_P2POperation_Peer::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string hostname = 1;
        if (has_hostname()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->hostname());
        }

        // optional int32 port = 2;
        if (has_port()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(
                              this->port());
        }

        // optional bool tls = 3;
        if (has_tls()) {
            total_size += 1 + 1;
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

void Command_P2POperation_Peer::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_P2POperation_Peer* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_P2POperation_Peer*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_P2POperation_Peer::MergeFrom(const Command_P2POperation_Peer& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_hostname()) {
            set_hostname(from.hostname());
        }
        if (from.has_port()) {
            set_port(from.port());
        }
        if (from.has_tls()) {
            set_tls(from.tls());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_P2POperation_Peer::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_P2POperation_Peer::CopyFrom(const Command_P2POperation_Peer& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_P2POperation_Peer::IsInitialized() const {

    return true;
}

void Command_P2POperation_Peer::Swap(Command_P2POperation_Peer* other) {
    if (other != this) {
        std::swap(hostname_, other->hostname_);
        std::swap(port_, other->port_);
        std::swap(tls_, other->tls_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_P2POperation_Peer::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_P2POperation_Peer_descriptor_;
    metadata.reflection = Command_P2POperation_Peer_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_P2POperation::kPeerFieldNumber;
const int Command_P2POperation::kOperationFieldNumber;
const int Command_P2POperation::kAllChildOperationsSucceededFieldNumber;
#endif  // !_MSC_VER

Command_P2POperation::Command_P2POperation()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.P2POperation)
}

void Command_P2POperation::InitAsDefaultInstance() {
    peer_ = const_cast<::com::seagate::kinetic::proto::Command_P2POperation_Peer*>(&::com::seagate::kinetic::proto::Command_P2POperation_Peer::default_instance());
}

Command_P2POperation::Command_P2POperation(const Command_P2POperation& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.P2POperation)
}

void Command_P2POperation::SharedCtor() {
    _cached_size_ = 0;
    peer_ = NULL;
    allchildoperationssucceeded_ = false;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_P2POperation::~Command_P2POperation() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.P2POperation)
    SharedDtor();
}

void Command_P2POperation::SharedDtor() {
    if (this != default_instance_) {
        delete peer_;
    }
}

void Command_P2POperation::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_P2POperation::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_P2POperation_descriptor_;
}

const Command_P2POperation& Command_P2POperation::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_P2POperation* Command_P2POperation::default_instance_ = NULL;

Command_P2POperation* Command_P2POperation::New() const {
    return new Command_P2POperation;
}

void Command_P2POperation::Clear() {
    if (_has_bits_[0 / 32] & 5) {
        if (has_peer()) {
            if (peer_ != NULL) peer_->::com::seagate::kinetic::proto::Command_P2POperation_Peer::Clear();
        }
        allchildoperationssucceeded_ = false;
    }
    operation_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_P2POperation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.P2POperation)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.P2POperation.Peer peer = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_peer()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_operation;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.P2POperation.Operation operation = 2;
            case 2: {
                if (tag == 18) {
parse_operation:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_operation()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_operation;
                if (input->ExpectTag(24)) goto parse_allChildOperationsSucceeded;
                break;
            }

            // optional bool allChildOperationsSucceeded = 3;
            case 3: {
                if (tag == 24) {
parse_allChildOperationsSucceeded:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &allchildoperationssucceeded_)));
                    set_has_allchildoperationssucceeded();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.P2POperation)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.P2POperation)
    return false;
#undef DO_
}

void Command_P2POperation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.P2POperation)
    // optional .com.seagate.kinetic.proto.Command.P2POperation.Peer peer = 1;
    if (has_peer()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            1, this->peer(), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.P2POperation.Operation operation = 2;
    for (int i = 0; i < this->operation_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            2, this->operation(i), output);
    }

    // optional bool allChildOperationsSucceeded = 3;
    if (has_allchildoperationssucceeded()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->allchildoperationssucceeded(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.P2POperation)
}

::google::protobuf::uint8* Command_P2POperation::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.P2POperation)
    // optional .com.seagate.kinetic.proto.Command.P2POperation.Peer peer = 1;
    if (has_peer()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     1, this->peer(), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.P2POperation.Operation operation = 2;
    for (int i = 0; i < this->operation_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     2, this->operation(i), target);
    }

    // optional bool allChildOperationsSucceeded = 3;
    if (has_allchildoperationssucceeded()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->allchildoperationssucceeded(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.P2POperation)
    return target;
}

int Command_P2POperation::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.P2POperation.Peer peer = 1;
        if (has_peer()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->peer());
        }

        // optional bool allChildOperationsSucceeded = 3;
        if (has_allchildoperationssucceeded()) {
            total_size += 1 + 1;
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.P2POperation.Operation operation = 2;
    total_size += 1 * this->operation_size();
    for (int i = 0; i < this->operation_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->operation(i));
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

void Command_P2POperation::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_P2POperation* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_P2POperation*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_P2POperation::MergeFrom(const Command_P2POperation& from) {
    GOOGLE_CHECK_NE(&from, this);
    operation_.MergeFrom(from.operation_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_peer()) {
            mutable_peer()->::com::seagate::kinetic::proto::Command_P2POperation_Peer::MergeFrom(from.peer());
        }
        if (from.has_allchildoperationssucceeded()) {
            set_allchildoperationssucceeded(from.allchildoperationssucceeded());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_P2POperation::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_P2POperation::CopyFrom(const Command_P2POperation& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_P2POperation::IsInitialized() const {

    return true;
}

void Command_P2POperation::Swap(Command_P2POperation* other) {
    if (other != this) {
        std::swap(peer_, other->peer_);
        operation_.Swap(&other->operation_);
        std::swap(allchildoperationssucceeded_, other->allchildoperationssucceeded_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_P2POperation::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_P2POperation_descriptor_;
    metadata.reflection = Command_P2POperation_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

const ::google::protobuf::EnumDescriptor* Command_GetLog_Type_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Type_descriptor_;
}
bool Command_GetLog_Type_IsValid(int value) {
    switch (value) {
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_GetLog_Type Command_GetLog::INVALID_TYPE;
const Command_GetLog_Type Command_GetLog::UTILIZATIONS;
const Command_GetLog_Type Command_GetLog::TEMPERATURES;
const Command_GetLog_Type Command_GetLog::CAPACITIES;
const Command_GetLog_Type Command_GetLog::CONFIGURATION;
const Command_GetLog_Type Command_GetLog::STATISTICS;
const Command_GetLog_Type Command_GetLog::MESSAGES;
const Command_GetLog_Type Command_GetLog::LIMITS;
const Command_GetLog_Type Command_GetLog::DEVICE;
const Command_GetLog_Type Command_GetLog::Type_MIN;
const Command_GetLog_Type Command_GetLog::Type_MAX;
const int Command_GetLog::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command_GetLog_Utilization::kNameFieldNumber;
const int Command_GetLog_Utilization::kValueFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Utilization::Command_GetLog_Utilization()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Utilization)
}

void Command_GetLog_Utilization::InitAsDefaultInstance() {
}

Command_GetLog_Utilization::Command_GetLog_Utilization(const Command_GetLog_Utilization& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Utilization)
}

void Command_GetLog_Utilization::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    name_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    value_ = 0;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Utilization::~Command_GetLog_Utilization() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    SharedDtor();
}

void Command_GetLog_Utilization::SharedDtor() {
    if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete name_;
    }
    if (this != default_instance_) {
    }
}

void Command_GetLog_Utilization::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Utilization::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Utilization_descriptor_;
}

const Command_GetLog_Utilization& Command_GetLog_Utilization::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Utilization* Command_GetLog_Utilization::default_instance_ = NULL;

Command_GetLog_Utilization* Command_GetLog_Utilization::New() const {
    return new Command_GetLog_Utilization;
}

void Command_GetLog_Utilization::Clear() {
    if (_has_bits_[0 / 32] & 3) {
        if (has_name()) {
            if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                name_->clear();
            }
        }
        value_ = 0;
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Utilization::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string name = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_name()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->name().data(), this->name().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "name");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(21)) goto parse_value;
                break;
            }

            // optional float value = 2;
            case 2: {
                if (tag == 21) {
parse_value:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &value_)));
                    set_has_value();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    return false;
#undef DO_
}

void Command_GetLog_Utilization::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->name(), output);
    }

    // optional float value = 2;
    if (has_value()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->value(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Utilization)
}

::google::protobuf::uint8* Command_GetLog_Utilization::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                1, this->name(), target);
    }

    // optional float value = 2;
    if (has_value()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->value(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Utilization)
    return target;
}

int Command_GetLog_Utilization::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string name = 1;
        if (has_name()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->name());
        }

        // optional float value = 2;
        if (has_value()) {
            total_size += 1 + 4;
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

void Command_GetLog_Utilization::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Utilization* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Utilization*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Utilization::MergeFrom(const Command_GetLog_Utilization& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_name()) {
            set_name(from.name());
        }
        if (from.has_value()) {
            set_value(from.value());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Utilization::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Utilization::CopyFrom(const Command_GetLog_Utilization& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Utilization::IsInitialized() const {

    return true;
}

void Command_GetLog_Utilization::Swap(Command_GetLog_Utilization* other) {
    if (other != this) {
        std::swap(name_, other->name_);
        std::swap(value_, other->value_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Utilization::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Utilization_descriptor_;
    metadata.reflection = Command_GetLog_Utilization_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Temperature::kNameFieldNumber;
const int Command_GetLog_Temperature::kCurrentFieldNumber;
const int Command_GetLog_Temperature::kMinimumFieldNumber;
const int Command_GetLog_Temperature::kMaximumFieldNumber;
const int Command_GetLog_Temperature::kTargetFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Temperature::Command_GetLog_Temperature()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Temperature)
}

void Command_GetLog_Temperature::InitAsDefaultInstance() {
}

Command_GetLog_Temperature::Command_GetLog_Temperature(const Command_GetLog_Temperature& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Temperature)
}

void Command_GetLog_Temperature::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    name_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    current_ = 0;
    minimum_ = 0;
    maximum_ = 0;
    target_ = 0;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Temperature::~Command_GetLog_Temperature() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    SharedDtor();
}

void Command_GetLog_Temperature::SharedDtor() {
    if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete name_;
    }
    if (this != default_instance_) {
    }
}

void Command_GetLog_Temperature::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Temperature::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Temperature_descriptor_;
}

const Command_GetLog_Temperature& Command_GetLog_Temperature::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Temperature* Command_GetLog_Temperature::default_instance_ = NULL;

Command_GetLog_Temperature* Command_GetLog_Temperature::New() const {
    return new Command_GetLog_Temperature;
}

void Command_GetLog_Temperature::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_GetLog_Temperature*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 31) {
        ZR_(current_, target_);
        if (has_name()) {
            if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                name_->clear();
            }
        }
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Temperature::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string name = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_name()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->name().data(), this->name().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "name");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(21)) goto parse_current;
                break;
            }

            // optional float current = 2;
            case 2: {
                if (tag == 21) {
parse_current:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &current_)));
                    set_has_current();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(29)) goto parse_minimum;
                break;
            }

            // optional float minimum = 3;
            case 3: {
                if (tag == 29) {
parse_minimum:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &minimum_)));
                    set_has_minimum();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(37)) goto parse_maximum;
                break;
            }

            // optional float maximum = 4;
            case 4: {
                if (tag == 37) {
parse_maximum:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &maximum_)));
                    set_has_maximum();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(45)) goto parse_target;
                break;
            }

            // optional float target = 5;
            case 5: {
                if (tag == 45) {
parse_target:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &target_)));
                    set_has_target();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    return false;
#undef DO_
}

void Command_GetLog_Temperature::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->name(), output);
    }

    // optional float current = 2;
    if (has_current()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->current(), output);
    }

    // optional float minimum = 3;
    if (has_minimum()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->minimum(), output);
    }

    // optional float maximum = 4;
    if (has_maximum()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->maximum(), output);
    }

    // optional float target = 5;
    if (has_target()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->target(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Temperature)
}

::google::protobuf::uint8* Command_GetLog_Temperature::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                1, this->name(), target);
    }

    // optional float current = 2;
    if (has_current()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->current(), target);
    }

    // optional float minimum = 3;
    if (has_minimum()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->minimum(), target);
    }

    // optional float maximum = 4;
    if (has_maximum()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->maximum(), target);
    }

    // optional float target = 5;
    if (has_target()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->target(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Temperature)
    return target;
}

int Command_GetLog_Temperature::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string name = 1;
        if (has_name()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->name());
        }

        // optional float current = 2;
        if (has_current()) {
            total_size += 1 + 4;
        }

        // optional float minimum = 3;
        if (has_minimum()) {
            total_size += 1 + 4;
        }

        // optional float maximum = 4;
        if (has_maximum()) {
            total_size += 1 + 4;
        }

        // optional float target = 5;
        if (has_target()) {
            total_size += 1 + 4;
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

void Command_GetLog_Temperature::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Temperature* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Temperature*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Temperature::MergeFrom(const Command_GetLog_Temperature& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_name()) {
            set_name(from.name());
        }
        if (from.has_current()) {
            set_current(from.current());
        }
        if (from.has_minimum()) {
            set_minimum(from.minimum());
        }
        if (from.has_maximum()) {
            set_maximum(from.maximum());
        }
        if (from.has_target()) {
            set_target(from.target());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Temperature::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Temperature::CopyFrom(const Command_GetLog_Temperature& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Temperature::IsInitialized() const {

    return true;
}

void Command_GetLog_Temperature::Swap(Command_GetLog_Temperature* other) {
    if (other != this) {
        std::swap(name_, other->name_);
        std::swap(current_, other->current_);
        std::swap(minimum_, other->minimum_);
        std::swap(maximum_, other->maximum_);
        std::swap(target_, other->target_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Temperature::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Temperature_descriptor_;
    metadata.reflection = Command_GetLog_Temperature_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Capacity::kNominalCapacityInBytesFieldNumber;
const int Command_GetLog_Capacity::kPortionFullFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Capacity::Command_GetLog_Capacity()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Capacity)
}

void Command_GetLog_Capacity::InitAsDefaultInstance() {
}

Command_GetLog_Capacity::Command_GetLog_Capacity(const Command_GetLog_Capacity& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Capacity)
}

void Command_GetLog_Capacity::SharedCtor() {
    _cached_size_ = 0;
    nominalcapacityinbytes_ = GOOGLE_ULONGLONG(0);
    portionfull_ = 0;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Capacity::~Command_GetLog_Capacity() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    SharedDtor();
}

void Command_GetLog_Capacity::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_GetLog_Capacity::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Capacity::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Capacity_descriptor_;
}

const Command_GetLog_Capacity& Command_GetLog_Capacity::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Capacity* Command_GetLog_Capacity::default_instance_ = NULL;

Command_GetLog_Capacity* Command_GetLog_Capacity::New() const {
    return new Command_GetLog_Capacity;
}

void Command_GetLog_Capacity::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_GetLog_Capacity*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    ZR_(nominalcapacityinbytes_, portionfull_);

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Capacity::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional uint64 nominalCapacityInBytes = 4;
            case 4: {
                if (tag == 32) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64 > (
                             input, &nominalcapacityinbytes_)));
                    set_has_nominalcapacityinbytes();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(45)) goto parse_portionFull;
                break;
            }

            // optional float portionFull = 5;
            case 5: {
                if (tag == 45) {
parse_portionFull:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT > (
                             input, &portionfull_)));
                    set_has_portionfull();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    return false;
#undef DO_
}

void Command_GetLog_Capacity::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    // optional uint64 nominalCapacityInBytes = 4;
    if (has_nominalcapacityinbytes()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->nominalcapacityinbytes(), output);
    }

    // optional float portionFull = 5;
    if (has_portionfull()) {
        ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->portionfull(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Capacity)
}

::google::protobuf::uint8* Command_GetLog_Capacity::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    // optional uint64 nominalCapacityInBytes = 4;
    if (has_nominalcapacityinbytes()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->nominalcapacityinbytes(), target);
    }

    // optional float portionFull = 5;
    if (has_portionfull()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->portionfull(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Capacity)
    return target;
}

int Command_GetLog_Capacity::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional uint64 nominalCapacityInBytes = 4;
        if (has_nominalcapacityinbytes()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt64Size(
                              this->nominalcapacityinbytes());
        }

        // optional float portionFull = 5;
        if (has_portionfull()) {
            total_size += 1 + 4;
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

void Command_GetLog_Capacity::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Capacity* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Capacity*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Capacity::MergeFrom(const Command_GetLog_Capacity& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_nominalcapacityinbytes()) {
            set_nominalcapacityinbytes(from.nominalcapacityinbytes());
        }
        if (from.has_portionfull()) {
            set_portionfull(from.portionfull());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Capacity::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Capacity::CopyFrom(const Command_GetLog_Capacity& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Capacity::IsInitialized() const {

    return true;
}

void Command_GetLog_Capacity::Swap(Command_GetLog_Capacity* other) {
    if (other != this) {
        std::swap(nominalcapacityinbytes_, other->nominalcapacityinbytes_);
        std::swap(portionfull_, other->portionfull_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Capacity::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Capacity_descriptor_;
    metadata.reflection = Command_GetLog_Capacity_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Configuration_Interface::kNameFieldNumber;
const int Command_GetLog_Configuration_Interface::kMACFieldNumber;
const int Command_GetLog_Configuration_Interface::kIpv4AddressFieldNumber;
const int Command_GetLog_Configuration_Interface::kIpv6AddressFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Configuration_Interface::Command_GetLog_Configuration_Interface()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
}

void Command_GetLog_Configuration_Interface::InitAsDefaultInstance() {
}

Command_GetLog_Configuration_Interface::Command_GetLog_Configuration_Interface(const Command_GetLog_Configuration_Interface& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
}

void Command_GetLog_Configuration_Interface::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    name_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    mac_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ipv4address_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ipv6address_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Configuration_Interface::~Command_GetLog_Configuration_Interface() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    SharedDtor();
}

void Command_GetLog_Configuration_Interface::SharedDtor() {
    if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete name_;
    }
    if (mac_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete mac_;
    }
    if (ipv4address_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete ipv4address_;
    }
    if (ipv6address_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete ipv6address_;
    }
    if (this != default_instance_) {
    }
}

void Command_GetLog_Configuration_Interface::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Configuration_Interface::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Configuration_Interface_descriptor_;
}

const Command_GetLog_Configuration_Interface& Command_GetLog_Configuration_Interface::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Configuration_Interface* Command_GetLog_Configuration_Interface::default_instance_ = NULL;

Command_GetLog_Configuration_Interface* Command_GetLog_Configuration_Interface::New() const {
    return new Command_GetLog_Configuration_Interface;
}

void Command_GetLog_Configuration_Interface::Clear() {
    if (_has_bits_[0 / 32] & 15) {
        if (has_name()) {
            if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                name_->clear();
            }
        }
        if (has_mac()) {
            if (mac_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                mac_->clear();
            }
        }
        if (has_ipv4address()) {
            if (ipv4address_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                ipv4address_->clear();
            }
        }
        if (has_ipv6address()) {
            if (ipv6address_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                ipv6address_->clear();
            }
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Configuration_Interface::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string name = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_name()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->name().data(), this->name().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "name");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_MAC;
                break;
            }

            // optional bytes MAC = 2;
            case 2: {
                if (tag == 18) {
parse_MAC:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_mac()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_ipv4Address;
                break;
            }

            // optional bytes ipv4Address = 3;
            case 3: {
                if (tag == 26) {
parse_ipv4Address:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_ipv4address()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_ipv6Address;
                break;
            }

            // optional bytes ipv6Address = 4;
            case 4: {
                if (tag == 34) {
parse_ipv6Address:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_ipv6address()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    return false;
#undef DO_
}

void Command_GetLog_Configuration_Interface::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->name(), output);
    }

    // optional bytes MAC = 2;
    if (has_mac()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->mac(), output);
    }

    // optional bytes ipv4Address = 3;
    if (has_ipv4address()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->ipv4address(), output);
    }

    // optional bytes ipv6Address = 4;
    if (has_ipv6address()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            4, this->ipv6address(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
}

::google::protobuf::uint8* Command_GetLog_Configuration_Interface::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    // optional string name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "name");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                1, this->name(), target);
    }

    // optional bytes MAC = 2;
    if (has_mac()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->mac(), target);
    }

    // optional bytes ipv4Address = 3;
    if (has_ipv4address()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->ipv4address(), target);
    }

    // optional bytes ipv6Address = 4;
    if (has_ipv6address()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                4, this->ipv6address(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface)
    return target;
}

int Command_GetLog_Configuration_Interface::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string name = 1;
        if (has_name()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->name());
        }

        // optional bytes MAC = 2;
        if (has_mac()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->mac());
        }

        // optional bytes ipv4Address = 3;
        if (has_ipv4address()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->ipv4address());
        }

        // optional bytes ipv6Address = 4;
        if (has_ipv6address()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->ipv6address());
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

void Command_GetLog_Configuration_Interface::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Configuration_Interface* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Configuration_Interface*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Configuration_Interface::MergeFrom(const Command_GetLog_Configuration_Interface& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_name()) {
            set_name(from.name());
        }
        if (from.has_mac()) {
            set_mac(from.mac());
        }
        if (from.has_ipv4address()) {
            set_ipv4address(from.ipv4address());
        }
        if (from.has_ipv6address()) {
            set_ipv6address(from.ipv6address());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Configuration_Interface::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Configuration_Interface::CopyFrom(const Command_GetLog_Configuration_Interface& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Configuration_Interface::IsInitialized() const {

    return true;
}

void Command_GetLog_Configuration_Interface::Swap(Command_GetLog_Configuration_Interface* other) {
    if (other != this) {
        std::swap(name_, other->name_);
        std::swap(mac_, other->mac_);
        std::swap(ipv4address_, other->ipv4address_);
        std::swap(ipv6address_, other->ipv6address_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Configuration_Interface::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Configuration_Interface_descriptor_;
    metadata.reflection = Command_GetLog_Configuration_Interface_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Configuration::kVendorFieldNumber;
const int Command_GetLog_Configuration::kModelFieldNumber;
const int Command_GetLog_Configuration::kSerialNumberFieldNumber;
const int Command_GetLog_Configuration::kWorldWideNameFieldNumber;
const int Command_GetLog_Configuration::kVersionFieldNumber;
const int Command_GetLog_Configuration::kCompilationDateFieldNumber;
const int Command_GetLog_Configuration::kSourceHashFieldNumber;
const int Command_GetLog_Configuration::kProtocolVersionFieldNumber;
const int Command_GetLog_Configuration::kProtocolCompilationDateFieldNumber;
const int Command_GetLog_Configuration::kProtocolSourceHashFieldNumber;
const int Command_GetLog_Configuration::kInterfaceFieldNumber;
const int Command_GetLog_Configuration::kPortFieldNumber;
const int Command_GetLog_Configuration::kTlsPortFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Configuration::Command_GetLog_Configuration()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Configuration)
}

void Command_GetLog_Configuration::InitAsDefaultInstance() {
}

Command_GetLog_Configuration::Command_GetLog_Configuration(const Command_GetLog_Configuration& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Configuration)
}

void Command_GetLog_Configuration::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    vendor_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    model_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    serialnumber_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    worldwidename_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    version_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    compilationdate_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    sourcehash_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    protocolversion_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    protocolcompilationdate_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    protocolsourcehash_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    port_ = 0;
    tlsport_ = 0;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Configuration::~Command_GetLog_Configuration() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    SharedDtor();
}

void Command_GetLog_Configuration::SharedDtor() {
    if (vendor_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete vendor_;
    }
    if (model_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete model_;
    }
    if (serialnumber_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete serialnumber_;
    }
    if (worldwidename_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete worldwidename_;
    }
    if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete version_;
    }
    if (compilationdate_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete compilationdate_;
    }
    if (sourcehash_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete sourcehash_;
    }
    if (protocolversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete protocolversion_;
    }
    if (protocolcompilationdate_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete protocolcompilationdate_;
    }
    if (protocolsourcehash_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete protocolsourcehash_;
    }
    if (this != default_instance_) {
    }
}

void Command_GetLog_Configuration::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Configuration::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Configuration_descriptor_;
}

const Command_GetLog_Configuration& Command_GetLog_Configuration::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Configuration* Command_GetLog_Configuration::default_instance_ = NULL;

Command_GetLog_Configuration* Command_GetLog_Configuration::New() const {
    return new Command_GetLog_Configuration;
}

void Command_GetLog_Configuration::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_GetLog_Configuration*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 255) {
        if (has_vendor()) {
            if (vendor_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                vendor_->clear();
            }
        }
        if (has_model()) {
            if (model_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                model_->clear();
            }
        }
        if (has_serialnumber()) {
            if (serialnumber_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                serialnumber_->clear();
            }
        }
        if (has_worldwidename()) {
            if (worldwidename_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                worldwidename_->clear();
            }
        }
        if (has_version()) {
            if (version_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                version_->clear();
            }
        }
        if (has_compilationdate()) {
            if (compilationdate_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                compilationdate_->clear();
            }
        }
        if (has_sourcehash()) {
            if (sourcehash_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                sourcehash_->clear();
            }
        }
        if (has_protocolversion()) {
            if (protocolversion_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                protocolversion_->clear();
            }
        }
    }
    if (_has_bits_[8 / 32] & 6912) {
        ZR_(port_, tlsport_);
        if (has_protocolcompilationdate()) {
            if (protocolcompilationdate_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                protocolcompilationdate_->clear();
            }
        }
        if (has_protocolsourcehash()) {
            if (protocolsourcehash_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                protocolsourcehash_->clear();
            }
        }
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    interface_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Configuration::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(16383);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional string vendor = 5;
            case 5: {
                if (tag == 42) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_vendor()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->vendor().data(), this->vendor().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "vendor");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_model;
                break;
            }

            // optional string model = 6;
            case 6: {
                if (tag == 50) {
parse_model:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_model()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->model().data(), this->model().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "model");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(58)) goto parse_serialNumber;
                break;
            }

            // optional bytes serialNumber = 7;
            case 7: {
                if (tag == 58) {
parse_serialNumber:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_serialnumber()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_version;
                break;
            }

            // optional string version = 8;
            case 8: {
                if (tag == 66) {
parse_version:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_version()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->version().data(), this->version().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "version");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(74)) goto parse_interface;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface interface = 9;
            case 9: {
                if (tag == 74) {
parse_interface:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_interface()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(74)) goto parse_interface;
                if (input->ExpectTag(80)) goto parse_port;
                break;
            }

            // optional int32 port = 10;
            case 10: {
                if (tag == 80) {
parse_port:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32 > (
                             input, &port_)));
                    set_has_port();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(88)) goto parse_tlsPort;
                break;
            }

            // optional int32 tlsPort = 11;
            case 11: {
                if (tag == 88) {
parse_tlsPort:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32 > (
                             input, &tlsport_)));
                    set_has_tlsport();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(98)) goto parse_compilationDate;
                break;
            }

            // optional string compilationDate = 12;
            case 12: {
                if (tag == 98) {
parse_compilationDate:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_compilationdate()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->compilationdate().data(), this->compilationdate().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "compilationdate");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(106)) goto parse_sourceHash;
                break;
            }

            // optional string sourceHash = 13;
            case 13: {
                if (tag == 106) {
parse_sourceHash:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_sourcehash()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->sourcehash().data(), this->sourcehash().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "sourcehash");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(114)) goto parse_worldWideName;
                break;
            }

            // optional bytes worldWideName = 14;
            case 14: {
                if (tag == 114) {
parse_worldWideName:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_worldwidename()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(122)) goto parse_protocolVersion;
                break;
            }

            // optional string protocolVersion = 15;
            case 15: {
                if (tag == 122) {
parse_protocolVersion:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_protocolversion()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->protocolversion().data(), this->protocolversion().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "protocolversion");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(130)) goto parse_protocolCompilationDate;
                break;
            }

            // optional string protocolCompilationDate = 16;
            case 16: {
                if (tag == 130) {
parse_protocolCompilationDate:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_protocolcompilationdate()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->protocolcompilationdate().data(), this->protocolcompilationdate().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "protocolcompilationdate");
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(138)) goto parse_protocolSourceHash;
                break;
            }

            // optional string protocolSourceHash = 17;
            case 17: {
                if (tag == 138) {
parse_protocolSourceHash:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                            input, this->mutable_protocolsourcehash()));
                    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
                        this->protocolsourcehash().data(), this->protocolsourcehash().length(),
                        ::google::protobuf::internal::WireFormat::PARSE,
                        "protocolsourcehash");
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    return false;
#undef DO_
}

void Command_GetLog_Configuration::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    // optional string vendor = 5;
    if (has_vendor()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->vendor().data(), this->vendor().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "vendor");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            5, this->vendor(), output);
    }

    // optional string model = 6;
    if (has_model()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->model().data(), this->model().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "model");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            6, this->model(), output);
    }

    // optional bytes serialNumber = 7;
    if (has_serialnumber()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            7, this->serialnumber(), output);
    }

    // optional string version = 8;
    if (has_version()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->version().data(), this->version().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "version");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            8, this->version(), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface interface = 9;
    for (int i = 0; i < this->interface_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            9, this->interface(i), output);
    }

    // optional int32 port = 10;
    if (has_port()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(10, this->port(), output);
    }

    // optional int32 tlsPort = 11;
    if (has_tlsport()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(11, this->tlsport(), output);
    }

    // optional string compilationDate = 12;
    if (has_compilationdate()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->compilationdate().data(), this->compilationdate().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "compilationdate");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            12, this->compilationdate(), output);
    }

    // optional string sourceHash = 13;
    if (has_sourcehash()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sourcehash().data(), this->sourcehash().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "sourcehash");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            13, this->sourcehash(), output);
    }

    // optional bytes worldWideName = 14;
    if (has_worldwidename()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            14, this->worldwidename(), output);
    }

    // optional string protocolVersion = 15;
    if (has_protocolversion()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolversion().data(), this->protocolversion().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolversion");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            15, this->protocolversion(), output);
    }

    // optional string protocolCompilationDate = 16;
    if (has_protocolcompilationdate()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolcompilationdate().data(), this->protocolcompilationdate().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolcompilationdate");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            16, this->protocolcompilationdate(), output);
    }

    // optional string protocolSourceHash = 17;
    if (has_protocolsourcehash()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolsourcehash().data(), this->protocolsourcehash().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolsourcehash");
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            17, this->protocolsourcehash(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Configuration)
}

::google::protobuf::uint8* Command_GetLog_Configuration::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    // optional string vendor = 5;
    if (has_vendor()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->vendor().data(), this->vendor().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "vendor");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                5, this->vendor(), target);
    }

    // optional string model = 6;
    if (has_model()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->model().data(), this->model().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "model");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                6, this->model(), target);
    }

    // optional bytes serialNumber = 7;
    if (has_serialnumber()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                7, this->serialnumber(), target);
    }

    // optional string version = 8;
    if (has_version()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->version().data(), this->version().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "version");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                8, this->version(), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface interface = 9;
    for (int i = 0; i < this->interface_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     9, this->interface(i), target);
    }

    // optional int32 port = 10;
    if (has_port()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(10, this->port(), target);
    }

    // optional int32 tlsPort = 11;
    if (has_tlsport()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(11, this->tlsport(), target);
    }

    // optional string compilationDate = 12;
    if (has_compilationdate()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->compilationdate().data(), this->compilationdate().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "compilationdate");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                12, this->compilationdate(), target);
    }

    // optional string sourceHash = 13;
    if (has_sourcehash()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sourcehash().data(), this->sourcehash().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "sourcehash");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                13, this->sourcehash(), target);
    }

    // optional bytes worldWideName = 14;
    if (has_worldwidename()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                14, this->worldwidename(), target);
    }

    // optional string protocolVersion = 15;
    if (has_protocolversion()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolversion().data(), this->protocolversion().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolversion");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                15, this->protocolversion(), target);
    }

    // optional string protocolCompilationDate = 16;
    if (has_protocolcompilationdate()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolcompilationdate().data(), this->protocolcompilationdate().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolcompilationdate");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                16, this->protocolcompilationdate(), target);
    }

    // optional string protocolSourceHash = 17;
    if (has_protocolsourcehash()) {
        ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->protocolsourcehash().data(), this->protocolsourcehash().length(),
            ::google::protobuf::internal::WireFormat::SERIALIZE,
            "protocolsourcehash");
        target =
            ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
                17, this->protocolsourcehash(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Configuration)
    return target;
}

int Command_GetLog_Configuration::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional string vendor = 5;
        if (has_vendor()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->vendor());
        }

        // optional string model = 6;
        if (has_model()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->model());
        }

        // optional bytes serialNumber = 7;
        if (has_serialnumber()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->serialnumber());
        }

        // optional bytes worldWideName = 14;
        if (has_worldwidename()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->worldwidename());
        }

        // optional string version = 8;
        if (has_version()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->version());
        }

        // optional string compilationDate = 12;
        if (has_compilationdate()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->compilationdate());
        }

        // optional string sourceHash = 13;
        if (has_sourcehash()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->sourcehash());
        }

        // optional string protocolVersion = 15;
        if (has_protocolversion()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->protocolversion());
        }

    }
    if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        // optional string protocolCompilationDate = 16;
        if (has_protocolcompilationdate()) {
            total_size += 2 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->protocolcompilationdate());
        }

        // optional string protocolSourceHash = 17;
        if (has_protocolsourcehash()) {
            total_size += 2 +
                          ::google::protobuf::internal::WireFormatLite::StringSize(
                              this->protocolsourcehash());
        }

        // optional int32 port = 10;
        if (has_port()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(
                              this->port());
        }

        // optional int32 tlsPort = 11;
        if (has_tlsport()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int32Size(
                              this->tlsport());
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.GetLog.Configuration.Interface interface = 9;
    total_size += 1 * this->interface_size();
    for (int i = 0; i < this->interface_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->interface(i));
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

void Command_GetLog_Configuration::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Configuration* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Configuration*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Configuration::MergeFrom(const Command_GetLog_Configuration& from) {
    GOOGLE_CHECK_NE(&from, this);
    interface_.MergeFrom(from.interface_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_vendor()) {
            set_vendor(from.vendor());
        }
        if (from.has_model()) {
            set_model(from.model());
        }
        if (from.has_serialnumber()) {
            set_serialnumber(from.serialnumber());
        }
        if (from.has_worldwidename()) {
            set_worldwidename(from.worldwidename());
        }
        if (from.has_version()) {
            set_version(from.version());
        }
        if (from.has_compilationdate()) {
            set_compilationdate(from.compilationdate());
        }
        if (from.has_sourcehash()) {
            set_sourcehash(from.sourcehash());
        }
        if (from.has_protocolversion()) {
            set_protocolversion(from.protocolversion());
        }
    }
    if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        if (from.has_protocolcompilationdate()) {
            set_protocolcompilationdate(from.protocolcompilationdate());
        }
        if (from.has_protocolsourcehash()) {
            set_protocolsourcehash(from.protocolsourcehash());
        }
        if (from.has_port()) {
            set_port(from.port());
        }
        if (from.has_tlsport()) {
            set_tlsport(from.tlsport());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Configuration::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Configuration::CopyFrom(const Command_GetLog_Configuration& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Configuration::IsInitialized() const {

    return true;
}

void Command_GetLog_Configuration::Swap(Command_GetLog_Configuration* other) {
    if (other != this) {
        std::swap(vendor_, other->vendor_);
        std::swap(model_, other->model_);
        std::swap(serialnumber_, other->serialnumber_);
        std::swap(worldwidename_, other->worldwidename_);
        std::swap(version_, other->version_);
        std::swap(compilationdate_, other->compilationdate_);
        std::swap(sourcehash_, other->sourcehash_);
        std::swap(protocolversion_, other->protocolversion_);
        std::swap(protocolcompilationdate_, other->protocolcompilationdate_);
        std::swap(protocolsourcehash_, other->protocolsourcehash_);
        interface_.Swap(&other->interface_);
        std::swap(port_, other->port_);
        std::swap(tlsport_, other->tlsport_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Configuration::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Configuration_descriptor_;
    metadata.reflection = Command_GetLog_Configuration_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Statistics::kMessageTypeFieldNumber;
const int Command_GetLog_Statistics::kCountFieldNumber;
const int Command_GetLog_Statistics::kBytesFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Statistics::Command_GetLog_Statistics()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Statistics)
}

void Command_GetLog_Statistics::InitAsDefaultInstance() {
}

Command_GetLog_Statistics::Command_GetLog_Statistics(const Command_GetLog_Statistics& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Statistics)
}

void Command_GetLog_Statistics::SharedCtor() {
    _cached_size_ = 0;
    messagetype_ = -1;
    count_ = GOOGLE_ULONGLONG(0);
    bytes_ = GOOGLE_ULONGLONG(0);
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Statistics::~Command_GetLog_Statistics() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    SharedDtor();
}

void Command_GetLog_Statistics::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_GetLog_Statistics::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Statistics::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Statistics_descriptor_;
}

const Command_GetLog_Statistics& Command_GetLog_Statistics::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Statistics* Command_GetLog_Statistics::default_instance_ = NULL;

Command_GetLog_Statistics* Command_GetLog_Statistics::New() const {
    return new Command_GetLog_Statistics;
}

void Command_GetLog_Statistics::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_GetLog_Statistics*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 7) {
        ZR_(count_, bytes_);
        messagetype_ = -1;
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Statistics::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 1;
            case 1: {
                if (tag == 8) {
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_MessageType_IsValid(value)) {
                        set_messagetype(static_cast<::com::seagate::kinetic::proto::Command_MessageType>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(1, value);
                    }
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_count;
                break;
            }

            // optional uint64 count = 4;
            case 4: {
                if (tag == 32) {
parse_count:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64 > (
                             input, &count_)));
                    set_has_count();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(40)) goto parse_bytes;
                break;
            }

            // optional uint64 bytes = 5;
            case 5: {
                if (tag == 40) {
parse_bytes:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64 > (
                             input, &bytes_)));
                    set_has_bytes();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    return false;
#undef DO_
}

void Command_GetLog_Statistics::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 1;
    if (has_messagetype()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            1, this->messagetype(), output);
    }

    // optional uint64 count = 4;
    if (has_count()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->count(), output);
    }

    // optional uint64 bytes = 5;
    if (has_bytes()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt64(5, this->bytes(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Statistics)
}

::google::protobuf::uint8* Command_GetLog_Statistics::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 1;
    if (has_messagetype()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     1, this->messagetype(), target);
    }

    // optional uint64 count = 4;
    if (has_count()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->count(), target);
    }

    // optional uint64 bytes = 5;
    if (has_bytes()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(5, this->bytes(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Statistics)
    return target;
}

int Command_GetLog_Statistics::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.MessageType messageType = 1;
        if (has_messagetype()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->messagetype());
        }

        // optional uint64 count = 4;
        if (has_count()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt64Size(
                              this->count());
        }

        // optional uint64 bytes = 5;
        if (has_bytes()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt64Size(
                              this->bytes());
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

void Command_GetLog_Statistics::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Statistics* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Statistics*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Statistics::MergeFrom(const Command_GetLog_Statistics& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_messagetype()) {
            set_messagetype(from.messagetype());
        }
        if (from.has_count()) {
            set_count(from.count());
        }
        if (from.has_bytes()) {
            set_bytes(from.bytes());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Statistics::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Statistics::CopyFrom(const Command_GetLog_Statistics& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Statistics::IsInitialized() const {

    return true;
}

void Command_GetLog_Statistics::Swap(Command_GetLog_Statistics* other) {
    if (other != this) {
        std::swap(messagetype_, other->messagetype_);
        std::swap(count_, other->count_);
        std::swap(bytes_, other->bytes_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Statistics::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Statistics_descriptor_;
    metadata.reflection = Command_GetLog_Statistics_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Limits::kMaxKeySizeFieldNumber;
const int Command_GetLog_Limits::kMaxValueSizeFieldNumber;
const int Command_GetLog_Limits::kMaxVersionSizeFieldNumber;
const int Command_GetLog_Limits::kMaxTagSizeFieldNumber;
const int Command_GetLog_Limits::kMaxConnectionsFieldNumber;
const int Command_GetLog_Limits::kMaxOutstandingReadRequestsFieldNumber;
const int Command_GetLog_Limits::kMaxOutstandingWriteRequestsFieldNumber;
const int Command_GetLog_Limits::kMaxMessageSizeFieldNumber;
const int Command_GetLog_Limits::kMaxKeyRangeCountFieldNumber;
const int Command_GetLog_Limits::kMaxIdentityCountFieldNumber;
const int Command_GetLog_Limits::kMaxPinSizeFieldNumber;
const int Command_GetLog_Limits::kMaxOperationCountPerBatchFieldNumber;
const int Command_GetLog_Limits::kMaxBatchCountPerDeviceFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Limits::Command_GetLog_Limits()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Limits)
}

void Command_GetLog_Limits::InitAsDefaultInstance() {
}

Command_GetLog_Limits::Command_GetLog_Limits(const Command_GetLog_Limits& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Limits)
}

void Command_GetLog_Limits::SharedCtor() {
    _cached_size_ = 0;
    maxkeysize_ = 0u;
    maxvaluesize_ = 0u;
    maxversionsize_ = 0u;
    maxtagsize_ = 0u;
    maxconnections_ = 0u;
    maxoutstandingreadrequests_ = 0u;
    maxoutstandingwriterequests_ = 0u;
    maxmessagesize_ = 0u;
    maxkeyrangecount_ = 0u;
    maxidentitycount_ = 0u;
    maxpinsize_ = 0u;
    maxoperationcountperbatch_ = 0u;
    maxbatchcountperdevice_ = 0u;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Limits::~Command_GetLog_Limits() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Limits)
    SharedDtor();
}

void Command_GetLog_Limits::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_GetLog_Limits::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Limits::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Limits_descriptor_;
}

const Command_GetLog_Limits& Command_GetLog_Limits::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Limits* Command_GetLog_Limits::default_instance_ = NULL;

Command_GetLog_Limits* Command_GetLog_Limits::New() const {
    return new Command_GetLog_Limits;
}

void Command_GetLog_Limits::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Command_GetLog_Limits*>(16)->f) - \
  reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

    if (_has_bits_[0 / 32] & 255) {
        ZR_(maxkeysize_, maxmessagesize_);
    }
    if (_has_bits_[8 / 32] & 7936) {
        ZR_(maxkeyrangecount_, maxbatchcountperdevice_);
    }

#undef OFFSET_OF_FIELD_
#undef ZR_

    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Limits::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Limits)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional uint32 maxKeySize = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxkeysize_)));
                    set_has_maxkeysize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(16)) goto parse_maxValueSize;
                break;
            }

            // optional uint32 maxValueSize = 2;
            case 2: {
                if (tag == 16) {
parse_maxValueSize:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxvaluesize_)));
                    set_has_maxvaluesize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_maxVersionSize;
                break;
            }

            // optional uint32 maxVersionSize = 3;
            case 3: {
                if (tag == 24) {
parse_maxVersionSize:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxversionsize_)));
                    set_has_maxversionsize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(32)) goto parse_maxTagSize;
                break;
            }

            // optional uint32 maxTagSize = 4;
            case 4: {
                if (tag == 32) {
parse_maxTagSize:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxtagsize_)));
                    set_has_maxtagsize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(40)) goto parse_maxConnections;
                break;
            }

            // optional uint32 maxConnections = 5;
            case 5: {
                if (tag == 40) {
parse_maxConnections:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxconnections_)));
                    set_has_maxconnections();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(48)) goto parse_maxOutstandingReadRequests;
                break;
            }

            // optional uint32 maxOutstandingReadRequests = 6;
            case 6: {
                if (tag == 48) {
parse_maxOutstandingReadRequests:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxoutstandingreadrequests_)));
                    set_has_maxoutstandingreadrequests();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(56)) goto parse_maxOutstandingWriteRequests;
                break;
            }

            // optional uint32 maxOutstandingWriteRequests = 7;
            case 7: {
                if (tag == 56) {
parse_maxOutstandingWriteRequests:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxoutstandingwriterequests_)));
                    set_has_maxoutstandingwriterequests();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(64)) goto parse_maxMessageSize;
                break;
            }

            // optional uint32 maxMessageSize = 8;
            case 8: {
                if (tag == 64) {
parse_maxMessageSize:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxmessagesize_)));
                    set_has_maxmessagesize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(72)) goto parse_maxKeyRangeCount;
                break;
            }

            // optional uint32 maxKeyRangeCount = 9;
            case 9: {
                if (tag == 72) {
parse_maxKeyRangeCount:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxkeyrangecount_)));
                    set_has_maxkeyrangecount();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(80)) goto parse_maxIdentityCount;
                break;
            }

            // optional uint32 maxIdentityCount = 10;
            case 10: {
                if (tag == 80) {
parse_maxIdentityCount:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxidentitycount_)));
                    set_has_maxidentitycount();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(88)) goto parse_maxPinSize;
                break;
            }

            // optional uint32 maxPinSize = 11;
            case 11: {
                if (tag == 88) {
parse_maxPinSize:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxpinsize_)));
                    set_has_maxpinsize();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(96)) goto parse_maxOperationCountPerBatch;
                break;
            }

            // optional uint32 maxOperationCountPerBatch = 12;
            case 12: {
                if (tag == 96) {
parse_maxOperationCountPerBatch:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxoperationcountperbatch_)));
                    set_has_maxoperationcountperbatch();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(104)) goto parse_maxBatchCountPerDevice;
                break;
            }

            // optional uint32 maxBatchCountPerDevice = 13;
            case 13: {
                if (tag == 104) {
parse_maxBatchCountPerDevice:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32 > (
                             input, &maxbatchcountperdevice_)));
                    set_has_maxbatchcountperdevice();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Limits)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Limits)
    return false;
#undef DO_
}

void Command_GetLog_Limits::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Limits)
    // optional uint32 maxKeySize = 1;
    if (has_maxkeysize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->maxkeysize(), output);
    }

    // optional uint32 maxValueSize = 2;
    if (has_maxvaluesize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->maxvaluesize(), output);
    }

    // optional uint32 maxVersionSize = 3;
    if (has_maxversionsize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->maxversionsize(), output);
    }

    // optional uint32 maxTagSize = 4;
    if (has_maxtagsize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->maxtagsize(), output);
    }

    // optional uint32 maxConnections = 5;
    if (has_maxconnections()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->maxconnections(), output);
    }

    // optional uint32 maxOutstandingReadRequests = 6;
    if (has_maxoutstandingreadrequests()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->maxoutstandingreadrequests(), output);
    }

    // optional uint32 maxOutstandingWriteRequests = 7;
    if (has_maxoutstandingwriterequests()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->maxoutstandingwriterequests(), output);
    }

    // optional uint32 maxMessageSize = 8;
    if (has_maxmessagesize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->maxmessagesize(), output);
    }

    // optional uint32 maxKeyRangeCount = 9;
    if (has_maxkeyrangecount()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->maxkeyrangecount(), output);
    }

    // optional uint32 maxIdentityCount = 10;
    if (has_maxidentitycount()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(10, this->maxidentitycount(), output);
    }

    // optional uint32 maxPinSize = 11;
    if (has_maxpinsize()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(11, this->maxpinsize(), output);
    }

    // optional uint32 maxOperationCountPerBatch = 12;
    if (has_maxoperationcountperbatch()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(12, this->maxoperationcountperbatch(), output);
    }

    // optional uint32 maxBatchCountPerDevice = 13;
    if (has_maxbatchcountperdevice()) {
        ::google::protobuf::internal::WireFormatLite::WriteUInt32(13, this->maxbatchcountperdevice(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Limits)
}

::google::protobuf::uint8* Command_GetLog_Limits::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Limits)
    // optional uint32 maxKeySize = 1;
    if (has_maxkeysize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->maxkeysize(), target);
    }

    // optional uint32 maxValueSize = 2;
    if (has_maxvaluesize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->maxvaluesize(), target);
    }

    // optional uint32 maxVersionSize = 3;
    if (has_maxversionsize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->maxversionsize(), target);
    }

    // optional uint32 maxTagSize = 4;
    if (has_maxtagsize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->maxtagsize(), target);
    }

    // optional uint32 maxConnections = 5;
    if (has_maxconnections()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(5, this->maxconnections(), target);
    }

    // optional uint32 maxOutstandingReadRequests = 6;
    if (has_maxoutstandingreadrequests()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->maxoutstandingreadrequests(), target);
    }

    // optional uint32 maxOutstandingWriteRequests = 7;
    if (has_maxoutstandingwriterequests()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->maxoutstandingwriterequests(), target);
    }

    // optional uint32 maxMessageSize = 8;
    if (has_maxmessagesize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->maxmessagesize(), target);
    }

    // optional uint32 maxKeyRangeCount = 9;
    if (has_maxkeyrangecount()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->maxkeyrangecount(), target);
    }

    // optional uint32 maxIdentityCount = 10;
    if (has_maxidentitycount()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(10, this->maxidentitycount(), target);
    }

    // optional uint32 maxPinSize = 11;
    if (has_maxpinsize()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(11, this->maxpinsize(), target);
    }

    // optional uint32 maxOperationCountPerBatch = 12;
    if (has_maxoperationcountperbatch()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(12, this->maxoperationcountperbatch(), target);
    }

    // optional uint32 maxBatchCountPerDevice = 13;
    if (has_maxbatchcountperdevice()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(13, this->maxbatchcountperdevice(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Limits)
    return target;
}

int Command_GetLog_Limits::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional uint32 maxKeySize = 1;
        if (has_maxkeysize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxkeysize());
        }

        // optional uint32 maxValueSize = 2;
        if (has_maxvaluesize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxvaluesize());
        }

        // optional uint32 maxVersionSize = 3;
        if (has_maxversionsize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxversionsize());
        }

        // optional uint32 maxTagSize = 4;
        if (has_maxtagsize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxtagsize());
        }

        // optional uint32 maxConnections = 5;
        if (has_maxconnections()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxconnections());
        }

        // optional uint32 maxOutstandingReadRequests = 6;
        if (has_maxoutstandingreadrequests()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxoutstandingreadrequests());
        }

        // optional uint32 maxOutstandingWriteRequests = 7;
        if (has_maxoutstandingwriterequests()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxoutstandingwriterequests());
        }

        // optional uint32 maxMessageSize = 8;
        if (has_maxmessagesize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxmessagesize());
        }

    }
    if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        // optional uint32 maxKeyRangeCount = 9;
        if (has_maxkeyrangecount()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxkeyrangecount());
        }

        // optional uint32 maxIdentityCount = 10;
        if (has_maxidentitycount()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxidentitycount());
        }

        // optional uint32 maxPinSize = 11;
        if (has_maxpinsize()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxpinsize());
        }

        // optional uint32 maxOperationCountPerBatch = 12;
        if (has_maxoperationcountperbatch()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxoperationcountperbatch());
        }

        // optional uint32 maxBatchCountPerDevice = 13;
        if (has_maxbatchcountperdevice()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::UInt32Size(
                              this->maxbatchcountperdevice());
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

void Command_GetLog_Limits::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Limits* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Limits*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Limits::MergeFrom(const Command_GetLog_Limits& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_maxkeysize()) {
            set_maxkeysize(from.maxkeysize());
        }
        if (from.has_maxvaluesize()) {
            set_maxvaluesize(from.maxvaluesize());
        }
        if (from.has_maxversionsize()) {
            set_maxversionsize(from.maxversionsize());
        }
        if (from.has_maxtagsize()) {
            set_maxtagsize(from.maxtagsize());
        }
        if (from.has_maxconnections()) {
            set_maxconnections(from.maxconnections());
        }
        if (from.has_maxoutstandingreadrequests()) {
            set_maxoutstandingreadrequests(from.maxoutstandingreadrequests());
        }
        if (from.has_maxoutstandingwriterequests()) {
            set_maxoutstandingwriterequests(from.maxoutstandingwriterequests());
        }
        if (from.has_maxmessagesize()) {
            set_maxmessagesize(from.maxmessagesize());
        }
    }
    if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        if (from.has_maxkeyrangecount()) {
            set_maxkeyrangecount(from.maxkeyrangecount());
        }
        if (from.has_maxidentitycount()) {
            set_maxidentitycount(from.maxidentitycount());
        }
        if (from.has_maxpinsize()) {
            set_maxpinsize(from.maxpinsize());
        }
        if (from.has_maxoperationcountperbatch()) {
            set_maxoperationcountperbatch(from.maxoperationcountperbatch());
        }
        if (from.has_maxbatchcountperdevice()) {
            set_maxbatchcountperdevice(from.maxbatchcountperdevice());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Limits::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Limits::CopyFrom(const Command_GetLog_Limits& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Limits::IsInitialized() const {

    return true;
}

void Command_GetLog_Limits::Swap(Command_GetLog_Limits* other) {
    if (other != this) {
        std::swap(maxkeysize_, other->maxkeysize_);
        std::swap(maxvaluesize_, other->maxvaluesize_);
        std::swap(maxversionsize_, other->maxversionsize_);
        std::swap(maxtagsize_, other->maxtagsize_);
        std::swap(maxconnections_, other->maxconnections_);
        std::swap(maxoutstandingreadrequests_, other->maxoutstandingreadrequests_);
        std::swap(maxoutstandingwriterequests_, other->maxoutstandingwriterequests_);
        std::swap(maxmessagesize_, other->maxmessagesize_);
        std::swap(maxkeyrangecount_, other->maxkeyrangecount_);
        std::swap(maxidentitycount_, other->maxidentitycount_);
        std::swap(maxpinsize_, other->maxpinsize_);
        std::swap(maxoperationcountperbatch_, other->maxoperationcountperbatch_);
        std::swap(maxbatchcountperdevice_, other->maxbatchcountperdevice_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Limits::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Limits_descriptor_;
    metadata.reflection = Command_GetLog_Limits_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog_Device::kNameFieldNumber;
#endif  // !_MSC_VER

Command_GetLog_Device::Command_GetLog_Device()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog.Device)
}

void Command_GetLog_Device::InitAsDefaultInstance() {
}

Command_GetLog_Device::Command_GetLog_Device(const Command_GetLog_Device& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog.Device)
}

void Command_GetLog_Device::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    name_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog_Device::~Command_GetLog_Device() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog.Device)
    SharedDtor();
}

void Command_GetLog_Device::SharedDtor() {
    if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete name_;
    }
    if (this != default_instance_) {
    }
}

void Command_GetLog_Device::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog_Device::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_Device_descriptor_;
}

const Command_GetLog_Device& Command_GetLog_Device::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog_Device* Command_GetLog_Device::default_instance_ = NULL;

Command_GetLog_Device* Command_GetLog_Device::New() const {
    return new Command_GetLog_Device;
}

void Command_GetLog_Device::Clear() {
    if (has_name()) {
        if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
            name_->clear();
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog_Device::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog.Device)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional bytes name = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_name()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog.Device)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog.Device)
    return false;
#undef DO_
}

void Command_GetLog_Device::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog.Device)
    // optional bytes name = 1;
    if (has_name()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            1, this->name(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog.Device)
}

::google::protobuf::uint8* Command_GetLog_Device::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog.Device)
    // optional bytes name = 1;
    if (has_name()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                1, this->name(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog.Device)
    return target;
}

int Command_GetLog_Device::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional bytes name = 1;
        if (has_name()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->name());
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

void Command_GetLog_Device::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog_Device* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog_Device*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog_Device::MergeFrom(const Command_GetLog_Device& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_name()) {
            set_name(from.name());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog_Device::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog_Device::CopyFrom(const Command_GetLog_Device& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog_Device::IsInitialized() const {

    return true;
}

void Command_GetLog_Device::Swap(Command_GetLog_Device* other) {
    if (other != this) {
        std::swap(name_, other->name_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog_Device::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_Device_descriptor_;
    metadata.reflection = Command_GetLog_Device_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_GetLog::kTypesFieldNumber;
const int Command_GetLog::kUtilizationsFieldNumber;
const int Command_GetLog::kTemperaturesFieldNumber;
const int Command_GetLog::kCapacityFieldNumber;
const int Command_GetLog::kConfigurationFieldNumber;
const int Command_GetLog::kStatisticsFieldNumber;
const int Command_GetLog::kMessagesFieldNumber;
const int Command_GetLog::kLimitsFieldNumber;
const int Command_GetLog::kDeviceFieldNumber;
#endif  // !_MSC_VER

Command_GetLog::Command_GetLog()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.GetLog)
}

void Command_GetLog::InitAsDefaultInstance() {
    capacity_ = const_cast<::com::seagate::kinetic::proto::Command_GetLog_Capacity*>(&::com::seagate::kinetic::proto::Command_GetLog_Capacity::default_instance());
    configuration_ = const_cast<::com::seagate::kinetic::proto::Command_GetLog_Configuration*>(&::com::seagate::kinetic::proto::Command_GetLog_Configuration::default_instance());
    limits_ = const_cast<::com::seagate::kinetic::proto::Command_GetLog_Limits*>(&::com::seagate::kinetic::proto::Command_GetLog_Limits::default_instance());
    device_ = const_cast<::com::seagate::kinetic::proto::Command_GetLog_Device*>(&::com::seagate::kinetic::proto::Command_GetLog_Device::default_instance());
}

Command_GetLog::Command_GetLog(const Command_GetLog& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.GetLog)
}

void Command_GetLog::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    capacity_ = NULL;
    configuration_ = NULL;
    messages_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    limits_ = NULL;
    device_ = NULL;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_GetLog::~Command_GetLog() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.GetLog)
    SharedDtor();
}

void Command_GetLog::SharedDtor() {
    if (messages_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete messages_;
    }
    if (this != default_instance_) {
        delete capacity_;
        delete configuration_;
        delete limits_;
        delete device_;
    }
}

void Command_GetLog::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_GetLog::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_GetLog_descriptor_;
}

const Command_GetLog& Command_GetLog::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_GetLog* Command_GetLog::default_instance_ = NULL;

Command_GetLog* Command_GetLog::New() const {
    return new Command_GetLog;
}

void Command_GetLog::Clear() {
    if (_has_bits_[0 / 32] & 216) {
        if (has_capacity()) {
            if (capacity_ != NULL) capacity_->::com::seagate::kinetic::proto::Command_GetLog_Capacity::Clear();
        }
        if (has_configuration()) {
            if (configuration_ != NULL) configuration_->::com::seagate::kinetic::proto::Command_GetLog_Configuration::Clear();
        }
        if (has_messages()) {
            if (messages_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                messages_->clear();
            }
        }
        if (has_limits()) {
            if (limits_ != NULL) limits_->::com::seagate::kinetic::proto::Command_GetLog_Limits::Clear();
        }
    }
    if (has_device()) {
        if (device_ != NULL) device_->::com::seagate::kinetic::proto::Command_GetLog_Device::Clear();
    }
    types_.Clear();
    utilizations_.Clear();
    temperatures_.Clear();
    statistics_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_GetLog::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.GetLog)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // repeated .com.seagate.kinetic.proto.Command.GetLog.Type types = 1;
            case 1: {
                if (tag == 8) {
parse_types:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_GetLog_Type_IsValid(value)) {
                        add_types(static_cast<::com::seagate::kinetic::proto::Command_GetLog_Type>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(1, value);
                    }
                }
                else if (tag == 10) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPackedEnumNoInline(
                             input,
                             &::com::seagate::kinetic::proto::Command_GetLog_Type_IsValid,
                             this->mutable_types())));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(8)) goto parse_types;
                if (input->ExpectTag(18)) goto parse_utilizations;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.GetLog.Utilization utilizations = 2;
            case 2: {
                if (tag == 18) {
parse_utilizations:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_utilizations()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_utilizations;
                if (input->ExpectTag(26)) goto parse_temperatures;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.GetLog.Temperature temperatures = 3;
            case 3: {
                if (tag == 26) {
parse_temperatures:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_temperatures()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_temperatures;
                if (input->ExpectTag(34)) goto parse_capacity;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.GetLog.Capacity capacity = 4;
            case 4: {
                if (tag == 34) {
parse_capacity:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_capacity()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(42)) goto parse_configuration;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.GetLog.Configuration configuration = 5;
            case 5: {
                if (tag == 42) {
parse_configuration:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_configuration()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_statistics;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.GetLog.Statistics statistics = 6;
            case 6: {
                if (tag == 50) {
parse_statistics:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_statistics()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_statistics;
                if (input->ExpectTag(58)) goto parse_messages;
                break;
            }

            // optional bytes messages = 7;
            case 7: {
                if (tag == 58) {
parse_messages:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_messages()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(66)) goto parse_limits;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.GetLog.Limits limits = 8;
            case 8: {
                if (tag == 66) {
parse_limits:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_limits()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(74)) goto parse_device;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.GetLog.Device device = 9;
            case 9: {
                if (tag == 74) {
parse_device:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_device()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.GetLog)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.GetLog)
    return false;
#undef DO_
}

void Command_GetLog::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.GetLog)
    // repeated .com.seagate.kinetic.proto.Command.GetLog.Type types = 1;
    for (int i = 0; i < this->types_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            1, this->types(i), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Utilization utilizations = 2;
    for (int i = 0; i < this->utilizations_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            2, this->utilizations(i), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Temperature temperatures = 3;
    for (int i = 0; i < this->temperatures_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            3, this->temperatures(i), output);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Capacity capacity = 4;
    if (has_capacity()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, this->capacity(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Configuration configuration = 5;
    if (has_configuration()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            5, this->configuration(), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Statistics statistics = 6;
    for (int i = 0; i < this->statistics_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            6, this->statistics(i), output);
    }

    // optional bytes messages = 7;
    if (has_messages()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            7, this->messages(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Limits limits = 8;
    if (has_limits()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            8, this->limits(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Device device = 9;
    if (has_device()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            9, this->device(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.GetLog)
}

::google::protobuf::uint8* Command_GetLog::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.GetLog)
    // repeated .com.seagate.kinetic.proto.Command.GetLog.Type types = 1;
    for (int i = 0; i < this->types_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     1, this->types(i), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Utilization utilizations = 2;
    for (int i = 0; i < this->utilizations_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     2, this->utilizations(i), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Temperature temperatures = 3;
    for (int i = 0; i < this->temperatures_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     3, this->temperatures(i), target);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Capacity capacity = 4;
    if (has_capacity()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     4, this->capacity(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Configuration configuration = 5;
    if (has_configuration()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     5, this->configuration(), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Statistics statistics = 6;
    for (int i = 0; i < this->statistics_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     6, this->statistics(i), target);
    }

    // optional bytes messages = 7;
    if (has_messages()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                7, this->messages(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Limits limits = 8;
    if (has_limits()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     8, this->limits(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.GetLog.Device device = 9;
    if (has_device()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     9, this->device(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.GetLog)
    return target;
}

int Command_GetLog::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[3 / 32] & (0xffu << (3 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.GetLog.Capacity capacity = 4;
        if (has_capacity()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->capacity());
        }

        // optional .com.seagate.kinetic.proto.Command.GetLog.Configuration configuration = 5;
        if (has_configuration()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->configuration());
        }

        // optional bytes messages = 7;
        if (has_messages()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->messages());
        }

        // optional .com.seagate.kinetic.proto.Command.GetLog.Limits limits = 8;
        if (has_limits()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->limits());
        }

    }
    if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.GetLog.Device device = 9;
        if (has_device()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->device());
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.GetLog.Type types = 1;
    {
        int data_size = 0;
        for (int i = 0; i < this->types_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
                             this->types(i));
        }
        total_size += 1 * this->types_size() + data_size;
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Utilization utilizations = 2;
    total_size += 1 * this->utilizations_size();
    for (int i = 0; i < this->utilizations_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->utilizations(i));
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Temperature temperatures = 3;
    total_size += 1 * this->temperatures_size();
    for (int i = 0; i < this->temperatures_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->temperatures(i));
    }

    // repeated .com.seagate.kinetic.proto.Command.GetLog.Statistics statistics = 6;
    total_size += 1 * this->statistics_size();
    for (int i = 0; i < this->statistics_size(); i++) {
        total_size +=
            ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->statistics(i));
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

void Command_GetLog::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_GetLog* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_GetLog*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_GetLog::MergeFrom(const Command_GetLog& from) {
    GOOGLE_CHECK_NE(&from, this);
    types_.MergeFrom(from.types_);
    utilizations_.MergeFrom(from.utilizations_);
    temperatures_.MergeFrom(from.temperatures_);
    statistics_.MergeFrom(from.statistics_);
    if (from._has_bits_[3 / 32] & (0xffu << (3 % 32))) {
        if (from.has_capacity()) {
            mutable_capacity()->::com::seagate::kinetic::proto::Command_GetLog_Capacity::MergeFrom(from.capacity());
        }
        if (from.has_configuration()) {
            mutable_configuration()->::com::seagate::kinetic::proto::Command_GetLog_Configuration::MergeFrom(from.configuration());
        }
        if (from.has_messages()) {
            set_messages(from.messages());
        }
        if (from.has_limits()) {
            mutable_limits()->::com::seagate::kinetic::proto::Command_GetLog_Limits::MergeFrom(from.limits());
        }
    }
    if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
        if (from.has_device()) {
            mutable_device()->::com::seagate::kinetic::proto::Command_GetLog_Device::MergeFrom(from.device());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_GetLog::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_GetLog::CopyFrom(const Command_GetLog& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_GetLog::IsInitialized() const {

    return true;
}

void Command_GetLog::Swap(Command_GetLog* other) {
    if (other != this) {
        types_.Swap(&other->types_);
        utilizations_.Swap(&other->utilizations_);
        temperatures_.Swap(&other->temperatures_);
        std::swap(capacity_, other->capacity_);
        std::swap(configuration_, other->configuration_);
        statistics_.Swap(&other->statistics_);
        std::swap(messages_, other->messages_);
        std::swap(limits_, other->limits_);
        std::swap(device_, other->device_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_GetLog::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_GetLog_descriptor_;
    metadata.reflection = Command_GetLog_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

const ::google::protobuf::EnumDescriptor* Command_Security_ACL_HMACAlgorithm_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Security_ACL_HMACAlgorithm_descriptor_;
}
bool Command_Security_ACL_HMACAlgorithm_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_Security_ACL_HMACAlgorithm Command_Security_ACL::INVALID_HMAC_ALGORITHM;
const Command_Security_ACL_HMACAlgorithm Command_Security_ACL::HmacSHA1;
const Command_Security_ACL_HMACAlgorithm Command_Security_ACL::HMACAlgorithm_MIN;
const Command_Security_ACL_HMACAlgorithm Command_Security_ACL::HMACAlgorithm_MAX;
const int Command_Security_ACL::HMACAlgorithm_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* Command_Security_ACL_Permission_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Security_ACL_Permission_descriptor_;
}
bool Command_Security_ACL_Permission_IsValid(int value) {
    switch (value) {
        case -1:
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
const Command_Security_ACL_Permission Command_Security_ACL::INVALID_PERMISSION;
const Command_Security_ACL_Permission Command_Security_ACL::READ;
const Command_Security_ACL_Permission Command_Security_ACL::WRITE;
const Command_Security_ACL_Permission Command_Security_ACL::DELETE;
const Command_Security_ACL_Permission Command_Security_ACL::RANGE;
const Command_Security_ACL_Permission Command_Security_ACL::SETUP;
const Command_Security_ACL_Permission Command_Security_ACL::P2POP;
const Command_Security_ACL_Permission Command_Security_ACL::GETLOG;
const Command_Security_ACL_Permission Command_Security_ACL::SECURITY;
const Command_Security_ACL_Permission Command_Security_ACL::Permission_MIN;
const Command_Security_ACL_Permission Command_Security_ACL::Permission_MAX;
const int Command_Security_ACL::Permission_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command_Security_ACL_Scope::kOffsetFieldNumber;
const int Command_Security_ACL_Scope::kValueFieldNumber;
const int Command_Security_ACL_Scope::kPermissionFieldNumber;
const int Command_Security_ACL_Scope::kTlsRequiredFieldNumber;
#endif  // !_MSC_VER

Command_Security_ACL_Scope::Command_Security_ACL_Scope()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
}

void Command_Security_ACL_Scope::InitAsDefaultInstance() {
}

Command_Security_ACL_Scope::Command_Security_ACL_Scope(const Command_Security_ACL_Scope& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
}

void Command_Security_ACL_Scope::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    offset_ = GOOGLE_LONGLONG(0);
    value_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    tlsrequired_ = false;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Security_ACL_Scope::~Command_Security_ACL_Scope() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    SharedDtor();
}

void Command_Security_ACL_Scope::SharedDtor() {
    if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete value_;
    }
    if (this != default_instance_) {
    }
}

void Command_Security_ACL_Scope::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Security_ACL_Scope::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Security_ACL_Scope_descriptor_;
}

const Command_Security_ACL_Scope& Command_Security_ACL_Scope::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Security_ACL_Scope* Command_Security_ACL_Scope::default_instance_ = NULL;

Command_Security_ACL_Scope* Command_Security_ACL_Scope::New() const {
    return new Command_Security_ACL_Scope;
}

void Command_Security_ACL_Scope::Clear() {
    if (_has_bits_[0 / 32] & 11) {
        offset_ = GOOGLE_LONGLONG(0);
        if (has_value()) {
            if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                value_->clear();
            }
        }
        tlsrequired_ = false;
    }
    permission_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Security_ACL_Scope::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional int64 offset = 1;
            case 1: {
                if (tag == 8) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64 > (
                             input, &offset_)));
                    set_has_offset();
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_value;
                break;
            }

            // optional bytes value = 2;
            case 2: {
                if (tag == 18) {
parse_value:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_value()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_permission;
                break;
            }

            // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Permission permission = 3;
            case 3: {
                if (tag == 24) {
parse_permission:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Security_ACL_Permission_IsValid(value)) {
                        add_permission(static_cast<::com::seagate::kinetic::proto::Command_Security_ACL_Permission>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(3, value);
                    }
                }
                else if (tag == 26) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPackedEnumNoInline(
                             input,
                             &::com::seagate::kinetic::proto::Command_Security_ACL_Permission_IsValid,
                             this->mutable_permission())));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_permission;
                if (input->ExpectTag(32)) goto parse_TlsRequired;
                break;
            }

            // optional bool TlsRequired = 4;
            case 4: {
                if (tag == 32) {
parse_TlsRequired:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL > (
                             input, &tlsrequired_)));
                    set_has_tlsrequired();
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    return false;
#undef DO_
}

void Command_Security_ACL_Scope::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    // optional int64 offset = 1;
    if (has_offset()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->offset(), output);
    }

    // optional bytes value = 2;
    if (has_value()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->value(), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Permission permission = 3;
    for (int i = 0; i < this->permission_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            3, this->permission(i), output);
    }

    // optional bool TlsRequired = 4;
    if (has_tlsrequired()) {
        ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->tlsrequired(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
}

::google::protobuf::uint8* Command_Security_ACL_Scope::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    // optional int64 offset = 1;
    if (has_offset()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->offset(), target);
    }

    // optional bytes value = 2;
    if (has_value()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->value(), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Permission permission = 3;
    for (int i = 0; i < this->permission_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     3, this->permission(i), target);
    }

    // optional bool TlsRequired = 4;
    if (has_tlsrequired()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->tlsrequired(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Security.ACL.Scope)
    return target;
}

int Command_Security_ACL_Scope::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 offset = 1;
        if (has_offset()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->offset());
        }

        // optional bytes value = 2;
        if (has_value()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->value());
        }

        // optional bool TlsRequired = 4;
        if (has_tlsrequired()) {
            total_size += 1 + 1;
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Permission permission = 3;
    {
        int data_size = 0;
        for (int i = 0; i < this->permission_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
                             this->permission(i));
        }
        total_size += 1 * this->permission_size() + data_size;
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

void Command_Security_ACL_Scope::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Security_ACL_Scope* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Security_ACL_Scope*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Security_ACL_Scope::MergeFrom(const Command_Security_ACL_Scope& from) {
    GOOGLE_CHECK_NE(&from, this);
    permission_.MergeFrom(from.permission_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_offset()) {
            set_offset(from.offset());
        }
        if (from.has_value()) {
            set_value(from.value());
        }
        if (from.has_tlsrequired()) {
            set_tlsrequired(from.tlsrequired());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Security_ACL_Scope::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Security_ACL_Scope::CopyFrom(const Command_Security_ACL_Scope& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Security_ACL_Scope::IsInitialized() const {

    return true;
}

void Command_Security_ACL_Scope::Swap(Command_Security_ACL_Scope* other) {
    if (other != this) {
        std::swap(offset_, other->offset_);
        std::swap(value_, other->value_);
        permission_.Swap(&other->permission_);
        std::swap(tlsrequired_, other->tlsrequired_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Security_ACL_Scope::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Security_ACL_Scope_descriptor_;
    metadata.reflection = Command_Security_ACL_Scope_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Security_ACL::kIdentityFieldNumber;
const int Command_Security_ACL::kKeyFieldNumber;
const int Command_Security_ACL::kHmacAlgorithmFieldNumber;
const int Command_Security_ACL::kScopeFieldNumber;
const int Command_Security_ACL::kMaxPriorityFieldNumber;
#endif  // !_MSC_VER

Command_Security_ACL::Command_Security_ACL()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Security.ACL)
}

void Command_Security_ACL::InitAsDefaultInstance() {
}

Command_Security_ACL::Command_Security_ACL(const Command_Security_ACL& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Security.ACL)
}

void Command_Security_ACL::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    identity_ = GOOGLE_LONGLONG(0);
    key_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    hmacalgorithm_ = -1;
    maxpriority_ = 5;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Security_ACL::~Command_Security_ACL() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Security.ACL)
    SharedDtor();
}

void Command_Security_ACL::SharedDtor() {
    if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete key_;
    }
    if (this != default_instance_) {
    }
}

void Command_Security_ACL::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Security_ACL::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Security_ACL_descriptor_;
}

const Command_Security_ACL& Command_Security_ACL::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Security_ACL* Command_Security_ACL::default_instance_ = NULL;

Command_Security_ACL* Command_Security_ACL::New() const {
    return new Command_Security_ACL;
}

void Command_Security_ACL::Clear() {
    if (_has_bits_[0 / 32] & 23) {
        identity_ = GOOGLE_LONGLONG(0);
        if (has_key()) {
            if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                key_->clear();
            }
        }
        hmacalgorithm_ = -1;
        maxpriority_ = 5;
    }
    scope_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Security_ACL::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Security.ACL)
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
                if (input->ExpectTag(18)) goto parse_key;
                break;
            }

            // optional bytes key = 2;
            case 2: {
                if (tag == 18) {
parse_key:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_key()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(24)) goto parse_hmacAlgorithm;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Security.ACL.HMACAlgorithm hmacAlgorithm = 3;
            case 3: {
                if (tag == 24) {
parse_hmacAlgorithm:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm_IsValid(value)) {
                        set_hmacalgorithm(static_cast<::com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm>(value));
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

            // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Scope scope = 4;
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
                if (input->ExpectTag(40)) goto parse_maxPriority;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Priority maxPriority = 5;
            case 5: {
                if (tag == 40) {
parse_maxPriority:
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_Priority_IsValid(value)) {
                        set_maxpriority(static_cast<::com::seagate::kinetic::proto::Command_Priority>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(5, value);
                    }
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Security.ACL)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Security.ACL)
    return false;
#undef DO_
}

void Command_Security_ACL::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Security.ACL)
    // optional int64 identity = 1;
    if (has_identity()) {
        ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->identity(), output);
    }

    // optional bytes key = 2;
    if (has_key()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            2, this->key(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Security.ACL.HMACAlgorithm hmacAlgorithm = 3;
    if (has_hmacalgorithm()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            3, this->hmacalgorithm(), output);
    }

    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Scope scope = 4;
    for (int i = 0; i < this->scope_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, this->scope(i), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Priority maxPriority = 5;
    if (has_maxpriority()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            5, this->maxpriority(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Security.ACL)
}

::google::protobuf::uint8* Command_Security_ACL::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Security.ACL)
    // optional int64 identity = 1;
    if (has_identity()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->identity(), target);
    }

    // optional bytes key = 2;
    if (has_key()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                2, this->key(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Security.ACL.HMACAlgorithm hmacAlgorithm = 3;
    if (has_hmacalgorithm()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     3, this->hmacalgorithm(), target);
    }

    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Scope scope = 4;
    for (int i = 0; i < this->scope_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     4, this->scope(i), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Priority maxPriority = 5;
    if (has_maxpriority()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     5, this->maxpriority(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Security.ACL)
    return target;
}

int Command_Security_ACL::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional int64 identity = 1;
        if (has_identity()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::Int64Size(
                              this->identity());
        }

        // optional bytes key = 2;
        if (has_key()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->key());
        }

        // optional .com.seagate.kinetic.proto.Command.Security.ACL.HMACAlgorithm hmacAlgorithm = 3;
        if (has_hmacalgorithm()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->hmacalgorithm());
        }

        // optional .com.seagate.kinetic.proto.Command.Priority maxPriority = 5;
        if (has_maxpriority()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->maxpriority());
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.Security.ACL.Scope scope = 4;
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

void Command_Security_ACL::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Security_ACL* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Security_ACL*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Security_ACL::MergeFrom(const Command_Security_ACL& from) {
    GOOGLE_CHECK_NE(&from, this);
    scope_.MergeFrom(from.scope_);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_identity()) {
            set_identity(from.identity());
        }
        if (from.has_key()) {
            set_key(from.key());
        }
        if (from.has_hmacalgorithm()) {
            set_hmacalgorithm(from.hmacalgorithm());
        }
        if (from.has_maxpriority()) {
            set_maxpriority(from.maxpriority());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Security_ACL::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Security_ACL::CopyFrom(const Command_Security_ACL& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Security_ACL::IsInitialized() const {

    return true;
}

void Command_Security_ACL::Swap(Command_Security_ACL* other) {
    if (other != this) {
        std::swap(identity_, other->identity_);
        std::swap(key_, other->key_);
        std::swap(hmacalgorithm_, other->hmacalgorithm_);
        scope_.Swap(&other->scope_);
        std::swap(maxpriority_, other->maxpriority_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Security_ACL::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Security_ACL_descriptor_;
    metadata.reflection = Command_Security_ACL_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command_Security::kAclFieldNumber;
const int Command_Security::kOldLockPINFieldNumber;
const int Command_Security::kNewLockPINFieldNumber;
const int Command_Security::kOldErasePINFieldNumber;
const int Command_Security::kNewErasePINFieldNumber;
#endif  // !_MSC_VER

Command_Security::Command_Security()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.Security)
}

void Command_Security::InitAsDefaultInstance() {
}

Command_Security::Command_Security(const Command_Security& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.Security)
}

void Command_Security::SharedCtor() {
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    oldlockpin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    newlockpin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    olderasepin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    newerasepin_ = const_cast<::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_Security::~Command_Security() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.Security)
    SharedDtor();
}

void Command_Security::SharedDtor() {
    if (oldlockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete oldlockpin_;
    }
    if (newlockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete newlockpin_;
    }
    if (olderasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete olderasepin_;
    }
    if (newerasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        delete newerasepin_;
    }
    if (this != default_instance_) {
    }
}

void Command_Security::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_Security::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_Security_descriptor_;
}

const Command_Security& Command_Security::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_Security* Command_Security::default_instance_ = NULL;

Command_Security* Command_Security::New() const {
    return new Command_Security;
}

void Command_Security::Clear() {
    if (_has_bits_[0 / 32] & 30) {
        if (has_oldlockpin()) {
            if (oldlockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                oldlockpin_->clear();
            }
        }
        if (has_newlockpin()) {
            if (newlockpin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                newlockpin_->clear();
            }
        }
        if (has_olderasepin()) {
            if (olderasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                olderasepin_->clear();
            }
        }
        if (has_newerasepin()) {
            if (newerasepin_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
                newerasepin_->clear();
            }
        }
    }
    acl_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_Security::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.Security)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // repeated .com.seagate.kinetic.proto.Command.Security.ACL acl = 2;
            case 2: {
                if (tag == 18) {
parse_acl:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, add_acl()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_acl;
                if (input->ExpectTag(26)) goto parse_oldLockPIN;
                break;
            }

            // optional bytes oldLockPIN = 3;
            case 3: {
                if (tag == 26) {
parse_oldLockPIN:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_oldlockpin()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(34)) goto parse_newLockPIN;
                break;
            }

            // optional bytes newLockPIN = 4;
            case 4: {
                if (tag == 34) {
parse_newLockPIN:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_newlockpin()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(42)) goto parse_oldErasePIN;
                break;
            }

            // optional bytes oldErasePIN = 5;
            case 5: {
                if (tag == 42) {
parse_oldErasePIN:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_olderasepin()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(50)) goto parse_newErasePIN;
                break;
            }

            // optional bytes newErasePIN = 6;
            case 6: {
                if (tag == 50) {
parse_newErasePIN:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                            input, this->mutable_newerasepin()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.Security)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.Security)
    return false;
#undef DO_
}

void Command_Security::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.Security)
    // repeated .com.seagate.kinetic.proto.Command.Security.ACL acl = 2;
    for (int i = 0; i < this->acl_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            2, this->acl(i), output);
    }

    // optional bytes oldLockPIN = 3;
    if (has_oldlockpin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            3, this->oldlockpin(), output);
    }

    // optional bytes newLockPIN = 4;
    if (has_newlockpin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            4, this->newlockpin(), output);
    }

    // optional bytes oldErasePIN = 5;
    if (has_olderasepin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            5, this->olderasepin(), output);
    }

    // optional bytes newErasePIN = 6;
    if (has_newerasepin()) {
        ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
            6, this->newerasepin(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.Security)
}

::google::protobuf::uint8* Command_Security::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.Security)
    // repeated .com.seagate.kinetic.proto.Command.Security.ACL acl = 2;
    for (int i = 0; i < this->acl_size(); i++) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     2, this->acl(i), target);
    }

    // optional bytes oldLockPIN = 3;
    if (has_oldlockpin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                3, this->oldlockpin(), target);
    }

    // optional bytes newLockPIN = 4;
    if (has_newlockpin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                4, this->newlockpin(), target);
    }

    // optional bytes oldErasePIN = 5;
    if (has_olderasepin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                5, this->olderasepin(), target);
    }

    // optional bytes newErasePIN = 6;
    if (has_newerasepin()) {
        target =
            ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
                6, this->newerasepin(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.Security)
    return target;
}

int Command_Security::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
        // optional bytes oldLockPIN = 3;
        if (has_oldlockpin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->oldlockpin());
        }

        // optional bytes newLockPIN = 4;
        if (has_newlockpin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->newlockpin());
        }

        // optional bytes oldErasePIN = 5;
        if (has_olderasepin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->olderasepin());
        }

        // optional bytes newErasePIN = 6;
        if (has_newerasepin()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::BytesSize(
                              this->newerasepin());
        }

    }
    // repeated .com.seagate.kinetic.proto.Command.Security.ACL acl = 2;
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

void Command_Security::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_Security* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_Security*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_Security::MergeFrom(const Command_Security& from) {
    GOOGLE_CHECK_NE(&from, this);
    acl_.MergeFrom(from.acl_);
    if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
        if (from.has_oldlockpin()) {
            set_oldlockpin(from.oldlockpin());
        }
        if (from.has_newlockpin()) {
            set_newlockpin(from.newlockpin());
        }
        if (from.has_olderasepin()) {
            set_olderasepin(from.olderasepin());
        }
        if (from.has_newerasepin()) {
            set_newerasepin(from.newerasepin());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_Security::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_Security::CopyFrom(const Command_Security& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_Security::IsInitialized() const {

    return true;
}

void Command_Security::Swap(Command_Security* other) {
    if (other != this) {
        acl_.Swap(&other->acl_);
        std::swap(oldlockpin_, other->oldlockpin_);
        std::swap(newlockpin_, other->newlockpin_);
        std::swap(olderasepin_, other->olderasepin_);
        std::swap(newerasepin_, other->newerasepin_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_Security::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_Security_descriptor_;
    metadata.reflection = Command_Security_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

const ::google::protobuf::EnumDescriptor* Command_PinOperation_PinOpType_descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_PinOperation_PinOpType_descriptor_;
}
bool Command_PinOperation_PinOpType_IsValid(int value) {
    switch (value) {
        case -1:
        case 1:
        case 2:
        case 3:
        case 4:
            return true;
        default:
            return false;
    }
}

#ifndef _MSC_VER
const Command_PinOperation_PinOpType Command_PinOperation::INVALID_PINOP;
const Command_PinOperation_PinOpType Command_PinOperation::UNLOCK_PINOP;
const Command_PinOperation_PinOpType Command_PinOperation::LOCK_PINOP;
const Command_PinOperation_PinOpType Command_PinOperation::ERASE_PINOP;
const Command_PinOperation_PinOpType Command_PinOperation::SECURE_ERASE_PINOP;
const Command_PinOperation_PinOpType Command_PinOperation::PinOpType_MIN;
const Command_PinOperation_PinOpType Command_PinOperation::PinOpType_MAX;
const int Command_PinOperation::PinOpType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Command_PinOperation::kPinOpTypeFieldNumber;
#endif  // !_MSC_VER

Command_PinOperation::Command_PinOperation()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command.PinOperation)
}

void Command_PinOperation::InitAsDefaultInstance() {
}

Command_PinOperation::Command_PinOperation(const Command_PinOperation& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command.PinOperation)
}

void Command_PinOperation::SharedCtor() {
    _cached_size_ = 0;
    pinoptype_ = -1;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command_PinOperation::~Command_PinOperation() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command.PinOperation)
    SharedDtor();
}

void Command_PinOperation::SharedDtor() {
    if (this != default_instance_) {
    }
}

void Command_PinOperation::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command_PinOperation::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_PinOperation_descriptor_;
}

const Command_PinOperation& Command_PinOperation::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command_PinOperation* Command_PinOperation::default_instance_ = NULL;

Command_PinOperation* Command_PinOperation::New() const {
    return new Command_PinOperation;
}

void Command_PinOperation::Clear() {
    pinoptype_ = -1;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command_PinOperation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command.PinOperation)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.PinOperation.PinOpType pinOpType = 1;
            case 1: {
                if (tag == 8) {
                    int value;
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive <
                         int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM > (
                             input, &value)));
                    if (::com::seagate::kinetic::proto::Command_PinOperation_PinOpType_IsValid(value)) {
                        set_pinoptype(static_cast<::com::seagate::kinetic::proto::Command_PinOperation_PinOpType>(value));
                    }
                    else {
                        mutable_unknown_fields()->AddVarint(1, value);
                    }
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command.PinOperation)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command.PinOperation)
    return false;
#undef DO_
}

void Command_PinOperation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command.PinOperation)
    // optional .com.seagate.kinetic.proto.Command.PinOperation.PinOpType pinOpType = 1;
    if (has_pinoptype()) {
        ::google::protobuf::internal::WireFormatLite::WriteEnum(
            1, this->pinoptype(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command.PinOperation)
}

::google::protobuf::uint8* Command_PinOperation::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command.PinOperation)
    // optional .com.seagate.kinetic.proto.Command.PinOperation.PinOpType pinOpType = 1;
    if (has_pinoptype()) {
        target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
                     1, this->pinoptype(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command.PinOperation)
    return target;
}

int Command_PinOperation::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.PinOperation.PinOpType pinOpType = 1;
        if (has_pinoptype()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::EnumSize(this->pinoptype());
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

void Command_PinOperation::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command_PinOperation* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command_PinOperation*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command_PinOperation::MergeFrom(const Command_PinOperation& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_pinoptype()) {
            set_pinoptype(from.pinoptype());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command_PinOperation::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command_PinOperation::CopyFrom(const Command_PinOperation& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command_PinOperation::IsInitialized() const {

    return true;
}

void Command_PinOperation::Swap(Command_PinOperation* other) {
    if (other != this) {
        std::swap(pinoptype_, other->pinoptype_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command_PinOperation::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_PinOperation_descriptor_;
    metadata.reflection = Command_PinOperation_reflection_;
    return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Command::kHeaderFieldNumber;
const int Command::kBodyFieldNumber;
const int Command::kStatusFieldNumber;
#endif  // !_MSC_VER

Command::Command()
    : ::google::protobuf::Message() {
    SharedCtor();
    // @@protoc_insertion_point(constructor:com.seagate.kinetic.proto.Command)
}

void Command::InitAsDefaultInstance() {
    header_ = const_cast<::com::seagate::kinetic::proto::Command_Header*>(&::com::seagate::kinetic::proto::Command_Header::default_instance());
    body_ = const_cast<::com::seagate::kinetic::proto::Command_Body*>(&::com::seagate::kinetic::proto::Command_Body::default_instance());
    status_ = const_cast<::com::seagate::kinetic::proto::Command_Status*>(&::com::seagate::kinetic::proto::Command_Status::default_instance());
}

Command::Command(const Command& from)
    : ::google::protobuf::Message() {
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:com.seagate.kinetic.proto.Command)
}

void Command::SharedCtor() {
    _cached_size_ = 0;
    header_ = NULL;
    body_ = NULL;
    status_ = NULL;
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Command::~Command() {
    // @@protoc_insertion_point(destructor:com.seagate.kinetic.proto.Command)
    SharedDtor();
}

void Command::SharedDtor() {
    if (this != default_instance_) {
        delete header_;
        delete body_;
        delete status_;
    }
}

void Command::SetCachedSize(int size) const {
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Command::descriptor() {
    protobuf_AssignDescriptorsOnce();
    return Command_descriptor_;
}

const Command& Command::default_instance() {
    if (default_instance_ == NULL) protobuf_AddDesc_Kinetic_2eproto();
    return *default_instance_;
}

Command* Command::default_instance_ = NULL;

Command* Command::New() const {
    return new Command;
}

void Command::Clear() {
    if (_has_bits_[0 / 32] & 7) {
        if (has_header()) {
            if (header_ != NULL) header_->::com::seagate::kinetic::proto::Command_Header::Clear();
        }
        if (has_body()) {
            if (body_ != NULL) body_->::com::seagate::kinetic::proto::Command_Body::Clear();
        }
        if (has_status()) {
            if (status_ != NULL) status_->::com::seagate::kinetic::proto::Command_Status::Clear();
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    mutable_unknown_fields()->Clear();
}

bool Command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    ::google::protobuf::uint32 tag;
    // @@protoc_insertion_point(parse_start:com.seagate.kinetic.proto.Command)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second) goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .com.seagate.kinetic.proto.Command.Header header = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_header()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18)) goto parse_body;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Body body = 2;
            case 2: {
                if (tag == 18) {
parse_body:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_body()));
                }
                else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26)) goto parse_status;
                break;
            }

            // optional .com.seagate.kinetic.proto.Command.Status status = 3;
            case 3: {
                if (tag == 26) {
parse_status:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                            input, mutable_status()));
                }
                else {
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
    // @@protoc_insertion_point(parse_success:com.seagate.kinetic.proto.Command)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:com.seagate.kinetic.proto.Command)
    return false;
#undef DO_
}

void Command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
    // @@protoc_insertion_point(serialize_start:com.seagate.kinetic.proto.Command)
    // optional .com.seagate.kinetic.proto.Command.Header header = 1;
    if (has_header()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            1, this->header(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Body body = 2;
    if (has_body()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            2, this->body(), output);
    }

    // optional .com.seagate.kinetic.proto.Command.Status status = 3;
    if (has_status()) {
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            3, this->status(), output);
    }

    if (!unknown_fields().empty()) {
        ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
            unknown_fields(), output);
    }
    // @@protoc_insertion_point(serialize_end:com.seagate.kinetic.proto.Command)
}

::google::protobuf::uint8* Command::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
    // @@protoc_insertion_point(serialize_to_array_start:com.seagate.kinetic.proto.Command)
    // optional .com.seagate.kinetic.proto.Command.Header header = 1;
    if (has_header()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     1, this->header(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Body body = 2;
    if (has_body()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     2, this->body(), target);
    }

    // optional .com.seagate.kinetic.proto.Command.Status status = 3;
    if (has_status()) {
        target = ::google::protobuf::internal::WireFormatLite::
                 WriteMessageNoVirtualToArray(
                     3, this->status(), target);
    }

    if (!unknown_fields().empty()) {
        target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
                     unknown_fields(), target);
    }
    // @@protoc_insertion_point(serialize_to_array_end:com.seagate.kinetic.proto.Command)
    return target;
}

int Command::ByteSize() const {
    int total_size = 0;

    if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        // optional .com.seagate.kinetic.proto.Command.Header header = 1;
        if (has_header()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->header());
        }

        // optional .com.seagate.kinetic.proto.Command.Body body = 2;
        if (has_body()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->body());
        }

        // optional .com.seagate.kinetic.proto.Command.Status status = 3;
        if (has_status()) {
            total_size += 1 +
                          ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                              this->status());
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

void Command::MergeFrom(const ::google::protobuf::Message& from) {
    GOOGLE_CHECK_NE(&from, this);
    const Command* source =
        ::google::protobuf::internal::dynamic_cast_if_available<const Command*>(
            &from);
    if (source == NULL) {
        ::google::protobuf::internal::ReflectionOps::Merge(from, this);
    }
    else {
        MergeFrom(*source);
    }
}

void Command::MergeFrom(const Command& from) {
    GOOGLE_CHECK_NE(&from, this);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_header()) {
            mutable_header()->::com::seagate::kinetic::proto::Command_Header::MergeFrom(from.header());
        }
        if (from.has_body()) {
            mutable_body()->::com::seagate::kinetic::proto::Command_Body::MergeFrom(from.body());
        }
        if (from.has_status()) {
            mutable_status()->::com::seagate::kinetic::proto::Command_Status::MergeFrom(from.status());
        }
    }
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Command::CopyFrom(const ::google::protobuf::Message& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

void Command::CopyFrom(const Command& from) {
    if (&from == this) return;
    Clear();
    MergeFrom(from);
}

bool Command::IsInitialized() const {

    return true;
}

void Command::Swap(Command* other) {
    if (other != this) {
        std::swap(header_, other->header_);
        std::swap(body_, other->body_);
        std::swap(status_, other->status_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }
}

::google::protobuf::Metadata Command::GetMetadata() const {
    protobuf_AssignDescriptorsOnce();
    ::google::protobuf::Metadata metadata;
    metadata.descriptor = Command_descriptor_;
    metadata.reflection = Command_reflection_;
    return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace kinetic
}  // namespace seagate
}  // namespace com

// @@protoc_insertion_point(global_scope)
