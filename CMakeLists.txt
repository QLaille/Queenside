PROJECT					(QUEENSIDE)
CMAKE_MINIMUM_REQUIRED	(VERSION 2.6)
SET (BINARY_NAME Queenside)

SET (BOOST_VERSION 1.67.0)

### BINARY FOLDER
SET	(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

### CONAN SETUP
INCLUDE (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

### SETUP CPP17
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

### PATH HANDLING
SET (ROOT src)
INCLUDE_DIRECTORIES(
	${ROOT}/Client
	${ROOT}/Protocol
	${ROOT}/Service
	${ROOT}/Singleton/Broadcast
	${ROOT}/Singleton/Coordinator
	${ROOT}/Utils
	${ROOT}/Utils/IDGenerator
)

FILE (GLOB SOURCES
	"${ROOT}/*.*pp"
	"${ROOT}/Client/*.*pp"
	"${ROOT}/Protocol/*.*pp"
	"${ROOT}/Service/*.*pp"
	"${ROOT}/Singleton/Broadcast/*.*pp"
	"${ROOT}/Singleton/Coordinator/*.*pp"
	"${ROOT}/Utils/*.*pp"
	"${ROOT}/Utils/IDGenerator/*.*pp"
)

### FLAGS FOR GPP
IF (UNIX AND NOT APPLE)
	SET	(UNIX_LIB -lboost_system -lboost_thread -lpthread)
ENDIF()

ADD_EXECUTABLE (${BINARY_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES	(${BINARY_NAME}
	${SERVER_FLAGS}
	${CONAN_LIBS}
	${UNIX_LIB}
)