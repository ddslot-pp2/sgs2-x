// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LOBBY.proto

#ifndef PROTOBUF_LOBBY_2eproto__INCLUDED
#define PROTOBUF_LOBBY_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace LOBBY {
class CS_LOG_IN;
class CS_LOG_INDefaultTypeInternal;
extern CS_LOG_INDefaultTypeInternal _CS_LOG_IN_default_instance_;
class SC_LOG_IN;
class SC_LOG_INDefaultTypeInternal;
extern SC_LOG_INDefaultTypeInternal _SC_LOG_IN_default_instance_;
}  // namespace LOBBY

namespace LOBBY {

namespace protobuf_LOBBY_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_LOBBY_2eproto

enum GameDataType {
  test_1 = 0,
  test_2 = 1,
  test_3 = 2,
  GameDataType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  GameDataType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool GameDataType_IsValid(int value);
const GameDataType GameDataType_MIN = test_1;
const GameDataType GameDataType_MAX = test_3;
const int GameDataType_ARRAYSIZE = GameDataType_MAX + 1;

const ::google::protobuf::EnumDescriptor* GameDataType_descriptor();
inline const ::std::string& GameDataType_Name(GameDataType value) {
  return ::google::protobuf::internal::NameOfEnum(
    GameDataType_descriptor(), value);
}
inline bool GameDataType_Parse(
    const ::std::string& name, GameDataType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GameDataType>(
    GameDataType_descriptor(), name, value);
}
// ===================================================================

class CS_LOG_IN : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:LOBBY.CS_LOG_IN) */ {
 public:
  CS_LOG_IN();
  virtual ~CS_LOG_IN();

  CS_LOG_IN(const CS_LOG_IN& from);

  inline CS_LOG_IN& operator=(const CS_LOG_IN& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CS_LOG_IN& default_instance();

  static inline const CS_LOG_IN* internal_default_instance() {
    return reinterpret_cast<const CS_LOG_IN*>(
               &_CS_LOG_IN_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(CS_LOG_IN* other);

  // implements Message ----------------------------------------------

  inline CS_LOG_IN* New() const PROTOBUF_FINAL { return New(NULL); }

  CS_LOG_IN* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CS_LOG_IN& from);
  void MergeFrom(const CS_LOG_IN& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CS_LOG_IN* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  #if LANG_CXX11
  void set_id(::std::string&& value);
  #endif
  void set_id(const char* value);
  void set_id(const char* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // string password = 2;
  void clear_password();
  static const int kPasswordFieldNumber = 2;
  const ::std::string& password() const;
  void set_password(const ::std::string& value);
  #if LANG_CXX11
  void set_password(::std::string&& value);
  #endif
  void set_password(const char* value);
  void set_password(const char* value, size_t size);
  ::std::string* mutable_password();
  ::std::string* release_password();
  void set_allocated_password(::std::string* password);

  // @@protoc_insertion_point(class_scope:LOBBY.CS_LOG_IN)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr password_;
  mutable int _cached_size_;
  friend struct protobuf_LOBBY_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class SC_LOG_IN : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:LOBBY.SC_LOG_IN) */ {
 public:
  SC_LOG_IN();
  virtual ~SC_LOG_IN();

  SC_LOG_IN(const SC_LOG_IN& from);

  inline SC_LOG_IN& operator=(const SC_LOG_IN& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SC_LOG_IN& default_instance();

  static inline const SC_LOG_IN* internal_default_instance() {
    return reinterpret_cast<const SC_LOG_IN*>(
               &_SC_LOG_IN_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(SC_LOG_IN* other);

  // implements Message ----------------------------------------------

  inline SC_LOG_IN* New() const PROTOBUF_FINAL { return New(NULL); }

  SC_LOG_IN* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const SC_LOG_IN& from);
  void MergeFrom(const SC_LOG_IN& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(SC_LOG_IN* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string ec = 3;
  void clear_ec();
  static const int kEcFieldNumber = 3;
  const ::std::string& ec() const;
  void set_ec(const ::std::string& value);
  #if LANG_CXX11
  void set_ec(::std::string&& value);
  #endif
  void set_ec(const char* value);
  void set_ec(const char* value, size_t size);
  ::std::string* mutable_ec();
  ::std::string* release_ec();
  void set_allocated_ec(::std::string* ec);

  // int64 timestamp = 2;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 2;
  ::google::protobuf::int64 timestamp() const;
  void set_timestamp(::google::protobuf::int64 value);

  // bool result = 1;
  void clear_result();
  static const int kResultFieldNumber = 1;
  bool result() const;
  void set_result(bool value);

  // @@protoc_insertion_point(class_scope:LOBBY.SC_LOG_IN)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr ec_;
  ::google::protobuf::int64 timestamp_;
  bool result_;
  mutable int _cached_size_;
  friend struct protobuf_LOBBY_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CS_LOG_IN

// string id = 1;
inline void CS_LOG_IN::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CS_LOG_IN::id() const {
  // @@protoc_insertion_point(field_get:LOBBY.CS_LOG_IN.id)
  return id_.GetNoArena();
}
inline void CS_LOG_IN::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:LOBBY.CS_LOG_IN.id)
}
#if LANG_CXX11
inline void CS_LOG_IN::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:LOBBY.CS_LOG_IN.id)
}
#endif
inline void CS_LOG_IN::set_id(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:LOBBY.CS_LOG_IN.id)
}
inline void CS_LOG_IN::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:LOBBY.CS_LOG_IN.id)
}
inline ::std::string* CS_LOG_IN::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:LOBBY.CS_LOG_IN.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CS_LOG_IN::release_id() {
  // @@protoc_insertion_point(field_release:LOBBY.CS_LOG_IN.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CS_LOG_IN::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:LOBBY.CS_LOG_IN.id)
}

// string password = 2;
inline void CS_LOG_IN::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CS_LOG_IN::password() const {
  // @@protoc_insertion_point(field_get:LOBBY.CS_LOG_IN.password)
  return password_.GetNoArena();
}
inline void CS_LOG_IN::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:LOBBY.CS_LOG_IN.password)
}
#if LANG_CXX11
inline void CS_LOG_IN::set_password(::std::string&& value) {
  
  password_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:LOBBY.CS_LOG_IN.password)
}
#endif
inline void CS_LOG_IN::set_password(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:LOBBY.CS_LOG_IN.password)
}
inline void CS_LOG_IN::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:LOBBY.CS_LOG_IN.password)
}
inline ::std::string* CS_LOG_IN::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:LOBBY.CS_LOG_IN.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CS_LOG_IN::release_password() {
  // @@protoc_insertion_point(field_release:LOBBY.CS_LOG_IN.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CS_LOG_IN::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:LOBBY.CS_LOG_IN.password)
}

