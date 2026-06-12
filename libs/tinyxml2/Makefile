#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=tinyxml2
PKG_VERSION:=11.0.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/leethomason/$(PKG_NAME)/tar.gz/$(PKG_VERSION)?
PKG_HASH:=5556deb5081fb246ee92afae73efd943c889cef0cafea92b0b82422d6a18f289

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=Zlib
PKG_LICENSE_FILES:=LICENSE.txt
PKG_CPE_ID:=cpe:/a:tinyxml2_project:tinyxml2

PKG_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libtinyxml2
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Simple, small, efficient C++ XML parser
  URL:=https://github.com/leethomason/tinyxml2
  DEPENDS:=+libstdcpp
endef

define Package/libtinyxml2/description
  TinyXML-2 is a simple, small, efficient C++ XML parser that can be
  easily integrated into other programs.
endef

CMAKE_OPTIONS += \
	-DBUILD_SHARED_LIBS=ON \
	-Dtinyxml2_BUILD_TESTING=OFF

define Package/libtinyxml2/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libtinyxml2.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libtinyxml2))
