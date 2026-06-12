#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rapidjson
PKG_VERSION:=1.1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/Tencent/$(PKG_NAME)/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=bf7ced29704a1e696fbccf2a2b4ea068e7774fa37f6d7dd4039d0787f8bed98e

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=license.txt
PKG_CPE_ID:=cpe:/a:tencent:rapidjson

CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/rapidjson
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Fast JSON parser/generator for C++ (header-only)
  URL:=https://rapidjson.org/
  BUILDONLY:=1
endef

define Package/rapidjson/description
  A fast JSON parser/generator for C++ with both SAX/DOM style API.
  This package only provides headers to build other packages against.
endef

CMAKE_OPTIONS += \
	-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
	-DRAPIDJSON_BUILD_DOC=OFF \
	-DRAPIDJSON_BUILD_EXAMPLES=OFF \
	-DRAPIDJSON_BUILD_TESTS=OFF

define Build/InstallDev
	$(call Build/InstallDev/cmake,$(1))
	$(SED) 's,set(RAPIDJSON_INCLUDE_DIRS .*,set(RAPIDJSON_INCLUDE_DIRS "$$$${RAPIDJSON_CMAKE_DIR}/../../../include"),' \
		$(1)/usr/lib/cmake/RapidJSON/RapidJSONConfig.cmake
	$(SED) 's,/usr/include,$$$${prefix}/include,g' $(1)/usr/lib/pkgconfig/RapidJSON.pc
endef

$(eval $(call BuildPackage,rapidjson))
