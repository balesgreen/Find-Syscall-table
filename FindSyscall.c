#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "kallsyms_lookup_name"
};

int __init init_test(void) {
	register_kprobe(&kp);

	pr_alert("Found at 0x%px \n", kp.addr);

	return 0;
}

void __exit cleanup_test(void) {
	unregister_kprobe(&kp);
}

MODULE_LICENSE("GPL");

module_init(init_test);
module_exit(cleanup_test);