// -------------------------------------------------------------------

// SC_LOG_IN

// bool result = 1;
inline void SC_LOG_IN::clear_result() {
  result_ = false;
}
inline bool SC_LOG_IN::result() const {
  // @@protoc_insertion_point(field_get:LOBBY.SC_LOG_IN.result)
  return result_;
}
inline void SC_LOG_IN::set_result(bool value) {
  
  result_ = value;
  // @@protoc_insertion_point(field_set:LOBBY.SC_LOG_IN.result)
}

// int64 timestamp = 2;
inline void SC_LOG_IN::clear_timestamp() {
  timestamp_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 SC_LOG_IN::timestamp() const {
  // @@protoc_insertion_point(field_get:LOBBY.SC_LOG_IN.timestamp)
  return timestamp_;
}
inline void SC_LOG_IN::set_timestamp(::google::protobuf::int64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:LOBBY.SC_LOG_IN.timestamp)
}

// string ec = 3;
inline void SC_LOG_IN::clear_ec() {
  ec_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& SC_LOG_IN::ec() const {
  // @@protoc_insertion_point(field_get:LOBBY.SC_LOG_IN.ec)
  return ec_.GetNoArena();
}
inline void SC_LOG_IN::set_ec(const ::std::string& value) {
  
  ec_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:LOBBY.SC_LOG_IN.ec)
}
#if LANG_CXX11
inline void SC_LOG_IN::set_ec(::std::string&& value) {
  
  ec_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:LOBBY.SC_LOG_IN.ec)
}
#endif
inline void SC_LOG_IN::set_ec(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  ec_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:LOBBY.SC_LOG_IN.ec)
}
inline void SC_LOG_IN::set_ec(const char* value, size_t size) {
  
  ec_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:LOBBY.SC_LOG_IN.ec)
}
inline ::std::string* SC_LOG_IN::mutable_ec() {
  
  // @@protoc_insertion_point(field_mutable:LOBBY.SC_LOG_IN.ec)
  return ec_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SC_LOG_IN::release_ec() {
  // @@protoc_insertion_point(field_release:LOBBY.SC_LOG_IN.ec)
  
  return ec_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SC_LOG_IN::set_allocated_ec(::std::string* ec) {
  if (ec != NULL) {
    
  } else {
    
  }
  ec_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ec);
  // @@protoc_insertion_point(field_set_allocated:LOBBY.SC_LOG_IN.ec)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace LOBBY

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::LOBBY::GameDataType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::LOBBY::GameDataType>() {
  return ::LOBBY::GameDataType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_LOBBY_2eproto__INCLUDED
