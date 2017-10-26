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
                        fprintf(stderr, "ERROR: Unable to access device\n");
                        return 1;
                }else{
                        command.ioctl_code = USBDEVFS_DISCONNECT;
                        command.data = NULL;
                        for(int i = 0; i < 255; i++){ // Iterate over interfaces
                                command.ifno = i;
                                int ret = ioctl(fd, USBDEVFS_IOCTL, &command); // Send disconnect ioctl event
                                if(ret != -1)
                                        printf("Releasing interface %03d : (%s)\n", i, (!ret) ? "success" : "fail");
                        }
                        return 0;
                }
        }else{
                printf("Usage: %s <BUS> <DEVICE>\n\n", argv[0]);
                printf("<BUS>\n");
                printf("\tRequired.  USB bus ID on which devices are released.\n\n");
                printf("<DEVICE>\n");
                printf("\tRequired.  Specific device ID to release.\n\n");
                printf("Example: %s 003 015\n", argv[0]);
                printf("\tReleases all interfaces of device 15 on bus 3\n");
                return 1;
        }
}
