include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=rooter
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

define Package/rooter
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Utility for testing root to host throught ICMP packets
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -I$(PKG_BUILD_DIR) -Wall -g \
		$(PKG_BUILD_DIR)/main.c \
		$(PKG_BUILD_DIR)/checksum.c \
		$(PKG_BUILD_DIR)/fqdn.c \
		$(PKG_BUILD_DIR)/networking.c \
		$(PKG_BUILD_DIR)/construct_packet.c \
		-o $(PKG_BUILD_DIR)/rooter
endef

define Package/rooter/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rooter $(1)/usr/bin/
endef

$(eval $(call BuildPackage,rooter))
