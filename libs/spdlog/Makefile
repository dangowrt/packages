#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=spdlog
PKG_VERSION:=1.17.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/gabime/$(PKG_NAME)/tar.gz/v$(PKG_VERSION)?
PKG_HASH:=d8862955c6d74e5846b3f580b1605d2428b11d97a410d86e2fb13e857cd3a744

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_CPE_ID:=cpe:/a:spdlog_project:spdlog

PKG_BUILD_PARALLEL:=1
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/spdlog
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Fast C++ logging library
  URL:=https://github.com/gabime/spdlog
  DEPENDS:=+libstdcpp +libfmt
endef

define Package/spdlog/description
  Very fast, header-only/compiled, C++ logging library.
endef

CMAKE_OPTIONS += \
	-DSPDLOG_BUILD_SHARED=ON \
	-DSPDLOG_BUILD_EXAMPLE=OFF \
	-DSPDLOG_BUILD_TESTS=OFF \
	-DSPDLOG_BUILD_BENCH=OFF \
	-DSPDLOG_FMT_EXTERNAL=ON

define Package/spdlog/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libspdlog.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,spdlog))
