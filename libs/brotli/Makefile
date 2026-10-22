#
# Copyright (C) 2024 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=brotli
PKG_VERSION:=1.1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/google/brotli/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=e720a6ca29428b803f4ad165371771f5398faba397edf6778837a18599ea13ff

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_CPE_ID:=cpe:/a:google:brotli

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/brotli/Default
  SECTION:=libs
  CATEGORY:=Libraries
  URL:=https://github.com/google/brotli
endef

define Package/libbrotlicommon
$(call Package/brotli/Default)
  TITLE:=Brotli common dictionary library
  ABI_VERSION:=1
endef

define Package/libbrotlicommon/description
  Brotli is a generic-purpose lossless compression algorithm. This package
  provides the dictionary library shared by the Brotli encoder and decoder.
endef

define Package/libbrotlidec
$(call Package/brotli/Default)
  TITLE:=Brotli decoder library
  ABI_VERSION:=1
  DEPENDS:=+libbrotlicommon
endef

define Package/libbrotlidec/description
  Brotli is a generic-purpose lossless compression algorithm. This package
  provides the Brotli decoder shared library.
endef

define Package/libbrotlienc
$(call Package/brotli/Default)
  TITLE:=Brotli encoder library
  ABI_VERSION:=1
  DEPENDS:=+libbrotlicommon
endef

define Package/libbrotlienc/description
  Brotli is a generic-purpose lossless compression algorithm. This package
  provides the Brotli encoder shared library.
endef

define Package/brotli
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Brotli compression utility
  URL:=https://github.com/google/brotli
  DEPENDS:=+libbrotlidec +libbrotlienc
endef

define Package/brotli/description
  Brotli is a generic-purpose lossless compression algorithm that compresses
  data using a combination of a modern variant of the LZ77 algorithm, Huffman
  coding and 2nd order context modelling. This package provides the brotli
  command line compression and decompression utility.
endef

CMAKE_OPTIONS += \
	-DBROTLI_DISABLE_TESTS=ON

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/brotli $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libbrotli*.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libbrotli*.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libbrotlicommon/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libbrotlicommon.so.* $(1)/usr/lib/
endef

define Package/libbrotlidec/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libbrotlidec.so.* $(1)/usr/lib/
endef

define Package/libbrotlienc/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libbrotlienc.so.* $(1)/usr/lib/
endef

define Package/brotli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/brotli $(1)/usr/bin/
endef

$(eval $(call BuildPackage,libbrotlicommon))
$(eval $(call BuildPackage,libbrotlidec))
$(eval $(call BuildPackage,libbrotlienc))
$(eval $(call BuildPackage,brotli))
