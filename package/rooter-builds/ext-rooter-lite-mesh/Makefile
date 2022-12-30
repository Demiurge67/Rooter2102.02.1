#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter-lite-mesh
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter-lite-mesh
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+luci +ext-rooter-basic \
		+luci-app-ddns +ddns-scripts \
		+luci-app-rootervpn +ext-wireguard \
		+bwmon +464xlat +webconsole \
		+ext-theme +luci-theme-argon +luci-theme-argondark +luci-theme-materialgray +ext-login \
		+ca-bundle +ca-certificates +libustream-wolfssl \
		+luci-app-ksmbd +usb-storage \
		+ext-p910nd +luci-app-sqm \
		+kmod-sched-cake +luci-app-nft-qos \
		+ext-command +luci-app-shadowsocks-libev +simple-obfs \
		+openvpn-easy-rsa +openvpn-openssl \
		+ext-extra +luci-app-wol +luci-app-guestwifi \
		+mesh-mesh +mesh-wpad +iperf3 +socat \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+nano +picocom +wget +kmod-mtd-rw \
		+qfirehose +luci-app-vpnbypass 
  TITLE:=ROOter support MESH w/o MWan3 for 16meg and larger routers
  PKGARCH:=all
endef

define Package/ext-rooter-lite-mesh/description
  Helper scripts to enable ROOter support MESH w/o MWan3 for 16meg and larger routers
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-rooter-lite-mesh))
