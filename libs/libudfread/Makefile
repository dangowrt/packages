#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libudfread
PKG_VERSION:=1.2.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://download.videolan.org/pub/videolan/libudfread/
PKG_HASH:=bb477cbd4cfbfc7787d9d05b71ee5e70430f5cfebf1297497f7e83547958050f

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=LGPL-2.1-or-later
PKG_LICENSE_FILES:=COPYING

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/libudfread
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=UDF reader library
  URL:=https://code.videolan.org/videolan/libudfread
endef

define Package/libudfread/description
  libudfread is a library to read UDF filesystems, such as those
  found in Blu-ray and DVD images.
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/udfread $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libudfread.{a,so*} $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libudfread.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libudfread/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libudfread.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libudfread))
