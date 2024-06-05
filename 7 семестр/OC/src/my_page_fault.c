#include <linux/proc_fs.h>
#include <linux/kprobes.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");

#define PROC_ENTRY_NAME "my_page_fault"

#define KB 1024

#define COMM_LEN 20

struct Process
{
    long pid;
    char *comm;
    long vma;
    long rss;
    long page_fault_counter;
    struct Process *next;
};

struct Process *head = NULL;

struct Process *find_process_by_id(struct Process *head, long pid){
    struct Process *cur = head;

    while (cur != NULL)
    {
        if (cur->pid == pid)
            break;

        cur = cur->next;
    }

    return cur;
}

struct Process *create_process(struct Process **head, struct Process *new_process) {
    new_process = vmalloc(sizeof(struct Process));
    new_process->comm = vmalloc(COMM_LEN);
    new_process->next = NULL;
    
    if (*head == NULL) {
        *head = new_process;
        (*head)->next = NULL;
    }
    else {
        new_process->next = *head;
        *head = new_process;
    }
    
    return new_process;
}

long count_vma(struct task_struct *task) {
    long virt_mem = 0;
    struct vm_area_struct *vma;
    
    VMA_ITERATOR(iter, task->mm, 0);
    
    for_each_vma(iter, vma)
        virt_mem += vma->vm_end - vma->vm_start;

    return virt_mem / KB;
}

long count_rss(struct task_struct *task){
    return get_mm_rss(task->mm) * PAGE_SIZE / KB;
}

void handler(struct kprobe *p, struct pt_regs *regs, unsigned long flags) {
    struct Process *process = find_process_by_id(head, current->pid);
    
    if (process == NULL) {
        process = create_process(&head, process);
        process->pid = current->pid;
        strncpy(process->comm, current->comm, COMM_LEN);
        process->page_fault_counter = 0;
    }
	
    process->vma = count_vma(current);
    process->rss = count_rss(current);
    process->page_fault_counter++;
    
    //printk(KERN_INFO "PID: %ld, Comm: %s, VMA/KB: %ld, RSS/KB: %ld, Page Faults: %ld\n", 
    	//process->pid, process->comm, 
    	//process->vma, process->rss, 
    	//process->page_fault_counter);
}

char *create_buffer(char *output_buffer)
{
    char *tmp = vmalloc(KB), *separator = vmalloc(COMM_LEN);
    
    memset(tmp, 0, KB);
    memset(output_buffer, 0, KB);

    sprintf(output_buffer, "PID\tCOMM\t\t    VMA/KB\tRSS/KB\tPF\n");
    
    struct Process *cur = head;
    
    while (cur != NULL)
    {
    	memset(separator, 0, COMM_LEN);
    	memset(separator, ' ', COMM_LEN - strlen(cur->comm));
    	
        sprintf(tmp, "%ld\t%s%s%ld\t%ld\t%ld\t\n",
                cur->pid,
                cur->comm,
                separator,
                cur->vma,
                cur->rss,
                cur->page_fault_counter);

        strcat(output_buffer, tmp);
        
        cur = cur->next;
    }
    
    vfree(tmp);
    vfree(separator);
    
    return output_buffer;
}

static ssize_t reader(struct file *file, char __user *buffer, size_t count, loff_t *offset)
{

	char *output_buffer = vmalloc(KB);
	output_buffer = create_buffer(output_buffer); 

    ssize_t len = strlen(output_buffer);
    if (*offset >= len)
        return 0;
    
    if (*offset + count > len)
        count = len - *offset;
    
    if (copy_to_user(buffer, output_buffer + *offset, count) != 0)
        return -EFAULT;
    
    *offset += count;
    
    vfree(output_buffer);
    
    return count;
}

static const struct proc_ops proc_fops = {
	.proc_read = reader,
};

static struct kprobe kp = {
    .symbol_name = "__handle_mm_fault",
    .post_handler = handler,
};

static int __init init_page_fault(void) {
    proc_create(PROC_ENTRY_NAME, 0, NULL, &proc_fops);
    register_kprobe(&kp);
    
    printk(KERN_INFO "Module initialized\n");
    return 0;
}

void free_processes(struct Process *head)
{
    struct Process *cur = head;
    
    while (cur != NULL)
    {
        vfree(cur->comm);
        vfree(cur);
        cur = cur->next;
    }
}


static void __exit exit_page_fault(void) {
    free_processes(head);
    unregister_kprobe(&kp);
    remove_proc_entry(PROC_ENTRY_NAME, NULL);
    printk(KERN_INFO "Module exited\n");
}

module_init(init_page_fault);
module_exit(exit_page_fault);
