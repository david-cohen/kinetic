# Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.

BASE_DIR	:= $(shell pwd)
TIMESTAMP   := $(shell date)
SOURCE_HASH := $(shell ./tools/create-source-hash.sh)

# Cross Compile for ARM and native compile for everything else

ifdef (ARM_CROSS_COMPILER)
COMPILER_PREFIX 	= arm-marvell-linux-gnueabi-
TOOLCHAIN_BIN_DIR   = $(BASE_DIR)/a370-tool-chain/bin
TOOLCHAIN_LIB_DIR   = $(BASE_DIR)/a370-tool-chain/arm-marvell-linux-gnueabi/libc/lib
else
COMPILER_PREFIX 	=
TOOLCHAIN_BIN_DIR   = /usr/bin
TOOLCHAIN_LIB_DIR   = /usr/lib/x86_64-linux-gnu
endif

# Build Input Directories

APP_SRC_DIR 	= $(BASE_DIR)/src
INCLUDE_DIR 	= $(BASE_DIR)/include
PROTO_DIR   	= $(BASE_DIR)/proto
TEST_SRC_DIR	= $(BASE_DIR)/test

# Build Output Directories

BUILD_DIR   		= $(BASE_DIR)/build
BUILD_APP_BIN_DIR   = $(BUILD_DIR)/bin/app
BUILD_APP_OBJ_DIR   = $(BUILD_DIR)/obj/app
BUILD_PROTO_DIR 	= $(BUILD_DIR)/proto
BUILD_TEST_BIN_DIR  = $(BUILD_DIR)/bin/test
BUILD_TEST_OBJ_DIR  = $(BUILD_DIR)/obj/test

# Dependencies Library Directories

DEPENDENCIES_DIR	= $(BASE_DIR)/dependencies
ASTYLE_DIR  		= $(DEPENDENCIES_DIR)/astyle/build/gcc/bin
BOOST_DIR   		= $(DEPENDENCIES_DIR)/boost
GOOGLE_TEST_DIR 	= $(DEPENDENCIES_DIR)/googletest
LEVELDB_DIR 		= $(DEPENDENCIES_DIR)/leveldb
LINT_DIR			= $(DEPENDENCIES_DIR)/styleguide/cpplint
PROTOBUF_DIR		= $(DEPENDENCIES_DIR)/protobuf
OPENSSL_DIR 		= $(DEPENDENCIES_DIR)/openssl
CONFIG_DIR  		= /etc/kaos

# Dependencies Libraries

GTEST_LIBRARY   	= $(GOOGLE_TEST_DIR)/make/gtest_main.a
LEVELDB_LIBRARY 	= $(LEVELDB_DIR)/libleveldb.a
PROTOBUF_LIBRARY	= $(PROTOBUF_DIR)/src/.libs/libprotobuf.a
OPENSSL_LIBRARIES   = $(OPENSSL_DIR)/libssl.a $(OPENSSL_DIR)/libcrypto.a

# Compiler/Linker Parameters

CC  			= $(COMPILER_PREFIX)gcc
CXX 			= $(COMPILER_PREFIX)g++
CXX_APP_FLAGS   = -std=c++0x -g -Wall -Wextra -DLOG_EVENT_LOCATION -DWORK_WITH_JAVA_SMOKE_TEST -DTIMESTAMP="\"$(TIMESTAMP)\"" -DSOURCE_HASH="\"$(SOURCE_HASH)\"" 
CXX_TEST_FLAGS  = $(CXX_APP_FLAGS) -DUNIT_TEST -DTIMESTAMP="\"$(TIMESTAMP)\""
APP_INCLUDES	= -I$(BASE_DIR)/include -I$(BOOST_DIR) -I$(LEVELDB_DIR)/include -I$(PROTOBUF_DIR)/src -I$(OPENSSL_DIR)/include
APP_LIBRARIES   = $(LEVELDB_LIBRARY) $(PROTOBUF_LIBRARY) $(OPENSSL_LIBRARIES) -L$(TOOLCHAIN_LIB_DIR) -lrt -lpthread
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
	$(BUILD_TEST_BIN_DIR)/serverSettingsUnitTest \
	$(BUILD_TEST_BIN_DIR)/translatorUnitTest

# Run the unit tests

run-tests:
	$(BUILD_TEST_BIN_DIR)/accessControlUnitTest
	$(BUILD_TEST_BIN_DIR)/accessScopeUnitTest
	$(BUILD_TEST_BIN_DIR)/heartbeatProviderUnitTest
	$(BUILD_TEST_BIN_DIR)/hmacUnitTest
	$(BUILD_TEST_BIN_DIR)/kineticMessageFramingUnitTest
	$(BUILD_TEST_BIN_DIR)/serverSettingsUnitTest
	$(BUILD_TEST_BIN_DIR)/translatorUnitTest

# Build source from the protocol buffer files (rename the .cc files to .cpp)

proto:
	[ -d $(BUILD_PROTO_DIR) ] || mkdir -p $(BUILD_PROTO_DIR)
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Kinetic.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Entry.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Settings.proto
	$(BASE_DIR)/tools/clean-proto-file.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Entry
	$(BASE_DIR)/tools/clean-proto-file.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Kinetic
	$(BASE_DIR)/tools/clean-proto-file.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Settings
	mv $(BASE_DIR)/$(BUILD_PROTO_DIR)/*.cpp $(APP_SRC_DIR)/
	mv $(BASE_DIR)/$(BUILD_PROTO_DIR)/*.hpp $(INCLUDE_DIR)/

# Check for suspicious coding

check:
	- $(LINT_DIR)/cpplint.py --extensions=hpp --linelength=200 --filter=-build/c++11,-runtime/references,-runtime/string $(INCLUDE_DIR)/*.hpp
	- $(LINT_DIR)/cpplint.py --extensions=cpp --linelength=250 --filter=-build/c++11,-runtime/references,-runtime/string $(APP_SRC_DIR)/*.cpp
	- $(LINT_DIR)/cpplint.py --extensions=cpp --linelength=250 --filter=-build/c++11,-runtime/references,-runtime/string $(TEST_SRC_DIR)/*.cpp

cpp-check:
	- cppcheck $(APP_SRC_DIR) --enable=all --force --includes-file=$(APP_INCLUDES)
	- cppcheck $(TEST_SRC_DIR) --enable=all --force --includes-file=$(APP_INCLUDES)

# Made the code follow a consistent coding style

conform:
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks	--recursive	"$(INCLUDE_DIR)/*.hpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks	--recursive	"$(TEST_SRC_DIR)/*.cpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --indent-switches	--keep-one-line-blocks	--recursive	"$(APP_SRC_DIR)/*.cpp"

# Install the tool chain for the Marvel ARM A370

cross-compiler:
	wget -P $(BASE_DIR) http://wdscnasbuild01.wdc.com:8081/nexus/service/local/repositories/cross-compiler/content/arm/armv7-marvell-linux-gnueabi/4.6.4/armv7-marvell-linux-gnueabi-4.6.4-hard_i686_64K_Dev_20131002.tbz2
	tar -xvjf $(BASE_DIR)/armv7-marvell-linux-gnueabi-4.6.4-hard_i686_64K_Dev_20131002.tbz2 -C $(BASE_DIR)
	rm $(BASE_DIR)/armv7-marvell-linux-gnueabi-4.6.4-hard_i686_64K_Dev_20131002.tbz2
	mv $(BASE_DIR)/armv7-marvell-linux-gnueabi-hard_i686_64K_Dev_20131002 $(BASE_DIR)/a370-tool-chain
	echo "export PATH=\$$PATH:$(BASE_DIR)/a370-tool-chain/bin" >> ~/.bashrc

install-cert:
	sudo mkdir $(CONFIG_DIR)
	sudo chmod 777 $(CONFIG_DIR)
	sudo cp cert/cert.pem $(CONFIG_DIR)

# Build the required dependencies

dependencies: dependencies-dir boost leveldb openssl protobuf googletest lint astyle install-cert

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

# Build the level DB library

leveldb:
	wget -P $(DEPENDENCIES_DIR) https://github.com/google/leveldb/archive/v1.18.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/v1.18.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/v1.18.tar.gz
	mv $(DEPENDENCIES_DIR)/leveldb-1.18 $(DEPENDENCIES_DIR)/leveldb
	export CC=$(CC) && export CXX=$(CXX) && cd $(LEVELDB_DIR) && \
	./build_detect_platform config $(LEVELDB_DIR) && make

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
	if [ "$(ARM_CROSS_COMPILER)" = "true" ]; then cd $(PROTOBUF_DIR); sudo make install; fi
	if [ "$(ARM_CROSS_COMPILER)" = "true" ]; then sudo cp $(PROTOBUF_DIR)/src/.libs/protoc /usr/bin; fi
	if [ "$(ARM_CROSS_COMPILER)" = "true" ]; then cd $(PROTOBUF_DIR); make distclean; fi
	if [ "$(ARM_CROSS_COMPILER)" = "true" ]; then cd $(PROTOBUF_DIR); ./configure --host=arm-linux CC=$(CC) CXX=$(CXX) --with-protoc=/usr/bin/protoc; fi
	if [ "$(ARM_CROSS_COMPILER)" = "true" ]; then cd $(PROTOBUF_DIR); export LD_LIBRARY_PATH=/usr/local/lib; make; fi

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
	sed -i '2494,2498d' $(LINT_DIR)/cpplint.py
	sed -i '3928,3933d' $(LINT_DIR)/cpplint.py
	sed -i '3911,3917d' $(LINT_DIR)/cpplint.py
	sed -i '3093,3097d' $(LINT_DIR)/cpplint.py
	sed -i '3072,3075d' $(LINT_DIR)/cpplint.py
	sed -i '3848,3850d' $(LINT_DIR)/cpplint.py
	sed -i '4143,4145d' $(LINT_DIR)/cpplint.py
	sed -i '6151,6152d' $(LINT_DIR)/cpplint.py
	sed -i '6151i \ \ \ \ pass' $(LINT_DIR)/cpplint.py
	sed -i '5297,5302d' $(LINT_DIR)/cpplint.py

astyle:
	wget -P $(DEPENDENCIES_DIR) http://sourceforge.net/projects/astyle/files/astyle/astyle%202.04/astyle_2.04_linux.tar.gz
	tar -zxf $(DEPENDENCIES_DIR)/astyle_2.04_linux.tar.gz -C $(DEPENDENCIES_DIR)
	rm $(DEPENDENCIES_DIR)/astyle_2.04_linux.tar.gz
	cd $(DEPENDENCIES_DIR)/astyle/build/gcc && make

# Remove any build artifacts

clean:
	rm -rf $(BUILD_DIR)

# Build main application and associated tests

all:	clean kaos test

# Identify the targets that are not files

.PHONY: all clean astyle lint googletest protobuf openssl leveldb boost dependencies-dir dependencies cross-compiler conform check cpp-check proto run-tests install-cert

# Build kaos application

$(BUILD_APP_BIN_DIR)/kaos: \
	$(BUILD_APP_OBJ_DIR)/AccessControl.o \
	$(BUILD_APP_OBJ_DIR)/ClearTextStream.o \
	$(BUILD_APP_OBJ_DIR)/CommunicationsManager.o \
	$(BUILD_APP_OBJ_DIR)/Connection.o \
	$(BUILD_APP_OBJ_DIR)/Entry.pb.o \
	$(BUILD_APP_OBJ_DIR)/HeartbeatProvider.o \
	$(BUILD_APP_OBJ_DIR)/Hmac.o \
	$(BUILD_APP_OBJ_DIR)/KineticLog.o \
	$(BUILD_APP_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_APP_OBJ_DIR)/Main.o \
	$(BUILD_APP_OBJ_DIR)/MessageHandler.o \
	$(BUILD_APP_OBJ_DIR)/MessageTrace.o \
	$(BUILD_APP_OBJ_DIR)/ObjectStore.o \
	$(BUILD_APP_OBJ_DIR)/ServerSettings.o \
	$(BUILD_APP_OBJ_DIR)/Settings.pb.o \
	$(BUILD_APP_OBJ_DIR)/SslControl.o \
	$(BUILD_APP_OBJ_DIR)/SslStream.o \
	$(BUILD_APP_OBJ_DIR)/SystemConfig.o \
	$(BUILD_APP_OBJ_DIR)/TcpTransport.o \
	$(BUILD_APP_OBJ_DIR)/Translator.o
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
	$(BUILD_TEST_OBJ_DIR)/ServerSettingsUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettings.o \
	$(BUILD_TEST_OBJ_DIR)/Settings.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o \
	$(BUILD_APP_OBJ_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/translatorUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/TranslatorUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Translator.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/accessScopeUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessScopeUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/accessControlUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessControlUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/hmacUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/HmacUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/perfTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/PerformanceTest.o \
	$(BUILD_TEST_OBJ_DIR)/ObjectStore.o \
	$(BUILD_TEST_OBJ_DIR)/Entry.pb.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/MessageTrace.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o \
	$(BUILD_APP_OBJ_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/objectStoreTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/ObjectStoreTest.o \
	$(BUILD_TEST_OBJ_DIR)/ObjectStore.o \
	$(BUILD_TEST_OBJ_DIR)/Entry.pb.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/MessageTrace.o \
	$(BUILD_TEST_OBJ_DIR)/Settings.pb.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettings.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o \
	$(BUILD_APP_OBJ_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_BIN_DIR)/heartbeatProviderUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProvider.o \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProviderUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@


