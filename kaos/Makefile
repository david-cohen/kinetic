# Common directories

BASE_DIR	= $(shell pwd)
BUILD_DIR	= build
BUILD_BIN_DIR	= $(BUILD_DIR)/bin
BUILD_TEST_DIR	= $(BUILD_DIR)/test
BUILD_PROTO_DIR	= $(BUILD_DIR)/proto
BUILD_TEST_OBJ_DIR = $(BUILD_DIR)/test_obj

SRC_DIR		= $(BASE_DIR)/src
INCLUDE_DIR     = $(BASE_DIR)/include
PROTO_DIR	= $(BASE_DIR)/proto
TEST_SRC_DIR    = $(BASE_DIR)/test


ifdef CROSS_COMPILE
$(info **** Cross Compiling for ${ARCH} ****)
TOOLCHAIN_LIB_DIR = /home/shaun/work/Marvel/A370/armv7-marvell-linux-gnueabi-hard_i686_64K_Dev_20131002/arm-marvell-linux-gnueabi/libc/lib
LEVELDB_DIR  	  = /home/shaun/work/Marvel/leveldb-1.15.0
LEVELDB_LIBRARY   = $(LEVELDB_DIR)/libleveldb.a
PROTOBUF_DIR 	  = /home/shaun/work/Marvel/protobuf-2.5.0
PROTOBUF_LIBRARY  = $(PROTOBUF_DIR)/src/.libs/libprotobuf.a
GTEST_DIR    	  = /home/shaun/work/Marvel/gtest-1.6.0
GTEST_LIBRARY     = $(GTEST_DIR)/make/gtest_main.a
SSL_DIR  	  = /usr
SSL_LIB_DIR  	  = /home/shaun/work/Marvel/usr/lib/x86_64-linux-gnu
SSL_LIBRARIES     = $(SSL_LIB_DIR)/libssl.a

else
# Local Build
$(info **** Local Build ****)
TOOLCHAIN_LIB_DIR = /usr/lib/x86_64-linux-gnu
BOOST_DIR         = $(BASE_DIR)/../3rdParty/boost
LINT_DIR          = $(BASE_DIR)/tools
LEVELDB_DIR    	  = $(BASE_DIR)/../3rdParty/leveldb
LEVELDB_LIBRARY   = $(LEVELDB_DIR)/libleveldb.a
PROTOBUF_DIR   	  = $(BASE_DIR)/../3rdParty/protobuf
PROTOBUF_LIBRARY  = $(PROTOBUF_DIR)/src/.libs/libprotobuf.a
GTEST_DIR      	  = $(BASE_DIR)/../3rdParty/googletest
ASTYLE_DIR	  = $(BASE_DIR)/../3rdParty/astyle/build/gcc/bin
GTEST_LIBRARY     = $(GTEST_DIR)/make/gtest_main.a
SSL_DIR	       	  = /usr
SSL_LIB_DIR    	  = /usr/lib/x86_64-linux-gnu
SSL_LIBRARIES     = -L$(SSL_LIB_DIR) -lssl -lcrypto
CXX            	  = g++
endif

CXXFLAGS       	  = -std=c++0x -g -Wall -Wextra -DLOG_EVENT_LOCATION -DWORK_WITH_JAVA_SMOKE_TEST
INCLUDES       	  = -I$(BASE_DIR)/include -I$(LEVELDB_DIR)/include -I$(SSL_DIR)/include -I$(PROTOBUF_DIR)/src -I$(BOOST_DIR)
TEST_INCLUDES  	  = $(INCLUDES) -I$(GTEST_DIR)/include
LIBRARIES      	  = $(LEVELDB_LIBRARY) $(PROTOBUF_LIBRARY) $(SSL_LIBRARIES) -L$(TOOLCHAIN_LIB_DIR) -lrt -lpthread
TEST_LIBRARIES    = $(GTEST_LIBRARY) $(LIBRARIES)

# Build the Kinetic Advanced Object Storage

kaos: 	$(BUILD_BIN_DIR)/kaos

# Build the unit tests

test:	$(BUILD_TEST_DIR)/heartbeatProviderUnitTest \
	$(BUILD_TEST_DIR)/accessControlUnitTest \
	$(BUILD_TEST_DIR)/accessScopeUnitTest \
	$(BUILD_TEST_DIR)/hmacUnitTest \
	$(BUILD_TEST_DIR)/kineticMessageFramingUnitTest \
	$(BUILD_TEST_DIR)/serverSettingsUnitTest \
	$(BUILD_TEST_DIR)/translatorUnitTest \

# Run the unit tests

runTests:
	$(BUILD_TEST_DIR)/heartbeatProviderUnitTest
	$(BUILD_TEST_DIR)/accessControlUnitTest
	$(BUILD_TEST_DIR)/accessScopeUnitTest
	$(BUILD_TEST_DIR)/hmacUnitTest
	$(BUILD_TEST_DIR)/kineticMessageFramingUnitTest
	$(BUILD_TEST_DIR)/serverSettingsUnitTest
	$(BUILD_TEST_DIR)/translatorUnitTest

# Build source from the protocol buffer files (rename the .cc files to .cpp)

