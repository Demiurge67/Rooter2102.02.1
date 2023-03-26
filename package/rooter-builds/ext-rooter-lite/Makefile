#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter-lite
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter-lite
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+luci +ext-rooter-basic \
		+luci-app-ddns +ddns-scripts +pingtest \
		+luci-app-openvpn +luci-app-wireguard +luci-app-vpnbypass \
		+bwmon +464xlat +webconsole \
		+ext-theme +luci-theme-materialgrey +ext-login \
		+ca-bundle +ca-certificates +libustream-wolfssl \
		+luci-app-ksmbd +usb-storage +ext-p910nd \
		+luci-app-sqm +kmod-sched-cake +luci-app-nft-qos \
		+ext-command +openvpn-easy-rsa +openvpn-openssl \
		+ext-extra +luci-app-wol +luci-app-shadowsocks-libev +simple-obfs \
		+iperf3 +socat \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+qlog +luci-ssl +usbutils +openssl-util +irqbalance +ext-splashconfig \
		+nano +picocom +wpad-openssl +wget +qfirehose +kmod-mtd-rw +ext-simplegps
  TITLE:=ROOter for 16+Meg routers  w/o MESH MWan3 
  PKGARCH:=all
endef

define Package/ext-rooter-lite/description
  Helper scripts to enable ROOter for 16+Meg routers w/o MESH MWan3
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-rooter-lite))
