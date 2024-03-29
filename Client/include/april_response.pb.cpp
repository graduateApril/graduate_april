// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "april_response.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace april {

namespace {

const ::google::protobuf::Descriptor* response_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  response_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_april_5fresponse_2eproto() {
  protobuf_AddDesc_april_5fresponse_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "april_response.proto");
  GOOGLE_CHECK(file != NULL);
  response_descriptor_ = file->message_type(0);
  static const int response_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(response, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(response, sync_),
  };
  response_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      response_descriptor_,
      response::default_instance_,
      response_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(response, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(response, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(response));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_april_5fresponse_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    response_descriptor_, &response::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_april_5fresponse_2eproto() {
  delete response::default_instance_;
  delete response_reflection_;
}

void protobuf_AddDesc_april_5fresponse_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024april_response.proto\022\005april\"$\n\010respons"
    "e\022\n\n\002id\030\001 \002(\005\022\014\n\004sync\030\002 \002(\010", 67);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "april_response.proto", &protobuf_RegisterTypes);
  response::default_instance_ = new response();
  response::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_april_5fresponse_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_april_5fresponse_2eproto {
  StaticDescriptorInitializer_april_5fresponse_2eproto() {
    protobuf_AddDesc_april_5fresponse_2eproto();
  }
} static_descriptor_initializer_april_5fresponse_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int response::kIdFieldNumber;
const int response::kSyncFieldNumber;
#endif  // !_MSC_VER

response::response()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void response::InitAsDefaultInstance() {
}

response::response(const response& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void response::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  sync_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

response::~response() {
  SharedDtor();
}

void response::SharedDtor() {
  if (this != default_instance_) {
  }
}

void response::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* response::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return response_descriptor_;
}

const response& response::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_april_5fresponse_2eproto();  return *default_instance_;
}

response* response::default_instance_ = NULL;

response* response::New() const {
  return new response;
}

void response::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0;
    sync_ = false;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool response::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_sync;
        break;
      }
      
      // required bool sync = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_sync:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &sync_)));
          set_has_sync();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void response::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }
  
  // required bool sync = 2;
  if (has_sync()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->sync(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* response::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }
  
  // required bool sync = 2;
  if (has_sync()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->sync(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int response::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }
    
    // required bool sync = 2;
    if (has_sync()) {
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

void response::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const response* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const response*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void response::MergeFrom(const response& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_sync()) {
      set_sync(from.sync());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void response::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void response::CopyFrom(const response& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool response::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void response::Swap(response* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(sync_, other->sync_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata response::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = response_descriptor_;
  metadata.reflection = response_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace april

// @@protoc_insertion_point(global_scope)