proto:
	[ -d $(BUILD_PROTO_DIR) ] || mkdir -p $(BUILD_PROTO_DIR)
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Kinetic.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Entry.proto
	$(PROTOBUF_DIR)/src/protoc -I=$(PROTO_DIR) --cpp_out=$(BASE_DIR)/$(BUILD_PROTO_DIR) $(PROTO_DIR)/Settings.proto
	$(BASE_DIR)/tools/cleanProtoFile.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Entry
	$(BASE_DIR)/tools/cleanProtoFile.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Kinetic
	$(BASE_DIR)/tools/cleanProtoFile.sh $(BASE_DIR)/$(BUILD_PROTO_DIR) Settings
	mv $(BASE_DIR)/$(BUILD_PROTO_DIR)/*.cpp $(SRC_DIR)/
	mv $(BASE_DIR)/$(BUILD_PROTO_DIR)/*.hpp $(INCLUDE_DIR)/

check:
	- $(LINT_DIR)/cpplint.py --extensions=hpp,cpp --linelength=200 --filter=-build/c++11,-runtime/references,-runtime/string,-readability/streams,-whitespace/blank_line,-whitespace/empty_loop_body $(INCLUDE_DIR)/*.hpp
	- $(LINT_DIR)/cpplint.py --extensions=hpp,cpp --linelength=250 --filter=-build/c++11,-runtime/references,-runtime/string,-readability/streams,-whitespace/blank_line,-whitespace/empty_loop_body $(SRC_DIR)/*.cpp
	- $(LINT_DIR)/cpplint.py --extensions=hpp,cpp --linelength=250 --filter=-build/c++11,-runtime/references,-runtime/string,-readability/streams,-whitespace/blank_line,-whitespace/empty_loop_body $(TEST_SRC_DIR)/*.cpp

conform:
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --remove-comment-prefix --indent-switches --keep-one-line-blocks --recursive "$(INCLUDE_DIR)/*.hpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --remove-comment-prefix --indent-switches --keep-one-line-blocks --recursive "$(TEST_SRC_DIR)/*.cpp"
	- $(ASTYLE_DIR)/astyle --suffix=none --lineend=linux --convert-tabs --indent=spaces=4 --style=java --break-closing-brackets --pad-oper --pad-header --unpad-paren --attach-classes --attach-namespaces --align-pointer=type --close-templates --remove-comment-prefix --indent-switches --keep-one-line-blocks --recursive "$(SRC_DIR)/*.cpp"


# Remove any build artifacts

clean:
	rm -Rf $(BUILD_DIR)


all:	clean kaos test

# Identify the targets that are not files

.PHONY: clean proto runTests beautify all

# Build application

$(BUILD_BIN_DIR)/kaos: \
	$(BUILD_DIR)/AccessControl.o \
	$(BUILD_DIR)/ClearTextStream.o \
	$(BUILD_DIR)/ConnectionHandler.o \
	$(BUILD_DIR)/Entry.pb.o \
	$(BUILD_DIR)/HeartbeatProvider.o \
	$(BUILD_DIR)/Hmac.o \
	$(BUILD_DIR)/KineticLog.o \
	$(BUILD_DIR)/Kinetic.pb.o \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/MessageHandler.o \
	$(BUILD_DIR)/MessageTrace.o \
	$(BUILD_DIR)/ObjectStore.o \
	$(BUILD_DIR)/ServerSettings.o \
	$(BUILD_DIR)/Settings.pb.o \
	$(BUILD_DIR)/SslControl.o \
	$(BUILD_DIR)/SslStream.o \
	$(BUILD_DIR)/SystemConfig.o \
	$(BUILD_DIR)/TcpTransport.o \
	$(BUILD_DIR)/TransportManager.o \
	$(BUILD_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(LIBRARIES) -o $@

# Rule to build application source

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

# Rule to build test source

$(BUILD_TEST_OBJ_DIR)/%.o: test/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -DUNIT_TEST $(TEST_INCLUDES) -c $^ -o $@

$(BUILD_TEST_OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -DUNIT_TEST $(INCLUDES) -c $^ -o $@

# Build the test code

$(BUILD_TEST_DIR)/kineticMessageFramingUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/KineticMessageFramingUnitTest.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/serverSettingsUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettingsUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/ServerSettings.o \
	$(BUILD_TEST_OBJ_DIR)/Settings.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o \
	$(BUILD_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/translatorUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/TranslatorUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Translator.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/accessScopeUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessScopeUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/accessControlUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/AccessControlUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/hmacUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/HmacUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/perfTest: \
	$(BUILD_TEST_OBJ_DIR)/AccessControl.o \
	$(BUILD_TEST_OBJ_DIR)/PerformanceTest.o \
	$(BUILD_TEST_OBJ_DIR)/ObjectStore.o \
	$(BUILD_TEST_OBJ_DIR)/Entry.pb.o \
	$(BUILD_TEST_OBJ_DIR)/Kinetic.pb.o \
	$(BUILD_TEST_OBJ_DIR)/MessageTrace.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o \
	$(BUILD_TEST_OBJ_DIR)/Hmac.o \
	$(BUILD_DIR)/Translator.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

$(BUILD_TEST_DIR)/heartbeatProviderUnitTest: \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProvider.o \
	$(BUILD_TEST_OBJ_DIR)/HeartbeatProviderUnitTest.o \
	$(BUILD_TEST_OBJ_DIR)/SystemConfig.o
	@mkdir -p $(@D)
	$(CXX) $^ $(TEST_LIBRARIES) -o $@

