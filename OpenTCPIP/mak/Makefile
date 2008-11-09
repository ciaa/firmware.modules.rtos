##############################################################################
# add library


LIB += OpenTCPIP.a

GEN += gentcpip

LFLAGS +=

OPENTCPIP_OBJ +=	api_lib.o					\
						api_msg.o					\
						err.o							\
						netbuf.o						\
						netdb.o						\
						netifapi.o					\
						sockets.o					\
						tcpip.o						\
														\
						dhcp.o						\
						init.o						\
						mem.o							\
						netif.o						\
						raw.o							\
						stats.o						\
						tcp.o							\
						tcp_out.o					\
						dns.o							\
						memp.o						\
						pbuf.o						\
						sys.o							\
						tcp_in.o						\
						udp.o							\
														\
						autoip.o						\
						icmp.o						\
						igmp.o						\
						inet.o						\
						inet_chksum.o				\
						ip_addr.o					\
						ip.o							\
						ip_frag.o					\
														\
						asn1_dec.o					\
						asn1_enc.o					\
						mib2.o						\
						mib_structs.o				\
						msg_in.o						\
						msg_out.o					\
														\
						etharp.o						\
						ethernetif.o				\
						loopif.o						\
						slipif.o						\
														\
						delif.o						\
						fifo.o						\
						list.o						\
						pcapif.o						\
						sio.o							\
						tapif.o						\
						tcpdump.o					\
						tunif.o						\
						unixif.o		

GENFILES +=	OpenTCPIP$(DIR)gen$(DIR)inc$(DIR)lwipopts.h.php

VPATH += OpenTCPIP$(DIR)src$(DIR)api						\
			OpenTCPIP$(DIR)src$(DIR)core						\
			OpenTCPIP$(DIR)src$(DIR)core$(DIR)ipv4			\
			OpenTCPIP$(DIR)src$(DIR)core$(DIR)snmp			\
			OpenTCPIP$(DIR)src$(DIR)netif						\
			OpenTCPIP$(DIR)src$(DIR)$(ARCH)					\
			OpenTCPIP$(DIR)src$(DIR)$(ARCH)$(DIR)netif

INCLUDE += 	-IOpenTCPIP$(DIR)inc							\
				-IOpenTCPIP$(DIR)inc$(DIR)ipv4$(DIR)	\
				-IOpenTCPIP$(DIR)inc$(DIR)lwip			\
				-IOpenTCPIP$(DIR)inc$(DIR)netif			\
				-IOpenTCPIP$(DIR)inc$(DIR)$(ARCH)		\

OpenTCPIP.a : $(OPENTCPIP_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenTCPIP.a $(foreach obj, $(OPENTCPIP_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=

gentcpip:

