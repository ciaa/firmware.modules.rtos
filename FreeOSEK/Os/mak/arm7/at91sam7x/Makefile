##############################################################################
# CPU specific targets
#
OBJCOPY = arm-none-eabi-objcopy
SAMBA = sam-ba_cdc
PORT = com22

bin:
	$(OBJCOPY) -O binary $(BINDIR)$(DIR)$(BIN) $(BINDIR)$(DIR)$(BIN).bin

download:
	$(SAMBA) $(PORT) at91sam7x512-ek FreeOsek$(DIR)Os$(DIR)mak$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)FreeOsek.tcl
