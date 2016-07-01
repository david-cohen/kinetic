# Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>

BASE_DIR    := $(shell pwd)
TIMESTAMP   := $(shell date)
SOURCE_HASH := $(shell ./tools/create-source-hash.sh)
PACKAGE_NAME = wdc-kinetic

# Currently only supports native builds

COMPILER_PREFIX     =
TOOLCHAIN_BIN_DIR   = /usr/bin
TOOLCHAIN_LIB_DIR   = /usr/lib/x86_64-linux-gnu

# Build Input Directories

APP_SRC_DIR     = $(BASE_DIR)/src
INCLUDE_DIR     = $(BASE_DIR)/include
PROTO_DIR       = $(BASE_DIR)/proto
TEST_SRC_DIR    = $(BASE_DIR)/test
PACKAGE_DIR     = $(BASE_DIR)/package
CONF_DIR        = $(BASE_DIR)/conf

# Build Output Directories

BUILD_DIR           = $(BASE_DIR)/build
BUILD_APP_BIN_DIR   = $(BUILD_DIR)/bin/app
BUILD_APP_OBJ_DIR   = $(BUILD_DIR)/obj/app
BUILD_PROTO_DIR     = $(BUILD_DIR)/proto
BUILD_TEST_BIN_DIR  = $(BUILD_DIR)/bin/test
BUILD_TEST_OBJ_DIR  = $(BUILD_DIR)/obj/test
BUILD_PACKAGE_DIR   = $(BUILD_DIR)/package
BUILD_DOXYGEN_DIR   = $(BUILD_DIR)/doxygen

# Dependencies Library Directories

DEPENDENCIES_DIR    = $(BASE_DIR)/dependencies
ASTYLE_DIR          = $(DEPENDENCIES_DIR)/astyle/build/gcc/bin
BOOST_DIR           = $(DEPENDENCIES_DIR)/boost
GOOGLE_TEST_DIR     = $(DEPENDENCIES_DIR)/googletest
ROCKSDB_DIR         = $(DEPENDENCIES_DIR)/rocksdb
LEVELDB_DIR         = $(DEPENDENCIES_DIR)/leveldb
LINT_DIR            = $(DEPENDENCIES_DIR)/styleguide/cpplint
PROTOBUF_DIR        = $(DEPENDENCIES_DIR)/protobuf
OPENSSL_DIR         = $(DEPENDENCIES_DIR)/openssl
CONFIG_DIR          = /etc/kaos

# Dependencies Libraries

GTEST_LIBRARY       = $(GOOGLE_TEST_DIR)/make/gtest_main.a
ROCKSDB_LIBRARY     = $(ROCKSDB_DIR)/librocksdb.a
LEVELDB_LIBRARY     = $(LEVELDB_DIR)/libleveldb.a
PROTOBUF_LIBRARY    = $(PROTOBUF_DIR)/src/.libs/libprotobuf.a
OPENSSL_LIBRARIES   = $(OPENSSL_DIR)/libssl.a $(OPENSSL_DIR)/libcrypto.a

# Compiler/Linker Parameters

CC              = $(COMPILER_PREFIX)gcc
CXX             = $(COMPILER_PREFIX)g++
CXX_APP_FLAGS   = -std=c++0x -g -Wall -Wextra -DTIMESTAMP="\"$(TIMESTAMP)\"" -DSOURCE_HASH="\"$(SOURCE_HASH)\""
CXX_TEST_FLAGS  = $(CXX_APP_FLAGS) -DUNIT_TEST -DTIMESTAMP="\"$(TIMESTAMP)\""
APP_INCLUDES    = -I$(BASE_DIR)/include -I$(BOOST_DIR) -I$(LEVELDB_DIR)/include -I$(ROCKSDB_DIR)/include -I$(PROTOBUF_DIR)/src -I$(OPENSSL_DIR)/include
APP_LIBRARIES   = $(LEVELDB_LIBRARY) $(ROCKSDB_LIBRARY) $(PROTOBUF_LIBRARY) $(OPENSSL_LIBRARIES) -L$(TOOLCHAIN_LIB_DIR) -lrt -lpthread
TEST_INCLUDES   = $(APP_INCLUDES) -I$(GOOGLE_TEST_DIR)/include
TEST_LIBRARIES  = $(GTEST_LIBRARY) $(APP_LIBRARIES)

