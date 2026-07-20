#
# Copyright (C) 2026 Mirko Vogt
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=python-scikit-build-core
PKG_VERSION:=1.0.3
PKG_RELEASE:=1

PYPI_NAME:=scikit_build_core
PKG_HASH:=a4d7a05978ee37975c37743510c8991e2debce7ef83afb0a07c0c576fd4f16e8

PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Mirko Vogt <mirko-openwrt@nanl.de>

PKG_HOST_ONLY:=1
HOST_BUILD_DEPENDS:= \
	python3/host \
	python-build/host \
	python-installer/host \
	python-hatchling/host \
	python-hatch-vcs/host \
	python-packaging/host \
	python-pathspec/host

include ../pypi.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include ../python3-package.mk
include ../python3-host-build.mk

define Package/python3-scikit-build-core
  SECTION:=lang
  CATEGORY:=Languages
  SUBMENU:=Python
  TITLE:=CMake build backend for Python packages
  URL:=https://github.com/scikit-build/scikit-build-core
  DEPENDS:= \
      +python3-light \
      +python3-packaging \
      +python3-pathspec
  BUILDONLY:=1
endef

define Package/python3-scikit-build-core/description
This is a next-generation, PEP 517 build backend for creating Python
packages whose extensions are built with CMake, without a dependency on
setuptools.
endef

$(eval $(call Py3Package,python3-scikit-build-core))
$(eval $(call BuildPackage,python3-scikit-build-core))
$(eval $(call BuildPackage,python3-scikit-build-core-src))
$(eval $(call HostBuild))
