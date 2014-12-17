################################################################################
#  Downrload and run FreeOSEK
################################################################################


################################################################################
# Get the variable containing board and connection information
#global target
################################################################################


# Do not unlock sectors if already locked (put 1 to force unlock)
set FLASH::ForceUnlockBeforeWrite 0

# Do not lock used sectors after write operation (put 1 to lock)
set FLASH::ForceLockAfterWrite    0

# Erase all Flash
#FLASH::ScriptEraseAllFlash


send_file {Flash} "out/bin/FreeOSEK.bin" 0x100000 0
#compare_file  {Flash} "out/bin/FreeOSEK.bin" 0x100000 0

# Boot from flash
FLASH::ScriptGPNMV 4

# Close connection. Without this, another connection cannot be established after resetting the board.
#TCL_Close $target(handle)

puts "-I-------------------------------------------------------"
puts "-I- Exemple : FreeOSEK SAM-BA script correctly executed !"
puts "-I-------------------------------------------------------"

