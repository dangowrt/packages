#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=exiv2
PKG_VERSION:=0.28.8
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Exiv2/$(PKG_NAME)/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=ea51b0609f58a9afa063b60daa1539948b62247721e154f4fff0ad3aec9f9756

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=GPL-2.0-or-later
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:exiv2:exiv2

PKG_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libexiv2
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Image metadata library
  URL:=https://exiv2.org/
  DEPENDS:=+libstdcpp +libexpat +zlib $(ICONV_DEPENDS)
endef

define Package/libexiv2/description
  Exiv2 is a C++ library and a command-line utility to read, write,
  delete and modify Exif, IPTC, XMP and ICC image metadata.
endef

CMAKE_OPTIONS += \
	-DEXIV2_BUILD_SAMPLES=OFF \
	-DEXIV2_BUILD_EXIV2_COMMAND=OFF \
	-DEXIV2_BUILD_UNIT_TESTS=OFF \
	-DEXIV2_BUILD_FUZZ_TESTS=OFF \
	-DEXIV2_BUILD_DOC=OFF \
	-DEXIV2_ENABLE_XMP=ON \
	-DEXIV2_ENABLE_PNG=ON \
	-DEXIV2_ENABLE_BMFF=ON \
	-DEXIV2_ENABLE_BROTLI=OFF \
	-DEXIV2_ENABLE_INIH=OFF \
	-DEXIV2_ENABLE_CURL=OFF \
	-DEXIV2_ENABLE_VIDEO=OFF \
	-DEXIV2_ENABLE_NLS=OFF

define Package/libexiv2/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libexiv2.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libexiv2))
