# Makefile for both OpenWRT and Ubuntu

PKG_NAME := traceroute
PKG_VERSION := 1.0
PKG_RELEASE := 1

SRC_DIR := src
INC_DIR := src
BUILD_DIR := build
TARGET := traceroute

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(wildcard $(INC_DIR)/*.h)

# Detect OpenWRT environment
ifeq ($(strip $(TOPDIR)),)
  # Ubuntu build
  CC := gcc
  CFLAGS := -Wall -g -I$(INC_DIR) -D_DEFAULT_SOURCE
  LDFLAGS :=
else
  # OpenWRT build
  include $(TOPDIR)/rules.mk
  include $(INCLUDE_DIR)/package.mk
  CC := $(TARGET_CC)
  CFLAGS := $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(INC_DIR)
  LDFLAGS := $(TARGET_LDFLAGS)
endif

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

ifeq ($(strip $(TOPDIR)),)
  # Ubuntu build
  clean:
	rm -rf $(BUILD_DIR) $(TARGET)
else
  # OpenWRT build
  define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
	$(CP) ./Makefile $(PKG_BUILD_DIR)/
  endef

  define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I$(INC_DIR)" \
		LDFLAGS="$(TARGET_LDFLAGS)"
  endef

  define Build/Install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(TARGET) $(1)/usr/bin/
  endef

  $(eval $(call BuildPackage,$(PKG_NAME)))

  package:
	$(MAKE) package/$(PKG_NAME)/compile
endif

.PHONY: all clean package
