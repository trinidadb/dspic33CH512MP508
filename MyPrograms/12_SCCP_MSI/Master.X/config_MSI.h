// ONLY MAILBOX 0 USED. PROTOCOL "A" USED.


// FMBXM
#pragma config MBXM0 = M2S              // Mailbox 0 data direction (Mailbox register configured for Main data write (Main to Secondary data transfer))
#pragma config MBXM1 = S2M              // Mailbox 1 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM2 = S2M              // Mailbox 2 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM3 = S2M              // Mailbox 3 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM4 = S2M              // Mailbox 4 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM5 = S2M              // Mailbox 5 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM6 = S2M              // Mailbox 6 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM7 = S2M              // Mailbox 7 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM8 = S2M              // Mailbox 8 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM9 = S2M              // Mailbox 9 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM10 = S2M             // Mailbox 10 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM11 = S2M             // Mailbox 11 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM12 = S2M             // Mailbox 12 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM13 = S2M             // Mailbox 13 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM14 = S2M             // Mailbox 14 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM15 = S2M             // Mailbox 15 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))

// FMBXHS1
#pragma config MBXHSA = MBX0            // Mailbox handshake protocol block A register assignment (MSIxMBXD0 assigned to mailbox handshake protocol block A)
#pragma config MBXHSB = MBX15           // Mailbox handshake protocol block B register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block B)
#pragma config MBXHSC = MBX15           // Mailbox handshake protocol block C register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block C)
#pragma config MBXHSD = MBX15           // Mailbox handshake protocol block D register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block D)

// FMBXHS2
#pragma config MBXHSE = MBX15           // Mailbox handshake protocol block E register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block E)
#pragma config MBXHSF = MBX15           // Mailbox handshake protocol block F register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block F)
#pragma config MBXHSG = MBX15           // Mailbox handshake protocol block G register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block G)
#pragma config MBXHSH = MBX15           // Mailbox handshake protocol block H register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block H)

// FMBXHSEN
#pragma config HSAEN = ON               // Mailbox A data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled.)
#pragma config HSBEN = OFF              // Mailbox B data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSCEN = OFF              // Mailbox C data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSDEN = OFF              // Mailbox D data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSEEN = OFF              // Mailbox E data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSFEN = OFF              // Mailbox F data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSGEN = OFF              // Mailbox G data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSHEN = OFF              // Mailbox H data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)