#ifndef		__V4L2_H__
#define		__V4L2_H__
#include <linux/types.h>
#include <linux/videodev2.h>


#ifdef __cplusplus
extern "C" {
#endif

#define IHEIGHT 600
#define IWIDTH 800

typedef	struct
{
    void	*start;
    size_t	length;
}buffer;

typedef	struct
{
    int			fd;
    int			n_buffers;
    char			*dev_name;
    buffer			*buffers;
    struct v4l2_buffer	buf;
    struct v4l2_format 	fmt;
}pass_data;

int init_dev (pass_data *s);
void stop_dev (pass_data *s);
void read_frame(pass_data *s);
void return_data (pass_data *s);

void init_mmap(pass_data *s);
void init_device(pass_data *s);
int open_device(pass_data *s);
void start_capturing(pass_data *s);
void close_device(pass_data *s);
void stop_capturing(pass_data *s);
void stop_device(pass_data *s);
void errno_exit(const char *s);
int xioctl(int fd, int request, void *arg);
void process_image(void *p, pass_data *s, int i);

int convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height);
void yuyv_to_rgb(unsigned char* yuv,unsigned char* rgb);

#ifdef __cplusplus
}
#endif

#endif
