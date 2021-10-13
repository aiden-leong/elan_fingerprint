#include <linux/module.h>     /* Needed by all modules */
#include <linux/kernel.h>     /* Needed for KERN_INFO */
#include <linux/usb.h>

static struct usb_device *elan_fp_device;

static struct usb_device_id elan_fp_table[] = {
        {
                USB_DEVICE(0x04F3, 0x0C28)
        },
        {} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, elan_fp_table);

static int elan_fp_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    pr_info("Elan drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);

    iface_desc = interface->cur_altsetting;
    printk(KERN_INFO "Pen i/f %d now probed: (%04X:%04X)\n",
            iface_desc->desc.bInterfaceNumber,
            id->idVendor, id->idProduct);
    printk(KERN_INFO "ID->bNumEndpoints: %02X\n",
            iface_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
            iface_desc->desc.bInterfaceClass);

    for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
    {
        endpoint = &iface_desc->endpoint[i].desc;

        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, endpoint->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize,
                endpoint->wMaxPacketSize);
    }

    elan_fp_device = interface_to_usbdev(interface);
    return 0;
}

static void elan_fp_disconnect(struct usb_interface *interface)
{
    pr_info("Elan drive removed\n");
}

static struct usb_driver elan_fp_driver =
        {
                .name = "elan_fingerprint",
                .id_table = elan_fp_table,
                .probe = elan_fp_probe,
                .disconnect = elan_fp_disconnect,
        };


static int __init elan_fingerprint_start(void)
{
    return usb_register(&elan_fp_driver);
}

static void __exit elan_fingerprint_end(void)
{
    usb_deregister(&elan_fp_driver);
}

module_init(elan_fingerprint_start);
module_exit(elan_fingerprint_end);

MODULE_DESCRIPTION("Linux Driver for Elan Fingerprint Devices");
MODULE_VERSION("0.1");
MODULE_AUTHOR("Aiden Leong");
MODULE_LICENSE("GPL");

