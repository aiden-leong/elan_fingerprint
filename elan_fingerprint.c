#include <linux/module.h>     /* Needed by all modules */
#include <linux/kernel.h>     /* Needed for KERN_INFO */
#include <linux/init.h>       /* Needed for the macros */

static int __init elan_fingerprint_start(void)
{
    printk(KERN_INFO "Loading Elan Fingerprint Driver...\n");
    return 0;
}

static void __exit elan_fingerprint_end(void)
{
    printk(KERN_INFO "Elan Fingerprint Driver Exit\n");
}

module_init(elan_fingerprint_start);
module_exit(elan_fingerprint_end);

MODULE_DESCRIPTION("Linux Driver for Elan Fingerprint Devices");
MODULE_VERSION("0.1");
MODULE_AUTHOR("Aiden Leong");
MODULE_LICENSE("GPL");
