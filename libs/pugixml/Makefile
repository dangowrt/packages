#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pugixml
PKG_VERSION:=1.15
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/zeux/$(PKG_NAME)/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=b39647064d9e28297a34278bfb897092bf33b7c487906ddfc094c9e8868bddcb

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE.md
PKG_CPE_ID:=cpe:/a:pugixml_project:pugixml

PKG_BUILD_PARALLEL:=1
HOST_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libpugixml
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Light-weight C++ XML processing library
  URL:=https://pugixml.org/
  DEPENDS:=+libstdcpp
endef

define Package/libpugixml/description
  pugixml is a C++ XML processing library featuring a DOM-like
  interface with rich traversal and modification capabilities, an
  extremely fast XML parser and XPath 1.0 support.
endef

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

CMAKE_HOST_OPTIONS += -DBUILD_SHARED_LIBS=OFF

define Package/libpugixml/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpugixml.so.* $(1)/usr/lib/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libpugixml))
