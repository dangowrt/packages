#
# Copyright (C) 2025 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lcms2
PKG_VERSION:=2.18
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/mm2/Little-CMS/releases/download/lcms$(PKG_VERSION)/
PKG_HASH:=ee67be3566f459362c1ee094fde2c159d33fa0390aa4ed5f5af676f9e5004347

PKG_MAINTAINER:=
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:littlecms:little_cms_color_engine

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/liblcms2
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Little CMS color management library
  URL:=https://www.littlecms.com/
  DEPENDS:=+libjpeg +libtiff
endef

define Package/liblcms2/description
  Little CMS (lcms2) is a small-footprint color management engine, with
  special focus on accuracy and performance. It uses the International Color
  Consortium standard (ICC) to perform color management.
endef

CONFIGURE_ARGS += \
	--disable-static \
	--without-zlib

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/lcms2*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/liblcms2.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/lcms2.pc $(1)/usr/lib/pkgconfig/
endef

define Package/liblcms2/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/liblcms2.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,liblcms2))
