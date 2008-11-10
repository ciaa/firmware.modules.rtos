##############################################################################
# add library


LIB += lwIP.a

GEN += genlwip

LFLAGS +=

LWIP_OBJ +=			api_lib.o					\
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

GENFILES +=	lwIP$(DIR)gen$(DIR)inc$(DIR)lwipopts.h.php

VPATH += lwIP$(DIR)src$(DIR)api						\
			lwIP$(DIR)src$(DIR)core						\
			lwIP$(DIR)src$(DIR)core$(DIR)ipv4			\
			lwIP$(DIR)src$(DIR)core$(DIR)snmp			\
			lwIP$(DIR)src$(DIR)netif						\
			lwIP$(DIR)src$(DIR)$(ARCH)					\
			lwIP$(DIR)src$(DIR)$(ARCH)$(DIR)netif

INCLUDE += 	-IlwIP$(DIR)inc							\
				-IlwIP$(DIR)inc$(DIR)ipv4$(DIR)	\
				-IlwIP$(DIR)inc$(DIR)lwip			\
				-IlwIP$(DIR)inc$(DIR)netif			\
				-IlwIP$(DIR)inc$(DIR)$(ARCH)		\

lwIP.a : $(LWIP_OBJ)
	ar -rcs $(LIBDIR)$(DIR)lwIP.a $(foreach obj, $(LWIP_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=

genlwip:

