/* 摘抄一段《用TCP/IP进行网际互连--客户-服务器编程与应用 第三卷》 */
int 
TCPecho(const char *host,const char *service)
{
    char buf[LINELEN+1];   /* buffer for one line of text */
    int s, n;              /* socket descriptor,read count */
    int outchars, inchars; /* characters sent and received */

    s=connectTCP(host,service);

    while(fgets(buf,sizeof(buf),stdin)){
        buf[LINELEN] = '\0';
        outchars = strlen(buf);
        (void)write(s, buf, outchars);

        /* read it back */
        for( inchars = 0; inchars < outchars; inchars+=n ) {
            n = read( s, &buf[inchars], outchars-inchars);
            if( n < 0)
              errexit("socket read failed:%s\n",strerror(errno));
        }
        fputs(buf, stdout);
    }
}