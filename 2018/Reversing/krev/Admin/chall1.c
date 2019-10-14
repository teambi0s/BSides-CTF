#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/device.h>
#include <sys/kernel.h>
#include <sys/md5.h>
#include <sys/sha1.h>
#include <sys/module.h>

#include <sys/kmem.h>
#include <uvm/uvm.h> 

dev_type_open(chall1_open);
dev_type_close(chall1_close);
dev_type_read(chall1_read);
dev_type_write(chall1_write);

#define YOULOSE "Why don't you try again?"
#define BUFFER_LEN 100

static int check_chall(void);
void get_flag_ready(void);
void md5hash(void);
void sha1hash(void);

static struct cdevsw chall1_cdevsw = {
	.d_open = chall1_open,
	.d_close = chall1_close,
	.d_read = chall1_read,
	.d_write = chall1_write,
	.d_ioctl = noioctl,
	.d_stop = nostop,
	.d_tty = notty,
	.d_poll = nopoll,
	.d_mmap = nommap,
	.d_kqfilter = nokqfilter,
	.d_discard = nodiscard,
	.d_flag = D_OTHER
};


struct chall1_softc {
	int		 refcnt;
	unsigned	 last;
	char *buffer;
	char *final_flag;
	int buf_len;
	char md5string[33];
	char sha1string[41];
};

static struct chall1_softc sc;

static int check_chall(void){

	if(sc.buffer[0] != 'g')
		return 1;

	if(sc.buffer[1] != 'i')
		return 1;
	
	if(sc.buffer[2] != 'v')
		return 1;

	if(sc.buffer[3] != 'e')
		return 1;

	if(sc.buffer[4] != '_')
		return 1;

	if(sc.buffer[5] != 't')
		return 1;

	if(sc.buffer[6] != 'h')
		return 1;

	if(sc.buffer[7] != 'i')
		return 1;
	
	if(sc.buffer[8] != 's')
		return 1;

	if(sc.buffer[9] != '_')
		return 1;

	if(sc.buffer[10] != 't')
		return 1;

	if(sc.buffer[11] != 'o')
		return 1;

	if(sc.buffer[12] != '_')
		return 1;

	if(sc.buffer[13] != 'g')
		return 1;

	if(sc.buffer[14] != 'e')
		return 1;

	if(sc.buffer[15] != 't')
		return 1;

	if(sc.buffer[16] != '_')
		return 1;

	if(sc.buffer[17] != 'f')
		return 1;

	if(sc.buffer[18] != 'l')
		return 1;

	if(sc.buffer[19] != 'a')
		return 1;

	if(sc.buffer[20] != 'g')
		return 1;

	return 0;
};

void md5hash(void){
	unsigned char digest[16];
	struct MD5Context context;
	MD5Init(&context);
	MD5Update(&context, sc.buffer, strlen(sc.buffer));
	MD5Final(digest, &context);
	for(int i = 0; i < 16; ++i)
    		snprintf(&sc.md5string[i*2],5, "%02x", (unsigned int)digest[i]);
}

void sha1hash(void) {
	unsigned char digest[20];
	SHA1_CTX context;
	SHA1Init(&context);
	SHA1Update(&context,sc.md5string, strlen(sc.md5string));
	SHA1Final(digest, &context);
	for(int i = 0; i < 20; ++i)
    		snprintf(&sc.sha1string[i*2],5, "%02x", (unsigned int)digest[i]);
}

void
get_flag_ready()
{
	char xor_pack[40] = { 86, 92, 80, 5, 77, 15, 83, 71, 118, 87, 33, 58, 94, 6, 59, 13, 17, 22, 2, 9, 11, 103, 27, 82, 65, 107, 64, 93, 86, 23, 93, 1, 58, 4, 19, 29, 104, 80, 6, 69 };
	md5hash();
	sha1hash();
	for(size_t i = 0; i < strlen(sc.sha1string); i++)
	{
		*(sc.final_flag + i) = (int)*(sc.sha1string + i) ^ (int)*(xor_pack + i);
	}
}

int
chall1_open(dev_t self __unused, int flag __unused, int mode __unused,
           struct lwp *l __unused)
{
	if (sc.refcnt > 0)
		return EBUSY;

	sc.last = 0;
	++sc.refcnt;
	sc.buf_len = BUFFER_LEN;
	sc.buffer = (char *)kmem_alloc(BUFFER_LEN, KM_SLEEP);

	sc.final_flag = (char *)uvm_km_alloc(kernel_map, BUFFER_LEN * sizeof(char),
					0,UVM_KMF_WIRED | UVM_KMF_ZERO);
	return 0;
}

int
chall1_close(dev_t self __unused, int flag __unused, int mode __unused,
            struct lwp *l __unused)
{
	--sc.refcnt;

	return 0;
}

int
chall1_read(dev_t self __unused, struct uio *uio, int flags __unused)
{
	char line[80];
	int e;
	
	int check = check_chall();

	//int check = 0;
	if(check == 0){
		get_flag_ready();
		snprintf(line, strlen(sc.final_flag)+1 , "%s", sc.final_flag);
		if ((e = uiomove(line, strlen(sc.final_flag)+1, uio)))
			return e;
	}else{
		snprintf(line, strlen(YOULOSE)+1 , "%s", YOULOSE);
		if ((e = uiomove(line, strlen(YOULOSE), uio)))
			return e;
	}	

	return 0;
}

int
chall1_write(dev_t self, struct uio *uio, int flags)
{
    if (sc.buffer)
	kmem_free(sc.buffer, sc.buf_len);
    sc.buf_len = uio->uio_iov->iov_len;
    sc.buffer = (char *)kmem_alloc(sc.buf_len, KM_SLEEP);
    uiomove(sc.buffer, sc.buf_len, uio);
    return 0;
}

MODULE(MODULE_CLASS_MISC, chall1, NULL);

static int
chall1_modcmd(modcmd_t cmd, void *arg __unused)
{
	/* The major should be verified and changed if needed to avoid
	 * conflicts with other devices. */
	
	int cmajor = 210, bmajor = -1;

	switch (cmd) {
	case MODULE_CMD_INIT:
		if (devsw_attach("chall1", NULL, &bmajor, &chall1_cdevsw,
				&cmajor))
			return ENXIO;	
		return 0;
	case MODULE_CMD_FINI:
		if (sc.refcnt > 0)
			return EBUSY;
		devsw_detach(NULL, &chall1_cdevsw);
		return 0;
	default:
		return ENOTTY;
	}
	return 0;
}
