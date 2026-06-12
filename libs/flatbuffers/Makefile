#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=flatbuffers
PKG_VERSION:=25.2.10
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/google/$(PKG_NAME)/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=b9c2df49707c57a48fc0923d52b8c73beb72d675f9d44b2211e4569be40a7421

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE
PKG_CPE_ID:=cpe:/a:google:flatbuffers

PKG_BUILD_PARALLEL:=1
HOST_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libflatbuffers
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Memory efficient serialization library
  URL:=https://flatbuffers.dev/
  DEPENDS:=+libstdcpp
endef

define Package/libflatbuffers/description
  FlatBuffers is a cross platform serialization library architected
  for maximum memory efficiency. It allows accessing serialised data
  without parsing or unpacking, while still having great forwards and
  backwards compatibility.
  The host build provides the flatc schema compiler.
endef

CMAKE_OPTIONS += \
	-DFLATBUFFERS_BUILD_FLATC=OFF \
	-DFLATBUFFERS_BUILD_FLATHASH=OFF \
	-DFLATBUFFERS_BUILD_TESTS=OFF \
	-DFLATBUFFERS_BUILD_SHAREDLIB=ON

CMAKE_HOST_OPTIONS += \
	-DFLATBUFFERS_BUILD_FLATC=ON \
	-DFLATBUFFERS_BUILD_FLATHASH=OFF \
	-DFLATBUFFERS_BUILD_TESTS=OFF \
	-DFLATBUFFERS_BUILD_SHAREDLIB=OFF

define Package/libflatbuffers/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libflatbuffers.so.* $(1)/usr/lib/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libflatbuffers))
