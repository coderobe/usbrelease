# usbrelease

### Usage

```console
usbrelease <BUS> <DEVICE>
```

__`<BUS>`__

> _Required_.  USB bus ID on which devices are released.

__`<DEVICE>`__

> _Required_.  Specific device ID to release.

### Example

Releases all interfaces of device 15 on bus 3.

```console
# usbrelease 003 015
```

