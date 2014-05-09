# Compiler configurations
CFLAGS := -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
CPPFLAGS := -std=c++11 -Wall -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-pointer-arith
LDFLAGS := -Wl,-rpath,. -Wl,-rpath,./lib -Wl,-rpath-link,.

CDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS
CPPDEFS := -DCUMULONIMBUS_EXPORTS -DGLEW_STATIC -D_CRT_SECURE_NO_WARNINGS

INCLUDE_DIR := -I./include -I$(TYPHOON_ROOT)/dependencies/gcc/include -I$(TYPHOON_ROOT)/dependencies/gcc/include/freetype2
LIBS_DIR := -L$(TYPHOON_ROOT)/dependencies/gcc/lib
 
LIBS := -lboost_locale -lfreetype -lGLEW -lphysfs -lpng -lz -ldl -lX11 -pthread


#Test conigurations
TEST_CPPFLAGS := -Wall -std=c++11
TEST_LDFLAGS := -Wl,-rpath,. -Wl,-rpath,./lib -Wl,-rpath-link,. -Wl,-rpath-link,$(TYPHOON_ROOT)/cumulonimbus/dist -Wl,-rpath,$(TYPHOON_ROOT)/cumulonimbus/dist

TEST_INCLUDE_DIR := -I./include -I$(TYPHOON_ROOT)/cumulonimbus/include
TEST_LIBS_DIR := -L$(TYPHOON_ROOT)/cumulonimbus/dist
 
TEST_LIBS := -lcumulonimbus