# Build the Kinetic Advanced Object Storage

kaos:   $(BUILD_APP_BIN_DIR)/kaos

# Build the unit tests

test: \
	$(BUILD_TEST_BIN_DIR)/accessControlUnitTest \
	$(BUILD_TEST_BIN_DIR)/accessScopeUnitTest \
	$(BUILD_TEST_BIN_DIR)/heartbeatProviderUnitTest \
	$(BUILD_TEST_BIN_DIR)/hmacUnitTest \
	$(BUILD_TEST_BIN_DIR)/kineticMessageFramingUnitTest \
	$(BUILD_TEST_BIN_DIR)/serverSettingsUnitTest

# Run the unit tests

run-tests:
	$(BUILD_TEST_BIN_DIR)/accessControlUnitTest
	$(BUILD_TEST_BIN_DIR)/accessScopeUnitTest
	$(BUILD_TEST_BIN_DIR)/heartbeatProviderUnitTest
	$(BUILD_TEST_BIN_DIR)/hmacUnitTest
	$(BUILD_TEST_BIN_DIR)/kineticMessageFramingUnitTest
	$(BUILD_TEST_BIN_DIR)/serverSettingsUnitTest

# Build source from the protocol buffer files (rename the .cc files to .cpp)

proto:
	cd $(PROTOBUF_DIR) && export CC=gcc && ./configure && sudo make install
	[ -d $(BUILD_PROTO_DIR) ] || mkdir -p $(BUILD_PROTO_DIR)
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BUILD_PROTO_DIR) $(PROTO_DIR)/Kinetic.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BUILD_PROTO_DIR) $(PROTO_DIR)/Entry.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BUILD_PROTO_DIR) $(PROTO_DIR)/Settings.proto
	$(BASE_DIR)/tools/clean-proto-file.sh $(BUILD_PROTO_DIR) Entry
	$(BASE_DIR)/tools/clean-proto-file.sh $(BUILD_PROTO_DIR) Kinetic
	$(BASE_DIR)/tools/clean-proto-file.sh $(BUILD_PROTO_DIR) Settings
	mv $(BUILD_PROTO_DIR)/*.cpp $(APP_SRC_DIR)/
	mv $(BUILD_PROTO_DIR)/*.hpp $(INCLUDE_DIR)/

# Check for suspicious coding

check:
	- $(BASE_DIR)/tools/filtered-lint.sh $(BASE_DIR)

cpp-check:
	- cppcheck $(APP_SRC_DIR) --enable=all --force --includes-file=$(APP_INCLUDES)
	- cppcheck $(TEST_SRC_DIR) --enable=all --force --includes-file=$(APP_INCLUDES)

# Made the code follow a consistent coding style

conform:
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks --recursive "$(INCLUDE_DIR)/*.hpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks --recursive "$(TEST_SRC_DIR)/*.cpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks --recursive "$(APP_SRC_DIR)/*.cpp"

# Build the required dependencies

dependencies: dependencies-dir boost leveldb rocksdb openssl protobuf googletest lint astyle

dependencies-dir:
	mkdir -p $(DEPENDENCIES_DIR)
	chmod 777 $(DEPENDENCIES_DIR)

# Install the Boost C++ headers

boost:
	wget -P $(DEPENDENCIES_DIR) http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/boost_1_59_0.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/boost_1_59_0.tar.gz
	mv $(DEPENDENCIES_DIR)/boost_1_59_0 $(DEPENDENCIES_DIR)/boost
	sed -i '71d' $(BOOST_DIR)/boost/property_tree/detail/json_parser/narrow_encoding.hpp

# Build the levelDB library

leveldb:
	wget -P $(DEPENDENCIES_DIR) https://github.com/google/leveldb/archive/v1.18.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/v1.18.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/v1.18.tar.gz
	mv $(DEPENDENCIES_DIR)/leveldb-1.18 $(DEPENDENCIES_DIR)/leveldb
	export CC=$(CC) && export CXX=$(CXX) && cd $(LEVELDB_DIR) && \
	./build_detect_platform config $(LEVELDB_DIR) && make

# Build the rocksDB library

rocksdb:
	wget -P $(DEPENDENCIES_DIR) https://github.com/facebook/rocksdb/archive/4.8.fb.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/4.8.fb.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/4.8.fb.tar.gz
	mv $(DEPENDENCIES_DIR)/rocksdb-4.8.fb $(DEPENDENCIES_DIR)/rocksdb
	sed -i "s/CFLAGS += /CFLAGS += -DNDEBUG /g" $(ROCKSDB_DIR)/Makefile
	sed -i "s/CXXFLAGS += /CXXFLAGS += -DNDEBUG /g" $(ROCKSDB_DIR)/Makefile
	export CC=$(CC) && export CXX=$(CXX) && cd $(ROCKSDB_DIR) && \
	make static_lib

# Build the Open SSL libraries

openssl:
	wget -P $(DEPENDENCIES_DIR) https://www.openssl.org/source/openssl-1.0.0s.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/openssl-1.0.0s.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/openssl-1.0.0s.tar.gz
	mv $(DEPENDENCIES_DIR)/openssl-1.0.0s $(DEPENDENCIES_DIR)/openssl
	export CC=$(CC) && export CXX=$(CXX) && cd $(OPENSSL_DIR) && \
	./Configure --openssldir=$(OPENSSL_DIR) no-shared os/compiler:gcc && make

# Build the protocol buffer library

protobuf:
	wget -P $(DEPENDENCIES_DIR) https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/protobuf-2.6.1.tar.gz -C $(DEPENDENCIES_DIR)
	mv $(DEPENDENCIES_DIR)/protobuf-2.6.1 $(DEPENDENCIES_DIR)/protobuf
	rm $(DEPENDENCIES_DIR)/protobuf-2.6.1.tar.gz
	sed -i '1288s/.*/\ \ \ \ \ \ ) {/' $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1289i\ \ \ \ \ \ \ \ \ \ static_cast<void>(filename);" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1290i\ \ \ \ \ \ \ \ \ \ static_cast<void>(element_name);" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1291i\ \ \ \ \ \ \ \ \ \ static_cast<void>(descriptor);" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1292i\ \ \ \ \ \ \ \ \ \ static_cast<void>(location);" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1293i\ \ \ \ \ \ \ \ \ \ static_cast<void>(message);" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "1294i\ \ \ \ \ \ }" $(PROTOBUF_DIR)/src/google/protobuf/descriptor.h
	sed -i "405i\ \ \ \ static_cast<void>(message);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "406i\ \ \ \ static_cast<void>(oneof_descriptor);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i '398s/}//' $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "399i\ \ \ \ static_cast<void>(message);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "400i\ \ \ \ static_cast<void>(oneof_descriptor);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "401i\ \ }" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "394i\ \ \ \ static_cast<void>(message);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	sed -i "395i\ \ \ \ static_cast<void>(oneof_descriptor);" $(PROTOBUF_DIR)/src/google/protobuf/message.h
	cd $(PROTOBUF_DIR) && export CC=gcc && ./configure && make

# Build the Google Test library

googletest:
	wget -P $(DEPENDENCIES_DIR) https://github.com/google/googletest/archive/release-1.7.0.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/release-1.7.0.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/release-1.7.0.tar.gz
	mv $(DEPENDENCIES_DIR)/googletest-release-1.7.0 $(DEPENDENCIES_DIR)/googletest
	cd $(GOOGLE_TEST_DIR)/make && export CC=$(CC) && export CXX=$(CXX) && make

# Install (and customize) the C++ lint script

lint:
	cd $(DEPENDENCIES_DIR) && git clone https://github.com/google/styleguide.git
	sed -i 's|filename.rfind|filename.find|g' $(LINT_DIR)/cpplint.py

# Install the coding style app

astyle:
	wget -P $(DEPENDENCIES_DIR) http://sourceforge.net/projects/astyle/files/astyle/astyle%202.04/astyle_2.04_linux.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/astyle_2.04_linux.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/astyle_2.04_linux.tar.gz
	cd $(DEPENDENCIES_DIR)/astyle/build/gcc && make

# Build doxygen documentation

doxygen:
	rm -rf $(BUILD_DOXYGEN_DIR)
	doxygen $(CONF_DIR)/Doxyfile

# Build a Debian package for Kaos

package:
	rm -rf $(BUILD_PACKAGE_DIR)
	mkdir -p $(BUILD_PACKAGE_DIR)
	cp -r $(PACKAGE_DIR) $(BUILD_PACKAGE_DIR)/$(PACKAGE_NAME)
	cp $(BUILD_APP_BIN_DIR)/kaos $(BUILD_PACKAGE_DIR)/$(PACKAGE_NAME)/usr/sbin
	cd $(BUILD_PACKAGE_DIR) && dpkg-deb --build $(PACKAGE_NAME)
	rm -rf $(BUILD_PACKAGE_DIR)/$(PACKAGE_NAME)

# Remove any build artifacts

clean:
	rm -rf $(BUILD_DIR)

# Build the main application, its associated tests, and its package

all:	clean kaos test package doxygen

# Identify the targets that are not files

.PHONY: all clean package doxygen astyle lint googletest protobuf openssl leveldb rocksdb boost dependencies-dir dependencies conform check cpp-check proto run-tests

# Build kaos application

$(BUILD_APP_BIN_DIR)/kaos: \
	$(BUILD_APP_OBJ_DIR)/AccessControl.o \
	$(BUILD_APP_OBJ_DIR)/ClearTextStream.o \
	$(BUILD_APP_OBJ_DIR)/Connection.o \
	$(BUILD_APP_OBJ_DIR)/Entry.pb.o \
	$(BUILD_APP_OBJ_DIR)/GlobalConfig.o \
	$(BUILD_APP_OBJ_DIR)/HeartbeatProvider.o \
	$(BUILD_APP_OBJ_DIR)/Hmac.o \
	$(BUILD_APP_OBJ_DIR)/KineticLog.o \
	$(BUILD_APP_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_APP_OBJ_DIR)/LevelDbObjectStore.o \
	$(BUILD_APP_OBJ_DIR)/MessageHandler.o \
	$(BUILD_APP_OBJ_DIR)/MessageTrace.o \
	$(BUILD_APP_OBJ_DIR)/RocksDbObjectStore.o \
	$(BUILD_APP_OBJ_DIR)/Server.o \
	$(BUILD_APP_OBJ_DIR)/ServerSettings.o \
	$(BUILD_APP_OBJ_DIR)/Settings.pb.o \
	$(BUILD_APP_OBJ_DIR)/SslControl.o \
	$(BUILD_APP_OBJ_DIR)/SslStream.o \
	$(BUILD_APP_OBJ_DIR)/TcpTransport.o
	@mkdir -p $(@D)
	$(CXX) $^ $(APP_LIBRARIES) -o $@

# Rule to build application source

$(BUILD_APP_OBJ_DIR)/%.o: $(APP_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_APP_FLAGS) $(APP_INCLUDES) -c $^ -o $@

# Rule to build test source

$(BUILD_TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_TEST_FLAGS) $(TEST_INCLUDES) -c $^ -o $@

$(BUILD_TEST_OBJ_DIR)/%.o: $(APP_SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_TEST_FLAGS) $(APP_INCLUDES) -c $^ -o $@

# Build the test code

$(BUILD_TEST_BIN_DIR)/kineticMessageFramingUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/KineticMessageFramingUnitTest.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/serverSettingsUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/GlobalConfig.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettingsUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettings.o \
	$(BUILD_TEST_OBJ_DIR)/Settings.pb.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/accessScopeUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessScopeUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/GlobalConfig.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/accessControlUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessControlUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/GlobalConfig.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/hmacUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/HmacUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/heartbeatProviderUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/GlobalConfig.o \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProvider.o \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProviderUnitTest.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@
