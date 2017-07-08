#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>

int main(int argc, char *argv[]){
        struct usbdevfs_ioctl command;
        if(argc > 2){
                char buffer[100];
                snprintf(buffer, 100, "/dev/bus/usb/%s/%s", argv[1], argv[2]);
                int fd = open(buffer, O_RDWR);
                if(fd < 1){
                        perror("unable to open file");
                        return 1;
                }
                for(int i = 0; i < 255; i++){ // Iterate over interfaces
                        command.ifno = i;
                        command.ioctl_code = USBDEVFS_DISCONNECT;
                        command.data = NULL;
                        int ret = ioctl(fd, USBDEVFS_IOCTL, &command); // Send disconnect ioctl event
                        if(ret != -1)
                                printf("releasing interface %d %d\n", i, ret);
                }
                return 0;
        }else{
                printf("usage: %s BUS DEVICE\n", argv[0]);
                printf("Release all interfaces of the USB DEVICE on BUS\n");
                printf("Example: %s 003 015\n", argv[0]);
                printf("         Releases all interfaces of device 15 on bus 3\n");
                return 1;
        }
}
