#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/proc_fs.h>
#include<linux/string.h>
#include<asm/uaccess.h>
#include<linux/kernel.h>

static int proc_read(char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data) {
	char *str = "Hi, this is Mr kernel!\n";	
	int len = strlen(str);
	strcpy(buffer, str);
	*eof = 1;
	return len;
}

static int __init procout_init(void) {
	struct proc_dir_entry *proc_entry = 0;
	proc_entry = create_proc_entry("Task1", 0744, NULL);
	proc_entry->read_proc = proc_read;
	proc_entry->size = 100;
	return 0;
}
static void __exit procout_exit(void) {
	remove_proc_entry("Task1", NULL);
	printk("Goodbye\n");
}
module_init(procout_init);
module_exit(procout_exit);
MODULE_LICENSE("GPL");
