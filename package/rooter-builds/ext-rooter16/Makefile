#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter16
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter16
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+luci +ext-rooter-basic +ext-extra +luci-app-ddns +ddns-scripts +kmod-sched-cake \
		+luci-app-rootervpn +ext-wireguard +bwmon +464xlat +kmod-mtd-rw +luci-app-ksmbd \
		+ext-theme +ext-login +ca-bundle +ca-certificates +libustream-wolfssl \
		+usb-storage +ext-p910nd +luci-app-sqm \
		+luci-app-nft-qos +ext-command +luci-app-shadowsocks-libev +simple-obfs \
		+luci-app-wol +luci-app-hotspot +mesh-mesh +mesh-wpad +iperf3 \
		+webconsole +socat +usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+nano +picocom +wget +qfirehose +luci-app-vpnbypass 
 TITLE:=ROOter support for 16meg and larger routers
 PKGARCH:=all
endef

define Package/ext-rooter16/description
  Helper scripts to enable ROOter on 16+MB routers
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-rooter16))
