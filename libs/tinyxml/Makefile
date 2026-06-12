#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=tinyxml
PKG_VERSION:=2.6.2
PKG_RELEASE:=1

PKG_SOURCE:=tinyxml_2_6_2.tar.gz
PKG_SOURCE_URL:=@SF/tinyxml
PKG_HASH:=15bdfdcec58a7da30adc87ac2b078e4417dbe5392f3afb719f9ba6d062645593

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=Zlib
PKG_CPE_ID:=cpe:/a:tinyxml_project:tinyxml

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/libtinyxml
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Simple, small C++ XML parser
  URL:=https://sourceforge.net/projects/tinyxml/
  DEPENDS:=+libstdcpp
endef

define Package/libtinyxml/description
  TinyXML is a simple, small C++ XML parser that can be easily
  integrated into other programs. Built with STL support
  (TIXML_USE_STL).
endef

TINYXML_SOURCES:=tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.cpp

define Build/Compile
	cd $(PKG_BUILD_DIR) && $(TARGET_CXX) $(TARGET_CXXFLAGS) $(TARGET_CPPFLAGS) \
		-fPIC -shared -Wl,-soname,libtinyxml.so.0 \
		-o libtinyxml.so.0.$(PKG_VERSION) $(TINYXML_SOURCES) $(TARGET_LDFLAGS)
	$(LN) libtinyxml.so.0.$(PKG_VERSION) $(PKG_BUILD_DIR)/libtinyxml.so.0
	$(LN) libtinyxml.so.0 $(PKG_BUILD_DIR)/libtinyxml.so
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/tinyxml.h $(PKG_BUILD_DIR)/tinystr.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libtinyxml.so* $(1)/usr/lib/
endef

define Package/libtinyxml/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libtinyxml.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libtinyxml))
